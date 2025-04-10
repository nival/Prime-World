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
 * Portions created by the Initial Developer are Copyright (C) 2004-2008
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

#ifndef __avmplus_CodegenLIR__
#define __avmplus_CodegenLIR__

using namespace MMgc;
#include "../nanojit/nanojit.h"

#define NJ_SOFTFLOAT !ARM_VFP

#ifdef DEBUGGER
#define DEBUGGER_ONLY(...) __VA_ARGS__
#else
#define DEBUGGER_ONLY(...)
#endif

namespace avmplus
{
    using namespace nanojit;

   #ifdef VTUNE
   class LineNumberRecord : public MMgc::GCObject
   {
       public:
           LineNumberRecord(Stringp fn, uint32_t ln)
           : filename(fn)
           , lineno(ln)
           { }

       String*  filename;
       uint32_t lineno;
   };

   class JITCodeInfo : public MMgc::GCObject
   {
       public:
           JITCodeInfo(MMgc::GC* gc) : lineNumTable(gc,512) {}

           MethodInfo* method;
           SortedMap<int, LineNumberRecord*, LIST_GCObjects> lineNumTable;       // populated during code generation
           uintptr startAddr;
           uintptr endAddr;
           iJIT_Method_NIDS* vtune;            // vtune record inlined in code (if any)
           uint32_t sid;  // code info id

           LineNumberRecord* add(MMgc::GC* gc, uintptr_t loc, Stringp file, uint32_t line);
           void clear();
   };
   #endif /* VTUNE */

    /**
     * CodegenLabel: information about a LIR label that hasn't been generated yet.
     * Once code at the label is generated, we fill in bb.  Later, we'll patch
     * branch instructions to point to this bb.  We have one of
     * these for each verifier FrameState.
     */
    class CodegenLabel {
    public:
        LIns *bb;
        int has_preds:1;
        int jtbl_forward_target:1;
        CodegenLabel() : bb(0), has_preds(0), jtbl_forward_target(0)
        {}
    };

    class BindingCache;

    /**
     * CodeMgr manages memory for compiled code, including the code itself
     * (in a nanojit::CodeAlloc), and any data with code lifetime
     * (in a nanojit::Allocator), such as debuging info, or inline caches.
     */
    class CodeMgr {
    public:
        CodeAlloc   codeAlloc;  // allocator for code memory
        LogControl  log;        // controller for verbose output
        Allocator   allocator;  // data with same lifetime of this CodeMgr
    #ifdef NJ_VERBOSE
        LabelMap    labels;     // pretty names for addresses in verbose code listing
    #endif
        BindingCache* bindingCaches;    // head of linked list of all BindingCaches allocated by this codeMgr
                                        // (only for flushing... lifetime is still managed by codeAlloc)
        CodeMgr();
        void flushBindingCaches();      // invalidate all binding caches for this codemgr... needed when AbcEnv is unloaded
    };

    /**
     * Each Patch record tracks a label for which we have not yet
     * generated LIR code.  At the end of code generation we'll iterate
     * through a list of these and patch all the unsatisfied forward branches.
     */
    class Patch {
    public:
        LIns *br;               // the branch instruction that needs patching
        CodegenLabel *label;    // information about the target of the branch
        uint32_t index;         // if br is a jtbl, which index in table to patch
        Patch() : br(0), label(0), index(0) {}
        Patch(int) : br(0), label(0), index(0) {}
        Patch(LIns *br, CodegenLabel &l) : br(br), label(&l), index(0) {}
        Patch(LIns *jtbl, CodegenLabel &l, uint32_t index) : br(jtbl), label(&l), index(index) {}
    };

