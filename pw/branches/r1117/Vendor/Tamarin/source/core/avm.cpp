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

#include "avmplus.h"

namespace avm {

	// you probably don't want to open this namespace.
	// using namespace avmplus;

	// -------- AvmObject --------

	bool isFunction(Object o)
	{
		avmplus::ScriptObject* so = avmplus::avmFromObject(o);
		return so && so->core()->isFunction(so->atom());
	}

	CodeContext getFunctionCodeContext(Object o)
	{
		if (!isFunction(o))
		{
			AvmAssert(!"Only Function is legal here.");
			return NULL;
		}
		avmplus::ScriptObject* so = avmplus::avmFromObject(o);
	//	avmplus::CodeContext* cc = ((avmplus::FunctionObject*)so)->getFunctionCodeContext();
	// getFunctionCodeContext() has been temporarily relocated to ScriptObject, as AIR defines
	// some classes that are subclasses of Function (in AS3) but not of FunctionObject (in C++)...
		avmplus::CodeContext* cc = ((avmplus::ScriptObject*)so)->getFunctionCodeContext();
		return avmToCodeContext(cc);
	}

	CodeContext getClassCodeContext(Object o)
	{
		if (!o)
			return NULL;
		avmplus::ScriptObject* so = avmplus::avmFromObject(o);
		if (so->core()->isFunction(so->atom()))
		{
			AvmAssert(!"Function or MC is not legal here.");
			return NULL;
		}
		avmplus::TraitsPosType t = so->traits()->posType();
		if (t == avmplus::TRAITSTYPE_CATCH || t == avmplus::TRAITSTYPE_ACTIVATION)
		{
			AvmAssert(!"Activation and Catch objects are not legal here.");
			return NULL;
		}
		avmplus::MethodEnv* init = so->vtable->init;
		if (!init)
		{
			AvmAssert(!"init method is null, should not be possible.");
			return NULL;
		}
		avmplus::CodeContext* cc = init->scope()->abcEnv()->codeContext();
		return avmToCodeContext(cc);
	}

} // namespace avm

