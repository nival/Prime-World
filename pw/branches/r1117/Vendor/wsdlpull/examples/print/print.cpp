
//This example simply prints out most of the WSDL elements encountered
//demonstrates the WSDL pull API
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
    while (wp.getEventType () != WsdlParser::END)
    
      {
	switch (wp.getNextElement ())
        
	  {
	  case WsdlParser::DOCUMENTATION:
	    cout << wp.getDocumentation () << endl;
	    break;
	  case WsdlParser::TYPES:
	    cout << wp.getNumSchemas () << "   schema(s) found" << endl;
	    break;
	  case WsdlParser::MESSAGE:
	    cout << "Message  :" << (wp.getMessage ())->getName () << endl;
	    break;
	  case WsdlParser::PORT_TYPE:
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
	      cout <<"  Input :"<<in->getName()<<endl;
	      cout <<"  Output :"<<out->getName()<<endl;
	      if (faults) {
		for (MessageList::iterator mli = faults->begin();
		     mli != faults->end();
		     mli++) {
		
		  cout<<"  Fault :"<<(*mli)->getName()<<endl;
		}
	      }
	      from++;
	    }
	    break;
	  }
      }
    if (!wp.status())
      return 1;
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


