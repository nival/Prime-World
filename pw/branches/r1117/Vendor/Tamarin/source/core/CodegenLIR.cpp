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
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *   leon.sha@sun.com
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

#ifdef FEATURE_NANOJIT

#include "FrameState.h"

#if defined(WIN32) && defined(AVMPLUS_ARM)
#include <cmnintrin.h>
#endif

#if defined AVMPLUS_IA32 || defined AVMPLUS_AMD64
# define SSE2_ONLY(...) __VA_ARGS__
#else
# define SSE2_ONLY(...)
#endif

#ifdef _MSC_VER
    #if !defined (AVMPLUS_ARM)
    extern "C"
    {
        int __cdecl _setjmp3(jmp_buf jmpbuf, int arg);
    }
    #else
    #include <setjmp.h>
    #undef setjmp
    extern "C"
    {
        int __cdecl setjmp(jmp_buf jmpbuf);
    }
    #endif // AVMPLUS_ARM
#endif // _MSC_VER

#ifdef AVMPLUS_ARM
#ifdef _MSC_VER
#define RETURN_METHOD_PTR(_class, _method) \
return *((int*)&_method);
#else
#define RETURN_METHOD_PTR(_class, _method) \
union { \
    int (_class::*bar)(); \
    int foo[2]; \
}; \
bar = _method; \
return foo[0];
#endif

#elif defined AVMPLUS_MAC
#define RETURN_METHOD_PTR(_class, _method) \
union { \
    int (_class::*bar)(); \
    intptr_t foo; \
}; \
bar = _method; \
return foo;
#else
#define RETURN_METHOD_PTR(_class, _method) \
return *((intptr_t*)&_method);
#endif

#ifdef PERFM
#define DOPROF
#endif /* PERFM */

//#define DOPROF
#include "../vprof/vprof.h"

#ifdef AVMPLUS_64BIT
#define AVMCORE_integer         AvmCore::integer64
#define AVMCORE_integer_d       AvmCore::integer64_d
#define AVMCORE_integer_d_sse2  AvmCore::integer64_d_sse2
#define PTR_SCALE 3
#else
#define AVMCORE_integer         AvmCore::integer
#define AVMCORE_integer_d       AvmCore::integer_d
#define AVMCORE_integer_d_sse2  AvmCore::integer_d_sse2
#define PTR_SCALE 2
#endif

namespace avmplus
{
        #define PROFADDR(f) profAddr((void (DynamicProfiler::*)())(&f))
        #define COREADDR(f) coreAddr((int (AvmCore::*)())(&f))
        #define GCADDR(f) gcAddr((int (MMgc::GC::*)())(&f))
        #define ENVADDR(f) envAddr((int (MethodEnv::*)())(&f))
        #define TOPLEVELADDR(f) toplevelAddr((int (Toplevel::*)())(&f))
        #define SCRIPTADDR(f) scriptAddr((int (ScriptObject::*)())(&f))
        #define ARRAYADDR(f) arrayAddr((int (ArrayObject::*)())(&f))
        #define VECTORINTADDR(f) vectorIntAddr((int (IntVectorObject::*)())(&f))
        #define VECTORUINTADDR(f) vectorUIntAddr((int (UIntVectorObject::*)())(&f))
        #define VECTORDOUBLEADDR(f) vectorDoubleAddr((int (DoubleVectorObject::*)())(&f))
        #define VECTOROBJADDR(f) vectorObjAddr((int (ObjectVectorObject::*)())(&f))
        #define EFADDR(f)   efAddr((int (ExceptionFrame::*)())(&f))
        #define DEBUGGERADDR(f)   debuggerAddr((int (Debugger::*)())(&f))
        #define CLASSCLOSUREADDR(f)   classClosureAddr((int (ClassClosure::*)())(&f))
        #define FUNCADDR(addr) (uintptr)addr

   #ifdef VTUNE
       extern void VTune_RegisterMethod(AvmCore* core, JITCodeInfo* inf);
   #endif  // VTUNE

        intptr_t coreAddr( int (AvmCore::*f)() )
        {
            RETURN_METHOD_PTR(AvmCore, f);
        }

        intptr_t  gcAddr( int (MMgc::GC::*f)() )
        {
            RETURN_METHOD_PTR(MMgc::GC, f);
        }

        intptr_t  envAddr( int (MethodEnv::*f)() )
        {
            RETURN_METHOD_PTR(MethodEnv, f);
        }

        intptr_t  toplevelAddr( int (Toplevel::*f)() )
        {
            RETURN_METHOD_PTR(Toplevel, f);
        }

    #ifdef DEBUGGER
        intptr_t  debuggerAddr( int (Debugger::*f)() )
        {
            RETURN_METHOD_PTR(Debugger, f);
        }
    #endif /* DEBUGGER */

        intptr_t scriptAddr(int (ScriptObject::*f)())
        {
            RETURN_METHOD_PTR(ScriptObject, f);
        }

        intptr_t  arrayAddr(int (ArrayObject::*f)())
        {
            RETURN_METHOD_PTR(ArrayObject, f);
        }

        intptr_t vectorIntAddr(int (IntVectorObject::*f)())
        {
            RETURN_METHOD_PTR(IntVectorObject, f);
        }

        intptr_t vectorUIntAddr(int (UIntVectorObject::*f)())
        {
            RETURN_METHOD_PTR(UIntVectorObject, f);
        }

        intptr_t vectorDoubleAddr(int (DoubleVectorObject::*f)())
        {
            RETURN_METHOD_PTR(DoubleVectorObject, f);
        }

        intptr_t vectorObjAddr(int (ObjectVectorObject::*f)())
        {
            RETURN_METHOD_PTR(ObjectVectorObject, f);
        }
        intptr_t efAddr( int (ExceptionFrame::*f)() )
        {
            RETURN_METHOD_PTR(ExceptionFrame, f);
        }
        intptr_t classClosureAddr(int (ClassClosure::*f)())
        {
            RETURN_METHOD_PTR(ClassClosure, f);
        }

    using namespace MMgc;
    using namespace nanojit;

    #if defined _MSC_VER && !defined AVMPLUS_ARM
    #  define SETJMP ((uintptr)_setjmp3)
    #elif defined AVMPLUS_MAC_CARBON
    #  define SETJMP setjmpAddress
    #else
    #  define SETJMP ((uintptr)::setjmp)
    #endif // _MSC_VER

    #include "../core/jit-calls.h"

#if NJ_EXPANDED_LOADSTORE_SUPPORTED && defined(AVMPLUS_UNALIGNED_ACCESS) && defined(VMCFG_LITTLE_ENDIAN)
    #define VMCFG_MOPS_USE_EXPANDED_LOADSTORE
#endif

    struct MopsInfo
    {
        uint32_t size;
#ifdef VMCFG_MOPS_USE_EXPANDED_LOADSTORE
        LOpcode op;
#else
        const CallInfo* call;
#endif
    };

    static const MopsInfo kMopsLoadInfo[7] = {
#ifdef VMCFG_MOPS_USE_EXPANDED_LOADSTORE
        { 1, LIR_ldsb },
        { 2, LIR_ldss },
        { 1, LIR_ldzb },
        { 2, LIR_ldzs },
        { 4, LIR_ld },
        { 4, LIR_ld32f }, 
        { 8, LIR_ldq }
#else
        { 1, FUNCTIONID(mop_lix8) },
        { 2, FUNCTIONID(mop_lix16) },
        { 1, FUNCTIONID(mop_liz8) },
        { 2, FUNCTIONID(mop_liz16) },
        { 4, FUNCTIONID(mop_li32) },
        { 4, FUNCTIONID(mop_lf32) },
        { 8, FUNCTIONID(mop_lf64) }
#endif
    };

    static const MopsInfo kMopsStoreInfo[5] = {
#ifdef VMCFG_MOPS_USE_EXPANDED_LOADSTORE
        { 1, LIR_stb },
        { 2, LIR_sts },
        { 4, LIR_sti },
        { 4, LIR_st32f }, 
        { 8, LIR_stqi }
#else
        { 1, FUNCTIONID(mop_si8) },
        { 2, FUNCTIONID(mop_si16) },
        { 4, FUNCTIONID(mop_si32) },
        { 4, FUNCTIONID(mop_sf32) },
        { 8, FUNCTIONID(mop_sf64) }
#endif
     };

#if NJ_SOFTFLOAT

    static double i2f(int32_t i) { return i; }
    static double u2f(uint32_t u) { return u; }
    static double fneg(double a) { return -a; }
    static double fadd(double a, double b) { return a + b; }
    static double fsub(double a, double b) { return a - b; }
    static double fmul(double a, double b) { return a * b; }
    static double fdiv(double a, double b) { return a / b; }
    static int feq(double a, double b) { return a == b; }
    static int flt(double a, double b) { return a <  b; }
    static int fgt(double a, double b) { return a >  b; }
    static int fle(double a, double b) { return a <= b; }
    static int fge(double a, double b) { return a >= b; }

    CSEFUNCTION(FUNCADDR(i2f), SIG1(F,I), i2f)
    CSEFUNCTION(FUNCADDR(u2f), SIG1(F,U), u2f)
    CSEFUNCTION(FUNCADDR(fneg), SIG1(F,F), fneg)
    CSEFUNCTION(FUNCADDR(fadd), SIG2(F,F,F), fadd)
    CSEFUNCTION(FUNCADDR(fsub), SIG2(F,F,F), fsub)
    CSEFUNCTION(FUNCADDR(fmul), SIG2(F,F,F), fmul)
    CSEFUNCTION(FUNCADDR(fdiv), SIG2(F,F,F), fdiv)
    CSEFUNCTION(FUNCADDR(feq), SIG2(B,F,F), feq)
    CSEFUNCTION(FUNCADDR(flt), SIG2(B,F,F), flt)
    CSEFUNCTION(FUNCADDR(fgt), SIG2(B,F,F), fgt)
    CSEFUNCTION(FUNCADDR(fle), SIG2(B,F,F), fle)
    CSEFUNCTION(FUNCADDR(fge), SIG2(B,F,F), fge)

    // replace fpu ops with function calls
    class SoftFloatFilter: public LirWriter
    {
    public:
        SoftFloatFilter(LirWriter *out) : LirWriter(out)
        {}

        LIns *hi(LIns *q) {
            return ins1(LIR_qhi, q);
        }
        LIns *lo(LIns *q) {
            return ins1(LIR_qlo, q);
        }

        LIns *split(LIns *a) {
            if (a->isQuad() && !a->isop(LIR_qjoin)) {
                // all quad-sized args must be qjoin's for soft-float
                a = ins2(LIR_qjoin, lo(a), hi(a));
            }
            return a;
        }

        LIns *split(const CallInfo *call, LInsp args[]) {
            LIns *lo = out->insCall(call, args);
            LIns *hi = out->ins1(LIR_callh, lo);
            return out->ins2(LIR_qjoin, lo, hi);
        }

        LIns *fcall1(const CallInfo *call, LIns *a) {
            LIns *args[] = { split(a) };
            return split(call, args);
        }

        LIns *fcall2(const CallInfo *call, LIns *a, LIns *b) {
            LIns *args[] = { split(b), split(a) };
            return split(call, args);
        }

        LIns *fcmp(const CallInfo *call, LIns *a, LIns *b) {
            LIns *args[] = { split(b), split(a) };
            return out->ins2(LIR_eq, out->insCall(call, args), out->insImm(1));
        }

        LIns *ins1(LOpcode op, LIns *a) {
            switch (op) {
                case LIR_i2f:
                    return fcall1(&ci_i2f, a);
                case LIR_u2f:
                    return fcall1(&ci_u2f, a);
                case LIR_fneg:
                    return fcall1(&ci_fneg, a);
                case LIR_fret:
                    return out->ins1(op, split(a));
                default:
                    return out->ins1(op, a);
            }
        }

        LIns *ins2(LOpcode op, LIns *a, LIns *b) {
            switch (op) {
                case LIR_fadd:
                    return fcall2(&ci_fadd, a, b);
                case LIR_fsub:
                    return fcall2(&ci_fsub, a, b);
                case LIR_fmul:
                    return fcall2(&ci_fmul, a, b);
                case LIR_fdiv:
                    return fcall2(&ci_fdiv, a, b);
                case LIR_feq:
                    return fcmp(&ci_feq, a, b);
                case LIR_flt:
                    return fcmp(&ci_flt, a, b);
                case LIR_fgt:
                    return fcmp(&ci_fgt, a, b);
                case LIR_fle:
                    return fcmp(&ci_fle, a, b);
                case LIR_fge:
                    return fcmp(&ci_fge, a, b);
            }
            return out->ins2(op, a, b);
        }

        LIns *insCall(const CallInfo *ci, LInsp args[]) {
            uint32_t argt = ci->_argtypes;

            for (uint32_t i=0, argsizes = argt>>ARGSIZE_SHIFT; argsizes != 0; i++, argsizes >>= ARGSIZE_SHIFT) {
                args[i] = split(args[i]);
            }

            if ((argt & ARGSIZE_MASK_ANY) == ARGSIZE_F) {
                // this function returns a double as two 32bit values, so replace
                // call with qjoin(qhi(call), call)
                return split(ci, args);
            } else {
                return out->insCall(ci, args);
            }
        }
    };
#endif // NJ_SOFTFLOAT

    /**
     * ---------------------------------
     * Instruction convenience functions
     * ---------------------------------
     */

    // address calc instruction
    LIns* CodegenLIR::leaIns(int32_t disp, LIns* base) {
        return lirout->ins2(LIR_addp, base, InsConstPtr((void*)disp));
    }

    // call
    LIns* LirHelper::callIns(const CallInfo *ci, uint32_t argc, ...)
    {
        AvmAssert(argc <= MAXARGS);
        AvmAssert(argc == ci->count_args());

        LInsp args[MAXARGS];
        va_list ap;
        va_start(ap, argc);
        for (uint32_t i=0; i < argc; i++)
            args[argc-i-1] = va_arg(ap, LIns*);
        va_end(ap);

        return lirout->insCall(ci, args);
    }

    LIns *CodegenLIR::localCopy(int i) {
        Value &v = state->value(i);
        switch (bt(v.traits)) {
        case BUILTIN_number:
            return v.ins = lirout->insLoad(LIR_ldq, vars, i*8);
        case BUILTIN_boolean:
        case BUILTIN_int:
        case BUILTIN_uint:
            return v.ins = lirout->insLoad(LIR_ld, vars, i*8);
        default:
            return v.ins = lirout->insLoad(LIR_ldp, vars, i*8);
        }
    }

    LIns* CodegenLIR::localGet(int i) {
        Value& v = state->value(i);
        NanoAssert(v.traits == INT_TYPE || v.traits == UINT_TYPE || v.traits == BOOLEAN_TYPE);
        LIns *r = v.ins = lirout->insLoad(LIR_ld, vars, i*8);
        NanoAssert(!r->isQuad());
        return r;
    }

    LIns* CodegenLIR::localGetq(int i) {
        Value& v = state->value(i);
        NanoAssert(v.traits == NUMBER_TYPE);
        LIns *r = v.ins = lirout->insLoad(LIR_ldq, vars, i*8);
        NanoAssert(r->isQuad());
        return r;
    }

    // load a pointer-sized var
    LIns* CodegenLIR::localGetp(int i) {
        Value& v = state->value(i);
        NanoAssert(v.traits != NUMBER_TYPE && v.traits != INT_TYPE &&
                   v.traits != UINT_TYPE && v.traits != UINT_TYPE);
        LIns *r = v.ins = lirout->insLoad(LIR_ldp, vars, i*8);
        NanoAssert(r->isPtr());
        return r;
    }

    void CodegenLIR::localSet(int i, LIns* o, Traits* type)
    {
        Value &v = state->value(i);
        v.ins = o;
        lirout->insStorei(o, vars, i*8);
        (void)type;
        // note that this now updates traits for values on the scopechain as well as locals
        DEBUGGER_ONLY(
            if (core->debugger() && i < (state->verifier->local_count + state->verifier->max_scope)) {
                lirout->insStorei(InsConstPtr(type), varTraits, i*sizeof(Traits*));
            }
        )
    }

    LIns* CodegenLIR::atomToNativeRep(int i, LIns* atom)
    {
        return atomToNativeRep(state->value(i).traits, atom);
    }

    LIns* CodegenLIR::ptrToNativeRep(Traits*t, LIns* ptr)
    {
        return t->isMachineType() ? orp(ptr, kObjectType) : ptr;
    }

#ifdef _DEBUG
    bool CodegenLIR::isPointer(int i)   {
        return !state->value(i).traits->isMachineType();
    }
#endif

    LIns* CodegenLIR::loadAtomRep(int i)
    {
        return nativeToAtom(localCopy(i), state->value(i).traits);
    }

    LIns* LirHelper::nativeToAtom(LIns* native, Traits* t)
    {
        switch (bt(t)) {
        case BUILTIN_number:
            return callIns(FUNCTIONID(doubleToAtom), 2, coreAddr, native);

        case BUILTIN_any:
        case BUILTIN_object:
        case BUILTIN_void:
            return native;  // value already represented as Atom

        case BUILTIN_int:
            if (native->isconst()) {
                Atom a = core->intToAtom(native->imm32());
                if (atomIsIntptr(a))
                    return InsConstAtom(a);
            }
            return callIns(FUNCTIONID(intToAtom), 2, coreAddr, native);

        case BUILTIN_uint:
            if (native->isconst()) {
                Atom a = core->uintToAtom(native->imm32());
                if (atomIsIntptr(a))
                    return InsConstAtom(a);
            }
            return callIns(FUNCTIONID(uintToAtom), 2, coreAddr, native);

        case BUILTIN_boolean:
            return u2p(ori(lshi(native, 3), kBooleanType));

        case BUILTIN_string:
            return orp(native, kStringType);

        case BUILTIN_namespace:
            return orp(native, kNamespaceType);

        default:
            return orp(native, kObjectType);
        }
    }

    LIns* CodegenLIR::storeAtomArgs(int count, int index)
    {
        LIns* ap = InsAlloc(sizeof(Atom)*count);
        for (int i=0; i < count; i++)
            stp(loadAtomRep(index++), ap, i * sizeof(Atom));
        return ap;
    }

    LIns* CodegenLIR::storeAtomArgs(LIns* receiver, int count, int index)
    {
        #ifdef NJ_VERBOSE
        if (verbose())
            core->console << "          store args\n";
        #endif
        LIns* ap = InsAlloc(sizeof(Atom)*(count+1));
        stp(receiver, ap, 0);
        for (int i=1; i <= count; i++)
        {
            LIns* v = loadAtomRep(index++);
            stp(v, ap, sizeof(Atom)*i);
        }
        return ap;
    }

    // initialize the code manager the first time we jit any method for this PoolObject.
    CodeMgr* initCodeMgr(PoolObject *pool) {
        if (!pool->codeMgr) {
            CodeMgr *mgr = mmfx_new( CodeMgr() );
            pool->codeMgr = mgr;
#ifdef NJ_VERBOSE
            if (pool->isVerbose(VB_jit)) {
                mgr->log.lcbits = pool->verbose_vb>>16; // upper 16bits hold our jit flags
                mgr->labels.add(pool->core, sizeof(AvmCore), 0, "core");
            }
#endif
        }
        return pool->codeMgr;
    }

    CodegenLIR::CodegenLIR(MethodInfo* i) :
        LirHelper(i->pool()->core),
#ifdef VTUNE
        jitInfoList(i->core()->gc),
        jitPendingRecords(i->core()->gc),
#endif
        info(i),
        ms(i->getMethodSignature()),
        pool(i->pool()),
        interruptable(true),
        globalMemoryInfo(NULL),
        patches(*alloc1),
        call_cache_builder(*alloc1, *initCodeMgr(pool)),
        get_cache_builder(*alloc1, *pool->codeMgr),
        set_cache_builder(*alloc1, *pool->codeMgr)
    {
        state = NULL;

        #ifdef AVMPLUS_MAC_CARBON
        setjmpInit();
        #endif

        abcStart = NULL;
        abcEnd   = NULL;

        overflow = false;

        #ifdef VTUNE
        hasDebugInfo = false;
       #endif /* VTUNE */
    }

    CodegenLIR::~CodegenLIR() {
        cleanup();
    }

    void CodegenLIR::cleanup()
    {
        finddef_cache_builder.cleanup();
        LirHelper::cleanup();
    }

    #ifdef AVMPLUS_MAC_CARBON
    int CodegenLIR::setjmpAddress = 0;

    extern "C" int __setjmp();

    asm int CodegenLIR::setjmpDummy(jmp_buf buf)
    {
        b __setjmp;
    }

    void CodegenLIR::setjmpInit()
    {
        // CodeWarrior defies all reasonable efforts to get
        // the address of __vec_setjmp.  So, we resort to
        // a crude hack: We'll search the actual code
        // of setjmpDummy for the branch instruction.
        if (setjmpAddress == 0)
        {
            setjmpAddress = *((int*)&setjmpDummy);
        }
    }
    #endif

    LIns* CodegenLIR::atomToNativeRep(Traits* t, LIns* atom)
    {
        return atomToNative(bt(t), atom);
    }

    LIns* LirHelper::atomToNative(BuiltinType bt, LIns* atom)
    {
        switch (bt)
        {
        case BUILTIN_any:
        case BUILTIN_object:
        case BUILTIN_void:
            return atom;

        case BUILTIN_number:
            if (atom->isconstp())
                return lirout->insImmf(AvmCore::number_d((Atom)atom->constvalp()));
            else
                return callIns(FUNCTIONID(number_d), 1, atom);

        case BUILTIN_int:
            if (atom->isconstp())
                return InsConst(AvmCore::integer_i((Atom)atom->constvalp()));
            else
                return callIns(FUNCTIONID(integer_i), 1, atom);

        case BUILTIN_uint:
            if (atom->isconstp())
                return InsConst(AvmCore::integer_u((Atom)atom->constvalp()));
            else
                return callIns(FUNCTIONID(integer_u), 1, atom);

        case BUILTIN_boolean:
            if (atom->isconst())
                return InsConst((int32_t)atomGetBoolean((Atom)atom->constvalp()));
            else
                return p2i(ushp(atom, 3));

        default:
            // pointer type
            if (atom->isconstp())
                return InsConstPtr(atomPtr((Atom)atom->constvalp()));
            else
                return andp(atom, ~7);
        }

#ifdef __GNUC__
        return 0;// satisfy GCC, although we should never get here
#endif
    }

#ifdef _DEBUG
    class ValidateWriter: public LirWriter
    {
        bool isCondOrConst(LIns *i) {
            return i->isCond() || i->isconst();
        }
    public:
        ValidateWriter(LirWriter *out) : LirWriter(out)
        {}
        LIns *ins0(LOpcode op) {
            switch (op) {
                case LIR_skip: AvmAssert(false); break;
                case LIR_label: break;
                case LIR_start: break;
                case LIR_regfence: break;
                default:AvmAssert(false);
            }
            return out->ins0(op);
        }

        LIns *insParam(int32_t i, int32_t kind) {
            return out->insParam(i, kind);
        }

        LIns *insImm(int32_t i) {
            return out->insImm(i);
        }

        LIns *insImmq(uint64_t i) {
            return out->insImmq(i);
        }

        LIns *ins1(LOpcode op, LIns *a) {
            switch (op) {
                case LIR_fneg:
                case LIR_fret:
                case LIR_qlo:
                case LIR_qhi:
                    AvmAssert(a->isQuad());
                    break;
                case LIR_not:
                case LIR_neg:
                case LIR_i2f: case LIR_u2f:
                case LIR_i2q: case LIR_u2q:
                    AvmAssert(!a->isQuad());
                    break;
                case LIR_ret:
                    AvmAssert(a->isPtr());
                    break;
                case LIR_live:
                    break;
                case LIR_callh:
                    AvmAssert(a->isop(LIR_icall));
                    break;
                default:
                    AvmAssert(false);
            }
            return out->ins1(op, a);
        }

