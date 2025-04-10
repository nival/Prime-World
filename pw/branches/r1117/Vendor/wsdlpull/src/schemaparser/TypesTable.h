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
#ifndef _TYPESTABLEH
#define _TYPESTABLEH

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include "xmlpull/wsdlpull_export.h"
#include "xmlpull/XmlUtils.h"
#include "schemaparser/SimpleType.h"
#include "schemaparser/ComplexType.h"

namespace Schema {
//List of all XSD types
class WSDLPULL_EXPORT TypesTable
{
 public:

  TypesTable();
  ~TypesTable();

  //Realease all the memory
  void clean();

  //add a new type and returns its id
  int addType(XSDType * type);
  int addExtType(XSDType * type, int id);

  //get the type id of a type
  int getTypeId(const Qname & name, bool create = false);
  std::string getAtomicTypeName(Schema::Type t)const;

  //store an external reference to another schema
  int addExternalTypeId(const Qname & type, const XSDType * pType);
  int getNumExtRefs()    {
      return extRefs_.size();
  }
  
  Qname & getExtRefName(int index) {
      return extRefs_[index].qname;
  }

  int getExtRefType(int index){
   
    return extRefs_[index].localTypeId;
  }
  
  void resolveForwardElementRefs(const std::string & name, Element & e);
  void resolveForwardAttributeRefs(const std::string & name, Attribute & a);

  //get the path to the descendant element
  int getCompleteXpath(int elemId, std::string & childName, int *xPath,
                       int limits, int &offset);

  //returns the pointer to a type whose id is given
  XSDType *getTypePtr(int id) const;
  int getNumTypes(void) const
    {
      return numTypes;
    }
  bool detectUndefinedTypes(void);
  void setTargetNamespace(std::string Uri)
    {
      m_tnsUri = Uri;
    }
  std::string getTargetNamespace(void)
    {
      return m_tnsUri;
    }
  void printUndefinedTypes(std::ostream & out);

#ifdef LOGGING
  //for logging purposes
  void printTypes(std::ostream & out);
#endif 
 private:
  //contains a pointer to the actual type
  XSDType ** typesArray;

  //maintains a std::map of all user defined type names and their ids
  std::map < std::string, int >Id;

  //This is a std::map of all types defined in XML Schema
  std::map < std::string, int >basicTypes;
  int currentId;
  int numTypes, nSize;
  std::string m_tnsUri;
  
  typedef struct 
  {
    int localTypeId;
    Qname qname;
  }extRefs;
  std::vector<extRefs> extRefs_;
  void ensureCapacity();
};
}
#endif                                            /*  */
