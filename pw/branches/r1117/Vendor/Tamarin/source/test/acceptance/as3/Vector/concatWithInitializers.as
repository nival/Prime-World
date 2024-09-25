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
   File Name:    concat.es
   Description:  The static concat method collects the vector elements from object followed by the vector
    elements from the additional items, in order, into a new vector object.  All the items must be objects.
    returns a new vector object
   */

var SECTION = " ";
var VERSION = "AS3";
startTest();

writeHeaderToLog( SECTION + " Vector.concat()-using-initializers");

var v1=new <uint>[0,1,2];
var v2=new <uint>[3,4,5];
var v3=v1.concat(v2)
AddTestCase(    "concat uint vector, original vector is unchanged",
		"0,1,2",
		v1.toString());
AddTestCase(	"concat uint vector, new vector concat worked",
		"0,1,2,3,4,5",
		v3.toString());

var v1=new <String>["zero","one","two"];
var v2=new <int>[0,1,2];
var errormsg;
try {
  var v3=v1.concat(v2);
} catch (e) {
  errormsg=e.toString();
}
AddTestCase(    "concat two differently typed vectors",
                "TypeError: Error #1034",
                parseError(errormsg,"TypeError: Error #1034".length));
                

var v1=new <uint>[5,6,7,8,9];
var v2=new <int>[0,1,2];
var errormsg;
try {
  var v3=v1.concat(v2);
} catch (e) {
  errormsg=e.toString();
}
AddTestCase(    "concat two differently typed vectors - uint and int",
                "TypeError: Error #1034",
                parseError(errormsg,"TypeError: Error #1034".length));


test();

