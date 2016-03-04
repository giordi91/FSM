using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
using System.IO;
using System.ComponentModel;
namespace FSMEditor
{




    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            //MouseLeftButtonDown += MainWindow_MouseLeftButtonDown;
            //MouseLeftButtonUp += MainWindow_MouseLeftButtonUp;
            //MouseMove += MainWindow_MouseMove;
            //KeyDown += MainWindow_KeyDown;
            view_model = (this.DataContext as ViewModel);
            // conn_model = this.ConnectionViewer as ListBox;
        }

        private void MainWindow_KeyDown(object sender, KeyEventArgs e)
        {
            Console.WriteLine("delete");
            if (e.Key == Key.Back || e.Key == Key.Delete)
            {
                if (m_selected != null)
                {
                    if (m_selected is CustomNode)
                    {
                        var node = m_selected as CustomNode;
                        node.CleanUpBeforeDelete(view_model);
                        view_model.Rectangles.Remove(node);
                    }
                    else if (m_selected is Connection)
                    {
                        var conn = m_selected as Connection;
                        conn.CleanUpBeforeDelete(view_model);
                        view_model.Connections.Remove(conn);
                    }
                }
                m_selected = null;
            }

        }

        private void MainWindow_MouseMove(object sender, System.Windows.Input.MouseEventArgs e)
        {
            if (m_dragging)
            {
                var view = (ItemsControl)this.FindName("view");
                var pos = e.GetPosition(view);
                if (m_selected != null)
                {
                    if (m_selected is CustomNode)
                    {
                        int deltaX = (int)pos.X - (int)m_mouse_pos.X;
                        int deltaY = (int)pos.Y - (int)m_mouse_pos.Y;
                        ((CustomNode)m_selected).moveRelative(deltaX, deltaY);
                    }
                    if (m_selected is Connection)
                    {

                        var conn = (m_selected as Connection);
                        double multX = ((pos.X - conn.StartPoint.X) * 0.95);
                        double multY = ((pos.Y - conn.StartPoint.Y) * 0.95);
                        double x = conn.StartPoint.X + multX;
                        double y = conn.StartPoint.Y + multY;
                        conn.EndPoint = new Point(x, y);
                        if (conn.EndPlug != null)
                        {
                            conn.EndPlug.IsSelected = false;
                        }
                    }
                }
                m_mouse_pos = pos;
            }
        }

        private void MainWindow_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            m_dragging = false;
            if (e.OriginalSource is Ellipse)
            {
                Plug p = find_visual_parent<Plug>(e.OriginalSource as DependencyObject);

                //first let check we have something selected
                if (m_selected != null)
                {
                    //is it a connection?
                    if (m_selected is Connection)
                    {
                        //if so cast it to connection
                        var conn = m_selected as Connection;
                        //if we  ha have the connection selected we make sure to
                        //set the right color
                        if (conn.IsSelected == true)
                        {
                            p.IsConnectionSelected = true;
                        }
                        else
                        {
                            p.IsSelected = true;
                        }

                        //create the connection
                        CustomNode node = find_visual_parent<CustomNode>(e.OriginalSource as DependencyObject);
                        var x = Canvas.GetLeft(node);
                        var y = Canvas.GetTop(node);

                        Ellipse ell = e.OriginalSource as Ellipse;
                        var radius = ell.Width / 2;

                        conn.EndPoint = new Point(x + p.X + radius, y + p.Y + radius);
                        conn.EndPlug = p;
                        var srcNode = find_visual_parent<CustomNode>(conn.StartPlug); 
                        var destNode = find_visual_parent<CustomNode>(p);

                        conn.FinalizeConnection(view_model.m_fsm, srcNode.m_state,
                                                destNode.m_state);
                        //ConditionBinding cb = new ConditionBinding(conn.cond);
                        p.AddConnection( conn);
                        //conn.Conditions.Add(cb);
                        //conn.conn.add_conditions(cb.m_wrapCond);
                        conn = null;
                        clear_selection();
                        return;
                    }
                }
            }
            else
            {
                var view = (ItemsControl)this.FindName("view");

                var isNull = m_selected != null;
                var isConnection = m_selected is Connection;
                var sourceisnotconn = !(e.OriginalSource is Connection);
                //check if anything is selected
                if (m_selected != null
                        //that what is selected is a connection
                        && m_selected is Connection
                        //also that the original source is not a connecton otherwise
                        //if we lift the mouse when a connection is selected we delete it
                        && !(e.OriginalSource is Connection))
                {
                    var conn = m_selected as Connection;
                    if (conn.StartPlug != null)
                    {
                        conn.StartPlug.IsSelected = false;
                    }
                    if (conn.EndPlug != null)
                    {
                        conn.EndPlug.IsSelected = false;
                    }
                    // view.Children.Remove(conn);
                    
                    view_model.Connections.Remove(conn);
                    conn = null;
                    m_selected = null;
                    clear_selection();
                }
            }
        }

        private void MainWindow_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            m_dragging = true;
            var view = (ItemsControl)this.FindName("view");
            m_mouse_pos = e.GetPosition(view);
            // Canvas foundCanvas = UIHelper.FindChild<Canvas>(Application.Current.MainWindow, "MarkerCanvas");

            if (e.OriginalSource is Rectangle)
            {
                CustomNode node = find_visual_parent<CustomNode>(e.OriginalSource as DependencyObject);
                clear_selection();
                node.IsSelected = true;
                m_selected = node;
                return;
            }
            else if (e.OriginalSource is Ellipse)
            {
                Plug p = find_visual_parent<Plug>(e.OriginalSource as DependencyObject);
                clear_selection();

                //create the connection
                var conn = new Connection();
                CustomNode node = find_visual_parent<CustomNode>(e.OriginalSource as DependencyObject);
                var x = Canvas.GetLeft(node);
                var y = Canvas.GetTop(node);

                //adding cross referencing
                p.AddConnection( conn);
                p.IsSelected = true;
                conn.StartPlug = p;


                Ellipse ell = e.OriginalSource as Ellipse;
                var radius = ell.Width / 2;

                conn.StartPoint = new Point(x + p.X + radius, y + p.Y + radius);
                conn.EndPoint = new Point(x + p.X + radius, y + p.Y + radius);
                view_model.Connections.Add(conn);
                m_selected = conn;
                return;
            }
            else if (e.OriginalSource is Connection)
            {
                clear_selection();
                Connection conn = e.OriginalSource as Connection;

                conn.IsSelected = true;
                m_selected = conn;
                /*
                view_model.m_conditions.Clear();
                foreach (var cond in conn.Conditions)
                {
                    
                    view_model.m_conditions.Add(cond); }
                
                */

                    ConnectionViewer.DataContext = conn;
                // view_model.Conditions= conn.Conditions;
                Console.WriteLine("connetionnn");
                return;
            }

            clear_selection();

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            System.Console.WriteLine("Pressing");
            // var view = (Canvas)this.FindName("view");
            var n = new CustomNode();
            n.move(100, 100);
            n.NodeName = "Jumping";
            //view.Children.Add(n);
            //m_nodes.Add(n);
            view_model.Rectangles.Add(n);
        }

        private T find_visual_parent<T>(DependencyObject obj)
            where T : DependencyObject
        {
            Console.WriteLine("walk");
            DependencyObject parent = VisualTreeHelper.GetParent(obj);
            if (parent is T)
                return (T)parent;
            else
                return find_visual_parent<T>(parent);
        }
        private void clear_selection()
        {
            if (m_selected != null)
            {
                if (m_selected is CustomNode)
                {
                    var obj = m_selected as CustomNode;
                    obj.IsSelected = false;
                }
                else if (m_selected is Connection)
                {
                    var obj = m_selected as Connection;
                    obj.IsSelected = false;
                }
                m_selected = null;
            }

            this.ConnectionViewer.DataContext = null;
            //view_model.Conditions = new System.Collections.ObjectModel.ObservableCollection<ConditionBinding>();
            //view_model.Conditions = null;
        }

        private bool m_dragging;
        Point m_mouse_pos;
        private object m_selected;
        private ViewModel view_model;

        private void addbutton2_Click(object sender, RoutedEventArgs e)
        {
            Console.WriteLine("Saving");
            string data = view_model.m_fsm.serialize();
            Console.WriteLine(data);
            string path = @"E:\WORK_IN_PROGRESS\C\FSM\FSMEditor\bin\textOut.fsm";
            string folder = System.IO.Path.GetDirectoryName(Process.GetCurrentProcess().MainModule.FileName) + @"\textOut.fsm";
            Console.WriteLine(folder);

            System.IO.File.WriteAllText(folder, data);

        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (string.IsNullOrEmpty(((TextBox)sender).Text))
                maintainsession = "";
            else
            {
                double num = 0;
                bool success = double.TryParse(((TextBox)sender).Text, out num);
                if (success & num >= 0)
                {
                    ((TextBox)sender).Text.Trim();
                    maintainsession = ((TextBox)sender).Text;
                }
                else
                {
                    ((TextBox)sender).Text = maintainsession;
                    ((TextBox)sender).SelectionStart = ((TextBox)sender).Text.Length;
                }
            }
        }
        private string maintainsession;

        private void Add_Click(object sender, RoutedEventArgs e)
        {
            if (m_selected != null && m_selected is Connection)
            {
                var conn = m_selected as Connection;
                var dialog = new AddConditionDialog(conn, view_model);
                dialog.Show();
            }
        }

    }
}
