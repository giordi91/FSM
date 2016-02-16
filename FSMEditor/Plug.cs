﻿using System;
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
        static Color BACKGROUND_COLOR = (Color)ColorConverter.ConvertFromString("Gray");


        public Plug()
        { }
        public Plug(CustomNode node)
        {
            m_node = node;
            m_radius = 0;
        }

        public void print()
        {
            Console.WriteLine("hei its mee plug");
            Console.WriteLine(this.Width);
        }

        public int get_radius()
        {
            return m_radius;
        }
        
        private CustomNode m_node;
        private int m_radius;

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

        public int X
        {
            get {
                return (int)Canvas.GetLeft(this); }
        }
        public int Y 
        {
            get {
                return (int)Canvas.GetTop(this); }
        }
        private bool m_is_selected;
        private int m_x;
    }

}
