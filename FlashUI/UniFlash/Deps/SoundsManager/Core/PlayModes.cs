using System;

namespace Unity.Components.SoundsManager.Core
{
  [Flags]
  public enum ClipPlayMode
  {
    None = 0,
    Loop = 2,
    FromRandomPoint = 4
  }
}
