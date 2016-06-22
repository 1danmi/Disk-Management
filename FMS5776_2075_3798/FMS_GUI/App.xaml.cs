using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Globalization;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;
using FMS_adapter;

namespace FMS_GUI
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
       
    }
    public class SLevelToStringConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            SLEVEL sl = (SLEVEL)value;
            switch(sl)
            {
                case SLEVEL.user:
                    return "User";
                case SLEVEL.Administrator:
                    return "Administrator";
                case SLEVEL.Super_User:
                    return "Super User";
                default:
                    return "Owner";
            }
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
}
