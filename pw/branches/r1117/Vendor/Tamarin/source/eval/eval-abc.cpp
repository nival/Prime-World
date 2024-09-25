/* -*- tab-width: 4 -*- */
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


#include "avmplus.h"

#ifdef VMCFG_EVAL

#include "eval.h"

namespace avmplus
{
	namespace RTC
	{
		using namespace ActionBlockConstants;

		template<class T> static uint32_t computeSize(Seq<T>* xs) 
		{
			uint32_t size = 0;
			for ( ; xs != NULL ; xs = xs->tl )
				size += xs->hd->size();
			return size;
		}

		template<class T> static uint8_t* serializeSeq(uint8_t* b, Seq<T>* xs)
		{
			for ( ; xs != NULL ; xs = xs->tl )
				b = xs->hd->serialize(b);
			return b;
		}

		template<class T> static uint32_t length(Seq<T>* xs)
		{
			uint32_t n = 0;
			for ( ; xs != NULL ; xs = xs->tl )
				n++;
			return n;
		}

		static uint8_t* emitBytes(uint8_t* buf, ByteBuffer * const src)
		{
			uint32_t nbytes = src->size();
			src->serialize(buf);
			return buf + nbytes;
		}

		// Never called, but gcc gets very annoyed if a class with virtual methods does not
		// have a virtual destructor.
		ABCChunk::~ABCChunk()
		{
		}
		
		ABCFile::ABCFile(Compiler* compiler)
			: major_version(46)
			, minor_version(16)
			, NO_VALUE(~0U)
			, compiler(compiler)
			, allocator(compiler->allocator)
			, intCount(1)	    // entry 0 not present
			, uintCount(1)	    // entry 0 not present
			, doubleCount(1)    // entry 0 not present
			, stringCount(1)    // entry 0 not present
			, namespaceCount(1) // entry 0 not present
			, nssetCount(1)     // entry 0 not present
			, multinameCount(1) // entry 0 not present
			, methodCount(0)
			, metadataCount(0)
			, instanceCount(0)
			, classCount(0)
			, scriptCount(0)
			, methodbodyCount(0)
			, intBuf(allocator, 16)
			, uintBuf(allocator, 16)
			, doubleBuf(allocator, 32)
			, stringBuf(allocator)
			, namespaceBuf(allocator, 16)
			, nssetBuf(allocator, 16)
			, multinameBuf(allocator, 16)
			, namespaces(allocator)
			, namespaceSets(allocator)
			, multinames(allocator)
			, methods(allocator)
			, metadatas(allocator)
			, instances(allocator)
			, classes(allocator)
			, scripts(allocator)
			, bodies(allocator)
		{
		}
		
		uint32_t ABCFile::addInt(int32_t i)
		{
			intBuf.emitS32(i);
			return intCount++;
		}
		
		uint32_t ABCFile::addUInt(uint32_t u)
		{
			uintBuf.emitU32(u);
			return uintCount++;
		}
		
		uint32_t ABCFile::addDouble(double d)
		{
			doubleBuf.emitDouble(d);
			return doubleCount++;
		}
		
		uint32_t ABCFile::addString(Str* s)
		{
			if (s->ident == ~0U) {
				s->ident = stringCount++;
				uint32_t len = utf8length(s);
				stringBuf.emitU30(len);
				stringBuf.emitUtf8(len, s);
			}
			return s->ident;
		}
		
		uint32_t ABCFile::addString(const char* s)
		{
			return addString(compiler->intern(s));
		}

		uint32_t ABCFile::addNamespace(uint8_t kind, uint32_t name)
		{
			uint32_t i;
			Seq<ABCNamespaceInfo*>* nss;
			for ( nss = namespaces.get(), i=1 ; nss != NULL ; nss = nss->tl, i++ )
				 if (nss->hd->kind == kind && nss->hd->name == name)
					 return i;
			namespaceBuf.emitU8(kind);
			namespaceBuf.emitU30(name);
			namespaces.addAtEnd(ALLOC(ABCNamespaceInfo, (kind, name)));
			return namespaceCount++;
		}

