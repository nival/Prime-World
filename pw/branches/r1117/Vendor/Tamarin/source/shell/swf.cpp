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
 * Portions created by the Initial Developer are Copyright (C) 2009
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
	// it's silly to write this again, but i'm being lazy.
	class SwfParser {
		int bitPos;
		int bitBuf;
	public:
		ScriptBuffer swf;
		uint32_t pos;
		SwfParser(ScriptBuffer swf)
			: bitPos(0)
			, bitBuf(0)
			, swf(swf)
			, pos(0)
		{
		}

		void skipHeader() {
			// skip rect
			int n = readUBits(5);
			readUBits(n); // xmin
			readUBits(n); // xmax
			readUBits(n); // ymin
			readUBits(n); // ymax

			// skip frame rate and frame count
			pos += 4;
		}

		int readU8() {
			return swf[pos++];
		}
		int readU16() {
			return readU8() | readU8()<<8;
		}
		uint32_t readU32() {
			return readU8() | readU8()<<8 | readU8()<<16 | readU8()<<24;
		}

		void fillBitBuf() {
			bitBuf = readU8();
			bitPos = 8;
		}

		int readUBits(int n) {
			if (n == 0)
				return 0;
			int bitsLeft = n;
			int result = 0;
			if (!bitPos)
				fillBitBuf();
			int shift;
			for (shift = bitsLeft - bitPos; shift > 0; shift = bitsLeft - bitPos) {
				result |= bitBuf << shift;
				bitsLeft -= bitPos;
				fillBitBuf();
			}
			// consume part of buffer
			result |= bitBuf >> -shift;
			bitPos -= bitsLeft;
			bitBuf &= 0xff >> (8 - bitPos); // mask consumed bits
			return result;
		}

		int readSBits(int n) {
			AvmAssert(n <= 32);
			int num = readUBits(n);
			int shift = 32 - n;
			return (num << shift) >> shift; // sign extend
		}

		void skipString() {
			while (readU8() != 0)
			{}
		}
	};

	/**
	 * isSwf() - return true if the swf magic # is present, ignoring version.
	 */
	bool isSwf(ScriptBuffer swf) {
		if (swf.getSize() < 4)
			return false;
		uint32_t magic = swf[0] | swf[1]<<8 | swf[2]<<16;
		const uint32_t SWF = 'S'<<16 | 'W'<<8 | 'F';
		const uint32_t SWC = 'S'<<16 | 'W'<<8 | 'C';
		return magic == SWF || magic == SWC;
	}

	void handleDoABC2(SwfParser &parser, int taglen,
						  DomainEnv* domainEnv, Toplevel*& toplevel, CodeContext* codeContext)
	{
		MMgc::GC *gc = toplevel->gc();
		AvmCore *core = toplevel->core();
		int tagstart = parser.pos;
		const int kDoAbcLazyInitializeFlag = 1;

		// Flags (UI32) A 32-bit flags value, which may
		// contain the following bits set: kDoAbcLazyInitializeFlag = 1: Indicates that
		// the ABC block should not be executed immediately, but only parsed. A later
		// finddef may cause its scripts to execute.
		uint32_t flags = parser.readU32();

		// skip the abc name
		parser.skipString();

		// parse and execute the abc.
		int abclen = taglen - (parser.pos - tagstart);
		ReadOnlyScriptBufferImpl* abcbuf = new (gc) ReadOnlyScriptBufferImpl(&parser.swf[parser.pos], abclen);
		ScriptBuffer code(abcbuf);

		// FIXME get this from the SWF
		uint32_t api = core->getAPI(NULL);
		if (flags & kDoAbcLazyInitializeFlag) {
			core->parseActionBlock(code, 0, toplevel, domainEnv->domain(), NULL, api);
		} else {
			core->handleActionBlock(code, 0, domainEnv, toplevel, NULL, codeContext, api);
		}
		parser.pos += abclen;
	}

	static const int stagDoABC2 = 82;

	/*
	 * Execute a swf as follows:
	 * skip the header
	 * for each DoABC2 tag
	 *   if lazy, parse it but don't run it:  parseActionBlock()
	 * else
	 *   run it via handleActionBlock() just as if it were on the commandline
	 */
	void handleSwf(const char *filename, ScriptBuffer swf, DomainEnv* domainEnv,
			  Toplevel*& toplevel, CodeContext* codeContext)
	{
		SwfParser parser(swf);
		parser.pos = 4; // skip magic #
		uint32_t swflen = parser.readU32();
		AvmCore *core = toplevel->core();
		if (swf[0] == 'C') {
			// decompress the swf
			MMgc::GC *gc = toplevel->gc();
			swflen -= 8;
			BasicScriptBufferImpl* newswfbuf = new (gc, swflen) BasicScriptBufferImpl(swflen);
			ScriptBuffer newswf(newswfbuf);
			uLongf dlen = swflen;
			int e = uncompress((Bytef*)&newswf[0], &dlen, (Bytef*)&swf[8], (uLongf)swf.getSize()-8);
			if (e != Z_OK) {
				core->console << filename << ": error decompressing body: " << e << "\n";
				return;
			}
			swf = newswf;
			parser = SwfParser(newswf);
			parser.pos = 0;
		}
		if (swflen != swf.getSize()) {
			core->console << filename <<
				": incorrect size: " << (uint32_t)swf.getSize() <<
				" should be " << swflen << "\n";
			return;
		}
		parser.skipHeader();
		while (parser.pos < swflen) {
			int tag = parser.readU16();
			int type = tag >> 6;
			uint32_t taglen = (tag & 63);
			if (taglen == 63)
				taglen = parser.readU32();
			if (type == stagDoABC2)
				handleDoABC2(parser, taglen, domainEnv, toplevel, codeContext);		
			else
				parser.pos += taglen;
		}
	}
}
