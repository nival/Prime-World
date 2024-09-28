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


#include "avmplus.h"

#include "pcre.h"

// todo figure out what to do about all the new/delete in here
// todo general clean-up

namespace avmplus
{
	using namespace MMgc;


	class PcreState {
	public:
		PcreState(Toplevel* t) { AvmCore::setPCREContext(t); }
		~PcreState() { AvmCore::setPCREContext(NULL); }
	};
	
#define PCRE_STATE(x) PcreState p(x)

#define OVECTOR_SIZE 99 // 32 matches = (32+1)*3

	// This variant is only used for creating the prototype
	RegExpObject::RegExpObject(RegExpClass *regExpClass, 
							   ScriptObject *objectPrototype)
		: ScriptObject(regExpClass->ivtable(), objectPrototype)
	{
		AvmAssert(traits()->getSizeOfInstance() == sizeof(RegExpObject));

		GC::SetFinalize(this);

		int			errptr;
		const char	*error;
		AvmCore		*core = this->core();
		m_optionFlags = PCRE_UTF8;
		m_hasNamedGroups = false;
		m_source = core->newConstantStringLatin1("(?:)");

		StUTF8String utf8Pattern(m_source);
		PCRE_STATE(toplevel());
		m_pcreInst = (void*)pcre_compile(utf8Pattern.c_str(), m_optionFlags, &error, &errptr, NULL );
	}

	RegExpObject::RegExpObject(RegExpObject *toCopy)
		: ScriptObject(toCopy->vtable, toCopy->getDelegate()), m_source(toCopy->m_source.value())
	{
		AvmAssert(traits()->getSizeOfInstance() == sizeof(RegExpObject));

		GC::SetFinalize(this);

		// m_source = toCopy->m_source; -- no, now done in the initializer list above
		m_global = toCopy->m_global;
		m_lastIndex = 0;
		m_optionFlags = toCopy->m_optionFlags;
		m_hasNamedGroups = toCopy->m_hasNamedGroups;

		StUTF8String utf8Pattern(m_source);
		int errptr;
		const char *error;
		PCRE_STATE(toplevel());
		m_pcreInst = (void*)pcre_compile(utf8Pattern.c_str(), m_optionFlags, &error, &errptr, NULL );
	}
		
	RegExpObject::RegExpObject(RegExpClass *type,
							   Stringp pattern,
							   Stringp options)
	   : ScriptObject(type->ivtable(), type->prototype), m_source(pattern)
	{
		AvmAssert(traits()->getSizeOfInstance() == sizeof(RegExpObject));
		// m_source = pattern;  -- no, now done in the initializer list above

		GC::SetFinalize(this);
		
		m_lastIndex = 0;
		m_global = false;
		int errptr;
		const char *error;

		m_optionFlags = PCRE_UTF8;

		StUTF8String utf8Pattern(pattern);

		// Check for named groups and embedded options if optionStr is NULL. ( Needed to handle
		//  new RegExp( existingRegExpValue.toString() ) )
		const char *ptr = utf8Pattern.c_str();
		StUTF8String optionUTF8(options);
		const char* optionStr = options ? optionUTF8.c_str() : NULL;

		m_hasNamedGroups = false;
		int numSlashSeen = 0;

		while (*ptr) {
			if (ptr[0] == '(' &&
				ptr[1] == '?' &&
				ptr[2] == 'P' &&
				ptr[3] == '<')
			{
				m_hasNamedGroups = true;
			}
			else if (optionStr == NULL && ptr[0] == '/' && (ptr == utf8Pattern.c_str() || ptr[-1] != '\\') && numSlashSeen++ > 0)
			{
				optionStr = ptr;
			}
					
			ptr++;
		}

		// check options
		if (optionStr)
		{		
			for(; *optionStr; optionStr++)
			{
				switch(*optionStr)
				{
				case 'g':
					m_global = true;
					break;
				case 'i':
					m_optionFlags |= PCRE_CASELESS;
					break;
				case 'm':
					m_optionFlags |= PCRE_MULTILINE;
					break;
				case 's':
					m_optionFlags |= PCRE_DOTALL;
					break;
				case 'x':
					m_optionFlags |= PCRE_EXTENDED;
					break;
				}
			}
		}

		PCRE_STATE(toplevel());
		
		m_pcreInst = (void*)pcre_compile(utf8Pattern.c_str(), m_optionFlags, &error, &errptr, NULL );
		// FIXME: make errors available to actionscript
	}

