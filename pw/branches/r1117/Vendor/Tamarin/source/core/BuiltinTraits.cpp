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
 * Portions created by the Initial Developer are Copyright (C) 1993-2006
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

namespace avmplus
{
	BuiltinTraits::BuiltinTraits()
	{
		VMPI_memset(this, 0, sizeof(BuiltinTraits));
	}

	// this is called after core types are defined.  we don't want to do
	// it earlier because we need Void and int
	void BuiltinTraits::initInstanceTypes(PoolObject* pool)
	{
		AvmCore* core = pool->core;

		Namespacep publicNS = core->getPublicNamespace(ApiUtils::getSmallestAPI());

		null_itraits = Traits::newTraits(pool, NULL, 0, 0, 0, TRAITSTYPE_NVA);
		null_itraits->set_names(publicNS, core->internConstantStringLatin1("null"));
		null_itraits->final = true;
		null_itraits->builtinType = BUILTIN_null;
		null_itraits->resolveSignatures(NULL);

		void_itraits = Traits::newTraits(pool, NULL, 0, 0, 0, TRAITSTYPE_NVA);
		void_itraits->set_names(publicNS, core->internConstantStringLatin1("void"));
		void_itraits->final = true;
		void_itraits->builtinType = BUILTIN_void;
		void_itraits->resolveSignatures(NULL);

#define DO_BUILTIN(nm, clsnm)	do { nm##_itraits = pool->getBuiltinTraits(core->internConstantStringLatin1(clsnm)); nm##_itraits->builtinType = BUILTIN_##nm; } while (0)
		DO_BUILTIN(array, "Array");
		DO_BUILTIN(boolean, "Boolean");
		DO_BUILTIN(class, "Class");
		DO_BUILTIN(date, "Date");
		DO_BUILTIN(error, "Error");
		DO_BUILTIN(function, "Function");
		DO_BUILTIN(int, "int");
		DO_BUILTIN(math, "Math");
		DO_BUILTIN(methodClosure, "MethodClosure");
		DO_BUILTIN(namespace, "Namespace");
//		DO_BUILTIN(null, "FOO");		// handled above
		DO_BUILTIN(number, "Number");
//		DO_BUILTIN(object, "FOO");		// can't do yet, handled elsewhere
		DO_BUILTIN(qName, "QName");
		DO_BUILTIN(regexp, "RegExp");
		DO_BUILTIN(string, "String");
		DO_BUILTIN(uint, "uint");
		DO_BUILTIN(vector, "Vector");
		DO_BUILTIN(vectordouble, "Vector$double");
		DO_BUILTIN(vectorint, "Vector$int");
		DO_BUILTIN(vectorobj, "Vector$object");
		DO_BUILTIN(vectoruint, "Vector$uint");
//		DO_BUILTIN(void, "FOO");		// handled above
		DO_BUILTIN(xmlList, "XMLList");
		DO_BUILTIN(xml, "XML");
#undef DO_BUILTIN

		// we have fast equality checks in the core that only work
		// because these two classes are final.  If they become non-final
		// then these checks need to be updated to account for possible
		// subclassing.
		AvmAssert(xml_itraits->final);
		AvmAssert(xmlList_itraits->final);

		// XML and XMLList are dynamic but do not need the
		// standard dynamic hash table
		xml_itraits->set_needsHashtable(false);
		xmlList_itraits->set_needsHashtable(false);

		// set the types that don't have custom construct (default is true)
//		array_itraits->hasCustomConstruct           = true;
//		boolean_itraits->hasCustomConstruct         = true;
//		class_itraits->hasCustomConstruct           = true;
//		date_itraits->hasCustomConstruct            = true;
		error_itraits->hasCustomConstruct           = false;
//		function_itraits->hasCustomConstruct  		= true;
//		int_itraits->hasCustomConstruct             = true;
//		math_itraits->hasCustomConstruct            = true;
		methodClosure_itraits->hasCustomConstruct  	= false;
//		namespace_itraits->hasCustomConstruct  		= true;
//		null_itraits->hasCustomConstruct            = true;
//		number_itraits->hasCustomConstruct  		= true;
//		object_itraits->hasCustomConstruct  		= true;
//		qName_itraits->hasCustomConstruct           = true;
//		regexp_itraits->hasCustomConstruct  		= true;
//		string_itraits->hasCustomConstruct  		= true;
//		uint_itraits->hasCustomConstruct            = true;
		vector_itraits->hasCustomConstruct  		= false;
		vectordouble_itraits->hasCustomConstruct  	= false;
		vectorint_itraits->hasCustomConstruct  		= false;
		vectorobj_itraits->hasCustomConstruct  		= false;
		vectoruint_itraits->hasCustomConstruct  	= false;
//		void_itraits->hasCustomConstruct            = true;
//		xmlList_itraits->hasCustomConstruct  		= true;
//		xml_itraits->hasCustomConstruct             = true;


		vectordouble_itraits->set_names(vectordouble_itraits->ns(), core->internConstantStringLatin1("Vector.<Number>"));
		vectorint_itraits->set_names(vectorint_itraits->ns(), core->internConstantStringLatin1("Vector.<int>"));
		vectoruint_itraits->set_names(vectoruint_itraits->ns(), core->internConstantStringLatin1("Vector.<uint>"));
		vectorobj_itraits->set_names(vectorobj_itraits->ns(), core->internConstantStringLatin1("Vector.<*>"));

		object_istc = ScopeTypeChain::createEmpty(core->GetGC(), object_itraits);
		class_istc = ScopeTypeChain::createEmpty(core->GetGC(), class_itraits);
	}

	void BuiltinTraits::initClassTypes(PoolObject* pool)
	{
		math_ctraits = findCTraits("Math$", pool);
		number_ctraits = findCTraits("Number$", pool);
		int_ctraits = findCTraits("int$", pool);
		uint_ctraits = findCTraits("uint$", pool);
		boolean_ctraits = findCTraits("Boolean$", pool);
		string_ctraits = findCTraits("String$", pool);
		vector_ctraits = findCTraits("Vector$", pool);
	}

	Traits* BuiltinTraits::findCTraits(const char* cname, PoolObject* pool)
	{
		Stringp name = pool->core->internConstantStringLatin1(cname);
		for (uint32_t i=0, n=pool->classCount(); i < n; i++) 
		{
			Traits* ctraits = pool->getClassTraits(i);
			if (ctraits && ctraits->name() == name) 
			{
				return ctraits;
			}
		}
		return NULL;
	}
}
