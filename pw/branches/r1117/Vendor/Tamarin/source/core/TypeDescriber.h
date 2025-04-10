/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: t; tab-width: 4 -*- */
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
 * Portions created by the Initial Developer are Copyright (C) 2008
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

#ifndef __avmplus_TypeDescriber__
#define __avmplus_TypeDescriber__

namespace avmplus
{
	class TypeDescriber
	{
	public:
		TypeDescriber(Toplevel* toplevel);
		
		enum Flags
		{
			// this bit replicates a bug in Flash9/10, where a method that uses a custom namespace
			// won't be in the output if any of its base classes (or interfaces) also define a method
			// in that custom namespace.
			HIDE_NSURI_METHODS		= 0x0001,
			INCLUDE_BASES			= 0x0002,
			INCLUDE_INTERFACES		= 0x0004,
			INCLUDE_VARIABLES		= 0x0008,
			INCLUDE_ACCESSORS		= 0x0010,
			INCLUDE_METHODS			= 0x0020,
			INCLUDE_METADATA		= 0x0040,
			INCLUDE_CONSTRUCTOR		= 0x0080,
			INCLUDE_TRAITS			= 0x0100,
			USE_ITRAITS				= 0x0200,
			HIDE_OBJECT				= 0x0400
		};
		ScriptObject* describeType(Atom value, uint32_t flags);
		Stringp getQualifiedClassName(Atom value);
		Stringp getQualifiedSuperclassName(Atom value);

	private:
		enum StringId
		{
			kstrid_access,
			kstrid_accessors,
			kstrid_asterisk,
			kstrid_bases,
			kstrid_constructor,
			kstrid_declaredBy,
			kstrid_emptyString,
			kstrid_interfaces,
			kstrid_isDynamic,
			kstrid_isFinal,
			kstrid_isStatic,
			kstrid_key,
			kstrid_metadata,
			kstrid_method,
			kstrid_methods,
			kstrid_name,
			kstrid_native,
			kstrid_optional,
			kstrid_parameters,
			kstrid_readonly,
			kstrid_readwrite,
			kstrid_returnType,
			kstrid_traits,
			kstrid_type,
			kstrid_uri,
			kstrid_value,
			kstrid_variables,
			kstrid_writeonly,
			maxStringId
		};

		struct KVPair 
		{
			StringId keyid;
			Atom value;
		};

	private:
	
		Traits* chooseTraits(Atom value, uint32_t flags);
		ScriptObject* new_object();
		ArrayObject* new_array();
		Traitsp getTraits(Atom value);
		Stringp describeClassName(Traitsp traits);
		ScriptObject* describeTraits(Traitsp traits, uint32_t flags, Toplevel* toplevel);
		ArrayObject* describeParams(MethodInfo* mi, MethodSignaturep ms);
		void addDescribeMetadata(ArrayObject* a, PoolObject* pool, const uint8_t* meta_pos);
		ScriptObject* describeMetadataInfo(PoolObject* pool, uint32_t metadata_index);
		Stringp poolstr(PoolObject* pool, uint32_t index);
		void setpropmulti(ScriptObject* o, const KVPair* kv, uint32_t count);
		Stringp str(StringId i);
		static void addBindings(AvmCore* core, MultinameHashtable* bindings, TraitsBindingsp tb, uint32_t flags);
		
	private:
		Toplevel* m_toplevel;
		Stringp m_strs[maxStringId];
	};
}

#endif /* __avmplus_TypeDescriber__ */
