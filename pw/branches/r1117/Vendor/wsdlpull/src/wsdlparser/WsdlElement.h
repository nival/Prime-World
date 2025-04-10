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
#ifndef _WSDLELEMENTH
#define  _WSDLELEMENTH

#include <string>
#include <vector>
#include "xmlpull/Qname.h"
#include "xmlpull/XmlUtils.h"
#include "schemaparser/Element.h"
#include "wsdlparser/WsdlException.h"
#include "xmlpull/wsdlpull_export.h"

using namespace Schema;

//Implementation of a Wsdl element
//This is the base class of all wsdl elements
namespace WsdlPull{
class WsdlParser;

class WSDLPULL_EXPORT WsdlElement
{
 public:
  
  WsdlElement(WsdlParser& w);
  virtual ~WsdlElement();
  /** @name Various Getter methods*/
  //@{

  /**
   * getName
   * @return name of the WsdlElement
   */
  std::string getName() const;

  /**
   * getDocumentation
   *   
   */
  const  std::string getDocumentation() const;

  /**
   *@name getExtensibilityElements/getExtensibilityAttributes
   *@brief return the extensibility elements/attributes belonging 
   *       to a given namespace
   *@params namspace uri
   *@params reference to a vector<int>
   * @return true if any extensibility elements were found
   */
  bool getExtensibilityElements(const std::string & namespc,
				std::vector<int>& ids);
  
  bool getExtensibilityAttributes(const std::string & namespc,
				  std::vector<int>& ids);
  
  //@}

  /** @name Various Setter methods*/
  //@{
  void setName(std::string nam);
  void addExtElement(int ident);
  void addExtAttribute(int ident);
  void setDocumentation(std::string* s);
  //@}

  virtual void print(std::ostream & out);
 protected:
  std::string name_;
  int id_;
  std::vector<int> extElems_;
  std::vector<int> extAttributes_;
  std::string * doc_;
 protected:
  WsdlParser & wParser_;
};

inline
WsdlElement::WsdlElement(WsdlParser & w)
  :wParser_(w)
{
  doc_=0;
  extElems_.clear();
  extAttributes_.clear();
}

inline
WsdlElement::~WsdlElement()
{
}

inline
std::string
WsdlElement::getName() const
{
  return name_;
}

inline
const  std::string 
WsdlElement::getDocumentation() const
{
  if (doc_)
    return *doc_;
  else
    return std::string ();
}

inline
void 
WsdlElement::setName(std::string nam)
{
  this->name_ = nam;
} 
inline
void
WsdlElement::setDocumentation(std::string* s)
{     
  doc_=s;
}

inline
void 
WsdlElement::addExtElement(int id)
{
  extElems_.push_back(id);
}

inline
void
WsdlElement::addExtAttribute(int id)
{
  extAttributes_.push_back(id);
}
}
#endif                                            /*  */
