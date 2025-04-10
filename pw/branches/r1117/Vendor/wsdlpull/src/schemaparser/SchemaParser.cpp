/* 
 * wsdlpull - A C++ parser  for WSDL  (Web services description language)
 * Copyright (C) 2005-2007 Vivek Krishna
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
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

#include "schemaparser/SchemaParser.h"

#ifndef _WIN32
#include "xmlpull/ConfigFile.h"
#endif

//
#include <climits>

namespace Schema {
using namespace std;
SchemaParser::SchemaParser(XmlPullParser * parser, 
                           std::string tns,
                           std::ostream & log,
			   const std::string & s)
  :tnsUri_(tns), 
   xParser_(parser),
   elementQualified_ (false),
   attributeQualified_ (false),
   deleteXmlParser_(false),
   resolveFwdRefs_(true),
   level_(1),
   logFile_(log),
   confPath_(s)
{
  init();
}

SchemaParser::SchemaParser(const std::string &Uri, 
                           std::string tns , 
                           std::ostream & log ,
			   const std::string & s)
  :tnsUri_(tns),
   xParser_(0),
   elementQualified_ (false),
   attributeQualified_ (false),
   deleteXmlParser_(false),
   resolveFwdRefs_(true),
   level_(1),
   logFile_(log),
   confPath_(s)
{
    if(XmlUtils::fetchUri(Uri,fname_))
    {
      xmlStream_.open(fname_.c_str());
      xParser_ = new XmlPullParser(xmlStream_);
      xParser_->setFeature(FEATURE_PROCESS_NAMESPACES, true);
      xParser_->require(XmlPullParser::START_DOCUMENT, "", "");
      while (!xmlStream_.fail() && xParser_->getEventType() != xParser_->END_DOCUMENT)
        { 
          xParser_->nextTag();
          if (xParser_->getEventType() == xParser_->START_TAG &&
              xParser_->getName() == "schema")
            {
              deleteXmlParser_=true;
              tnsUri_=tns;
              break; 
            }
        }

    }
  if(!deleteXmlParser_) //something wron while opening the schema file
    {
      delete xParser_;
      xParser_=0;
    }
      
  init();
  uri_ = Uri.substr(0,Uri.rfind('/') + 1);
}

void
SchemaParser::init()
{
  lElems_.clear()   ;
  lAttributes_.clear();
  lAttributeGroups_.clear();
  importedSchemas_.clear();
  constraints_.clear();

  if (confPath_.empty()) {
#if defined SCHEMADIR
    confPath_ = SCHEMADIR;
#else
    confPath_ = "src/schemas";
#endif
  }
  
  Element e("schema",
	    SchemaUri,
	    SchemaUri,
            Schema::XSD_SCHEMA);
  lElems_.push_back(e);



#ifdef LOGGING
  level_ = 2;
#endif
}

SchemaParser::~SchemaParser()
{
  //clear the Types table
  typesTable_.clean();
  if(deleteXmlParser_) {
    
    delete xParser_;
    xmlStream_.close();
  }
   
  for (ConstraintList::iterator ci=constraints_.begin();
       ci != constraints_.end();
       ci++)
    delete *ci;
  for (AttributeGroupList::iterator agi = lAttributeGroups_.begin();
       agi != lAttributeGroups_.end();
       agi++)
    delete *agi; 
}


/*
 * Parses an schema definition.
 * This is the main entry method for the schema parser
 */
bool 
SchemaParser::parseSchemaTag()
{
  int i = 0;
  try {
  if(!xParser_)
    return false;
  while (xParser_->getEventType() != xParser_->START_TAG)
    xParser_->next();
  xParser_->require(xParser_->START_TAG, Schema::SchemaUri, "schema");
  int attcnt = xParser_->getAttributeCount();

  //parse the schema tag's attributes
  for (i = 0; i < attcnt; i++) {
    std::string attName = xParser_->getAttributeName(i);
    if ("targetNamespace" == attName)
      //store the tns URI
      tnsUri_ = xParser_->getAttributeValue(i);
    if ("version" == attName)
      version_ = xParser_->getAttributeValue(i);
    if ("elementFormDefault" == attName){
      if (xParser_->getAttributeValue(i) == "unqualified")
	elementQualified_ = false;

      else if (xParser_->getAttributeValue(i) == "qualified")
	elementQualified_ = true;
    }
    if ("attributeFormDefault" == attName) {
      if (xParser_->getAttributeValue(i) == "unqualified")
	attributeQualified_ = false;

      else if (xParser_->getAttributeValue(i) == "qualified")
	attributeQualified_ = true;
    }
  }

  for (i = xParser_->getNamespaceCount(xParser_->getDepth()) - 1;
       i > xParser_->getNamespaceCount(xParser_->getDepth() - 1) - 1; i--)
    if (xParser_->getNamespaceUri(i) == tnsUri_)
      tnsPrefix_ = xParser_->getNamespacePrefix(i);
  typesTable_.setTargetNamespace(tnsUri_);
  xParser_->nextTag();

  return   parseSchema();
  } catch (XmlPullParserException xpe){

       logFile_ <<"Error parsing schema for namespace "<<tnsUri_<<std::endl;
       logFile_ << xpe.description << " at "
           << xpe.line << ":" << xpe.col 
           << std::endl;
      return false;
  }
  catch(SchemaParserException spe) {

      spe.line = xParser_->getLineNumber();
      spe.col = xParser_->getColumnNumber();

       logFile_ << spe.description << " at "
           << spe.line << ":" << spe.col 
           << std::endl;

      return false;
  }
}

//this function handles the schema
bool
SchemaParser::parseSchema(std::string tag)
{
  try
    {
      do
        {
  
          if (xParser_->getEventType() == xParser_->END_TAG)
            {
              if (xParser_->getName() == tag)
                break;
              while (xParser_->getEventType() != xParser_->START_TAG)
                xParser_->nextTag();
            }

          /*
            This is the main loop
            Depending on the tag encountered call the appropriate routines
            Schema elements visible at this level
            1. Global  Element declarations
            2. Global attribute declarations
            3. Complex type and Simple type declarations

          */
          std::string elemName = xParser_->getName();
          if (elemName == "element") {
            bool fwd;
          Element e = parseElement(fwd);
          lElems_.push_back(e);
          }
          else if (elemName == "complexType")
            {
              XSDType *t = parseComplexType();
              typesTable_.addType(t);
            }
          else if (elemName == "simpleType")
            {
              XSDType *t = parseSimpleType();
              typesTable_.addType(t);
            }
          else if (elemName == "attribute") {
            bool fwd;
            lAttributes_.push_back(parseAttribute(fwd));
          }
          else if (elemName == "annotation"){
            parseAnnotation();
	  }
          else if (elemName == "import") {
            parseImport();
	  }
          else if (elemName=="include"){
            parseInclude();
	  }
          else if(elemName=="attributeGroup") {
 	    AttributeGroup* ag = parseAttributeGroup();
 	    if (ag)
 	      lAttributeGroups_.push_back(ag);
            
          }else if(elemName=="group") {
            
            lGroups_.push_back(parseGroup());
	    Group & g=lGroups_.back();
	    //make this grp the owner of the content model
	    g.setContents(g.getContents(),false);
          }
	  else if( elemName=="key")	{
            
	    constraints_.push_back(parseConstraint(Schema::Key));
	  }
	  else if( elemName=="keyref")	{
	    constraints_.push_back(parseConstraint(Schema::Keyref));
	  }
	  else if( elemName=="unique")	{
	    constraints_.push_back(parseConstraint(Schema::Unique));
	  }else if (elemName=="redefine"){
	    parseRedefine();
	  }
          else {
	    error("Unknown element "+ elemName,1);
	    break;
          }
	  xParser_->nextTag();
        }
      while (true);
      if ((importedSchemas_.size() == 0) &&
	  typesTable_.detectUndefinedTypes()){
	
	typesTable_.printUndefinedTypes(logFile_);logFile_.flush();
	error("Undefined Types in namespace "+tnsUri_);
        }
      if(shouldResolve())
        {
            
          resolveForwardElementRefs();
          resolveForwardAttributeRefs();
        }
        
    }
  catch(SchemaParserException spe)
    {
      spe.line = xParser_->getLineNumber();
      spe.col = xParser_->getColumnNumber();

       logFile_ << spe.description << " at "
           << spe.line << ":" << spe.col 
           << std::endl;

      return false;
    }
  return true;
}


