using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace MyCsharp5776
{
    struct ComplexNumber
    {
        public int x { get; set; }
        public int y { get; set; }

        public override string ToString()
        {
            return string.Format("{0}+{1}i", x, y);
        }
    }
}
