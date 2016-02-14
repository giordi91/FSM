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
            if (m_dragging && m_selected_node != null)
            {

                var view = (Canvas)this.FindName("view");
                var pos = e.GetPosition(view);
                int deltaX = (int)pos.X - (int)m_mouse_pos.X;
                int deltaY = (int)pos.Y - (int)m_mouse_pos.Y;
                Console.WriteLine(deltaX);
                m_selected_node.moveRelative(deltaX, deltaY);
                //m_selected_node.move((int)pos.X, (int)pos.Y);
                m_mouse_pos = pos;
            }
        }

        private void MainWindow_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            m_dragging = false;
        }

        private void MainWindow_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            m_dragging = true;
            var view= (Canvas)this.FindName("view");
            m_mouse_pos = e.GetPosition(view);
            Console.WriteLine("left downnn");
            if (e.OriginalSource is Rectangle)
            {
                CustomNode node = find_visual_parent<CustomNode>(e.OriginalSource as DependencyObject);
                if (m_selected_node != null)
                {
                    m_selected_node.IsSelected = false;
                }
                node.print();
                node.IsSelected = true;
                m_selected_node = node;
                return;

            }
            else if (e.OriginalSource is Ellipse)
            {
                Plug p = find_visual_parent<Plug>(e.OriginalSource as DependencyObject);
                p.print();
                return;
            }

            if (m_selected_node != null)
            {
                m_selected_node.IsSelected = false;
                m_selected_node = null;
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
        public List<CustomNode> m_nodes;
        private Dictionary<Object, Node> m_data; 
        private bool m_dragging;
        Point m_mouse_pos;
    }
}
