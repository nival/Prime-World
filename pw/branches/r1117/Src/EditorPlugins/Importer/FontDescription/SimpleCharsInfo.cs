using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Text;
using System.Runtime.InteropServices;

namespace EditorPlugins.Importer.FontDescriptionExporter
{
	public struct SimpleCharInfo
	{
		public readonly int a;
		public readonly int b;
		public readonly int c;
		public readonly bool nonEmpty;
		public readonly int maxWidth;

		public SimpleCharInfo( int _a, int _b, int _c )
		{
			a = _a;
			b = _b + 1;
			c = _c;
			maxWidth = Math.Abs(_a) + Math.Abs(_b) + Math.Abs(_c);
			nonEmpty = maxWidth > 0;
		}
	}

	public class SimpleCharsInfo
	{
		public readonly int height;
		public readonly int internalLeading;
		public readonly int externalLeading;
		public readonly int ascent;
		public readonly int descent;

		public readonly char defaultChar;
		public readonly int spaceWidth;
    public readonly int maxWidth;

		public Dictionary<char, SimpleCharInfo> chars;

    public readonly List<Win32.KERNINGPAIR> kerningPairs;

		private static SimpleCharInfo MeasureChar( IntPtr hdc, char c )
		{
			Win32.ABC abc = new Win32.ABC();
			if ( Win32.GDI.GetCharABCWidthsW( hdc, (int)c, (int)c, ref abc ) != 0 )
				return new SimpleCharInfo( abc.abcA, abc.abcB, abc.abcC );
			else
				return new SimpleCharInfo( 0, 0, 0 );
		}

		public SimpleCharsInfo( Font font, char[] _chars )
		{
			Bitmap image = new Bitmap( 16, 16, System.Drawing.Imaging.PixelFormat.Format32bppArgb );
			Graphics graphics = Graphics.FromImage( image );
			IntPtr hdc = graphics.GetHdc();

			IntPtr hFont = font.ToHfont();
			Win32.GDI.SelectObject( hdc, hFont );
			Win32.TEXTMETRIC metrics = new Win32.TEXTMETRIC();
			Win32.GDI.GetTextMetrics( hdc, ref metrics );

			SimpleCharInfo space = MeasureChar(hdc, ' ');

			height = metrics.tmHeight;
			ascent = metrics.tmAscent;
			externalLeading = metrics.tmExternalLeading;
			internalLeading = metrics.tmInternalLeading;
			descent = metrics.tmDescent;

			defaultChar = (char)metrics.tmDefaultChar;
			spaceWidth = space.a + space.b + space.c;

      maxWidth = 0;

			chars = new Dictionary<char, SimpleCharInfo>();

			foreach ( char c in _chars )
			{
				if ( !chars.ContainsKey( c ) )
				{
					SimpleCharInfo charInfo = MeasureChar( hdc, c );
          if (charInfo.nonEmpty)
          {
            chars.Add(c, charInfo);
            maxWidth = Math.Max(maxWidth, charInfo.a + charInfo.b + charInfo.c);
          }
				}
			}

      ///Kerning pairs///
      Trace.TraceInformation("Retrieving kerning information for font '{0}' {1}", font.Name, font.Size);
      uint kerningLength = Win32.GDI.GetKerningPairs(hdc, 0, null);
      if (kerningLength > 0)
      {
        //TODO:iA: вычитал в инете про баг в старых виндах: если размер буфера меньше или равен 128,
        //то функция может самопроизвольно валить приложение.
        //Сохранился ли этот баг в современных виндах, неизвестно
        Win32.KERNINGPAIR[] tmp = new Win32.KERNINGPAIR[kerningLength];
        kerningLength = Win32.GDI.GetKerningPairs(hdc, kerningLength, tmp);
        Trace.TraceInformation("{0} kerning pairs found", kerningLength);

        kerningPairs = new List<Win32.KERNINGPAIR>();

        uint nonZeroPairs = 0;
        for (int i = 0; i < kerningLength; ++i)
          if (tmp[i].iKernAmount > 0)
          {
            ++nonZeroPairs;
            SimpleCharInfo buf;
            if (chars.TryGetValue((char)tmp[i].wFirst, out buf) && chars.TryGetValue((char)tmp[i].wSecond, out buf))
              kerningPairs.Add(tmp[i]);
          }
        Trace.TraceInformation("{0} of them is non-zero and {1} is needed", nonZeroPairs, kerningPairs.Count);

        //Lets dump available pairs
        if (kerningPairs.Count > 0)
        {
          string dumpPairs = "";
          foreach (Win32.KERNINGPAIR pair in kerningPairs)
          {
            if (dumpPairs.Length > 0)
              dumpPairs += ", ";
            dumpPairs += "('" + (char)pair.wFirst + "' " + pair.iKernAmount.ToString() + " '" + (char)pair.wSecond + "')";
          }
          Trace.TraceInformation("Available pairs: {0}", dumpPairs);
        }
      }
      else
        Trace.TraceInformation("No kerning information found!");

			graphics.ReleaseHdc( hdc );
		}
	}
}
