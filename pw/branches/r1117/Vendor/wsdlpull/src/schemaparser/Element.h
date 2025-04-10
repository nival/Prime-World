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
#ifndef _ELEMENTH
#define _ELEMENTH

#include <string>
#include "xmlpull/wsdlpull_export.h"
#include "schemaparser/Constraint.h"

namespace Schema {
#define UNBOUNDED INT_MAX
class WSDLPULL_EXPORT Element
{
 public:
  Element(const std::string & name, 
	  const std::string & elemNs,
	  const std::string & typeNs,
          int type_id, 
          int minimum = 1,
          int maximum = 1,
          bool qualified = false, 
          std::string def = "", 
          std::string fixed ="");
  
  Element(void);
  void setType(int id);
  std::string getName() const;
  void setTypeNamespace(const std::string & ns);
  std::string getTypeNamespace() const;
  void setNamespace(const std::string &ns);
  std::string getNamespace()const;
  int getType() const;
  int getMax() const ;
  int getMin() const;
  std::string & defaultVal();
  std::string & fixedVal();
  bool isQualified() const;
  Element& operator = (const Element & e);
  void setMin(int m);
  void setMax(int m);
  //add a key/keyref/unique constraint
  void addConstraint(Constraint* c);
  Constraint* constraint();
  const std::list<std::string> & getConstraints(); // Proposed modification: return a list of constraints, every constraint identified by its name.
  int nOccurrences;

 private:
  std::string elemName;
  std::string dval, fval;
  int elemType;
  bool bQualified;
  int minOccurs, maxOccurs;
  std::string elemNamespace;//namespace where the element is defined 
  std::string typeNamespace;//namespace where the type of this element is defined
 
  Constraint* cstr;
};

#ifdef LOGGING
std::ostream & operator << (std::ostream & stream, Element & e);
#endif

inline
Element::Element(const std::string & name, 
		 const std::string & elemNs,
		 const std::string & typeNs, 
		 int type_id, 
                 int minimum,
                 int maximum,
		 bool qualified, 
		 std::string def , 
		 std::string fixed)
  : nOccurrences(0),
  elemName(name),
  dval(def),
  fval(fixed),
  elemType(type_id),
  bQualified(qualified),
  minOccurs(minimum),
  maxOccurs(maximum),
  elemNamespace(elemNs),
  typeNamespace(typeNs),
  cstr(0)
 {
 }

inline
Element::Element(void)
   :nOccurrences(0),
    elemType(0),
    bQualified (false),
    minOccurs (1),
    maxOccurs (1),
     cstr(0)
{
}

inline
void
Element::setType(int id)
{
  elemType = id;
}

inline
std::string
Element::getName() const
{
  return elemName;
}

inline
void
Element::setTypeNamespace(const std::string& ns)
{
  typeNamespace = ns;
}

inline
std::string 
Element::getTypeNamespace() const
{
  return typeNamespace;
}


inline
int
Element::getType() const
{
  return elemType;
}

inline
int
Element::getMax() const
{
  return maxOccurs;
}
inline
int
Element::getMin() const
{
  return minOccurs;
}

inline
std::string &
Element::defaultVal()
{
  return dval;
}

inline
std::string &
Element::fixedVal()
{
  return fval;
}

inline
bool
Element::isQualified() const
{
  return bQualified;
}

inline
Element& 
Element::operator = (const Element & e)
{
  elemName = e.elemName;
  elemType = e.elemType;
  bQualified = e.isQualified();
  dval = e.dval;
  fval = e.fval;
  typeNamespace = e.typeNamespace;
  cstr = e.cstr;
  return *this;
  //minimum and maximum are not copied because they are specific to the
  //occurrence
}
inline
void
Element::setMin(int m)
{
  minOccurs=m;
}

inline
void 
Element::setMax(int m)
{
  maxOccurs=m;
}

inline
void
Element::addConstraint(Constraint* c)
{
  cstr=c;
}

inline
Constraint*
Element::constraint()
{
  return cstr;
}


inline
void
Element::setNamespace(const std::string& ns)
{
  elemNamespace = ns;
}

inline
std::string 
Element::getNamespace() const
{
  return elemNamespace;
}



}
#endif                                            /*  */
