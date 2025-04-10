/* 
 * wsdlpull- A C++ parser  for WSDL  (Web services description language)
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

#include "schemaparser/TypeContainer.h"

namespace Schema {
bool TypeContainer::printTypeNames_ = true;

TypeContainer::TypeContainer(int id, 
                             const SchemaParser * sp)
  :typeId_((Schema::Type)id),
   cm_(0),
   sParser_(sp),
   baseContainer_(0),
   isValueValid_(true)
{
  /**
   * This is a union so setting one pointer
   *  will set all to 0 
   */
    
  Value.sValue=0;
  
}

TypeContainer::TypeContainer(ContentModel* cm,
                             const SchemaParser * sp,
			     int typeId)
  :typeId_((Schema::Type)typeId), //the type of the complex type which uses this content model
   cm_(cm),
   sParser_(sp),
   baseContainer_(0),
   isValueValid_(false)
{
  /**
   * This is a union so setting one pointer
   *  will set all to 0 
   */
    
  Value.sValue=0;
  
}

TypeContainer::~TypeContainer()
{
  if (baseContainer_)
    delete baseContainer_;

  /*
    delete all particle containers
  */
  for (std::map < std::string, Containers *>::iterator i = particleContainers_.begin();
       particleContainers_.end() != i; ++i){
    
    delete i->second;
  }
  
  if(tcTable.size()>0) {
    
    /* 
       delete all sub type containers
    */
    for (size_t i = 0; i < tcTable.size(); i++)
      delete tcTable[i];
  
  }
  else {
    /* 
       delete the values if it is an atomic type container
    */
    deleteValue();
  }
}

TypeContainer*
TypeContainer::getAttributeContainer(std::string elemName,
                                     bool create)
{
  TypeContainer *container = 0;
  if ((container = attributeContainers_[elemName]) != 0)
    return container;
  if (!create)
    return container;

  /*
    Create and return a Type Container
  */
  const XSDType *pType = sParser_->getType(typeId_);
  if (pType != 0 && !pType->isSimple())
    {
      ComplexType *cType = (ComplexType *) pType;
      for (int i = 0; i < cType->getNumAttributes(); i++)
        {
          if (cType->getAttributeName(i) == elemName)
            {
              container =
                new TypeContainer(cType->getAttributeType(i), sParser_);
              tcTable.push_back(container);
              break;
            }
        }
    }
  attributeContainers_[elemName] = container;
  return container;
}


TypeContainer *
TypeContainer::getChildContainer(std::string elemName,
                                 bool create)
{
  Containers *cs = 0;
  TypeContainer *tC = 0;
  if(!create)
    {
      /*
        Each time this method is called the next occurence  of
        the child container is returned .Once all the occurrences
        of the child container have been accessed ,return 0
      */
      
      if((cs = particleContainers_[elemName]) != 0)
        {
	  
          if (cs->count >= cs->num)
            {
              cs->count = 0;
              return 0;
            }
          else
            return cs->tc[cs->count++];
        }
      else {
	//recurse child containers
	std::vector<TypeContainer*>::iterator iTc=tcTable.begin();
        while(iTc != tcTable.end()) {

	  tC = (*iTc)->getChildContainer(elemName);
	  if(tC)
	    return tC;
	  iTc++;
	}
	return 0;
      }
    }
  else
    {
      /*
        Create and return a Type Container
	Sometimes elements have multiple occurrences 
	in that case incrememnt Containers::num
      */
      cs = particleContainers_[elemName];
      if (!cs)
        {
          cs = new Containers;
          cs->count = cs->num = 0;
          particleContainers_[elemName] = cs;
        }

          
      ContentModel::ContentsIterator cit_b=cm_->begin();
      ContentModel::ContentsIterator cit_e=cm_->end();
      ContentModel::ContentsIterator ci=cit_b;
      
      for (ci=cit_b;ci!=cit_e;ci++){
        if(ci->second==ContentModel::Particle){
          if(ci->first.e->getName()==elemName){
	    
            tC = new TypeContainer (ci->first.e->getType(),
                                    sParser_);
	    tcTable.push_back(tC);
            break;
          }
        }
      }
      cs->tc.push_back(tC);
      cs->num++;
      return tC;
    }
}

