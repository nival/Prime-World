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

//This class is a recursive storage container for any xml data type
//It stores the actual values occuring in an XML Schema Instance ,
//for a given type defined in the SchemaParser

#ifndef _TYPECONTAINERH
#define  _TYPECONTAINERH
#include <map>

#include "xmlpull/wsdlpull_export.h"
#include "xmlpull/XmlUtils.h"
#include "schemaparser/SchemaParser.h"


namespace Schema {
class TypeContainer;


typedef struct{
  std::vector<TypeContainer *>tc;
  int count;//Count maintains the last accessed container
  int num;//num is the number of occurrences of this child
} Containers;

class WSDLPULL_EXPORT TypeContainer
{
 public:
  TypeContainer(int  typeId,const SchemaParser * sp);
  TypeContainer(ContentModel* cm,const SchemaParser * sp,int typeId);
//type id is the complex type in which this content model is created

  ~TypeContainer();
  TypeContainer *getAttributeContainer(std::string attName, 
                                       bool create=false);
  TypeContainer *getBaseTypeContainer(bool create=false);

  TypeContainer *getChildContainer(std::string elemName, 
                                   bool create = false);

  TypeContainer * getChildContainer(ContentModel* cm,
                                    bool create=false);

  //If this is a container for simple type this method 
  //returns a void* to the type .The actual type  must be found using getTypeId()
  void *getValue();

  //Set position markers for this TypeContainer and all its' children to the start
  //TODO add an iterator interface to typecontainer
  void rewind();

  //This method searches the xml instance for an element whose name is specified
  //and is a simple type.If the return value is non null then type has the actual
  //type of the returned value which can be used for type casting
  void * getValue(const std::string & name,Schema::Type & type);

  const SchemaParser * schemaParser()const;
  bool isValueValid()const;
  //return the type which the container instanciates
  //The typeId is 0 if this is a container for an anonymous content model
  int getTypeId()const;
  //return the content model which the container instanciates
  //The content model is null if this is a container instanciates a schema defined type
  ContentModel* getContentModel()const;

  //Various set methods
  void setValue(const std::string & sValue,bool valid=true);
  void setValue(int iValue,bool valid=true);
  void setValue(char  cValue,bool valid=true);
  void setValue(long lValue,bool valid=true);
  void setValue(unsigned long  ulValue,bool valid=true);
  void setValue(float fValue,bool valid=true);
  void setValue(double dbValue,bool valid=true);
  void setValue(bool bValue,bool valid=true);
  void setValue(Qname & qnValue,bool valid=true);

  //if the container actually stores atomic data,return its type
  void setValAsString(const std::string &v);//set a value without validating
  void print(std::ostream & os); 
  friend  std::ostream &operator<<(std::ostream &os, TypeContainer &tc);
  static bool printTypeNames_;
  friend class SchemaValidator;
 private:
  //The unique id of the type for which this holds data
  Schema::Type typeId_; 
  ContentModel* cm_;
  std::map < std::string, Containers *> particleContainers_;//Type containers for particles
  std::map<ContentModel*,TypeContainer* >cmContainers_;//Type container for the content models
  std::map < std::string, TypeContainer *> attributeContainers_;//TypeContainers for attributes
  const SchemaParser *sParser_;
  TypeContainer * baseContainer_;

  union
  {
    std::string *sValue;
    int *iValue;
    unsigned int *uiValue;
    long *lValue;
    unsigned long *ulValue;
    short *shValue;
    unsigned short *usValue;
    float *fValue;
    double *dbValue;
    bool *bValue;
    char *cValue;

    //              Date *dValue;
    //              DateTime *dtValue;
    //              Time *tValue;
    Qname *qnValue;

    //      Uri *uriValue ;
  } Value;
  bool isValueValid_;//is the atomic date type valid
  std::string strVal;
  std::vector<TypeContainer*> tcTable;

  void deleteValue();
  void printComplexType (std::ostream & os);
  void printSimpleType (std::ostream & os);
  void printContentModel(std::ostream & os);

  //Set position markers for this TypeContainer to the start
  void rewindParticleContainers(std::map < std::string, Containers *> &particleContainers);
};

inline
void
TypeContainer::setValue(const std::string & sValue,bool valid)
{
  deleteValue();
  Value.sValue = new std::string(sValue);
  isValueValid_=valid;
}

inline
void
TypeContainer::setValue(int iValue,bool valid)
{
  deleteValue();
  Value.iValue = new int (iValue);
  isValueValid_=valid;
}

inline
void 
TypeContainer::setValue(char cValue,bool valid)
{
  deleteValue();
  Value.cValue = new char (cValue);
  isValueValid_=valid;
}

inline
void 
TypeContainer::setValue(long lValue,bool valid)
{
  deleteValue();
  Value.lValue = new long (lValue);
  isValueValid_=valid;
}

inline
void 
TypeContainer::setValue(unsigned long  ulValue,bool valid)
{
  deleteValue();
  Value.ulValue = new unsigned long (ulValue);
  isValueValid_=valid;
}

inline
void 
TypeContainer::setValue(float fValue,bool valid)
{
  deleteValue();
  Value.fValue = new float;
  *(Value.fValue) = fValue;
  isValueValid_=valid;
}

inline
void 
TypeContainer::setValue(double dbValue,bool valid)
{
  deleteValue();
  Value.dbValue = new double;
  *(Value.dbValue) = dbValue;
  isValueValid_=valid;
}

inline
void 
TypeContainer::setValue(bool bValue,bool valid)
{
  deleteValue();
  Value.bValue = new bool;
  *(Value.bValue) = bValue;
  isValueValid_=valid;
}

inline
void 
TypeContainer::setValue(Qname & qnValue,bool valid)
{
  deleteValue();
  Value.qnValue = new Qname(qnValue);
  isValueValid_=valid;
}

inline
int 
TypeContainer::getTypeId()const
{
  return typeId_;
}

inline 
ContentModel* 
TypeContainer::getContentModel()const
{
  return cm_;
}

inline
void
TypeContainer::setValAsString(const std::string&v)
{
  strVal=v;
}
/*
inline
void
TypeContainer::setValidity(bool b )
{
  isValueValid_ = b;
}
*/


inline
bool
TypeContainer::isValueValid()const
{
  return isValueValid_;
}
}
#endif                                            /*  */
