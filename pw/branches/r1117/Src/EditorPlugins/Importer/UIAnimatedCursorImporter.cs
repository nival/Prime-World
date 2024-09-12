using EditorLib;                       // for IEditorCommonApplication
using EditorLib.Extensions;            // for Importer<>
using libdb.DB;                        // for DBPtr
using libdb.IO;                        // for FileNameCounter
using libdb.Diagnostics;               // for Log
using System;                          // for UInt32 etc.
using System.IO;                       // for Stream
using System.Drawing;                  // for Bitmap
using System.Collections.Generic;      // for List<>
using System.Text;                     // for Encoding
using System.Runtime.InteropServices;  // for StructLayout, Marshal
using System.Drawing.Imaging;          // for PixelFormat
using System.Diagnostics;              // for Debug.Assert

namespace EditorPlugins.Importer.UIAnimatedCursor
{
  class Align
  {
    public static UInt32 On(UInt32 step, UInt32 value)
    {
      Debug.Assert(step > 0 && (step & (step - 1)) == 0); // must be power of two
      return (value + step - 1) & ~(step - 1);
    }
  }

  class StructWriter
  {
    public static void Write(BinaryWriter o, object data)
    {
      int rawsize = Marshal.SizeOf(data);
      byte[] rawdata = new byte[rawsize];
      GCHandle handle = GCHandle.Alloc(rawdata, GCHandleType.Pinned);
      Marshal.StructureToPtr(data, handle.AddrOfPinnedObject(), false);
      handle.Free();
      o.Write(rawdata);
    }
  }

