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
 */

#include "wsdlparser/WsdlElement.h"
#include "wsdlparser/WsdlParser.h"

namespace WsdlPull {
void
WsdlElement::print(std::ostream & out)
{
  size_t i;
  out << extElems_.size() << XmlUtils::dbsp << XmlUtils::dbsp;
  for (i = 0; i < extElems_.size(); i++)
    out << extElems_[i] << XmlUtils::dbsp;
  out << std::endl;
  out << extAttributes_.size() << XmlUtils::dbsp << XmlUtils::dbsp;
  for (i = 0; i < extAttributes_.size(); i++)
    out << extAttributes_[i] << XmlUtils::dbsp;
}


bool
WsdlElement::getExtensibilityElements(const std::string & namespc,
				      std::vector<int>& ids)
{
  WsdlExtension * we = wParser_.getExtensibilityHandler(namespc);
  if (we == 0)
    return false;
  bool ret = false;
  for (size_t i = 0 ;i<extElems_.size();i++){

    if (we->getElementName(extElems_[i])!=0){
      ids.push_back(extElems_[i]);
      ret = true;
    }
  }
  return ret;
}

  
bool
WsdlElement::getExtensibilityAttributes(const std::string & namespc,
					std::vector<int>& ids)
{
  WsdlExtension * we = wParser_.getExtensibilityHandler(namespc);
  if (we == 0)
    return false;
  bool ret = false;
  for (size_t i = 0 ;i<extAttributes_.size();i++){

    if (we->getAttributeName(extAttributes_[i])!=0){
      ids.push_back(extAttributes_[i]);
      ret = true;
    }
  }
  return ret;
}
}
