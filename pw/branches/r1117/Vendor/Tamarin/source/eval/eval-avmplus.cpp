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

#include "avmplus.h"

#ifdef VMCFG_EVAL

#include "eval.h"

namespace avmplus
{
	class AvmplusHostContext : public RTC::HostContext 
	{
	public:
		AvmplusHostContext(AvmCore* core, Toplevel* toplevel)
			: core(core)
			, toplevel(toplevel)
			, nextstring(0)
		{
		}

		uint8_t* obtainStorageForResult(uint32_t nbytes);
		const wchar* readFileForEval(const wchar* basename, const wchar* filename, uint32_t* inputlen);
		void   freeInput(const wchar* input);
		void doubleToString(double d, char* buf, size_t bufsiz);
		bool stringToDouble(const char* s, double* d);
		void throwInternalError(const char* msgz);
		void throwSyntaxError(const char* msgz);
		
		ScriptBuffer script_buffer;

	private:
		AvmCore* const core;
		Toplevel* const toplevel;
		wchar* strings[10];
		int nextstring;
	};
	
	uint8_t* AvmplusHostContext::obtainStorageForResult(uint32_t nbytes)
	{
		script_buffer = core->newScriptBuffer(nbytes);
		return script_buffer.getBuffer();
	}
	
	const wchar* AvmplusHostContext::readFileForEval(const wchar* basename, const wchar* filename, uint32_t* inputlen)
	{
		// FIXME: the mismatch between what eval needs and what the core API delivers is just stunning. 
		if (nextstring == sizeof(strings)/sizeof(strings[0]))
			throwInternalError("includes too deeply nested");
		StUTF16String str(core->readFileForEval(core->newStringUTF16(basename), core->newStringUTF16(filename)));	// return value is already NUL-terminated
		wchar *s = new wchar[str.length()];
		memcpy(s, str.c_str(), str.length()*sizeof(wchar));
		*inputlen = str.length();
		strings[nextstring++] = s;
		return s;
	}
	
	void AvmplusHostContext::freeInput(const wchar* input)
	{
		int i=0;
		while (i < nextstring && strings[i] != input)
			i++;
		if (i == nextstring) {
			AvmAssert(!"Bug in eval - freeing unallocated input");
			return;
		}
		delete [] strings[i];
		while (i < nextstring-1) {
			strings[i] = strings[+1];
			i++;
		}
		nextstring--;
	}
	
	void AvmplusHostContext::doubleToString(double d, char* buf, size_t bufsiz)
	{
		StUTF8String s(MathUtils::convertDoubleToString(core, d));
		strncpy(buf, s.c_str(), bufsiz);
		buf[bufsiz-1] = 0;
	}

	bool AvmplusHostContext::stringToDouble(const char* s, double* d)
	{
		return MathUtils::convertStringToDouble(core->newStringLatin1(s), d, false);
	}

	void AvmplusHostContext::throwSyntaxError(const char* msgz)
	{
		Atom error_args[3] = { nullObjectAtom, core->newStringUTF8(msgz)->atom(), core->intToAtom(0) };	// FIXME - proper error ID?
		core->throwAtom(toplevel->syntaxErrorClass()->construct(2, error_args));
	}
	
	void AvmplusHostContext::throwInternalError(const char* msgz)
	{
		Atom error_args[3] = { nullObjectAtom, core->newStringUTF8(msgz)->atom(), core->intToAtom(0) };	// FIXME - proper error ID?
		core->throwAtom(toplevel->errorClass()->construct(2, error_args));
	}
	
	ScriptBuffer compileProgram(AvmCore* core, Toplevel* toplevel, String* code, String* filename)
	{
		AvmplusHostContext context(core, toplevel);
		StUTF16String src(code);
		StUTF16String fn(filename);
		AvmAssert(src.c_str()[src.length()-1] == 0);
		RTC::Compiler compiler(&context, filename == NULL ? NULL : fn.c_str(), src.c_str(), src.length());
		TRY(core, kCatchAction_Rethrow) {
			compiler.compile();
			return context.script_buffer;
		}
		CATCH(Exception *exception) {
			compiler.destroy();
			core->throwException(exception);
			/*NOTREACHED*/
		again:
			goto again;
		}
		END_CATCH
		END_TRY
	}
}

#endif // VMCFG_EVAL
