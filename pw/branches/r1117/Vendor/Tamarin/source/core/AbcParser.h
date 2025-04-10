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

#ifndef __avmplus_AbcParser__
#define __avmplus_AbcParser__


namespace avmplus
{
	/**
	 * Parser for reading .abc (Actionscript Byte Code) files.
	 */
	class AbcParser
	{
	public:
		AbcParser(AvmCore* core, ScriptBuffer code, 
			Toplevel* toplevel,
			Domain* domain,
			const NativeInitializer* natives);

		~AbcParser();

		/**
		 * parse an .abc file
		 * @param code
		 * @return
		 */
		static PoolObject* decodeAbc(AvmCore* core, ScriptBuffer code, 
			Toplevel* toplevel,
			Domain* domain,
			const NativeInitializer* natives,
			API api);

		/** return 0 iff the code starts with a known magic number,
		  * otherwise an appropriate error code.
		  *
		  * Store the magic number in *version if version != NULL
		  */
		static int canParse(ScriptBuffer code, int* version = NULL);

#if defined(VMCFG_AOT) && defined(DEBUGGER)
		static void addAOTDebugInfo(PoolObject *pool);
#endif
		
	protected:
		PoolObject* parse(API api);
		MethodInfo* resolveMethodInfo(uint32 index) const;

		#if defined(VMCFG_AOT) || defined(AVMPLUS_VERBOSE)
		void parseTypeName(const byte* &p, Multiname& m) const;
		#endif

		Namespacep parseNsRef(const byte* &pc) const;
		Stringp resolveUtf8(uint32 index) const;
		Stringp parseName(const byte* &pc) const;
		uint32_t resolveQName(const byte*& pc, Multiname& m) const;
		void computeInstanceSizeAndSlotsOffset(int class_id, Traits* base, uint16_t& sizeofInstance, uint16_t& offsetofSlots) const;
		void parseMethodInfos();
		void parseMetadataInfos();
		bool parseInstanceInfos();
		void parseClassInfos();
		bool parseScriptInfos();
		void parseMethodBodies();
		void parseCpool(API api);
		Traits* parseTraits(uint16_t sizeofInstance,
							uint16_t offsetofSlots,
							Traits* base, 
							Namespacep ns, 
							Stringp name, 
							MethodInfo* script, 
							TraitsPosPtr traitsPos,
							TraitsPosType posType, 
							Namespacep protectedNamespace);
		
		/**
		 * add script to VM-wide table
		 */
		void addNamedScript(NamespaceSetp nss, Stringp name, MethodInfo* script);

		/**
		 * Adds traits to the VM-wide traits table, for types
		 * that can be accessed from multiple abc's.
		 * @param name The name of the class
		 * @param ns The namespace of the class
		 * @param itraits The instance traits of the class
		 */
		void addNamedTraits(Namespacep ns, Stringp name, Traits* itraits);
		void addNamedTraits(NamespaceSetp nss, Stringp name, Traits* itraits);

		/**
		 * reads in 8 bytes in little endian order and stores in
		 * memory as an ieee double, doing endian swapping as needed
		 */
		double readDouble(const byte* &p) const;

        /**
         * Reads in 2 bytes and turns them into a 16 bit number.  Always reads in 2 bytes.  Currently
         * only used for version number of the ABC file and for version 11 support.
         */
		int readU16(const byte* p) const;

        /**
         * Read in a 32 bit number that is encoded with a variable number of bytes.  The value can 
         * take up 1-5 bytes depending on its value.  0-127 takes 1 byte, 128-16383 takes 2 bytes, etc.
         * The scheme is that if the current byte has the high bit set, then the following byte is also
         * part of the value.  
         *
         * Returns the value, and the 2nd argument is set to the number of bytes that were read to get that
         * value.
         */
		int readS32(const byte *&p) const;

		uint32_t readU30(const byte*& p) const;

	// ------------------------ DATA SECTION BEGIN
	private:
		ScriptBuffer				code;
		List<Traits*>				instances;
		Toplevel* const				toplevel;
		Domain* const				domain;
		AvmCore*					core;
		PoolObject*					pool;
		const byte*					pos;
		const NativeInitializer*	natives;
		byte*						abcStart;
		byte*						abcEnd; // one past the end, actually
		Stringp*					metaNames;
		Stringp						kNeedsDxns;
#ifdef AVMPLUS_VERBOSE
		Stringp 					kVerboseVerify;
#endif
		int32_t						version;
		uint32_t					classCount;
	// ------------------------ DATA SECTION END
	};

}

#endif // __avmplus_AbcParser__
