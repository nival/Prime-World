/* Copyright (c) 2005,2007 Vivek Krishna
 *  Based on kxml2 by Stefan Haustein, Oberhausen, Rhld., Germany
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
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

#include "xmlpull/XmlPullParser.h"
#include "xmlpull/XmlPullParserException.h"
#include "xmlpull/XmlUtils.h"
//
#include <cstring>


XmlPullParser::XmlPullParser (std::istream & is)
  :unexpected_eof ("Unexpected EOF"),
   illegal_type ("wrong Event Type"),
   nspStack (16),
   elementStack (16),
   attributes (16),
   reader (is)
{
  initBuf ();
  commonInit ();
}


XmlPullParser::XmlPullParser (void)
  :unexpected_eof ("Unexpected EOF"),
   illegal_type ("wrong Event Type"),
   nspStack (16),
   elementStack (16),
   attributes (16),
   reader (std::cin)
{
  initBuf ();
  commonInit ();
}


void
XmlPullParser::initBuf ()
{
  srcBuf = new char[8192];
  srcBuflength = 8192;
  txtBuf = new char[256];
  txtBufSize = 256;
  nspCounts = new int[8];
  nspSize = 8;
}


//does common initializations
void
XmlPullParser::commonInit ()
{
  line = 1;
  column = 0;
  type = START_DOCUMENT;
  name = "";
  Ns = "";
  degenerated = false;
  attributeCount = -1;
  encoding = "";
  version = "";
  standalone = false;
  unresolved = false;
  LEGACY = 999;
  XML_DECL = 998;
  srcPos = 0;
  srcCount = 0;
  peekCount = 0;
  depth = 0;
  relaxed = false;
  skipNextTag=false;
  entityMap["apos"] = "'";
  entityMap["gt"] = ">";
  entityMap["lt"] = "<";
  entityMap["quot"] = "\"";
  entityMap["amp"] = "&";
  for (int i = 0; i < nspSize; i++)
    nspCounts[i] = 0;
}


XmlPullParser::~XmlPullParser (void)
{
  delete [] srcBuf;
  delete [] txtBuf;
  delete [] nspCounts;
}


std::string
XmlPullParser::state (int eventType)
{
  switch (eventType)
    {
    case 0:
      return "START_DOCUMENT";
    case 1:
      return "END_DOCUMENT";
    case 2:
      return "START_TAG";
    case 3:
      return "END_TAG";
    case 4:
      return "TEXT";
    case 5:
      return "CDSECT";
    case 6:
      return "ENTITY_REF";
    case 7:
      return "IGNORABLE_WHITESPACE";
    case 8:
      return "PROCESSING_INSTRUCTION";
    case 9:
      return "COMMENT";
    case 10:
      return "DOCDECL";
    default:
      return "Illegal state";
      break;
    }
  return "";
}


bool XmlPullParser::isProp (std::string n1, bool prop, std::string n2)
{
  if (n1.find ("http://xmlpull.org/v1/doc/") != 0)
    return false;
  if (prop)
    return (n1.substr (42) == n2);
  else
    return (n1.substr (40) == n2);
}


bool XmlPullParser::adjustNsp ()
{
  bool
    any = false;
  for (int i = 0; i < attributeCount << 2; i += 4)

    {
      std::string
	attrName = attributes[i + 2];
      int
	cut = attrName.find (":");
      std::string
	prefx;
      // Creating a variable named 'prefix' generates a warning about hiding the member, so I changed it to 'prefx'. -KEC
      if (cut != -1)

        {
	  prefx = attrName.substr (0, cut);
	  attrName = attrName.substr (cut + 1);
        }

      else if (attrName == "xmlns")

        {
	  prefx = attrName;
	  attrName = "";
        }

      else
	continue;
      if (prefx != "xmlns")
        {
	  any = true;
        }
      else
        {
	  unsigned int j = (nspCounts[depth]++) << 1;

	  //nspStack = ensureCapacity(nspStack, j + 2);
	  if (nspStack.size () <= j + 2)
	    nspStack.resize (j + 2 + RESIZE_BUFFER);
	  nspStack[j] = attrName;
	  nspStack[j + 1] = attributes[i + 3];
	  if (!attrName.empty () && attributes[i + 3] == "")
	    exception ("illegal empty namespace");

	  //vivek,array copy??
	  int to = ((--attributeCount) << 2) - i;
	  for (int p = 1; p <= to; p++)
	    attributes[i + p - 1] = attributes[i + 4 + p - 1];
	  i -= 4;
        }
    }
  if (any)

    {
      for (int i = (attributeCount << 2) - 4; i >= 0; i -= 4)

        {
	  std::string
	    attrName = attributes[i + 2];
	  int
	    cut = attrName.find (":");
	  if (cut == 0 && !relaxed)
	    exception ("illegal attribute name: " + attrName);

	  else if (cut != -1)

            {
	      std::string
		attrPrefix = attrName.substr (0, cut);
	      attrName = attrName.substr (cut + 1);
	      std::string
		attrNs = getNamespace (attrPrefix);
	      if (attrNs.empty () && !relaxed)
		exception ("Undefined Prefix: " + attrPrefix + " in ");
	      attributes[i] = attrNs;
	      attributes[i + 1] = attrPrefix;
	      attributes[i + 2] = attrName;
	      if (!relaxed)

                {
		  for (int j = (attributeCount << 2) - 4; j > i; j -= 4)
		    if (attrName == attributes[j + 2]
                        && attrNs == attributes[j])
		      exception ("Duplicate Attribute: {"
				 + attrNs + "}" + attrName);
                }
            }
        }
    }
  int cut = name.find (":");
  if (cut == 0 && !relaxed)
    exception ("illegal tag name: " + name);

  else if (cut != -1)
    {
      prefix = name.substr (0, cut);
      name = name.substr (cut + 1);
    }
  Ns = getNamespace (prefix);
  if (Ns.empty ())

    {
      if (!prefix.empty () && !relaxed)
	exception ("undefined prefix: " + prefix);
      Ns = NO_NAMESPACE;
    }
  return any;
}


void
XmlPullParser::exception (std::string desc)
{
  XmlPullParserException e (desc, state (type), line, column);
  throw e;
}


/**
 * common base for next and nextToken. Clears the state, except from
 * txtPos and whitespace. Does not set the type variable */
