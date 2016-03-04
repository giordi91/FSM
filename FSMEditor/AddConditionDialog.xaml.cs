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
    /// <summary>
    /// Interaction logic for AddConditionDialog.xaml
    /// </summary>
   
    public partial class AddConditionDialog : Window
    {
        private Connection m_conn;
        private ViewModel m_model;
        private int m_cond_type;
        private int m_data_type;
        public AddConditionDialog( Connection conn, ViewModel model)
        {
            InitializeComponent();
            m_conn = conn;
            m_model = model;
            m_cond_type = 1;
            m_data_type = 2;
        }

        private void add_connection_create_click(object sender, RoutedEventArgs e)
        {
            Console.WriteLine("creating");
            if (m_cond_type == 1)
            {
                Console.WriteLine(m_data_type);
                if (m_data_type == 1)
                {
                    var cond =  FSMWrapper.ConditionFactory<float>.Create<float>(m_model.m_fsm, "foo", 12.2f, 0);

                    var bind = new ConditionBinding(cond);
                    m_conn.Conditions.Add(bind);

                    m_conn.conn.add_conditions(cond);
                    Console.WriteLine("creating typed float");
                }
                else if (m_data_type == 0)
                {
                    var cond =  FSMWrapper.ConditionFactory<int>.Create<int>(m_model.m_fsm, "foo", 2, 0);

                    var bind = new ConditionBinding(cond);
                    m_conn.Conditions.Add(bind);

                    m_conn.conn.add_conditions(cond);
                    Console.WriteLine("creating typed int");
                }
                else if (m_data_type == 2)
                {
                    var cond =  FSMWrapper.ConditionFactory<bool>.Create<bool>(m_model.m_fsm, "foo", 0, 0);

                    var bind = new ConditionBinding(cond);
                    m_conn.Conditions.Add(bind);
                    m_conn.conn.add_conditions(cond);
                    Console.WriteLine("creating typed bool");
                }

            }
            this.Close();
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
                    Console.WriteLine("setting float");
                    m_data_type = 1;
                    break;
                default:
                    Console.WriteLine("setting default");
                    m_data_type = 2;
                    break;
            }
        }

        private void RadioButton_Click_1(object sender, RoutedEventArgs e)
        {
            var obj = sender as RadioButton;
            Console.WriteLine(obj.Content);

            switch (obj.Content as string)
            {
                case "DoubleVar":
                    m_cond_type = 0;
                    break;
                case "Typed":
                    m_cond_type = 1;
                    break;
                default:
                    m_cond_type = 1;
                    break;
            }
        }
    }
}
