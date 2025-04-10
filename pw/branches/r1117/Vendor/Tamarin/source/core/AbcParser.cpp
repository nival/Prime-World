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

#ifdef VMCFG_AOT
#include "AOTCompiler.h"
#endif

namespace avmplus
{
    /**
     * parse a .abc file completely
     * @param code
     * @return
     */
    PoolObject* AbcParser::decodeAbc(AvmCore* core, ScriptBuffer code, 
		Toplevel* toplevel,
		Domain* domain,
		const NativeInitializer* natives,
		API api)
    {
		int version;
		int result = canParse(code, &version);
		
#ifdef AVMPLUS_VERBOSE
		if (core->isVerbose(VB_parse))
			core->console << "major=" << (version&0xFFFF) << " minor=" << (version>>16) << "\n";
#endif
		
		if (result != 0) {
			switch (result) {
				case kInvalidMagicError:
					toplevel->throwVerifyError(kInvalidMagicError, core->toErrorString(version>>16), core->toErrorString(version&0xFFFF));
				case kCorruptABCError:
				default:
					toplevel->throwVerifyError(kCorruptABCError);
			}
		}

#ifdef VMCFG_AOT
		if(!natives) // no natives -- runtime-loaded script
		{
			if(version == 0 && code.getSize() == 24) // only ABC "references" -- these are 0.0 version followed by SHA1
			{
				void *sha1 = (void *)(code.getBuffer() + 4);
				for(int i = 0; i < nAOTInfos; i++)
				{
					const AOTInfo *aotInfo = &aotInfos[i];
					AvmAssert(aotInfo != NULL);
					
					MMGC_STATIC_ASSERT(sizeof(aotInfo->origABCSHA1) == 20);
					if(!memcmp(aotInfo->origABCSHA1, sha1, 20))
					{
						ReadOnlyScriptBufferImpl scriptBufferImpl(aotInfo->abcBytes, aotInfo->nABCBytes);
						ScriptBuffer code(&scriptBufferImpl);
						
						NativeInitializer ninit(core, aotInfo, 0, 0);
						PoolObject *pool = decodeAbc(core, code, toplevel, domain, &ninit, api);
						AvmAssert(pool != NULL);
						AvmAssert(!pool->isBuiltin);
						AvmAssert(pool->aotInfo == aotInfo);
#ifdef DEBUGGER
						// TODO: is there a better pace to do this for both builtins and user scripts?
						addAOTDebugInfo(pool);
#endif
						return pool;
					}
				}
			}
			toplevel->throwVerifyError( kCorruptABCError ); // not a reference or not found	
			return NULL;
		}
#endif
		
		AbcParser parser(core, code, toplevel, domain, natives);
		PoolObject *pObject = parser.parse(api);
 		if ( !pObject ) {
 			toplevel->throwVerifyError( kCorruptABCError );
			/*NOTREACHED*/
			return NULL;
		}
 		else
 			return pObject;
	}

#if defined(VMCFG_AOT) && defined(DEBUGGER)
	void AbcParser::addAOTDebugInfo(PoolObject *pool)
	{
		AvmCore *core = pool->core;
		const AOTInfo *aotInfo = pool->aotInfo;
		Debugger *debugger = core->debugger();
		
		if(debugger)
		{
			const MethodDebugInfo* methodDebugInfos = aotInfo->methodDebugInfos;
		
			if(methodDebugInfos != NULL)
			{				
				// create the structure representing the ABC
				AbcFile* abc = new (core->GetGC()) AbcFile(core, 0);
				
				for(int n = 0; n < aotInfo->nABCMethods; n++)
				{
					MethodInfo *f = pool->getMethodInfo(n);
					
					// create DMIs
					const MethodDebugInfo &info = methodDebugInfos[n];
					DebuggerMethodInfo* dmi = DebuggerMethodInfo::create(core, info.local_count, -1, info.scope_count);
					pool->_method_dmi.set(n, dmi);
					
					// set the file in the MethodInfo
					f->setFile(abc);
					
					// get a SourceFile
					SourceFile *src = NULL;
					
					if(info.file_name)
					{
						Stringp fileName = pool->getString(info.file_name);
						src = abc->sourceNamed(fileName);
						if(!src)
						{
							src = new (core->GetGC()) SourceFile(core->GetGC(), fileName);
							abc->sourceAdd(src);
						}
					}
					
					// set register names
					for(int i = 0; i < info.local_count; i++)
					{
						int name = info.local_names[i];
						
						if(name)
							f->setRegName(i, pool->getString(name));
					}
					
					// add line info
					if(src)
						for(int i = 0; i < info.line_count; i++)
							src->addLine(info.lines[i], f, 0);
				}
				// hook the ABC in
				debugger->pool2abcIndex.add(pool, (const void *)debugger->abcList.size());
				debugger->abcList.add(abc);
			}
		}
    }
#endif

	int AbcParser::canParse(ScriptBuffer code, int* version)
	{
		if (version != NULL)
			*version = 0;
		
		if (code.getSize() < 4)
			return kCorruptABCError;
		
		int v = AvmCore::readU16(&code[0]) | AvmCore::readU16(&code[2])<<16;
		if (version != NULL)
			*version = v;
		
		switch (v) {
#ifdef VMCFG_AOT
			case 0: // just a "reference" to an AOT-ed ABC!
#endif
			case (46<<16|16):
				return 0;
			default:
				return kInvalidMagicError;
		}
	}
	
	AbcParser::AbcParser(AvmCore* core, ScriptBuffer code, 
		Toplevel* toplevel,
		Domain* domain,
		const NativeInitializer* natives)
		: instances(core->GetGC(), 0),
		  toplevel(toplevel),
		  domain(domain)
	{
		this->core = core;
		this->code = code;
		this->pool = NULL;
		this->version = AvmCore::readU16(&code[0]) | AvmCore::readU16(&code[2])<<16;
		this->pos = &code[4];
		this->natives = natives;

		abcStart = &code[0];
		abcEnd = &code[(int)code.getSize()];

		classCount = 0;
		metaNames = NULL;
	}

	AbcParser::~AbcParser()
	{
		if (metaNames)
			core->GetGC()->Free(metaNames);
	}

	REALLY_INLINE void AbcParser::computeInstanceSizeAndSlotsOffset(int class_id, 
																	Traits* base,
																	uint16_t& sizeofInstance,
																	uint16_t& offsetofSlots) const
	{
		// If this is a native class, use the stated instance size and offset to slot area.
		const NativeClassInfo* nativeEntry;
		if (natives && (nativeEntry = natives->get_class(class_id)) != NULL && nativeEntry->sizeofInstance)
		{
			sizeofInstance = nativeEntry->sizeofInstance;
			offsetofSlots = nativeEntry->offsetofSlotsInstance;
			return;
		}

		// Search the inheritance chain for any native classes.
		while (base)
		{
			if (base->getSizeOfInstance() > sizeof(ScriptObject))
			{
				// non-Object base class uses a subclass of ScriptObject, so use that size.
				sizeofInstance = base->getSizeOfInstance();
				// non-native class so slots start after end of C++ data.
				offsetofSlots = sizeofInstance;
				return;
			}
			base = base->base;
		}

		// no derived native classes found
		sizeofInstance = uint16_t(sizeof(ScriptObject));
		offsetofSlots = uint16_t(sizeof(ScriptObject));
	}

