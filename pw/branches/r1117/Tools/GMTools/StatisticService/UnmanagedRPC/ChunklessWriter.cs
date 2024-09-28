using System.Collections.Generic;
using System.IO;

namespace StatisticService
{
  public class ChunklessWriter : IChunklessSerializer
  {
    private BinaryWriter writer;

    public ChunklessWriter(BinaryWriter writer)
    {
      this.writer = writer;
    }

    public override void Add(ref int v) { throw new System.NotImplementedException(); }
    public override void Add(ref uint v) { throw new System.NotImplementedException(); }
    public override void Add(ref long v) { throw new System.NotImplementedException(); }
    public override void Add(ref ulong v) { throw new System.NotImplementedException(); }
    public override void Add(ref byte v) { throw new System.NotImplementedException(); }
    public override void Add(ref float v) { throw new System.NotImplementedException(); }
    public override void Add(ref double v) { throw new System.NotImplementedException(); }
    public override void Add(ref bool v) { throw new System.NotImplementedException(); }
    public override void Add(ref string v) { throw new System.NotImplementedException(); }

    public override void Add(List<int> v)
    {
      writer.Write(v.Count);
      v.ForEach(writer.Write); // c# power!
    }
    
    public override void Add<T>(List<T> v)
    {
      throw new System.NotImplementedException();
    }
  }
}