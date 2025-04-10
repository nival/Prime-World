/* 
 * wsdl2cpp - A C++ parser  for WSDL  (Web services description language)
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

/* 
 * Abstract interface for all xsd types
 */


#ifndef _XSDTYPEH
#define _XSDTYPEH

#include <string>
#include "xmlpull/Qname.h"
#include "xmlpull/wsdlpull_export.h"
#include "schemaparser/Schema.h"


namespace Schema {
class WSDLPULL_EXPORT XSDType
{
 public:

  /** @name Constructors and Destructors */
  //@{
  /**
   * @param the namespace uri of the type
   */
  XSDType(const std::string & ns);
  XSDType();
  virtual ~ XSDType(){};
  //@}


  /**
   * getName 
   * @return NCName of the type 
   */
  std::string getName() const ;
  /**
   * getNamespace
   * @return namespace this type belongs to 
   */
  
  std::string getNamespace() const ;
  /**
   * getQName 
   * @return QName (namespace qualified name)of the simple type 
   */
  Qname getQname() const;
  /**
   * getContentModel 
   * @return content model which is simple,complex or mixed or none
   */
  Schema::ContentModelType getContentModel() const ;    

  /**
   * getTypeId
   * @return the unique type id
   */
  int getTypeId() const ;
  /**
   * getBaseTypeId
   * @return the unique type id of this type's base type
   *          default is anyType
   */
  int getBaseTypeId()const;
  /**
   * getBaseDerivation
   * @return Extension or Derivation 
   */
  Schema::Derivation getBaseDerivation()const;
  /**
   * @name isAnonymous
   * @brief is this an anonymous type ,created inside an element or group
   * @return bool
   */
  bool isAnonymous() const ;
  /**
   * @name isSimple
   * @brief IS this a simple type or not
   * @return bool
   */
  virtual bool isSimple()const =0;
  
  //@{ Various setter methods 
  virtual void setName(std::string);
  virtual void setContentModel(Schema::ContentModelType );
  virtual void setTypeId(int);
  virtual void setAnonymous(bool);
  void setBaseType(int id , Schema::Derivation type = Schema::Restriction);
  void setBaseTypeNamespace(std::string ns);
  //@}
#ifdef LOGGING
  virtual void print (std::ostream & out) { };
#endif
 private:
  std::string nsUri_;
  std::string name_;
  int typeId_;
  int baseType_;
  Schema::Derivation baseDerivation_;
  Schema::ContentModelType contentModel_;//simple,complex,mixed?
  bool anonymous_;
};

inline
XSDType::XSDType(const std::string & ns)
  :nsUri_(ns),
     typeId_(0),
     baseType_(Schema::XSD_ANYTYPE),
     baseDerivation_(Schema::Extension),
     contentModel_(Schema::None),
     anonymous_(false)
{
}

inline
XSDType::XSDType()
  :nsUri_(Schema::SchemaUri),
     typeId_(0),
     baseType_(Schema::XSD_ANYTYPE),
     baseDerivation_(Schema::Extension),
     contentModel_(Schema::None),
     anonymous_(false)
{
}

inline
std::string 
XSDType::getName() const
{
  return name_;
}

inline
Qname 
XSDType::getQname() const
{
  Qname qn(name_);
  qn.setNamespace(nsUri_);
  return qn;
}

inline
Schema::ContentModelType
XSDType::getContentModel() const
{
  return contentModel_;
}

inline
int 
XSDType::getTypeId() const
{
  return typeId_;
}

inline
bool 
XSDType::isAnonymous() const
{
  return anonymous_;
}

inline
int
XSDType::getBaseTypeId()const
{
  return baseType_;
}

inline
Schema::Derivation 
XSDType::getBaseDerivation()const
{
  return baseDerivation_;
}

inline
void 
XSDType::setTypeId(int id)
{
  typeId_ = id;
}

inline
void
XSDType:: setBaseType(int id ,
		      Schema::Derivation type)
{
  baseType_=id;
  baseDerivation_=type;
}

inline
void 
XSDType::setAnonymous(bool flag)
{
  anonymous_ = flag;
}

inline
void 
XSDType::setName(std::string name)
{
  name_ = name;
}

inline
void 
XSDType::setContentModel(Schema::ContentModelType model)
{
    contentModel_ = model;
}

inline
std::string
XSDType::getNamespace() const
{
  return nsUri_;
}
}
#endif                                            /*  */
