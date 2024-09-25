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


#ifndef __avmplus_VectorClass__
#define __avmplus_VectorClass__

#include "AvmCore.h"
#include "Toplevel.h"

namespace avmplus
{

	class VectorBaseObject : public ScriptObject
	{
	public:
		VectorBaseObject(VTable *ivtable, ScriptObject *delegate)
			: ScriptObject(ivtable, delegate)
		{
			m_capacity = 0;
			m_length = 0;
			m_fixed = false;
		}

		~VectorBaseObject()
		{
			m_capacity = 0;
			m_length = 0;
			m_fixed = false;
		}

		virtual bool hasAtomProperty(Atom name) const;
		virtual void setAtomProperty(Atom name, Atom value);
		virtual Atom getAtomProperty(Atom name) const;

		uint32 get_length();
		void set_length(uint32 newLength);

		bool get_fixed();
		void set_fixed(bool fixed);

		// Iterator support - for in, for each
		Atom nextName(int index);
		Atom nextValue(int index);
		int nextNameIndex(int index);

		Atom map(ScriptObject *callback, Atom thisObject);
		Atom filter(ScriptObject *callback, Atom thisObject);

		uint32 AS3_push(Atom *args, int argc);

		uint32 m_length;
	protected:
		uint32 m_capacity;
		bool m_fixed;

		virtual void grow(uint32 newCapacity, bool exact=false) = 0;
		virtual VectorBaseObject* newVector(uint32 length = 0) = 0;

		bool getVectorIndex(Atom name, uint32& index, bool& isNumber) const;
	};

	template <class T>
	class TypedVectorObject : public VectorBaseObject
	{
	public:
		TypedVectorObject(VTable *ivtable, ScriptObject *delegate)
			: VectorBaseObject(ivtable, delegate)
		{
			m_array = NULL;
		}

		~TypedVectorObject()
		{
			mmfx_delete_array((T*)m_array);
			m_array = NULL;
		}

		Atom _filter(ScriptObject* callback, Atom thisObject) { return filter(callback, thisObject); }
		Atom _map(ScriptObject* callback, Atom thisObject) { return map(callback, thisObject); }

		virtual Atom getUintProperty(uint32 index) const
		{
			return _getUintProperty(index);
		}
		
		virtual void setUintProperty(uint32 index, Atom value)
		{
			_setUintProperty(index, value);
		}			

		T _getNativeUintProperty(uint32 index) const
		{
			if( m_length <= index )
				toplevel()->throwRangeError(kOutOfRangeError, core()->uintToString(index), core()->uintToString(m_length));
			return m_array[index];
		}

		T _getNativeIntProperty(int index) const
		{
			if( m_length <= uint32(index) )
				toplevel()->throwRangeError(kOutOfRangeError, core()->intToString(index), core()->uintToString(m_length));
			return m_array[index];
		}

		void _setNativeUintProperty(uint32 index, T value)
		{
			if (m_length <= index)
			{
				if(index > m_length || m_fixed)
					toplevel()->throwRangeError(kOutOfRangeError, core()->uintToString(index), core()->uintToString(m_length));
				grow(index+1);
				m_length = index+1;
			}
			m_array[index] = value;
		}

		void _setNativeIntProperty(int index, T value)
		{
			if (m_length <= uint32(index))
			{
				if( index < 0 )
					toplevel()->throwRangeError(kOutOfRangeError, core()->intToString(index), core()->uintToString(m_length));
				else if(uint32(index) > m_length || m_fixed)
					toplevel()->throwRangeError(kOutOfRangeError, core()->intToString(index), core()->uintToString(m_length));
				grow(index+1);
				m_length = index+1;
			}
			m_array[index] = value;
		}

		Atom _getUintProperty(uint32 index) const
		{
			if (m_length <= index)
			{
				toplevel()->throwRangeError(kOutOfRangeError, core()->intToString(index), core()->uintToString(m_length));
			}
			return valueToAtom(m_array[index]);
		}

		Atom _getIntProperty(int index) const
		{
			if (index >= 0) 
				return _getUintProperty(index);
			else // integer is negative - we must intern it
				toplevel()->throwRangeError(kOutOfRangeError, core()->intToString(index), core()->uintToString(m_length));
			return 0;
		}

		void _setUintProperty(uint32 index, Atom value)
		{
			if (m_length <= index)
			{
				if(index > m_length || m_fixed)
					toplevel()->throwRangeError(kOutOfRangeError, core()->uintToString(index), core()->uintToString(m_length));
				grow(index+1);
				m_length = index+1;
			}
			atomToValue(value, m_array[index]);
		}

