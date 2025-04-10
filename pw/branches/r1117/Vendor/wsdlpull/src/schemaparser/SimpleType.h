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
#ifndef _SIMPLETYPEH
#define _SIMPLETYPEH
#include <list>
#include <map>
#include <vector>

#include "schemaparser/XSDType.h"
#include "xmlpull/wsdlpull_export.h"
#include "xmlpull/Qname.h"
#include "xmlpull/XmlUtils.h"
#include "schemaparser/SchemaParserException.h"

namespace Schema {
//union to store the values for various facets
typedef union
{
  int length;
  struct
  {
    int minlen, maxlen;
  } lenRange;
  int numEnums;
  int wsp;
  struct
  {
    int maxinc, mininc, maxex, minex;
  } valRange;
  int tot;
  int frac;
  const char *pattern;
} facetValueType;

class WSDLPULL_EXPORT SimpleType:public XSDType
{
 public:
  /** @name Constructors and Destructors */
  //@{
  /**
   * @param the namespace uri of the simple type
   */
  SimpleType(const std::string & ns);
  ~SimpleType();
  //@}
    
  /** @name Various Getter methods*/
  //@{
  /**
   * isList
   * @return :is this a list type
   */
  bool isList() const;
  /**
   * isUnion
   * @return :is this a union type
   */
  bool isUnion() const;
  /**
   * isSimple
   * return false
   */
  bool isSimple() const;

  //facet and restriction methods
  bool isvalidFacet(std::string facet);
  bool isValidInt(int val)const;
  bool isValidFloat(float val)const;
  bool isValidString(std::string val)const;
  bool getFacetValue(int facet, void* &val);
  const std::list<int>* unionTypes()const;

  //@}

  //@{ Various setter and utility methods
  void setUnionType(int id);
  void setListType(int id);
  void setFacetValue(std::string facet,std::string val);
  //@}
    
  //enum for facet Ids
  enum
    {
      NONE = 0,
      LENGTH = 0x1,
      MINLEN = 0x2,
      MAXLEN = 0x4,
      ENUM =0x8,
      WSP = 0x10,
      MAXINC = 0x20,
      MININC = 0x40,
      MAXEX =0x80,
      MINEX = 0x100,
      TOTALDIGITS = 0x200,
      FRAC = 0x400,
      PATTERN = 0x800
    };

  //whitespace values
  enum
    {
      PRESERVE = 1,
      REPLACE,
      COLLAPSE
    };
#ifdef LOGGING
  void print(std::ostream & out);
#endif
 private:
  std::vector<int> facetId_;
  std::map<std::string,int> facets_;
  std::list < std::string > enumValues_;
  int *validFacets_;
  facetValueType facetValue_;
  void error(std::string msg);
  bool isList_;
  bool isUnion_;
  std::list<int> * uTypes_;
};

inline
bool
SimpleType::isList() const
{
  return isList_;
}

inline
bool
SimpleType::isUnion() const
{
  return isUnion_;
}

inline
void
SimpleType::setListType(int typeId)
{
  isList_ = true;
  setBaseType(typeId);
}

inline
void
SimpleType::setUnionType(int typeId)
{
  isUnion_ = true;
  if(uTypes_ == 0){
    uTypes_ = new std::list<int>();
  }
  uTypes_->push_back(typeId);
}

inline
bool
SimpleType::isSimple() const
{
  return true;
}
inline
const std::list<int>*
SimpleType::unionTypes()const
{
  return uTypes_;
}
}
#endif                                            /*  */
