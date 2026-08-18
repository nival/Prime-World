using System.Collections.Generic;
using UnityEngine;

namespace Flash
{
  internal class FontStorageDebugViewer : MonoBehaviour
  {
    public List<Texture2D> _textures = new List<Texture2D>();

    private void OnDestroy()
    {
      foreach ( Texture2D texture in _textures )
      {
        DestroyImmediate( texture );
      }
    }
  }
}


