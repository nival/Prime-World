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

//This file parses a sample schema document and validates/generates an instance
  
#include <iostream>
#include <fstream>
#include <string>
#include "xmlpull/XmlPullParser.h"
#include "xmlpull/XmlPullParserException.h"
#include "schemaparser/SchemaParser.h"
#include "schemaparser/SchemaValidator.h"
#include "schemaparser/TypeContainer.h"
#include "schemaparser/SchemaParserException.h"
using namespace std;
using namespace Schema;

void
usage(void)
{
  cout << "Usage: schema [options] <schema_file_name> [-i schema instance file name]"<<endl;
  cout << "Example:schema po.xsd -i po.xsi"<<endl;
  cout << "Example:schema first-building-blocks.xsd -i first.xml "<<endl;
  std::cout<<"Options"<<std::endl;
  std::cout<<"   -x host[:port] Use HTTP proxy on given port"<<std::endl;
  std::cout<<"   -U user[:password] Specify Proxy authentication"<<std::endl;
  std::cout<<"   -g generate an xml instance for a top level element in the schema"<<std::endl;
  std::cout<<"   -v Verbose mode"<<std::endl;
  cout << endl;
}

int 
main (int argc, char *argv[]) 
{
  ifstream schfs;
  ifstream insfs;
  SchemaParser * sp=0;
  bool brkloop =false;
  bool accept_password =false;
  unsigned char  lvl = 0;
  bool genInstance = false,validate=false;
  int i =1;
  for (;i<argc && !brkloop;){
    switch(argv[i][0]){
    case '-'://option
      {
	std::string opt(argv[i]+1);
	if (opt=="v"){
	  lvl = 2;
	  i++;
	}
	else if (opt == "g"){

	  genInstance = true;
	  i++;
	}
	else if (opt == "v") {
         validate=true;
	 i++;
	}
	else if (opt == "x"){
	  opt = argv[i+1];
	  size_t pos=opt.find(':');
          XmlUtils::setProxyHost (opt);
	  if(pos==std::string::npos){
	    
            XmlUtils::setProxyHost (XmlUtils::getProxyHost () + ":80");
          }
          XmlUtils::setProxy (true);
	  i+=2;
	}
	else if (opt == "U"){
	  opt = argv[i+1];
	  size_t pos=opt.find(':');
          XmlUtils::setProxyUser (opt.substr(0,pos));
	  if(pos!=std::string::npos)
            XmlUtils::setProxyPass (opt.substr(pos+1));
	  else
	    accept_password = true;
	  i+=2;
          XmlUtils::setProxy (true);
	}
	else if (opt =="h"){
	  usage();
	  return 0;
	}
	else{
	  std::cerr<<"Unknown option "<<argv[i]<<std::endl;
	  usage();
	  return 2;
	}
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

    sp = new SchemaParser (argv[i]);
    i++;
  }
  else
    {
      usage();
      return 2;
    }
  
  try{

    if (!sp)
      return 1;
    sp->setWarningLevel(lvl);
    if (sp->parseSchemaTag ())
      {
	if (lvl >=2)
	  cout << "Successfully parsed schema  " <<sp->getNamespace() << endl;
	//sp->print (cout);
      }
    else {

      std::cerr<<"Could not successfully parse "<<argv[i-1]<<std::endl;
      std::cerr<<"Run the command with -v option for more details"<<std::endl;
      return 1;
    }
  
    if (genInstance ) {

      std::string elemName;

      Schema::Element element;
      const Schema::SchemaParser::ElementList & el = sp->getElements(); 
      //the global element for which to generate the instance
      if (i <=argc && argv[i]){
	bool found = false;
	elemName = std::string(argv[i]);
		  
	for ( Schema::SchemaParser::ElementList::const_iterator eli= el.begin();
	      eli!=el.end() && !found;
	      eli++)
	  {
	    if (eli->getName()  == elemName){ 
	      found = true;
	      element = *eli;
	      
	      
	    }
	  }
	if (!found) {
			  
	  std::cerr<<"element '"<<elemName<<"' not found in the schema.Try 'schema -g "<<argv[2]<<"'  to see the list of elements in the schema"<<std::endl;
	  return 1;	  
	}
      }
      else {
	int n = 0;
	for ( Schema::SchemaParser::ElementList::const_iterator eli= el.begin();
	      eli!=el.end();
	      eli++,n++)
	  {
	    if (n !=0)
	      std::cout<<n<<"."<<eli->getName()<<std::endl;
	  }
	if (n<= 1){
          std::cout<<"No top level elements to generate instance.. exiting"<<std::endl;
	  return 0;
	}
	std::cout<<"Which element should I generate an instance for [1.."<<n-1<<"]?";
	std::cin>>n;

	n++; // locate the element in the list (first element bydefault is <schema> so skip it
	for ( Schema::SchemaParser::ElementList::const_iterator eli1= el.begin();
	      eli1!=el.end() && n ;
	      eli1++,n--) element = *eli1;
      } 
  
      SchemaValidator * sv = new SchemaValidator(sp);
      return sv->instance(element.getName(),(Schema::Type)element.getType());    
    }
    else if (i <argc )
      {
	std::string xmlDoc;
	XmlUtils::fetchUri(argv[i+1],xmlDoc);
        insfs.open (xmlDoc.c_str());	//open the schema instance file
        if (insfs.fail ())
          {
            cerr << "An Error occrred while opening " << argv[i+1] << endl;
            return 1;
          }
	i++;
        XmlPullParser * xpp = new XmlPullParser (insfs);
        xpp->setFeature (FEATURE_PROCESS_NAMESPACES, true);
        xpp->require (XmlPullParser::START_DOCUMENT, "", "");
        SchemaValidator * sv= new SchemaValidator(sp);
        while (xpp->getEventType () != xpp->END_DOCUMENT)
          {
            xpp->nextTag ();
            if (xpp->getEventType () == xpp->END_DOCUMENT)
              break;
            Qname elemName (xpp->getName ());
	    elemName.setNamespace(xpp->getNamespace());
            const Element * e = sp->getElement (elemName);
	    if(e){
	      int typeId = e->getType () ;
	      //for each element in the instance doc we call the
	      //validator with the parser instance of the instance file
	      // and the element's type identifier
	      TypeContainer * t = sv->validate (xpp, typeId);

	      cout << "{"<<elemName.getNamespace () << "}" << elemName. 
		getLocalName ()<<std::endl;
	      //once validated the element instance is stored
	      //in the type container from which values can be
	      //obtained or just printed
	      t->print(cout);
	      std::cout<<std::endl;
	      delete t;
	    }
	    else{
	      
	      Qname typ(xpp->getAttributeValue(Schema::SchemaInstaceUri, "type"));
	      typ.setNamespace(xpp->getNamespace(typ.getPrefix()));
	      
	      if (typ.getNamespace() == sp->getNamespace() ||
		  typ.getNamespace().empty()) {
		int typeId = sp->getTypeId(typ);

		TypeContainer * t = sv->validate (xpp, typeId);
		
		cout << "{"<<elemName.getNamespace () << "}" << elemName. 
		  getLocalName ()<<std::endl;
		//once validated the element instance is stored
		//in the type container from which values can be
		//obtained or just printed
		t->print(cout);
		std::cout<<std::endl;
		delete t;

	      } 
	      else {
		std::cerr<<"Unknown element {"<<elemName.getNamespace()<<"}"<<elemName.getLocalName()<<std::endl;
	      }
	    }
	    
	  }
      }
    delete sp;
    return 0;
  }
  
  
  catch (SchemaParserException spe)
    {
      cerr<<"An Exception occurred ...@"<<spe.line
          <<":"<<spe.col<<endl;

      cerr<<spe.description<<endl;
    }
  catch (XmlPullParserException xpe)
    {
      cerr<<"An Exception occurred ...@"<<xpe.line
          <<":"<<xpe.col<<endl;

      cerr<<xpe.description<<endl;
    }
  return 1;
}
