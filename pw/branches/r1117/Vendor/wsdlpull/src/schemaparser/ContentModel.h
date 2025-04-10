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

#ifndef _CONTENTMODELH
#define _CONTENTMODELH

#include <list>
#include <utility>
#include "xmlpull/wsdlpull_export.h"
#include "xmlpull/Qname.h"
#include "xmlpull/XmlUtils.h"
#include "schemaparser/Schema.h"
#include "schemaparser/SchemaParserException.h"

namespace Schema {

class Group;
class Element;

class WSDLPULL_EXPORT ContentModel
{
public:

  typedef union
  {
    Element* e;
    Group * g;
    ContentModel *c;
  }ContentType;

  typedef enum {
    Particle,
    ParticleGroup,
    Container
  } ContentDiscriminator;

  typedef std::pair<ContentType,ContentDiscriminator> ContentHolder;
  typedef std::list<ContentHolder> Contents;
  typedef std::list<ContentHolder>::iterator ContentsIterator;
  
  
  ContentModel(Schema::Compositor);
  ~ContentModel();
  Schema::Compositor getCompositor()const;
  ContentsIterator begin();
  ContentsIterator end();
  void addElement(const Element & e);
  void addGroup(const Group & e ,bool own=false);
  void addContentModel(const ContentModel* c);
  void setMin(const int & m);
  void setMax(const int & m);
  int getMin()const;
  int getMax()const;
  int getNumParticles()const;
  bool anyContents()const;
  void matchforwardRef(const std::string &name,Element &e);

private:
  Schema::Compositor m_compositor;
  Contents contents_;
  int minOccurs,maxOccurs;
  int nParticles;
  bool anyContent_;
};

inline
Schema::Compositor 
ContentModel::getCompositor()const
{
  return m_compositor;
}

inline 
ContentModel::ContentsIterator
ContentModel::begin()
{
  return contents_.begin();
}

inline
ContentModel::ContentsIterator
ContentModel::end()
{
  return contents_.end();
}


inline
int
ContentModel::getMin()const
{
  return minOccurs;
  
}

inline
int
ContentModel::getMax()const
{
  return maxOccurs;
  
}

inline
void
ContentModel::setMin(const int & m)
{
  minOccurs=m;
  
}

inline
void
ContentModel::setMax(const int & m)
{
  maxOccurs=m;
  
}

inline
int
ContentModel::getNumParticles()const
{
  return nParticles;
}

inline
bool
ContentModel::anyContents()const
{
  return anyContent_;
}
}
#endif                                            /*  */
