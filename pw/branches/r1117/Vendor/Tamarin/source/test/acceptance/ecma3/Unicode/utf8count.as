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
 * Portions created by the Initial Developer are Copyright (C) 2005-2006
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

var str_utf16_codes = [0x31,
				0x32,
				0x33,
				0xd842,
				0xdf9f,
				0x54a4,
				0x41,
				0x42,
				0x43,
				0xd842,
				0xdfb7,
				0x91ce,
				0x5c4b,
				0x61,
				0x62,
				0x63,
				0x5357,
				0xd87e,
				0xdc84,
				0x99c5];

var str_utf16:String = "";
for each (var c in str_utf16_codes)
	str_utf16 += String.fromCharCode(c);

// note, it's critical that these be embedded as literal utf8 strings to trigger the proper code path
// (constructing via String.fromCharCode won't do the trick)
var str_utf8:String = "123𠮟咤ABC𠮷野屋abc南巽駅";
var str_utf8_a:String = "123𠮟咤ABC";
var str_utf8_b:String = "𠮷野屋abc南巽駅";

var str_utf8_ab:String = str_utf8_a + str_utf8_b;

startTest();

AddTestCase("str_utf8 == str_utf16", true, str_utf8 == str_utf16);
AddTestCase("str_utf8.length == str_utf16.length", true, str_utf8.length == str_utf16.length);
AddTestCase("str_utf8_ab == str_utf8", true, str_utf8_ab == str_utf8);

test();

