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
using LiveCharts;
using LiveCharts.Defaults;
using LiveCharts.Wpf;

namespace FMS_GUI
{
    public class DiskInfo
    {
        string name;
        string owner;
        int capacity;
        int freeSpace;
        int usedSpace;

        public string Name
        {
            get
            {
                return name;
            }

            set
            {
                name = value;
            }
        }

        public string Owner
        {
            get
            {
                return owner;
            }

            set
            {
                owner = value;
            }
        }

        public int Capacity
        {
            get
            {
                return capacity;
            }

            set
            {
                capacity = value;
            }
        }

        public int FreeSpace
        {
            get
            {
                return freeSpace;
            }

            set
            {
                freeSpace = value;
            }
        }

        public int UsedSpace
        {
            get
            {
                return usedSpace;
            }

            set
            {
                usedSpace = value;
            }
        }

        public DiskInfo()
        {
            Name = "Disk Name";
            Owner = "Disk Owner";
            Capacity = 3200;
            FreeSpace = (1600 - 3) * 2;
            UsedSpace = Capacity - FreeSpace;
        }
    }
    /// <summary>
    /// Interaction logic for DiskInfoUserControl.xaml
    /// </summary>
    public partial class DiskInfoUserControl : UserControl
    {
        public DiskInfo diskInfo { get; set; }
        public SeriesCollection pie { get; set; }
        public SeriesCollection SeriesCollection { get; set; }
        public DiskInfoUserControl()
        {
            InitializeComponent();
            diskInfo = new DiskInfo();

            //this.ownerLabel.Content = "Disk Owner";
            this.MainGrid.DataContext = this.diskInfo;
            this.PieChart.DataContext = this;
            pie = new SeriesCollection();
            var free = new PieSeries
            {
                Title = "Free Space: " + diskInfo.FreeSpace.ToString() + " KB",
                Values = new ChartValues<double> { diskInfo.FreeSpace },
                PushOut = 0, Fill = (SolidColorBrush)(new BrushConverter().ConvertFrom("#f44336"))
        };
            var used = new PieSeries
            {
                Title = "Used Space: " + diskInfo.UsedSpace.ToString() + " KB",
                Values = new ChartValues<double> { 500 },
                PushOut = 0, Fill = Brushes.Gray
            };
            pie.Add(free);
            pie.Add(used);
            //SeriesCollection = new SeriesCollection
            //{
            //    new PieSeries
            //    {
            //        Title = "Chrome",
            //        Values = new ChartValues<double> { 8 },
            //        PushOut = 15
            //    },
            //    new PieSeries
            //    {
            //        Title = "Mozilla",
            //        Values = new ChartValues<double> { 6 }
            //    },
            //    new PieSeries
            //    {
            //        Title = "Opera",
            //        Values = new ChartValues<double> { 10 }
            //    },
            //    new PieSeries
            //    {
            //        Title = "Explorer",
            //        Values = new ChartValues<double> { 4 }
            //    }
            //};

            ////adding values or series will update and animate the chart automatically
            ////SeriesCollection.Add(new PieSeries());
            ////SeriesCollection[0].Values.Add(5);

            //DataContext = this;
        }
    }
}