        LIns *ins2(LOpcode op, LIns *a, LIns *b) {
            switch (op) {
                case LIR_fadd:
                case LIR_fsub:
                case LIR_fmul:
                case LIR_fdiv:
                case LIR_feq:
                case LIR_flt:
                case LIR_fgt:
                case LIR_fle:
                case LIR_fge:
                case LIR_qaddp:
                case LIR_qior:
                case LIR_qxor:
                case LIR_qiand:
                case LIR_qiadd:
                case LIR_qeq:
                case LIR_qlt:   case LIR_qult:
                case LIR_qgt:   case LIR_qugt:
                case LIR_qle:   case LIR_qule:
                case LIR_qge:   case LIR_quge:
                    AvmAssert(a->isQuad() && b->isQuad());
                    break;
                case LIR_qjoin:
                case LIR_add:
                case LIR_iaddp:
                case LIR_sub:
                case LIR_mul:
                case LIR_and:
                case LIR_or:
                case LIR_xor:
                case LIR_lsh:
                case LIR_rsh:
                case LIR_ush:
                case LIR_eq:
                case LIR_lt:    case LIR_ult:
                case LIR_gt:    case LIR_ugt:
                case LIR_le:    case LIR_ule:
                case LIR_ge:    case LIR_uge:
                    AvmAssert(!a->isQuad() && !b->isQuad());
                    break;
                case LIR_qilsh:
                case LIR_qirsh:
                case LIR_qursh:
                    AvmAssert(a->isQuad() && !b->isQuad());
                    break;
                default:
                    AvmAssert(false);
                    break;
            }
            return out->ins2(op, a, b);
        }

        LIns *ins3(LOpcode op, LIns* a, LIns* b, LIns* c) {
            switch (op) {
                case LIR_cmov:
                    AvmAssert(isCondOrConst(a) && !b->isQuad() && !c->isQuad());
                    break;
                case LIR_qcmov:
                    AvmAssert(isCondOrConst(a) && b->isQuad() && c->isQuad());
                    break;
                default:
                    AvmAssert(false);
                    break;
            }
            return out->ins3(op, a, b, c);
        }

        LIns *insLoad(LOpcode op, LIns *base, int32_t disp) {
            switch (op) {
                case LIR_ld:
                case LIR_ldq:
                case LIR_ldc:
                case LIR_ldqc:
#ifdef VMCFG_MOPS_USE_EXPANDED_LOADSTORE
                case LIR_ldzb:
                case LIR_ldzs:
                case LIR_ldsb:
                case LIR_ldss:
                case LIR_ld32f:
                case LIR_ldcb:
                case LIR_ldcs:
                case LIR_ldcsb:
                case LIR_ldcss:
                case LIR_ldc32f:
#endif
                    // all loads require base to be a pointer, regardless of the value size
                    AvmAssert(base->isPtr());
                    break;
                default:
                    AvmAssert(false);
                    break;
            }
            return out->insLoad(op, base, disp);
        }

        LIns *insStore(LOpcode op, LIns *value, LIns *base, int32_t d) {
            AvmAssert(base && value && base->isPtr());
            return out->insStore(op, value, base, d);
        }

        LIns *insBranch(LOpcode op, LIns *cond, LIns *to) {
            switch (op) {
                case LIR_jt: AvmAssert(cond->isCond() && (!to || to->isop(LIR_label))); break;
                case LIR_jf: AvmAssert(cond->isCond() && (!to || to->isop(LIR_label))); break;
                case LIR_j:  AvmAssert(!cond && (!to || to->isop(LIR_label))); break;
                default: AvmAssert(false);
            }
            return out->insBranch(op, cond, to);
        }

        LIns* insJtbl(LIns* index, uint32_t size) {
            AvmAssert(!index->isQuad());
            return out->insJtbl(index, size);
        }

        LIns *insGuard(LOpcode v, LIns *cond, GuardRecord *gr) {
            AvmAssert(false);
            return out->insGuard(v, cond, gr);
        }

        LIns *insAlloc(int32_t size) {
            AvmAssert(size >= 4 && isU16((size+3)>>2));
            return out->insAlloc(size);
        }

        LIns *insCall(const CallInfo *call, LInsp args[]) {
            uint32_t argt = call->_argtypes;
            for (uint32_t i = 0; i < MAXARGS; i++) {
                argt >>= ARGSIZE_SHIFT;
                ArgSize sz = ArgSize(argt & ARGSIZE_MASK_ANY);
                if (sz == ARGSIZE_NONE)
                    break;
                AvmAssert((sz == ARGSIZE_I || sz == ARGSIZE_U || sz == ARGSIZE_Q || sz == ARGSIZE_F) &&
                          ((sz == ARGSIZE_I || sz == ARGSIZE_U) == !args[i]->isQuad()));
            }
            return out->insCall(call, args);
        }
    };
#endif //  _DEBUG

// if DEFER_STORES is defined, we defer local variable stores to the
// ends of basic blocks, then only emit the ones that are live
// #define DEFER_STORES(...) __VA_ARGS__
#define DEFER_STORES(...)

    class CopyPropagation: public LirWriter
    {
        AvmCore* core;
        LInsp *tracker;
        LIns *vars;
        int nvar;
        nanojit::BitSet dirty;
        bool hasExceptions;
    public:
        CopyPropagation(AvmCore* core, Allocator& alloc, LirWriter *out, int nvar, bool ex)
            : LirWriter(out), core(core), vars(NULL), nvar(nvar), dirty(alloc, nvar), hasExceptions(ex)
        {
            tracker = new (alloc) LInsp[nvar];
            clearState();
        }

        void init(LIns *vars) {
            this->vars = vars;
        }

        void saveState() {
            LIns *vars = this->vars;
            for (int i=0, n=nvar; i < n; i++) {
                LIns *v = tracker[i];
                if (!v)
                    continue;
                if (dirty.get(i)) {
                    if (v->isLoad() && v->oprnd1() == vars && v->disp() == int32_t(i*sizeof(double))) {
                        // not modified
                        continue;
                    }
                    out->insStorei(v, vars, i*sizeof(double));
                    dirty.clear(i);
                }
            }
        }

        void clearState() {
            VMPI_memset(tracker, 0, nvar*sizeof(LInsp));
            dirty.reset();
        }

        void trackStore(LIns *value, int d) {
            AvmAssert((d&7) == 0);
            int i = d >> 3;
            tracker[i] = value;
            dirty.set(i);
        }

        void trackMerge(int i, LIns *cur, LIns *target) {
            (void) i; (void) cur; (void) target;
            /*if (cur != target) {
                tracker[i] = 0;
                dirty.clear(i);
            }*/
        }

        LIns *insLoad(LOpcode op, LIns *base, int32_t d) {
            if (base == vars) {
                AvmAssert((d&7) == 0);
                int i = d >> 3;
                LIns *val = tracker[i];
                if (!val) {
                    val = out->insLoad(op, base, d);
                    tracker[i] = val;
                }
                return val;
            }
            return out->insLoad(op, base, d);
        }

        LIns *insStore(LOpcode op, LIns *value, LIns *base, int32_t d) {
            if (base == vars) {
                trackStore(value, d);
                DEFER_STORES(return 0;)
            }
            return out->insStore(op, value, base, d);
        }

        LIns *ins0(LOpcode op) {
            if (op == LIR_label) {
                DEFER_STORES(saveState();)
                clearState();
            }
            return out->ins0(op);
        }

        LIns *insBranch(LOpcode v, LInsp cond, LInsp to) {
            DEFER_STORES(saveState();)
            return out->insBranch(v, cond, to);
        }

        LIns *insJtbl(LIns* index, uint32_t size) {
            DEFER_STORES(saveState();)
            return out->insJtbl(index, size);
        }

        LIns *insCall(const CallInfo *call, LInsp args[]) {
            #ifdef DEBUGGER
            if (core->debugger())
            {
                DEFER_STORES(
                    if (!call->_cse)
                        saveState();
                )
                LIns *i = out->insCall(call, args);
                // debugger might have modified locals, so make sure we reload after call.
                if (!call->_cse)
                    clearState();
                return i;
            }
            #endif

            DEFER_STORES(
                if (hasExceptions && !call->_cse)
                    saveState();
            )
            return out->insCall(call, args);
        }

        // TODO
        // * reset when vars passed as arg to a function that could modify vars (debugenter/exit)
        // * handle load/store size mismatches -- loading high word of quad, etc
        // * suppress stores until ends of blocks
    };

    void emitStart(Allocator& alloc, LirBuffer *lirbuf, LirWriter* &lirout) {
        (void)alloc;
        (void)lirbuf;
        debug_only(
            // catch problems before they hit the buffer
            lirout = new (alloc) ValidateWriter(lirout);
        )
        lirout->ins0(LIR_start);

        // create params for saved regs -- processor specific
        for (int i=0; i < NumSavedRegs; i++) {
            LIns *p = lirout->insParam(i, 1); (void) p;
            verbose_only(if (lirbuf->names)
                lirbuf->names->addName(p, regNames[Assembler::savedRegs[i]]);)
        }
    }

    /**
     * Specializer holds specializations of certian calls into inline code sequences.
     * this could just as easily be a standalone filter instead of subclassing
     * ExprFilter, however having one less pipeline stage saves 5% of verify
     * time for esc (2000 methods).  when/if this subclassing becomes painful
     * then a separate stage is waranted.
     */
    class Specializer: public ExprFilter
    {
        Config &config;
    public:
        Specializer(LirWriter *out, Config &config) : ExprFilter(out), config(config)
        {}

        bool isPromote(LOpcode op) {
            return (op & ~1) == LIR_i2f;
        }

        LIns *imm2Int(LIns* imm) {
            // return LIns* if we can fit the constant into a i32
            if (imm->isconst())
                ; // just use imm
            else if (imm->isconstq()) {
                double val = imm->imm64f();
                double cvt = (int)val;
                if (val == 0 || val == cvt)
                    imm = out->insImm((int32_t)cvt);
                else
                    imm = 0; // can't convert
            } else {
                imm = 0; // non-imm
            }
            return imm;
        }

        LIns *insCall(const CallInfo *call, LInsp args[]) {
            if (call == FUNCTIONID(integer_d)) {
                LIns *v = args[0];
                LOpcode op = v->opcode();
                if (isPromote(op))
                    return v->oprnd1();
                if (op == LIR_fadd || op == LIR_fsub || op == LIR_fmul) {
                    LIns *a = v->oprnd1();
                    LIns *b = v->oprnd2();
                    a = isPromote(a->opcode()) ? a->oprnd1() : imm2Int(a);
                    b = isPromote(b->opcode()) ? b->oprnd1() : imm2Int(b);
                    if (a && b)
                        return out->ins2(f64arith_to_i32arith(op), a, b);
                }
                else if (op == LIR_quad) {
                    // const fold
                    return insImm(AvmCore::integer_d(v->imm64f()));
                }
            }

            SSE2_ONLY(if(config.sse2) {
                if (call == FUNCTIONID(integer_d))
                    call = FUNCTIONID(integer_d_sse2);
                else if (call == FUNCTIONID(doubleToAtom))
                    call = FUNCTIONID(doubleToAtom_sse2);
            })

            return out->insCall(call, args);
        }
    };

#if defined(DEBUGGER) && defined(_DEBUG)
    // The AS debugger requires type information for variables contained
    // in the AS frame regions (i.e. 'vars').  In the interpreter this
    // is not an issues, since the region contains box values (i.e. Atoms)
    // and so the type information is self-contained.  With the jit, this is
    // not the case, and thus 'varTraits' is used to track the type of each
    // variable in 'vars'.
    // This filter watches stores to 'vars' and 'varTraits' and upon encountering
    // debugline (i.e. place where debugger can halt), it ensures that the
    // varTraits entry is consistent with the value stored in 'vars'
    class DebuggerCheck : public LirWriter
    {
        AvmCore* core;
        LInsp *tracker;
        LInsp *traitsTracker;
        LIns *vars;
        LIns *traits;
        int nvar;
    public:
        DebuggerCheck(AvmCore* core, Allocator& alloc, LirWriter *out, int nvar)
            : LirWriter(out), core(core), vars(NULL), traits(NULL), nvar(nvar)
        {
            tracker = new (alloc) LInsp[nvar];
            traitsTracker = new (alloc) LInsp[nvar];
            clearState();
        }

        void init(LIns *vars, LIns *traits) {
            this->vars = vars;
            this->traits = traits;
        }

        void trackStore(LIns *value, int d, bool traits) {
            AvmAssert( (!traits && (d&7) == 0) || (traits && (d&3)==0));
            int i = (traits) ? d / sizeof(Traits*) : d >> 3;
            if (i>=nvar) return;
            if (traits)  {
                traitsTracker[i] = value;
                value = !isValid(i) ? value : (LIns*)((intptr_t)value|1); // lower bit => validated
                traitsTracker[i] = value;
            }
            else {
                tracker[i] = value;
            }
        }

        void clearState() {
            VMPI_memset(tracker, 0, nvar*sizeof(LInsp));
            VMPI_memset(traitsTracker, 0, nvar*sizeof(LInsp));
        }

        bool isValid(int i) {
            // @pre tracker[i] has been previously filled
            LIns* val = tracker[i];
            LIns* tra = traitsTracker[i];
            NanoAssert(val && tra);

            Traits *t = (Traits*) tra->constvalp();
            bool is = false;
            if (t == NUMBER_TYPE)
            {
                is = val->isFloat() || val->isQuad();
                AvmAssert(is);
            }
            else if (t == INT_TYPE)
            {
                is = !val->isQuad() && !val->isFloat();
                AvmAssert(is);
            }
            else if (t == UINT_TYPE)
            {
                is = !val->isQuad() && !val->isFloat();
                AvmAssert(is);
            }
            else if (t == BOOLEAN_TYPE)
            {
                is = !val->isQuad() && !val->isFloat();
                AvmAssert(is);
            }
            else
            {
                is = val->isPtr();
                AvmAssert(is);
            }
            return is;
        }

        void checkState() {
            for(int i=0; i<this->nvar; i++) {
                LIns* val = tracker[i];
                LIns* tra = traitsTracker[i];
                AvmAssert(val && tra);

                // isValid should have already been called on everything
                AvmAssert(((intptr_t)tra&0x1) == 1);
            }
        }

        LIns *insCall(const CallInfo *call, LInsp args[]) {
            if (call == FUNCTIONID(debugLine))
                checkState();
            return out->insCall(call,args);
        }

        LIns *insStore(LOpcode op, LIns *value, LIns *base, int32_t d) {
            if (base == vars)
                trackStore(value, d,false);
            else if (base == traits)
                trackStore(value, d,true);
            return out->insStore(op, value, base, d);
        }

    };
#endif

    // Generate the prolog for a function with this C++ signature:
    //
    //    <return-type> f(MethodEnv* env, int argc, void* args)
    //
    // argc is the number of arguments, not counting the receiver
    // (aka "this"). args points to the arguments in memory:
    //
    //    [receiver] [arg1, arg2, ... ]
    //
    // the arguments in memory are typed according to the AS3 method
    // signature.  types * and Object are represented as Atom, and all
    // other types are native pointers or values.  return-type is whatever
    // the native type is for the AS3 return type; one of double, int32_t,
    // uint32_t, ScriptObject*, String*, Namespace*, Atom, or void.
    //
    // The stack frame layout of a jit-compiled function is determined by
    // the jit backend.  Stack-allocated structs are declared in LIR with
    // a LIR_alloc instruction.  Incoming parameters are declared with LIR_param
    // instructions, and any other local variables with function-body scope
    // and lifetime are declared with the expressions that compute them.
    // The backend will also allocate additional stack space for spilled values
    // and callee-saved registers.  The VM and LIR do not currently depend on how
    // the backend organizes the stack frame.
    //
    // Incoming parameters:
    //
    // env_param (LIR_param, MethodEnv*) is the incoming MethodEnv* parameter
    // that provides access to the environment for this function and all vm services.
    //
    // argc_param (LIR_param, int32_t) the # of arguments that follow.  Ignored
    // when the # of args is fixed, but otherwise used for optional arg processing
    // and/or creating the rest[] or arguments[] arrays for undeclared varargs.
    //
    // ap_param (LIR_param, uint32_t*) pointer to (argc+1) incoming arguments.
    // arguments are packed.  doubles are sizeof(double), everything else is sizeof(Atom).
    //
    // Distinguished locals:
    //
    // methodFrame (LIR_alloc, MethodFrame*) is the current MethodFrame.  in the prolog
    // we push this onto the call stack pointed to by AvmCore::currentMethodFrame, and
    // in the epilog we pop it back off.
    //
    // coreAddr (LIR_int|LIR_quad) constant address of AvmCore*.  used in lots of places.
    // undefConst (LIR_int|LIR_quad) constant value = undefinedAtom. used all over.
    //
    // vars (LIR_alloc) storage for ABC stack frame variables.  8 bytes per variable,
    // always, laid out according to ABC param/local var numbering.  The total number
    // is local_count + scope_depth + stack_depth, i.e. enough for the whole ABC frame.
    // values at any given point in the jit code are are represented according to the
    // statically known type of the variable at that point in the code.  (the type and
    // representation may change at different points.  verifier->frameState maintains
    // the known static types of variables.
    //
    // The contents of vars are up-to-date at all labels and all debugging safe points.
    // Inbetween those points, the contents are stale; the JIT optimizes away
    // stores and loads in straightline code.  Additional dead stores at ends-of-blocks
    // are elided by deadvars_analyze() and deadvars_kill().
    //
    // Locals for Debugger use, only present when Debugger is in use:
    //
    // varTraits (LIR_alloc, Traits**).  Array of Traits*, with the same ordering as
    // vars.  Used by the debugger to enable decoding local variables in vars[].
    //
    // csn (LIR_alloc, CallStackNode).  extra information about this call frame
    // used by the debugger and also used for constructing human-readable stack traces.
    //
    // Locals for Exception-handling, only present when method has try/catch blocks:
    //
    // _save_eip (LIR_alloc, int32_t) storage for the current ABC-based "pc", used by exception
    // handling to determine which catch blocks are in scope.  The value is an ABC
    // instruction offset, which is how catch handler records are indexed.
    //
    // _ef (LIR_alloc, ExceptionFrame) an instance of struct ExceptionFrame, including
    // a jmp_buf holding our setjmp() state, a pointer to the next outer ExceptionFrame,
    // and other junk.
    //
    // setjmpResult (LIR_call, int) result from calling setjmp; feeds a conditional branch
    // that surrounds the whole function body; logic to pick a catch handler and jump to it
    // is compiled after the function body.  if setjmp returns a nonzero result then we
    // jump forward, pick a catch block, then jump backwards to the catch block.
    //

    bool CodegenLIR::prologue(FrameState* state)
    {
        this->state = state;
        abcStart = state->verifier->code_pos;
        abcEnd   = abcStart + state->verifier->code_length;
        framesize = state->verifier->frameSize;

        frag = new (*lir_alloc) Fragment(abcStart verbose_only(, 0));
        LirBuffer *lirbuf = frag->lirbuf = new (*lir_alloc) LirBuffer(*lir_alloc);
        lirbuf->abi = ABI_CDECL;
        lirout = new (*alloc1) LirBufWriter(lirbuf);
        debug_only(
            lirout = new (*alloc1) ValidateWriter(lirout);
        )
        verbose_only(
            vbWriter = 0;
            if (verbose() && !core->quiet_opt()) {
                lirbuf->names = new (*lir_alloc) LirNameMap(*lir_alloc, &pool->codeMgr->labels);
                lirout = vbWriter = new (*alloc1) VerboseWriter(*alloc1, lirout, lirbuf->names, &log);
            }
        )
        LoadFilter *loadfilter = 0;
        if (core->config.cseopt) {
            loadfilter = new (*alloc1) LoadFilter(lirout, *alloc1);
            lirout = new (*alloc1) CseFilter(loadfilter, *alloc1);
        }
        #if NJ_SOFTFLOAT
        lirout = new (*alloc1) SoftFloatFilter(lirout);
        #endif
        lirout = new (*alloc1) Specializer(lirout, core->config);
        CopyPropagation *copier = new (*alloc1) CopyPropagation(core, *alloc1, lirout,
            framesize, info->hasExceptions() != 0);
        lirout = this->copier = copier;

        #if defined(DEBUGGER) && defined(_DEBUG)
        DebuggerCheck *checker = NULL;
        if (core->debugger()) {
            checker = new (*alloc1) DebuggerCheck(core, *alloc1, lirout, state->verifier->local_count + state->verifier->max_scope);
            lirout = checker;
        }
        #endif

        emitStart(*alloc1, lirbuf, lirout);

        if (overflow)
            return false;

        // last pc value that we generated a store for
        lastPcSave = 0;

        //
        // generate lir to define incoming method arguments.  Stack
        // frame allocations follow.
        //

        env_param = lirout->insParam(0, 0);
        argc_param = lirout->insParam(1, 0);
    #ifdef AVMPLUS_64BIT
        argc_param = qlo(argc_param);
    #endif
        ap_param = lirout->insParam(2, 0);

        // allocate room for a MethodFrame structure
        methodFrame = InsAlloc(sizeof(MethodFrame));
        verbose_only( if (lirbuf->names) {
            lirbuf->names->addName(methodFrame, "methodFrame");
        })

        coreAddr = InsConstPtr(core);

        // replicate MethodFrame ctor inline
        LIns* currentMethodFrame = loadIns(LIR_ldp, offsetof(AvmCore,currentMethodFrame), coreAddr);
        // save env in MethodFrame.envOrCodeContext
        //     explicitly leave IS_EXPLICIT_CODECONTEXT clear
        //     explicitly leave DXNS_NOT_NULL clear, dxns is effectively null without doing the store here.
        stp(env_param, methodFrame, offsetof(MethodFrame,envOrCodeContext));
        stp(currentMethodFrame, methodFrame, offsetof(MethodFrame,next));
        stp(methodFrame, coreAddr, offsetof(AvmCore,currentMethodFrame));
        #ifdef _DEBUG
        // poison MethodFrame.dxns since it's uninitialized by default
        stp(InsConstPtr((void*)(uintptr_t)0xdeadbeef), methodFrame, offsetof(MethodFrame,dxns));
        #endif

        // allocate room for our local variables
        vars = InsAlloc(framesize * 8);
        lirbuf->sp = vars;
        if (loadfilter)
            loadfilter->sp = vars;
        copier->init(vars);

        verbose_only( if (lirbuf->names) {
            lirbuf->names->addName(env_param, "env");
            lirbuf->names->addName(argc_param, "argc");
            lirbuf->names->addName(ap_param, "ap");
            lirbuf->names->addName(vars, "vars");
        })

        // stack overflow check - use methodFrame address as comparison
        LIns *d = loadIns(LIR_ldp, offsetof(AvmCore, minstack), coreAddr);
        LIns *c = binaryIns(LIR_pult, methodFrame, d);
        LIns *b = branchIns(LIR_jf, c);
        callIns(FUNCTIONID(handleStackOverflowMethodEnv), 1, env_param);
        LIns *begin_label = label();
        verbose_only( if (lirbuf->names) { lirbuf->names->addName(begin_label, "begin");  })
        b->setTarget(begin_label);

        // we emit the undefined constant here since we use it so often and
        // to ensure it dominates all uses.
        undefConst = InsConstAtom(undefinedAtom);

        #ifdef DEBUGGER
        if (core->debugger())
        {
            // pointers to traits so that the debugger can decode the locals
            // IMPORTANT don't move this around unless you change MethodInfo::boxLocals()
            // note that this now updates traits for values on the scopechain as well as locals
            varTraits = InsAlloc((state->verifier->local_count + state->verifier->max_scope) * sizeof(Traits*));
            verbose_only( if (lirbuf->names) {
                lirbuf->names->addName(varTraits, "varTraits");
            })
            debug_only( checker->init(vars,varTraits); )
        }
        #endif

        // whether this sequence is interruptable or not.
        interruptable = ! info->isNonInterruptible();

        // then space for the exception frame, be safe if its an init stub
        if (info->hasExceptions())
        {
            // [_save_eip][ExceptionFrame]
            // offsets of local vars, rel to current ESP
            _save_eip = InsAlloc(sizeof(intptr_t));
            _ef       = InsAlloc(sizeof(ExceptionFrame));
            verbose_only( if (lirbuf->names) {
                lirbuf->names->addName(_save_eip, "_save_eip");
                lirbuf->names->addName(_ef, "_ef");
            })
        }

        #ifdef DEBUGGER
        if (core->debugger())
        {
            // Allocate space for the call stack
            csn = InsAlloc(sizeof(CallStackNode));
            verbose_only( if (lirbuf->names) {
                lirbuf->names->addName(csn, "csn");
            })
        }
        #endif

        for (int i=0, n = state->verifier->stackBase+state->stackDepth; i < n; i++)
        {
            Value& v = state->value(i);
            v.ins = 0;
        }

        //
        // copy args to local frame
        //

        // copy required args, and initialize optional args.
        // this whole section only applies to functions that actually
        // have arguments.

        const int param_count = ms->param_count();
        const int optional_count = ms->optional_count();
        const int required_count = param_count - optional_count;

        LIns* apArg = ap_param;
        if (info->hasOptional())
        {
            // compute offset of first optional arg
            int offset = 0;
            for (int i=0, n=required_count; i <= n; i++) {
                offset += ms->paramTraitsBT(i) == BUILTIN_number ? sizeof(double) : sizeof(Atom);
            }

            // now copy the default optional values
            LIns* argcarg = argc_param;
            for (int i=0, n=optional_count; i < n; i++)
            {
                // first set the local[p+1] = defaultvalue
                int param = i + required_count; // 0..N
                int loc = param+1;

                LIns* defaultVal = InsConstAtom(ms->getDefaultValue(i));
                defaultVal = atomToNativeRep(loc, defaultVal);
                localSet(loc, defaultVal, state->value(loc).traits);

                // then generate: if (argc > p) local[p+1] = arg[p+1]
                LIns* cmp = binaryIns(LIR_le, argcarg, InsConst(param));
                LIns* br = branchIns(LIR_jt, cmp); // will patch
                copyParam(loc, offset);

                LIns *optional_label = label();
                verbose_only( if (lirbuf->names) {
                    char str[64];
                    VMPI_sprintf(str,"param_%d",i);
                    lirbuf->names->addName(optional_label,str);
                })
                br->setTarget(optional_label);
            }
        }
        else
        {
            // !HAS_OPTIONAL
            AvmAssert(optional_count == 0);
        }

        // now set up the required args (we can ignore argc)
        // for (int i=0, n=param_count; i <= n; i++)
        //     framep[i] = argv[i];
        int offset = 0;
        for (int i=0, n=required_count; i <= n; i++)
            copyParam(i, offset);

        if (info->unboxThis())
        {
            localSet(0, atomToNativeRep(0, localGet(0)), state->value(0).traits);
        }

        int firstLocal = 1+param_count;

        // capture remaining args
        if (info->needRest())
        {
            //framep[info->param_count+1] = createRest(env, argv, argc);
            // use csop so if rest value never used, we don't bother creating array
            LIns* rest = callIns(FUNCTIONID(createRestHelper), 3,
                env_param, argc_param, apArg);

            localSet(firstLocal, rest, ARRAY_TYPE);
            firstLocal++;
        }
        else if (info->needArguments())
        {
            //framep[info->param_count+1] = createArguments(env, argv, argc);
            // use csop so if arguments never used, we don't create it
            LIns* arguments = callIns(FUNCTIONID(createArgumentsHelper), 3,
                env_param, argc_param, apArg);

            localSet(firstLocal, arguments, ARRAY_TYPE);
            firstLocal++;
        }

        if (firstLocal < state->verifier->local_count)
        {
            // set remaining locals to undefined
            for (int i=firstLocal, n=state->verifier->local_count; i < n; i++)
            {
                if(!(state->value(i).traits == NULL)){ // expecting *
                    AvmAssertMsg(0,"(state->value(i).traits != NULL)");
                    return false; // fail verify
                }
                localSet(i, undefConst, VOID_TYPE);
            }
        }

        #ifdef DEBUGGER
        if (core->debugger())
        {
            for (int i=state->verifier->scopeBase; i<state->verifier->scopeBase+state->verifier->max_scope; ++i)
            {
                localSet(i, undefConst, VOID_TYPE);
            }

            callIns(FUNCTIONID(debugEnter), 5,
                env_param,
                varTraits,
                csn,
                vars,
                info->hasExceptions() ? _save_eip : InsConstPtr(0)
                );
        }
        #endif // DEBUGGER

        if (info->hasExceptions()) {
            // _ef.beginTry(core);
            callIns(FUNCTIONID(beginTry), 2, _ef, coreAddr);

            // Exception* setjmpResult = setjmp(_ef.jmpBuf);
            // ISSUE this needs to be a cdecl call
            LIns* jmpbuf = leaIns(offsetof(ExceptionFrame, jmpbuf), _ef);
            setjmpResult = callIns(FUNCTIONID(fsetjmp), 2,
                jmpbuf, InsConst(0));

            // if (setjmp() != 0) goto catch dispatcher, which we generate in the epilog.
            exBranch = branchIns(LIR_jf, eq0(setjmpResult));
        }
        else {
            exBranch = 0;
        }
        verbose_only( if (vbWriter) { vbWriter->flush();} )
        return true;
    }

