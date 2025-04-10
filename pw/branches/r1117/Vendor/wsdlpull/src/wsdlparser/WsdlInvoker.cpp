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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef  WITH_CURL
#include <curl/curl.h>
#endif 

#include <iostream>
using namespace std;

#include "wsdlparser/WsdlInvoker.h"



#ifdef WITH_CURL
size_t storeResults(void * buf, size_t sz, size_t nmemb, void* userdata);
#endif

namespace WsdlPull {

WsdlInvoker::WsdlInvoker()
  :wParser_(0),
   ourParser_(0),
   xmlStream_(0),
   soap_(0),
   soapheaders_(false),
   hPartId_(-1),
   soapstr_(0),
   status_(false),
   serializeMode_(false),
   verbose_(false),
   dontPost_(false),
   oHeaders_(0),
   op_(0),
   n_(0),
   iHeaders_(0),
   messageType_(WsdlPull::Input),
   bAuth(false),
   ctx(0),
   m_buildXmlTree( false),
   m_xmlTreeProduced( false)
{
}

WsdlInvoker::WsdlInvoker(std::istream &input, const std::string &schemaPath) 
  :wParser_(0),
   ourParser_(0),
   xmlStream_(0),
   soap_(0),
   soapheaders_(false),
   hPartId_(-1),
   soapstr_(0),
   status_(false),
   serializeMode_(false),
   verbose_(false),
   dontPost_(false),
   op_(0),
   n_(0),
   iHeaders_(0),
   messageType_(WsdlPull::Input),
   bAuth(false),
   ctx(0),
   m_buildXmlTree( false),
   m_xmlTreeProduced( false)
{
  try{
    wParser_ = new WsdlParser(input,logger_, schemaPath);
    ourParser_= wParser_;
    if (wParser_){
      //parse the web service
      while (wParser_->getNextElement () != WsdlParser::END);
      if (wParser_->status()){
        
        status_=true;
        init(wParser_);
      }
    }
  }
  catch (WsdlException we)
  {
    logger_<<"An exception  occurred at "<<we.line   
    <<":"<<we.col<<std::endl;
    logger_<<we.description<<std::endl;
    status_ =false;
  }
  catch (SchemaParserException spe)
  {
    logger_<<"An exception occurred at "<<spe.line
    <<":"<<spe.col<<std::endl;
    logger_<<spe.description<<std::endl;
    status_ =false;
  }
  catch (XmlPullParserException xpe)
  {
    logger_<<"An exception occurred at "<<xpe.line
    <<":"<<xpe.col<<std::endl;
    logger_<<xpe.description<<std::endl;
    status_= false;
  }
}

WsdlInvoker::WsdlInvoker(const std::string & url, const std::string & schemaPath)
   :wParser_(0),
    ourParser_(0),
    xmlStream_(0),
    soap_(0),
    soapheaders_(false),
    hPartId_(-1),
    soapstr_(0),
    status_(false),
    serializeMode_(false),
    verbose_(false),
    dontPost_(false),
    op_(0),
    n_(0),
    iHeaders_(0),
    messageType_(WsdlPull::Input),
    bAuth(false),
    ctx(0),
    m_buildXmlTree( false),
    m_xmlTreeProduced( false)
{
  parseWsdl(url, schemaPath);
}


void
WsdlInvoker::parseWsdl(const std::string & url, const std::string & schemaPath)
{
  try{
    wParser_ = new WsdlParser(url,logger_, schemaPath);
    ourParser_= wParser_;
    if (wParser_){
      //parse the web service
      while (wParser_->getNextElement () != WsdlParser::END);
      if (wParser_->status()){
      
	status_=true;
	init(wParser_);
      }
    }
  }
    catch (WsdlException we)
      {
       logger_<<"An exception  occurred at "<<we.line   
  	     <<":"<<we.col<<std::endl;
        logger_<<we.description<<std::endl;
        status_ =false;
      }
    catch (SchemaParserException spe)
      {
       logger_<<"An exception occurred at "<<spe.line
  	     <<":"<<spe.col<<std::endl;
        logger_<<spe.description<<std::endl;
        status_ =false;
      }
    catch (XmlPullParserException xpe)
      {
       logger_<<"An exception occurred at "<<xpe.line
  	     <<":"<<xpe.col<<std::endl;
       logger_<<xpe.description<<std::endl;
       status_= false;
      }
}

bool
WsdlInvoker::init(WsdlParser* parser)
{
  try{
    wParser_ = parser;
    status_ = wParser_->status();

    if (status_){
      
      PortType::cPortTypeIterator p1,p2;
      wParser_->getPortTypes(p1,p2);
      int i=0;

      while(p1!=p2){
    
	Operation::cOpIterator op1,op2;
	(*p1)->getOperations(op1,op2);
	bool bn = (*p1)->binding(Soap::soapBindingUri11) || (*p1)->binding(Soap::soapBindingUri12) ; 
	//if neither SOAP1.1 or SOAP1.2 bindings are available for a port type skip it
	///eventually we should add a test to check for all supported bindings in the invoker
	if (!bn){
	  p1++;
	  continue;
	}

	while(op1!=op2){
	
	  opMap_[(*op1)->getName()]=*op1;
	  op1++; 
	  i++;
	}
	p1++;
      }
    }
  }
  catch (WsdlException we)
    {
      logger_<<"A WSDL exception occurred at"<<we.line
	     <<":"<<we.col<<std::endl;
      logger_<<we.description<<std::endl;
      status_ =false;
    }
  catch (SchemaParserException spe)
    {
      logger_<<"A Schema Parser exception occurred at "<<spe.line
	     <<":"<<spe.col<<std::endl;
      logger_<<spe.description<<std::endl;
      status_ =false;
    }
  catch (XmlPullParserException xpe)
    {
      logger_<<"An Xml Parsing exception occurred at row:col "<<xpe.line
	     <<":"<<xpe.col<<std::endl;
      logger_<<xpe.description<<std::endl;
      status_ =false;
    }
  return status_;
}
 
int
WsdlInvoker::getOperations(std::vector<std::string> & operations)
{
  int i = 0;
  for(
  std::map<std::string,const Operation*>::iterator it =
    opMap_.begin();
  it != opMap_.end();
  it++,i++){

    operations.push_back(it->first);
  }
  return i;
}

std::string
WsdlInvoker::getDocumentation()
{
  std::stringstream result;
  result << wParser_->getDocumentation();
  return result.str();
}
   
std::string
WsdlInvoker::getOpDocumentation(const std::string & n)
{
  
  std::map<std::string,const Operation*>::iterator it =
    opMap_.find(n);
  
  if (it != opMap_.end()){
    
    return  it->second->getDocumentation();
  }
  return "";
}

bool
WsdlInvoker::setOperation(const std::string & opname,
			  WsdlPull::MessageType mType)
{
  reset();
  messageType_ = mType;
   std::map<std::string,const Operation*>::iterator it =
    opMap_.find(opname);

  if (it != opMap_.end()){
    
    op_ = it->second;

    getOperationDetails(op_);
    if (!status_)
      return false;
    
    if (soapheaders_){
      serializeHeader();
    }
    serialize();
    n_ = iHeaders_;
    return status_;
  }
  else{
    return false;
  }
}

std::string
WsdlInvoker::getServiceEndPoint(const std::string & opname) 
{

  reset();
  location_="";
  std::map<std::string,const Operation*>::iterator it =
    opMap_.find(opname);

  if (it != opMap_.end()){
    
    const Operation* op = it->second;

    getOperationDetails(op);
    reset();
  }
  return location_;
}

void
WsdlInvoker::getOperationDetails(const Operation* op) 
{

  const Binding * bnSoap = 0;
  bnSoap = op->portType()->binding(Soap::soapBindingUri11);
  if (bnSoap) {

    soap_ = static_cast<Soap*> (wParser_->getExtensibilityHandler(Soap::soapBindingUri11));
  }else {
    
    bnSoap = op->portType()->binding(Soap::soapBindingUri12);
    soap_ = static_cast<Soap*> (wParser_->getExtensibilityHandler(Soap::soapBindingUri12));

  }
  
  ///get various soap properties
  soap_->getServiceLocation (bnSoap->getServiceExtId (),location_);
  style_ = soap_->getStyle();

  if (location_.empty()){

    logger_<<"No service location specified for SOAP binding "<<bnSoap->getName()<<std::endl;
    status_ = false;
    return;
  }
  //get the soap:operation's SOAPAction and style
  const int *bindings = 0;
  int opIndex  = bnSoap->getOperationIndex(op->getName());
  bnSoap->getOpBinding (opIndex, bindings);
  int soapOpBindingId = bindings[0];
  //operation's style over rides 
  soap_->getSoapOperationInfo (soapOpBindingId, action_, style_);

  //get the soap:body namespace and use attributes
  int nBindings=bnSoap->getInputBinding(opIndex,bindings);
  //get the body and header
  for (int x=0;x<nBindings;x++){
    if (soap_->isSoapBody(bindings[x])){

      soap_->getSoapBodyInfo(bindings[x],nsp_,use_,encodingStyle_);
    }
    if (soap_->isSoapHeader(bindings[x]))
      soapheaders_ = true;

  }
    
  if (nsp_.empty()){

    nsp_ = wParser_->getNamespace();
  }
}

void
WsdlInvoker::serializeHeader()
{
  //create input  holders for the soap header,use the same list
  //but just remember where the header's params end
  std::string name;
  
  int hPartId;
  const Message* hMessage;//message corresponding to soap header

  const Binding * bnSoap = op_->portType()->binding(soap_->getNamespace());
  const int *bindings = 0;
  int opIndex  = op_->portType()->getOperationIndex(op_->getName());
  int nBindings=bnSoap->getInputBinding(opIndex,bindings);
  //get the body and header
  for (int x=0;x<nBindings;x++){
    
    if (soap_->isSoapHeader(bindings[x])){
      
      soap_->getSoapHeaderInfo(bindings[x],hnsp_,hPartId,hMessage);  

  
      Schema::Type pType =Schema::XSD_INVALID;
      if (hMessage->getPartRefType(hPartId)==Part::Elem){
	
	name = hMessage->getMessagePart(hPartId)->element()->getName();
	pType = (Schema::Type)hMessage->getMessagePart(hPartId)->element()->getType();
      }
      else {
	
	name = hMessage->getPartName(hPartId);
	pType = (Schema::Type)hMessage->getMessagePart(hPartId)->type();
      }
      std::vector<std::string> parents;
      parents.push_back(name);
      serializeType(pType,
		    name,
		    wParser_->getSchemaParser(hMessage->getPartContentSchemaId(hPartId)),
		    1,1,parents,hnsp_,true);
    }
  }
  iHeaders_ = elems_.size();

}

//this method extracts the  atomic types needed for the web service
//it recursively calls serializeType for all the input or output types expected
//This method works in 2 modes.In the serializeMode_ == false it creates holders
//for the parameter values.In serializeMode_ == true it uses the inputs from the holders 
//to generate the SOAP XML message
void
WsdlInvoker::serialize()
{
  const Message * m = op_->getMessage(messageType_);
  if (!m)
    return;
  
  for (int i = 0 ;i<m->getNumParts();i++){
      
    Part::PartRefType prt = m->getPartRefType(i);
    const Part * p = m->getMessagePart(i);
    const SchemaParser * sParser = wParser_->getSchemaParser(p->schemaId());
    const std::string nsp = sParser->getNamespace();
    
    std::vector<std::string> parents;
    if (prt == Part::Elem){
      
      const Element * e = p->element();
      if (e->getTypeNamespace() != sParser->getNamespace()) {
	sParser = wParser_->getSchemaParser(e->getTypeNamespace());
      }
      //the above can happen when the actual type/element is defined in someother namespace via imports
      serializeType((Schema::Type)e->getType(),e->getName(),sParser,1,1,parents,e->getTypeNamespace(),true);
    }
    else{
      
      serializeType((Schema::Type)p->type(),p->name(),sParser,1,1,parents,nsp,true);
    }
  }
}

void
WsdlInvoker::serializeType(Schema::Type typeId,
			   const std::string &tag,
			   const SchemaParser * sParser,
                           int minimum,
                           int maximum,
			   std::vector<std::string> parents,
			   const std::string nsp,
			   bool isRoot)
{
  std::string t = tag;
  if (t == "*")
    t = "item";


  //for( std::vector<std::string>::iterator it=parents.begin();it!=parents.end();it++) std::cout<<*it; 

  const XSDType * pType = sParser->getType(typeId);

  for (size_t z=0;z<avoidrecurse_.size();z++){
    //if there is a recursive type reference return to avoid infinite loop
    if (avoidrecurse_[z] == pType) 
      return;
    
  }
  avoidrecurse_.push_back(pType);
  
  if ( pType== 0 ||
       pType->isSimple() ||
       pType->getContentModel() == Schema::Simple){
    //simple types
    if (serializeMode_ == false){
      
      parents.push_back(tag);
      Parameter p(typeId,t,minimum,maximum,sParser,parents);
      elems_.push_back(p);

#ifdef LOGGING

      std::cout<<"Adding input type "<<tag<<XmlUtils::dbsp
               <<sParser->getTypeName(typeId)<<XmlUtils::dbsp;
      std::cout<<sParser->getNamespace()<<std::endl;
#endif
    }
    else{
      //generate the xml
      serializeParam(n_++,t,sParser,nsp,isRoot);
    }
  }
  else{

    if (serializeMode_){
      
      if (style_ == Soap::DOC ){
    

	if (sParser->getElementQualified()) {
	  
	  xmlStream_->startTag("",t);
	  if (isRoot)
	    xmlStream_->attribute("","xmlns",nsp);
	}
	else {
	  
	    if (isRoot) {
	      xmlStream_->setPrefix(getPrefix(nsp),nsp);  
	      xmlStream_->startTag(nsp,t);
	    } 
	    else {
	      xmlStream_->startTag("",t);
	    }
	}
      }
      else{
	
	xmlStream_->startTag("",t);

	//fix for sending SOAP arrays.add the soap arrayType attribute
	//works only for 1-D arrays
	const ComplexType* ct = static_cast<const ComplexType*>(pType);
	if(isSoapArray(ct,sParser)){

	  std::string arrayName = ct->getName();
	  arrayName = "ns:"+arrayName+"[1]";
	  xmlStream_->attribute(soap_->getEncodingUri(),"arrayType",arrayName);
	}
      }
    }
    else {
      
      //complex types with multiple occurences


      //      parents.push_back(tag);
      //      Parameter p(typeId,t,minimum,maximum,sParser,parents);
      //      elems_.push_back(p);       TODO
      
    }
    
    
    const ComplexType * ct =
      static_cast<const ComplexType*>(pType);
    
    //complex types handling
    if (ct->getNumAttributes() > 0) {
      
      for (int i = 0; i < ct->getNumAttributes(); i++) {
	  
	const Attribute*at = ct->getAttribute(i);
	/*
	 * Check for the correctness of each attribute
	 */
	if (at->isRequired()){
	
	  if (serializeMode_ == false){

	    std::vector<std::string> attparents(parents);
	    attparents.push_back(tag);
	    attparents.push_back("#" + at->getName() + "#");
	    Parameter p((Schema::Type)at->getType(),at->getName(),elems_.size(),0,sParser,
	                attparents);
	    elems_.push_back(p);
	  }
	  else{
	    //generate the xml
	    
	    xmlStream_->attribute(sParser->getNamespace(),at->getName(),elems_[n_++].data_[0]);
	  }
	}
	else
	  continue;
      }
    }
  
    if (ct->getContentModel() == Schema::Simple) {

      if (serializeMode_ == false){
      
	parents.push_back(tag);
        Parameter p((Schema::Type)ct->getContentType(),tag,minimum,maximum,sParser,parents);
	elems_.push_back(p);
      }
      else{
	//generate the xml
	serializeParam(n_++,t,sParser,nsp,isRoot);
      }
    }
    else{
      
      const XSDType * baseType=sParser->getType(ct->getBaseTypeId());
      if (baseType && !baseType->isSimple()){

	const ComplexType * cType=static_cast<const ComplexType*>(baseType);
	ContentModel * bCm = cType->getContents();
	if (bCm){
	  if (!isSoapArray(ct,sParser)){
	    //hack ..for soap arrays base type is SOAP-ENC:Array, but dont serialize it	    
	    parents.push_back(tag);
	    serializeContentModel(bCm,sParser,parents);
	  }
	}
      }
      ContentModel* cm=ct->getContents();
      if(cm){

	parents.push_back(tag);
	serializeContentModel(cm,sParser,parents);
      }
    }

    if (serializeMode_){

      if (style_ == Soap::DOC ){
    
	if (sParser->getElementQualified()) {
	    
	  xmlStream_->endTag("",t);
	}
	else {
	  
	  if (isRoot) {
	    
	    xmlStream_->endTag(nsp,t);
	  } 
	  else {
	      xmlStream_->endTag("",t);
	  }
	}
      }
      else{
	
	xmlStream_->endTag("",t);
      }
    }
  }
  avoidrecurse_.pop_back();
}

void
WsdlInvoker::serializeContentModel(ContentModel *cm,
				   const SchemaParser *sParser,
				   std::vector<std::string> parents)
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