		uint32_t ABCFile::addNsset(Seq<uint32_t>* nss)
		{
			uint32_t length = 0;
			uint32_t i, j;
			Seq<uint32_t>* tmp;
			
			for ( tmp=nss ; tmp != NULL ; tmp=tmp->tl)
				length++;

			Seq<ABCNamespaceSetInfo*>* nsss;
			for ( nsss = namespaceSets.get(), i=1 ; nsss != NULL ; nsss = nsss->tl, i++ ) {
				if (length == nsss->hd->length) {
					for ( tmp=nss, j=0 ; j < length ; tmp=tmp->tl, j++ )
						if (nsss->hd->ns[j] != tmp->hd)
							goto loop_end;
					return i;
				}
			}
		loop_end:

			ABCNamespaceSetInfo* info = new (allocator->alloc(sizeof(ABCNamespaceSetInfo) + (length-1)*sizeof(uint32_t))) ABCNamespaceSetInfo(length);
			nssetBuf.emitU30(length);
			for ( tmp=nss, j=0 ; tmp != NULL ; tmp=tmp->tl ) {
				info->ns[j] = tmp->hd;
				nssetBuf.emitU30(tmp->hd);
			}
			
			return nssetCount++;
		}

		uint32_t ABCFile::multinameLookup(uint8_t kind, uint32_t ns_or_nsset, uint32_t name) 
		{
			Seq<ABCMultinameInfo*>* mns;
			uint32_t i;
			
			for ( mns = multinames.get(), i=1 ; mns != NULL ; mns = mns->tl, i++ )
				if (mns->hd->kind == kind && mns->hd->ns_or_nsset == ns_or_nsset && mns->hd->name == name)
					return i;

			multinameBuf.emitU8(kind);
			switch (kind) {
				case CONSTANT_QnameA:
				case CONSTANT_Qname:
					multinameBuf.emitU30(ns_or_nsset);
					multinameBuf.emitU30(name);
					break;
					
				case CONSTANT_RTQnameA:
				case CONSTANT_RTQname:
					multinameBuf.emitU30(name);
					break;
					
				case CONSTANT_RTQnameLA:
				case CONSTANT_RTQnameL:
					break;
					
				case CONSTANT_MultinameA:
				case CONSTANT_Multiname:
					multinameBuf.emitU30(name);
					multinameBuf.emitU30(ns_or_nsset);
					break;
					
				case CONSTANT_MultinameLA:
				case CONSTANT_MultinameL:
					multinameBuf.emitU30(ns_or_nsset);
					break;

				default:
					compiler->internalError(0, "Invalid multiname kind");
			}

			multinames.addAtEnd(ALLOC(ABCMultinameInfo, (kind, ns_or_nsset, name)));
			return multinameCount++;
		}

		ABCMultinameInfo* ABCFile::getMultiname(uint32_t index)
		{
			Seq<ABCMultinameInfo*>* mns;
			
			for ( mns = multinames.get() ; index > 1 ; mns = mns->tl, index-- )
				;
			return mns->hd;
		}

		bool ABCFile::hasRTNS(uint32_t index)
		{
			switch (getMultiname(index)->kind) {
				case CONSTANT_RTQname:
				case CONSTANT_RTQnameA:
				case CONSTANT_RTQnameL:
				case CONSTANT_RTQnameLA:
					return true;
				default:
					return false;
			}
		}
		
		bool ABCFile::hasRTName(uint32_t index) 
		{
			switch (getMultiname(index)->kind) {
				case CONSTANT_RTQnameL:
				case CONSTANT_RTQnameLA:
				case CONSTANT_MultinameL:
				case CONSTANT_MultinameLA:
					return true;
				default:
					return false;
			}
		}

