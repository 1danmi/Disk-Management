using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FMS_adapter;


namespace FMS_GUI
{
    public class DMS
    {
        List<FCB> fcbList;
        uint fcbListSize;
        Disk disk;
        FCB fcb;

        public DMS(uint size = 5)
        {
            fcbList = new List<FCB>();
            fcbListSize = size;
            for (int i = 0; i < fcbListSize; i++)
            {
                disk = new Disk();
                fcbList.Add(disk.openFile("", MODE.WR));
            }
        }
        ~DMS()
        {
            fcbList.Clear();
            fcbList = null;
        }
        public FCB openfile(string fn, MODE mode)
        {
            try
            {
                if (disk == null) throw new Exception("no file");
                fcb = disk.openFile(fn, mode);
                return fcb;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
}
