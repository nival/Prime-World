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


//A generic web service invocation tool which uses the invocation API
#include "wsdlparser/WsdlInvoker.h"
//
#include <cstdlib>

using namespace std;
using namespace WsdlPull;

#ifdef _WIN32
#define PACKAGE_VERSION "1.x"
#endif

void
usage(void)
{
  std::cout<<"Usage wsdl [options] wsdl-uri [operation name] [method parameters] [xpath expression for response]"<<std::endl;
  std::cout<<"Version "<<PACKAGE_VERSION<<std::endl;
  std::cout<<"Options: "<<std::endl;
  std::cout<<"   -h  Display this message"<<std::endl;
  std::cout<<"   -x host[:port] Use HTTP proxy on given port"<<std::endl;
  std::cout<<"   -U user[:password] Specify Proxy authentication"<<std::endl;
  std::cout<<"   -v Verbose mode,SOAP request and response are logged"<<std::endl;
  std::cout<<"   -d display WSDL operation's documentation"<<std::endl;
  std::cout<<"   -p display WSDL port types and their operations"<<std::endl;
  std::cout<<"   -l list all the WSDL operations "<<std::endl;
  std::cout<<"   -o Allow setting occurrence constraint (default is 1)"<<std::endl;
  std::cout<<"   -s Suppress printing type/element names in the output"<<std::endl;
  std::cout<<"   -t requesttimeout in seconds"<<std::endl;
  std::cout<<"   -e set SOAP headers in input"<<std::endl;
  std::cout<<"   -g generate sample SOAP message for the invocation"<<std::endl;
  std::cout<<"   -w get soap,encoding and wsdl schemas from the web"<<std::endl;
  std::cout<<"   -f get soap,encoding and wsdl schemas from the filesystem"<<std::endl;
  std::cout<<"   -r Validate the response message with schema even when xpath selector is used(default is off)"<<std::endl;
  std::cout<<"With no arguments,wsdl starts in the interactive mode accepting operation name and parameters from the standard input."<<std::endl<<std::endl;
  std::cout<<"An xpath expression can be used to extract elements from web service response.If the expression points to an element or an attribute,the element's text or attribute value will be returned.The expression will match all occurrences in the xml tree"<<std::endl;


}

bool
printPortTypes(std::string uri)
{

  WsdlParser wp (uri, cout);
  while (wp.getEventType () != WsdlParser::END){

      if(wp.getNextElement () == WsdlParser::PORT_TYPE){

	  
	const PortType * p = wp.getPortType ();
	cout << "Port Type :" << p->getName () << "  has  " << 
	  p->getNumOps () << " operations "<<endl;
	Operation::cOpIterator from,to;
	p->getOperations(from,to);
	while(from!=to){
	  
	  const Message* in = (*from)->getMessage(Input); 
	  const Message* out = (*from)->getMessage(Output); 
	  MessageList * faults = (*from)->getFaults();
	  cout<<(*from)->getName()<<endl;
	  cout <<"  Input Message:"<<in->getName()<<endl;
	  if (out)
	    cout <<"  Output Message:"<<out->getName()<<endl;
	  if (faults) {
	    for (MessageList::iterator mli = faults->begin();
		 mli != faults->end();
		 mli++) {
	      
	      cout<<"  Fault :"<<(*mli)->getName()<<endl;
	    }
	  }
	  from++;
	}

      }
  }
  return true;
}



