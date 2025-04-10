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
#include "xmlpull/XmlUtils.h"
#include "wsdlparser/Message.h"

using namespace std;

namespace WsdlPull {
int
Message::getPartIndex(string & nam) const         
{
  for (size_t i = 0; i < parts.size(); i++)
    {
      if (parts[i].name() == nam)
	return i;
    }
  return -1;
}

Part::PartRefType 
Message::getPartRefType(int index) const
{
  return parts[index].refType();
}

Part::PartRefType
Message::getPartRefType(const string & nam) const
{
  const Part* p=getMessagePart(nam);
  if(p)
    return p->refType();
  else
    return Part::None;
}


const Part*
Message::getMessagePart(const std::string & nam)const
{
 for (size_t i = 0; i < parts.size(); i++)
   if (parts[i].name() == nam)
     return &parts[i];
 return 0;
}

int
Message::getPartType(const std::string & nam) const
{
  const Part* p=getMessagePart(nam);
  if(p)
   return p->type();
  else
    return 0;
}


int
Message::getPartContentSchemaId(const std::string & nam) const
{
  const Part* p=getMessagePart(nam);
  if(p)
    return p->schemaId();
  else
    return 0;
}

const Part*
Message::getMessagePart(size_t index)const
{
  if(index>=0 && index < parts.size())
    return &(parts[index]);
  else
    return 0;
}
   
void
Message::addPart(string pname, 
		 Part::PartRefType reftype, 
		 void* d,
		 int schema_id)
{
  Part p(pname);
  if(reftype==Part::Elem) {
    p.setPartElement((Element*)d,schema_id);
  }else {
    p.setPartType(*((int*)d),schema_id);
  }
  parts.push_back(p);
}

void
Part::setPartType(int typeId,int schema)
{
  discriminator=Part::Type;
  type_id=typeId;
  schema_id=schema;
}

void
Part::setPartElement(const Element* el,int schema)
{
  discriminator=Part::Elem;
  this->e=el;
  schema_id=schema;
}


int
Part::type()const
{
  if(discriminator==Part::Type)
    return type_id;
  else if(e!=0)
    return e->getType();
  else
    return 0;
}

const Element* 
Part::element()const
{
 if(discriminator==Part::Elem)
    return e;
 else
   return 0;
}
}
