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

#ifndef __avmplus_Multiname__
#define __avmplus_Multiname__


namespace avmplus
{
	#ifdef FEATURE_NANOJIT
	class CodegenLIR;
	#endif

	/**
	 * Multiname is a reference to an identifier in 0 or more namespaces.  It consists
	 * of the simple name and a list of namespaces.
	 * 
	 * Multinames are always stack allocated.  Namespace and name values are interened, since
	 * they are used as hashtable keys.  
	 */
	class Multiname 
	{
		const static int32_t ATTR   = 0x01;	// attribute name
		const static int32_t QNAME  = 0x02;	// qualified name (size==1, explicit in code)
		const static int32_t RTNS   = 0x04;	// runtime namespace
		const static int32_t RTNAME = 0x08;	// runtime name
		const static int32_t NSSET  = 0x10;
		const static int32_t TYPEPARAM = 0x20;
		#ifdef FEATURE_NANOJIT
		friend class CodegenLIR;
		#endif 
		friend class HeapMultiname;

		Stringp name;
		union
		{
			Namespacep ns;
			NamespaceSetp nsset;
		};
		int32_t flags;
		uint32_t next_index;

	public:
		Multiname();
		Multiname(NamespaceSetp nsset);
		Multiname(const Multiname &other);
		Multiname(Namespacep ns, Stringp name);
		Multiname(Namespacep ns, Stringp name, bool qualified);
		~Multiname();

		Stringp getName() const;
		void setName(Stringp _name);
		void setName(const Multiname* other);
		int32_t namespaceCount() const;
		Namespacep getNamespace(int32_t i) const;
		Namespacep getNamespace() const;
		void setNamespace(Namespacep _ns);
		void setNamespace(const Multiname* other);
		NamespaceSetp getNsset() const;
		void setNsset(NamespaceSetp _nsset);
		uint32_t getTypeParameter() const;
		void setTypeParameter(uint32_t index);

		bool contains(Namespacep ns) const;
	    bool containsAnyPublicNamespace() const;
		bool isValidDynamicName() const;		

		/**
		 * return the flags we want to keep when copying a compile-time
		 * multiname into a runtime temporary multiname
		 */
		int32_t ctFlags() const;

		/**
		 * returns true if this multiname could resolve to a binding.  Attributes,
		 * wildcards, and runtime parts mean it can't match any binding.
		 */
		int32_t isBinding() const;

		int32_t isRuntime() const;
		int32_t isRtns() const;
		int32_t isRtname() const;
		int32_t isQName() const;
		bool isAttr() const;
		bool isAnyName() const;
		bool isAnyNamespace() const;
		int32_t isNsset() const;
		int32_t isParameterizedType() const;

		void setAttr(bool b=true);
		void setQName();
		void setRtns();
		void setRtname();
		void setAnyName();
		void setAnyNamespace();
		bool matches(const Multiname *mn) const;

#ifdef VMCFG_PRECOMP_NAMES
		// As an optimization a Multiname may be part of a GCRoot.  The following
		// two methods make sure the reference counted dependents of a Multiname
		// stick around (or not, as the case may be).  The reference counts are
		// *not* adjusted by the methods above; multinames on which IncrementRef
		// and DecrementRef are called *must* be considered constant.
	public:
		void IncrementRef();
		void DecrementRef();
#endif
		
//#ifdef AVMPLUS_VERBOSE
	public:
		typedef enum _MultiFormat
		{
			MULTI_FORMAT_FULL = 0,		/* default */
			MULTI_FORMAT_NAME_ONLY,     /* only name */
			MULTI_FORMAT_NS_ONLY		/* only namespaces */
		}
		MultiFormat;

		Stringp format(AvmCore* core, MultiFormat form=MULTI_FORMAT_FULL) const;
		static Stringp format(AvmCore* core, Namespacep ns, Stringp name, bool attr=false, bool hideNonPublicNamespaces=true);
//#endif
	};

	// version of multiname sporting write barriers
	// NOTE NOTE NOTE
	// This is embedded into other GCObjects, it's not a GCObject by itself
	class HeapMultiname 
	{
	public:

		explicit HeapMultiname();
		explicit HeapMultiname(const Multiname& other);
		~HeapMultiname();

		operator const Multiname* () const;
		operator const Multiname& () const;
		const HeapMultiname& operator=(const HeapMultiname& that);
		const HeapMultiname& operator=(const Multiname& that);

		Stringp getName() const;
		int32_t namespaceCount() const;
		Namespacep getNamespace(int32_t i) const;
		Namespacep getNamespace() const;
		NamespaceSetp getNsset() const;
		bool contains(Namespacep ns) const;
		int32_t ctFlags() const;
		int32_t isBinding() const;
		int32_t isRuntime() const;
		int32_t isRtns() const;
		int32_t isRtname() const;
		int32_t isQName() const;
		bool isAttr() const;
		bool isAnyName() const;
		bool isAnyNamespace() const;
		int32_t isNsset() const;
		bool matches(const Multiname *mn) const;

//#ifdef AVMPLUS_VERBOSE
	public:
		Stringp format(AvmCore* core, Multiname::MultiFormat form=Multiname::MULTI_FORMAT_FULL) const;
		static Stringp format(AvmCore* core, Namespacep ns, Stringp name, bool attr=false, bool hideNonPublicNamespaces=true);
//#endif
	private:
        Multiname name;
		MMgc::GC* gc() const;

	private:
		void setMultiname(const Multiname& other);

	private:
		explicit HeapMultiname(const HeapMultiname& toCopy); // unimplemented
	};
}

#endif /* __avmplus_Multiname__ */
