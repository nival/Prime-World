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

#ifndef __avmplus_E4XNode__
#define __avmplus_E4XNode__


// E4X 9.1.1 Internal Properties and Methods
// Name
// Parent
// Attributes
// InScopeNamespaces
// Length
// Delete (overrides Object version)
// Get (overrides Object version)
// HasProperty (overrides Object version)
// Put (overrides Object version)
// DeleteByIndex (PropertyName)
// DeepCopy
// ResolveValue
// Descendants (PropertyName)
// Equals (Value)
// Insert (PropertyName, Value)
// Replace (PropertyName, Value)
// AddInScopeNamespace (Namespace)

// These are static objects on the XML type
// E4X: The XML constructor has the following properties
// XML.ignoreComments
// XML.ignoreProcessingInstructions
// XML.ignoreWhitespace
// XML.prettyPrinting
// XML.prettyIndent
// XML.settings
// XML.setSettings ([settings])
// XML.defaultSettings()

// XML.prototype.constructor ??
// XML.prototype.addNamespace
// XML.prototype.appendChild
// XML.prototype.attribute
// XML.prototype.attributes
// XML.prototype.child
// XML.prototype.childIndex
// XML.prototype.children
// XML.prototype.comments
// XML.prototype.contains
// XML.prototype.copy
// XML.prototype.descendants
// XML.prototype.elements
// XML.prototype.hasOwnProperty
// XML.prototype.hasComplexContent
// XML.prototype.hasSimpleContent
// XML.prototype.inScopeNamespaces
// XML.prototype.insertChildAfter
// XML.prototype.insertChildBefore
// XML.prototype.length
// XML.prototype.localName
// XML.prototype.name
// XML.prototype.namespace
// XML.prototype.namespaceDeclarations
// XML.prototype.nodeKind
// XML.prototype.normalize
// XML.prototype.parent
// XML.prototype.processingInstructions
// XML.prototype.prependChild
// XML.prototype.propertyIsEnumerable
// XML.prototype.removeNamespace
// XML.prototype.replace
// XML.prototype.setChildren
// XML.prototype.setLocalName
// XML.prototype.setName
// XML.prototype.setNamespace
// XML.prototype.text
// XML.prototype.toString
// XML.prototype.toXMLString
// XML.prototype.valueOf

namespace avmplus
{
	class E4XNodeAux : public MMgc::GCObject
	{
		DRCWB(Stringp)		m_name;
		DRCWB(Namespace*)		m_ns;
				
		/** callback on changes to children, attribute, name or namespace */
		DRCWB(FunctionObject*)	m_notification;

		friend class E4XNode;
		friend class ElementE4XNode;

	public:
		E4XNodeAux(Stringp s, Namespace* ns, FunctionObject* notify = NULL);
	};

	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	/**
	 * E4XNode is the C++ implementation of the XML class
	 * in the E4X Specification.
	 */
	// Currently this is 12-bytes in size (4 bytes wasted by GC)
	// Element nodes are 24 bytes
	// All other nodes are 16 bytes
	class E4XNode : public MMgc::GCObject
	{
	protected:
		/** Either null or an E4XNode, valid for all node types */
		DWB(E4XNode*) m_parent; 

		// If this is a simple name with no namespace or notification function, 
		// we just have a string pointer.  Otherwise, we're a E4XNodeAux value
		// containing a name + namespace as well as a notification function.
		// E4XNodeAux *
		// String *
		uintptr m_nameOrAux;
		#define AUXBIT 0x1

	public:
		E4XNode(E4XNode* parent) : m_parent(parent), m_nameOrAux(0) { }

		// we have virtual functions, so we probably need a virtual dtor
		virtual ~E4XNode() {}

		bool getQName (Multiname *mn, Namespacep publicNS) const;
		void setQName (AvmCore *core, Stringp name, Namespace *ns = 0);
		void setQName (AvmCore *core, const Multiname *mn);

		virtual Stringp getValue() const = 0;
		virtual void setValue (String *s) = 0;

		E4XNode* getParent() const { return m_parent; };
		void setParent(E4XNode* n) { m_parent = n; }

		// Not used as bit fields (only one bit at a time can be set) but
		// used for fast multi-type compares.
		enum NodeTypes
		{
			kUnknown				= 0x0001,
			kAttribute				= 0x0002,
			kText					= 0x0004,
			kCDATA					= 0x0008, // same as text but no string conversion on output
			kComment				= 0x0010,
			kProcessingInstruction	= 0x0020,
			kElement				= 0x0040
		};

		virtual int getClass() const = 0;

		virtual uint32 numAttributes() const { return 0; };
		virtual AtomArray *getAttributes() const { return 0; };
		virtual E4XNode *getAttribute(uint32 /*index*/) const { return NULL; };

		virtual uint32 numNamespaces() const { return 0; };
		virtual AtomArray *getNamespaces() const { return 0; };

		virtual uint32 numChildren()   const { return 0; };
		virtual E4XNode *_getAt(uint32 /*i*/) const { return 0; };

		virtual void clearChildren() {};
		virtual void setChildAt (uint32 /*i*/, E4XNode* /*x*/) {};
		virtual void insertChild (uint32 /*i*/, E4XNode* /*x*/) {};
		virtual void removeChild (uint32 /*i*/) {};
		virtual void convertToAtomArray() {};

 		bool hasSimpleContent() const;
 		bool hasComplexContent() const;
 		int32 childIndex() const;
 		String* nodeKind(Toplevel* toplevel) const;
 
		virtual void addAttribute (E4XNode *x);

		// Should this silently fail or assert?
		virtual void setNotification(AvmCore* /*core*/, FunctionObject* /*f*/, Namespacep /*publicNS*/) { return; }
		virtual FunctionObject* getNotification() const { return NULL; }