	    const SchemaParser* s1Parser = sParser;
	    bool isRoot = false;
	    std::string nsp;
	    Schema::Type t=(Schema::Type)ci->first.e->getType();
	    
	    if (!ci->first.e->getTypeNamespace().empty() &&
		sParser->isImported(ci->first.e->getTypeNamespace()) &&
                sParser->getNamespace() != ci->first.e->getTypeNamespace()) {
	
	      //here the type of the element is defined in another imported schemaparser
	      //so try to get the pointer.
	      if ( !sParser->isBasicType(t)){ 
	          t = (Schema::Type)sParser->getType(t)->getTypeId();
	          sParser = sParser->getImportedSchemaParser(ci->first.e->getTypeNamespace());
	      }
	      if(ci->first.e->getNamespace() != s1Parser->getNamespace()){
		nsp = ci->first.e->getNamespace();
		isRoot = true ;// the element is from another namespace so need to qualify it
	      }
	    }
	

	    if ((ci->first.e->getMin() == 0) &&  //nillable check for complex types
		serializeMode_ && !sParser->isBasicType(ci->first.e->getType()) && isSubTreeNil() ) {
	      
	      serializeParam(-1,ci->first.e->getName(),sParser,nsp,isRoot);
	      
	      //if an elements contents are nil and the element is nillable then nil the element

	    }
	    else {
	    
	      serializeType(t,
			    ci->first.e->getName(),
			    sParser,
			    ci->first.e->getMin(),
			    ci->first.e->getMax(),
			    parents,
			    nsp,isRoot);
	    }
	    sParser = s1Parser;
	  }
	  else if (ci->second==ContentModel::Container) {
	    
	    //nested xsd:sequence inside choice..nested content models
	    serializeContentModel(ci->first.c,
				  sParser,
				  parents);
	      
	  }
	  else if (ci->second==ContentModel::ParticleGroup){
	    
	    //xsd:group inside 
	    serializeContentModel(ci->first.g->getContents(),
				  sParser,
				  parents);
	  }
	}
	break;
      }
    }
}


