/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */


#include "avmplus.h"
#include "BuiltinNatives.h"

namespace avmplus
{
	XMLClass::XMLClass(VTable* cvtable)
		: ClassClosure(cvtable)
	{
		AvmAssert(traits()->getSizeOfInstance() == sizeof(XMLClass));

		AvmCore* core = this->core();

		createVanillaPrototype();

		// These are static objects on the XML type
		// E4X: The XML constructor has the following properties
		// XML.ignoreComments
		// XML.ignoreProcessingInstructions
		// XML.ignoreWhitespace
		// XML.prettyPrinting
		// XML.prettyIndent
		m_flags = kFlagIgnoreComments | kFlagIgnoreProcessingInstructions | kFlagIgnoreWhitespace | kFlagPrettyPrinting;
		m_prettyIndent = 2;

		kAttribute = core->internConstantStringLatin1("attribute");
		kComment = core->internConstantStringLatin1("comment");
		kProcessingInstruction = core->internConstantStringLatin1("processing-instruction");
		kElement = core->internConstantStringLatin1("element");
		kText = core->internConstantStringLatin1("text");

		kColon = core->internConstantStringLatin1(":");
		kXml = core->internConstantStringLatin1("xml");

		// for notifications
		kAttrAdded = core->internConstantStringLatin1("attributeAdded");
		kAttrRemoved = core->internConstantStringLatin1("attributeRemoved");
		kAttrChanged = core->internConstantStringLatin1("attributeChanged");
		kNodeAdded = core->internConstantStringLatin1("nodeAdded");
		kNodeRemoved = core->internConstantStringLatin1("nodeRemoved");
		kNodeChanged = core->internConstantStringLatin1("nodeChanged");
		kNamespaceAdded = core->internConstantStringLatin1("namespaceAdded");
		kNamespaceRemoved = core->internConstantStringLatin1("namespaceRemoved");
		kNamespaceSet = core->internConstantStringLatin1("namespaceSet");
		kNameSet = core->internConstantStringLatin1("nameSet");
		kTextSet = core->internConstantStringLatin1("textSet");

		// XML.settings
		// XML.setSettings ([settings])
		// XML.defaultSettings()
	}

	XMLClass::~XMLClass()
	{
		m_prettyIndent = 0;
		m_flags = 0;
	}

	// E4X 13.4.2, page 70
	// this = argv[0] (ignored)
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom XMLClass::construct(int argc, Atom* argv)
	{
		// We are no longer supporting this weird Rhino behavior.  According to the spec
		// and a discussion with the E4X developers, Rhino is buggy and a no argument
		// constructor should be equivalent to the empty string constructor.
		// !!@ This is different then the spec but runtime behavior of Rhino shows
		// that a "new XML()" call creates some sort of special node that can change 
		// type automatically.
		//var x = new XML();
		//print(x); // prints nothing
		//print(x.nodeKind()); // prints text
		//print(x.children()); // prints nothing
		//x.foo = 5;
		//print(x); // prints 5
		//print(x.nodeKind()); // prints element - how did it switch?
		//print(x.attributes()); // prints nothing
		//print(x.children()); // prints 5

		AvmCore* core = this->core();

		if (!argc || AvmCore::isNullOrUndefined(argv[1]))
		{
			return ToXML (core->kEmptyString->atom());
		}

		Atom x = ToXML (argv[1]);
		// if args[0] is xml, xmllist or w3c xml, return a deep copy
		if (AvmCore::isXML(argv[1]) || AvmCore::isXMLList(argv[1]))
		{
			// return deepCopy of x
			XMLObject *x2 = AvmCore::atomToXMLObject(x);
			return x2->_deepCopy()->atom();
		}

		return x;
	}
	
	// E4X 13.4.1, page 70
	// this = argv[0] (ignored)
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom XMLClass::call(int argc, Atom* argv)
	{
		if ((!argc) || AvmCore::isNullOrUndefined(argv[1]))
		{
			return ToXML (core()->kEmptyString->atom());
		}

		return ToXML(argv[1]);
    }

	// E4X 10.3, page 32
	Atom XMLClass::ToXML(Atom arg)
	{
		Toplevel* toplevel = this->toplevel();
		AvmCore* core = this->core();

		if (AvmCore::isNullOrUndefined(arg))
		{
			toplevel->throwTypeError(
					   (arg == undefinedAtom) ? kConvertUndefinedToObjectError :
											kConvertNullToObjectError);
			return arg;
		}
		else if (AvmCore::isXML(arg))
		{
			return arg;
		}
		else if (AvmCore::isXMLList(arg))
		{
			XMLListObject *xl = AvmCore::atomToXMLList(arg);
			if (xl->_length() == 1)
			{
				return xl->_getAt(0)->atom();
			}
			else
			{
				toplevel->throwTypeError(kXMLMarkupMustBeWellFormed);
				return 0;//notreached
			}
		}
		else
		{
			Namespace *defaultNamespace = toplevel->getDefaultNamespace();

			// 2. Parse parentString as a W3C element information info e
			// 3. If the parse fails, throw a SyntaxError exception
			XMLObject *x = new (core->GetGC()) XMLObject(toplevel->xmlClass(), core->string(arg), defaultNamespace);

			// 4. x = toXML(e);
			// 5. if x.length == 0
			//       return new xml object
			if (!x->getNode()->_length())
			{
				x->setNode( new (core->GetGC()) TextE4XNode(0, core->kEmptyString) );
			}
			// 6. else if x.length == 1
			//       x[0].parent = null
			//		return x[0]
			else if (x->getNode()->_length() == 1)
			{
				x->setNode( x->getNode()->_getAt (0)); // discard parent node
				x->getNode()->setParent (0);
			}
			// 7. else throw a syntaxError
			else
			{
				// check for multiple nodes where the first n-1 are PI/comment nodes and the 
				// last one is an element node.  Just ignore the PI/comment nodes and return
				// the element node.  (bug 148526).
				// Will also now ignore any text nodes that just contain whitespace (leading
				// or trailing) the one valid element node.  If multiple element nodes are found,
				// that is a failing case as well. (bug 192355)
				E4XNode *node = x->getNode();
				E4XNode *validNode = NULL;

				for (uint32 i = 0; i < node->_length(); i++)
				{
					E4XNode *n = node->_getAt (i);
					if (n->getClass() == E4XNode::kElement)
					{
						if (validNode != NULL)
							toplevel->throwTypeError(kXMLMarkupMustBeWellFormed);

						validNode = n;
					}
					else if (n->getClass() == E4XNode::kText)
					{
						if (!n->getValue()->isWhitespace())
						{
							toplevel->throwTypeError(kXMLMarkupMustBeWellFormed);
						}
					}
				}

				// No valid nodes found
				if (!validNode)
					toplevel->throwTypeError(kXMLMarkupMustBeWellFormed);

				x->setNode( validNode ); // discard parent node
				validNode->setParent (0);
			}
			return x->atom();
		}
	}

