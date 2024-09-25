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
//#define DOPROF
//#include "vprof.h"

namespace avmplus
{

#if defined FEATURE_NANOJIT
	
	/*
		Research suggests that linear searches are best for up to 4 entries, binary
		search best for 4...10, and lookup-table best for larger sizes. Lookup tables
		are impractical here, since our iid values aren't consecutive but rather
		arbitrary integers, so we just use linear-and-binary. Furthermore, profiling
		suggested that separate linear search wasn't a measurable gain, so we
		always do a binary search, in the name of simplicity.
	
		http://www.sagecertification.org/events/javavm02/full_papers/zendra/zendra_html/index.html
	*/
	
	// AvmCore::bindingToMethodId will assert inapproppriately
	static inline uint32_t getRawDispID(Binding b) { return  uint32_t(uintptr_t(b))>>3; }
	
	static void sortImtThunkEntries(ImtThunkEntry* map, uint32_t count)
	{
		// intervals suggested by http://www.research.att.com/~njas/sequences/A108870
		// we'll never get anywhere near the upper limits but it's probably cheaper than extending algorithmically
		static const uint32_t k_shellsort_intervals[] = { 1, 4, 9, 20, 46, 103, 233, 525, 1182, 2660, 5985, 13467, 30301, 
											68178, 153401, 345152, 776591, 1747331, 3931496, 8845866, 19903198, 
											44782196, 100759940, 226709866, 510097200, 1147718700 };
		
		// simple ShellSort -- the list rarely gets larger than 100 or so, so this is efficient and compact
		if (count <= 1)
			return;

		ImtThunkEntry* beg = map;
		ImtThunkEntry* end = map + count;	// one past end!

		int32_t interval_idx = 0;
		while (count > k_shellsort_intervals[interval_idx+1])
			++interval_idx;

		while (interval_idx >= 0)
		{
			const int32_t interval = k_shellsort_intervals[interval_idx--];
			for (ImtThunkEntry* i = beg + interval; i < end; i++) 
			{
				ImtThunkEntry temp = *i;
				ImtThunkEntry* j = i;
				ImtThunkEntry* nj = j - interval;
				while ((nj >= beg) && nj->iid > temp.iid)
				{
					AvmAssert(j >= beg && j < end);
					AvmAssert(nj >= beg && nj < end);
					*j = *nj;
					j = nj;
					nj = j - interval;
				}
				AvmAssert(j >= beg && j < end);
				*j = temp;
		   }
		}
	}
	
	class ImtEntry: public MMgc::GCObject
	{
	public:
		inline ImtEntry(ImtEntry* n, MethodInfo* v, uint32_t d) : next(n), iid(v->iid()), disp_id(d) { }
		ImtEntry* const next;
		uintptr_t const iid;
		uintptr_t const disp_id;
	};

	static ImtEntry* buildImtEntries(VTable* vtable, uint32_t slot, uint32_t& count)
	{
		ImtEntry* map = NULL;
		count = 0;
		
		MMgc::GC* gc = vtable->traits->core->GetGC(); 
		Traitsp traits = vtable->traits;
		AvmAssert(!traits->isInterface());
		AvmAssert(traits->core->IsJITEnabled());
		
		// first check to see if we added any interfaces. if not, we can just inherit.
		// do this first, since it's pretty common and allows us to skip lots of hashtable lookups
		// and memory allocations.
		if (!traits->implementsNewInterfaces())
			return NULL;
		
		TraitsBindingsp tb = traits->getTraitsBindings();
		for (InterfaceIterator ifc_iter(traits); ifc_iter.hasNext();)
		{
			Traits* ifc = ifc_iter.next();
			
			TraitsBindingsp ifcd = ifc->getTraitsBindings();
			StTraitsBindingsIterator iter(ifcd);
			while (iter.next())
			{
				const Stringp name = iter.key();
				if (name == NULL)
					continue;

				const Namespacep ns = iter.ns();
				const Binding iBinding = iter.value();

				// taking some liberties here in the name of compact code...
				// the opaque AvmCore accessors aren't flexible enough here,
				// rely on knowledge of current Binding structure
				const uint32_t iDispID = getRawDispID(iBinding);
				const BindingKind ibk = AvmCore::bindingKind(iBinding);
				Binding cBinding = BIND_NONE;
				
				MethodInfo* v0 = ((1<<ibk) & ((1<<BKIND_METHOD)|(1<<BKIND_GET)|(1<<BKIND_GETSET))) ? 
									ifcd->getMethod(iDispID) :
									NULL;

				if (v0 && uint32_t(v0->iid() % VTable::IMT_SIZE) == slot)
				{
					if (cBinding == BIND_NONE)
						cBinding = tb->findBinding(name, ns);
					AvmAssert(cBinding != BIND_NONE);
					map = new (gc) ImtEntry(map, v0, getRawDispID(cBinding));
					++count;
				}

				MethodInfo* v1 = ((1<<ibk) & ((1<<BKIND_SET)|(1<<BKIND_GETSET))) ? 
									ifcd->getMethod(iDispID+1) :
									NULL;
				if (v1 && uint32_t(v1->iid() % VTable::IMT_SIZE) == slot)
				{
					if (cBinding == BIND_NONE)
						cBinding = tb->findBinding(name, ns);
					AvmAssert(cBinding != BIND_NONE);
					map = new (gc) ImtEntry(map, v1, getRawDispID(cBinding)+1);
					++count;
				}
			} // for j
		}
		
		AvmAssert(map != NULL);
		return map;
	}

