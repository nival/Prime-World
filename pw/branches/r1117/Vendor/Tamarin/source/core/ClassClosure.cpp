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

#include "avmplus.h"


namespace avmplus
{
	ClassClosure::ClassClosure(VTable *cvtable)
		: ScriptObject(cvtable, NULL)
	{
		AvmAssert(traits()->getSizeOfInstance() >= sizeof(ClassClosure));

		// prototype will be set by caller
		
		// don't assert here any more: MethodClosure descends 
		//AvmAssert(cvtable->traits->itraits != NULL);
		//AvmAssert(ivtable() != NULL);
	}

	void ClassClosure::createVanillaPrototype()
	{
        prototype = toplevel()->objectClass->construct();
	}

	Atom ClassClosure::get_prototype()
	{
		// Illegal to apply this getter to anything but instances of Class
		// (verifier should ensure this)
		return prototype ? prototype->atom() : undefinedAtom;
	}

	void ClassClosure::set_prototype(Atom value)
	{
		// ISSUE can value be null/undefined?

		if (AvmCore::isNullOrUndefined(value))
		{
			this->prototype = NULL;
		}
		else
		{
			if (!AvmCore::isObject(value))
			{
				toplevel()->throwTypeError(kPrototypeTypeError);
			}

			// allow any prototype object.  if the object has methods or slots, so be it
			this->prototype = AvmCore::atomToScriptObject(value);
		}
	}

	VTable* ClassClosure::ivtable() const
	{
		return vtable->ivtable;
	}

	// Called from construct or generated code to alloc a new instance
	ScriptObject* ClassClosure::newInstance() 
	{
		VTable* ivtable = this->ivtable();
		AvmAssert(ivtable != NULL);

		if (prototype == NULL) // ES3 spec, 13.2.2 (we've already ensured prototype is either an Object or null)
			prototype = AvmCore::atomToScriptObject(toplevel()->objectClass->get_prototype());

		ScriptObject *obj = createInstance(ivtable, prototype);

		return obj;
	}

	// this = argv[0] (ignored)
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom ClassClosure::construct(int argc, Atom* argv)
	{
		VTable* ivtable = this->ivtable();
		AvmAssert(ivtable != NULL);
		AvmAssert(argv != NULL); // need at least one arg spot passed in

		ScriptObject* obj = newInstance();

		Atom a = obj->atom();
		argv[0] = a; // new object is receiver
		ivtable->init->coerceEnter(argc, argv);
		// this is a class. always return new instance.
		return a;
	}

	// this = argv[0]
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom ClassClosure::call(int argc, Atom* argv)
	{
		Toplevel* toplevel = this->toplevel();
		// explicit coercion of a class object.
		if (argc != 1)
		{
			toplevel->throwArgumentError(kCoerceArgumentCountError, toplevel->core()->toErrorString(argc));
		}
		return toplevel->coerce(argv[1], (Traits*)ivtable()->traits);
	}

#ifdef DEBUGGER
	uint64 ClassClosure::size() const
	{
		uint64 size = ScriptObject::size();
		size += vtable->size();
		return size;
	}
#endif

#ifdef AVMPLUS_VERBOSE
	Stringp ClassClosure::format(AvmCore* core) const
	{
		if (traits()->name())
		{
			return traits()->format(core);
		}

		Stringp prefix = core->newConstantStringLatin1("CC{}@");
		return core->concatStrings(prefix, core->formatAtomPtr(atom()));
	}
#endif

	Stringp ClassClosure::implToString() const
	{
		AvmCore* core = this->core();
		Traits* t = this->traits()->itraits;
		Stringp s = core->concatStrings(core->newConstantStringLatin1("[class "), t->name());
		return core->concatStrings(s, core->newConstantStringLatin1("]"));
	}
}