void
WsdlInvoker::serializeParam(int n,const std::string & tag,
			    const SchemaParser * sParser,
			    const std::string nsp,
			    bool isRoot)
{

  std::string t=tag;
  if (tag=="*")
    t="item";
   
  if (n == -1 ) {
    xmlStream_->startTag("",t);
    xmlStream_->endTag("",t);
    return;//for nillable element ,just generate an empty tag
  }
 
  for (int i = 0 ;i<elems_[n].n_;i++){

    if (style_ == Soap::DOC){

      if (!isRoot)
	xmlStream_->startTag("",t);
      
      else {
	
	if (!nsp.empty())
	  xmlStream_->setPrefix(getPrefix(nsp),nsp);

	xmlStream_->startTag(nsp,t);

      }
    }
    else{
      
	xmlStream_->startTag("",t);
	
	//xsi::type is needed for many SOAP servers
	if (sParser->isBasicType(elems_[n].type_) && 
	    use_ == Soap::ENCODED){
	  
	  xmlStream_->attribute(Schema::SchemaInstaceUri,
				"type",
				"xsd:"+sParser->getTypeName(elems_[n].type_));
	}
    }
    
    xmlStream_->text(elems_[n].data_[i]);
    if (style_ == Soap::DOC && isRoot)
      xmlStream_->endTag(nsp,t);
    else
      xmlStream_->endTag("",t);
  }
}


bool
WsdlInvoker::setInputValue(const int param,void** values,unsigned int occurs)
{

  if (occurs < elems_[param].min_ ||
      occurs > elems_[param].max_)
    return false;

  SchemaValidator *sv = new SchemaValidator (elems_[param].sParser_);
  for (unsigned int i = 0 ;i < occurs ;i++){
      
    TypeContainer * tc = sv->validate(values[i],
				      elems_[param].type_);
    if (!tc->isValueValid()){
	
      return false;
    }
    std::ostringstream oss;
    tc->print(oss);
    elems_[param].data_.push_back(oss.str());
    delete tc;
  }
  delete sv;
  
  elems_[param].n_ = occurs;
  return true;
}

bool
WsdlInvoker::setInputValue(const int param,std::vector<std::string> values)
{


  if (values.size() < elems_[param].min_ ||
      values.size() > elems_[param].max_)
    return false;

  SchemaValidator *sv = new SchemaValidator (elems_[param].sParser_);
  
  for (size_t i = 0 ;i < values.size() ;i++){
      
    TypeContainer * tc = sv->validate(values[i],
				      elems_[param].type_);
    if (!tc->isValueValid()){
	
      return false;
    }
    elems_[param].data_.push_back(values[i]);
    delete tc;
  }
  delete sv;
  
  elems_[param].n_ = values.size();
  return true;
}