void SchemaParser::parseAnnotation()
{

  do
    {
      xParser_->nextToken();
      if (xParser_->getEventType() == xParser_->END_TAG
          && xParser_->getName() == "annotation")
        break;
    }
  while (true);
}


ComplexType *
SchemaParser::parseComplexType()
{
  ComplexType *newType = new ComplexType(tnsUri_);
  int attcnt = xParser_->getAttributeCount();
  for (int i = 0; i < attcnt; i++)
    {
      if ("name" == xParser_->getAttributeName(i))
        newType->setName(xParser_->getAttributeValue(i));
     
      if ("mixed" == xParser_->getAttributeName(i) &&
	  (xParser_->getAttributeValue(i).empty() ||
	   xParser_->getAttributeValue(i)=="true"))
	
        newType->setContentModel(Schema::Mixed);
    }


  do
    {
      //begin parsing the complex type's children
      xParser_->nextTag();
      if (xParser_->getEventType() == xParser_->END_TAG)
        {
          if (xParser_->getName() == "complexType")
            break;

          //if an end tag is seen proceed till next start tag
          while (xParser_->getEventType() != xParser_->START_TAG)
            xParser_->nextTag();
        }
      std::string elemName = xParser_->getName();
      
      
      if (elemName == "all"){
        ContentModel * cm= new ContentModel(Schema::All);
        newType->setContents(cm);
        parseContent(cm);
      }
      else if (elemName == "sequence"){
        ContentModel * cm= new ContentModel(Schema::Sequence);
        newType->setContents(cm);
        parseContent(cm);
      }
      else if (elemName == "choice"){
        ContentModel * cm= new ContentModel(Schema::Choice);
        newType->setContents(cm);
        parseContent(cm);
      }
      else if (elemName == "attribute") {
        bool f=false;
        Attribute a=parseAttribute(f);
        newType->addAttribute(a,f);
      }else if (elemName=="attributeGroup"){
        parseAttributeGroup(newType);
      }
      else if (elemName=="group"){
	//TODO
	ContentModel* cm= new ContentModel(Schema::Sequence);
	newType->setContents(cm);
        parseGroup(cm);
      }
      else if (elemName == "anyAttribute")
        addAnyAttribute(newType);

      else if (elemName == "complexContent")
        parseComplexContent(newType);

      else if (elemName == "simpleContent")
        parseSimpleContent(newType);

      else if (xParser_->getName() == "annotation")
        parseAnnotation();

      else
        error("Unexpected tag: '"+elemName+"' in "+newType->getName() );
    }
  while (true);
  makeListFromSoapArray(newType);
  return newType;
}

AttributeGroup*
SchemaParser::parseAttributeGroup(ComplexType* cType)
{
  std::string name,ref;
  ref = xParser_->getAttributeValue("", "ref");
  if (!ref.empty())
    {
      Qname agRef(ref);
      AttributeGroup *ag= getAttributeGroup(agRef);
      if(cType && ag){
        
        for(list<Attribute>::iterator ai= ag->begin();
            ai!=ag->end();
            ai++)
          cType->addAttribute(*ai);
      }
      else if (cType){
	cType->addAttributeGroupName(ref);
      }
      xParser_->nextTag();    
      return ag;
    }
  
  name = xParser_->getAttributeValue("", "name");
  AttributeGroup *ag = new AttributeGroup(name);
  xParser_->nextTag();
  while (xParser_->getName() == "annotation")
    {
      parseAnnotation();
      xParser_->nextTag();
    }
  std::string elemName=xParser_->getName();
  while (!((xParser_->getEventType() == xParser_->END_TAG) &&
           (elemName == "attributeGroup"))){
   
    if(elemName=="attribute"){
      bool fwd;
      ag->addAttribute(parseAttribute(fwd));
    }else if(elemName=="attributeGroup"){
      AttributeGroup* ag1=parseAttributeGroup();
      for(list<Attribute>::iterator ai= ag1->begin();
          ai!=ag1->end();
          ai++)
        ag->addAttribute(*ai);
    }else if(elemName=="anyAttribute"){
      ag->addAttribute(addAnyAttribute(cType));
    }
    xParser_->nextTag();    
    elemName=xParser_->getName();
  }
  
  if(cType){
    
    for(list<Attribute>::iterator ai= ag->begin();
        ai!=ag->end();
        ai++)
      cType->addAttribute(*ai);
    delete ag;//dont store anonymous attribute groups
    ag = 0;
  }
  return ag;
}

Group
SchemaParser::parseGroup(ContentModel* c)
{
  int minimum = 1, maximum = 1;
  std::string tmp, name,ref;
  
  tmp = xParser_->getAttributeValue("", "minOccurs");
  if (!tmp.empty())
    minimum = XmlUtils::parseInt(tmp);
  tmp = xParser_->getAttributeValue("", "maxOccurs");
  if (!tmp.empty()) {
    if ("unbounded" == tmp)
      maximum = UNBOUNDED;
    else
      maximum = XmlUtils::parseInt(tmp);
  }
  ref = xParser_->getAttributeValue("", "ref");
  if (!ref.empty()) {

    Qname gName(ref);
    xParser_->nextTag();
    Group* gRef=getGroup(gName);
    if(gRef){
      Group g(*gRef);
      if(c)
	c->addGroup(g,true);
      return g;
    }
    else{
      Group g(gName.getLocalName(),minimum,maximum);
      if(c)
	c->addGroup(g,true);
      return g;
    }
  }

  name = xParser_->getAttributeValue("", "name");
  Group g(name,minimum,maximum);
  xParser_->nextTag();
  while (xParser_->getName() == "annotation") {
    parseAnnotation();
    xParser_->nextTag();
  }

  std::string elemName = xParser_->getName();
  ContentModel * cm=0;
  if (elemName == "all"){
    cm = new ContentModel(Schema::All);
  }
  else if (elemName == "sequence"){
    cm= new ContentModel(Schema::Sequence);
  }
  else if (elemName == "choice"){
    cm= new ContentModel(Schema::Choice);
  }
  g.setContents(cm,true);
  parseContent(cm);
  xParser_->nextTag();

  if(c)
    c->addGroup(g,false);
  return g;
}