    void CodegenLIR::copyParam(int i, int& offset) {
        LIns* apArg = ap_param;
        Traits* type = ms->paramTraits(i);
        switch (bt(type)) {
        case BUILTIN_number:
            localSet(i, loadIns(LIR_ldqc, offset, apArg),type);
            offset += sizeof(double);
            break;
        case BUILTIN_int:
        case BUILTIN_uint:
        case BUILTIN_boolean:
            // in the args these are widened to intptr_t or uintptr_t, so truncate here.
            localSet(i, p2i(loadIns(LIR_ldcp, offset, apArg)),type);
            offset += sizeof(Atom);
            break;
        default:
            localSet(i, loadIns(LIR_ldcp, offset, apArg),type);
            offset += sizeof(Atom);
            break;
        }
    }

    void CodegenLIR::emitCopy(FrameState* state, int src, int dest) {
        this->state = state;
        localSet(dest, localCopy(src), state->value(src).traits);
    }

    void CodegenLIR::emitGetscope(FrameState* state, int scope_index, int dest)
    {
        this->state = state;
        Traits* t = info->declaringScope()->getScopeTraitsAt(scope_index);
        LIns* scope = loadEnvScope();
        LIns* scopeobj = loadIns(LIR_ldcp, offsetof(ScopeChain,_scopes) + scope_index*sizeof(Atom), scope);
        localSet(dest, atomToNativeRep(t, scopeobj), t);
    }

    void CodegenLIR::emitSwap(FrameState* state, int i, int j) {
        this->state = state;
        LIns* t = localCopy(i);
        localSet(i, localCopy(j), state->value(j).traits);
        localSet(j, t, state->value(i).traits);
    }

    void CodegenLIR::emitKill(FrameState* state, int i)
    {
        this->state = state;
        localSet(i, undefConst, VOID_TYPE);
    }

    void CodegenLIR::writeBlockStart(FrameState* state)
    {
        // our new extended BB now starts here, this means that any branch targets
        // should hit the next instruction our bb start instruction
        LIns* bb = label();  // mark start of block
        verbose_only( if (frag->lirbuf->names) {
            char str[64];
            VMPI_sprintf(str,"B%d",(int)state->pc);
            frag->lirbuf->names->addName(bb, str);
        });

        // get a label for our block start and tie it to this location
        CodegenLabel& label = state->verifier->getFrameState(state->pc)->label;
        setLabelPos(label, bb);
        if (label.jtbl_forward_target) {
            // A jtbl (switch) jumps forward to here, creating a situation our
            // register allocator cannot handle; force regs to be loaded at the
            // start of this block.
            Ins(LIR_regfence);
        }

        // If this is a backwards branch, generate an interrupt check.
        // current verifier state, includes tack pointer.
        if (interruptable && core->config.interrupts && state->targetOfBackwardsBranch)
        {
            if (state->insideTryBlock)
                stp(InsConstPtr((void*)state->pc), _save_eip, 0);

            LIns* interrupted = loadIns(LIR_ld, offsetof(AvmCore,interrupted), coreAddr);
            LIns* br = branchIns(LIR_jf, binaryIns(LIR_eq, interrupted, InsConst(AvmCore::NotInterrupted)));
            patchLater(br, interrupt_label);
        }

        // load undefined into any killed locals
        int stackBase = state->verifier->stackBase;
        for (int i=0, n=stackBase+state->stackDepth; i < n; i++)
        {
            int scopeTop = state->verifier->scopeBase+state->scopeDepth;
            if (i >= scopeTop && i < stackBase)
                continue; // not live
            Value &v = state->value(i);
            if (v.killed)
                localSet(i, undefConst, VOID_TYPE);
        }
    }

    void CodegenLIR::emitBlockEnd(FrameState* state)
    {
        this->state = state;
        // our eBB now terminates.  For all branch instructions we are
        // able to detect this situation and have already generated the
        // correct spill code prior to the jump, only for the case where
        // the pc is a target of a jump do we not know enough during emit()
        // to do this.  The Verifier tracks this information and merges
        // the states across the various blocks generating this op prior
        // to the merge.  After this emit, we should receive a writeBlockStart()
        // from the Verifier.
    }

    void CodegenLIR::writePrologue(FrameState* state, const byte *pc)
    {
        (void)pc;
        if( !prologue(state) )
        {
            if (!overflow)
                state->verifier->verifyFailed(kCorruptABCError);
        }
    }

    void CodegenLIR::writeOpcodeVerified(FrameState* state, const byte* pc, AbcOpcode opcode)
    {
        (void)state;
        (void)pc;
        (void)opcode;
        verbose_only( if (vbWriter) { vbWriter->flush();} )
    }

    void CodegenLIR::fixExceptionsAndLabels(FrameState* state, const byte* pc)
    {
        (void)state;
        (void)pc;
    }

    void CodegenLIR::write(FrameState* state, const byte* pc, AbcOpcode opcode, Traits *type)
    {
      //AvmLog("CodegenLIR::write %x\n", opcode);

        const byte* nextpc = pc;
        unsigned int imm30=0, imm30b=0;
        int imm8=0, imm24=0;
        AvmCore::readOperands(nextpc, imm30, imm24, imm30b, imm8);
        int sp = state->sp();

        switch (opcode) {
        case OP_nop:
        case OP_pop:
        case OP_label:
            // do nothing
            break;
        case OP_getlocal0:
        case OP_getlocal1:
        case OP_getlocal2:
        case OP_getlocal3:
            imm30 = opcode-OP_getlocal0;
            // hack imm30 and fall through
        case OP_getlocal:
            emitCopy(state, imm30, sp+1);
            break;
        case OP_setlocal0:
        case OP_setlocal1:
        case OP_setlocal2:
        case OP_setlocal3:
            imm30 = opcode-OP_setlocal0;
            // hack imm30 and fall through
        case OP_setlocal:
            emitCopy(state, sp, imm30);
            break;
        case OP_pushtrue:
            emitIntConst(state, sp+1, 1);
            break;
        case OP_pushfalse:
            emitIntConst(state, sp+1, 0);
            break;
        case OP_pushnull:
            emitPtrConst(state, sp+1, 0, NULL_TYPE);
            break;
        case OP_pushundefined:
            emitPtrConst(state, sp+1, (void*)undefinedAtom, VOID_TYPE);
            break;
        case OP_pushshort:
            emitIntConst(state, sp+1, (signed short)imm30);
            break;
        case OP_pushbyte:
            emitIntConst(state, sp+1, (signed char)imm8);
            break;
        case OP_pushstring:
            emitPtrConst(state, sp+1, pool->getString(imm30), STRING_TYPE);
            break;
        case OP_pushnamespace:
            emitPtrConst(state, sp+1, pool->cpool_ns[imm30], NAMESPACE_TYPE);
            break;
        case OP_pushint:
            emitIntConst(state, sp+1, pool->cpool_int[imm30]);
            break;
        case OP_pushuint:
            emitIntConst(state, sp+1, pool->cpool_uint[imm30]);
            break;
        case OP_pushdouble:
            emitDoubleConst(state, sp+1, pool->cpool_double[imm30]);
            break;
        case OP_pushnan:
            emitDoubleConst(state, sp+1, (double*)atomPtr(core->kNaN));
            break;
        case OP_lookupswitch:
            emit(state, opcode, state->pc+imm24, imm30b /*count*/);
            break;
        case OP_throw:
        case OP_returnvalue:
        case OP_returnvoid:
            emit(state, opcode, sp);
            break;
        case OP_debugfile:
        {
#if defined(DEBUGGER) || defined(VTUNE)
            #ifdef VTUNE
            const bool do_emit = true;
            #else
            const bool do_emit = core->debugger() != NULL;
            #endif
            Stringp str = pool->getString(imm30);  // assume been checked already
            if(do_emit) emit(state, opcode, (uintptr)str);
#endif
            break;
        }
        case OP_dxns:
        {
            Stringp str = pool->getString(imm30);  // assume been checked already
            emit(state, opcode, (uintptr)str);
            break;
        }
        case OP_dxnslate:
            // codgen will call intern on the input atom.
            emit(state, opcode, sp);
            break;
        case OP_kill:
            emitKill(state, imm30);
            break;
        case OP_inclocal:
        case OP_declocal:
            emit(state, opcode, imm30, opcode==OP_inclocal ? 1 : -1, NUMBER_TYPE);
            break;
        case OP_inclocal_i:
        case OP_declocal_i:
            emit(state, opcode, imm30, opcode==OP_inclocal_i ? 1 : -1, INT_TYPE);
            break;
        case OP_lessthan:
        case OP_greaterthan:
        case OP_lessequals:
        case OP_greaterequals:
            emit(state, opcode, 0, 0, BOOLEAN_TYPE);
            break;

        case OP_getdescendants:
        {
            const Multiname *name = pool->precomputedMultiname(imm30);
            emit(state, opcode, (uintptr)name, 0, NULL);
            break;
        }

        case OP_checkfilter:
            emit(state, opcode, sp, 0, NULL);
            break;

        case OP_deleteproperty:
        {
            const Multiname *name = pool->precomputedMultiname(imm30);
            emit(state, opcode, (uintptr)name, 0, BOOLEAN_TYPE);
            break;
        }

        case OP_astype:
        {
            const Multiname *name = pool->precomputedMultiname(imm30);
            Traits *t = pool->getTraits(*name, state->verifier->getToplevel(this));
            emit(state, OP_astype, (uintptr)t, sp, t && t->isMachineType() ? OBJECT_TYPE : t);
            break;
        }
        case OP_astypelate:
        {
            Value& classValue = state->peek(1); // rhs - class
            Traits* ct = classValue.traits;
            Traits* t = NULL;
            if (ct && (t=ct->itraits) != 0)
                if (t->isMachineType())
                    t = OBJECT_TYPE;
            emit(state, opcode, 0, 0, t);
            break;
        }

        case OP_coerce:
            AvmAssert (type!=NULL);
            state->verifier->emitCoerce(type, state->sp());
            break;

        case OP_coerce_b:
        case OP_convert_b:
            AvmAssert (type==NULL ? true : type==BOOLEAN_TYPE);
            state->verifier->emitCoerce(BOOLEAN_TYPE, state->sp());
            break;

        case OP_coerce_o:
            AvmAssert (type==NULL ? true : type==OBJECT_TYPE);
            state->verifier->emitCoerce(OBJECT_TYPE, state->sp());
            break;

        case OP_coerce_a:
            AvmAssert (type==NULL ? true : false);
            state->verifier->emitCoerce(NULL, state->sp());
            break;

        case OP_convert_i:
        case OP_coerce_i:
            AvmAssert (type==NULL ? true : type==INT_TYPE);
            state->verifier->emitCoerce(INT_TYPE, state->sp());
            break;

        case OP_convert_u:
        case OP_coerce_u:
            AvmAssert (type==NULL ? true : type==UINT_TYPE);
            state->verifier->emitCoerce(UINT_TYPE, state->sp());
            break;

        case OP_convert_d:
        case OP_coerce_d:
            AvmAssert (type==NULL ? true : type==NUMBER_TYPE);
            state->verifier->emitCoerce(NUMBER_TYPE, state->sp());
            break;

        case OP_coerce_s:
            AvmAssert (type==NULL ? true : type==STRING_TYPE);
            state->verifier->emitCoerce(STRING_TYPE, state->sp());
            break;

        case OP_istype:
        {
            // expects a CONSTANT_Multiname cpool index
            // used when operator "is" RHS is a compile-time type constant
            //sp[0] = istype(sp[0], itraits);
            const Multiname *name = pool->precomputedMultiname(imm30);
            Traits* itraits = pool->getTraits(*name, state->verifier->getToplevel(this));
            emitPrep(state);
            LIns* obj = loadAtomRep(sp);
            LIns* out = callIns(FUNCTIONID(istype), 2, obj, InsConstPtr(itraits));
            localSet(sp, out, BOOLEAN_TYPE);
            break;
        }

        case OP_istypelate:
        {
            emitPrep(state);
            // null check for the type value T in (x is T).  This also preserves
            // any side effects from loading T, even if we end up inlining T.itraits() as a const.
            state->verifier->emitCheckNull(sp);
            LIns* obj = loadAtomRep(sp-1);
            Traits* class_type = state->value(sp).traits;
            LIns* istype_result;
            if (class_type && class_type->base == CLASS_TYPE) {
                // (x is T) where T is a class object: get T.itraits as constant.
                istype_result = callIns(FUNCTIONID(istype), 2, obj, InsConstPtr(class_type->itraits));
            } else {
                // RHS is unknown, call general istype
                istype_result = callIns(FUNCTIONID(istypelate), 3, env_param, obj, loadAtomRep(sp));
            }
            localSet(sp-1, istype_result, BOOLEAN_TYPE);
            break;
        }

        case OP_convert_o:
            // NOTE check null has already been done
            break;

        case OP_applytype:
            // * is ok for the type, as Vector classes have no statics
            // when we implement type parameters fully, we should do something here.
            emit(state, opcode, imm30/*argc*/, 0, NULL);
            break;

        case OP_newobject:
            emit(state, opcode, imm30, 0, OBJECT_TYPE);
            break;

        case OP_newarray:
            emit(state, opcode, imm30, 0, ARRAY_TYPE);
            break;

        case OP_newactivation:
            emit(state, opcode, 0, 0, info->activationTraits());
            break;

        case OP_newcatch:
        {
            ExceptionHandler* handler = &info->abc_exceptions()->exceptions[imm30];
            emit(state, opcode, 0, 0, handler->scopeTraits);
            break;
        }

        case OP_popscope:
            #ifdef DEBUGGER
            if (core->debugger()) emitKill(state, ms->local_count()/*scopeBase*/ + state->scopeDepth);
            #endif
            break;

        case OP_getslot:
        {
            Value& obj = state->peek();
            int index = imm30-1;
            Traits* slotTraits = obj.traits ? obj.traits->getTraitsBindings()->getSlotTraits(index) : NULL;
            emitGetslot(state, index, sp, slotTraits);
            break;
        }

        case OP_setslot:
            emitSetslot(state, OP_setslot, imm30-1, sp-1);
            break;

        case OP_dup:
            emitCopy(state, sp, sp+1);
            break;

        case OP_swap:
            emitSwap(state, sp, sp-1);
            break;

        case OP_equals:
        case OP_strictequals:
        case OP_instanceof:
        case OP_in:
            emit(state, opcode, 0, 0, BOOLEAN_TYPE);
            break;

        case OP_not:
            emit(state, opcode, sp);
            break;

        case OP_modulo:
        case OP_subtract:
        case OP_divide:
        case OP_multiply:
            emit(state, opcode, 0, 0, NUMBER_TYPE);
            break;

        case OP_increment:
        case OP_decrement:
            emit(state, opcode, sp, opcode == OP_increment ? 1 : -1, NUMBER_TYPE);
            break;

        case OP_increment_i:
        case OP_decrement_i:
            emit(state, opcode, sp, opcode == OP_increment_i ? 1 : -1, INT_TYPE);
            break;

        case OP_add_i:
        case OP_subtract_i:
        case OP_multiply_i:
            emit(state, opcode, 0, 0, INT_TYPE);
            break;

        case OP_negate:
            emit(state, opcode, sp, 0, NUMBER_TYPE);
            break;

        case OP_negate_i:
            emit(state, opcode, sp, 0, INT_TYPE);
            break;

        case OP_bitand:
        case OP_bitor:
        case OP_bitxor:
            emit(state, opcode, 0, 0, INT_TYPE);
            break;

        case OP_lshift:
        case OP_rshift:
            emit(state, opcode, 0, 0, INT_TYPE);
            break;

        case OP_urshift:
            emit(state, opcode, 0, 0, INT_TYPE);
            break;

        case OP_bitnot:
            emit(state, opcode, sp, 0, INT_TYPE);
            break;

        case OP_typeof:
            emit(state, opcode, sp, 0, STRING_TYPE);
            break;

        case OP_debugline:
        {
            #if defined(DEBUGGER) || defined(VTUNE)
            #ifdef VTUNE
            const bool do_emit = true;
            #else
            const bool do_emit = core->debugger() != NULL;
            #endif
            // we actually do generate code for these, in debugger mode
            if (do_emit) emit(state, opcode, imm30);
            #endif
            break;
        }
        case OP_nextvalue:
        case OP_nextname:
            emit(state, opcode, 0, 0, NULL);
            break;

        case OP_hasnext:
            emit(state, opcode, 0, 0, INT_TYPE);
            break;

        case OP_hasnext2:
            emit(state, opcode, imm30, imm30b, BOOLEAN_TYPE);
            break;

        // sign extends
        case OP_sxi1:
        case OP_sxi8:
        case OP_sxi16:
            emit(state, opcode, sp, 0, INT_TYPE);
            break;

        // loads
        case OP_lix8:
        case OP_lix16:
        case OP_li8:
        case OP_li16:
        case OP_li32:
        case OP_lf32:
        case OP_lf64:
        {
            Traits* result = (opcode == OP_lf32 || opcode == OP_lf64) ? NUMBER_TYPE : INT_TYPE;
            emit(state, opcode, sp, 0, result);
            break;
        }

        // stores
        case OP_si8:
        case OP_si16:
        case OP_si32:
        case OP_sf32:
        case OP_sf64:
        {
            emit(state, opcode, 0, 0, VOID_TYPE);
            break;
        }

        case OP_getglobalscope:
            emitGetGlobalScope();
            break;

        case OP_add:
        {
            emitPrep(state);
            Value& val1 = state->value(sp-1);
            Value& val2 = state->value(sp);
            if ((val1.traits == STRING_TYPE && val1.notNull) || (val2.traits == STRING_TYPE && val2.notNull)) {
                // string add
                AvmAssert(type == STRING_TYPE);
                LIns* lhs = convertToString(sp-1);
                LIns* rhs = convertToString(sp);
                LIns* out = callIns(FUNCTIONID(concatStrings), 3, coreAddr, lhs, rhs);
                localSet(sp-1,  out, type);
            } else if (val1.traits && val2.traits && val1.traits->isNumeric() && val2.traits->isNumeric()) {
                // numeric add
                AvmAssert(type == NUMBER_TYPE);
                LIns* num1 = coerceToNumber(sp-1);
                LIns* num2 = coerceToNumber(sp);
                localSet(sp-1, binaryIns(LIR_fadd, num1, num2), type);
            } else {
                // any other add
                AvmAssert(type == OBJECT_TYPE);
                LIns* lhs = loadAtomRep(sp-1);
                LIns* rhs = loadAtomRep(sp);
                LIns* out = callIns(FUNCTIONID(op_add), 3, coreAddr, lhs, rhs);
                localSet(sp-1, atomToNativeRep(type, out), type);
                break;
            }
            break;
        }

        case OP_convert_s:
            emitPrep(state);
            localSet(sp, convertToString(sp), STRING_TYPE);
            break;

        case OP_esc_xelem:
        case OP_esc_xattr:
            emit(state, opcode, sp, 0, STRING_TYPE);
            break;

        case OP_debug:
            // ignored
            break;

        default:
            AvmAssert(false);
            // FIXME need error handler here
            break;
        }
    }

    void CodegenLIR::emitGetGlobalScope()
    {
        const ScopeTypeChain* scope = info->declaringScope();
        int captured_depth = scope->size;
        if (captured_depth > 0)
        {
            // enclosing scope
            emitGetscope(state, 0, state->sp()+1);
        }
        else
        {
            // local scope
            if (state->scopeDepth > 0)
            {
                emitCopy(state, state->verifier->scopeBase, state->sp()+1);
                // this will copy type and all attributes too
            }
            else
            {
                #ifdef _DEBUG
                if (pool->isBuiltin)
                    core->console << "getglobalscope >= depth (0) "<< state->scopeDepth << "\n";
                #endif
            }
        }
    }

