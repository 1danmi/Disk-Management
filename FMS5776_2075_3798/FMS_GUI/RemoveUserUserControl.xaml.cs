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
    /// Interaction logic for RemoveUserUserControl.xaml
    /// </summary>
    public partial class RemoveUserUserControl : UserControl
    {
        Disk disk { get; set; }
        public RemoveUserUserControl()
        {
            InitializeComponent();
        }

        private void ContinueButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                MainWindow w = Window.GetWindow(this) as MainWindow;
                var x = w.MainFrame.Content as MainPage;
                disk = x.disk;
                MessageBoxResult remove = MessageBox.Show(
                   "Are you sure that you want to delete these user?\nThis action cannot be undone!",
                   "Remove " + this.UserNameTextBox.Text, MessageBoxButton.OKCancel, MessageBoxImage.Warning, MessageBoxResult.Cancel, MessageBoxOptions.None);
                switch (remove)
                {
                    case MessageBoxResult.OK:
                        disk.removeUserSigned(this.UserNameTextBox.Text, disk.getCU().SLevel);
                        MessageBox.Show("User deleted succesfully");
                        break;
                    case MessageBoxResult.Cancel:
                        break;
                    default:
                        break;
                }
               
                x.removeUserTranstion.UnloadPage(this);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow w = Window.GetWindow(this) as MainWindow;
            var x = w.MainFrame.Content as MainPage;
            x.removeUserTranstion.UnloadPage(this);
        }
    }
}
