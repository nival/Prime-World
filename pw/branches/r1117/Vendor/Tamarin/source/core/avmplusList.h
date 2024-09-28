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

#ifndef __avmplus_List__
#define __avmplus_List__

#include "TypeTraits.h"

namespace avmplus
{
	/**
	 * The List<T> template implements a simple List, which can
	 * be templated to support different types.
	 * 
	 * Elements can be added to the end, modified in the middle, 
	 * but no holes are allowed.  That is for set(n, v) to work
	 * size() > n
	 *
	 * Note that [] operators are provided and you can violate the
	 * set properties using these operators, if you want a real
	 * list dont use the [] operators, if you want a general purpose
	 * array use the [] operators.  
	 */

	enum ListElementType {
		LIST_NonGCObjects = 0,
		LIST_GCObjects = 1,
		LIST_RCObjects = 2
	};

	template <bool isGCObject, bool isGCFinalizedObject, bool isRCObject>
	struct _ListElementType
	{
	};

	/*
		Only valid combinations of the above variables are listed below.
	*/
	template <>
	struct _ListElementType<true, false, false>
	{
		static const ListElementType kElementType = LIST_GCObjects;
	};

	template <>
	struct _ListElementType<false, true, false>
	{
		static const ListElementType kElementType = LIST_GCObjects;
	};

	template <>
	struct _ListElementType<false, true, true>
	{
		static const ListElementType kElementType = LIST_RCObjects;
	};

	template <>
	struct _ListElementType<false, false, false>
	{
		static const ListElementType kElementType = LIST_NonGCObjects;
	};

	template <class T>
	struct _ListElementTypeHelper
	{
		typedef typename MMgc::remove_pointer<T>::type base_type;

		typedef MMgc::is_base_of<MMgc::GCObject, base_type> _isGCObject;
		typedef MMgc::is_base_of<MMgc::GCFinalizedObject, base_type> _isGCFinalizedObject;
		typedef MMgc::is_base_of<MMgc::RCObject, base_type> _isRCObject;

		static const ListElementType kElementType = _ListElementType<_isGCObject::value, _isGCFinalizedObject::value, _isRCObject::value>::kElementType;
	};

	class ListAllocPolicy_GC
    {
    public:
		typedef MMgc::GCObject Base;
    };

	class ListAllocPolicy_InsideRCObject
	{
    public:
        class Base {};
    };
	
	template<class T, ListElementType kElementType, class ListAllocPolicy>
	class ListBase;
	
	template<class T, class ListAllocPolicy>
	class ListBase<T, LIST_NonGCObjects, ListAllocPolicy> : public ListAllocPolicy::Base
	{
	protected:
		T *data;
		uint32 len;
		uint32 max;
		MMgc::GC* gc;
		
		void wb(uint32 index, T value)
		{
			AvmAssert(index < max);
			AvmAssert(data != NULL);
			data[index] = value;
		}
	};
	
	template<class T, class ListAllocPolicy>
	class ListBase<T, LIST_GCObjects, ListAllocPolicy> : public ListAllocPolicy::Base
	{
	protected:
		T *data;
		uint32 len;
		uint32 max;
		MMgc::GC* gc;

		void wb(uint32 index, T value)
		{
			AvmAssert(index < max);
			AvmAssert(data != NULL);
			WB(gc, data, &data[index], value);
		}
	};

	template<class T, class ListAllocPolicy>
	class ListBase<T, LIST_RCObjects, ListAllocPolicy> : public ListAllocPolicy::Base
	{
	protected:
		T *data;
		uint32 len;
		uint32 max;
		MMgc::GC* gc;

		void wb(uint32 index, T value)
		{
			AvmAssert(index < max);
			AvmAssert(data != NULL);
			WBRC(gc, data, &data[index], value);
		}
	};

	template <class T, ListElementType kElementType = _ListElementTypeHelper<T>::kElementType, class ListAllocPolicy = ListAllocPolicy_GC>
	class List : public ListBase<T, kElementType, ListAllocPolicy>
	{
		using ListBase<T, kElementType, ListAllocPolicy>::data;
		using ListBase<T, kElementType, ListAllocPolicy>::len;
		using ListBase<T, kElementType, ListAllocPolicy>::max;
		using ListBase<T, kElementType, ListAllocPolicy>::gc;
		using ListBase<T, kElementType, ListAllocPolicy>::wb;

	public:
		enum { kInitialCapacity = 128 };		

