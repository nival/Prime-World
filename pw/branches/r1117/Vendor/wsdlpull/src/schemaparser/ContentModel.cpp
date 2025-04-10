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

#include "schemaparser/ContentModel.h"
#include "schemaparser/Element.h"
#include "schemaparser/Group.h"

namespace Schema {
void
ContentModel::addElement(const Element & elem)
{
  ContentType ct;

  if(m_compositor==Schema::All){
    if(elem.getMax()>1)
      {
        SchemaParserException spe("<all> MUST not have multiple occurrences of an element "+
                                  elem.getName());
        throw spe;
      }
    
  }
  ct.e=new Element(elem);  
  ContentHolder c(ct,ContentModel::Particle);
  contents_.push_back(c);
  if (elem.getType() == Schema::XSD_ANY) {
    
    anyContent_ = true;
  }
  nParticles++;
}

void
ContentModel::addGroup(const Group & g,bool  isRef)
{
  ContentType ct;
  if(m_compositor==Schema::All){

        SchemaParserException spe("<all> MUST  have only element ");
        throw spe;
  }
  ct.g=new Group(g);
  ct.g->setContents(g.getContents (),isRef);
  ContentHolder c(ct,ContentModel::ParticleGroup);
  contents_.push_back(c);
}

void
ContentModel::addContentModel(const ContentModel * container)
{
  if(m_compositor==Schema::All){
    SchemaParserException spe("<all> MUST have only elements within");
    throw spe;
  }
  
  ContentType ct;
  ct.c=const_cast<ContentModel*> (container);
  ContentHolder c(ct,ContentModel::Container);
  contents_.push_back(c);
}

ContentModel::ContentModel(Schema::Compositor c)
  :m_compositor(c),
   nParticles(0),
   anyContent_(false)
{
  contents_.clear();
  
}

  
ContentModel::~ContentModel()
{
  for(ContentsIterator ci=begin();ci!=end();ci++){

    if(ci->second==ContentModel::Container)
      delete (ci->first).c;
    else if(ci->second==ContentModel::Particle)
      delete  (ci->first).e;
    else if(ci->second==ContentModel::ParticleGroup)
      delete  (ci->first).g;
  }
}

void 
ContentModel::matchforwardRef(const std::string &name,Element &e)
{
  for(ContentsIterator ci=begin();ci!=end();ci++){
    if(ci->second==ContentModel::Particle)
      if((ci->first).e->getName()==name){
    	*((ci->first).e)=e;
      }
  }
}
}