    void CodegenLIR::writeOp1(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, Traits *type)
    {
        (void)pc;
        switch (opcode) {
        case OP_iflt:
        case OP_ifle:
        case OP_ifnlt:
        case OP_ifnle:
        case OP_ifgt:
        case OP_ifge:
        case OP_ifngt:
        case OP_ifnge:
        case OP_ifeq:
        case OP_ifstricteq:
        case OP_ifne:
        case OP_ifstrictne:
        {
            int32_t offset = (int32_t) opd1;
            int lhs = state->sp()-1;
            emitIf(state, opcode, state->pc+4/*size*/+offset, lhs, lhs+1);
            break;
        }
        case OP_iftrue:
        case OP_iffalse:
        {
            int32_t offset = (int32_t) opd1;
            int sp = state->sp();
            emitIf(state, opcode, state->pc+4/*size*/+offset, sp, 0);
            break;
        }
        case OP_jump:
        {
            int32_t offset = (int32_t) opd1;
            emit(state, opcode, state->pc+4/*size*/+offset);
            break;
        }
        case OP_getslot:
            emitGetslot(state, opd1, state->sp(), type);
            break;
        case OP_getglobalslot:
            emitGetGlobalScope();
            emitGetslot(state, opd1, state->sp(), type);
            break;
        case OP_setglobalslot:
            emitSetslot(state, OP_setglobalslot, opd1, 0 /* computed or ignored */);
            break;
        case OP_call:
            emit(state, opcode, opd1 /*argc*/, 0, NULL);
            break;

        case OP_construct:
        {
            const uint32_t argc = opd1;
            int ctor_index = state->sp() - argc;
            Traits* ctraits = state->value(ctor_index).traits;
            emitConstruct(state, argc, ctor_index, ctraits);
            break;
        }
        case OP_getouterscope:
            emitGetscope(state, opd1, state->sp()+1);
            break;
        case OP_getscopeobject:
            emitCopy(state, opd1+state->verifier->scopeBase, state->sp()+1);
            break;
        case OP_newfunction:
            AvmAssert(pool->getMethodInfo(opd1)->declaringTraits() == type);
            emit(state, opcode, opd1, state->sp()+1, type);
            break;
        case OP_pushscope:
        case OP_pushwith:
            emitCopy(state, state->sp(), opd1);
            break;
        case OP_findpropstrict:
        case OP_findproperty:
        {
            const Multiname *name = pool->precomputedMultiname(opd1);
            emit(state, opcode, (uintptr)name, 0, OBJECT_TYPE);
            break;
        }
        case OP_findpropglobalstrict:
        {
            // NOTE opcode not supported, deoptimizing
            const Multiname *name = pool->precomputedMultiname(opd1);
            emit(state, OP_findpropstrict, (uintptr)name, 0, OBJECT_TYPE);
            break;
        }
        case OP_findpropglobal:
        {
            // NOTE opcode not supported, deoptimizing
            const Multiname *name = pool->precomputedMultiname(opd1);
            emit(state, OP_findproperty, (uintptr)name, 0, OBJECT_TYPE);
            break;
        }

        case OP_newclass:
        {
            Traits* ctraits = pool->getClassTraits(opd1);
            AvmAssert(ctraits == type);
            emit(state, opcode, (uintptr)(void*)ctraits, state->sp(), type);
            break;
        }

        case OP_finddef:
        {
            // opd1=name index
            // type=script->declaringTraits
            const Multiname *multiname = pool->precomputedMultiname(opd1);
            AvmAssert(multiname->isBinding());
            int32_t dest_index = state->sp() + 1;
            emitPrep(state);
            // This allocates a cache slot even if the finddef ultimately becomes dead.
            // As long as caches tend to be small compared to size of pool data and code,
            // filtering out dead cache lines isn't worth the complexity.
            LIns* slot = InsConst(finddef_cache_builder.allocateCacheSlot(opd1));
            LIns* out = callIns(FUNCTIONID(finddef_cache), 3, env_param, InsConstPtr(multiname), slot);
            localSet(dest_index, ptrToNativeRep(type, out), type);
            break;
        }

        default:
            // verifier has called writeOp1 improperly
            AvmAssert(false);
            break;
        }
    }

    LIns* CodegenLIR::coerceToString(int index)
    {
        Value& value = state->value(index);
        Traits* in = value.traits;

        switch (bt(in)) {
        case BUILTIN_null:
        case BUILTIN_string:
            // fine to just load the pointer
            return localGetp(index);
        case BUILTIN_int:
            return callIns(FUNCTIONID(intToString), 2, coreAddr, localGet(index));
        case BUILTIN_uint:
            return callIns(FUNCTIONID(uintToString), 2, coreAddr, localGet(index));
        case BUILTIN_number:
            return callIns(FUNCTIONID(doubleToString), 2, coreAddr, localGetq(index));
        case BUILTIN_boolean: {
            // load "true" or "false" string constant from AvmCore.booleanStrings[]
            LIns *offset = binaryIns(LIR_pilsh, i2p(localGet(index)), InsConst(PTR_SCALE));
            LIns *arr = InsConstPtr(&core->booleanStrings);
            return loadIns(LIR_ldcp, 0, binaryIns(LIR_addp, arr, offset));
        }
        default:
            if (value.notNull) {
                // not eligible for CSE, and we know it's not null/undefined
                return callIns(FUNCTIONID(string), 2, coreAddr, loadAtomRep(index));
            }
            return callIns(FUNCTIONID(coerce_s), 2, coreAddr, loadAtomRep(index));
        }
    }

    /** emit code for * -> Number conversion */
    LIns* CodegenLIR::coerceToNumber(int index)
    {
        // assume emitPrep() already called
        Value& value = state->value(index);
        Traits* in = value.traits;

        if (in && (in->isNumeric() || in == BOOLEAN_TYPE)) {
            return promoteNumberIns(in, index);
        } else {
            // * -> Number
            return callIns(FUNCTIONID(number), 1, loadAtomRep(index));
        }
    }

    LIns* CodegenLIR::convertToString(int index)
    {
        // assume emitPrep() already called
        Value& value = state->value(index);
        Traits* in = value.traits;
        Traits* stringType = STRING_TYPE;

        if (in != stringType || !value.notNull) {
            if (in && (value.notNull || in->isNumeric() || in == BOOLEAN_TYPE)) {
                // convert is the same as coerce
                return coerceToString(index);
            } else {
                // explicitly convert to string
                return callIns(FUNCTIONID(string), 2, coreAddr, loadAtomRep(index));
            }
        } else {
            // already String*
            return localGetp(index);
        }
    }

    void CodegenLIR::writeNip(FrameState* state, const byte *pc)
    {
        (void)pc;
        emitCopy(state, state->sp(), state->sp()-1);
    }

    void CodegenLIR::writeInterfaceCall(FrameState* state, const byte *pc, AbcOpcode opcode, uintptr opd1, uint32_t opd2, Traits *type)
    {
        (void)pc;
        switch (opcode) {
        case OP_callproperty:
        case OP_callproplex:
        case OP_callpropvoid:
            emitCall(state, OP_callinterface, opd1, opd2, type);
            break;
        default:
            AvmAssert(false);
            break;
        }
    }

    void CodegenLIR::writeOp2(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, uint32_t opd2, Traits *type)
    {
        (void)pc;
        switch (opcode) {

        case OP_constructsuper:
            // opd1=unused, opd2=argc
            emitCall(state, opcode, 0, opd2, VOID_TYPE);
            break;

        case OP_setsuper:
        {
            const uint32_t index = opd1;
            const uint32_t n = opd2;
            Traits* base = type;
            int32_t ptrIndex = state->sp()-(n-1);

            const Multiname* name = pool->precomputedMultiname(index);

            Toplevel* toplevel = state->verifier->getToplevel(this);
            Binding b = toplevel->getBinding(base, name);
            Traits* propType = state->verifier->readBinding(base, b);
            const TraitsBindingsp basetd = base->getTraitsBindings();

            if (AvmCore::isSlotBinding(b))
            {
                if (AvmCore::isVarBinding(b))
                {
                    int slot_id = AvmCore::bindingToSlotId(b);
                    state->verifier->emitCoerce(propType, state->sp());
                    emitSetslot(state, OP_setslot, slot_id, ptrIndex);
                }
                // else, ignore write to readonly accessor
            }
            else
            if (AvmCore::isAccessorBinding(b))
            {
                if (AvmCore::hasSetterBinding(b))
                {
                    // Invoke the setter
                    int disp_id = AvmCore::bindingToSetterId(b);
                    MethodInfo *f = basetd->getMethod(disp_id);
                    AvmAssert(f != NULL);
                    MethodSignaturep fms = f->getMethodSignature();
                    state->verifier->emitCoerceArgs(f, 1);
                    emitCall(state, OP_callsuperid, disp_id, 1, fms->returnTraits());
                }
                // else, ignore write to readonly accessor
            }
            else {
                emit(state, opcode, (uintptr)name);
            }
            break;
        }
        case OP_getsuper:
        {
            const uint32_t index = opd1;
            const uint32_t n = opd2;
            Traits* base = type;

            const Multiname* name = pool->precomputedMultiname(index);

            Toplevel* toplevel = state->verifier->getToplevel(this);
            Binding b = toplevel->getBinding(base, name);
            Traits* propType = state->verifier->readBinding(base, b);

            if (AvmCore::isSlotBinding(b))
            {
                int slot_id = AvmCore::bindingToSlotId(b);
                emitGetslot(state, slot_id, state->sp()-(n-1), propType);
            }
            else
            if (AvmCore::hasGetterBinding(b))
            {
                // Invoke the getter
                int disp_id = AvmCore::bindingToGetterId(b);
                const TraitsBindingsp basetd = base->getTraitsBindings();
                MethodInfo *f = basetd->getMethod(disp_id);
                AvmAssert(f != NULL);
                state->verifier->emitCoerceArgs(f, 0);
                MethodSignaturep fms = f->getMethodSignature();
                Traits* resultType = fms->returnTraits();
                emitCall(state, OP_callsuperid, disp_id, 0, resultType);
            }
            else {
                emit(state, opcode, (uintptr)name, 0, propType);
            }
            break;
        }
        case OP_callsuper:
        case OP_callsupervoid:
        {
            const uint32_t index = opd1;
            const uint32_t argc = opd2;
            Traits* base = type;
            const TraitsBindingsp basetd = base->getTraitsBindings();

            const Multiname *name = pool->precomputedMultiname(index);

            Toplevel* toplevel = state->verifier->getToplevel(this);
            Binding b = toplevel->getBinding(base, name);

            if (AvmCore::isMethodBinding(b))
            {
                int disp_id = AvmCore::bindingToMethodId(b);
                MethodInfo* m = basetd->getMethod(disp_id);
                state->verifier->emitCoerceArgs(m, argc);

                MethodSignaturep mms = m->getMethodSignature();
                Traits* resultType = mms->returnTraits();
                emitCall(state, OP_callsuperid, disp_id, argc, resultType);
            }
            else {

                // TODO optimize other cases
                emit(state, opcode, (uintptr)name, argc, NULL);
            }

            break;
        }

        case OP_constructprop:
        {
            const uint32_t argc = opd2;
            const uint32_t n = argc+1;
            const Multiname* name = pool->precomputedMultiname(opd1);

            Value& obj = state->peek(n); // object
            Toplevel* toplevel = state->verifier->getToplevel(this);
            Binding b = toplevel->getBinding(obj.traits, name);

            if (AvmCore::isSlotBinding(b))
            {
                int slot_id = AvmCore::bindingToSlotId(b);
                int ctor_index = state->sp()-(n-1);
                emitGetslot(state, slot_id, ctor_index, type);
                obj.notNull = false;
                obj.traits = type;
                emitConstruct(state, argc, ctor_index, type);
            }
            else
            {
                emit(state, opcode, (uintptr)name, argc, NULL);
            }
            break;
        }

        case OP_getproperty:
        {
            // NOTE opd2 is the stack offset to the reciever
            const Multiname* name = pool->precomputedMultiname(opd1);
            Value& obj = state->peek(opd2); // object
            Toplevel* toplevel = state->verifier->getToplevel(this);
            Binding b = toplevel->getBinding(obj.traits, name);

            // early bind accessor
            if (AvmCore::hasGetterBinding(b))
            {
                // Invoke the getter
                int disp_id = AvmCore::bindingToGetterId(b);
                const TraitsBindingsp objtd = obj.traits->getTraitsBindings();
                MethodInfo *f = objtd->getMethod(disp_id);
                AvmAssert(f != NULL);

                if (!obj.traits->isInterface()) {
                    emitCall(state, OP_callmethod, disp_id, 0, type);
                }
                else {
                    // FIXME f->iid() is a 64 bit value, being passed through a 32 bit
                    // location. need to understand why this works.
                    emitCall(state, OP_callinterface, f->iid(), 0, type);
                }
                AvmAssert(type == f->getMethodSignature()->returnTraits());
            }
            else {
                emit(state, OP_getproperty, opd1, 0, type);
            }
            break;
        }

        case OP_setproperty:
        case OP_initproperty:
        {
            // opd2=n the stack offset to the reciever
            const Multiname *name = pool->precomputedMultiname(opd1);
            Value& obj = state->peek(opd2); // object
            Toplevel* toplevel = state->verifier->getToplevel(this);
            Binding b = toplevel->getBinding(obj.traits, name);

            // early bind accessor
            if (AvmCore::hasSetterBinding(b))
            {
                // invoke the setter
                int disp_id = AvmCore::bindingToSetterId(b);
                const TraitsBindingsp objtd = obj.traits->getTraitsBindings();
                MethodInfo *f = objtd->getMethod(disp_id);
                AvmAssert(f != NULL);

                if (!obj.traits->isInterface()) {
                    emitCall(state, OP_callmethod, disp_id, 1, type);
                }
                else {
                    // FIXME f->iid() is a 64 bit value, being passed through a 32 bit
                    // location. need to understand why this works.
                    emitCall(state, OP_callinterface, f->iid(), 1, type);
                }
            }
            else {
                emit(state, opcode, (uintptr)name);
            }
            break;
        }

        case OP_setslot:
            emitSetslot(state, OP_setslot, opd1, opd2);
            break;

        case OP_abs_jump:
        {
            #ifdef AVMPLUS_64BIT
            const byte* nextpc = pc;
            unsigned int imm30=0, imm30b=0;
            int imm8=0, imm24=0;
            AvmCore::readOperands(nextpc, imm30, imm24, imm30b, imm8);
            const byte* new_pc = (const byte *) (uintptr(opd1) | (((uintptr) opd2) << 32));
            const byte* new_code_end = new_pc + AvmCore::readU30 (nextpc);
            #else
            const byte* new_pc = (const byte*) opd1;
            const byte* new_code_end = new_pc + opd2;
            #endif
            this->abcStart = new_pc;
            this->abcEnd = new_code_end;
            break;
        }

        case OP_callmethod:
            emitCall(state, opcode, opd1, opd2, type);
            break;

        case OP_callproperty:
        case OP_callproplex:
        case OP_callpropvoid:
        {
            emit(state, opcode, opd1, opd2, NULL);
            break;
        }

        case OP_callstatic:
            // opd1=method_id, opd2=argc
            emitCall(state, OP_callstatic, opd1, opd2, type);
            break;

        default:
            AvmAssert(false);
            break;
        }
    }

    void CodegenLIR::emitIntConst(FrameState* state, int index, int32_t c)
    {
        this->state = state;
        localSet(index, lirout->insImm(c), INT_TYPE);
    }

    void CodegenLIR::emitPtrConst(FrameState* state, int index, void* c, Traits* type)
    {
        this->state = state;
        localSet(index, lirout->insImmPtr(c), type);
    }

    void CodegenLIR::emitDoubleConst(FrameState* state, int index, double* pd)
    {
        this->state = state;
        uint64_t *pquad = (uint64_t*) pd;
        localSet(index, lirout->insImmq(*pquad), NUMBER_TYPE);
    }

    void CodegenLIR::writeCoerce(FrameState* state, uint32_t loc, Traits* result)
    {
        emitPrep(state);

        Value& value = state->value(loc);
        Traits* in = value.traits;

        if (result == NULL)
        {
            // coerce to * is simple, we just save the atom rep.
            localSet(loc, loadAtomRep(loc), result);
        }
        else if (result == OBJECT_TYPE)
        {
            if (in == NULL || in == VOID_TYPE)
            {
                // value already boxed but we need to coerce undefined->null
                if (!value.notNull) {
                    // v == undefinedAtom ? nullObjectAtom : v;
                    LIns *v = localGetp(loc);
                    v = lirout->ins_choose(binaryIns(LIR_peq, v, undefConst),
                        InsConstAtom(nullObjectAtom), v, true /* use_cmov */);
                    localSet(loc, v, result);
                }
            }
            else
            {
                // value cannot be undefined so just box it
                localSet(loc, loadAtomRep(loc), result);
            }
        }
        else if (!result->isMachineType() && in == NULL_TYPE)
        {
            // do nothing, it's fine to coerce null to a pointer type
        }
        else if (result == NUMBER_TYPE)
        {
            localSet(loc, coerceToNumber(loc), result);
        }
        else if (result == INT_TYPE)
        {
            if (in == UINT_TYPE || in == BOOLEAN_TYPE)
            {
                //do nothing
            }
            else if (in == NUMBER_TYPE)
            {
                // narrowing conversion number->int
                LIns* ins = localGetq(loc);
                localSet(loc, callIns(FUNCTIONID(integer_d), 1, ins), result);
            }
            else
            {
                // * -> int
                localSet(loc, callIns(FUNCTIONID(integer), 1,
                    loadAtomRep(loc)), result);
            }
        }
        else if (result == UINT_TYPE)
        {
            if (in == INT_TYPE || in == BOOLEAN_TYPE)
            {
                //do nothing
            }
            else if (in == NUMBER_TYPE)
            {
                LIns* ins = localGetq(loc);
                localSet(loc, callIns(FUNCTIONID(integer_d), 1, ins), result);
            }
            else
            {
                // * -> uint
                localSet(loc, callIns(FUNCTIONID(toUInt32), 1,
                    loadAtomRep(loc)), result);
            }
        }
        else if (result == BOOLEAN_TYPE)
        {
            if (in == NUMBER_TYPE)
            {
                localSet(loc, callIns(FUNCTIONID(doubleToBool), 1, localGetq(loc)), result);
            }
            else if (in == INT_TYPE || in == UINT_TYPE)
            {
                // int to bool: b = (i==0) == 0
                localSet(loc, eq0(eq0(localGet(loc))), result);
            }
            else if (in && !in->notDerivedObjectOrXML())
            {
                // ptr to bool: b = (p==0) == 0
                localSet(loc, eq0(peq0(localGetp(loc))), result);
            }
            else
            {
                // * -> Boolean
                localSet(loc, callIns(FUNCTIONID(boolean), 1,
                    loadAtomRep(loc)), result);
            }
        }
        else if (result == STRING_TYPE)
        {
            localSet(loc, coerceToString(loc), result);
        }
        else if (in && !in->isMachineType() && !result->isMachineType()
               && in != STRING_TYPE && in != NAMESPACE_TYPE)
        {
            // coerceobj is void, but we mustn't optimize it out; verifier only calls it when required
            callIns(FUNCTIONID(coerceobj), 3,
                env_param, localGetp(loc), InsConstPtr(result));
            // the input pointer has now been checked but it's still the same value.
            // verifier remembers this fact by updating the verify time type.
        }
        else if (!result->isMachineType() && result != NAMESPACE_TYPE)
        {
            // result is a ScriptObject based type.
            localSet(loc, callIns(FUNCTIONID(coerceAtom2SO), 3,
                env_param, loadAtomRep(loc), InsConstPtr(result)), result);
        }
        else
        {
            LIns* value = loadAtomRep(loc);
            // sp[0] = coerce(caller_env, sp[0], traits)
            LIns* out = callIns(FUNCTIONID(coerce), 3,
                env_param, value, InsConstPtr(result));

            // store the result
            localSet(loc, atomToNativeRep(result, out), result);
        }
    }

    void CodegenLIR::writeCheckNull(FrameState* state, uint32_t index)
    {
        emitPrep(state);

        // The result is either unchanged or an exception is thrown, so
        // we don't save the result.  This is the null pointer check.
        Traits* t = state->value(index).traits;
        switch (bt(t)) {
            case BUILTIN_any:
            case BUILTIN_object:
            case BUILTIN_void: {
                // Atom
                // checking atom for null or undefined (AvmCore::isNullOrUndefined())
                LIns *value = localGetp(index);
                callIns(FUNCTIONID(nullcheck), 2, env_param, value);
                break;
            }
            case BUILTIN_int:
            case BUILTIN_uint:
            case BUILTIN_boolean:
            case BUILTIN_number:
                // never null
                break;
            default: {
                // checking pointer for null
                LIns *value = localGetp(index);
                LIns* br = branchIns(LIR_jt, peq0(value)); // will be patched
                patchLater(br, npe_label);
            }
        }
        // else: number, int, uint, and boolean, are never null
    }

    void CodegenLIR::emitPrep(FrameState* state)
    {
        this->state = state;

        // update bytecode ip if necessary
        if (state->insideTryBlock && lastPcSave != state->pc)
        {
            stp(InsConstPtr((void*)state->pc), _save_eip, 0);
            lastPcSave = state->pc;
        }
    }

    void LirHelper::liveAlloc(LIns* alloc)
    {
        if (alloc->isop(LIR_alloc))
            live(alloc);
    }

    void CodegenLIR::emitCall(FrameState *state, AbcOpcode opcode, intptr_t method_id, int argc, Traits* result)
    {
        emitPrep(state);

        int sp = state->sp();

        int dest = sp-argc;
        int objDisp = dest;

        // make sure null check happened.
        AvmAssert(state->value(objDisp).notNull);

        LIns *method = NULL;
        LIns *iid = NULL;
        switch (opcode)
        {
        case OP_constructsuper:
        {
            // env->vtable->base->init->enter32v(argc, ...);
            LIns* vtable = loadEnvVTable();
            LIns* base = loadIns(LIR_ldcp, offsetof(VTable,base), vtable);
            method = loadIns(LIR_ldcp, offsetof(VTable,init), base);
            break;
        }
        case OP_callmethod:
        {
            // stack in:  obj arg1..N
            // stack out: result
            // sp[-argc] = callmethod(disp_id, argc, ...);
            // method_id is disp_id of virtual method
            LIns* vtable = loadVTable(objDisp);
            method = loadIns(LIR_ldcp, int32_t(offsetof(VTable,methods)+sizeof(MethodEnv*)*method_id), vtable);
            break;
        }
        case OP_callsuperid:
        {
            // stack in: obj arg1..N
            // stack out: result
            // method_id is disp_id of super method
            LIns* declvtable = loadEnvVTable();
            LIns* basevtable = loadIns(LIR_ldcp, offsetof(VTable, base), declvtable);
            method = loadIns(LIR_ldcp, int32_t(offsetof(VTable,methods)+sizeof(MethodEnv*)*method_id), basevtable);
            break;
        }
        case OP_callstatic:
        {
            // stack in: obj arg1..N
            // stack out: result
            LIns* abcenv = loadEnvAbcEnv();
            method = loadIns(LIR_ldcp, int32_t(offsetof(AbcEnv,m_methods)+sizeof(MethodEnv*)*method_id), abcenv);
            break;
        }
        case OP_callinterface:
        {
            // method_id is pointer to interface method name (multiname)
            int index = int(method_id % VTable::IMT_SIZE);
            LIns* vtable = loadVTable(objDisp);
            // note, could be MethodEnv* or ImtThunkEnv*
            method = loadIns(LIR_ldcp, offsetof(VTable,imt)+sizeof(ImtThunkEnv*)*index, vtable);
            iid = InsConstPtr((void*)method_id);
            break;
        }
        case OP_construct:
        {
            // stack in: ctor arg1..N
            // stack out: newinstance
            LIns* vtable = loadVTable(objDisp);
            LIns* ivtable = loadIns(LIR_ldcp, offsetof(VTable, ivtable), vtable);
            method = loadIns(LIR_ldcp, offsetof(VTable, init), ivtable);
            LIns* inst = callIns(FUNCTIONID(newInstance),1, localGetp(objDisp));
            localSet(dest, inst, result);
            break;
        }
        default:
            AvmAssert(false);
        }

        // store args for the call
        int index = objDisp;
        LIns* ap = InsAlloc(sizeof(Atom)); // we will update this size, below
        int disp = 0;
        int pad = 0;

        // LIR_alloc of any size >= 8 is always 8-aligned.
        // if the first double arg would be unaligned, add padding to align it.
    #if !defined AVMPLUS_64BIT
        for (int i=0; i <= argc; i++) {
            if (state->value(index+i).traits == NUMBER_TYPE) {
                if ((disp&7) != 0) {
                    // this double would be unaligned, so add some padding
                    pad = 8-(disp&7); // should be 4
                }
                break;
            }
            else {
                disp += sizeof(Atom);
            }
        }
    #endif

        disp = pad;
        for (int i=0; i <= argc; i++)
        {
            // load and widen the argument
            LIns *v;
            switch (bt(state->value(index).traits)) {
            case BUILTIN_number:
                v = localGetq(index);
                stq(v, ap, disp);
                break;
            case BUILTIN_int:
                v = i2p(localGet(index));
                stp(v, ap, disp);
                break;
            case BUILTIN_uint:
            case BUILTIN_boolean:
                v = u2p(localGet(index));
                stp(v, ap, disp);
                break;
            default:
                v = localGetp(index);
                stp(v, ap, disp);
                break;
            }
            index++;
            disp += v->isQuad() ? sizeof(double) : sizeof(Atom);
        }

        // patch the size to what we actually need
        ap->setSize(disp);

#if VMCFG_METHODENV_IMPL32
        LIns* target = loadIns(LIR_ldp, offsetof(MethodEnvProcHolder,_implGPR), method);
#else
        LIns* meth = loadIns(LIR_ldp, offsetof(MethodEnvProcHolder, method), method);
        LIns* target = loadIns(LIR_ldp, offsetof(MethodInfoProcHolder, _implGPR), meth);
#endif
        LIns* apAddr = leaIns(pad, ap);

        LIns *out;
        BuiltinType rbt = bt(result);
        if (!iid) {
            const CallInfo *fid;
            switch (rbt) {
            case BUILTIN_number:
                fid = FUNCTIONID(fcalli);
                break;
            case BUILTIN_int: case BUILTIN_uint: case BUILTIN_boolean:
                fid = FUNCTIONID(icalli);
                break;
            default:
                fid = FUNCTIONID(acalli);
                break;
            }
            out = callIns(fid, 4, target, method, InsConst(argc), apAddr);
        } else {
            const CallInfo *fid;
            switch (rbt) {
            case BUILTIN_number:
                fid = FUNCTIONID(fcallimt);
                break;
            case BUILTIN_int: case BUILTIN_uint: case BUILTIN_boolean:
                fid = FUNCTIONID(icallimt);
                break;
            default:
                fid = FUNCTIONID(acallimt);
                break;
            }
            out = callIns(fid, 5, target, method, InsConst(argc), apAddr, iid);
        }

        // ensure the stack-allocated args are live until after the call
        liveAlloc(ap);

        if (opcode != OP_constructsuper && opcode != OP_construct)
        {
            localSet(dest, out, result);
        }
    }

