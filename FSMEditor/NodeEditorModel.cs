﻿using System;
using System.Windows;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using System.Windows.Media;
using System.ComponentModel;
using System.Drawing;

namespace FSMEditor 
{
    /// <summary>
    /// A simple example of a view-model.  
    /// </summary>
    public class ViewModel : INotifyPropertyChanged
    {

        /// <summary>
        /// The list of rectangles that is displayed in the ListBox.
        /// </summary>
        ObservableCollection<CustomNode> m_rectangles = new ObservableCollection<CustomNode>();
        ObservableCollection<Connection> m_connections= new ObservableCollection<Connection>();

        /// <summary>
        /// List of connections between rectangles.
        /// </summary>
        //private ObservableCollection<ConnectionViewModel> connections = new ObservableCollection<ConnectionViewModel>();


        public ViewModel()
        {
            //
            // Populate the view model with some example data.
            //
            var r1 = new CustomNode();
            r1.X = 200;
            r1.Y = 101;
            r1.NodeName = "PUPPA";

            var r2 = new CustomNode();
            r2.X = 40;
            r2.Y = 69;
            r2.NodeName = "CAZZO";

            m_rectangles.Add(r1);
            m_rectangles.Add(r2);


            Connection con = new Connection();
            con.StartPoint = new Point(100, 200);
            con.EndPoint= new Point(200, 100);

            m_connections.Add(con);

            }

        /// <summary>
        /// The list of rectangles that is displayed in the ListBox.
        /// </summary>
        public ObservableCollection<CustomNode> Rectangles
        {
            get
            {
                return m_rectangles;
            }
        }

        public ObservableCollection<Connection> Connections 
        {
            get
            {
                return m_connections;
            }
        }
        
        /// <summary>
        /// List of connections between rectangles.
        /// </summary>


        /// <summary>
        /// Raises the 'PropertyChanged' event when the value of a property of the view model has changed.
        /// </summary>
        private void OnPropertyChanged(string name)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(name));
            }
        }

        /// <summary>
        /// 'PropertyChanged' event that is raised when the value of a property of the view model has changed.
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

    }
}