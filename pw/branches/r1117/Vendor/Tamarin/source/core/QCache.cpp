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

#include "avmplus.h"

namespace avmplus
{
	using namespace MMgc;

	QCache::QCache(uint32_t _max, MMgc::GC* _gc) : 
		m_gc(_gc),
		m_head(NULL), 
		m_count(0), 
		m_max(0)
	{ 
		MathUtils::RandomFastInit(&m_rand);
		resize(_max);
	}
	
	QCache::~QCache()
	{
		flush();
	}

	void QCache::flush() 
	{
		QCachedItem* gen = first();
		while (gen)
		{
			QCachedItem* n = next(gen);
			gen->next = NULL;
			gen = n;
		}
		m_head = NULL;
		m_count = 0;
	}

	void QCache::resize(uint32_t _max) 
	{
		flush();
		// 0 -> unlimited
		m_max = !_max ? 0xffffffff : _max;
	}

	QCachedItem* QCache::add(QCachedItem* gen) 
	{ 
		AvmAssert(gen && !next(gen));
		
		QCachedItem* evicted = NULL;
		
		// if no space, evict oldest
		if (m_count >= m_max)
		{
			AvmAssert(m_count == m_max);
			uint32_t which = MathUtils::Random(count(), &m_rand);
			QCachedItem* evicted_prev = NULL;
			for (QCachedItem* td = first(); td; td = next(td))
			{
				if (!which--)
				{
					evicted = td;
					break;
				}
				evicted_prev = td;
			}
			if (evicted_prev)
			{
				evicted = evicted_prev->next;
				AvmAssert(evicted != NULL && evicted != gen);
				WB(m_gc, evicted_prev, &evicted_prev->next, evicted->next);
			}
			else
			{
				evicted = m_head;
				AvmAssert(evicted != NULL && evicted != gen);
				WB(m_gc, this, &m_head, evicted->next);
			}
			evicted->next = NULL;	// never need a WB to write NULL
			--m_count;
			#ifdef QCACHE_DEBUG
			validate();
			#endif
		}
		
		// add at head
		WB(m_gc, gen, &gen->next, m_head);
		WB(m_gc, this, &m_head, gen);
		++m_count;
				
		#ifdef QCACHE_DEBUG
		validate();
		#endif
		
		AvmAssert(evicted ? evicted->next == NULL : true);
		return evicted;
	}
	
	#ifdef QCACHE_DEBUG
	void QCache::validate() const
	{
		if (!m_head) 
		{
			AvmAssert(m_count == 0);
			return;
		}
		uint32_t c = 0;
		QCachedItem* prev = NULL;
		for (QCachedItem* td = first(); td; td = next(td))
		{
			AvmAssert(prev ? prev->next == td : true);
			++c;
			prev = td;
			if (c > m_max)
			{
				// oops, probably a cycle, busted code
				AvmAssert(0);
			}
		}
		AvmAssert(c == m_count);
	}
	#endif
}

