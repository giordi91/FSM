using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Shapes;
using System.Windows.Media;

namespace FSMEditor
{
    public class Node
    {
        static Color BACKGROUND_COLOR =(Color) ColorConverter.ConvertFromString( "#FF1C1C25") ;
        static Color BORDER_COLOR =(Color) ColorConverter.ConvertFromString( "#FF2EE411") ;
        static int BORDER_THICKNESS = 5;
        static int SMOOTH_CORNER = 10;
        static int WIDTH = 140;
        static int HEIGHT= 100;

        //       <Rectangle Fill="#FF1C1C25" Height="100" Stroke="#FF2EE411" Width="135" Canvas.Left="149" Canvas.Top="95" RadiusX="10" RadiusY="10" StrokeThickness="5"/>
        public Node()
        {
            System.Console.WriteLine("Constructor called");
            m_body = new Rectangle();
            m_body.Fill = new SolidColorBrush(BACKGROUND_COLOR); 
            m_body.Stroke= new SolidColorBrush(BORDER_COLOR);
            m_body.RadiusX = SMOOTH_CORNER;
            m_body.RadiusY = SMOOTH_CORNER;
            m_body.Width = WIDTH;
            m_body.Height= HEIGHT;
            m_body.StrokeThickness = BORDER_THICKNESS;
        }

        public Rectangle m_body;

    }
}
