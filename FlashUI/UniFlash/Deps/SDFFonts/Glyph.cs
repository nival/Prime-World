using UnityEngine;
using UnityEngine.Assertions;

namespace SDFFonts
{
    public class Glyph
    {
        public Texture2D Atlas { get; set; }

        public char Char { get; set; }
        public int X { get; set; }
        public int Y { get; set; }
        public int Width { get; set; }
        public int Height { get; set; }
        public int XOffset { get; set; }
        public int YOffset { get; set; }
        public int XAdvance { get; set; }
        public int YAdvance { get; set; }
        public int FontSize { get; set; }
        public int LineHeight { get; set; }
        public int BaseLine { get; set; }

        public Vector2 UvMin { get; private set; }
        public Vector2 UvMax { get; private set; }

        public void CalculateUvs()
        {
            Assert.IsTrue(Atlas != null);
            UvMin = new Vector2((float)X / (float)Atlas.width, (float)(Atlas.height - Y) / (float)Atlas.height);
            UvMax = new Vector2((float)(X + Width) / (float)Atlas.width, (float)(Atlas.height - Y - Height) / (float)Atlas.height);
        }
    }
}