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
        public ObservableCollection<object> m_storage= new ObservableCollection<object>(); 

        public FiniteStateMachineWrap m_fsm; 

        public ViewModel()
        {
            m_fsm = new FiniteStateMachineWrap();

            // Populate the view model with some example data.
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

            Console.WriteLine(m_fsm.get_int_dict());
            foreach(var p in m_fsm.get_int_dict())
            {
                Console.WriteLine(p.Value); 
            }

        }

        public ObservableCollection<CustomNode> Rectangles
        {
            get
            {
                return m_rectangles;
            }
        }
        public ObservableCollection<object> Storage 
        {
            get
            {
                m_storage.Clear();
                var bool_map = m_fsm.get_bool_dict();
                foreach (var p in bool_map)
                {
                    var s_k = new StorageKey<bool>(m_fsm,p.Key);
                    m_storage.Add(s_k);
                }

                var float_map = m_fsm.get_float_dict();
                foreach (var p in float_map)
                {
                    var s_k = new StorageKey<float>(m_fsm,p.Key);
                    m_storage.Add(s_k);
                }
                var int_map = m_fsm.get_int_dict();
                foreach (var p in int_map)
                {

                    Console.WriteLine(p.Value);
                    var s_k = new StorageKey<int>(m_fsm,p.Key);
                    m_storage.Add(s_k);
                }
                return m_storage;
            }
            set
            {
                m_storage= value;
                OnPropertyChanged("Storage");
            }
        }
        public ObservableCollection<Connection> Connections 
        {
            get
            {
                return m_connections;
            }

        }
        
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
