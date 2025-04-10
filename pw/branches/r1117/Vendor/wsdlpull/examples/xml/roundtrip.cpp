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


#include <fstream>
#include <xmlpull/XmlPullParser.h>
#include <xmlpull/XmlPullParserException.h>
#include <xmlpull/XmlSerializer.h>

//demonstrates how to use the xml pull parser and serializer
//this file parses an xml and just prints it back
class Roundtrip
{
public:
  Roundtrip(XmlPullParser& p,XmlSerializer& s) ;
  void writeStartTag();
  void writeToken();
  void roundTrip();
private:
  XmlPullParser & parser;
  XmlSerializer& serializer;
};
	
Roundtrip::Roundtrip(XmlPullParser& p,XmlSerializer& s) 
  :parser(p),
   serializer(s)
{
}

void
Roundtrip::writeStartTag()
{
    
    if (!parser.getFeature(FEATURE_REPORT_NAMESPACE_ATTRIBUTES)) {
	for (int i =
		 parser.getNamespaceCount(parser.getDepth() - 1);
	     i
		 < parser.getNamespaceCount(parser.getDepth())
		 - 1;
	     i++) {
	    serializer.setPrefix(parser.getNamespacePrefix(i),
				 parser.getNamespaceUri(i));
	}
    }
    serializer.startTag(parser.getNamespace(),
			parser.getName());
    
    for (int i = 0; i < parser.getAttributeCount(); i++) {
	serializer.attribute(
			     parser.getAttributeNamespace(i),
			     parser.getAttributeName(i),
			     parser.getAttributeValue(i));
    }
}

void
Roundtrip::writeToken()
{
    
  switch (parser.getEventType()) {
  case XmlPullParser::START_DOCUMENT :
    serializer.startDocument ("", "");
    break;

  case XmlPullParser::END_DOCUMENT :
    serializer.endDocument();
    break;

  case XmlPullParser::START_TAG :
    writeStartTag();
    break;

  case XmlPullParser::END_TAG :
    serializer.endTag(
		      parser.getNamespace(),
		      parser.getName());
    break;

  case XmlPullParser::IGNORABLE_WHITESPACE :
    //comment it to remove ignorable whtespaces from XML infoset
    serializer.ignorableWhitespace(parser.getText());
    break;

  case XmlPullParser::TEXT :
    if(parser.getText() == "")
      std::cout<<"null text error at: "<<parser.getPositionDescription()<<std::endl;
    else
      serializer.text(parser.getText());
    break;

  case XmlPullParser::ENTITY_REF :
    if(parser.getText() != "")
      serializer.text(parser.getText());
    else 
      serializer.entityRef(parser.getName());
    break;

  case XmlPullParser::CDSECT :
    serializer.cdsect(parser.getText());
    break;

  case XmlPullParser::PROCESSING_INSTRUCTION :
    serializer.processingInstruction(
				     parser.getText());
    break;

  case XmlPullParser::COMMENT :
    serializer.comment(parser.getText());
    break;

  case XmlPullParser::DOCDECL :
    serializer.docdecl(parser.getText());
    break;

  default :
    throw new XmlPullParserException("unrecognized event: ","",0,0);
  }
}

void
Roundtrip::roundTrip()
{        	
    while (parser.getEventType() != XmlPullParser::END_DOCUMENT) {
	writeToken();
	serializer.flush();
	parser.nextToken();
    }
    writeToken();
}



int main(int argc,char**argv)
{
    
    if (argc!=2){
	std::cout<<"Usage"<<argv[0]<<" xmlfile"<<std::endl;
	return 0;
    }
 
    std::ifstream ifs;
    ifs.open(argv[1]);
    XmlPullParser xpp(ifs);
    xpp.setFeature(FEATURE_PROCESS_NAMESPACES,
		   true);
    XmlSerializer serializer;
    Roundtrip rt(xpp,serializer);
    rt.roundTrip();
    serializer.flush();
}