void
XmlPullParser::nextImpl ()
{
  if (type == END_TAG)
    depth--;
  while (true)
    {
      attributeCount = -1;
      if (degenerated)

        {
	  degenerated = false;
	  type = END_TAG;
	  return;
        }
      prefix = "";
      name = "";
      Ns = "";
      text = "";
      type = peekType ();
      switch (type)
        {
	case ENTITY_REF:
	  pushEntity ();
	  return;
	case START_TAG:
	  parseStartTag (false);
	  return;
	case END_TAG:
	  parseEndTag ();
	  return;
	case END_DOCUMENT:
	  return;
	case TEXT:
	  pushText ('<', !token);
	  if (depth == 0)

	    {
	      if (isWspace)
		type = IGNORABLE_WHITESPACE;

	      // make exception switchable for instances.chg... !!!!
	      //      else
	      //    exception ("text '"+getText ()+"' not allowed outside root element");
	    }
	  return;
	default:
	  type = parseLegacy (token);
	  if (type != XML_DECL)
	    return;
        }
    }
}


int
XmlPullParser::parseLegacy (bool bpush)
{
  std::string req = "";
  int term;
  int result;
  int prev = 0;
  read ();                                      // <
  int c = read ();
  if (c == '?')

    {
      if ((peekbuf (0) == 'x' || peekbuf (0) == 'X')
	  && (peekbuf (1) == 'm' || peekbuf (1) == 'M'))

        {
	  if (bpush)

            {
	      push (peekbuf (0));
	      push (peekbuf (1));
            }
	  read ();
	  read ();
	  if ((peekbuf (0) == 'l' || peekbuf (0) == 'L')
	      && peekbuf (1) <= ' ')

            {
	      if (line != 1 || column > 4)
		exception ("PI must not start with xml");
	      parseStartTag (true);
	      if (attributeCount < 1 || "version" != attributes[2])
		exception ("version expected");
	      version = attributes[3];
	      int pos = 1;
	      if (pos < attributeCount && "encoding" == attributes[2 + 4])

                {
		  encoding = attributes[3 + 4];
		  pos++;
                }
	      if (pos < attributeCount
		  && "standalone" == attributes[4 * pos + 2])

                {
		  std::string st = attributes[3 + 4 * pos];
		  if ("yes" == st)
		    standalone = true;

		  else if ("no" == st)
		    standalone = false;

		  else
		    exception ("illegal standalone value: " + st);
		  pos++;
                }
	      if (pos != attributeCount)
		exception ("illegal xmldecl");
	      isWspace = true;
	      txtPos = 0;
	      return XML_DECL;
            }
        }

      /*            int c0 = read ();
		    int c1 = read ();
		    int */
      term = '?';
      result = PROCESSING_INSTRUCTION;
    }

  else if (c == '!')

    {
      if (peekbuf (0) == '-')

        {
	  result = COMMENT;
	  req = "--";
	  term = '-';
        }

      else if (peekbuf (0) == '[')

        {
	  result = CDSECT;
	  req = "[CDATA[";
	  term = ']';
	  bpush = true;
        }

      else

        {
	  result = DOCDECL;
	  req = "DOCTYPE";
	  term = -1;
        }
    }

  else

    {
      exception ("illegal: <" + c);
      return -1;
    }
  for (unsigned int i = 0; i < req.length (); i++)
    read (req.at (i));
  if (result == DOCDECL)
    parseDoctype (bpush);

  else

    {
      while (true)

        {
	  c = read ();
	  if (c == -1)
	    exception (unexpected_eof);
	  if (bpush)
	    push (c);
	  if ((term == '?' || c == term)
	      && peekbuf (0) == term && peekbuf (1) == '>')
	    break;
	  prev = c;
        }
      if (term == '-' && prev == '-' && !relaxed)
	exception ("illegal comment delimiter: --->");
      read ();
      read ();
      if (bpush && term != '?')
	txtPos--;
    }
  return result;
}


