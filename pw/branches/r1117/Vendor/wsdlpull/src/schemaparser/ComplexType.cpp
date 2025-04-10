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

#include "schemaparser/ComplexType.h"

namespace Schema {

ComplexType::ComplexType(const std::string & ns)
  :XSDType(ns),
   simpleContentTypeId_ (0),
   cm_(0),
   fwdElemRef_(false),
   fwdAttrRef_(false)
{

  setContentModel(Schema::Complex);
}

void 
ComplexType::addAttribute(const Attribute& a,
                          bool ref)
{
  fwdAttrRef_=ref;
    
  Attribute *at= (Attribute *)getAttribute(a.getName());
  if(at){
    *at=a;
  }else{
    attList_.push_back(a);
  }
}


void
ComplexType::addAttributeGroupName(const Qname & qn)
{
  //TODO
  //store the attribute group and add all attributes later
  //by calling addAttribute()
}

void
ComplexType::matchElementRef(const std::string & name, Element & e)
{
  if(cm_) {
    cm_->matchforwardRef(name,e);
  }
}

void
ComplexType::matchAttributeRef(const std::string & nam, 
			       Attribute & a)
{
  if (fwdAttrRef_) {
    Attribute *at = (Attribute*)getAttribute(nam);
    if (at)
      *at = a;
  }
}

const Attribute *
ComplexType::getAttribute(const std::string & nam) const
{
    std::list < Attribute >::const_iterator pAttr = attList_.begin();
    while (pAttr != attList_.end())
    {
        if (pAttr->getName() == nam)
            return &(*pAttr);
        pAttr++;
    }
    return 0;
}


void ComplexType::error(std::string msg) const
{
  msg+="Complex Type "+ getName() +msg;
  SchemaParserException spe(msg);
  throw spe;
  return;
}

const Attribute *
ComplexType::getAttribute(int index) const
{
  
  int i=0;
  for (std::list<Attribute>::const_iterator ali=attList_.begin();
       ali!=attList_.end();ali++,i++) {
    if(i==index)
      return &(*ali);
  }  
  return 0;
  
}
}