void
SchemaParser::parseContent(ContentModel * cm)
{
  int minimum = 1, maximum = 1;
  std::string tmp;

  tmp = xParser_->getAttributeValue("", "minOccurs");
  if (!tmp.empty())
    minimum = XmlUtils::parseInt(tmp);
  tmp = xParser_->getAttributeValue("", "maxOccurs");
  if (!tmp.empty())
    {
      if ("unbounded" == tmp)
        maximum = UNBOUNDED;
      else
        maximum = XmlUtils::parseInt(tmp);
    }
  cm->setMin(minimum);
  cm->setMax(maximum);

  xParser_->nextTag();
  while (xParser_->getName() == "annotation")
    {
      parseAnnotation();
      xParser_->nextTag();
    }

  while (!((xParser_->getEventType() == xParser_->END_TAG) &&
           (xParser_->getName() == "choice"
            || xParser_->getName() == "sequence"
            || xParser_->getName() == "all")))
    {
      if (xParser_->getName() == "element") {
        bool f=false;
        Element e =parseElement(f);
        cm->addElement(e);
      }else if(cm->getCompositor()!=Schema::All){
        
        if (xParser_->getName() == "any")
          addAny(cm);
        else if (xParser_->getName() == "choice"){
          ContentModel * cmc= new ContentModel(Schema::Choice);
          cm->addContentModel(cmc);
          parseContent(cmc);  
        }
        else if (xParser_->getName() == "sequence"){
          ContentModel * cms= new ContentModel(Schema::Sequence);
          cm->addContentModel(cms);
          parseContent(cms);  
        }
        else if (xParser_->getName() == "group"){
	  parseGroup(cm);
        }
        else if(xParser_->getName() == "annotation") {
	  parseAnnotation();
	}
	else
          error("parseContent: Unexpected tag "+xParser_->getName());
      }else{
        
        error("parseContent <all>:Syntax Error");
      }
      xParser_->nextTag();
    }
}

Element
SchemaParser::parseElement(bool & fwdRef)
{
  std::string name, fixedVal, defaultVal, 
    // the namespace of the element is the
    // namespace of the sp that parsed it!
    typeNs = tnsUri_,elemNs = tnsUri_;
  Constraint* c=0;
  int type_id = 0, minimum = 1, maximum = 1, attcnt;
  Qname refName;
  bool qualified = false,nill = false;
  XSDType *elemType;
  fwdRef=false;
  attcnt = xParser_->getAttributeCount();
  for (int i = 0; i < attcnt; i++)
    {
      std::string attName = xParser_->getAttributeName(i);
      if ("name" == attName)
        name = xParser_->getAttributeValue(i);

      else if ("type" == attName)
        {
          Qname typeName(xParser_->getAttributeValue(i));
          if (type_id > 0)
            error
              ("<element> : type and ref are mutually exclusive in element decl");
	  typeName.setNamespace(typeNs=xParser_->getNamespace(typeName.getPrefix()));
          type_id = getTypeId(typeName, true);
          if (type_id == 0)
            error("<element>:Could not resolve type " +
                  typeName.getNamespace() + ":" +
                  typeName.getLocalName(),0);
        }

      else if ("form" == attName)
        {
          if ("qualified" == xParser_->getAttributeValue(i))
            qualified = true;

          else if ("unqualified" == xParser_->getAttributeValue(i))
            qualified = false;
          else
            error("<element>:Invalid value for form in element " +
                  name,1);
        }

      else if ("ref" == attName)
        {
          if (!name.empty())
            error
              ("<element>:name and ref are mutually exclusive in element decl");
          if (type_id > 0)
            error
              ("<element>:type and ref are mutually exclusive in element decl");
          refName = xParser_->getAttributeValue(i);
          refName.setNamespace(xParser_->getNamespace(refName.getPrefix()));
	  Element *e=0;
	  elemNs = refName.getNamespace();

          if(refName.getNamespace()==tnsUri_){

            e = const_cast<Element*>(getElement(refName));
	    if (e)
	      type_id = e->getType();
          }
	  else{
	    //The referenced element may be in an imported schemaparser
            int i=checkImport(refName.getNamespace());
            if(i>=0 && importedSchemas_[i].sParser) {
           
	      e=const_cast<Element*>(importedSchemas_[i].sParser->getElement(refName));
	      if (e){
		//if the type is in an imported schema then we must add a local reference to
		// its type,because the type id as got by e->getType()
		// is not valid in the current schema context
		const XSDType* pType = importedSchemas_[i].sParser->getType(e->getType());
		type_id= typesTable_.addExternalTypeId(e->getName()+"_"+e->getTypeNamespace(),
						       pType);
	      }
	    }
          }
	  
          if (e == 0){

	    fwdRef=true;
	    name=refName.getLocalName();
	    lForwardElemRefs_.push_back(refName);
	    //this will be resolved later
	  }
          else{
	    name = e->getName();
	    qualified = e->isQualified();
	    defaultVal = e->defaultVal();
	    fixedVal = e->fixedVal();
	    typeNs = e->getTypeNamespace();
	    elemNs = e->getNamespace();
	  }

#ifdef LOGGING
	    logFile_<<elemNs<<":"<<name<<" ->  element reference("<<type_id<<")"<<std::endl;
#endif
	  
        }
      else if ("minOccurs" == attName){
        minimum = XmlUtils::parseInt(xParser_->getAttributeValue(i), 10);
      }
      else if ("maxOccurs" == attName){
	if ("unbounded" == xParser_->getAttributeValue(i))
          maximum = UNBOUNDED;
	else
          maximum = XmlUtils::parseInt(xParser_->getAttributeValue(i), 10);
        if (maximum == -1){                        //invalid value for maxOccurs
	  error("<element>:Invalid value for maxOccurs",1);
          maximum=1;
	}
      }
      else if ("default" == attName){
	if (fixedVal.empty())
	  defaultVal = xParser_->getAttributeValue(i);

	else
	  error("<element>:fixed and default cannot occur together");
      }
      else if ("fixed" == attName){
	if (defaultVal.empty())
	  fixedVal = xParser_->getAttributeValue(i);

	else
	  error("<element>:fixed and default cannot occur together");
      }

      else if ("substitutionGroup" == attName) {

	//do nothing
      }
      else if ("nillable" == attName)  {

	//a nillable element need not have a type ,so set it to anyType id if nop type was given
	nill = true;
	minimum = 0;
      }
      else
        error("<element>:Unsupported Attribute "+attName ,2) ;
    }

  do
    {
      xParser_->nextTag();
      std::string elemName=xParser_->getName();
      if (xParser_->getEventType() == xParser_->END_TAG) {
	if (elemName == "element")
	  break;

	//if an end tag is seen proceed till next start tag
	while (xParser_->getEventType() != xParser_->START_TAG)
	  xParser_->nextTag();
      }

      if (elemName == "complexType"){
	elemType = parseComplexType();
	type_id = typesTable_.addType(elemType);
        typeNs = elemType->getNamespace();
      }
      else if (elemName == "simpleType"){
	elemType = parseSimpleType();
	type_id = typesTable_.addType(elemType);
        typeNs = elemType->getNamespace();
      }
      else if (elemName == "annotation"){
        parseAnnotation();
      }
      else if( elemName=="key")	{
	if (c)
	  delete c;
	c=parseConstraint(Schema::Key);
      }
      else if( elemName=="keyref")	{
	if (c)
	  delete c;
	c=parseConstraint(Schema::Keyref);
      }
      else if( elemName=="unique")	{
	if (c)
	  delete c;
	c=parseConstraint(Schema::Unique);
      }
      else{
	error("<element> : syntax error or unkown tag :"+elemName);
      }
    }
  while (true);
  
  if (nill && type_id == 0) {
    type_id = Schema::XSD_ANYTYPE;
  }
  
  constraints_.push_back(c);  
  Element e(name,
	    elemNs,
	    typeNs,
            type_id,
            minimum,
            maximum,
            qualified,
            defaultVal,
            fixedVal);
  e.addConstraint(c);
  return e;
}