		uint32_t ABCFile::size() 
		{
			AvmAssert(scriptCount != 0);
			AvmAssert(methodCount != 0);
			AvmAssert(methodbodyCount != 0);
			AvmAssert(classCount == instanceCount);
			
			uint32_t method_size = computeSize(methods.get());
			uint32_t metadata_size = computeSize(metadatas.get());
			uint32_t instance_size = computeSize(instances.get());
			uint32_t class_size = computeSize(classes.get());
			uint32_t script_size = computeSize(scripts.get());
			uint32_t body_size = computeSize(bodies.get());

			reported_size = (4 +
							 lenU30(intCount) + intBuf.size() + 
							 lenU30(uintCount) + uintBuf.size() + 
							 lenU30(doubleCount) + doubleBuf.size() + 
							 lenU30(stringCount) + stringBuf.size() +
							 lenU30(namespaceCount) + namespaceBuf.size() +
							 lenU30(nssetCount) + nssetBuf.size() +
							 lenU30(multinameCount) + multinameBuf.size() +
							 lenU30(methodCount) + method_size +
							 lenU30(metadataCount) + metadata_size +
							 lenU30(instanceCount) + instance_size + class_size +
							 lenU30(scriptCount) + script_size +
							 lenU30(methodbodyCount) + body_size);
			return reported_size;
		}

		uint8_t* ABCFile::serialize(uint8_t* b)
		{
			DEBUG_ONLY( uint8_t* b0 = b; )
			b = emitU16(b, minor_version);
			b = emitU16(b, major_version);
				
			b = emitU30(b, intCount);
			b = emitBytes(b, &intBuf);
			b = emitU30(b, uintCount);
			b = emitBytes(b, &uintBuf);
			b = emitU30(b, doubleCount);
			b = emitBytes(b, &doubleBuf);
			b = emitU30(b, stringCount);
			b = emitBytes(b, &stringBuf);
			b = emitU30(b, namespaceCount);
			b = emitBytes(b, &namespaceBuf);
			b = emitU30(b, nssetCount);
			b = emitBytes(b, &nssetBuf);
			b = emitU30(b, multinameCount);
			b = emitBytes(b, &multinameBuf);

			b = emitU30(b, methodCount);
			b = serializeSeq(b, methods.get());
			b = emitU30(b, metadataCount);
			b = serializeSeq(b, metadatas.get());
			b = emitU30(b, instanceCount);
			b = serializeSeq(b, instances.get());
			b = serializeSeq(b, classes.get());
			b = emitU30(b, scriptCount);
			b = serializeSeq(b, scripts.get());
			b = emitU30(b, methodbodyCount);
			b = serializeSeq(b, bodies.get());
			AvmAssert( b == b0 + reported_size );
			return b;
		}

		ABCTraitsTable::ABCTraitsTable(Compiler* compiler)
			: traitsCount(0)
			, traits(compiler->allocator)
		{
		}

		uint32_t ABCTraitsTable::size()
		{
			reported_size = lenU30(traitsCount) + computeSize(traits.get());
			return reported_size;
		}
		
		uint8_t* ABCTraitsTable::serialize(uint8_t* b)
		{
			DEBUG_ONLY( uint8_t* b0 = b; )
			b = emitU30(b, traitsCount);
			b = serializeSeq(b, traits.get());
			AvmAssert( b == b0 + reported_size );
			return b;
		}
		
		uint32_t ABCTrait::size()
		{
			// no provision for metadata
			reported_size = (lenU30(name) +
							 1 /* kind */ +
							 dataSize());
			return reported_size;
		}
		
		uint8_t *ABCTrait::serialize(uint8_t* b)
		{
			DEBUG_ONLY( uint8_t* b0 = b; )
			b = emitU30(b, name);
			AvmAssert(kind < 8);
			*b++ = (uint8_t)kind;
			b = serializeData(b);
			AvmAssert( b == b0 + reported_size );
			return b;
		}
		
		uint32_t ABCSlotTrait::dataSize()
		{
			uint32_t slot_id = 0, vindex = 0;
			return (lenU30(slot_id) +
					lenU30(type_name) +
					lenU30(vindex) +
					(vindex != 0 ? 1 : 0));
		}
		
		uint8_t* ABCSlotTrait::serializeData(uint8_t *b)
		{
			uint32_t slot_id = 0, vindex = 0, vkind = 0;
			b = emitU30(b, slot_id);
			b = emitU30(b, type_name);
			b = emitU30(b, vindex);
			if (vindex != 0)
				*b++ = (uint8_t)vkind;
			return b;
		}
		
