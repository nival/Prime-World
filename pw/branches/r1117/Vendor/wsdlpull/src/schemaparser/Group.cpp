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

// *********************************************************************
// Include files:
// *********************************************************************
#include "schemaparser/Element.h"
#include "schemaparser/Group.h"

namespace Schema {
Group::Group()
  :maxOccurs_(1),
   minOccurs_(1)
{
}
  
Group::Group(const std::string & n,
             int minimum,
             int maximum)
  :maxOccurs_(maximum),
   minOccurs_(minimum),
   name_(n),
   cm_(0),
   ref_(false)
{
}
  
Group::Group(const Group & g)
  :maxOccurs_(g.maxOccurs_),
   minOccurs_(g.minOccurs_),
   name_(g.name_),
   cm_(g.cm_),
   ref_(true)
{
}
  
Group::~Group()
{
  if(ref_==false &&  cm_)
    delete cm_;
}
}
