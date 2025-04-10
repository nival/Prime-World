/* 
 * wsdlpull - A C++ parser for WSDL (Web services description
 * language) Copyright (C) 2005-2007 Vivek Krishna
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

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "xmlpull/osdir.h"
#include "wsdlparser/WsdlParser.h"
#include "wsdlparser/Soap.h"

using namespace std;
namespace WsdlPull{

bool WsdlParser::useLocalSchema_=true;

WsdlParser::WsdlParser(istream & in, ostream & out,
                       const std::string & schemaPath)
  :errorOccured_(false), 
   ostr(out),
   istr(in),
   state_ (START),
   element_(START),
   Doc_(0),
   xParser_(0),
   MAX_EXT_XML(256),
   schemaPath_(schemaPath)
{
  initialize(false);
}

WsdlParser::WsdlParser(const std::string & Uri, ostream & out,
                       const std::string & schemaPath)
  :errorOccured_(false), 
   ostr(out),
   istr(std::cin),
   state_ (START),
   element_(START),
   Doc_(0),
   xParser_(0),
   MAX_EXT_XML(256),
   schemaPath_(schemaPath)
{
  uri_ = Uri.substr(0,Uri.rfind('/') + 1);
  if(XmlUtils::fetchUri(Uri,wsdlFileName))
    {
      xmlStream.open(wsdlFileName.c_str());
      initialize(true);
    }
  else{
    std::string e= "Unable to connect to ";
    error(e + Uri);   
  }
}

void
WsdlParser::initialize(bool file)
{
  if (schemaPath_.empty()) {

#if defined SCHEMADIR
    schemaPath_= SCHEMADIR;
#else 
    schemaPath_= "src/schemas";
#endif
  }
 
  if(file)
    xParser_= new XmlPullParser(xmlStream);
  else
    xParser_= new XmlPullParser(istr);

  xParser_->setFeature(FEATURE_PROCESS_NAMESPACES, true);
  xParser_->require(xParser_->START_DOCUMENT, "", "");
  messages_.clear();
  bindings_.clear();
  porttypes_.clear();
  wsdlExtensions_.clear();
  schemaParser_.clear();
  
  //add the schema for wsdl1.0 to parse arrayType
  SchemaParser * sParser=0;
  if (WsdlPull::WsdlParser::useLocalSchema_ == false ) {
    
    sParser = new SchemaParser (wsdlUri,wsdlUri,ostr);
  }
  else {
    
    sParser = new SchemaParser (schemaPath_+"wsdl10.xsd",
					       wsdlUri,ostr,schemaPath_);

  }
  sParser->parseSchemaTag();
  schemaParser_.push_back(sParser);


  soap_ = new Soap(schemaPath_);
  addExtensibilityHandler (soap_);
  soap2_ = new Soap(schemaPath_,Soap::SOAP12);  
  addExtensibilityHandler (soap2_);
 
}


WsdlParser::~WsdlParser()
{
  size_t i = 0;
  for (list < const Message * >::iterator mi =
         messages_.begin(); mi != messages_.end();
       mi++)
    delete(*mi);
  for (list < Binding * >::iterator bi =
         bindings_.begin(); bi != bindings_.end();
       bi++)
    delete(*bi);

  for (list < Service*>::iterator si =services_.begin();
       si != services_.end();
       si++)
    delete(*si);
  
  for (list < PortType * >::iterator pti =
         porttypes_.begin(); pti != porttypes_.end();
       pti++)
    delete(*pti);

  for (i = 0; i < schemaParser_.size(); i++)
    delete schemaParser_[i];
	    
  //  for (i = 0; i < Ops_.size(); i++)
  //  delete Ops_[i];

  for (list < string * >::iterator sti =
         docs_list_.begin(); sti != docs_list_.end();
       sti++)
    delete(*sti);

  for (vector<ExtensionInfo>::iterator ie = wsdlExtensions_.begin();
       ie != wsdlExtensions_.end();
       ie++)
    delete ie->we;
  
  delete xParser_;
  xmlStream.close(); 

  // delete all the temp files
  XmlUtils::delUriFiles();

}

const Binding *
WsdlParser::getBinding()
{
  if (element_ != BINDING)
    {
      error ("Attempted to extract a Binding when ,no binding was parsed",1);
      return 0;
    }
  else
    {
      return bindings_.back();
    }
}

void
WsdlParser::addExtensibilityHandler(WsdlExtension * ext)
{
  ExtensionInfo exi;
  exi.we=ext;
  exi.spe=0;
  wsdlExtensions_.push_back(exi);
} 


const Binding *
WsdlParser::getBinding(const Qname & q)
{
  Qname qn(q);
  if (!qn.getPrefix().empty())
    qn.setNamespace(getNamespace(qn.getPrefix()));
  else
    qn.setNamespace(tnsUri_);
  if (tnsUri_ != qn.getNamespace())
    return 0;
  for (list <Binding * >::iterator pBinding =
         bindings_.begin(); pBinding != bindings_.end();
       pBinding++)
    if ((*pBinding)->getName() == qn.getLocalName())
      return *pBinding;
  return 0;
}


const Service *
WsdlParser::getService()
{
  if (element_ != SERVICE){
    
    error ("Attempted to extract a Service when ,no service was parsed",1);
    return 0;
  }
  else{

    return services_.back();
  }
}

const Service *
WsdlParser::getService(const Qname & q)
{
  Qname qn(q);
  if (!qn.getPrefix().empty())
    qn.setNamespace(getNamespace(qn.getPrefix()));
  else
    qn.setNamespace(tnsUri_);
  if (tnsUri_ != qn.getNamespace())
    return 0;
  
  for (list <Service * >::iterator si =services_.begin();
       si != services_.end();
       si++)
    if ((*si)->getName() == qn.getLocalName())
      return *si;
  
  return 0;
}

  void 
    WsdlParser::getServices(ServiceIterator &from, ServiceIterator &to)
  {
    if (services_.size() > 0)
    {
      from = services_.begin();
      to = services_.end();
    }
  }

const PortType *
WsdlParser::getPortType()
{
  if (element_ != PORT_TYPE)
    {
      error ("Attempted to extract a PortType when ,no PortType was parsed",1);
      return 0;
    }
  else
    {
      return porttypes_.back();
    }
}


const PortType *
WsdlParser::getPortType(const Qname & qn)
{
  string name = qn.getLocalName();
  
  if (!qn.getPrefix().empty()){
    if(getNamespace(qn.getPrefix())!=tnsUri_)
      return 0;
  }

  for (PortType::cPortTypeIterator pPortType =porttypes_.begin();
       pPortType != porttypes_.end();
       pPortType++)
    if ((*pPortType)->getName() == name)
      return *pPortType;
  return 0;
}


bool
WsdlParser::getOperations(const Qname & portType,
                          Operation::cOpIterator& begin,
                          Operation::cOpIterator& end)
{
  const PortType *pt = getPortType(portType);
  if(pt){
    return pt->getOperations(begin,end);
  }
  else
    return false;
}
 


const Operation *
WsdlParser::getOperation(const Qname & portType, const Qname & q)
{
  const PortType *pt = getPortType(portType);
  int num = pt->getNumOps();
  if (num > 0)
    {
      const Operation *op = NULL;
      for (int i = 0; i < num; i++)
        {
          op = pt->getOperation(i);
          if (op->getName() == q.getLocalName())
            return op;
        }
    }
  return 0;
}


const Message *
WsdlParser::getMessage()
{
  if (element_ != MESSAGE)
    {
      error ("Attempted to extract a Message when ,no Message was parsed",1);
      return 0;
    }
  else
    {
      return messages_.back();
    }
}


const Message *
WsdlParser::pgetMessage(const Qname & qn)
{
  const Message*m=getMessage(qn);
  if(m==0){
    Message* newMessage = new Message(*this);
    newMessage->setName(qn.getLocalName());
    putMessage(newMessage);
    return newMessage;
  }else{
    return m;
  }
}


const Message *
WsdlParser::getMessage(const Qname & qn)
{
  string name = qn.getLocalName();
  if(!qn.getNamespace().empty() &&
     tnsUri_ != qn.getNamespace())
    return 0;

  for (list < const Message * >::iterator pMessage =
         messages_.begin(); pMessage != messages_.end();
       pMessage++)
    if ((*pMessage)->getName() == name)
      return *pMessage;
  
  return 0;
}


const SchemaParser *
WsdlParser::getSchemaParser(string targetNamespace) const
{
  if (targetNamespace == Schema::SchemaUri)
    return 0;
  for (size_t i = 0; i < schemaParser_.size(); i++){
    if (schemaParser_[i]->getNamespace() == targetNamespace)
      return (const SchemaParser *) schemaParser_[i];
  
    if (schemaParser_[i]->isImported(targetNamespace)) {
      
      return schemaParser_[i]->getImportedSchemaParser(targetNamespace);
    }
  }
  return 0;
}



  ////////// private methods
bool  isValidWsdlElement(int id)
{
  if (id >= 0)
    return true;

  else
    return false;
}


int
WsdlParser::peek(bool lookahead)
{

  //event Type returned by XML pull parser
  int event_type, tmp_event_type = xParser_->getEventType();
  int tmpState = state_;
  if (state_ == END)
    return state_;

  do
    {
      if (lookahead == true || state_ == START || state_ == NONE)
        xParser_->nextTag();

      else
        return state_;
      event_type = xParser_->getEventType();
      string tag = xParser_->getName();
      switch (event_type)
        {
        case XmlPullParser::START_DOCUMENT:
          if (state_ != START)
            error("Syntax error at the start");
          break;
        case XmlPullParser::START_TAG:
          if (xParser_->getNamespace() != wsdlUri
              && xParser_->getNamespace() != Schema::SchemaUri)
            state_ = EXTENSIBILITY;

          else if (tag == "definitions")
            state_ = DEFINITION;

          else if (tag == "documentation")
            state_ = DOCUMENTATION;

          else if (tag == "annotation")
            state_ = ANNOTATION;

          else if (tag == "import")
            state_ = IMPORT;

          else if (tag == "schema")
            state_ = SCHEMA;

          else if (tag == "types")
            state_ = TYPES;

          else if (tag == "message")
            state_ = MESSAGE;

          else if (tag == "port")
            state_ = PORT;

          else if (tag == "operation")
            state_ = OPERATION;

          else if (tag == "portType")
            state_ = PORT_TYPE;

          else if (tag == "input")
            state_ = INPUT;

          else if (tag == "output")
            state_ = OUTPUT;

          else if (tag == "fault")
            state_ = FAULT;

          else if (tag == "part")
            state_ = PART;

          else if (tag == "binding")
            state_ = BINDING;

          else if (tag == "service")
            state_ = SERVICE;

          else
            error("Unknown Tag " + tag);
          break;
        case XmlPullParser::END_TAG:
          if (tag == "definitions")
            state_ = END;

          else
            {
              /*
                If its one of the top level Wsdl elements
                set the State to NONE
              */
              if (tag == "types" ||
                  tag == "message"||
                  tag == "documentation"||
                  tag == "annotation"||
                  tag == "portType" ||
                  tag == "import" ||
                  (tag == "binding"  &&
                   state_ != EXTENSIBILITY) ||
                  tag == "service")
                return state_ = NONE;
              else
                return peek(lookahead);   //get the next tag
            }
          break;
        case XmlPullParser::TEXT:
        case XmlPullParser::ENTITY_REF:
        case XmlPullParser::COMMENT:
        case XmlPullParser::PROCESSING_INSTRUCTION:
        case XmlPullParser::CDSECT:
          xParser_->getText();
          break;
        case XmlPullParser::DOCDECL:
          error("Doc Declaration ??");
          break;
        default:
          error("Unknown Wsdl tag");
          break;
        }
    } while (event_type != xParser_->END_DOCUMENT
             && tmpState == state_  &&event_type ==
             tmp_event_type);
  return state_;
}


  //this method looks at the top level Wsdl elements
