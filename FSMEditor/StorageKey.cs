using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FSMWrapper;

namespace FSMEditor
{
    public class StorageKey<T>
    {
        private FiniteStateMachineWrap m_fsm;
        private string m_name;
        private Type m_t;
        public StorageKey( FiniteStateMachineWrap fsm,
                          string name)
        {
            m_fsm = fsm;
            m_name = name;
            m_t = typeof(T);
        }


        public float Value
        {
            get
            {
                if (m_t == typeof(bool))
                {
                    Console.WriteLine("getting bool");
                    if (m_fsm.get_bool_value(m_name))
                    {
                        return 1.0f;
                    }
                    else
                    {
                        return 0.0f;
                    }
                }
                else if (m_t == typeof(float))
                {
                    Console.WriteLine("getting float");
                    return m_fsm.get_float_value(m_name);
                }
                else if(m_t == typeof(int))
                {
                    Console.WriteLine("getting int");
                    return m_fsm.get_int_value(m_name);
                }
                return 2;
            }

            set
            { } }
    }
}
