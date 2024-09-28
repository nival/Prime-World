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
 * Portions created by the Initial Developer are Copyright (C) 2008
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

#ifndef __avmplus_QCache__
#define __avmplus_QCache__

#ifdef _DEBUG
	#define QCACHE_DEBUG
#endif

#include "MathUtils.h"

/*
	QCache is a simple framework for maintaining a cache of items, with a random
	eviction policy. The cache is limited by count of items, which can be set arbitrarily
	(or allowed to grow to unlimited size).
	
	The recommended use case is to split a a data structure split into a small, frequently-used
	chunk (owner), and a larger, less-frequently-used chunk (cacheditem) that can be reconstituted
	from compressed data; e.g., the slot-binding tables for Traits, which are kept in memory in 
	a highly compressed	form (the ABC bytecode), and expanded into convenient hashtable format
	as a cacheditem.
	
	Important note: For proper use, the only "strong" ref to the cacheditem should be via
	the QCache itself; the owner should keep a reference to the cacheditem via a GCWeakRef, which
	will allow the cacheditem to be collected when it is evicted from the cache. (Naturally, the owner
	must check the GCWeakRef for null before using it.)
	
	Cached items are stored in a singly-linked list; it's assumed that the cost
	of building a new item to add to the cache is likely to dwarf the cost of walking
	the list to evict an item (this is currently the case for all existing use cases).
*/

namespace avmplus
{
	class QCachedItem : public MMgc::GCObject
	{
		friend class QCache;
	public:
		inline QCachedItem() : next(NULL) { }
	private:
		QCachedItem*	next;	// written with explicit WB
	};

	class QCache : public MMgc::GCFinalizedObject
	{
	public:

		QCache(uint32_t _max, MMgc::GC* _gc);
		~QCache();
		
		inline uint32_t count() const { return m_count; }
		inline uint32_t maxcount() const { return m_max; }	// sadly, "max" is a macro in some environments
		inline QCachedItem* first() const { return m_head; }
		inline QCachedItem* next(QCachedItem* gen) const { return gen->next; }

		void flush();
		void resize(uint32_t _max);

		QCachedItem* add(QCachedItem* gen);
		
	private:
		#ifdef QCACHE_DEBUG
		void validate() const;
		#endif
		
	private:
		MMgc::GC*				m_gc;
		QCachedItem*			m_head;
		uint32_t				m_count;
		uint32_t				m_max;
		TRandomFast				m_rand;
	};
}

#endif /* __avmplus_QCache__ */
