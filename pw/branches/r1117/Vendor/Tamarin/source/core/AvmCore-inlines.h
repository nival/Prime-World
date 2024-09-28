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

#ifndef __avmplus_AvmCore_inlines__
#define __avmplus_AvmCore_inlines__

namespace avmplus
{

#ifdef VTUNE
REALLY_INLINE iJIT_IsProfilingActiveFlags AvmCore::CheckVTuneStatus() 
{
	iJIT_IsProfilingActiveFlags profiler = iJIT_IsProfilingActive();	
	return profiler;
}
#endif // VTUNE

#ifdef DEBUGGER
REALLY_INLINE Debugger* AvmCore::debugger() const 
{ 
	return _debugger; 
}

REALLY_INLINE Profiler* AvmCore::profiler() const 
{ 
	return _profiler; 
}

REALLY_INLINE Sampler* AvmCore::get_sampler() const 
{ 
	return _sampler; 
}

REALLY_INLINE void AvmCore::sampleCheck() 
{ 
	if (_sampler) 
		_sampler->sampleCheck(); 
}
#endif // DEBUGGER

REALLY_INLINE bool AvmCore::interruptCheck(bool interruptable)
{
	return interruptable && (interrupted != NotInterrupted);
}

REALLY_INLINE void AvmCore::branchCheck(MethodEnv *env, bool interruptable, int go)
{
	if (go < 0)
	{
#ifdef DEBUGGER
		sampleCheck();
#endif
		if (interruptCheck(interruptable))
			handleInterruptMethodEnv(env);
	}
}

REALLY_INLINE QCache* AvmCore::tbCache() 
{ 
	return m_tbCache; 
}

REALLY_INLINE QCache* AvmCore::tmCache() 
{ 
	return m_tmCache; 
}

REALLY_INLINE QCache* AvmCore::msCache() 
{ 
	return m_msCache; 
}

#ifdef FEATURE_NANOJIT // accessors

REALLY_INLINE bool AvmCore::quiet_opt() const 
{ 
	return false; 
} 

#if defined AVMPLUS_IA32 || defined AVMPLUS_AMD64
REALLY_INLINE bool AvmCore::use_sse2() const 
{ 
	return config.sse2; 
}
#endif

#endif // FEATURE_NANOJIT

#ifdef AVMPLUS_VERBOSE
REALLY_INLINE /*static*/ bool AvmCore::isBitSet(uint32_t v, uint32_t bit) 
{ 
	return (v&bit) ? true : false; 
} 

REALLY_INLINE bool AvmCore::isVerbose(uint32_t b) const 
{ 
	return isBitSet(config.verbose_vb, b); 
}
#endif // AVMPLUS_VERBOSE

REALLY_INLINE void AvmCore::SetJITEnabled(bool isEnabled) 
{
#if defined FEATURE_NANOJIT
	config.runmode = (isEnabled) ? RM_mixed : RM_interp_all;
#else
	(void)isEnabled;
#endif
}

REALLY_INLINE bool AvmCore::IsJITEnabled() const 
{
#if defined FEATURE_NANOJIT
	return (config.runmode == RM_mixed || config.runmode == RM_jit_all) ? true : false;
#else
	return false;
#endif
}

REALLY_INLINE bool AvmCore::JITMustSucceed() const 
{
#if defined FEATURE_NANOJIT
	return config.jitordie;
#else
	return false;
#endif
}

REALLY_INLINE void AvmCore::stackCheck(MethodEnv* env)
{
	// Take the address of a local variable to get stack pointer
	void* dummy;
	//fprintf(stderr, "%p\n", &dummy);
	if ((uintptr_t)&dummy < minstack)
		handleStackOverflowMethodEnv(env);
}

REALLY_INLINE void AvmCore::stackCheck(Toplevel* toplevel)
{
	// Take the address of a local variable to get stack pointer
	void* dummy;
	//fprintf(stderr, "%p\n", &dummy);
	if ((uintptr_t)&dummy < minstack)
		handleStackOverflowToplevel(toplevel);
}

REALLY_INLINE /*static*/ bool AvmCore::isObject(Atom atom)
{
	return atomKind(atom) == kObjectType && !isNull(atom);
}

REALLY_INLINE /*static*/ bool AvmCore::isPointer(Atom atom)
{
	return atomKind(atom) < kSpecialType || atomKind(atom) == kDoubleType;
}

REALLY_INLINE /*static*/ bool AvmCore::isNamespace(Atom atom)
{
	return atomKind(atom) == kNamespaceType && !isNull(atom);
}

REALLY_INLINE /*static*/ BindingKind AvmCore::bindingKind(Binding b)
{
	return BindingKind(uintptr_t(b) & 7);
}

REALLY_INLINE /*static*/ bool AvmCore::isMethodBinding(Binding b)
{
	return bindingKind(b) == BKIND_METHOD;
}

REALLY_INLINE /*static*/ bool AvmCore::isAccessorBinding(Binding b)
{
	return bindingKind(b) >= BKIND_GET;
}

REALLY_INLINE /*static*/ bool AvmCore::hasSetterBinding(Binding b)
{
	return (bindingKind(b) & 6) == BKIND_SET;
}

REALLY_INLINE /*static*/ bool AvmCore::hasGetterBinding(Binding b)
{
	return (bindingKind(b) & 5) == BKIND_GET;
}

REALLY_INLINE /*static*/ int AvmCore::bindingToGetterId(Binding b)
{
	AvmAssert(hasGetterBinding(b));
	return int(uintptr_t(b)) >> 3;
}

REALLY_INLINE /*static*/ int AvmCore::bindingToSetterId(Binding b)
{
	AvmAssert(hasSetterBinding(b));
	return 1 + (int(uintptr_t(b)) >> 3);
}

REALLY_INLINE /*static*/ int AvmCore::bindingToMethodId(Binding b)
{
	AvmAssert(isMethodBinding(b));
	return int(uintptr_t(b)) >> 3;
}

REALLY_INLINE /*static*/ int AvmCore::bindingToSlotId(Binding b)
{
	AvmAssert(isSlotBinding(b));
	return int(uintptr_t(b)) >> 3;
}

REALLY_INLINE /*static*/ int AvmCore::isSlotBinding(Binding b)
{
	AvmAssert((BKIND_CONST & 6)==BKIND_VAR);
	return (bindingKind(b) & 6) == BKIND_VAR;
}

REALLY_INLINE /*static*/ Binding AvmCore::makeSlotBinding(uintptr_t id, BindingKind kind)
{
	AvmAssert(kind == BKIND_VAR || kind == BKIND_CONST);
	return Binding((id << 3) | kind);
}

REALLY_INLINE /*static*/ Binding AvmCore::makeMGSBinding(uintptr_t id, BindingKind kind)
{
	AvmAssert(kind == BKIND_METHOD || kind == BKIND_GET || kind == BKIND_SET);
	return Binding((id << 3) | kind);
}

REALLY_INLINE /*static*/ Binding AvmCore::makeGetSetBinding(Binding b)
{
	AvmAssert(bindingKind(b) == BKIND_GET || bindingKind(b) == BKIND_SET);
	return Binding((uintptr_t(b) & ~7) | BKIND_GETSET);
}

REALLY_INLINE /*static*/ int AvmCore::isVarBinding(Binding b)
{
	return bindingKind(b) == BKIND_VAR;
}

REALLY_INLINE /*static*/ int AvmCore::isConstBinding(Binding b)
{
	return bindingKind(b) == BKIND_CONST;
}

REALLY_INLINE bool AvmCore::isFunction(Atom atom)
{
	return istype(atom, traits.function_itraits);
}

/** Helper method; returns true if atom's type is double */
REALLY_INLINE /*static*/ bool AvmCore::isDouble(Atom atom)
{
	return atomKind(atom) == kDoubleType;
}

REALLY_INLINE /*static*/ bool AvmCore::isNumber(Atom atom)
{
	// accept kIntptrType(6) or kDoubleType(7)
    MMGC_STATIC_ASSERT(kIntptrType == 6 && kDoubleType == 7);
	return (atom&6) == kIntptrType;
}

REALLY_INLINE /*static*/ bool AvmCore::isBoolean(Atom atom)
{
	return atomKind(atom) == kBooleanType;
}

REALLY_INLINE /*static*/ bool AvmCore::isNull(Atom atom)
{
	return ISNULL(atom);
}

REALLY_INLINE /*static*/ bool AvmCore::isUndefined(Atom atom)
{
	return (atom == undefinedAtom);
}

REALLY_INLINE /*static*/ bool AvmCore::isNullOrUndefined(Atom atom)
{
	return ((uintptr)atom) <= (uintptr)kSpecialType;
}

REALLY_INLINE int32_t AvmCore::getActiveAPIs() 
{
	return this->active_api_flags;
}

REALLY_INLINE /*static*/ uint32_t AvmCore::toUInt32(Atom atom)
{
	return (uint32)integer(atom);
}

REALLY_INLINE /*static*/ double AvmCore::toInteger(Atom atom)
{
	if (atomIsIntptr(atom)) 
	{
		return (double) atomGetIntptr(atom);
	} 
	else 
	{
		return MathUtils::toInt(AvmCore::number(atom));
	}
}

#ifdef AVMPLUS_64BIT

REALLY_INLINE /*static*/ int64_t AvmCore::integer64(Atom atom)
{ 
	return (int64_t)integer(atom); 
}

REALLY_INLINE /*static*/ int64_t AvmCore::integer64_i(Atom atom)	
{ 
	return (int64_t)integer_i(atom); 
}

REALLY_INLINE /*static*/ int64_t AvmCore::integer64_d(double d)		
{ 
#ifdef AVMPLUS_AMD64
	return (int64_t)integer_d_sse2(d); 
#else
	return (int64_t)integer_d(d);
#endif
}

#ifdef AVMPLUS_AMD64
REALLY_INLINE /*static*/ int64_t AvmCore::integer64_d_sse2(double d)
{ 
	return (int64_t)integer_d_sse2(d); 
}
#endif

#endif // AVMPLUS_64BIT

REALLY_INLINE /*static*/ int32_t AvmCore::integer_i(Atom a)
{
	if (atomIsIntptr(a))
	{  
		intptr_t const i = atomGetIntptr(a);
		AvmAssert(i == int32_t(i));
		return int32_t(i);
	}
	else
	{
		// TODO since we know value is legal int, use faster d->i
		return MathUtils::real2int(atomToDouble(a));
	}
}

REALLY_INLINE /*static*/ uint32_t AvmCore::integer_u(Atom a)
{
	if (atomIsIntptr(a))
	{
		intptr_t const i = atomGetIntptr(a);
		AvmAssert(i == intptr_t(uint32_t(i)));
		return uint32_t(i);
	}
	else
	{
		// TODO figure out real2int for unsigned
		return (uint32_t) atomToDouble(a);
	}
}

#ifdef AVMPLUS_SSE2_ALWAYS
REALLY_INLINE /*static*/ int AvmCore::integer_d(double d) 
{
	return integer_d_sse2(d);
}
REALLY_INLINE Atom AvmCore::doubleToAtom(double n) 
{
	return doubleToAtom_sse2(n);
}
#else
// they are defined out-of-line
#endif // AVMPLUS_SSE2_ALWAYS

REALLY_INLINE /*static*/ double AvmCore::number_d(Atom a)
{
	AvmAssert(isNumber(a));

	if (atomIsIntptr(a))
		return (double)atomGetIntptr(a);
	else
		return atomToDouble(a);
}

REALLY_INLINE Atom AvmCore::intAtom(Atom atom)
{
	return intToAtom(AvmCore::integer(atom));
}

REALLY_INLINE Atom AvmCore::uintAtom(Atom atom)
{
	return uintToAtom(AvmCore::toUInt32(atom));
}

REALLY_INLINE /*static*/ bool AvmCore::isString(Atom atom)
{
	return atomKind(atom) == kStringType && !isNull(atom);
}

REALLY_INLINE /*static*/ bool AvmCore::isName(Atom atom)
{
	return isString(atom) && atomToString(atom)->isInterned();
}

/** Helper function; reads a signed 24-bit integer from pc */
REALLY_INLINE /*static*/ int AvmCore::readS24(const byte *pc)
{
	#ifdef AVMPLUS_UNALIGNED_ACCESS
		// unaligned short access still faster than 2 byte accesses
		return ((uint16_t*)pc)[0] | ((int8_t*)pc)[2]<<16;
	#else
		return pc[0] | pc[1]<<8 | ((int8_t*)pc)[2]<<16;
	#endif
}

/**
 * Returns the size of the instruction + all it's operands.  For OP_lookupswitch the size will not include
 * the size for the case targets.
 */
REALLY_INLINE /*static*/ int AvmCore::calculateInstructionWidth(const byte* p)
{
	int a, b;
	unsigned int c, d;
	const byte* p2 = p;
	readOperands(p2, c, a, d, b);
	return int(p2-p);
}

/** Helper function; reads an unsigned 16-bit integer from pc */
REALLY_INLINE /*static*/ int32_t AvmCore::readU16(const byte *pc)
{
	#ifdef AVMPLUS_UNALIGNED_ACCESS
		// unaligned short access still faster than 2 byte accesses
		return *((uint16_t*)pc);
	#else
		return pc[0] | pc[1]<<8;
	#endif
}

// note, return of true means we definitely DO NOT need a coerce, 
// but return of false still means we *might* need to (ie, negating the result of this function 
// isn't "needscoerce")
REALLY_INLINE /*static*/ bool AvmCore::atomDoesNotNeedCoerce(Atom a, BuiltinType bt)
{
	// cheat and use "kUnusedAtomTag" for all null values (streamlines the test)
	AvmAssert(atomKind(a) != kUnusedAtomTag);
	const int kind = isNull(a) ? kUnusedAtomTag : atomKind(a);
	return ((1<<bt) & k_atomDoesNotNeedCoerce_Masks[kind]) != 0;
}

REALLY_INLINE /*static*/ Atom AvmCore::istypeAtom(Atom atom, Traits* itraits) 
{ 
	return istype(atom, itraits) ? trueAtom : falseAtom; 
}

REALLY_INLINE /*static*/ Atom AvmCore::astype(Atom atom, Traits* expected)
{
	return istype(atom, expected) ? atom : nullObjectAtom;
}

// return true if there is a pending interrupt of the specific InterruptReason.
REALLY_INLINE bool AvmCore::interruptCheckReason(InterruptReason r) const
{
	AvmAssert(r != NotInterrupted);
	return interrupted == r;
}

REALLY_INLINE /*static*/ bool AvmCore::isXML(Atom atm)
{
	return isBuiltinType(atm, BUILTIN_xml);
}

REALLY_INLINE /*static*/ bool AvmCore::isXMLList(Atom atm)
{
	return isBuiltinType(atm, BUILTIN_xmlList);
}

REALLY_INLINE /*static*/ bool AvmCore::isXMLorXMLList(Atom atm)
{
	return isBuiltinTypeMask(atm, (1<<BUILTIN_xml)|(1<<BUILTIN_xmlList));
}

REALLY_INLINE /*static*/ bool AvmCore::isDate(Atom atm)
{
	return isBuiltinType(atm, BUILTIN_date);
}

REALLY_INLINE /*static*/ bool AvmCore::isQName(Atom atm)
{
	return isBuiltinType(atm, BUILTIN_qName);
}

REALLY_INLINE /*static*/ bool AvmCore::isDictionaryLookup(Atom key, Atom obj)
{
	return isObject(key) && isDictionary(obj);
}

REALLY_INLINE /*static*/ Namespacep AvmCore::atomToNamespace(Atom atom)
{
	AvmAssert(atomKind(atom)==kNamespaceType);
	return (Namespacep)atomPtr(atom);
}

REALLY_INLINE /*static*/ double AvmCore::atomToDouble(Atom atom)
{
	AvmAssert(atomKind(atom)==kDoubleType);
	return *(const double*)atomPtr(atom);
}

/**
 * Convert an Atom of kStringType to a Stringp
 * @param atom atom to convert.  Note that the Atom
 *             must be of kStringType
 */
REALLY_INLINE /*static*/ Stringp AvmCore::atomToString(Atom atom)
{
	AvmAssert(atomKind(atom)==kStringType);
	return (Stringp)atomPtr(atom);
}

// Avoid adding validation checks here and returning NULL.  If this
// is returning a bad value, the higher level function should be fixed
// or AbcParser/Verifier should be enhanced to catch this case.
REALLY_INLINE /*static*/ ScriptObject* AvmCore::atomToScriptObject(const Atom atom)
{
	AvmAssert(atomKind(atom)==kObjectType);
	return (ScriptObject*)atomPtr(atom);
}

// Helper function, allows generic objects to work with InlineHashtable
// and AtomArray, uses double type which is the only non-RC pointer tag.
// The key here is that these methods round-trip any pointer value to the
// same pointer value, there is no casting that might adjust the pointer.
#ifdef _DEBUG
// defined out-of-line
#else
REALLY_INLINE /*static*/ Atom AvmCore::genericObjectToAtom(const void* obj) 
{ 
	return (Atom)obj|kDoubleType; 
}
#endif			

REALLY_INLINE /*static*/ const void* AvmCore::atomToGenericObject(Atom a) 
{ 
	return atomPtr(a); 
}

REALLY_INLINE /*static*/ bool AvmCore::isGenericObject(Atom a) 
{ 
	return atomKind(a)==kDoubleType; 
}

REALLY_INLINE /*static*/ bool AvmCore::getIndexFromAtom(Atom a, uint32 *result)
{
	if (atomIsIntptr(a) && atomCanBeUint32(a))
	{
		*result = uint32_t(atomGetIntptr(a));
		return true;
	}
	else
	{
		AvmAssert(AvmCore::isString(a));
		return AvmCore::getIndexFromString(atomToString(a), result); 
	}
}

REALLY_INLINE Atom AvmCore::allocDouble(double n)
{
	union { 
		double *d;
		void *v;
	};
	v = GetGC()->AllocDouble();
	*d = n;
	return kDoubleType | (uintptr)v;
}

#ifdef VMCFG_LOOKUP_CACHE
REALLY_INLINE uint32_t AvmCore::lookupCacheTimestamp() const
{ 
	return lookup_cache_timestamp == ~0U ? 0 : lookup_cache_timestamp; 
}

REALLY_INLINE bool AvmCore::lookupCacheIsValid(uint32_t t) const
{ 
	return t == lookup_cache_timestamp; 
}

REALLY_INLINE void AvmCore::invalidateLookupCache() 
{ 
	if (lookup_cache_timestamp != ~0U) 
		++lookup_cache_timestamp; 
}
#endif // VMCFG_LOOKUP_CACHE

#ifdef VMCFG_NANOJIT
REALLY_INLINE void AvmCore::flushBindingCachesNextSweep() 
{ 
	m_flushBindingCachesNextSweep = true; 
}
#endif // VMCFG_NANOJIT

// NOTE, the code in enter/exit is replicated in CodegenLIR.cpp;
// if you make changes here, you may need to make changes there as well.
REALLY_INLINE void MethodFrame::enter(AvmCore* core, MethodEnv* e)
{
	AvmAssert(core->codeContextThread == VMPI_currentThread());
	AvmAssert(!(uintptr_t(e) & FLAGS_MASK));
	// implicitly leave IS_EXPLICIT_CODECONTEXT and DXNS_NOT_NULL clear
	this->envOrCodeContext = uintptr_t(e);
	this->next = core->currentMethodFrame;
	core->currentMethodFrame = this;
	#ifdef _DEBUG
	this->dxns = (Namespace*)(uintptr_t)0xdeadbeef;
	#endif
}

REALLY_INLINE void MethodFrame::enter(AvmCore* core, CodeContext* cc)
{
	AvmAssert(core->codeContextThread == VMPI_currentThread());
	AvmAssert(!(uintptr_t(cc) & FLAGS_MASK));
	// set IS_EXPLICIT_CODECONTEXT and leave DXNS_NOT_NULL clear
	this->envOrCodeContext = uintptr_t(cc) | IS_EXPLICIT_CODECONTEXT;
	this->next = core->currentMethodFrame;
	core->currentMethodFrame = this;
	#ifdef _DEBUG
	this->dxns = (Namespace*)(uintptr_t)0xdeadbeef;
	#endif
}

REALLY_INLINE void MethodFrame::exit(AvmCore* core)
{
	AvmAssert(core->codeContextThread == VMPI_currentThread());
	AvmAssert(core->currentMethodFrame == this);
	core->currentMethodFrame = this->next;
}

REALLY_INLINE CodeContext* MethodFrame::cc() const 
{
	return (envOrCodeContext & IS_EXPLICIT_CODECONTEXT)
		? (CodeContext*)(envOrCodeContext & ~FLAGS_MASK)
		: NULL;
}

REALLY_INLINE MethodEnv* MethodFrame::env() const 
{
	return (envOrCodeContext & IS_EXPLICIT_CODECONTEXT)
		? NULL
		: (MethodEnv*)(envOrCodeContext & ~FLAGS_MASK);
}

REALLY_INLINE void MethodFrame::setDxns(Namespace* ns) 
{
	AvmAssert(ns != NULL);
	envOrCodeContext |= DXNS_NOT_NULL;
	dxns = ns;
}

REALLY_INLINE /*static*/ API ApiUtils::getSmallestAPI() 
{ 
	return 0x1; 
}

REALLY_INLINE /*static*/ API ApiUtils::getLargestAPI(AvmCore* core) 
{ 
	return core->largest_api; 
}


} // namespace avmplus

#endif /* __avmplus_AvmCore_inlines__ */
