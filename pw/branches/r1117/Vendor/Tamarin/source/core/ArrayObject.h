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

#ifndef __avmplus_ArrayObject__
#define __avmplus_ArrayObject__


namespace avmplus
{
	/**
	 * an instance of class Array.  constructed with "new Array" or
	 * an array literal [...].   We need this class to support Array's
	 * special "get" and "put" semantics and to maintain the virtual
	 * "length" property.
	 */
	class ArrayObject : public ScriptObject
	{
	private:
		friend class ArrayClass;
		AtomArray m_denseArr;

		// We can NOT use 0xFFFFFFFF for this since x[0xFFFFFFFE] is a valid prop
		// which would make our length 0xFFFFFFFF
		static const uint32 NO_LOW_HTENTRY	= 0;
		uint32 m_lowHTentry; // lowest numeric entry in our hash table
		uint32 m_length;
	public:
		
		ArrayObject(VTable* ivtable, ScriptObject *delegate, uint32 capacity);
		~ArrayObject()
		{
			m_lowHTentry = 0;
			m_length = 0;
		}

		bool hasDense() const { return (m_denseArr.getLength() != 0); };
		bool isSimpleDense() const { return (m_denseArr.getLength() == m_length); };
		uint32 getDenseLength() const { return m_denseArr.getLength(); }

		// Non-virtual members for ActionScript method implementation
		uint32 get_length() const;
		void set_length(uint32 newLength);

		// Virtual members so Array subclasses can treat length differently (in both C++ and AS3)
		virtual uint32 getLength() const;
		virtual void setLength(uint32 newLength);

		virtual Atom getAtomProperty(Atom name) const;
		virtual void setAtomProperty(Atom name, Atom value);
		virtual bool deleteAtomProperty(Atom name);
		virtual bool hasAtomProperty(Atom name) const;

		// Faster versions that takes direct indices
		virtual Atom getUintProperty(uint32 index) const
		{
			 return _getUintProperty(index);
		}
		virtual void setUintProperty(uint32 index, Atom value)
		{
			_setUintProperty(index, value);
		}
		virtual bool delUintProperty(uint32 index);
		virtual bool hasUintProperty(uint32 i) const;

		inline Atom getIntProperty(int index) const
		{
			return _getIntProperty(index);
		}
		inline void setIntProperty(int index, Atom value)
		{
			_setIntProperty(index, value);
		}

		virtual bool getAtomPropertyIsEnumerable(Atom name) const;
		
		Atom _getUintProperty(uint32 index) const;
		void _setUintProperty(uint32 index, Atom value);
		Atom _getIntProperty(int index) const;
		void _setIntProperty(int index, Atom value);

		// Iterator support - for in, for each
		virtual Atom nextName(int index);
		virtual Atom nextValue(int index);
		virtual int nextNameIndex(int index);

		// native methods
		Atom AS3_pop(); // pop(...rest)
		uint32 AS3_push(Atom *args, int argc); // push(...args):uint
		uint32 AS3_unshift(Atom *args, int argc); // unshift(...args):

		inline Atom pop() { return AS3_pop(); }
		inline uint32 push(Atom *args, int argc) { return AS3_push(args, argc); }
		inline uint32 unshift(Atom *args, int argc) { return AS3_unshift(args, argc); }

		void checkForSparseToDenseConversion();

#ifdef DEBUGGER
		virtual uint64 size() const;
#endif

#ifdef AVMPLUS_VERBOSE
	public:
		Stringp format(AvmCore* core) const;
#endif

		DECLARE_SLOTS_ArrayObject;
	};
}

#endif /* __avmplus_ArrayObject__ */