    LIns* CodegenLIR::loadFromSlot(int ptr_index, int slot, Traits* slotType)
    {
        // assumes emitPrep already called and state already saved

        Traits *t = state->value(ptr_index).traits;
        LIns *ptr = localGetp(ptr_index);
        AvmAssert(state->value(ptr_index).notNull);
        AvmAssert(isPointer((int)ptr_index)); // obj

        AvmAssert(t->isResolved());
        const TraitsBindingsp tb = t->getTraitsBindings();
        int offset = tb->getSlotOffset(slot);

        // get
        LOpcode op;
        switch (bt(slotType)) {
        case BUILTIN_number:    op = LIR_ldq;   break;
        case BUILTIN_int:
        case BUILTIN_uint:
        case BUILTIN_boolean:   op = LIR_ld;    break;
        default:                op = LIR_ldp;   break;
        }
        return loadIns(op, offset, ptr);
    }

    void CodegenLIR::emitGetslot(FrameState *state, int slot, int ptr_index, Traits *slotType)
    {
        emitPrep(state);
        localSet(ptr_index, loadFromSlot(ptr_index, slot, slotType), slotType);
    }

    void CodegenLIR::emitSetslot(FrameState *state, AbcOpcode opcode, int slot, int ptr_index)
    {
        emitPrep(state);
        int sp = state->sp();

        Traits* t;
        LIns* ptr;

        if (opcode == OP_setslot)
        {
            t = state->value(ptr_index).traits;
            ptr = localGetp(ptr_index);
            AvmAssert(state->value(ptr_index).notNull);
            AvmAssert(isPointer((int)ptr_index)); // obj
        }
        else
        {
            // setglobalslot
            const ScopeTypeChain* scopeTypes = info->declaringScope();
            if (scopeTypes->size == 0)
            {
                // no captured scopes, so global is local scope 0
                ptr_index = state->verifier->scopeBase;
                t = state->value(ptr_index).traits;
                ptr = localGetp(ptr_index);
                AvmAssert(state->value(ptr_index).notNull);
                AvmAssert(isPointer((int)ptr_index)); // obj
            }
            else
            {
                // global is outer scope 0
                t = scopeTypes->getScopeTraitsAt(0);
                LIns* scope = loadEnvScope();
                LIns* scopeobj = loadIns(LIR_ldp, offsetof(ScopeChain,_scopes) + 0*sizeof(Atom), scope);
                ptr = atomToNativeRep(t, scopeobj);
            }
        }

        AvmAssert(t->isResolved());
        const TraitsBindingsp tb = t->getTraitsBindings();
        int offset = tb->getSlotOffset(slot);

        LIns *unoffsetPtr = ptr;

        // set
        // use localCopy() to sniff the type and use ldq if it's Number
        LIns* value = localCopy(sp);

        // if storing to a pointer-typed slot, inline a WB
        Traits* slotType = tb->getSlotTraits(slot);

        if (!slotType || !slotType->isMachineType() || slotType == OBJECT_TYPE)
        {
            // slot type is Atom (for *, Object) or RCObject* (String, Namespace, or other user types)
            const CallInfo *wbAddr = FUNCTIONID(privateWriteBarrierRC);
            if (slotType == NULL || slotType == OBJECT_TYPE) {
                // use fast atom wb
                wbAddr = FUNCTIONID(atomWriteBarrier);
            }
            callIns(wbAddr, 4,
                    InsConstPtr(core->GetGC()),
                    unoffsetPtr,
                    leaIns(offset, ptr),
                    value);
        }
        else if (slotType == NUMBER_TYPE) {
            // slot type is double or int
            stq(value, ptr, offset);
        } else {
            AvmAssert(slotType == INT_TYPE || slotType == UINT_TYPE || slotType == BOOLEAN_TYPE);
            sti(value, ptr, offset);
        }
    }

    /**
     * emit a constructor call, or a late bound constructor call.
     * early binding is possible when we know the constructor (class) being
     * used, and we know that it doesn't use custom native instance initializer
     * code, as indicated by the itraits->hasCustomConstruct flag.
    */
    void CodegenLIR::emitConstruct(FrameState* state, int argc, int ctor_index, Traits* ctraits)
    {
        emitPrep(state);

        // attempt to early bind to constructor method.
        Traits* itraits = NULL;
        if (ctraits) {
            itraits = ctraits->itraits;
            if (itraits && !itraits->hasCustomConstruct) {
                Toplevel* toplevel = state->verifier->getToplevel(this);
                itraits->resolveSignatures(toplevel);
                AvmAssert(itraits->init->isResolved());
                if (itraits->init->getMethodSignature()->argcOk(argc)) {
                    state->verifier->emitCheckNull(ctor_index);
                    state->verifier->emitCoerceArgs(itraits->init, argc, true);
                    emitCall(state, OP_construct, 0, argc, itraits);
                    return;
                }
            }
        }

        // generic path, could not early bind to a constructor method
        // stack in: ctor-object arg1..N
        // sp[-argc] = construct(env, sp[-argc], argc, null, arg1..N)
        LIns* func = loadAtomRep(ctor_index);
        LIns* args = storeAtomArgs(InsConstAtom(nullObjectAtom), argc, ctor_index+1);
        LIns* newobj = callIns(FUNCTIONID(op_construct), 4, env_param, func, InsConst(argc), args);
        liveAlloc(args);
        localSet(ctor_index, atomToNativeRep(itraits, newobj), itraits);
    }

    typedef const CallInfo *CallInfop;

