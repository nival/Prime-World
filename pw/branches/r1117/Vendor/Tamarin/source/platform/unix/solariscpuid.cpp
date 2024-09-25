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
 *   leon.sha@sun.com
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

#include <stdio.h>
#include <sys/types.h>
#include <sys/elf.h>
#include <sys/fcntl.h>
struct cpuid_get_hwcap {
    char *cgh_archname;
    uint_t cgh_hwcap;
};
#ifndef AV_SPARC_V8PLUS // For OpenSolaris, these were defined
#define AV_SPARC_V8PLUS		0x0008
#define AV_SPARC_VIS		0x0020
#define AV_SPARC_VIS2		0x0040
#endif

#ifndef AV_386_MMX // For OpenSolaris, these were defined
#define AV_386_MMX			0x0040
#define AV_386_AMD_MMX		0x0080
#define AV_386_AMD_3DNow	0x0100
#define AV_386_AMD_3DNowx	0x0200
#define AV_386_SSE			0x0800
#define AV_386_SSE2			0x1000
#define AV_386_SSE3			0x4000
#endif
extern "C" int open(const char *, int, ...);
extern "C" int ioctl(int, int, ...);
extern "C" int close(int);

static unsigned int GetFeatureFlags()
{
	static bool checked = false;
	static unsigned int flag = 0;
	if (checked) return flag;
		
	checked = true;
	static const char dev_cpu_self_cpuid[] = "/dev/cpu/self/cpuid";
#ifdef AVMPLUS_SPARC
	static const char isa[] = "sparc";
#else
	static const char isa[] = "i386";
#endif
	int d = -1;
	d = open(dev_cpu_self_cpuid, O_RDONLY);
	if (d == -1)
	  return 0;

	struct cpuid_get_hwcap __cgh, *cgh = &__cgh;

	cgh->cgh_archname = (char *)isa;
	if (ioctl(d, (('c' << 24) | ('i' << 16) | ('d' << 8) | 0) /* CPUID_GET_HWCAP */,
		cgh) == 0)
	  flag = cgh->cgh_hwcap;

	close(d);

	return flag;
}

bool P4Available()
{
#ifdef AVMPLUS_SPARC
	return false;
#else
	static int checked = 0;
	if ( !checked ) {
		unsigned int dwFeatures = GetFeatureFlags();
		if (dwFeatures & AV_386_SSE2) {
			checked = 2;
			return true;
		}
		checked = 1;
	}
	if ( checked == 2 ) {
		return true;
	}
	return false;
#endif
}
