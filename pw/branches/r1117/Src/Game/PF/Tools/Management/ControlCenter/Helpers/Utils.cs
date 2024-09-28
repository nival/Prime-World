using System;
using System.Collections.Generic;

namespace ControlCenter.Helpers
{

  public static class Utils
  {

    public static int ToUnixTimestamp(this DateTime date)
    {
      DateTime origin = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
      TimeSpan diff = date - origin;
      return (int)Math.Floor(diff.TotalSeconds);
    }

    public static DateTime FromUnixTimestamp(this long timestamp)
    {
      DateTime origin = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
      return origin.AddSeconds(timestamp);
    }

    public static DateTime FromUnixTimestamp(this int timestamp)
    {
      return FromUnixTimestamp((long)timestamp);
    }


    public static void CommandElementMove<T>(int index, List<T> elements)
    {
      if (index < 1 || index >= elements.Count)
        return;
      var to = elements[index - 1];
      var from = elements[index];
      elements[index - 1] = from;
      elements[index] = to;
    }

  }

}