	RegExpObject::~RegExpObject()
	{
		PCRE_STATE(toplevel());
		(pcre_free)((void*)(pcre*)m_pcreInst);
		m_global = false;
		m_lastIndex = 0;
		m_optionFlags = 0;
		m_hasNamedGroups = false;
		m_pcreInst = NULL;
	}
		
	// this = argv[0]
	// arg1 = argv[1]
	// argN = argv[argc]
	Atom RegExpObject::call(int argc, Atom *argv)
	{
		// this call occurs when a regexp object is invoked directly as a function ala "/a|b/('dcab')"
		AvmCore *core = this->core();
		Atom inAtom = argc ? core->string(argv[1])->atom() : core->kEmptyString->atom();
		return AS3_exec(core->atomToString(inAtom));
	}

    /**
     * read a string.  No resource table stuff here, caller must take care of it.
     * @param code
     * @return
     */
    Atom RegExpObject::stringFromUTF8(const char* buffer, int len)
    {
		AvmAssert(len >= 0);
		return core()->newStringUTF8(buffer, len)->atom();
    }

	int RegExpObject::search(Stringp subject)
	{
		int matchIndex, matchLen;
		StIndexableUTF8String utf8Subject(subject);
		if (!_exec(subject, utf8Subject, 0, matchIndex, matchLen))
		{
			matchIndex = -1;
		}
		else
		{
			matchIndex = utf8Subject.toIndex(matchIndex);
		}
		return matchIndex;
	}
	
	int RegExpObject::numBytesInUtf8Character(const uint8 *in)
	{
		unsigned int c = *in;
		switch(c>>4)
		{
			case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			default:
				// 0xxx xxxx
				return 1;
			case 12: case 13:
				// 110xxxxx   10xxxxxx
				return 2;
			case 14:
				// 1110xxxx  10xxxxxx  10xxxxxx
				return 3;
			case 15:
				// 11110xxx  10xxxxxx  10xxxxxx  10xxxxxx
				return 4;
		}
	}


	ArrayObject* RegExpObject::split(Stringp subject, uint32 limit)
	{
		ArrayObject *out = toplevel()->arrayClass->newArray();
		StIndexableUTF8String utf8Subject(subject);

		int startIndex=0;
		int matchIndex;
		int matchLen;
		ArrayObject* matchArray;
		unsigned n=0;
		bool isEmptyRE = m_source->length() == 0;
		while ((matchArray = _exec(subject,
								  utf8Subject,
								  startIndex,
								  matchIndex,
								  matchLen)) != NULL)
		{
			// [cn 11/22/04] when match is made, but is length 0 we've matched the empty
			//  position between characters.  Although we've "matched", its zero length so just break out.
			if (matchLen == 0 ) {
				matchLen = 0;
				matchIndex = startIndex+numBytesInUtf8Character((uint8*)(utf8Subject.c_str())+startIndex); // +1char  will advance startIndex, extract just one char
				if( !isEmptyRE )
				{
					// don't break if we're processing an empty regex - then we want to split the string into each character
					// so we want the loop to continue
					break;
				}
			}

			//[ed 8/10/04] don't go past end of string. not sure why pcre doesn't return null
			//for a match starting past the end.
			//[cn 12/3/04] because a regular expression which matches an empty position (space between characters)
			//  will match the empty position just past the last character.  This test is correct, though 
			//  it needs to come before we do any setProperties to avoid a bogus xtra result.
			if (matchIndex+matchLen > utf8Subject.length()) {
				startIndex = matchIndex+matchLen;
				break;
			} else {
				out->setUintProperty(n++, stringFromUTF8(utf8Subject.c_str()+startIndex, matchIndex-startIndex));
				if (n >= limit)
					break;
				for (uint32 j=1; j<matchArray->getLength(); j++) {
					out->setUintProperty(n++, matchArray->getUintProperty(j));
					if (n >= limit)
						break;
				}
				// Advance past this match
				startIndex = matchIndex+matchLen;				
			}
		}

		// If we found no match, or we did find a match and are still under limit, and there is a remainder left, add it 
		if ((unsigned)n < limit && startIndex <= utf8Subject.length()) {
			out->setUintProperty(n++, stringFromUTF8(utf8Subject.c_str()+startIndex, utf8Subject.length()-startIndex));
		}

		return out;
	}
	
