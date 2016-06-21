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
using FMS_adapter;
using System.Runtime.CompilerServices;

namespace FMS_GUI
{
    /// <summary>
    /// Interaction logic for MainPage.xaml
    /// </summary>
    public partial class MainPage : Page
    {
        UserControl info;
        UserControl fileInfo;
        public CreateOpenDiskPage codp { get; set; }
        public CreateFileUserControl cfuc { get; set; }

        public NewUserUserControl nuuc { get; set; }
        public SignUserControl suc { get; set; }
        public UserControl Info {
            get { return info; }
            set
            {
                info = value;
                if (info is DiskInfoUserControl)
                    this.InfoContentControl.Content = info;
                else if(info is FileInfoUserControl)
                    this.InfoContentControl.Content = info;
            }
        }
        //public UserControl FileInfo
        //{
        //    get { return fileInfo; }
        //    set
        //    {
        //        fileInfo = value;
        //        if (fileInfo is new)
        //        {
        //            this.InfoContentControl.Content = info;
        //        }
        //    }
        //}

        public Disk disk { get; set; }
        public FCB fcb { get; set; }
        public string DiskName { get; set; }
        public MainPage()
        {
            InitializeComponent();
            disk = new Disk();
            //Info = new DiskInfoUserControl(disk);

            this.InfoContentControl.DataContext = this;
            
        }

        #region Disk

        private void CreateDiskButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (disk.Mounted)
                    throw new Exception("You must unmount the current disk first!");
                this.shadowRectangle.Visibility = Visibility.Visible;
                codp = new CreateOpenDiskPage();
                codpContentControl.Content = codp;
                this.codpContentControl.DataContext = this;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private void MountDiskButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                OpenFileDialog f = new OpenFileDialog();
                f.Filter = "All Files (*)|*|DISK Files (*.fms)|*.fms";
                if (f.ShowDialog() == true)
                {
                    //var a = new Uri(f.FileName);
                    disk.mountDisk(f.FileName);
                    disk.Mounted = true;
                    DiskName = disk.getVHD().DiskName;
                    this.dataGrid.ItemsSource = disk.getDirEntryInRootDir();
                    this.MyRibbon.BackStageHeader = DiskName;
                    suc = new SignUserControl(DiskName);
                    transitionFrame.ShowPage(suc);
                }
                
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }

        private void FormatButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                string diskName = "Disk Name";
                MessageBoxResult format = MessageBox.Show(
                    "WARNING: Formatting will erase ALL data on this disk.\nTo format the disk, click OK. To quit, click CANCEL.",
                    "Format " + diskName, MessageBoxButton.OKCancel, MessageBoxImage.Warning, MessageBoxResult.Cancel, MessageBoxOptions.None);

                switch (format)
                {
                    case MessageBoxResult.OK:
                        disk.format();
                        Info = new DiskInfoUserControl(disk);
                        
                        this.dataGrid.ItemsSource = disk.getDirEntryInRootDir();
                        break;
                    case MessageBoxResult.Cancel:
                        break;
                    default:
                        break;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void SignOutButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                disk.signOut();
                suc = new SignUserControl(DiskName);
                transitionFrame.ShowPage(suc);
                if (fcb != null && fcb.Loaded)
                    CloseFileButton_Click(new object(), new RoutedEventArgs());
                
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void UnmountDiskButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                disk.signOut();
                disk.unmountDisk();
                disk.Mounted = false;
                this.dataGrid.ItemsSource = null;
                var inf = new DiskInfoUserControl(disk);
                Info = inf;

                //MessageBox.Show("Disk unmounted.", "Unmount Disk", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        #endregion

        #region File

        private void CreateFileButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                if (fcb != null && fcb.Loaded)
                    throw new Exception("File already open!");

                this.shadowRectangle.Visibility = Visibility.Visible;
                cfuc = new CreateFileUserControl();
                codpContentControl.Content = cfuc;
                this.codpContentControl.DataContext = this;
                
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void OpenFileButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                if (fcb != null && fcb.Loaded)
                    throw new Exception("File already open!");
                DirEntry r = (DirEntry)this.dataGrid.SelectedItem;
                if (r == null)
                    throw new Exception("You must select a file!");
                fcb = disk.openFile(r.FileName , MODE.WR);
                fcb.Loaded = true;
                this.dataGrid.Visibility = Visibility.Hidden;
                this.recordsDataGrid.Visibility = Visibility.Visible;
                this.recordsDataGrid.ItemsSource = fcb.getRecEntryList();
                Info = new FileInfoUserControl(fcb);
                //this.InfoContentControl = Info;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void DeleteFileButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                if (fcb != null && fcb.Loaded)
                    throw new Exception("You must close the file first!");
                DirEntry r = (DirEntry)this.dataGrid.SelectedItem;
                MessageBoxResult delete = MessageBox.Show(
                    "Are you sure that you want to delete " + r.FileName + "?\nThis action cannot be undone!",
                    "Delete " + r.FileName, MessageBoxButton.OKCancel, MessageBoxImage.Warning, MessageBoxResult.Cancel, MessageBoxOptions.None);

                switch (delete)
                {
                    case MessageBoxResult.OK:
                        this.disk.delFile(r.FileName);
                        this.dataGrid.ItemsSource = disk.getDirEntryInRootDir();
                        Info = new DiskInfoUserControl(disk);
                        break;
                    case MessageBoxResult.Cancel:
                        break;
                    default:
                        break;
                }

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void CloseFileButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                if (fcb == null || !fcb.Loaded)
                    throw new Exception("No file is open!");
                fcb.closeFile();
                fcb.Loaded = false;
                if (recordsDataGrid.Visibility == Visibility.Visible)
                {
                    recordsDataGrid.Visibility = Visibility.Hidden;
                    dataGrid.Visibility = Visibility.Visible;
                }
                this.Info = new DiskInfoUserControl(disk);
                
                //MessageBox.Show("File closed.", "Closing file", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        #endregion

        #region Record

        private void AddRecordButoon_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                if (fcb == null || !fcb.Loaded)
                    throw new Exception("No file is open!");

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void DeleteRecordButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                if (fcb == null || !fcb.Loaded)
                    throw new Exception("No file is open!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void UpdateRecordButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                if (fcb == null || !fcb.Loaded)
                    throw new Exception("No file is open!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        #endregion

        #region User

        private void AddUserButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                this.shadowRectangle.Visibility = Visibility.Visible;
                nuuc = new NewUserUserControl();
                codpContentControl.Content = nuuc;
                this.codpContentControl.DataContext = this;

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void RemoveUserButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                
                this.removeUserTranstion.ShowPage(new RemoveUserUserControl());
                
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void UserInfoButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void ChangePasswordButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void SignOutButton2_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                if (!disk.Mounted)
                    throw new Exception("No disk is mounted!");
                disk.signOut();
                suc = new SignUserControl(DiskName);
                transitionFrame.ShowPage(suc);
                if (fcb != null && fcb.Loaded)
                    CloseFileButton_Click(new object(), new RoutedEventArgs());
               
                //MessageBox.Show("Disk unmounted.", "Unmount Disk", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        #endregion

        private void shadowRectangle_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if(this.shadowRectangle.Visibility==Visibility.Visible)
            {
                this.shadowRectangle.Visibility = Visibility.Collapsed;
                this.codpContentControl.Content = null;
            }
        }

        
    }
}
