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
using System.Windows.Navigation;
using System.Windows.Shapes;
using FMS_adapter;

namespace FMS_GUI
{
    /// <summary>
    /// Interaction logic for CreateFileUserControl.xaml
    /// </summary>
    public partial class CreateFileUserControl : UserControl
    {
        recType recordType;
        SLEVEL slevel;
        public enum recType {Student = 1};
        public CreateFileUserControl()
        {
            
            InitializeComponent();
            RecordTypeComboBox.ItemsSource = Enum.GetValues(typeof(recType));
            SecLevelComboBox.ItemsSource = Enum.GetValues(typeof(SLEVEL));
               
        }

        private void newFileButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                MainWindow w = Window.GetWindow(this) as MainWindow;
                var x = w.MainFrame.Content as MainPage;
                x.codpContentControl.Content = null;
                x.shadowRectangle.Visibility = Visibility.Collapsed;
                string fileName = this.FileNameTextBox.Text;
                int numberOfRecords = Convert.ToInt32(this.RecordsNumberTextBox.Text);
                if (recordType == recType.Student)
                {
                    x.disk.createFile(fileName, "F", 88, (uint)Math.Ceiling(((double)numberOfRecords / (1020 / 88))) * (1020 / 88),
                        (uint)Math.Ceiling(((double)numberOfRecords / (1020 / 88))) + 1 ,"s", slevel, 0, 10, 0);
                }
                else
                {
                    throw new Exception("You didn't choose a correct record type");
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void RecordTypeComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            recordType = (recType)this.RecordTypeComboBox.SelectedItem;
        }

        private void SecLevelComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            slevel = (SLEVEL)this.SecLevelComboBox.SelectedItem;
        }
    }
}
