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
    class StorageTemplateSelector : DataTemplateSelector
    {
        public DataTemplate FloatStorageTemplate{ get; set; }
        public DataTemplate IntStorageTemplate{ get; set; }
        public DataTemplate BoolStorageTemplate{ get; set; }
        //public DataTemplate DoubleConditionTemplate { get; set; }

        public override DataTemplate SelectTemplate(object item, DependencyObject container)
        {
            Console.WriteLine(item.GetType());
            if (item is StorageKey<float>)
            {
                return FloatStorageTemplate;
            }
            else if (item is StorageKey<int>)
            {
                return IntStorageTemplate;
            }
            else if (item is StorageKey<bool>)
            {
                return BoolStorageTemplate;
            }
            return base.SelectTemplate(item, container);
        }
    }
}
