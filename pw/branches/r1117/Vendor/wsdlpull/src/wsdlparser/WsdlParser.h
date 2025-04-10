/* 
 * Wsdlpull - A C++ parser  for WSDL  (Web services description language)
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
#ifndef _WSDLPARSERH
#define _WSDLPARSERH

#include "xmlpull/wsdlpull_export.h"
#include "xmlpull/XmlPullParser.h"
#include "xmlpull/XmlPullParserException.h"
#include "schemaparser/SchemaParser.h"

#include "wsdlparser/PortType.h"
#include "wsdlparser/Message.h"
#include "wsdlparser/Operation.h"
#include "wsdlparser/Binding.h"
#include "wsdlparser/Service.h"
#include "wsdlparser/WsdlExtension.h"



namespace WsdlPull{

  const std::string wsdlUri="http://schemas.xmlsoap.org/wsdl/";

class Soap;
//Wsdl pull parser
class WSDLPULL_EXPORT WsdlParser
{
 public:
  /** @name Constructors and Destructors */
  //@{
  /**
   * The default constructor for WsdlParser
   * @param input stream for the wsdl file
   * @param output stream for any error outputs
   * @param schemaPath path to directory containing XML schema files
   *
   */
  WsdlParser(std::istream & in = std::cin, std::ostream & out = std::cout,
             const std::string & schemaPath = "");
  WsdlParser(const std::string& Uri,std::ostream & out = std::cout,
             const std::string & schemaPath = "");
  ~WsdlParser();
  //@}

  /**
   * setSchemaPath
   * Set path to location of XML schema files, used by parser.
   */
  void setSchemaPath(const std::string & schemaPath);

    /** @name methods used for parsing */
  //@{
  /**
   * getNextElement processes the next Wsdl ELement in the stream and
   * returns the type of the root Wsdl element parsed.
   * @return  one of  START,DEFINITION,DOCUMENTATION,ANNOTATION,
   *            TYPES,MESSAGE,PORT_TYPE,BINDING,SERVICE,IMPORT
   */
  int getNextElement();

  /**
   * getEventType
   * returns the type Wsdl element parsed.
   * @return  one of the Wsdl event types
   */
  int getEventType();

  //@}

  /** @name Various Getter methods*/
  //@{
  //NOTE:The caller must *NOT* free the pointers returned by the getter apis
  //This is true for all apis except whenever the api returns a pointer to 
  //a list of elements which is not one  of the root wsdl elements ,
  //such as getOperations(port type) which is the only exception
  /**
   * getTargetNamespace
   * @return target namespace of the wsdl document
   */
  std::string getNamespace(void);

  /**
   * getName
   * @return name of the wsdl document
   */
  std::string getName();

  /**
   * getDocumentation Returns the documentation string for the WSDL file
   *                  This method must be called after <code>getEventType</code> returns DOCUMENT
   * @return documentation std::string .
   */
  const std::string*  getDocumentation();

  /**
   * getBinding .This method must be called after
   *  <code>getEventType</code> returns BINDING
   * @return reference to the Binding element just parsed.
   * @exception WsdlException
   */
  const Binding *getBinding();

  /**
   * getBinding .
   * @param Qname refering to the binding element
   * @return reference to the Binding element
   * @exception WsdlException
   */
  const Binding *getBinding(const Qname & q);

  /**
   * getBindings
   * @return iterator to a list of binding elements
   * @exception WsdlException
   */
  bool  getBindings(Binding::cBindingIterator & begin,
		    Binding::cBindingIterator & end)const;

  /**
   * getService .This method must be called after
   *  <code>getEventType</code> returns SERVICE
   * @return reference to the Binding element just parsed.
   * @exception WsdlException
   */
  const Service *getService();

  /**
   * getService.
   * @param Qname refering to the service element
   * @return reference to the Service element
   * @exception WsdlException
   */
    typedef std::list<Service*>::iterator ServiceIterator;
  const Service *getService(const Qname & q);
    void getServices(ServiceIterator &from, ServiceIterator &to);

  /**
   * getPortType .This method must be called after
   *  <code>getEventType</code> returns PORT_TYPE
   * @return reference to the port type element just parsed.
   * @exception WsdlException
   */
  const PortType *getPortType();

  /**
   * getPortType
   * @param Qname refering to the port type element
   * @return reference to the port type element
   * @exception WsdlException
   */
  const PortType *getPortType(const Qname & q);

  /**
   * getPortTypes
   * @return iterators to a container of port types
   * @exception WsdlException
   */
  bool getPortTypes(PortType::cPortTypeIterator& begin,
		    PortType::cPortTypeIterator& end)const;

  /**
   * getOperations
   * @param Qname refering to the port type element
   * @return true if the port type is found.
   returns the start and ending iterators to operations
   * @exception WsdlException
   */
  bool getOperations(const Qname & portType,
		     Operation::cOpIterator& begin,
		     Operation::cOpIterator& end);

  /**
   * getOperation
   * @param Qname refering to the port type element
   * @param Qname refering to the operation element
   * @return reference to the operation element
   * @exception WsdlException
   */
  const Operation *getOperation(const Qname & portType, 
				const Qname & q);

  /**
   * getMessage .This method must be called after
   *  <code>getEventType</code> returns MESSAGE
   * @return reference to the message element just parsed.
   * @exception WsdlException
   */
  const Message *getMessage();

  /**
   * getMessage .
   * @param Qname of the message element
   * @return reference to the message element
   * @exception WsdlException
   */
  const Message *getMessage(const Qname & q);

  /**
   * getMessages
   * @return list of all messages  parsed.
   * @exception WsdlException
   */
  std::list < const Message *>& getMessages();

  /**
   * getSchemaParsers
   * @return iterators to list of schema parsers 
   *         the first element is the start of the list
   *         second being the end of it
   * @exception WsdlException
   */

  void getSchemaParsers(std::vector<SchemaParser* >::iterator & from,
                        std::vector<SchemaParser* >::iterator & to) ;
  
  /**
   * getNumSchemas
   * @return number of schemas in the wsdl document
   * @exception WsdlException
   */
  int getNumSchemas() const;

  /**
   * getSchemaParser
   * @param target namespace of the schema
   * @return pointer to the schema parser for the namespace
   * @exception WsdlException
   */
  const SchemaParser *getSchemaParser(std::string targetNamespace) const;


  /**
   * to query the status of wsdl parsing
   */
  bool status()const;
  std::string wsdlPath()const;
  std::ostream & logger();
  std::string &getWsdlFileName() {
    return wsdlFileName;
  }
  
  static bool useLocalSchema_;//if false fetch the schemas from the web
  //@}

  
  /** @name Extensibility handler methods*/
  //@{
  /**
   * addExtensibilityHandler Registers an extensibility handler
   *                         for Wsdl extensibility namespaces
   * @param pointer to the instance of WsdlExtension
   * @exception WsdlException
   */
  void addExtensibilityHandler(WsdlExtension * ext);
  /**
   * getExtensibilityHandler returns theextensibility handler
   *                         for the namespaces
   * @param namespace
   * @exception WsdlException
   */
  WsdlExtension *  getExtensibilityHandler(const std::string & ns);
   //return the extensibility handler for the given id.
   //WsdlParser only stores ids for the extensibility elements.
  WsdlExtension * getExtensibilityHandler(int extId);
  //@}

 
  /** @name Miscellaneous methods*/
  //@{
  /**
   * setFeature enables one of the features of the parser
   * @return   true or false 
   */
  bool setFeature (int feature_id);
  //@}


  /**
   *The various states of the Wsdl Parser
   */
  enum
    {
      NONE ,
      START,
      DEFINITION,
      DOCUMENTATION,
      ANNOTATION,
      IMPORT,
      SCHEMA,
      TYPES,
      MESSAGE,
      PART,
      PORT_TYPE,
      OPERATION,
      INPUT,
      OUTPUT,
      FAULT,
      BINDING,
      EXTENSIBILITY,
      SERVICE,
      PORT,
      END
    };

