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



#include "avmshell.h"
#include "genericzlib.h"

namespace avmshell
{
	//
	// ByteArray
	//
	
	ByteArray::ByteArray()
	{
		m_subscriberRoot = NULL;
		m_capacity = 0;
		m_length   = 0;
		m_array    = NULL;
	}

	ByteArray::ByteArray(const ByteArray &lhs) 
        // GCC will warn if we don't explicitly init GlobalMemoryProvider, 
        // even though it has no fields or ctor... sigh
        : GlobalMemoryProvider()
	{
		m_subscriberRoot = NULL;
		m_array    = mmfx_new_array(uint8_t, lhs.m_length);
		if (!m_array)
		{
			ThrowMemoryError();
			return;
		}

		m_capacity = lhs.m_length;
		m_length   = lhs.m_length;

		VMPI_memcpy(m_array, lhs.m_array, m_length);
	}

	ByteArray::~ByteArray()
	{
		m_subscriberRoot = NULL;
		if (m_array)
		{
			mmfx_delete_array(m_array);
			m_array = NULL;
		}
		m_capacity = 0;
		m_length = 0;
	}

	void ByteArray::ThrowMemoryError()
	{
		// todo throw out of memory exception
		// m_toplevel->memoryError->throwError(kOutOfMemoryError);
	}

	bool ByteArray::Grow(uint32_t minimumCapacity)
	{
		if (minimumCapacity > m_capacity)
		{
			uint32_t newCapacity = m_capacity << 1;			
			if (newCapacity < minimumCapacity)
			{
				newCapacity = minimumCapacity;
			}
			if (newCapacity < kGrowthIncr) 
			{
				newCapacity = kGrowthIncr;
			}
			U8 *newArray = mmfx_new_array(uint8_t, newCapacity);
			if (!newArray)
			{
				return false;
			}
			if (m_array)
			{
				VMPI_memcpy(newArray, m_array, m_length);
				mmfx_delete_array(m_array);
			}
			VMPI_memset(newArray+m_length, 0, newCapacity-m_capacity);
			m_array = newArray;
			m_capacity = newCapacity;
			NotifySubscribers();
		}
		return true;
	}
		
	U8 ByteArray::operator[] (uint32_t index) const
	{
		if (m_length <= index)
		{
			return 0;
		}
		return m_array[index];
	}

	U8& ByteArray::operator[] (uint32_t index)
	{
		if (m_length <= index)
		{
			Grow(index+1);
			m_length = index+1;
			NotifySubscribers();
		}
		return m_array[index];
	}

	void ByteArray::Push(U8 value)
	{
		if (m_length >= m_capacity)
		{
			Grow(m_length + 1);
		}
		m_array[m_length++] = value;
		NotifySubscribers();
	}
		
	void ByteArray::Push(const U8 *data, uint32_t count)
	{
		Grow(m_length + count);
		VMPI_memcpy(m_array + m_length, data, count);
		m_length += count;
		NotifySubscribers();
	}
	
	void ByteArray::SetLength(uint32_t newLength)
	{
 		if(m_subscriberRoot && m_length < Domain::GLOBAL_MEMORY_MIN_SIZE)
 			ThrowMemoryError();
		if (newLength > m_capacity)
		{
			if (!Grow(newLength))
			{
				ThrowMemoryError();
				return;
			}
		}
		m_length = newLength;
		NotifySubscribers();
	}

 	void ByteArray::NotifySubscribers()
 	{
 		SubscriberLink *curLink = m_subscriberRoot;
 		SubscriberLink **prevNext = &m_subscriberRoot;
 
 		while(curLink != NULL) // notify subscribers
 		{
 			AvmAssert(m_length >= Domain::GLOBAL_MEMORY_MIN_SIZE);
 
 			GlobalMemorySubscriber* subscriber = (GlobalMemorySubscriber*)curLink->weakSubscriber->get();
 
 			if (subscriber)
 			{
 				subscriber->notifyGlobalMemoryChanged(m_array, m_length);
 				prevNext = &curLink->next;
 			}
 			else
            {
 				// Domain went away? remove link
 				MMgc::GC::WriteBarrier(prevNext, curLink->next);
            }
 			curLink = curLink->next;
 		}
 	}
 
