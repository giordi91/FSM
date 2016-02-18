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
using System.Windows.Forms;
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
            m_nodes = new List<CustomNode>();
            m_conns = new List<Connection>();

            MouseLeftButtonDown += MainWindow_MouseLeftButtonDown;
            MouseLeftButtonUp += MainWindow_MouseLeftButtonUp;
            MouseMove += MainWindow_MouseMove;
        }
        
        private void MainWindow_MouseMove(object sender, System.Windows.Input.MouseEventArgs e)
        {
            if (m_dragging)
            {
                var view = (Canvas)this.FindName("view");
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

                if (m_selected != null)
                {
                    if (m_selected is Connection)
                    {
                        var conn = m_selected as Connection;
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
                        p.AddConnection( conn);
                        m_conns.Add(conn);
                        conn = null;
                        clear_selection();
                        return;
                    }
                }
            }
            else
            {
                var view = (Canvas)this.FindName("view");
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
                    view.Children.Remove(conn);
                    conn = null;
                    m_selected = null;
                    clear_selection();
                }
            }
            Console.WriteLine(e.OriginalSource);
        }

        private void MainWindow_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            m_dragging = true;
            var view = (Canvas)this.FindName("view");
            m_mouse_pos = e.GetPosition(view);

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
                view.Children.Add(conn);
                m_selected = conn;
                return;
            }
            else if (e.OriginalSource is Connection)
            {
                clear_selection();
                Connection conn = e.OriginalSource as Connection;

                conn.IsSelected = true;
                m_selected = conn;

                return;
            }

            clear_selection();

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            System.Console.WriteLine("Pressing");
            var view = (Canvas)this.FindName("view");
            var n = new CustomNode();
            n.move(100, 100);
            n.NodeName = "Jumping";
            view.Children.Add(n);
            m_nodes.Add(n);
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
        }
        public List<CustomNode> m_nodes;
        public List<Connection> m_conns;
        private bool m_dragging;
        Point m_mouse_pos;
        private object m_selected;
    }
}