	Atom RegExpObject::AS3_exec(Stringp subject)
	{
		if (!subject)
		{
			subject = core()->knull;
		}
		StIndexableUTF8String utf8Subject(subject);
		ArrayObject *result = _exec(subject, utf8Subject);
		return result ? result->atom() : nullStringAtom;
	}

	ArrayObject* RegExpObject::_exec(Stringp subject, StIndexableUTF8String& utf8Subject)
	{
		AvmAssert(subject != NULL);

		int matchIndex = 0, matchLen = 0;
		int startIndex = (get_global() ? utf8Subject.toUtf8Index(m_lastIndex) : 0);

		ArrayObject* result = _exec(subject,
								   utf8Subject,
								   startIndex,
								   matchIndex,
								   matchLen);
		if (get_global())
		{
			m_lastIndex = utf8Subject.toIndex(matchIndex+matchLen);
		}

		return result;
	}

    ArrayObject* RegExpObject::_exec(Stringp subject, 
									StIndexableUTF8String& utf8Subject,
									int startIndex,
									int& matchIndex,
									int& matchLen)
	{
		AvmAssert(subject != NULL);
		
		int ovector[OVECTOR_SIZE];
		int results;
		int subjectLength = utf8Subject.length();

		PCRE_STATE(toplevel());
		if( startIndex < 0 ||
			startIndex > subjectLength ||
			(results = pcre_exec((pcre*)m_pcreInst,
								NULL,
								utf8Subject.c_str(),
								subjectLength,
								startIndex,
								PCRE_NO_UTF8_CHECK,
								ovector,
								OVECTOR_SIZE)) < 0)
		{
			matchIndex = 0;
			matchLen = 0;
			return NULL;
		}

		AvmCore *core = this->core();
		ArrayObject *a = toplevel()->arrayClass->newArray(results);

		a->setAtomProperty(toplevel()->regexpClass()->kindex->atom(),
			   core->intToAtom(utf8Subject.toIndex(ovector[0])));
		a->setAtomProperty(toplevel()->regexpClass()->kinput->atom(),
			   subject->atom());
		a->setLength(results);

		// set array slots
		for (int i=0; i<results; i++) {
			if (ovector[i*2] > -1) {
				int length = ovector[i*2 + 1] - ovector[i*2];
				Atom match = stringFromUTF8(utf8Subject.c_str()+ovector[i*2], length);
				a->setUintProperty(i, match);
			} else {
				a->setUintProperty(i, undefinedAtom);
			}
		}

		// handle named groups
		if (m_hasNamedGroups)
		{
			int entrySize;
			pcre_fullinfo((pcre*)m_pcreInst, NULL, PCRE_INFO_NAMEENTRYSIZE, &entrySize);
	 
			int nameCount;
			pcre_fullinfo((pcre*)m_pcreInst, NULL, PCRE_INFO_NAMECOUNT, &nameCount);
	 
			// this space is freed when (pcre*)m_pcreInst is freed 
			char *nameTable;
			pcre_fullinfo((pcre*)m_pcreInst, NULL, PCRE_INFO_NAMETABLE, &nameTable);
	 
			/* nameTable is a series of fixed length entries (entrySize) 
			   the first two bytes are the index into the ovector and the result
			   is a null terminated string (the subgroup name) */
			for (int i = 0; i < nameCount; i++)
			{
				int nameIndex, length;
				nameIndex = (nameTable[0] << 8) + nameTable[1];
				length = ovector[nameIndex * 2 + 1] - ovector[ nameIndex * 2 ];

				Atom name = stringFromUTF8((nameTable+2), (uint32)VMPI_strlen(nameTable+2));
				name = core->internString(name)->atom();

				Atom value = stringFromUTF8(utf8Subject.c_str()+ovector[nameIndex*2], length);

				a->setAtomProperty(name, value);

				nameTable += entrySize;
			}
		}
		
		matchIndex = ovector[0];
		matchLen = ovector[1]-ovector[0];

		return a;
	}