	/*static*/ GprImtThunkProcRetType VTable::dispatchImt(ImtThunkEnv* ite, int argc, uint32* ap, uintptr_t iid)
	{
		AvmAssert(ite->imtMapCount > 1);
		const ImtThunkEntry* const m = ite->entries();
		uint32_t lo = 0;
		uint32_t hi = ite->imtMapCount;
		while (lo < hi)
		{
			uint32_t const mid = (lo + hi) >> 1;
			if (m[mid].iid < iid)
			{
				lo = mid + 1;
			}
			else
			{
				hi = mid;
			}
		}
		AvmAssert((lo < ite->imtMapCount) && (m[lo].iid == iid));
   		ScriptObject* const receiver = *(ScriptObject**)ap;
		MethodEnv* const env = receiver->vtable->methods[m[lo].disp_id];
		return (*env->implGPR())(env, argc, ap);
	}

	/*static*/ GprImtThunkProcRetType VTable::resolveImt(ImtThunkEnv* ite, int argc, uint32* ap, uintptr_t iid)
	{
		const uint32_t slot = iid % IMT_SIZE;

		VTable* self = ite->vtable;
		
		self->resolveImtSlot(slot);

		ite = self->imt[slot]; // get the fresh, new one

		return (*ite->implImtGPR())(ite, argc, ap, iid);
	}

	// Copy the imt thunk from the base vtable - callers must make sure
	// that the stub can be copied from the base class - i.e. resolveImtSlotFromBase
	// or resolveImtSlotSelf must have already been called successfully on the base vtable.
	void VTable::resolveImtSlotFromBase(uint32_t slot)
	{
		AvmCore* core = traits->core;
		MMgc::GC* gc = core->GetGC();

		ImtThunkEnv* ite = base->imt[slot];
		// copy down imt stub from base class
		AvmAssert(ite != NULL);

		// if base->imt[i] is really an IMT thunk, use it.
		// BUT, it might be a plain MethodEnv* from a single-entry case, in which case
		// we want to use our own MethodEnv at the same disp-id. Alas, we don't have the disp-id 
		// handy at this point, since we didn't build the ImtEntry chain. Rather than build it in 
		// all cases, let's compare vs our parent's method list; linear search, but I'm guessing that's
		// still a net win vs. doing the ImtEntry chain building. (Our base's TB is most likely still
		// in the cache since we used it inside buildImtEntries.)
		TraitsBindingsp tb = base->traits->getTraitsBindings();
		for (uint32_t j = 0; j < tb->methodCount; ++j)
		{
			if (ite == (ImtThunkEnv*)base->methods[j])
			{
				ite = (ImtThunkEnv*)this->methods[j];
				break;
			}
		}
		WB(gc, this, &imt[slot], ite);
	}

