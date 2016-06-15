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

namespace FMS_GUI
{
    /// <summary>
    /// Interaction logic for CreateOpenDiskPage.xaml
    /// </summary>
    public partial class CreateOpenDiskPage : UserControl
    {
        public CreateOpenDiskPage()
        {
            InitializeComponent();
        }
        private void newDiskButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow w = Window.GetWindow(this) as MainWindow;
            var x = w.MainFrame.Content as MainPage;
            x.codpContentControl.Content = null;
            x.shadowRectangle.Visibility =Visibility.Collapsed;
            x.suc = new SignUserControl();
            x.transitionFrame.ShowPage(x.suc);
        }

        private void openDiskButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow w = Window.GetWindow(this) as MainWindow;
            var x = w.MainFrame.Content as MainPage;
            x.codpContentControl.Content = null;
            x.shadowRectangle.Visibility = Visibility.Collapsed;
            x.suc = new SignUserControl();
            x.transitionFrame.ShowPage(x.suc);
        }
    }
}
