using System;
using libdb.Diagnostics;

namespace EditorLib.OutputPanel
{
  public class OutputMessage
  {
    public readonly Log.Level level;
    public readonly string message;
    public readonly DateTime time;

    public OutputMessage(Log.Level _level, string _message)
    {
      level = _level;
      message = _message;
      time = DateTime.Now;
    }
  }
}