Constraint*
SchemaParser::parseConstraint(Schema::ConstraintType cstr)
{
  Constraint * c= new Constraint(cstr);
  c->setName(xParser_->getAttributeValue("","name"));

  do
    {
      xParser_->nextTag();
      std::string elemName=xParser_->getName();
      if (xParser_->getEventType() == xParser_->END_TAG) {
	if ((cstr==Schema::Key && elemName == "key")
		|| (cstr==Schema::Keyref && elemName == "keyref")
		|| (cstr==Schema::Unique && elemName == "unique")) {
	  break;
	}

	//if an end tag is seen proceed till next start tag
	while (xParser_->getEventType() != xParser_->START_TAG)
	  xParser_->nextTag();
      }
      if(elemName=="selector"){
	c->setSelector(xParser_->getAttributeValue("", "xpath"));
	xParser_->nextTag();
      }
      else if(elemName=="field"){
	c->addField(xParser_->getAttributeValue("", "xpath"));
	xParser_->nextTag();
      }
    }while (true);
  return c;
}


Element
SchemaParser::addAny(ContentModel* cm)
{
  std::string ns;
  
  int type_id = Schema::XSD_ANY, minimum = 1, maximum = 1, attcnt;
  //note  processContents=lax .
  attcnt = xParser_->getAttributeCount();
  for (int i = 0; i < attcnt; i++)
    {
      std::string attr = xParser_->getAttributeName(i);
      if ("namespace" == attr)
        ns = xParser_->getAttributeValue(i);

      else if ("minOccurs" == attr)
        minimum = XmlUtils::parseInt(xParser_->getAttributeValue(i), 10);

      else if ("maxOccurs" == attr)
        {
          if ("unbounded" == xParser_->getAttributeValue(i))
            maximum = UNBOUNDED;
          else
            maximum = XmlUtils::parseInt(xParser_->getAttributeValue(i), 10);
          if (maximum == -1){                        //invalid value for maxOccurs
            error("<element>:Invalid value for maxOccurs",1);
            maximum=1;
	  }
        }

      else if ("processContents" == attr || "id" == attr) {
	
	//do nothing
        }
      else
        error("<any>:Unsupported Attribute "+attr,2);
    }

  xParser_->nextTag();
  do
    {
      if (xParser_->getEventType() == xParser_->END_TAG)
        {
          if (xParser_->getName() == "any")
            break;
	  
        }
      xParser_->nextToken();
    }while (true);


  Element e(ns,
	    ns,
	    ns,
            type_id,
            minimum,
            maximum);
  
  cm->addElement(e);
  return e;
}


Attribute
SchemaParser::addAnyAttribute(ComplexType * cType)
{
  std::string ns;
  int type_id = Schema::XSD_ANY,attcnt;
  bool qualified = true;

  //note  processContents=lax .
  attcnt = xParser_->getAttributeCount();
  for (int i = 0; i < attcnt; i++)
    {
      std::string attr = xParser_->getAttributeName(i);
      if ("namespace" == attr)
        ns = xParser_->getAttributeValue(i);

      else if ("processContents" == attr || "id" == attr)
        {

          //do nothing
        }
      else
        error("<anyAttribute>:Unsupported Attribute "+attr,1);
    }
  
  Attribute a(ns,
              type_id,
              qualified);
 if(cType)
   cType->addAttribute(a);
  xParser_->nextTag();
  while (xParser_->getName() == "annotation")
    {
      parseAnnotation();
      xParser_->nextTag();
    }
  return a;
  
}


//This function parses and attribute
Attribute
SchemaParser::parseAttribute(bool & fwdRef)
{
  std::string name, fixedVal, defaultVal;
  int type_id = 0, attcnt;
  bool qualified = false, use = false;
  fwdRef=false;
  
  Qname refAttribute;
  attcnt = xParser_->getAttributeCount();
  for (int i = 0; i < attcnt; i++) {
    std::string attName = xParser_->getAttributeName(i);
    std::string attNs=xParser_->getAttributeNamespace(i);
    std::string attVal=xParser_->getAttributeValue(i);
    
    
    if ("name" == attName)
      name = attVal;
    else if ("type" == attName) {
      if (type_id > 0)
	error("<attribute>:type and ref are mutually exclusive in element decl");
      Qname typeName(attVal);
      typeName.setNamespace(xParser_->
			    getNamespace(typeName.getPrefix()));
      type_id = getTypeId(typeName, true);
      if (type_id == 0)
	error("<attribute>:Could not resolve type " +
	      typeName.getNamespace() + 
	      ":" +typeName.getLocalName(),1);
    }
    else if ("form" == attName) {
      if ("qualified" == attVal)
	qualified = true;
      else 
	qualified = false;
    }
    else if ("ref" == attName) {
      if (!name.empty())
	error("<attribute>:name and ref are mutually exclusive in element decl");
      if (type_id > 0)
	error("<attribute>:type and ref are mutually exclusive in element decl");
      refAttribute = attVal;
      refAttribute.setNamespace(xParser_->getNamespace(refAttribute.getPrefix()));
      Attribute *a =0;
      if(refAttribute.getNamespace()==tnsUri_){
	a=getAttribute(refAttribute);
      }else{
	int i=checkImport(refAttribute.getNamespace());
	if(i >=0 && importedSchemas_[i].sParser){
	  a=importedSchemas_[i].sParser->getAttribute(refAttribute);
	}
	else
	  a=0;
      }
          
      if (a == 0){
	fwdRef = true;
	name=refAttribute.getLocalName();
	lForwardAttributeRefs_.push_back(refAttribute);
      }
      else{
	name = a->getName();
	type_id = a->getType();
	qualified = a->isQualified();
	if (defaultVal.empty())
	  defaultVal = a->defaultVal();
	if (fixedVal.empty())
	  fixedVal = a->fixedVal();
      }
    }
    else if ("default" == attName) {
      if (fixedVal.empty())
	defaultVal = attVal;
      else
	error
	  ("<attribute>:fixed and default cannot occur together");
    }
    else if ("fixed" == attName) {
      if (defaultVal.empty())
	fixedVal = attVal;
      else
	error("<attribute>:fixed and default cannot occur together");
    }
    else if ("use" == attName) {
      if (attVal == "required")
	use = true;
      else 
	use = false;
    }
    else {
      int n=-1;
      if(!attNs.empty() && ((n=checkImport(attNs))!=-1)){
	fixedVal=attNs;//hack for non schema attributes
	defaultVal=attVal;//store non schema attributes.esp for soapenc:arrayType
      }else{
	error("<attribute>:Unsupported attribute {"+ attNs+ "}:"+attName,2);
      }
    }
  }
  //Now parse the children of the attribute tag viz simpleType
  do
    {
      xParser_->nextTag();
      if (xParser_->getEventType() == xParser_->END_TAG)
        {
          if (xParser_->getName() == "attribute")
            break;

          //if an end tag is seen proceed till next start tag
          while (xParser_->getEventType() != xParser_->START_TAG)
            xParser_->nextTag();
        }

      else if (xParser_->getName() == "simpleType")
        {
          XSDType *elemType = parseSimpleType();

          //create an anonymous type
          type_id = typesTable_.addType(elemType);
        }

      else if (xParser_->getName() == "annotation")
        parseAnnotation();
      else
        error("<attribute>:Syntax error or unkown tag  "+xParser_->getName());
    }
  while (true);

  Attribute a(name,
              type_id,
              qualified,
              defaultVal,
              fixedVal,
              use);
  return a;
  
}