/** precondition: &lt! consumed */
void
XmlPullParser::parseDoctype (bool bpush)
{
  int nesting = 1;
  bool quoted = false;

  // read();
  while (true)

    {
      int i = read ();
      switch (i)

        {
	case -1:
	  exception (unexpected_eof);
	case '\'':
	  quoted = !quoted;
	  break;
	case '<':
	  if (!quoted)
	    nesting++;
	  break;
	case '>':
	  if (!quoted)

	    {
	      if ((--nesting) == 0)
		return;
	    }
	  break;
        }
      if (bpush)
	push (i);
    }
}


/* precondition: &lt;/ consumed */
void
XmlPullParser::parseEndTag ()
{
  read ();                                      // '<'
  read ();                                      // '/'
  name = readName ();
  skip ();
  read ('>');
  int sp = (depth - 1) << 2;
  if (!relaxed)

    {
      if (depth == 0)
	exception ("element stack empty");
      if (name != elementStack[sp + 3])
	exception ("expected: " + elementStack[sp + 3]);
    }

  else if (depth == 0 || name != elementStack[sp + 3])
    return;
  Ns = elementStack[sp];
  prefix = elementStack[sp + 1];
  name = elementStack[sp + 2];
}


int
XmlPullParser::peekType ()
{
  switch (peekbuf (0))

    {
    case -1:
      return END_DOCUMENT;
    case '&':
      return ENTITY_REF;
    case '<':
      switch (peekbuf (1))

        {
	case '/':
	  return END_TAG;
	case '?':
	case '!':
	  return LEGACY;
	default:
	  return START_TAG;
	}
    default:
      return TEXT;
    }
}