bool
WsdlInvoker::setInputValue(const int param,std::string val)
{

  const SchemaParser* sParser = elems_[param].sParser_;
  SchemaValidator *sv = new SchemaValidator (sParser);
  Schema::Type t = elems_[param].type_;
  const XSDType * pType = sParser->getType(t);
  if (pType && !pType->isSimple()){

    if (pType->getContentModel() != Schema::Simple)
      return false;

    const ComplexType * ct = static_cast<const ComplexType*>(pType);
    t = (Schema::Type)ct->getContentType();
  }
  
  TypeContainer * tc = sv->validate(val,t);
  if (!(tc && tc->isValueValid())){
	
    return false;
  }
  if (elems_[param].data_.size() == 0)
    elems_[param].data_.push_back(val);
  else
    elems_[param].data_[0]=val;

  delete tc;
    
  delete sv;
  
  elems_[param].n_ = 1;
  return true;
}



bool
WsdlInvoker::setInputValue(const int param,void* val)
{

  const SchemaParser*  sParser = elems_[param].sParser_;
  SchemaValidator *sv = new SchemaValidator (sParser);
  Schema::Type t = elems_[param].type_;
  const XSDType * pType = sParser->getType(t);
  if (pType && !pType->isSimple()){

    if (pType->getContentModel() != Schema::Simple)
      return false;

    const ComplexType * ct = static_cast<const ComplexType*>(pType);
    t = (Schema::Type)ct->getContentType();
  }

  TypeContainer * tc = sv->validate(val,t);
  if (!(tc && tc->isValueValid())){
	
    return false;
  }
  std::ostringstream oss;
  tc->print(oss);
  if (elems_[param].data_.size() == 0)
    elems_[param].data_.push_back(oss.str());
  else
    elems_[param].data_[0]=oss.str();
  delete tc;
  delete sv;
  elems_[param].n_ = 1;
  return true;
}

bool
WsdlInvoker::setValue(const std::string & param,void* val)
{
  for (size_t s = 0;s<elems_.size();s++){
    
    if (elems_[s].tag_ == param)
      return setInputValue(s,val);
  }
  return false;
}

bool
WsdlInvoker::setValue(const std::string & param,void** values,unsigned int occur)
{

  for (size_t s = 0;s<elems_.size();s++){
    
    if (elems_[s].tag_ == param)
      return setInputValue(s,values,occur);
  }
  return false;
}
 
bool
WsdlInvoker::setValue(const std::string & param,std::string val)
{
  for (size_t s = 0;s<elems_.size();s++){
    
    if (elems_[s].tag_ == param)
      return setInputValue(s,val);
  }
  return false;
}

bool
WsdlInvoker::setValue(const std::string & param,std::vector<std::string> values)
{
  for (size_t s = 0;s<elems_.size();s++){
    
    if (elems_[s].tag_ == param)
      return setInputValue(s,values);
  }
  return false;
}


std::string
WsdlInvoker::getSoapMessage(){

  dontPost_ = true;
  invoke();
  dontPost_ = false;
  return soapstr_->str();
}

std::string
WsdlInvoker::getXMLResponse(){
 
  return strResults_;
}


bool
WsdlInvoker::invoke(long timeout,bool processResponse)
{

try{
    
  if (xmlStream_){
    
    delete xmlStream_;
  }
  if (soapstr_){
    
    delete soapstr_;
  }
  if (!strResults_.empty()){
    strResults_.clear();
  }


  for (size_t x = 0;x<outputs_.size();x++)
    delete outputs_[x].second;

  outputs_.clear();

  soapstr_ = new std::ostringstream();
  xmlStream_ = new XmlSerializer(*soapstr_);

  serializeMode_ = true;

  xmlStream_->startDocument("UTF-8",false);
  xmlStream_->setPrefix("SOAP-ENV",soap_->getEnvelopeUri());
  xmlStream_->setPrefix("SOAP-ENC",soap_->getEncodingUri());
  xmlStream_->setPrefix("xsd",Schema::SchemaUri);
  xmlStream_->setPrefix("xsi",Schema::SchemaInstaceUri);
  xmlStream_->setPrefix(getPrefix(nsp_),nsp_);
  xmlStream_->startTag(soap_->getEnvelopeUri(),"Envelope");
  
  if (style_ == Soap::RPC) {
    
    xmlStream_->attribute(soap_->getEnvelopeUri(),
			  "encodingStyle",
			  soap_->getEncodingUri());
  }

  n_ = 0;
  if (soapheaders_){
    xmlStream_->startTag(soap_->getEnvelopeUri(),"Header");
    serializeHeader();
    xmlStream_->endTag(soap_->getEnvelopeUri(),"Header");
  }

  xmlStream_->startTag(soap_->getEnvelopeUri(),"Body");
  if (style_ == Soap::RPC){
    
    xmlStream_->startTag(nsp_,op_->getName());
  }

  serialize();
  if (style_ == Soap::RPC){
    xmlStream_->endTag(nsp_,op_->getName());
  }

  xmlStream_->endTag(soap_->getEnvelopeUri(),"Body");
  xmlStream_->endTag(soap_->getEnvelopeUri(),"Envelope");
  xmlStream_->flush();
  


  //test
  //  status_ = true;
  // if(processResponse)
  //   processResults();
  // return status_;
  //test

  if (dontPost_)
    return true;

  post(timeout);
  if (!strResults_.empty()){

    if (processResponse)
      processResults();

    m_xmlTreeProduced = false;

    if( m_buildXmlTree == true) {

      std::istringstream l_respstr( strResults_);
      //std::ifstream l_respstr( "r.xml");//test

      XmlPullParser l_xpp( l_respstr);
      l_xpp.setFeature( FEATURE_PROCESS_NAMESPACES, true);
      l_xpp.require( XmlPullParser::START_DOCUMENT, "", "");

      m_xmlDoc.clear();

      buildXmlTree( l_xpp, m_xmlDoc.getRootNode());
      m_xmlTreeProduced = true;
    }
    
    if (status_)
      return true;
  }
  else{
    
    if (!op_->getMessage(WsdlPull::Output))
      return true; //for web services which have no output

    logger_<<"Couldnt connect to "<<location_;
  }
  return false;
}
catch (WsdlException we)
  {
    logger_<<"A WSDL exception occurred at"<<we.line
	   <<":"<<we.col<<std::endl;
    logger_<<we.description<<std::endl;
    return false;
  }
catch (SchemaParserException spe)
  {
    logger_<<"A Schema Parser exception occurred at "<<spe.line
	   <<":"<<spe.col<<std::endl;
    logger_<<spe.description<<std::endl;
    return false;
  }
catch (XmlPullParserException xpe)
  {
    logger_<<"An Xml Parsing exception occurred at row:col "<<xpe.line
	   <<":"<<xpe.col<<std::endl;
    logger_<<xpe.description<<std::endl;
    return false;
  }
}

int
WsdlInvoker::getNextInput(std::string & param ,Schema::Type & type,int & minimum,int & maximum)
{
  std::vector<std::string> parents;
  return getNextInput(param, type, minimum, maximum, parents);
}

int
WsdlInvoker::getNextInput(std::string & param ,Schema::Type & type,int & minimum,int & maximum,
			  std::vector<std::string> & parents)
{
  if (n_ < elems_.size()){
    
    param = elems_[n_].tag_;
    type = elems_[n_].type_;
    minimum = elems_[n_].min_;
    parents = elems_[n_].parents_;
    maximum = elems_[n_].max_;
    return n_++;
  }
  else{
    return -1;
  }
}

int
WsdlInvoker::getNextHeaderInput(std::string & param ,Schema::Type & type,
				int & minimum,int & maximum)
{

  std::vector<std::string> parents;
  return getNextHeaderInput(param,type,minimum,maximum,parents);
}