SimpleType *
SchemaParser::parseSimpleType()
{
  SimpleType *st = new SimpleType(tnsUri_);
  int basetype_id = 0;
  int attcnt;
  attcnt = xParser_->getAttributeCount();
  for (int i = 0; i < attcnt; i++)
    {
      if ("name" == xParser_->getAttributeName(i))
        st->setName(xParser_->getAttributeValue(i));

      else
        error("<simpleType> :" + xParser_->getAttributeName(i) +
              ":Unknown/Unsupported  attribute ",2);
    }

  do
    {
      xParser_->nextTag();
      if (xParser_->getEventType() == xParser_->END_TAG)
        {
          if (xParser_->getName() == "simpleType")
            break;

          //if an end tag is seen proceed till next start tag
          while (xParser_->getEventType() != xParser_->START_TAG)
            xParser_->nextTag();
        }
      if (xParser_->getName() == "restriction")
        {
          attcnt = xParser_->getAttributeCount();
          for (int i = 0; i < attcnt; i++)
            {
              if ("base" == xParser_->getAttributeName(i))
                {
                  Qname typeName(xParser_->getAttributeValue(i));
                  typeName.setNamespace(xParser_->
                                        getNamespace(typeName.
                                                     getPrefix()));
                  st->setBaseType(basetype_id =
                                  getTypeId(typeName, true));
                  if (basetype_id == 0)
                    error("<simpleType>:" +
                          xParser_->getAttributeValue(i) +
                          ":Unknown base type ",1);
                }
              else
                error("<simpleType>:" + xParser_->getAttributeName(i) +
                      ":Unknown/Unsupported  attribute for <restriction>",2);
            }
          parseRestriction(st);
        }
      else if (xParser_->getName() == "union"){
	
	std::string members = xParser_->getAttributeValue("", "memberTypes");
	size_t s = 0;
	while(s < members.length()){
	  while(members[s]==' ')s++;
	  std::string type = members.substr(s,members.find(' ',s)-s);
	  Qname typeName(type);
	  typeName.setNamespace(xParser_->getNamespace(typeName.getPrefix()));
	  basetype_id = getTypeId(typeName,true);
	  st->setUnionType(basetype_id);
	  s+=type.length()+1;
	}
	
	xParser_->nextTag();
	while(xParser_->getName() == "simpleType"){
	  XSDType * t = parseSimpleType();
	  Schema::Type i = (Schema::Type)typesTable_.addType(t);

	  st->setUnionType(i);
	  xParser_->nextTag();
	}
      } 
      else if(xParser_->getName() == "list"){
	
	basetype_id = getTypeId(xParser_->getAttributeValue("", "itemType"));
	st->setListType(basetype_id);
	xParser_->nextTag();
      }
      else if (xParser_->getName() == "annotation")
        parseAnnotation();
      else
        error("<simpleType>:Syntax error");
    }
  while (true);
  return st;
}

void 
SchemaParser::parseRestriction(SimpleType * st,
			       ComplexType * ct)
{
  if (st->getBaseTypeId() == 0)
    error("<restriction>:unkown BaseType",1);

  do {
    xParser_->nextTag();
    if (xParser_->getEventType() == xParser_->END_TAG)
      {
	if (xParser_->getName() == "restriction")
	  break;
	else
	  xParser_->nextTag();
	if (xParser_->getName() == "restriction"
	    && xParser_->getEventType() == xParser_->END_TAG)
	  break;
      }
    while (xParser_->getName() == "annotation") {
      parseAnnotation();
      xParser_->nextTag();
    }
    if(xParser_->getName()=="attribute" && ct!=0){
      bool f=false;
      Attribute a=parseAttribute(f);
      ct->addAttribute(a,f);
    }
    else if (st->isvalidFacet(xParser_->getName())){
      //This function also sets the facet if valid

      st->setFacetValue(xParser_->getName(),
			xParser_->getAttributeValue("", "value"));
    }else{
      error("<restriction>:" + xParser_->getName() +
	    " is not a valid facet /attribute for the type",1);
    }
  } while (true);
}

void
SchemaParser::parseComplexContent(ComplexType * ct)
{
  int attcnt = xParser_->getAttributeCount();
  int i = 0;
  Qname typeName;

  ct->setContentModel(Schema::Complex);
  xParser_->nextTag();

  while (xParser_->getName() == "annotation") {
    parseAnnotation();
    xParser_->nextTag();
  }

  if (xParser_->getName() == "restriction")  {
    attcnt = xParser_->getAttributeCount();
    for (i = 0; i < attcnt; i++) {
      if ("base" == xParser_->getAttributeName(i))
	{
	  typeName = xParser_->getAttributeValue(i);
	  typeName.setNamespace(xParser_->
				getNamespace(typeName.getPrefix()));
	}
    }
    ct->setBaseType(getTypeId(typeName, true),
		    Schema::Restriction);
  }
  else if (xParser_->getName() == "extension") {
    attcnt = xParser_->getAttributeCount();
    for (i = 0; i < attcnt; i++) {
      if ("base" == xParser_->getAttributeName(i))  {
	typeName = xParser_->getAttributeValue(i);
	typeName.setNamespace(xParser_->
			      getNamespace(typeName.getPrefix()));
      }
    }
    ct->setBaseType(getTypeId(typeName, true),
		    Schema::Extension);
  }
  
  xParser_->nextTag();
  while (xParser_->getName() == "annotation") {
    parseAnnotation();
    xParser_->nextTag();
  }
  
  {
    std::string elemName=xParser_->getName();
    ContentModel * cm=0;      
    if (elemName == "all"){
      cm= new ContentModel(Schema::All);
    }
    else if (elemName == "sequence"){
      cm= new ContentModel(Schema::Sequence);
    }
    else if (elemName == "choice"){
      cm= new ContentModel(Schema::Choice);
    }

    if(cm){
      parseContent(cm);
      ct->setContents(cm);
      xParser_->nextTag();
    }

    //parse any attributes
    while (xParser_->getEventType() != xParser_->END_TAG){
      
      if (xParser_->getName() == "attribute") {
	bool f=false;
	Attribute a=parseAttribute(f);
	ct->addAttribute(a,f);
      }
      else if(xParser_->getName() == "attributeGroup")
	{
	  parseAttributeGroup(ct);
	  
	}
      else if (xParser_->getName() == "anyAttribute")
	addAnyAttribute(ct);
      
      xParser_->nextTag();
    }
  }
  
  do {
    if (xParser_->getEventType() == xParser_->END_TAG)
      if ((xParser_->getName() == "restriction" ||
	   xParser_->getName() == "extension") ) 
	break;
    xParser_->nextTag();
  }
  while (true);
  
  xParser_->nextTag();
}


