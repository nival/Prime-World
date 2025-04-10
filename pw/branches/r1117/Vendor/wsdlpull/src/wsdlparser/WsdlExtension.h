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

#ifndef _WSDLEXTENSIONH
#define _WSDLEXTENSIONH

#include "xmlpull/XmlPullParser.h"
#include "schemaparser/SchemaParser.h"
#include "xmlpull/wsdlpull_export.h"

using namespace Schema;

#if (defined _WIN32) && !(defined SCHEMADIR)
#define SCHEMADIR "src/schemas/"
#endif


namespace WsdlPull {

class WsdlParser;

//This class is the generic interface that all extensibility namespaces must derive from
class WSDLPULL_EXPORT WsdlExtension
{
 public:
  WsdlExtension(){};
  virtual ~WsdlExtension(){};
  virtual std::string getNamespace()const = 0;
  
  //returns the namespace Uri of the wsdl extensibility elements that it can handle.
  virtual void setNamespacePrefix(std::string) = 0;
  virtual std::string getNamespacePrefix()const = 0;

  //does this extensibility handler handle the given namespace
  virtual bool isNamespaceHandler(const std::string &)const = 0;
  virtual std::string getExtensibilitySchema()const = 0;
  virtual void setSchemaParser(SchemaParser * spe) = 0;
  virtual void setSchemaPath(const std::string & /* schemaPath */){};

  // parent is the Wsdl parent element type under which the extensibility element has come
  // the id returned must be non zero if the extensibility handler has handled the element correctly
  virtual int handleElement(int parent, XmlPullParser *) = 0;

  //attName is the extensibility attribute
  // the id returned must be non zero if the extensibility handler has handled the attribute correctly
  virtual int handleAttribute(int parent, std::string attName,
                              XmlPullParser *) = 0;

  //returns a valid extensibilty element
  //must return a non zero integer if the element was present in the wsdl
  virtual int getElementName(int id)const = 0;

  //returns a valid extensibility attribute
  //must return a non zero integer if the attribute was present in the wsdl
  virtual int getAttributeName(int id)const = 0;

  //this is the start of all ids that must be used for elems/attributes in this namespace
  virtual void setStartId(int) = 0;
  virtual int getStartId() const= 0;
  virtual void setWsdlParser(WsdlParser *){};
  virtual WsdlParser * wsdlParser()const { return 0;} ;

  //this method returns true if the Wsdl file had extensibility elements parsed by this extensibility handler
  virtual bool wasUsed()const = 0;
};
}
#endif                                            /*  */
