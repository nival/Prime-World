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
#ifndef _BINDINGH
#define  _BINDINGH

#include "wsdlparser/WsdlElement.h"
#include "xmlpull/wsdlpull_export.h"

namespace WsdlPull {
class PortType;
const int MAX_EXT_ELEM=50;

//Wsdl Binding element
class WSDLPULL_EXPORT Binding:public WsdlElement
{

  /**
   * The default constructor for Wsdl Binding
   */
 public:
  typedef std::list<Binding*>::iterator BindingIterator;
  typedef std::list<Binding*>::const_iterator cBindingIterator;

  Binding(WsdlParser & w);
  ~Binding();
  
  /** @name Various Getter methods*/
  //@{
  /**
   * getBindingInfo
   * @return the extensibility element id of the  main binding extension element.
   *         In case of soap it would  be the id of the soap:binding element
   */
  int getBindingInfo() const;
  /**
   * getPortType
   * @return the wsdl port type associated with this binding
   */
  const PortType *getPortType() const;
  /**
   * getServiceExtId
   * @return the id of the service element assocaited with this binding
   */
  int getServiceExtId() const;

  /**
   * numOps
   * @return number of operations in this binding
   */
  int numOps(void) const;

  /**
   * getOperation
   * @param the index of the operation (index ranges from 0 to Ops_.size()-1)
   * @return pointer to the  operation
   */
  const Operation *getOperation(int index) const;
  /**
   * getBindingMethod
   * @param void
   * @return The namespace of the binding protocol 
   *         example "http://schemas.xmlsoap.org/wsdl/soap/"
   */
  std::string getBindingMethod()const;


  /**
   * getBinding
   * @return The number of binding extensibility elements assocated with each
   *         message of the operation whose index is given
   *         returns a pointer to a list of extensibility binding ids
   */
  int getOpBinding(int index, const int*& bindings) const;
  int getOutputBinding(int index, const int*& bindings) const;
  int getInputBinding(int index, const int*& bindings) const;
  int getFaultBinding(int index, const int*& bindings) const;
  //@}
  ///** @name Various Setter methods*//
  ///@{

  /**
   *Their descriptions are similar to the corresponding getter methods
   */

  void setPortType(const PortType * pt);
  void setBindingInfo(int id);
  void setBindingMethod(const std::string & ns);
  void addServiceExtId(int id);
  /**
   * Add an operation to the binding .The index returned is to be used
   * to add more bindings to the operation
   */
  int  addOperation(const Operation * op);
  void addOpBinding(int index, int oBn);
  void addOutputBinding(int index, int opBn);
  void addInputBinding(int index, int ipBn);
  void addFaultBinding(int index, int fBn);
  int  getOperationIndex(const Qname & name) const;

  //@}

 private:
  class OperationBinding
    {
    public:
      OperationBinding();
      const Operation *op;
      int opBinding[MAX_EXT_ELEM];
      int nObn;                           
      //additional extensibility elements,example soap:operation element
      int inputBinding[MAX_EXT_ELEM];
      int nIpbn;
      int outputBinding[MAX_EXT_ELEM];
      int nOpbn;
      int faultBinding[MAX_EXT_ELEM];
      int nFbn;
    };

  std::vector<OperationBinding> Ops_;
  const PortType *portType_;
  std::string binding_;//namespace of the binding protocol(SOAP,HTTP etc)
  int bindingInfo;  //binding information for the whole port type 
  //this is the id of the element whichgives details about service for this binding
  std::list<int> serviceExtIds_;                       
};

inline
Binding::OperationBinding::OperationBinding()
  :op(0),
     nObn(0),
     nIpbn (0),
     nOpbn(0),
     nFbn(0)
{
}

inline
int
Binding::getBindingInfo() const
{
  return bindingInfo;
}

inline
const PortType *
Binding::getPortType() const
{
  return portType_;
}

inline
int 
Binding::getServiceExtId() const
{
  if (serviceExtIds_.size() > 0)
    return serviceExtIds_.front();
  else 
    return 0;
}

inline
int
Binding::numOps(void) const
{
  return Ops_.size();
}

inline
const Operation *
Binding::getOperation(int index) const
{
  return Ops_[index].op;
}

inline
int
Binding::getOpBinding(int index, const int*& bindings) const
{
  bindings = Ops_[index].opBinding;
  return Ops_[index].nObn;
}

inline
int
Binding::getOutputBinding(int index, const int*& bindings) const
{
  bindings = Ops_[index].outputBinding;
  return Ops_[index].nOpbn;
}

inline
int
Binding::getInputBinding(int index, const int*& bindings) const
{
  bindings = Ops_[index].inputBinding;
  return Ops_[index].nIpbn;
}

inline
int
Binding::getFaultBinding(int index, const int*& bindings) const
{
  bindings = Ops_[index].faultBinding;
  return Ops_[index].nFbn;
}

inline
void 
Binding::setPortType(const PortType * pt)
{
  portType_ = pt;
}

inline
void
Binding:: setBindingInfo(int id)
{
  bindingInfo = id;
  WsdlElement::addExtElement(id);
}

inline
void 
Binding::addServiceExtId(int id)
{
  serviceExtIds_.push_back(id);
}

inline
int
Binding::addOperation(const Operation * op)
{
  OperationBinding ob;
  ob.op=op;
  Ops_.push_back(ob);
  return Ops_.size()-1;
}

inline
void
Binding::addOpBinding(int index, int oBn)
{
  Ops_[index].opBinding[Ops_[index].nObn++] = oBn;
}

inline
void
Binding::addOutputBinding(int index, int opBn)
{
  Ops_[index].outputBinding[Ops_[index].nOpbn++] = opBn;
}
inline
void
Binding::addInputBinding(int index, int ipBn)
{
  Ops_[index].inputBinding[Ops_[index].nIpbn++] = ipBn;
}

inline
void
Binding::addFaultBinding(int index, int fBn)
{
  Ops_[index].faultBinding[Ops_[index].nFbn++] = fBn;
}


inline
Binding::Binding(WsdlParser& w)
  :WsdlElement(w)
{
  portType_ = 0;
  Ops_.clear();
}

inline
Binding::~Binding()
{
}

inline
void
Binding::setBindingMethod(const std::string & ns)
{
  binding_=ns;
}

inline
std::string
Binding::getBindingMethod()const
{
  return binding_;
}

inline int
Binding::getOperationIndex(const Qname & name) const
{
   for (int i=0; i < int(Ops_.size()); i++ )   {
      if (Ops_[i].op->getName() == name.getLocalName() ) return i;
       }
    return -1;
}


}
#endif                                            /*  */
