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

#ifndef __avmplus_ArrayClass__
#define __avmplus_ArrayClass__


namespace avmplus
{
	/**
	 * class Array
	 */
    class ArrayClass : public ClassClosure
    {
	public:
		ArrayClass(VTable* cvtable);
		
		// this = argv[0]
		// arg1 = argv[1]
		// argN = argv[argc]
		Atom call(int argc, Atom* argv)
		{
			return construct(argc, argv);
		}

		// create a new array, even when argc=1
		ArrayObject* newarray(Atom* argv, int argc);

		ArrayObject* newArray(uint32 capacity=0);

		// override ScriptObject::createInstance
		ArrayObject* createInstance(VTable *ivtable, ScriptObject* prototype);

		// AS3 glue code methods (not inlined, just declared here for convenience)
		ArrayObject* _concat(Atom thisAtom, ArrayObject* args) { return ArrayClass::generic_concat(toplevel(), thisAtom, args); }
		Atom _pop(Atom thisAtom) { return ArrayClass::generic_pop(toplevel(), thisAtom); }
		Atom _reverse(Atom thisAtom) { return ArrayClass::generic_reverse(toplevel(), thisAtom); }
		Atom _shift(Atom thisAtom) { return ArrayClass::generic_shift(toplevel(), thisAtom); }
		ArrayObject* _slice(Atom thisAtom, double A, double B) { return ArrayClass::generic_slice(toplevel(), thisAtom, A, B); }
		Atom _sort(Atom thisAtom, ArrayObject *args) { return ArrayClass::generic_sort(toplevel(), thisAtom, args); }
		Atom _sortOn(Atom thisAtom, Atom namesAtom, Atom optionsAtom) { return ArrayClass::generic_sortOn(toplevel(), thisAtom, namesAtom, optionsAtom); }
		ArrayObject* _splice(Atom thisAtom, ArrayObject* args) { return ArrayClass::generic_splice(toplevel(), thisAtom, args); }
		int _indexOf(Atom thisAtom, Atom searchElement, int startIndex) { return ArrayClass::generic_indexOf(toplevel(), thisAtom, searchElement, startIndex); }
		int _lastIndexOf(Atom thisAtom, Atom searchElement, int startIndex) { return ArrayClass::generic_lastIndexOf(toplevel(), thisAtom, searchElement, startIndex); }
		bool _every(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_every(toplevel(), thisAtom, callback, thisObject); }
		ArrayObject* _filter(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_filter(toplevel(), thisAtom, callback, thisObject); }
		void _forEach(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_forEach(toplevel(), thisAtom, callback, thisObject); }
		bool _some(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_some(toplevel(), thisAtom, callback, thisObject); }
		ArrayObject* _map(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_map(toplevel(), thisAtom, callback, thisObject); }
		uint32 _unshift(Atom thisAtom, ArrayObject* args) { return ArrayClass::generic_unshift(toplevel(), thisAtom, args); }

		// inline wrappers for legacy code.
		inline ArrayObject* concat(Atom thisAtom, ArrayObject* args) { return ArrayClass::generic_concat(toplevel(), thisAtom, args); }
		inline Atom pop(Atom thisAtom) { return ArrayClass::generic_pop(toplevel(), thisAtom); }
		inline Atom reverse(Atom thisAtom) { return ArrayClass::generic_reverse(toplevel(), thisAtom); }
		inline Atom shift(Atom thisAtom) { return ArrayClass::generic_shift(toplevel(), thisAtom); }
		inline ArrayObject* slice(Atom thisAtom, double A, double B) { return ArrayClass::generic_slice(toplevel(), thisAtom, A, B); }
		inline Atom sort(Atom thisAtom, ArrayObject *args) { return ArrayClass::generic_sort(toplevel(), thisAtom, args); }
		inline Atom sortOn(Atom thisAtom, Atom namesAtom, Atom optionsAtom) { return ArrayClass::generic_sortOn(toplevel(), thisAtom, namesAtom, optionsAtom); }
		inline ArrayObject* splice(Atom thisAtom, ArrayObject* args) { return ArrayClass::generic_splice(toplevel(), thisAtom, args); }
		inline int indexOf(Atom thisAtom, Atom searchElement, int startIndex) { return ArrayClass::generic_indexOf(toplevel(), thisAtom, searchElement, startIndex); }
		inline int lastIndexOf(Atom thisAtom, Atom searchElement, int startIndex) { return ArrayClass::generic_lastIndexOf(toplevel(), thisAtom, searchElement, startIndex); }
		inline bool every(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_every(toplevel(), thisAtom, callback, thisObject); }
		inline ArrayObject* filter(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_filter(toplevel(), thisAtom, callback, thisObject); }
		inline void forEach(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_forEach(toplevel(), thisAtom, callback, thisObject); }
		inline bool some(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_some(toplevel(), thisAtom, callback, thisObject); }
		inline ArrayObject* map(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_map(toplevel(), thisAtom, callback, thisObject); }

		static ArrayObject* generic_concat(Toplevel* toplevel, Atom thisAtom, ArrayObject* args);
		static Atom generic_pop(Toplevel* toplevel, Atom thisAtom);
		static Atom generic_reverse(Toplevel* toplevel, Atom thisAtom);
		static Atom generic_shift(Toplevel* toplevel, Atom thisAtom);
		static ArrayObject* generic_slice(Toplevel* toplevel, Atom thisAtom, double A, double B);
		static Atom generic_sort(Toplevel* toplevel, Atom thisAtom, ArrayObject *args);
		static Atom generic_sortOn(Toplevel* toplevel, Atom thisAtom, Atom namesAtom, Atom optionsAtom);
		static ArrayObject* generic_splice(Toplevel* toplevel, Atom thisAtom, ArrayObject* args);
		static int generic_indexOf(Toplevel* toplevel, Atom thisAtom, Atom searchElement, int startIndex);
		static int generic_lastIndexOf(Toplevel* toplevel, Atom thisAtom, Atom searchElement, int startIndex);
		static bool generic_every(Toplevel* toplevel, Atom thisAtom, ScriptObject* callback, Atom thisObject); 
		static ArrayObject* generic_filter(Toplevel* toplevel, Atom thisAtom, ScriptObject* callback, Atom thisObject); 
		static void generic_forEach(Toplevel* toplevel, Atom thisAtom, ScriptObject* callback, Atom thisObject); 
		static bool generic_some(Toplevel* toplevel, Atom thisAtom, ScriptObject* callback, Atom thisObject); 
		static ArrayObject* generic_map(Toplevel* toplevel, Atom thisAtom, ScriptObject* callback, Atom thisObject); 
		static uint32 generic_unshift(Toplevel* toplevel, Atom thisAtom, ArrayObject* args);
		
		static uint32_t getLengthHelper(Toplevel* toplevel, ScriptObject* d);

	private:
		static void setLengthHelper(Toplevel* toplevel, ScriptObject *d, uint32 newLen);

		static ArrayObject* isArray(Toplevel* toplevel, Atom instance);

		const DRCWB(Stringp) kComma;
        
		DECLARE_SLOTS_ArrayClass;
	};
}

#endif /* __avmplus_ArrayClass__ */
