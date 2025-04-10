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


#ifndef BYTEARRAYGLUE_INCLUDED
#define BYTEARRAYGLUE_INCLUDED

namespace avmshell
{
	class ByteArray : public GlobalMemoryProvider
	{
	public:
		ByteArray();
		ByteArray(const ByteArray &lhs);
		~ByteArray();

		U8 operator [] (uint32_t index) const;
		U8& operator [] (uint32_t index);
		void Push(U8 value);
		void Push(const U8 *buffer, uint32_t count);
		uint32_t GetLength() const { return m_length; }
		void SetLength(uint32_t newLength);
		bool Grow(uint32_t newCapacity);
		U8 *GetBuffer() const { return m_array; }

        // from GlobalMemoryProvider
        /*virtual*/ bool addSubscriber(GlobalMemorySubscriber* subscriber);
        /*virtual*/ bool removeSubscriber(GlobalMemorySubscriber* subscriber);

	protected:
 		// singly linked list of all subscribers to this ByteArray...
 		// in practice, there isn't much liklihood of too many
 		// subscribers at a time and notifications should be rare
 		// hence the slower, simpler, smaller structures and algorithms
 
 		// links are removed explicitly via GlobalMemoryUnsubscribe
 		// or implicitly when the backing store changes
 		struct SubscriberLink : public MMgc::GCObject
 		{
 			// weak reference to the subscriber DomainEnv so
 			// multiple DomainEnvs subscribing to the same
 			// ByteArray don't result in a DomainEnv not being
 			// collectable because a ByteArray refers to it and
 			// is referenced by another live DomainEnv
 			MMgc::GCWeakRef* weakSubscriber;
 			// next link
 			SubscriberLink* next;
 		};
 		SubscriberLink* m_subscriberRoot;
 
 		void NotifySubscribers();
		void ThrowMemoryError();

		uint32_t m_capacity;
		uint32_t m_length;
		U8 *m_array;

		enum { kGrowthIncr = 4096 };
	};

	class ByteArrayFile : public ByteArray, public DataInput, public DataOutput
	{
	public:
		ByteArrayFile(Toplevel *toplevel);
		virtual ~ByteArrayFile()
		{
			m_filePointer = 0; 
		}

		uint32_t GetFilePointer() { return m_filePointer; }
		void Seek(uint32_t filePointer) { m_filePointer = filePointer; }
		void SetLength(uint32_t newLength);
		uint32_t Available();
		void Read(void *buffer, uint32_t count);
		void Write(const void *buffer, uint32_t count);
		
	private:
		uint32_t m_filePointer;
	};
	
	class ByteArrayObject : public ScriptObject
	{
	public:
		ByteArrayObject(VTable *ivtable, ScriptObject *delegate);

		void fill(const void *b, uint32_t len);
	
		void checkNull(void *instance, const char *name);

		uint32_t getLength() { return m_byteArray.GetLength(); }
		void setLength(uint32_t newLength);

		virtual bool hasAtomProperty(Atom name) const;
		virtual void setAtomProperty(Atom name, Atom value);
		virtual Atom getAtomProperty(Atom name) const;
		virtual Atom getUintProperty(uint32_t i) const;
		virtual void setUintProperty(uint32_t i, Atom value);

		void readBytes(ByteArrayObject *bytes, uint32_t offset, uint32_t length);
		void writeBytes(ByteArrayObject *bytes, uint32_t offset, uint32_t length);

		String* _toString();

		// renamed to avoid preprocessor conflict with mozilla's zlib, which #define's compress and uncompress
		void zlib_compress();
		void zlib_uncompress();

		void writeBoolean(bool value);
		void writeByte(int value);
		void writeShort(int value);
		void writeInt(int value);
		void writeUnsignedInt(uint32_t value);
		void writeFloat(double value);
		void writeDouble(double value);
		void writeUTF(String *value);
		void writeUTFBytes(String *value);
	
		bool readBoolean();
		int readByte();
		int readUnsignedByte();
		int readShort();
		int readUnsignedShort();
		int readInt();
		uint32_t readUnsignedInt();
		double readFloat();
		double readDouble();
		String* readUTF();
		String* readUTFBytes(uint32_t length);		
		
		int get_bytesAvailable();
		int get_position();
		void set_position(int offset);
		inline int available() { return get_bytesAvailable(); }
		inline int getFilePointer() { return get_position(); }
		inline void seek(int offset) { set_position(offset); }

		uint32_t get_length();
		void set_length(uint32_t value);

		Stringp get_endian();
		void set_endian(Stringp type);
		
		ByteArray& GetByteArray() { return m_byteArray; }

		void writeFile(Stringp filename);

		/*virtual*/ GlobalMemoryProvider* getGlobalMemoryProvider() { return &m_byteArray; }

	private:
		MMgc::Cleaner c;
		ByteArrayFile m_byteArray;
		
		DECLARE_SLOTS_ByteArrayObject;
	};

	//
	// ByteArrayClass
	//
	
	class ByteArrayClass : public ClassClosure
	{
    public:
		ByteArrayClass(VTable *vtable);

		ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);

		ByteArrayObject *readFile(Stringp filename);
		
		DECLARE_SLOTS_ByteArrayClass;
    };
}

#endif /* BYTEARRAYGLUE_INCLUDED */
