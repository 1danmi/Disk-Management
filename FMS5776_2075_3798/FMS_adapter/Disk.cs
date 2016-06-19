using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS_adapter
{
    public class Disk
    {
        //disk class from c++
        bool vhdUpdate;
        public bool VhdUpdate{ get { return vhdUpdate; } }

        //DAT dat;

        bool datUpdate;
        public bool DatUpdate { get { return datUpdate; } }

        User currUser;
        UsersSec users;

        bool usersUpdate;
        public bool UsersUpdate { get { return usersUpdate; } }

        bool rootDirUpdate;
        public bool RootDirUpdate { get { return rootDirUpdate; } }

        bool mounted;
        public bool Mounted { get { return mounted; } }

        //fstream dskfl;

        bool sign;
        public bool Sign { get { return sign; } }

        uint currDiskSectorNr;
        public uint CurrDiskSectorNr { get { return currDiskSectorNr; } }

        //string lastErrorMessage;

        VHD vhd;
        public VHD Vhd { get { return vhd; } }

        RootDir rootDir;

        IntPtr myDiskPtr;

        //level 0
        public Disk()
        {
            myDiskPtr = cppToCsharpAdapter.makeDiskObject();
        }
        ~Disk()
        {
            if (myDiskPtr != null) cppToCsharpAdapter.deleteDiskObject(ref myDiskPtr);
        }

        public void createDisk(string dn, string dow, string pwd)
        {
            try
            {
                cppToCsharpAdapter.createDisk(this.myDiskPtr, dn, dow,pwd);
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
        public void mountDisk(string fn)
        {
            try
            {
                cppToCsharpAdapter.mountDisk(this.myDiskPtr, fn);
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
        public void unmountDisk()
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

        public void addUser(string user, SLEVEL sLevel, string pwd, SLEVEL applicantSLevel)
        {
            try
            {
                cppToCsharpAdapter.addUser(this.myDiskPtr, user, sLevel, pwd, applicantSLevel);
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
        public void signIn(string user, string pwd)
        {
            try
            {
                cppToCsharpAdapter.signIn(this.myDiskPtr, user, pwd);
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
        public void signOut()
        {
            try
            {
                cppToCsharpAdapter.signOut(this.myDiskPtr);
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
        public void removeUser(string user, string pwd)
        {
            try
            {
                cppToCsharpAdapter.removeUser(this.myDiskPtr, user, pwd);
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
        public void removeUserSigned(string user, SLEVEL applicantSLevel)
        {
            try
            {
                cppToCsharpAdapter.removeUserSigned(this.myDiskPtr, user, applicantSLevel);
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

        public void format()
        {
            try
            {
                cppToCsharpAdapter.format(this.myDiskPtr);
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
        public void createFile(string fileName, string recFormat,
                                uint recSize, uint recNum, uint numOfSecs,
                                string keyType, SLEVEL slevel, uint keyOffset, uint keySize = 0, uint algo = 0)
        {
            try
            {
                cppToCsharpAdapter.createFile(this.myDiskPtr, fileName, recFormat, recSize, recNum, numOfSecs, keyType, slevel, keyOffset, keySize, algo);
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
        public void delFile(string fn)
        {
            try
            {
                cppToCsharpAdapter.delFile(this.myDiskPtr, fn);
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
        public void extendFile(string fn, uint size)
        {
            try
            {
                cppToCsharpAdapter.extendFile(this.myDiskPtr, fn, size);
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
        public FCB openFile(string fn, MODE mo)
        {
            try
            {
                IntPtr p = cppToCsharpAdapter.openFile(this.myDiskPtr, fn, mo);
                return new FCB(p);
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

        //level 4
        public VHD getVHD()
        {
            try
            {

                VHD v = new VHD();
                int structSize = Marshal.SizeOf(v.GetType()); //Marshal.SizeOf(typeof(Student)); 
                IntPtr buffer = Marshal.AllocHGlobal(structSize);
                Marshal.StructureToPtr(v, buffer, true);

                // ... send buffer to dll
                cppToCsharpAdapter.getVHD(this.myDiskPtr, buffer);
                Marshal.PtrToStructure(buffer, v);

                // free allocate
                Marshal.FreeHGlobal(buffer);

                return v;
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
    }
}