 	bool ByteArray::addSubscriber(GlobalMemorySubscriber* subscriber)
 	{
 		if(m_length >= Domain::GLOBAL_MEMORY_MIN_SIZE)
 		{
 			removeSubscriber(subscriber);
			SubscriberLink *newLink = new (MMgc::GC::GetGC(subscriber)) SubscriberLink;
 			newLink->weakSubscriber = subscriber->GetWeakRef();
 			MMgc::GC::WriteBarrier(&newLink->next, m_subscriberRoot);
 			MMgc::GC::WriteBarrier(&m_subscriberRoot, newLink);
 			// notify the new "subscriber" of the current state of the world
 			subscriber->notifyGlobalMemoryChanged(m_array, m_length);
 			return true;
 		}
 		return false;
 	}
 
 	bool ByteArray::removeSubscriber(GlobalMemorySubscriber* subscriber)
 	{
 		SubscriberLink **prevNext = &m_subscriberRoot;
 		SubscriberLink *curLink = m_subscriberRoot;
 
 		while(curLink)
 		{
 			if ((GlobalMemorySubscriber*)curLink->weakSubscriber->get() == subscriber)
 			{
 				MMgc::GC::WriteBarrier(prevNext, curLink->next);
 				return true;
 			}
 			prevNext = &curLink->next;
 			curLink = curLink->next;
 		}
 		return false;
	}

	//
	// ByteArrayFile
	//

	ByteArrayFile::ByteArrayFile(Toplevel *toplevel)
		: DataInput(toplevel),
		  DataOutput(toplevel)
	{
		m_filePointer = 0;
	}

	uint32_t ByteArrayFile::Available()
	{
		if (m_filePointer <= m_length) {
			return m_length - m_filePointer;
		} else {
			return 0;
		}
	}

	void ByteArrayFile::SetLength(uint32_t newLength)
	{
		ByteArray::SetLength(newLength);
		if (m_filePointer > newLength) {
			m_filePointer = newLength;
		}
	}
	
	void ByteArrayFile::Read(void *buffer, uint32_t count)
	{
		CheckEOF(count);

		if (count > 0)
		{
			VMPI_memcpy(buffer, m_array+m_filePointer, count);
			m_filePointer += count;
		}
	}

	void ByteArrayFile::Write(const void *buffer, uint32_t count)
	{
		if (m_filePointer+count >= m_length) {
			Grow(m_filePointer+count);
			m_length = m_filePointer+count;
		}
		VMPI_memcpy(m_array+m_filePointer, buffer, count);
		m_filePointer += count;
	}

	//
	// ByteArrayObject
	//
	
	ByteArrayObject::ByteArrayObject(VTable *ivtable,
									 ScriptObject *delegate)
		: ScriptObject(ivtable, delegate),
		  m_byteArray(toplevel())
	{
		c.set(&m_byteArray, sizeof(ByteArrayFile));
	}

	Atom ByteArrayObject::getUintProperty(uint32_t i) const
	{
		if (i < (uint32_t)m_byteArray.GetLength()) {
			return core()->intToAtom(m_byteArray[i]);
		} else {
			return undefinedAtom;
		}
	}
	
	void ByteArrayObject::setUintProperty(uint32_t i, Atom value)
	{
		m_byteArray[i] = (U8)(AvmCore::integer(value));
	}
	
	Atom ByteArrayObject::getAtomProperty(Atom name) const
	{
		uint32_t index;
		if (AvmCore::getIndexFromAtom(name, &index)) {
			if (index < (uint32_t) m_byteArray.GetLength()) {
				return core()->intToAtom(m_byteArray[index]);
			} else {
				return undefinedAtom;
			}
		}

		return ScriptObject::getAtomProperty(name);
	}
	