int
WsdlParser::next()
{
  try
    {
      switch (peek(false))
        {
        case START:
          element_ = START;
          break;
        case DEFINITION:
          parseDefinitions();
          peek();
          element_ = DEFINITION;
          break;
        case DOCUMENTATION:
          Doc_=parseDoc();
          element_ = DOCUMENTATION;
          break;
        case ANNOTATION:
          parseAnnotation();
          element_ = ANNOTATION;
          break;
        case IMPORT:
          parseImport();
          element_ = IMPORT;
          break;
        case TYPES:
          parseTypes();
          element_ = TYPES;
          break;
        case MESSAGE:
          parseMessage();
          element_ = MESSAGE;
          break;
        case PORT_TYPE:
          parsePortType();
          element_ = PORT_TYPE;
          break;
        case EXTENSIBILITY:
          handleExtensibilityElement(DEFINITION);
          peek();
          element_ = EXTENSIBILITY;
          break;
        case SERVICE:
          parseService();
          element_ = SERVICE;
          break;
        case BINDING:
          parseBinding();
          element_ = BINDING;
          break;
        case END:
          element_ = END;
          return state_;
        default:
          error("Syntax error");
        }
      return state_;
    }
  catch(WsdlException we)
    {
      we.line = xParser_->getLineNumber();
      we.col = xParser_->getColumnNumber();
      errorOccured_ = true;
      element_ = END;
      //      ostr.seekp(0);we loose the other errors
      //      ostr.clear();
      ostr << we.description << " at " << we.line << "," << we.col << std::endl;
      return state_ = END;
    }
  catch(XmlPullParserException xe)
    {
      //      ostr.seekp(0);
      //      ostr.clear();
      errorOccured_ = true;
      ostr<<xe.description<<std::endl;
      element_ = END;
      return state_ = END;
    }
}


  /*
    Parse a documentation tag
  */
