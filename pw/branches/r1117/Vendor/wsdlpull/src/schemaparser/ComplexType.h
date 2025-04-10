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
 */

#ifndef _COMPLEXTYPEH
#define _COMPLEXTYPEH

#include <list>
#include "xmlpull/wsdlpull_export.h"
#include "xmlpull/Qname.h"
#include "xmlpull/XmlUtils.h"
#include "schemaparser/XSDType.h"
#include "schemaparser/ContentModel.h"
#include "schemaparser/Attribute.h"
#include "schemaparser/SchemaParserException.h"

namespace Schema {

class WSDLPULL_EXPORT ComplexType:public XSDType
{
 public:
       
  ComplexType(const std::string& );
  ~ComplexType();

  /*
   * Various getter methods
   */

  //virtual function ,always return false for complex types
  bool isSimple() const;

  //returns the content type for complex types whose content model is SIMPLE
  int getContentType() const;

  //returns the number of attributes ,indices start from 0 to n-1
  int getNumAttributes() const;
  
  //gets the id of the attribute at the position "index"
  int getAttributeType(int index);
  
  //gets the NCName of the attribute
  std::string getAttributeName(int index)const;
  
  //returns the content model structure
  ContentModel*  getContents()const;
  
  //returns a pointer to the attribute
  const Attribute *getAttribute(const std::string & name)const;

  const Attribute *getAttribute(int index)const;
  //returns the list of  attributes
  std::list < Attribute > & pAttributeList() ;
  
  /*
   * Various setter methods
   */

  void setSimpleContentType(int id);

  void setContents(ContentModel* ct);
  
  void addAttribute(const Attribute &a,
                    bool fwdRef=false);
   //forward reference to attributeGroup
   void addAttributeGroupName(const Qname & qn);

  void matchAttributeRef(const std::string & name, Attribute & a);
  void matchElementRef(const std::string & name, Element & e);
  bool checkOccurrences(void);
  void resetCounters(void);


#ifdef LOGGING
  void print(std::ostream & out);
#endif

 private:
  std::list < Attribute > attList_;
  int simpleContentTypeId_;                            //for simple content
  ContentModel* cm_;
  void error(std::string msg) const;
  bool fwdElemRef_, fwdAttrRef_;
};


inline
int 
ComplexType::getContentType() const
{
  return simpleContentTypeId_;
}

inline
bool 
ComplexType::isSimple() const
{
  return false;
}

inline
int 
ComplexType::getNumAttributes() const
{
  return attList_.size();
}

inline
int
ComplexType::getAttributeType(int index)
{
  return getAttribute(index)->getType();
}

inline
std::string 
ComplexType::getAttributeName(int index)const
{
  return getAttribute(index)->getName();
}

inline
std::list < Attribute > & 
ComplexType::pAttributeList() 
{
  return attList_;
}


inline
void 
ComplexType::setSimpleContentType(int id)
{
  simpleContentTypeId_ = id;
}


inline
ContentModel*  
ComplexType::getContents()const
{
  return cm_;
  
}

inline
void 
ComplexType::setContents(ContentModel* ct)
{
  cm_=ct;
}


inline
ComplexType::~ComplexType()
{
  if(cm_)
    delete cm_;
}
}
#endif                                            /*  */