std::string XmlPullParser::get (int pos)
{
  std::string
    tmp (txtBuf);
  return tmp.substr (pos, txtPos - pos);
}


void
XmlPullParser::push (int c)
{
  isWspace &= c <= ' ';
  if (txtPos >= txtBufSize - 1)

    {
      char *bigger = new char[txtBufSize = txtPos * 4 / 3 + 4];
      memcpy (bigger, txtBuf, txtPos);
      delete[] txtBuf;
      txtBuf = bigger;
    }
  txtBuf[txtPos++] = (char) c;
  txtBuf[txtPos] = 0;
}


/** Sets name and attributes */
void
XmlPullParser::parseStartTag (bool xmldecl)
{
  if (!xmldecl)
    read ();
  name = readName ();
  attributeCount = 0;
  while (true)

    {
      skip ();
      int c = peekbuf (0);
      if (xmldecl)

        {
	  if (c == '?')

            {
	      read ();
	      read ('>');
	      return;
            }
        }

      else

        {
	  if (c == '/')

            {
	      degenerated = true;
	      read ();
	      skip ();
	      read ('>');
	      break;
            }
	  if (c == '>' && !xmldecl)

            {
	      read ();
	      break;
            }
        }
      if (c == -1)
	exception (unexpected_eof);
      std::string attrName = readName ();
      if (attrName.empty ())
	exception ("attr name expected");
      skip ();
      read ('=');
      skip ();
      int delimiter = read ();
      if (delimiter != '\'' && delimiter != '"')

        {
	  if (!relaxed)
	    exception ("<"
		       + name + ">: invalid delimiter: " + (char) delimiter);
	  delimiter = ' ';
        }
      unsigned int i = (attributeCount++) << 2;

      //attributes = ensureCapacity(attributes, i + 4);
      if (attributes.size () <= i + 4)
	attributes.resize (i + 4 + RESIZE_BUFFER);
      attributes[i++] = "";
      attributes[i++] = "";
      attributes[i++] = attrName;
      int p = txtPos;
      pushText (delimiter, true);
      attributes[i] = get (p);
      txtPos = p;
      if (delimiter != ' ')
	read ();                              // skip endquote
    }
  unsigned  int sp = depth++ << 2;

  //elementStack = ensureCapacity(elementStack, sp + 4,elementStackSize);
  if (elementStack.size () <= sp + 4)
    elementStack.resize (sp + 4 + RESIZE_BUFFER);
  elementStack[sp + 3] = name;

  /*    vivek ,avoided the increment array logic..fix later*/
  if (depth >= nspSize)

    {
      int *bigger = new int[nspSize + 4];
      int i = 0;
      for (i = 0; i < nspSize; i++)
	bigger[i] = nspCounts[i];
      for (i = nspSize; i < nspSize + 4; i++)
	bigger[i] = 0;
      delete [] nspCounts;
      nspCounts = bigger;
      nspSize += 4;
    }
  nspCounts[depth] = nspCounts[depth - 1];
  for (int i = attributeCount - 1; i > 0; i--)

    {
      for (int j = 0; j < i; j++)

        {
	  if (getAttributeName (i) == getAttributeName (j))
	    exception ("Duplicate Attribute: " + getAttributeName (i));
        }
    }
  if (processNsp)
    adjustNsp ();

  else
    Ns = "";
  elementStack[sp] = Ns;
  elementStack[sp + 1] = prefix;
  elementStack[sp + 2] = name;
}


