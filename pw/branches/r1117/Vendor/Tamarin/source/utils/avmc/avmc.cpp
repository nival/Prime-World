/* -*- tab-width: 4 -*- */
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

#include "avmplus.h"
#include "eval.h"

// avmc - ahead-of-time ActionScript compiler based on the eval code in Tamarin.
//
// usage: avmc <actionscript source file> ...

class AvmcHostContext : public avmplus::RTC::HostContext {
public:
	uint8_t* obtainStorageForResult(uint32_t nbytes);
	const wchar* readFileForEval(const wchar* basename, const wchar* filename, uint32_t* inputlen);
	void freeInput(const wchar* input);
	void doubleToString(double d, char* buf, size_t bufsiz);
	bool stringToDouble(const char* s, double* d);
	void throwInternalError(const char* msgz);
	void throwSyntaxError(const char* msgz);
	
	uint8_t* result;
	uint32_t result_size;
};

int fail(const char* fmt, ...);

int main (int argc, char** argv) 
{
	argc > 1 || fail("Usage: avmc <actionscript source file> ...");

	AvmcHostContext context;
	for ( int i=1 ; i < argc ; i++ )
	{
		char* filename = argv[i];
		FILE *fp = fopen(filename, "r");
		fp != NULL || fail("Could not open file for input: %s", filename);
		fseek(fp, 0, SEEK_END) == 0 || fail("Could not seek on input file: %s", filename);
		long int llen = ftell(fp);
		llen >= 0 || fail("Could not seek on input file: %s", filename);
		uint32_t len = (uint32_t)llen;
		fseek(fp, 0, SEEK_SET) == 0 || fail("Could not seek on input file: %s", filename);
		wchar *text = new wchar[len+1];
		text != NULL || fail("Out of memory");
		fread(text, 1, len, fp) == len || fail("Could not read from file: %s\n", filename);
		fclose(fp);
		wchar* wdest = text+len-1;
		char* csrc = (char*)text+len-1;
		while (wdest >= text)
			*wdest-- = *csrc--;
		text[len] = 0;
		wchar* wfilename = new wchar[strlen(filename)+1];
		wfilename != NULL || fail("Out of memory");
		wdest = wfilename;
		csrc = filename;
		while (*wdest++ = *csrc++)
			;
		avmplus::RTC::Compiler compiler(&context, wfilename, text, len+1);
		compiler.compile();
		delete [] text;
		char *dotpos = strrchr(filename, '.');
		if (dotpos && strcmp(dotpos, ".as") == 0)
			*dotpos = 0;
		char outfn[FILENAME_MAX];
		snprintf(outfn, sizeof(outfn), "%s.abc", filename);
		outfn[sizeof(outfn)-1] = 0;
		fp = fopen(outfn, "wb");
		fp != NULL || fail("Could not open file for output: %s\n", outfn);
		fwrite(context.result, 1, context.result_size, fp) == context.result_size || fail("Could not write to output: %s\n", outfn);
		fclose(fp);
		delete [] context.result;
		context.result = NULL;
	}
	return 0;
}

int fail(const char* fmt, ...)
{
    va_list args;
    fprintf(stderr, "Error: ");
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    exit(1);
	/*NOTREACHED*/
    return 0;
}

bool MathUtils::isNaN(double d)
{
	return d != d;
}

uint8_t* AvmcHostContext::obtainStorageForResult(uint32_t nbytes)
{
	result = new uint8_t[nbytes];
	result != NULL || fail("Out of memory");
	result_size = nbytes;
	return result;
}

const wchar* AvmcHostContext::readFileForEval(const wchar* basename, const wchar* filename, uint32_t* inputlen)
{
	throwInternalError("No support for 'include' yet");
	/*NOTREACHED*/
	return NULL;
}

void AvmcHostContext::freeInput(const wchar* input)
{
	throwInternalError("No support for 'include' yet");
}

void AvmcHostContext::doubleToString(double d, char* buf, size_t bufsiz)
{
	snprintf(buf, bufsiz, "%f", d);		// not sure about this
	buf[bufsiz-1] = 0;
}

bool AvmcHostContext::stringToDouble(const char* s, double* d)
{
	*d = strtod(s, NULL);
	return true;
}

void AvmcHostContext::throwInternalError(const char* msgz)
{
	fprintf(stderr, "%s", msgz);
	exit(1);
}

void AvmcHostContext::throwSyntaxError(const char* msgz)
{
	fprintf(stderr, "%s", msgz);
	exit(1);
}

