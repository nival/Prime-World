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

//An api to examine and invoke the web service in a protocol independent fashion

#ifndef _WSDLINVOKERH
#define _WSDLINVOKERH

#include "xmlpull/XmlSerializer.h"
#include "wsdlparser/WsdlParser.h"
#include "wsdlparser/Soap.h"
#include "xmlpull/wsdlpull_export.h"

#include "xmlpull/XmlDoc.h"

namespace WsdlPull{

 struct Parameter
 {
   Parameter(Schema::Type ,std::string,int m,int x,const SchemaParser* s,
             const std::vector<std::string>& parents);
   Schema::Type type_;
   std::string tag_;
   unsigned int min_;
   unsigned int max_;
   int n_;
   std::vector<std::string> data_;
   //bool str_;
   const SchemaParser* sParser_;
   std::vector<std::string> parents_;

 };

class WSDLPULL_EXPORT WsdlInvoker
{
 public:
  /** @name Constructors and Destructors */
  //@{
  /**
   * The default constructor for WsdlInvoker
   * @param wsdl url
   * @param stream for logging errors
   */

  WsdlInvoker(const std::string &url, const std::string &schemaPath="");
  WsdlInvoker(std::istream &input, const std::string &schemaPath = "");
  WsdlInvoker();
  ~WsdlInvoker();
  //@}

  /** @name WSDL Inspection*/
  //@{
  /** setWSDLUri
   * set the url of the wsdl file to be processed
   * @param url for the wsdl file
   * @param optional path to schema files required to parse wsdl extensions (soap,http) 
   */
  bool setWSDLUri(const std::string &url, const std::string & schemaPath="");
  /** getOperations
   *  @param reference to vector<string>
   *  @brief return names of operations (only for the SOAP binding portType)
   *  @return int ,number of operations
   */
  int getOperations(std::vector<std::string> & operations);
  std::string getOpDocumentation(const std::string & n);
  std::string getDocumentation();
  /** setOperation
   *  @param operation name to invoke
   *  @brief set the operation to invoke
   *  @return bool ,true if successful
   */
  bool setOperation(const std::string & operation,
		    WsdlPull::MessageType mType = WsdlPull::Input);
  /** getServiceEndPoint
   *  returns the url to be invoked for the operation
   */
  std::string getServiceEndPoint(const std::string & opname) ;
  //@}


  /** @name Simple Invocation usage*/
  //@{ 
  
  /** setValue
   *  @brief sets the param value for an operation by name of the parameter
   *  @param name of the operation's parameter
   *  @param string/void*  representation of the parameter
   *  @return true if successful,false if the values didnt match or occurrence constraint failed
   *  example invoker.setInputValue("symbol","ABC") or 
   *  int zip = 94018; invoker.setInputValue("zip",(void*)(&zip));
   *  Note that "symbol" or "zip" above can be a message part or a constituent particle in a complex type
   *  The API takes care of it.
   */
  bool setValue(const std::string & param,void* val);
  bool setValue(const std::string & param,void** values,unsigned int occur);
  bool setValue(const std::string & param,std::string val);
  bool setValue(const std::string & param,std::vector<std::string> values);//multiple occurrences
  bool setValue(const std::vector<std::string> & parents,void* val);
  /** invoke
   *  invoke the web service operation
   @param timeout set the timeout for the request in seconds
   *  @return true if successful,false otherwise
   */
  bool invoke(long timeout = 0,bool processResponse = true);
  /** getValue
   *  return the value of the output whose name is 'param'
   *  @param type is set by reference to enable type casting in client code
   *  @return pointer to the value or 0 if there is no simple type or part name 
   *  whose name is 'param' in  the web service output.
   *  example  float * val = (int*) invoker.getOutput("Result",t);//stock quotes
   *  t would be Schema::FLOAT
   */
  void* getValue(const std::string & param,Schema::Type & t); 


  /** getValue
   *  return the value based on an xpath like expression
   *  @param xpath - the xpath expression or an element name which leads to a simple type element or attribute
   *                 if it points to a simple type element,the element's text is returned, if it points to the attribute 
   *                 the attribute is returned
   *
   *                  /login/result/header/errorCode -> will do an absolute from the root node
   *                   result/header/errorCode -> will do a relative match starting with "result"
   *                   result//errorCode -> will return all "errorCode" under "result"
   *                   //errorCode will return all "errorCode" from the root node
   *                   result/@type -> will return attribute value of type for element result
   *  @param p_index - default value "1". Return the conten stored in the "Nth" node when several nodes that would match
   *                   the xpath expression are found. It starts at "1" to comply with W3C Xpath standards
   *                   A value of "0" would return the content of ll matching nodes, but this function does only
   *                   return one "content"
   *  @return - The value , an empty string is returned if the xpath expression doesnt lead to some CDATA
   *            Exception is thrown if this method is called when the status() returns false or web service response is 
   *            empty
   *  example   float getValue<float>('StockQuoteResponse/quote')
   */
  template <typename T>
  T  getValue(const std::string & xpath, size_t p_index = 1);  

