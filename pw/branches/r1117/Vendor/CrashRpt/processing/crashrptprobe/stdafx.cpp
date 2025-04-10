/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/


// stdafx.cpp : source file that includes just the standard includes
// CrashRptProbe.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

int _STPRINTF_S(TCHAR* buffer, size_t sizeOfBuffer, const TCHAR* format, ... )
{
    va_list args; 
    va_start(args, format);

#if _MSC_VER<1400
    UNREFERENCED_PARAMETER(sizeOfBuffer);
    return _vstprintf(buffer, format, args);
#else
    return _vstprintf_s(buffer, sizeOfBuffer, format, args);
#endif
}
