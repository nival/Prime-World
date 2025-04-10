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

#ifndef __avmplus_Toplevel__
#define __avmplus_Toplevel__


namespace avmplus
{
	class IntVectorClass;
	class UIntVectorClass;
	class DoubleVectorClass;
	class ObjectVectorClass;
	class VectorClass;

	/**
	 * class Toplevel
	 */
    class Toplevel : public MMgc::GCFinalizedObject
    {
	public:
		Toplevel(AbcEnv*);
		virtual ~Toplevel() {} // silence compiler warnings
		
		AbcEnv* abcEnv() const;
		DomainEnv* domainEnv() const;
		AvmCore* core() const;
		MMgc::GC* gc() const;
		ScriptObject* global() const;
		Atom atom() const;
		ScriptEnv* mainEntryPoint() const;

		DateClass* dateClass();
		RegExpClass* regexpClass();
		XMLClass* xmlClass();
		XMLListClass* xmlListClass();
		QNameClass* qnameClass();
		/**
		 * @name Error Subclasses
		 * These are subclasses of Error used in the VM.
		 */
		/*@{*/
		ErrorClass* errorClass() const;
		ErrorClass* argumentErrorClass() const;
		ErrorClass* evalErrorClass() const;
		ErrorClass* typeErrorClass() const;
		ErrorClass* rangeErrorClass() const;
		ErrorClass* uriErrorClass() const;
		ErrorClass* referenceErrorClass() const;
		ErrorClass* securityErrorClass() const;
		ErrorClass* syntaxErrorClass() const;
		ErrorClass* verifyErrorClass() const;
		/*@}*/

		void throwVerifyError(int id) const;
		void throwVerifyError(int id, Stringp arg1) const;
		void throwVerifyError(int id, Stringp arg1, Stringp arg2) const;

		void throwTypeError(int id) const;
		void throwTypeError(int id, Stringp arg1) const;
		void throwTypeError(int id, Stringp arg1, Stringp arg2) const;
		void throwTypeErrorWithName(int id, const char* namestr) const;

		void throwError(int id) const;
		void throwError(int id, Stringp arg1) const;
		void throwError(int id, Stringp arg1, Stringp arg2) const;

		void throwArgumentError(int id) const;
		void throwArgumentError(int id, Stringp arg1) const;
		void throwArgumentError(int id, const char *arg1) const;
		void throwArgumentError(int id, Stringp arg1, Stringp arg2) const;

		void throwRangeError(int id) const;
		void throwRangeError(int id, Stringp arg1) const;
		void throwRangeError(int id, Stringp arg1, Stringp arg2) const;
		void throwRangeError(int id, Stringp arg1, Stringp arg2, Stringp arg3) const;

		void throwReferenceError(int id, const Multiname* multiname, const Traits* traits) const;
		void throwReferenceError(int id, const Multiname* multiname) const;

		void throwReferenceError(int id, const Multiname& multiname, const Traits* traits) const;
		void throwReferenceError(int id, const Multiname& multiname) const;

		inline Toplevel* toplevel() { return this; }
		inline const Toplevel* toplevel() const { return this; }

		// 
		// methods that used to be on AvmCore but depend on the caller's environment
		//
		ScriptObject* toPrototype(Atom atom);
		VTable* toVTable(Atom atom);

		/** toObject + get traits */
		Traits*        toTraits(Atom atom);
		
		/**
		 * OP_call.
		 *
		 * this = atomv[0]
		 * arg1 = atomv[1]
		 * argN = atomv[argc]
		 */
		Atom op_call(Atom method,
					 int argc,
					 Atom* atomv);

		/**
		 * OP_construct.
		 *
		 * this = atomv[0] (ignored)
		 * arg1 = atomv[1]
		 * argN = atomv[argc]
		 */
		Atom op_construct(Atom ctor,
						  int argc,
						  Atom* atomv);


