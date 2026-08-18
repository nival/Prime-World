using Unity.Components.SoundsManager.Effects;
using UnityEngine;

namespace Unity.Components.SoundsManager.Chains
{
  public class CrossFade : ICrossMode
  {
    public void Change (AudioSource ended, AudioSource started, float changeDuration)
    {
      if (ended != null)
        Fade.Create (ended, FadeType.Out, changeDuration, true);
      if (started != null)
        Fade.Create (started, FadeType.In, changeDuration, false);
    }
  }
}
