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


#ifndef _SOAPEXTH
#define _SOAPEXTH

#include <iostream>
#include <fstream>

#include "wsdlparser/WsdlExtension.h"
#include "wsdlparser/WsdlParser.h"
#include "schemaparser/SchemaValidator.h"
#include "xmlpull/wsdlpull_export.h"

namespace WsdlPull {



class WSDLPULL_EXPORT Soap:public WsdlExtension
{
 public:
  
  static const std::string httpTransport;
  static const std::string httpBinding ;
  static const std::string soapEncUri11 ;
  static const std::string soapEnvUri11 ;
  static const std::string soapEncUri12 ;
  static const std::string soapEnvUri12 ;
  static const std::string soapBindingUri11;
  static const std::string soapBindingUri12 ;

  typedef enum  {
    SOAP11,
    SOAP12
  } SoapVersion;

  typedef enum
    {
      LITERAL,
      ENCODED
    } Encoding;
  
  typedef enum
    {
      RPC,
      DOC
    } Style;

  typedef enum
    {
      NONE,
      HTTP,
      SMTP
    } Transport;

  Soap(const std::string & schemaPath = "", SoapVersion a_soapVersion = SOAP11);
  virtual ~Soap();

  /**
   * Set path to directory containing XML schemas.
   */
  void setSchemaPath(const std::string & schemaPath);

  Transport getTransportMethod()const;
  Style getStyle()const;
  /*
    Returns the namespace URI of the wsdl
    extensibility elements that it can handle.
  */
  std::string getNamespace()const ;
  void setNamespacePrefix(std::string pre);
  std::string getNamespacePrefix()const;
  bool isNamespaceHandler(const std::string & ns)const;
  std::string getExtensibilitySchema(void)const;
  std::string getEncodingSchema(void)const ;
  std::string getEncodingUri(void) const;
  std::string getEnvelopeUri(void) const;
  void setSchemaParser(SchemaParser * spe);

  // parent is the Wsdl parent element type under which the extensibility element has come
  int handleElement(int parent, XmlPullParser *);
  //attName is the extensibility attribute
  int handleAttribute(int parent, std::string attName, XmlPullParser *);
  //returns a valid extensibilty element
  int getElementName(int id)const;
  int getElemAttribute(int id, int att_num);
  int getElemAttributeValue(int id, int att_num);
  //returns a valid extensibility attribute
  int getAttributeName(int id)const;

  //this is the start of all ids that must be used for elems/attributes in this namespace
  void setStartId(int id);
  int getStartId()const;

  void setWsdlParser(WsdlParser * wp);
  WsdlParser * wsdlParser()const;
  bool wasUsed()const;

  void serialize(std::ostream & out);
  void getSoapOperationInfo(int elemId, std::string & soapAction, Soap::Style& style);
  void getSoapBodyInfo(int elemId, std::string &ns, Soap::Encoding &use, std::string &encodingStyle);
  void getSoapHeaderInfo(int elemId, std::string &ns, int &partId, const Message* & m);
  bool  getServiceLocation(int elemId, std::string &location);

  SoapVersion getSoapVersion() const { return soapVersion_; }
  
  //TODO add more methods like this
  bool isSoapBody(int id);
  bool isSoapHeader(int id);

  /*
    Enums used in soap
  */

 private:
  void error(std::string);
  int processBinding(TypeContainer * t);
  int processOp(int, TypeContainer * t);
  int processBody(int, TypeContainer * t);
  int processHeader(int, TypeContainer * t);
  int processFault(int, TypeContainer * t);
  int processAddress(int parent, TypeContainer * t);
  std::string sNamespace, sNsPrefix, sTitle;
  int startId;
  SchemaParser *mySchemaParser;
  SchemaValidator *mySchemaValidator;
  WsdlParser *wParser_;
  
  typedef struct  
  {
    int typeId;
    int index;
  }IDTableIndex ;

  std::vector<IDTableIndex> idTable;
  int idCounter;

  typedef struct
  {
    int wsdlOpId;
    std::string soapAction;
    Style style;
  } SoapOperationBinding;
  std::vector<SoapOperationBinding> ops_;

  typedef struct
  {
    int messageId;
    Encoding use;
    std::string encodingStyle;
    std::string urn;
  } SoapMessageBinding;
  std::vector<SoapMessageBinding> body_;
  //  int nMsgs;

  typedef struct
  {
    std::string urn;
    int partId_;
    const Message* message_;
  }SoapHeaderBinding;
  std::vector<SoapHeaderBinding> header_;
  //  int nHeader;

  Transport transport_;
  Style style_;
  std::vector<std::string> location_;
  std::string schemaPath_;

  SoapVersion soapVersion_; //The SOAP version to use
};

inline 
int
Soap::getElementName(int id)const
{
    if (id < startId || id > (startId + idCounter - 1))
        return 0;
    return idTable[id - startId].typeId;
}


inline
int
Soap::getAttributeName(int id)const
{
    if (id < startId || id > (startId + idCounter - 1))
        return 0;
    return idTable[id - startId].typeId;
}

inline
std::string
Soap::getNamespace()const 
{
  return sNamespace;
}

inline
void
Soap::setNamespacePrefix(std::string pre)
{
  sNsPrefix = pre;
}

inline
std::string
Soap::getNamespacePrefix()const
{
  return sNsPrefix;
}

inline
bool
Soap::isNamespaceHandler(const std::string & ns)const
{
  return (ns == sNamespace);
}

inline
void
Soap::setSchemaParser(SchemaParser * spe)
{
  mySchemaParser = spe;
  mySchemaValidator = new SchemaValidator(mySchemaParser);
}

inline
void
Soap::setStartId(int id)
{
  startId = id;
}

inline
int
Soap:: getStartId()const
{
  return startId;
}

inline
void
Soap::setWsdlParser(WsdlParser * wp)
{
  wParser_ = wp;
}

inline
bool
Soap::wasUsed()const
{
  return (wParser_ != 0);
}

inline
Soap::Transport
Soap::getTransportMethod()const
{
  return transport_;
}

inline
Soap::Style
Soap::getStyle()const
{
  return style_;
}

inline
WsdlParser *
Soap::wsdlParser()const
{
  return wParser_;
}

}
#endif                                            /*  */