    // Binding Cache Design
    //
    // When we don't know the type of the base object at a point we access a property,
    // we must look up the property at runtime./ We cache the results of this lookup
    // in a BindingCache instance, and install a handler specialized for the object
    // type and binding kind. Each BindingCache consists of:
    //
    //    call_handler      initially, points to callprop_miss(), later points
    //                      to the specialized handler
    //
    //    vtable or tag     VTable* or Atom tag for the base object.  specialized
    //                      handlers quickly check this and "miss" when they dont match
    //                      the object seen at runtime.
    //
    //    slot_offset or    precomputed offset for a slot, for fast loads, or a preloaded
    //    method            MethodEnv* for a method, for fast calls
    //
    //    name              Multiname* for this dynamic access.  Used on a cache miss,
    //                      and also for handlers that access dynamic properties.
    //
    // If jit'd code for a method needs cache entries, they are allocated and
    // saved on MethodInfo::_abc.call_cache. The table is only allocated when jit
    // compilation was successful, so jit'd code must load this pointer at runtime
    // since we don't have the address at compile time.
    //
    // cache instances are in unmanaged memory, so VTable and MethodEnv pointers
    // are effectively weak references: gc-visible pointers must exist elsewhere,
    // and the cache doesn't cause them to be pinned.
    //
    // we allocate one entry for each unique Multiname in each method (only at
    // late-bound reference sites, of course).
    //
    // Limitations:
    //
    //   * we only use a binding cache if the name has no runtime parts.
    //   * only implemented for OP_callproperty OP_callproplex, OP_getproperty,
    //     and OP_setproperty
    //   * only common cases observed in testing are handled, others use a generic
    //     handler that's slightly slower than not using a cache at all.
    //     see callprop_miss() in jit-calls.h for detail on handled cases.
    //
    // Alternatives that led to current design:
    //
    //   * specializing slot accessors on slot type, and storing slot_offset,
    //     avoids calling ScriptObject::getSlotAtom()  (15% faster for gets & calls)
    //   * decl_type:  when an object type doesn't match the cached type, sometimes the
    //     binding doesn't change.  for example calling a method declared on
    //     a base class, on many different subclasses that don't override the
    //     method.  the subsequent misses can be handled faster if we saved the method_id,
    //     and checked that the actual type & cached type are related by inheritance.
    //     This doesn't help for interface methods and the fast case didn't occur often
    //     enough for the extra cache size and code complexity.
    //   * vtable: When a single type (Traits*) is used in different environments we'll
    //     have distinct VTable*'s that point to the same Traits*.  the cache might hit
    //     more often if we stored Traits*.  however, specializing the cache on VTable*
    //     lest us pre-load the MethodEnv* for calls, saving one load.  also, comparing
    //     vtable pointers instead of traits pointers saves one more load. (5% median speedup)
    //   * we pass the base object to CallCache::Handler instead of accessing it indirectly
    //     via args[], to save a load on the fast path.  Worth 2-3%, and enables the same
    //     code to handle OP_callproperty and OP_callproplex.
    //   * we put Multiname* in the cache instead of passing it as a constant parameter,
    //     because the increase in cache size is smaller than the savings in code size,
    //     less parameters is faster, and the multiname is only used on relatively slow paths.
    //   * we allocate cache instances while generating code, which lets us embed
    //     the cache address in code instead of loading from methodinfo.  some stats on ESC:
    //        call cache entries: 489
    //        bytes of call cache entries: 7,824
    //        instructions saved by early allocation (static): 1,445 (loads, movs, adds)
    //        MethodInfo instances: 2436
    //        bytes saved by eliminating 2 cache pointers on MethodInfo: 19,448
    //
    //   (footnote: Times are from the tests in tamarin/test/performance as well as a
    //   selection of Flash/Flex benchmark apps)
    //
    // Alternatives not yet investigated:
    //
    //   * we could put the whole Multiname in the cache, and maybe eliminate
    //     PoolObject::precomputedMultinames[].  Not all multinames are used in late bound
    //     call sites, so this could save some memory.  precomputed multinames have been
    //     measured at over 10% of code size.  Need to study cache size increase vs pool
    //     memory decrease.  Later when we have a code cache, this could be more compelling.
    //   * we could specialize BKIND_METHOD handlers on method return type, enabling us
    //     to inline the native-value boxing logic from MethodEnv::endCoerce()
    //   * we could specialize getter & setter handlers on return/parameter type,
    //     allowing us to inline boxing & unboxing code from coerceEnter AND endCoerce
    //   * the MethodEnv* passed to each handler is only used on slow paths.  Could we
    //     put it somewhere else?  maybe core->currentMethodFrame->env?
    //   * on x86, FASTCALL might be faster, if it doesn't inhibit tail calls in handlers
    //   * other cache instance groupings:
    //       * one per call site instead of per-unique-multiname?
    //       * share them between methods?
    //   * handlers that access primitive dynamic properites have to call toplevel->toPrototype(val),
    //     maybe we could save the result and check its validity with (env->toplevel() == saved_proto->toplevel())
    //   * we could specialize on primitive type too, inlining just the toPrototype() path we need,
    //     instead of using a single set of handlers for all primitives types
    //   * OP_initproperty is rarely late bound in jit code; if this evidence changes
    //     then we should consider an inline cache for it.

