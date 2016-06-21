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
    /// Interaction logic for FileInfoUserControl.xaml
    /// </summary>
    public partial class FileInfoUserControl : UserControl
    {
        public DirEntry fileDesc { get; set; }
        public FileInfoUserControl(FCB fcb)
        {
            InitializeComponent();
            if (!fcb.Loaded)
                this.MainGrid.Visibility = Visibility.Hidden;
            else
            {
                fileDesc = fcb.getfileDesc();
                this.MainGrid.DataContext = this.fileDesc;
                NumOfRecordsLabel.Content = "   Number Of Record: "+ fcb.getNumOfRecords().ToString();
                switch (fileDesc.SLEVEL)
                {
                    case 1:
                        this.SLevelSpaceLabel.Content = "   Security Level: User";
                        break;
                    case 2:
                        this.SLevelSpaceLabel.Content = "   Security Level: Administrator";
                        break;
                    case 3:
                        this.SLevelSpaceLabel.Content = "   Security Level: Super User";
                        break;
                    case 4:
                        this.SLevelSpaceLabel.Content = "   Security Level: Owner";
                        break;
                }
                //diskInfo = new DiskInfo(d.getVHD().DiskName, d.getVHD().DiskOwner, d.howMuchEmpty(new IntPtr()));
                //this.ownerLabel.Content = "Disk Owner";
            }
        }
    }
}