		/** Implementation of OP_callproperty */
		Atom callproperty(Atom base, const Multiname* name, int argc, Atom* atomv, VTable* vtable);

		/** Implementation of OP_constructprop */
		Atom constructprop(const Multiname* name, int argc, Atom* atomv, VTable* vtable);
		
		/**
		* OP_applytype.
		*
		* arg1 = atomv[0]
		* argN = atomv[argc-1]
		*/
		Atom op_applytype(Atom obj,
			int argc,
			Atom* atomv);

		/**
		 * Implements the ToAttributeName API as specified in E4X 10.5.1, pg 37
		 */
		QNameObject* ToAttributeName (Atom arg);
		QNameObject* ToAttributeName (const Stringp arg);

		/**
		 * Implements the ToXMLName API as specified in E4X 10.6.1, page 38
		 */
		void ToXMLName (const Atom arg, Multiname& m);

		/**
		 * E4X support for coercing regular Multinames into E4X specific ones
		 */
		void CoerceE4XMultiname (const Multiname *m, Multiname &out);

		/**
		 * operator instanceof from ES3
		 */
		Atom instanceof(Atom atom, Atom ctor);

		/** returns the instance traits of the factorytype of the passed atom */
		Traits* toClassITraits(Atom atom);

		/**
		 * operator in from ES3
		 */
		Atom in_operator(Atom name, Atom obj);

	public:
		/** legacy wrapper around coerce() from instr.h */
		Atom coerce(Atom atom, Traits* expected) const;

		/**
		 * Reads a property from an object, with the property
		 * to retrieve specified by its binding.
		 * The binding was likely retrieved using getBinding.
		 * @param obj Object to retrieve property from
		 * @param b The binding of the property
		 * @param traits The traits of the object
		 */
		Atom getproperty(Atom obj, const Multiname* name, VTable* vtable);

		/**
		 * Determines if a specified object has a specified property
		 * where the property is specified by a multiname.
		 * @param obj Object on which to look for the property
		 * @param multiname The name of the property
		 * @param vtable The vtable of the object
		 * @return	true if the object has a readable property with the
					specified name, false otherwise.
		 */
		bool hasproperty(Atom obj, const Multiname* multiname, VTable* vtable);

	    /**
		 * Delete a specified property on a specified object,where the property is specified
		 * by a multiname.
		 * @param obj Object on which to look for the specified property.
		 * @param multiname The name of the property
		 * @param vtable The vtable of the object
		 * @return	true if the property is deleted. false if the property cannot be deleted.
		 */
		bool deleteproperty( Atom obj, const Multiname* multiname, VTable* vtable ) const;

	    void setproperty(Atom obj, const Multiname* multiname, Atom value, VTable* vtable) const;
	    void setproperty_b(Atom obj, const Multiname* multiname, Atom value, VTable* vtable, Binding b) const;

		/**
		 * operator +
		 */
		Atom add2(Atom lhs, Atom rhs);

		/**
		 * Implements the GetDefaultNamespace API as specified in E4X 12.1.1, pg 59
		 *
		 */
		Namespace *getDefaultNamespace();

		/**
		 * Retrieve a binding for a property of a class.
		 * This differs from the other overload of getBinding
		 * in that it takes a multiname instead of a name/ns
		 * pair.
		 * The returned binding can then be used to read/write
		 * the property 
		 * @param traits    The traits of the class
		 * @param multiname The multiname of the property
		 */
		Binding getBinding(Traits* traits, const Multiname* multiname) const;
		
		// like getBinding, but do extra work to find the initial declarer of the member
		Binding getBindingAndDeclarer(Traits* traits, const Multiname& multiname, Traitsp& declarer) const;

		/**
		 * @name ECMA-262 Appendix B.2 extensions
		 * Extensions to ECMAScript, in ECMA-262 Appendix B.2
		 */
		/*@{*/
		static Stringp escape(ScriptObject*, Stringp in);
		static Stringp unescape(ScriptObject*, Stringp in);
		/*@}*/

