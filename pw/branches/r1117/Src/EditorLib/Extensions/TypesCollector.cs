using System;
using System.Collections.Generic;
using libdb.DB;

namespace EditorLib.Extensions
{
  public abstract class TypesCollector<T> : ITypesCollector, IEnumerable<Type>
  {
    private readonly List<Type> types = new List<Type>();

    public void TryRegisterType(Type type)
    {
      if (TypeUtils.IsSubclassOf(type, typeof(T)) && type != typeof(T)) types.Add(type);
    }

    public List<Type> GetTypes()
    {
      return types;
    }

    #region IEnumerable Members

    public IEnumerator<Type> GetEnumerator()
    {
      return types.GetEnumerator();
    }

    System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
    {
      return types.GetEnumerator();
    }

    #endregion
  }
}