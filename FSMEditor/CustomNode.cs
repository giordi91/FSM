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
using System.ComponentModel;
using FSMWrapper;
namespace FSMEditor
{
    public class CustomNode : Control
    {
        static Color BACKGROUND_COLOR = (Color)ColorConverter.ConvertFromString("#FF1C1C25");
        static Color SELECTED_COLOR   = (Color)ColorConverter.ConvertFromString("#FF093800");
        

        public CustomNode()
        {
            this.DataContext = this;
            //create instance of the state
            m_state = new StateWrapper();
        }

        public void move( int x, int y)
        {
            Canvas.SetLeft(this, x);
            Canvas.SetTop(this, y);
        }

        public string NodeName
        {
            get {
                Console.WriteLine("Getting name " );
                Console.WriteLine(m_state.get_name());
                return m_state.get_name(); }
            set
            {
                Console.WriteLine("Writing name");
                m_state.set_name(value); 
            }
        }


        #region Graphic related
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
            Canvas.SetLeft(this, currX + deltaX);
            Canvas.SetTop(this, currY + deltaY);

            //need to update plugs if there 
            Plug inp = this.GetTemplateChild("m_in") as Plug;
            Plug outp = this.GetTemplateChild("m_out") as Plug;

            var conns = inp.GetConnections();
            if (conns.Count() != 0 )
            {

                Point pnt = new Point(inp.X + currX +10,
                                      inp.Y + currY +10);
                foreach (var conn in conns)
                {
                    if (conn.StartPlug == inp)
                    {
                        conn.StartPoint = pnt;
                    }
                    else
                    {
                        conn.EndPoint = pnt;
                    }
                }
            }

            conns = outp.GetConnections();
            if (conns.Count() != 0 )
            {

                Point pnt = new Point(outp.X + currX + 10,
                                      outp.Y + currY + 10);
                foreach (var conn in conns)
                {
                    if (conn.StartPlug == outp)
                    {
                        conn.StartPoint = pnt;
                    }
                    else
                    {
                        conn.EndPoint = pnt;
                    }
                }
            }
        }

        public void CleanUpBeforeDelete(ViewModel view_model)
        {
            Plug inp = this.GetTemplateChild("m_in") as Plug;
            Plug outp = this.GetTemplateChild("m_out") as Plug;
            var conns = inp.GetConnections();
            foreach (var conn in inp.GetConnections())
            {
                conn.StartPlug.IsSelected = false;
                conn.EndPlug.IsSelected = false;
                view_model.Connections.Remove(conn);
            }

            conns = outp.GetConnections();
            foreach (var conn in conns)
            {
                conn.StartPlug.IsSelected = false;
                conn.EndPlug.IsSelected = false;
                view_model.Connections.Remove(conn);
            }
        }

        public double X
        {
            get {
                Console.WriteLine("GETTING!");
                return (double)GetValue(XProperty); }
            set {
                Console.WriteLine("property changed");
                SetValue(XProperty, value); }
        }

        // Using a DependencyProperty as the backing store for X.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty XProperty =
            DependencyProperty.Register("X", typeof(double), typeof(CustomNode), new PropertyMetadata(0.0));

        public double Y
        {
            get { return (double)GetValue(YProperty); }
            set { SetValue(YProperty, value); }
        }

        // Using a DependencyProperty as the backing store for X.  This enables animation, styling, binding, etc...
        // Using a DependencyProperty as the backing store for X.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty YProperty =
            DependencyProperty.Register("Y", typeof(double), typeof(CustomNode), new PropertyMetadata(0.0) );


        static CustomNode()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(CustomNode), new FrameworkPropertyMetadata(typeof(CustomNode)));
        }

        #endregion


        //private delcarations
        private bool m_is_selected;
        public StateWrapper m_state;
    }
}