  class CursorFile
  {
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    private struct CURSORHEADER
    {
      public Byte Width;
      public Byte Height;
      public Byte res00;
      public Byte res01;
      public UInt16 XHotSpot;
      public UInt16 YHotSpot;
      public UInt32 SizeInBytes;
      public UInt32 FileOffset;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    private struct BITMAPINFOHEADER
    {
      public UInt32 Size;
      public Int32 Width;
      public Int32 Height;
      public UInt16 Planes;
      public UInt16 BitCount;
      public UInt32 Compression;
      public UInt32 SizeImage;
      public Int32 XPelsPerMeter;
      public Int32 YPelsPerMeter;
      public UInt32 ClrUsed;
      public UInt32 ClrImportant;
    }

    CURSORHEADER entry;
    BITMAPINFOHEADER header;
    MemoryStream colorStream = new MemoryStream();
    MemoryStream maskStream = new MemoryStream();

    public UInt32 Size { 
      get {
        return entry.FileOffset + header.Size + (UInt32)colorStream.Length + (UInt32)maskStream.Length;
      }
    }

    /*
     * ---------------------------
     * .CUR file format simplified
     * ---------------------------
     * 
     * <0:WORD>
     * <2:WORD> - cursor
     * <1:WORD> - count
     * <CURSORHEADER>
     * <BITMAPINFOHEADER> - biHeight=2*H, 
     * ...bitmap... - bottom to top, each line aligned on <DWORD>, any BPP
     * ...mask...   - bottom to top, each line aligned on <DWORD>, 1 BPP
     */
    public CursorFile(Bitmap bitmap, int xHotSpot, int yHotSpot, int bitCount)
    {
      Debug.Assert(bitCount == 32 || bitCount == 16);
      if (!(bitCount == 32 || bitCount == 16))
        bitCount = 32;

      // fill cursor header
      entry.Width = (byte)bitmap.Width;
      entry.Height = (byte)bitmap.Height;
      entry.res00 = entry.res01 = 0;
      entry.XHotSpot = (UInt16)xHotSpot;
      entry.YHotSpot = (UInt16)yHotSpot;
      entry.SizeInBytes = 0; // to be filled below
      entry.FileOffset = 3 * (UInt32)Marshal.SizeOf(typeof(UInt16)) + (UInt32)Marshal.SizeOf(entry);

      // fill bitmap header
      header.Size = (UInt32)Marshal.SizeOf(header);
      header.Width = bitmap.Width;
      header.Height = bitmap.Height * 2;
      header.Planes = 1;
      header.BitCount = (UInt16)bitCount;
      header.Compression = 0;
      header.SizeImage = 0; // to be filled below
      header.XPelsPerMeter = 0;
      header.YPelsPerMeter = 0;
      header.ClrUsed = 0;
      header.ClrImportant = 0;

      // read pixels from the bitmap
      Rectangle rect = new Rectangle(0, 0, bitmap.Width, bitmap.Height);
      BitmapData data = bitmap.LockBits(rect, ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
      int size = data.Stride * bitmap.Height;
      byte[] pixels = new byte[size];
      Marshal.Copy(data.Scan0, pixels, 0, size);
      bitmap.UnlockBits(data);

      BinaryWriter colorWriter = new BinaryWriter(colorStream);
      BinaryWriter maskWriter = new BinaryWriter(maskStream);

      // convert to 15-bpp colors and 1-bpp mask
      for (int row = bitmap.Height - 1; row >= 0; --row)
      {
        int i = row * data.Stride;
        byte mask = 0;
        int maskIdx = 0;
        for (int col = 0; col < bitmap.Width; ++col)
        {
          byte b = pixels[i++];
          byte g = pixels[i++];
          byte r = pixels[i++];
          byte a = pixels[i++];

          // transparent pixels must be black (otherwise they are inverted)
          byte maskBit = 0;
          if (a == 0) // alpha-test with ref=0
          {
            r = g = b = 0;
            maskBit = 0x80; // mark as transparent
          }
          
          if (bitCount == 16)
          {
            // write converted color
            UInt16 color = (UInt16)(((r & 0xF8) << 7) | ((g & 0xF8) << 2) | ((b & 0xF8) >> 3));
            colorWriter.Write(color);
          }
          else if (bitCount == 32)
          {
            colorWriter.Write(b);
            colorWriter.Write(g);
            colorWriter.Write(r);
            colorWriter.Write(a);
          }

          // write grouped mask bits
          mask |= (byte)(maskBit >> maskIdx);
          if (++maskIdx > 7)
          {
            maskWriter.Write(mask);
            maskIdx = 0;
            mask = 0;
          }
        }
        Debug.Assert(i <= (row + 1) * data.Stride);

        // flush bit cache
        if (maskIdx != 0)
          maskWriter.Write(mask);

        // align row in both streams
        long misAlign = (colorWriter.BaseStream.Position & 3);
        while (misAlign != 0)
        {
          colorWriter.Write((byte)0);
          misAlign = (misAlign + 1) & 3;
        }
        misAlign = (maskWriter.BaseStream.Position & 3);
        while (misAlign != 0)
        {
          maskWriter.Write((byte)0);
          misAlign = (misAlign + 1) & 3;
        }
      }

      // check that data is of correct size
      UInt32 predictedSize = (UInt32)bitmap.Height * Align.On(4, (UInt32)bitmap.Width * (UInt32)bitCount / 8); // N bytes per pixel + 4 byte alignment per scanline
      Debug.Assert((Int64)predictedSize == colorWriter.BaseStream.Length);
      predictedSize = (UInt32)bitmap.Height * Align.On(4, Align.On(8, (UInt32)bitmap.Width) / 8); // 1 bit per pixel + 4 byte alignment per scanline
      Debug.Assert((Int64)predictedSize == maskWriter.BaseStream.Length);

      // calculate data size
      header.SizeImage = (UInt32)(colorWriter.BaseStream.Length + maskWriter.BaseStream.Length);
      entry.SizeInBytes = header.Size + header.SizeImage;
    } // end of ctor

    public void Serialize(BinaryWriter o)
    {
      o.Write((UInt16)0);
      o.Write((UInt16)2);
      o.Write((UInt16)1);
      StructWriter.Write(o, entry);
      StructWriter.Write(o, header);
      o.Write(colorStream.GetBuffer(), 0, (int)colorStream.Length);
      o.Write(maskStream.GetBuffer(), 0, (int)maskStream.Length);
    }
  } // end of CursorFile class

  namespace RIFF
  {
    class FOURCC
    {
      public static UInt32 From(char ch0, char ch1, char ch2, char ch3)
      {
        return ((UInt32)(ch0) | ((UInt32)(ch1) << 8) | ((UInt32)(ch2) << 16) | ((UInt32)(ch3) << 24));
      }
    }

    abstract class Chunk
    {
      private UInt32 id = 0;
      private UInt32 size = 0; // TODO: Update size

      protected UInt32 DataSize { get { return size;  } set { size = value; } }
      public UInt32 ChunkSize { get { return (UInt32)Marshal.SizeOf(id) + (UInt32)Marshal.SizeOf(size) + size; } }

      public Chunk(UInt32 id)
      {
        this.id = id;
      }

      public void Serialize(BinaryWriter o)
      {
        // there must be padding so the chunk starts on an even byte
        Int64 startPosition = o.BaseStream.Position;
        if ((startPosition & 1) != 0)
          o.Write((Byte)0);

        o.Write(id);
        o.Write(size);
        startPosition = o.BaseStream.Position;
        SerializeBody(o);
        Int64 bodySize = o.BaseStream.Position - startPosition;
        Debug.Assert(bodySize == size);
      }

      abstract public void UpdateSize();
      abstract protected void SerializeBody(BinaryWriter o);
    }

    class CompoundChunk : Chunk
    {
      private UInt32 formId;
      List<Chunk> subchunks = new List<Chunk>();

      public CompoundChunk(UInt32 id, UInt32 formId)
        : base(id)
      {
        this.formId = formId;
      }

      public CompoundChunk AddChild(Chunk subchunk)
      {
        subchunks.Add(subchunk);
        return this;
      }

      override public void UpdateSize()
      {
        this.DataSize = (UInt32)Marshal.SizeOf(formId);
        foreach (Chunk subchunk in subchunks)
        {
          this.DataSize = Align.On(2, this.DataSize); // there must be padding so the chunk starts on an even byte
          subchunk.UpdateSize();
          this.DataSize += subchunk.ChunkSize;
        }
      }

      override protected void SerializeBody(BinaryWriter o)
      {
        o.Write(formId);
        foreach (Chunk subchunk in subchunks)
        {
          subchunk.Serialize(o);
        }
      }
    }

    sealed class RiffChunk : CompoundChunk
    {
      public RiffChunk(UInt32 formId)
        : base(FOURCC.From('R', 'I', 'F', 'F'), formId)
      {
      }
    }

    sealed class ListChunk : CompoundChunk
    {
      public ListChunk(UInt32 formId)
        : base(FOURCC.From('L', 'I', 'S', 'T'), formId)
      {
      }
    }

    class AsciizChunk : Chunk
    {
      private byte[] asciiBytes;

      public AsciizChunk(UInt32 id, String data)
        : base(id)
      {
        byte[] unicodeBytes = Encoding.Unicode.GetBytes(data);
        this.asciiBytes = Encoding.Convert(Encoding.Unicode, Encoding.ASCII, unicodeBytes);
      }

      override public void UpdateSize()
      {
        this.DataSize = (UInt32)this.asciiBytes.Length + 1;
      }

      override protected void SerializeBody(BinaryWriter o)
      {
        o.Write(asciiBytes);
        o.Write((byte)0);
      }
    }

    class UInt32Chunk : Chunk
    {
      UInt32[] data;

      public UInt32Chunk(UInt32 id)
        : base(id)
      {
      }

      public void SetData(UInt32[] data)
      {
        this.data = data;
      }

      override public void UpdateSize()
      {
        this.DataSize = (UInt32)this.data.Length * (UInt32)Marshal.SizeOf(typeof(UInt32));
      }

      override protected void SerializeBody(BinaryWriter o)
      {
        foreach (var element in data)
        {
          o.Write(element);
        }
      }
    }

    class ANIHeaderChunk : Chunk
    {
      private enum ANIFLAGS
      {
        AF_ICON        = 0x00000001,
        AF_SEQUENCE    = 0x00000002,
      }

      [StructLayout(LayoutKind.Sequential, Pack = 1)]
      private struct ANIHEADER
      {
        public UInt32 size;    // Num bytes in AniHeader (36 bytes)
        public UInt32 frames;  // Number of unique Icons in this cursor
        public UInt32 steps;   // Number of Blits before the animation cycles
        public UInt32 res00, res01, res02, res03;
        public UInt32 rate;    // Default Jiffies (1/60th of a second) if rate chunk not present.
        public UInt32 flags;   // Animation Flag (see AF_ constants)
      }

      private ANIHEADER data;

      public UInt32 Frames { get { return data.frames; } set { data.frames = value; } }
      public UInt32 Steps { get { return data.steps; } set { data.steps = value; } }
      public UInt32 Rate { get { return data.rate; } set { data.rate = value; } }
      public UInt32 Flags { get { return data.flags; } set { data.flags = value; } }

      public ANIHeaderChunk()
        : base(FOURCC.From('a', 'n', 'i', 'h'))
      {
        data.size = (UInt32)Marshal.SizeOf(typeof(ANIHEADER));
        data.frames = 0;
        data.steps = 0;
        data.res00 = data.res01 = data.res02 = data.res03 = 0;
        data.rate = 1;
        data.flags = (UInt32)ANIFLAGS.AF_ICON;
      }

      override public void UpdateSize()
      {
        this.DataSize = (UInt32)Marshal.SizeOf(typeof(ANIHEADER));
      }

      override protected void SerializeBody(BinaryWriter o)
      {
        StructWriter.Write(o, data);
      }
    }

    class CursorChunk : Chunk
    {
      CursorFile cursor;

      public CursorChunk(CursorFile cursor)
        : base(FOURCC.From('i', 'c', 'o', 'n'))
      {
        this.cursor = cursor;
      }

      override public void UpdateSize()
      {
        this.DataSize = this.cursor.Size;
      }

      override protected void SerializeBody(BinaryWriter o)
      {
        this.cursor.Serialize(o);
      }
    }

  } // end of namespace RIFF


  public class UIAnimatedCursorImporter : Importer<DBTypes.UIAnimatedCursor>
  {
    protected override bool KnownDuration { get { return false; } }

    private void ImportCursor(BinaryWriter writer, DBTypes.UIAnimatedCursor cursor, List<Bitmap> frames)
    {
      /* 
       * ----------------
       * .ANI file format
       * ----------------
       * 
       * RIFF('ACON'
       *   LIST('INFO'
       *     INAM(<name:ZSTR>)
       *     IART(<copyright:ZSTR>)
       *   )
       *   anih(<ANIHEADER>)
       *   [ rate(<DWORD> <DWORD> ...) ]
       *   [ seq(<DWORD> <DWORD> ...) ]
       *   LIST('fram'
       *     icon(<frame00:ICONFILE>)
       *     icon(<frame01:ICONFILE>)
       *     ...
       *   )
       * )
       * 
       */

      RIFF.ANIHeaderChunk anih;
      RIFF.ListChunk fram;
      RIFF.UInt32Chunk rate;

      RIFF.Chunk riff = 
        new RIFF.RiffChunk(RIFF.FOURCC.From('A', 'C', 'O', 'N'))
          .AddChild(new RIFF.ListChunk(RIFF.FOURCC.From('I', 'N', 'F', 'O'))
            .AddChild(new RIFF.AsciizChunk(RIFF.FOURCC.From('I', 'N', 'A', 'M'), FileUtils.GetFileNameWithoutExtension(cursor.dstFileName)))
            .AddChild(new RIFF.AsciizChunk(RIFF.FOURCC.From('I', 'A', 'R', 'T'), "Nival Network, Copyright 2011"))
            )
          .AddChild(anih = new RIFF.ANIHeaderChunk())
          .AddChild(rate = new RIFF.UInt32Chunk(RIFF.FOURCC.From('r', 'a', 't', 'e')))
          .AddChild(fram = new RIFF.ListChunk(RIFF.FOURCC.From('f', 'r', 'a', 'm'))
          );

      // fill default frame duration in "jiffies" (1/60 sec)
      anih.Rate = cursor.fps > 0 ? (UInt32)Math.Round(60.0 / Math.Min(cursor.fps, 60)) : 1;

      // create array with frame durations
      UInt32[] rateData = new UInt32[frames.Count];
      for (int i = 0; i < frames.Count; ++i)
        rateData[i] = i == 0 ? (UInt32)Math.Round(cursor.delay * 60.0f) : anih.Rate;
      rate.SetData(rateData);

      // prepare for resize
      Int32 width = 0, height = 0;
      if (frames.Count > 0)
      {
        width = frames[0].Width;
        height = frames[0].Height;
      }

      foreach (Bitmap frame in frames)
      {
        // resize frame if required
        Bitmap bmp = frame;
        if (bmp.Height != height || bmp.Width != width)
        {
          Log.TraceWarning("Not all cursor animation frames have the same size in \"{0}\"", cursor.srcFileName.FileName);
          bmp = new Bitmap(bmp, width, height);
        }

        // append frame
        fram.AddChild(new RIFF.CursorChunk(new CursorFile(bmp, cursor.hotSpotX, cursor.hotSpotY, 32)));
        anih.Frames++;
        anih.Steps++;
      }

      riff.UpdateSize();
      riff.Serialize(writer);
    }

    protected override bool Process(DBPtr<DBTypes.UIAnimatedCursor> resource, IEditorCommonApplication application, bool fast)
    {
      DBTypes.UIAnimatedCursor cursor = resource.Get();
      if (cursor.frameCount < 1)
        cursor.frameCount = 1;

      // read sequence of image files
      List<Bitmap> frames = new List<Bitmap>(cursor.frameCount);
      FileNameCounter srcFileNames = new FileNameCounter(cursor.srcFileName.FileName, cursor.frameCount);
      foreach (string srcFileName in srcFileNames)
      {
        Bitmap image = EditorPlugins.Importer.Texture.TextureImporter.LoadImage(application.SourceFileSystem, srcFileName);
        if ( image.Width > 61 || image.Height > 61 )
        {
          Log.TraceError( "Error import animated cursor: size of bitmap \"{0}\" ({1}x{2}) exceed {3}x{3}", srcFileName, image.Width, image.Height, 61 );
          return false;
        }
        frames.Add(image);
      }

      // write ANI output
      using (BinaryWriter writer = new BinaryWriter(application.FileSystem.CreateFile(cursor.dstFileName)))
      {
        ImportCursor(writer, cursor, frames);
      }

      return true;
    }
  }
}
