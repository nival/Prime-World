using System;
using System.Collections.Generic;

namespace StatisticService
{
  public class ChunklessReader : IChunklessSerializer
  {
    public ChunklessReader(System.IO.BinaryReader _reader)
    {
      reader = _reader;
    }

    public override void Add( ref int v ) { v = reader.ReadInt32(); }
    public override void Add( ref uint v ) { v = reader.ReadUInt32(); }
    public override void Add( ref long v ) { v = reader.ReadInt64(); }
    public override void Add( ref ulong v ) { v = reader.ReadUInt64(); }
    public override void Add( ref byte v ) { v = reader.ReadByte(); }
    public override void Add( ref float v ) { v = reader.ReadSingle(); }
    public override void Add( ref double v ) { v = reader.ReadDouble(); }
    public override void Add( ref bool v ) { v = reader.ReadBoolean(); }

    public override void Add( ref String v )
    {
      int len = reader.ReadInt32();

      if (len <= 0)
        return;

      var builder = new System.Text.StringBuilder(len);
      for (int i = 0; i < len; ++i)
      {
        var c = (char)reader.ReadInt16();
        builder.Append(c);
      }

      v = builder.ToString();
    }

    public override void Add(List<int> v)
    {
      int size = reader.ReadInt32();

      for (int i = 0; i < size; ++i)
      {
        v.Add(reader.ReadInt32());
      }
    }

    public override void Add<T>(List<T> v)
    {
      int size = reader.ReadInt32();

      for (int i = 0; i < size; ++i)
      {
        var tmp = new T();
        tmp.Serialize(this);
        v.Add(tmp);
      }
    }

    private System.IO.BinaryReader reader;
  }
}