string* 
WsdlParser::parseDoc()
{
  string*  documentation = new string();
  if (state_ != DOCUMENTATION)
    error("syntax error");

  do
    {
      xParser_->nextToken();
      if (xParser_->getEventType() == xParser_->TEXT)
        *documentation += xParser_->getText();
      if (xParser_->getEventType() == xParser_->END_TAG
          && xParser_->getName()  == "documentation")
        break;
    } while (true);
  docs_list_.push_back(documentation);
  peek();
  
  return documentation;
}


  /*
    Parse Annotation
  */
void
WsdlParser::parseAnnotation()
{
  if (state_ != ANNOTATION)
    error("syntax error");

  do
    {
      xParser_->nextToken();
      if (xParser_->getEventType() == xParser_->END_TAG
          &&xParser_->getName() == "annotation")
        break;
    } while (true);
  peek();
}


  /*Parses the definition tag
    If any extensibility namespaces are defined then the relevant
    information is stored
  */
void
WsdlParser::parseDefinitions()
{
  if (state_ != DEFINITION)
    error("syntax error");

  tnsUri_ = xParser_->getAttributeValue("", "targetNamespace");
  int i = 0;
  for (i = xParser_->getNamespaceCount(xParser_->getDepth()) - 1;
       i > xParser_->getNamespaceCount(xParser_->getDepth() - 1) - 1; i--)
    {
      if (xParser_->getNamespaceUri(i) == tnsUri_)
        tnsPrefix_ = xParser_->getNamespacePrefix(i);
      
      if (xParser_->getNamespaceUri(i) == soap_->getEncodingUri()) {
	//add the schema for soap encoding uri
	
	SchemaParser * sParser = new SchemaParser(soap_->getEncodingSchema(),
				   soap_->getEncodingUri(),ostr,schemaPath_);
	if (sParser->parseSchemaTag())
	  schemaParser_.push_back(sParser);
	
      }
      if (xParser_->getNamespaceUri(i) == soap2_->getEncodingUri()) {
	//add the schema for soap1.2 encoding uri
	
	SchemaParser * sParser = new SchemaParser(soap2_->getEncodingSchema(),
				   soap2_->getEncodingUri(),ostr,schemaPath_);
	if (sParser->parseSchemaTag())
	  schemaParser_.push_back(sParser);
      }
      
      /* 
       * Associate the extension prefixes with the handlers.
       * It is asssumed that by this time all the extensibility handlers have been registered .
       * Check if the namespace defined here matches that Uri ,whose namespace the handler handles .
       */
      for (size_t j = 0; j < wsdlExtensions_.size(); j++)
        if (wsdlExtensions_[j].we != 0 &&
            wsdlExtensions_[j].we->isNamespaceHandler(xParser_->getNamespaceUri(i)))
          {
            wsdlExtensions_[j].we->setNamespacePrefix(xParser_->
                                                      getNamespacePrefix
                                                      (i));
            //each extensibility handler allocates element ids in assigned range
            wsdlExtensions_[j].we->setStartId(MAX_EXT_XML * j + 1);

            /*
             * If there is a schema associated with the extensibility namespace
             * use the schema parser to parse its types.
             */

            SchemaParser * xtmpSchemaParser =
              new SchemaParser(wsdlExtensions_[j].we->getExtensibilitySchema(),
                               wsdlExtensions_ [j].we->getNamespace(),ostr,schemaPath_);

	    //import the wsdl definition file as many binding schemas reference it
	    xtmpSchemaParser->addImport(schemaParser_[0]);
            if (xtmpSchemaParser->parseSchemaTag())
              {
                wsdlExtensions_[j].spe = xtmpSchemaParser;
                wsdlExtensions_[j].we->
                  setSchemaParser(xtmpSchemaParser);
                wsdlExtensions_[j].we->setWsdlParser(this);
              }
            else {
	      
	      std::string err = "Error parsing the schema for the namespace ";
              err +=wsdlExtensions_[j].we->getNamespace();
	      err +="\n";
	      err +="Unable to locate the file ";
	      err += wsdlExtensions_[j].we->getExtensibilitySchema();
	      err +="\n";
              error(err);
                    
	    }
          }
    }
  int num_attr = xParser_->getAttributeCount();
  if (num_attr < 0)
    error("Atleast a targetNamespace attribute is needed");
  for (i = 0; i < num_attr; i++)
    {
      if (xParser_->getAttributeName(i) == "name")
        {
          name_ = xParser_->getAttributeValue(i);
          continue;
        }

      else if (xParser_->getAttributeName(i) != "targetNamespace")
        {                                         //this is to handle extensibility attributes
          handleExtensibilityAttributes(xParser_->getAttributePrefix(i),
                                        xParser_->getAttributeName(i));
        }
    }
  return;
}