void
SchemaParser::parseSimpleContent(ComplexType * ct)
{
  ct->setContentModel(Schema::Simple);
  xParser_->nextTag();
  if (xParser_->getName() == "restriction")
    {
      SimpleType *st = new SimpleType(tnsUri_);
      int attcnt = xParser_->getAttributeCount();
      int basetype_id = 0;
      for (int i = 0; i < attcnt; i++)
        {
          if ("base" == xParser_->getAttributeName(i))
            {
              Qname typeName(xParser_->getAttributeValue(i));
              typeName.setNamespace(xParser_->
                                    getNamespace(typeName.getPrefix()));
              st->setBaseType(basetype_id = getTypeId(typeName, true));
              if (basetype_id == 0)
                error("<simpleContent> :" +
                      xParser_->getAttributeValue(i) +
                      ":Unknown base type ",1);
            }

          else
            error("<simpleContent> :" + xParser_->getAttributeName(i) +
                  ":Unknown/Unsupported  attribute ",2);
        }
      parseRestriction(st,ct);
      int typeId = typesTable_.addType(st);
      ct->setSimpleContentType(typeId);
    }

  else if (xParser_->getName() == "extension")
    {
      //This extension does not use the full model that can come in
      //ComplexContent .It uses the simple model.no particle allowed ,only attributes
      int attcnt = xParser_->getAttributeCount();
      int basetype_id = 0;
      for (int i = 0; i < attcnt; i++)
        {
          if ("base" == xParser_->getAttributeName(i))
            {
              Qname typeName(xParser_->getAttributeValue(i));
              typeName.setNamespace(xParser_->
                                    getNamespace(typeName.getPrefix()));
              ct->setSimpleContentType(basetype_id =
                                       getTypeId(typeName, true));
              if (basetype_id == 0)
                error("<simpleContent> :" +
                      xParser_->getAttributeValue(i) +
                      ":Unknown base type ",1);
            }

          else
            error("<simpleContent> :" + xParser_->getAttributeName(i) +
                  ":Unknown/Unsupported  attribute ");
        }
      xParser_->nextTag();
      do
	{
	  
	  if (xParser_->getName() == "attribute")
	    {
	      bool f=false;
	      Attribute a=parseAttribute(f);
	      ct->addAttribute(a,f);


	    }
	  else if(xParser_->getName() == "attributeGroup")
	    {
	      parseAttributeGroup(ct);

	    }

          else if (xParser_->getName() == "anyAttribute")
              addAnyAttribute(ct);
	  else
	    break;
	  xParser_->nextTag();
	}while(true);
      
      if (!
          (xParser_->getName() == "extension"
           && xParser_->getEventType() == xParser_->END_TAG))
        error("<simpleContent> :Syntax error :extension");
    }
  xParser_->nextTag();
  if (!
      (xParser_->getName() == "simpleContent"
       && xParser_->getEventType() == xParser_->END_TAG))
    error("<simpleContent> :Syntax error ");
}


bool
SchemaParser::parseRedefine()
{
  parseInclude();
  resolveFwdRefs_=false;
  parseSchema("redefine");
  resolveFwdRefs_=true;
  return true;
}

bool
SchemaParser::parseInclude()
{
  ifstream xsdStream;
  std::string loc = xParser_->getAttributeValue("", "schemaLocation");


  // FV Sat Dec 22 15:33:09 CET 2007 I added the absolute path and the file:/ use-cases 
  //in the the test. Will not work for paths like "C:\temp\schema.xsd" .Use the file:/ protocol


  if ( loc.find("/",0)      != 0                 &&         // not an asolute path
       loc.find("file:/",0) == std::string::npos &&
       loc.find("http://")  == std::string::npos)
    loc = uri_ + loc;


#ifndef _WIN32
  
  if (!loc.empty()) {
    
    std::string schemaconf= confPath_ + "schema.conf";
    try {
    ConfigFile cf(schemaconf);
    cf.readInto<std::string>(loc,loc);
    }catch (const ConfigFile::file_not_found & e) {}
  }
#endif
  
  
  if(!loc.empty())
    {
      if(XmlUtils::fetchUri(loc,fname_))
        {
          /*
           * If the schema definition was retrieved successfully 
           * process it and add all type definitions and
           * declaration to the current namespace
           */
        xsdStream.open(fname_.c_str());
            
          XmlPullParser * xpp = new XmlPullParser(xsdStream);
          XmlPullParser * tmpXparser=xParser_;
          xParser_=xpp;

          xParser_->setFeature(FEATURE_PROCESS_NAMESPACES, true);
          xParser_->require(XmlPullParser::START_DOCUMENT, "", "");
          while (xParser_->getEventType() != xParser_->END_DOCUMENT){ 
	    xParser_->nextTag();
	    if (xParser_->getEventType() == xParser_->START_TAG &&
		xParser_->getName() == "schema"){
	      resolveFwdRefs_=false;
                   
	      if(!parseSchemaTag())
		error("Error while parsing the included schema " + loc);
	      else{

		resolveFwdRefs_=true;  
		break;
	      }
	    }
	  }
          xParser_=tmpXparser;
          delete xpp;
        }
      else{
	  
	  error("Error while opening the included schema " + loc);
	}
    }
  else{

      error("schemaLocation is a required attribute for <include>");
    }
          
  xParser_->nextTag();
  return true;
}

bool
SchemaParser::parseImport()
{
  Qname typeName;
  std::string xsdFile;
  std::string ns = xParser_->getAttributeValue("", "namespace");
  std::string loc=xParser_->getAttributeValue("", "schemaLocation");

  if(ns == tnsUri_)
    return parseInclude();//sometimes import is used to import schemas in same ns.
                          //treat it internally like include


  //  if (loc.empty()) 
  //    loc = ns; //try using the namespace as schemalocation
  

//   if ( !loc.empty() && loc.find("http://") == std::string::npos)
//      loc = uri_ + loc;

  if ( !loc.empty() &&
       loc.find("/",0)      != 0                 &&         // no an asolute path
       loc.find("file:/",0) == std::string::npos &&
       loc.find("http://")  == std::string::npos)
    loc = uri_ + loc;
  
#ifndef _WIN32 
  if (!loc.empty()) {
    
    std::string schemaconf= confPath_ + "schema.conf";
    try {
      ConfigFile cf(schemaconf);
      cf.readInto<std::string>(loc,loc);
    }catch (const ConfigFile::file_not_found &e) {}
  }
#endif
  
  if(!loc.empty())
    {
      if(XmlUtils::fetchUri(loc,xsdFile))
        {
          /*
           * If the schema definition was retrieved successfully 
           * process it and add it to list of imported schemas
           */
          SchemaParser *sp = new SchemaParser(xsdFile,ns);
	  sp->setUri(uri_);
	  //pass the imports to the new schema parser
	  for (size_t i = 0; i < importedSchemas_.size(); i++) {
	
	    if(importedSchemas_[i].sParser ) {
	      sp->addImport(importedSchemas_[i].sParser);
	    }
	  }



          if(sp->parseSchemaTag())
            addImport(sp);
          else
            error("Error while parsing imported namespace "+ns,0);
               
        }
      else{
	
	error("could not import namespace from location "+loc);
      }
    }
  else{
    // if no location is mentioned ,just add the namespace,types will be resolved later
    
    addImport(ns);
  }

  error("Imported namespace "+ns+"  from " + loc,2);

  if (loc.empty()) 
    error("No location supplied for the import"+ns,2);

  xParser_->nextTag();
  return true;
}

bool SchemaParser::isBasicType(int sType) const
{
  if (sType > Schema::XSD_ANYURI || sType <= Schema::XSD_INVALID)
    return false;

  else
    return true;
}


//This function gets the id of a type whose Qname is passed.
//The Qname struct if it has a prefix must either be a valid namespace
//default is http://www.w3.org/2001/XMLSchema
//This function has two modes
//if 'create' is true a new type is created (for fwd references)
//otherwise the existing list of parsed types is used for resolution

