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

#ifndef ATTRIBUTEGROUP_H

#define ATTRIBUTEGROUP_H
// *********************************************************************
// Include files:
// *********************************************************************
#include <list>
#include "xmlpull/wsdlpull_export.h"
#include "schemaparser/Schema.h"
#include "schemaparser/Attribute.h"

namespace Schema {
class WSDLPULL_EXPORT AttributeGroup
{
 public:
  AttributeGroup();
  AttributeGroup(const std::string & n);
  void addAttribute(const Attribute& a);
  std::string getName()const;
  std::list<Attribute>::iterator begin();
  std::list<Attribute>::iterator end();

 private:
  std::list<Attribute> att_list;
  std::string name;
  
};

inline
AttributeGroup::AttributeGroup(const std::string & n)
  :name(n)
{
  att_list.clear();
}

inline
void
AttributeGroup::addAttribute(const Attribute& a)
{
  att_list.push_back(a);
}

inline
std::list<Attribute>::iterator
AttributeGroup::begin()
{
 return att_list.begin();
}

inline
std::list<Attribute>::iterator
AttributeGroup::end()
{
 return att_list.end();
}
   
inline
std::string
AttributeGroup::getName()const
{
  return name;
}
}
#endif // ATTRIBUTEGROUP_H
