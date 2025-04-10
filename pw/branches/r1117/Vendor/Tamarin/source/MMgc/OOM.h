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

#ifndef __OOM_H__
#define __OOM_H__

#define MMGC_ENTER_VOID							\
	MMgc::GCHeap::EnterLock();					\
	if(MMgc::GCHeap::ShouldNotEnter())			\
	{											\
		MMgc::GCHeap::EnterRelease();			\
		return;									\
	}											\
	MMgc::EnterFrame _ef;						\
	MMgc::GCHeap::EnterRelease();				\
	_ef.status = VMPI_setjmpNoUnwind(_ef.jmpbuf);            \
	if(_ef.status != 0)							\
		return;


#define MMGC_ENTER_VOID_NO_GUARD				\
	MMgc::GCHeap::EnterLock();					\
	MMgc::EnterFrame _ef;						\
	MMgc::GCHeap::EnterRelease();				\
	_ef.status = VMPI_setjmpNoUnwind(_ef.jmpbuf);            \
	if(_ef.status != 0)							\
		return;


#define MMGC_ENTER_RETURN(_val)					\
	MMgc::GCHeap::EnterLock();					\
	if(MMgc::GCHeap::ShouldNotEnter())			\
	{											\
		MMgc::GCHeap::EnterRelease();			\
		return _val;							\
	}											\
	MMgc::EnterFrame _ef;						\
	MMgc::GCHeap::EnterRelease();				\
	_ef.status = VMPI_setjmpNoUnwind(_ef.jmpbuf);            \
	if(_ef.status != 0)							\
		return _val;

namespace MMgc
{
	class EnterFrame
	{
		friend class GCHeap;
		friend class FixedMalloc;
	public:
		EnterFrame();
		~EnterFrame();
		jmp_buf jmpbuf;
		int status;
		void Destroy() { m_heap = NULL; }
		GC* GetActiveGC() { return m_gc; }
		void SetActiveGC(GC *gc) { m_gc = gc; }
		void SetCollectingGC(GC *gc){ m_collectingGC = gc; }
		GC* GetCollectingGC(){return m_collectingGC;}
	private:
		GCHeap *m_heap;
		GC *m_gc;
		GC *m_collectingGC;

	};
	
	typedef enum _MemoryStatus {
		kMemNormal,
		kMemSoftLimit,
		kMemHardLimit,
		kMemAbort
	} MemoryStatus;

	/**
	 * Mutator oom callback mechanism, subclass and call GCHeap::AddOOMCallback
	 */
	class OOMCallback
	{
	public:
		virtual ~OOMCallback() {}
		virtual void memoryStatusChange(MemoryStatus oldStatus, MemoryStatus newStatus) = 0;
	};
}

#endif /* __OOM_H__ */

