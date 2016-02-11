using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Shapes;
using System.Windows.Media;
using System.Windows.Controls;
using System.Drawing;
using System.Windows;

namespace FSMEditor
{
    public class Node: Shape
    {
        static Color BACKGROUND_COLOR = (Color)ColorConverter.ConvertFromString("#FF1C1C25");
        static Color BORDER_COLOR = (Color)ColorConverter.ConvertFromString("#FF2EE411");
        static Color PLUG_COLOR = (Color)ColorConverter.ConvertFromString("Gray");
        static int BORDER_THICKNESS = 3;
        static int SMOOTH_CORNER = 10;
        static int NODE_WIDTH = 140;
        static int NODE_HEIGHT = 100;
        static int PLUG_DIAMETER = 20;
        static int PLUG_Y_OFFSET = NODE_HEIGHT / 2 - PLUG_DIAMETER / 2;
        static int PLUG_X_IN_OFFSET = 2;
        static int PLUG_X_OUT_OFFSET = NODE_WIDTH - PLUG_DIAMETER - PLUG_X_IN_OFFSET;

        //       <Rectangle Fill="#FF1C1C25" Height="100" Stroke="#FF2EE411" Width="135" Canvas.Left="149" Canvas.Top="95" RadiusX="10" RadiusY="10" StrokeThickness="5"/>
        public Node(ref Canvas canvas, int x =0, int y = 0)
        {
            System.Console.WriteLine("Constructor called");
            m_body = new Rectangle();
            m_body.Fill = new SolidColorBrush(BACKGROUND_COLOR);
            m_body.Stroke = new SolidColorBrush(BORDER_COLOR);
            m_body.RadiusX = SMOOTH_CORNER;
            m_body.RadiusY = SMOOTH_CORNER;
            m_body.Width = NODE_WIDTH;
            m_body.Height = NODE_HEIGHT;
            m_body.StrokeThickness = BORDER_THICKNESS;

            //create input output connection
            m_in = new Ellipse();
            m_in.Fill = new SolidColorBrush(PLUG_COLOR);
            m_in.Stroke = new SolidColorBrush(BORDER_COLOR);
            m_in.StrokeThickness = 3;
            m_in.Width = PLUG_DIAMETER;
            m_in.Height = PLUG_DIAMETER;

            m_out = new Ellipse();
            m_out.Fill = new SolidColorBrush(PLUG_COLOR);
            m_out.Stroke = new SolidColorBrush(BORDER_COLOR);
            m_out.StrokeThickness = 3;
            m_out.Width = PLUG_DIAMETER;
            m_out.Height = PLUG_DIAMETER;

            //add_to_canvas(ref canvas);
            move(ref canvas, x, y);

            m_body.Measure(new Size(NODE_WIDTH, NODE_HEIGHT));
            var r = new Rect();
            m_body.Arrange(r);
        }

        public void add_to_canvas(ref Canvas canvas)
        {
            canvas.Children.Add(m_body);
            Panel.SetZIndex(m_body, 2);
            canvas.Children.Add(m_in);
            Panel.SetZIndex(m_in, 3);
            Canvas.SetLeft(m_in, PLUG_X_IN_OFFSET);
            Canvas.SetTop(m_in, PLUG_Y_OFFSET);

            canvas.Children.Add(m_out);
            Panel.SetZIndex(m_out, 3);
            Canvas.SetLeft(m_out, 2);
            Canvas.SetLeft(m_out, PLUG_X_OUT_OFFSET);
            Canvas.SetTop(m_out, PLUG_Y_OFFSET);
        }


        public void move(ref Canvas canvas, int x, int y)
        {
            x -= NODE_WIDTH / 2;
            y -= NODE_HEIGHT/ 2;
            Canvas.SetLeft(m_body, x);
            Canvas.SetTop(m_body, y);

            Canvas.SetLeft(m_in, x + PLUG_X_IN_OFFSET);
            Canvas.SetTop(m_in, y + PLUG_Y_OFFSET);

            Canvas.SetLeft(m_out, x + PLUG_X_OUT_OFFSET);
            Canvas.SetTop(m_out, y + PLUG_Y_OFFSET);

        }

        public void set_selected(bool value)
        {
            m_selected = value;
            if (value)
            {
                m_body.Fill = new SolidColorBrush(Color.FromArgb(255, 255, 0, 0));
            }
            else
            {
                m_body.Fill = new SolidColorBrush(BACKGROUND_COLOR); 
            }
        }

        public void register_node(ref Dictionary<Object, Node> data)
        {
            data[m_body]= this;
            data.Add((Object)m_in, this);
            data[m_out] = this;
        }

        public string get_text()
        {
            return "fuffa";
        }
        protected override Geometry DefiningGeometry
        {
            get
            {

                Console.WriteLine("GETTING");
                // Create a StreamGeometry for describing the shape
                StreamGeometry geometry = new StreamGeometry();
                geometry.FillRule = FillRule.EvenOdd;

                using (StreamGeometryContext context = geometry.Open())
                {
                    InternalDrawArrowGeometry(context);
                }

                // Freeze the geometry for performance benefits
                geometry.Freeze();


                //return geometry;
                return m_body.RenderedGeometry;
            }
        }
        private void InternalDrawArrowGeometry(StreamGeometryContext context)
        {

            Point pt1 = new Point(0, 0);
            Point pt2 = new Point(100, 100);
            context.BeginFigure(pt1, true, true);
            context.LineTo(pt2, true, true);
        }

        private Rectangle m_body;
        private Ellipse m_in;
        private Ellipse m_out;
        private bool m_selected;
    }




} 