int
WsdlInvoker::getNextHeaderInput(std::string & param ,Schema::Type & type,
				int & minimum,int & maximum,
				std::vector<std::string> & parents)
{
  static int h = 0;
  if (h<iHeaders_){
    param = elems_[h].tag_;
    type = elems_[h].type_;
    minimum = elems_[h].min_;
    maximum = elems_[h].max_;
    parents = elems_[h].parents_;
    return h++;
  }
  else{
    h = 0;
    return -1;
  }
}

void
WsdlInvoker::processResults()
{
  XmlPullParser* xpp = 0;
  try{

    const Message* m = op_->getMessage(WsdlPull::Output);
    std::istringstream respstr(strResults_);
    //std::ifstream respstr("response.xml");//test
    xpp = new XmlPullParser(respstr);
    xpp->setFeature (FEATURE_PROCESS_NAMESPACES, true);
    xpp->require (XmlPullParser::START_DOCUMENT, "", "");

    while (status_ && 
	   xpp->getEventType () != XmlPullParser::END_DOCUMENT) {

      if (xpp->getEventType () == XmlPullParser::END_DOCUMENT)
	break;
      
      if (xpp->getEventType () == XmlPullParser::END_TAG &&
	  xpp->getName() == "Envelope" &&
	  xpp->getNamespace() == soap_->getEnvelopeUri())
	break;
	

      xpp->nextTag();
      Qname elemName (xpp->getName ());
      elemName.setNamespace(xpp->getNamespace());
      
      if (elemName.getNamespace() == soap_->getEnvelopeUri()){
	
	if (elemName.getLocalName() == "Fault"){
	  processFault(xpp);
	  status_ = false;
	  delete xpp;
	  return;
	} 
	else if (elemName.getLocalName() == "Header"){

	  processHeader(xpp);
	}
        else if (elemName.getLocalName() == "Body"){

	  xpp->nextTag();
	  processBody(m,xpp);
	}
      }
    }
    delete xpp;
    n_ = oHeaders_;
  }
  catch (WsdlException we)
    {

      logger_<<"A WSDL exception occurred while parsing the response at line "<<we.line
	     <<":"<<we.col<<std::endl;
      logger_<<we.description<<std::endl;
      status_ =false;
      if (xpp) delete xpp;
    }
  catch (SchemaParserException spe)
    {
      logger_<<"A Schema Parser exception occurred while parsing the response at line "<<spe.line
	     <<":"<<spe.col<<std::endl;
      logger_<<spe.description<<std::endl;
      status_ =false;
      if (xpp) delete xpp;
    }
  catch (XmlPullParserException xpe)
    {
      logger_<<"An Xml Parsing exception occurred while parsing the response at line "<<xpe.line
	     <<":"<<xpe.col<<std::endl;
      logger_<<xpe.description<<std::endl;
      status_ =false;
      if (xpp) delete xpp;
    }
  return;
}

WsdlInvoker::~WsdlInvoker()
{
  reset();
  if (ourParser_){  
      delete ourParser_;
  }
  if (xmlStream_){
    
    delete xmlStream_;
  }
  if (soapstr_){
    
    delete soapstr_;
  }

#ifdef WITH_CURL
  if(ctx) {
        curl_easy_cleanup(ctx) ;
  }
#endif  
}

void
WsdlInvoker::reset()
{
  n_ =  iHeaders_ = oHeaders_ = 0;
  elems_.clear();

  for (size_t x = 0;x<outputs_.size();x++)
    delete outputs_[x].second;

  outputs_.clear();
  serializeMode_ = false;



}

bool 
WsdlInvoker::getNextOutput(std::string & name,TypeContainer * & tc)
{
  if (status_ && n_ < outputs_.size()){
    
    name = outputs_[n_].first;
    tc = outputs_[n_].second;
    n_++;
    return true;
  }
  n_ = oHeaders_;
  return false;
}


TypeContainer*
WsdlInvoker::getOutput(const std::string  & name)
{
  for (unsigned int i = 0 ;status_ && i <outputs_.size();i++){

    if ( name == outputs_[i].first)
      return outputs_[i].second;
  }
  return 0;
}

bool
WsdlInvoker::getNextHeaderOutput(std::string & name,TypeContainer*& tc)
{
  static int j = 0;
  if(j<oHeaders_){
    name = outputs_[j].first;
    tc = outputs_[j].second;
    j++;
    return true;
  }
  else{
    j = 0;
    return false;
  }
}

void * 
WsdlInvoker::getValue(const std::string  & name ,Schema::Type & t)
{
  for (unsigned int i = 0 ;status_ && i <outputs_.size();i++){

    if (outputs_[i].second!=0){
      outputs_[i].second->rewind();
      void * tmp= outputs_[i].second->getValue(name,t);
      if (tmp)
	return tmp;
    }
  }
  return 0;
}