void
WsdlParser::parseImport()
{
  if (state_ != IMPORT)
    error("syntax error");
  Imports imp (xParser_->getAttributeValue("", "namespace"),
               xParser_->getAttributeValue("", "location"));
  if (imp.ns == getNamespace() ) {
    
    std::string fname;
    ifstream wsdlStream;
    if(!imp.loc.empty())
      {
	if(XmlUtils::fetchUri(imp.loc,fname))
	  {
	    /*
	     * If the schema definition was retrieved successfully 
	     * process it and add all type definitions and
	     * declaration to the current namespace
	     */
	    wsdlStream.open(fname.c_str());
            
	    XmlPullParser * xpp = new XmlPullParser(wsdlStream);
	    XmlPullParser * tmpXparser=xParser_;
	    xParser_=xpp;

	    xParser_->setFeature(FEATURE_PROCESS_NAMESPACES, true);
	    xParser_->require(XmlPullParser::START_DOCUMENT, "", "");
	    while (getNextElement () != WsdlParser::END);
	    xParser_=tmpXparser;
	    delete xpp;
	  }else{
	    error("Error while opening the included wsdl " + imp.loc);
	  }
      }else{
	error("location is a required attribute for <import>");
      }
    imports_.push_back(imp);
    
    xParser_->nextTag();
  }
  peek();
}


