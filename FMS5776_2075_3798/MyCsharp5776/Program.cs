using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace MyCsharp5776
{
    class Program
    {
        static void runSum()
        {
            int x = 2;
            int y = 3;
            int z = cppToCsharpAdapter.sum(x, y);
            Console.WriteLine("{0} + {1} = {2}", x, y, z);
        }

        static void runSwap()
        {
            int x = 2;
            int y = 3;
            Console.WriteLine("x={0} y={1}", x, y);
            cppToCsharpAdapter.swap(out x, ref y);
            Console.WriteLine("x={0} y={1}", x, y);
        }

        static void runSwap2()
        {
            int x = 2;
            int y = 3;
            Console.WriteLine("x={0} y={1}", x, y);
            cppToCsharpAdapter.swap2(ref x, ref y);
            Console.WriteLine("x={0} y={1}", x, y);
        }

        static void strLength()
        {
            string str = "abcdefghijklmnopqrstuvwxyz";
            int length = cppToCsharpAdapter.strLength(str);
            Console.WriteLine("str = \"{0}\"\nlength = {1}", str, length);
        }

        static void changeString()
        {
            string str = "abcdefghijklmnopqrstuvwxyz";
            Console.WriteLine("old string = {0}", str);
            cppToCsharpAdapter.changeString(ref str);
            Console.WriteLine("new string = {0}", str);
        }

        static void changeStringByIntPtr()
        {
            String oldStr = "abcdefghijklmnopqrstuvwxyz";
            IntPtr myPtr = Marshal.StringToHGlobalAnsi(oldStr);
            cppToCsharpAdapter.changeString(ref myPtr);
            string newStr = Marshal.PtrToStringAnsi(myPtr);

            Marshal.FreeHGlobal(myPtr);

            Console.WriteLine("old string = {0}", oldStr);
            Console.WriteLine("new string = {0}", newStr);
        }

        static void getChangeStringByIntPtr()
        {
            String oldStr = "abcdefghijklmnopqrstuvwxyz";
            IntPtr myPtr = Marshal.StringToHGlobalAnsi(oldStr);
            string newStr = cppToCsharpAdapter.getChangeString(ref myPtr);

            Marshal.FreeHGlobal(myPtr);

            Console.WriteLine("old string = {0}", oldStr);
            Console.WriteLine("new string = {0}", newStr);
        }

        static void getString()
        {
            string str = cppToCsharpAdapter.getString();
            Console.WriteLine("return string = {0}", str);
        }

        static void getDynamicArray()
        {
            string str1 = cppToCsharpAdapter.getDynamicArray(5);
            string str2 = cppToCsharpAdapter.getDynamicArray(10);

            Console.WriteLine("str1 = {0}", str1);
            Console.WriteLine("str2 = {0}", str2);

            cppToCsharpAdapter.deleteDynamicArray();
        }

        static void getDynamicArray_v2()
        {
            IntPtr p; // = new IntPtr();
            string str1 = cppToCsharpAdapter.getDynamicArray_v2(out p, 5);
            string str2 = cppToCsharpAdapter.getDynamicArray_v2(out p, 10);

            Console.WriteLine("str1 = {0}", str1);
            Console.WriteLine("str2 = {0}", str2);

            cppToCsharpAdapter.deleteDynamicArray_v2(out p);
        }

        static void getException()
        {
            try
            {
                cppToCsharpAdapter.getException();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
                string info = cppToCsharpAdapter.getExceptionInfo();
                Console.WriteLine("info: {0}", info);
            }
        }

        static void sumComplex()
        {
            ComplexNumber c1 = new ComplexNumber { x = 2, y = 3 };
            ComplexNumber c2 = new ComplexNumber { x = 4, y = 5 };
            ComplexNumber c3 = cppToCsharpAdapter.sumComplex(c1, c2);

            Console.WriteLine(c1);
            Console.WriteLine("+");
            Console.WriteLine(c2);
            Console.WriteLine("______");
            Console.WriteLine(c3);
        }

        static void runGetStringArray_v2()
        {
            StringCppArray v = cppToCsharpAdapter.getStringArray_v2();
            foreach (var item in v.Arr)
                Console.WriteLine(item);

            cppToCsharpAdapter.deleteStringArray_v2();
        }

        static void runGetBigWordLength_v2()
        {
            string[] arr = { "abc", "abcde", "ab", "abcd" };
            StringCppArray v = new StringCppArray { Arr = arr };
            string bigWord = cppToCsharpAdapter.getBigWordLength_v2(v);
            Console.WriteLine("big word length '{0}'", bigWord);
        }

        //static void runGetStringArray()
        //{
        //    string[] v = cppToCsharpAdapter.getStringArray();
        //    foreach (var item in v)
        //        Console.WriteLine(item);
        //}
        static void runGetBigWordNumber()
        {
            int[] arr = { 1, 2, 45, 32, 4, 5, 3, 44, 1, 0 };
            int bigNumber = cppToCsharpAdapter.getBigNumber(arr, arr.Length);
            Console.WriteLine("big word length '{0}'", bigNumber);
        }
        static void runGetBigWordLength()
        {
            string[] arr = { "abc", "abcde", "ab", "abcd" };
            string bigWord = cppToCsharpAdapter.getBigWordLength(arr, arr.Length);
            Console.WriteLine("big word length '{0}'", bigWord);
        }

        static void ReadWriteBuffer()
        {

            int structSize = Marshal.SizeOf(typeof(Data)); //Marshal.SizeOf(typeof(Student)); 

            IntPtr buffer = Marshal.AllocHGlobal(structSize);

            for (int i = 0; i < 10; i++)
            {
                Data d = new Data(i);
                Marshal.StructureToPtr(d, buffer, true);
                cppToCsharpAdapter.writeBuffer("temp.bin", i * structSize, structSize, buffer); // ... send buffer to dll
            }


            Data[] dataArray = new Data[10];

            for (int i = 0; i < 10; i++)
            {
                cppToCsharpAdapter.readBuffer("temp.bin", i * structSize, structSize, buffer);
                dataArray[i] = new Data(-1);
                Marshal.PtrToStructure(buffer, dataArray[i]);
            }

            // free allocate
            Marshal.FreeHGlobal(buffer);
        }

        static void Main(string[] args)
        {
            ReadWriteBuffer();
        }
    }
}