//a complete xpath lookup 
std::string
WsdlInvoker::getAsStringFromXPath( const std::string &p_xpath,
				   size_t p_index,
				   std::vector<std::string> *p_array) 
{
  //if( status_) {//test
  if( status_ && !strResults_.empty()){

    if( p_xpath.empty())
      return "";

    if( m_xmlTreeProduced == true) {

      std::vector< std::string> l_results;
      m_xmlDoc.xpath( p_xpath, l_results, p_index);

      if( p_array == NULL) {

	if( l_results.empty() == false)
	  return l_results[ 0];

	return "";
      }

      *p_array = l_results;
      return "";
    }
    
    //get all the nodes in the expression into an array
    std::vector< std::string> l_xpathList;

    size_t l_xpathTotalLevels = 0; // Number of nodes in the xpath expression (not including attribute)
    bool l_matchFromRoot = false; // If match must only be made from root node
    bool l_doubleSlashMatch = false; //
    size_t l_matchAllAtXPathLevel = 0;
    bool l_matchAttribute = false; // True if match must be an attribute


    // Parse the Xpath-like expression
    std::string l_tmpElementText; // Temporary string
    bool l_seenSlash = false;
    for( size_t l_i = 0; l_i < p_xpath.size(); l_i++) {
      
      if( p_xpath[ l_i] == '/') {
	// We have found a xpath node separator: '/'

	if( l_seenSlash == false) {
	  // No separator has just been seen before
	  l_seenSlash = true;

	  if( l_tmpElementText.empty() == false) {
	    // if text was collected between 2 separators
	    // store it in the xpathList
	    l_xpathList.push_back( l_tmpElementText);
	    l_tmpElementText.clear();
	  }
	} else { // l_SeenSlash == false
	  // Two '/' in a row indicate a all-elements match after a certain point
	  // in the xpath string. Mark the start of the all-elements match
	  // by inserting an empty string
	  l_doubleSlashMatch = true;
	  l_matchAllAtXPathLevel = l_xpathList.size();

	  // Clear the "seenSlash" flag
	  l_seenSlash = false;
	}
      } else { // xpath[ l_i] == '/'
	// Normal char seen

	// if first char is '/' and second is a regular char
	// we will have to match from the Xml root level
	if( l_i == 1 && l_seenSlash == true)
	  l_matchFromRoot = true;

	// Mark that we didn't see a separator
	l_seenSlash = false;
	// Append the text to the temporary string until we find a separator
	l_tmpElementText.append( 1, p_xpath[ l_i]);
      }
    }

    // push the last node (or attribute) into the xpathList (if any)
    if( l_tmpElementText.empty() == false)
      l_xpathList.push_back( l_tmpElementText);

    // Store the number of xpathTotalLevels that we must traverse
    l_xpathTotalLevels = l_xpathList.size();

    if( l_xpathList[ l_xpathTotalLevels - 1][ 0] == '@') {
      // If an attribute is to be matched, mark it so
      l_matchAttribute = true;
      // xpathLevels is decremented as the attribute is not a node to traverse
      l_xpathTotalLevels--;
    }

    // Parse the XML to deliver the results

    std::istringstream respstr( strResults_);
    //std::ifstream respstr( "r.xml");//test

    XmlPullParser l_xpp( respstr);
    l_xpp.setFeature( FEATURE_PROCESS_NAMESPACES, true);
    l_xpp.require( XmlPullParser::START_DOCUMENT, "", "");

    size_t l_xpathLevel = 0;
    size_t l_xmlLevel = 0;
    size_t l_failedXpathMatchAtXmlLevel = 0;

    bool l_textWasRetrieved = false;
    std::string l_retrievedText;
    std::string l_xmlTagName;

    int l_xmlPullEvent;

    do {
      l_xmlPullEvent = l_xpp.nextToken();

      if( l_xmlPullEvent == XmlPullParser::START_TAG) {

	l_xmlTagName = l_xpp.getName();

	// Skip envelope and body tags at xml root level
	if( l_xmlLevel == 0 && ( l_xmlTagName == "Envelope" || l_xmlTagName == "Body"))
	  continue;

	// Mark the entrace to xmlLevel
	l_xmlLevel++;

	//bool l_doubleSlashMatch = false;
	//size_t l_matchAllAtXPathLevel = 0;

	if( l_xmlTagName == l_xpathList[ l_xpathLevel] &&
	    ( l_failedXpathMatchAtXmlLevel == 0 ||
	      ( l_doubleSlashMatch == true && l_xpathLevel >= l_matchAllAtXPathLevel))
	    ) {

	  // Check if we must match at root level
	  // See if "root" levels match (0 for xpathLevel and 1 for xmlLevel)
	  // if root levels do not match -- skip checks
	  if( l_matchFromRoot == true)
	    if( l_xpathLevel == 0 && l_xmlLevel != 1)
	      continue;

	  l_xpathLevel++;

	  // If we have not reached the final sought node, carry on
	  if( l_xpathLevel < l_xpathTotalLevels)
	    continue;

	  // if we have reached the last element of the xpath expression
	  // and given that all preconditions were met
	  // store the results

	  // Since we have already processed a "start_tag" event the next
	  // has to be content. "Text" events may be delivered in several
	  // consecutive events, hence the loop
	  // Entity references will be shown as independent events

	  if( l_matchAttribute == false) {
	    // We have to store/return the text of the node
	    // Clear the temporary storage before starting
	    l_retrievedText.clear();

	    do {
	      // First token after a START_TAG has to be "text or entity" (the returned string might be empty)
	      l_xmlPullEvent = l_xpp.nextToken();
	      l_retrievedText += l_xpp.getText();
	      // Carry on while Text or Entity are returned
	    } while( l_xmlPullEvent == XmlPullParser::ENTITY_REF || l_xmlPullEvent == XmlPullParser::TEXT);

	    // Mark that we have content in "tmp" to be stored or returned
	    l_textWasRetrieved = true;

	  } else {

	    // Retrieve the attribue
	    l_retrievedText = l_xpp.getAttributeValue( "", l_xpathList[ l_xpathLevel].substr( 1));
	    // Mark that we have content in "tmp" to be stored or returned
	    l_textWasRetrieved = true;
	  } 

	  if( l_textWasRetrieved == true) {
	    // If something (node's text or attribute's value) was retrieved
	    if( p_array == NULL)
	      return l_retrievedText; // return it, as only one value was sought

	    // Store it in the array to be returned
	    p_array->push_back( l_retrievedText);
	    // Decrease the xpathLevel, to enable a new match by re-entering the loop
	    l_xpathLevel--;
	    
	    // Clear the "textRetrieved" flag
	    l_textWasRetrieved = false;
	  }
	} // if( l_xmlTagName == l_xpathList[ l_xpathLevel]) {
	else if( l_xpathLevel > 0 && l_failedXpathMatchAtXmlLevel == 0) {
	  // If a match has already happened (xpathLevel > 0) and we find ourselves here
	  // the name of the node did not match, we record the xmllevel, so skip
	  // any deeper tag
	  // The value will be reset to 0, as soon as END_TAG at the same level is seen
	  l_failedXpathMatchAtXmlLevel = l_xmlLevel;
	}
      }

      if( l_xmlPullEvent == XmlPullParser::END_TAG) {

	// Check if we may clear the "failedXpathMatchAtXmlLevel" flag
	if( l_failedXpathMatchAtXmlLevel == l_xmlLevel) {
	  l_failedXpathMatchAtXmlLevel = 0;
	}
	else if( l_failedXpathMatchAtXmlLevel == 0) {
	  if( l_xpathLevel > 0 && l_xpp.getName() == l_xpathList[ l_xpathLevel - 1])
	    l_xpathLevel--;
	  // Just above. If we have just seen a closing tag that corresponds to the previous xpathLevel
	  // decrease one xpathLevel (it is 0 based, unlike xmlLevel which is 1 based)
	}

	// Skip the envelope and body tags at xml root level
	if( l_xmlLevel == 0)
	  continue;

	l_xmlLevel--;
      }

    } while( l_xmlPullEvent != XmlPullParser::END_DOCUMENT);

  } // if (status_ && !strResults_.empty()) 
  else {
    //throw exception
    WsdlException we("Attempted to extract response when web service invocation did not succeed");
    throw we;
  }
 
  return "";//nothing found or values returned in vector 'arr'
}



