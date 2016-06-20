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
    /// Interaction logic for CreateOpenDiskPage.xaml
    /// </summary>
    public partial class CreateOpenDiskPage : UserControl
    {
        Disk disk { get; set; }
        public CreateOpenDiskPage()
        {
            InitializeComponent();
        }
        private void newDiskButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                MainWindow w = Window.GetWindow(this) as MainWindow;
                var x = w.MainFrame.Content as MainPage;
                x.codpContentControl.Content = null;
                x.shadowRectangle.Visibility = Visibility.Collapsed;
                x.DiskName = this.DiskNameTextBox.Text;
                string ownerName = this.OwnerNameTextBox.Text;
                string password = this.DiskPwdBox.Password;
                x.disk.createDisk(x.DiskName, ownerName, password);
                x.disk.mountDisk(x.DiskName + ".fms");
                x.disk.Mounted = true;
                x.MyRibbon.BackStageHeader = x.DiskName;
                x.suc = new SignUserControl(x.DiskName);
                x.transitionFrame.ShowPage(x.suc);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

    }
}