int
SchemaParser::getTypeId( const Qname &  type, bool create)
{
  std::string typens = type.getNamespace();
  if (typens.empty()||
      typens == tnsUri_ ||
      typens == Schema::SchemaUri){

    return typesTable_.getTypeId(type, create);
  }
  else {
    //postpone resolution till matchExtRefs is called
    if (importedSchemas_.size() == 0  && create) {                
      
      return typesTable_.addExternalTypeId(type, 0);
    }

    //search in the array of imported schemas
    int typeId = 0;
    for (size_t i = 0; i < importedSchemas_.size(); i++) {
	
      if ( importedSchemas_[i].ns == type.getNamespace()) {

	if(importedSchemas_[i].sParser ) {

	  typeId = importedSchemas_[i].sParser->getTypeId(type, false);
	  //get the type definition from the imported namespace schema parser and 
	  // add a reference to the current schema parser
	  if (typeId) {
	    return typesTable_.addExternalTypeId(type,
						 (XSDType *) importedSchemas_[i].sParser->getType(typeId));
	  }
	  else
	    return 0;
	}
      }
    }
    if (create){
	  //automatically add an unreferenced namespace as an import
      addImport(type.getNamespace()); 
      return typesTable_.addExternalTypeId(type, 0);
	}
  }
  return XSD_INVALID;
}


//resolves any external references with  the imported schemas
//This method must be called to ensure resolution of all types
bool SchemaParser::finalize(void)
{
  int unresolved=typesTable_.getNumExtRefs();
  if(unresolved > 0) {
    for (int i = 0; i < unresolved; i++){
    
      Qname & type = typesTable_.getExtRefName(i);
      int localId = typesTable_.getExtRefType(i);

      //search in the array of imported schemas
      int typeId = 0;
      for (size_t n = 0; n < importedSchemas_.size(); n++)
	{
	  if (importedSchemas_[n].ns == type.getNamespace())
	    {
	      if(importedSchemas_[n].sParser){
		typeId = importedSchemas_[n].sParser->getTypeId(type);
		if (typeId != 0)
		  typesTable_.addExtType((XSDType *) importedSchemas_[n].sParser->getType(typeId),
					 localId);
	      }
	    }
	}
      
      if (typeId == 0) {
	
	logFile_<<"Undefined type "<<type<<std::endl;
      }
    }
  }
  if (typesTable_.detectUndefinedTypes())
    {
      typesTable_.printUndefinedTypes(logFile_);logFile_.flush();
      logFile_<<"Unresolved types in namespace "<<tnsUri_<<std::endl;
      return false;
    }

  else{
    
    return true;
  }
  
}


//resolves any forward references of the kind<element ref=Qname... >
void
SchemaParser::resolveForwardElementRefs()
{
  bool errors=false;
  if (lForwardElemRefs_.empty())
    return;
  for (list < Qname >::iterator pQnames = lForwardElemRefs_.begin();
       pQnames != lForwardElemRefs_.end(); pQnames++) {
    
    // cout<<*pQnames<<std::endl;
    Element *e = const_cast<Element*>(getElement(*pQnames));
    //TODO , in case the forward ref is in an imported schema we cant just copy the type id
    //it needs to be changed to make it a valid type id in current schema
    if (e)
      typesTable_.resolveForwardElementRefs(pQnames->getLocalName(),*e);
    else {
      error("Could not resolve element reference "+pQnames->getLocalName(),1);
      errors=true;
    }
  }
  if(errors)
    error("Unresolved element references",1);
}


void
SchemaParser::resolveForwardAttributeRefs()
{
  bool errors=false;
  if (lForwardAttributeRefs_.empty())
    return;
  for (list < Qname >::iterator pQnames = lForwardAttributeRefs_.begin();
       pQnames != lForwardAttributeRefs_.end(); pQnames++)
    {
      Attribute *a = getAttribute(*pQnames);
      if (a)
        typesTable_.resolveForwardAttributeRefs(pQnames-> getLocalName(), *a);
      else {
	error("Could not resolve attribute reference  {"+pQnames->getNamespace()
               +"}"+pQnames->getLocalName(),1);
	errors=true;
      }
    }
  if(errors)
    error("Unresolved attributes references");
}


//get the element id of a globally declared element
const Element*
SchemaParser::getElement(const Qname & element,bool checkImports)const
{
  std::string typens = element.getNamespace();
  if (typens.empty())
    typens = tnsUri_;
  if (typens== tnsUri_ || typens == Schema::SchemaUri)
    {
      int i = 0;
      //check if it is a global element
      for (std::list<Element>::const_iterator eli=lElems_.begin();
           eli!= lElems_.end();
           eli++,i++)
        if (eli->getName() == element.getLocalName())
          return &(*eli);
      return 0;
    }
  else if (checkImports)
    { //search imported namespaces
      for (size_t i = 0; i < importedSchemas_.size(); i++)
        {
          if ( importedSchemas_[i].ns == typens)
            {
              if(importedSchemas_[i].sParser )
		{
                  return importedSchemas_[i].sParser->getElement(element);
		}
            }
        }
    }
  return 0;
}

//get the attribute id of a globally declared attribute
Attribute*
SchemaParser::getAttribute(const Qname & attribute)
{
  std::string typens = attribute.getNamespace();
  if (typens.empty())
    typens = tnsUri_;
  
  if (typens == tnsUri_ || typens == Schema::SchemaUri) {
    //check if it is a global attribute
    for(std::list<Attribute>::iterator ali=lAttributes_.begin();
        ali!=lAttributes_.end();
        ali++)
      if (ali->getName() == attribute.getLocalName())
        return &(*ali);
  }else {
    //search imported namespaces
    for (size_t i = 0; i < importedSchemas_.size(); i++)
      {
        if ( importedSchemas_[i].ns == typens)
          {
            if(importedSchemas_[i].sParser )
              {
                return importedSchemas_[i].sParser->getAttribute(attribute);
              }
          }
      }
  }
  return 0;
}

//get the element id of a globally declared element
Group*
SchemaParser::getGroup(const Qname & name)
{
  std::string typens = name.getNamespace();
  if (typens.empty())
    typens = tnsUri_;
  if (typens== tnsUri_ || typens == Schema::SchemaUri)
    {

      //check if it is a global group
      for (std::list<Group>::iterator gli =lGroups_.begin();
           gli!= lGroups_.end();
           gli++)
        if (gli->getName() == name.getLocalName())
          return &(*gli);
      return 0;
    }
  else
    { //search imported namespaces
      for (size_t i = 0; i < importedSchemas_.size(); i++)
        {
          if ( importedSchemas_[i].ns == typens)
            {
              if(importedSchemas_[i].sParser )
		{
                  return importedSchemas_[i].sParser->getGroup(name);
		}
            }
        }
    }
  return 0;
}

AttributeGroup*
SchemaParser::getAttributeGroup(const Qname & name)
{
  std::string typens = name.getNamespace();
  if (typens.empty())
    typens = tnsUri_;
  if (typens== tnsUri_ || typens == Schema::SchemaUri)
    {

      //check if it is a global group
       for (AttributeGroupList::iterator agli = lAttributeGroups_.begin();
            agli!= lAttributeGroups_.end();
            agli++)
        if ((*agli)->getName() == name.getLocalName())
          return (*agli);
      return 0;
    }
  else
    { //search imported namespaces
      for (size_t i = 0; i < importedSchemas_.size(); i++)
        {
          if ( importedSchemas_[i].ns == typens)
            {
              if(importedSchemas_[i].sParser )
		{
                  return importedSchemas_[i].sParser->getAttributeGroup(name);
		}
            }
        }
    }
  return 0;
}

