using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS_adapter
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class SectorDir
    {
        int sectorNr;
        public int SectorNr { get { return sectorNr; } }

        DirEntry[] dirEntry = new DirEntry[14];

        //DirEntry dirEntry[14];
        //[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 14)]
        //DirEntry dirEntry;
        //public DirEntry DirEntry { get { return dirEntry; } }

        //char unUsed[12];
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        char unUsed;
        public char UnUsed { get { return unUsed; } }

        IntPtr mySectorDirPtr;

        public DirEntry getDirEntry(int index)
        {
            try
            {

                DirEntry de = new DirEntry();
                int structSize = Marshal.SizeOf(de.GetType()); //Marshal.SizeOf(typeof(Student)); 
                IntPtr buffer = Marshal.AllocHGlobal(structSize);
                Marshal.StructureToPtr(de, buffer, true);

                // ... send buffer to dll
                cppToCsharpAdapter.getDirEntry(this.mySectorDirPtr, buffer, index);
                Marshal.PtrToStructure(buffer, de);

                // free allocate
                Marshal.FreeHGlobal(buffer);

                return de;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.mySectorDirPtr);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

     }
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class RootDir
    {
        SectorDir lsbSector;
        public SectorDir LsbSector { get { return lsbSector; } }

        SectorDir msbSector;
        public SectorDir MsbSector { get { return msbSector; } }
    }
}