/** result: isWspace; if the setName parameter is set,
the name of the entity is stored in "name" */
void
XmlPullParser::pushEntity ()
{
  read ();                                      // &
  int pos = txtPos;
  while (true)

    {
      int c = read ();
      if (c == ';')
	break;
      if (relaxed && (c == '<' || c == '&' || c <= ' '))

        {
	  if (c != -1)
	    push (c);
	  return;
        }
      if (c == -1)
	exception (unexpected_eof);
      push (c);
    }
  std::string code = get (pos);
  txtPos = pos;
  if (token && type == ENTITY_REF)
    name = code;
  if (code[0] == '#')

    {
      int c = (code[1] == 'x' ? XmlUtils::parseInt (code.substr (2),16)
	       : XmlUtils::parseInt (code.substr (1)));
      push (c);
      return;
    }
  std::string result = (std::string) entityMap[code];
  unresolved = result == "";
  if (unresolved)

    {
      if (!token)
	exception ("unresolved: &" + code + ";");
    }

  else

    {
      for (unsigned int i = 0; i < result.length (); i++)
	push (result.at (i));
    }
}


/** types:
'<': parse to any token (for nextToken ())
'"': parse to quote
' ': parse to whitespace or '>'
*/
void
XmlPullParser::pushText (int delimiter, bool resolveEntities)
{
  int next = peekbuf (0);
  while (next != -1 && next != delimiter)       // covers eof, '<', '"'
    {
      if (delimiter == ' ')
	if (next <= ' ' || next == '>')
	  break;
      if (next == '&')

        {
	  if (!resolveEntities)
	    break;
	  pushEntity ();
        }

      else if (next == '\n' && type == START_TAG)

        {
	  read ();
	  push (' ');
        }

      else
	push (read ());
      next = peekbuf (0);
    }
}


void
XmlPullParser::read (char c)
{
  int a = read ();
  std::string sa (1, (char) a), sc (1, c);
  if (a != c)
    exception ("expected: '" + sc + "' actual: '" + sa + "'");
}


int
XmlPullParser::read ()
{
  int result;
  if (peekCount == 0)
    result = peekbuf (0);

  else

    {
      result = peek[0];
      peek[0] = peek[1];
    }
  peekCount--;
  column++;
  if (result == '\n')

    {
      line++;
      column = 1;
    }
  return result;
}


/** Does never read more than needed */
int
XmlPullParser::peekbuf (int pos)
{
  while (pos >= peekCount)

    {
      int nw;
      if (srcBuflength <= 1)
	nw = reader.get ();

      else if (srcPos < srcCount)
	nw = srcBuf[srcPos++];

      else

        {
	  srcCount = reader.read (srcBuf, srcBuflength).gcount ();
	  if (srcCount <= 0)
	    nw = -1;

	  else
	    nw = srcBuf[0];
	  srcPos = 1;
        }
      if (nw == '\r')

        {
	  wasCR = true;
	  peek[peekCount++] = '\n';
        }

      else

        {
	  if (nw == '\n')

            {
	      if (!wasCR)
		peek[peekCount++] = '\n';
            }

	  else
	    peek[peekCount++] = nw;
	  wasCR = false;
        }
    }
  return peek[pos];
}


std::string XmlPullParser::readName ()
{
  int  pos = txtPos;
  int  c = peekbuf (0);
  if ((c < 'a' || c > 'z')
      && (c < 'A' || c > 'Z') && c != '_' && c != ':' && c < 0x0c0)
    exception ("name expected");

  do

    {
      push (read ());
      c = peekbuf (0);
    }
  while ((c >= 'a' && c <= 'z')
	 || (c >= 'A' && c <= 'Z')
	 || (c >= '0' && c <= '9')
	 || c == '_' || c == '-' || c == ':' || c == '.' || c >= 0x0b7);
  std::string
    result = get (pos);
  txtPos = pos;
  return result;
}


void
XmlPullParser::skip ()
{
  while (true)

    {
      int c = peekbuf (0);
      if (c > ' ' || c == -1)
	break;
      read ();
    }
}


