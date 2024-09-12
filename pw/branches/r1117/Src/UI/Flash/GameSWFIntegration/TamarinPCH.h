#ifndef _TAMARIN_STDAFX_H_
#define _TAMARIN_STDAFX_H_

#undef VMCFG_EVAL
#define AVMPLUS_VERBOSE
#include "../../stdafx.h"
#include "avmplus.h"

//This is for generated files. It turned out that I missed it when generated them. uint should be uint32_t
//TODO: consider to remove this.
typedef uint32_t	uint;

#endif


