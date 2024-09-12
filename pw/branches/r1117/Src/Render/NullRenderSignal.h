#pragma once
#include "..\System\SimpleSignalST.h"

struct NullRenderTag {};

typedef SimpleSignalST<int, NullRenderTag> NullRenderSignal;

enum { RENDER_DISABLE_FLAG = 2 };

#ifndef _SHIPPING
  #define _CHECK_NULLRENDER_
#endif

#ifdef _CHECK_NULLRENDER_
  #define DECLARE_NULL_RENDER_FLAG static NullRenderSignal s_nullrender;
  #define RENDER_DISABLED (RENDER_DISABLE_FLAG == s_nullrender)
#else
  #define DECLARE_NULL_RENDER_FLAG
  #define RENDER_DISABLED false
#endif // _SHIPPING