		List(int _capacity = kInitialCapacity)
		{
			init(0, _capacity);
		}
		List(MMgc::GC* _gc, uint32 _capacity = kInitialCapacity)
		{
			init(_gc, _capacity);
		}
		void init(MMgc::GC* _gc, uint32 _capacity)
		{
			len = 0;
			max = 0;
			data = NULL;
			this->gc = _gc;
			AvmAssert (_gc || kElementType == LIST_NonGCObjects);
			ensureCapacity(_capacity);
		}
		~List()
		{
			if(gc) {
				if(kElementType == LIST_RCObjects) {
					for (unsigned int i=0; i<len; i++) {
						set(i, 0);
					}
				}	
				gc->Free(data);
			} else
				mmfx_delete_array(data);
			// List can be a stack object, or it can be inside an RCObject, so clearing it
			// can help the gc or indeed be required.
			data = NULL;
            len = 0;
            max = 0;
			gc = 0;
		}
		uint32 add(T value)
		{
			if (len >= max) {
				grow();
			}
			// messy WB, need to ignore write in cases where data isn't gc memory
			wb(len++, value);
			return len-1;
		}
		bool isEmpty() const
		{
			return len == 0;
		}
		uint32 size() const
		{
			return len;
		}
		uint32 capacity() const
		{
			return max;
		}
		T get(uint32 index) const
		{
			AvmAssert(index < len);
			return data[index];
		}
		T last() const
		{
			AvmAssert(len > 0);
			return data[len-1];
		}
		void set(uint32 index, T value)
		{
			wb(index, value);
			len = (index+1 > len) ? index+1 : len;
			AvmAssert(index < max);
		}
		void insert(int index, T value)
		{
			if ((uint32)index >= len)
			{
				// Someone is trying to insert at the end
				add(value);
				return;
			}

			if (len >= max) {
				grow();
			}

			//move items up
			arraycopy(data, index, data, index + 1, len - index);

			// The item formerly at "index" is still in the array (at index+1),
			//   but arraycopy didn't increment its refcount.
			// Null out its former slot, so that set() doesn't decrement its refcount.
			if(kElementType == LIST_RCObjects)
				data[ index ] = 0;

			set(index, value);
			len++;
		}
		
		void add(const List<T, kElementType>& l)
		{
			ensureCapacity(len+l.size());
			// FIXME: make RCObject version
			AvmAssert(kElementType != LIST_RCObjects);
			arraycopy(l.getData(), 0, data, len, l.size());
			len += l.size();
		}

		void clear()
		{
			if(kElementType == LIST_RCObjects) {
				for (unsigned int i=0; i<len; i++) {
					set(i, 0);
				}
			} else {
				if ( len ) {
					VMPI_memset(data, 0, len*sizeof(T));
				}
			}
			len = 0;
		}

		int indexOf(T value) const
		{
			for(uint32 i=0; i<len; i++)
				if (data[i] == value)
					return i;
			return -1;
		}
		int lastIndexOf(T value) const
		{
			for(int32 i=len-1; i>=0; i--)
				if (data[i] == value)
					return i;
			return -1;
		}

		T removeAt(uint32 i)
		{
			T old = (T)0;
			old = data[i];
			if(kElementType == LIST_RCObjects)
				set(i, NULL);
			arraycopy(data, i+1, data, i, len-i-1);
			len--;
			// clear copy at the end so it can be collected if removed
			// and isn't decremented on next add
			if(kElementType != LIST_NonGCObjects)
				data[len] = NULL;
			AvmAssert((int32_t)len >= 0);
			return old;
		}

		T removeFirst() { return isEmpty() ? (T)0 : removeAt(0); }
		T removeLast()  { return isEmpty() ? (T)0 : removeAt(len-1); }
		
		T operator[](uint32 index) const
		{
			AvmAssert(index < len);
			return data[index];
		}

		void ensureCapacity(uint32 cap)
		{			
			if(cap > max) {
				int gcflags = 0;
				if(kElementType == LIST_GCObjects)
					gcflags |= MMgc::GC::kContainsPointers;
				if(kElementType == LIST_RCObjects)
					gcflags |= (MMgc::GC::kContainsPointers|MMgc::GC::kZero);

				T* newData = (gc) ? (T*) gc->Calloc(cap, sizeof(T), gcflags) : mmfx_new_array(T, cap);
				for (unsigned int i=0; i<len; i++) {
					newData[i] = data[i];
				}
				if (!gc) {
					mmfx_delete_array(data);
				}
				if(gc && gc->IsPointerToGCPage(this)) {
					// data = newData;
					WB(gc, gc->FindBeginningFast(this), &data, newData);
				} else {
					data = newData;
				}
				max = cap;
			}
		}

		const T *getData() const { return data; }

        void become(List<T, kElementType> &list) {
            clear();
            for (int i=0, n=list.size(); i < n; i++)
                add(list[i]);
            list.clear();
        }

	private:

		List<T,kElementType>& operator=(const List<T,kElementType>& other);	// unimplemented
		List(const List<T,kElementType>& other);							// unimplemented

		void grow()
		{
			// growth is fast at first, then slows at larger list sizes.
			int newMax = 0;
			if (max == 0)
				newMax = kInitialCapacity;
			else if(max > 15)
				newMax = max * 3/2;
			else
				newMax = max * 2;
		
			ensureCapacity(newMax);
		}

		void arraycopy(const T* src, int srcStart, T* dst, int dstStart, int nbr)
		{
			// we have 2 cases, either closing a gap or opening it.
			if ((src == dst) && (srcStart > dstStart) )
			{
				for(int i=0; i<nbr; i++)
					dst[i+dstStart] = src[i+srcStart];	
			}
			else
			{
				for(int i=nbr-1; i>=0; i--)
					dst[i+dstStart] = src[i+srcStart];
			}
		}
	};
}

#endif /* __avmplus_List__ */