void
WsdlParser::parseMessage()
{
  if (state_ != MESSAGE)
    error("syntax error");
  
  Message * m =0;
  int num_att = xParser_->getAttributeCount();
  std::string  n=xParser_->getAttributeValue("", "name");
  m=const_cast<Message*>(getMessage(n));
  if(!m){
    m= new Message(*this);
    m->setName(n);
    putMessage(m);
  }
	
  for (int i = 0; i < num_att; i++){

    if (!(xParser_->getAttributePrefix(i)).empty())
      m->addExtAttribute(handleExtensibilityAttributes
                         (xParser_->getAttributePrefix(i),
                          xParser_->getAttributeName(i)));
    
  }
  if (m->getName() == "")
    error("syntax error <message> name required");
  peek();
  try
    {
      if (state_ == DOCUMENTATION)
        {
          m->setDocumentation(parseDoc());
          //          peek();
        }

      //parse all the parts in the message
      //TODO .if a part has a type reference ,check that only one part is allowed in the message
      if (state_ == PART)
        {
          while (state_ == PART)
            {
              string p_name;
              int type_id = 0, schemaId = -1;
              Element* e=0;
              Part::PartRefType reftype = Part::None;
              int num_att = xParser_->getAttributeCount();
              int p_extId = 0;
              for (int i = 0; i < num_att; i++)
                {
                  if ("name" == xParser_->getAttributeName(i) &&
                      //Wsdl attribute name must have a null prefix
                      (xParser_->getAttributePrefix(i)).empty())
                    p_name = xParser_->getAttributeValue(i);

                  else if (("type" == xParser_->getAttributeName(i)
                            &&xParser_->getAttributePrefix(i).empty())
                           ||("element" == xParser_->getAttributeName(i)
                              &&xParser_->getAttributePrefix(i).empty()))
                    {
                      if (reftype != Part::None)
                        error
                          ("either type or element must occur(only once) in part ");
                      if ("type" == xParser_->getAttributeName(i))
                        reftype = Part::Type;

                      else
                        reftype = Part::Elem;
                      Qname type(xParser_->getAttributeValue(i));
                      type.setNamespace(getNamespace(type.getPrefix()));
                      if (reftype == Part::Type)
                        {

                          //get the type id
                          type_id = getTypeId(type);
                          if (type_id == 0)
                            error("Could not resolve type " +
                                  type.getNamespace() + ":" +
                                  type.getLocalName());
                        }

                      else
                        {
                          //get the element id
                          e   = getElement(type);
                          if (e== 0 )
                            error("Could not resolve element " +
                                  type.getNamespace() + ":" +
                                  type.getLocalName());
                        }

                      //if the ref type is "element",the id is that of a global element and not a type
                      //get the schema parser of the namespace to which "type" belongs
                      schemaId = getSchema(type,reftype == Part::Type);
                    }

                  else if (!(xParser_->getAttributePrefix(i)).empty())
                    p_extId = handleExtensibilityAttributes(xParser_->
                                                            getAttributePrefix
                                                            (i),
                                                            xParser_->

                                                            getAttributeName
                                                            (i));

                  else
                    error("Syntax error");
                }
              peek();
              if (state_ == DOCUMENTATION)
                {
                  parseDoc();
                  //                  peek();
                }
              if(reftype==Part::Elem)
                m->addPart(p_name, reftype, (void*)(e) , schemaId);
              else
                m->addPart(p_name, reftype, (void*)(&type_id) , schemaId);
              m->addExtElement(p_extId);
            }
        }
    }
  catch(WsdlException we)
    {
      we.line = xParser_->getLineNumber();
      we.col = xParser_->getColumnNumber();
      throw we;
    }

  //now parse the extensibility elements
  if (state_ == EXTENSIBILITY)
    {
      while (state_ == EXTENSIBILITY)
        {
          m->addExtElement(handleExtensibilityElement(MESSAGE));
          peek();
        }
    }


  return;
}



PortType * 
WsdlParser::parsePortType()
{
  if (state_ != PORT_TYPE)
    return 0;

  PortType * pt = new PortType(*this);
  int num_att = xParser_->getAttributeCount();
  for (int i = 0; i < num_att; i++){

    if ("name" == xParser_->getAttributeName(i) &&
	//Wsdl attribute name must have a null prefix
	(xParser_->getAttributePrefix(i)).empty())
      pt->setName(xParser_->getAttributeValue(i));

    else if (!(xParser_->getAttributePrefix(i)).empty()) {
	
      pt->addExtAttribute(handleExtensibilityAttributes
			  (xParser_->getAttributePrefix(i),
			   xParser_->getAttributeName(i)));
    }
    else {
       
      error("Syntax error.Unrecognized attribute");
    }
  }
  if (pt->getName() == "")
    error("syntax error <PortType> name required");
  
  peek();
  if (state_ == DOCUMENTATION) {
    
    pt->setDocumentation(parseDoc());
    //      peek();
  }
  if (state_ == OPERATION) {

    //parse all the operations in the port type
    while (state_ == OPERATION){

      Operation * op = parseOperation(pt);
      pt->addOp(op);
    }
    if (state_ == EXTENSIBILITY) {

      //now parse the extensibility elements
      while (state_ == EXTENSIBILITY){
	
	pt->addExtElement(handleExtensibilityElement(PORT_TYPE));
	peek();
      }
    }
  }
  putPortType(pt);
  return pt;
}