//--------------- public part starts here... ---------------
bool XmlPullParser::getFeature (std::string feature)
{
  if (FEATURE_PROCESS_NAMESPACES == feature)
    return processNsp;

  else if (isProp (feature, false, "relaxed"))
    return relaxed;

  else
    return false;
}


std::string XmlPullParser::getInputEncoding ()
{
  return encoding;
}


void
XmlPullParser::defineEntityReplacementText (std::string entity, std::string value)
{
  if (entityMap.empty ())
    exception ("entity replacement text must be defined after setInput!");
  entityMap[entity] = value;
}


int
XmlPullParser::getNamespaceCount (int d)
{
  if (d > depth)
    exception ("IndexOutOfBoundsException");;
  return nspCounts[d];
}


std::string XmlPullParser::getNamespacePrefix (int pos)
{
  return nspStack[pos << 1];
}


std::string XmlPullParser::getNamespaceUri (int pos)
{
  return nspStack[(pos << 1) + 1];
}


std::string XmlPullParser::getNamespace (std::string prefx)
{
  if ("xml" == prefx)
    return "http://www.w3.org/XML/1998/namespace";
  if ("xmlns" == prefx)
    return "http://www.w3.org/2000/xmlns/";
  for (int i = (getNamespaceCount (depth) << 1) - 2; i >= 0; i -= 2)

    {
      if (prefx.empty ())

        {

	  //cout<<nspStack[i]<<nspStack[i+1]<<endl;
	  if (nspStack[i].empty ())
	    return nspStack[i + 1];
        }

      else if (prefx == nspStack[i])
	return nspStack[i + 1];
    }
  return "";
}


int
XmlPullParser::getDepth ()
{
    return depth;
}


std::string 
XmlPullParser::getPositionDescription ()
{
  std::ostringstream buf (std::ios::ate);  
  //vivek,replace 11 by the number of event types
  buf << (type < 11 ? state (type) : "Unknown Event");
  buf << " ";
  if (type == START_TAG || type == END_TAG)

    {
      if (degenerated)
	buf << "(empty) ";
      buf << "<";
      if (type == END_TAG)
	buf << "/";
      if (!prefix.empty ())
	buf << "{" << Ns << "}" << prefix << ":";
      buf << name;
      int
	cnt = attributeCount << 2;
      for (int i = 0; i < cnt; i += 4)

        {
	  buf << " ";
	  if (!attributes[i + 1].empty ())
	    buf << "{" << attributes[i] << "}" << attributes[i + 1] << ":";
	  buf << attributes[i + 2] << "='" << attributes[i + 3] << "'";
        }
      buf << ">";
    }

  else if (type == IGNORABLE_WHITESPACE);

  else if (type != TEXT)
    buf << getText ();

  else if (isWspace)
    buf << "(whitespace)";

  else

    {
      std::string
	txt = getText ();
      if (txt.length () > 16)
	txt = txt.substr (0, 16) + "...";
      buf << txt;
    }
  buf << " @" << line << ":" << column;
  return buf.str ();                            //replace buf with an ostream
}


bool XmlPullParser::isWhitespace ()
{
  if (type != TEXT && type != IGNORABLE_WHITESPACE && type != CDSECT)
    exception (illegal_type);
  return isWspace;
}


std::string XmlPullParser::getText ()
{
  return type < TEXT || (type == ENTITY_REF && unresolved) ? "" : get (0);
}


const char *
XmlPullParser::getTextCharacters (int *poslen)
{
  if (type >= TEXT)

    {
      if (type == ENTITY_REF)

        {
	  poslen[0] = 0;
	  poslen[1] = name.length ();
	  return name.c_str ();                 //return name.toCharArray();
        }
      poslen[0] = 0;
      poslen[1] = txtPos;
      return txtBuf;
    }
  poslen[0] = -1;
  poslen[1] = -1;
  return 0;
}


