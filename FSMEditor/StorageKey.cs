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

        public string Name { get { return m_name; } set { m_name = value; } }

        public float Value
        {
            get
            {
                if (m_t == typeof(bool))
                {
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
                    return m_fsm.get_float_value(m_name);
                }
                else if (m_t == typeof(int))
                {
                    return m_fsm.get_int_value(m_name);
                }
                return 1.0f;
            }

            set
            {

                if (m_t == typeof(bool))
                {
                    if (Math.Abs(value) < 0.0001)
                    {
                        m_fsm.set_bool_value(m_name, false);
                    }
                    else
                    {
                        m_fsm.set_bool_value(m_name, true);
                    }
                }
                else if (m_t == typeof(float))
                {
                    m_fsm.set_float_value(m_name, value);
                }
                else if (m_t == typeof(int))
                {
                    m_fsm.set_int_value(m_name, (int)value);
                }
            }
        }

    }
}
