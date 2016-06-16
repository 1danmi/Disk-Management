
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS_adapter
{
    public enum MODE { W, R, WR, E };
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class FCB
    {
        //   Disk* d;
        int path;
        public int Path { get { return path; } }

        DirEntry fileDesc;
        public DirEntry FileDesc { get { return fileDesc; } }

        //DATtype FAT;
        //Sector buffer;
        uint currRecNr;
        public uint CurrRecNr { get { return currRecNr; } }

        uint currSecNr;
        public uint CurrSecNr { get { return currSecNr; } }

        uint currRecNrInBuff;
        public uint CurrRecNrInBuff { get { return currRecNrInBuff; } }

        bool updateMode;
        public bool UpdateMode { get { return updateMode; } }

        //bool lock;
        //public bool Lock { get { return lock; } }

        MODE mode;
        public MODE Mode { get { return mode; } }

        uint numOfRecords;
        public uint NumOfRecords { get { return numOfRecords; } }

        //string lastErrorMessage;

        int maxRecNum;
        public int MaxRecNum { get { return maxRecNum; } }

        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 36)]
        //int dat;
        //public int DAT { get { return dat; } }
        
        bool loaded;
        public bool Loaded { get { return loaded; } }

        RecInfo recInfo;
        public RecInfo RecInfo { get { return recInfo; } }

        private IntPtr myFCBpointer;

        public FCB(IntPtr myFCBpointer)
        {
            this.myFCBpointer = myFCBpointer;
        }

        ~FCB()
        {
            if (myFCBpointer != null)
                cppToCsharpAdapter.deleteFcbObject(ref myFCBpointer);
        }

        public void closeFile()
        {
            try
            {
                cppToCsharpAdapter.closeFile(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public object readRecord(object dest, uint readForUpdate = 0)
        {
            try
            {

                IntPtr buffer;
                buffer = Marshal.AllocHGlobal(Marshal.SizeOf(dest.GetType()));

                cppToCsharpAdapter.readRecord(this.myFCBpointer, buffer, readForUpdate);
                Marshal.PtrToStructure(buffer, dest);

                Marshal.FreeHGlobal(buffer);

                return dest;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void addRecord(object source)
        {
            try
            {
                IntPtr buffer = Marshal.AllocHGlobal(Marshal.SizeOf(source.GetType()));
                Marshal.StructureToPtr(source, buffer, true);

                cppToCsharpAdapter.addRecord(this.myFCBpointer, buffer);

                Marshal.FreeHGlobal(buffer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        //public void seekRec(uint from, int pos)
        //{
        //    try
        //    {
        //        cppToCsharpAdapter.seekRec(this.myFCBpointer, from, pos);
        //    }
        //    catch (SEHException)
        //    {
        //        IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
        //        string message = Marshal.PtrToStringAnsi(cString);
        //        throw new Exception(message);
        //    }
        //    catch
        //    {
        //        throw;
        //    }
        //}

        public void updateRecCancel()
        {
            try
            {
                cppToCsharpAdapter.updateRecCancel(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void deleteRecord(uint readForUpdate)
        {
            try
            {
                cppToCsharpAdapter.deleteRecord(this.myFCBpointer, readForUpdate);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void updateRecord(object source)
        {
            try
            {
                IntPtr buffer = Marshal.AllocHGlobal(Marshal.SizeOf(source.GetType()));
                Marshal.StructureToPtr(source, buffer, true);
                cppToCsharpAdapter.updateRecord(this.myFCBpointer, buffer);
                Marshal.FreeHGlobal(buffer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
    }
}
