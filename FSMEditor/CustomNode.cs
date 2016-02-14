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
    public class CustomNode : Control
    {
        static Color BACKGROUND_COLOR = (Color)ColorConverter.ConvertFromString("#FF1C1C25");
        static Color SELECTED_COLOR   = (Color)ColorConverter.ConvertFromString("#FF093800");
        

        public CustomNode()
        {

        }

        public void move( int x, int y)
        {
            Canvas.SetLeft(this, x);
            Canvas.SetTop(this, y);
        }

        public string NodeName { get; set; }

        public bool IsSelected
        {
            get { return m_is_selected; }
            set
            {
                m_is_selected = value;
                var obj = this.GetTemplateChild("body");
                if (obj != null)
                {
                    Rectangle rect = obj as Rectangle;
                    if (value)
                    {
                        rect.Fill = new SolidColorBrush(SELECTED_COLOR);
                    }
                    else
                    {
                        rect.Fill = new SolidColorBrush(BACKGROUND_COLOR);
                    }
                }
            }
        }

        internal void moveRelative(int deltaX, int deltaY)
        {
            int currX = (int)Canvas.GetLeft(this);
            int currY = (int)Canvas.GetTop(this);
            Console.WriteLine("current X");
            Console.WriteLine(currX);
            Canvas.SetLeft(this, currX + deltaX);
            Canvas.SetTop(this, currY + deltaY);
        }

        static CustomNode()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(CustomNode), new FrameworkPropertyMetadata(typeof(CustomNode)));
        }

        public void print()
        {
            Console.WriteLine("hello .... it s meeeeee");
        }
        bool m_is_selected;
    }
}