		/**
		 * E262-3 eval, but for the top level only (no lexical capture)
		 */
		static Atom eval(ScriptObject*, Atom in);
		
		/**
		 * This is a variant of escape() which doesn't encode
		 * Unicode characters using the %u sequence
		 */
		Stringp escapeBytes(Stringp in);

		/**
		 * @name Toplevel Function Properties
		 * Function properties of the global object (ECMA 15.1.2)
		 */
		/*@{*/
		static Stringp decodeURI(ScriptObject*, Stringp uri);
		static Stringp decodeURIComponent(ScriptObject*, Stringp uri);
		static Stringp encodeURI(ScriptObject*, Stringp uri);
		static Stringp encodeURIComponent(ScriptObject*, Stringp uri);
		static bool isNaN(ScriptObject*, double d);
		static bool isFinite(ScriptObject*, double d);
		static double parseInt(ScriptObject*, Stringp in, int radix);
		static double parseFloat(ScriptObject*, Stringp in);
		/*@}*/

		// For E4X
		static bool isXMLName(ScriptObject*, Atom v);

        ClassClosure* getBuiltinClass(int class_id) const;
		ErrorClass* getErrorClass(int class_id) const { return (ErrorClass*)getBuiltinClass(class_id); }

		unsigned int readU30(const byte *&p) const;

		// implementations supporting any of our extensions should override this
		virtual ClassClosure *getBuiltinExtensionClass(int clsid);

		// subclasses can override this to check for security violations
		// and prohibit certain operations. default implementation always
		// allows but FlashPlayer takes advantage of this.
		virtual bool sampler_trusted(ScriptObject* /*sampler*/);

	protected:
		ClassClosure* findClassInPool(int class_id, PoolObject* pool);

	private:

		static int parseHexChar(wchar c);
		static Stringp decode(AvmCore* core, Stringp in, bool decodeURIComponentFlag);
		static Stringp encode(AvmCore* core, Stringp in, bool encodeURIComponentFlag);

		static const uint32 unescaped[];
		static const uint32 uriUnescaped[];
		static const uint32 uriReservedPlusPound[];
		
		static bool contains(const uint32 *uriSet, uint32 ch);

		ClassClosure* resolveBuiltinClass(int class_id);

	// ------------------------ DATA SECTION BEGIN
	private:
		DWB(AbcEnv*)				_abcEnv;
		DWB(ClassClosure**)			_builtinClasses;
		DRCWB(ScriptObject*)		_global; // the toplevel script that's run
	public:
		DWB(VTable*)				object_ivtable;
		DWB(VTable*)				class_ivtable;
		DWB(ScopeChain*)			object_cscope;
		DWB(ScopeChain*)			vectorobj_cscope;
		DWB(ScopeChain*)			vectorobj_iscope;
		DWB(ScopeChain*)			toplevel_scope;
	public:
		DRCWB(ArrayClass*)			arrayClass;
		DRCWB(BooleanClass*)		booleanClass;
		DRCWB(ClassClass*)			classClass;
		DRCWB(FunctionClass*)		functionClass;		
		DRCWB(MethodClosureClass*)  methodClosureClass;		
		DRCWB(NamespaceClass*)		namespaceClass;
		DRCWB(NumberClass*)			numberClass;
		DRCWB(IntClass*)			intClass;
		DRCWB(UIntClass*)			uintClass;
		DRCWB(ObjectClass*)			objectClass;
		DRCWB(IntVectorClass*)		intVectorClass;
		DRCWB(DoubleVectorClass*)	doubleVectorClass;
		DRCWB(UIntVectorClass*)		uintVectorClass;
		DRCWB(ObjectVectorClass*)	objectVectorClass;
		DRCWB(VectorClass*)			vectorClass;
		DRCWB(StringClass*)			stringClass;
	// ------------------------ DATA SECTION END
	};
}

#endif /* __avmplus_Toplevel__ */