  /* identical to previous method but returns multiple matches if found in the document*/
  template <typename T>
  std::vector<T>  getValues(const std::string & xpath);  
  //@} 
  
  /** @name A more complex but  powerful usage*/
  //@{ 
  
  /** getNextInput
   *  Calling this method repeatedly informs the caller
   *   of the input types the web service operation expects.
   *   Each call returns a unique id which must be used while setting the
   *   value using setInputValue.This method exposes only atomic types.Even if 
   *   a web service needs a complex type,the api exposes only the constituent
   *   particles.The only exception is when a complex content model needs multiple
   *   occurrences which is still a TODO
   *  @param ref:param name  Name of the param
   *  @param ref:Schema::Type ,the schema type 
   *  @param ref: minimum and maximum (occurrences)
   *  @param ref:parents, parent list of type hierarchy for this parameter.
   *  @return unique id of this parameter
   */
  int getNextInput(std::string & param ,Schema::Type & type,int & minimum,int & maximum);
  int getNextInput(std::string & param ,Schema::Type & type,int & minimum,int & maximum,
                   std::vector<std::string>& parents);
  /**
   * getNextHeaderInput
   * Similar to the previous method except that it gets the SOAP headers if any
   * Set methods are same as for regular inputs
   */
  int getNextHeaderInput(std::string & param ,Schema::Type & type,int & minimum,int & maximum);
  int getNextHeaderInput(std::string & param ,Schema::Type & type,int & minimum,int & maximum,
			 std::vector<std::string>& parents);
  /**
   * returns the number of input headers you may need to set
   */
  int nInputHeaders()const;
  
  /** setInputValue
   *  sets the param value for an operation
   *         only simple types can be set.
   *  @param id return by getNextInput()
   *  @param void ** pointer to array of pointers to the the values
   *  @return true if successful,false if the values didnt match or occurrence constraint failed
   */
  bool setInputValue(const int param,void* val);
  bool setInputValue(const int id,void** values,unsigned int occur);

  /** setInputValue
   *  sets the param value for an operation
   *         only simple types can be set.
   *  @param id return by getNextInput()
   *  @param string representation of the parameter
   *  @return true if successful,false if the values didnt match or occurrence constraint failed
   */
  bool setInputValue(const int param,std::string val);
  bool setInputValue(const int param,std::vector<std::string> values);//multiple occurrences

  /** getNextOutput
   *  get the part/elem name and type container
   * @return false when we finished iterating through all outputs
   *         after which it rewinds and you can start again
   */
  bool getNextOutput(std::string  & name,TypeContainer * & tc);
  
  /** getOutput
   *   return the type container which stores the output
   *   for the output part/elem name
   */
  TypeContainer* getOutput(const std::string  & name);
  
  /** getNextHeaderOutput
   *  get the type container which stores the SOAP header
   * @return false when we finished iterating through all outputs
   *         after which it rewinds and you can start again
   */
   bool getNextHeaderOutput(std::string & name,TypeContainer*& tc);

  //@} 
   // change location of the service
  void setLocation(const std::string  & url);
  // set credentials for the service
  void setCredentials(const std::string & user, const std::string & pass);
  // set http authentication for the service
  void setAuth(const std::string & user, const std::string & pass);
  //ouput the soap message without invoking the service
  std::string getSoapMessage();
  std::string getXMLResponse();
  void setProxy(const std::string & host,int  port=80);
  //enable logging
  void setVerbose(bool f);
  // prints the output along with typenames like
  // name:value.
  //if false only value is printed
  void printTypeNames(bool f);
  //get the error message
  std::string errors();
  //if this returns false something went wrong
  bool status()const;

  //get SOAP fault related things
  std::string getFaultCode() const;
  std::string getFaultSubCode() const;
  std::string getFaultString() const;
  std::string getFaultActor() const;

  // Control XML Tree Generation and Xpath search fine tuning
  void setProcessEnvAndBody( bool p_processEnvAndBody);
  bool getProcessEnvAndBody( void) const;

  void setLazyRelativeMatch( bool p_lazyRelativeMatch);
  bool getLazyRelativeMatch( void) const;

  void setBuildXmlTree( bool p_buildXmlTree);
  bool getBuildXmlTree( void) const;
  void buildXmlTree( XmlPullParser &p_xmlPullParser, XmlNode_t &p_xmlNode,
		     bool p_notScannedEventAvail = false);

 private:
  //private stuff 

  bool init(WsdlParser* parser);
  //creaate xml request
  void serialize();
  void serializeType(Schema::Type typeId,
		     const std::string &tag,
		     const SchemaParser * sParser,
                     int minimum,
                     int maximum,
		     std::vector<std::string> parents,
		     const std::string nsp="",
		     bool isRoot = false);

