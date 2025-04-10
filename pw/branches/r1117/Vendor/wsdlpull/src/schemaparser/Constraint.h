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

#ifndef CONSTRAINT_H
#define CONSTRAINT_H
// *********************************************************************
// Include files:
// *********************************************************************
#include <string>
#include <list>
#include "xmlpull/wsdlpull_export.h"
#include "schemaparser/Schema.h"
#include "schemaparser/Annotation.h"               // Proposed upgrade

namespace Schema {
class WSDLPULL_EXPORT Constraint
{
public:
  Constraint(Schema::ConstraintType c);
  
  std::string getName()const;
  void setName(const std::string & n);
  virtual Schema::ConstraintType  getConstraintType();
  void setSelector(const std::string & xpath);
  void addField(const std::string &xpath);
  std::string selector()const;
  const std::list<std::string>& fields();
  virtual ~Constraint();
  void setAnnotation(const std::string & s);
    
private:
  Schema::ConstraintType m_constraints;
  std::string m_name,m_annotation;
  std::string m_selector;
  std::list<std::string> m_fields;
};

inline
Constraint::Constraint(Schema::ConstraintType c)
  :m_constraints(c)
{
  m_fields.clear();
}

inline
void
Constraint::setSelector(const std::string & xpath)
{
  m_selector=xpath;
}

inline
std::string
Constraint::selector()const
{
  return m_selector;
}

inline
const std::list<std::string>&
Constraint::fields()
{
  return m_fields;
}

inline
void
Constraint::addField(const std::string & xpath)
{
  m_fields.push_back(xpath);
}

inline
std::string 
Constraint::getName()const
{
  return m_name;
}

inline
void
Constraint::setName(const std::string &n)
{
  m_name=n;
}

inline
void
Constraint::setAnnotation(const std::string &s)
{
  m_annotation=s;
}

inline
Constraint::~Constraint()
{
}

inline
Schema::ConstraintType 
Constraint::getConstraintType()
{
  return Schema::NoConstraint;
}

}
#endif // GROUP_H
