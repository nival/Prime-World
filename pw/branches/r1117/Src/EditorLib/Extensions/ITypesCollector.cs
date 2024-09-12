using System;
using System.Collections.Generic;

namespace EditorLib.Extensions
{
  public interface ITypesCollector
  {
    void TryRegisterType(Type type);
  }
}