//Returns an operation element
Operation *
WsdlParser::parseOperation(PortType * p)
{
  Operation * op = new Operation(*this,p);
  if (state_ != OPERATION)
    error("syntax error");

  int num_att = xParser_->getAttributeCount();
  for (int i = 0; i < num_att; i++){

    if ("name" == xParser_->getAttributeName(i) &&
	(xParser_->getAttributePrefix(i)).empty())
      op->setName(xParser_->getAttributeValue(i));

    //Wsdl attribute name must have a null prefix

    else if (!(xParser_->getAttributePrefix(i)).empty()) {
       
      op->addExtAttribute(handleExtensibilityAttributes
			  (xParser_->getAttributePrefix(i),
			   xParser_->getAttributeName(i)));
    }

    else if ("parameterOrder" == xParser_->getAttributeName(i)) {

    }

    else
      error("Syntax error..unrecognized attribute");
  }
  if (op->getName() == "")
    error("syntax error <operation> name required");
  peek();
  if (state_ == DOCUMENTATION)
    {
      op->setDocumentation(parseDoc());
      //      peek();
    }
  if (state_ == INPUT)
    {
      op->setMessage(pgetMessage(Qname(xParser_->getAttributeValue("", "message"))),
                     Input,
		     xParser_->getAttributeValue("", "name"));

      processMessageExtensibility(op,WsdlPull::Input);
      peek();
      if (state_ == OUTPUT)
        {
          op->setMessage(pgetMessage(Qname(xParser_->getAttributeValue("", "message"))),
                         Output,
			 xParser_->getAttributeValue("", "name"));

	  processMessageExtensibility(op,WsdlPull::Output);
          peek();
        }
      while (state_ == FAULT)
        {
          op->setMessage(pgetMessage(Qname(xParser_->getAttributeValue("", "message"))),
                         Fault,
			 xParser_->getAttributeValue("", "name"));
	  
	  processMessageExtensibility(op,WsdlPull::Fault);
          peek();
        }
    }

  else if (state_ == OUTPUT)
    {
      op->setMessage(pgetMessage(Qname(xParser_->getAttributeValue("", "message"))),
                     Output,
		     xParser_->getAttributeValue("", "name"));
      processMessageExtensibility(op,WsdlPull::Output);
      peek();
      if (state_ == INPUT)
        {
          op->setMessage(pgetMessage(Qname(xParser_->getAttributeValue("", "message"))),
                         Input,
			 xParser_->getAttributeValue("", "name"));
	  processMessageExtensibility(op,WsdlPull::Input);
          peek();
        }
      while (state_ == FAULT)
        {
          op->setMessage(pgetMessage(Qname(xParser_->getAttributeValue("", "message"))),
                         Fault,
			 xParser_->getAttributeValue("", "name"));
	  processMessageExtensibility(op,WsdlPull::Fault);
          peek();
        }
    }
  if (state_ == DOCUMENTATION)
    {
      op->setDocumentation(parseDoc());
      //      peek();
    }
  if (state_ == EXTENSIBILITY)
    while (state_ == EXTENSIBILITY)
      {
        op->addExtElement(handleExtensibilityElement(OPERATION));
        peek();
      }

  //  Ops_.push_back(op);
  return op;
}


void
WsdlParser::processMessageExtensibility(Operation * op,
					WsdlPull::MessageType mtype)
{

  int num_att = xParser_->getAttributeCount();
  std::string message_name;
  for (int i = 0; i < num_att; i++){

    if ("name" == xParser_->getAttributeName(i) &&
	(xParser_->getAttributePrefix(i)).empty())
      message_name = xParser_->getAttributeValue(i);

    //Wsdl attribute name must have a null prefix

    else if (!(xParser_->getAttributePrefix(i)).empty()) {
       
      op->addMessageExtensibility(mtype,handleExtensibilityAttributes
				  (xParser_->getAttributePrefix(i),
				   xParser_->getAttributeName(i)));
    }
  }
}

void
WsdlParser::parseTypes()
{
  peek();
  if (state_ == DOCUMENTATION)
    {
      parseDoc();
      //      peek();
    }
  try
    {
      while (state_ == SCHEMA)
        {
          SchemaParser *sParser=new SchemaParser(xParser_, tnsUri_,ostr,schemaPath_);
	      sParser->setUri(uri_);
          sParser->addImport(schemaParser_[0]);//wsdl schema for wsdl namespace (wsdl:arrayType)

	  for (size_t s = 1 ;s<schemaParser_.size();s++){
	    //add the soap encoding schemas to parse elements like soap:array

	    if (schemaParser_[s]->getNamespace() == soap_->getEncodingUri())
	      sParser->addImport(schemaParser_[s]);//soap1.1 encoding schema
	    if (schemaParser_[s]->getNamespace() == soap2_->getEncodingUri())
	      sParser->addImport(schemaParser_[s]);//soap1.2 encoding schema
	  }
          
	      
			
          if (!sParser->parseSchemaTag())
            error("Error parsing schema types for "+tnsUri_);
          else
            schemaParser_.push_back(sParser);
          peek();
          error(sParser->getNamespace() +" schema parsed",2);
        }
      for (size_t i = 1; i < schemaParser_.size(); i++)
        {
       	  
          for (size_t j = 1; j < schemaParser_.size(); j++) {
			  
			   if (schemaParser_[i]->isImported(schemaParser_[j]->getNamespace()))
				   schemaParser_[i]->addImport(schemaParser_[j]);
		  }
           
		
          if (!schemaParser_[i]->finalize())
            error("Invalid schema");
        }
      
    } 
  catch(SchemaParserException spe)
    {
      WsdlException we(spe.description);
      we.col = spe.col;
      we.line = spe.line;
      we.WsdlState = state_;
      throw we;
    }
}