void
WsdlInvoker::post(long timeout, std::string username, std::string passwd)
{
  const std::string  postData = soapstr_->str();
  if(verbose_){
    
    std::ofstream ofs("request.log",std::ios::app);
    ofs<<postData;
    ofs<<std::endl;
    ofs.flush();
  }
    
#ifdef WITH_CURL
  CURLcode res;  
  std::string strCurlBuffer = "";
  if (!ctx){
    ctx=curl_easy_init();
  }

  if (!ctx)
    return ;
  curl_easy_setopt( ctx , CURLOPT_URL,  location_.c_str()) ;

  curl_easy_setopt( ctx , CURLOPT_NOPROGRESS , 1 ) ;
  if(timeout){
    curl_easy_setopt( ctx ,CURLOPT_TIMEOUT, timeout);
    curl_easy_setopt( ctx , CURLOPT_CONNECTTIMEOUT, timeout);
  }

  if (verbose_) {
    curl_easy_setopt( ctx , CURLOPT_VERBOSE,1);
    curl_easy_setopt( ctx , CURLOPT_NOPROGRESS , 0 ) ;
  }

  curl_easy_setopt( ctx , CURLOPT_POST , 1 );
  curl_easy_setopt( ctx , CURLOPT_POSTFIELDS , postData.c_str()) ;
  curl_slist* responseHeaders = NULL ;
  std::string tmp="SOAPAction: ";
  tmp.push_back('"');
  tmp+=action_;
  tmp.push_back('"');
  responseHeaders = curl_slist_append( responseHeaders , tmp.c_str());
  responseHeaders = curl_slist_append( responseHeaders ,"Content-Type: text/xml; charset=UTF-8");
  responseHeaders = curl_slist_append( responseHeaders ,"Accept: text/xml;");
  curl_easy_setopt( ctx , CURLOPT_HTTPHEADER , responseHeaders ) ;
  tmp = "wsdlpull";
#ifdef HAVE_CONFIG_H
  tmp=tmp+"/"+VERSION;
#endif
  curl_easy_setopt( ctx,CURLOPT_USERAGENT,tmp.c_str());
  curl_easy_setopt( ctx,CURLOPT_POSTFIELDSIZE,postData.length());
  
  if (XmlUtils::getProxy()){
    curl_easy_setopt(ctx,CURLOPT_PROXY,XmlUtils::getProxyHost().c_str());
    tmp=XmlUtils::getProxyUser()+":"+XmlUtils::getProxyPass();
    curl_easy_setopt(ctx,CURLOPT_PROXYUSERPWD,tmp.c_str());
  }
  curl_easy_setopt(ctx, CURLOPT_WRITEDATA, &strCurlBuffer) ;
  curl_easy_setopt( ctx ,CURLOPT_WRITEFUNCTION,storeResults) ;

  if (bAuth) {
    curl_easy_setopt(ctx, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
    std::string tmp = sAuthUser + ":" + sAuthPass;
    curl_easy_setopt(ctx, CURLOPT_USERPWD, tmp.c_str());
  }
  curl_easy_setopt(ctx, CURLOPT_COOKIEFILE, "");
  // std::logger_ << "- - - BEGIN: response - - -" << std::endl ;
  res=curl_easy_perform(ctx);
  //  std::logger_ << "- - - END: response - - -" << std::endl ;

  curl_slist_free_all( responseHeaders ) ;
  strResults_ = strCurlBuffer;

#elif _WIN32
	
  char* sResults = (char*)0;
  XmlUtils::winPost(location_,username,passwd,postData,action_,sResults);
  strResults_ = (sResults != (char*)0) ? std::string(sResults) : "";
#endif

  if(verbose_ && !strResults_.empty()){
    
    std::ofstream ofs("response.log",std::ios::app);
    ofs<<strResults_;
    ofs<<std::endl;
    ofs.flush();
  }

}

void
WsdlInvoker::printTypeNames(bool f)
{
  TypeContainer::printTypeNames_ = false;
}

//build an XML Tree from the results
void
WsdlInvoker::buildXmlTree( XmlPullParser &p_xmlPullParser, XmlNode_t &p_xmlNode, bool p_pendingEvent)
{
  int l_xmlPullEvent;

  do {

    if( p_pendingEvent == false) {
      l_xmlPullEvent = p_xmlPullParser.nextToken();
    } else {
      p_pendingEvent = false;
      l_xmlPullEvent = p_xmlPullParser.getEventType();
    }

    if( l_xmlPullEvent == XmlPullParser::START_TAG) {

      if( p_xmlNode.empty() == true) {

	p_xmlNode.setName( p_xmlPullParser.getName(), XmlNode_t::NON_EMPTY_NODE);

	size_t l_numAttributes = static_cast< size_t>( p_xmlPullParser.getAttributeCount());
	for( size_t l_i = 0; l_i < l_numAttributes; l_i++) {

	  p_xmlNode.addAttribute( p_xmlPullParser.getAttributeName( l_i),
				  p_xmlPullParser.getAttributeValue( l_i));
	}
      } else {
	XmlNode_t &l_childNodeRef = p_xmlNode.addNode( p_xmlPullParser.getName(), XmlNode_t::EMPTY_NODE);
	buildXmlTree( p_xmlPullParser, l_childNodeRef, true);
      }
    }
    else if( l_xmlPullEvent == XmlPullParser::TEXT || l_xmlPullEvent == XmlPullParser::ENTITY_REF) {

      ::std::string l_tmpTxt;
      do {
	l_tmpTxt += p_xmlPullParser.getText();
	l_xmlPullEvent = p_xmlPullParser.nextToken();
      } while( l_xmlPullEvent == XmlPullParser::ENTITY_REF || l_xmlPullEvent == XmlPullParser::TEXT);

      p_xmlNode.setText( l_tmpTxt);

      // The previous loop leaves an unprocessed event after calling "nextToken" and seeing
      // that it's not text or entity_ref
      p_pendingEvent = true;
    }
    else if( l_xmlPullEvent == XmlPullParser::END_TAG) {
      break;
    }

  } while( l_xmlPullEvent != XmlPullParser::END_DOCUMENT);
}

void
WsdlInvoker::processFault(XmlPullParser* xpp)
{

  if (soap_->getSoapVersion() == Soap::SOAP12) {
    
    while (!(xpp->getEventType() == XmlPullParser::END_TAG && xpp->getName() == "Fault")) {
      
      if (xpp->getEventType() == XmlPullParser::START_TAG && xpp->getName() == "Code") {
	xpp->next();
	
	while (!(xpp->getEventType() == XmlPullParser::END_TAG && xpp->getName() == "Code")) {
	  
	  if (xpp->getEventType() == XmlPullParser::START_TAG && xpp->getName() == "Value") {
	    xpp->next();
	    sFaultCode = xpp->getText();
	    logger_ << "SOAP Fault Code: " << sFaultCode << std::endl;
	  }
	  
	  if (xpp->getEventType() == XmlPullParser::START_TAG && xpp->getName() == "Subcode") {
	    xpp->next();
	    
	    if (xpp->getEventType() == XmlPullParser::START_TAG && xpp->getName() == "Value") {
	      xpp->next();
	      sFaultSubCode = xpp->getText();
	      logger_ << "SOAP Fault SubCode: " << sFaultSubCode << std::endl;
	    }
	  }
	  xpp->next();
	}
      }
      
      if (xpp->getEventType() == XmlPullParser::START_TAG && xpp->getName() == "Reason") {
	xpp->next();
	
	if (xpp->getEventType() == XmlPullParser::START_TAG && xpp->getName() == "Text") {
	  xpp->next();
	  sFaultString = xpp->getText();
	  logger_ << "SOAP Fault String: " << sFaultString << std::endl;
	}
      }
      xpp->next();
    }
  } else {	// SOAP 1.1
    
    while (!(xpp->getEventType () == XmlPullParser::END_TAG &&
	     xpp->getName() == "Fault")) {
      
      if (xpp->getEventType() == XmlPullParser::START_TAG &&
	  xpp->getName() == "faultcode"){
	
	xpp->next();
	sFaultCode = xpp->getText();
	logger_<<"SOAP Fault Code: "<<sFaultCode<<std::endl;
      }
      
      if (xpp->getEventType() == XmlPullParser::START_TAG &&
	  xpp->getName() == "faultstring"){
	
	xpp->next();
	sFaultString = xpp->getText();
	logger_<<"SOAP Fault String: "<<sFaultString<<std::endl;
      }
      if (xpp->getEventType() == XmlPullParser::START_TAG &&
	  xpp->getName() == "faultactor"){
	
	xpp->next();
	sFaultActor = xpp->getText();
	logger_<<"SOAP Fault Actor: "<<sFaultActor<<std::endl;
      }
      xpp->next();
    }
  }
}

void 
WsdlInvoker::processBody(const Message* m,
			 XmlPullParser* xpp)
{
  
  if (xpp->getName() == "Fault") {
    
    processFault(xpp);
    status_ = false;
    return;
  }

  if (style_ == Soap::RPC && use_==Soap::ENCODED){
	  
    if (xpp->getName () == op_->getName()+"Response") {

      //operation's name followed by 'Response' must be the containing element
      xpp->nextTag ();
      
      do {
      
	
	//first look for xsi:type
	Qname typ(xpp->getAttributeValue(Schema::SchemaInstaceUri, "type"));
	typ.setNamespace(xpp->getNamespace(typ.getPrefix()));
	const SchemaParser * sParser = 0;
	int typeId = 0;
	  
	if (!(typ.getNamespace() == soap_->getEncodingUri() &&
	      typ.getLocalName() == "Array"))//for soap array just use the part's type info
	  sParser= wParser_->getSchemaParser(typ.getNamespace());
	  
	if (sParser){
	    
	  typeId = (const_cast<SchemaParser*>(sParser))->getTypeId(typ);
	}
	else{

	  //if xsi:type doesnt give a clue then see if the part name matches
	  const Part * p = m->getMessagePart(xpp->getName ());
	  if (p){
	    
	    sParser = wParser_->getSchemaParser(p->schemaId());
	    typeId = p->type();
	  }else {


	  }
	}
	if (sParser && typeId !=0){  
	    
	  SchemaValidator * sv= new SchemaValidator(sParser);	  
	  std::string tag = xpp->getName();
	  TypeContainer * t = sv->validate (xpp, typeId);
	  outputs_.push_back(std::pair<std::string,TypeContainer*>(tag,t));
	  xpp->nextTag();
	  delete sv;
	}
	else{

	  status_ = false;
	  logger_<<"Unknown element "<<xpp->getName()<<std::endl;
	  return;
	}
      } while (!(xpp->getName() == op_->getName()+"Response" &&
		 xpp->getEventType() == XmlPullParser::END_TAG));
    }
  }
  else{
    
    while (!(xpp->getName() == "Body" && 
	     xpp->getNamespace() == soap_->getEnvelopeUri() &&
	     xpp->getEventType() == XmlPullParser::END_TAG)) {
	     
      Qname elemName (xpp->getName ());
      elemName.setNamespace(xpp->getNamespace());

      //doc/literal has ref type element in the part
      const SchemaParser * sParser =
	wParser_->getSchemaParser(elemName.getNamespace());
      if (!sParser){
	  
	status_ = false;
	logger_<<"Unknown element "<<elemName<<std::endl;
	return;
      }
      SchemaValidator * sv= new SchemaValidator(sParser);	  
	  
      const Element * e = sParser->getElement (elemName);
      if(e){
	int typeId = e->getType () ;
	TypeContainer * t = sv->validate (xpp, typeId);
	std::pair<std::string,TypeContainer*> pr(elemName.getLocalName(),t);
	outputs_.push_back(pr);
      }
      else{
	status_ = false;
	std::cerr<<"Unknown element "<<elemName.getLocalName()<<std::endl;
	return;
      }
      delete sv;
      xpp->nextTag();
    }
  }
  status_ = true;
}

void
WsdlInvoker::processHeader(XmlPullParser *xpp)
{
  Qname elem;
  const SchemaParser * sParser = 0;
  int type = Schema::XSD_INVALID;
  xpp->nextTag ();
  std::string tag = xpp->getName();

  while (!(xpp->getEventType() == XmlPullParser::END_TAG &&
	   xpp->getName() == "Header")){


    //first look for xsi:type
    if (xpp->getAttributeValue(Schema::SchemaInstaceUri, "type") != "" ) {
      
      elem = Qname(xpp->getAttributeValue(Schema::SchemaInstaceUri, "type"));
      elem.setNamespace(xpp->getNamespace(elem.getPrefix()));
      sParser= wParser_->getSchemaParser(elem.getNamespace());
      type = (const_cast<SchemaParser*>(sParser))->getTypeId(elem);  
    }
    else {

      elem = Qname(xpp->getName());
      elem.setNamespace(xpp->getNamespace());      
      sParser=wParser_->getSchemaParser(elem.getNamespace());
      const Element * e = sParser->getElement (elem);
      if(e){
	     type = e->getType ();
      }
    }
    SchemaValidator * sv= new SchemaValidator(sParser);	  
    TypeContainer * t = sv->validate (xpp, type);
    outputs_.push_back(std::pair<std::string,TypeContainer*>(tag,t));
    oHeaders_++; 
    xpp->nextTag();
    delete sv;
  }
}

bool
WsdlInvoker::isSoapArray (const ComplexType * ct,
			  const SchemaParser * sParser)
{
  const XSDType * baseType=sParser->getType(ct->getBaseTypeId());
  if (baseType) {
    if(baseType->getNamespace()==soap_->getEncodingUri() &&
       baseType->getName()=="Array")
      return true;
  }
  return false;
}

void
WsdlInvoker::setCredentials(const std::string & user, const std::string & pass)
{
  username_ = user;
  password_ = pass;
  XmlUtils::setProxyUser(user);
  XmlUtils::setProxyPass(pass);
  XmlUtils::setProxy(true);
}

void
WsdlInvoker::setBuildXmlTree( bool p_buildXmlTree)
{
  m_buildXmlTree = p_buildXmlTree;
}

bool
WsdlInvoker::getBuildXmlTree( void) const
{
  return m_buildXmlTree;
}

void
WsdlInvoker::setProcessEnvAndBody( bool p_processEnvAndBody)
{
  m_xmlDoc.setProcessEnvAndBody( p_processEnvAndBody);
}

bool
WsdlInvoker::getProcessEnvAndBody( void) const
{
  return m_xmlDoc.getProcessEnvAndBody();
}

void
WsdlInvoker::setLazyRelativeMatch( bool p_lazyRelativeMatch)
{
  m_xmlDoc.setLazyRelativeMatch( p_lazyRelativeMatch);
}

bool
WsdlInvoker::getLazyRelativeMatch( void) const
{
  return m_xmlDoc.getLazyRelativeMatch();

}

void
WsdlInvoker::setAuth(const std::string & user, const std::string & pass)
{
  sAuthUser = user;
  sAuthPass = pass;
  bAuth = true;
}

void
WsdlInvoker::setProxy(const std::string & host,int  port)
{
  host_ = host;
  port_ = port;
  std::ostringstream oss;
  oss<<host<<":"<<port;
  XmlUtils::setProxyHost(oss.str());
  XmlUtils::setProxy(true);
}

std::string
WsdlInvoker::getPrefix(const std::string & nsp)
{
  
  unsigned int i = 0;
  char prefix='1';
  while (i<prefixes_.size()) {
    if (prefixes_[i] == nsp)
      break;
    i++;
  }

  std::string tmp("ns");
  tmp.append(1,prefix+i);
  if (i == prefixes_.size())
    prefixes_.push_back(nsp);
  
  return tmp;

}

bool
WsdlInvoker::isSubTreeNil() {

  if (!serializeMode_)
    return false;
  size_t i = n_;
  size_t depth =  elems_[n_].parents_.size() - 1;
  std::string parent ;
  if (depth > 0 )
   parent = elems_[n_].parents_[depth - 1 ];
  bool nil = false;
  for (; i< elems_.size() && elems_[i].parents_.size() >= (depth + 1) && 
	 ( depth == 0  || elems_[i].parents_[depth - 1 ] == parent );i ++){

	   nil = true;//there are child elements
	   if (!elems_[i].data_[0].empty() )
	     nil = false; //check if it is empty

	   if (!nil) break; //if non empty then break loop right away 
	   
  }
  if (nil)
    n_ = i;//since this is called only in serializeMode = true advance the counter
  return nil;
}

}

#ifdef WITH_CURL
size_t
storeResults(void * buf,size_t sz,size_t nmemb,void* userdata)
{
    char* sBuffer = (char*) buf;
    std::string* strCurlBuffer = (std::string*) userdata;

    int result = 0;
    if (strCurlBuffer) {
	strCurlBuffer->append(sBuffer, sz * nmemb);
	result = sz * nmemb;
    }

    return result;
}
#endif 