		uint32_t ABCMethodTrait::dataSize()
		{
			uint32_t disp_id = 0;
			return (lenU30(disp_id) + lenU30(method_info));
		}
		
		uint8_t* ABCMethodTrait::serializeData(uint8_t* b)
		{
			uint32_t disp_id = 0;
			b = emitU30(b, disp_id);
			b = emitU30(b, method_info);
			return b;
		}

		ABCScriptInfo::ABCScriptInfo(Compiler* compiler, ABCMethodInfo* init_method, ABCTraitsTable* traits) 
			: index(compiler->abc.addScript(this))
			, init_method(init_method)
			, traits(traits)
		{
		}
		
		uint32_t ABCScriptInfo::size() 
		{
			reported_size = (lenU30(init_method->index) + traits->size());
			return reported_size;
		}
		
		uint8_t *ABCScriptInfo::serialize(uint8_t* b)
		{
			DEBUG_ONLY( uint8_t* b0 = b; )
			b = emitU30(b, init_method->index);
			b = traits->serialize(b);
			AvmAssert( b == b0 + reported_size );
			return b;
		}
		
		ABCMethodBodyInfo::ABCMethodBodyInfo(Compiler* compiler, ABCMethodInfo* method_info, ABCTraitsTable* traits, uint32_t first_temp)
			: cogen(compiler, &compiler->abc, traits, this, first_temp)
			, exceptions(compiler)
			, index(compiler->abc.addMethodBody(this))
			, method_info(method_info)
			, traits(traits)
		{
		}
	
		uint32_t ABCMethodBodyInfo::size() 
		{
			reported_size = (lenU30(method_info->index) +
							 lenU30(cogen.getMaxStack()) +
							 lenU30(cogen.getLocalCount()) +
							 lenU30(0) /* init_scope_depth */ +
							 lenU30(cogen.getMaxScope()) +
							 lenU30(cogen.getCodeLength()) +
							 cogen.getCodeLength() +
							 exceptions.size() +
							 (traits ? traits->size() : lenU30(0)));
			return reported_size;
		}
		
		uint8_t* ABCMethodBodyInfo::serialize(uint8_t* b)
		{
			DEBUG_ONLY( uint8_t* b0 = b; )
			b = emitU30(b, method_info->index);
			b = emitU30(b, cogen.getMaxStack());
			b = emitU30(b, cogen.getLocalCount());
			b = emitU30(b, 0); /* init_scope_depth */
			b = emitU30(b, cogen.getMaxScope());
			b = emitU30(b, cogen.getCodeLength());
			b = cogen.serializeCodeBytes(b);
			b = exceptions.serialize(b);
			b = (traits ? traits->serialize(b) : emitU30(b, 0));
			AvmAssert( b == b0 + reported_size );
			return b;
		}
		
		ABCMethodInfo::ABCMethodInfo(Compiler* compiler, 
									 uint32_t name, 
									 uint32_t param_count,
									 Seq<uint32_t>* param_types,
									 uint32_t return_type)
			: index(compiler->abc.addMethod(this))
			, name(name)
			, param_count(param_count)
			, param_types(param_types)
			, return_type(return_type)
			, flags(~0U)
		{
		}

		uint32_t ABCMethodInfo::size() 
		{
			AvmAssert(flags != ~0U);
			uint32_t param_size = 0;
			for ( Seq<uint32_t>* param_types = this->param_types ; param_types != NULL ; param_types = param_types->tl )
				param_size += lenU30(param_types->hd);
			reported_size = (lenU30(param_count) +
							 lenU30(return_type) + 
							 param_size +
							 lenU30(name) +
							 1 /* flags */ + 
							 0 /* option_info */ +
							 0 /* param_names */);
			return reported_size;
		}
		
		uint8_t* ABCMethodInfo::serialize(uint8_t* b)
		{
			DEBUG_ONLY( uint8_t* b0 = b; )
			AvmAssert(flags != ~0U);
			b = emitU30(b, param_count);
			b = emitU30(b, return_type);
			for ( Seq<uint32_t>* param_types = this->param_types ; param_types != NULL ; param_types = param_types->tl )
				b = emitU30(b, param_types->hd);
			b = emitU30(b, name);
			*b++ = (uint8_t)flags;
			AvmAssert( b == b0 + reported_size );
			return b;
		}
		