  void serializeParam(int n,const std::string & tag,
		      const SchemaParser * sParser,
		      const std::string nsp="",
		      bool isRoot = false);
  void serializeContentModel(ContentModel *cm,
			     const SchemaParser *sParser,
			     std::vector<std::string> parents);
  /** create xml request 
    and do the http post request 
    @param timeout in seconds default 0 -> no timeout
    **/
  void post(long timeout=0, std::string username="", std::string passwd="");
  void processResults();
  void processFault(XmlPullParser* xpp);
  void processHeader(XmlPullParser *xpp);
  void processBody(const Message* m,XmlPullParser* xpp);
  void parseWsdl(const std::string & url, const std::string & schemaPath = "");
  void serializeHeader();
  bool isSoapArray (const ComplexType * ct,const SchemaParser * sParser);
  //reset state information
  void reset();
  void getOperationDetails(const Operation* op);
  std::string getPrefix(const std::string& nsp);
  std::string getAsStringFromXPath(const std::string & xpath, size_t p_index, std::vector<std::string>* arr = 0);
  bool isSubTreeNil();
  WsdlParser * wParser_;
  std::string strResults_;
  WsdlParser * ourParser_;
  XmlSerializer * xmlStream_;
  Soap* soap_;
  bool soapheaders_;
  int hPartId_;
  std::string hnsp_;
  std::ostringstream * soapstr_;
  std::ostringstream logger_;
  bool status_;
  bool serializeMode_;
  bool verbose_;
  bool dontPost_;
  int oHeaders_;
  std::map<std::string,const Operation*> opMap_;
  const Operation* op_;
  Soap::Encoding use_;//literal or encoded
  std::string encodingStyle_; // this is usually the soap encoding style
  Soap::Style style_;//rpc or doc
  std::string nsp_; // namespace for the operation
  std::string location_;
  std::string username_,password_,host_;
  int port_;
  std::string action_;//SOAPAction header
  std::vector<Parameter> elems_;//the simple types
  size_t n_;//a counter to iterate through the element params
  int iHeaders_; //number of soap header inputs
  std::vector<std::pair<std::string,TypeContainer*> > outputs_;
  std::vector<const XSDType* > avoidrecurse_;
  WsdlPull::MessageType messageType_;

  std::vector<std::string> prefixes_;
  bool bAuth;
  std::string sAuthUser;
  std::string sAuthPass;

  std::string sFaultCode;
  std::string sFaultSubCode;
  std::string sFaultString;
  std::string sFaultActor;
  void* ctx;//for connection purposes

  bool m_buildXmlTree;
  bool m_xmlTreeProduced;
  XmlDoc_t m_xmlDoc;
};

inline
Parameter::Parameter(Schema::Type t,std::string n,int m,int x,const SchemaParser* s,
		     const std::vector<std::string>& parents)
  :type_(t),
     tag_(n),
     min_(m),
     max_(x),
     n_(0),
     sParser_(s),
     parents_(parents)
     
{
}

inline
std::string 
WsdlInvoker::errors()
{
  return logger_.str();
}

inline
bool
WsdlInvoker::setWSDLUri(const std::string &url,const std::string & schemaPath)
{
  parseWsdl(url,schemaPath);
  return status_;
}

inline
bool
WsdlInvoker::status()const
{
  return status_;
}

inline 
void
WsdlInvoker::setLocation(const std::string  & url)
{
  location_ = url;
}

inline
void
WsdlInvoker::setVerbose(bool f)
{
  verbose_ = f;
}

inline
int
WsdlInvoker::nInputHeaders()const
{
  return iHeaders_;
}

inline
std::string
WsdlInvoker::getFaultCode() const
{
  return sFaultCode;
}

inline
std::string
WsdlInvoker::getFaultSubCode() const
{
  return sFaultSubCode;
}

inline
std::string 
WsdlInvoker::getFaultString() const
{
  return sFaultString;
}

inline
std::string 
WsdlInvoker::getFaultActor() const
{
  return sFaultActor;
}


template<typename T>
inline T
WsdlInvoker::getValue(const std::string & xpath, size_t p_index) 
{
  
  T val;
  std::string v = getAsStringFromXPath(xpath, p_index);
  std::istringstream iss(v);
  iss>>val;
  return val;
}

template<>
inline std::string
WsdlInvoker::getValue<std::string>(const std::string & xpath, size_t p_index) 
{
  
  return getAsStringFromXPath(xpath, p_index);

}

template <typename T>
inline std::vector<T>
WsdlInvoker::getValues(const std::string & xpath)
{
  std::vector<std::string> arr ;
  std::vector<T> arrT;
  getAsStringFromXPath(xpath, 0, &arr);
  T val;
  for (size_t s = 0 ;s<arr.size();s++){
    
    
    std::istringstream iss(arr[s]);
    iss>>val;
    arrT.push_back(val);
  }
  return arrT;
}

//specialization for string
template<>
inline 
std::vector<std::string>
WsdlInvoker::getValues<std::string>(const std::string & xpath)
{
  std::vector<std::string> arr ;
  getAsStringFromXPath(xpath, 0, &arr);
  return arr;
}


}
#endif
