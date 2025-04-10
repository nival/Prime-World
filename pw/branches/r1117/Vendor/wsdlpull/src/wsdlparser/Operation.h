/* 
 * wsdlpull - A C++ parser  for Wsdl  (Web services description language)
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
#ifndef _OPERATIONH
#define  _OPERATIONH

#include "xmlpull/Qname.h"

#include "wsdlparser/WsdlException.h"
#include "wsdlparser/WsdlElement.h"
#include "wsdlparser/Message.h"
#include "xmlpull/wsdlpull_export.h"


namespace WsdlPull {

enum Optype{
  OP_NONE,
  OP_IN ,
  OP_OUT,
  OP_IN_OUT,
  OP_OUT_IN
};
 
enum MessageType{

  Input,
  Output,
  Fault
};

typedef std::list<const Message*> MessageList;
typedef std::map<const Message *, std::string> MessageNameList;
class PortType;
//class for Wsdl operation element
class WSDLPULL_EXPORT Operation:public WsdlElement
{
 public:
  typedef std::vector<Operation*>::iterator OpIterator;
  typedef std::vector<Operation*>::const_iterator cOpIterator;

  Operation(WsdlParser& w,PortType * pt);
  ~Operation();
  /** @name Various Getter methods*/
  //@{

  /**
   * getMessage
   * @param mesage type ,Input,Output or Fault
   * @return pointer to the message
   */
  const Message *getMessage(WsdlPull::MessageType type) const;
  //get the input/output/fault element's name
  std::string getMessageName(WsdlPull::MessageType type) const;
  std::list<const Message*>* getFaults()const;
  const Message* getFault(const std::string& name)const;
  /**
   * getOptype
   * @return type of the operation in,in-out,out,out-in
   */
  Optype getType() const;
  
  /**
   * portType
   * @return The porttype to which this operation belongs
   */
  const PortType* portType()const;

  //@}/** @name Various Setter methods*///@{
  void setMessage(const Message * message, WsdlPull::MessageType type,
		  const std::string & name = "");
  void addMessageExtensibility(WsdlPull::MessageType m,int ext);
  int getMessageExtension(WsdlPull::MessageType m);

  //@}
  void print(std::ostream & out);

 private:
  PortType * pt_;
  Optype type_;
  const Message *inMessage_, *outMessage_;
  std::list<const Message*> *faultMessages_;
  MessageNameList messageNames_;
  int in_e,out_e,fault_e; //extensibility elements for <input>,<output>,<fault> elements
    
};



inline
Operation::Operation(WsdlParser& w,PortType * p)
  :WsdlElement(w),
     pt_(p),
     type_(OP_NONE),
     inMessage_(0),
     outMessage_(0),
  faultMessages_(0),
  in_e(0),out_e(0),fault_e(0)
{
}

inline
Operation::~Operation()
{
  
  delete faultMessages_;
}

inline
const PortType* 
Operation::portType()const
{
  return pt_;
}

inline
const Message *
Operation::getMessage(WsdlPull::MessageType type) const     
{
  if (type == Input)
    return inMessage_;

  else if (type == Output)
    return outMessage_;

  else if (type == Fault && faultMessages_)
    return faultMessages_->front();

  else
    return 0;
}

inline
void 
Operation::addMessageExtensibility(WsdlPull::MessageType type,int ext)
{
 if (type == Input)
   in_e = ext;

  else if (type == Output)
    out_e = ext;

  else if (type == Fault)
    fault_e = ext;
  
 return;
}
inline
int 
Operation::getMessageExtension(WsdlPull::MessageType type)
{
 if (type == Input)
   return in_e ;

  else if (type == Output)
    return out_e;

  else if (type == Fault)
    return fault_e;

 return 0;
}
inline  
Optype
Operation::getType() const                        
{
  return type_;
}


inline
void 
Operation::setMessage(const Message * message,
		      WsdlPull::MessageType type,
		      const std::string &name)
{
  if (message == 0)
    throw WsdlException("Invalid message name");
  if (type == Input) {

    inMessage_ = message;
    if (type_ == OP_NONE)
      type_ = OP_IN;

    else if (type_ == OP_OUT)
      type_ = OP_OUT_IN;

    else
      type_ = OP_NONE;
  }
  else if (type == Output){
    
    outMessage_ = message;
    if (type_ == OP_NONE)
      type_ = OP_OUT;

    else if (type_ == OP_IN)
      type_ = OP_IN_OUT;

    else
      type_ = OP_NONE;
  } 
  else if (type == Fault) {
      
    if (!faultMessages_)
      faultMessages_ = new std::list<const Message*>();
    
    faultMessages_->push_back(message);
  }
  //Save mesasge name
  messageNames_[message]=name;
}

inline
void 
Operation::print(std::ostream & out)
{
  out << id_ << XmlUtils::dbsp << name_ << std::endl;
  out << type_ << std::endl;
  out << inMessage_ << XmlUtils::dbsp << outMessage_ << XmlUtils::dbsp <<std::endl;
  out << XmlUtils::blk;
}

inline
std::list<const Message*>*
Operation::getFaults()const
{

  return faultMessages_;
}
inline
const Message* 
Operation::getFault(const std::string& name)const
{
  for ( std::list<const Message*>::iterator mli = faultMessages_->begin();
	mli != faultMessages_->end();
	mli++) {

    if ((*mli)->getName() == name)
      return (*mli);
  }
  return 0;
}

inline
std::string
Operation::getMessageName(WsdlPull::MessageType type) const
{
 std::string name("");
 const Message * pMessage = 0;
 MessageNameList::const_iterator it;

  if (type == Input)  {

    pMessage = inMessage_;
  }
  else if (type == Output)  {

    pMessage = outMessage_;
  }
  else if (type == Fault && faultMessages_)  {

    pMessage = faultMessages_->front();
  }

  it = messageNames_.find(pMessage);

  if (messageNames_.end() != it)
    name = it->second;
 
  return name;
}

}

#endif                                            /*  */