int 
main (int argc, char *argv[]) 
{
  WsdlInvoker invoker;
  bool brkloop =false;
  bool showDoc = false;
  bool verbose = false;
  bool occurs = false;
  bool listops = false;
  bool generateSoapMsg = false;
  bool accept_password =false;
  bool accept_headers = false;
  bool   processResponse = false;
  long timeout = 0;

#ifdef _WIN32
  WsdlPull::WsdlParser::useLocalSchema_ = false;
#endif

  int i =1;
  for (;i<argc && !brkloop;){
    switch(argv[i][0]){
    case '-'://option
      {
	std::string options(argv[i]+1);
	char n = options.length();
	while(n--) {
	  
	  std::string opt(1,options[n]);
	  
	  if (opt=="v"){
	    invoker.setVerbose(true);
	    verbose = true;
	    showDoc = true;

	  }
	  else if (opt == "s"){
	  
	    invoker.printTypeNames(false);

	  }
	  else if (opt == "d"){
	  
	    showDoc = true;

	  }
	  else if (opt == "e"){
	  
	    accept_headers = true;

	  }
	  else if (opt == "l"){
	  
	    listops=true;

	  }
	  else if (opt == "x"){
	    opt = argv[i+1];
	    size_t pos=opt.find(':');
	    XmlUtils::setProxyHost (opt);
	    if(pos==std::string::npos){
	    
	      XmlUtils::setProxyHost (XmlUtils::getProxyHost () + ":80");
	    }
	    XmlUtils::setProxy (true);
	    i+=1;
	    break;
	  }
	  else if (opt == "U"){
	    opt = argv[i+1];
	    size_t pos=opt.find(':');
	    XmlUtils::setProxyUser (opt.substr(0,pos));
	    if(pos!=std::string::npos)
	      XmlUtils::setProxyPass (opt.substr(pos+1));
	    else
	      accept_password = true;
	    i+=1;
	    XmlUtils::setProxy (true);
	    break;
	  }
	  else if (opt =="p"){
	    
	    if(printPortTypes(argv[i+1]))
	      return 0;
	    else 
	      return 1;
	  }
	  else if (opt =="h"){
	    usage();
	    return 0;
	  }
	  else if (opt == "g"){

	    generateSoapMsg = true;
	  }
	  else if(opt == "o"){
	  
	    occurs = true;//ask for occurrence constraints

	  }
	  else if(opt == "t"){
	    opt = argv[i+1];
	    timeout=atoi(opt.c_str());
	    i+=1;
	    break;
	  }
	  else if(opt == "r"){
	    processResponse = true;
	  }
          else if (opt == "w"){

             WsdlPull::WsdlParser::useLocalSchema_ = false;
	  }
          else if (opt == "f"){

             WsdlPull::WsdlParser::useLocalSchema_ = true;
	  }
	  else{
	    std::cerr<<"Unknown option "<<argv[i]<<std::endl;
	    usage();
	    return 2;
	  }

	}
	i++;
	break;

      }
    default:
      brkloop = true;
      //end of options
      break;
    }
  }

  if (XmlUtils::getProxy () && accept_password){
     
    XmlUtils::setProxyPass (XmlUtils::acceptSecretKey("Proxy Password"));
    std::cout<<endl;
  }

  if (i < argc){
    if(!invoker.setWSDLUri(argv[i])) {

      std::cerr<<"Error processing "<<argv[i]<<std::endl;
      std::cerr<<invoker.errors()<<std::endl;
      return 1;
    }
#ifdef LOGGING
      std::cerr<<invoker.errors()<<std::endl;
#endif
    i++;
  }
  else{
    
    usage();
    return 2;
  }

  if (verbose)
    std::cout<<invoker.errors()<<std::endl;
  
  if (i<argc && !listops){
    
    if(!invoker.setOperation(argv[i])){
      
      std::cerr<<"Unkown operation name "<<argv[i]<<std::endl;
      return 2;
    }
    i++;
  }
  else{
  
    std::vector<std::string> ops;
    unsigned int choice = 0;
    if (invoker.getOperations(ops)){
    
      for (size_t s = 0;s<ops.size();s++){
      
	std::cout<<s+1<<"."<<ops[s];
	
	if (showDoc) {
	 
	  std::string doc = invoker.getOpDocumentation(ops[s]);
	  if (!doc.empty())
	    std::cout<<"("<<doc<<")";
	}
	std::cout<<endl;
      }
      if (listops == true){
	
	return 0;
      }
      while (choice==0){
	
	std::cout<<"Choose one of the above operations [1-"<<ops.size()<<"] :";
	std::cin>>choice;
	if (choice>0 && choice<=ops.size())
	  break;
	else
	  choice=0;
      }
    }
    else {

      std::cerr<<"No operation found or missing <binding> section"<<std::endl;
      return 2;
    }
    if (!invoker.setOperation(ops[choice-1])){
      
      std::cerr<<"Couldn't invoke operation "<<std::endl<<invoker.errors()<<std::endl;
      return 1;
    }
  }
  if(!accept_headers && invoker.nInputHeaders()>0){
    
    std::cout<<"Warning:This operation has some SOAP headers in its inputs!(use -e)"<<std::endl;
  }

  if (invoker.status()){
  
    int id =0,minimum,maximum,n;
    Schema::Type t;
    std::string param;
    std::string val;
    std::vector<std::string> values;
    std::vector<std::string> parents;
    
    do{    

      if (accept_headers && invoker.nInputHeaders()>0){
	
        id = invoker.getNextHeaderInput(param,t,minimum,maximum,parents);
	if (id == -1){
	  accept_headers=false;//done with headers
	  continue;
	}
      }
      else{
	
        id = invoker.getNextInput(param,t,minimum,maximum,parents);
      }
      if (id == -1)
	break;
      n = minimum;
      if (occurs && minimum < maximum) {
	values.clear();
        std::cout<<param<<"["<<minimum<<","<<maximum<<"] Enter number of occurrences:";
	cin>>n;
	
        if (n<minimum || n>maximum){
	  
	  std::cerr<<"Didnt match occurrence constraints"<<std::endl;
	  return 2;
	}
	while(n--) {

	  if (i <argc) {
	    val = argv[i++];
	  }
	  else {
	    std::cout<<param<<": ";
	    cin>>val;
	  }
	  values.push_back(val);
	}
	if (!invoker.setInputValue(id,values)){

	  std::cerr<<"Incorrect input values "<<std::endl;
	  return 2;
	}
      }
      else{

	if (i <argc) {
	  
	  val = argv[i++];
	}
	else{
	  size_t j = 0;
	  for (j=0;j<parents.size()-1;j++){

	    std::cout<<parents[j]<<".";
	  }
	  std::cout<<parents[j]<<": ";
	  cin>>val;
	}
	if (!invoker.setInputValue(id,val)){

	  std::cerr<<"Incorrect input value "<<val<<std::endl;
	  return 2;
	}
      }
    }while(1);
  

    if (generateSoapMsg) {

      //output the soap message and exit
      std::cout <<invoker.getSoapMessage()<<std::endl;
      return 0;

    }

#ifndef WITH_CURL
#ifndef _WIN32
    std::cerr<<"libcurl needs to be installed to proceed with invocation"<<std::endl;
    std::cerr<<"Try using the -g option to just print the soap message"<<std::endl;
    return 2;
#endif
#endif 

    if (invoker.invoke(timeout,(i>=argc || processResponse))){

      TypeContainer* tc = 0;
      std::string name;
      
      if (i <argc) {
	
	try {
	//the last argument is an xpath expression to get the output
	  std::vector<std::string> arr=invoker.getValues<std::string>(argv[i++]);
	  for (size_t s = 0;s<arr.size();s++) 
	    std::cout<<arr[s]<<std::endl;

	  return 0;
	}
	catch (WsdlException we) {

	  std::cerr<<we.description<<std::endl;
	}
	catch (XmlPullParserException xpe) {

	  std::cerr<<xpe.description<<std::endl;
	}
	return 2;
      }
      while(invoker.getNextHeaderOutput(name,tc)) {
        

	tc->print(std::cout);
	std::cout<<std::endl;
      }
      
      while (invoker.getNextOutput(name,tc)){
	    
	tc->print(std::cout);
	std::cout<<std::endl;
      }
      return 0;
    }
    else{
      cerr<<invoker.errors()<<std::endl;
      cerr<<"Run with -v option and see request.log and response.log"<<endl;
    }
  }
  return 1;
}




