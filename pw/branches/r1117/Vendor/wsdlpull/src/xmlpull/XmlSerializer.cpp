/* Copyright (c) 2005,2007 Vivek Krishna
 *  Based on kxml2 by Stefan Haustein, Oberhausen, Rhld., Germany
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The  above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE. 
 *
 */


#include "xmlpull/XmlSerializer.h"
#include "xmlpull/XmlPullParserException.h"
#include "xmlpull/XmlUtils.h"
 
XmlSerializer::XmlSerializer(std::ostream &os,std::string enc)
  :writer(os),
   encoding(enc),
   elementStack(16),
   nspStack(16),
   nspCounts(8),
   indent(8)
{
  init();
}

XmlSerializer::XmlSerializer(std::string enc)
  :writer(std::cout),
   encoding(enc),
   elementStack(16),
   nspStack(16),
   nspCounts(8),
   indent(8)
{
  init();
}

XmlSerializer::~XmlSerializer()
{
}

void
XmlSerializer::init()
{
  nspCounts[0] = 2;
  nspCounts[1] = 2;
  nspStack[0] = "";
  nspStack[1] = "";
  nspStack[2] = "xml";
  nspStack[3] = "http://www.w3.org/XML/1998/namespace";
  pending = false;
  auto_ = 0;
  depth = 0;
  if (encoding.find("utf",0)!=std::string::npos)
    unicode = true;
  else
    unicode = false;
}

void
XmlSerializer::check(bool close)
{
  if (!pending)
    return;
  depth++;
  pending = false;

  if (indent.size() <= depth) {
    indent.resize(depth + 4);
  }
  indent[depth] = indent[depth - 1];

  for (int i = nspCounts[depth - 1];
       i < nspCounts[depth];
       i++) {
    
    writer<<' ';
    writer<<"xmlns";
    if (""!=nspStack[i * 2]) {
      writer<<':';
      writer<<nspStack[i * 2];
    }
    else if (getNamespace() != ""  && nspStack[i * 2 + 1]!="")
      exception("Cannot set default namespace for elements in no namespace");
    writer<<"=\"";
    writeEscaped(nspStack[i * 2 + 1], '"');
    writer<<'"';
  }

  if (nspCounts.size() <= depth + 1) {
    nspCounts.resize(depth + 8);
  }

  nspCounts[depth + 1] = nspCounts[depth];
  //   nspCounts[depth + 2] = nspCounts[depth];

  writer<<(close ? " />" : ">");
}

void
XmlSerializer::writeEscaped(std::string s, int quot)
{

  for (size_t i = 0; i < s.length(); i++) {
    unsigned char c = s[i];
    switch (c) {
    case '\n':
    case '\r':
    case '\t':
      if(quot == -1) 
	writer<<c;
      else 
	writer<<"&#"+((int) c)+';';
      break;
    case '&' :
      writer<<"&amp;";
      break;
    case '>' :
      writer<<"&gt;";
      break;
    case '<' :
      writer<<"&lt;";
      break;
    case '"' :
    case '\'' :
      if (c == quot) {
	writer<<(c == '"' ? "&quot;" : "&apos;");
	break;
      }
    default :
      //if(c < ' ')
      //	exception("Illegal control code:"+((int) c));

      if (c >= ' ' && c !='@' && (c < 127 || unicode))
	writer<<c;
      else
	writer<<"&#" << ((int) c) << ";";
    }
  }
}


void
XmlSerializer::docdecl(std::string dd) 
{
  writer<<"<!DOCTYPE";
  writer<<dd;
  writer<<">";
}

void
XmlSerializer::endDocument() {
  while (depth > 0) {
    endTag(
	   elementStack[depth * 3 - 3],
	   elementStack[depth * 3 - 1]);
  }
  flush();
}

void
XmlSerializer::entityRef(std::string name) 
{
  check(false);
  writer<<'&';
  writer<<name;
  writer<<';';
}

bool
XmlSerializer:: getFeature(std::string name) {
  //return false;
  return ("http://xmlpull.org/v1/doc/features.html#indent-output" == name)
    ? indent[depth]
    : false;
}

std::string 
XmlSerializer::getPrefix(std::string ns, bool create) 
{
  return getPrefix(ns, false, create);
}


std::string
XmlSerializer::getPrefix(std::string ns,
			 bool includeDefault,
			 bool create)
{
  
  for (int i = nspCounts[depth + 1] * 2 - 2;
       i >= 0;
       i -= 2) {
    
    if (nspStack[i + 1] == ns
	&& (includeDefault || nspStack[i]!="")) {
      std::string cand = nspStack[i];
      for (int j = i + 2;
	   j < nspCounts[depth + 1] * 2;
	   j++) {
	if (nspStack[j]==cand) {
	  cand = "";
	  break;
	}
      }
      if (cand != "")
	return cand;
    }
  }

  if (!create)
    return "";

  std::string prefix;

  if (ns=="")
    prefix = "";
  else {
    do {
      prefix = "n" + (auto_++);
      for (int i = nspCounts[depth + 1] * 2 - 2;
	   i >= 0;
	   i -= 2) {
	if (prefix==nspStack[i]) {
	  prefix = "";
	  break;
	}
      }
    }
    while (prefix == "");
  }

  bool p = pending;
  pending = false;
  setPrefix(prefix, ns);
  pending = p;
  return prefix;
}

void
XmlSerializer::ignorableWhitespace(std::string s)
{
  text(s);
}

void
XmlSerializer::setFeature(std::string name, bool value) 
{
  if ("http://xmlpull.org/v1/doc/features.html#indent-output"==name) {
    indent[depth] = value;
  }
  else
    exception("Unsupported Feature");
}

