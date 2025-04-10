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

/////////////////////////////////////////////////////////
// Internal properties of the E4XNode classes 
//		Multiname *m_name;
//		Stringp m_value;		
//		E4XNode *m_parent; // the parent or NULL for top item
//		AtomArray *m_attributes;
//		AtomArray *m_namespaces;
//		AtomArray *m_children;
//
//		kAttribute (AttributeE4XNode)
//			m_name = Multiname containing namespace:name pair (marked as an attribute)
//			m_value = text value of the attribute
//		kText/kCDATA (TextE4XNode, CDATAE4XNode)
//			m_value - text value of the node
//		kComment (CommentE4XNode)
//			m_value - text value of the node
//		kProcessingInstruction (PIE4XNode)
//			m_name = Multiname containing namespace:name pair
//			m_value - text value of the node
//		kElement (ElementE4XNode)
//			m_name = Multiname containing namespace:name pair
//			m_attributes : list of attributes (E4XNodes's)
//			m_children : array of children nodes (E4XNodes's) or
//			m_namespaces: array of namespaces for this node
//
//	QName contains a Multiname with only ONE namespace
//     null
//     "" empty string
//     uri
//
//  Properties of the XML object can be either qualified (one associated namespace)
//  or unqualified.
//
// Property access to the XML object can be a variety of cases:
//   qualified: one namespace
//   unqualified: one or more namespaces (the public namespace, plus others)
//   anyName operator - matches both qualified and unqualified properties
#include "avmplus.h"
#include "BuiltinNatives.h"

//#define STRING_DEBUG

namespace avmplus
{
  XMLObject::~XMLObject(){}
  
	XMLObject::XMLObject(XMLClass *type, E4XNode *node)
		: ScriptObject(type->ivtable(), type->prototype), m_node(node)
	{
		SAMPLE_FRAME("XML", this->core());
		this->publicNS = core()->findPublicNamespace();
	}

	// This is considered the "toXML function"
	XMLObject::XMLObject(XMLClass *type, Stringp str, Namespace *defaultNamespace)
		: ScriptObject(type->ivtable(), type->prototype)
	{
		SAMPLE_FRAME("XML", this->core());
		#if 0//def _DEBUG
		// *** NOTE ON THREAD SAFETY ***
		//
		// Enabling this code means that there may be a race to initialize 'once' on different
		// threads, or, alternatively, that only one core gets to run this code, not each core
		// individually.  This may or may not be OK, but needs to be considered before enabling
		// the code.
		static bool once = false;
		if (!once)
		{
			once = true;
			AvmDebugMsg(false, "sizeof(E4XNode): %d\r\n", sizeof(E4XNode));
			AvmDebugMsg(false, "sizeof(TextE4XNode): %d\r\n", sizeof(TextE4XNode));
			AvmDebugMsg(false, "sizeof(ElementE4XNode): %d\r\n", sizeof(ElementE4XNode));
			AvmDebugMsg(false, "sizeof(E4XNodeAux): %d\r\n", sizeof(E4XNodeAux));
		}
		#endif
		if (!str)
			return;

		AvmCore *core = this->core();
		Toplevel* toplevel = this->toplevel();
		MMgc::GC *gc = core->GetGC();
		this->publicNS = core->findPublicNamespace();

		AvmAssert(traits()->getSizeOfInstance() == sizeof(XMLObject));
		AvmAssert(traits()->getExtraSize() == 0);

		// str, ignoreWhite
		bool bIgnoreWhite = toplevel->xmlClass()->get_ignoreWhitespace() != 0;
		XMLParser parser(core, str);
		parser.parse(bIgnoreWhite);
		parser.setCondenseWhite(true);

		XMLTag tag(gc);
		E4XNode* p = 0;

		// When we're passed in a defaultNamespace, we simulate the following XML code
		// <parent xmlns=defaultNamespace's URI>string</parent>
		if (defaultNamespace)
		{
			setNode( new (gc) ElementE4XNode (0) );

			// create a namespace for the parent using defaultNamespace->URI()
			Namespace *ns = core->internNamespace (core->newNamespace (core->kEmptyString->atom(), defaultNamespace->getURI()->atom()));

			m_node->_addInScopeNamespace (core, ns, publicNS);

			Stringp name = core->internConstantStringLatin1("parent");

			m_node->setQName (core, name, ns);

			p = m_node;
		}

		int m_status;

		while ((m_status = parser.getNext(tag)) == XMLParser::kNoError)
		{

			E4XNode* pNewElement = NULL;

			switch (tag.nodeType)
			{
			case XMLTag::kXMLDeclaration:
				{
					// !!@ add some checks to ensure this is the first tag
					// encountered in our file (deal with <parent> stuff from
					// XMLObject and XMLListObject parser setup
				}
				break;
			case XMLTag::kDocTypeDeclaration:
				break;
			case XMLTag::kElementType:
				{
					// A closing tag
					if (tag.text->charAt(0) == '/')
					{
						const int32_t nodeNameStart = 1; // skip the slash

						Multiname m;
						p->getQName(&m, publicNS);
						Namespace* ns = m.getNamespace();

						// Get our parent's qualified name string here
						Stringp parentName = m.getName();

						if (!NodeNameEquals(tag.text, nodeNameStart, parentName, ns) &&
							// We're trying to support paired nodes where the first node gets a namespace
							// from the default namespace.
							parentName->Compare(*tag.text, nodeNameStart, tag.text->length()-nodeNameStart) != 0 && 
							ns->getURI() == toplevel->getDefaultNamespace()->getURI())
						{
							// If p == m_node, we are at the top of our tree and we're parsing the fake "parent"
							// wrapper tags around our actual XML text.  Instead of warning about a missing "</parent>"
							// tag, we instead complain about the XML markup not being well-formed.
							// (Emulating Rhino behavior)
							if (p == m_node)
								toplevel->throwTypeError(kXMLMarkupMustBeWellFormed);
							else
								toplevel->throwTypeError(kXMLUnterminatedElementTag, parentName, parentName);
						}
						else
						{
							// Catch the case where our input string ends with a bogus <parent> tag
							if (defaultNamespace && (p == m_node))
								toplevel->throwTypeError(kXMLMarkupMustBeWellFormed);

							// found matching closing tag so we can pop back up a level now
							if (p != m_node)
								p = p->getParent();
						}

					}
					else // an opening tag
					{
						ElementE4XNode *e = new (gc) ElementE4XNode(0);
						pNewElement = e;
						// Our first tag modifies this object itself
						if (!m_node)
						{
							setNode(pNewElement);
						}
						else // all other tags create a new element tag
						{
							p->_append(pNewElement);
						}

						if (!tag.empty) // if our tag is not empty, we're now the "parent" tag
						{
							p = pNewElement;
						}

						// Needs to happen after setting m_name->name so throw error can use name in routine
						e->CopyAttributesAndNamespaces(core, toplevel, tag, publicNS);

						// Find a namespace that matches this tag in our parent chain.  If this name
						// is a qualified name (ns:name), we search for a namespace with a matching
						// prefix.  If is an unqualified name, we find the first empty prefix name.
						Namespace *ns = pNewElement->FindNamespace(core, toplevel, tag.text, false);

						// pg 35, map [[name]].uri to "namespace name" of node

						if (!ns) {
							// NOTE use caller's public
							ns = core->findPublicNamespace();
						}

						pNewElement->setQName(core, tag.text, ns);
					}
				}
				break;

			case XMLTag::kComment:
				if (!toplevel->xmlClass()->get_ignoreComments()) 
				{
					pNewElement = new (gc) CommentE4XNode (0, tag.text);
					if (!m_node)
						setNode( pNewElement );
				}
				break;
			case XMLTag::kCDataSection:

				pNewElement = new (gc) CDATAE4XNode (0, tag.text);
				if (!m_node)
					setNode( pNewElement );
				break;
			case XMLTag::kTextNodeType:
				// For small strings, we intern them in an attempt to save memory
				// with large XML files with of lot of repeating text nodes.
				if (tag.text->length() < 32)
				{
					Stringp text = core->internString(tag.text);
					// Reduce our GC pressure if we know our tag.text is unused.
					if (text != tag.text)
					{
						AvmAssert(!tag.text->isInterned());
						tag.text = NULL;
					}
					pNewElement = new (gc) TextE4XNode(0, text);
				}
				else
				{
					pNewElement = new (gc) TextE4XNode(0, tag.text);
				}

				if (!m_node)
					setNode( pNewElement );
				break;
			case XMLTag::kProcessingInstruction:
				if (!toplevel->xmlClass()->get_ignoreProcessingInstructions()) 
				{
					Stringp name, val;
					int32_t space = tag.text->indexOfLatin1(" ", 1, 0);
					if (space < 0)
					{
						// no spaces, no value
						name = tag.text;
						val = core->kEmptyString;
					}
					else
					{
						name = tag.text->substring(0, space);
						while (String::isSpace((wchar) tag.text->charAt(++space))) {}
						val  = tag.text->substring(space, tag.text->length());
					}
					pNewElement = new (gc) PIE4XNode(0, val); 
					// NOTE use caller's public
					pNewElement->setQName (core, name, core->findPublicNamespace());
					if (!m_node)
						setNode( pNewElement );
				}
				break;

			//kNoType             = 0,
			default:
				AvmAssert(0); // unknown tag type??
			}
			
			if ( pNewElement && (XMLTag::kElementType != tag.nodeType))
			{
				if (pNewElement != m_node)
					p->_append( pNewElement);
			}

			if ( m_status != XMLParser::kNoError )
			{
				break; // stop getting tags
			}

		}

		if ( m_status == XMLParser::kEndOfDocument )
		{
			m_status = XMLParser::kNoError;
		}
		else
		{
			switch (m_status)
			{
			case XMLParser::kMalformedElement:
				toplevel->throwTypeError(kXMLMalformedElement);
				break;
			case XMLParser::kUnterminatedCDataSection:
				toplevel->throwTypeError(kXMLUnterminatedCData);
				break;
			case XMLParser::kUnterminatedXMLDeclaration:
				toplevel->throwTypeError(kXMLUnterminatedXMLDecl);
				break;
			case XMLParser::kUnterminatedDocTypeDeclaration:
				toplevel->throwTypeError(kXMLUnterminatedDocTypeDecl);
				break;
			case XMLParser::kUnterminatedComment:
				toplevel->throwTypeError(kXMLUnterminatedComment);
				break;
			case XMLParser::kUnterminatedAttributeValue:
				toplevel->throwTypeError(kXMLUnterminatedAttribute);
				break;
			case XMLParser::kUnterminatedElement:
				toplevel->throwTypeError(kXMLUnterminatedElement);
				break;
			case XMLParser::kUnterminatedProcessingInstruction:
				toplevel->throwTypeError(kXMLUnterminatedProcessingInstruction);
				break;
			case XMLParser::kOutOfMemory:
			case XMLParser::kElementNeverBegun:
				AvmAssert(0);
				break;
			}
		}

		if ( p != m_node && ! m_status )
		{
			Multiname m;
			p->getQName(&m, publicNS);

			// Get our parents qualified name string here
			Stringp parentName = m.getName();

			toplevel->throwTypeError(kXMLUnterminatedElementTag, parentName, parentName);
		}

	}

