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

/*
 * This class stores the list of parsed types 
 */
 
#include "schemaparser/TypesTable.h"

using namespace std;
namespace Schema {

TypesTable::TypesTable()
{
  currentId = Schema::XSD_ANYURI + 1;
  numTypes = 0;
  typesArray = new XSDType *[nSize = 10];

  //map of simple types
  basicTypes["string"] = Schema::XSD_STRING;
  basicTypes["integer"] = Schema::XSD_INTEGER;
  basicTypes["int"] = Schema::XSD_INT;
  basicTypes["byte"] = Schema::XSD_BYTE;
  basicTypes["positiveInteger"] = Schema::XSD_POSINT;
  basicTypes["unsignedInt"] = Schema::XSD_UINT;
  basicTypes["long"] = Schema::XSD_LONG;
  basicTypes["unsignedLong"] = Schema::XSD_ULONG;
  basicTypes["short"] = Schema::XSD_SHORT;
  basicTypes["unsignedShort"] = Schema::XSD_USHORT;
  basicTypes["decimal"] = Schema::XSD_DECIMAL;
  basicTypes["float"] = Schema::XSD_FLOAT;
  basicTypes["double"] = Schema::XSD_DOUBLE;
  basicTypes["boolean"] = Schema::XSD_BOOLEAN;
  basicTypes["time"] = Schema::XSD_TIME;
  basicTypes["dateTime"] = Schema::XSD_DATETIME;
  basicTypes["date"] = Schema::XSD_DATE;
  basicTypes["token"] = Schema::XSD_TOKEN;
  basicTypes["QName"] = Schema::XSD_QNAME;
  basicTypes["NCName"] = Schema::XSD_NCNAME;
  basicTypes["NMTOKEN"] = Schema::XSD_NMTOKEN;
  basicTypes["NMTOKENS"] = Schema::XSD_NMTOKENS;
  basicTypes["base64Binary"] = Schema::XSD_BASE64BIN;
  basicTypes["hexBinary"] = Schema::XSD_HEXBIN;
  basicTypes["anyType"] = Schema::XSD_ANYTYPE;
  basicTypes["any"] = Schema::XSD_ANY;
  basicTypes["anyURI"] = Schema::XSD_ANYURI;
}


TypesTable::~TypesTable()
{
  clean();
}


std::string
TypesTable::getAtomicTypeName(Schema::Type t)const
{
  
  for(
      std::map<std::string,int>::const_iterator it =
	basicTypes.begin();
      it != basicTypes.end();
      it++){

    if (it->second == t)
      return it->first;
  }
  return "";
}

void
TypesTable::clean()
{
  for (map < string, int >::iterator it = Id.begin(); it != Id.end();
       ++it)
    delete getTypePtr(it->second);
  numTypes = 0;
  if (typesArray)
    {
      delete[] typesArray;
      typesArray = 0;
    }
}


int TypesTable::addType(XSDType * type)
{
  Qname qn = type->getQname();
  string type_name(qn.getLocalName());
  int i = 0;

  //  string ns(qn.getNamespace());
  if (type_name.empty())
    {

      //create an anonymous type name
      ostringstream tmp_name_str;
      tmp_name_str << "type" << numTypes;
      type_name = tmp_name_str.str();
      type->setName(type_name);
      type->setAnonymous(true);                 //auto generated name
    }
  ensureCapacity();

  //  std::cout<<type_name<<" ";

  //add the typename and its id  to the map
  if ((i = Id[type_name]) != 0)
    {

      //this type was refernced earlier.
      typesArray[i - (Schema::XSD_ANYURI + 1)] = type;
      type->setTypeId(i);
      //  cout<<i<<endl;
      return i;
    }

  else
    {
      Id[type_name] = currentId;
      type->setTypeId(currentId);
      typesArray[numTypes] = type;
      currentId++;
      numTypes++;
      //      cout<<type->getName()<<" "<<currentId -1<<"  "<<numTypes<<" "<<this<<endl;
      return currentId - 1;
    }
}




//get the type id of a type
int TypesTable::getTypeId(const Qname & name, bool create)
{
  int typeId;
  if (name.getNamespace() == Schema::SchemaUri)
    {

      //This is one of the basic types
      typeId = basicTypes[name.getLocalName()];
      if(typeId==0) //if this is a basic type which is not mapped,treat as string
        typeId=Schema::XSD_STRING;
    }

  else if (name.getNamespace() == m_tnsUri )
    typeId = Id[name.getLocalName()];
  else if (name.getNamespace().empty()){

    typeId = basicTypes[name.getLocalName()];
    if(typeId==0) 
      typeId = Id[name.getLocalName()];
    if(typeId==0) 
      typeId = Schema::XSD_INVALID;
  }
  else
    return Schema::XSD_INVALID;                                 //the Type does not belong to this schema
  if (typeId == 0 && create)
    {

      //handle forward reference
      //create an id and return its value
      Id[name.getLocalName()] = currentId;
      ensureCapacity();
      typesArray[numTypes] = 0;
      currentId++;
      numTypes++;
      typeId = currentId - 1;
      //std::cout<<typeId<<" "<<name<<endl;

    }
  return typeId;
}

//for types present in an imported schema we cant use the type id
//since its specific to the imported schema
//we need to keep a local type id 
int 
TypesTable::addExternalTypeId(const Qname & type, const XSDType * pType)
{
  for (unsigned int i = 0; i < extRefs_.size(); i++)
    if (extRefs_[i].qname == type)
      return extRefs_[i].localTypeId;
  
  extRefs er;
  er.qname = (pType)?pType->getQname():type;
  er.localTypeId = currentId;
  extRefs_.push_back(er);
  ensureCapacity();
  typesArray[numTypes] = const_cast<XSDType*>(pType);
  numTypes++;
  return currentId++;

}

//adds a type into a type table for a given type id
//used for types present in imported schemas but referenced in current schema
int TypesTable::addExtType(XSDType * type, int localId)
{
  int index = localId - Schema::XSD_ANYURI - 1;
  if (index >= numTypes)
    return 0;
  typesArray[index] = type;
  return localId;
}

//increase the array storage if necessary
void TypesTable::ensureCapacity()
{
  if (numTypes >= nSize)
    {
      XSDType **tempArray = new XSDType *[numTypes + 5];
      for (int ind = 0; ind < nSize; ind++)
        tempArray[ind] = typesArray[ind];
      delete[] typesArray;
      typesArray = tempArray;
      nSize = numTypes + 5;
    }
}


#if 0

/*
  Takes a XSD type  and an accessor name to determine if the
  accessor is a descendant of the given type
  If found ,returns the schematype Id of the found element
  and populates an array of indices denoting the path
  from the parent to accessor .
  otherwise return 0(invalid type)

*/
int TypesTable::getCompleteXpath(int elemId, string & childName,
				 int *xPath, int limits, int &offset)
{
    int childId = 0, type = 0, i = 0, childIndex;
    bool found = false;
    if (xPath == 0 || limits == 0)
        return 0;
    XSDType *pType = getTypePtr(elemId);
    if (pType == 0)
        return 0;
    if (pType->isSimple())
        return 0;
    ComplexType *ct = (ComplexType *) pType;
    for (i = 0; i < ct->getNumChildren(); i++)
        if (ct->getChildName(i) == childName)
    {
        childId = ct->getChildType(i);
        childIndex = i;
    }
    if (childId == 0)
    {

/*
 childName is not a child of elemId,
 so call this method recursively
*/
        for (int i = 0; i < ct->getNumChildren() && !childId; i++)
        {
            if (childId =
                getCompleteXpath(ct->getChildType(i), childName, xPath + 1,
                limits - 1, ++offset))
                xPath[0] = i;

            else
                offset--;
        }
    }

    else
    {
        xPath[0] = childIndex;
        offset++;
    }
    return childId;
}
#endif


bool 
TypesTable::detectUndefinedTypes(void)
{
    for (int i = 0; i < numTypes; i++)
        if (typesArray[i] == 0)
            return true;
    return false;
}


void 
TypesTable::resolveForwardElementRefs(const string & name, Element & e)
{
    for (int i = 0; i < numTypes; i++)
        if (typesArray[i] != 0)
    {
        if (!typesArray[i]->isSimple())
        {
            ComplexType *ct = (ComplexType *) typesArray[i];
            ct->matchElementRef(name, e);
        }
    }
}


void
TypesTable::resolveForwardAttributeRefs(const string & name, Attribute & a)
{
    for (int i = 0; i < numTypes; i++)
        if (typesArray[i] != 0)
    {
        if (!typesArray[i]->isSimple())
        {
            ComplexType *ct = (ComplexType *) typesArray[i];
            ct->matchAttributeRef(name, a);
        }
    }
}


void 
TypesTable::printUndefinedTypes(ostream & out)
{
    for (map < string, int >::iterator it = Id.begin(); it != Id.end();
        ++it)
    {
        if (getTypePtr(it->second) == 0)
	  out << "Could not find {"<<m_tnsUri << "}:" << it->first << std::endl;
    }
}

XSDType *
TypesTable::getTypePtr(int id) const
{
  
  // this is a basic XSD type
  if (id < Schema::XSD_ANYURI + 1 || id > Schema::XSD_ANYURI + numTypes) {
 
    //    if (id > Schema::XSD_ANYURI + numTypes) 
      //      std::cout<<id<<" "<<this<<"  "<<numTypes<<std::endl;
    return 0;
  }
  return typesArray[id - (Schema::XSD_ANYURI + 1)];
}

}

