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
#ifndef _MESSAGEH
#define  _MESSAGEH

#include <string>
#include <vector>
#include "xmlpull/Qname.h"
#include "xmlpull/wsdlpull_export.h"
#include "schemaparser/Element.h"
#include "wsdlparser/WsdlException.h"
#include "wsdlparser/WsdlElement.h"

namespace WsdlPull {
//Message part
class WSDLPULL_EXPORT Part{
 public:
  
    typedef enum 
    {
      None,
      Elem,
      Type
    }PartRefType;
    
  Part(const std::string& n);
  ~Part();
  PartRefType refType()const;
  std::string name()const;
  int type()const;
  const Element* element()const;
  int schemaId()const;
  void setPartType(int typeId,int schema);
  void setPartElement(const Element* e,int schema);
 private:
  std::string pname;
  PartRefType discriminator;
  union {
    int type_id;
    const Element * e;
  };
  int schema_id;
};

//Implementation of Wsdl message element
class WSDLPULL_EXPORT Message:public WsdlElement
{
 public:
  
  Message(WsdlParser& w);
  ~Message();
  /** @name Various Getter methods*/
  //@{

  /**
   * @name getNumParts
   * @return number of parts in the message
   */
  int getNumParts(void) const;
  /**
   * @name getPartIndex
   * @param the name of the part
   * @return index of the of the part whose name is passed
   *         index:0..nParts-1
   */
  int getPartIndex(std::string & nam) const ;
  /* @name getPartType
   * @param the index  of the part       index:0..nParts-1
   * @return type id  of the part
   *         for ex if we have <part name="one" type="xsd:int">
   *         the id returned represents xsd:int,the schema type for integers
   */
  int getPartType(int index) const;
  int getPartType(const std::string & nam) const;

  /* @name getPartElement
   * @param the index  of the part  index:0..nParts-1
   * @return pointer to the Element which the part uses
   *         for ex if we have <part name="one" element="ns:elem">
   *         a pointer to the Element representing ns:elem is returned
   *        I the part's reftype is Type ,0 is returned
   */
  const Element * getPartElement(int index)const;

  /* @name getMessagePart
   * @param the index  of the part,or the name
   * @return pointer to the Part
   */
  const Part* getMessagePart(size_t index)const;
  const Part* getMessagePart(const std::string & nam)const;

  /* @name getPartContentSchemaId
   * @param the index  of the part,or the name
   * @return schema id to which the part's type or element belongs to
   */
  int getPartContentSchemaId(int index) const;
  int getPartContentSchemaId(const std::string & nam) const;

  std::string getPartName(int index) const;
  Part::PartRefType getPartRefType(const std::string & nam) const;
  Part::PartRefType getPartRefType(int index) const;



  //@}

  /** @name Various Setter methods*/
  //@{
  void addPart(std::string pname, 
               Part::PartRefType reftype, 
               void* d,
               int schema_id);

  //@}

  //  void print(ostream & out);
 private:
  std::vector<Part> parts;
};

inline
Message::Message(WsdlParser & w)
  :WsdlElement(w)
{
  parts.clear();
}

inline
Message::~Message()
{
}


inline
int 
Message::getNumParts(void) const                   
{
  return parts.size();
}

inline
std::string
Message::getPartName(int index) const
{
  return parts[index].name();
}

inline
int
Message::getPartContentSchemaId(int index) const
{
  return parts[index].schemaId();
}

inline
int
Message::getPartType(int index) const
{
  return parts[index].type();
}

inline
const Element *
Message::getPartElement(int index)const
{
  return parts[index].element();
}

inline
Part::Part(const std::string& n)
  :pname(n),
     discriminator(Part::None),
     e(0)
{
}

inline
Part::~Part(){}

inline
Part::PartRefType
Part::refType()const
{
  return discriminator;
}
inline
std::string
Part::name()const
{
  return pname;
}

inline
int 
Part::schemaId()const
{
  return schema_id;
}
}
#endif                                            /*  */
