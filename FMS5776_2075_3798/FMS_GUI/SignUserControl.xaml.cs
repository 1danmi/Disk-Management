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
    /// Interaction logic for SignUserControl.xaml
    /// </summary>
    public partial class SignUserControl : UserControl
    {
        Disk disk { get; set; }
        public SignUserControl(Disk d)
        {
            InitializeComponent();
            disk = d;
        }

        private void SignInButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                disk.signIn(this.UserNameTextBox.Text, this.passwordBox.Password);
                MainWindow w = Window.GetWindow(this) as MainWindow;
                var x = w.MainFrame.Content as MainPage;
                x.transitionFrame.UnloadPage(this);
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void SignInButton_Click(object sender, MouseButtonEventArgs e)
        {
            try
            {
                disk.signIn(this.UserNameTextBox.Text, this.passwordBox.Password);
                MainWindow w = Window.GetWindow(this) as MainWindow;
                var x = w.MainFrame.Content as MainPage;
                x.transitionFrame.UnloadPage(this);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
