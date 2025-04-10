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
   Description:  The elements of this object are converted to strings and
   these strings are then concatenated, separated by comma
   characters. The result is the same as if the built-in join
   method were invoiked for this object with no argument.
   */

var SECTION = "";
var VERSION = "AS3";
startTest();

writeHeaderToLog( SECTION + " Vector.some()-initializers");

function greaterThanTen(item, index, vec):Boolean {
    if (item > 10) {
        return true;
    }
    return false;
}

var errormsg="";
try {
  result=new <int>[].some();
} catch (e) {
  errormsg=e.toString();
}

AddTestCase(
		"some no checker",
		"ArgumentError: Error #1063",
		parseError(errormsg,"ArgumentError: Error #1063".length));

var checker2="a string";
var errormsg="";
try {
  result=new<int>[1,2,3].some(checker2);
} catch (e) {
  errormsg=e.toString();
}
AddTestCase(
		"some checker not a function",
		"TypeError: Error #1034",
		parseError(errormsg,"TypeError: Error #1034".length));

AddTestCase(
    "some empty vector result",
    false,
    new<int>[].some(greaterThanTen));
    
AddTestCase(
    "some vector with no match",
    false,
    new<int>[-3000,2,3,4,5,-1,9, 10].some(greaterThanTen));
    
AddTestCase(
    "some vector with match",
    true,
    new<int>[-3000,2,3,22,4,5,-1,9, 10, 3].some(greaterThanTen));
    
function noReturnValue(item, index, vec) {
    // do nothing
}

AddTestCase(
    "some function with no return value",
    false,
    new<String>['asdf','hello','out','there'].some(noReturnValue));

test();