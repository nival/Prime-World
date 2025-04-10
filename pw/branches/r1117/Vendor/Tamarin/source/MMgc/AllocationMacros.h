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
 
#ifndef __ALLOCATIONMACROS__
#define __ALLOCATIONMACROS__

// The allocation macros. mmfx_? ones will have an alternative implementation of mapping to original new/delete implementations
// the others are always on.

namespace MMgc 
{
	enum NewDummyOperand { kUseFixedMalloc };
}

#ifndef MMGC_OVERRIDE_GLOBAL_NEW

// Used for allocating/deallocating memory with MMgc's fixed allocator.
// The memory allocated using these macros will be released when the MMgc aborts due to 
// an unrecoverable out of memory situation.
#define mmfx_new(new_data)					new (MMgc::kUseFixedMalloc) new_data
#define mmfx_new0(new_data)					new (MMgc::kUseFixedMalloc, MMgc::kZero) new_data

#define mmfx_new_array(type, n)				::MMgcConstructTaggedArray((type*)NULL, n, MMgc::kNone)

#define mmfx_new_opt(new_data, opts)		new (MMgc::kUseFixedMalloc, opts) new_data
#define mmfx_new_array_opt(type, n, opts)	::MMgcConstructTaggedArray((type*)NULL, n, opts)

#define mmfx_delete(p)						::MMgcDestructTaggedScalarChecked(p)
#define mmfx_delete_array(p)				::MMgcDestructTaggedArrayChecked(p)

#define mmfx_alloc(_siz)					MMgc::AllocCall(_siz)
#define mmfx_alloc_opt(_siz, opts)          MMgc::AllocCall(_siz, opts)
#define mmfx_free(_ptr)						MMgc::DeleteCall(_ptr)

#else

#define mmfx_new(new_data)					new new_data
#define mmfx_new0(new_data)					new (MMgc::kZero) new_data

#define mmfx_new_array(type, n)				new type[n]

#define mmfx_new_opt(new_data, opts)		new (opts) new_data
#define mmfx_new_array_opt(type, n, opts)	new (opts) type[n]

#define mmfx_delete(p)						delete p
#define mmfx_delete_array(p)				delete[] p

#define mmfx_alloc(_siz)                    new char[_siz]
#define mmfx_alloc_opt(_siz, opts)          new (opts) char[_siz]
#define mmfx_free(_ptr)                     delete [] (char*)_ptr

#endif // MMGC_OVERRIDE_GLOBAL_NEW

// Used to allocate memory from the system default operator new. The lifetime of these
// allocations may exceed the lifetime of MMgc.
#define system_new(new_data)				new new_data
#define system_new_array(type, n)			new type[n]
#define system_delete(p)					delete p
#define system_delete_array(p)				delete[] p

#endif // __ALLOCATIONMACROS__
