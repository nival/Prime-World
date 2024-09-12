// Copyright 2009 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include "timesupport.h"

#include <time.h>
#include <ctype.h>
#include <string.h>

#include <System/ported/cwfn.h>

#ifdef WIN32
// Implement strptime under windows
static const char* kWeekFull[] = {
  "Sunday", "Monday", "Tuesday", "Wednesday",
  "Thursday", "Friday", "Saturday"
};

static const char* kWeekAbbr[] = {
  "Sun", "Mon", "Tue", "Wed",
  "Thu", "Fri", "Sat"
};

static const char* kMonthFull[] = {
  "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December"
};

static const char* kMonthAbbr[] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const char* _parse_num(const char* s, int low, int high, int* value) {
  const char* p = s;
  for (*value = 0; *p != NULL && isdigit(*p); ++p) {
    *value = (*value) * 10 + static_cast<int>(*p) - static_cast<int>('0');
  }

  if (p == s || *value < low || *value > high) return NULL;
  return p;
}

static char* _strptime(const char *s, const char *format, struct tm *tm) {
  while (*format != NULL && *s != NULL) {
    if (*format != '%') {
      if (*s != *format) return NULL;

      ++format;
      ++s;
      continue;
    }

    ++format;
    int len = 0;
    switch (*format) {
      // weekday name.
      case 'a':
      case 'A':
        tm->tm_wday = -1;
        for (int i = 0; i < 7; ++i) {
          len = static_cast<int>(strlen(kWeekAbbr[i]));
          if (_strnicmp(kWeekAbbr[i], s, len) == 0) {
            tm->tm_wday = i;
            break;
          }

          len = static_cast<int>(strlen(kWeekFull[i]));
          if (_strnicmp(kWeekFull[i], s, len) == 0) {
            tm->tm_wday = i;
            break;
          }
        }
        if (tm->tm_wday == -1) return NULL;
        s += len;
        break;

      // month name.
      case 'b':
      case 'B':
      case 'h':
        tm->tm_mon = -1;
        for (int i = 0; i < 12; ++i) {
          len = static_cast<int>(strlen(kMonthAbbr[i]));
          if (_strnicmp(kMonthAbbr[i], s, len) == 0) {
            tm->tm_mon = i;
            break;
          }

          len = static_cast<int>(strlen(kMonthFull[i]));
          if (_strnicmp(kMonthFull[i], s, len) == 0) {
            tm->tm_mon = i;
            break;
          }
        }
        if (tm->tm_mon == -1) return NULL;
        s += len;
        break;

      // month [1, 12].
      case 'm':
        s = _parse_num(s, 1, 12, &tm->tm_mon);
        if (s == NULL) return NULL;
        --tm->tm_mon;
        break;

      // day [1, 31].
      case 'd':
      case 'e':
        s = _parse_num(s, 1, 31, &tm->tm_mday);
        if (s == NULL) return NULL;
        break;

      // hour [0, 23].
      case 'H':
        s = _parse_num(s, 0, 23, &tm->tm_hour);
        if (s == NULL) return NULL;
        break;

      // minute [0, 59]
      case 'M':
        s = _parse_num(s, 0, 59, &tm->tm_min);
        if (s == NULL) return NULL;
        break;

      // seconds [0, 60]. 60 is for leap year.
      case 'S':
        s = _parse_num(s, 0, 60, &tm->tm_sec);
        if (s == NULL) return NULL;
        break;

      // year [1900, 9999].
      case 'Y':
        s = _parse_num(s, 1900, 9999, &tm->tm_year);
        if (s == NULL) return NULL;
        tm->tm_year -= 1900;
        break;

      // year [0, 99].
      case 'y':
        s = _parse_num(s, 0, 99, &tm->tm_year);
        if (s == NULL) return NULL;
        if (tm->tm_year <= 68) {
          tm->tm_year += 100;
        }
        break;

      // arbitray whitespace.
      case 't':
      case 'n':
        while (isspace(*s)) ++s;
        break;

      // '%'.
      case '%':
        if (*s != '%') return NULL;
        ++s;
        break;

      // All the other format are not supported.
      default:
        return NULL;
    }
    ++format;
  }

  if (*format != NULL) {
    return NULL;
  } else {
    return const_cast<char*>(s);
  }
}

char* strptime(const char *buf, const char *fmt, struct tm *tm) {
  return _strptime(buf, fmt, tm);
}
#endif  // WIN32

#if defined(__linux__) || defined(__unix__)

time_t _mkgmtime(const struct tm *tm) {
  // Month-to-day offset for non-leap-years.
  static const int month_day[12] =
    {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

  // Most of the calculation is easy; leap years are the main difficulty.
  int month = tm->tm_mon % 12;
  int year = tm->tm_year + tm->tm_mon / 12;
  if (month < 0) {   // Negative values % 12 are still negative.
    month += 12;
    --year;
  }

  // This is the number of Februaries since 1900.
  const int year_for_leap = (month > 1) ? year + 1 : year;

  time_t rt = tm->tm_sec                             // Seconds
       + 60 * (tm->tm_min                          // Minute = 60 seconds
       + 60 * (tm->tm_hour                         // Hour = 60 minutes
       + 24 * (month_day[month] + tm->tm_mday - 1  // Day = 24 hours
       + 365 * (year - 70)                         // Year = 365 days
       + (year_for_leap - 69) / 4                  // Every 4 years is leap...
       - (year_for_leap - 1) / 100                 // Except centuries...
       + (year_for_leap + 299) / 400)));           // Except 400s.
  return rt < 0 ? -1 : rt;
}

#endif

bool ParseRfcTime(const char* buf, struct tm *tm) {
  memset(tm, 0, sizeof(*tm));
  return
    strptime(buf, "%a, %e %b %Y %H:%M:%S", tm) ||  // RFC 822/1123
    strptime(buf, "%a, %e-%b-%y %H:%M:%S", tm) ||  // RFC 850/1036
    strptime(buf, "%a %b %e %H:%M:%S %Y",  tm);    // asctime()
}

// Covert the time to W3C Datetime formats.
// See http://www.w3.org/TR/NOTE-datetime
const std::string FormatW3CTime(const time_t &time) {
  char buffer[80];
  struct tm TM;
  gmtime_s(&TM, &time);
  strftime(buffer, 80,
           "%Y-%m-%dT%H:%M:%SZ",  // like 2001-12-31T23:59:59Z
           &TM);
  return buffer;
}

std::string FormatHttpDate(time_t t) {
  // Convert 'time_t' to struct tm (GMT)
  tm gmt_p;
  gmtime_s(&gmt_p, &t);

  // Convert struct tm to HTTP-date string
  char buff[256];
  strftime(buff, sizeof(buff), "%a, %d %b %Y %H:%M:%S GMT", &gmt_p);
  return buff;
}
