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


// This files includes functions to support time related operations.
// It defines common functions, which are only available on platforms.
// It also provides functions to parse RFC times.

#ifndef COMMON_TIMESUPPORT_H__
#define COMMON_TIMESUPPORT_H__

#include <time.h>
#include <string>

#ifdef WIN32
// Convert a string representation time to a time tm structure.
// It is the conversion function of strftime().
// Linux provides this function.
char *strptime(const char *buf, const char *fmt, struct tm *tm);
#endif

#if defined(__linux__) || defined(__unix__)
// Convert GMT time to UTC time value.
// It is like mktime(), but interprets the fields as GMT rather than local.
// This is the inverse of gmtime().
// Windows provides this function.
time_t _mkgmtime(const struct tm *tm);
#endif

// Tries various rfc's to convert a buffer to a struct tm.
// Warning: this function only handles a few cases and completely ignores
// time zones!
bool ParseRfcTime(const char* buf, struct tm *tm);

// Covert the time to W3C Datetime formats.
// See http://www.w3.org/TR/NOTE-datetime
const std::string FormatW3CTime(const time_t &time);

// A helper method used to format HttpDate.
std::string FormatHttpDate(time_t t);

#endif  // COMMON_TIMESUPPORT_H__
