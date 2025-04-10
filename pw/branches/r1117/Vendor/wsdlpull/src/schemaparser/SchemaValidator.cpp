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
#include <sstream>
#include "schemaparser/SchemaValidator.h"
using namespace std;

namespace Schema {
/*
  This class validates an incoming Xml instance against a given type
  whose schema has been processed by a given SchemaParser instance

*/
SchemaValidator::SchemaValidator(const SchemaParser * sp,
				 std::ostream& os)
  :ostr_(os),
   sParser_(sp)
{

  
}

SchemaValidator::~SchemaValidator()
{
}


/*
  Main entry method for validation
  Inputs
  1. XmlStream ,xpp.getName() muct return the name of the  type
  which must be validated
  2. typeId of the type against which this stream must be
  validated against
  3.An Input type container  (default  0)
*/
TypeContainer *
SchemaValidator::validate(XmlPullParser * xpp, 
			  int typeId,
			  TypeContainer * ipTc)
{
  TypeContainer *t=0;

  try{  
    string elemName = xpp->getName();
    const SchemaParser * s1Parser = sParser_;
    int typeId1= typeId;

    if (!ipTc)
      t = new TypeContainer(typeId, sParser_);
    else
      t = ipTc;



    if (t->getTypeId() != typeId)
      error("Fatal error ,container's type is not same as the validated type",xpp);

    // a schema definition inside an instance
    if (typeId == Schema::XSD_SCHEMA){
      
      SchemaParser * ssParser_ = new SchemaParser(xpp);
      if (!ssParser_->parseSchemaTag()){

	delete ssParser_;
	return 0;
      }
      delete ssParser_;
      return t;
    }

    //ignore ANY
    if (typeId == Schema::XSD_ANY){
      
      xpp->skipSubTree();
      return t;
    }

    // check if this type belongs to the current schema, if not we need to switch contexts
    if (!sParser_->isBasicType(typeId)){
      
      const XSDType * pType = sParser_->getType(typeId);
      
      if (sParser_->isImported(pType->getNamespace())) {
	
	sParser_ = sParser_->getImportedSchemaParser(pType->getNamespace());
	typeId = const_cast<SchemaParser*>(sParser_)->getTypeId(pType->getQname());
	
	t->sParser_ = sParser_;
	t->typeId_ = (Schema::Type)typeId;

      }
    }

    
    if (sParser_->getType(typeId) == 0
	|| sParser_->getType(typeId)->isSimple()) {

      //simple type validation
      string val;
      xpp->nextToken();
      if (xpp->getEventType() == XmlPullParser::TEXT ||
	  xpp->getEventType() == XmlPullParser::ENTITY_REF){

	val = xpp->getText();

	xpp->nextToken();
	while (xpp->getEventType() == XmlPullParser::ENTITY_REF ||
	       xpp->getEventType() == XmlPullParser::TEXT){

	  val += xpp->getText();
	  xpp->nextToken();
	    
	}
	validate(val, typeId, t,xpp);
      }
      else{
	//text was probably empty,nevertheless create  a type container 
	validate(val, typeId, t, xpp);
      }
      if (xpp->getEventType() == XmlPullParser::END_TAG)
	{
	  if (xpp->getName() != elemName)
	    error("Syntax error "+elemName,xpp);
	}
      else
	error("Expected a closing tag for " + elemName,xpp);
    }
    else {

      /*
	Perform Validation of Complex types
	Check for
	1.Is the tag name correct (this has to be right !!)
	2.Attributes ,if any should be valid
	3.Are there any mandatory (#required) attributes
	4. Validate its content model 
	6.Return the type container which has the
	correctly filled in values

      */
      const ComplexType *ct =
	static_cast<const ComplexType *>(sParser_->getType(typeId));
	
      const ComplexType * bt = 0;
      TypeContainer * btCnt = 0;
      if (ct->getBaseTypeId()!=Schema::XSD_ANYTYPE) {

	bt = static_cast<const ComplexType*>
	  (sParser_->getType(ct->getBaseTypeId()));
	btCnt = t->getBaseTypeContainer(true);
      }
	
      int attcnt = xpp->getAttributeCount();
	
      for (int i = 0; i < attcnt; i++) {
	  
	std::string attName = xpp->getAttributeName(i);
	std::string attVal = xpp->getAttributeValue("", attName);
	std::string attNsp = xpp->getAttributeNamespace(i);
	if (!attNsp.empty() && attNsp != sParser_->getNamespace())
	  continue;

	const Attribute*at = 0;
	TypeContainer *atCnt = 0;
	at = ct->getAttribute(attName);

	if (!at && bt){
	  at  = bt->getAttribute(attName);
	  if (at)
	    atCnt = btCnt->getAttributeContainer(attName, true);
	}
	else{
	  atCnt = t->getAttributeContainer(attName, true);
	}

	if (!at)
	  error("Unknown attribute \"" + attName +  "\"",xpp);

	validate(attVal, at->getType(), atCnt, xpp);
      }
	
      //see if some required attributes are missing
      checkAttributeOccurence(ct,xpp);
      if (bt)
	checkAttributeOccurence(bt,xpp);


      if (ct->getContentModel() == Schema::Simple)
	{
	  //complex types with a simple content model

	  string val;
	  xpp->nextToken();
	  if (xpp->getEventType() == xpp->TEXT){
	    val = xpp->getText();
	    validate(val, ct->getContentType(), t, xpp);
	    xpp->nextTag();
	  }
	  else{
	    //text was probably empty,nevertheless create  a type container 
	    validate(val, ct->getContentType(), t, xpp);
	  }

	  if (xpp->getEventType() == XmlPullParser::END_TAG)
	    {
	      if (xpp->getName() != elemName)
		error("Syntax error",xpp);
	    }
	  else
	    error("Expected a closing tag for " + elemName,xpp);
	}
      else if (ct->getContentModel() == Schema::Complex){
	//a complex type with complex content model
	ContentModel* cm=ct->getContents();
	ContentModel * bCm = 0;
	if (bt)
	  bCm = bt->getContents();
	if(cm)
	  validateContentModel(xpp,
			       cm,
			       t->getChildContainer(cm,true),
			       elemName,
                               false,
			       btCnt);
	else if (bCm)
	  validateContentModel(xpp,
			       bCm,
			       btCnt->getChildContainer(bCm,true),
                               elemName);
	else
	  xpp->nextTag();
      }
      else{
	// a complex type with mixed content model.no support yet
      }
    }
    typeId = typeId1;
    sParser_ = s1Parser;
    return t;
    
  }catch (SchemaParserException spe){
   
    if (!ipTc && t) delete t;
    
    if(xpp){
    
      spe.line=xpp->getLineNumber();
      spe.col=xpp->getColumnNumber();    
      throw spe;
    }
  }
  return 0;
}

TypeContainer*
SchemaValidator::validateContentModel(XmlPullParser * xpp, 
                                      ContentModel* cm,
                                      TypeContainer * ipTc,
                                      const string & elemName,
				      bool nested,
				      TypeContainer * btCnt)
{
  ContentModel::ContentsIterator cit_b=cm->begin();
  ContentModel::ContentsIterator cit_e=cm->end();
  ContentModel::ContentsIterator ci=cit_e;

  ContentModel::ContentsIterator bci;//base content model iterator
  ContentModel * bCm=0;

  
  for (ci=cit_b;ci!=cit_e;ci++){
    if(ci->second==ContentModel::Particle)
      ci->first.e->nOccurrences=0;
  }
  ci=cit_b;

  if (btCnt) {
    int t = btCnt->getTypeId();
    const ComplexType* ct = static_cast<const ComplexType*>(btCnt->schemaParser()->getType(t));
    bCm = ct->getContents();
    if (bCm)
      bci =bCm->begin();
  }

  switch (cm->getCompositor()) {
    
  case Schema::All:
    {
      do
	{
	  if (!nested)
	    xpp->nextTag();
	  if (xpp->getEventType() == XmlPullParser::END_TAG)
	    {
	      if (xpp->getName() == elemName)
		break;
	      while (xpp->getEventType() != XmlPullParser::START_TAG)
		xpp->nextTag();
	    }
	  //All cannot have another content model inside like group/choice etc
 
	  if(!findElement(cit_b,cit_e,xpp->getName(),ci))
	    error("Could not find element " +xpp->getName()+" in "+elemName,xpp);
	  ci->first.e->nOccurrences++;

	  validate(xpp, ci->first.e->getType(),
		   ipTc->getChildContainer(ci->first.e->getName(), true));
	  //ipTc->getChildContainer(xpp->getName(), true));
	}
      while (true);

      /*
	check for occurrence constraints
      */
      for (ci=cit_b;ci!=cit_e;ci++){
	if(ci->second==ContentModel::Particle && 
           (ci->first.e->nOccurrences<ci->first.e->getMin()||
            ci->first.e->nOccurrences>ci->first.e->getMax()))
	  error(ci->first.e->getName()+" did not meet occurrence constraints",xpp);
      }
	
      break;
    }
  case Schema::Sequence:
    {
      do
	{
	  if (!nested)
	    xpp->nextTag();
	    
	  if(xpp->getEventType() == XmlPullParser::END_TAG){

	    if (xpp->getName() == elemName)
	      break;
	    if(ci==cit_e)
	      break;

	    //position the xml parser to the next element
	    while ((xpp->getEventType() != XmlPullParser::START_TAG)&&
		   ((xpp->getEventType() != XmlPullParser::END_TAG)||
		    (xpp->getName() != elemName)))
	      xpp->nextTag();
	  }
	  //loop through all the contents inside
	  //the child elements in the content model must be in the same
	  //order as defined in the <sequence> tag of the schema

	  if(ci->second==ContentModel::Container){
            
	    if ((xpp->getEventType() == xpp->END_TAG)&&
		(xpp->getName() == elemName))
	      break;
	    //nested content model
	    validateContentModel(xpp,ci->first.c,
				 ipTc->getChildContainer(ci->first.c,true),
				 elemName,true,btCnt);
	    ci++;
	  }
	  else{

	   
	    if(cm->anyContents() || 
	       findElement(ci,cit_e,xpp->getName(), ci)){

	      ci->first.e->nOccurrences++;
	      validate(xpp,ci->first.e->getType(),
		       ipTc->getChildContainer(ci->first.e->getName(), true));
	      
	    }else if (bCm && (bCm->anyContents() ||
		      findElement(bCm->begin(),bCm->end(),xpp->getName(), bci))){

	      TypeContainer * t = btCnt->getChildContainer(bCm,true);
	      validate(xpp,bci->first.e->getType(),t->getChildContainer(bci->first.e->getName(),true));

	    } else {

	      error("Could not find element " +xpp->getName()+" in "+elemName,xpp);	      
	    }

	  }
	}
      while (true);

      /*
	check for occurrence constraints
      */
      for (ci=cit_b;ci!=cit_e;ci++){
	if(ci->second==ContentModel::Particle && 
           (ci->first.e->nOccurrences<ci->first.e->getMin()||
            ci->first.e->nOccurrences>ci->first.e->getMax()))
	  error(ci->first.e->getName()+" did not meet occurrence constraints",xpp);
      }
      break;
    }      
  case Schema::Choice:
    {

      if (!nested)
	xpp->nextTag();
	
	
      if(findElement(ci,cit_e,xpp->getName(), ci)) {
	
	std::string choiceElem = xpp->getName();
	do {
	//see if one of the choices is a particle and it occurs in the instance
	ci->first.e->nOccurrences++;
	validate(xpp, ci->first.e->getType(),
		 ipTc->getChildContainer(ci->first.e->getName(), true));
	xpp->nextTag();
	}while(xpp->getName() == choiceElem);
	xpp->prevTag();  
	break;
      } 
      else {
	//its a choice which has a content model
	ci++;
      }
      if (ci->second == ContentModel::Container){
        
	try {
	  validateContentModel(xpp,ci->first.c,
			       ipTc->getChildContainer(ci->first.c,true),
			       elemName,true,btCnt);
	}
	catch (SchemaParserException spe){

	  ci++;
	  //try the other content model
	  validateContentModel(xpp,ci->first.c,
			       ipTc->getChildContainer(ci->first.c,true),
			       elemName,true,btCnt);
	}
      }
      else{
        
	error("Could not find element " +xpp->getName()+" in "+elemName,xpp);
      }
         
      /*
       * Only one of the choices is allowed
       */
	
      /*
       * check for occurrence constraints
       */
      if(ci->second==ContentModel::Particle && 
         (ci->first.e->nOccurrences<ci->first.e->getMin()||
          ci->first.e->nOccurrences>ci->first.e->getMax()))
	error(ci->first.e->getName()+"did not meet occurrence constraints",xpp);
      
      break;
    }
  }
  /*
   * reset occurence ocunters
   */
  for (ci=cit_b;ci!=cit_e;ci++){
    
    if(ci->second==ContentModel::Particle)
      ci->first.e->nOccurrences=0;
  }
  return ipTc;
}
  


/*
 *  This method validates all supported simple types
 *  Both native atomic types and schema defined 
 */

TypeContainer * 
SchemaValidator::validate(void* value ,
                          int typeId,
                          TypeContainer * ipTc,
                          XmlPullParser * xpp)
{
  
  int basetype = sParser_->getBasicContentType(typeId);
  
  const XSDType * pType = sParser_->getType(typeId);
  if (pType && !pType->isSimple()){
    
    return 0;
  }
  const SimpleType  *st = static_cast<const SimpleType*>(pType);
  
  //check for the validity of the value
  //if available also check against restrictions in the schema

  if (!ipTc)
    ipTc = new TypeContainer(typeId, sParser_);

  if (st && (st->isList() || st->isUnion())){
	    
    std::string val = *((std::string*)value);
    ipTc->setValue(val,validateListOrUnion(st,val,xpp));
    return ipTc;
  }
  switch (basetype)
    {
    case Schema::XSD_INTEGER:
    case Schema::XSD_INT:
      {
	int x= *((int*)value);
	if (!st) {
	  ipTc->setValue(x);
	}
	else{

	  ipTc->setValue(x,st->isValidInt(x));
	}
	break;
      }
    case Schema::XSD_BYTE:
      {
	char c= *((char*)value);
	ipTc->setValue(c);
      }
      break;
    case Schema::XSD_FLOAT:
      {
	float f = *((float*)value);
	if (!st) {
	  
	  ipTc->setValue(f);
	  
	}else{
	  
	  ipTc->setValue(f,st->isValidFloat(f));
	}
	break;
      }
    case Schema::XSD_DOUBLE:
    case Schema::XSD_DECIMAL:
      {
	double db = *((double*)value);
	ipTc->setValue(db);
      }
      break;
    case Schema::XSD_LONG:
      {
	long l = *((long*)value);
	ipTc->setValue(l);
      }
      break;
    case Schema::XSD_POSINT:
    case Schema::XSD_ULONG:
      {
	unsigned long  ul= *((unsigned  long*)value);
	ipTc->setValue(ul);
      }
      break;
    case Schema::XSD_BOOLEAN:
      {
	bool b  = *((bool*)value);
	ipTc->setValue(b);
	break;
      }
    case Schema::XSD_QNAME:
      {
	Qname q  = *((Qname* )value);
	ipTc->setValue(q);
      }
      break;
    case Schema::XSD_STRING:
    default: 
      {
	std::string val = *((std::string* )value);
	if (!st) {
	  
	  ipTc->setValue(val);
	}
	else{
	  
	  ipTc->setValue(val,st->isValidString(val));
	}
      }
      break;
    }

  return  ipTc;
}

/*
 *  This method validates all supported simple types
 *  Both native atomic types and schema defined 
 */

TypeContainer *
SchemaValidator::validate(const string & val,
			  int typeId,
                          TypeContainer *ipTc,
                          XmlPullParser * xpp)
{

  int basetype = sParser_->getBasicContentType(typeId);
  if (basetype == Schema::XSD_INVALID) {
    
    return 0;
  }
  
  const XSDType * pType = sParser_->getType(typeId);
  if (pType && 
      !pType->isSimple() && 
      pType->getContentModel() != Schema::Simple){
    
    return 0;
  }

  if (pType && !pType->isSimple() && 
      pType->getContentModel() ==Schema::Simple) {
    //this is a complex type but has a simple content model
    
    const ComplexType * ct = static_cast<const ComplexType*>(pType);
    int contentType = ct->getContentType();
    return validate(val,contentType,ipTc,xpp);

  }
  const SimpleType  *st = static_cast<const SimpleType*>(pType);
  
  //check for the validity of the value
  //if available also check against restrictions in the schema

  if (!ipTc)
    ipTc = new TypeContainer(typeId, sParser_);
  ipTc->setValAsString(val);

  while(ipTc->isValueValid()){
    
    extractSimpleType(val, basetype, ipTc, st, xpp);

    
    if(!st || (st && (st->isList() || st->isUnion()))){
      
      break;
      //if we validated an atomic type we are done
      //if we just validated a list or union,there is no need 
      //to continue checking base types
    }

    if (!sParser_->isBasicType(st->getBaseTypeId())){
      
      st=static_cast<const SimpleType*>(sParser_->getType(st->getBaseTypeId()));
    }
    else{
      st = 0;
    }
  }
  return ipTc;
}


void 
SchemaValidator::extractSimpleType(const std::string & val,
				   int basetype,
				   TypeContainer * ipTc,
                                   const SimpleType * st,
                                   XmlPullParser * xpp)
{

  if (st && (st->isList() || st->isUnion())){
	    
    ipTc->setValue(val,validateListOrUnion(st,val,xpp));
    return;
  }
  
  istringstream istr(val);
  int x;
  double db;
  long l;
  char c;
  unsigned long  ul;
  float f;

  switch (basetype)
    {
    case Schema::XSD_INTEGER:
    case Schema::XSD_INT:
      {
	istr >> x;
	if (!st) {
	  ipTc->setValue(x,!istr.fail());
	}
	else{

	  ipTc->setValue(x,!istr.fail() && st->isValidInt(x));
	}
	break;
      }
    case Schema::XSD_BYTE:
      istr >> c;
      ipTc->setValue(c,!istr.fail());
      break;
    case Schema::XSD_FLOAT:
      {
	istr >> f;
	if (!st) {
	  ipTc->setValue(f,!istr.fail());
	}else{
	  ipTc->setValue(f,!istr.fail() && st->isValidFloat(f));
	}
	break;
      }
    case Schema::XSD_DOUBLE:
    case Schema::XSD_DECIMAL:
      istr >> db;
      ipTc->setValue(db,!istr.fail());
      break;
    case Schema::XSD_LONG:
      istr >> l;
      ipTc->setValue(l,!istr.fail());
      break;
    case Schema::XSD_POSINT:
    case Schema::XSD_ULONG:
      istr >> ul;
      ipTc->setValue(ul,!istr.fail());
      break;
    case Schema::XSD_BOOLEAN:
      {

	if(val=="true" ||
	   val=="yes" ||
	   val=="1")
	
	  ipTc->setValue(true);
	else
	  ipTc->setValue(false);
	break;
      }
    case Schema::XSD_QNAME:
      {
	Qname q(val);
	if (xpp)
	  q.setNamespace(xpp->getNamespace(q.getPrefix()));
	ipTc->setValue(q);
	break;
      }
    case Schema::XSD_STRING:
    default: 
      {
	if (!st) {
	    
	  ipTc->setValue(val);
	}
	else{
          if (basetype == Schema::XSD_STRING)
	    ipTc->setValue(val,st->isValidString(val));
	  else
	    ipTc->setValue(val);//other types such as date for which no validation is done
	}
      }
      break;
    }
}

/*
 * This function validates a string as a list or union 
 * for the simple type 
 */

bool
SchemaValidator::validateListOrUnion(const SimpleType* st,
                                     const std::string &val,
                                     XmlPullParser * xpp)
{
  if (st->isList()){
   
    size_t s = 0;

    while(s < val.length()){
      while(val[s]==' ')s++;
      std::string t = val.substr(s,val.find(' ',s)-s);
      TypeContainer * tc = validate(t,st->getBaseTypeId(),0,xpp);
      if (!(tc && tc->isValueValid()))
	return false;
      s+=t.length()+1;
    }
    return true ;
  
  }else if (st->isUnion()){
    
    std::list<int>::const_iterator it= st->unionTypes()->begin();
    while (it!=st->unionTypes()->end()){
      
      TypeContainer * tc = validate(val,*it,0,xpp);
      
      if (tc && tc->isValueValid())
	return true;
      it++;
    }
    return false;
  }
  else{
    return false;
  }
}
/*
 * This function searches for a child element in a complex type 
 * The iterator pElem is set to point to the found element
 * rewind controls whether a search is to be done by resetting pElem 
 * to the begining of the list 
 * Returns true if element is found else false 
 */

bool
SchemaValidator::findElement(ContentModel::ContentsIterator start, 
			     ContentModel::ContentsIterator end, 
			     std::string name,
			     ContentModel::ContentsIterator & found)
{
  for (ContentModel::ContentsIterator ci=start;
       ci!=end;
       ci++){
    
    if(ci->second==ContentModel::Particle){
#ifdef LOGGING
      std::cout<<"Looking for "<< name<<" found "<<ci->first.e->getName()<<std::endl;
#endif
      if(ci->first.e->getName()==name ||
	 ci->first.e->getName() == "*")//* is  a hack for soap arrays
        {
          found=ci;
          return true;
        }
    }
  }
  return false;
}

void SchemaValidator::error(const std::string& mesg,XmlPullParser* xpp)
{
    
  SchemaParserException spe(mesg + "\nError validating schema instance\n");
  if(xpp){
    
    spe.line=xpp->getLineNumber();
    spe.col=xpp->getColumnNumber();
  }
  throw spe;
}


bool
SchemaValidator::checkAttributeOccurence(const ComplexType* ct ,
					 XmlPullParser* xpp)
{

  if (ct->getNumAttributes() > 0)
    {
      for (int i = 0; i < ct->getNumAttributes(); i++)
	{
	  const Attribute*at = ct->getAttribute(i);
              
	  /*
	    Check for the correctness of each attribute
	  */
	  string attVal = xpp->getAttributeValue("", at->getName());
	  if (attVal.empty())
	    {
	      if (at->isRequired())
		error("Required attribute \"" + at->getName() +
		      "\" missing or empty",xpp);

	      else
		continue;
	    }
	}
    }
  return true;
}



bool
SchemaValidator::instance(const std::string& tag,
			  Schema::Type type_id)

{

  //generate an instance of the given type
  std::string nsp = sParser_->getNamespace();
  xmlStream_ = new XmlSerializer(ostr_); //xml serializer
  
  if (!nsp.empty()) 
    xmlStream_->setPrefix("s",nsp);
  
  xmlStream_->setPrefix("xsi",Schema::SchemaInstaceUri);
  xmlStream_->startDocument("UTF-8",false);

  return instance1(tag,type_id);
}

bool
SchemaValidator::instance1(const std::string &tag,
			   Schema::Type type_id)
{

  std::string nsp = sParser_->getNamespace();
  static bool first = false;
  xmlStream_->startTag(nsp,tag);
  if (!first){
    xmlStream_->attribute("",
			  "xmlns",
			  nsp);
    first = true;
  }


  //  xmlStream_->attribute(Schema::SchemaInstaceUri,
  //		"type",
  //		"s:"+sParser_->getTypeName(type_id));
  const XSDType * pType = sParser_->getType(type_id);

  if ( pType== 0 ||
       pType->isSimple()){

    xmlStream_->text(""); //simple content types
    
  }
  else {

    const ComplexType * ct =
      static_cast<const ComplexType*>(pType);
    
    //print attributes if any
    if (ct->getNumAttributes() > 0) {
      
      for (int i = 0; i < ct->getNumAttributes(); i++) {
	
	const Attribute*at = ct->getAttribute(i);
	xmlStream_->attribute(sParser_->getNamespace(),at->getName(),"");
      }
    }
  

    if (ct->getContentModel() == Schema::Simple) {
      
      xmlStream_->text("");
    }
    else{

      ContentModel* cm=ct->getContents();
      instanceCM(cm);
      
    }
  }
  xmlStream_->endTag(nsp,tag);
  return  true;
}




void
SchemaValidator::instanceCM(ContentModel *cm)
	
{
  
  ContentModel::ContentsIterator cit_b=cm->begin();
  ContentModel::ContentsIterator cit_e=cm->end();
  ContentModel::ContentsIterator ci=cit_b;

  switch (cm->getCompositor())
    {
    case Schema::All:
    case Schema::Sequence:
    case Schema::Choice:
      {
	// a simple logic to start with
	// not taking care of all,choice ,sequence as of now
	
	for (ci=cit_b;ci!=cit_e;ci++){
	  
	  if(ci->second==ContentModel::Particle &&
             ci->first.e->getMax() > 0){

	    const SchemaParser* s1Parser = sParser_;
	    Schema::Type t=(Schema::Type)ci->first.e->getType();
	    
	    if (!ci->first.e->getTypeNamespace().empty() &&
		sParser_->isImported(ci->first.e->getTypeNamespace()) &&
                sParser_->getNamespace() != ci->first.e->getTypeNamespace()) {
	
	      //here the type of the element is defined in another imported schemaparser
	      //so try to get the pointer.
	      t = (Schema::Type)sParser_->getType(t)->getTypeId();
	      sParser_ = sParser_->getImportedSchemaParser(ci->first.e->getTypeNamespace());
	    }
	   
	    instance1(ci->first.e->getName(),t);
	    sParser_ = s1Parser;
	  }
	  else if (ci->second==ContentModel::Container) {
	    
	    //nested xsd:sequence inside choice..nested content models
	    instanceCM(ci->first.c);
	      
	  }
	  else if (ci->second==ContentModel::ParticleGroup){
	    
	    //xsd:group inside 
	    instanceCM(ci->first.g->getContents());
				
	  }
	}
	break;
      }
    }
}

}
//TODO validation of <any>
//TODO validation of base64binary,hexBinary
//TODO validation of types derived by extension/restriction of complex types