    // binding cache common code
    class BindingCache {
    public:
        BindingCache(const Multiname*, BindingCache* next);
        union {
            VTable* vtable;         // for kObjectType receivers
            Atom tag;               // for primitive receivers
        };
        union {
            ptrdiff_t slot_offset;  // for gets of a slot
            MethodEnv* method;      // calls to a method
        };
        const Multiname* const name;      // multiname for this entry, saved when cache created.
        BindingCache* const next;         // singly-linked list
    };

    // cache for late bound calls
    class CallCache: public BindingCache {
    public:
        typedef Atom (*Handler)(CallCache&, Atom base, int argc, Atom* args, MethodEnv*);
        CallCache(const Multiname*, BindingCache* next);
        Handler call_handler;
    };

    // cache for late bound gets
    class GetCache: public BindingCache {
    public:
        typedef Atom (*Handler)(GetCache&, MethodEnv*, Atom);
        GetCache(const Multiname*, BindingCache* next);
        Handler get_handler;
    };

    // bind cache for sets.  This is necessarily larger than for gets because
    // an assignment implies a coercion, and the target type is an additional
    // cached parameter to the coercion
    class SetCache: public BindingCache {
    public:
        typedef void (*Handler)(SetCache&, Atom obj, Atom val, MethodEnv*);
        SetCache(const Multiname*, BindingCache* next);
        Handler set_handler;
        union {
            Traits* slot_type;  // slot or setter type, for implicit coercion
            GC* gc;             // saved GC* for set-handlers that call WBATOM
        };
    };

    /** helper class for allocating binding caches during jit compilation */
    template <class C>
    class CacheBuilder
    {
        SeqBuilder<C*> caches;   // each entry points to an initialized cache
        CodeMgr& codeMgr;                   // this allocator is used for new caches
        C* findCacheSlot(const Multiname*);
    public:
        /** each new entry will be initialized with the given handler.
         *  temp_alloc is the allocator for this cache builder, with short lifetime.
         *  codeMgr.allocator is used to allocate memory for the method's caches, with method lifetime */
        CacheBuilder(Allocator& builder_alloc, CodeMgr& codeMgr)
            : caches(builder_alloc), codeMgr(codeMgr) {}

        /** allocate a new cache slot or reuse an existing one with the same multiname */
        C* allocateCacheSlot(const Multiname* name);
    };

    class CopyPropagation;

    /** helper code to make LIR generation nice and tidy */
    class LirHelper {
    protected:
        LirHelper(AvmCore*);
        ~LirHelper();
        void cleanup();

    protected:
        static BuiltinType bt(Traits *t);
        LIns* nativeToAtom(LIns* value, Traits* valType);
        LIns* atomToNative(BuiltinType, LIns* i);
        LIns* eq0(LIns* i);             // eq(i, imm(0))
        LIns* peq0(LIns* ptr);          // peq(ptr, immq(0))
        LIns* qlo(LIns* q);             // LIR_qlo(q)
        LIns* i2p(LIns* i);             // 32bit: nop, 64bit: i2q(i)
        LIns* u2p(LIns* u);             // 32bit: nop, 64bit: u2q(i)
        LIns* p2i(LIns* ptr);           // 32bit: nop, 64bit: qlo(ptr)
        LIns* InsConst(int32_t c);
        LIns* InsConstPtr(const void *p);
        LIns* InsConstAtom(Atom c);
        LIns* callIns(const CallInfo *, uint32_t argc, ...);
        LIns* peq(LIns* a, Atom b);
        LIns* choose(LIns* c, Atom t, LIns* f);
        LIns* andp(LIns* a, Atom mask);
        LIns* orp(LIns* a, Atom mask);
        LIns* ori(LIns* a, int32_t mask);
        LIns* ret(LIns* a);
        LIns* label();
        LIns* jlt(LIns* a, int32_t b);
        LIns* jgt(LIns* a, int32_t b);
        LIns* jne(LIns* a, int32_t b);
        LIns* sti(LIns* val, LIns* p, int32_t d);
        LIns* stp(LIns* val, LIns* p, int32_t d);
        LIns* stq(LIns* val, LIns* p, int32_t d);
        LIns* ldp(LIns* p, int32_t d);
        LIns* live(LIns*);
        LIns* param(int n, const char *name);
        LIns* lshi(LIns* a, int32_t b);
        LIns* ushp(LIns* a, int32_t b);
        void  liveAlloc(LIns* expr);        // extend lifetime of LIR_alloc, otherwise no-op

