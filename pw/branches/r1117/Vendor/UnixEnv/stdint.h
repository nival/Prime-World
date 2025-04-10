#ifndef UNIX_STDINT
#include <stddef.h>
#include <limits.h>
#include <signal.h>
#include <boost/cstdint.hpp>

#ifndef INT16_MAX
#define INT16_MAX SHRT_MAX
#endif

#ifndef INT16_MIN
#define INT16_MIN SHRT_MIN
#endif

#ifndef INT64_MAX
#define INT64_MAX _I64_MAX
#endif

#ifndef INT64_MIN
#define INT64_MIN  _I64_MIN
#endif

#ifndef INT32_MAX
#define INT32_MAX  _I32_MAX
#endif

#ifndef INT32_MIN
#define INT32_MIN  _I32_MIN
#endif

typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned char   uint8_t;

#endif
