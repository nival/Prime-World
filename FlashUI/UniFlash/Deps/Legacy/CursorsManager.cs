using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class CursorsManager : MonoBehaviour 
{
  public List<Texture2D> cursors;

  Dictionary<string, Texture2D> cursors_d;
  string lastCursor = null;
  int lastMode = 0;

  static CursorsManager instance;

  public static string GetCastleCursor() { return instance.lastCursor; }

  public static void SetCastleCursor(string cursorName)
  {
    instance.lastCursor = cursorName;
    if (Lobby.Configs.Config.cursor_mode == 0)
    {
      Native.NativeCode.SetCastleCursor(cursorName);
    }
    else
    {
      if (cursorName == null)
        Cursor.SetCursor(null, Vector2.zero, CursorMode.Auto);
      else
      {
        Texture2D value;
        if (instance.cursors_d.TryGetValue(cursorName, out value))
          Cursor.SetCursor(value, Vector2.zero, Lobby.Configs.Config.cursor_mode == 1 ? CursorMode.ForceSoftware : CursorMode.Auto);
      } 
    }
  }

  void Awake()
  {
    instance = this;
    cursors_d = new Dictionary<string, Texture2D>();
    foreach (Texture2D tex in cursors)
      cursors_d.Add(tex.name, tex);
  }

  void Update()
  {
    if (lastMode != Lobby.Configs.Config.cursor_mode)
    {
      Native.NativeCode.SetCastleCursor(null);
      Cursor.SetCursor(null, Vector2.zero, CursorMode.Auto);
      SetCastleCursor(lastCursor);
      lastMode = Lobby.Configs.Config.cursor_mode;
    }
  }
}