	void ByteArrayObject::setAtomProperty(Atom name, Atom value)
	{
		uint32_t index;
		if (AvmCore::getIndexFromAtom(name, &index)) {
			int intValue = AvmCore::integer(value);
			m_byteArray[index] = (U8)(intValue);
		} else {
			ScriptObject::setAtomProperty(name, value);
		}
	}
	
	bool ByteArrayObject::hasAtomProperty(Atom name) const
	{
		return ScriptObject::hasAtomProperty(name) || getAtomProperty(name) != undefinedAtom;
	}

	void ByteArrayObject::setLength(uint32_t newLength)
	{
		m_byteArray.SetLength(newLength);
	}

	uint32_t ByteArrayObject::get_length()
	{
		return m_byteArray.GetLength();
	}

	void ByteArrayObject::set_length(uint32_t value)
	{
		setLength(value);
	}

	int ByteArrayObject::get_position()
	{
		return m_byteArray.GetFilePointer();
	}

	int ByteArrayObject::get_bytesAvailable()
	{
		return m_byteArray.Available();
	}
	
	void ByteArrayObject::set_position(int offset)
	{
		if (offset >= 0) {
			m_byteArray.Seek(offset);
		}
	}

	String* ByteArrayObject::_toString()
	{
		union {
			uint8_t* c;
			wchar* c_w;
		};
		c = (uint8_t*)m_byteArray.GetBuffer();
		uint32_t len = m_byteArray.GetLength();

		if (len >= 3)
		{
			// UTF8 BOM
			if ((c[0] == 0xef) && (c[1] == 0xbb) && (c[2] == 0xbf))
			{
				return core()->newStringUTF8((const char*)c + 3, len - 3);
			}
			else if ((c[0] == 0xfe) && (c[1] == 0xff))
			{
				//UTF-16 big endian
				c += 2;
				len = (len - 2) >> 1;
				return core()->newStringEndianUTF16(/*littleEndian*/false, c_w, len);
			}
			else if ((c[0] == 0xff) && (c[1] == 0xfe))
			{
				//UTF-16 little endian
				return core()->newStringEndianUTF16(/*littleEndian*/true, c_w, len);
			}
		}

		// Use newStringUTF8() with "strict" explicitly set to false to mimick old,
		// buggy behavior, where malformed UTF-8 sequences are stored as single characters.
		return core()->newStringUTF8((const char*)c, len, false);
	}
	
	int ByteArrayObject::readByte()
	{
		return (signed char)m_byteArray.ReadU8();
	}

	int ByteArrayObject::readUnsignedByte()
	{
		return m_byteArray.ReadU8();
	}

	int ByteArrayObject::readShort()
	{
		return (short)m_byteArray.ReadU16();
	}

	int ByteArrayObject::readUnsignedShort()
	{
		return m_byteArray.ReadU16();
	}

	int ByteArrayObject::readInt()
	{
		return (int)m_byteArray.ReadU32();		
	}

	uint32_t ByteArrayObject::readUnsignedInt()
	{
		return m_byteArray.ReadU32();		
	}
	
	double ByteArrayObject::readFloat()
	{
		return m_byteArray.ReadFloat();
	}

	double ByteArrayObject::readDouble()
	{
		return m_byteArray.ReadDouble();
	}

	bool ByteArrayObject::readBoolean()
	{
		return m_byteArray.ReadBoolean();
	}

	void ByteArrayObject::writeBoolean(bool value)
	{
		m_byteArray.WriteBoolean(value);
	}

	void ByteArrayObject::writeByte(int value)
	{
		m_byteArray.WriteU8((U8)value);
	}

	void ByteArrayObject::writeShort(int value)
	{
		m_byteArray.WriteU16((unsigned short)value);
	}

	void ByteArrayObject::writeInt(int value)
	{
		m_byteArray.WriteU32((uint32_t)value);
	}

