// $Id: HTTP_10.cpp 80826 2008-03-04 14:51:23Z wotte $

#include "HTTP_10.h"

#include "JAWS/JAWS.h"

ACE_RCSID(PROTOTYPE, HTTP_10, "$Id: HTTP_10.cpp 80826 2008-03-04 14:51:23Z wotte $")

char *
JAWS_HTTP_10_Helper::HTTP_decode_string (char *path)
{
  // replace the percentcodes with the actual character
  int i, j;
  char percentcode[3];

  for (i = j = 0; path[i] != '\0'; i++, j++)
    {
      if (path[i] == '%')
        {
          percentcode[0] = path[++i];
          percentcode[1] = path[++i];
          percentcode[2] = '\0';
          path[j] = (char) ACE_OS::strtol (percentcode, (char **) 0, 16);
        }
      else
        path[j] = path[i];
    }

  path[j] = path[i];

  return path;
}
