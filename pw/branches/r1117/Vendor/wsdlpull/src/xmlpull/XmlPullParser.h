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


#ifndef _XMLPULLPARSERH
#define _XMLPULLPARSERH

#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#ifdef HAVE_CONFIG_H //
#include <config.h>
#endif 
#include "wsdlpull_export.h"

/** A simple, pull based XML parser.  */
const int RESIZE_BUFFER = 16;


//features
#define FEATURE_PROCESS_NAMESPACES "http://xmlpull.org/v1/doc/features.html#process-namespaces"
#define FEATURE_REPORT_NAMESPACE_ATTRIBUTES "http://xmlpull.org/v1/doc/features.html#report-namespace-prefixes"
#define FEATURE_PROCESS_DOCDECL "http://xmlpull.org/v1/doc/features.html#process-docdecl"
#define FEATURE_VALIDATION "http://xmlpull.org/v1/doc/features.html#validation"
#define NO_NAMESPACE ""

class WSDLPULL_EXPORT XmlPullParser
{
 public:
 
  XmlPullParser (std::istream & is);
  //constructor
  XmlPullParser (void);
  ~XmlPullParser (void);
  bool getFeature (std::string feature);
  std::string getInputEncoding ();
  void defineEntityReplacementText (std::string entity, std::string value);
  int getNamespaceCount (int depth);
  std::string getNamespacePrefix (int pos);
  std::string getNamespaceUri (int pos);
  std::string getNamespace (std::string prefix);
  
  int getDepth ();
  std::string getPositionDescription ();
  int getLineNumber ()
    {
      return line;
    }
  int getColumnNumber ()
    {
      return column;
    }
  bool isWhitespace ();
  std::string getText ();
  const char *getTextCharacters (int *poslen);
  std::string getNamespace ()
    {
      return Ns;
    }
  std::string getName ()
    {
      return name;
    }
  std::string getPrefix ()
    {
      return prefix;
    }
  bool isEmptyElementTag ();
  int getAttributeCount ()
    {
      return attributeCount;
    }
  std::string getAttributeType (int /* index */)
    {
      return "CDATA";
    }
  bool isAttributeDefault (int /* index */)
    {
      return false;
    }
  std::string getAttributeNamespace (int index);
  std::string getAttributeName (int index);
  std::string getAttributePrefix (int index);
  std::string getAttributeValue (int index);
  std::string getAttributeValue (std::string ns, std::string name);
  int getEventType ()
    {
      return type;
    }
  //parsing methods
  int next ();
  int nextToken ();
  int nextTag ();
  void prevTag();

  //----------------------------------------------------------------------
  // utility methods to make XML parsing easier ...
  void require (int type, std::string ns, std::string name);
  std::string nextText ();
  void setFeature (std::string feature, bool value);
  void skipSubTree() ;
  //  void setProperty(std::string property,  std::string value);


  //enum for event types
  enum
    {
      START_DOCUMENT ,
      END_DOCUMENT,
      START_TAG,
      END_TAG,
      TEXT,
      CDSECT,
      ENTITY_REF,
      IGNORABLE_WHITESPACE,
      PROCESSING_INSTRUCTION,
      COMMENT,
      DOCDECL
    };
 private:
  void commonInit (void);
  void initBuf (void);

  //returns the state name as  a std::string
  std::string state (int eventType);
  bool isProp (std::string n1, bool prop, std::string n2);
  bool adjustNsp ();                            //throws XmlPullParserException
  std::string *ensureCapacity (std::string * arr, int required);
  void exception (std::string desc);                 //throws XmlPullParserException

  /**
   * common base for next and nextToken. Clears the state, except from
   * txtPos and whitespace. Does not set the type variable */
  void nextImpl ();                             //throws IOException, XmlPullParserException
  int parseLegacy (bool push);

  //throws IOException, XmlPullParserException

  /** precondition: &lt! consumed */
  void parseDoctype (bool push);

  /* precondition: &lt;/ consumed */
  void parseEndTag ();
  int peekType ();
  std::string get (int pos);
  void push (int c);

  /** Sets name and attributes */
  void parseStartTag (bool xmldecl);

  /** result: isWspace; if the setName parameter is set,
      the name of the entity is stored in "name" */

  //vivek
  void pushEntity ();

  /** types:
      '<': parse to any token (for nextToken ())
      '"': parse to quote
      ' ': parse to whitespace or '>'
  */
  void pushText (int delimiter, bool resolveEntities);
  void read (char c);
  int read ();

  /** Does never read more than needed */
  int peekbuf (int pos);
  std::string readName ();
  void skip ();
  std::string unexpected_eof;
  std::string illegal_type;
  int LEGACY;
  int XML_DECL;

  // general
  std::string version;
  bool standalone;

  //   private bool reportNspAttr;
  bool processNsp;
  bool relaxed;
  std::map < std::string, std::string > entityMap;
  int depth;
  std::vector < std::string > nspStack;
  std::vector < std::string > elementStack;
  int *nspCounts;
  int nspSize;


  std::string encoding;
  char *srcBuf;
  int srcPos;
  int srcCount;
  int srcBuflength;

  //    private bool eof;
  int line;
  int column;

  // txtbuffer
  char *txtBuf;
  int txtPos;
  int txtBufSize;

  // Event-related
  int type;
  std::string text;
  bool isWspace,skipNextTag;
  std::string Ns;
  std::string prefix;
  std::string name;
  bool degenerated;
  int attributeCount;
  std::vector < std::string > attributes;
  // source
  std::istream & reader;

  /**
   * A separate peek buffer seems simpler than managing
   * wrap around in the first level read buffer */
  int peek[2];
  int peekCount;
  bool wasCR;
  bool unresolved;
  bool token;
};
#endif                                            /*  */
