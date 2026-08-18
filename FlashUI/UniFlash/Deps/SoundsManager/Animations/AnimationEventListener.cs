using Unity.Components.SoundsManager;
using UnityEngine;

[RequireComponent( typeof( Animation ) )]
public class AnimationEventListener : MonoBehaviour
{
  public void PlaySound( AudioClip clip )
  {
    Sound.PlayUI( clip);
  }
}