	ArrayObject* RegExpObject::match(Stringp subject)
	{
		StIndexableUTF8String utf8Subject(subject);
		if (!get_global())
		{
			return _exec(subject, utf8Subject);
		}
		else
		{
			ArrayObject *a = toplevel()->arrayClass->newArray();

			int oldLastIndex = m_lastIndex;
			m_lastIndex = 0;

			int n = 0;

			ArrayObject* matchArray;
			while (true)
			{
				int last = m_lastIndex;
				int matchIndex = 0, matchLen = 0;
				int startIndex = utf8Subject.toUtf8Index(m_lastIndex);

				matchArray = _exec(subject,
								  utf8Subject,
								  startIndex,
								  matchIndex,
								  matchLen);
				m_lastIndex = utf8Subject.toIndex(matchIndex+matchLen);
				
				if ((matchArray == NULL) || (last == m_lastIndex))
					break;
				a->setUintProperty(n++, matchArray->getUintProperty(0));
			}
			
			if (m_lastIndex == oldLastIndex)
			{
				m_lastIndex++;
			}
			
			return a;
		}
	}
	
#define NUM_MATCHES 100

	Atom RegExpObject::replace(Stringp subject,
							   Stringp replacement)
	{
		StUTF8String utf8Subject(subject);
		StUTF8String utf8Replacement(replacement);

		int ovector[OVECTOR_SIZE];
		int subjectLength = utf8Subject.length();
		int lastIndex=0;

		StringBuffer resultBuffer(core());

		const char *src = utf8Subject.c_str();
		
		PCRE_STATE(toplevel());

		// get start/end index of all matches
		int matchCount;
		while (lastIndex <= subjectLength &&
			   (matchCount = pcre_exec((pcre*)m_pcreInst, NULL, (const char*)src,
			   subjectLength, lastIndex, PCRE_NO_UTF8_CHECK, ovector, OVECTOR_SIZE)) > 0)
		{
			int captureCount = matchCount-1;
			
			int matchIndex = ovector[0];
			int matchLen   = ovector[1]-ovector[0];
			
			// copy in stuff leading up to match
			resultBuffer.write(src+lastIndex, matchIndex-lastIndex);

			const char *ptr = utf8Replacement.c_str();
			while (*ptr) {
				if (*ptr == '$') {
					switch (*(ptr+1)) {
					case '$':
						resultBuffer << '$';
						ptr += 2;
						break;
					case '&':
						resultBuffer.write(src+matchIndex, matchLen);
						ptr += 2;
						break;
					case '`':
						resultBuffer.write(src, matchIndex);
						ptr += 2;
						break;
					case '\'':
						resultBuffer << src+ovector[1];
						ptr += 2;
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						{
							int i;
							if (*(ptr+2) >= '0' && *(ptr+2) <= '9') {
								int j = 10*(ptr[1]-'0')+(ptr[2]-'0');
								if (j > captureCount) {
									// Gobbling up two digits would overflow the
									// capture count, so just use the one digit.
									i = ptr[1]-'0';
								} else {
									i = j;
								}
							} else {
								i = ptr[1]-'0';
							}
							if (i >= 1 && i <= captureCount) {
								resultBuffer.write(src+ovector[i*2],
												   ovector[i*2+1]-ovector[i*2]);
								ptr += (i >= 10) ? 3 : 2;								
							} else {
								resultBuffer << *ptr++;
							}
						}
						break;
					default:
						resultBuffer << *ptr++;
						break;
					}
				} else {
					resultBuffer << *ptr++;
				}
			}
			
			int newLastIndex = ovector[0] + (ovector[1] - ovector[0]);

			// prevents infinite looping in certain cases
			fixReplaceLastIndex(src,
								subjectLength,
								matchLen,
								newLastIndex,
								resultBuffer);

			lastIndex = newLastIndex;

			if (!get_global())
			{
				break;
			}
		}

		// copy in stuff after last match
		if (lastIndex < subjectLength)
		{
			resultBuffer.write(src+lastIndex, subjectLength-lastIndex);
		}

		return stringFromUTF8((const char*)resultBuffer.c_str(), resultBuffer.length());
	}

