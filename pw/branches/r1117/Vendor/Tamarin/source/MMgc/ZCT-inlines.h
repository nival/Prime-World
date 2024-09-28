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

#ifndef __ZCT_INLINES__
#define __ZCT_INLINES__

/**
 * In-line functions for ZCT.cpp and ZCT.h, factored out to break otherwise
 * forward references to class definitions.
 */

namespace MMgc
{
	REALLY_INLINE void ZCT::Add(RCObject *obj REFCOUNT_PROFILING_ARG(bool initial=false))
	{
		REFCOUNT_PROFILING_ONLY( gc->policy.signalZCTAdd(initial, count); )
		
		// Note:
		//  - If gc->collecting is true then top == limit and we'll
		//    take the slow path; the slow path takes care of extra
		//    checking during sweeping 
		//  - 'limit' is set such that 'topIndex' will not grow beyond
		//    the limit of the ZCT_INDEX field of obj, so no checking
		//    for that is required

		if (top < limit) {
			*top++ = obj;
			obj->setZCTIndexAndMaybeUnpin(topIndex++, uint32_t(reaping));
		}
		else
			AddSlow(obj);
	}

	REALLY_INLINE void ZCT::Remove(RCObject *obj REFCOUNT_PROFILING_ARG(bool final=false))
	{
		REFCOUNT_PROFILING_ONLY( gc->policy.signalZCTRemove(final); )
		
		// Note:
		//  - We just clear out the entry, compaction takes care of NULL entries later.
		//    The volume of removals is expected to be small (see statistics earlier),
		//    so excessive memory use due to no freelist should not be a problem.

		uint32_t index = obj->getZCTIndex();
		GCAssert(Get(index) == obj);
		Put(index, NULL);
		obj->ClearZCTFlag();
	}

	REALLY_INLINE bool ZCT::IsReaping()
	{
		return reaping;
	}

	REALLY_INLINE uint32_t ZCT::BlockNumber(uint32_t idx)
	{
		return idx/CAPACITY(RCObject**);
	}

	REALLY_INLINE uint32_t ZCT::EntryNumber(uint32_t idx)
	{
		return idx & (CAPACITY(RCObject*)-1);
	}

	REALLY_INLINE RCObject** ZCT::PointerTo(uint32_t idx)
	{
		GCAssert((slowState && idx < slowTopIndex) || (!slowState && idx < topIndex));  // Fascistic compiler settings compel us to add the inner parens here
		return blocktable[BlockNumber(idx)] + EntryNumber(idx);
	}

	REALLY_INLINE RCObject* ZCT::Get(uint32_t idx)
	{
		return *PointerTo(idx);
	}
	
	REALLY_INLINE void ZCT::Put(uint32_t idx, RCObject* value)
	{
		*PointerTo(idx) = value;
	}
}

#endif // __ZCT_INLINES__
