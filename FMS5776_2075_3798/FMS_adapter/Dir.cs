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

        //DirEntry dirEntry[14];
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 14)]
        DirEntry dirEntry;
        public DirEntry DirEntry { get { return dirEntry; } }

        //char unUsed[12];
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        char unUsed;
        public char UnUsed { get { return unUsed; } }

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