#ifdef LOGGING
  //for debugging
  void print(std::ostream & out);
#endif

  //{@ Deprecated
  /**
   * getSchemaParser
   * @param index of the schema parser .index:0..getNumSchemas-1
   * @return pointer to the schema parser for the namespace
   * @exception WsdlException
   */
  const SchemaParser *getSchemaParser(int schemaId) const;
  //@}


 private:
  /* 
   *  private methods for parsing
   */
  int peek(bool lookahead = true);
  int next();
  void error(std::string s,int level=0);
  std::string getNamespace(std::string prefix);
  Element * getElement(const Qname &);
  int getTypeId(const Qname &);
    int getSchema(const Qname & name,bool type = true);
  std::string* parseDoc();
  void parseDefinitions();
  void parseMessage();
  void parseAnnotation();
  void parseImport();
  PortType *parsePortType();
  Operation *parseOperation(PortType* p);
  void processMessageExtensibility(Operation * op,
				   WsdlPull::MessageType mtype);
  void parseTypes();
  void parseBinding();
  void parseService();
  int handleExtensibilityAttributes(std::string prefix, std::string name);
  int handleExtensibilityElement(int);
  void putMessage(Message * m);
  void putPortType(PortType * pt);
  void putBinding(Binding * bn);
  void initialize(bool);
  bool errorOccured_;
  XmlPullParser* openSchemaFile(const std::string& path);
  const Message *pgetMessage(const Qname& q);
  std::string name_, tnsPrefix_, tnsUri_;
  std::vector<SchemaParser*> schemaParser_;

  typedef struct
  {
    WsdlExtension *we;
    SchemaParser *spe;
  } ExtensionInfo;
  std::list < const Message *> messages_;
  std::vector<ExtensionInfo> wsdlExtensions_;
  std::list < PortType *>porttypes_;
  std::list < Binding *>bindings_;
  std::list < Service*> services_;

  class Imports
  {
  public:
    Imports(std::string,std::string);
    std::string ns, loc;
  };
  std::vector<Imports> imports_;
  std::list < std::string *> docs_list_;
  std::ostream & ostr;
  std::istream & istr;
  int state_;
  int element_;                            //the last Wsdl element parsed
  std::string* Doc_;
  XmlPullParser * xParser_;
  std::ifstream xmlStream;
  std::string wsdlFileName;
  Soap * soap_,*soap2_;
  const int MAX_EXT_XML;
  std::string schemaPath_; // Path to schemas, used by parser during parsing.
  std::string uri_; //The uri to use to resolve imports.1 level up the location of the wsdl file
};


