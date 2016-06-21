using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace FMS_adapter
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class DirEntry
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string fileName;
        public string FileName { get { return fileName; } set { fileName = value; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string fileOwner;
        public string FileOwner { get { return fileOwner; } set { fileOwner = value; } }

        uint fileAddr;
        public uint FileAddr { get { return fileAddr; }  }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 10)]
        string crDate;
        public string CrDate { get { return crDate; } set { crDate = value; } }

        uint fileSize;
        public uint FileSize { get { return fileSize; } set { fileSize = value; } }

        uint eofRecNr;
        public uint EofRecNr { get { return eofRecNr; } }

        uint actualRecSize;
        public uint ActualRecSize { get { return actualRecSize; } set { actualRecSize = value; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 2)]
        string recFormat;
        public string RecFormat { get { return recFormat; } }

        uint keyOffset;
        public uint KeyOffset { get { return keyOffset; } }

        uint keySize;
        public uint KeySize { get { return keySize; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 2)]
        string keyType;
        public string KeyType { get { return keyType; } }

        char entryStatus;
        public char EntryStatus { get { return entryStatus; } }

        uint sLevel;
        public uint SLEVEL { get { return sLevel; } set { sLevel = value; } }
    }

}
