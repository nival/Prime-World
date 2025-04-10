
//This example demonstrates the WSDL pull API
//It prints out the service name and location of the random bushism WSDL webservice
#include <iostream>
#include <fstream>
#include <string>
#include <xmlpull/XmlPullParser.h>
#include <xmlpull/XmlPullParserException.h>
#include <schemaparser/SchemaParser.h>
#include <schemaparser/SchemaParserException.h>
#include <wsdlparser/WsdlParser.h>
#include <wsdlparser/Soap.h>
using namespace std;
using namespace WsdlPull;

int 
main (int argc, char *argv[]) 
{
  if (argc <= 1)
    {
      cout << "Usage: print <wsdl_File_Name>" << endl;
      return 1;
    }
  
  try{

    WsdlParser wp (argv[1], cout);
    while (wp.getNextElement () != WsdlParser::END);
    if (!wp.status())
      return 1;
    Qname q ("RandomBushismService");//put a valid service name from your WSDL here 
    const Service * sv = wp.getService(q);
    std::cout<<sv->getName()<<std::endl;
    //    Soap* soap=static_cast<Soap*>(wp.getExtensibilityHandler(Soap::soapBindingUri));
    std::list<std::string> ports = sv->getPorts();
    for (std::list<std::string>::iterator si = ports.begin();
	 si != ports.end();
	 si++) {

      int extension = sv->getPortExtension(*si);
      WsdlExtension * we = wp.getExtensibilityHandler(extension);
      if(we->getNamespace() == Soap::soapBindingUri) {
	
	Soap * s = static_cast<Soap*>(we);
	std::string location;
	s->getServiceLocation(extension,location);
	std::cout <<location<<std::endl;
      }
    }
    return 0;
  }
  catch (WsdlException we)
    {
      cout<<"An Exception occurred ...@"<<we.line   
	  <<":"<<we.col<<endl;
      cout<<we.description<<endl;
      return 1;
   
    }
  catch (SchemaParserException spe)
    {
      cout<<"An Exception occurred ...@"<<spe.line
	  <<":"<<spe.col<<endl;
      cout<<spe.description<<endl;
      return 1;
    }
  catch (XmlPullParserException xpe)
    {
      cout<<"An Exception occurred ...@"<<xpe.line
	  <<":"<<xpe.col<<endl;
      cout<<xpe.description<<endl;
      return 1;
    }
}


