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

#ifndef __BasicList__
#define __BasicList__

namespace MMgc
{	
	template<typename T, int growthIncrement=4>
	class BasicList
	{
	public:
		BasicList() : count(0), 
					  capacity(0), 
					  items(NULL), 
					  iteratorCount(0),
					  holes(false)
		{
		}
		
		~BasicList()
		{
			Destroy();
		}
		
		void Destroy()
		{
			if ( items )
			{
				mmfx_delete_array(items);
				items = NULL;
			}
			count = capacity = iteratorCount = 0;
			holes = false;
		}
		
		void Add(T item)
		{
			if (holes && iteratorCount == 0)
				Compact();
			if (count == capacity)
			{
				capacity += growthIncrement;
				T* newItems = mmfx_new_array_opt(T,  capacity, kZero);
				if (items)
					VMPI_memcpy(newItems, items, count * sizeof(T));
				mmfx_delete_array(items);
				items = newItems;
			}
			items[count] = item;
			count++;
		}

		bool TryAdd(T item)
		{
			if (holes && iteratorCount == 0)
				Compact();
			if (count == capacity)
			{
				uint32_t tryCapacity = capacity + growthIncrement;
				T* newItems = mmfx_new_array_opt(T,  tryCapacity, (MMgc::FixedMallocOpts)(kZero|kCanFail));
				
				if (newItems == NULL)
					return false;

				capacity = tryCapacity;
				if (items)
					VMPI_memcpy(newItems, items, count * sizeof(T));
				mmfx_delete_array(items);
				items = newItems;
			}
			items[count] = item;
			count++;
			return true;
		}
		
		void Remove(T item)
		{
			if (holes && iteratorCount == 0)
				Compact();
			uint32_t i=0;
			while (i < Limit() && items[i] != item)
				i++;
			if (i == Limit()) 
			{
				GCAssertMsg(false, "Bug: should not try to remove something that's not in the list");
				return;
			}
			items[i] = NULL;
			count--;
			if (i != count)
				holes = true;
		}
		
		T Get(uint32_t i) const
		{ 
			GCAssertMsg(i < Limit(), "Index out of bounds");
			return items[i]; 
		}
		
		uint32_t Count() const { return count; }

		// iterator needs this to give complete iteration in the face of in-flight mutation
		uint32_t Limit() const { return holes ? capacity : count; }
		
		void IteratorAttach() { iteratorCount++; }
		void IteratorDettach() 
		{ 
			iteratorCount--; 
			if (holes && iteratorCount == 0)
				Compact();
		}

	protected:
		// no impl
		BasicList(const BasicList& other);
		BasicList& operator=(const BasicList& other);

	private:

		void Compact()
		{
			// i iterates through destintation slots and j iterates through source slots
			// j skips over holes i doesn't
			// at the end i = count
			uint32_t i=0,j=1;
			while (j < capacity) 
			{
				if (items[i] == NULL) 
				{
					if (items[j] != NULL) 
					{
						items[i++] = items[j++];
						items[j-1] = NULL; // NULL it so next item goes in this hole
					} 
					else
					{
						j++;
					}
				} 
				else 
				{
					i++,j++;
				}
			}
			GCAssert(i == count);
			holes = false;
		}

		uint32_t count, capacity;
		T *items;
		uint32_t iteratorCount;
		bool holes;

	};

	template<typename T>
	class BasicListIterator
	{
	public:
		BasicListIterator(BasicList<T>& bl) : index(0), bl(bl) 
		{
			bl.IteratorAttach();
		}
		~BasicListIterator()
		{
			bl.IteratorDettach();
		}
		T next() 
		{ 
			T t = NULL;
			// iterate over holes until end
			while (index < bl.Limit() && t == NULL) 
			{
				t = bl.Get(index++);
			}
			return t;
		}

	private:
		uint32_t index;
		BasicList<T> &bl;
	};
}

#endif /* __GCStack__ */
