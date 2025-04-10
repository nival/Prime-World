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
 */

#ifndef SCHEMA_H

#define SCHEMA_H
// *********************************************************************
// Include files:
// *********************************************************************
#include <string>

namespace Schema {
  
  // enums ,compositors
  typedef enum { 
    Sequence, 
    Choice, 
    All 
  } Compositor;

  typedef enum {
    Restriction,
    Extension
  } Derivation;
  
  //Content Model
  typedef enum{
      None,
      Simple,
      Complex,
      Mixed
      } ContentModelType;
  
  typedef enum {
    NoConstraint,
    Key,
    Keyref,
    Unique
  } ConstraintType;
  
  //List of primitive types
  typedef enum
    {
      XSD_INVALID,
      XSD_SCHEMA,
      XSD_STRING,
      XSD_INTEGER,
      XSD_INT,
      XSD_BYTE,
      XSD_POSINT,
      XSD_UINT,
      XSD_LONG,
      XSD_ULONG,
      XSD_SHORT,
      XSD_USHORT,
      XSD_DECIMAL,
      XSD_FLOAT,
      XSD_DOUBLE,
      XSD_BOOLEAN,
      XSD_TIME,
      XSD_DATETIME,
      XSD_DATE,
      XSD_TOKEN,
      XSD_QNAME,
      XSD_NCNAME,
      XSD_NMTOKEN,
      XSD_NMTOKENS,
      XSD_BASE64BIN,
      XSD_HEXBIN,
      XSD_ANY,
      XSD_ANYTYPE,
      XSD_ANYURI
    }Type;
  
  const std::string SchemaUri = "http://www.w3.org/2001/XMLSchema";
  const std::string SchemaInstaceUri = "http://www.w3.org/2001/XMLSchema-instance";
}
#endif // SCHEMA_H