	bool XMLObject::NodeNameEquals(Stringp nodeName, int32_t nodeNameStart, Stringp parentName, Namespace * parentNs)
	{
		int32_t const nodeNameLength = nodeName->length() - nodeNameStart;
		if (parentNs && parentNs->hasPrefix())
		{
			AvmCore *core = this->core();
			Stringp parentNSName = core->string(parentNs->getPrefix());
			int prefixLen = parentNSName->length();

			// Does nodeName == parentNS:parentName
			int totalLen = prefixLen + 1 + parentName->length(); // + 1 for ':' separator
			if (totalLen != nodeNameLength)
				return false;

			if (parentNSName->Compare(*nodeName, nodeNameStart, prefixLen) != 0)
				return false;

			if (nodeName->charAt(nodeNameStart + prefixLen) != ':')
				return false;

			// -1 for ':'
			prefixLen++;
			return (parentName->Compare(*nodeName, nodeNameStart + prefixLen, nodeNameLength - prefixLen) == 0); 
		}
		else
		{
			return parentName->Compare(*nodeName, nodeNameStart, nodeNameLength) == 0; 
		}
	}

	//////////////////////////////////////////////////////////////////////
	// E4X Section 9.1.1
	//////////////////////////////////////////////////////////////////////

	// sec 11.2.2.1 CallMethod
	// this = argv[0] (ignored)
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom XMLObject::callProperty(const Multiname* multiname, int argc, Atom* argv)
	{
		AvmCore *core = this->core();

		Atom f = getDelegate()->getMultinameProperty(multiname);
		if (f == undefinedAtom)
		{
			f = getMultinameProperty(multiname);
			// If our method returned is a 0 element XMLList, it means that we did not
			// find a matching property for this method name.  In this case, if our XML
			// node is simple, we convert it to a string and callproperty on the string.
			// This allows node elements to be treated as simple strings even if they
			// are XML or XMLList objects.  See 11.2.2.1 in the E4X spec for CallMethod.
			if (AvmCore::isXMLList(f) && 
				!AvmCore::atomToXMLList(f)->_length() &&
				(hasSimpleContent()))
			{
				Stringp r0 = core->string (this->atom());
				return toplevel()->callproperty (r0->atom(), multiname, argc, argv, toplevel()->stringClass->vtable);
			}
		}
		argv[0] = atom(); // replace receiver
		return toplevel()->op_call(f, argc, argv);
	}

	// E4X 9.1.1.1, pg 12 - [[GET]]
	Atom XMLObject::getAtomProperty(Atom P) const
	{
		Multiname m;
		toplevel()->ToXMLName(P, m);
		return getMultinameProperty(&m);
	}

	// E4X 9.1.1.1, pg 12 - [[GET]]
	Atom XMLObject::getMultinameProperty(const Multiname* name_in) const
	{
		AvmCore *core = this->core();
		Toplevel* toplevel = this->toplevel();

		Multiname name;
		toplevel->CoerceE4XMultiname(name_in, name);

#ifdef STRING_DEBUG
		Stringp n1 = name.getName();
#endif

		if (!name.isAnyName() && !name.isAttr())
		{
			// We have an integer argument - direct child lookup
			Stringp nameString = name.getName();
			uint32 index;
			if (AvmCore::getIndexFromString (nameString, &index))
			{
				//	//l = ToXMLList (this);
				//	//return l->get(p);
				// ToXMLList on a XMLNode just creates a one item XMLList.  The only valid
				// property number for the new XMLList is 0 which just returns this node.  Handle
				// that case here.
				if (index == 0)
					return this->atom();
				else
					return undefinedAtom;
			}
		}

		XMLListObject *xl = new (core->GetGC()) XMLListObject(toplevel->xmlListClass(), this->atom(), &name);


		if (name.isAttr())
		{
			// does not hurt, but makes things faster
			xl->checkCapacity(m_node->numAttributes());
			// for each a in x.[[attributes]]
			for (uint32 i = 0; i < m_node->numAttributes(); i++)
			{
				E4XNode *xml = m_node->getAttribute(i);

				AvmAssert(xml && xml->getClass() == E4XNode::kAttribute);

				Multiname m;
				AvmAssert(xml->getQName(&m, publicNS) != 0);

				//if (((n.[[Name]].localName == "*") || (n.[[Name]].localName == a.[[Name]].localName)) &&
				//	((n.[[Name]].uri == nulll) || (n.[[Name]].uri == a.[[Name]].uri)))
				//	l.append (a);

				xml->getQName(&m, publicNS);
				if (name.matches(&m))
				{
					xl->_appendNode (xml);
				}
			}

			return xl->atom();
		}
		// step 5 - look through all the children for a match - [[length]] implies length of children
		// n isn't an attributeName so it must be a qname??
//		for k = 0 to x.[[length]]-1
//		if (n.localName = "*" and this[k].class == "element" and (this[k].name.localName == n.localName)
//			and (!n.uri) or (this[k].class == "element) and (n.uri == this[k].name.uri)))
//			xl->_append (x[k]);

		if (name.isAnyName())
			xl->checkCapacity(m_node->numChildren());

		for (uint32 i = 0; i < m_node->numChildren(); i++)
		{
			E4XNode *child = m_node->_getAt(i);
			Multiname m;
			Multiname *m2 = 0;
			if (child->getClass() == E4XNode::kElement)
			{
				child->getQName(&m, publicNS);
				m2 = &m;
			}

			//	if (n.localName = "*" OR this[k].class == "element" and (this[k].name.localName == n.localName)
			//	and (!n.uri) or (this[k].class == "element) and (n.uri == this[k].name.uri)))
			//		xl->_append (x[k]);
			if (name.matches(m2))
			{
				xl->_appendNode (child);
			}
		}

		return xl->atom();
	}

	void XMLObject::setMultinameProperty(const Multiname* name_in, Atom V)
	{
		AvmCore *core = this->core();
		Toplevel* toplevel = this->toplevel();

		Multiname m;
		toplevel->CoerceE4XMultiname(name_in, m);

		// step 3
		if (!m.isAnyName() && !m.isAttr())
		{
			Stringp name = m.getName();
			uint32 index;
			if (AvmCore::getIndexFromString (name, &index))
			{
				// Spec says: NOTE: this operation is reserved for future versions of E4X
				toplevel->throwTypeError(kXMLAssignmentToIndexedXMLNotAllowed);
			}
		}

		// step 4
		if (getClass() & (E4XNode::kText | E4XNode::kCDATA | E4XNode::kComment | E4XNode::kProcessingInstruction | E4XNode::kAttribute))
			return; 

		Atom c;
		if (AvmCore::atomToXMLList(V))
		{
			XMLListObject *src = AvmCore::atomToXMLList(V);
			if ((src->_length() == 1) && src->_getAt(0)->getClass() & (E4XNode::kText | E4XNode::kAttribute))
            {
                c = core->string(V)->atom();
            }
			else
			{
				c = src->_deepCopy()->atom();									
			}
		}
		else if (AvmCore::atomToXML(V))
		{
			XMLObject *x = AvmCore::atomToXMLObject(V);
			if (x->getClass() & (E4XNode::kText | E4XNode::kAttribute))
			{
				// This string is converted into a XML object below in step 2(g)(iii)
				c = core->string(V)->atom();
			}
			else
			{
				c = x->_deepCopy()->atom();									
			}
		}
		else
		{
#ifdef STRING_DEBUG
			String *foo = core->string(V);
#endif // STRING_DEBUG
			c = core->string(V)->atom();
		}


		// step 5
		//Atom n = core->ToXMLName (P);
		// step 6
		//Atom defaultNamespace = core->getDefaultNamespace()->atom();

		// step 7
		if (m.isAttr())
		{
			// step 7b
			Stringp sc;
			if (AvmCore::isXMLList(c))
			{
				XMLListObject *xl = AvmCore::atomToXMLList(c);
				if (!xl->_length())
				{
					sc = core->kEmptyString;
				}
				else
				{
					StringBuffer output (core);
					output << core->string (xl->_getAt (0)->atom());
					for (uint32 i = 1; i < xl->_length(); i++)
					{
						output << " " << core->string (xl->_getAt (i)->atom());
					}

					sc = core->newStringUTF8(output.c_str());
				}
			}
			else // step 7c
			{
				sc = core->string (c);
			}

			// step 7d
			int a = -1; // -1 is null in spec
			// step 7e
			for (uint32 j = 0; j < this->m_node->numAttributes(); j++)
			{
				E4XNode *x = m_node->getAttribute(j);
				Multiname m2;
				x->getQName(&m2, publicNS);
				if (m.matches(&m2))
				{
					if (a == -1)
					{
						a = j;
					}
					else
					{
						this->deleteMultinameProperty(&m2);
						// notification occurrs in deleteproperty
					}
				}
			}

            Stringp name = !m.isAnyName() ? m.getName() : NULL;
            Atom nameAtom = name ? name->atom() : nullStringAtom;
			if (a == -1) // step 7f
			{
				E4XNode *e = new (core->GetGC()) AttributeE4XNode(this->m_node, sc);
				Namespace *ns = 0;
				if (m.namespaceCount() == 1)
					ns = m.getNamespace();
				e->setQName(core, name, ns);

				this->m_node->addAttribute (e);
				
				e->_addInScopeNamespace(core, ns, publicNS);

				nonChildChanges(xmlClass()->kAttrAdded, nameAtom, sc->atom());
			}
			else // step 7g
			{
				E4XNode *x = m_node->getAttribute(a);
				Stringp prior = x->getValue();
				x->setValue (sc);

				nonChildChanges(xmlClass()->kAttrChanged, nameAtom, (prior) ? prior->atom() : undefinedAtom);
			}

			// step 7h
			return;
		}

		if (!m.isAnyName())
		{
			// step 8
			bool isValidName = core->isXMLName(m.getName()->atom());

			// step 9
			if (!isValidName)
				return;
		}

		// step 10
		int32 i = -1; // -1 is undefined in spec
		bool primitiveAssign = ((!AvmCore::isXML(c) && !AvmCore::isXMLList(c)) && (!m.isAnyName()));

		// step 12
		bool notify = notifyNeeded(getNode());
		for (int k = _length() - 1; k >= 0; k--)
		{
			E4XNode *x = m_node->_getAt(k);
			Multiname mx;
			Multiname *m2 = 0;
				
			if (x->getClass() == E4XNode::kElement)
			{
				x->getQName(&mx, publicNS);
				m2 = &mx;
			}

			if (m.matches(m2))
			{
				// remove n-1 nodes of n matching
				if (i != -1)
				{
					E4XNode* was = m_node->_getAt(i);

					m_node->_deleteByIndex (i);

					// notify 
					if (notify && (was->getClass() == E4XNode::kElement))
					{
						XMLObject* nd = new (core->GetGC())  XMLObject (toplevel->xmlClass(), was);
						childChanges(xmlClass()->kNodeRemoved, nd->atom());
					}
				}

				i = k;
			}
		}

		// step 13
		if (i == -1)
		{
			i = _length();
			if (primitiveAssign)
			{
				E4XNode *e = new (core->GetGC()) ElementE4XNode (m_node);
				// We use m->namespaceCount here to choose to use the default xml namespace
				// name here for an unqualified prop access. For a qualified access,
				// there will be only one namespace
				Stringp name = m.getName();
				Namespace *ns;
				if (m.namespaceCount() == 1)
					ns = m.getNamespace();
				else
					ns = toplevel->getDefaultNamespace();
				e->setQName (core, name, ns);
				
				XMLObject *y = new (core->GetGC())  XMLObject (toplevel->xmlClass(), e);

				m_node->_replace (core, toplevel, i, y->atom());
				e->_addInScopeNamespace (core, ns, publicNS);
			}
		}

		// step 14
		if (primitiveAssign)
		{
			E4XNode *xi = m_node->_getAt(i);

			// children are being removed notify parent if necc.
			bool notify = notifyNeeded(xi);
			XMLObject* target = (notify) ? new (core->GetGC()) XMLObject(xmlClass(), xi) : 0;

			int count = xi->numChildren();
			for(int r=0;notify && (r<count); r++)
			{
				E4XNode* ild = xi->_getAt(r);
				if (ild->getClass() == E4XNode::kElement)
				{
					XMLObject* nd = new (core->GetGC())  XMLObject (toplevel->xmlClass(), ild);
					target->childChanges(xmlClass()->kNodeRemoved, nd->atom());
				}
			}

			// remember node if there was one...
			Atom prior = undefinedAtom;
			if (notify && count > 0) 
			{
				XMLObject* nd = new (core->GetGC())  XMLObject (toplevel->xmlClass(), xi->_getAt(0));
				prior = nd->atom();
			}

			// step 14a - delete all properties of x[i]
			xi->clearChildren();

			Stringp s = core->string (c);
			if (s->length())
			{
				xi->_replace (core, toplevel, i, c, prior);
			}
		}
		else
		{
			E4XNode* prior = m_node->_replace (core, toplevel, i, c);

			if (notifyNeeded(getNode()))
			{
				// The above _replace call may be used to insert new nodes at the end.  However, if a null is inserted
				// the effect is as though nothing was inserted.  Test for this case.
				if (m_node->_length() > (uint32)i)
				{
					XMLObject* xml = new (core->GetGC()) XMLObject(xmlClass(), m_node->_getAt(i));
					childChanges( (prior) ? xmlClass()->kNodeChanged : xmlClass()->kNodeAdded, xml->atom(), prior);
				}
			}
		}
		return;
	}