bool XmlPullParser::isEmptyElementTag ()
{
  if (type != START_TAG)
    exception (illegal_type);
  return degenerated;
}


std::string XmlPullParser::getAttributeNamespace (int index)
{
  if (index >= attributeCount)
    exception ("IndexOutOfBoundsException()");
  return attributes[index << 2];
}


std::string XmlPullParser::getAttributeName (int index)
{
  if (index >= attributeCount)
    exception ("IndexOutOfBoundsException()");
  return attributes[(index << 2) + 2];
}


std::string XmlPullParser::getAttributePrefix (int index)
{
    if (index >= attributeCount)
        exception ("IndexOutOfBoundsException()");
    return attributes[(index << 2) + 1];
}


std::string XmlPullParser::getAttributeValue (int index)
{
    if (index >= attributeCount)
        exception ("IndexOutOfBoundsException()");
    return attributes[(index << 2) + 3];
}


std::string XmlPullParser::getAttributeValue (std::string ns, std::string nam)
{
    for (int i = (attributeCount << 2) - 4; i >= 0; i -= 4)

    {
        if (attributes[i + 2] == nam && (ns.empty () || attributes[i] == ns))
            return attributes[i + 3];
    }
    return "";
}


int
XmlPullParser::next ()
{
    txtPos = 0;
    isWspace = true;
    int minType = 9999;
    token = false;

    do

    {
        nextImpl ();
        if (type < minType)
            minType = type;

//          if (curr <= TEXT) type = curr;
    }
    while (minType > CDSECT                       // ignorable
        || (minType >= TEXT && peekType () >= TEXT));
    type = minType;
    if (type > TEXT)
        type = TEXT;
    return type;
}


int
XmlPullParser::nextToken ()
{
    isWspace = true;
    txtPos = 0;
    token = true;
    nextImpl ();
    return type;
}

void
XmlPullParser::prevTag()
{
  skipNextTag=true;
}

//----------------------------------------------------------------------
// utility methods to make XML parsing easier ...
int
XmlPullParser::nextTag ()
{
  if(skipNextTag){
    skipNextTag = false;
    return type;
  }
   next ();
    if (type == TEXT && isWspace)
        next ();
    if (type != END_TAG && type != START_TAG && type != END_DOCUMENT)
        exception ("unexpected type");
    return type;
}


void
XmlPullParser::require (int Type, std::string ns, std::string nam)
{
    if (Type != type || (!ns.empty () && ns != getNamespace ())
        || (!nam.empty () && nam != getName ()))
        exception ("expected: " + state (Type) + " {" + ns + "}" + nam);
}


std::string XmlPullParser::nextText ()
{
    if (type != START_TAG)
        exception ("precondition: START_TAG");
    next ();
    std::string
        result;
    if (type == TEXT)

    {
        result = getText ();
        next ();
    }

    else
        result = "";
    if (type != END_TAG)
        exception ("END_TAG expected");
    return result;
}


void
XmlPullParser::setFeature (std::string feature, bool value)
{
    if (FEATURE_PROCESS_NAMESPACES == feature)
        processNsp = value;

    else if (isProp (feature, false, "relaxed"))
        relaxed = value;

    else
        exception ("unsupported feature: " + feature);
}

/*
void
XmlPullParser::setProperty(std::string property,  std::string value)
{
  if(isProp(property, true, "location"))
    {
      location = value;
    }
  else
  exception ("unsupported property: " + property);
}
*/

/**
 * Skip sub tree that is currently parser positioned on.
 * <br>NOTE: parser must be on START_TAG and when funtion returns
 * parser will be positioned on corresponding END_TAG. 
 */
//	Implementation copied from Alek's mail... 

void
XmlPullParser::skipSubTree() {
  require(START_TAG, "", "");
  int level = 1;
  while (level > 0) {
    int eventType = next();
    if (eventType == END_TAG) {
      --level;
    }
    else if (eventType == START_TAG) {
      ++level;
    }
  }
}

