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
        public TypedConditionFloatWrap m_wrapCond;
        public ConditionBinding( TypedConditionFloatWrap wrap_cond)
        {
            m_wrapCond = wrap_cond; 
        }

        public string Operation
        {

            get {
                int value = m_wrapCond.get_operation();
                string name = OperationNamesList[value];
                return name;                
            }
            set {
                    int v = OperationNamesList.IndexOf(value);
                    m_wrapCond.set_operation(v);
                    OnPropertyChanged("Operation");
                 }
        }
        public List<string> OperationNames { get {return OperationNamesList; } }

        public float CompareValue
        {
            get { return m_wrapCond.get_compare_value(); }
            set
            {
                m_wrapCond.set_compare_value(value);
                OnPropertyChanged("CompareValue");

            }
        }

        public string KeyName 
        {
            get { return m_wrapCond.get_key_name(); }
            set
            {
                m_wrapCond.set_key_name(value);
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