	bool XMLObject::deleteMultinameProperty(const Multiname* name_in)
	{
		AvmCore *core = this->core();

		Multiname m;
		toplevel()->CoerceE4XMultiname(name_in, m);

		// step 1
		if (!m.isAnyName() && !m.isAttr())
		{
			Stringp name = m.getName();
			uint32 index;
			if (AvmCore::getIndexFromString (name, &index))
			{
				// Spec says: NOTE: this operation is reserved for future versions of E4X
				// In Rhino, this silently fails
				return true;
			}
		}

		if (m.isAttr())
		{
			uint32 j = 0;
			while (j < m_node->numAttributes())
			{
				E4XNode *x = m_node->getAttribute(j);
				Multiname m2;
				x->getQName(&m2, publicNS);
				if (m.matches(&m2))
				{
					x->setParent(NULL);

					// remove the attribute from m_attributes
					m_node->getAttributes()->removeAt (j);

					Multiname previous;
					x->getQName(&previous, publicNS);
					Stringp name = previous.getName();
					Stringp val = x->getValue();
					nonChildChanges(xmlClass()->kAttrRemoved, (name) ? name->atom() : undefinedAtom, (val) ? val->atom() : undefinedAtom);
				}
				else
				{
					j++;
				}
			}

			return true;
		}

		bool notify = notifyNeeded(m_node);
		uint32 q = 0;
		while (q < _length())
		{
			E4XNode *x = m_node->_getAt(q);
			Multiname mx;
			Multiname *m2 = 0;
			bool isElem = x->getClass() == (E4XNode::kElement) ? true : false;
			if (isElem)
			{
				x->getQName(&mx, publicNS);
				m2 = &mx;
			}

			if (m.matches(m2))
			{
				x->setParent (NULL);
				m_node->_deleteByIndex (q);

				if (notify && isElem)
				{
					XMLObject *r = new (core->GetGC())  XMLObject (xmlClass(), x);
					childChanges(xmlClass()->kNodeRemoved, r->atom());
				}
			}
			else
			{
				q++;
				//	if (dp > 0)
					// rename property (q) to (q-dp)
					// this automatically gets taken care of by deleteByIndex
			}
		}
		// x.length = x.length - dp 
		// this is handled b _deleteByIndex logic

		return true;
	}

	Atom XMLObject::getDescendants(const Multiname* name_in) const
	{
		AvmCore *core = this->core();
		Toplevel* toplevel = this->toplevel();

		core->stackCheck(toplevel);

		Multiname m;
		toplevel->CoerceE4XMultiname(name_in, m);

		XMLListObject *l = new (core->GetGC()) XMLListObject(toplevel->xmlListClass()); 

		if (m.isAttr())
		{
			for (uint32 i = 0; i < m_node->numAttributes(); i++)
			{
				E4XNode *ax = m_node->getAttribute(i);
				Multiname m2;
				AvmAssert(ax->getQName(&m2, publicNS));
				ax->getQName(&m2, publicNS);

				if (m.matches(&m2))
				{
					// for each atribute, if it's name equals m,
					l->_appendNode (ax);
				}
			}
		}

		for (uint32 k = 0; k < _length(); k++)
		{
			E4XNode *child = m_node->_getAt(k);

			if (!m.isAttr())
			{
				Multiname mx;
				Multiname *m2 = 0;
				if (child->getClass() == E4XNode::kElement)
				{
					child->getQName(&mx, publicNS);
					m2 = &mx;
				}
				if (m.matches(m2))
				{
					l->_appendNode (child);
				}
			}

			XMLObject *co = new (core->GetGC()) XMLObject(toplevel->xmlClass(), child);
			Atom dq = co->getDescendants (&m); 
			::delete co;
			XMLListObject *dql = AvmCore::atomToXMLList(dq);
			if (dql && dql->_length())
			{
				l->_append (dq);
			}
		}

		return l->atom();
	}

	// E4X 9.1.1.2, pg 13 - [[PUT]]
	// E4X errata:
	// 9.1.1.2 Move steps 3 and 4 to before 1 and 2, to avoid wasted effort in
    //    ToString or [[DeepCopy]].
	void XMLObject::setAtomProperty(Atom P, Atom V)
	{
		Multiname m;
		toplevel()->ToXMLName(P, m);
		setMultinameProperty(&m, V);
	}

	Atom XMLObject::getUintProperty(uint32 index) const
	{
		if (index == 0)
			return this->atom();
		else
			return undefinedAtom;
	}

	void XMLObject::setUintProperty(uint32 /*i*/, Atom /*value*/)
	{
		// Spec says: NOTE: this operation is reserved for future versions of E4X
		toplevel()->throwTypeError(kXMLAssignmentToIndexedXMLNotAllowed);
	}

	bool XMLObject::delUintProperty(uint32 /*i*/)
	{
		// Spec says: NOTE: this operation is reserved for future versions of E4X
		// In Rhino, this silently fails
		return true;
	}

	// E4X 9.1.1.3, pg 14 - [[DELETE]]
	bool XMLObject::deleteAtomProperty(Atom P)
	{
		Multiname m;
		toplevel()->ToXMLName(P, m);
		return deleteMultinameProperty(&m);
	}

	// E4X 9.1.1.5, ??
	// [[DefaultValue]] ??

	bool XMLObject::hasUintProperty(uint32 index) const
	{
		return (index == 0);
	}

	bool XMLObject::hasMultinameProperty(const Multiname* name_in) const
	{
		Multiname m;
		toplevel()->CoerceE4XMultiname(name_in, m);

		if (!m.isAnyName() && !m.isAttr())
		{
			Stringp name = m.getName();
			uint32 index;
			if (AvmCore::getIndexFromString (name, &index))
			{
				return (index == 0);
			}
		}

		if (m.isAttr())
		{
			for (uint32 i = 0; i < m_node->numAttributes(); i++)
			{
				E4XNode *ax = m_node->getAttribute(i);
				Multiname m2;
				if (ax->getQName(&m2, publicNS) && (m.matches(&m2)))
				{
					return true;
				}
			}

			return false;
		}

		// n is a QName
		for (uint32 k = 0; k < m_node->_length(); k++)
		{
			E4XNode *child = m_node->_getAt(k);
			Multiname mx;
			Multiname *m2 = 0;
			if (child->getClass() == E4XNode::kElement)
			{
				child->getQName(&mx, publicNS);
				m2 = &mx;
			}

			if (m.matches(m2))
			{
				return true;
			}
		}

		return false;
	}

	// E4X 9.1.1.6, 16
	bool XMLObject::hasAtomProperty(Atom P) const
	{
		Multiname m;
		toplevel()->ToXMLName (P, m);
		return hasMultinameProperty(&m);
	}

	// E4X 9.1.1.7, page 16
	XMLObject *XMLObject::_deepCopy () const
	{
		AvmCore *core = this->core();

		E4XNode *e = m_node->_deepCopy (core, toplevel(), publicNS);

		XMLObject *y = new (core->GetGC()) XMLObject(xmlClass(), e);

		return y;
	}

	// E4X 9.1.1.8, page 17
	XMLListObject *XMLObject::AS3_descendants(Atom P) const
	{
		Multiname m;
		toplevel()->ToXMLName (P, m);
		return AvmCore::atomToXMLList (getDescendants (&m));
	}

	// E4X 9.1.1.10, page 18
	Atom XMLObject::_resolveValue ()
	{
		return this->atom();
	}

