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
#include "BuiltinNatives.h"

namespace avmplus
{
	ObjectClass::ObjectClass(VTable* cvtable)
		: ClassClosure(cvtable)
	{
		toplevel()->objectClass = this;

		// patch Object's instance vtable scope, since we created it earlier for
		// bootstrapping
		//ivtable()->scope = cvtable->scope;

		AvmAssert(traits()->getSizeOfInstance() == sizeof(ObjectClass));
        // it is correct call construct() when this.prototype == null
        prototype = construct();
	}

	void ObjectClass::initPrototype()
	{
		// patch global.__proto__ = Object.prototype
		Toplevel* toplevel = this->toplevel();
		toplevel->global()->setDelegate(prototype);				// global.__proto__ = Object.prototype
		this->setDelegate(toplevel->classClass->prototype);		// Object.__proto__ = Class.prototype
	}

	ScriptObject* ObjectClass::construct()
	{
		return (ScriptObject*) core()->newObject(ivtable(), prototype);
	}

	// this = argv[0]
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom ObjectClass::call(int argc, Atom* argv)
	{
		// see E-262 15.2.1
		if (argc == 0 || AvmCore::isNullOrUndefined(argv[1]))
			return construct(argc, argv);
		else
			return argv[1];
	}

	// this = argv[0] (ignored)
	// arg1 = argv[1]
	// argN = argv[argc]
    Atom ObjectClass::construct(int argc, Atom* argv)
    {
		switch (argc)
		{
		default:
			// TODO throw exception if argc > 1 (see E4 semantics)
		case 1: {
			Atom o = argv[1];
			if (!AvmCore::isNullOrUndefined(o))
				return o;
			// else fall through
		}
		case 0:
			return construct()->atom();
		}
    }

	/**
		15.2.4.5 Object.prototype.hasOwnProperty (V)
		When the hasOwnProperty method is called with argument V, the following steps are taken:
		1. Let O be this object.
		2. Call ToString(V).
		3. If O doesn't have a property with the name given by Result(2), return false.
		4. Return true.
		NOTE Unlike [[HasProperty]] (section 8.6.2.4), this method does not consider objects in the prototype chain.
     */
	bool ObjectClass::_hasOwnProperty(Atom thisAtom, Stringp name)
	{
		AvmCore* core = this->core();
		name = name ? core->internString(name) : (Stringp)core->knull;

		Traitsp t = NULL;
		switch (atomKind(thisAtom))
		{
			case kObjectType:
			{
				// ISSUE should this look in traits and dynamic vars, or just dynamic vars.
				ScriptObject* obj = AvmCore::atomToScriptObject(thisAtom);
				if (obj->hasStringProperty(name))
					return true;
				t = obj->traits();
				break;
			}
			case kNamespaceType:
			case kStringType:
			case kBooleanType:
			case kDoubleType:
			case kIntptrType:
				t = toplevel()->toTraits(thisAtom);
				break;
			default:
				return false;
		}
		// NOTE use caller's public namespace
		return t->getTraitsBindings()->findBinding(name, core->findPublicNamespace()) != BIND_NONE;
	}

	bool ObjectClass::_propertyIsEnumerable(Atom thisAtom, Stringp name)
	{
		AvmCore* core = this->core();
		name = name ? core->internString(name) : (Stringp)core->knull;

		if (atomKind(thisAtom) == kObjectType)
		{
			ScriptObject* obj = AvmCore::atomToScriptObject(thisAtom);
			return obj->getStringPropertyIsEnumerable(name);
		}
		else if (atomKind(thisAtom) == kNamespaceType)
		{
			// Special case:
			// E4X 13.2.5.1, 13.2.5.2 specifies that prefix and uri
			// are not DontEnum.
			return name == core->kuri || name == core->kprefix;
		}
		else
		{
			return false;
		}
	}

	void ObjectClass::_setPropertyIsEnumerable(Atom thisAtom, Stringp name, bool enumerable)
	{
		AvmCore* core = this->core();
		name = name ? core->internString(name) : (Stringp)core->knull;

		if (atomKind(thisAtom) == kObjectType)
		{
			ScriptObject* obj = AvmCore::atomToScriptObject(thisAtom);
			obj->setStringPropertyIsEnumerable(name, enumerable);
		}
		else
		{
			// cannot create properties on a sealed object.
			// NOTE just use the unmarked version
			Multiname multiname(core->getAnyPublicNamespace(), name);
			// NOTE use default public
			toplevel()->throwReferenceError(kWriteSealedError, &multiname, traits());
		}
	}		
	
	/**
		15.2.4.6 Object.prototype.isPrototypeOf (V)
		When the isPrototypeOf method is called with argument V, the following steps are taken:
		1. Let O be this object.
		2. If V is not an object, return false.
		3. Let V be the value of the [[Prototype]] property of V.
		4. if V is null, return false
		5. If O and V refer to the same object or if they refer to objects joined to each other (section 13.1.2), return true.
		6. Go to step 3.     
	*/
	bool ObjectClass::_isPrototypeOf(Atom thisAtom, Atom V)
	{
		// ECMA-262 Section 15.2.4.6
		if (AvmCore::isNullOrUndefined(V))
			return false;

		ScriptObject* o = toplevel()->toPrototype(V);
		for (; o != NULL; o = o->getDelegate())
		{
			if (o->atom() == thisAtom)
				return true;
		}
		return false;
	}

	/**
     * Object.prototype.toString()
     */
	Stringp ObjectClass::_toString(Atom thisAtom)
	{		
		AvmCore* core = this->core();

		if (AvmCore::isObject(thisAtom))
		{
			return AvmCore::atomToScriptObject(thisAtom)->implToString();
		}
		else
		{
			Traits*		t = toplevel()->toTraits(thisAtom);
			Stringp s = core->concatStrings(core->newConstantStringLatin1("[object "), t->name());
			return core->concatStrings(s, core->newConstantStringLatin1("]"));
		}
	}
}