	void XMLClass::set_ignoreComments(uint32 ignoreFlag) 
	{ 
		if (ignoreFlag)
			m_flags |= kFlagIgnoreComments; 
		else
			m_flags &= ~kFlagIgnoreComments; 
	}

	uint32 XMLClass::get_ignoreComments() 
	{ 
		return ((m_flags & kFlagIgnoreComments) != 0); 
	}

	void XMLClass::set_ignoreProcessingInstructions(uint32 ignoreFlag)
	{ 
		if (ignoreFlag)
			m_flags |= kFlagIgnoreProcessingInstructions; 
		else
			m_flags &= ~kFlagIgnoreProcessingInstructions; 
	}

	uint32 XMLClass::get_ignoreProcessingInstructions() 
	{ 
		return ((m_flags & kFlagIgnoreProcessingInstructions) != 0); 
	}

	void XMLClass::set_ignoreWhitespace(uint32 ignoreFlag)
	{ 
		if (ignoreFlag)
			m_flags |= kFlagIgnoreWhitespace; 
		else
			m_flags &= ~kFlagIgnoreWhitespace; 
	}
	
	uint32 XMLClass::get_ignoreWhitespace()
	{ 
		return ((m_flags & kFlagIgnoreWhitespace) != 0); 
	}

	void XMLClass::set_prettyPrinting(uint32 prettyFlag)
	{
		if (prettyFlag)
			m_flags |= kFlagPrettyPrinting; 
		else
			m_flags &= ~kFlagPrettyPrinting; 
	}

	uint32 XMLClass::get_prettyPrinting()
	{
		return ((m_flags & kFlagPrettyPrinting) != 0); 
	}

	void XMLClass::set_prettyIndent(int printVal)
	{
		m_prettyIndent = printVal;
	}

	int XMLClass::get_prettyIndent()
	{
		return m_prettyIndent;
	}

	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////

	QNameClass::QNameClass(VTable* cvtable)
		: ClassClosure(cvtable)
	{
		AvmAssert(traits()->getSizeOfInstance() == sizeof(QNameClass));

		createVanillaPrototype();

		AvmCore* core = this->core();
		kUri = core->internConstantStringLatin1("uri")->atom();
		kLocalName = core->internConstantStringLatin1("localName")->atom();
	}

	// E4X 13.3.1, page 66
	// this = argv[0] (ignored)
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom QNameClass::call(int argc, Atom* argv)
	{
		if (argc == 1)
		{
			AvmCore* core = this->core();
			if (core->isObject(argv[1]) && AvmCore::istype(argv[1], core->traits.qName_itraits))
				return argv[1];
		}

		return construct (argc, argv);
	}

	// E4X 13.3.2, page 67
	Atom QNameClass::construct(int argc, Atom* argv)
	{
		AvmCore* core = this->core();

		if (argc == 0)
			return (new (core->GetGC(), ivtable()->getExtraSize()) QNameObject(this, undefinedAtom))->atom();

		if (argc == 1)
		{
			if (core->isObject(argv[1]) && AvmCore::istype(argv[1], core->traits.qName_itraits))
				return argv[1];

			return (new (core->GetGC(), ivtable()->getExtraSize()) QNameObject(this, argv[1]))->atom();
		}
		else
		{
			Atom a = argv[1];
			if (a == undefinedAtom)
			{
				// ns undefined same as unspecified
				return (new (core->GetGC(), ivtable()->getExtraSize()) QNameObject(this, argv[2]))->atom();
			}
			else
			{
				Namespace* ns;
				if (AvmCore::isNull(a))
					ns = NULL;
				// It's important to preserve the incoming namespace because it's type
				// may not be public.  I.E...
				// namespace ns;
				// q = new QName(ns, "name"); // ns is a NS_PackageInternal ns
				// If we ever use this QName as a multiname, we need to preserve the exact ns
				else if (core->isNamespace(a))
					ns = core->atomToNamespace(a);				
				else
					ns = core->newNamespace (a);
				return (new (core->GetGC(), ivtable()->getExtraSize()) QNameObject(this, ns, argv[2]))->atom();
			}
		}
	}
}