	Namespace *XMLObject::GenerateUniquePrefix (Namespace *ns, const AtomArray *namespaces) const
	{
		AvmCore *core = this->core();
	
		// should only be called when a namespace doesn't have a prefix
		AvmAssert (ns->getPrefix() == undefinedAtom);

		// Try to use the empty string as a first try (ISNS changes)
		uint32 i;
		for (i = 0; i < namespaces->getLength(); i++)
		{
			Namespace *ns = AvmCore::atomToNamespace (namespaces->getAt(i));
			if (ns->getPrefix() == core->kEmptyString->atom())
				break;
		}

		if (i == namespaces->getLength())
		{
			return core->newNamespace (core->kEmptyString->atom(), ns->getURI()->atom());
		}

		// Rhino seems to start searching with whatever follows "://www" or "://"
		//String *origURI = core()->string(ns->getURI());

		wchar s[4];
		s[0] = s[1] = s[2] = 'a';
		s[3] = 0;

		for (wchar x1 = 'a'; x1 <= 'z'; x1++)
		{
			s[0] = x1;
			for (wchar x2 = 'a'; x2 <= 'z'; x2++)
			{
				s[1] = x2;
				for (wchar x3 = 'a'; x3 <= 'z'; x3++)
				{
					s[2] = x3;
					bool bMatch = false;
					Atom pre = core->internStringUTF16(s, 3)->atom();
					for (uint32 i = 0; i < namespaces->getLength(); i++)
					{
						Namespace *ns = AvmCore::atomToNamespace (namespaces->getAt(i));
						if (pre == ns->getPrefix())
						{
							bMatch = true;
							break;
						}
					}

					if (!bMatch)
					{
						return core->newNamespace (pre, ns->getURI()->atom());
					}
				}
			}
		}

		return 0;
	}

	// E4X 10.2, pg 29
	void XMLObject::__toXMLString(StringBuffer &s, AtomArray *AncestorNamespaces, int indentLevel, bool includeChildren) const
	{
		AvmCore *core = this->core();

		core->stackCheck(toplevel());

		if (toplevel()->xmlClass()->okToPrettyPrint()) 
		{
			for (int i = 0; i < indentLevel; i++)
			{
				s << " ";
			}
		}
		if (this->getClass() == E4XNode::kText) // CDATA checked below
		{
			if (toplevel()->xmlClass()->okToPrettyPrint()) 
			{
				// v = removing leading and trailing whitespace from x.value
				// return escapeElementValue (v);

				s << core->EscapeElementValue(m_node->getValue(), true);
				return;
			}
			else
			{
				s << core->EscapeElementValue(m_node->getValue(), false);
				return;
			}
		}
		if (this->getClass() == E4XNode::kCDATA)
		{
			s << "<![CDATA[" << m_node->getValue() << "]]>";
			return;
		}
		if (this->getClass() == E4XNode::kAttribute)
		{
			s << core->EscapeAttributeValue (m_node->getValue()->atom());
			return;
		}
		if (this->getClass() == E4XNode::kComment)
		{
			s << "<!--";
			s << m_node->getValue();
			s << "-->";
			return;
		}

		if (this->getClass() == E4XNode::kProcessingInstruction) // step 7
		{
			s << "<?";
			Multiname m;
			AvmAssert (m_node->getQName(&m, publicNS) != 0);
			if (m_node->getQName(&m, publicNS))
			{
				s << m.getName() << " ";
			}
			s << m_node->getValue() << "?>";
			return;
		}

		// We're a little different than the spec here.  Instead of each XMLObject
		// keeping track of its entire in-scope namespace list (all the way to the
		// topmost parent), the XMLObject only knows about its own declared nodes.
		// So when were converting to a string, we need to build the inScopeNamespace
		// list here.

		AtomArray *inScopeNS = new (core->GetGC()) AtomArray();
		m_node->BuildInScopeNamespaceList (core, inScopeNS);
		uint32 origLength = AncestorNamespaces->getLength();

		// step 8 - ancestorNamespaces passed in
		// step 9/10 - add in our namespaces into ancestorNamespaces if there are no conflicts
		for (uint32 i = 0; i < inScopeNS->getLength(); i++)
		{
			Namespace *ns = AvmCore::atomToNamespace (inScopeNS->getAt(i));
			uint32 j;
			for (j = 0; j < AncestorNamespaces->getLength(); j++)
			{
				Namespace *ns2 = AvmCore::atomToNamespace (AncestorNamespaces->getAt(j));
#ifdef STRING_DEBUG
				Stringp u1 = ns->getURI();
				Stringp p1 = core->string(ns->getPrefix());
				Stringp u2 = ns2->getURI();
				Stringp p2 = core->string(ns2->getPrefix());
#endif				
				if ((ns->getURI() == ns2->getURI()) && (ns->getPrefix() == ns2->getPrefix()))
					break;
			}

			if (j == AncestorNamespaces->getLength()) // a match was not found
			{
				AncestorNamespaces->push (ns->atom());
			}
		}

		// step 11 - new ISNS changes
		// If this node's namespace has an undefined prefix, generate a new one
		Multiname m;
		AvmAssert (getNode()->getQName(&m, publicNS));
		getNode()->getQName(&m, publicNS);
		Namespace *thisNodesNamespace = GetNamespace (m, AncestorNamespaces);
		AvmAssert(thisNodesNamespace != 0);
		if (thisNodesNamespace->getPrefix() == undefinedAtom)
		{
			// find a prefix and add this namespace to our list
			thisNodesNamespace = GenerateUniquePrefix (thisNodesNamespace, AncestorNamespaces);
			AncestorNamespaces->push (thisNodesNamespace->atom());
		}

		String *nsPrefix = core->string (thisNodesNamespace->getPrefix());

		// If any of this node's attribute's namespaces have an undefined prefix, generate a new one
		for (uint32 i = 0; i < m_node->numAttributes(); i++)
		{
			E4XNode *an = m_node->getAttribute(i);
			AvmAssert(an != 0);
			AvmAssert(an->getClass() == E4XNode::kAttribute);
			Multiname nam;
			if (an->getQName(&nam, publicNS))
            {
                Namespace* ns = GetNamespace(nam, AncestorNamespaces);
                AvmAssert(ns != 0);
                if (ns->getPrefix() == undefinedAtom)
                {
                    // find a prefix and add this namespace to our list
                    ns = GenerateUniquePrefix (ns, AncestorNamespaces);

                    AncestorNamespaces->push (ns->atom());
                }
            }
		}
		// step 12
		s << "<";
		// step13 - insert namespace prefix if we have one
		if (nsPrefix != core->kEmptyString)
		{
			s << nsPrefix << ":";
		}

		// step 14
		AvmAssert (!m.isAnyName());
		s << m.getName();

		// step 15 - attrAndNamespaces = sum of x.attributes and namespaceDeclarations

		// step 16
		// for each an in attrAndNamespaces
		for (uint32 i = 0; i < m_node->numAttributes(); i++)
		{
			// step 17a
			E4XNode *an = m_node->getAttribute(i);
			AvmAssert(an != 0);
			AvmAssert(an->getClass() == E4XNode::kAttribute);
			Multiname nam;
			if (an->getQName(&nam, publicNS))
            {
                s << " ";

                // step16b-i - ans = an->getName->getNamespace(AncestorNamespace);
                AvmAssert(nam.isAttr());
                Namespace *attr_ns = GetNamespace (nam, AncestorNamespaces);

                //!!@step16b-ii - should never get hit now with revised 10.2.1 step 11.
                AvmAssert(attr_ns->getPrefix() != undefinedAtom);

                // step16b-iii
                if (attr_ns && attr_ns->hasPrefix ())
                {
                    s << core->string(attr_ns->getPrefix()) << ":";
                }
                //step16b-iv
                s << nam.getName();

                //step16c - namespace case - see below

                //step 16d
                s << "=\"";
                //step 16e
                s << core->EscapeAttributeValue(an->getValue()->atom());
                //step 16f - namespace case
                //step 16g
                s << "\"";
            }
		}

		// This adds any NS that were added to our ancestor namespace list (from origLength on up)
		for (uint32 i = origLength; i < AncestorNamespaces->getLength(); i++)
		{
			Namespace *an = AvmCore::atomToNamespace(AncestorNamespaces->getAt(i));
			if (an->getURI() != core->kEmptyString)
			{
				s << " xmlns";
				AvmAssert (an->getPrefix() != undefinedAtom);
				if (an->getPrefix() != core->kEmptyString->atom()) 
				{
					// 17c iii
					s << ":" << core->string(an->getPrefix());
				}
				// 17d
				s << "=\"";
				//step 17f - namespace case
				s << an->getURI();
				//step 17g
				s << "\"";
			}
		}

//		if (thisNodesNamespace)
//			AncestorNamespaces->push (thisNodesNamespace->atom());

		// step 18
		if (!m_node->numChildren())
		{
			s << "/>";
			return;
		}

		// step 19
		s << ">";

		// Added by mmorearty for the debugger
		if (!includeChildren)
		{
			return;
		}

		// step 20
		E4XNode *firstChild = m_node->_getAt(0);
		AvmAssert(firstChild != 0);
		bool bIndentChildren = ((_length() > 1) || (firstChild->getClass() & ~(E4XNode::kText | E4XNode::kCDATA))); 

		// step 21/22
		int nextIndentLevel = 0;
		if (toplevel()->xmlClass()->get_prettyPrinting() && bIndentChildren)
		{
			nextIndentLevel = indentLevel + toplevel()->xmlClass()->get_prettyIndent();
		}

		// We need to prune any namespaces with duplicate prefixes in our AncestorNamespace
		// array to prevent shadowing of similar namespaces.  Bug 153363.
		//	var x = <order xmlns:x="x">
		//	<item id="1" xmlns:x="x2">
		//		<menuName xmlns:x="x" x:foo='10'>burger</menuName>
		//		<price>3.95</price>
		//	</item>
		//	</order>;
		//
		// The namespace for menuName should be output even though the identical namespace
		// was output for the top node.  (Since the item node is using an incompatible 
		// namespace with the same prefix.)
		AtomArray *newNamespaceArray = new (core->GetGC()) AtomArray();
		uint32 anLen = AncestorNamespaces->getLength();
		for (uint32 i = 0; i < anLen; i++)
		{
			Namespace *first = AvmCore::atomToNamespace(AncestorNamespaces->getAt(i));
			if (i < origLength)
			{
				uint32 j;
				for (j = origLength; j < anLen; j++)
				{
					Namespace *second = AvmCore::atomToNamespace(AncestorNamespaces->getAt(j));
					if (second->getPrefix() == first->getPrefix())
					{
						break;
					}
				}

				// No match, push our namespace on the list.
				if (j == anLen)
				{
					newNamespaceArray->push (first->atom());
				}
			}
			else
			{
				newNamespaceArray->push (first->atom());
			}
		}
		uint32 namespaceLength = newNamespaceArray->getLength();

		// step 23
		for (uint32 i = 0; i < _length(); i++)
		{
			// step 23b
			E4XNode *child = m_node->_getAt(i);
			XMLObject *xo = new (core->GetGC()) XMLObject(toplevel()->xmlClass(), child);
			if (toplevel()->xmlClass()->okToPrettyPrint() && bIndentChildren)
			{
				s << "\n";
			}
			xo->__toXMLString (s, newNamespaceArray, nextIndentLevel, includeChildren);

			// Our __toXMLString call might have added new namespace onto our list.  We don't want to 
			// save these new namespaces so clear them out here.
			newNamespaceArray->setLength (namespaceLength);
		}

		// Part of the latest spec
		if (toplevel()->xmlClass()->okToPrettyPrint() && bIndentChildren)
		{
			s << "\n";
		}

		//step 24
		if (toplevel()->xmlClass()->okToPrettyPrint() && bIndentChildren)
		{
			for (int i = 0; i < indentLevel; i++)
			{
				s << " ";
			}
		}

		//step 25
		s << "</";

		//step 26
		if (nsPrefix != core->kEmptyString)
		{
			s << nsPrefix << ":";
		}

		//step 27
		s << m.getName() << ">";

		//step 28
		return;
	}

