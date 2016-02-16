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
            m_data = new Dictionary<object, Node>();
            m_nodes= new List<CustomNode>();

            MouseLeftButtonDown += MainWindow_MouseLeftButtonDown;
            MouseLeftButtonUp += MainWindow_MouseLeftButtonUp;
            MouseMove += MainWindow_MouseMove;
        }

        private void MainWindow_MouseMove(object sender, System.Windows.Input.MouseEventArgs e)
        {
            if (m_dragging )
            {
                var pos = e.GetPosition(view);
                if (m_selected_node != null)
                {
                    var view = (Canvas)this.FindName("view");
                    int deltaX = (int)pos.X - (int)m_mouse_pos.X;
                    int deltaY = (int)pos.Y - (int)m_mouse_pos.Y;
                    m_selected_node.moveRelative(deltaX, deltaY);


                }
                else if (m_conn!= null)
                {
                    var copy = pos;
                    copy.X -= 2;
                    copy.Y -= 2;
                    m_conn.EndPoint = copy;
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
                if (m_selected_node != null)
                {
                    m_selected_node.IsSelected = false;
                    m_selected_node = null;
                }
                p.IsSelected = true;
                m_selected_plug = null;

                //create the connection
                CustomNode node = find_visual_parent<CustomNode>(e.OriginalSource as DependencyObject);
                var x = Canvas.GetLeft(node);
                var y = Canvas.GetTop(node);

                Ellipse ell = e.OriginalSource as Ellipse;
                var radius = ell.Width / 2;

                m_conn.EndPoint = new Point(x + p.X + radius, y + p.Y + radius);
                m_conn.EndPlug = p;
                p.ConnectionObject = m_conn;
                return;
            }
            else
            {
                if (m_conn != null)
                {
                    if (m_conn.StartPlug != null)
                    {
                        m_conn.StartPlug.IsSelected = false;
                    }
                    var view= (Canvas)this.FindName("view");
                    view.Children.Remove(m_conn);
                    m_conn = null;
                }
            }
            Console.WriteLine(e.OriginalSource);
        }

        private void MainWindow_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            m_dragging = true;
            var view= (Canvas)this.FindName("view");
            m_mouse_pos = e.GetPosition(view);

            if (e.OriginalSource is Rectangle)
            {
                CustomNode node = find_visual_parent<CustomNode>(e.OriginalSource as DependencyObject);
                if (m_selected_node != null)
                {
                    m_selected_node.IsSelected = false;
                }
                if (m_selected_plug != null)
                {
                    m_selected_plug.IsSelected = false;
                    m_selected_plug = null;
                }

                node.IsSelected = true;
                m_selected_node = node;
                return;
            }
            else if (e.OriginalSource is Ellipse)
            {
                Plug p = find_visual_parent<Plug>(e.OriginalSource as DependencyObject);
                if (m_selected_node != null)
                {
                    m_selected_node.IsSelected = false;
                    m_selected_node = null;
                }
                if (m_selected_plug != null)
                {
                    m_selected_plug.IsSelected = false;
                    m_selected_plug = null;
                }
                p.IsSelected = true;
                m_selected_plug = p;

                //create the connection
                m_conn = new Connection();
                CustomNode node = find_visual_parent<CustomNode>(e.OriginalSource as DependencyObject);
                var x = Canvas.GetLeft(node );
                var y = Canvas.GetTop(node);

                //adding cross referencing
                p.ConnectionObject = m_conn;
                m_conn.StartPlug = p;


                Ellipse ell = e.OriginalSource as Ellipse;
                var radius = ell.Width / 2;
                m_conn.StartPoint = new Point(x +p.X + radius ,y +p.Y + radius);
                m_conn.EndPoint= new Point(x + p.X + radius, y+p.Y + radius);
                view.Children.Add(m_conn);
                return;
            }
            else if (e.OriginalSource is Connection)
            {
                Connection conn = e.OriginalSource as Connection;
            }

            if (m_selected_node != null)
            {
                m_selected_node.IsSelected = false;
                m_selected_node = null;
            }
                if (m_selected_plug != null)
                {
                    m_selected_plug.IsSelected = false;
                    m_selected_plug = null;
                }

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            System.Console.WriteLine("Pressing");
            var view= (Canvas)this.FindName("view");
            var n = new CustomNode();
            n.move( 100, 100);
            n.NodeName= "Jumping";
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


        public CustomNode m_selected_node;
        public Plug m_selected_plug;
        public List<CustomNode> m_nodes;
        private Dictionary<Object, Node> m_data; 
        private bool m_dragging;
        Point m_mouse_pos;
        private Connection m_conn;
    }
}
