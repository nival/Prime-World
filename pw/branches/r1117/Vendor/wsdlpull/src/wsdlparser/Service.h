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

#ifndef _SERVICEH
#define  _SERVICEH

#include "wsdlparser/WsdlElement.h"
#include "xmlpull/wsdlpull_export.h"

namespace WsdlPull {
class Binding;

class WSDLPULL_EXPORT Service :public WsdlElement {
public:
  typedef struct {
    std::string name_;
    const Binding* binding_;
    int serviceExtId_;
  }ServicePort;
  typedef std::list<ServicePort>::const_iterator cServicePortIterator;
  
public:  
  Service(WsdlParser & w);
  
  /** @name Various getter/setter methods*/
  //@{
   
  void addPort(const std::string& name,const Binding* bn,int serviceExtId);
 
  int getPortExtension(const std::string& name)const;
  const Binding* getPortBinding(const std::string& name)const;
  void getPortBindings(cServicePortIterator &from, cServicePortIterator &to)const;
  std::list<std::string> getPorts()const;
  //@}
private:
   
  std::list<ServicePort> ports_;
};

  
inline
Service::Service(WsdlParser& w)
  :WsdlElement(w)
{
}
inline
void
Service::addPort(const std::string& n,const Binding* bn,int serviceExtId)
{
  ServicePort sp;
  sp.name_=n;
  sp.binding_ = bn;
  sp.serviceExtId_ = serviceExtId;
  ports_.push_back(sp);
}

inline
int
Service::getPortExtension(const std::string & name)const
{
  for(std::list<ServicePort>::const_iterator it = ports_.begin();
      it != ports_.end();
      it++){
    if(it->name_ == name)
      return it->serviceExtId_;
  }
  return 0;
}

inline 
const Binding*
Service::getPortBinding(const std::string & name)const
{
  for(std::list<ServicePort>::const_iterator it = ports_.begin();
      it != ports_.end();
      it++){
    if(it->name_ == name)
      return it->binding_;
  }
  return 0;
}

inline 
void
Service::getPortBindings(cServicePortIterator &from,
			 cServicePortIterator &to)const
{
  if (ports_.size()> 0)
  {
    from = ports_.begin();
    to = ports_.end();
  }
}

inline 
std::list<std::string>
Service::getPorts()const
{
  std::list<std::string> names;
  for(std::list<ServicePort>::const_iterator it = ports_.begin();
      it != ports_.end();
      it++){
    names.push_back(it->name_);
  }
  return names;
}
}
#endif