TypeContainer *
TypeContainer::getBaseTypeContainer(bool create)
{
  if (! baseContainer_ && create){

    const XSDType * t = sParser_->getType(typeId_);
    if (t->getBaseTypeId() == Schema::XSD_ANYTYPE)
      return 0;
    baseContainer_ = new TypeContainer(t->getBaseTypeId(),sParser_);
  }
  return baseContainer_;
}

TypeContainer *
TypeContainer::getChildContainer(ContentModel* cm ,
                                 bool create)
{

  TypeContainer *tC = 0;
  if(!create)
    {
      tC = cmContainers_[cm];
      if(tC)
	return tC;
      
	//recurse child containers
      std::vector<TypeContainer*>::iterator iTc=tcTable.begin();
      while(iTc!=tcTable.end()) {
	
	tC = (*iTc)->getChildContainer(cm);
	if(tC)
	  return tC;
	iTc++;
      }
      return 0;
    }
  else
    {
      /*
        Create and return a Type Container
      */
      tC= cmContainers_[cm];
      if (!tC)
        {
          tC= new TypeContainer(cm,sParser_,typeId_);
          cmContainers_[cm]=tC;
	  tcTable.push_back(tC);
        }
      return tC;
    }
}


void *
TypeContainer::getValue()
{
  if(!Value.sValue)
    return 0; 
  
  int id = sParser_->getBasicContentType(typeId_);
  if(id==0)
    return 0;

  switch (id)
    {

    case Schema::XSD_INT:
    case Schema::XSD_INTEGER:
      return (void *) Value.iValue;
    case Schema::XSD_LONG:
      return (void *) Value.lValue;
    case Schema::XSD_POSINT:
    case Schema::XSD_ULONG:
      return (void *) Value.ulValue;
    case Schema::XSD_FLOAT:
      return (void *) Value.fValue;
    case Schema::XSD_DOUBLE:
    case Schema::XSD_DECIMAL:
      return (void *) Value.dbValue;
    case Schema::XSD_BOOLEAN:
      return (void *) Value.bValue;
    case Schema::XSD_QNAME:
      return (void *) Value.qnValue;
    default:
      return (void *) Value.sValue;

    }
}

const SchemaParser *
TypeContainer::schemaParser() const
{
      return sParser_;
};

void
TypeContainer::deleteValue()
{
  if(!Value.sValue)
    return;

  int id = sParser_->getBasicContentType(typeId_);
  if(id==0 || id == Schema::XSD_INVALID)
    return ;

  switch (id)
    {

    case Schema::XSD_INT:
    case Schema::XSD_INTEGER:
      delete  Value.iValue;
      break;
    case Schema::XSD_LONG:
       delete Value.lValue;
      break;
    case Schema::XSD_POSINT:
    case Schema::XSD_ULONG:
       delete Value.ulValue;
      break;
    case Schema::XSD_FLOAT:
       delete Value.fValue;
       break;
    case Schema::XSD_DOUBLE:
    case Schema::XSD_DECIMAL:
       delete Value.dbValue;
       break;
    case Schema::XSD_BOOLEAN:
       delete Value.bValue;
       break;
    case Schema::XSD_QNAME:
       delete Value.qnValue;
       break;
    default:
      delete Value.sValue;
      break;
    }
}

void
TypeContainer::print(std::ostream &os)
{
  if (typeId_ == Schema::XSD_SCHEMA ||
      typeId_ == Schema::XSD_ANY)
    return ;
  
  if (baseContainer_)
    baseContainer_->print(os);

  if(cm_){
    printContentModel(os);
  }
  else if (typeId_ != Schema::XSD_INVALID){
    
    if (sParser_->getBasicContentType(typeId_) == Schema::XSD_INVALID ){

      printComplexType(os);
    }
    else {

      printSimpleType(os);
    }
  }
}

