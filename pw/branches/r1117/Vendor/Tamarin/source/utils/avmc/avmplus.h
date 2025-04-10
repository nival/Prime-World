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

// replacement for avmplus.h for the eval code.
//
// You also need to define a couple of things on your command line or in your project file:
//
//  __avmplus__        (to prevent core/ActionBlockConstants.cpp from picking up the wrong file)
//  AVMC_STANDALONE    (to make core/ActionBlockConstants.cpp pick up the right file)
//  VMCFG_EVAL         (to enable the evaluator)
//
// We can clean this up by and by by factoring ActionBlockConstants.cpp so that code needed
// by multiple products are included into product-specific files.

#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

// The following represent dependencies that eval makes on avmplus.
// We also depend on the opcode table in ActionBlockConstants.h

typedef uint16_t wchar;

#define AvmAssert assert

#include "../../core/ActionBlockConstants.h"

class MathUtils
{
public:
    static bool isNaN(double x);
};

class MethodInfo
{
public:
	static const int NEED_ARGUMENTS		= 0x00000001;
	static const int NEED_ACTIVATION	= 0x00000002;
	static const int NEED_REST          = 0x00000004;
	static const int HAS_OPTIONAL       = 0x00000008;
	static const int IGNORE_REST        = 0x00000010;
	static const int NATIVE				= 0x00000020;
	static const int SETS_DXNS			= 0x00000040;
	static const int HAS_PARAM_NAMES	= 0x00000080;
};
