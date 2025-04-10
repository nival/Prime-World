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

#include "schemaparser/SchemaParser.h"

#ifdef LOGGING
using namespace std;
namespace Schema {
void SchemaParser::print(ostream & out) 
{
  typesTable_.printTypes(out);
}


void TypesTable::printTypes(ostream & out)
{
  out << numTypes << endl;
  for (int i = 0; i < numTypes; i++)
    {
      typesArray[i]->print(out);
      out << XmlUtils::blk;
    }
}

void
ComplexType::print (ostream & out)
{
  out << getName() << XmlUtils::dbsp << getTypeId() << XmlUtils::dbsp << isSimple () << endl;
  out << getContentModel() << XmlUtils::dbsp;
  if (getContentModel() == Schema::Simple)
    out << simpleContentTypeId_;
  out << endl;

  out << attList_.size()<< endl;
  list < Attribute >::iterator pAttr = attList_.begin ();
  while (pAttr != attList_.end ()){
    out << *pAttr;
    pAttr++;
  }

  if(getContentModel() != Schema::Simple && cm_ ){

    out << cm_->getNumParticles()<< endl;
    ContentModel::ContentsIterator cit_b=cm_->begin();
    ContentModel::ContentsIterator cit_e=cm_->end();
    ContentModel::ContentsIterator ci=cit_b;
  
    for (ci=cit_b;ci!=cit_e;ci++){
      if(ci->second==ContentModel::Particle){
	out<<*(ci->first.e);
      }
    }
  }
}


ostream & operator << (ostream & stream, Attribute & a)
{
  stream << "@" << a.getName () << XmlUtils::dbsp << a.getType () << XmlUtils::dbsp << XmlUtils::dbsp;
  stream << a.isRequired () << XmlUtils::dbsp;

  if (!(a.defaultVal ()).empty ())
    {
      stream << 1 << XmlUtils::dbsp << a.defaultVal ();
    } else
      stream << 0 << XmlUtils::dbsp;
  if (!(a.fixedVal ()).empty ())
    {
      stream << 1 << XmlUtils::dbsp << a.fixedVal ();
    } else
      stream << 0 << XmlUtils::dbsp;
  stream << endl;

  return stream;

}


ostream & operator << (ostream & stream, Element & e)
{
  stream << e.getName () << XmlUtils::dbsp << e.getType () << XmlUtils::dbsp << XmlUtils::dbsp;
  stream << e.getMin () << XmlUtils::dbsp << e.getMax () << XmlUtils::dbsp;
  if (!(e.defaultVal ()).empty ())
    {
      stream << 1 << XmlUtils::dbsp << e.defaultVal ();
    } else
      stream << 0 << XmlUtils::dbsp;
  if (!(e.fixedVal ()).empty ())
    {
      stream << 1 << XmlUtils::dbsp << e.fixedVal ();
    } else
      stream << 0 << XmlUtils::dbsp;

  stream << endl;

  return stream;
}

void
SimpleType::print (ostream & out)
{

  out << getName() << XmlUtils::dbsp << getTypeId() << XmlUtils::dbsp << isSimple () << endl;
  out << getBaseTypeId() << endl;
  out << getBaseDerivation() << XmlUtils::dbsp;
  out << facetId_.size() << endl;
  for (size_t j = 0; j < facetId_.size(); j++)
    {
      out << facetId_[j] << XmlUtils::dbsp;
      if (facetId_[j] == ENUM)
        {
          out << facetValue_.numEnums << XmlUtils::dbsp;
          for (list < string >::iterator pEnums = enumValues_.begin ();
               pEnums != enumValues_.end (); pEnums++)
            out << *pEnums << XmlUtils::dbsp;
        }
      out << endl;
    }
  out << endl;
  //TODO need to o/p other facets
}
}
#endif