void
WsdlParser::putMessage(Message * m)
{

  //m->setId (nMessage++);
  messages_.push_back(m);
} 


void
WsdlParser::putBinding(Binding * bn)
{
  bindings_.push_back(bn);
} 

void
WsdlParser::putPortType(PortType * pt)
{
  porttypes_.push_back(pt);
} 


int
WsdlParser::handleExtensibilityElement(int parent)
{
  WsdlExtension * we = getExtensibilityHandler(xParser_->getNamespace());
  if (we == 0) {
    xParser_->skipSubTree();
    return 0;
  }

  else
    return we->handleElement(parent, xParser_);
}


int
WsdlParser::handleExtensibilityAttributes(string prefix, string name)
{
  WsdlExtension * we = getExtensibilityHandler(getNamespace(prefix));
  if (we == 0)
    return 0;

  else
    return we->handleAttribute(state_, name, xParser_);
}

WsdlExtension *
WsdlParser::getExtensibilityHandler(const std::string &Ns)
{
  for (size_t i = 0; i < wsdlExtensions_.size(); i++)
    if (wsdlExtensions_[i].we != 0 &&
        (wsdlExtensions_[i].we->isNamespaceHandler(Ns)))
      return wsdlExtensions_[i].we;
  return 0;
}

WsdlExtension *
WsdlParser::getExtensibilityHandler(int extId)
{

  if (extId == 0)
    return 0;

  for (size_t i = 0; i < wsdlExtensions_.size(); i++)
    if (wsdlExtensions_[i].we != 0 &&
        (extId >= wsdlExtensions_[i].we->getStartId()&&
         extId < MAX_EXT_XML + wsdlExtensions_[i].we->getStartId()))
      return wsdlExtensions_[i].we;
  return 0;
}


void
WsdlParser::parseBinding()
{

  Binding * bn = new Binding(*this);
  const PortType *pt = 0;
  int opBinding, inputBinding, outputBinding, faultBinding, index,
    bindingInfo;
  opBinding = inputBinding = outputBinding = faultBinding = index =
    bindingInfo = 0;
  if (state_ != BINDING)
    error("syntax error");
  int num_att = xParser_->getAttributeCount();
  int i;
  WsdlExtension* bindingExtension;

  for (i = 0; i < num_att; i++)
    {
      if ("name" == xParser_->getAttributeName(i) &&
          (xParser_->getAttributePrefix(i)).empty())
        bn->setName(xParser_->getAttributeValue(i));

      else if ("type" == xParser_->getAttributeName(i) &&
               (xParser_->getAttributePrefix(i)).empty())
        {
          Qname q(xParser_->getAttributeValue(i));
          pt = getPortType(q);
          if (!pt) 
            error("Unknown port type "+ q.getLocalName());
          bn->setPortType(pt);
          (const_cast<PortType*>(pt))->setBinding(bn);
        }

      else
        error("Syntax error..unrecognized attribute");
    }
  peek();

  if (state_ == DOCUMENTATION) {

    bn->setDocumentation(parseDoc());
    //      peek();
  }
  if (state_ == EXTENSIBILITY) {

    while (state_ == EXTENSIBILITY) {

      bn->setBindingInfo(bindingInfo =
			 handleExtensibilityElement(BINDING));
      bindingExtension=getExtensibilityHandler(bindingInfo);
      
      if(bindingExtension)
	bn->setBindingMethod(bindingExtension->getNamespace());
      peek();
    }
  }
  while (state_ == OPERATION){
    
    num_att = xParser_->getAttributeCount();
    const Operation *op = NULL;
    for (i = 0; i < num_att; i++){

      if ("name" == xParser_->getAttributeName(i) &&
	  (xParser_->getAttributePrefix(i)).empty()){

	Qname q(xParser_->getAttributeValue(i));
	op = pt->getOperation(q);
      }

      else
	error("Unrecognized attribute");
    }
    index = bn->addOperation(op);
    peek();

    if (state_ == DOCUMENTATION) {

      parseDoc();
    }

    while (state_ == EXTENSIBILITY) {

      opBinding = handleExtensibilityElement(OPERATION);
      if(opBinding) bn->addOpBinding(index, opBinding);
      peek();
    }

    if (state_ == DOCUMENTATION) {

      parseDoc();
    }
    if (state_ == INPUT) {

      peek();
      while (state_ == EXTENSIBILITY){
	
	inputBinding = handleExtensibilityElement(OPERATION);
	if(inputBinding) bn->addInputBinding(index, inputBinding);
	peek();
      }
    }
    if (state_ == OUTPUT) {

      peek();
      while (state_ == EXTENSIBILITY){

	outputBinding = handleExtensibilityElement(OPERATION);
	if(outputBinding) bn->addOutputBinding(index, outputBinding);
	peek();
      }
    }
    while (state_ == FAULT) {

      peek();
      while (state_ == EXTENSIBILITY){

	faultBinding = handleExtensibilityElement(OPERATION);
	peek();
	if(faultBinding) bn->addFaultBinding(index, faultBinding);
      }
    }
  }
  putBinding(bn);
}


