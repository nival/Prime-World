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

#include "wsdlparser/WsdlParser.h"

#ifdef LOGGING

using namespace std;

namespace WsdlPull {
// just print all the stuff,for debugging
void  WsdlParser::print(std::ostream & out)
{
  Binding *bn = bindings_.front();
  int i = 0, soapBindingId, inId, outId, faultId;
  int numOps = bn->numOps();

  /*
    Print all the  operations and messages and then the types of
    the Schema Parser
  */
  for (i = 0; i < getNumSchemas(); i++)
    schemaParser_[i]->print(out);
  i = 0;
  while (i < numOps)
    {
      const int *bindings = 0;
      int n = 0;
      n = bn->getOpBinding(i, bindings);
      soapBindingId = bindings[0];
      n = bn->getInputBinding(i, bindings);
      inId = bindings[0];
      n = bn->getOutputBinding(i, bindings);
      outId = bindings[0];
      n = bn->getFaultBinding(i, bindings);
      faultId = bindings[0];
      const Operation *op = bn->getOperation(i);
      out << op->getName() << endl;
      const Message *inMessage = op->getMessage(Input);
      const Message *outMessage = op->getMessage(Output);
      int nParams = 0, j = 0;
      int typeId = 0,schemaId;
      const XSDType *pType = 0;
      nParams = inMessage->getNumParts();
      for (j = 0; j < nParams; j++)
        {
          if (inMessage->getPartRefType(j) == Part::Elem)
            {
              
              typeId = inMessage->getPartType(j);
              pType = schemaParser_[schemaId]->getType(typeId);

              if (!pType->isSimple())
                {
                  ComplexType * cType = (ComplexType *) pType;

                  ContentModel::ContentsIterator cit_b=cType->getContents()->begin();
                  ContentModel::ContentsIterator cit_e=cType->getContents()->end();
                  ContentModel::ContentsIterator ci=cit_b;
  
                  for (ci=cit_b;ci!=cit_e;ci++){
                    if(ci->second==ContentModel::Particle){
                      out<<ci->first.e->getName()<< ":" <<
                        ci->first.e->getType();
                    }
                  }
                 
                }
            }

          else
            out << inMessage->getPartName(j) << ":" << inMessage->
              getPartType(j) << XmlUtils::dbsp;
        }
      out << endl;
      nParams = outMessage->getNumParts();
      for (j = 0; j < nParams; j++)
        {
          if (outMessage->getPartRefType(j) == Part::Elem)
            {

              const Element * e =outMessage->getPartElement(j);
              out << e->getName() << ":" << e->getType() << XmlUtils::dbsp;
            }

          else
            out << outMessage->getPartName(j) << ":" << outMessage->
              getPartType(j) << XmlUtils::dbsp;
        }
      out << XmlUtils::blk;
      i++;
    }
}
}
#endif
