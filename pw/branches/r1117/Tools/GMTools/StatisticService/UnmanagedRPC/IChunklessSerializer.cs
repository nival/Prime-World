using System;
using System.Collections.Generic;

namespace StatisticService
{
  public abstract class ISerializable
  {
    public abstract void Serialize(IChunklessSerializer s);
  }

  public abstract class IChunklessSerializer
  {
    public abstract void Add(ref int v);
    public abstract void Add(ref uint v);
    public abstract void Add(ref long v);
    public abstract void Add(ref ulong v);
    public abstract void Add(ref byte v);
    public abstract void Add(ref float v);
    public abstract void Add(ref double v);
    public abstract void Add(ref bool v);
    public abstract void Add(ref String v);
    public abstract void Add(List<int> v);

    public abstract void Add<T>(List<T> v) where T : ISerializable, new();

    public void Add(ISerializable v)
    {
      v.Serialize(this);
    }
  }
}