		void _setIntProperty(int index, Atom value)
		{
			if (index >= 0) 
				_setUintProperty(index, value);
			else 
				toplevel()->throwRangeError(kOutOfRangeError, core()->intToString(index), core()->uintToString(m_length));
		}

		void set_length(uint32 newLength)
		{
			if( newLength < m_length )
			{
				VMPI_memset(m_array+newLength, 0, (m_length-newLength)*sizeof(T));
			}
			VectorBaseObject::set_length(newLength);
		}

		uint32 AS3_unshift(Atom* argv, int argc)
		{
			// shift elements up by argc
			// inserts args into initial spots

			if( argc > 0 )
			{
				if( m_fixed )
					toplevel()->throwRangeError(kVectorFixedError);
				grow (m_length + argc);
				T *arr = m_array;
				VMPI_memmove (arr + argc, arr, m_length * sizeof(T));
				for(int i=0; i<argc; i++) {
					atomToValue(argv[i], m_array[i]);
				}

				m_length += argc;
			}
			return m_length;
		}

		void _reverse()
		{
			if(!m_length)
				return;
			T temp;
			for(uint32 i = 0, j = m_length-1; i < j; ++i, --j)
			{
				temp = m_array[i];
				m_array[i] = m_array[j];
				m_array[j] = temp;
			}
		}
		void _spliceHelper(uint32 insertPoint, uint32 insertCount, uint32 deleteCount, Atom args, int offset)
		{
			long l_shiftAmount = (long)insertCount - (long) deleteCount; // long because result could be negative

			grow(m_length + l_shiftAmount);

			T *arr = m_array;

			ScriptObject* so_args = AvmCore::atomToScriptObject(args);
			TypedVectorObject<T>* vec_args = isVector(args);

			if (l_shiftAmount < 0) 
			{
				//int numberBeingDeleted = -l_shiftAmount;

				// shift elements down
				int toMove = m_length - insertPoint - deleteCount;
				VMPI_memmove (arr + insertPoint + insertCount, arr + insertPoint + deleteCount, toMove * sizeof(T));

				//VMPI_memset (arr + m_length - numberBeingDeleted, 0, numberBeingDeleted * sizeof(T));
			}
			else if (l_shiftAmount > 0)
			{
				VMPI_memmove (arr + insertPoint + l_shiftAmount, arr + insertPoint, (m_length - insertPoint) * sizeof(T));
				//
				//VMPI_memset (arr + insertPoint, 0, l_shiftAmount * sizeof(T));
			}

			set_length(m_length + l_shiftAmount);

			// Add the items to insert
			if (insertCount)
			{
				if( vec_args && (offset+insertCount <= vec_args->m_length) )
				{
					VMPI_memmove(arr+insertPoint, vec_args->m_array+offset, insertCount*sizeof(T));
				}
				else if( so_args )
				{
					for (uint32 i=0; i<insertCount; i++)
					{
						//setUintProperty(insertPoint+i, so_args->getUintProperty(i+offset));
						atomToValue(so_args->getUintProperty(i+offset), m_array[insertPoint+i]);
					}
				}
			}

			return;
		}

		T AS3_pop() 
		{
			if(m_fixed)
				toplevel()->throwRangeError(kVectorFixedError);
			if(m_length)
			{
				uint32 l = --m_length;
				T r = m_array[l];
				m_array[l] = 0;
				return r;
			}
			return 0;  // Undefined cast to number/int/uint
		}

		DWB(T *) m_array;

		// Helper method to init the vector with another object
		void initWithObj(Atom obj) 
		{
			ScriptObject* so_args = atomKind(obj)==kObjectType ?  AvmCore::atomToScriptObject(obj) : 0;
			if( so_args )
			{
				uint32 len = ArrayClass::getLengthHelper(toplevel(), so_args);
				for( uint32 i = 0; i < len; ++i )
				{
					this->setUintProperty(i, so_args->getUintProperty(i));
				}
				return;
			}
			toplevel()->throwTypeError(kCheckTypeFailedError, core()->atomToErrorString(obj), core()->toErrorString(this->traits()));
			return;
		}

	protected:

		enum { kGrowthIncr = 4096 };