std::ostream &operator<<(std::ostream &os, TypeContainer &tc)
{
  tc.print(os);
  return os;
}



void
TypeContainer::printSimpleType(std::ostream & os)
{
  if (!strVal.empty())
    os<<strVal;
  else{
    
    int type = sParser_->getBasicContentType(typeId_);
    switch(type){
    case Schema::XSD_INT:
    case Schema::XSD_INTEGER:
      os << *((int *) (getValue ()));
      break;
    case Schema::XSD_LONG:
      os << *((long *) (getValue ()));
      break;
    case Schema::XSD_POSINT:
    case Schema::XSD_ULONG:
      os << *((unsigned long *) (getValue ()));
      break;
    case Schema::XSD_FLOAT:
      os << *((float *) (getValue ()));
      break;
    case Schema::XSD_DOUBLE:
    case Schema::XSD_DECIMAL:
      os << *((double *) (getValue ()));
      break;
    case Schema::XSD_BOOLEAN:
      os << *((bool *) (getValue ()));
      break;
    case Schema::XSD_QNAME:
      {
#ifdef _WIN32 
	Qname qn=*((Qname *) (getValue ()));
	os<<qn.getPrefix()<<"{"<<qn.getNamespace()<<"}:"<<qn.getLocalName();
#else
	os << *((Qname *) (getValue ()));
#endif
      }
      break;
    default:
      os << *((std::string *) (getValue ()));
      break;
    }

  }
  if(!isValueValid_)
    os<<" -->Invalid value for data type";
}


void 
TypeContainer::printComplexType (std::ostream & os)
{
  const ComplexType * ct =static_cast<const ComplexType*>(sParser_->getType(typeId_));
  TypeContainer * tmp= 0;
  for (int i = 0; i < ct->getNumAttributes (); i++) {
    
    tmp =getAttributeContainer (ct->getAttributeName (i));
    
    if(tmp){
      
      os << "@" << ct->getAttributeName (i) << ":";
      os<<*tmp<<std::endl;
    }
  }
  
  if(ct->getContentModel()==Schema::Simple){
    printSimpleType(os);
  }
  else{

    ContentModel* cm=ct->getContents();
    TypeContainer* tmp=getChildContainer(cm);
    if(tmp)
      os<<*tmp;
  }
  os<<std::endl;
}

void
TypeContainer::printContentModel(std::ostream & os)
{
  ContentModel* cm=cm_;
  ContentModel::ContentsIterator cit_b=cm->begin();
  ContentModel::ContentsIterator cit_e=cm->end();
  ContentModel::ContentsIterator ci=cit_e;
  for (ci=cit_b;ci!=cit_e;ci++){
    TypeContainer* tmp=0 ;
    if(ci->second==ContentModel::Particle) {
	
      do{
	tmp=getChildContainer (ci->first.e->getName());
	if (tmp == 0)
	  continue;
	//if more than one occurences of the element are found then
	//the same call will return the successive instances of the element
	if( ci->first.e->getName() !="*" && 
	    TypeContainer::printTypeNames_)
	  os << ci->first.e->getName() << ":";
	
        if( sParser_->getBasicContentType(ci->first.e->getType()) == Schema::XSD_INVALID &&
	    TypeContainer::printTypeNames_) 
	  os<<std::endl; //if its a complex type ..print the contents in a new line
	
	os<<*tmp<<std::endl;
	
      }while (tmp != 0);
    }else{
      tmp=getChildContainer (ci->first.c);
      if(tmp==0)
	continue;
      os<<*tmp<<std::endl;
    }
  }
}


void
TypeContainer::rewindParticleContainers(std::map < std::string, Containers *> &particleContainers) 
{
  Containers *cs;
  std::map < std::string, Containers *>::iterator it = particleContainers_.begin();
  std::map < std::string, Containers *>::iterator end = particleContainers_.end();
  for ( ; it != end; ++it) {
    cs = it->second;
    if(cs)
      cs->count = 0;
  }
}

