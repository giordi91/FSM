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

namespace FSMEditor
{
    /// <summary>
    /// Follow steps 1a or 1b and then 2 to use this custom control in a XAML file.
    ///
    /// Step 1a) Using this custom control in a XAML file that exists in the current project.
    /// Add this XmlNamespace attribute to the root element of the markup file where it is 
    /// to be used:
    ///
    ///     xmlns:MyNamespace="clr-namespace:FSMEditor"
    ///
    ///
    /// Step 1b) Using this custom control in a XAML file that exists in a different project.
    /// Add this XmlNamespace attribute to the root element of the markup file where it is 
    /// to be used:
    ///
    ///     xmlns:MyNamespace="clr-namespace:FSMEditor;assembly=FSMEditor"
    ///
    /// You will also need to add a project reference from the project where the XAML file lives
    /// to this project and Rebuild to avoid compilation errors:
    ///
    ///     Right click on the target project in the Solution Explorer and
    ///     "Add Reference"->"Projects"->[Browse to and select this project]
    ///
    ///
    /// Step 2)
    /// Go ahead and use your control in the XAML file.
    ///
    ///     <MyNamespace:CustomNode/>
    ///
    /// </summary>
    [System.ComponentModel.DefaultBindingProperty("NodeName")]
    public class CustomNode : Control
    {

        public CustomNode(ref Canvas canvas)
        {
            /*
            m_in = new Plug(this);
            m_out = new Plug(this);
            canvas.Children.Add(this);
            canvas.Children.Add(m_in);
            Panel.SetZIndex(this, 2);
            Panel.SetZIndex(m_in, 3);
            x = 0;
            y = 0;
            */
            
            Loaded += CustomNode_Loaded;
        }

        private void CustomNode_Loaded(object sender, RoutedEventArgs e)
        {
            var obj= this.GetTemplateChild("body");
            if (obj != null)
            {
                m_body_canvas = obj as Canvas;
            }

            obj= this.GetTemplateChild("NodeNameText");
            if (obj != null)
            {
                Console.WriteLine("found text block");
            }
        }

        public void move( int x, int y)
        {
            Canvas.SetLeft(this, x);
            Canvas.SetTop(this, y);
            
        }




        public string NodeName
        {
            get { return (string)GetValue(NodeNameProperty); }
            set { SetValue(NodeNameProperty, value); }
        }

        // Using a DependencyProperty as the backing store for NodeName.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty NodeNameProperty =
            DependencyProperty.Register("NodeName", typeof(string), typeof(CustomNode), 
                                new PropertyMetadata(String.Empty, OnNodeNameChanged));

        private static void OnNodeNameChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            Console.WriteLine("callback");            
        }

        static CustomNode()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(CustomNode), new FrameworkPropertyMetadata(typeof(CustomNode)));
        }

        public void print()
        {
            Console.WriteLine("hello .... it s meeeeee");
        }


        public Plug m_in;
        public Plug m_out;
        public int x;
        public int y;
        Canvas m_body_canvas;
        String m_name;
    }
}
