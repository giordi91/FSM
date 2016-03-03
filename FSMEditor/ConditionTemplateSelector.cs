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
            var cond = item as ConditionBinding;
            if ( cond.m_wrap_cond is ITypedCondition<int> ||
                cond.m_wrap_cond is ITypedCondition<bool> ||
                cond.m_wrap_cond is ITypedCondition<float> )
            {
                return TypedConditionTemplate;
            }
             return base.SelectTemplate(item, container);
        }

    }
}
