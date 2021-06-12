using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TileGridEditor
{
    class GridData
    {
        // Number of Rows (X) and Columns (Y)
        public int numOfX { get; set; }
        public int numOfY { get; set; }

        //X and Y Pos + Sprite Path connected to Level Grid
        public int XPos { get; set; }
        public int YPos { get; set; }
        public string SpriteFilePath { get; set; }
    }
}
