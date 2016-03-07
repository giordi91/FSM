using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using FSMWrapper;

namespace FSMEditor
{
    class ConditionTemplateSelector : DataTemplateSelector
    {
        public DataTemplate TypedConditionTemplate { get; set; }
        public DataTemplate DoubleConditionTemplate { get; set; }

        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            if (item is TypedConditionBinding)
            {
                return TypedConditionTemplate;
            }
            else if(item is DoubleConditionBinding)
            {
                return DoubleConditionTemplate;
            }
             return base.SelectTemplate(item, container);
        }
    }
}
