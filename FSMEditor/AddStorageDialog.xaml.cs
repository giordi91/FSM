using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace FSMEditor
{
    public partial class AddStorageDialog : Window
    {
        int m_data_type =2;
        ViewModel m_view;
        public AddStorageDialog( ViewModel view)
        {
            InitializeComponent();
            m_view = view;
        }
        private void RadioButton_Click(object sender, RoutedEventArgs e)
        {
            var obj = sender as RadioButton;
            Console.WriteLine(obj.Content);
            
            switch (obj.Content as string)
            {
                case "int":
                    m_data_type = 0;
                    break;
                case "float":
                    m_data_type = 1;
                    break;

                default:
                    m_data_type = 2;
                    break;
            }
        }

        private void StorageButton_Click(object sender, RoutedEventArgs e)
        {
            if (m_data_type == 1)
            {
                m_view.m_fsm.set_float_value(keyName.Text, 0.0f);
            }
            else if (m_data_type == 0)
            {
                m_view.m_fsm.set_int_value(keyName.Text, 0);
            }
            else if (m_data_type == 2)
            {
                m_view.m_fsm.set_bool_value(keyName.Text, false);
            }
            this.Close();
            //this is just to trigger the property changed, maybe there is a better way?
            //maybe .... but do i really care right now? ahahah NO
            var b =m_view.Storage;
        }

    }
}
