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
   File Name:    shift.as
   Description:  shift(object)
     removes the element called 0 in object, moves the element at index i+1 to index i,
     and decrements the length property of object by 1.
   *
   */
var SECTION="";
var VERSION = "ECMA_1";

startTest();

writeHeaderToLog( " Vector.shift()");

var v1=new Vector.<int>();
AddTestCase(
		"shift on empty vector returns undefined",
		0,
		v1.shift());
AddTestCase(
		"shift on empty vector original vector is empty",
		"",
		v1.toString());

var v1=new Vector.<int>();
v1.push(10);
AddTestCase(
		"shift on single element vector returns element[0]",
		10,
		v1.shift());
AddTestCase(
		"shift on single element vector removes first element",
		"",
		v1.toString());

var v1=new Vector.<int>();
for (var i=0;i<5;i++) v1[i]=10+i;
AddTestCase(
		"shift on vector returns element[0]",
		10,
		v1.shift());
AddTestCase(
		"shift on vector removes first element",
		"11,12,13,14",
		v1.toString());

var v1=new Vector.<int>(10);
AddTestCase(
		"shift on initialized vector returns element[0]",
		0,
		v1.shift());
AddTestCase(
		"shift on initialized vector removes first element",
		"0,0,0,0,0,0,0,0,0",
		v1.toString());

var v1=new Vector.<int>(10,true);
for (var i=0;i<10;i++) v1[i]=10+i;

var errormsg="";
try {
  v1.shift();
} catch (e) {
  errormsg=e.toString();
}
AddTestCase(
		"shift on fixed vector throws exception",
		"RangeError: Error #1126",
		parseError(errormsg,"RangeError: Error #1126".length));

AddTestCase(
		"shift on fixed vector does not shift",
		"10,11,12,13,14,15,16,17,18,19",
		v1.toString());

AddTestCase("Shift string vector",
            "h",
            Vector.<String>(['h','e','l','l','o']).shift()
            );

class TestClass {
    private var myVal:Object;
    public function TestClass(v:Object):void {
        myVal = v;
    }
    public function toString():String {
        return myVal.toString();
    }
}

AddTestCase("Shift custom vector class",
            "-Infinity",
            Vector.<TestClass>([new TestClass(-Infinity), new TestClass(55), new TestClass(789)]).shift().toString()
            );

test();