	Namespacep AbcParser::parseNsRef(const byte* &pc) const
	{
		uint32 index = readU30(pc);
		if (index == 0)
		{
			return NULL; // AnyNamespace
		}

		if (index >= pool->constantNsCount)
			toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(index), core->toErrorString(pool->constantNsCount));
		return pool->cpool_ns[index];
	}

#if defined(VMCFG_AOT) || defined(AVMPLUS_VERBOSE)
	void AbcParser::parseTypeName(const byte* &pc, Multiname& m) const
	{
		// only save the type name for now.  verifier will resolve to traits
		uint32 index = readU30(pc);
		if (index == 0)
		{
			// type is *
			m.setNamespace(core->getPublicNamespace(pool));
			m.setName(core->kAsterisk);
			return;
		}

		if (index >= pool->cpool_mn_offsets.size())
			toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(index), core->toErrorString(pool->cpool_mn_offsets.size()));

		pool->parseMultiname(m, index);
	}
	#endif

	uint32_t AbcParser::resolveQName(const byte* &p, Multiname &m) const
	{
		uint32 index = readU30(p);
		if (index == 0 || index >= pool->cpool_mn_offsets.size())
			toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(index), core->toErrorString(pool->constantCount));

		pool->parseMultiname(m, index);

		if (!pool->isBuiltin && !m.isQName())
			toplevel->throwVerifyError(kCpoolEntryWrongTypeError, core->toErrorString(index));
		return index;
	}

	MethodInfo* AbcParser::resolveMethodInfo(uint32 index) const
	{
		const uint32_t c = pool->methodCount();
		if (index >= c)
			toplevel->throwVerifyError(kMethodInfoExceedsCountError, core->toErrorString(index), core->toErrorString(c));

		MethodInfo* f = pool->getMethodInfo(index);
		if (!f)
			toplevel->throwVerifyError(kMethodInfoOrderError, core->toErrorString(index));

		return f;
	}

	Stringp AbcParser::resolveUtf8(uint32 index) const
	{
		if (index > 0 && index < pool->constantStringCount)
		{
			return pool->getString(index);
		}
		toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(index), core->toErrorString(pool->constantStringCount));
		return NULL;
	}

	Stringp AbcParser::parseName(const byte* &pc) const
	{
		uint32 index = readU30(pc);
		if (index == 0)
			return NULL;
		return resolveUtf8(index);
	}

	PoolObject* AbcParser::parse(API api)
	{
#ifdef VMCFG_LOOKUP_CACHE
		// Loading a new ABC file always invalidates the lookup cache
		core->invalidateLookupCache();
#endif
		// Loading a new ABC file always invalidates the traits cache(s)
		core->tbCache()->flush();
		core->tmCache()->flush();

		// constant pool
		parseCpool(api);

		// parse all methodInfos in one pass.  Nested functions must come before outer functions
		parseMethodInfos();

		// parse all metadataInfos - AVM+ doesn't care about this, so we are really just skipping them
		parseMetadataInfos();

		// parse classes.  base classes must come first.
		if (!parseInstanceInfos()) return NULL;

		bool first = false;
		if (CLASS_TYPE == NULL)
		{
			// if we haven't got types from the builtin file yet, do it now.
			first = true;
			core->traits.initInstanceTypes(pool);

			// register "void"
			addNamedTraits(core->getPublicNamespace(ApiUtils::getSmallestAPI()), VOID_TYPE->name(), VOID_TYPE);
		}

		// type information about class objects
		parseClassInfos();

		if (first)
		{
			core->traits.initClassTypes(pool);
		}

		// scripts
		if( !parseScriptInfos() ) return NULL;

		// method bodies: code, exception info, and activation traits
		parseMethodBodies();

        return pool;
	}

	// check to see if we are trying to read past the file end or the beginning.
	#define CHECK_POS(pos) do { if ((pos) < abcStart || (pos) >= abcEnd ) toplevel->throwVerifyError(kCorruptABCError); } while (0)

	/**
	 * setting up a traits that extends another one.  Two parser passes are required,
	 * one for sizing the traits object and the other for allocating it and filling
	 * it in.
	 */
	Traits* AbcParser::parseTraits(uint16_t sizeofInstance,
									uint16_t offsetofSlots,
									Traits* base, 
									Namespacep ns, 
									Stringp name, 
									MethodInfo* script, 
									TraitsPosPtr traitsPos,
									TraitsPosType posType, 
									Namespacep protectedNamespace)
	{
		uint32_t nameCount = readU30(pos);

		// Very generous check for nameCount being way too large.
		if (nameCount > (uint32_t)(abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		#ifdef AVMPLUS_VERBOSE
		if (pool->isVerbose(VB_parse))
			core->console << "        trait_count=" << nameCount << "\n";
		#endif

		Traits* traits = Traits::newTraits(pool, base, sizeofInstance,offsetofSlots , traitsPos, posType);
		traits->set_names(ns, name);
		traits->protectedNamespace = protectedNamespace;
		
		for (uint32_t i=0; i < nameCount; i++)
        {
			Multiname mn;
			const uint32_t qn_index = resolveQName(pos, mn);
			Namespacep ns;
			const NamespaceSet* nss;
			if (mn.namespaceCount() > 1) {
				nss = (NamespaceSet*) mn.getNsset();
				ns = nss->nsAt(0);
			}
			else {
				ns = mn.getNamespace();
				nss = NamespaceSet::create(core->GetGC(), ns);
			}
			// TODO name can come out null and fire all kinds of asserts from a broken compiler
			// and crash a release build, not sure if null is valid in any cases but there's definitely
			// a missing verify error here somewhere
			Stringp name = mn.getName();
			CHECK_POS(pos);
            int tag = *pos++;
            TraitKind kind = (TraitKind) (tag & 0x0f);
			
			uint32_t class_index = 0;
			uint32_t method_index = 0;
			uint32_t slot_id = 0;
			uint32_t value_index = 0;
			uint32_t earlyDispId = 0;
			bool needsDxns = false;
#ifdef AVMPLUS_VERBOSE
			Multiname typeName;
#endif

			// Read in the trait entry.
			switch (kind)
			{
			case TRAIT_Slot:
			case TRAIT_Const:
				slot_id = readU30(pos);							// slot id
#ifdef AVMPLUS_VERBOSE
				parseTypeName(pos, typeName);
#else
				readU30(pos);
#endif
				value_index = readU30(pos);	// value index
				if (value_index)
				{
					CHECK_POS(pos);
					pos += 1;				// value_kind
				}
				break;
			case TRAIT_Class:
				readU30(pos); // slot id
				class_index = readU30(pos);
				break;
			case TRAIT_Getter:
			case TRAIT_Setter:
			case TRAIT_Method:
				earlyDispId = readU30(pos);			// disp id
				method_index = readU30(pos);	
				break;
			default:
				// unsupported traits type
				toplevel->throwVerifyError(kUnsupportedTraitsKindError, core->toErrorString(kind));
			}

			const byte* meta_pos = pos;
			if (tag & ATTR_metadata)
			{
				const uint32_t metadataCount = readU30(pos);
				for (uint32_t metadata = 0; metadata < metadataCount; ++metadata)
				{
					const uint32_t index = readU30(pos);
					if (index >= pool->metadataCount || !metaNames)
						toplevel->throwVerifyError(kCorruptABCError);
					Stringp name = metaNames[index];
					if (name == core->kNeedsDxns)
						needsDxns = true;
				}
			}

			switch (kind)
            {
            case TRAIT_Slot:
            case TRAIT_Const:
            case TRAIT_Class:
			{
				if (script)
					addNamedScript(nss, name, script);

				if (kind == TRAIT_Class)
				{
					// get the class type
					if (class_index >= classCount)
						toplevel->throwVerifyError(kClassInfoExceedsCountError, core->toErrorString(class_index), core->toErrorString(classCount));

					Traits* ctraits = pool->getClassTraits(class_index);
					if (!ctraits) 
						toplevel->throwVerifyError(kClassInfoOrderError, core->toErrorString(class_index));

					#ifdef AVMPLUS_VERBOSE
					if (pool->isVerbose(VB_parse))
					{
						core->console << "            " << traitNames[kind]
							<< " name=" << Multiname::format(core, ns, name)
							<< " slot_id=" << slot_id
							<< " type=" << ctraits
							<< "\n";
					}
					#endif

					if (script)
					{
						// promote instance type to the vm-wide type table.
						// map type name to traits
						addNamedTraits(nss, name, ctraits->itraits);
						if (tag & ATTR_metadata)
						{
							ctraits->itraits->setMetadataPos(meta_pos);
						}
					}
					else
					{
						if (tag & ATTR_metadata)
						{
							ctraits->setMetadataPos(meta_pos);
						}
					}
				}
				else
				{
					#ifdef AVMPLUS_VERBOSE
					if (pool->isVerbose(VB_parse))
					{
						core->console << "            " << traitNames[kind]
							<< " name=" << Multiname::format(core,ns,name)
							<< " slot_id=" << slot_id
							<< " value_index=" << value_index
							<< " type=" << typeName
							<< "\n";
					}
					#endif
				}
	            break;
			}
			case TRAIT_Getter:
			case TRAIT_Setter:
            case TRAIT_Method:
			{
				#ifdef AVMPLUS_VERBOSE
				if (pool->isVerbose(VB_parse))
				{
					core->console << "            " << traitNames[kind]
						<< " name=" << Multiname::format(core, ns, name)
						<< " disp_id=" << earlyDispId << " (ignored)"
					    << " method_index=" << method_index
						<< " attr=" << ((tag&ATTR_final)?"final":"virtual");
					if (tag&ATTR_override)
						core->console << "|override";
					core->console << "\n";
				}
				#endif

				// id is unused here
				MethodInfo* f = resolveMethodInfo(method_index);

				#if VMCFG_METHOD_NAMES
				if (core->config.methodNames)
				{
					pool->_method_name_indices.set(method_index, -int32_t(qn_index));
				}
				#else
				(void)qn_index;
				#endif

				// since this function is ref'ed here, we know the receiver type.
				if (!f->makeMethodOf(traits))
					toplevel->throwVerifyError(kCorruptABCError);
				
				f->setKind(kind); // sets the IS_GETTER/IS_SETTER flags
				if (tag & ATTR_final)
					f->setFinal();
				if (tag & ATTR_override)
					f->setOverride();
				if (needsDxns)
					f->setNeedsDxns();
				
				// only export one name for an accessor 
				if (script && !domain->getNamedScript(name,ns))
					addNamedScript(nss, name, script);

                break;
			}

			default:
				// unsupported traits type
				toplevel->throwVerifyError(kUnsupportedTraitsKindError, core->toErrorString(kind));
            }

#ifdef AVMPLUS_VERBOSE
            if (tag & ATTR_metadata)
            {
                uint32_t metadataCount = readU30(meta_pos);
				for (uint32_t metadata = 0; metadata < metadataCount; ++metadata)
				{
					uint32_t index = readU30(meta_pos);
					if (pool->isVerbose(VB_parse))
						core->console << "            [" << metaNames[index] << "]\n";
				}
            }
#endif
        }

		return traits;
	}

	void AbcParser::parseMethodInfos()
    {
        int methodCount = readU30(pos);

		#ifdef AVMPLUS_VERBOSE
		if(pool->isVerbose(VB_parse)) {
			core->console << "method_count=" << methodCount << "\n";
		}
		#endif

		int size = methodCount == 0 ? 1 : methodCount;

		if (size > (abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		MMGC_MEM_TYPE(pool);
		pool->_methods.ensureCapacity(size);
#ifdef DEBUGGER
		if (core->debugger())
		{
			pool->_method_dmi.ensureCapacity(size);
			for (int i = 0; i < size; ++i)
				pool->_method_dmi.set(i, NULL);
		}
#endif
#if VMCFG_METHOD_NAMES
		if (core->config.methodNames)
		{
			pool->_method_name_indices.ensureCapacity(size);
		}
#endif

#ifdef AVMPLUS_VERBOSE
		const byte* startpos = pos;
#endif

		for (int i=0; i < methodCount; i++)
        {
#ifdef AVMPLUS_VERBOSE
			int offset = (int)(pos-startpos);
#endif
			const byte* info_pos = pos;
		
			// MethodInfo
			const int param_count = readU30(pos);

#ifdef VMCFG_AOT
			const byte* ret_type_pos = pos;
#endif

		// @todo -- we should add an AbcParser equivalent of skipU30;
		// then the next two clauses would be 			
		//		skipU30(pos, param_count+1);
		// in non-verbose builds
			#ifdef AVMPLUS_VERBOSE
			Multiname returnTypeName;
			parseTypeName(pos, returnTypeName);
			if(pool->isVerbose(VB_parse)) {
				core->console << "    " << offset << ":method["<<i<<"]\n"
					<< "        returnType=" << returnTypeName << "\n"
					<< "        param_count=" << param_count 
				    << "\n";
			}
			#else
			readU30(pos);// return type name
			#endif

			for( int j = 1; j <= param_count; ++j)
			{
				#ifdef AVMPLUS_VERBOSE
				Multiname multiname;
				parseTypeName(pos, multiname);
				if(pool->isVerbose(VB_parse)) {
					core->console << "            paramType["<<j<<"]="<< multiname << "\n";
				}
				#else
				readU30(pos);
				#endif
			}

            uint32_t name_index = readU30(pos);
            (void)name_index;
			CHECK_POS(pos);
			uint8_t abcFlags = *pos++;

			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console << "        name_index=" << name_index;
				if (name_index > 0 && name_index < pool->constantStringCount)
					core->console << " \"" << pool->getString(name_index) << "\"";
				core->console << "\n        flags=" << (uint32_t)abcFlags << "\n";
			}
			#endif

			const NativeMethodInfo* ni = NULL;
			if (abcFlags & MethodInfo::NATIVE)
			{
				ni = natives ? natives->getNativeInfo(i) : NULL;
				if (!ni)
				{
					// If this assert hits, you're missing a native method.  Method "i"
					// corresponds to the function of the same number in 
					// source\avmglue\avmglue.h if you're running the Flash player.
					AvmAssertMsg(0, "missing native method decl");
					toplevel->throwVerifyError(kIllegalNativeMethodError);
				}
			}

#ifdef VMCFG_AOT
			bool isCompiled = false;
			{
				Multiname returnTypeName;
				parseTypeName(ret_type_pos, returnTypeName);

				NativeMethodInfo compiledMethodInfo;

				if (!ni && natives->getCompiledInfo(&compiledMethodInfo, returnTypeName, i))
				{
					ni = &compiledMethodInfo;
					abcFlags |= MethodInfo::compiledMethodFlags();
					isCompiled = true;
				}
			}
#endif

			const int optional_count = (abcFlags & MethodInfo::HAS_OPTIONAL) ? readU30(pos) : 0;

			MethodInfo* info = new (core->GetGC()) MethodInfo(i, pool, info_pos, abcFlags, ni);
			
#ifdef VMCFG_AOT
			if(isCompiled)
				info->setCompiledMethod();
#endif
			
			#if VMCFG_METHOD_NAMES
			if (core->config.methodNames)
			{
				pool->_method_name_indices.set(i, int32_t(name_index));
			}
			#endif

			if (abcFlags & MethodInfo::HAS_OPTIONAL)
			{
				for( int j = 0; j < optional_count; ++j)
				{
					readU30(pos);
					++pos; // Kind bytes for each default value
				}

				if (!optional_count || (optional_count > param_count))
				{
					// cannot have more optional params than total params
					toplevel->throwVerifyError(kCorruptABCError);
				}
			}

			if (abcFlags & MethodInfo::HAS_PARAM_NAMES)
			{
				// AVMPlus doesn't care about the param names, just skip past them
				for( int j = 0; j < param_count; ++j )
				{
					readU30(pos);
				}
			}

			// save method info pointer.  we will verify code later.
			pool->_methods.set(i, info);
#ifdef DEBUGGER
			// don't create the corresponding DebuggerMethodInfo yet, we'll do that in parseMethodBodies
#endif
		}
    }
	

	void AbcParser::parseMetadataInfos()
    {
        uint32_t metadataCount = readU30(pos);

		#ifdef AVMPLUS_VERBOSE
		if(pool->isVerbose(VB_parse)) {
			core->console << "metadata_count=" << metadataCount << "\n";
		}
		#endif

		if (metadataCount > uint32_t(abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		pool->metadata_infos.ensureCapacity(metadataCount);
		pool->metadataCount = metadataCount;

		if (metadataCount > 0)
		{
			metaNames = (Stringp*) core->GetGC()->Calloc(metadataCount, sizeof(Stringp), MMgc::GC::kContainsPointers);

#ifdef AVMPLUS_VERBOSE
			kVerboseVerify = core->internConstantStringLatin1("VerboseVerify");
#endif

			for (uint32_t i=0; i < metadataCount; i++)
			{
				pool->metadata_infos.set(i, pos);
				// MetadataInfo
				uint32_t index = readU30(pos);
				Stringp name = resolveUtf8(index);
				// constant pool names are stuck and always reachable via PoolObject, DRC or WB
				metaNames[i] = name;

				#ifdef AVMPLUS_VERBOSE
				if(pool->isVerbose(VB_parse)) {
					core->console << "    " << name;
				}
				#endif

				int values_count = readU30(pos);
				if (values_count > 0)
				{
					#ifdef AVMPLUS_VERBOSE
					if(pool->isVerbose(VB_parse)) {
						core->console << "(";
					}
					#endif
					for(int q = 0; q < values_count; ++q)
					{
						uint32_t a = readU30(pos);
						uint32_t b = readU30(pos);
						#ifdef AVMPLUS_VERBOSE
						if(pool->isVerbose(VB_parse)) {
							core->console << a << "," << b;
							if (q+1 < values_count)
								core->console << " ";
						}
						#else
						(void)a;
						(void)b;
						#endif
					}
					#ifdef AVMPLUS_VERBOSE
					if(pool->isVerbose(VB_parse)) {
						core->console << ")";
					}
				#endif
				}
			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
					core->console << "\n";
			}
			#endif
			}
		}
    }

    void AbcParser::parseMethodBodies()
    {
        int bodyCount = readU30(pos);

		#ifdef AVMPLUS_VERBOSE
		if(pool->isVerbose(VB_parse)) {
			core->console << "bodies_count=" << bodyCount << "\n";
		}
		#endif

#ifdef AVMPLUS_VERBOSE
		const byte* startpos = pos;
#endif

		for (int i=0; i < bodyCount; i++)
        {
#ifdef AVMPLUS_VERBOSE
			int offset = (int)(pos-startpos);
#endif

			uint32_t method_index = readU30(pos);
			MethodInfo* info = resolveMethodInfo(method_index);

			const byte *body_pos = pos;

            int max_stack = readU30(pos);
            (void)max_stack;
            
            int local_count = readU30(pos);
			(void)local_count;

			// can't do this check here because param_count isn't available
			// until the method is resolved. (we could do some tricks to extract
			// it, but we just defer this check to Verifier::verify instead.)
			//if (local_count < info->param_count()+1)
			//{
			//	// must have enough locals to hold all parameters including this
			//	toplevel->throwVerifyError(kCorruptABCError);
			//}

			// TODO change file format, just want local max_scope
			int init_scope_depth = readU30(pos);
			(void)init_scope_depth;
			
			int max_scope_depth = readU30(pos);
			(void)max_scope_depth;

			int code_length = readU30(pos);

			if (code_length <= 0
#ifdef VMCFG_AOT
				&& !info->needActivation() // AOT allows a dummy body so that it can represent activation traits
#endif
				) 
			{
				toplevel->throwVerifyError(kInvalidCodeLengthError, core->toErrorString(code_length));
			}

			// check to see if we are trying to jump past the file end or the beginning.
			if ( pos < abcStart || pos+code_length >= abcEnd )
				toplevel->throwVerifyError(kCorruptABCError);
            pos += code_length;

            int exception_count = readU30(pos);

			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console << "    " << offset << ":method["<<method_index<<"] max_stack=" << max_stack
					<< " local_count=" << local_count 
					<< " init_scope_depth=" << init_scope_depth 
					<< " max_scope_depth=" << max_scope_depth
					<< " code_length=" << code_length
					<< " exception_count=" << exception_count
				    << "\n";
			}
			#endif

			if (exception_count != 0) 
			{
				info->setHasExceptions();
				for (int i=0; i<exception_count; i++) 
				{
					// this will be parsed when method is verified.
					// see MethodInfo::resolveSignature

					#ifdef AVMPLUS_VERBOSE
					int from = readU30(pos);
					int to = readU30(pos);
					int target = readU30(pos);
					Multiname typeName;
					parseTypeName(pos, typeName);

					Multiname qn;
					uint32 name_index = (version != (46<<16|15)) ? readU30(pos) : 0;
					if (name_index != 0)
					{
						if (name_index >= pool->cpool_mn_offsets.size())
							toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(name_index), core->toErrorString(pool->constantCount));
						pool->parseMultiname(qn, name_index);
					}

					if (pool->isVerbose(VB_parse))
					{
						core->console << "            exception["<<i<<"] from="<< from
							<< " to=" << to
							<< " target=" << target 
							<< " type=" << typeName
							<< " name=";
						if (name_index)
						{
							core->console << qn;
						}
						else
						{
							core->console << "(none)";
						}
						core->console << "\n";
					}
					#else
					readU30(pos); // from
					readU30(pos); // to
					readU30(pos); // target
					readU30(pos); // type name
					if (version != (46<<16|15))
					{
						const uint32 name_index = readU30(pos); // variable name
						if (name_index >= pool->cpool_mn_offsets.size())
							toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(name_index), core->toErrorString(pool->constantCount));
					}
					#endif
				}
			}

			if (info->hasMethodBody())
			{
				// Interface methods should not have bodies
				Traits* declaringTraits = info->declaringTraits();
				if (declaringTraits && declaringTraits->isInterface())
				{
					toplevel->throwVerifyError(kIllegalInterfaceMethodBodyError, core->toErrorString(info));
				}

#ifdef DEBUGGER
				if (core->debugger())
				{
					DebuggerMethodInfo* dmi = DebuggerMethodInfo::create(core, local_count, code_length, max_scope_depth - init_scope_depth);
					pool->_method_dmi.set(method_index, dmi);
				}
#endif

				// if non-zero, we have a duplicate method body - throw a verify error
				if (info->abc_body_pos())
				{
					toplevel->throwVerifyError(kDuplicateMethodBodyError, core->toErrorString(info));
				}
				
				AvmAssert(!info->isResolved());
				info->set_abc_body_pos(body_pos);

				// there will be a traits_count here, even if NEED_ACTIVATION is not
				// set.  So we parse the same way all the time.  We could reduce file size and
				// memory by omitting the count + traits completely.

				const byte* traits_pos = pos;
				int nameCount = readU30(pos);
				if (info->needActivation() || nameCount > 0)
				{
					pos = traits_pos;
					Namespacep ns = NULL;
					Stringp name = NULL;
					#ifdef AVMPLUS_VERBOSE
					if (core->config.methodNames)
					{
						ns = core->getPublicNamespace(pool);
						name = core->internString(info->getMethodNameWithTraits(declaringTraits));
					}
					#endif
					// activation traits are raw types, not subclasses of object.  this is
					// okay because they aren't accessable to the programming model.
					Traits* act = parseTraits(sizeof(ScriptObject),
																sizeof(ScriptObject), 
																NULL, 
																ns, 
																name, 
																NULL, 
																traits_pos,
																TRAITSTYPE_ACTIVATION, 
																NULL);
					act->final = true;
					info->init_activationTraits(act);
				}
				else
				{
					// TODO remove this assert once abc format is adjusted
					AvmAssert(nameCount == 0);
				}
			}
			else
			{
#ifdef VMCFG_AOT
				if (info->needActivation())
				{
					Namespacep ns = NULL;
					Stringp name = NULL;
					#ifdef AVMPLUS_VERBOSE
					if (core->config.methodNames)
					{
						ns = core->getPublicNamespace(pool);
						name = core->internString(info->getMethodNameWithTraits(info->declaringTraits()));
					}
					#endif
					// activation traits are raw types, not subclasses of object.  this is
					// okay because they aren't accessable to the programming model.
					Traits* act = parseTraits(sizeof(ScriptObject), 
											  sizeof(ScriptObject),
											  NULL, 
											  ns, 
											  name, 
											  NULL, 
											  pos,
											  TRAITSTYPE_ACTIVATION, 
											  NULL);
						act->final = true;
						info->init_activationTraits(act);
						pool->aotInfo->activationTraits[method_index] = act;
				} else
#endif
				{
					// native methods should not have bodies!
					toplevel->throwVerifyError(kIllegalNativeMethodBodyError, core->toErrorString(info));
				}
			}
    	}
    }

    void AbcParser::parseCpool(API api)
    {
		pool = new (core->GetGC()) PoolObject(core, code, pos, api);
		pool->domain = domain;
		
#ifdef VMCFG_AOT
		AvmAssert(natives != 0);
		pool->isBuiltin = natives->hasBuiltins();
		pool->aotInfo = natives->get_aotInfo();
#else
		pool->isBuiltin = (natives != NULL);
#endif

		uint32 int_count = readU30(pos);
		// sanity check to prevent huge allocations
		if (int_count > (uint32)(abcEnd - pos)) 
			toplevel->throwVerifyError(kCorruptABCError);

		List<int>& cpool_int = pool->cpool_int;
		cpool_int.ensureCapacity(int_count);
		pool->constantIntCount = int_count;

#ifdef AVMPLUS_VERBOSE
		pool->verbose_vb = core->config.verbose_vb; // pool picks up global settings
#endif

#ifdef AVMPLUS_VERBOSE
		const byte* startpos = pos;
#endif

		for(uint32_t i = 1; i < int_count; ++i)
		{
#ifdef AVMPLUS_VERBOSE
			int offset = (int)(pos-startpos);
#endif
			// S32 value
			cpool_int.set(i, readS32(pos));
			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console << "    " << offset << ":" << "cpool_int["<<(uint32_t)i<<"]="
					<<constantNames[CONSTANT_Int] << " ";
				core->console << cpool_int[i] << "\n";
			}
			#endif
		}

		uint32 uint_count = readU30(pos);
		if (uint_count > (uint32)(abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		List<uint32>& cpool_uint = pool->cpool_uint;
		cpool_uint.ensureCapacity(uint_count);
		pool->constantUIntCount = uint_count;

#ifdef AVMPLUS_VERBOSE
		startpos = pos;
#endif

		for(uint32_t i = 1; i < uint_count; ++i)
		{
#ifdef AVMPLUS_VERBOSE
			int offset = (int)(pos-startpos);
#endif
			// U32 value
			cpool_uint.set(i, (unsigned)readS32(pos));

			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console << "    " << offset << ":" << "cpool_uint["<<i<<"]="
					<<constantNames[CONSTANT_UInt] << " ";
				core->console << (double)cpool_uint[i];
				core->console << "\n";
			}
			#endif
		}

		uint32 double_count = readU30(pos);
		if (double_count > (uint32)(abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		List<double*, LIST_GCObjects>& cpool_double = pool->cpool_double;
		cpool_double.ensureCapacity(double_count);
		pool->constantDoubleCount = double_count;

#ifdef AVMPLUS_VERBOSE
		startpos = pos;
#endif

		for(uint32_t i = 1; i < double_count; ++i)
		{
#ifdef AVMPLUS_VERBOSE
			int offset = (int)(pos-startpos);
#endif
			double value = readDouble(pos);
			cpool_double.set(i, (double*)(core->allocDouble(value)&~7));
			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console << "    " << offset << ":" << "cpool_double["<<i<<"]="
					<<constantNames[CONSTANT_Double] << " ";
				core->console << *cpool_double[i];
				core->console << "\n";
			}
			#endif
		}

		uint32 string_count = readU30(pos);
		if (string_count > (uint32)(abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		MMGC_MEM_TYPE(pool);
		pool->setupConstantStrings(string_count);

#ifdef AVMPLUS_VERBOSE
		startpos = pos;
#endif

		pool->_abcStringStart = pos;

		PoolObject::ConstantStringData* dataP = pool->_abcStrings.data;
		AvmAssert(core->kEmptyString != NULL);
		dataP->str = core->kEmptyString;
		for(uint32_t i = 1; i < string_count; ++i)
		{
#ifdef AVMPLUS_VERBOSE
			int offset = (int)(pos-startpos);
#endif
			// save the byte position into the cpool array
			(++dataP)->abcPtr = pos;
			// number of characters
			// todo - is compiler emitting no. of chars or no. of bytes?
			int len = readU30(pos);

			// check to see if we are trying to read past the file end or the beginning.
            // Also check for valid UTF8.
			if (pos < abcStart || pos+len >= abcEnd || 
                UnicodeUtils::Utf8ToUtf16((const uint8*) pos, len, NULL, 0, true) < 0)
            {
                // if we throw a verify error here, _abcStringEnd will never be set, and _abcStrings
                // will be left in an inconsistent state. having _abcStringStart set but not _abcStringEnd
                // can cause dynamicizeStrings to make poor decisions. So clean up before throwing.
                pool->_abcStringStart = NULL;
                pool->_abcStringEnd = NULL;
                VMPI_memset(pool->_abcStrings.data, 0, string_count*sizeof(PoolObject::ConstantStringData*));
				toplevel->throwVerifyError(kCorruptABCError);
            }

#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console << "    " << offset << ":" << "cpool_string["<<i<<"]="
					<< constantNames[CONSTANT_Utf8] << " ";
				core->console.write(pos, len);
				core->console << "\n";
			}
#endif
			// skip the UTF-8 string
			pos += len;
		}
		pool->_abcStringEnd = pos;

		uint32 ns_count = readU30(pos);
		if (ns_count > (uint32)(abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		List<Namespacep> &cpool_ns = pool->cpool_ns;

		MMGC_MEM_TYPE(pool);
		cpool_ns.ensureCapacity(ns_count);
		pool->constantNsCount = ns_count;

#ifdef AVMPLUS_VERBOSE
		startpos = pos;
#endif
		for( uint32_t i = 1; i < ns_count; ++i )
		{
#ifdef AVMPLUS_VERBOSE
			int offset = (int)(pos-startpos);
#endif
			CHECK_POS(pos);
			CPoolKind kind = (CPoolKind) *(pos++);
			switch(kind)
			{
				case CONSTANT_Namespace:
                case CONSTANT_PackageNamespace:
                case CONSTANT_PackageInternalNs:
                case CONSTANT_ProtectedNamespace:
			    case CONSTANT_ExplicitNamespace:
                case CONSTANT_StaticProtectedNs:
				{
					uint32 index = readU30(pos);
                    Namespace::NamespaceType type = Namespace::NS_Public;
                    switch(kind)
                    {
                    case CONSTANT_PackageInternalNs:
                        type = Namespace::NS_PackageInternal;
                        break;
                    case CONSTANT_ProtectedNamespace:
                        type = Namespace::NS_Protected;
                        break;
                    case CONSTANT_ExplicitNamespace:
                        type = Namespace::NS_Explicit;
						break;
                    case CONSTANT_StaticProtectedNs:
                        type = Namespace::NS_StaticProtected;
                        break;
                    }

                    if (index)
					{
						Stringp uri = resolveUtf8(index);
						API api = ApiUtils::getURIAPI(core, uri);
						if (api) {
							uri = ApiUtils::getBaseURI(core, uri);
						}
						else {
							if (pool->isBuiltin) {
								// builtins are by default in the largest version
								api = ApiUtils::getLargestAPI(core);
							}
							else {
								api = pool->getAPI();
							}

							// finally, if it has as version mark then strip it. this only happens
							// when asc and avm are out of sync, which is a contingency we support
							if (ApiUtils::hasVersionMark(uri))
								uri = ApiUtils::getBaseURI(core, uri);
						}
						Namespacep ns = core->internNamespace(core->newNamespace(uri, type, api));
						cpool_ns.set(i, ns);
					}
					else
					{
						// issue this looks wrong.  should uri be ""?
						Atom uri = undefinedAtom;
						cpool_ns.set(i, core->internNamespace(core->newNamespace(uri, type)));
					}
					break;
				}

				case CONSTANT_PrivateNs: 
				{
					uint32 index =  readU30(pos);
					Stringp uri = index ? resolveUtf8(index) : (Stringp)core->kEmptyString;
                    Namespacep ns = new (core->GetGC()) Namespace(nullStringAtom, uri, Namespace::NS_Private);
					cpool_ns.set(i, ns);
					break;
				}
				default:
				{
					toplevel->throwVerifyError(kCpoolEntryWrongTypeError, core->toErrorString(i));
				}
			}
			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console << "    " << offset << ":" << "cpool_ns["<<i<<"]="
					<<constantNames[kind] << " ";
				core->console << core->format(cpool_ns[i]->atom());
				core->console << "\n";
			}
			#endif
		}

		uint32 ns_set_count = readU30(pos);
		if (ns_set_count > (uint32)(abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		List<NamespaceSetp>& cpool_ns_set = pool->cpool_ns_set;
		cpool_ns_set.ensureCapacity(ns_set_count);
		pool->constantNsSetCount = ns_set_count;

#ifdef AVMPLUS_VERBOSE
		startpos = pos;
#endif

		for( uint32_t i = 1; i < ns_set_count; ++i)
		{
#ifdef AVMPLUS_VERBOSE
			int offset = (int)(pos-startpos);
#endif
			uint32 ns_count = readU30(pos);
			
			if (ns_count > (uint32)(abcEnd - pos))
				toplevel->throwVerifyError(kCorruptABCError);

			NamespaceSet* namespace_set = NamespaceSet::_create(core->GetGC(), ns_count);
			for(uint32 j=0; j < ns_count; ++j)
			{
				Namespacep ns = parseNsRef(pos);
				if (!ns)
					toplevel->throwVerifyError(kIllegalNamespaceError);
				namespace_set->_initNsAt(j, ns);
			}
			cpool_ns_set.set(i, namespace_set);

			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console << "    " << offset << ":" << "cpool_ns_set["<<i<<"]="
					<<constantNames[CONSTANT_NamespaceSet] << " ";
				core->console << cpool_ns_set[i]->format(core);
				core->console << "\n";
			}
			#endif
		}

		uint32 mn_count = readU30(pos);
		if (mn_count > (uint32)(abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		List<uint32_t>& cpool_mn_offsets = pool->cpool_mn_offsets;

		MMGC_MEM_TYPE(pool);
		cpool_mn_offsets.ensureCapacity(mn_count);

		for(uint32_t i = 1; i < mn_count; ++i )
		{
			CHECK_POS(pos);
			uint32_t const offset = uint32_t(pos - pool->_abcStart);
			cpool_mn_offsets.set(i, offset);
			CPoolKind kind = (CPoolKind)*pos++;
			switch(kind)
			{
			case CONSTANT_Qname: 
			case CONSTANT_QnameA:
			{
				// U16 namespace_index
				// U16 name_index
				// parse a multiname with one namespace (aka qname)
				parseNsRef(pos);
				parseName(pos);
				break;
			}

			case CONSTANT_RTQname:
			case CONSTANT_RTQnameA: 
			{
				// U16 name_index
				// parse a multiname with just a name; ns fetched at runtime
				parseName(pos);
				break;
			}
			case CONSTANT_RTQnameL:
			case CONSTANT_RTQnameLA:
			{
				break;
			}

			case CONSTANT_Multiname:
			case CONSTANT_MultinameA:
			{
				parseName(pos);
				
				uint32 index = readU30(pos);

				if (!index || index >= pool->constantNsSetCount)
					toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(index), core->toErrorString(pool->constantNsSetCount));

				// If it is in the range of Namespace Sets then it must be a namespace set/
				break;
			}

			case CONSTANT_MultinameL:
			case CONSTANT_MultinameLA:
			{
				uint32 index = readU30(pos);

				if (!index || index >= pool->constantNsSetCount)
					toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(index), core->toErrorString(pool->constantNsSetCount));

				// If it is in the range of Namespace Sets then it must be a namespace set.

				break;
			}
			
			case CONSTANT_TypeName:
			{
				uint32 index = readU30(pos);

                // compare index against mn_count, *not* cpool_mn_offsets.size(), as the latter is still being built...
                // it's ok to forward-reference here.
				if(!index || index >= mn_count)
					toplevel->throwVerifyError(kCpoolIndexRangeError, core->toErrorString(index), core->toErrorString(mn_count));

				index = readU30(pos);
				if(index != 1)
					toplevel->throwVerifyError(kCorruptABCError);
				readU30(pos);
				break;
			}
			default:
				toplevel->throwVerifyError(kCpoolEntryWrongTypeError, core->toErrorString(i));
			}
			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console << "    " << offset << ":" << "cpool_mn["<<i<<"]="
					<<constantNames[kind] << " ";
				Multiname name;
				pool->parseMultiname(name, i);
				core->console << name;
				core->console << "\n";
			}
			#endif
		}
    }

    void AbcParser::addNamedTraits(NamespaceSetp nss, Stringp name, Traits* itraits)
    {
        // check to see if the base namespace has been added, if so then
        // all versions have been added
        Namespace* ns = nss->nsAt(0);
        if (!ns->isPrivate()) {
			// compute the compatible apis for all namespaces and construct a namespace
			// with that composite api
			API apis = 0;
            for (NamespaceSetIterator iter(nss); iter.hasNext();) 
            {
                Namespacep nsi = iter.next();
				AvmAssert(pool->isBuiltin && ApiUtils::isVersionedNS(core, nsi->getType(), nsi->getURI()) ? nsi->getAPI() != 0 : true);
				apis |= ApiUtils::getCompatibleAPIs(core, nsi->getAPI());
			}
			ns = ApiUtils::getVersionedNamespace(core, ns, apis);
			if (!domain->getNamedTrait(name, ns)) {
				domain->addNamedTrait(name, ns, itraits);
			}
		}
        else {
            // duplicate class
            //Multiname qname(ns,name);
            //toplevel->definitionErrorClass()->throwError(kRedefinedError, core->toErrorString(&qname));
        }
    }

	void AbcParser::addNamedTraits(Namespacep ns, Stringp name, Traits* itraits)
	{
		addNamedTraits(NamespaceSet::create(core->GetGC(), ns), name, itraits);
	}

	void AbcParser::addNamedScript(NamespaceSetp nss, Stringp name, MethodInfo* script)
	{
		Namespacep ns = nss->nsAt(0); // just need one
		if (ns->isPrivate()) 
		{
			pool->addPrivateNamedScript(name, ns, script);
		}
		else 
		{
			// use the first namespace to see if its been added
			MethodInfo* s = domain->getNamedScript(name, ns);
			if (!s)
			{
				API apis = 0;
                for (NamespaceSetIterator iter(nss); iter.hasNext();) 
                {
                    Namespacep nsi = iter.next();
					AvmAssert(pool->isBuiltin && ApiUtils::isVersionedNS(core, nsi->getType(), nsi->getURI()) ? nsi->getAPI() != 0 : true);
					apis |= ApiUtils::getCompatibleAPIs(core, nsi->getAPI());
				}
				ns = ApiUtils::getVersionedNamespace(core, ns, apis);
				domain->addNamedScript(name, ns, script);
			}
			else
			{
				// duplicate definition
				//Multiname qname(ns, name);
				//toplevel->definitionErrorClass()->throwError(kRedefinedError, core->toErrorString(&qname));
			}
		}
	}

	bool AbcParser::parseScriptInfos()
	{
		/*
			U16 script_count
			ScriptInfo[script_count]
			{
				U16 init_index			// method_info index of init function
				Traits script_traits    // traits for the global object of this package
			}
		*/

		uint32_t count = readU30(pos);

		#ifdef AVMPLUS_VERBOSE
		if(pool->isVerbose(VB_parse)) {
			core->console << "script_count=" << count << "\n";
		}
		#endif

#ifdef AVMPLUS_VERBOSE
		const byte* startpos = pos;
#endif

		if (count == 0)
		{
			return true;
		}

		if (count > (uint32)(abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		pool->_scripts.ensureCapacity(count);

		// make global objects subclasses of Object

		for (uint32_t i=0; i < count; i++)
		{
			const byte* script_pos = pos;

			int init_index = readU30(pos);

			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console << "    " << (int)(script_pos-startpos) << ":script[" << i << "]"
					<< " init_index=" << init_index
					<< "\n";
			}
			#endif
			MethodInfo* script = resolveMethodInfo(init_index);
			Traits* declaringTraits = script->declaringTraits();

			if (declaringTraits != NULL)
			{
				// method has already been bound to a different type.  Can't bind it twice because
				// it can only have one environment, for its scope chain and super references.
				toplevel->throwVerifyError(kAlreadyBoundError, core->toErrorString(script), core->toErrorString(declaringTraits));
			}

			Traits* traits = parseTraits(sizeof(ScriptObject),
											sizeof(ScriptObject),
											core->traits.object_itraits, 
											core->getPublicNamespace(pool), 
											core->kglobal, 
											script, 
											script_pos,
											TRAITSTYPE_SCRIPT,
											NULL);

			if( !traits ) return false; // parseTraits failed

			
			// global object, make it dynamic
			traits->set_needsHashtable(true);
			traits->final = true;

			script->makeMethodOf(traits);
			traits->init = script;

            #if defined FEATURE_NANOJIT
			if (core->config.runmode == RM_mixed || core->config.runmode == RM_interp_all)
			{
				// suggest that we don't jit the $init methods
				script->setSuggestInterp();
			}
			#endif

			pool->_scripts.set(i, traits);
#ifdef VMCFG_AOT
			pool->aotInfo->scriptTraits[i] = traits;
#endif
		}

		return true;
	}

	bool AbcParser::parseInstanceInfos()
	{
		classCount = readU30(pos);
#ifdef AVMPLUS_VERBOSE
		if(pool->isVerbose(VB_parse)) {
			core->console << "class_count=" << classCount <<"\n";
		}
#endif

#ifdef AVMPLUS_VERBOSE
		const byte* startpos = pos;
#endif

		if (classCount == 0)
		{
			return true;
		}

		if (classCount > uintptr_t(abcEnd - pos))
			toplevel->throwVerifyError(kCorruptABCError);

		// allocate room for class infos early, to handle nested classes
		pool->_classes.ensureCapacity(classCount);

		instances.ensureCapacity(classCount);

		for (uint32_t i=0; i < classCount; i++)
		{
			const byte* instancepos = pos;

			// CONSTANT_QName name of this class

			Multiname mn;
			resolveQName(pos, mn);
			Namespacep ns;
			Stringp name;
			name = mn.getName();
			const NamespaceSet* nss;
			if (mn.namespaceCount() > 1) 
			{
				nss = mn.getNsset();
				ns = nss->nsAt(0);
			}
			else 
			{
				ns = mn.getNamespace();
				nss = NamespaceSet::create(core->GetGC(), ns);
			}

			// resolving base class type means class heirarchy must be a Tree
			Traits* baseTraits = pool->resolveTypeName(pos, toplevel);

			if ((baseTraits && baseTraits->final) ||
				(CLASS_TYPE != NULL && baseTraits == CLASS_TYPE) ||
				// note, builtins are allowed to override Function
				(FUNCTION_TYPE != NULL && baseTraits == FUNCTION_TYPE && !pool->isBuiltin))
			{
				// error - attempt to extend final class
                #ifdef AVMPLUS_VERBOSE
				if(pool->isVerbose(VB_parse)) {
					core->console << mn << " can't extend final class " << baseTraits << "\n";
				}
                #endif
				toplevel->throwVerifyError(kCannotExtendFinalClass, core->toErrorString(&mn));
			}

			if (baseTraits && baseTraits->isInterface())
			{
				// error, can't extend interface
				toplevel->throwVerifyError(kCannotExtendError, core->toErrorString(&mn), core->toErrorString(baseTraits));
			}

			// read flags:	bit 0: sealed
			//				bit 1: final
			//				bit 2: interface
			//				bit 3: protected
			CHECK_POS(pos);
			int flags = *pos++;

			// read protected namespace
			Namespacep protectedNamespace = NULL;
			if (flags & 8)
			{
				protectedNamespace = parseNsRef(pos);
			}
			
			int interfaceCount = readU30(pos);
			const byte* interfacePos = pos;

			if(interfaceCount)
			{
				if (interfaceCount >= 0x10000000)
					toplevel->throwVerifyError(kCorruptABCError);

				for( int x = 0; x < interfaceCount; ++ x )
				{
					Traits *t = pool->resolveTypeName(pos, toplevel);
					if (!t || !t->isInterface())
					{
						// error, can't implement non-interface type
						toplevel->throwVerifyError(kCannotImplementError, core->toErrorString(&mn), core->toErrorString(t));
					}
				}
			}

			// TODO make sure the inheritance is legal.	 
			//	- can't override final members
			//	- overrides agree with base class signature
			
			uint32_t iinit_index = readU30(pos);
			MethodInfo* iinit = resolveMethodInfo(iinit_index);

#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				// TODO:  fixup this math here, since the 2's are all wrong
				core->console
					<< "	" << (int)(instancepos-startpos) << ":instance[" << i << "]"
					<< " " << mn;

				if (baseTraits)
					core->console << " extends " << baseTraits;

				core->console
					<< " interface_count=" << interfaceCount
					<< " iinit_index=" << iinit_index
					<< "\n";
			}
#endif
			TraitsPosType postype = (flags & 4) ? TRAITSTYPE_INTERFACE : TRAITSTYPE_INSTANCE;
			uint16_t sizeofInstance = 0;
			uint16_t offsetofSlots = 0;
			computeInstanceSizeAndSlotsOffset(i, baseTraits, sizeofInstance, offsetofSlots);
			Traits* itraits = parseTraits(sizeofInstance, 
										  offsetofSlots,  
										  baseTraits, 
										  ns, 
										  name, 
										  0, 
										  instancepos,
										  postype, 
										  protectedNamespace);
			if( !itraits ) return false;
			if (!baseTraits && core->traits.object_itraits == NULL)
			{
				// save object traits
				core->traits.object_itraits = itraits;
				itraits->builtinType = BUILTIN_object;
			}

			// AS3 language decision: dynamic is not inherited.
			itraits->set_needsHashtable((flags&1) == 0);
			itraits->final	 = (flags&2) != 0;

			if (itraits->isInterface())
			{
				// check for slotCount != 0 now done at resolve time

				// interface base must be *
				if (baseTraits)
				{
					// error, can't extend this type
					toplevel->throwVerifyError(kCannotExtendError, core->toErrorString(&mn), core->toErrorString(baseTraits));
				}
			}

			Traits* declaringTraits = iinit->declaringTraits();
			if (declaringTraits != NULL)
			{
				// method has already been bound to a different type.  Can't bind it twice because
				// it can only have one environment, for its scope chain and super references.
				toplevel->throwVerifyError(kAlreadyBoundError, core->toErrorString(iinit), core->toErrorString(declaringTraits));
			}

			iinit->makeMethodOf(itraits);
			itraits->init = iinit;

#ifdef AVMPLUS_VERBOSE
			// print the interfaces.  interfaces have been resolved above so any
			// errors would have been reported earlier.
			for (int j=0, n=interfaceCount; j < n; j++)
			{
				Traits *interfaceTraits = pool->resolveTypeName(interfacePos, toplevel);
				if(pool->isVerbose(VB_parse)) {
					core->console << "		  interface["<<j<<"]=" << interfaceTraits <<"\n";
				}
			}
#else
			(void)interfacePos;
#endif
						
			instances.set(i, itraits);

			if (pool->getTraits(name, ns, false) == NULL)
			{
				pool->addNamedTraits(name, ns, itraits);
			}
			else
			{
				// error, can't redefine a class or interface
				//toplevel->definitionErrorClass()->throwError(kRedefinedError, core->toErrorString(&mn));
			}
		}

		return true;
    }

	void AbcParser::parseClassInfos()
    {
		if (classCount == 0)
		{
			return;
		}

#ifdef AVMPLUS_VERBOSE
		const byte* startpos = pos;
#endif

        for (uint32_t i=0; i < classCount; i++)
        {
            // CONSTANT_Multiname name of this class
			Traits* itraits = instances[i];
			Namespacep ns = itraits->ns();
			Stringp name = itraits->name();

			const byte* class_pos = pos;

			uint32_t cinit_index = readU30(pos);
            MethodInfo* cinit = resolveMethodInfo(cinit_index);

			#ifdef AVMPLUS_VERBOSE
			if(pool->isVerbose(VB_parse)) {
				core->console
					<< "    " << (int)(class_pos-startpos) << ":class[" << i << "]"
					<< " " << ns << "::" << name;

				core->console
					<< " cinit_index=" << cinit_index
					<< "\n";
			}
			#endif

			const NativeClassInfo* nativeEntry = natives ? natives->get_class(i) : NULL;
			bool haveClassNativeInfo = nativeEntry && nativeEntry->sizeofClass;
			Traits* ctraits = parseTraits(haveClassNativeInfo ? nativeEntry->sizeofClass : sizeof(ClassClosure),
											haveClassNativeInfo ? nativeEntry->offsetofSlotsClass : sizeof(ClassClosure), 
											CLASS_TYPE, 
											ns, 
											core->internString(core->concatStrings(name, core->newConstantStringLatin1("$"))), 
											NULL, 
											class_pos,
											TRAITSTYPE_CLASS, 
											itraits->protectedNamespace);

			ctraits->setCreateClassClosureProc(nativeEntry ? nativeEntry->createClassClosure : NULL);

			Traits* declaringTraits = cinit->declaringTraits();
			if (declaringTraits != NULL)
			{
				// method has already been bound to a different type.  Can't bind it twice because
				// it can only have one environment, for its scope chain and super references.
				toplevel->throwVerifyError(kAlreadyBoundError, core->toErrorString(cinit), core->toErrorString(declaringTraits));
			}
			
			cinit->makeMethodOf(ctraits);
			ctraits->init = cinit;
			ctraits->itraits = itraits;
			ctraits->final = true;
			ctraits->set_needsHashtable(true);

            #if defined FEATURE_NANOJIT
			if (core->config.runmode == RM_mixed || core->config.runmode == RM_interp_all)
			{
				// suggest that we don't jit the class initializer
				cinit->setSuggestInterp();
			}
			#endif

			pool->_classes.set(i, ctraits);
        }
    }

	uint32_t AbcParser::readU30(const byte*& p) const
	{
		// We have added kBufferPadding bytes to the end of the main swf buffer.
		// Why?  Here we can read from 1 to 5 bytes.  If we were to
		// put the required safety checks at each byte read, we would slow
		// parsing of the file down.  With this buffer, only one check at the
		// top of this function is necessary. (we will read on into our own memory)
		CHECK_POS(p);
		return toplevel->readU30(p);
	}

	double AbcParser::readDouble(const byte* &p) const
	{
		// check to see if we are trying to read past the file end.
		if (p < abcStart || p+7 >= abcEnd )
			toplevel->throwVerifyError(kCorruptABCError);

		union {
			double value;
			#if defined AVMPLUS_BIG_ENDIAN || defined VMCFG_DOUBLE_MSW_FIRST
				struct { uint32_t hi, lo; } words;
			#else
				struct { uint32_t lo, hi; } words;
			#endif
		};
		// the bytes in the abc are little endian but the words
		// in memory can be little endian or big endian.
		words.lo = p[0] | p[1]<<8 | p[2]<<16 | p[3]<<24;
		words.hi = p[4] | p[5]<<8 | p[6]<<16 | p[7]<<24;
		p += 8;
		return value;
	}
}
