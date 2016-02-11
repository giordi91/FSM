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
            Node n = new Node(ref view, 200,100);
            m_node = n;
            //m_node.Fill = new SolidColorBrush(Color.FromArgb(255, 255, 0, 0));
            //m_node.Stroke= new SolidColorBrush(Color.FromArgb(255, 255, 0, 0));
            view.Children.Add(m_node);
            //n.register_node(ref m_data);
            Console.WriteLine(m_data.Count);
        }

        private void view_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            System.Console.WriteLine(e.OriginalSource.ToString()); 
            System.Console.WriteLine("Pressing");
            /*
            if (m_node != null)
            {
                var view= (Canvas)this.FindName("view");
                var pos = Mouse.GetPosition(view);
                System.Console.Write(pos);
                m_node.move(ref view, (int)pos.X, (int)pos.Y);

            }
            */
            Console.WriteLine(e.OriginalSource.ToString());
            if (e.OriginalSource is Node)
            {
                Console.WriteLine(((Node)e.OriginalSource).get_text());
            }
                if (m_data.ContainsKey(e.OriginalSource))
                {
                    Console.WriteLine("we got a node");
                    Console.WriteLine(m_data[e.OriginalSource].get_text());
                }

        }


        public Node m_node;
        private Dictionary<Object, Node> m_data; 
    }
}
