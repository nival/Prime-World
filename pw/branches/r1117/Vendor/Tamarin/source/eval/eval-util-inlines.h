/* -*- mode: c++; tab-width: 4 -*- */
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

// This file is included into eval.h

inline void* Allocator::alloc(size_t nbytes)
{
	nbytes = (nbytes + 7) & ~7;
	if (current_top + nbytes <= current_limit) {
		void *p = current_top;
		current_top += nbytes;
		return p;
	}
	return allocSlow(nbytes);
}

inline uint8_t* emitU16(uint8_t* out, uint16_t val)
{
	*out++ = val & 255;
	*out++ = (val >> 8) & 255;
	return out;
}

inline uint8_t* emitU30(uint8_t* out, uint32_t val)
{
	AvmAssert(val <= 0x3FFFFFFF);
	return emitU32(out, val);
}

inline uint8_t* emitS32(uint8_t* out, int32_t val)
{
	return emitU32(out, (uint32_t)val);
}

template<class T> inline Seq<T>* SeqBuilder<T>::get() const
{
	return items;
}

inline uint32_t ByteBuffer::size() const
{
	return last == NULL ? 0 : (uint32_t)(size_rest + (out - last->start));
}

inline void ByteBuffer::makeRoom(uint32_t nbytes)
{
	if (out + nbytes > limit)
		makeRoomSlow(nbytes);
}

inline void ByteBuffer::emitU8(uint8_t v)
{
	makeRoom(1);
	*out++ = v;
}

inline void ByteBuffer::emitS8(int8_t v)
{
	emitU8((uint8_t)v);
}

inline void ByteBuffer::emitU16(uint16_t v)
{
	makeRoom(2);
	out = avmplus::RTC::emitU16(out, v);
}

inline void ByteBuffer::emitS24(int32_t v)
{
	makeRoom(3);
	out = avmplus::RTC::emitS24(out, v);
}

inline void ByteBuffer::emitU30(uint32_t v)
{
	makeRoom(5);
	out = avmplus::RTC::emitU30(out, v);
}

inline void ByteBuffer::emitU32(uint32_t v)
{
	makeRoom(5);
	out = avmplus::RTC::emitU32(out, v);
}

inline void ByteBuffer::emitS32(int32_t v)
{
	makeRoom(5);
	out = avmplus::RTC::emitS32(out, v);
}

inline void ByteBuffer::emitDouble(double v)
{
	makeRoom(8);
	out = avmplus::RTC::emitDouble(out, v);
}

inline void ByteBuffer::emitUtf8(uint32_t nbytes, Str* str)
{
	makeRoom(nbytes);
	out = avmplus::RTC::emitUtf8(out, str);
}

inline uint32_t StringBuilder::length()
{
	return len;
}

