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
    /// Interaction logic for UserInfoUserControl.xaml
    /// </summary>
    public partial class UserInfoUserControl : UserControl
    {
        public User user { get; set; }
        public UserInfoUserControl(User u)
        {
            InitializeComponent();
            user = u;
            this.MainGrid.DataContext = user;
        }

        private void CloseButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow w = Window.GetWindow(this) as MainWindow;
            var x = w.MainFrame.Content as MainPage;
            x.userInfoTranstion.UnloadPage(this);
        }
    }
}
