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
#ifndef _ATTRIBUTEH
#define _ATTRIBUTEH
#include <string>
#include "xmlpull/wsdlpull_export.h"

namespace Schema {
class WSDLPULL_EXPORT Attribute
{
 public:
  Attribute(const std::string & name, 
            int type_id,
            bool qualified = false,
            std::string defaultVal = "", 
            std::string fixedVal = "", 
            bool use = false);
  Attribute(void);

  std::string getName() const;
  int getType() const;
  bool isRequired() const;
  std::string  defaultVal()const;
  std::string  fixedVal()const;
  bool isQualified()const ;
  Attribute & operator = (const Attribute & a);

 private:
  std::string attName;
  std::string dval, fval;
  int attType;
  bool bQualified, attUse;

};
#ifdef LOGGING
std::ostream & operator << (std::ostream & stream, Attribute & a);
#endif                                            /*  */

inline
Attribute::Attribute(const std::string & name, 
		     int type_id,
		     bool qualified,
		     std::string defaultVal, 
		     std::string fixedVal, 
		     bool use)
  :attName(name),
     dval(defaultVal),
     fval(fixedVal),
     attType(type_id),
     bQualified (qualified),
     attUse (use)
{
}

inline
Attribute::Attribute(void)
  :attType(0),
     bQualified (false),
     attUse (false)
{
}

inline
std::string
Attribute::getName() const
{
  return attName;
}

inline
int 
Attribute::getType() const
{
  return attType;
}

inline
bool
Attribute::isRequired() const
{
  return attUse;
}

inline
std::string 
Attribute::defaultVal()const
{
  return dval;
}

inline
std::string 
Attribute::fixedVal()const
{
  return fval;
}

inline
bool 
Attribute::isQualified()const 
{
  return bQualified;
}

inline
Attribute & 
Attribute::operator = (const Attribute & a)
{
  attName = a.attName;
  attType = a.attType;
  bQualified = a.isQualified();
  dval = a.dval;
  fval = a.fval;
  attUse = a.attUse;
  return *this;
}
}
#endif                                            /*  */