///resets the access counters so that all access starts from first child
void
TypeContainer::rewind()
{
  
  //must be rewound here make sure that we we get all childs
  rewindParticleContainers(particleContainers_);

  if (sParser_->isBasicType(sParser_->getBasicContentType(typeId_))) {
    //do nothing more than set count of particleContainers_ below
  } else if (cm_) {
    ContentModel::ContentsIterator ci = cm_->begin();
    ContentModel::ContentsIterator cit_e = cm_->end();
    for ( ; ci != cit_e; ci++) {
      TypeContainer* tmp = 0;
      if (ci->second == ContentModel::Particle) {
	while ((tmp = getChildContainer(ci->first.e->getName()))) {
	  tmp->rewind();
	}
      } else {
	tmp = getChildContainer (ci->first.c);
	if (tmp) {
	  tmp->rewind();
	}
      }
    }
  } else {
    const ComplexType * ct =static_cast<const ComplexType*>(sParser_->getType(typeId_));
    ContentModel* cm=ct->getContents();
    TypeContainer * tmp;
    if (cm && (tmp = getChildContainer(cm)) != 0) {
      tmp->rewind();
    }
  }

  //must be rewound here again to make sure that our position markers are reset
  //because getChildContainer increments them
  rewindParticleContainers(particleContainers_);
}


/*This is a  helper method to get an element instance whose name is 'name'
and is a simple type.The method is recursive and searches the entire xml instance
for example,if the instance is
  <address> 
      <city>El Dorado</city>
      <street>elm</street>
      <name>
        <firstname>John</firstname>
		<firstname>Jack</firstname>
        <lastname>Doe</lastname>
      </name>
 </address>
 calling getValue("lastname",t) will return a void* to the string "Doe" 
 Note that if you want to call this method repeatedly you need to 
 rewind the typecontainer.
 Also getValue() returns only the first instance of the occurrence of 
 "name".So in the above example "John" is returned always.
 If you want all instances you the complete API of TypeContainer.
*/

void * 
TypeContainer::getValue(const std::string & name,Schema::Type & type)
{

  if(sParser_->isBasicType(sParser_->getBasicContentType(typeId_))
     && Value.sValue){
    
    //simple type
    
    type = typeId_;
    return (void*)Value.sValue;
  }
  else if (cm_){
    
    void * val = 0 ;
    ContentModel::ContentsIterator cit_b=cm_->begin();
    ContentModel::ContentsIterator cit_e=cm_->end();
    ContentModel::ContentsIterator ci=cit_e;
    for (ci=cit_b;ci!=cit_e;ci++){
      TypeContainer* tmp=0 ;
      if(ci->second==ContentModel::Particle) {

	tmp=getChildContainer (ci->first.e->getName());
        //cout<<ci->first.e->getName()<<std::endl;
	if (tmp == 0)
      continue;
	if (sParser_->isBasicType(sParser_->getBasicContentType(ci->first.e->getType()))){
	  
	  if(ci->first.e->getName() == name){
	     
	    return tmp->getValue(name,type);
	  }
	  else{
	    
	    tmp =0;
	  }
	}

      }
      else{

	tmp=getChildContainer (ci->first.c);
      }
      if (tmp == 0)
	continue;
      val = tmp->getValue(name,type);
      if (val)
	return val;
	  
    }
    return 0;
  }
  else{
    //complex type
    const ComplexType * ct =static_cast<const ComplexType*>(sParser_->getType(typeId_));
    TypeContainer * tmp= getAttributeContainer (name);
    if (tmp){
      return tmp->getValue(name,type);
    }
    
    ContentModel* cm=ct->getContents();
    if (cm && (tmp=getChildContainer(cm))!=0){
      
      return tmp->getValue(name,type);
    }
  }
  return 0;
}

}
