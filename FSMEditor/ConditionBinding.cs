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
        static public List<string> OperationNames = 
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
                string name = OperationNames[value];
                return name;                
            }
            set {
                    int v = OperationNames.IndexOf(value);
                    m_wrapCond.set_operation(v);
                    OnPropertyChanged("Operation");
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