	void ByteArrayObject::writeUnsignedInt(uint32_t value)
	{
		m_byteArray.WriteU32(value);
	}
	
	void ByteArrayObject::writeFloat(double value)
	{
		m_byteArray.WriteFloat((float)value);
	}

	void ByteArrayObject::writeDouble(double value)
	{
		m_byteArray.WriteDouble(value);
	}

	void ByteArrayObject::zlib_compress()
	{
		int len = m_byteArray.GetLength();
		if (!len) // empty buffer should give us a empty result
			return; 
		unsigned long gzlen = len * 3/2 + 32; // enough for growth plus zlib headers
		U8 *gzdata = mmfx_new_array( uint8_t, gzlen );

		// Use zlib to compress the data
		compress2((uint8_t*)gzdata, (unsigned long*)&gzlen,
				m_byteArray.GetBuffer(), len, 9);

		// Replace the byte array with the compressed data
		m_byteArray.SetLength(0);
		//m_byteArray.WriteU32((U32)len);
		m_byteArray.Write(gzdata, gzlen);

		mmfx_delete_array( gzdata );
	}

    void ByteArrayObject::zlib_uncompress()
    {
        // Snapshot the compressed data.
        unsigned long gzlen = m_byteArray.GetLength();
		if (!gzlen) // empty buffer should give us a empty result
			return; 

		uint8_t *gzdata = mmfx_new_array( uint8_t, gzlen );
        VMPI_memcpy(gzdata, m_byteArray.GetBuffer(), gzlen);

        // Clear the buffer
        m_byteArray.Seek(0);
        m_byteArray.SetLength(0);

        // The following block is to force destruction
        // of zstream before potential exception throw.
        int error = Z_OK;
        {
            // Decompress the data
            PlatformZlibStream zstream;
            zstream.SetNextIn(gzdata);
            zstream.SetAvailIn(gzlen);

            const int kBufferSize = 8192;
            uint8_t *buffer = mmfx_new_array( uint8_t, kBufferSize );

            do {
                zstream.SetNextOut(buffer);
                zstream.SetAvailOut(kBufferSize);
                error = zstream.InflateWithStatus();
                m_byteArray.Write(buffer, kBufferSize-zstream.AvailOut());
            } while (error == Z_OK);

            mmfx_delete_array( buffer );
	    mmfx_delete_array( gzdata );
        }

		// position byte array at the beginning
		m_byteArray.Seek(0);

        if (error != Z_OK && error != Z_STREAM_END) {
            toplevel()->throwError(kShellCompressedDataError);
        }
    }

	void ByteArrayObject::checkNull(void *instance, const char *name)
	{
		if (instance == NULL) {
			toplevel()->throwTypeError(kNullArgumentError, core()->toErrorString(name));
		}
	}	
	void ByteArrayObject::writeBytes(ByteArrayObject *bytes,
									 uint32_t offset,
									 uint32_t length)
	{
		checkNull(bytes, "bytes");

		if (length == 0) {
			length = bytes->getLength() - offset;
		}
		
		m_byteArray.WriteByteArray(bytes->GetByteArray(),
								   offset,
								   length);
	}

	void ByteArrayObject::readBytes(ByteArrayObject *bytes,
									uint32_t offset,
									uint32_t length)
	{
		checkNull(bytes, "bytes");

		if (length == 0) {
			length = m_byteArray.Available();
		}
		
		m_byteArray.ReadByteArray(bytes->GetByteArray(),
								  offset,
								  length);
	}
	
	String* ByteArrayObject::readUTF()
	{
		return m_byteArray.ReadUTF();
	}

	String* ByteArrayObject::readUTFBytes(uint32_t length)
	{
		return m_byteArray.ReadUTFBytes(length);
	}
	
	void ByteArrayObject::writeUTF(String *value)
	{
		checkNull(value, "value");
		m_byteArray.WriteUTF(value);
	}

