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
#ifndef _QNAMEH
#define _QNAMEH
#include <string>
#include <iostream>
#ifdef HAVE_CONFIG_H //
#include <config.h>
#endif 
#include "wsdlpull_export.h"

class WSDLPULL_EXPORT Qname
{
 public:
  Qname (const std::string & name);
  Qname (const Qname & qn);
  Qname ();
  std::string  getLocalName (void)const;
  std::string  getPrefix (void) const;
  std::string  getNamespace (void)const;
  void setNamespace (std::string uri);
  bool operator== (const Qname & qn)const;
  void operator= (const std::string & name);
  friend std::ostream & operator<<(std::ostream & os,const Qname& qn);
 private:
  void parse (const std::string & name);
  std::string namespaceUri, localname, prefix;
};

inline
Qname::Qname (const std::string & name)
{
  parse (name);
}

inline
Qname::Qname (const Qname & qn)
{
  localname = qn.localname;
  prefix = qn.prefix;
  namespaceUri = qn.namespaceUri;
}

inline
Qname::Qname ()
{
}

inline
void 
Qname::operator= (const std::string & name)
{
  parse (name);
}

inline
std::string
Qname::getLocalName (void)const
{
  return localname;
}

inline
std::string
Qname::getPrefix (void) const
{
  return prefix;
}

inline
std::string 
Qname::getNamespace (void)const
{
  return namespaceUri;
}

inline
void
Qname::setNamespace (std::string uri)
{
  namespaceUri = uri;
}

inline
bool 
Qname::operator== (const Qname & qn)const
{
  if (qn.getNamespace () == namespaceUri && qn.getLocalName () == localname)
    return true;
  else
    return false;
}

inline
void
Qname::parse (const std::string & name)
{
  int cut = -1;
  if (name.empty ())
    return;
  cut = name.find (":");
  if (cut == -1 || cut == 0)
    localname = name;

  else

    {
      localname = name.substr (cut + 1);
      prefix = name.substr (0, cut);
    }
  cut = localname.find ("[]");
  if (cut > 0)
    localname = localname.substr (0, cut);
}

inline
std::ostream &
operator<<(std::ostream & os,const Qname& qn)
{
  os<<qn.getPrefix()<<"{"<<qn.getNamespace()<<"}:"<<qn.getLocalName();
  return os;
}
#endif                                            /*  */
