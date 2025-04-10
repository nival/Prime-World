/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: t; tab-width: 4 -*- */
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
 * Portions created by the Initial Developer are Copyright (C) 1993-2007
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


#ifndef __avm__
#define __avm__

#include "VMPI.h"

/*
	Rules of the game:
	
	-- no ifdefs; all calls for Debugger/Debug are all present (though perhaps stubbed)

	-- all types must be opaque, with accessors required (some accessors might
		have an inline implementation in a separate file, but that's an implementation detail)
	
	-- there are conversion routines for lots of the opaque types in avmplus.h
		(e.g. AvmMethod<->MethodEnv) but these are intended as temporary impedance matchers;
		code outside of AVM itself should wean itself away from these

	-- someday, should compile without requiring avmplus.h; design with that in mind

	-- C++ is fine, but strive for simple, normal function calls rather than class hierarchies. in particular,
		avoid the need (por possibility) of the client subclasses any provided classes.
*/


namespace avm {

	// -------- Types --------

	typedef struct Instance_*		Instance;	
	typedef struct Object_*			Object;
	typedef struct CodeContext_*	CodeContext;

	// -------- Object --------

	// If the given Object is a Function (or subclass thereof), return true. Otherwise, return false.
	bool			isFunction(Object o);

	// given an Object that is a Function or MethodClosure, return the CodeContext 
	// that is associated with the function's point of definition. 
	// It will not return a useful result for anything other than a Function (or MethodClosure
	// or other subclass of Function): passing such an object to this call will return NULL
	// (and assert in debug builds.)
	CodeContext		getFunctionCodeContext(Object o);

	// given an Object, return the CodeContext that is associated with the object's
	// point of definition. Note that this API is deprecated and should really only be
	// used for legacy code that relies on this; do NOT use this for new code.
	// It will not return a useful result for Functions, MethodClosures, activation
	// objects, or catch objects: passing such an object to this call will return NULL
	// (and assert in debug builds.)
	CodeContext		getClassCodeContext(Object o);

} // namespace avm

#endif /* __avm__ */ 
