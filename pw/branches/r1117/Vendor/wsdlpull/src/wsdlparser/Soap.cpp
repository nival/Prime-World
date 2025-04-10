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
#include "wsdlparser/Soap.h"


using namespace std;

namespace WsdlPull {
/*
  TODO
  1.When the use is "encoded" the part must reference the an
  abstract type using the "type" attribute .
  2.Only Soap encoding style is supported
*/

#include <iomanip>

const std::string Soap::httpTransport = "http://schemas.xmlsoap.org/soap/http";
const std::string Soap::httpBinding = "http://schemas.xmlsoap.org/wsdl/http/";
const std::string Soap::soapEncUri11 = "http://schemas.xmlsoap.org/soap/encoding/";
const std::string Soap::soapEnvUri11 = "http://schemas.xmlsoap.org/soap/envelope/";
const std::string Soap::soapEncUri12 = "http://www.w3.org/2003/05/soap-encoding";
const std::string Soap::soapEnvUri12 = "http://www.w3.org/2003/05/soap-envelope";
const std::string Soap::soapBindingUri11 ="http://schemas.xmlsoap.org/wsdl/soap/";
const std::string Soap::soapBindingUri12= "http://schemas.xmlsoap.org/wsdl/soap12/wsdl11soap12.xsd";


Soap::Soap(const std::string & schemaPath, SoapVersion a_soapVersion)
  :startId(0),
   mySchemaParser(0),
   mySchemaValidator(0),
   wParser_(0),
   idCounter(0),
   schemaPath_(schemaPath),
   soapVersion_(a_soapVersion)
{
  header_.clear();
  body_.clear();
  location_.clear();
  ops_.clear();
  idTable.clear();

  if (a_soapVersion == SOAP12)
    sNamespace = Soap::soapBindingUri12;
  else
    sNamespace = Soap::soapBindingUri11;
}


Soap::~Soap()
{
  if (mySchemaParser)
    delete mySchemaParser;
  if (mySchemaValidator)
    delete mySchemaValidator;
}

std::string 
Soap::getExtensibilitySchema(void)const
{


  if (WsdlPull::WsdlParser::useLocalSchema_ == false) {
    return sNamespace;
  }

  string path=schemaPath_;
  path+="soap.xsd";
  return path;
}

std::string
Soap::getEncodingSchema(void)const
{

  if (WsdlPull::WsdlParser::useLocalSchema_ == false) {
    
    switch(getSoapVersion()) {
    
    case SOAP12:
      return soapEncUri12;
      break;
	  
    case SOAP11:
    default:
      return soapEncUri11;
      break;
    }
  }

  string path=schemaPath_;
  path+="soap-encoding.xsd";
  return path;
}

std::string
Soap::getEncodingUri(void)const
{
    switch(getSoapVersion()) {
	case SOAP12:
    	    return soapEncUri12;
	    break;

	case SOAP11:
	default:
    	    return soapEncUri11;
	    break;
    }
}

std::string
Soap::getEnvelopeUri(void)const
{
    switch(getSoapVersion()) {
	case SOAP12:
    	    return soapEnvUri12;
	    break;

	case SOAP11:
	default:
    	    return soapEnvUri11;
	    break;
    }
}

int 
Soap::handleElement(int parent, XmlPullParser * xParser)
{
  if (mySchemaParser == 0) {
   error("Could not parse soap extensibility elements");
    return 0;
  }
  string elemName = xParser->getName();
  int elemId = 0;
  Qname q(elemName);
  const  Element* e= mySchemaParser->getElement(q);
  if (e == 0) {

    error("Unknown element");
    return 0;
  }
  TypeContainer * t = new TypeContainer(e->getType(), mySchemaParser);
  
  try{

    mySchemaValidator->validate(xParser,e->getType(), t);
  } 
  catch (SchemaParserException spe) {
    
    error(spe.description + "Encountered error while validating {"+sNamespace +"}:"+elemName);
  }
  if (elemName == "binding")
    elemId = processBinding(t);

  else if (elemName == "operation")
    elemId = processOp(parent, t);

  else if (elemName == "body")
    elemId = processBody(parent, t);

  else if (elemName == "header")
    elemId = processHeader(parent, t);

  else if (elemName == "fault")
    elemId = processFault(parent, t);

  else if (elemName == "address")
    elemId = processAddress(parent, t);

  delete t;
  return elemId;
}


int
Soap::handleAttribute(int parent, string att,
                      XmlPullParser * xParser)
{
  return 0;
}


int  Soap::processBinding(TypeContainer * t)
{
  TypeContainer * temp = 0;
  if ((temp = t->getAttributeContainer("transport")) != 0)
    {
      string tp = *((string *) (temp->getValue()));
      if (tp == httpTransport)
        transport_ = HTTP;

      else
        transport_ = NONE;
    }

  else
    transport_ = HTTP;

  /*
   * Assume default transport as HTTP
   */
  if ((temp = t->getAttributeContainer("style")) != 0)
    {
      string style = *((string *) (temp->getValue()));
      if (style == "rpc")
        style_ = RPC;

      else
        style_ = DOC;
    }

  else
    style_ = DOC;
  Qname binding("binding");
  IDTableIndex idi;
  idi.typeId=(mySchemaParser->getElement(binding))->getType();
  idi.index=0;
  idTable.push_back(idi);
  idCounter++;
  return startId + idCounter - 1;
}


int
Soap::processOp(int parent, TypeContainer * t)
{
  TypeContainer * temp = 0;
  SoapOperationBinding sopb;
  
  if ((temp = t->getAttributeContainer("soapAction")) != 0)
    {
      string * s = (string *) (temp->getValue());
      if(s)
	sopb.soapAction = *s;
    }

  if ((temp = t->getAttributeContainer("style")) != 0)
    {
      string style = *((string *) (temp->getValue()));
      if (style == "rpc")
        sopb.style = RPC;

      else
	sopb.style = DOC;
    }
  else                                          //Use the binding element's style attribute
    sopb.style = style_;
  sopb.wsdlOpId = parent;

  ops_.push_back(sopb);

  Qname oprn("operation");
  IDTableIndex idi;
  idi.typeId=(mySchemaParser->getElement(oprn))->getType();
  idi.index=ops_.size()-1;
  idTable.push_back(idi);
  idCounter++;
  return startId + idCounter - 1;
}


int
Soap::processBody(int parent, TypeContainer * t)
{
  TypeContainer * temp = 0;
  string use;
  SoapMessageBinding smb;

  if ((temp = t->getAttributeContainer("use")) != 0)
    {
      use = *((string *) (temp->getValue()));
      if (use == "literal")
        smb.use = LITERAL;
      else
        smb.use = ENCODED;
    }
  else
    smb.use = LITERAL;

  if ((temp = t->getAttributeContainer("namespace")) != 0)
    {
      string * s = (string *) (temp->getValue());
      smb.urn = *s;
    }
  else{
    
    smb.urn="";
  }

  if ((temp = t->getAttributeContainer("encodingStyle")) != 0)
  {
    string * s = (string *) (temp->getValue());
    smb.encodingStyle = *s;
  }
  else{

    smb.encodingStyle="";
  }

  body_.push_back(smb);

  Qname body("body");
  IDTableIndex idi;
  idi.typeId=(mySchemaParser->getElement(body))->getType();
  idi.index=body_.size()-1;
  idTable.push_back(idi);
  idCounter++;
  return startId + idCounter - 1;
}


int
Soap::processFault(int parent, TypeContainer *)
{
  //TODO
  return startId + idCounter - 1;
}


int  
Soap::processAddress(int parent, TypeContainer * t)
{
  TypeContainer * temp = 0;
  string location;

  if ((temp = t->getAttributeContainer("location")) != 0)
    {
      string * s = (string *) (temp->getValue());
      if(s)
	location_.push_back(*s);
    }
  Qname address("address");

  IDTableIndex idi;
  idi.typeId=(mySchemaParser->getElement(address))->getType();
  idi.index=location_.size()-1;
  idTable.push_back(idi);
  idCounter++;
  return startId + idCounter - 1;
}


int
Soap::processHeader(int parent, TypeContainer * t)
{
  TypeContainer * temp = 0;
  Qname msg;
  std::string ns, part;
  Qname header("header");
  int partType;
  SoapHeaderBinding shb;
  if ((temp = t->getAttributeContainer("message")) != 0) {
    
    msg = *((Qname *) (temp->getValue()));
  }
  if ((temp = t->getAttributeContainer("namespace")) != 0) {

    ns = *((string *) (temp->getValue()));
  }
  const Message *m = wParser_->getMessage(msg);
  if (m == 0) {
    error("Unkown message " + msg.getLocalName());
    return 0;
  }
  if ((temp = t->getAttributeContainer("parts")) != 0) {
    
    part = *((string *) (temp->getValue()));  //this is actually NMTOKENS
    //Multiple parts not supported
  }
  else if ((temp = t->getAttributeContainer("part")) != 0) {
    //some wsdls use 'part' instead of 'parts'
    part = *((string *) (temp->getValue()));  
  }
  partType = m->getPartType(part);

  if (partType == 0)
    error("Unkown part type :"+ part);

  shb.partId_= m->getPartIndex(part);
  shb.message_ = m;
  shb.urn = ns;
  header_.push_back(shb);

  IDTableIndex idi;
  idi.typeId=(mySchemaParser->getElement(header))->getType();
  idi.index=header_.size()-1;
  idTable.push_back(idi);

  idCounter++;
  return startId + idCounter - 1;
}


void
Soap::getSoapOperationInfo(int elemId, string & action, Soap::Style &style)
{
  if (elemId - startId >= idCounter ||
      elemId < startId )            //invalid elem Id
    return;
  int opId = idTable[elemId - startId].index;
  action = ops_[opId].soapAction;
  style = ops_[opId].style;
} 

void  
Soap::getSoapBodyInfo(int elemId, string &ns, Soap::Encoding &use, std::string &encodingStyle)
{
  if (elemId - startId >= idCounter ||
      elemId < startId )            //invalid elem Id
    return;
  int bodyId = idTable[elemId - startId].index;
  ns = body_[bodyId].urn;
  use = body_[bodyId].use;
  encodingStyle = body_[bodyId].encodingStyle;
} 

void
Soap::getSoapHeaderInfo(int elemId, string &ns, int &partId, const Message* & m)
{
  if (elemId - startId >= idCounter  ||
      elemId < startId )            //invalid elem Id
    return;
  int headerId = idTable[elemId - startId].index;
  ns = header_[headerId].urn;
  partId = header_[headerId].partId_;
  m = header_[headerId].message_;
} 

bool
Soap::getServiceLocation(int elemId, std::string &location)
{
  if (elemId - startId >= idCounter ||
      elemId < startId )            //invalid elem Id
    return false;
  int locId = idTable[elemId - startId].index;
  location = location_[locId];
  if(!location.empty())
    return true;
  else
    return false;
} 

bool 
Soap::isSoapBody(int elemId)
{
  Qname  body("body");
  if (elemId - startId >= idCounter||
      elemId < startId )//invalid elem Id
    
    return false;
  
  if (idTable[elemId - startId].typeId ==
      (mySchemaParser->getElement(body))->getType())
    return true;
  else
    return false;
}


bool 
Soap::isSoapHeader(int elemId)
{
  Qname  header("header");
  if (elemId - startId >= idCounter||
      elemId < startId )//invalid elem Id
    return false;
  if (idTable[elemId - startId].typeId ==
      (mySchemaParser->getElement(header))->getType())
    return true;

  else
    return false;
}


void
Soap::error(std::string s)
{
  wParser_->logger()<< "Soap Processing" << XmlUtils::dbsp << s << endl;
}

void
Soap::setSchemaPath(const std::string & schemaPath)
{
  schemaPath_ = schemaPath;
}

}
