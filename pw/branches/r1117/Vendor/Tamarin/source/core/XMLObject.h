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

#ifndef __avmplus_XMLObject__
#define __avmplus_XMLObject__


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
	class XMLObject : public ScriptObject
	{
		XMLClass* xmlClass() const
		{
			return toplevel()->xmlClass();
		}

	protected:
		DWB(E4XNode*) m_node;

		friend class XMLClass;

	public:

		E4XNode* getNode() const { return m_node; }
		void setNode(E4XNode* node) { m_node = node; }

		// Functions that override object version
		// Delete (deleteProperty)
		// Get (getProperty)
		// HasProperty 
		// Put (setProperty)
		Atom toString ();

		Atom callProperty(const Multiname* name, int argc, Atom* argv);

		Atom getAtomProperty(Atom name) const;		
		void setAtomProperty(Atom name, Atom value);
		bool deleteAtomProperty(Atom name);

		Atom getMultinameProperty(const Multiname* name) const;
		void setMultinameProperty(const Multiname* name, Atom value);
		bool deleteMultinameProperty(const Multiname* name);

		bool hasMultinameProperty(const Multiname* name) const;
		bool hasAtomProperty(Atom name) const;
		bool hasUintProperty(uint32 i) const;

		Atom getDescendants(const Multiname* name) const;

		Atom getUintProperty(uint32 i) const;
		void setUintProperty(uint32 i, Atom value);
		bool delUintProperty(uint32 i);

		// Iterator support - for in, for each
		Atom nextName(int index);
		Atom nextValue(int index);
		int nextNameIndex(int index);

		Atom _resolveValue ();

		// Exposed routines to AS (NATIVE_METHODs)
		XMLObject* AS3_addNamespace (Atom _namespace);
		XMLObject*  AS3_appendChild (Atom child);
		XMLListObject* AS3_attribute (Atom arg);
		XMLListObject* AS3_attributes ();
		XMLListObject* AS3_child (Atom propertyName);
		int AS3_childIndex();
		XMLListObject* AS3_children ();
		XMLListObject* AS3_comments ();
		bool AS3_contains (Atom value);
		XMLObject* AS3_copy ();
		XMLListObject* AS3_descendants (Atom PropertyName) const;
		XMLListObject* AS3_elements (Atom name); 
		bool XML_AS3_hasOwnProperty (Atom P);
		bool AS3_hasComplexContent ();
		bool AS3_hasSimpleContent ();
		ArrayObject* AS3_inScopeNamespaces ();
		Atom AS3_insertChildAfter (Atom child1, Atom child2);
		Atom AS3_insertChildBefore (Atom child1, Atom child2);

		// non-E4X extensions
		FunctionObject* AS3_notification();
		Atom AS3_setNotification(FunctionObject* f); // AS3 declaration sez this returns an Atom

		Atom AS3_localName ();
		Atom AS3_name ();
		Atom _namespace (Atom prefix, int argc); // prefix is optional (was previously called namespace)
		ArrayObject* AS3_namespaceDeclarations ();
		String* AS3_nodeKind () const;
		XMLObject* AS3_normalize ();
		Atom AS3_parent ();
		XMLListObject* AS3_processingInstructions (Atom name); 
		XMLObject* AS3_prependChild (Atom value);
		bool XML_AS3_propertyIsEnumerable(Atom P);	// NOT virtual, NOT an override
		XMLObject* AS3_removeNamespace (Atom _namespace);
		XMLObject* AS3_replace (Atom propertyName, Atom value);
		XMLObject* AS3_setChildren (Atom value);
		void AS3_setLocalName (Atom name);
		void AS3_setName (Atom name);
		void AS3_setNamespace (Atom ns);
		XMLListObject* AS3_text ();
		Stringp AS3_toString();
		String* AS3_toXMLString ();

		// inline wrappers for legacy code
		inline XMLObject* addNamespace (Atom _namespace) { return AS3_addNamespace (_namespace); }
		inline XMLObject*  appendChild (Atom child) { return AS3_appendChild (child); }
		inline XMLListObject* attribute (Atom arg) { return AS3_attribute (arg); }
		inline XMLListObject* attributes () { return AS3_attributes (); }
		inline XMLListObject* child (Atom propertyName) { return AS3_child (propertyName); }
		inline int childIndex() { return AS3_childIndex(); }
		inline XMLListObject* children () { return AS3_children (); }
		inline XMLListObject* comments () { return AS3_comments (); }
		inline bool contains (Atom value) { return AS3_contains (value); }
		inline XMLObject* copy () { return AS3_copy (); }
		inline XMLListObject* descendants (Atom PropertyName) const { return AS3_descendants (PropertyName); }
		inline XMLListObject* elements (Atom name) { return AS3_elements (name); } 
		inline bool hasOwnProperty (Atom P) { return XML_AS3_hasOwnProperty(P); }
		inline bool hasComplexContent () { return AS3_hasComplexContent (); }
		inline bool hasSimpleContent () { return AS3_hasSimpleContent (); }
		inline ArrayObject* inScopeNamespaces () { return AS3_inScopeNamespaces (); }
		inline Atom insertChildAfter (Atom child1, Atom child2) { return AS3_insertChildAfter (child1, child2); }
		inline Atom insertChildBefore (Atom child1, Atom child2) { return AS3_insertChildBefore (child1, child2); }

		// non-E4X extensions
		inline FunctionObject* notification() { return AS3_notification(); }
		inline void setNotification(FunctionObject* f) { AS3_setNotification(f); }

		inline Atom localName () { return AS3_localName (); }
		inline Atom name () { return AS3_name (); }
		inline ArrayObject* namespaceDeclarations () { return AS3_namespaceDeclarations (); }
		inline String* nodeKind () const { return AS3_nodeKind (); }
		inline XMLObject* normalize () { return AS3_normalize (); }
		inline Atom parent () { return AS3_parent (); }
		inline XMLListObject* processingInstructions (Atom name) { return AS3_processingInstructions (name); } 
		inline XMLObject* prependChild (Atom value) { return AS3_prependChild (value); }
		inline bool propertyIsEnumerable (Atom P) { return XML_AS3_propertyIsEnumerable(P); }
		inline XMLObject* removeNamespace (Atom _namespace) { return AS3_removeNamespace (_namespace); }
		inline XMLObject* replace (Atom propertyName, Atom value) { return AS3_replace (propertyName, value); }
		inline XMLObject* setChildren (Atom value) { return AS3_setChildren (value); }
		inline void setLocalName (Atom name) { return AS3_setLocalName (name); }
		inline void setName (Atom name) { return AS3_setName (name); }
		inline void setNamespace (Atom ns) { return AS3_setNamespace (ns); }
		inline XMLListObject* text () { return AS3_text (); }
		inline String* toXMLString () { return AS3_toXMLString (); }

		// E4X support routines
		void __toXMLString(StringBuffer &s, AtomArray *AncestorNamespace, int indentLevel = 0, bool includeChildren = true) const;
		XMLObject* _deepCopy () const;

		Namespace *GenerateUniquePrefix (Namespace *ns, const AtomArray *namespaces) const;

		static bool notifyNeeded(E4XNode* target);
		void issueNotifications(AvmCore* core, Toplevel* top, E4XNode* initialTarget, Atom target, Stringp type, Atom value, Atom detail=undefinedAtom);

		void childChanges(Stringp type, Atom value, E4XNode* prior=0);
		void nonChildChanges(Stringp type, Atom value, Atom detail=undefinedAtom);

		// accessors to node functions
		int getClass() const; 
		uint32 _length() const;
		XMLObject* getParent();
		void setValue(Stringp s);
		Stringp getValue();
		bool getQName(Multiname *m);

		Namespace *GetNamespace (const Multiname &mn, const AtomArray *nsArray) const;

#ifdef XML_FILTER_EXPERIMENT
		XMLListObject* filter (Atom propertyName, Atom value);
		void _filter (XMLListObject* , const Multiname &m, Atom value);
#endif
		void dispose();

	public:
		XMLObject(XMLClass *type, Stringp s=NULL, Namespace *defaultNamespace=NULL);
		XMLObject(XMLClass *type, E4XNode *node);
		
		~XMLObject();

#ifdef AVMPLUS_VERBOSE
	public:
		Stringp format(AvmCore* core) const;
#endif
	private:
		/**
		 * Conversion routine to verify XML related flags of Multiname
		 * (strips @ from strings and marks multiname as attribute)
		 */
		void CoerceE4XMultiname(const Multiname *m, Multiname &out) const;
		bool NodeNameEquals(Stringp nodeName, int32_t nodeNameStart, Stringp parentName, Namespace *ns);
		Namespacep publicNS;
		DECLARE_SLOTS_XMLObject;
	};

	/**
	 * QNameObject is used to represent the "QName" object in the E4X Specification
	 *
	 * We also use this same object to represent "AttributeName" in the E4X spec.
	 * An AttributeName is simply a QName wrapper for finding properties that have a leading @ sign.
	 * It's an internal class to the spec and the only difference between a QName is the @.  Instead of
	 * having the overhead of an AttributeName class that wraps the QName class, we just use a boolean
	 * inside the QName to differentiate betweent the two types.
	 */
	class QNameObject : public ScriptObject
	{
		XMLClass* xmlClass() const
		{
			return toplevel()->xmlClass();
		}

		HeapMultiname m_mn;
		friend class QNameClass;

	public:
		QNameObject(QNameClass *type, const Multiname &mn);
		QNameObject(QNameClass *type, Atom name, bool bAttribute=false);
		QNameObject(QNameClass *type, Namespace *nameSpace, Atom name, bool bAttribute=false);

		Atom getURI() const;
		Stringp get_localName() const;
		Atom get_uri() const;

		bool isAttr() const { return m_mn.isAttr(); };

		// Iterator support - for in, for each
		Atom nextName(int index);
		Atom nextValue(int index);
		int nextNameIndex(int index);

		void getMultiname(Multiname& name) const
		{
			name = m_mn;
		}
		
		DECLARE_SLOTS_QNameObject;
	};
}
#endif /* __avmplus_XMLObject__ */