		void atomToValue(Atom atom, sint16& value)
		{
			value = (sint16) AvmCore::integer(atom);						
		}
		void atomToValue(Atom atom, uint16& value)
		{
			value = (uint16) AvmCore::integer_u(atom);			
		}
		void atomToValue(Atom atom, sint32& value)
		{
			value = AvmCore::integer(atom);						
		}
		void atomToValue(Atom atom, sint64& value)
		{
			value = AvmCore::integer(int(atom));						
		}
		void atomToValue(Atom atom, uint32& value)
		{
			value = AvmCore::toUInt32(atom);			
		}
		void atomToValue(Atom atom, float& value)
		{
			value = (float) AvmCore::number(atom);
		}
		void atomToValue(Atom atom, double& value)
		{
			value = AvmCore::number(atom);
		}
		void atomToValue(Atom atom, ScriptObject*& value)
		{
			value = AvmCore::atomToScriptObject(atom);
		}

		Atom valueToAtom(sint16 value) const
		{
			return core()->intToAtom(value);
		}
		Atom valueToAtom(uint16 value) const
		{
			return core()->uintToAtom(value);
		}
		Atom valueToAtom(sint32 value) const
		{
			return core()->intToAtom(value);
		}
		Atom valueToAtom(uint32 value) const
		{
			return core()->uintToAtom(value);
		}
		Atom valueToAtom(sint64 value) const
		{
			return core()->intToAtom(int(value));
		}
		Atom valueToAtom(float value) const
		{
			return core()->doubleToAtom((double)value);
		}
		Atom valueToAtom(double value) const
		{
			return core()->doubleToAtom(value);
		}
		Atom valueToAtom(ScriptObject* value) const
		{
			return value ? value->atom() : nullObjectAtom;
		}

		TypedVectorObject<T>* isVector(Atom instance)
		{
			if (AvmCore::istype(instance, vtable->traits))
				return (TypedVectorObject<T>*)AvmCore::atomToScriptObject(instance);
			return NULL;
		}

		virtual void grow(uint32 newCapacity, bool exact = false)
		{
			if (newCapacity > m_capacity)
			{
				if( !exact )
					newCapacity = newCapacity + (newCapacity >>2);
				//newCapacity = ((newCapacity+kGrowthIncr)/kGrowthIncr)*kGrowthIncr;
				T *newArray = mmfx_new_array(T, newCapacity);
				if (!newArray)
				{
					toplevel()->throwError(kOutOfMemoryError);
				}
				if (m_array)
				{
					VMPI_memcpy(newArray, m_array, m_length * sizeof(T));
					mmfx_delete_array((T*)m_array);
				}
				VMPI_memset(newArray+m_length, 0, (newCapacity-m_capacity) * sizeof(T));
				m_array = newArray;
				m_capacity = newCapacity;
			}
		}
	};

	class IntVectorObject : public TypedVectorObject<sint32> {
	public:
		IntVectorObject(VTable *ivtable, ScriptObject *delegate)
			: TypedVectorObject<sint32>(ivtable, delegate)
		{
		}

		~IntVectorObject()
		{
		}
	protected:
		virtual VectorBaseObject* newVector(uint32 length = 0);
		DECLARE_SLOTS_IntVectorObject;
	};

	class UIntVectorObject : public TypedVectorObject<uint32> {
	public:
		UIntVectorObject(VTable *ivtable, ScriptObject *delegate)
			: TypedVectorObject<uint32>(ivtable, delegate)
		{
		}

		~UIntVectorObject()
		{
		}

	protected:
		virtual VectorBaseObject* newVector(uint32 length = 0);
		DECLARE_SLOTS_UIntVectorObject;
	};

	class DoubleVectorObject : public TypedVectorObject<double> {
	public:
		DoubleVectorObject(VTable *ivtable, ScriptObject *delegate)
			: TypedVectorObject<double>(ivtable, delegate)
		{
		}

		~DoubleVectorObject()
		{
		}

	protected:
		virtual VectorBaseObject* newVector(uint32 length = 0);
		DECLARE_SLOTS_DoubleVectorObject;
	};

	class ObjectVectorObject : public TypedVectorObject<Atom>
	{
	public:
		ObjectVectorObject(VTable *ivtable, ScriptObject *delegate)
			: TypedVectorObject<Atom>(ivtable, delegate)
		{
		}

		~ObjectVectorObject()
		{
			AvmCore::decrementAtomRegion(m_array, m_length);
			m_length = 0;
			if(m_array) {
				MMgc::GC::GetGC(m_array)->Free(m_array);
				m_array = 0;
			}
		}

		virtual Atom getUintProperty(uint32 index) const;
		virtual void setUintProperty(uint32 index, Atom value);

		Atom _getUintProperty(uint32 index) const;
		void _setUintProperty(uint32 index, Atom value);

		Atom _getIntProperty(int index) const;
		void _setIntProperty(int index, Atom value);

		void set_length(uint32 newLength);

