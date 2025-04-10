/* 
 * wsdlpull - A C++ parser  for WSDL  (Web services description language)
 * Copyright (C) 2005-2007 Vivek Krishna
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *
 */
#ifndef _SCHEMAPARSEREXCEPTIONH
#define _SCHEMAPARSEREXCEPTIONH

#include <string>
#include "xmlpull/wsdlpull_export.h"

namespace Schema {
class WSDLPULL_EXPORT SchemaParserException
{
 public:
  SchemaParserException(std::string desc);
  ~SchemaParserException() throw();
  std::string description;
  int line, col;
};

inline
SchemaParserException::SchemaParserException(std::string desc)
{
 description = "Schema Parser Exception : ";
 description += desc;
}
inline
SchemaParserException::~SchemaParserException() throw()
{
}
}
#endif                                            /*  */
