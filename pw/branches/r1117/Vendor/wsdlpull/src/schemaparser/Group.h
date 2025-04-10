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

#ifndef GROUP_H
#define GROUP_H
// *********************************************************************
// Include files:
// *********************************************************************
#include <string>
#include "xmlpull/wsdlpull_export.h"
#include "schemaparser/Schema.h"
#include "schemaparser/ContentModel.h"

namespace Schema {

class WSDLPULL_EXPORT Group
{
 public:
  Group();
  ~Group();
  Group(const Group & g);
  Group(const std::string & name,
        int minimum,
        int maximum);
  int getMin()const;
  void setMin(int m);
  
  int getMax() const;
  void setMax(int m);
  
  std::string getName()const;
  void setName(const std::string & n);

  void setAnnotation(const std::string & s);
  ContentModel * getContents()const;
  void setContents(const ContentModel* cm,bool isRef=false);
 private:
  int maxOccurs_;
  int minOccurs_;
  std::string name_;
  std::string annotation_;
  ContentModel * cm_;
  bool ref_;
};


inline
std::string 
Group::getName()const
{
  return name_;
}

inline
void
Group::setName(const std::string &n)
{
  name_=n;
}

inline
void
Group::setAnnotation(const std::string &s)
{
  annotation_=s;
}

inline
int 
Group::getMax() const
{
  return maxOccurs_;
}

inline
int 
Group::getMin() const
{
  return minOccurs_;
}

inline
void 
Group::setMin(int m) 
{
  minOccurs_=m;
  
}

inline
void 
Group::setMax(int m) 
{
  maxOccurs_=m;
  
}

inline
ContentModel * 
Group::getContents()const
{
  return cm_;
  
}

inline
void
Group::setContents(const ContentModel* cm,bool setRef)
{
  cm_=const_cast<ContentModel*> (cm);
  ref_=setRef;
}

}
#endif // GROUP_H
