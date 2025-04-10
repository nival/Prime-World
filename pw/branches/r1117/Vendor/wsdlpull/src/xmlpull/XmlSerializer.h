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
 * IN THE SOFTWARE. */
 
#ifndef _XMLSERIALIZERH
#define _XMLSERIALIZERH

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#ifdef HAVE_CONFIG_H //
#include <config.h>
#endif 
#include "wsdlpull_export.h"

class WSDLPULL_EXPORT XmlSerializer {
 
 public:
  XmlSerializer(std::ostream &os, std::string encoding="utf");
  XmlSerializer(std::string encoding="utf");//standard output
  ~XmlSerializer(void);
  void docdecl(std::string dd);
  void startDocument(std::string encoding,
		     bool standalone);
  XmlSerializer& startTag(std::string nsp, std::string name);
  XmlSerializer& attribute(std::string nsp,
			   std::string name,
			   std::string value);
  XmlSerializer& endTag(std::string nsp, std::string name);
  void endDocument();
  void entityRef(std::string name);
  bool getFeature(std::string name);
  std::string getPrefix(std::string nsp, bool create);
  std::string getPrefix(std::string nsp,
			bool includeDefault,
			bool create);

  void ignorableWhitespace(std::string s);
  void setFeature(std::string name, bool value);
  void setPrefix(std::string prefix, std::string nsp);

  void flush();
  std::string getNamespace();
  std::string getName();
  int getDepth();
  XmlSerializer& text(std::string txt);
  XmlSerializer& text(std::string txt, int start, int len);
  void cdsect(std::string data);
  void comment(std::string comment);
  void processingInstruction(std::string pi);

  
 private:
  std::ostream& writer;
  bool pending;
  int auto_;
  unsigned int depth;
  std::string encoding;
  std::vector<std::string> elementStack,nspStack;
  //nsp/prefix/name
  std::vector<int> nspCounts;
  //prefix/nsp; both empty are ""
  std::vector<bool> indent;
  bool unicode;
  void check(bool close);
  void writeEscaped(std::string s, int quot);
  void exception (std::string desc);
  void init();
};

#endif