void
XmlSerializer::setPrefix(std::string prefix, std::string nsp)
{
  check(false);
  std::string defined = getPrefix(nsp, true, false);

  // boil out if already defined

  if (prefix==defined)
    return;

  unsigned int pos = (nspCounts[depth + 1]++) << 1;

  if (nspStack.size() < pos + 1) {
    nspStack.resize(nspStack.size() + 16);
  }

  nspStack[pos++] = prefix;
  nspStack[pos] = nsp;
}

void
XmlSerializer::startDocument(std::string enc,
				 bool standalone)
  {
    writer<<"<?xml version='1.0' ";
    
    if (encoding != "") {
      this->encoding = enc;
      if (encoding.find("utf",0)!=std::string::npos)
	unicode = true;
    }
    
    if (encoding != "") {
      writer<<"encoding='";
      writer<<encoding;
      writer<<"' ";
    }

      writer<<"standalone='";
      writer<<(standalone ? "yes" : "no");
      writer<<"' ";
      writer<<"?>";
  }

XmlSerializer&
XmlSerializer::startTag(std::string nsp, std::string name)
{
  check(false);
  
  //        if (namespace == "")
  //            namespace = "";

  if (indent[depth]) {
    writer<<"\r\n";
    for (unsigned int i = 0; i < depth; i++)
      writer<<"  ";
  }

  unsigned int esp = depth * 3;
  if (elementStack.size() < esp + 3) {
    elementStack.resize(elementStack.size() + 16);
  }

  std::string prefix =
    nsp == ""
    ? ""
    : getPrefix(nsp, true, true);

  if (nsp=="") {
    for (int i = nspCounts[depth];
	 i < nspCounts[depth + 1];
	 i++) {
      
      if (nspStack[i * 2]== "" &&  nspStack[i * 2 + 1]!= "") {
	exception("Cannot set default namespace for elements in no namespace");
      }
    }
  }

  elementStack[esp++] = nsp;
  elementStack[esp++] = prefix;
  elementStack[esp] = name;

  writer<<'<';
  if (prefix!="") {
    writer<<prefix;
    writer<<':';
  }

  writer<<name;

  pending = true;
  return *this;
}

XmlSerializer&
XmlSerializer::attribute(std::string nsp,
			     std::string name,
			     std::string value)
{
  if (!pending)
    exception("illegal position for attribute");

  //        int cnt = nspCounts[depth];

  if (nsp == "")
    nsp = "";

  //		depth--;
  //		pending = false;
  
  std::string prefix =(nsp=="")? "": getPrefix(nsp, false, true);

  //		pending = true;
  //		depth++;

  /*        if (cnt != nspCounts[depth]) {
	    writer<<' ';
	    writer<<"xmlns";
	    if (nspStack[cnt * 2] != "") {
	    writer<<':';
	    writer<<nspStack[cnt * 2];
	    }
	    writer<<"=\"";
	    writeEscaped(nspStack[cnt * 2 + 1], '"');
	    writer<<'"';
	    }
  */

  writer<<' ';
  if (prefix!="") {
    writer<<prefix;
    writer<<':';
  }
  writer<<name;
  writer<<'=';
  char q = value.find('"') == std::string::npos ? '"' : '\'';
  writer<<q;
  writeEscaped(value, q);
  writer<<q;
  return *this;
}

void
XmlSerializer::flush()
{
  check(false);
  writer.flush();
}

XmlSerializer&
XmlSerializer::endTag(std::string nsp, std::string name)
{

  if (!pending)
    depth--;
  //        if (nsp == "")
  //          nsp = "";

  if ((nsp == ""
       && elementStack[depth * 3] != "")
      || (nsp != ""
	  && nsp!=elementStack[depth * 3])
      || elementStack[depth * 3 + 2] != name)
    
    exception("</{"+nsp+"}"+name+"> does not match start");
  
  if (pending) {
    check(true);
    depth--;
  }
  else {
    if (indent[depth + 1]) {
      writer<<"\r\n";
      for (unsigned int i = 0; i < depth; i++)
	writer<<"  ";
    }

    writer<<"</";
    std::string prefix = elementStack[depth * 3 + 1];
    if (prefix != "") {
      writer<<prefix;
      writer<<':';
    }
    writer<<name;
    writer<<'>';
  }
  
  nspCounts[depth + 1] = nspCounts[depth];
  return *this;
}


std::string
XmlSerializer::getNamespace() 
{
  return getDepth() == 0 ? "" : elementStack[getDepth() * 3 - 3];
}

std::string
XmlSerializer::getName() 
{
  return getDepth() == 0 ? "" : elementStack[getDepth() * 3 - 1];
}

int
XmlSerializer::getDepth() {
  return pending ? depth + 1 : depth;
}

XmlSerializer&
XmlSerializer::text(std::string txt){
   check(false);
   indent[depth] = false;
   writeEscaped(txt, -1);
   return *this;
 }

XmlSerializer&
XmlSerializer::text(std::string txt, int start, int len)
{
  text(txt.substr(start, len));
  return *this;
}

void
XmlSerializer::cdsect(std::string data)
{
  check(false);
  writer<<"<![CDATA[";
  writer<<data;
  writer<<"]]>";
}

void
XmlSerializer::comment(std::string comment) {
  check(false);
  writer<<"<!--";
  writer<<comment;
  writer<<"-->";
}

void
XmlSerializer::processingInstruction(std::string pi)
{
  check(false);
  writer<<"<?";
  writer<<pi;
  writer<<"?>";
}

void
XmlSerializer::exception (std::string desc)
{
  XmlPullParserException e (desc,elementStack.front(),0,0);
  throw e;
}