	// E4X 12.2, page 59
	// Support for for-in, for-each for XMLObjects
	Atom XMLObject::nextName(int index)
	{
		AvmAssert(index > 0);
		
		if (index == 1)
		{
			AvmCore *core = this->core();
			return core->internInt (0)->atom();
		}
		else
		{
			return nullStringAtom;
		}
	}

	Atom XMLObject::nextValue(int index)
	{
		AvmAssert(index > 0);

		if (index == 1)
			return this->atom();
		else
			return undefinedAtom;
	}

	int XMLObject::nextNameIndex(int index)
	{
		AvmAssert(index >= 0);

		// XML types just return one value
		if (index == 0)
			return 1;
		else
			return 0;
	}

	XMLObject *XMLObject::AS3_addNamespace (Atom _namespace)
	{
		AvmCore *core = this->core();

		if (core->isNamespace (_namespace))
		{
			m_node->_addInScopeNamespace (core, AvmCore::atomToNamespace(_namespace), publicNS);
		}
		else
		{
			Namespace *ns = core->newNamespace (_namespace);
			m_node->_addInScopeNamespace (core, ns, publicNS);

			_namespace = ns->atom();
		}

		nonChildChanges(xmlClass()->kNamespaceAdded, _namespace);
		return this;
	}

	XMLObject *XMLObject::AS3_appendChild (Atom child)
	{
		AvmCore *core = this->core();

		if(!(PoolObject::kbug444630 & traits()->pool->bugFlags))
		{
			if (AvmCore::isXML(child))
			{
				child = AvmCore::atomToXMLObject(child)->atom();
			}
			else if (AvmCore::isXMLList(child))
			{
				child = AvmCore::atomToXMLList(child)->atom();
			}
			else // all other types go through XML constructor as a string
			{
				child = xmlClass()->ToXML (core->string(child)->atom());
			}
		}

		Atom children = getStringProperty(core->kAsterisk);

		XMLListObject *cxl = AvmCore::atomToXMLList(children);
		int index = _length();
		cxl->setUintProperty (index, child);
		return this;
	}

	XMLListObject *XMLObject::AS3_attribute (Atom arg)
	{
		// E4X 13.4.4.4
		// name= ToAttributeName (attributeName);
		// return [[get]](name)
		return AvmCore::atomToXMLList(getAtomProperty(toplevel()->ToAttributeName(arg)->atom()));
	}

	XMLListObject *XMLObject::AS3_attributes ()
	{
		// E4X 13.4.4.5
		// name= ToAttributeName ("*");
		// return [[get]](name)		

		return AvmCore::atomToXMLList(getAtomProperty(toplevel()->ToAttributeName(core()->kAsterisk)->atom()));
	}

	XMLListObject *XMLObject::AS3_child (Atom P)
	{
		AvmCore *core = this->core();

		// We have an integer argument - direct child lookup
		uint32 index;
		if (AvmCore::getIndexFromString (core->string(P), &index))
		{
			XMLListObject *xl = new (core->GetGC()) XMLListObject(toplevel()->xmlListClass());
			if (index < m_node->numChildren())
			{
				xl->_appendNode (m_node->_getAt(index));
			}
			return xl;
		}

		return AvmCore::atomToXMLList(getAtomProperty(P));
	}

	int XMLObject::AS3_childIndex()
	{
		return m_node->childIndex();
	}

	XMLListObject *XMLObject::AS3_children ()
	{
		return AvmCore::atomToXMLList(getStringProperty(core()->kAsterisk));
	}

	// E4X 13.4.4.8, pg 75
	XMLListObject *XMLObject::AS3_comments ()
	{
		AvmCore *core = this->core();

		XMLListObject *l = new (core->GetGC()) XMLListObject(toplevel()->xmlListClass(), this->atom());

		for (uint32 i = 0; i < m_node->_length(); i++)
		{
			E4XNode *child = m_node->_getAt(i);

			if (child->getClass() == E4XNode::kComment)
			{
				l->_appendNode (child);
			}
		}

		return l;
	}

	// E4X 13.4.4.10, pg 75
	bool XMLObject::AS3_contains (Atom value)
	{
		AvmCore *core = this->core();

		// !!@ Rhino returns false for this case...
		// var xml = new XML("simple");
		// print ("contains: " + xml.contains ("simple"));
		// ...which seems to imply that this routine is calling _equals and not
		// does a "comparison x == value" as stated in the spec.  We'll mimic
		// Rhino for the time being but the correct behavior needs to be determined
		if (this->atom() == value)
			return true;

		if (!AvmCore::isXML(value))
			return false;

		E4XNode *v = AvmCore::atomToXML(value);

		return getNode()->_equals(toplevel(), core, v); // rhino
		//SPEC - return (core()->equals (this->atom(), value) == trueAtom);
	}

	// E4X 13.4.4.11, pg 76
	XMLObject *XMLObject::AS3_copy ()
	{
		return _deepCopy ();
	}

	// E4X 13.4.4.13, pg 76
	XMLListObject *XMLObject::AS3_elements (Atom name) // name defaults to '*'
	{
		AvmCore *core = this->core();

		Multiname m;
		toplevel()->ToXMLName(name, m);

		XMLListObject *l = new (core->GetGC()) XMLListObject(toplevel()->xmlListClass(), this->atom());

		for (uint32 i = 0; i < _length(); i++)
		{
			E4XNode *child = m_node->_getAt(i);

			if (child->getClass() == E4XNode::kElement)
			{
				Multiname m2;
				child->getQName(&m2, publicNS);

				// if name.localName = "*" or name.localName =child->name.localName)
				// and (name.uri == null) or (name.uri == child.name.uri))
				if (m.matches(&m2))
				{
					// if name.localName = "*" or name.localName =child->name.localName)
					// and (name.uri == null) or (name.uri == child.name.uri))
					l->_appendNode (child);
				}
			}
		}

		return l;
	}

	// E4X 13.4.4.14, page 77
	bool XMLObject::XML_AS3_hasOwnProperty (Atom P)
	{
		if (hasAtomProperty(P))
			return true;

		// if this has a property with name ToSString(P), return true;
		// !!@ spec talks about prototype object being different from regular XML object

		return false;
	}

	// E4X 13.4.4.15, page 77
	bool XMLObject::AS3_hasComplexContent ()
	{
		return m_node->hasComplexContent();
	}

	// E4X 13.4.4.16, page 77
	bool XMLObject::AS3_hasSimpleContent ()
	{
		return m_node->hasSimpleContent();
	}

	// E4X 13.4.4.17, page 78
	ArrayObject *XMLObject::AS3_inScopeNamespaces ()
	{
		AvmCore *core = this->core();
		// step 2
		AtomArray *inScopeNS = new (core->GetGC()) AtomArray();

		// step 3
		m_node->BuildInScopeNamespaceList (core, inScopeNS);

		ArrayObject *a = toplevel()->arrayClass->newArray(inScopeNS->getLength());

		uint32 i;
		for (i = 0; i < inScopeNS->getLength(); i++)
		{
			a->setUintProperty (i, inScopeNS->getAt(i)); 
		}

		// !!@ Rhino behavior always seems to return at least one NS
		if (!inScopeNS->getLength())
		{
			// NOTE use caller's public
			a->setUintProperty (i, core->findPublicNamespace()->atom());
		}

		return a;
	}

	// E4X 13.4.4.18, page 78
	Atom XMLObject::AS3_insertChildAfter (Atom child1, Atom child2)
	{
		AvmCore *core = this->core();
		Toplevel *toplevel = this->toplevel();

		if (getClass() & (E4XNode::kText | E4XNode::kComment | E4XNode::kProcessingInstruction | E4XNode::kAttribute | E4XNode::kCDATA))
			return undefinedAtom;

		if(!(PoolObject::kbug444630 & traits()->pool->bugFlags)) 
		{
			if (AvmCore::isXML(child2))
			{
				child2 = AvmCore::atomToXMLObject(child2)->atom();
			}
			else if (AvmCore::isXMLList(child2))
			{
				child2 = AvmCore::atomToXMLList(child2)->atom();
			}
			else // all other types go through XML constructor as a string
			{
				child2 = xmlClass()->ToXML (core->string(child2)->atom());
			}
		}

		if (AvmCore::isNull(child1))
		{
			m_node->_insert (core, toplevel, 0, child2);
			childChanges(xmlClass()->kNodeAdded, child2);
			return this->atom();
		}
		else
		{
			E4XNode *c1 = AvmCore::atomToXML(child1);
			// Errata extension to E4X spec - treat XMLList with length=1 as a XMLNode
			if (!c1 && AvmCore::isXMLList(child1))
			{
				XMLListObject *xl = AvmCore::atomToXMLList(child1);
				if (xl->_length() == 1)
					c1 = xl->_getAt(0)->m_node;
			}
			if (c1)
			{
				for (uint32 i = 0; i < _length(); i++)
				{
					E4XNode *child = m_node->_getAt(i);

					if (child == c1)
					{
						m_node->_insert (core, toplevel, i + 1, child2);
						childChanges(xmlClass()->kNodeAdded, child2);
						return this->atom(); 
					}
				}
			}
		}

		return undefinedAtom; 
	}