    void CodegenLIR::emit(FrameState* state, AbcOpcode opcode, uintptr op1, uintptr op2, Traits* result)
    {
        emitPrep(state);

        int sp = state->sp();

        switch (opcode)
        {
            // sign extends
            case OP_sxi1:
            case OP_sxi8:
            case OP_sxi16:
            {
                // straightforward shift based sign extension
                static const uint8_t kShiftAmt[3] = { 31, 24, 16 };
                int32_t index = (int32_t) op1;
                LIns* val = localGet(index);
                if ((opcode == OP_sxi8 && val->opcode() == LIR_ldsb) ||
                    (opcode == OP_sxi16 && val->opcode() == LIR_ldss))
                {
                    // if we are sign-extending the result of a load-and-sign-extend
                    // instruction, no need to do anything. 
                    break;
                }
                LIns* sh = InsConst(kShiftAmt[opcode - OP_sxi1]);
                LIns* shl = binaryIns(LIR_lsh, val, sh);
                LIns* res = binaryIns(LIR_rsh, shl, sh);
                localSet(index, res, result);
                break;
            }

            // loads
            case OP_lix8:
            case OP_lix16:
            case OP_li8:
            case OP_li16:
            case OP_li32:
            case OP_lf32:
            case OP_lf64:
            {
                int32_t index = (int32_t) op1;
                LIns* mopAddr = localGet(index);
                const MopsInfo& mi = kMopsLoadInfo[opcode-OP_lix8];
            #ifdef VMCFG_MOPS_USE_EXPANDED_LOADSTORE
                int32_t disp = 0;
                LIns* realAddr = mopAddrToRangeCheckedRealAddrAndDisp(mopAddr, mi.size, &disp);
                LIns* i2 = loadIns(mi.op, disp, realAddr);
            #else
                LIns* realAddr = mopAddrToRangeCheckedRealAddrAndDisp(mopAddr, mi.size, NULL);
                LIns* i2 = callIns(mi.call, 1, realAddr);
            #endif
                localSet(index, i2, result);
                break;
            }

            // stores
            case OP_si8:
            case OP_si16:
            case OP_si32:
            case OP_sf32:
            case OP_sf64:
            {
                LIns* svalue = (opcode == OP_sf32 || opcode == OP_sf64) ? localGetq(sp-1) : localGet(sp-1);
                LIns* mopAddr = localGet(sp);
                const MopsInfo& mi = kMopsStoreInfo[opcode-OP_si8];
            #ifdef VMCFG_MOPS_USE_EXPANDED_LOADSTORE
                int32_t disp = 0;
                LIns* realAddr = mopAddrToRangeCheckedRealAddrAndDisp(mopAddr, mi.size, &disp);
                lirout->insStore(mi.op, svalue, realAddr, disp);
            #else
                LIns* realAddr = mopAddrToRangeCheckedRealAddrAndDisp(mopAddr, mi.size, NULL);
                callIns(mi.call, 2, realAddr, svalue);
            #endif
                break;
            }

            case OP_jump:
            {
                // spill everything first
                int targetpc_off = (int)op1;

#ifdef DEBUGGER
                Sampler* s = core->get_sampler();
                if (s && s->sampling() && targetpc_off < state->pc)
                {
                    emitSampleCheck();
                }
#endif

                // relative branch
                branchIns(LIR_j, 0, targetpc_off); // will be patched
                break;
            }

            case OP_lookupswitch:
            {
                //int index = integer(*(sp--));
                //pc += readS24(index < readU16(pc+4) ?
                //  (pc+6+3*index) :    // matched case
                //  (pc+1));            // default
                int count = int(1 + op2);
                int targetpc_off = (int)op1;

                AvmAssert(state->value(sp).traits == INT_TYPE);
                AvmAssert(count >= 0);

                // Compute address of jump table
                const byte* pc = 4 + abcStart + state->pc;
                AvmCore::readU30(pc);  // skip count

                // Delete any trailing table entries that == default case (effective for asc output)
                while (count > 0 && targetpc_off == (state->pc + AvmCore::readS24(pc+3*(count-1))))
                    count--;

                if (count > 0) {
                    LIns* index = localGet(sp);
                    LIns* cmp = binaryIns(LIR_ult, index, InsConst(count));
                    branchIns(LIR_jf, cmp, targetpc_off); // will be patched

                    if (NJ_JTBL_SUPPORTED) {
                        // Backend supports LIR_jtbl for jump tables
                        LIns* jtbl = lirout->insJtbl(index, count);
                        for (int i=0; i < count; i++) {
                            int target = state->pc + AvmCore::readS24(pc+3*i);
                            patchLater(jtbl, target, i);
                        }
                    } else {
                        // Backend doesn't support jump tables, use cascading if's
                        for (int i=0; i < count; i++) {
                            int target = state->pc + AvmCore::readS24(pc+3*i);
                            branchIns(LIR_jt, binaryIns(LIR_eq, index, InsConst(i)), target);
                        }
                    }
                }
                else {
                    // switch collapses into a single target
                    branchIns(LIR_j, 0, targetpc_off);
                }
                break;
            }

            case OP_returnvoid:
            case OP_returnvalue:
            {
                // ISSUE if a method has multiple returns this causes some bloat

                #ifdef DEBUGGER
                if (core->debugger())
                {
                    callIns(FUNCTIONID(debugExit), 2,
                        env_param, csn);
                    // now we toast the cse and restore contents in order to
                    // ensure that any variable modifications made by the debugger
                    // will be pulled in.
                    //firstCse = ip;
                }
                #endif // DEBUGGER

                if (info->abc_exceptions())
                {
                    // _ef.endTry();
                    callIns(FUNCTIONID(endTry), 1, _ef);
                }

                // replicate MethodFrame dtor inline -- must come after endTry call (if any)
                LIns* nextMethodFrame = loadIns(LIR_ldp, offsetof(MethodFrame,next), methodFrame);
                stp(nextMethodFrame, coreAddr, offsetof(AvmCore,currentMethodFrame));

                Traits* t = ms->returnTraits();
                LIns* retvalue;
                if (opcode == OP_returnvalue)
                {
                    // already coerced to required native type
                    // use localCopy to sniff type and use appropriate load instruction
                    int32_t index = (int32_t) op1;
                    retvalue = localCopy(index);
                }
                else
                {
                    retvalue = undefConst;
                    if (t && t != VOID_TYPE)
                    {
                        // implicitly coerce undefined to the return type
                        retvalue = callIns(FUNCTIONID(coerce), 3,
                            env_param, retvalue, InsConstPtr(t));
                        retvalue = atomToNativeRep(t, retvalue);
                    }
                }
                switch (bt(t)) {
                case BUILTIN_number:
                    Ins(LIR_fret, retvalue);
                    break;
                case BUILTIN_int:
                    ret(i2p(retvalue));
                    break;
                case BUILTIN_uint:
                case BUILTIN_boolean:
                    ret(u2p(retvalue));
                    break;
                default:
                    ret(retvalue);
                    break;
                }
                break;
            }

            case OP_typeof:
            {
                //sp[0] = typeof(sp[0]);
                int32_t index = (int32_t) op1;
                LIns* value = loadAtomRep(index);
                LIns* i3 = callIns(FUNCTIONID(typeof), 2,
                    coreAddr, value);
                AvmAssert(result == STRING_TYPE);
                localSet(index, i3, result);
                break;
            }

            case OP_not:
            {
                int32_t index = (int32_t) op1;
                AvmAssert(state->value(index).traits == BOOLEAN_TYPE);
                LIns* value = localGet(index);
                LIns* i3 = binaryIns(LIR_xor, value, InsConst(1));
                localSet(index, i3, result);
                break;
            }

            case OP_negate: {
                int32_t index = (int32_t) op1;
                localSet(index, Ins(LIR_fneg, localGetq(index)),result);
                break;
            }

            case OP_negate_i: {
                //framep[op1] = -framep[op1]
                int32_t index = (int32_t) op1;
                AvmAssert(state->value(index).traits == INT_TYPE);
                localSet(index, Ins(LIR_neg, localGet(index)), result);
                break;
            }

            case OP_increment:
            case OP_decrement:
            case OP_inclocal:
            case OP_declocal: {
                int32_t index = (int32_t) op1;
                int32_t incr = (int32_t) op2; // 1 or -1
                localSet(index, binaryIns(LIR_fadd, localGetq(index), i2dIns(InsConst(incr))), result);
                break;
            }

            case OP_inclocal_i:
            case OP_declocal_i:
            case OP_increment_i:
            case OP_decrement_i: {
                int32_t index = (int32_t) op1;
                int32_t incr = (int32_t) op2;
                AvmAssert(state->value(index).traits == INT_TYPE);
                localSet(index, binaryIns(LIR_add, localGet(index), InsConst(incr)), result);
                break;
            }

            case OP_bitnot: {
                // *sp = core->intToAtom(~integer(*sp));
                int32_t index = (int32_t) op1;
                AvmAssert(state->value(index).traits == INT_TYPE);
                localSet(index, lirout->ins1(LIR_not, localGet(index)), result);
                break;
            }

            case OP_modulo: {
                LIns* out = callIns(FUNCTIONID(mod), 2,
                    localGetq(sp-1), localGetq(sp));
                localSet(sp-1,  out, result);
                break;
            }

            case OP_divide:
            case OP_multiply:
            case OP_subtract: {
                LOpcode op;
                switch (opcode) {
                    default:
                    case OP_divide:     op = LIR_fdiv; break;
                    case OP_multiply:   op = LIR_fmul; break;
                    case OP_subtract:   op = LIR_fsub; break;
                }
                localSet(sp-1, binaryIns(op, localGetq(sp-1), localGetq(sp)), result);
                break;
            }

            case OP_subtract_i:
            case OP_add_i:
            case OP_multiply_i:
            case OP_lshift:
            case OP_rshift:
            case OP_urshift:
            case OP_bitand:
            case OP_bitor:
            case OP_bitxor:
            {
                LOpcode op;
                switch (opcode) {
                    default:
                    case OP_bitxor:     op = LIR_xor;  break;
                    case OP_bitor:      op = LIR_or;   break;
                    case OP_bitand:     op = LIR_and;  break;
                    case OP_urshift:    op = LIR_ush;  break;
                    case OP_rshift:     op = LIR_rsh;  break;
                    case OP_lshift:     op = LIR_lsh;  break;
                    case OP_multiply_i: op = LIR_mul; break;
                    case OP_add_i:      op = LIR_add;  break;
                    case OP_subtract_i: op = LIR_sub;  break;
                }
                LIns* lhs = localGet(sp-1);
                LIns* rhs = localGet(sp);
                LIns* out = binaryIns(op, lhs, rhs);
                localSet(sp-1, out, result);
                break;
            }

            case OP_throw:
            {
                //throwAtom(*sp--);
                int32_t index = (int32_t) op1;
                callIns(FUNCTIONID(throwAtom), 2, coreAddr, loadAtomRep(index));
                break;
            }

            case OP_getsuper:
            {
                // stack in: obj [ns [name]]
                // stack out: value
                // sp[0] = env->getsuper(sp[0], multiname)
                int objDisp = sp;
                LIns* multi = initMultiname((Multiname*)op1, objDisp);
                AvmAssert(state->value(objDisp).notNull);

                LIns* obj = loadAtomRep(objDisp);

                LIns* i3 = callIns(FUNCTIONID(getsuper), 3,
                    env_param, obj, multi);
                liveAlloc(multi);

                i3 = atomToNativeRep(result, i3);
                localSet(objDisp, i3, result);
                break;
            }

            case OP_setsuper:
            {
                // stack in: obj [ns [name]] value
                // stack out: nothing
                // core->setsuper(sp[-1], multiname, sp[0], env->vtable->base)
                int objDisp = sp-1;
                LIns* multi = initMultiname((Multiname*)op1, objDisp);
                AvmAssert(state->value(objDisp).notNull);

                LIns* obj = loadAtomRep(objDisp);
                LIns* value = loadAtomRep(sp);

                callIns(FUNCTIONID(setsuper), 4,
                    env_param, obj, multi, value);
                liveAlloc(multi);
                break;
            }

            case OP_nextname:
            case OP_nextvalue:
            {
                // sp[-1] = next[name|value](sp[-1], sp[0]);
                LIns* obj = loadAtomRep(sp-1);
                AvmAssert(state->value(sp).traits == INT_TYPE);
                LIns* index = localGet(sp);
                LIns* i1 = callIns((opcode == OP_nextname) ? FUNCTIONID(nextname) : FUNCTIONID(nextvalue), 3,
                                   env_param, obj, index);
                localSet(sp-1, atomToNativeRep(result, i1), result);
                break;
            }

            case OP_hasnext:
            {
                // sp[-1] = hasnext(sp[-1], sp[0]);
                LIns* obj = loadAtomRep(sp-1);
                AvmAssert(state->value(sp).traits == INT_TYPE);
                LIns* index = localGet(sp);
                LIns* i1 = callIns(FUNCTIONID(hasnext), 3,
                    env_param, obj, index);
                AvmAssert(result == INT_TYPE);
                localSet(sp-1, i1, result);
                break;
            }

            case OP_hasnext2:
            {
                // fixme - if obj is already Atom, or index is already int,
                // easier to directly reference space in vars.
                int32_t obj_index = (int32_t) op1;
                int32_t index_index = (int32_t) op2;
                LIns* obj = InsAlloc(sizeof(Atom));
                LIns* index = InsAlloc(sizeof(int32_t));
                stp(loadAtomRep(obj_index), obj, 0);       // Atom obj
                sti(localGet(index_index), index, 0);      // int32 index
                LIns* i1 = callIns(FUNCTIONID(hasnextproto), 3,
                                     env_param, obj, index);
                localSet(obj_index, loadIns(LIR_ldp, 0, obj), OBJECT_TYPE);  // Atom obj
                localSet(index_index, loadIns(LIR_ld, 0, index), INT_TYPE); // int32 index
                AvmAssert(result == BOOLEAN_TYPE);
                localSet(sp+1, i1, result);
                break;
            }

            case OP_newfunction:
            {
                uint32_t function_id = (uint32_t) op1;
                int32_t index = (int32_t) op2;
                //sp[0] = core->newfunction(env, body, _scopeBase, scopeDepth);
                MethodInfo* func = pool->getMethodInfo(function_id);
                int extraScopes = state->scopeDepth;

                // prepare scopechain args for call
                LIns* ap = storeAtomArgs(extraScopes, state->verifier->scopeBase);

                LIns* outer = loadEnvScope();

                LIns* i3 = callIns(FUNCTIONID(newfunction), 4,
                    env_param, InsConstPtr(func), outer, ap);
                liveAlloc(ap);

                AvmAssert(!result->isMachineType());
                localSet(index, i3, result);
                break;
            }

            case OP_call:
            {
                // stack in: method obj arg1..N
                // sp[-argc-1] = op_call(env, sp[-argc], argc, ...)
                int argc = int(op1);
                int funcDisp = sp - argc - 1;
                int dest = funcDisp;

                // convert args to Atom[] for the call
                LIns* func = loadAtomRep(funcDisp);
                LIns* ap = storeAtomArgs(loadAtomRep(funcDisp+1), argc, funcDisp+2);
                LIns* i3 = callIns(FUNCTIONID(op_call), 4, env_param, func, InsConst(argc), ap);
                liveAlloc(ap);
                localSet(dest, atomToNativeRep(result, i3), result);
                break;
            }

            case OP_callproperty:
            case OP_callproplex:
            case OP_callpropvoid:
            {
                // stack in: obj [ns [name]] arg1..N
                // stack out: result

                // obj = sp[-argc]
                //tempAtom = callproperty(env, name, toVTable(obj), argc, ...);
                //  *(sp -= argc) = tempAtom;
                int argc = int(op2);
                int argv = sp-argc+1;
                int baseDisp = sp-argc;
                const Multiname* name = pool->precomputedMultiname((int)op1);
                LIns* multi = initMultiname(name, baseDisp);
                AvmAssert(state->value(baseDisp).notNull);

                // convert args to Atom[] for the call
                LIns* base = loadAtomRep(baseDisp);
                LIns* receiver = opcode == OP_callproplex ? InsConstAtom(nullObjectAtom) : base;
                LIns* ap = storeAtomArgs(receiver, argc, argv);

                Traits* baseTraits = state->value(baseDisp).traits;
                Binding b = state->verifier->getToplevel(this)->getBinding(baseTraits, name);

                LIns* out;
                if (AvmCore::isSlotBinding(b)) {
                    // can early bind call to closure in slot
                    Traits* slotType = state->verifier->readBinding(baseTraits, b);
                    // todo if funcValue is already a ScriptObject then don't box it, use a different helper.
                    LIns* funcValue = loadFromSlot(baseDisp, AvmCore::bindingToSlotId(b), slotType);
                    LIns* funcAtom = nativeToAtom(funcValue, slotType);
                    out = callIns(FUNCTIONID(op_call), 4, env_param, funcAtom, InsConst(argc), ap);
                }
                else if (!name->isRuntime()) {
                    // use inline cache for late bound call
                    // cache contains: [handler, vtable, [data], Multiname*]
                    // and we call (*cache->handler)(cache, obj, argc, args*, MethodEnv*)
                    CallCache* cache = call_cache_builder.allocateCacheSlot(name);
                    LIns* cacheAddr = InsConstPtr(cache);
                    LIns* handler = loadIns(LIR_ldp, offsetof(CallCache, call_handler), cacheAddr);
                    out = callIns(FUNCTIONID(call_cache_handler), 6,
                        handler, cacheAddr, base, InsConst(argc), ap, env_param);
                }
                else {
                    // generic late bound call to anything
                    out = callIns(FUNCTIONID(callprop_late), 5, env_param, base, multi, InsConst(argc), ap);
                    liveAlloc(multi);
                }
                liveAlloc(ap);
                localSet(baseDisp, atomToNativeRep(result, out), result);
                break;
            }

            case OP_constructprop:
            {
                // stack in: obj [ns [name]] arg1..N
                // stack out: result

                int argc = int(op2);
                // obj = sp[-argc]
                //tempAtom = callproperty(env, name, toVTable(obj), argc, ...);
                //  *(sp -= argc) = tempAtom;
                int argv = sp-argc+1;

                int objDisp = sp-argc;
                LIns* multi = initMultiname((Multiname*)op1, objDisp);
                AvmAssert(state->value(objDisp).notNull);

                // convert args to Atom[] for the call
                LIns* ap = storeAtomArgs(loadAtomRep(objDisp), argc, argv);
                LIns* i3 = callIns(FUNCTIONID(construct_late), 4,
                    env_param, multi, InsConst(argc), ap);
                liveAlloc(multi);
                liveAlloc(ap);

                localSet(objDisp, atomToNativeRep(result, i3), result);
                break;
            }

            case OP_callsuper:
            case OP_callsupervoid:
            {
                // stack in: obj [ns [name]] arg1..N
                // stack out: result
                // null check must have already happened.
                //  tempAtom = callsuper(multiname, obj, sp-argc+1, argc, vtable->base);
                int argc = int(op2);
                int argv = sp - argc + 1;
                int objDisp = sp - argc;
                LIns* multi = initMultiname((Multiname*)op1, objDisp);
                AvmAssert(state->value(objDisp).notNull);

                // convert args to Atom[] for the call
                LIns* obj = loadAtomRep(objDisp);

                LIns* ap = storeAtomArgs(obj, argc, argv);

                LIns* i3 = callIns(FUNCTIONID(callsuper), 4,
                    env_param, multi, InsConst(argc), ap);
                liveAlloc(multi);
                liveAlloc(ap);

                localSet(objDisp, atomToNativeRep(result, i3), result);
                break;
            }

            case OP_applytype:
            {
                // stack in: method arg1..N
                // sp[-argc] = applytype(env, sp[-argc], argc, null, arg1..N)
                int argc = int(op1);
                int funcDisp = sp - argc;
                int dest = funcDisp;
                int arg0 = sp - argc + 1;

                LIns* func = loadAtomRep(funcDisp);

                // convert args to Atom[] for the call
                LIns* ap = storeAtomArgs(argc, arg0);

                LIns* i3 = callIns(FUNCTIONID(op_applytype), 4,
                    env_param, func, InsConst(argc), ap);
                liveAlloc(ap);

                localSet(dest, atomToNativeRep(result, i3), result);
                break;
            }

            case OP_newobject:
            {
                // result = env->op_newobject(sp, argc)
                int argc = int(op1);
                int dest = sp - (2*argc-1);
                int arg0 = dest;

                // convert args to Atom for the call[]
                LIns* ap = storeAtomArgs(2*argc, arg0);

                LIns* i3 = callIns(FUNCTIONID(op_newobject), 3,
                    env_param, leaIns(sizeof(Atom)*(2*argc-1), ap), InsConst(argc));
                liveAlloc(ap);

                localSet(dest, ptrToNativeRep(result, i3), result);
                break;
            }

            case OP_newactivation:
            {
                // result = env->newActivation()
                LIns* activation = callIns(FUNCTIONID(newActivation), 1, env_param);
                localSet(sp+1, ptrToNativeRep(result, activation), result);
                break;
            }

            case OP_newcatch:
            {
                // result = core->newObject(env->activation, NULL);
                int dest = sp+1;

                LIns* activation = callIns(FUNCTIONID(newcatch), 2,
                                         env_param, InsConstPtr(result));

                localSet(dest, ptrToNativeRep(result, activation), result);
                break;
            }

            case OP_newarray:
            {
                // sp[-argc+1] = env->toplevel()->arrayClass->newarray(sp-argc+1, argc)
                int argc = int(op1);
                int arg0 = sp - 1*argc+1;

                // convert array elements to Atom[]
                LIns* ap = storeAtomArgs(argc, arg0);
                LIns* i3 = callIns(FUNCTIONID(newarray), 3, env_param, InsConst(argc), ap);
                liveAlloc(ap);

                AvmAssert(!result->isMachineType());
                localSet(arg0, i3, result);
                break;
            }

            case OP_newclass:
            {
                // sp[0] = core->newclass(env, ctraits, scopeBase, scopeDepth, base)
                Traits* ctraits = (Traits*) op1;
                int localindex = int(op2);
                int extraScopes = state->scopeDepth;

                LIns* outer = loadEnvScope();
                LIns* base = localGetp(localindex);

                // prepare scopechain args for call
                LIns* ap = storeAtomArgs(extraScopes, state->verifier->scopeBase);

                LIns* i3 = callIns(FUNCTIONID(newclass), 5,
                    env_param, InsConstPtr(ctraits), base, outer, ap);
                liveAlloc(ap);

                AvmAssert(!result->isMachineType());
                localSet(localindex, i3, result);
                break;
            }

            case OP_getdescendants:
            {
                // stack in: obj [ns [name]]
                // stack out: value
                //sp[0] = core->getdescendants(sp[0], name);
                int objDisp = sp;
                Multiname* multiname = (Multiname*) op1;

                LIns* envArg = env_param;
                LIns* out;
                LIns* multi = initMultiname(multiname, objDisp);
                LIns* obj = loadAtomRep(objDisp);
                AvmAssert(state->value(objDisp).notNull);

                out = callIns(FUNCTIONID(getdescendants), 3,
                    envArg, obj, multi);
                liveAlloc(multi);

                localSet(objDisp, atomToNativeRep(result, out), result);
                break;
            }

            case OP_checkfilter: {
                int32_t index = (int32_t) op1;
                callIns(FUNCTIONID(checkfilter), 2, env_param, loadAtomRep(index));
                break;
            }

            case OP_findpropstrict:
            case OP_findproperty:
            {
                // stack in: [ns [name]]
                // stack out: obj
                // sp[1] = env->findproperty(scopeBase, scopedepth, name, strict)
                int dest = sp;
                LIns* multi = initMultiname((Multiname*)op1, dest);
                dest++;
                int extraScopes = state->scopeDepth;

                // prepare scopechain args for call
                LIns* ap = storeAtomArgs(extraScopes, state->verifier->scopeBase);

                LIns* outer = loadEnvScope();

                LIns* withBase;
                if (state->withBase == -1)
                {
                    withBase = InsConstPtr(0);
                }
                else
                {
                    withBase = leaIns(state->withBase*sizeof(Atom), ap);
                }

                //      return env->findproperty(outer, argv, extraScopes, name, strict);

                LIns* i3 = callIns(FUNCTIONID(findproperty), 7,
                    env_param, outer, ap, InsConst(extraScopes), multi,
                    InsConst((int32_t)(opcode == OP_findpropstrict)),
                    withBase);
                liveAlloc(multi);
                liveAlloc(ap);

                localSet(dest, atomToNativeRep(result, i3), result);
                break;
            }

            case OP_getproperty:
            {
                // stack in: obj [ns] [name]
                // stack out: value
                // obj=sp[0]
                //sp[0] = env->getproperty(obj, multiname);

                const Multiname* multiname = pool->precomputedMultiname((int)op1);
                bool attr = multiname->isAttr();
                Traits* indexType = state->value(sp).traits;
                int objDisp = sp;

                bool maybeIntegerIndex = !attr && multiname->isRtname() && multiname->containsAnyPublicNamespace();
                if (maybeIntegerIndex && indexType == INT_TYPE)
                {
                    bool valIsAtom = true;
                    LIns* index = localGet(objDisp--);

                    if (multiname->isRtns())
                    {
                        // Discard runtime namespace
                        objDisp--;
                    }

                    Traits* objType = state->value(objDisp).traits;

                    LIns *value;
                    if (objType == ARRAY_TYPE || (objType!= NULL && objType->subtypeof(VECTOROBJ_TYPE)) )
                    {
                        value = callIns((objType==ARRAY_TYPE ?
                                        FUNCTIONID(ArrayObject_getIntProperty) :
                                        FUNCTIONID(ObjectVectorObject_getIntProperty)), 2,
                            localGetp(sp-1), index);
                    }
                    else if( objType == VECTORINT_TYPE || objType == VECTORUINT_TYPE)
                    {
                        if( result == INT_TYPE || result == UINT_TYPE)
                        {
                            value = callIns((objType==VECTORINT_TYPE ?
                                                    FUNCTIONID(IntVectorObject_getNativeIntProperty) :
                                                    FUNCTIONID(UIntVectorObject_getNativeIntProperty)), 2,
                            localGetp(sp-1), index);
                            valIsAtom = false;
                        }
                        else
                        {
                            value = callIns((objType==VECTORINT_TYPE ?
                                                    FUNCTIONID(IntVectorObject_getIntProperty) :
                                                    FUNCTIONID(UIntVectorObject_getIntProperty)), 2,
                            localGetp(sp-1), index);
                        }
                    }
                    else if( objType == VECTORDOUBLE_TYPE )
                    {
                        if( result == NUMBER_TYPE )
                        {
                            value = callIns(FUNCTIONID(DoubleVectorObject_getNativeIntProperty), 2,
                                localGetp(sp-1), index);
                            valIsAtom = false;
                        }
                        else
                        {
                            value = callIns(FUNCTIONID(DoubleVectorObject_getIntProperty), 2,
                                localGetp(sp-1), index);
                        }
                    }
                    else
                    {
                        value = callIns(FUNCTIONID(getpropertylate_i), 3,
                            env_param, loadAtomRep(sp-1), index);
                    }

                    localSet(sp-1, valIsAtom?atomToNativeRep(result, value):value, result);
                }
                else if (maybeIntegerIndex && indexType == UINT_TYPE)
                {
                    bool valIsAtom = true;

                    LIns* index = localGet(objDisp--);

                    if (multiname->isRtns())
                    {
                        // Discard runtime namespace
                        objDisp--;
                    }

                    Traits* objType = state->value(objDisp).traits;

                    LIns *value;
                    if (objType == ARRAY_TYPE || (objType!= NULL && objType->subtypeof(VECTOROBJ_TYPE)))
                    {
                        value = callIns((objType==ARRAY_TYPE ?
                                                FUNCTIONID(ArrayObject_getUintProperty) :
                                                FUNCTIONID(ObjectVectorObject_getUintProperty)), 2,
                            localGetp(sp-1), index);
                    }
                    else if( objType == VECTORINT_TYPE || objType == VECTORUINT_TYPE )
                    {
                        if( result == INT_TYPE || result == UINT_TYPE )
                        {
                            value = callIns((objType==VECTORINT_TYPE ?
                                                    FUNCTIONID(IntVectorObject_getNativeUintProperty) :
                                                    FUNCTIONID(UIntVectorObject_getNativeUintProperty)), 2,
                            localGetp(sp-1), index);
                            valIsAtom = false;
                        }
                        else
                        {
                            value = callIns((objType==VECTORINT_TYPE ?
                                                    FUNCTIONID(IntVectorObject_getUintProperty) :
                                                    FUNCTIONID(UIntVectorObject_getUintProperty)), 2,
                            localGetp(sp-1), index);
                        }
                    }
                    else if( objType == VECTORDOUBLE_TYPE )
                    {
                        if( result == NUMBER_TYPE )//|| result == UINT_TYPE)
                        {
                            value = callIns(FUNCTIONID(DoubleVectorObject_getNativeUintProperty), 2,
                                localGetp(sp-1), index);
                            valIsAtom = false;
                        }
                        else
                        {
                            value = callIns(FUNCTIONID(DoubleVectorObject_getUintProperty), 2,
                                localGetp(sp-1), index);
                        }
                    }
                    else
                    {
                        value = callIns(FUNCTIONID(getpropertylate_u), 3,
                            env_param, loadAtomRep(sp-1), index);
                    }

                    localSet(sp-1, valIsAtom?atomToNativeRep(result, value):value, result);
                }
                else if (maybeIntegerIndex && indexType != STRING_TYPE)
                {
                    LIns* multi = InsConstPtr(multiname); // inline ptr to precomputed name
                    LIns* index = loadAtomRep(objDisp--);
                    AvmAssert(state->value(objDisp).notNull);
                    LIns* obj = loadAtomRep(objDisp);
                    LIns* value = callIns(FUNCTIONID(getprop_index), 4,
                                        env_param, obj, multi, index);

                    localSet(objDisp, atomToNativeRep(result, value), result);
                }
                else
                {
                    LIns* multi = initMultiname(multiname, objDisp);
                    AvmAssert(state->value(objDisp).notNull);

                    LIns* value;
                    LIns* obj = loadAtomRep(objDisp);
                    if (multiname->isRuntime()) {
                        //return getprop_late(obj, name);
                        value = callIns(FUNCTIONID(getprop_late), 3, env_param, obj, multi);
                        liveAlloc(multi);
                    } else {
                        // static name, use property cache
                        GetCache* cache = get_cache_builder.allocateCacheSlot(multiname);
                        LIns* cacheAddr = InsConstPtr(cache);
                        LIns* handler = loadIns(LIR_ldp, offsetof(GetCache, get_handler), cacheAddr);
                        value = callIns(FUNCTIONID(get_cache_handler), 4, handler, cacheAddr, env_param, obj);
                    }

                    localSet(objDisp, atomToNativeRep(result, value), result);
                }
                break;
            }
            case OP_initproperty:
            case OP_setproperty:
            {
                // stack in: obj [ns] [name] value
                // stack out:
                // obj = sp[-1]
                //env->setproperty(obj, multiname, sp[0], toVTable(obj));
                //LIns* value = loadAtomRep(sp);

                const Multiname* multiname = (const Multiname*)op1;
                bool attr = multiname->isAttr();
                Traits* indexType = state->value(sp-1).traits;
                Traits* valueType = state->value(sp).traits;
                int objDisp = sp-1;

                bool maybeIntegerIndex = !attr && multiname->isRtname() && multiname->containsAnyPublicNamespace();

                if (maybeIntegerIndex && indexType == INT_TYPE)
                {
                    LIns* index = localGet(objDisp--);

                    if (multiname->isRtns())
                    {
                        // Discard runtime namespace
                        objDisp--;
                    }

                    Traits* objType = state->value(objDisp).traits;

                    if (objType == ARRAY_TYPE || (objType!= NULL && objType->subtypeof(VECTOROBJ_TYPE)))
                    {
                        LIns* value = loadAtomRep(sp);
                        callIns((objType==ARRAY_TYPE ?
                                        FUNCTIONID(ArrayObject_setIntProperty) :
                                        FUNCTIONID(ObjectVectorObject_setIntProperty)), 3,
                            localGetp(objDisp), index, value);
                    }
                    else if(objType == VECTORINT_TYPE || objType == VECTORUINT_TYPE )
                    {
                        if( valueType == INT_TYPE )
                        {
                            LIns* value = localGet(sp);
                            callIns((objType==VECTORINT_TYPE ?
                                            FUNCTIONID(IntVectorObject_setNativeIntProperty) :
                                            FUNCTIONID(UIntVectorObject_setNativeIntProperty)),
                                            3,
                                            localGetp(objDisp), index, value);
                        }
                        else if( valueType == UINT_TYPE )
                        {
                            LIns* value = localGet(sp);
                            callIns((objType==VECTORINT_TYPE ?
                                            FUNCTIONID(IntVectorObject_setNativeIntProperty) :
                                            FUNCTIONID(UIntVectorObject_setNativeIntProperty)),
                                            3,
                                            localGetp(objDisp), index, value);
                        }
                        else
                        {
                            LIns* value = loadAtomRep(sp);
                            value = callIns((objType==VECTORINT_TYPE ?
                                                    FUNCTIONID(IntVectorObject_setIntProperty) :
                                                    FUNCTIONID(UIntVectorObject_setIntProperty)),
                                                    3,
                                                    localGetp(objDisp), index, value);
                        }
                    }
                    else if(objType == VECTORDOUBLE_TYPE)
                    {
                        if( valueType == NUMBER_TYPE )
                        {
                            LIns* value = localGetq(sp);
                            callIns(FUNCTIONID(DoubleVectorObject_setNativeIntProperty), 3,
                                localGetp(objDisp), index, value);
                        }
                        else
                        {
                            LIns* value = loadAtomRep(sp);
                            value = callIns(FUNCTIONID(DoubleVectorObject_setIntProperty), 3,
                                localGetp(objDisp), index, value);
                        }
                    }
                    else
                    {
                        LIns* value = loadAtomRep(sp);
                        callIns(FUNCTIONID(setpropertylate_i), 4,
                            env_param, loadAtomRep(objDisp), index, value);
                    }
                }
                else if (maybeIntegerIndex && indexType == UINT_TYPE)
                {
                    LIns* index = localGet(objDisp--);

                    if (multiname->isRtns())
                    {
                        // Discard runtime namespace
                        objDisp--;
                    }

                    Traits* objType = state->value(objDisp).traits;

                    if (objType == ARRAY_TYPE || (objType!= NULL && objType->subtypeof(VECTOROBJ_TYPE)))
                    {
                        LIns* value = loadAtomRep(sp);
                        callIns((objType==ARRAY_TYPE ?
                                        FUNCTIONID(ArrayObject_setUintProperty) :
                                        FUNCTIONID(ObjectVectorObject_setUintProperty)), 3,
                            localGetp(objDisp), index, value);
                    }
                    else if(objType == VECTORINT_TYPE || objType == VECTORUINT_TYPE )
                    {
                        if( valueType == INT_TYPE )
                        {
                            LIns* value = localGet(sp);
                            callIns((objType==VECTORINT_TYPE ?
                                            FUNCTIONID(IntVectorObject_setNativeUintProperty) :
                                            FUNCTIONID(UIntVectorObject_setNativeUintProperty)),
                                            3,
                                            localGetp(objDisp), index, value);
                        }
                        else if( valueType == UINT_TYPE )
                        {
                            LIns* value = localGet(sp);
                            callIns((objType==VECTORINT_TYPE ?
                                            FUNCTIONID(IntVectorObject_setNativeUintProperty) :
                                            FUNCTIONID(UIntVectorObject_setNativeUintProperty)),
                                            3,
                                            localGetp(objDisp), index, value);
                        }
                        else
                        {
                            LIns* value = loadAtomRep(sp);
                            value = callIns((objType==VECTORINT_TYPE ?
                                                    FUNCTIONID(IntVectorObject_setUintProperty) :
                                                    FUNCTIONID(UIntVectorObject_setUintProperty)),
                                                    3,
                                                    localGetp(objDisp), index, value);
                        }
                    }
                    else if(objType == VECTORDOUBLE_TYPE)
                    {
                        if( valueType == NUMBER_TYPE )
                        {
                            LIns* value = localGetq(sp);
                            callIns(FUNCTIONID(DoubleVectorObject_setNativeUintProperty), 3,
                                localGetp(objDisp), index, value);
                        }
                        else
                        {
                            LIns* value = loadAtomRep(sp);
                            value = callIns(FUNCTIONID(DoubleVectorObject_setUintProperty), 3,
                                localGetp(objDisp), index, value);
                        }
                    }
                    else
                    {
                        LIns* value = loadAtomRep(sp);
                        callIns(FUNCTIONID(setpropertylate_u), 4,
                            env_param, loadAtomRep(objDisp), index, value);
                    }
                }
                else if (maybeIntegerIndex)
                {
                    LIns* name = InsConstPtr(multiname); // precomputed multiname
                    LIns* value = loadAtomRep(sp);
                    LIns* index = loadAtomRep(objDisp--);
                    AvmAssert(state->value(objDisp).notNull);
                    LIns* obj = loadAtomRep(objDisp);
                    const CallInfo *func = opcode==OP_setproperty ? FUNCTIONID(setprop_index) :
                                                        FUNCTIONID(initprop_index);
                    callIns(func, 5, env_param, obj, name, value, index);
                }
                else
                {
                    LIns* value = loadAtomRep(sp);
                    LIns* multi = initMultiname(multiname, objDisp);
                    AvmAssert(state->value(objDisp).notNull);

                    LIns* obj = loadAtomRep(objDisp);
                    if (opcode == OP_setproperty) {
                        if (!multiname->isRuntime()) {
                            // use inline cache for dynamic setproperty access
                            SetCache* cache = set_cache_builder.allocateCacheSlot(multiname);
                            LIns* cacheAddr = InsConstPtr(cache);
                            LIns* handler = loadIns(LIR_ldp, offsetof(SetCache, set_handler), cacheAddr);
                            callIns(FUNCTIONID(set_cache_handler), 5, handler, cacheAddr, obj, value, env_param);
                        } else {
                            // last resort slow path for OP_setproperty
                            callIns(FUNCTIONID(setprop_late), 4, env_param, obj, multi, value);
                            liveAlloc(multi);
                        }
                    }
                    else
                    {
                        // initproplate is rare in jit code because we typically interpret static
                        // initializers, and constructor initializers tend to early-bind successfully.
                        callIns(FUNCTIONID(initprop_late), 4, env_param, obj, multi, value);
                        liveAlloc(multi);
                    }
                }
                break;
            }

            case OP_deleteproperty:
            {
                // stack in: obj [ns] [name]
                // stack out: Boolean
                //sp[0] = delproperty(sp[0], multiname);
                int objDisp = sp;
                Multiname *multiname = (Multiname*)op1;
                if(!multiname->isRtname()) {
                    LIns* multi = initMultiname(multiname, objDisp, true);

                    LIns* obj = loadAtomRep(objDisp);

                    LIns* i3 = callIns(FUNCTIONID(delproperty), 3,
                        env_param, obj, multi);
                    liveAlloc(multi);

                    localSet(objDisp, atomToNativeRep(result, i3), result);
                } else {
                    LIns* _tempname = copyMultiname(multiname);
                    LIns* index = loadAtomRep(objDisp--);

                    if( !multiname->isRtns() )
                    {
                        // copy the compile-time namespace to the temp multiname
                        LIns* mSpace = InsConstPtr(multiname->ns);
                        stp(mSpace, _tempname, offsetof(Multiname, ns));
                    }
                    else
                    {
                        // intern the runtime namespace and copy to the temp multiname
                        LIns* nsAtom = loadAtomRep(objDisp--);
                        LIns* internNs = callIns(FUNCTIONID(internRtns), 2,
                            env_param, nsAtom);

                        stp(internNs, _tempname, offsetof(Multiname,ns));
                    }
                    liveAlloc(_tempname);

                    AvmAssert(state->value(objDisp).notNull);
                    LIns* obj = loadAtomRep(objDisp);

                    LIns* value = callIns(FUNCTIONID(delpropertyHelper), 4,
                                        env_param, obj, _tempname, index);

                    localSet(objDisp, atomToNativeRep(result, value), result);
                }
                break;
            }

            case OP_esc_xelem: // ToXMLString will call EscapeElementValue
            {
                //sp[0] = core->ToXMLString(sp[0]);
                int32_t index = (int32_t) op1;
                LIns* value = loadAtomRep(index);
                LIns* i3 = callIns(FUNCTIONID(ToXMLString), 2,
                    coreAddr, value);
                AvmAssert(result == STRING_TYPE);
                localSet(index, i3, result);
                break;
            }

            case OP_esc_xattr:
            {
                //sp[0] = core->EscapeAttributeValue(sp[0]);
                int32_t index = (int32_t) op1;
                LIns* value = loadAtomRep(index);
                LIns* i3 = callIns(FUNCTIONID(EscapeAttributeValue), 2,
                    coreAddr, value);
                AvmAssert(result == STRING_TYPE);
                localSet(index, i3, result);
                break;
            }

            case OP_astype:
            {
                // sp[0] = AvmCore::astype(sp[0], traits)
                Traits *type = (Traits*) op1;
                int32_t index = (int32_t) op2;
                LIns* obj = loadAtomRep(index);
                LIns* i1 = callIns(FUNCTIONID(astype), 2, obj, InsConstPtr(type));
                i1 = atomToNativeRep(result, i1);
                localSet(index, i1, result);
                break;
            }

            case OP_astypelate:
            {
                //sp[-1] = astype_late(env, sp[-1], sp[0]);
                LIns* type = loadAtomRep(sp);
                LIns* obj = loadAtomRep(sp-1);
                LIns* i3 = callIns(FUNCTIONID(astype_late), 3, env_param, obj, type);
                i3 = atomToNativeRep(result, i3);
                localSet(sp-1, i3, result);
                break;
            }

            case OP_strictequals:
            {
                AvmAssert(result == BOOLEAN_TYPE);
                localSet(sp-1, cmpEq(FUNCTIONID(stricteq), sp-1, sp), result);
                break;
            }

            case OP_equals:
            {
                AvmAssert(result == BOOLEAN_TYPE);
                localSet(sp-1, cmpEq(FUNCTIONID(equals), sp-1, sp), result);
                break;
            }

            case OP_lessthan:
            {
                AvmAssert(result == BOOLEAN_TYPE);
                localSet(sp-1, cmpLt(sp-1, sp), result);
                break;
            }

            case OP_lessequals:
            {
                AvmAssert(result == BOOLEAN_TYPE);
                localSet(sp-1, cmpLe(sp-1, sp), result);
                break;
            }

            case OP_greaterthan:
            {
                AvmAssert(result == BOOLEAN_TYPE);
                localSet(sp-1, cmpLt(sp, sp-1), result);
                break;
            }

            case OP_greaterequals:
            {
                AvmAssert(result == BOOLEAN_TYPE);
                localSet(sp-1, cmpLe(sp, sp-1), result);
                break;
            }

            case OP_instanceof:
            {
                LIns* lhs = loadAtomRep(sp-1);
                LIns* rhs = loadAtomRep(sp);
                LIns* out = callIns(FUNCTIONID(instanceof), 3, env_param, lhs, rhs);
                out = atomToNativeRep(result, out);
                localSet(sp-1,  out, result);
                break;
            }

            case OP_in:
            {
                LIns* lhs = loadAtomRep(sp-1);
                LIns* rhs = loadAtomRep(sp);
                LIns* out = callIns(FUNCTIONID(op_in), 3, env_param, lhs, rhs);
                out = atomToNativeRep(result, out);
                localSet(sp-1, out, result);
                break;
            }

            case OP_dxns:
            {
                LIns* uri = InsConstPtr((String*)op1); // namespace uri from string pool
                callIns(FUNCTIONID(setDxns), 3, coreAddr, methodFrame, uri);
                break;
            }

            case OP_dxnslate:
            {
                int32_t index = (int32_t) op1;
                LIns* atom = loadAtomRep(index);
                callIns(FUNCTIONID(setDxnsLate), 3, coreAddr, methodFrame, atom);
                break;
            }

            /*
             * debugger instructions
             */
            case OP_debugfile:
            {
            #ifdef DEBUGGER
            if (core->debugger())
            {
                // todo refactor api's so we don't have to pass argv/argc
                LIns* debugger = loadIns(LIR_ldcp, offsetof(AvmCore, _debugger),
                                            coreAddr);
                callIns(FUNCTIONID(debugFile), 2,
                        debugger,
                        InsConstPtr((String*)op1));
            }
            #endif // DEBUGGER
           #ifdef VTUNE
                Ins(LIR_file, InsConstPtr((String*)op1));
           #endif /* VTUNE */
                break;
            }

            case OP_debugline:
            {
            #ifdef DEBUGGER
            if (core->debugger())
            {
                // todo refactor api's so we don't have to pass argv/argc
                LIns* debugger = loadIns(LIR_ldcp, offsetof(AvmCore, _debugger),
                                            coreAddr);
                callIns(FUNCTIONID(debugLine), 2,
                        debugger,
                        InsConst((int32_t)op1));
            }
            #endif // DEBUGGER
            #ifdef VTUNE
                Ins(LIR_line, InsConst((int32_t)op1));
                hasDebugInfo = true;
           #endif /* VTUNE */
                break;
            }

            default:
            {
                AvmAssert(false); // unsupported
            }
        }

    } // emit()