		ABCExceptionTable::ABCExceptionTable(Compiler* compiler)
			: exceptionCount(0)
			, exceptions(compiler->allocator)
		{
		}

		uint32_t ABCExceptionTable::size()
		{
			reported_size = lenU30(exceptionCount);
			for ( Seq<ABCExceptionInfo*>* exceptions = this->exceptions.get() ; exceptions != NULL ; exceptions = exceptions->tl )
				reported_size += exceptions->hd->size();
			return reported_size;
		}
		
		uint8_t* ABCExceptionTable::serialize(uint8_t* b)
		{
			DEBUG_ONLY( uint8_t* b0 = b; )
			b = emitU30(b, exceptionCount);
			for ( Seq<ABCExceptionInfo*>* exceptions = this->exceptions.get() ; exceptions != NULL ; exceptions = exceptions->tl )
				b = exceptions->hd->serialize(b);
			AvmAssert( b == b0 + reported_size );
			return b;
		}

		ABCExceptionInfo::ABCExceptionInfo(uint32_t from, uint32_t to, uint32_t target, uint32_t exception_type, uint32_t var_name)
			: from(from)
			, to(to)
			, target(target)
			, exception_type(exception_type)
			, var_name(var_name)
		{
		}
		
		uint32_t ABCExceptionInfo::size() 
		{
			reported_size = (lenU30(from) +
							 lenU30(to) +
							 lenU30(target) +
							 lenU30(exception_type) +
							 lenU30(var_name));
			return reported_size;
		}
		
		uint8_t* ABCExceptionInfo::serialize(uint8_t* b)
		{
			DEBUG_ONLY( uint8_t* b0 = b; )
			b = emitU30(b, from);
			b = emitU30(b, to);
			b = emitU30(b, target);
			b = emitU30(b, exception_type);
			b = emitU30(b, var_name);
			AvmAssert( b == b0 + reported_size );
			return b;
		}
		
#if 0

		class ABCInstanceInfo
		{
			function ABCInstanceInfo(name, super_name, flags, protectedNS, interfaces) {
				this.name = name;
				this.super_name = super_name;
				this.flags = flags;
				this.protectedNS = protectedNS;
				this.interfaces = interfaces;
				this.traits = [];
			}

			function setIInit(x) {
				iinit = x;
			}

			function addTrait(t) {
				return traits.push(t)-1;
			}

			function serialize(bs) {
				let i, limit;

				Util::assert( iinit != undefined || (flags & CONSTANT_ClassInterface) != 0);

				bs.uint30(name);
				bs.uint30(super_name);
				bs.uint8(flags);
				if (flags & CONSTANT_ClassProtectedNs)
					bs.uint30(protectedNS);
				bs.uint30(interfaces.length);
				for ( i=0, limit=interfaces.length ; i < limit ; i++ ) {
					Util::assert( interfaces[i] != 0 );
					bs.uint30(interfaces[i]);
				}
				bs.uint30(iinit);
				bs.uint30(traits.length);
				for ( i=0, limit=traits.length ; i < limit ; i++ )
					traits[i].serialize(bs);
			}

			// abc-parse.es grubs around here.
			/ *private* / var name, super_name, flags, protectedNS, interfaces, iinit, traits;
		};

		class ABCClassInfo
		{
			function setCInit(cinit) {
				this.cinit = cinit;
			}

			function addTrait(t) {
				return traits.push(t)-1;
			}

			function serialize(bs) {
				Util::assert( cinit != undefined );
				bs.uint30(cinit);
				bs.uint30(traits.length);
				for ( let i=0, limit=traits.length ; i < limit ; i++ )
					traits[i].serialize(bs);
			}

			// abc-parse.es grubs around here.
			/*private*/ var cinit, traits = [];
		};

#endif // 0
	}
}

#endif // VMCFG_EVAL