    protected: // data
        LirWriter *lirout;
        Fragment *frag;
        AvmCore* core;
        LIns *coreAddr;
        Allocator* alloc1;    // allocator used in first pass, while writing LIR
        Allocator* lir_alloc; // allocator with LIR buffer lifetime
    };

    struct GlobalMemoryInfo
    {
        uint8_t* base;
        uint32_t size;
    };

    /**
     * CodegenLIR is a kitchen sink class containing all state for all passes
     * of the JIT.  It is intended to be instantiated on the stack once for each
     * jit-compiled method, and is a terminator of a CodeWriter pipeline.
     */
    class CodegenLIR : public LirHelper, public CodeWriter {
    public:
        bool overflow;
        const byte *abcStart;
        const byte *abcEnd;

       #ifdef VTUNE
       bool hasDebugInfo;
       List<JITCodeInfo*,LIST_GCObjects> jitInfoList;
       List<LineNumberRecord*,LIST_GCObjects> jitPendingRecords;
       void jitPushInfo();
       JITCodeInfo* jitCurrentInfo();

       LineNumberRecord* jitAddRecord(uintptr_t pos, uint32_t filename, uint32_t line, bool pending=false);
       void jitFilenameUpdate(uint32_t filename);
       void jitLineNumUpdate(uint32_t line);
       void jitCodePosUpdate(uint32_t pos);
       #endif /* VTUNE */

    private:
        LogControl log;
        MethodInfo *info;
        const MethodSignaturep ms;
        PoolObject *pool;
        FrameState *state;
        LIns *vars, *varTraits;
        LIns *env_param, *argc_param, *ap_param;
        LIns *_save_eip, *_ef;
        LIns *methodFrame;
        LIns *csn;
        LIns *undefConst;
        bool interruptable;
        CodegenLabel interrupt_label, npe_label;
        CodegenLabel mop_rangeCheckFailed_label;
        GlobalMemoryInfo* globalMemoryInfo; // allocated with CodeMgr, so lifetime is same as the code's
        intptr_t lastPcSave;
        SeqBuilder<Patch> patches;
        LIns *exBranch;
        LIns *setjmpResult;
        CopyPropagation *copier;
        int framesize;
        int labelCount;
        LookupCacheBuilder finddef_cache_builder;
        CacheBuilder<CallCache> call_cache_builder;
        CacheBuilder<GetCache> get_cache_builder;
        CacheBuilder<SetCache> set_cache_builder;
        verbose_only(VerboseWriter *vbWriter;)

        LIns *InsAlloc(int32_t);
        LIns *atomToNativeRep(int loc, LIns *i);
        LIns *atomToNativeRep(Traits *, LIns *i);
        LIns *ptrToNativeRep(Traits*, LIns*);
        LIns *loadAtomRep(int i);
        LIns *leaIns(int32_t d, LIns *base);
        LIns *localGet(int i);
        LIns *localGetp(int i);
        LIns *localGetq(int i);
        LIns *localCopy(int i); // sniff's type
        LIns *branchIns(LOpcode op, LIns *cond);
        LIns *branchIns(LOpcode op, LIns *cond, int target_off);
        LIns *retIns(LIns *val);
        LIns *loadToplevel();
        LIns* mopAddrToRangeCheckedRealAddrAndDisp(LIns* mopAddr, int32_t const size, int32_t* disp);
        LIns *loadEnvScope();
        LIns *loadEnvVTable();
        LIns *loadEnvAbcEnv();
        LIns *copyMultiname(const Multiname* multiname);
        LIns *initMultiname(const Multiname* multiname, int& csp, bool isDelete =false);
        LIns *storeAtomArgs(int count, int index);
        LIns *storeAtomArgs(LIns *obj, int count, int index);
        LIns *promoteNumberIns(Traits *t, int i);
        LIns *loadVTable(int i);
        LIns *cmpEq(const CallInfo *fid, int lhsi, int rhsi);
        LIns *cmpLt(int lhsi, int rhsi);
        LIns *cmpLe(int lhsi, int rhsi);
        LIns *cmpOptimization(int lhsi, int rhsi, LOpcode icmp, LOpcode ucmp, LOpcode fcmp);
        debug_only( bool isPointer(int i); )
        void emitPrep(FrameState*);
        void emitSampleCheck();
        bool verbose();
        void patchLater(LIns *br, CodegenLabel &);
        void patchLater(LIns *br, int pc_off);
        void patchLater(LIns *jtbl, CodegenLabel &, uint32_t index);
        void patchLater(LIns *jtbl, int pc_off, uint32_t index);
        void setLabelPos(CodegenLabel &l, LIns *target);
        void deadvars();
        void deadvars_analyze(Allocator& alloc, nanojit::BitSet& livein, HashMap<LIns*, nanojit::BitSet*> &labels);
        void deadvars_kill(nanojit::BitSet& livein, HashMap<LIns*, nanojit::BitSet*> &labels);
        void copyParam(int i, int &offset);

