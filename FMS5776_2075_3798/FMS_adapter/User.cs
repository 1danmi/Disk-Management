using System.Runtime.InteropServices;

namespace FMS_adapter
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class User
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string name;
        public string Name { get { return name; } set { name = value; } }

        SLEVEL sLevel;
        public SLEVEL SLevel { get { return sLevel; } set { sLevel = value; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        string password;
        public string Password { get { return password; } set { password = value; } }
    }
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class UsersSec
    {
        int sectorNr;
        public int SectorNr { get { return sectorNr; } }

        int numOfUsers = 0;
        public int NumOfUsers { get { return numOfUsers; } }

        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 5)]
        User users;
        public User Users { get { return users; } }

        //char RawData[1024 - 5 * sizeof(User) - 2 * sizeof(int)];
    }
}
