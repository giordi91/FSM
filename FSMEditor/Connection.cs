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
using System.Drawing;

namespace FSMEditor
{
    public class Connection : Shape 
    {
        public Connection()
        {
            Stroke= new SolidColorBrush((Color)ColorConverter.ConvertFromString("#FFF5A00C"));
            StartPlug = null;
            EndPlug = null;
        }

        protected override Geometry DefiningGeometry
        {
            get
            {
                // Create a StreamGeometry for describing the shape
                var path = new PathGeometry();

                // Freeze the geometry for performance benefits
                PointCollection pts = new PointCollection();
                Point s = StartPoint;
                Point e = EndPoint;


                Point p1 = new Point (s.X, s.Y);
                Point p2 = new Point( (s.X + e.X) /2, s.Y);
                Point p3 = new Point( (s.X + e.X) /2, (s.Y + e.Y) /2);
                Point p4 = new Point( (s.X + e.X) /2, e.Y);
                Point p5 = new Point (e.X, e.Y);

                pts.Add(p1);
                pts.Add(p2);
                pts.Add(p3);
                //return geometry;
                var fig = new PathFigure();
                fig.StartPoint = p1;
                fig.Segments.Add(new BezierSegment(p1, p2, p3, true));
                fig.Segments.Add(new BezierSegment(p3, p4, p5, true));
                fig.IsClosed = false;
                fig.IsFilled= false;
                path.Figures.Add(fig);
                 
                return path ;
            }
        }

        public Point StartPoint
        {
            get { return (Point)GetValue(StartPointProperty); }
            set { SetValue(StartPointProperty, value); }
        }

        // Using a DependencyProperty as the backing store for StartPoint.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty StartPointProperty =
            DependencyProperty.Register("StartPoint", typeof(Point), 
                typeof(Connection), new FrameworkPropertyMetadata(new Point(0,0), FrameworkPropertyMetadataOptions.AffectsRender));


        public Point EndPoint
        {
            get { return (Point)GetValue(EndPointProperty); }
            set { SetValue(EndPointProperty, value); }
        }

        public Plug StartPlug { get; set; }
        public Plug EndPlug { get; set; }


        // Using a DependencyProperty as the backing store for EndPoint.  This enables animation, styling, binding, etc...
        public static readonly DependencyProperty EndPointProperty =
            DependencyProperty.Register("EndPoint", typeof(Point), typeof(Connection), 
                new FrameworkPropertyMetadata(new Point(0,0), FrameworkPropertyMetadataOptions.AffectsRender));





    }
}
