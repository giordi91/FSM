using System;
using System.Windows;
using System.Windows.Controls;

namespace WPFCustomControls
{

    public class MyCustomControl : Button
    {

        static MyCustomControl()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(MyCustomControl), new
               FrameworkPropertyMetadata(typeof(MyCustomControl)));
        }

    }
}