	// returns false if we need to copy the imt stub from base,
	// otherwise returns true
	bool VTable::resolveImtSlotSelf(uint32_t slot)
	{
		AvmAssert(this->linked);
		AvmAssert(this->base != NULL); // only Object has null base, and it has no Interfaces
		AvmAssert(!traits->isInterface());
		AvmAssert(traits->core->IsJITEnabled());
		
		ImtThunkEnv* ite;
		uint32_t imtMapCount = 0;

		ImtEntry* imtMap = buildImtEntries(this, slot, imtMapCount);
		if (!imtMap)
		{
			return false;
		}
		else
		{
			AvmCore* core = traits->core;
			MMgc::GC* gc = core->GetGC();

			AvmAssert(imtMapCount > 0);
			if (imtMapCount == 1)
			{
				ite = (ImtThunkEnv*) this->methods[imtMap->disp_id];
				gc->Free(imtMap);
			}
			else
			{
				ite = new (gc, imtMapCount * sizeof(ImtThunkEntry)) ImtThunkEnv(VTable::dispatchImt, imtMapCount);
				//_nvprof("IMT ",MMgc::GC::Size(ite));
				ImtThunkEntry* m = ite->entries();
				ImtEntry* e = imtMap;
				while (e)
				{
					m->iid = e->iid;
					m->disp_id = e->disp_id;
					++m;
					ImtEntry* t = e;
					e = e->next;
					gc->Free(t);
				}
				sortImtThunkEntries(ite->entries(), ite->imtMapCount);
			}
			WB(gc, this, &imt[slot], ite);
		}
		return true;
	}

	void VTable::resolveImtSlot(uint32_t slot)
	{
		AvmCore* core = traits->core;
		MMgc::GC* gc = core->GetGC();

		if( this->resolveImtSlotSelf(slot) )
			return;

		List<VTable*> work_stack(gc);

		work_stack.add(this);

		// Walk up the base VTables until we find one where the slot
		// can be resolved without copying it from its base
		VTable* cur = this->base;
		while(cur->imt[slot]->implImtGPR() == VTable::resolveImt 
			&& !cur->resolveImtSlotSelf(slot) ) 
		{
			work_stack.add(cur);
			cur = cur->base;
		}

		// work backwards through the base types, copying
		// the imt stub down as we go
		uint32 size = work_stack.size();
		for(uint32 i = 0; i < size; ++i)
		{
			cur = work_stack[size-i-1];
			cur->resolveImtSlotFromBase(slot);
		}
	}
	
#endif // FEATURE_NANOJIT
	
	VTable::VTable(Traits* traits, VTable* _base, Toplevel* toplevel) :
		_toplevel(toplevel),
		init(NULL),
		base(_base),
		ivtable(NULL),
		traits(traits),
		linked(false)
	{
		AvmAssert(traits != NULL);
	}

	void VTable::resolveSignatures(ScopeChain* scope)
	{
		AvmAssert(scope != NULL);

		if( this->linked )
			return;
		linked = true;
		if (!traits->isResolved())
		{
			traits->resolveSignatures(toplevel());
			traits->init_declaringScopes(scope->scopeTraits());
		}

#if defined(DEBUG) || defined(_DEBUG)
		// have to use local variables for CodeWarrior
		Traits* traitsBase = traits->base;
		Traits* baseTraits = base ? base->traits : 0;
		// make sure the traits of the base vtable matches the base traits
		AvmAssert((base == NULL && traits->base == NULL) || (base != NULL && traitsBase == baseTraits));
#endif // DEBUG

		AvmCore* core = traits->core;
		MMgc::GC* gc = core->GetGC();

		if (traits->init && !this->init)
		{
			this->init = makeMethodEnv(traits->init, scope);
		}

		// populate method table

		const TraitsBindingsp td = traits->getTraitsBindings();
		const TraitsBindingsp btd = td->base;
		for (uint32_t i = 0, n = td->methodCount; i < n; i++)
		{
			MethodInfo* method = td->getMethod(i);

			if (btd && i < btd->methodCount && method == btd->getMethod(i))
			{
					// inherited method
					//this->methods[i] = base->methods[i];
				WB(gc, this, &methods[i], base->methods[i]);
				continue;
			}
					// new definition
			if (method != NULL)
			{
				//this->methods[i] = new (gc) MethodEnv(method, this);
				WB(gc, this, &methods[i], makeMethodEnv(method, scope));
				continue;
			}
			#ifdef AVMPLUS_VERBOSE
			if (traits->pool->isVerbose(VB_traits))
			{
				// why would the compiler assign sparse disp_id's?
				traits->core->console << "WARNING: empty disp_id " << i << " on " << traits << "\n";
			}
			#endif
		}

			// this is done here b/c this property of the traits isn't set until the
			// Dictionary's ClassClosure is called
		if (base)
			traits->isDictionary = base->traits->isDictionary;

#if defined FEATURE_NANOJIT
		if (traits->core->IsJITEnabled())
		{
			ImtThunkEnv* ite = new (gc) ImtThunkEnv(VTable::resolveImt, this);
			for (uint32_t i=0; i < IMT_SIZE; i++)
			{
				// they all share the same ImtThunkEnv for now 
				// (lazily replaced in resolveImt by an inherited or new one)
				WB(gc, this, &imt[i], ite);
			}
		}
#endif
	}

