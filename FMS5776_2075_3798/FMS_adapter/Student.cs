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
        public string ID { get { return id; } set { id = value; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        string firstName;
        public string FirstName { get { return firstName; } set { firstName = value; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string lastName;
        public string LastName { get { return lastName; } set { lastName = value; } }

        int grade;
        public int Grade { get { return grade; } set { grade = value; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string street;
        public string Street { get { return street; } set { street = value; } }

        int houseNo;
        public int HouseNo { get { return houseNo; } set { houseNo = value; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string city;
        public string City { get { return city; } set { city = value; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        string zipCode;
        public string ZipCode { get { return zipCode; } set { zipCode = value; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        string phoneNo;
        public string PhoneNo { get { return phoneNo; } set { phoneNo = value; } }

        IntPtr myStudentPtr;
        public Student()
        {
            myStudentPtr = cppToCsharpAdapter.makeStudentObject();
        }
        ~Student()
        {
            //if (myStudentPtr != null)
            //    cppToCsharpAdapter.deleteStudentObject(ref myStudentPtr);
        }
    }
}