	void ByteArrayObject::writeUTFBytes(String *value)
	{
		checkNull(value, "value");
		m_byteArray.WriteUTFBytes(value);
	}

	void ByteArrayObject::fill(const void *b, uint32_t len)
	{
		m_byteArray.Write(b, len);
	}
	
	//
	// ByteArrayClass
	//

	ByteArrayClass::ByteArrayClass(VTable *vtable)
		: ClassClosure(vtable)
    {
        prototype = toplevel()->objectClass->construct();
	}

	ScriptObject* ByteArrayClass::createInstance(VTable *ivtable,
												 ScriptObject *prototype)
    {
        return new (core()->GetGC(), ivtable->getExtraSize()) ByteArrayObject(ivtable, prototype);
    }


	ByteArrayObject * ByteArrayClass::readFile(Stringp filename)
	{
		Toplevel* toplevel = this->toplevel();
		if (!filename) {
			toplevel->throwArgumentError(kNullArgumentError, "filename");
		}
		StUTF8String filenameUTF8(filename);

		File* fp = Platform::GetInstance()->createFile();
		if (fp == NULL || !fp->open(filenameUTF8.c_str(), File::OPEN_READ_BINARY)) 
		{
			if(fp)
			{
				Platform::GetInstance()->destroyFile(fp);
			}
			toplevel->throwError(kFileOpenError, filename);
		}

		int64_t len = fp->size();
		if((uint64_t)len >= UINT32_T_MAX) //ByteArray APIs cannot handle files > 4GB
		{
			toplevel->throwRangeError(kOutOfRangeError, filename);
		}

		uint32_t readCount = (uint32_t)len;

		unsigned char *c = mmfx_new_array( unsigned char, readCount+1);

		Atom args[1] = {nullObjectAtom};
		ByteArrayObject *b = (ByteArrayObject*)AvmCore::atomToScriptObject(construct(0,args));
		b->setLength(0);

		while (readCount > 0)
		{
			uint32_t actual = (uint32_t) fp->read(c, readCount);
			if (actual > 0)
			{
				b->fill(c, actual);
				readCount -= readCount;
			}
			else
			{
				break;
			}
		}
		b->seek(0);

		mmfx_delete_array( c );

		fp->close();
		Platform::GetInstance()->destroyFile(fp);

		return b;
	}

	Stringp ByteArrayObject::get_endian()
	{
		return (m_byteArray.GetEndian() == kBigEndian) ? core()->internConstantStringLatin1("bigEndian") : core()->internConstantStringLatin1("littleEndian");
	}

	void ByteArrayObject::set_endian(Stringp type)
	{
		AvmCore* core = this->core();
		type = core->internString(type);
		if (type == core->internConstantStringLatin1("bigEndian"))
		{
			m_byteArray.SetEndian(kBigEndian);
		}
		else if (type == core->internConstantStringLatin1("littleEndian"))
		{
			m_byteArray.SetEndian(kLittleEndian);
		}
		else
		{
			toplevel()->throwArgumentError(kInvalidArgumentError, "type");
		}
	}

	void ByteArrayObject::writeFile(Stringp filename)
	{
		Toplevel* toplevel = this->toplevel();
		if (!filename) {
			toplevel->throwArgumentError(kNullArgumentError, "filename");
		}

		StUTF8String filenameUTF8(filename);

		File* fp = Platform::GetInstance()->createFile();
		if (fp == NULL || !fp->open(filenameUTF8.c_str(), File::OPEN_WRITE_BINARY)) 
		{
			if(fp)
			{
				Platform::GetInstance()->destroyFile(fp);
			}
			toplevel->throwError(kFileWriteError, filename);
		}

		int32_t len = this->get_length();
		bool success = (int32_t)fp->write(&(this->GetByteArray())[0], len) == len;
		
		fp->close();
		Platform::GetInstance()->destroyFile(fp);
		
		if (!success) {
			toplevel->throwError(kFileWriteError, filename);
		}
	}


}	

