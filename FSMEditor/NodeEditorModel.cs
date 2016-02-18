using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using System.Windows.Media;
using System.ComponentModel;

namespace FSMEditor 
{
    /// <summary>
    /// A simple example of a view-model.  
    /// </summary>
    public class ViewModel : INotifyPropertyChanged
    {

        /// <summary>
        /// The list of rectangles that is displayed in the ListBox.
        /// </summary>
        ObservableCollection<CustomNode> rectangles = new ObservableCollection<CustomNode>();

        /// <summary>
        /// List of connections between rectangles.
        /// </summary>
        //private ObservableCollection<ConnectionViewModel> connections = new ObservableCollection<ConnectionViewModel>();


        public ViewModel()
        {
            //
            // Populate the view model with some example data.
            //
            var r1 = new CustomNode();
            r1.X = 200;
            r1.Y = 101;
            r1.NodeName = "PUPPA";

            var r2 = new CustomNode();
            r2.X = 40;
            r2.Y = 69;
            r2.NodeName = "CAZZO";

            rectangles.Add(r1);
            rectangles.Add(r2);
        }

        /// <summary>
        /// The list of rectangles that is displayed in the ListBox.
        /// </summary>
        public ObservableCollection<CustomNode> Rectangles
        {
            get
            {
                return rectangles;
            }
        }

        /// <summary>
        /// List of connections between rectangles.
        /// </summary>


        /// <summary>
        /// Raises the 'PropertyChanged' event when the value of a property of the view model has changed.
        /// </summary>
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