    void CodegenLIR::emitIf(FrameState *state, AbcOpcode opcode, int target_off, int a, int b)
    {
        this->state = state;

#ifdef DEBUGGER
        Sampler* s = core->get_sampler();
        if (s && s->sampling() && target_off < state->pc)
        {
            emitSampleCheck();
        }
#endif

        //
        // compile instructions that cannot throw exceptions before we add exception handling logic
        //

        // op1 = abc opcode target
        // op2 = what local var contains condition

        LIns* cond;
        LOpcode br;

        switch (opcode)
        {
        case OP_iftrue:
            NanoAssert(state->value(a).traits == BOOLEAN_TYPE);
            br = LIR_jf;
            cond = eq0(localGet(a));
            break;
        case OP_iffalse:
            NanoAssert(state->value(a).traits == BOOLEAN_TYPE);
            br = LIR_jt;
            cond = eq0(localGet(a));
            break;
        case OP_iflt:
            br = LIR_jt;
            cond = cmpLt(a, b);
            break;
        case OP_ifnlt:
            br = LIR_jf;
            cond = cmpLt(a, b);
            break;
        case OP_ifle:
            br = LIR_jt;
            cond = cmpLe(a, b);
            break;
        case OP_ifnle:
            br = LIR_jf;
            cond = cmpLe(a, b);
            break;
        case OP_ifgt:  // a>b === b<a
            br = LIR_jt;
            cond = cmpLt(b, a);
            break;
        case OP_ifngt: // !(a>b) === !(b<a)
            br = LIR_jf;
            cond = cmpLt(b, a);
            break;
        case OP_ifge:  // a>=b === b<=a
            br = LIR_jt;
            cond = cmpLe(b, a);
            break;
        case OP_ifnge: // !(a>=b) === !(a<=b)
            br = LIR_jf;
            cond = cmpLe(b, a);
            break;
        case OP_ifeq:
            br = LIR_jt;
            cond = cmpEq(FUNCTIONID(equals), a, b);
            break;
        case OP_ifne:
            br = LIR_jf;
            cond = cmpEq(FUNCTIONID(equals), a, b);
            break;
        case OP_ifstricteq:
            br = LIR_jt;
            cond = cmpEq(FUNCTIONID(stricteq), a, b);
            break;
        case OP_ifstrictne:
            br = LIR_jf;
            cond = cmpEq(FUNCTIONID(stricteq), a, b);
            break;
        default:
            AvmAssert(false);
            return;
        }

        if (cond->isconst()) {
            if ((br == LIR_jt && cond->imm32()) || (br == LIR_jf && !cond->imm32())) {
                // taken
                br = LIR_j;
                cond = 0;
            }
            else {
                // not taken = no-op
                return;
            }
        }

        branchIns(br, cond, target_off);
    } // emitIf()

    // Faster compares for ints, uint, doubles
    LIns* CodegenLIR::cmpOptimization(int lhsi, int rhsi, LOpcode icmp, LOpcode ucmp, LOpcode fcmp)
    {
        Traits* lht = state->value(lhsi).traits;
        Traits* rht = state->value(rhsi).traits;

        if (lht == rht && lht == INT_TYPE)
        {
            LIns* lhs = localGet(lhsi);
            LIns* rhs = localGet(rhsi);
            return binaryIns(icmp, lhs, rhs);
        }
        else if (lht == rht && lht == UINT_TYPE)
        {
            LIns* lhs = localGet(lhsi);
            LIns* rhs = localGet(rhsi);
            return binaryIns(ucmp, lhs, rhs);
        }
        else if (lht && lht->isNumeric() && rht && rht->isNumeric())
        {
            // If we're comparing a uint to an int and the int is a non-negative
            // integer constant, don't promote to doubles for the compare
            if ((lht == UINT_TYPE) && (rht == INT_TYPE))
            {
                LIns* lhs = localGet(lhsi);
                LIns* rhs = localGet(rhsi);
            #ifdef AVMPLUS_64BIT
                // 32-bit signed and unsigned values fit in 64-bit registers
                // so we can promote and simply do a signed 64bit compare
                LOpcode qcmp = i32cmp_to_i64cmp(icmp);
                NanoAssert((icmp == LIR_eq && qcmp == LIR_qeq) ||
                           (icmp == LIR_lt && qcmp == LIR_qlt) ||
                           (icmp == LIR_le && qcmp == LIR_qle));
                return binaryIns(qcmp, u2p(lhs), i2p(rhs));
            #else
                if (rhs->isconst() && rhs->imm32() >= 0)
                    return binaryIns(ucmp, lhs, rhs);
            #endif
            }
            else if ((lht == INT_TYPE) && (rht == UINT_TYPE))
            {
                LIns* lhs = localGet(lhsi);
                LIns* rhs = localGet(rhsi);
            #ifdef AVMPLUS_64BIT
                // 32-bit signed and unsigned values fit in 64-bit registers
                // so we can promote and simply do a signed 64bit compare
                LOpcode qcmp = i32cmp_to_i64cmp(icmp);
                NanoAssert((icmp == LIR_eq && qcmp == LIR_qeq) ||
                           (icmp == LIR_lt && qcmp == LIR_qlt) ||
                           (icmp == LIR_le && qcmp == LIR_qle));
                return binaryIns(qcmp, i2p(lhs), u2p(rhs));
            #else
                if (lhs->isconst() && lhs->imm32() >= 0)
                    return binaryIns(ucmp, lhs, rhs);
            #endif
            }

            LIns* lhs = promoteNumberIns(lht, lhsi);
            LIns* rhs = promoteNumberIns(rht, rhsi);
            return binaryIns(fcmp, lhs, rhs);
        }

        return NULL;
    }

    // set cc's for < operator
    LIns* CodegenLIR::cmpLt(int lhsi, int rhsi)
    {
        LIns *result = cmpOptimization (lhsi, rhsi, LIR_lt, LIR_ult, LIR_flt);
        if (result)
            return result;

        AvmAssert(trueAtom == 13);
        AvmAssert(falseAtom == 5);
        AvmAssert(undefinedAtom == 4);
        LIns* lhs = loadAtomRep(lhsi);
        LIns* rhs = loadAtomRep(rhsi);
        LIns* atom = callIns(FUNCTIONID(compare), 3,
            coreAddr, lhs, rhs);

        // caller will use jt for (a<b) and jf for !(a<b)
        // compare          ^8    <8
        // true       1101  0101   y
        // false      0101  1101   n
        // undefined  0100  1100   n

        LIns* c = InsConst(8);
        return binaryIns(LIR_lt, binaryIns(LIR_xor, p2i(atom), c), c);
    }

    LIns* CodegenLIR::cmpLe(int lhsi, int rhsi)
    {
        LIns *result = cmpOptimization (lhsi, rhsi, LIR_le, LIR_ule, LIR_fle);
        if (result)
            return result;

        LIns* lhs = loadAtomRep(lhsi);
        LIns* rhs = loadAtomRep(rhsi);
        LIns* atom = callIns(FUNCTIONID(compare), 3,
            coreAddr, rhs, lhs);

        // assume caller will use jt for (a<=b) and jf for !(a<=b)
        // compare          ^1    <=4
        // true       1101  1100  n
        // false      0101  0100  y
        // undefined  0100  0101  n

        LIns* c2 = InsConst(1);
        LIns* c4 = InsConst(4);
        return binaryIns(LIR_le, binaryIns(LIR_xor, p2i(atom), c2), c4);
    }

    LIns* CodegenLIR::cmpEq(const CallInfo *fid, int lhsi, int rhsi)
    {
        LIns *result = cmpOptimization (lhsi, rhsi, LIR_eq, LIR_eq, LIR_feq);
        if (result) {
            return result;
        }

        Traits* lht = state->value(lhsi).traits;
        Traits* rht = state->value(rhsi).traits;

        // If we have null and a type that is derived from an Object (but not Object or XML)
        // we can optimize our equal comparison down to a simple ptr comparison. This also
        // works when both types are derived Object types.
        if (((lht == NULL_TYPE) && (rht && !rht->notDerivedObjectOrXML())) ||
            ((rht == NULL_TYPE) && (lht && !lht->notDerivedObjectOrXML())) ||
            ((rht && !rht->notDerivedObjectOrXML()) && (lht && !lht->notDerivedObjectOrXML())))
        {
            LIns* lhs = localGetp(lhsi);
            LIns* rhs = localGetp(rhsi);
            result = binaryIns(LIR_peq, lhs, rhs);
        }
        else
        {
            LIns* lhs = loadAtomRep(lhsi);
            LIns* rhs = loadAtomRep(rhsi);
            LIns* out = callIns(fid, 3, coreAddr, lhs, rhs);
            result = binaryIns(LIR_peq, out, InsConstAtom(trueAtom));
        }
        return result;
    }

    void CodegenLIR::writeEpilogue(FrameState *state)
    {
        this->state = state;
        this->labelCount = state->verifier->labelCount;

        if (mop_rangeCheckFailed_label.has_preds) {
            LIns* range_label = label();
            verbose_only( if (frag->lirbuf->names) { frag->lirbuf->names->addName(range_label, "mop_rangeCheckFailed"); })
            setLabelPos(mop_rangeCheckFailed_label, range_label);
            callIns(FUNCTIONID(mop_rangeCheckFailed), 1, env_param);
        }

        if (npe_label.has_preds) {
            LIns *npelabel = label();
            verbose_only( if (frag->lirbuf->names) { frag->lirbuf->names->addName(npelabel, "npe"); })
            setLabelPos(npe_label, npelabel);
            callIns(FUNCTIONID(npe), 1, env_param);
        }

        if (interrupt_label.has_preds) {
            LIns *intlabel = label();
            verbose_only( if (frag->lirbuf->names) { frag->lirbuf->names->addName(intlabel, "interrupt"); })
            setLabelPos(interrupt_label, intlabel);
            callIns(FUNCTIONID(handleInterruptMethodEnv), 1, env_param);
        }

        if (info->hasExceptions()) {
            LIns *catchlabel = label();
            verbose_only( if (frag->lirbuf->names) { frag->lirbuf->names->addName(catchlabel, "catch"); })
            exBranch->setTarget(catchlabel);

            // exception case
            LIns *exptr = loadIns(LIR_ldp, offsetof(AvmCore, exceptionAddr), coreAddr);
            LIns *exAtom = loadIns(LIR_ldp, offsetof(Exception, atom), exptr);
            localSet(state->verifier->stackBase, exAtom, NULL_TYPE);
            // need to convert exception from atom to native rep, at top of
            // catch handler.  can't do it here because it could be any type.

            // _ef.beginCatch()
            LIns* pc = loadIns(LIR_ldp, 0, _save_eip);
            LIns* handler = callIns(FUNCTIONID(beginCatch), 5,
                coreAddr, _ef, InsConstPtr(info), pc, exptr);

            int handler_count = info->abc_exceptions()->exception_count;
            // Jump to catch handler
            LIns *handler_target = loadIns(LIR_ld, offsetof(ExceptionHandler, target), handler);
            // Do a compare & branch to each possible target.
            for (int i=0; i < handler_count; i++)
            {
                ExceptionHandler* h = &info->abc_exceptions()->exceptions[i];
                int handler_pc_off = h->target;
                if (i+1 < handler_count) {
                    branchIns(LIR_jt, binaryIns(LIR_eq, handler_target, InsConst(handler_pc_off)), handler_pc_off);
                } else {
                    branchIns(LIR_j, 0, handler_pc_off);
                }
            }
        }

        // extend live range of critical stuff
        // fixme -- this should be automatic based on live analysis
        Ins(LIR_live, methodFrame);
        Ins(LIR_live, env_param);
        Ins(LIR_live, coreAddr);
        Ins(LIR_live, undefConst);

        if (info->hasExceptions()) {
            Ins(LIR_live, _ef);
            Ins(LIR_live, _save_eip);
        }

        LIns* last = Ins(LIR_live, vars);

        #ifdef DEBUGGER
        if (core->debugger())
        {
            Ins(LIR_live, csn);
            last = Ins(LIR_live, varTraits);
        }
        #endif

        for (Seq<Patch>* p = patches.get(); p != NULL; p = p->tail) {
            Patch& patch = p->head;
            AvmAssert(patch.label->bb != NULL);
            if (patch.br->isop(LIR_jtbl)) {
                patch.br->setTarget(patch.index, patch.label->bb);
            } else {
                AvmAssert(patch.br->isBranch() && patch.index == 0);
                patch.br->setTarget(patch.label->bb);
            }
        }

        frag->lastIns = last;

        info->set_lookup_cache_size(finddef_cache_builder.next_cache);
    }

    // emit code to create a stack-allocated copy of the given multiname.
    // this helper only initializes Multiname.flags and Multiname.next_index
    LIns* CodegenLIR::copyMultiname(const Multiname* multiname)
    {
        LIns* name = InsAlloc(sizeof(Multiname));
        sti(InsConst(multiname->ctFlags()), name, offsetof(Multiname, flags));
        sti(InsConst(multiname->next_index), name, offsetof(Multiname, next_index));
        return name;
    }

    LIns* CodegenLIR::initMultiname(const Multiname* multiname, int& csp, bool isDelete /*=false*/)
    {
        if (!multiname->isRuntime()) {
            // use the precomputed multiname
            return InsConstPtr(multiname);
        }

        // create an initialize a copy of the given multiname
        LIns* _tempname = copyMultiname(multiname);

        // then initialize its name and ns|nsset fields.
        LIns* nameAtom = NULL;
        if (multiname->isRtname())
        {
            nameAtom = loadAtomRep(csp--);
        }
        else
        {
            // copy the compile-time name to the temp name
            LIns* mName = InsConstPtr(multiname->name);
            stp(mName, _tempname, offsetof(Multiname,name));
        }

        if (multiname->isRtns())
        {
            // intern the runtime namespace and copy to the temp multiname
            LIns* nsAtom = loadAtomRep(csp--);
            LIns* internNs = callIns(FUNCTIONID(internRtns), 2,
                env_param, nsAtom);

            stp(internNs, _tempname, offsetof(Multiname,ns));
        }
        else
        {
            // copy the compile-time namespace to the temp multiname
            LIns* mSpace = InsConstPtr(multiname->ns);
            stp(mSpace, _tempname, offsetof(Multiname, ns));
        }

        // Call initMultinameLate as the last step, since if a runtime
        // namespace is present, initMultinameLate may clobber it if a
        // QName is provided as index.
        if (nameAtom)
        {
            if (isDelete)
            {
                callIns(FUNCTIONID(initMultinameLateForDelete), 3,
                        env_param, _tempname, nameAtom);
            }
            else
            {
                callIns(FUNCTIONID(initMultinameLate), 3,
                        coreAddr, _tempname, nameAtom);
            }
        }

        return _tempname;
    }

    LIns* CodegenLIR::loadToplevel()
    {
        LIns* vtable = loadEnvVTable();
        return loadIns(LIR_ldcp, offsetof(VTable,_toplevel), vtable);
    }

    static bool sumFitsInInt32(int32_t a, int32_t b)
    {
        return int64_t(a) + int64_t(b) == int64_t(a + b);
    }

    LIns* CodegenLIR::mopAddrToRangeCheckedRealAddrAndDisp(LIns* mopAddr, int32_t const size, int32_t* disp)
    {
        AvmAssert(size > 0);    // it's signed to help make the int promotion correct

        if (!globalMemoryInfo)
        {
            globalMemoryInfo = (GlobalMemoryInfo*)pool->codeMgr->allocator.alloc(sizeof(GlobalMemoryInfo));
            globalMemoryInfo->base = pool->domain->globalMemoryBase();
            globalMemoryInfo->size = pool->domain->globalMemorySize();
            pool->domain->addGlobalMemoryBaseRef(&globalMemoryInfo->base);
            pool->domain->addGlobalMemorySizeRef(&globalMemoryInfo->size);
        }

        if (disp != NULL)
        {
            *disp = 0;

            // mopAddr is an int (an offset from globalMemoryBase) on all archs.
            // if mopAddr is an expression of the form
            //      expr+const
            //      const+expr
            //      expr-const
            //      (but not const-expr)
            // then try to pull the constant out and return it as a displacement to
            // be used in the instruction as an addressing-mode offset.
            // (but only if caller requests it that way.)
            for (;;)
            {
                LOpcode const op = mopAddr->opcode();
                if (op != LIR_add && op != LIR_sub)
                    break;

                int32_t imm;
                LInsp nonImm;
                if (mopAddr->oprnd2()->isconst())
                {
                    imm = mopAddr->oprnd2()->imm32();
                    nonImm = mopAddr->oprnd1();

                    if (op == LIR_sub)
                        imm = -imm;
                }
                else if (mopAddr->oprnd1()->isconst())
                {
                    // don't try to optimize const-expr
                    if (op == LIR_sub)
                        break;

                    imm = mopAddr->oprnd1()->imm32();
                    nonImm = mopAddr->oprnd2();
                }
                else
                {
                    break;
                }

                if (!sumFitsInInt32(*disp, imm))
                    break;

                *disp += imm;
                mopAddr = nonImm;
            }
        }

        LInsp mopsMemoryBase = loadIns(LIR_ldcp, 0, InsConstPtr(&globalMemoryInfo->base));
        LInsp mopsMemorySize = loadIns(LIR_ldc, 0, InsConstPtr(&globalMemoryInfo->size));

        LInsp lhs, rhs, br;
        if (!disp || *disp == 0)
        {
            // note that the mops "addr" (offset from globalMemoryBase) is in fact a signed int, so we have to check
            // for it being < 0 ... but we can get by with a single unsigned compare since all values < 0 will be > size
            lhs = mopAddr;
            rhs = binaryIns(LIR_sub, mopsMemorySize, InsConst(size));
            br = branchIns(LIR_jt, binaryIns(LIR_ugt, lhs, rhs));
            patchLater(br, mop_rangeCheckFailed_label);
        }
        else
        {
            // @todo, can we get by with a simpler test here?
            lhs = binaryIns(LIR_add, mopAddr, InsConst(*disp));
            rhs = InsConst(0);
            br = branchIns(LIR_jt, binaryIns(LIR_lt, lhs, rhs));
            patchLater(br, mop_rangeCheckFailed_label);

            lhs = binaryIns(LIR_add, mopAddr, InsConst(*disp+size));
            rhs = mopsMemorySize;
            br = branchIns(LIR_jt, binaryIns(LIR_gt, lhs, rhs));
            patchLater(br, mop_rangeCheckFailed_label);
        }

        // if mopAddr is a compiletime constant, we still have to do the range-check above
        // (since globalMemorySize can vary at runtime), but we might be able to encode
        // the address into the displacement (if any)...
        if (mopAddr->isconst() && disp != NULL && sumFitsInInt32(*disp, mopAddr->imm32()))
        {
            *disp += mopAddr->imm32();
            return mopsMemoryBase;
        }
        // note: we can use piadd here only because we know this is never a GCObject.
        // (if it was, we'd have to use LIR_addp, which is restricted from certain
        // optimizations that can leave dangling interior pointers)
        //
        // (yes, i2p, not u2p... it might legitimately be negative due to the
        // displacement optimization loop above.)
        return binaryIns(LIR_piadd, mopsMemoryBase, i2p(mopAddr));
    }

    LIns* CodegenLIR::loadEnvScope()
    {
        LIns* scope = loadIns(LIR_ldcp, offsetof(MethodEnv,_scope), env_param);
        return scope;
    }

    LIns* CodegenLIR::loadEnvVTable()
    {
        LIns* scope = loadIns(LIR_ldcp, offsetof(MethodEnv,_scope), env_param);
        LIns* vtable = loadIns(LIR_ldcp, offsetof(ScopeChain,_vtable), scope);
        return vtable;
    }

