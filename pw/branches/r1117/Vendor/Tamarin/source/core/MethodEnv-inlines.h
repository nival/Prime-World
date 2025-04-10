/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
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
 * Portions created by the Initial Developer are Copyright (C) 2009
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

namespace avmplus
{
#if VMCFG_METHODENV_IMPL32
REALLY_INLINE MethodEnvProcHolder::MethodEnvProcHolder(GprMethodProc p)
    : _implGPR(p)
{ }

REALLY_INLINE GprMethodProc MethodEnvProcHolder::implGPR() const
{
    return _implGPR;
}

REALLY_INLINE FprMethodProc MethodEnvProcHolder::implFPR() const
{
    return _implFPR;
}

#else

REALLY_INLINE MethodEnvProcHolder::MethodEnvProcHolder(MethodInfo* m)
    : method(m)
{ }

REALLY_INLINE GprMethodProc MethodEnvProcHolder::implGPR() const
{
    return method->implGPR();
}

REALLY_INLINE FprMethodProc MethodEnvProcHolder::implFPR() const
{
    return method->implFPR();
}
#endif

REALLY_INLINE AbcEnv* MethodEnv::abcEnv() const
{
    return _scope->abcEnv();
}

REALLY_INLINE AvmCore* MethodEnv::core() const
{
    return method->pool()->core;
}

REALLY_INLINE CodeContext* MethodEnv::codeContext() const
{
    return abcEnv()->codeContext();
}

REALLY_INLINE DomainEnv* MethodEnv::domainEnv() const
{
    return abcEnv()->domainEnv();
}

REALLY_INLINE ScopeChain* MethodEnv::scope() const
{
    return _scope;
}

REALLY_INLINE MethodEnv* MethodEnv::super_init() const
{
    AvmAssert(vtable()->base != NULL);
    return vtable()->base->init;
}

REALLY_INLINE Toplevel* MethodEnv::toplevel() const
{
    return vtable()->toplevel();
}

REALLY_INLINE Stringp MethodEnv::traitsName() const
{
    return vtable()->traits->name();
}

REALLY_INLINE Namespacep MethodEnv::traitsNs() const
{
    return vtable()->traits->ns();
}

/** null pointer check called from jit code */
REALLY_INLINE void MethodEnv::nullcheck(Atom atom)
{
    // Shark recommends inlining the isNullOrUndefined call
    if (AvmCore::isNullOrUndefined(atom))
        nullcheckfail(atom);
}

REALLY_INLINE MethodEnv::ActivationMethodTablePair::ActivationMethodTablePair(VTable *a, WeakKeyHashtable*wkh)
    : activation(a), methodTable(wkh)
{}

REALLY_INLINE MethodEnv::ActivationMethodTablePair* MethodEnv::getPair() const
{
    return (ActivationMethodTablePair*)(activationOrMCTable&~7);
}

REALLY_INLINE int32_t MethodEnv::getType() const
{
    return activationOrMCTable & 3;
}

REALLY_INLINE void MethodEnv::setActivationOrMCTable(void *ptr, int32_t type)
{
    AvmAssert((uintptr_t(ptr) & 7) == 0);
    WB(core()->GetGC(), this, &activationOrMCTable, (uintptr_t)ptr | type | (activationOrMCTable & kIsScriptEnv));
}

REALLY_INLINE void MethodEnv::setIsScriptEnv()
{
    activationOrMCTable |= kIsScriptEnv;
}

REALLY_INLINE bool MethodEnv::isScriptEnv() const
{
    return (activationOrMCTable & kIsScriptEnv) != 0;
}

REALLY_INLINE VTable* MethodEnv::vtable() const
{
    return _scope->vtable();
}

// specialized for calling init/get functions with no parameters
REALLY_INLINE Atom MethodEnv::coerceEnter(Atom thisArg)
{
    return method->invoke(this, 0, &thisArg);
}

// general case for method calls
REALLY_INLINE Atom MethodEnv::coerceEnter(int32_t argc, Atom* args)
{
    Atom result = method->invoke(this, argc, args);
    AvmAssert(VMPI_memset(args, 0, (argc+1)*sizeof(Atom)) == args); // clobber incoming args in DEBUG
    return result;
}

REALLY_INLINE bool MethodEnv::isInterpreted()
{
    return method->isInterpreted();
}

REALLY_INLINE ScriptEnv::ScriptEnv(MethodInfo* _method, VTable* _vtable, AbcEnv* _abcEnv)
    : MethodEnv(_method, createScriptScope(_method->declaringScope(), _vtable, _abcEnv))
{
    setIsScriptEnv();
}

REALLY_INLINE FunctionEnv::FunctionEnv(MethodInfo* _method, ScopeChain* _scope)
    : MethodEnv(_method, _scope)
{ }

#ifdef FEATURE_NANOJIT

#if VMCFG_METHODENV_IMPL32

REALLY_INLINE ImtThunkEnv::ImtThunkEnv(GprImtThunkProc p, VTable* v)
    : MethodEnvProcHolder((GprMethodProc)p), vtable(v)
{ }

REALLY_INLINE ImtThunkEnv::ImtThunkEnv(GprImtThunkProc p, uint32_t c)
    : MethodEnvProcHolder((GprMethodProc)p), imtMapCount(c)
{ }

#else // !VMCFG_METHODENV_IMPL32

REALLY_INLINE ImtThunkEnv::ImtThunkEnv(GprImtThunkProc p, VTable* v)
    : MethodEnvProcHolder((MethodInfo*)&methodProcHolder), vtable(v), methodProcHolder((GprMethodProc)p)
{ }

REALLY_INLINE ImtThunkEnv::ImtThunkEnv(GprImtThunkProc p, uint32_t c)
    : MethodEnvProcHolder((MethodInfo*)&methodProcHolder), imtMapCount(c), methodProcHolder((GprMethodProc)p)
{ }

#endif // VMCFG_METHODENV_IMPL32

REALLY_INLINE GprImtThunkProc ImtThunkEnv::implImtGPR() const
{
    return (GprImtThunkProc)this->implGPR();
}

REALLY_INLINE ImtThunkEntry* ImtThunkEnv::entries() const
{
    return (ImtThunkEntry*)(this+1);
}

#endif // FEATURE_NANOJIT

} // namespace avmplus
