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
            /*
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
            */

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

        public event PropertyChangedEventHandler PropertyChanged;

        public void read_from_file(string path)
        {
            m_rectangles.Clear();
            m_connections.Clear();
            m_fsm.from_file(path);
            var count = m_fsm.get_state_count();


            var state_map = new Dictionary<string, CustomNode>();
            for (int i = 0; i < count; i++)
            {
                StateWrapper w = m_fsm.get_state_at_index(i);
                var n = new CustomNode(w);
                n.NodeName = w.get_name();
                m_rectangles.Add(n);
                state_map[n.NodeName] = n;
            }

            for (int i = 0; i < count; i++)
            {
                var node = Rectangles[i];
                var state = node.m_state;
                var conn_count = state.get_connection_count();
                Console.WriteLine(conn_count);
                for (int c = 0; c < conn_count; ++c)
                {

                    var conn = state.get_connection_at_index(c);
                    string endName = conn.get_destination_name();
                    CustomNode endNode = state_map[endName];
                    StateWrapper endState = endNode.m_state;
                    var connShape = new Connection();
                    connShape.conn = conn;
                    var outp = node.OutPlug;
                    var inp = endNode.InPlug;
                    outp.IsSelected = true;
                    inp.IsSelected = true;
                    //TODO FIX RADIUSSS
                    outp.AddConnection(connShape);
                    inp.AddConnection(connShape);
                    connShape.StartPlug = inp;
                    connShape.EndPlug = outp;
                    var r = 10;
                    connShape.EndPoint= new Point(outp.X+r, outp.Y+r);
                    connShape.StartPoint= new Point(inp.X+r, inp.Y+r);
                    Connections.Add(connShape);

                
                }

            }
            //lets loop again and build the connections
            Console.WriteLine("reading from file");
        }
    }
}
