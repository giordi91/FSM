using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FSMWrapper;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows;
using System.Collections.ObjectModel;
using System.ComponentModel;

namespace FSMEditor
{
    public class TypedConditionBinding: INotifyPropertyChanged
    {
        public enum OperationEnum { EQUAL, GREATHER, LESS,GREATHEREQUAL,LESSEQUAL};
        static public List<string> OperationNamesList = 
        new List<string>(){ "EQUAL", "GREATHER", "LESS","GREATHEREQUAL","LESSEQUAL"};
        public dynamic m_wrap_cond;

        public TypedConditionBinding( object wrap_cond)
        {
            m_wrap_cond= wrap_cond;

        }

        public string Operation
        {

            get {
                int value = 0;
                value = m_wrap_cond.get_operation();
                string name = OperationNamesList[value];
                return name;
            }
            set {
                    int v = OperationNamesList.IndexOf(value);
                    m_wrap_cond.set_operation(v);
                    OnPropertyChanged("Operation");
                 }
        }
        public List<string> OperationNames { get {return OperationNamesList; } }

        public float CompareValue
        {
            get
            {

                var obj = m_wrap_cond as object;
                if (obj is ITypedCondition<bool>)
                {
                    bool value = m_wrap_cond.get_compare_value();
                    if (value)
                    {
                        return 1;
                    }
                    else { return 0; }

                }
                else
                {
                    return m_wrap_cond.get_compare_value();
                }
            }
            set
            {
                Console.WriteLine("in setter");
                var obj = m_wrap_cond as object;
                if (obj is ITypedCondition<float>)
                {
                    m_wrap_cond.set_compare_value(value);
                    return;
                }
                else if (obj is ITypedCondition<int>)
                {
                    m_wrap_cond.set_compare_value((int)value);
                    return;
                }

                else if (obj is ITypedCondition<bool>)
                {
                    m_wrap_cond.set_compare_value(value != 0);
                    return;
                }
                m_wrap_cond.set_compare_value(value);
                OnPropertyChanged("CompareValue");

            }
        }

        public string KeyName 
        {
            get { return m_wrap_cond.get_key_name(); }
            set
            {
                m_wrap_cond.set_key_name(value);
                OnPropertyChanged("KeyName");

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
    }

    public class DoubleConditionBinding: INotifyPropertyChanged
    {
        public enum OperationEnum { EQUAL, GREATHER, LESS,GREATHEREQUAL,LESSEQUAL};
        static public List<string> OperationNamesList = 
        //duplicated need to move it?
        new List<string>(){ "EQUAL", "GREATHER", "LESS","GREATHEREQUAL","LESSEQUAL"};
        public dynamic m_wrap_cond;

        public DoubleConditionBinding( object wrap_cond)
        {
            m_wrap_cond= wrap_cond;

        }

        public string Operation
        {

            get {
                int value = 0;
                value = m_wrap_cond.get_operation();
                string name = OperationNamesList[value];
                return name;
            }
            set {
                    int v = OperationNamesList.IndexOf(value);
                    m_wrap_cond.set_operation(v);
                    OnPropertyChanged("Operation");
                 }
        }

        public List<string> OperationNames { get {return OperationNamesList; } }

        public string KeyName1 
        {
            get { return m_wrap_cond.get_key_name_1(); }
            set
            {
                m_wrap_cond.set_key_name_1(value);
                OnPropertyChanged("KeyName1");

            }
        }
        public string KeyName2 
        {
            get { return m_wrap_cond.get_key_name_2(); }
            set
            {
                m_wrap_cond.set_key_name_2(value);
                OnPropertyChanged("KeyName2");

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

    }
}
