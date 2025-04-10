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


namespace avmplus
{

	/**
	 * type descriptor for a captured scope chain
	 *
	 * Note: ScopeTypeChain is now immutable; once created it cannot be modified
	 */
	class ScopeTypeChain : public MMgc::GCObject
	{
	private:
		ScopeTypeChain(int32_t _size, int32_t _fullsize, Traits* traits);
		static const ScopeTypeChain* create(MMgc::GC* gc, Traits* traits, const ScopeTypeChain* outer, const Value* values, int32_t nValues, Traits* append, Traits* extra);

	public:

		static const ScopeTypeChain* create(MMgc::GC* gc, Traits* traits, const ScopeTypeChain* outer, const FrameState* state, Traits* append, Traits* extra);
#ifdef VMCFG_AOT
		static const ScopeTypeChain* create(MMgc::GC* gc, Traits* traits, const ScopeTypeChain* outer, Traits* const* stateTraits, uint32_t nStateTraits, uint32_t nStateWithTraits, Traits* append, Traits* extra);
#endif
		static const ScopeTypeChain* createEmpty(MMgc::GC* gc, Traits* traits);

		const ScopeTypeChain* cloneWithNewTraits(MMgc::GC* gc, Traits* traits) const;
		Traits* traits() const;
		Traits* getScopeTraitsAt(uint32_t i) const;
		bool getScopeIsWithAt(uint32_t i) const;

		#if VMCFG_METHOD_NAMES
		Stringp format(AvmCore* core) const;
		#endif

	private:
		void setScopeAt(uint32_t i, Traits* t, bool w);

		// Traits are MMgc-allocated, thus always 8-byte-aligned, so the low 3 bits are available for us to use
		static const uintptr_t ISWITH = 0x01;

	// ------------------------ DATA SECTION BEGIN
	public:
		const int32_t		size;
		const int32_t		fullsize;
	private:
		Traits* const		_traits;
		uintptr_t			_scopes[1];	// actual length = fullsize;
	// ------------------------ DATA SECTION END
    };

	/**
	* a captured scope chain
	*/
	class ScopeChain : public MMgc::GCObject
	{
		ScopeChain(VTable* vtable, AbcEnv* abcEnv, const ScopeTypeChain* scopeTraits, Namespacep dxns);

		#if defined FEATURE_NANOJIT
		friend class CodegenLIR;
		#endif

	public:

		/*
			dxns is modelled as a variable on an activation object.  The activation
			object will be in several scope chains, so we can't store dxns in the SC.
			When it changes, it's new valuable is visible in all closures in scope.
		*/
		
		static ScopeChain* create(MMgc::GC* gc, VTable* vtable, AbcEnv* abcEnv, const ScopeTypeChain* scopeTraits, const ScopeChain* outer, Namespacep dxns);

		ScopeChain* cloneWithNewVTable(MMgc::GC* gc, VTable* vtable, AbcEnv* abcEnv, const ScopeTypeChain* scopeTraits = NULL);

		VTable* vtable() const;
		AbcEnv* abcEnv() const;
		const ScopeTypeChain* scopeTraits() const;
		int32_t getSize() const;
		Atom getScope(int32_t i) const;
		void setScope(MMgc::GC* gc, int32_t i, Atom value);
		Namespacep getDefaultNamespace() const;

		#if VMCFG_METHOD_NAMES
		Stringp format(AvmCore* core) const;
		#endif

	// ------------------------ DATA SECTION BEGIN
	private:
		VTable* const					_vtable;
		AbcEnv* const					_abcEnv;
		const ScopeTypeChain* const		_scopeTraits;
		DRCWB(Namespacep) const			_defaultXmlNamespace;
		Atom							_scopes[1];			// actual length == size
	// ------------------------ DATA SECTION END
    };
	
}