inline
WsdlParser::Imports::Imports(std::string nameSpace,std::string location)
  :ns(nameSpace),
     loc(location)
{
}


inline
std::string
WsdlParser::getNamespace(std::string prefix)
{
  return xParser_->getNamespace(prefix);
}


//public  APIs
inline
int  
WsdlParser::getNextElement()
{
  next();
  return element_;
}

inline
const std::string*
WsdlParser::getDocumentation() 
{
  return  (const std::string*) Doc_;
}

inline
std::string
WsdlParser::getNamespace(void)
{
  return tnsUri_;
}

inline
std::string
WsdlParser::getName()
{
  return name_;
}



inline
int
WsdlParser::getEventType()
{
  return element_;
}


inline
std::list < const Message *>&
WsdlParser::getMessages()
{
  return messages_;
}

//This is deprecated
//the ids 0 and 1 are return the schema parsers used to internally parse the soap schema.
//Ideally you should use getSchemaParser(std::string).If you want to iterate over all the schema parsers
//use getSchemaParsers
inline
const SchemaParser *
WsdlParser::getSchemaParser(int schemaId) const
{
  return (const SchemaParser *) schemaParser_[schemaId];
}

inline
std::string
WsdlParser::wsdlPath()const
{
  return wsdlFileName		;
}
inline
bool
WsdlParser::status()const
{
 return !errorOccured_;
}

inline
std::ostream&
WsdlParser::logger()
{
  return ostr;
}
}
/*  */
#endif                                            /*  */
