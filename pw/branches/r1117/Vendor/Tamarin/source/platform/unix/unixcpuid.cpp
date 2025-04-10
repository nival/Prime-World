
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

#ifdef FEATURE_NANOJIT

#if defined(AVMPLUS_IA32)

#define SSE_FLAG  0x02000000		// SSE flag is bit 25 of Feature Flags
#define SSE2_FLAG 0x04000000		// SSE2 flag is bit 26 of Feature Flags

static bool HasCPUIDsupport()
{
	unsigned int f1, f2;
	const unsigned int flag = 0x200000;
	asm("pushfl\n\t"
	    "pushfl\n\t"
	    "popl %0\n\t"
	    "movl %0,%1\n\t"
	    "xorl %2,%0\n\t"
	    "pushl %0\n\t"
	    "popfl\n\t"
	    "pushfl\n\t"
	    "popl %0\n\t"
	    "popfl\n\t"
	    : "=&r" (f1), "=&r" (f2)
	    : "ir" (flag));
	return ((f1^f2) & flag) != 0;
}

static unsigned int GetFeatureFlags()
{
	int dwCPUFeatureFlags = 0x00000000;
	if (HasCPUIDsupport())
	{
		__asm__ (	"pushl %%ebx\n\t"
					"movl $1, %%eax\n\t"
					"cpuid\n\t"	
					"popl %%ebx\n\t"
				  : "=d" (dwCPUFeatureFlags) : "0" (1) : "eax", "ecx", "cc");
	}
	return dwCPUFeatureFlags;
} // GetFeatureFlags()

bool P4Available()
{
	static int checked = 0;
	if ( !checked ) {
		unsigned int dwFeatures = GetFeatureFlags();
		if (dwFeatures & SSE2_FLAG) {
			checked = 2;
			return true;
		}
		checked = 1;
	}
	if ( checked == 2 ) {
		return true;
	}
	return false;
} // P4Available()

#elif defined(AVMPLUS_AMD64)

bool P4Available()
{
	return true;
}

#endif

#endif // FEATURE_NANOJIT
