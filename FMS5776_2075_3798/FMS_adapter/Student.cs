using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS_adapter
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class Student
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 10)]
        string id;
        public string ID { get { return id; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        string firstName;
        public string FirstName { get { return firstName; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string lastName;
        public string LastName { get { return lastName; } }

        int grade;
        public int Grade { get { return grade; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string street;
        public string Street { get { return street; } }

        int houseNo;
        public int HouseNo { get { return houseNo; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string city;
        public string City { get { return city; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        string zipCode;
        public string ZipCode { get { return zipCode; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        string phoneNo;
        public string PhoneNo { get { return phoneNo; } }

        IntPtr myStudentPtr;
        Student()
        {
            myStudentPtr = cppToCsharpAdapter.makeStudentObject();
        }
        ~Student()
        {
            if (myStudentPtr != null)
                cppToCsharpAdapter.deleteStudentObject(ref myStudentPtr);
        }
    }
}
