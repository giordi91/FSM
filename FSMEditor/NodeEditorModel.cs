using System;
using System.Windows;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using System.Windows.Media;
using System.ComponentModel;
using System.Drawing;
using FSMWrapper;

namespace FSMEditor 
{
    /// <summary>
    /// A simple example of a view-model.  
    /// </summary>
    public class ViewModel : INotifyPropertyChanged
    {

        ObservableCollection<CustomNode> m_rectangles = new ObservableCollection<CustomNode>();
        ObservableCollection<Connection> m_connections= new ObservableCollection<Connection>();
        public ObservableCollection<ConditionBinding> m_conditions = new ObservableCollection<ConditionBinding>(); 

        public FiniteStateMachineWrap m_fsm; 

        public ViewModel()
        {
            //m_conditions.Add("puppaa");
            //m_conditions.Add("daje");
            //m_conditions.Add("cazzo");
            m_fsm = new FiniteStateMachineWrap();
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

            m_fsm.add_state(r1.m_state);
            m_fsm.add_state(r2.m_state);

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

        public ObservableCollection<ConditionBinding> Conditions 
        {
            get
            {
                Console.WriteLine("getting condiitions");
                return m_conditions;
            }
            set
            {
                m_conditions = value;
                OnPropertyChanged("Conditions");
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
