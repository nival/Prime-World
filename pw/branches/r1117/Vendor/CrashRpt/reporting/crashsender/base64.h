/************************************************************************************* 
This file is a part of CrashRpt library.
Copyright (c) 2003-2013 The CrashRpt project authors. All Rights Reserved.

Use of this source code is governed by a BSD-style license
that can be found in the License.txt file in the root of the source
tree. All contributing project authors may
be found in the Authors.txt file in the root of the source tree.
***************************************************************************************/
#pragma once

#include <string>

std::string base64_encode(unsigned char const* , unsigned int len, int split_count = 76, const char *split = "\r\n");
std::string base64_decode(std::string const& s);