	MethodEnv* VTable::makeMethodEnv(MethodInfo* func, ScopeChain* scope)
	{
		AvmCore* core = this->core();
		AbcEnv* abcEnv = scope->abcEnv();
		MethodEnv* methodEnv = new (core->GetGC()) MethodEnv(func, scope);
		// register this env in the callstatic method table
		int method_id = func->method_id();
		if (method_id != -1)
		{
			AvmAssert(abcEnv->pool() == func->pool());
			if (abcEnv->getMethod(method_id) == NULL)
			{
				abcEnv->setMethod(method_id, methodEnv);
			}
			#ifdef AVMPLUS_VERBOSE
			else if (func->pool()->isVerbose(VB_traits))
			{
				core->console << "WARNING: tried to re-register global MethodEnv for " << func << "\n";
			}
			#endif
		}
		return methodEnv;
	}

#ifdef DEBUGGER
	uint32 VTable::size() const
	{
		uint32 size = sizeof(VTable);

		if(ivtable != NULL)
			size += ivtable->size();

		const TraitsBindingsp td = traits->getTraitsBindings();
		const uint32_t n = td->methodCount;
		const uint32_t baseMethodCount = base ? td->base->methodCount : 0;
		size += td->methodCount*sizeof(MethodInfo*);

		for (uint32_t i=0; i < n; i++)
		{
			MethodInfo* method = td->getMethod(i);
			
			if (i < baseMethodCount && td->base && method == td->base->getMethod(i))
			{
				continue;
			}
			else if(method != NULL)
			{
				size += method->size();
			}
		}
		return size;
	}
#endif

	VTable* VTable::newParameterizedVTable(Traits* param_traits, Stringp fullname)
	{
		Toplevel* toplevel = this->toplevel();
		AvmCore* core = toplevel->core();
		Namespacep traitsNs = this->traits->ns();
		PoolObject* traitsPool = this->traits->pool;

		Stringp classname = core->internString(fullname->appendLatin1("$"));
		Traits* ctraits = traitsPool->getTraits(Multiname(traitsNs, classname), toplevel);
		Traits* itraits;
		if (!ctraits)
		{
			ctraits = this->traits->newParameterizedCTraits(classname, traitsNs);
			itraits = traitsPool->resolveParameterizedType(toplevel, this->ivtable->traits, param_traits);
			ctraits->itraits = itraits;
		}
		else
		{
			itraits = ctraits->itraits;
		}

		AvmAssert(itraits != NULL);
		itraits->resolveSignatures(toplevel);
		ctraits->resolveSignatures(toplevel);

		VTable* objVecVTable = toplevel->objectVectorClass->vtable;
		AbcEnv* objVecAbcEnv = toplevel->vectorobj_cscope->abcEnv();
		Toplevel* objVecToplevel = objVecVTable->toplevel();
		VTable* objVecIVTable = objVecVTable->ivtable;

		VTable* cvtab = core->newVTable(ctraits, objVecToplevel->class_ivtable, objVecToplevel); 
		ScopeChain* cvtab_cscope = toplevel->vectorobj_cscope->cloneWithNewVTable(core->GetGC(), cvtab, objVecAbcEnv);

		VTable* ivtab = core->newVTable(itraits, objVecIVTable, objVecToplevel);
		ScopeChain* ivtab_iscope = toplevel->vectorobj_iscope->cloneWithNewVTable(core->GetGC(), ivtab, objVecAbcEnv);
		cvtab->ivtable = ivtab;
		ivtab->init = objVecIVTable->init;

		cvtab->resolveSignatures(cvtab_cscope);
		ivtab->resolveSignatures(ivtab_iscope);
		
		return cvtab;
	}
}
