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
 * Portions created by the Initial Developer are Copyright (C) 1993-2006
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

#define avmplus_stringify2(x)     # x
#define avmplus_stringify(x)      avmplus_stringify2(x)

// The visible build code: d(evelopment) or r(elease candidate), followed by an identifying string.
//
// This string is used by QE, the build system replaces the string in this header file
// with the correct value before compilation.  Do not change this.
#define AVMPLUS_BUILD_CODE			"cyclone"

#ifdef DEBUGGER
#define AVMPLUS_BIN_DEBUGGER_TAG "-debugger"
#else
#define AVMPLUS_BIN_DEBUGGER_TAG ""
#endif

#ifdef DEBUG
#define AVMPLUS_BIN_TYPE_TAG  "debug"
#else
#define AVMPLUS_BIN_TYPE_TAG  "release"
#endif

#define AVMPLUS_BIN_TYPE  AVMPLUS_BIN_TYPE_TAG AVMPLUS_BIN_DEBUGGER_TAG

// A possibly-obsolete build number, not used by the VM itself but
// possibly by embedders.  It is supposed to count 1-n for development
// builds, and restart at 1-n for release builds.
#define AVMPLUS_BUILD_NUMBER		0

// User-facing version numbering.
//
// AVMPLUS_MAJOR_VERSION and AVMPLUS_MINOR_VERSION track the engine generation
// and release number within a generation, respectively.
// 
// AVMPLUS_MAJOR_VERSION is updated when we think it is appropriate to do so
// (major technology change, incompatible API changes maybe, new bytecodes
// maybe).  The rules for this are not set in stone.  It signifies that
// "something important just happened".  We have to just reach a consensus on
// whether something should trigger a change.
// 
// AVMPLUS_MINOR_VERSION is updated on /every/ merge from tamarin-redux
// to tamarin-central and is therefore a serial number for the release.
//
// AVMPLUS_MAJOR_DATE and AVMPLUS_MINOR_DATE reflect the dates of the incrementing
// of the major and minor version numbers, respectively, for the current code.

#define AVMPLUS_MAJOR_VERSION		1				// original open source version
#define AVMPLUS_MAJOR_DATE			"2007-04-01"	// close enough
#define AVMPLUS_MINOR_VERSION		5
#define AVMPLUS_MINOR_DATE			"2009-12-15"

// The simple user-facing version number
#define AVMPLUS_VERSION_USER		avmplus_stringify(AVMPLUS_MAJOR_VERSION) "." avmplus_stringify(AVMPLUS_MINOR_VERSION)

// A more complex user-facing version number
#define AVMPLUS_VERSION_STRING		avmplus_stringify(AVMPLUS_MAJOR_VERSION) "," avmplus_stringify(AVMPLUS_MINOR_VERSION) "," avmplus_stringify(AVMPLUS_BUILD_NUMBER) "," AVMPLUS_BUILD_CODE

// Define Mac only resource change to 'vers' resource so that player installer will
// replace previous player versions
#define AVMPLUS_MAC_RESOURCE_MINOR_VERSION	0x00

