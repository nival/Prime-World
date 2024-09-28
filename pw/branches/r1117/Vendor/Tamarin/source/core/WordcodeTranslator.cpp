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

namespace avmplus
{
#ifdef SUPERWORD_PROFILING
	// 32-bit only

	static FILE *swprof_code_fp = NULL;
	static FILE *swprof_sample_fp = NULL;
#ifdef SUPERWORD_LIMIT
	static unsigned int sample_count = 0;
#endif

	void WordcodeTranslator::swprofStart()
	{
		swprof_code_fp = fopen("superwordprof_code.txt", "wb");
		if (swprof_code_fp == NULL)
			AvmLog("SUPERWORD PROFILING: COULD NOT OPEN CODE FILE.\n");
		else
		{
			unsigned int signature = 0xC0DEC0DE;
			fwrite(&signature, sizeof(uint32_t), 1, swprof_code_fp);
		}
		swprof_sample_fp = fopen("superwordprof_sample.txt", "wb");
		if (swprof_sample_fp == NULL)
			AvmLog("SUPERWORD PROFILING: COULD NOT OPEN SAMPLE FILE.\n");
		else
		{
			unsigned int signature = 0xDA1ADA1A;
			fwrite(&signature, sizeof(uint32_t), 1, swprof_sample_fp);
		}
	}
	
	void WordcodeTranslator::swprofStop() 
	{
		if (swprof_code_fp != NULL)	{ fclose(swprof_code_fp); swprof_code_fp = NULL; }
		if (swprof_sample_fp != NULL) { fclose(swprof_sample_fp); swprof_sample_fp = NULL; }
	}
			
	void WordcodeTranslator::swprofCode(const uint32_t* start, const uint32_t* limit)
	{
		if (swprof_code_fp != NULL) {
			fwrite(&start, sizeof(uint32_t*), 1, swprof_code_fp);
			fwrite(&limit, sizeof(uint32_t*), 1, swprof_code_fp);
			fwrite(start, sizeof(uint32_t), limit-start, swprof_code_fp);
			fflush(swprof_code_fp);
		}
	}

	void WordcodeTranslator::swprofPC(const uint32_t* pc)
	{
		if (swprof_sample_fp != NULL) {
			fwrite(&pc, sizeof(uint32_t*), 1, swprof_sample_fp);
#ifdef SUPERWORD_LIMIT
			if (++sample_count == SUPERWORD_LIMIT) {
				swprofStop();
				AvmLog("SAMPLING HALTED.\n");
			}
#endif
		}
	}
#endif  // SUPERWORD_PROFILING
}