void
WsdlParser::parseService()
{
  if (state_ != SERVICE)
    error("Syntax error");
  string serviceName;
  Service * sv = new Service(*this);
  int num_att = xParser_->getAttributeCount();
  int i;
  for (i = 0; i < num_att; i++) {

    if ("name" == xParser_->getAttributeName(i) &&
	(xParser_->getAttributePrefix(i)).empty())
      serviceName = xParser_->getAttributeValue(i);

    else
      error("Unrecognized attribute");
  }
  sv->setName(serviceName);
  peek();
  if (state_ == DOCUMENTATION) {

    sv->setDocumentation(parseDoc());
  }
  while (state_ == PORT) {

    string bnName,portName;
    Binding * bn = 0;;
    int serviceExtId = 0;
    num_att = xParser_->getAttributeCount();
    for (i = 0; i < num_att; i++) {

      if ("binding" == xParser_->getAttributeName(i) &&
	  (xParser_->getAttributePrefix(i)).empty()) {
	
	bnName = xParser_->getAttributeValue(i);
      }
      else if ("name" == xParser_->getAttributeName(i)) {
	
	portName = xParser_->getAttributeValue(i);
      }
    }
    //    Qname bindingName(bnName);
    bn = (Binding *) getBinding(bnName);
    peek();
    if (state_ == DOCUMENTATION) {
	
      parseDoc();
      //          peek();
    }
    if (state_ == EXTENSIBILITY) {
	
      serviceExtId = handleExtensibilityElement(BINDING);
      peek();
    }
    if (bn != 0)
      bn->addServiceExtId(serviceExtId);

    sv->addPort(portName,bn,serviceExtId);
  }
  services_.push_back(sv);
}


/*
 * returns the id of the schema to which "type" 
 * or "element" is defined
 */
int
WsdlParser::getSchema(const Qname & name,bool isType)
{
  Qname type = name;
  type.setNamespace(getNamespace(type.getPrefix()));

  //this is a primitve type ,simple instance of schemaparser will do. 
 if (name.getNamespace() == Schema::SchemaUri)
    return 0;        


  for (size_t i = 0; i < schemaParser_.size(); i++) {
	  
	  //check in the schema parser which defines the namespace or imports it
	  
    if( schemaParser_[i]->getNamespace() == type.getNamespace()){
			
		//check for definitions
			
      if ((isType && schemaParser_[i]->getType(name,false) != 0) ||
		(!isType && schemaParser_[i]->getElement(name,false) != 0))
 		 
    	  return i;
		
    }
     else if (schemaParser_[i]->isImported(type.getNamespace())) {


      if ((isType && schemaParser_[i]->getType(name) != 0) ||
               (!isType && schemaParser_[i]->getElement(name) != 0))

         return i;
    }
  }
  return -1;
}

Element *
WsdlParser::getElement(const Qname& name)
{
  int i = getSchema(name,false);
  if (i >= 0)
    return const_cast<Element*>(schemaParser_[i]->getElement(name));
  else
    return 0;
}

int
WsdlParser::getTypeId(const Qname & type)
{
  
  int i = getSchema(type,true);
  Qname t=type;
 
  if (i >= 0)
    return schemaParser_[i]->getTypeId(t);

  else
    return 0;
}

void
WsdlParser::getSchemaParsers(std::vector<SchemaParser* >::iterator & from,
                             std::vector<SchemaParser* >::iterator & to)
{
  
  from=schemaParser_.begin();
  from++;
  from++;
  to=schemaParser_.end();
  return ;
}

void
WsdlParser::error(string s,int level)
{
  if(level==0){

    WsdlException we(s);
    if(xParser_){

      we.line = xParser_->getLineNumber();
      we.col = xParser_->getColumnNumber();
    }
    we.WsdlState = state_;
    errorOccured_ = true;
    throw we;
  }
#ifdef LOGGING
  else if (level == 1) {

    ostr<<"Wsdl parser warning : "<<s<<endl;
  }
  else if (level == 2) {

    ostr<<"Wsdl parser info : "<<s<<endl;
  }
#endif
}

bool
WsdlParser::getBindings(Binding::cBindingIterator & begin,
                        Binding::cBindingIterator & end)const
{
  if(bindings_.size()>0){
    
    begin=bindings_.begin();
    end=bindings_.end();
    return true;
  }
  else
    return false;
}

bool
WsdlParser::getPortTypes(PortType::cPortTypeIterator& begin,
                         PortType::cPortTypeIterator& end)const
{
  if(porttypes_.size()>0){
    
    begin=porttypes_.begin();
    end=porttypes_.end();
    return true;
  }
  else
    return false;
}

int
WsdlParser::getNumSchemas() const
{
  return schemaParser_.size() - 2;
  //soap-enc and wsdl schema are parsed by default
}

void
WsdlParser::setSchemaPath(const std::string & schemaPath)
{
	schemaPath_ = schemaPath;
	
	for (vector<ExtensionInfo>::iterator ie = wsdlExtensions_.begin();
	     ie != wsdlExtensions_.end();
	     ie++)
	  ie->we->setSchemaPath(schemaPath);
	
	//	soap_->setSchemaPath(schemaPath);
}

}
