/* Copyright (c) 2005,2007 Vivek Krishna
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The  above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE. */

#ifndef _XMLPULLPARSEREXCEPTIONH
#define _XMLPULLPARSEREXCEPTIONH

#include <string>
#include <iostream>
#ifdef HAVE_CONFIG_H //
#include <config.h>
#endif 
#include "wsdlpull_export.h"

class WSDLPULL_EXPORT XmlPullParserException
{
 public:
  XmlPullParserException (std::string desc,
			  std::string STATE,
			  int l,
			  int c)
    :state (STATE),
    line(l),
    col(c)
    {
      description = "Xml Parser Exception : " ;
      description += desc;
    }
  ~XmlPullParserException () throw ()
    {};
  std::string description, state;
  int line, col;
};
#endif                                            /*  */
