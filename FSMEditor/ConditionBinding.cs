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
    public class ConditionBinding: INotifyPropertyChanged
    {
        public enum OperationEnum { EQUAL, GREATHER, LESS,GREATHEREQUAL,LESSEQUAL};
        static public List<string> OperationNamesList = 
        new List<string>(){ "EQUAL", "GREATHER", "LESS","GREATHEREQUAL","LESSEQUAL"};
        public dynamic m_wrap_cond;

        public ConditionBinding( object wrap_cond)
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
            get { return m_wrap_cond.get_compare_value(); }
            set
            {
                Console.WriteLine("in setter");
                var obj = m_wrap_cond as object;
                if (obj is ITypedCondition<float>)
                {
                    m_wrap_cond.set_compare_value(value);
                }
                else if (obj is ITypedCondition<int>)
                {
                    m_wrap_cond.set_compare_value((int)value);
                }

                else if (obj is ITypedCondition<bool>)
                {
                    m_wrap_cond.set_compare_value(value != 0);
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


        /// <summary>
        /// 'PropertyChanged' event that is raised when the value of a property of the view model has changed.
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;


    }
}
