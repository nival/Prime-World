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
 * Portions created by the Initial Developer are Copyright (C) 2007-2008
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
/**
   File Name:    unshift.as
   Description:  unshift(object,...items)
     inserts the values in items as new vector elements at the start of object, such
     that their order within the vector elements of object is the same as the order in which
     they appear in items. Existing vector elements in object are shifted upward in the index range
     and the length property of object is updated.
   *
   */
var SECTION="";
var VERSION = "ECMA_1";

startTest();

writeHeaderToLog( " Vector.unshift()");

var v1=new Vector.<int>();
v1.unshift();
AddTestCase(
		"unshift empty vector with no items still empty",
		"",
		v1.toString());
var v1=new Vector.<int>();
v1.unshift(10);
AddTestCase(
		"unshift empty vector with single item",
		"10",
		v1.toString());

var v1=new Vector.<int>();
v1[0]=10;
v1.unshift(11);
AddTestCase(
		"unshift single element vector with single item",
		"11,10",
		v1.toString());

var v1=new Vector.<int>();
for (var i=0;i<10;i++) v1[i]=i;
v1.unshift(11);
AddTestCase(
		"unshift small vector with single item",
		"11,0,1,2,3,4,5,6,7,8,9",
		v1.toString());

var v1=new Vector.<int>(3,true);
v1[0]=10; v1[1]=11; v1[2]=12;
var errormsg="";
try {
  v1.unshift(9);
} catch (e) {
  errormsg=e.toString();
}
AddTestCase(
		"unshift single element vector with single item",
		"RangeError: Error #1126",
		parseError(errormsg,"RangeError: Error #1126".length));

// bug: https://bugzilla.mozilla.org/show_bug.cgi?id=469377
var strVector = new Vector.<String>;
strVector.push("Carol", "Justine");
strVector.unshift("Betty");
AddTestCase(
    "Vector.<String>.unshift()",
    "Betty,Carol,Justine",
    strVector.toString());

test();
