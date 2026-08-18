using UnityEngine;

namespace Unity.Components.SoundsManager.Chains
{
  public interface ICrossMode
  {
    void Change (AudioSource ended, AudioSource started, float changeDuration);
  }
}
