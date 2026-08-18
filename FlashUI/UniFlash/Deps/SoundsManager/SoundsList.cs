using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class SoundItem
{
  public string Name;
  [SerializeField]
  public AudioClip Clip;
}

public class SoundsList : MonoBehaviour
{
  public SoundItem[] Items;

  public Dictionary<string, AudioClip> GetItems()
  {
    Dictionary<string, AudioClip> result = new Dictionary<string, AudioClip>();
    foreach ( var item in Items )
    {
      bool isNameEmpty = string.IsNullOrEmpty( item.Name );
      bool isClipEmpty = item.Clip == null;
      if ( isNameEmpty || isClipEmpty )
      {
        if ( isNameEmpty )
          Debug.LogWarning( string.Format( "SoundsList contains entry with empty name '{0}'", isClipEmpty ? string.Empty : item.Clip.name ) );
        if ( isClipEmpty )
          Debug.LogWarning( string.Format( "SoundsList contains entry without clip '{0}'", item.Name ) );
        continue;
      }

      if ( result.ContainsKey( item.Name ) )
      {
        Debug.LogWarning( string.Format( "SoundsList contains entries with same name '{0}'", item.Name ) );
        continue;
      }

      result.Add( item.Name, item.Clip );
    }
    return result;
  }
}
