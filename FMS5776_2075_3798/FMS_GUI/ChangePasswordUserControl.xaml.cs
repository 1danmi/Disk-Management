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
    /// Interaction logic for ChangePasswordUserControl.xaml
    /// </summary>
    public partial class ChangePasswordUserControl : UserControl
    {
        public Disk disk { get; set; }
        public ChangePasswordUserControl(Disk d)
        {
            InitializeComponent();
            disk = d;
        }

        private void changePwdButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                MainWindow w = Window.GetWindow(this) as MainWindow;
                var x = w.MainFrame.Content as MainPage;

                string oldPwd = this.oldPasswordTextBox.Password;
                string newPwd = this.newPasswordTextBox.Password;
                string newConfPwd = this.confirmPwdTextBox.Password;
                if (newPwd != newConfPwd)
                    throw new Exception("Password doesn't match!");
                x.disk.changePassword(x.disk.getCU().Name, oldPwd, newPwd);
                x.shadowRectangle.Visibility = Visibility.Hidden;
                x.codpContentControl.Content = null;
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
