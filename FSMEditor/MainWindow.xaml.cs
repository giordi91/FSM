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
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            System.Console.WriteLine("Pressing");
            var view= (Canvas)this.FindName("view");
            var n = new CustomNode( ref view );
            m_node = n;
            m_node.move( 100, 100);
            m_node.NodeName= "FUFFAAAAAAA";
            view.Children.Add(m_node);
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


        private void view_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            // System.Console.WriteLine(e.OriginalSource.ToString()); 
            //System.Console.WriteLine("Pressing");


            if (e.OriginalSource is Rectangle)
            {
                CustomNode node = find_visual_parent<CustomNode>(e.OriginalSource as DependencyObject);
                node.print();
            }
            else if (e.OriginalSource is Ellipse)
            {
                Plug p = find_visual_parent<Plug>(e.OriginalSource as DependencyObject);
                p.print();
            }

            /*
            if (m_node != null)
            {
                var view= (Canvas)this.FindName("view");
                var pos = Mouse.GetPosition(view);
                System.Console.Write(pos);
                m_node.move(ref view, (int)pos.X, (int)pos.Y);

            }
            */

        }


        public CustomNode m_node;
        private Dictionary<Object, Node> m_data; 
    }
}
