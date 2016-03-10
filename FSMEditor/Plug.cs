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
 
    public class Plug : Control
    {
        static Color SELECTED_COLOR = (Color)ColorConverter.ConvertFromString("#FFF5A00C");
        static Color SELECTED_CONN_COLOR = (Color)ColorConverter.ConvertFromString("Yellow");
        static Color BACKGROUND_COLOR = (Color)ColorConverter.ConvertFromString("Gray");


        public Plug()
        {
            this.DataContext = this;
            m_connections = new List<Connection>();            
        }

        static Plug()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(Plug), new FrameworkPropertyMetadata(typeof(Plug)));
        }

        public bool IsSelected
        {
            get { return m_is_selected; }
            set
            {
                m_is_selected = value;
                var obj = this.GetTemplateChild("PlugVisual");
                if (obj != null)
                {
                    var ell= obj as Ellipse;
                    if (value)
                    {
                        ell.Fill = new SolidColorBrush(SELECTED_COLOR);
                    }
                    else
                    {
                        ell.Fill = new SolidColorBrush(BACKGROUND_COLOR);
                    }
                }
            }
        }

        public bool IsConnectionSelected
        {
            get { return m_connection_is_selected; }
            set
            {
                m_connection_is_selected= value;
                var obj = this.GetTemplateChild("PlugVisual");
                if (obj != null)
                {
                    var ell = obj as Ellipse;
                    if (value)
                    {
                        ell.Fill = new SolidColorBrush(SELECTED_CONN_COLOR);
                    }
                    else
                    {
                        ell.Fill = new SolidColorBrush(SELECTED_COLOR);
                    }
                }
            }
        }

        public int X { get; set; }
        public int Y { get; set; }
        /*
        public int X
        {
            get { return (int)Canvas.GetLeft(this); }
        }
        public int Y 
        {
            get { return (int)Canvas.GetTop(this); }
        }
        */

        public void AddConnection(Connection conn)
        {
            if (!m_connections.Contains(conn))
            {
                m_connections.Add(conn);
            }
        }
        public void RemoveConnection(Connection conn)
        {
            foreach (var m_conn in m_connections)
            {
                m_connections.Remove(conn);
            }
        }

        public List<Connection> GetConnections()
        {
            return m_connections;
        }
        private bool m_is_selected;
        private bool m_connection_is_selected;
        private List<Connection> m_connections;

    }

}