	// E4X 13.4.4.19, page 79
	Atom XMLObject::AS3_insertChildBefore (Atom child1, Atom child2)
	{
		AvmCore *core = this->core();
		Toplevel *toplevel = this->toplevel();

		if (getClass() & (E4XNode::kText | E4XNode::kComment | E4XNode::kProcessingInstruction | E4XNode::kAttribute | E4XNode::kCDATA))
			return undefinedAtom;

		if(!(PoolObject::kbug444630 & traits()->pool->bugFlags))
		{
			if (AvmCore::isXML(child2))
			{
				child2 = AvmCore::atomToXMLObject(child2)->atom();
			}
			else if (AvmCore::isXMLList(child2))
			{
				child2 = AvmCore::atomToXMLList(child2)->atom();
			}
			else // all other types go through XML constructor as a string
			{
				child2 = xmlClass()->ToXML (core->string(child2)->atom());
			}
		}

		if (AvmCore::isNull(child1))
		{
			m_node->_insert (core, toplevel, _length(), child2);
			childChanges(xmlClass()->kNodeAdded, child2);
			return this->atom();
		}
		else
		{
			E4XNode *c1 = AvmCore::atomToXML(child1);
			// Errata extension to E4X spec - treat XMLList with length=1 as a XMLNode
			if (!c1 && AvmCore::isXMLList(child1))
			{
				XMLListObject *xl = AvmCore::atomToXMLList(child1);
				if (xl->_length() == 1)
					c1 = xl->_getAt(0)->m_node;
			}
			if (c1)
			{
				for (uint32 i = 0; i < _length(); i++)
				{
					E4XNode *child = m_node->_getAt(i);

					if (child == c1)
					{
						m_node->_insert (core, toplevel, i, child2);
						childChanges(xmlClass()->kNodeAdded, child2);
						return this->atom();
					}
				}
			}
		}

		return undefinedAtom; 
	}

	// E4X 13.4.4.21, page 80
	Atom XMLObject::AS3_localName ()
	{
		Multiname m;
		if (m_node->getQName(&m, publicNS) == 0)
		{
			return nullStringAtom;
		}
		else
		{
			return m.getName()->atom();
		}
	}

	// E4X 13.4.4.22, page 80
	Atom XMLObject::AS3_name ()
	{
		AvmCore *core = this->core();
		Multiname m;
		if (!m_node->getQName(&m, publicNS))
			return nullObjectAtom;

		return (new (core->GetGC(), toplevel()->qnameClass()->ivtable()->getExtraSize()) QNameObject(toplevel()->qnameClass(), m))->atom();
	}

	// E4X 13.4.4.23, page 80
	Atom XMLObject::_namespace (Atom p_prefix, int argc) // prefix is optional
	{
		AvmAssert(argc == 0 || argc == 1);

		AvmCore *core = this->core();

		// step 2
		AtomArray *inScopeNS = new (core->GetGC()) AtomArray();

		// step 3
		m_node->BuildInScopeNamespaceList (core, inScopeNS);

		// step 5
		if (!argc)
		{
			// step 5a
			if (getClass() & (E4XNode::kText | E4XNode::kComment | E4XNode::kCDATA | E4XNode::kProcessingInstruction))
				return nullObjectAtom; 

			// step 5b
			// Return the result of calling [[GetNamespace]] method of 
			// x.[[Name]] with argument inScopeNS
			Multiname m;
			AvmAssert(getQName(&m));
			getQName(&m);
			Namespace *ns = GetNamespace (m, inScopeNS);

			return (ns->atom());
		}
		else
		{
			Atom prefix = core->internString(core->string (p_prefix))->atom();

			for (uint32 i = 0; i < inScopeNS->getLength(); i++)
			{
				Namespace *ns = AvmCore::atomToNamespace (inScopeNS->getAt(i));
				if (ns->getPrefix() == prefix)
					return ns->atom();
			}

			return undefinedAtom;
		}
	}

	// 13.4.4.24, pg 80-81
	ArrayObject *XMLObject::AS3_namespaceDeclarations ()
	{
		AvmCore *core = this->core();
		ArrayObject *a = toplevel()->arrayClass->newArray();

		if (getClass() & (E4XNode::kText | E4XNode::kComment | E4XNode::kProcessingInstruction | E4XNode::kAttribute | E4XNode::kCDATA))
			return a; 

		E4XNode *y = m_node->getParent();

		// step 4+5
		AtomArray *ancestorNS = new (core->GetGC()) AtomArray();
		if (y)	
			y->BuildInScopeNamespaceList (core, ancestorNS);

		uint32 arrayIndex = 0;

		// step 7+8+9+10
		for (uint32 i = 0; i < m_node->numNamespaces(); i++)
		{
			Namespace *ns = AvmCore::atomToNamespace (m_node->getNamespaces()->getAt(i));
			if (!ns->hasPrefix ())
			{
				// Emulating Rhino behavior
			    if (ns->getURI() != core->kEmptyString)
				{
					bool bMatch = false;
					for (uint32 j = 0; j < ancestorNS->getLength(); j++)
					{
						Namespace *ns2 = AvmCore::atomToNamespace (ancestorNS->getAt(j));
						if (ns->getURI() == ns2->getURI())
						{
							bMatch = true;
							break;
						}
					}

					if (!bMatch)
					{
						a->setUintProperty (arrayIndex++, ns->atom());
					}
				}
			}
			else // ns.prefix is NOT empty
			{
				bool bMatch = false;
				for (uint32 j = 0; j < ancestorNS->getLength(); j++)
				{
					Namespace *ns2 = AvmCore::atomToNamespace (ancestorNS->getAt(j));
					if (ns->getPrefix() == ns2->getPrefix() && ns->getURI() == ns2->getURI())
					{
						bMatch = true;
						break;
					}
				}

				if (!bMatch)
				{
					a->setUintProperty (arrayIndex++, ns->atom());
				}
			}
		}

		return a;
	}

	String *XMLObject::AS3_nodeKind () const
	{
		return m_node->nodeKind(toplevel());
	}

	XMLObject *XMLObject::AS3_normalize ()
	{
		AvmCore* core = this->core();

		bool notify = notifyNeeded(getNode());
		uint32 i = 0;
		while (i < _length())
		{
			E4XNode *x = m_node->_getAt(i);
			if (x->getClass() == E4XNode::kElement)
			{
				XMLObject *xo = new (core->GetGC()) XMLObject(toplevel()->xmlClass(), x);
				xo->normalize();
				::delete xo;
				i++;
			}
			else if (x->getClass() & (E4XNode::kText | E4XNode::kCDATA))
			{
				Stringp prior = x->getValue();
				while (((i + 1) < _length()) && (m_node->_getAt(i + 1)->getClass() & (E4XNode::kText | E4XNode::kCDATA)))
				{
					E4XNode *x2 = m_node->_getAt(i + 1);
					x->setValue (core->concatStrings(x->getValue(), x2->getValue()));
					m_node->_deleteByIndex (i + 1);

					if (notify)
					{
						XMLObject *nd = new (core->GetGC())  XMLObject (xmlClass(), x2);
						childChanges(xmlClass()->kNodeRemoved, nd->atom());
					}
				}
				/// Need to check if string is "empty" - 0 length or filled with whitespace
				if (x->getValue()->isWhitespace())
				{
					E4XNode* prior = m_node->_getAt(i);

					m_node->_deleteByIndex (i);

					if (notify)
					{
						XMLObject *nd = new (core->GetGC())  XMLObject (xmlClass(), prior);
						childChanges(xmlClass()->kNodeRemoved, nd->atom());
					}
				}
				else
				{
					i++;
				}
				
				// notify if the node has changed value
				Stringp current = x->getValue();
				if ((current != prior) && notify)
				{
					XMLObject *xo = new (core->GetGC())  XMLObject (xmlClass(), x);
					xo->nonChildChanges(xmlClass()->kTextSet, current->atom(), (prior) ? prior->atom() : undefinedAtom);
				}
			}
			else
			{
				i++;
			}
		}

		return this;
	}

	Atom XMLObject::AS3_parent ()
	{
		if (m_node->getParent())
			return (new (core()->GetGC()) XMLObject (toplevel()->xmlClass(), m_node->getParent()))->atom();
		else
			return undefinedAtom;
	}

	XMLListObject *XMLObject::AS3_processingInstructions (Atom name) // name defaults to '*'
	{
		AvmCore *core = this->core();

		Multiname m;
		toplevel()->ToXMLName(name, m);

		XMLListObject *xl = new (core->GetGC()) XMLListObject(toplevel()->xmlListClass(), this->atom());

		if (m.isAttr())
			return xl;

		for (uint32 i = 0; i < m_node->_length(); i++)
		{
			E4XNode *child = m_node->_getAt(i);

			if (child->getClass() == E4XNode::kProcessingInstruction)
			{
				Multiname m2;
				bool bFound = child->getQName(&m2, publicNS);

				// if name.localName = "*" or name.localName =child->name.localName)
				// and (name.uri == null) or (name.uri == child.name.uri))
				if (m.matches(bFound ? &m2 : 0))
				{
					xl->_appendNode (child);
				}
			}
		}

		return xl;
	}

	XMLObject *XMLObject::AS3_prependChild (Atom value)
	{
		AvmCore *core = this->core();
		Toplevel *toplevel = this->toplevel();

		if(!(PoolObject::kbug444630 & traits()->pool->bugFlags))
		{
			if (AvmCore::isXML(value))
			{
				value = AvmCore::atomToXMLObject(value)->atom();
			}
			else if (AvmCore::isXMLList(value))
			{
				value = AvmCore::atomToXMLList(value)->atom();
			}
			else // all other types go through XML constructor as a string
			{
				value = xmlClass()->ToXML (core->string(value)->atom());
			}
		}

		m_node->_insert (core, toplevel, 0, value);

		childChanges(xmlClass()->kNodeAdded, value);
		return this;
	}

	bool XMLObject::XML_AS3_propertyIsEnumerable(Atom P)	// NOT virtual, not an override
	{
		AvmCore *core = this->core();
		if (core->intern(P) == core->internConstantStringLatin1("0"))
			return true;

		return false;
	}

	// 13.4.4.31, pg 83
	XMLObject *XMLObject::AS3_removeNamespace (Atom nsAtom)
	{
		AvmCore *core = this->core();
		if (getClass() & (E4XNode::kText | E4XNode::kComment | E4XNode::kProcessingInstruction | E4XNode::kAttribute | E4XNode::kCDATA))
			return this; 
		
		Namespace *ns = core->isNamespace (nsAtom) ? AvmCore::atomToNamespace (nsAtom) : core->newNamespace (nsAtom);

		Multiname m;
		AvmAssert(getQName(&m));
		getQName(&m);
		Namespace *thisNS = GetNamespace (m, m_node->getNamespaces());

		// step 4
		if (thisNS == ns)
			return this;

		//step 5
		for (uint32 j = 0; j < m_node->numAttributes(); j++)
		{
			E4XNode *a = m_node->getAttribute(j);
			Multiname m;
			AvmAssert(a->getQName(&m, publicNS));
			a->getQName(&m, publicNS);
			Namespace *anNS = GetNamespace (m, m_node->getNamespaces());
			if (anNS == ns)
				return this;
		}

		// step 6+7
		int32 i = m_node->FindMatchingNamespace (core, ns);
		if (i != -1)
		{
			m_node->getNamespaces()->removeAt(i);
		}

		// step 8
		for (uint32 k = 0; k < _length(); k++)
		{
			E4XNode *p = m_node->_getAt(k);
			if (p->getClass() == E4XNode::kElement)
			{
				XMLObject *xo = new (core->GetGC()) XMLObject(toplevel()->xmlClass(), p);
				xo->removeNamespace (ns->atom());
				::delete xo;
			}
		}

		// step 9
		// Note about namespaces in ancestors and parents, etc.
		nonChildChanges(xmlClass()->kNamespaceRemoved, ns->atom());
		return this;
	}

