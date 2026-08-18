using System;
using UILocalization;

namespace FlashView.Utils
{
  public static class TimeFormat
  {

    public static string ConvertAction(TimeSpan time)
    {
      if (time.Days > 1)
        return string.Format(TextResources.TimeFormatDays, time.Days);

      return string.Format("{0:00}:{1:00}:{2:00}", time.Hours + time.Days*24, time.Minutes, time.Seconds);
    }

    public static string ConvertSecondsToHoursMinutes(TimeSpan time)
    {
      if (time.Days > 0)
        return string.Format("{0:0}:{1:00}:{2:00}", time.Days, time.Hours, time.Minutes);

      if (time.Hours > 0)
        return string.Format("{0:0}:{1:00}", time.Hours, time.Minutes);

      return string.Format("{0:0}:{1:00}", time.Minutes, time.Seconds);
    }

    public static string ToShortDuration(this TimeSpan time)
    {
      int hours = time.Hours;
      if (time.Days > 0)
      {
        hours += time.Days*24;
      }

      if (hours > 0)
      {
        return string.Format("{0:00}:{1:00}:{2:00}", time.Hours, time.Minutes, time.Seconds);
      }

      return string.Format("{0:00}:{1:00}", time.Minutes, time.Seconds);
    }

    public static string ConvertSecondsToHHMM(TimeSpan time)
    {
      TimeSpan timeSpan = time;
      return String.Format("{0:00}:{1:00}", timeSpan.Days*24 + timeSpan.Hours, timeSpan.Minutes);
    }

    public static string ConvertSecondsToDDHHMM(TimeSpan time)
    {
      TimeSpan timeSpan = time;

      if (timeSpan.Days > 0)
        return string.Format("{0:0}:{1:00}:{2:00}", timeSpan.Days, timeSpan.Hours, timeSpan.Minutes);

      return String.Format("{0:0}:{1:00}", timeSpan.Hours, timeSpan.Minutes);
    }

    public static string ConvertSecondsToStopedTime(TimeSpan time)
    {
      return ConvertSecondsToStopedTime(time, false);
    }

    public static string ConvertSecondsToStopedHours(TimeSpan time, bool round)
    {
      var timeAmount = 0D;
      var finalFormat = "{0}";

      if (time.TotalHours >= 1)
      {
        timeAmount = time.TotalHours;
        finalFormat = TextResources.TimeFormatHours;
      }
      else if (time.TotalMinutes >= 1)
      {
        timeAmount = time.TotalMinutes;
        finalFormat = TextResources.TimeFormatMinutes;
        round = true; // PF-97207
      }

      if (!(timeAmount > 0)) return string.Format(TextResources.TimeFormatSeconds, Math.Round(time.TotalSeconds));
      var timeStr = string.Format(round ? "{0:#}" : "{0:0.#}", timeAmount);
      return string.Format(finalFormat, timeStr);
    }

    public static string ConvertSecondsToStopedTime(TimeSpan time, bool round)
    {
      double timeAmount = 0;
      string finalFormat = "{0}";

      if (time.Days > 0)
      {
        // PF-102420 Один день "с хвостиком" - это два дня
        timeAmount = time.Days + 1;
        finalFormat = TextResources.TimeFormatDays;
      }
      else if (time.Hours > 0)
      {
        timeAmount = time.TotalHours;
        finalFormat = TextResources.TimeFormatHours;
      }
      else if (time.Minutes > 0)
      {
        timeAmount = time.TotalMinutes;
        finalFormat = TextResources.TimeFormatMinutes;
      }

      if (timeAmount > 0)
      {
        string timeStr = string.Format(round ? "{0:#}" : "{0:0.#}", timeAmount);
        return string.Format(finalFormat, timeStr);
      }

      return string.Format(TextResources.TimeFormatSeconds, Math.Round(time.TotalSeconds));
    }

    public static string ToLongDuration(this long seconds)
    {
      var span = TimeSpan.FromSeconds(seconds);

      int days = (int) (span.TotalDays + 0.5);
   
      if (span.TotalDays < 3 * 30)
      {
        if (days == 0)
          days = 1;

        return string.Format(TextResources.TimeFormatDaysShort, days);
      }

      int month = (int)(((float)days) / 30 + 0.5);
      if (month<12)
      {
        return string.Format(TextResources.TimeFormatMonthShort, month);
      }

      int years = (int)(((float)days) / 365 + 0.5);
      return string.Format(TextResources.TimeFormatYearsShort, years);
    }

    public static string ToDaysShort(int days)
    {
      return string.Format(TextResources.TimeFormatDaysShort, days);
    }

    public static string ToWords(DateTime dateTime)
    {
      return string.Format( "{0} {1} {2}", dateTime.Day, ConvertToMonth( dateTime.Month ), dateTime.Year);
    }

    public static string ToShortWord(DateTime dateTime)
    {
      return string.Format("{0} {1}", dateTime.Day, ConvertToMonth(dateTime.Month));
    }

    public static string ToHourMinute(DateTime dateTime)
    {
      return string.Format("{0:00}:{1:00}", dateTime.Hour, dateTime.Minute);
    }

    public static string ToHourMinuteLocal( DateTime dateTime )
    {
      return string.Format( "{0:00}:{1:00}", dateTime.ToLocalTime().Hour, dateTime.ToLocalTime().Minute );
    }

    public static string ConvertToMonth(int month)
    {
      switch (month)
      {
        case 1: return TextResources.MonthJanuary;
        case 2: return TextResources.MonthFebruary;
        case 3: return TextResources.MonthMarch;
        case 4: return TextResources.MonthApril;
        case 5: return TextResources.MonthMay;
        case 6: return TextResources.MonthJune;
        case 7: return TextResources.MonthJuly;
        case 8: return TextResources.MonthAugust;
        case 9: return TextResources.MonthSeptember;
        case 10: return TextResources.MonthOctober;
        case 11: return TextResources.MonthNovember;
        case 12: return TextResources.MonthDecember;
      }

      return string.Empty;
    }
  }
}