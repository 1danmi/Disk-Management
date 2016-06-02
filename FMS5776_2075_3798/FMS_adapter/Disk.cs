using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS_adapter
{
    class Disk
    {
        IntPtr myDiskPtr;

        //level 0
        public Disk()
        {
            this.myDiskPtr = cppToCsharpAdapter.makeDiskObject();
        }
        ~Disk()
        {
            if (myDiskPtr != null) cppToCsharpAdapter.deleteDiskObject(ref myDiskPtr);
        }

        public void createDisk(string dn, string dow)
        {
            try
            {
                cppToCsharpAdapter.createDisk(this.myDiskPtr, dn, dow);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPtr);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void mountDisk(string dn)
        {
            try
            {
                cppToCsharpAdapter.mountDisk(this.myDiskPtr, dn);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPtr);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void unmountDisk(IntPtr THIS)
        {
            try
            {
                cppToCsharpAdapter.unmountDisk(this.myDiskPtr);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPtr);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void recreateDisk(string dow)
        {
            try
            {
                cppToCsharpAdapter.recreateDisk(this.myDiskPtr, dow);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPtr);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        //level 1

        public void format(string dow)
        {
            try
            {
                cppToCsharpAdapter.format(this.myDiskPtr, dow);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPtr);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public int howMuchEmpty(IntPtr THIS)
        {
            try
            {
                return cppToCsharpAdapter.howMuchEmpty(this.myDiskPtr);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPtr);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        //level 2
        public void createFile(string fn, string fo, string ft, uint recLen, uint numOfSecs, string kt, uint ko, uint ks = 0, uint algo = 0)
        {
            try
            {
                cppToCsharpAdapter.createFile(this.myDiskPtr, fn, fo, ft, recLen, numOfSecs, kt, ko, ks = 0, algo);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPtr);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void delFile(string fn, string fow)
        {
            try
            {
                cppToCsharpAdapter.delFile(this.myDiskPtr, fn, fow);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPtr);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void extendFile(string fn, string fow, uint size)
        {
            try
            {
                cppToCsharpAdapter.extendFile(this.myDiskPtr, fn, fow, size);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPtr);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        // Level3
        //public FCB openFile(string fn, string fow, MODE mo)
        //{
        //    try
        //    {
        //        return cppToCsharpAdapter.openFile(this.myDiskPtr, fn, fow, mo);
        //    }
        //    catch (SEHException)
        //    {
        //        IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPtr);
        //        string message = Marshal.PtrToStringAnsi(cString);
        //        throw new Exception(message);
        //    }
        //    catch
        //    {
        //        throw;
        //    }
        //}
    }
}
