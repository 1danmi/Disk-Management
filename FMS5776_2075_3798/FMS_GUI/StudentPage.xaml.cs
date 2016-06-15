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
    /// Interaction logic for StudentPage.xaml
    /// </summary>
    public partial class StudentPage : Page
    {
        public StudentPage(bool update)
        {
            InitializeComponent();
            if (update == false)
                this.UpdateButton.Visibility = Visibility.Hidden;
            Random R = new Random();
            int a = R.Next(0, 14);
            switch (a)
            {
                case 0:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#f44336"));
                    break;
                case 1:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#E91E63"));
                    break;
                case 2:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#9C27B0"));
                    break;
                case 3:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#673AB7"));
                    break;
                case 4:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#3F51B5"));
                    break;
                case 5:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#2196F3"));
                    break;
                case 6:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#03A9F4"));
                    break;
                case 7:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#FF5722"));
                    break;
                case 8:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#FF9800"));
                    break;
                case 9:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#4CAF50"));
                    break;
                case 10:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#8BC34A"));
                    break;
                case 11:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#CDDC39"));
                    break;
                case 12:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#FFC107"));
                    break;
                default:
                    this.TitleBorder.Background = (SolidColorBrush)(new BrushConverter().ConvertFrom("#9E9E9E"));
                    break;
            }
        }
    }
}
