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


//A stock portfolio application to illustrate the use of the Invocation API
#include <wsdlparser/WsdlInvoker.h>
using namespace WsdlPull;
int 
main (int argc, char *argv[]) 
{
  //  std::string myStocks[] = {"IBM","YHOO","MSFT","GOOG","RHAT"};

  WsdlInvoker invoker;
  if (!invoker.setWSDLUri("http://www.webservicex.net/stockquote.asmx?WSDL")) {
      
    std::cerr<<invoker.errors()<<std::endl;
    return 2;
  }
  
  //  invoker.setVerbose(true);   
  if(!invoker.setOperation("GetQuote")){
      
    std::cerr<<"Error calling GetQuote "<<std::endl;
    return 2;
  }

  if (invoker.status()){
  
    Schema::Type t;
    
    
    
    if (!invoker.setValue("symbol","MSFT")){
      
      std::cerr<<"Incorrect input value "<<std::endl;
      return 2;
    }
    
    if (invoker.invoke()){
      
      std::string name;
      std::cout<<"MSFT stock quote"<<std::endl;
      void * val = invoker.getValue("GetQuoteResult",t);
      //t is a string 
      std::cout<<*((std::string*)val)<<std::endl;
    }
    else{
      std::cerr<<"Couldnt invoke the web service"<<std::endl;
    }
    
  }
  return 0;
}


