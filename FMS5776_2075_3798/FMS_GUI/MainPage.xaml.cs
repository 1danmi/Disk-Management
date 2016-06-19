using System;
using System.IO;
using Microsoft.Win32;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Markup;
using Syncfusion.Windows.Tools.Controls;
using Syncfusion.Windows.Tools;
using System.Threading;
using System.Collections;
using System.Diagnostics;
using System.ComponentModel;
using Syncfusion.Windows.Shared;
using System.Globalization;
using System.Windows.Threading;
using System.Windows.Interop;

namespace FMS_GUI
{
    /// <summary>
    /// Interaction logic for MainPage.xaml
    /// </summary>
    public partial class MainPage : Page
    {
        public CreateOpenDiskPage codp { get; set; }
        public SignUserControl suc { get; set; }
        public UserControl info { get; set; }

        public MainPage()
        {
            InitializeComponent();
            //codp = new CreateOpenDiskPage();
            //this.codpContentControl.DataContext = this;
            info = new DiskInfoUserControl();
            this.InfoContentControl.DataContext = this;

        }

        private void CreateDiskButton_Click(object sender, RoutedEventArgs e)
        {
            this.shadowRectangle.Visibility = Visibility.Visible;
            codp = new CreateOpenDiskPage();
            this.codpContentControl.DataContext = this;
        }

        private void MountDiskButton_Click(object sender, RoutedEventArgs e)
        {
            
            Microsoft.Win32.OpenFileDialog f = new Microsoft.Win32.OpenFileDialog();
            f.Filter = "All Files (*)|*|DISK Files (*.fms)|*.fms";
            if (f.ShowDialog() == true)
            {
                var a = new Uri(f.FileName);

            }
            suc = new SignUserControl();
            transitionFrame.ShowPage(suc);

        }

        private void FormatButton_Click(object sender, RoutedEventArgs e)
        {
            string diskName = "Disk Name";
            MessageBoxResult format =  MessageBox.Show(
                "WARNING: Formatting will erase ALL data on this disk.\nTo format the disk, click OK. To quit, click CANCEL.",
                "Format " + diskName, MessageBoxButton.OKCancel, MessageBoxImage.Warning, MessageBoxResult.Cancel,MessageBoxOptions.None);

            switch(format)
            {
                case MessageBoxResult.OK:
                    break;
                case MessageBoxResult.Cancel:
                    break;
                default:
                    break;
            }
        }

        private void SignOutButton_Click(object sender, RoutedEventArgs e)
        {
            suc = new SignUserControl();
            transitionFrame.ShowPage(suc);
        }

        private void UnmountDiskButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void CreateFileButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void OpenFileButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void CloseFileButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void AddRecordButoon_Click(object sender, RoutedEventArgs e)
        {

        }

        private void DeleteRecordButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void UpdateRecordButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void AddUserButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void RemoveUserButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void UserInfoButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void ChangePasswordButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void SignOutButton2_Click(object sender, RoutedEventArgs e)
        {

        }

       
    }
}