std::string
SchemaParser::getNamespace(void) const
{
  return tnsUri_;
}


const XSDType *
SchemaParser::getType(int id) const
{
  return (const XSDType *) typesTable_.getTypePtr(id);
}


const XSDType *
SchemaParser::getType(const Qname & type,bool checkImports ) 
{
  int id;
  Qname t=type;
  
  if((id=getTypeId(t,false))==0)
    return 0;
  else {
    const XSDType* pType = (const XSDType *) typesTable_.getTypePtr(id);
    if (!checkImports) {

      if(pType->getNamespace() != tnsUri_)
	return 0;

    }
    return pType;
   }
}


 const XSDType *
 SchemaParser::getType(int id, std::string &nameSpace)
 {
    const SchemaParser *sp = getImportedSchema(nameSpace);
    if (sp == NULL)
    {
      return 0;
    }
    else
    {
      return sp->getType(id);
    }
  }

  const SchemaParser *
    SchemaParser::getImportedSchema(std::string &nameSpace)
  {
    if (nameSpace.empty()|| nameSpace == tnsUri_ || nameSpace == Schema::SchemaUri)    
    {
      return this;
    }

    for (size_t i = 0; i < importedSchemas_.size(); i++) 
    {
      if ( importedSchemas_[i].ns == nameSpace) 
      {
        return importedSchemas_[i].sParser;
      }
    }
    return NULL;
  }

list < const XSDType *>*
SchemaParser::getAllTypes() const
{
  list < const XSDType *>*pLTypes = new list < const XSDType * >;
  for (int i = 0; i < getNumTypes(); i++)
    {
      const XSDType *pType = getType(i + Schema::XSD_ANYURI + 1);
      pLTypes->push_back(pType);
    }
  return pLTypes;
}


int
SchemaParser::getNumTypes() const
{
  return typesTable_.getNumTypes();
}


int
SchemaParser::getNumElements() const
{
  return lElems_.size();
}


int
SchemaParser::getNumAttributes() const
{
  return lAttributes_.size();
}

//To be deprecated
bool
SchemaParser::addImports(const std::vector<SchemaParser *> & schemaParsers)
{
  for (size_t i=0;i<schemaParsers.size() ;i++){
      
    if(schemaParsers[i]->getNamespace()!=tnsUri_){
	
      addImport(schemaParsers[i]);
    }
  }
  return true;
}

bool 
SchemaParser::addImport(SchemaParser *sp)
{
  //check if the namespace is added in the import list
  int i= checkImport(sp->getNamespace());
  //  std::cout<<"Copying imports to "<<sp->tnsUri_<<std::endl;
  //  sp->copyImports(this);
  if(i>=0) {
    importedSchemas_[i].sParser=sp;
    importedSchemas_[i].ns=sp->getNamespace();    
  }
  else {
    //if this was a new import increment
    ImportedSchema imp;
    imp.sParser=sp;
    imp.ns=sp->getNamespace();
    importedSchemas_.push_back(imp);
  }
  return true;
}

void
SchemaParser::copyImports(SchemaParser * sp)
{
  for(size_t i=0;i<importedSchemas_.size();i++) {
    
    if (importedSchemas_[i].sParser) 
      sp->addImport(importedSchemas_[i].sParser);
  }
}

int 
SchemaParser::checkImport(std::string nsp)const
{
  for(size_t i=0;i<importedSchemas_.size();i++)
    {
      if(importedSchemas_[i].ns==nsp)
        return i;
    }
  return -1;
}

bool 
SchemaParser::addImport(std::string ns,
                        std::string location)
{

  int i= checkImport(ns);
  if(i==-1) {
    ImportedSchema imp;
    imp.sParser=0;
    imp.ns=ns;
    importedSchemas_.push_back(imp);
    i =importedSchemas_.size()-1;
  }else {
    return true;
  }

  if(location.empty())
    return true;
  std::string xsdFile;
  if(XmlUtils::fetchUri(location,xsdFile))
    {
      /*
       * If the schema definition was retrieved successfully 
       * process it and add it to list of imported schemas
       */
      SchemaParser *sp = new SchemaParser(xsdFile,ns);
      sp->setUri(uri_);
      if(sp->parseSchemaTag())
        {
          importedSchemas_[i].sParser=sp;
          return true;
        }
      else return false;
    }
  else return false;

}


void SchemaParser::error(std::string mesg, int level)
{
  
  if (level == 0) {
    
    SchemaParserException spe(mesg + "\nFatal Error in SchemaParser\n");
    spe.line = xParser_->getLineNumber();
    spe.col = xParser_->getColumnNumber();
    throw spe;
  }

  else if (level_ >=1 && level == 1){

    logFile_ << "Error @" << xParser_->
      getLineNumber() << ":" << xParser_->
      getColumnNumber() << XmlUtils::dbsp << mesg << endl;
  }
  else if (level_ >= 2 && level == 2) {

    logFile_ << "Alert @" << xParser_->
      getLineNumber() << ":" << xParser_->
      getColumnNumber() << XmlUtils::dbsp << mesg << endl;

  }
}


int
SchemaParser::getBasicContentType(int typeId)const
{
  const XSDType *pType = getType(typeId);
  int id = typeId;
  if (pType != 0) {
    
    /* 
       It could be a complex type with
       simple content or a schema defined simpleType
    */
    if (pType->isSimple() == false){

      const ComplexType * cType= static_cast<const ComplexType*> (pType);

      if(cType->getContentModel()==Schema::Simple){
	
	id = cType->getContentType();
      }
      else {
	
        return Schema::XSD_INVALID;
      }
    }
    else{
      
      id = (static_cast<const SimpleType *>(pType))->getBaseTypeId();
    }
    id = getBasicContentType(id);
  }
  return id;
}

std::string
SchemaParser::getTypeName(Schema::Type t)const
{
  if (isBasicType(t)){
    return typesTable_.getAtomicTypeName(t);
  }
  else {
    const XSDType * pType = (const XSDType *) typesTable_.getTypePtr(t);
    if (pType)
      return pType->getName();
  }
  return "";
}


//handle soap arrays .this is really a special case.more like a hack
bool
SchemaParser::makeListFromSoapArray (ComplexType * ct)
{
  const XSDType * baseType=getType(ct->getBaseTypeId());
  if (baseType) {
    if(baseType->getNamespace()== "http://schemas.xmlsoap.org/soap/encoding/" && 
       baseType->getName()=="Array"){
      
      const Attribute* a = ct->getAttribute("arrayType");
      if (!a)
	return false;
      
      std::string array = a->defaultVal();
      Qname q(array);
      array = q.getLocalName();
      while (array[array.length()-1] ==']' && 
	     array[array.length()-2] =='[')
	array = array.substr(0,array.length()-2);

      std::string arrayNs = xParser_->getNamespace(q.getPrefix());
      q = Qname(array);
      q.setNamespace(arrayNs);
      Schema::Type t = (Schema::Type)getTypeId(q,true);
          Element e("*",tnsUri_,tnsUri_,t,0,UNBOUNDED);
      if (ct->getContents() == 0){
	ContentModel * cm = new ContentModel(Schema::Sequence);
	ct->setContents(cm);
      }
      ct->getContents()->addElement(e);
      return true;
    }
  }
  return false;
}
}
