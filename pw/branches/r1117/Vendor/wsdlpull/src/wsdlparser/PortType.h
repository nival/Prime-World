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
#ifndef _PORTTYPEH
#define _PORTTYPEH

#include "wsdlparser/Operation.h"
#include "wsdlparser/Binding.h"
#include "xmlpull/wsdlpull_export.h"

namespace WsdlPull {
//This class implements a port type of WSDL .
class WSDLPULL_EXPORT PortType:public WsdlElement
{
 public:
  typedef std::list<PortType*>::iterator PortTypeIterator;
  typedef std::list<PortType*>::const_iterator cPortTypeIterator;

  PortType(WsdlParser& w);
  ~PortType();
  /** @name Various Getter methods*/
  //@{

  int getNumOps(void) const;

  /**
   * getOperation
   * @param index of the operation index:0..ops.size()-1
   * @return pointer to  the Operation
   */
  const Operation *getOperation(int index) const;

  /**
   * getOperation
   * @param name of the operation
   * @return pointer to  the Operation
   */
  const Operation *getOperation(const Qname & name) const;
  int  getOperationIndex(const Qname & name) const;
  
  /**
   * getOperations
   * @return bool
   * returns the iterators to start and end of operations 
   */
  bool getOperations(Operation::cOpIterator & start ,Operation::cOpIterator & finish)const;

  /**
   * @name   binding
   * @return const Binding*
   * returns Binding associated with the port type 
   *         which has a binding protocol specified by 'nsp'
   */
  
  const Binding* binding(const std::string & nsp)const;
  
  //@}

  /** @name Various Setter methods*/
  //@{
  void addOp(Operation * op);
  void setBinding(Binding* bn);
  //@}
 private:
  std::vector<Operation *> ops_;
  std::vector<const Binding *> bindings_;
};

inline
PortType::PortType(WsdlParser& w)
  :WsdlElement(w)
{
  ops_.clear() ;
}
inline
PortType::~PortType() 
{
  for (size_t i = 0; i < ops_.size(); i++)
    delete ops_[i];  

}

inline
int
PortType::getNumOps(void) const
{
  return ops_.size();
}

inline
const Operation *
PortType::getOperation(int index) const
{
  return ops_[index];
}
 
inline
int
PortType::getOperationIndex(const Qname & name) const
{
  for (size_t i = 0; i < ops_.size(); i++)
    {
      if (ops_[i]->getName() == name.getLocalName())
	return i;
    }
  return 0;
}

inline
const Operation *
PortType::getOperation(const Qname & name) const
{
  for (size_t i = 0; i < ops_.size(); i++)
    {
      if (ops_[i]->getName() == name.getLocalName())
	return ops_[i];
    }
  return 0;
}

inline
bool
PortType::getOperations(Operation::cOpIterator & start ,
			Operation::cOpIterator & finish)const
{
  start=ops_.begin();
  finish=ops_.end();
  return true;
}


inline
void 
PortType::addOp(Operation * op)
{
  ops_.push_back(op);
}

inline
void
PortType::setBinding(Binding* bn)
{
  bindings_.push_back(bn);
}

inline
const Binding*
PortType::binding(const std::string & nsp)const
{
  for (unsigned int i = 0; i<bindings_.size();i++){
    if (bindings_[i]->getBindingMethod() == nsp)
      return bindings_[i];
  }
  return 0;
}
}
#endif                                            /*  */
