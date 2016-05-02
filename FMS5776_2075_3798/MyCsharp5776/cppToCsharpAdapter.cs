using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;



namespace MyCsharp5776
{

    struct Student
    {
        private int id;
        public int Id
        {
            get { return id; }
            set { id = value; }
        }

        private IntPtr pName;
        public string Name
        {
            get { return Marshal.PtrToStringAnsi(pName); }
            set { pName = Marshal.StringToHGlobalAnsi(value); }
        }
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    class Data
    {

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 8)]
        string start;

        int id;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 84)]
        string data;

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 4)]
        string end;

        public Data(int id)
        {
            this.id = id;
            start = "start";
            end = "end";
            data = "code id: " + id;
        }
    }


    class cppToCsharpAdapter
    {
        const string dllPath = "MyCpp5773.dll";

        [DllImport(dllPath)]
        public static extern int sum(int a, int b);

        [DllImport(dllPath)]
        public static extern void swap(out int x, ref int y);

        [DllImport(dllPath)]
        public static extern void swap2(ref int x, ref int y);

        [DllImport(dllPath)]
        public static extern int strLength(string str);

        [DllImport(dllPath)]
        public static extern void changeString(ref string str);

        [DllImport(dllPath, CharSet = CharSet.Unicode)]
        public static extern int changeString(ref IntPtr str);

        [DllImport(dllPath)]
        [return: MarshalAs(UnmanagedType.AnsiBStr)]
        public static extern string getChangeString(ref IntPtr str);

        [DllImport(dllPath)]
        [return: MarshalAs(UnmanagedType.AnsiBStr)]
        public static extern string getString();

        [DllImport(dllPath)]
        [return: MarshalAs(UnmanagedType.AnsiBStr)]
        public static extern string getDynamicArray(int x);

        [DllImport(dllPath)]
        public static extern void deleteDynamicArray();

        [DllImport(dllPath)]
        [return: MarshalAs(UnmanagedType.AnsiBStr)]
        public static extern string getDynamicArray_v2(out IntPtr arr, int x);

        [DllImport(dllPath)]
        public static extern void deleteDynamicArray_v2(out IntPtr arr);

        [DllImport(dllPath)]
        public static extern void getException();

        [DllImport(dllPath)]
        [return: MarshalAs(UnmanagedType.AnsiBStr)]
        public static extern string getExceptionInfo();

        [DllImport(dllPath)]
        public static extern ComplexNumber sumComplex(ComplexNumber a, ComplexNumber b);

        [DllImport(dllPath)]
        public static extern int getBigNumber(int[] arr, int size);
            
        [DllImport(dllPath)]
        [return: MarshalAs(UnmanagedType.AnsiBStr)]
        public static extern string getBigWordLength(string[] arr, int size);

        //[DllImport(dllPath)]
        //[return: MarshalAs(UnmanagedType.SafeArray, SafeArraySubType=VarEnum.VT_UI1)]
        //public static extern string[] getStringArray();


        [DllImport(dllPath)]
        public static extern StringCppArray getStringArray_v2();

        [DllImport(dllPath)]
        public static extern void deleteStringArray_v2();

        [DllImport(dllPath)]
        [return: MarshalAs(UnmanagedType.AnsiBStr)]
        public static extern string getBigWordLength_v2(StringCppArray stringarray);

[DllImport(dllPath)]
public static extern void writeBuffer(string fileName, int start, int size, IntPtr buffer);

[DllImport(dllPath)]
public static extern void readBuffer(string fileName, int start, int size, IntPtr buffer);

    }
}