		void set_type(Atom a);
		Atom get_type();

		//void _reverse();
		// insert array of arguments at front of array
		uint32 AS3_unshift(Atom* argv, int argc);
		void _spliceHelper(uint32 insertPoint, uint32 insertCount, uint32 deleteCount, Atom args, int offset);

		Atom AS3_pop();

	protected:
		virtual void grow(uint32 newCapacity, bool exact=false);
		virtual VectorBaseObject* newVector(uint32 length = 0);

	private:
		ObjectVectorObject* isVector(Atom instance)
		{
			if (instance && AvmCore::istype(instance, vtable->traits))
				return (ObjectVectorObject*)AvmCore::atomToScriptObject(instance);
			return NULL;
		}

		DRCWB(ClassClosure*) t;
		DECLARE_SLOTS_ObjectVectorObject;
	};

	class IntVectorClass : public ClassClosure
	{
    public:
		IntVectorClass(VTable *vtable);

		ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);

		Atom call(int argc, Atom* argv);

		IntVectorObject* newVector(uint32 length = 0);

		void _forEach(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_forEach(toplevel(), thisAtom, callback, thisObject); }
		bool _every(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_every(toplevel(), thisAtom, callback, thisObject); }
		bool _some(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_some(toplevel(), thisAtom, callback, thisObject); }
		Atom _sort(Atom thisAtom, ArrayObject *args) { return ArrayClass::generic_sort(toplevel(), thisAtom, args); }
		
		DECLARE_SLOTS_IntVectorClass;
    };

	class UIntVectorClass : public ClassClosure
	{
    public:
		UIntVectorClass(VTable *vtable);

		ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);

		Atom call(int argc, Atom* argv);

		UIntVectorObject* newVector(uint32 length = 0);

		void _forEach(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_forEach(toplevel(), thisAtom, callback, thisObject); }
		bool _every(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_every(toplevel(), thisAtom, callback, thisObject); }
		bool _some(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_some(toplevel(), thisAtom, callback, thisObject); }
		Atom _sort(Atom thisAtom, ArrayObject *args) { return ArrayClass::generic_sort(toplevel(), thisAtom, args); }
		
		DECLARE_SLOTS_UIntVectorClass;
    };

	class DoubleVectorClass : public ClassClosure
	{
    public:
		DoubleVectorClass(VTable *vtable);

		ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);

		Atom call(int argc, Atom* argv);

		DoubleVectorObject* newVector(uint32 length = 0);

		void _forEach(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_forEach(toplevel(), thisAtom, callback, thisObject); }
		bool _every(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_every(toplevel(), thisAtom, callback, thisObject); }
		bool _some(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_some(toplevel(), thisAtom, callback, thisObject); }
		Atom _sort(Atom thisAtom, ArrayObject *args) { return ArrayClass::generic_sort(toplevel(), thisAtom, args); }
		
		DECLARE_SLOTS_DoubleVectorClass;
    };

	class VectorClass : public ClassClosure
	{
	public:
		VectorClass(VTable * vtable);
        
        /**
         *  This unspecialized class cannot be instantiated.
         *  Ensure any attempt fails.
         *  @throw TypeError
         */
        ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);

        /**
         *  Apply type arguments and call the specialized class' newVector().
         *  @pre The type must be an Object type.
         *  
         */
		ObjectVectorObject* newVector(ClassClosure* type, uint32 length = 0);

		virtual Atom applyTypeArgs(int argc, Atom* argv);
	
		static Stringp makeVectorClassName(AvmCore* core, Traits* t);
	
	private:
		DWB(HeapHashtable*) instantiated_types;
		
		DECLARE_SLOTS_VectorClass;
	};

	class ObjectVectorClass : public ClassClosure
	{
		friend class VectorClass;
	public:
		ObjectVectorClass(VTable * vtable);

		ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);

		Atom call(int argc, Atom* argv);

		ObjectVectorObject* newVector(uint32 length = 0);
	
		void _forEach(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_forEach(toplevel(), thisAtom, callback, thisObject); }
		bool _every(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_every(toplevel(), thisAtom, callback, thisObject); }
		bool _some(Atom thisAtom, ScriptObject* callback, Atom thisObject) { return ArrayClass::generic_some(toplevel(), thisAtom, callback, thisObject); }
		Atom _sort(Atom thisAtom, ArrayObject *args) { return ArrayClass::generic_sort(toplevel(), thisAtom, args); }

	private:
		DRCWB(ClassClosure*) index_type;
		DECLARE_SLOTS_ObjectVectorClass;
	};

}	

#endif /* __avmplus_VectorClass__ */