        // on successful jit, allocate memory for BindingCache instances, if necessary
        void initBindingCache();

        LIns *loadIns(LOpcode op, int32_t disp, LIns *base);
        LIns *Ins(LOpcode op);
        LIns *Ins(LOpcode op, LIns *a);
        LIns *i2dIns(LIns* v);
        LIns *u2dIns(LIns* v);
        LIns *binaryIns(LOpcode op, LIns *a, LIns *b);

        /** emit a constructor call, and early bind if possible */
        void emitConstruct(FrameState*, int argc, int ctor_index, Traits* ctraits);

        void formatOperand(PrintWriter& buffer, LIns* oprnd);
        bool prologue(FrameState* state);
        void emitCall(FrameState* state, AbcOpcode opcode, intptr_t method_id, int argc, Traits* result);
        void emit(FrameState* state, AbcOpcode opcode, uintptr op1=0, uintptr op2=0, Traits* result=NULL);
        void emitIf(FrameState* state, AbcOpcode opcode, int target_off, int lhs, int rhs);
        void emitSwap(FrameState* state, int i, int j);
        void emitCopy(FrameState* state, int src, int dest);
        void emitGetscope(FrameState* state, int scope, int dest);
        void emitKill(FrameState* state, int i);
        void emitBlockEnd(FrameState* state);
        void emitIntConst(FrameState* state, int index, int32_t c);
        void emitPtrConst(FrameState* state, int index, void* c, Traits* type);
        void emitDoubleConst(FrameState* state, int index, double* pd);
        void emitGetslot(FrameState*, int slot, int ptr_index, Traits *slotType);
        void emitSetslot(FrameState*, AbcOpcode opcode, int slot, int ptr_index);
        void emitGetGlobalScope();
        void localSet(int i, LIns* o, Traits* type);
        LIns* convertToString(int i);
        LIns* coerceToString(int i);
        LIns* coerceToNumber(int i);
        LIns* loadFromSlot(int ptr_index, int slot, Traits* slotType);

    public:
        CodegenLIR(MethodInfo* info);
        ~CodegenLIR();
        void emitMD();

        // CodeWriter methods
        void write(FrameState* state, const byte* pc, AbcOpcode opcode, Traits *type = NULL);
        void writeOp1(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, Traits* type = NULL);
        void writeOp2(FrameState* state, const byte *pc, AbcOpcode opcode, uint32_t opd1, uint32_t opd2, Traits* type = NULL);
        void writeInterfaceCall(FrameState* state, const byte *pc, AbcOpcode opcode, uintptr opd1, uint32_t opd2, Traits* type = NULL);
        void writeNip(FrameState* state, const byte *pc);
        void writeCheckNull(FrameState* state, uint32_t index);
        void writeCoerce(FrameState* state, uint32_t index, Traits *type);
        void writePrologue(FrameState* state, const byte *pc);
        void writeEpilogue(FrameState* state);
        void writeBlockStart(FrameState* state);
        void writeOpcodeVerified(FrameState* state, const byte* pc, AbcOpcode opcode);
        void fixExceptionsAndLabels(FrameState* state, const byte* pc);
        void formatOperand(PrintWriter& buffer, Value& v);
        void cleanup();
    };
}

#include "CodegenLIR-inlines.h"

#endif /* __avmplus_CodegenLIR__ */