    LIns* CodegenLIR::loadEnvAbcEnv()
    {
        LIns* scope = loadIns(LIR_ldcp, offsetof(MethodEnv,_scope), env_param);
        LIns* abcenv = loadIns(LIR_ldcp, offsetof(ScopeChain,_abcEnv), scope);
        return abcenv;
    }

    LIns* CodegenLIR::loadVTable(int i)
    {
        AvmAssert(state->value(i).notNull);
        Traits* t = state->value(i).traits;

        if (t && !t->isMachineType() && t != STRING_TYPE && t != NAMESPACE_TYPE && t != NULL_TYPE)
        {
            // must be a pointer to a scriptobject, and we've done the n
            // all other types are ScriptObject, and we've done the null check
            return loadIns(LIR_ldcp, offsetof(ScriptObject, vtable), localGetp(i));
        }

        LIns* toplevel = loadToplevel();

        int offset;
        if (t == NAMESPACE_TYPE)    offset = offsetof(Toplevel, namespaceClass);
        else if (t == STRING_TYPE)  offset = offsetof(Toplevel, stringClass);
        else if (t == BOOLEAN_TYPE) offset = offsetof(Toplevel, booleanClass);
        else if (t == NUMBER_TYPE)  offset = offsetof(Toplevel, numberClass);
        else if (t == INT_TYPE)     offset = offsetof(Toplevel, intClass);
        else if (t == UINT_TYPE)    offset = offsetof(Toplevel, uintClass);
        else
        {
            // *, Object or Void
            LIns* obj = loadAtomRep(i);
            return callIns(FUNCTIONID(toVTable), 2, toplevel, obj);
        }

        // now offset != -1 and we are returning a primitive vtable

        LIns* cc = loadIns(LIR_ldcp, offset, toplevel);
        LIns* cvtable = loadIns(LIR_ldcp, offsetof(ClassClosure, vtable), cc);
        return loadIns(LIR_ldcp, offsetof(VTable, ivtable), cvtable);
    }

    LIns* CodegenLIR::promoteNumberIns(Traits* t, int i)
    {
        if (t == NUMBER_TYPE)
        {
            return localGetq(i);
        }
        if (t == INT_TYPE || t == BOOLEAN_TYPE)
        {
            return i2dIns(localGet(i));
        }
        AvmAssert(t == UINT_TYPE);
        return u2dIns(localGet(i));
    }

    void CodegenLIR::formatOperand(PrintWriter& buffer, Value& v)
    {
#ifdef NJ_VERBOSE
        if (v.ins) formatOperand(buffer, v.ins);
#else
        (void)buffer;
        (void)v;
#endif
    }

#ifdef NJ_VERBOSE
    void CodegenLIR::formatOperand(PrintWriter& buffer, LIns* opr)
    {
        if (opr) {
            buffer.format("@%s", frag->lirbuf->names->formatRef(opr));
        }
        else {
            buffer << "0";
        }
    }
#endif /* NJ_VERBOSE */

    /* set position of label */
    void CodegenLIR::setLabelPos(CodegenLabel& l, LIns* bb) {
        AvmAssert(bb->isop(LIR_label));
        AvmAssert(l.bb == 0);
        l.bb = bb;
    }

#ifdef DEBUGGER
    void CodegenLIR::emitSampleCheck()
    {
        /* @todo inline the sample check code, help!  */
        callIns(FUNCTIONID(sampleCheck), 1, coreAddr);
    }
#endif

#ifdef NJ_VERBOSE
    bool CodegenLIR::verbose()
    {
        return (state && state->verifier->verbose) || pool->isVerbose(VB_jit);
    }
#endif

    LIns *CodegenLIR::branchIns(LOpcode op, LIns *cond) {
        if (cond) {
            if (!cond->isCmp()) {
                // branching on a non-condition expression, so test (v==0)
                // and invert the sense of the branch.
                cond = eq0(cond);
                op = LOpcode(op ^ 1);
            }
            if (cond->isconst()) {
                if ((op == LIR_jt && cond->imm32()) || (op == LIR_jf && !cond->imm32())) {
                    // taken
                    op = LIR_j;
                    cond = 0;
                }
                else {
                    // not taken - no code to emit.
                    return 0;
                }
            }
        }
        return lirout->insBranch(op, cond, 0);
    }

    LIns *CodegenLIR::branchIns(LOpcode op, LIns *cond, int pc_off) {
        LIns *br = branchIns(op, cond);
        patchLater(br, pc_off);
        return br;
    }

    /* patch the location 'where' with the value of the label */
    void CodegenLIR::patchLater(LIns* br, int pc_off)   {
        patchLater(br, state->verifier->getFrameState(pc_off)->label);
    }

    void CodegenLIR::patchLater(LIns* jtbl, int pc_off, uint32_t index) {
        patchLater(jtbl, state->verifier->getFrameState(pc_off)->label, index);
    }

    void CodegenLIR::patchLater(LIns *br, CodegenLabel &l) {
        if (!br) return; // occurs if branch was unconditional and thus never emitted.
        l.has_preds = 1;
        if (l.bb != 0) {
            br->setTarget(l.bb);
        } else {
            patches.add(Patch(br, l));
        }
    }

    void CodegenLIR::patchLater(LIns *jtbl, CodegenLabel &l, uint32_t index) {
        l.has_preds = 1;
        if (l.bb != 0) {
            jtbl->setTarget(index, l.bb);           // backward edge
        } else {
            l.jtbl_forward_target = 1;              // target of jtbl forward edge
            patches.add(Patch(jtbl, l, index));
        }
    }

    LIns* CodegenLIR::InsAlloc(int32_t size) {
        //fixme - why InsAlloc(0)?
        return lirout->insAlloc(size >= 4 ? size : 4);
    }

    CodeMgr::CodeMgr() : codeAlloc()
#ifdef NJ_VERBOSE
        , labels(allocator, &log)
#endif
        , bindingCaches(NULL)
    {
        verbose_only( log.lcbits = 0; )
    }

    void CodeMgr::flushBindingCaches()
    {
        // this clears vtable so all kObjectType receivers are invalidated.
        // of course, this field is also "tag" for primitive receivers,
        // but 0 is never a legal value there (and this is asserted when the tag is set)
        // so this should safely invalidate those as well (though we don't really need to invalidate them)
        for (BindingCache* b = bindingCaches; b != NULL; b = b->next)
            b->vtable = NULL;
    }

#ifdef _DEBUG
    class ValidateReader: public LirFilter {
    public:
        ValidateReader(LirFilter *in) : LirFilter(in)
        {}

        LIns* read() {
            LIns *i = in->read();
            switch (i->opcode()) {
            case LIR_jt:
            case LIR_jf:
            case LIR_j:
                AvmAssert(i->getTarget() != NULL && i->getTarget() == i->oprnd2() && i->oprnd2()->isop(LIR_label));
                break;
            case LIR_jtbl:
                AvmAssert(i->getTableSize() > 0);
                for (uint32_t j=0, n=i->getTableSize(); j < n; j++)
                    AvmAssert(i->getTarget(j) != NULL && i->getTarget(j)->isop(LIR_label));
                break;
            }
            return i;
        }
    };
#endif

    void analyze_edge(LIns* label, nanojit::BitSet &livein,
                      HashMap<LIns*, nanojit::BitSet*> &labels,
                      InsList* looplabels)
    {
        nanojit::BitSet *lset = labels.get(label);
        if (lset) {
            livein.setFrom(*lset);
        } else {
            looplabels->add(label);
        }
    }

    void CodegenLIR::deadvars_analyze(Allocator& alloc, nanojit::BitSet& livein,
        HashMap<LIns*, nanojit::BitSet*> &labels)
    {
        LirBuffer *lirbuf = frag->lirbuf;
        LIns *catcher = exBranch ? exBranch->getTarget() : 0;
        LIns *vars = lirbuf->sp;
        InsList looplabels(alloc);

        verbose_only(int iter = 0;)
        bool again;
        do {
            again = false;
            livein.reset();
            LirReader in(frag->lastIns);
            for (LIns *i = in.read(); !i->isop(LIR_start); i = in.read()) {
                LOpcode op = i->opcode();
                switch (op) {
                case LIR_ret:
                case LIR_fret:
                    livein.reset();
                    break;
                case LIR_sti:
                case LIR_stqi:
                    if (i->oprnd2() == vars) {
                        int d = i->disp() >> 3;
                        livein.clear(d);
                    }
                    break;
                case LIR_ld:
                case LIR_ldc:
                case LIR_ldq:
                case LIR_ldqc:
                    if (i->oprnd1() == vars) {
                        int d = i->disp() >> 3;
                        livein.set(d);
                    }
                    break;
                case LIR_label: {
                    // we're at the top of a block, save livein for this block
                    // so it can be propagated to predecessors
                    nanojit::BitSet *lset = labels.get(i);
                    if (!lset) {
                        lset = new (alloc) nanojit::BitSet(alloc, framesize);
                        labels.put(i, lset);
                    }
                    if (lset->setFrom(livein) && !again) {
                        for (Seq<LIns*>* p = looplabels.get(); p != NULL; p = p->tail) {
                            if (p->head == i) {
                                again = true;
                                break;
                            }
                        }
                    }
                    break;
                }
                case LIR_j:
                    // the fallthrough path is unreachable, clear it.
                    livein.reset();
                    // fall through to other branch cases
                case LIR_jt:
                case LIR_jf:
                    // merge the LiveIn sets from each successor:  the fall
                    // through case (livein) and the branch case (lset).
                    analyze_edge(i->getTarget(), livein, labels, &looplabels);
                    break;
                case LIR_jtbl:
                    livein.reset(); // fallthrough path is unreachable, clear it.
                    for (uint32_t j=0, n=i->getTableSize(); j < n; j++)
                        analyze_edge(i->getTarget(j), livein, labels, &looplabels);
                    break;
                case LIR_qcall:
                case LIR_icall:
                case LIR_fcall:
                    if (catcher && !i->isCse()) {
                        // non-cse call is like a conditional forward branch to the catcher label.
                        // this could be made more precise by checking whether this call
                        // can really throw, and only processing edges to the subset of
                        // reachable catch blocks.  If we haven't seen the catch label yet then
                        // the call is to an exception handling helper (eg beginCatch())
                        // that won't throw.
                        nanojit::BitSet *lset = labels.get(catcher);
                        if (lset)
                            livein.setFrom(*lset);
                    }
                    break;
                }
            }
            verbose_only(iter++;)
        }
        while (again);

        // now make a final pass, modifying LIR to delete dead stores (make them LIR_neartramps)
        verbose_only( if (pool->isVerbose(VB_jit))
            AvmLog("killing dead stores after %d LA iterations.\n",iter);
        )
    }

    void CodegenLIR::deadvars_kill(nanojit::BitSet& livein, HashMap<LIns*, nanojit::BitSet*> &labels)
    {
        // table of LIR instruction sizes (private to this file)
        // TODO this can go away if we turn this kill pass into a LirReader
        // and do the work inline with the assembly pass.
        static const uint8_t lirSizes[] = {
        #define OPDEF(op, number, repkind, retType) sizeof(LIns##repkind),
        #include "../nanojit/LIRopcode.tbl"
        #undef OPDEF
                0
        };

        verbose_only(LirNameMap *names = frag->lirbuf->names;)
        verbose_only(bool verbose = names && pool->isVerbose(VB_jit); )
        LIns *catcher = exBranch ? exBranch->getTarget() : 0;
        LirBuffer *lirbuf = frag->lirbuf;
        LIns *vars = lirbuf->sp;
        livein.reset();
        LirReader in(frag->lastIns);
        for (LIns *i = in.read(); !i->isop(LIR_start); i = in.read()) {
            LOpcode op = i->opcode();
            switch (op) {
                case LIR_ret:
                case LIR_fret:
                    livein.reset();
                    break;
                case LIR_sti:
                case LIR_stqi:
                    if (i->oprnd2() == vars) {
                        int d = i->disp() >> 3;
                        if (!livein.get(d)) {
                            verbose_only(if (verbose)
                                AvmLog("- %s\n", names->formatIns(i));)
                            // erase the store by rewriting it as a skip
                            LIns* prevIns = (LIns*) (uintptr_t(i) - lirSizes[op]);
                            i->initLInsSk(prevIns);
                            continue;
                        } else {
                            livein.clear(d);
                        }
                    }
                    break;
                case LIR_ld:
                case LIR_ldc:
                case LIR_ldq:
                case LIR_ldqc:
                    if (i->oprnd1() == vars) {
                        int d = i->disp() >> 3;
                        livein.set(d);
                    }
                    break;
                case LIR_label: {
                    // we're at the top of a block, save livein for this block
                    // so it can be propagated to predecessors
                    nanojit::BitSet *lset = labels.get(i);
                    AvmAssert(lset != 0); // all labels have been seen by deadvars_analyze()
                    lset->setFrom(livein);
                    break;
                }
                case LIR_j:
                    // the fallthrough path is unreachable, clear it.
                    livein.reset();
                    // fall through to other branch cases
                case LIR_jt:
                case LIR_jf:
                    // merge the LiveIn sets from each successor:  the fall
                    // through case (live) and the branch case (lset).
                    analyze_edge(i->getTarget(), livein, labels, 0);
                    break;
                case LIR_jtbl:
                    livein.reset();
                    for (uint32_t j = 0, n = i->getTableSize(); j < n; j++)
                        analyze_edge(i->getTarget(j), livein, labels, 0);
                    break;
                case LIR_qcall:
                case LIR_icall:
                case LIR_fcall:
                    if (catcher && !i->isCse()) {
                        // non-cse call is like a conditional branch to the catcher label.
                        // this could be made more precise by checking whether this call
                        // can really throw, and only processing edges to the subset of
                        // reachable catch blocks.
                        nanojit::BitSet *lset = labels.get(catcher);
                        AvmAssert(lset != 0); // this is a forward branch, we have seen the label.
                        // the target LiveIn set (lset) is non-empty,
                        // union it with fall-through set (live).
                        livein.setFrom(*lset);
                    }
                    break;
            }
            verbose_only(if (verbose) {
                AvmLog("  %s\n", names->formatIns(i));
            })
        }
    }

    /*
     * this is iterative live variable analysis.  We walk backwards through
     * the code.  when we see a load, we mark the variable live, and when
     * we see a store, we mark it dead.  Dead stores are dropped, not returned
     * by read().
     *
     * at labels, we save the liveIn set associated with that label.
     *
     * at branches, we merge the liveIn sets from the fall through case (which
     * is the current set) and the branch case (which was saved with the label).
     * this filter can be run multiple times, which is required to pick up
     * loop-carried live variables.
     *
     * once the live sets are stable, the DeadVars.kill flag is set to cause the filter
     * to not only drop dead stores, but overwrite them as tramps so they'll be
     * ignored by any later passes even without using this filter.
     */

    void CodegenLIR::deadvars()
    {
        // if debugging, don't eliminate vars.  this way the debugger sees the true
        // variable state at each safe point.
        DEBUGGER_ONLY(if (core->debugger()) return; )

        // allocator used only for duration of this phase.  no exceptions are
        // thrown while this phase runs, hence no try/catch is necessary.
        Allocator dv_alloc;

        // map of label -> bitset, tracking what is livein at each label.
        // populated by deadvars_analyze, then used by deadvars_kill
        // estimate number of required buckets based on the verifier's labelCount,
        // which is slightly below the actual # of labels in LIR.  being slightly low
        // is okay for a bucket hashtable.  note: labelCount is 0 for simple 1-block
        // methods, so use labelCount+1 as the estimate to ensure we have >0 buckets.
        HashMap<LIns*, nanojit::BitSet*> labels(dv_alloc, labelCount + 1);

        // scratch bitset used by both dv_analyze and dv_kill.  Each resets
        // the bitset before using it.  creating it here saves one allocation.
        nanojit::BitSet livein(dv_alloc, framesize);

        deadvars_analyze(dv_alloc, livein, labels);
        deadvars_kill(livein, labels);
    }

#ifdef AVMPLUS_JITMAX
    int jitcount = 0;
    int jitmin = 1;
    int jitmax = 0x7fffffff;
#endif

    void CodegenLIR::emitMD()
    {
        mmfx_delete( alloc1 );
        alloc1 = NULL;

        PERFM_NTPROF("compile");
        debug_only(
            LirReader reader(frag->lastIns);
            ValidateReader validator(&reader);
            for (LIns* i = validator.read(); !i->isop(LIR_start); i = validator.read())
            { }
        )

        deadvars();

        CodeMgr *mgr = pool->codeMgr;
        verbose_only(if (pool->isVerbose(VB_jit)) {
            Allocator live_alloc;
            nanojit::live(live_alloc, frag, &mgr->log);
        })

        Assembler *assm = new (*lir_alloc) Assembler(mgr->codeAlloc, mgr->allocator, *lir_alloc, core, &mgr->log);
        #ifdef VTUNE
        assm->cgen = this;
        #endif

        LirReader bufreader(frag->lastIns);

        verbose_only( StringList asmOutput(*lir_alloc); )
        verbose_only( assm->_outputCache = &asmOutput; )

        assm->beginAssembly(frag);
        assm->assemble(frag, &bufreader);
        assm->endAssembly(frag);
        PERFM_TPROF_END();

        verbose_only(
            assm->_outputCache = 0;
            for (Seq<char*>* p = asmOutput.get(); p != NULL; p = p->tail) {
                assm->outputf("%s", p->head);
            }
        );

        PERFM_NVPROF("IR-bytes", frag->lirbuf->byteCount());
        PERFM_NVPROF("IR", frag->lirbuf->insCount());

        bool keep = //!info->hasExceptions() &&
            !assm->error();
    #ifdef AVMPLUS_JITMAX
        jitcount++;
        keep = keep && (jitcount >= jitmin && jitcount <= jitmax);
        //AvmLog(stderr, "jitcount %d keep %d\n", jitcount, (int)keep);
    #endif
        //_nvprof("keep",keep);
        if (keep) {
            // save pointer to generated code
            union {
                GprMethodProc fp;
                void *vp;
            } u;
            u.vp = frag->code();
            info->setNativeImpl(u.fp);
            // mark method as been JIT'd
            info->_flags |= MethodInfo::JIT_IMPL;
            #if defined AVMPLUS_JITMAX && defined NJ_VERBOSE
            if (verbose())
                AvmLog("keeping %d, loop=%d\n", jitcount, assm->hasLoop);
            #endif
        } else {
            // assm puked, or we did something untested, so interpret.
            overflow = true;
            #if defined AVMPLUS_JITMAX && defined NJ_VERBOSE
            if (verbose())
                AvmLog("reverting to interpreter %d assm->error %d \n", jitcount, assm->error());
            #endif
            PERFM_NVPROF("lir-error",1);
        }

        #ifdef VTUNE
        if (keep) x{
            AvmAssert(!jitPendingRecords.size());  // all should be resolved by now
            int32_t count = jitInfoList.size();
            uint32_t id = 0;
            for(int i=0; i<count; i++) {
                JITCodeInfo* jitInfo = jitInfoList.get(i);
                if (jitInfo->lineNumTable.size()) {
                    jitInfo->sid = id++;
                    VTune_RegisterMethod(core, jitInfo);
                }
                jitInfo->clear();
            }
            jitInfoList.clear();
        }
        #endif /* VTUNE */
    }

#ifdef VTUNE
   JITCodeInfo* CodegenLIR::jitCurrentInfo()
   {
       if (jitInfoList.size()<1)
           jitPushInfo();
       return jitInfoList[jitInfoList.size()-1];
   }

   void CodegenLIR::jitPushInfo()
   {
       JITCodeInfo* inf = new (gc) JITCodeInfo(gc);
       jitInfoList.add(inf);
       inf->method = info;
   }

   LineNumberRecord* CodegenLIR::jitAddRecord(uint32_t pos, uint32_t filename, uint32_t line, bool pending)
   {
       // create a new record in the table; possibly overwriting an existing one.
       // for pending (i.e. reverse code gen) we want to keep the first line entry we, see
       // for forwards generation we'll take the last one then we encounter
       AvmAssert(pending || (filename && line));
       if (pending && jitCurrentInfo()->lineNumTable.containsKey(pos)) return 0;
       LineNumberRecord* rec = new (gc) LineNumberRecord((Stringp)filename, line);
       jitCurrentInfo()->lineNumTable.put(pos,rec);
       if (pending) jitPendingRecords.add(rec);
       return rec;
   }

   void CodegenLIR::jitFilenameUpdate(uint32_t filename)
   {
       AvmAssert(filename);
       int32_t size = jitPendingRecords.size();
       for(int32_t i=size-1; i>=0; i--)    {
           LineNumberRecord* rec = jitPendingRecords.get(i);
           if (!rec->filename) {
               rec->filename = (Stringp)filename;
               if (rec->lineno && rec->filename) jitPendingRecords.removeAt(i); // has both fields set?
           }
       }
   }

   void CodegenLIR::jitLineNumUpdate(uint32_t num)
   {
       AvmAssert(num);
       int32_t size = jitPendingRecords.size();
       for(int32_t i=size-1; i>=0; i--)    {
           LineNumberRecord* rec = jitPendingRecords.get(i);
           if (!rec->lineno)   {
               rec->lineno = num;
               if (rec->lineno && rec->filename) jitPendingRecords.removeAt(i); // has both fields set?
           }
       }
   }

   void CodegenLIR::jitCodePosUpdate(uint32_t pos)
   {
       JITCodeInfo* inf = jitCurrentInfo();
       if (!inf->endAddr) inf->endAddr = pos;
       inf->startAddr = pos;
   }
#endif

    REALLY_INLINE BindingCache::BindingCache(const Multiname* name, BindingCache* next)
        : name(name), next(next)
    {}

    REALLY_INLINE CallCache::CallCache(const Multiname* name, BindingCache* next)
        : BindingCache(name, next), call_handler(callprop_miss)
    {}

    REALLY_INLINE GetCache::GetCache(const Multiname* name, BindingCache* next)
        : BindingCache(name, next), get_handler(getprop_miss)
    {}

    REALLY_INLINE SetCache::SetCache(const Multiname* name, BindingCache* next)
        : BindingCache(name, next), set_handler(setprop_miss)
    {}

    template <class C>
    C* CacheBuilder<C>::findCacheSlot(const Multiname* name)
    {
        for (Seq<C*> *p = caches.get(); p != NULL; p = p->tail)
            if (p->head->name == name)
                return p->head;
        return NULL;
    }

    // The cache structure is expected to be small in the normal case, so use a
    // linear list.  For some programs, notably classical JS programs, it may however
    // be larger, and we may need a more sophisticated structure.
    template <class C>
    C* CacheBuilder<C>::allocateCacheSlot(const Multiname* name)
    {
        C* c = findCacheSlot(name);
        if (!c) {
            _nvprof("binding cache bytes", sizeof(C));
            c = new (codeMgr.allocator) C(name, codeMgr.bindingCaches);
            codeMgr.bindingCaches = c;
            caches.add(c);
        }
        return c;
    }

    LirHelper::LirHelper(AvmCore* core) :
        core(core),
        alloc1(mmfx_new(Allocator())),
        lir_alloc(mmfx_new(Allocator()))
    { }

    LirHelper::~LirHelper()
    {
        cleanup();
    }

    void LirHelper::cleanup()
    {
        mmfx_delete( alloc1 );
        alloc1 = NULL;
        mmfx_delete( lir_alloc );
        lir_alloc = NULL;
    }
}

namespace nanojit
{
    void StackFilter::getTops(LInsp /*br*/, int& /*spTop*/, int& /*rpTop*/) {
        AvmAssert(false);
    }

    #ifdef NJ_VERBOSE
    void LirNameMap::formatGuard(LIns*, char*) {
        AvmAssert(false);
    }
    #endif

    void* Allocator::allocChunk(size_t size) {
        return mmfx_alloc(size);
    }

    void Allocator::freeChunk(void* p) {
        return mmfx_free(p);
    }

    void Allocator::postReset() {
    }

    // static
    void* CodeAlloc::allocCodeChunk(size_t nbytes) {
        size_t npages = (nbytes + GCHeap::kBlockSize - 1) / GCHeap::kBlockSize;
        return GCHeap::GetGCHeap()->AllocCodeMemory(npages);
    }

    // static
    void CodeAlloc::freeCodeChunk(void* addr, size_t) {
        return GCHeap::GetGCHeap()->FreeCodeMemory(addr);
    }
}

#endif // FEATURE_NANOJIT