		// The following routines are E4X support routines
		
		// Private functions not exposed to AS
		// DeleteByIndex (PropertyName)
		// DeepCopy
		// ResolveValue
		// Descendants (PropertyName)
		// Equals (Value)
		// Insert (PropertyName, Value)
		// Replace (PropertyName, Value)
		// AddInScopeNamespace (Namespace)

		// Corresponds to [[Length]] in the docs
		virtual uint32 _length() const { return 0; };

		bool _equals(Toplevel* toplevel, AvmCore *core, E4XNode *value) const;

		void _deleteByIndex (uint32 entry);
		E4XNode *_deepCopy (AvmCore *core, Toplevel *toplevel, Namespacep publicNS) const;
		virtual void _insert (AvmCore *core, Toplevel *toplevel, uint32 entry, Atom value);
		virtual E4XNode* _replace (AvmCore *core, Toplevel *toplevel, uint32 entry, Atom value, Atom pastValue = 0);
		virtual void _addInScopeNamespace (AvmCore *core, Namespace *ns, Namespacep publicNS);
		virtual void _append (E4XNode* /*childNode*/) { AvmAssert(0); };
		// Extract a namespace from a tag name, and return the new tag name in tagName
		Namespace *FindNamespace(AvmCore *core, Toplevel *toplevel, Stringp& tagName, bool bAttribute);
		int FindMatchingNamespace(AvmCore *core, Namespace *ns);

		void BuildInScopeNamespaceList(AvmCore *core, AtomArray *list) const;
		void dispose();

		MMgc::GC *gc() const { return MMgc::GC::GetGC(this); }
	};

	class TextE4XNode : public E4XNode
	{
		DRCWB(Stringp) m_value;

	public:
		TextE4XNode (E4XNode *parent, String *value);

		int getClass() const { return kText; };
		Stringp getValue() const { return m_value; };
		void setValue (String *s) { m_value = s; }
	};

	class CommentE4XNode : public E4XNode
	{
		DRCWB(Stringp) m_value;

	public:
		CommentE4XNode (E4XNode *parent, String *value);

		int getClass() const { return kComment; };
		Stringp getValue() const { return m_value; };
		void setValue (String *s) { m_value = s; }
	};

	class AttributeE4XNode : public E4XNode
	{
		DRCWB(Stringp) m_value;

	public:
		AttributeE4XNode (E4XNode *parent, String *value);

		int getClass() const { return kAttribute; };
		Stringp getValue() const { return m_value; };
		void setValue (String *s) { m_value = s; }
	};

	class CDATAE4XNode : public E4XNode
	{
		DRCWB(Stringp) m_value;

	public:
		CDATAE4XNode (E4XNode *parent, String *value);

		int getClass() const { return kCDATA; };
		Stringp getValue() const { return m_value; };
		void setValue (String *s) { m_value = s; }
	};

	class PIE4XNode : public E4XNode
	{
		/** only when m_class != kElement */
		DRCWB(Stringp) m_value;

	public:
		PIE4XNode (E4XNode *parent, String *value);

		int getClass() const { return kProcessingInstruction; };
		Stringp getValue() const { return m_value; };
		void setValue (String *s) { m_value = s; }
	};

	// Currently this is 24-bytes in size
	class ElementE4XNode : public E4XNode
	{
		// This stores E4XNode pointers and NOT Atoms
		DWB(AtomArray *) m_attributes;

		// This stores Atoms (atom-ized Namespace pointers)
		DWB(AtomArray *) m_namespaces;
	
		// If the low bit of this integer is set, this value points directly
		// to a single child (one E4XNode *).  If there are multiple children,
		// this points to an AtomArray containing E4XNode pointers (NOT Atoms)
		DWB(uintptr) m_children;
		#define SINGLECHILDBIT 0x1

		friend class E4XNode;

	public:
		ElementE4XNode (E4XNode *parent);
		int getClass() const { return kElement; };

		uint32 numAttributes() const { return (m_attributes ? m_attributes->getLength() : 0); };
		AtomArray *getAttributes() const { return m_attributes; };
		E4XNode *getAttribute(uint32 index) const { return (E4XNode *)AvmCore::atomToGenericObject(m_attributes->getAt(index)); };
		void addAttribute (E4XNode *x);

		uint32 numNamespaces() const { return (m_namespaces ? m_namespaces->getLength() : 0); };
		AtomArray *getNamespaces() const { return m_namespaces; };

		uint32 numChildren()   const;// { return (m_children ? m_children->getLength() : 0); };

		void clearChildren();
		void setChildAt (uint32 i, E4XNode *x);
		#define SINGLECHILDBIT 0x1
		void insertChild (uint32 i, E4XNode *x);
		void removeChild (uint32 i);
		void convertToAtomArray();

		Stringp getValue() const { return 0; };
		void setValue (String *s) { (void)s; AvmAssert(s == 0); }

		void setNotification(AvmCore* core, FunctionObject* f, Namespacep publicNS);
		FunctionObject* getNotification() const;

		// E4X support routines below
		uint32 _length() const { return numChildren(); };
		E4XNode *_getAt(uint32 i) const;

		void _append (E4XNode *childNode);

		void _addInScopeNamespace (AvmCore *core, Namespace *ns, Namespacep publicNS);
		void _insert (AvmCore *core, Toplevel *toplevel, uint32 entry, Atom value);
		E4XNode* _replace (AvmCore *core, Toplevel *toplevel, uint32 entry, Atom value, Atom pastValue = 0);

		void CopyAttributesAndNamespaces(AvmCore *core, Toplevel *toplevel, XMLTag& tag, Namespacep publicNS);
	};
}
#endif /* __avmplus_E4XNode__ */