	Atom RegExpObject::replace(Stringp subject,
							   ScriptObject* replaceFunction)
	{
		StUTF8String utf8Subject(subject);

		int ovector[OVECTOR_SIZE];
		int subjectLength = utf8Subject.length();
		int lastIndex=0;

		StringBuffer resultBuffer(core());

		const char *src = utf8Subject.c_str();
		
		PCRE_STATE(toplevel());

		// get start/end index of all matches
		int matchCount;
		while (lastIndex < subjectLength &&
			   (matchCount = pcre_exec((pcre*)m_pcreInst, NULL, (const char*)src,
						 subjectLength, lastIndex, PCRE_NO_UTF8_CHECK, ovector, OVECTOR_SIZE)) > 0)
		{
			int captureCount = matchCount-1;
			
			int matchIndex = ovector[0];
			int matchLen   = ovector[1]-ovector[0];
			
			// copy in stuff leading up to match
			resultBuffer.write(src+lastIndex, matchIndex-lastIndex);

			// call the replace function
			Atom argv[NUM_MATCHES+4];
			int argc = captureCount+3;

			argv[0] = undefinedAtom;

			// ECMA 15.5.4.11: Argument 1 is the substring that matched.
			argv[1] = stringFromUTF8(src+matchIndex, matchLen);

			// ECMA 15.5.4.11: The next m arguments are all of the captures in the
			// MatchResult
			for (int i=1; i<=captureCount; i++)
			{
				argv[i+1] = stringFromUTF8(src+ovector[i*2], ovector[i*2+1]-ovector[i*2]);
			}

			// ECMA 15.5.4.11: Argument m+2 is the offset within string
			// where the match occurred
			argv[captureCount+2] = core()->uintToAtom(matchIndex);

			// ECMA 15.5.4.11: Argument m+3 is string
			argv[captureCount+3] = subject->atom();

			resultBuffer << core()->string(toplevel()->op_call(replaceFunction->atom(),
															   argc, argv));
			
			int newLastIndex = ovector[0] + (ovector[1] - ovector[0]);

			// prevents infinite looping in certain cases
			fixReplaceLastIndex(src,
								subjectLength,
								matchLen,
								newLastIndex,
								resultBuffer);

			lastIndex = newLastIndex;

			if (!get_global())
				break;
		}

		// copy in stuff after last match
		if (lastIndex < subjectLength)
		{
			resultBuffer.write(src+lastIndex, subjectLength-lastIndex);
		}

		return stringFromUTF8((const char*)resultBuffer.c_str(), resultBuffer.length());
	}

	void RegExpObject::fixReplaceLastIndex(const char *src,
										   int subjectLength,
										   int matchLen,
										   int& newLastIndex,
										   StringBuffer& resultBuffer)
	{
		if (matchLen == 0 && get_global())
		{
			// Advance one character
			if (newLastIndex < subjectLength)
			{
				uint32 ch;
				int n = UnicodeUtils::Utf8ToUcs4((const uint8*)src+newLastIndex, subjectLength-newLastIndex, &ch);
				if (n <= 0)
				{
					// Invalid UTF8 sequence, advance one byte
					n = 1;
				}
				resultBuffer.write(src+newLastIndex, n);
				newLastIndex += n;
			}
			else
			{
				newLastIndex++;
			}
		}
	}
	
	//
	// Accessors
	//

	bool RegExpObject::get_ignoreCase() { return hasOption(PCRE_CASELESS); }
	bool RegExpObject::get_multiline() { return hasOption(PCRE_MULTILINE); }
	bool RegExpObject::get_dotall() { return hasOption(PCRE_DOTALL); }
	bool RegExpObject::get_extended() { return hasOption(PCRE_EXTENDED); }

}