	XMLObject *XMLObject::AS3_replace (Atom P, Atom value)
	{
		AvmCore *core = this->core();
		Toplevel *toplevel = this->toplevel();

		if (getClass() & (E4XNode::kText | E4XNode::kComment | E4XNode::kProcessingInstruction | E4XNode::kAttribute | E4XNode::kCDATA))
			return this; 

		Atom c;
		if (AvmCore::isXML(value))
		{
			XMLObject *x = AvmCore::atomToXMLObject(value);
			c = x->_deepCopy()->atom();
		}
		else if (AvmCore::isXMLList(value))
		{
			XMLListObject *xl = AvmCore::atomToXMLList(value);
			c = xl->_deepCopy()->atom();
		}
		else
		{
			if(!(PoolObject::kbug444630 & traits()->pool->bugFlags))
				c = xmlClass()->ToXML (core->string(value)->atom());
			else
				c = core->string(value)->atom();
		}

		uint32 index;
		if (AvmCore::getIndexFromString (core->string(P), &index))
		{
			E4XNode* prior = m_node->_replace (core, toplevel, index, c);
			childChanges(xmlClass()->kNodeChanged, c, prior);
			return this;
		}

		QNameObject *qn1 = new (core->GetGC(), toplevel->qnameClass()->ivtable()->getExtraSize()) QNameObject(toplevel->qnameClass(), P);
		Multiname m;
		qn1->getMultiname(m);
		bool notify = notifyNeeded(getNode());
		int i = -1;
		for (int k = int(_length()) - 1; k >= 0; k--)
		{
			E4XNode *x = m_node->_getAt (k);
			Multiname *m2 = 0;
			
			// m3 needs to exist outside this if scope since m2 will point to it
			Multiname m3;
			if (x->getClass() == E4XNode::kElement)
			{
				if (x->getQName(&m3, publicNS))
					m2 = &m3;
			}

			if (m.matches(m2))
			{
				if (i != -1)
				{
					E4XNode* was = m_node->_getAt(i);

					m_node->_deleteByIndex (i);

					// notify 
					if (notify && was->getClass() == E4XNode::kElement)
					{
						XMLObject* nd = new (core->GetGC())  XMLObject (xmlClass(), was);
						childChanges(xmlClass()->kNodeRemoved, nd->atom());
					}
				}
				
				i = k;
			}
		}
		::delete qn1;

		if (i == -1)
			return this;

		E4XNode* prior = m_node->_replace (core, toplevel, i, c);
		childChanges( (prior) ? xmlClass()->kNodeChanged : xmlClass()->kNodeAdded, c, prior);
		return this;
	}

	XMLObject *XMLObject::AS3_setChildren (Atom value)
	{
		setStringProperty(core()->kAsterisk, value);
		return this;
	}

	void XMLObject::AS3_setLocalName (Atom name)
	{
		if (m_node->getClass() & (E4XNode::kText | E4XNode::kComment | E4XNode::kCDATA))
			return;

		AvmCore *core = this->core();
		QNameObject *qn = AvmCore::atomToQName(name);
		Stringp newname;
		if (qn)
		{
			newname = qn->get_localName();
		}
		else
		{
			newname = core->intern(name);
		}

		if (!core->isXMLName(newname->atom()))
			toplevel()->throwTypeError(kXMLInvalidName, newname);

		Multiname m;

		if (this->getNode()->getQName(&m, publicNS))
		{
			Multiname previous;
			getNode()->getQName(&previous, publicNS);
			Stringp prior = previous.getName();

			m.setName (newname);
			getNode()->setQName (core, &m);

			nonChildChanges(xmlClass()->kNameSet, m.getName()->atom(), (prior) ? prior->atom() : undefinedAtom );
		}
		return;
	}

	void XMLObject::AS3_setName (Atom name)
	{
		AvmCore *core = this->core();

		if (m_node->getClass() & (E4XNode::kText | E4XNode::kComment | E4XNode::kCDATA))
			return;

		if (AvmCore::isQName(name))
		{
			QNameObject *q  = AvmCore::atomToQName(name);
			if (AvmCore::isNull(q->getURI()))
			{
				name = q->get_localName()->atom();
			}
		}

		QNameObject *n = new (core->GetGC(), toplevel()->qnameClass()->ivtable()->getExtraSize()) QNameObject(toplevel()->qnameClass(), name); 

		Stringp s = n->get_localName();
		if (!core->isXMLName(s->atom()))
			toplevel()->throwTypeError(kXMLInvalidName, s);

		Multiname m;
		if (m_node->getQName(&m, publicNS))
		{
			if (m_node->getClass() == E4XNode::kProcessingInstruction)
			{
				m_node->setQName (core, n->get_localName(), core->findPublicNamespace());
			}
			else // only for attribute and element nodes
			{
				Multiname m2;
				n->getMultiname (m2);
				m_node->setQName (core, &m2);

				// ISNS changes
				if (n->getURI() != core->kEmptyString->atom())
				{
					m_node->getQName(&m, publicNS); // get our new multiname

					if (this->getClass() == E4XNode::kAttribute && getNode()->getParent())
					{
						getNode()->getParent()->_addInScopeNamespace (core, m.getNamespace(), publicNS);
					}
					else if (this->getClass() == E4XNode::kElement)
					{
						getNode()->_addInScopeNamespace (core, m.getNamespace(), publicNS);
					}
				}
			}

			nonChildChanges(xmlClass()->kNameSet, name, m.getName()->atom());
		}
		return;
	}

	void XMLObject::AS3_setNamespace (Atom ns)
	{
		AvmCore *core = this->core();

		if (m_node->getClass() & (E4XNode::kText | E4XNode::kComment | E4XNode::kProcessingInstruction | E4XNode::kCDATA))
			return;

		Namespace* newns = core->newNamespace (ns);

		Multiname m;
		if (m_node->getQName(&m, publicNS))
		{
			m_node->setQName (core, m.getName(), newns);
		}

		// ISNS changes
		if (this->getClass() == E4XNode::kAttribute && getNode()->getParent())
		{
			getNode()->getParent()->_addInScopeNamespace (core, newns, publicNS);
		}
		else if (this->getClass() == E4XNode::kElement)
		{
			getNode()->_addInScopeNamespace (core, newns, publicNS);
		}

		nonChildChanges(xmlClass()->kNamespaceSet, newns->atom());
		return;
	}

	XMLListObject *XMLObject::AS3_text ()
	{
		XMLListObject *l = new (gc()) XMLListObject(toplevel()->xmlListClass(), this->atom());

		for (uint32 i = 0; i < m_node->_length(); i++)
		{
			E4XNode *child = m_node->_getAt(i);
			if (child->getClass() & (E4XNode::kText | E4XNode::kCDATA))
			{
				l->_appendNode (child);
			}
		}

		return l;
	}

	// E4X 10.1, page 28
	Atom XMLObject::toString ()
	{
		AvmCore *core = this->core();
			
		if (getClass() & (E4XNode::kText | E4XNode::kCDATA | E4XNode::kAttribute))
		{
			return m_node->getValue()->atom(); 
		}

		if (hasSimpleContent())
		{
			Stringp s = core->kEmptyString;

			for (uint32 i = 0; i < _length(); i++)
			{
				E4XNode *child = m_node->_getAt(i);
				if ((child->getClass() != E4XNode::kComment) && (child->getClass() != E4XNode::kProcessingInstruction))
				{

					XMLObject *xo = new (core->GetGC()) XMLObject(toplevel()->xmlClass(), child);
					s = core->concatStrings(s, core->string(xo->toString())); 
					::delete xo;
				}
			}

			return s->atom();
		}
		else
		{
			AtomArray *AncestorNamespaces = new (core->GetGC()) AtomArray();
			StringBuffer s(core);
			__toXMLString(s, AncestorNamespaces, 0);
			return core->newStringUTF8(s.c_str())->atom();
		}
	}

	Stringp XMLObject::AS3_toString()
	{
        return core()->atomToString(toString());
	}

	String *XMLObject::AS3_toXMLString ()
	{
		AtomArray *AncestorNamespaces = new (MMgc::GC::GetGC(this)) AtomArray();
		StringBuffer s(core());
		__toXMLString(s, AncestorNamespaces, 0);
		return core()->newStringUTF8(s.c_str());
	}

#ifdef AVMPLUS_VERBOSE
	Stringp XMLObject::format(AvmCore* core) const
	{
		//
		// [mmorearty 10/24/05] Flex Builder 2.0 relies on this format in order to
		// have a nice display of XML in the Variables view:
		//
		//		"XML@hexaddr nodeKind text_to_display"
		//
		AtomArray *AncestorNamespaces = new (core->GetGC()) AtomArray();
		StringBuffer openTag(core);
		__toXMLString(openTag, AncestorNamespaces, 0, false);
		Stringp openingTag = core->newStringUTF8(openTag.c_str());

		Stringp result = ScriptObject::format(core);
		result = result->appendLatin1(" ");
		result = core->concatStrings(result, nodeKind());
		result = result->appendLatin1(" ");
		result = core->concatStrings(result, openingTag);
		return result;
	}
#endif

	int XMLObject::getClass() const
	{ 
		return m_node->getClass() ;
	}

	uint32 XMLObject::_length() const
	{ 
		return m_node->_length();
	}

	XMLObject *XMLObject::getParent()
	{
		if (m_node->getParent())
			return new (core()->GetGC()) XMLObject (toplevel()->xmlClass(), m_node->getParent());
		else
			return 0;
	}

	void XMLObject::setValue(Stringp s) 
	{ 
		m_node->setValue (s); 
	}

	Stringp XMLObject::getValue() 
	{ 
		return m_node->getValue(); 
	}

	bool XMLObject::getQName(Multiname *m) 
	{ 
		return m_node->getQName(m, publicNS); 
	}

	Atom XMLObject::AS3_setNotification(FunctionObject* f)
	{
		AvmCore* core  = this->core();

		// Notifiers MUST be functions or null
		if (f && !AvmCore::istype(f->atom(), core->traits.function_itraits)) 
			toplevel()->throwArgumentError( kInvalidArgumentError, "f");
		else
			m_node->setNotification(core, f, publicNS);
		// since AS3 sez this returns an Atom, our implementation must do so.
		return undefinedAtom;
	}

	FunctionObject* XMLObject::AS3_notification()
	{
		return m_node->getNotification();
	}

	bool XMLObject::notifyNeeded(E4XNode* initialTarget)
	{
		// do a quick probe to see if we need to issue any notifications
		bool hit = false;
		E4XNode* node = initialTarget;
		while(node)
		{
			if (node->getNotification())
			{
				hit = true;
				break;
			}
			node = node->getParent();
		}
		return hit;
	}

	/**
	 * Notification on generic node addition from XML or XMLList 
	 */
	void XMLObject::childChanges(Stringp type, Atom value, E4XNode* prior)
	{
		AvmCore* core = this->core();
		Toplevel* top = this->toplevel();
		E4XNode* initialTarget = m_node;

		if (notifyNeeded(initialTarget))
		{
			XMLObject* target = new (core->GetGC()) XMLObject(top->xmlClass(), initialTarget);
			Atom detail = undefinedAtom;
			if (prior)
			{
				XMLObject* xml = new (core->GetGC()) XMLObject(xmlClass(), prior);
				detail = xml->atom();
			}

			if (AvmCore::isXML(value))
			{
				issueNotifications(core, top, initialTarget, target->atom(), type, value, detail);
			}
			else if (AvmCore::isXMLList(value))
			{
				// if its a list each element in the list is added.
				XMLListObject* xl = AvmCore::atomToXMLList(value);
				if (xl)
				{
					issueNotifications(core, top, initialTarget, target->atom(), type, xl->atom(), detail);
				}
				else
				{
					AvmAssert(false);
				}
			}
			else
			{
				// non child updates
			}
		}
	}

	void XMLObject::nonChildChanges(Stringp type, Atom value, Atom detail)
	{
		AvmCore* core = this->core();
		Toplevel* top = this->toplevel();
		E4XNode* initialTarget = m_node;
		if (notifyNeeded(initialTarget))
		{
			XMLObject* target = new (core->GetGC()) XMLObject(top->xmlClass(), initialTarget);
			issueNotifications(core, top, initialTarget, target->atom(), type, value, detail);
		}
	}

	/**
	 * Perform the callback for each node in which the notification property is set.
	 */
	void XMLObject::issueNotifications(AvmCore* core, Toplevel* top, E4XNode* initialTarget, Atom target, Stringp type, Atom value, Atom detail)
	{
		// start notification at initialtarget
		E4XNode* volatile node = initialTarget;

		while(node)
		{
			// check if notification param set
			ScriptObject* methodObj = node->getNotification();
			if (methodObj) 
			{
				XMLObject* currentTarget = new (core->GetGC())  XMLObject(top->xmlClass(), node);
				Atom argv[6] = { top->atom(), currentTarget->atom(), type->atom(), target, value, detail };
				int argc = 5;

				//EnterScriptTimeout enterScriptTimeout(core);				
				TRY(core, kCatchAction_Rethrow)
				{
					methodObj->call(argc, argv);
				}
				CATCH(Exception *exception)
				{
					// you chuck, we chuck 
					core->throwException(exception);
				}
				END_CATCH
				END_TRY
			}			

			// bubble up
			node = node->getParent();
		}
	}

#ifdef XML_FILTER_EXPERIMENT
	XMLListObject * XMLObject::filter (Atom propertyName, Atom value)
	{
		Multiname m;
		toplevel()->ToXMLName(propertyName, m);

		Multiname name;
		toplevel()->CoerceE4XMultiname(&m, name);

		// filter opcode experiment
		XMLListObject *l = new (core()->gc) XMLListObject(toplevel()->xmlListClass(), nullObjectAtom);
		this->_filter (l, name, value);

		return l;
	}

	void XMLObject::_filter (XMLListObject *l, const Multiname &name, Atom value)
	{
		AvmCore *core = this->core();

		if (!name.isAnyName())
		{
			// We have an integer argument - direct child lookup
			Stringp nameString = name.getName();
			uint32 index;
			if (AvmCore::getIndexFromString (nameString, &index))
			{
				if (index == 0)
				{
					if (core->equals (this->atom(), value))
					{
						l->_append (this->getNode());
					}
				}
			}
		}

		if (name.isAttr())
		{
			// for each a in x.[[attributes]]
			for (uint32 i = 0; i < m_node->numAttributes(); i++)
			{
				E4XNode *xml = m_node->getAttribute(i);

				AvmAssert(xml && xml->getClass() == E4XNode::kAttribute);

				Multiname m;
				AvmAssert(xml->getQName(&m, publicNS) != 0);

				xml->getQName(&m, publicNS);
				if (name.matches(&m))
				{
					if (core->equals(xml->getValue()->atom(), value) == trueAtom)
						l->_append (xml);
				}
			}

			return;
		}

		for (uint32 i = 0; i < m_node->numChildren(); i++)
		{
			E4XNode *child = m_node->_getAt(i);
			Multiname m;
			Multiname *m2 = 0;
			if (child->getClass() == E4XNode::kElement)
			{
				child->getQName(&m, publicNS);
				m2 = &m;
			}

			if (name.matches(m2))
			{
				// If we're an element node, we do something more complicated than a string compare
				if (child->getClass() == E4XNode::kElement)
				{
					// Hacky swaping of our XMLObject's node ptr to point to the child
					// node so we can call out to AvmCore::eq with an atom.
					E4XNode *savedNode = this->m_node;
					this->m_node = child;
					if (core->equals(this->atom(), value) == trueAtom)
						l->_append (child);
					this->m_node = savedNode;
				}
				else
				{
					// !!@ this needs testing with comments/PI/text/etc.
					if (core->equals(child->getValue()->atom(), value) == trueAtom)
						l->_append (child);
				}

			}
		}
	}
#endif // XML_FILTER_EXPERIMENT

	void XMLObject::dispose()
	{
		m_node->dispose();
	}

	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////

	QNameObject::QNameObject (QNameClass *factory, const Multiname &name)
		: ScriptObject(factory->ivtable(), factory->prototype), m_mn(name)
	{
	}

	/**
	 * QNameObject is used to represent the "QName" object in the E4X Specification.
	 *
	 * We also use this same object to represent "AttributeName" in the E4X spec.
	 * An AttributeName is simply a QName wrapper for finding properties that have a leading @ sign.
	 * It's an internal class to the spec and the only difference between a QName is the @.  Instead of
	 * having the overhead of an AttributeName class that wraps the QName class, we just use a boolean
	 * inside the QName to differentiate betweent the two types.
	 */
	QNameObject::QNameObject(QNameClass *factory, Namespace *ns, Atom nameatom, bool bA)
		: ScriptObject(factory->ivtable(), factory->prototype)
	{
		AvmCore *core = this->core();

		Stringp name;
		if (AvmCore::isQName(nameatom))
		{
			QNameObject *q = AvmCore::atomToQName(nameatom);
			name = q->m_mn.getName();
		}
		else if (nameatom == undefinedAtom)
		{
			name = core->kEmptyString;
		}
		else
		{
			name = core->intern(nameatom);
		}

		Multiname mn;

		// Set attribute bit in multiname
		if (bA)
			mn.setAttr();

		if (name == core->kAsterisk)
		{
			mn.setAnyName();
			AvmAssert(mn.isAnyName());
		}
		else
		{
			mn.setName(name);
		}

		if (ns == NULL)
		{
			mn.setAnyNamespace();
		}
		else
		{
			mn.setNamespace(core->internNamespace(ns));
			mn.setQName();
		}
		this->m_mn = mn;
	}

	/**
	 * called when no namespace specified.
	 */
	QNameObject::QNameObject(QNameClass *factory, Atom nameatom, bool bA)
	: ScriptObject(factory->ivtable(), factory->prototype)
	{
		AvmCore *core = this->core();
		Toplevel* toplevel = this->toplevel();

		Multiname mn;

		if (AvmCore::isQName(nameatom))
		{
			QNameObject *q = AvmCore::atomToQName(nameatom);
			mn = q->m_mn;
		}
		else
		{
			Stringp name = core->intern(nameatom);
			if (name == core->kAsterisk)
			{
				mn.setAnyNamespace();
				mn.setAnyName();
				AvmAssert(mn.isAnyName());
			}
			else
			{
				if (nameatom == undefinedAtom)
				{
					mn.setName(core->kEmptyString);
				}			
				else
				{
					mn.setName(name);
				}
				Namespacep ns = ApiUtils::getVersionedNamespace(core, toplevel->getDefaultNamespace(), core->getAPI(NULL));
				mn.setNamespace(ns);
			}
		}

		// Set attribute bit in multiname
		if (bA)
			mn.setAttr();
		
		this->m_mn = mn;
	}

	Stringp QNameObject::get_localName() const
	{
		if (this->m_mn.isAnyName())
			return core()->kAsterisk;

		return m_mn.getName();
	}

	Atom QNameObject::getURI() const
	{
		if (m_mn.isAnyNamespace())
		{
			return nullStringAtom;
		}
		else if (m_mn.namespaceCount() > 1)
		{
			return core()->kEmptyString->atom();
		}
		else
		{
			return m_mn.getNamespace()->getURI()->atom();
		}
	}

	Atom QNameObject::get_uri() const
	{
	    return getURI();
	}

	// E4X 13.3.5.4, pg 69
	Namespace *XMLObject::GetNamespace (const Multiname &mn, const AtomArray *nsArray) const
	{
		AvmCore *core = this->core();

		Stringp uri = (mn.isAnyNamespace() ? 0 : mn.getNamespace()->getURI());

		if (nsArray)
		{
			for (uint32 i = 0; i < nsArray->getLength(); i++)
			{
				Namespace *ns = AvmCore::atomToNamespace (nsArray->getAt(i));
				AvmAssert(ns!=NULL);
#ifdef STRING_DEBUG
				Stringp s1 = ns->getURI();
				Stringp s2 = uri;
#endif // STRING_DEBUG
				if (ns->getURI() == uri)
				{
					return ns;
				}
			}
		}

		// not found, return empty namespace based upon this QName's uri.
		return core->newNamespace (uri->atom());
	}

	// Iterator support - for in, for each
	Atom QNameObject::nextName(int index)
	{
		AvmAssert(index > 0);
		// first return "uri" then "localName"
		if (index == 1)
			return toplevel()->qnameClass()->kUri;
		else if (index == 2)
			return toplevel()->qnameClass()->kLocalName;
		else
			return nullObjectAtom;
	}

	Atom QNameObject::nextValue(int index)
	{
		AvmAssert(index > 0);
		// first return uri then localName
		if (index == 1)
			return this->get_localName()->atom();
		else if (index == 2)
			return this->getURI();
		else
			return nullStringAtom;
	}

	int QNameObject::nextNameIndex(int index)
	{
		AvmAssert(index >= 0);

		if (index < 2)
			return index + 1;
		else 
			return 0;
	}
}
