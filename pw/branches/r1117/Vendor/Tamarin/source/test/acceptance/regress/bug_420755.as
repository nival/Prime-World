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
 * Portions created by the Initial Developer are Copyright (C) 2007-2009
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

var SECTION="";
var VERSION = "AS3";

startTest();

writeHeaderToLog("Bug 420755: Expand Array Test Coverage");

// check for subclassing of Array, both with and without "dynamic"

dynamic class MyDynamicArray extends Array				// dynamic child
{
}

class MyNonDynamicArray extends Array					// nondynamic child (dynamic isn't inherited in AS3)
{
}

dynamic class MyDynamicArray2 extends MyDynamicArray	// dynamic grandchild
{
}

class MyNonDynamicArray2 extends MyDynamicArray			// nondynamic grandchild
{
}

// Validate behaviour of "holes" in an array
function testArray(a:Array)
{
	var len = 100;
    a[0] = 0;
    for (var i:int = 1; i < len; ++i)
	{
		// test getprop & setprop (and .length)
        a[i] = a[i-1]+1;
	}
	
	// test delprop
	delete a[20];

	var tot = 0;
    for (var i:int = 1; i < a.length; ++i)
	{
		// test hasprop (should skip 20)
		if (a.hasOwnProperty(i))
			tot += a[i];
	}
	// print("tot "+tot);
    return tot;
}

AddTestCase("Validate behaviour of holes in Array",
            4930,
            testArray(new Array())
            );

AddTestCase("Validate behaviour of holes in subclassed dynamic Array",
            4930,
            testArray(new MyDynamicArray())
            );

AddTestCase("Validate behaviour of holes in subclassed grandchild of dynamic Array",
            4930,
            testArray(new MyDynamicArray2())
            );

var err = "no error";
try {
	testArray(new MyNonDynamicArray());	// expect ReferenceError: Error #1056
} catch (e) {
    err = grabError(e, e.toString());
} finally {
    AddTestCase("Validate behaviour of holes in subclassed non-dynamic Array",
                "Error #1056",
                err );
}

err = "no error";
try {
	testArray(new MyNonDynamicArray2());	// expect ReferenceError: Error #1056
} catch (e) {
	err = grabError(e, e.toString());
} finally {
    AddTestCase("Validate behaviour of holes in subclassed grandchild of non-dynamic Array",
                "Error #1056",
                err );
}

// test "construct"

var a = new Array(1,2,3);
AddTestCase("test array construct",
            3,
            a.length);

err = "no error";
try {
	var a = new MyDynamicArray(1,2,3);
	var temp = a.length;							// expect ArgumentError: Error #1063
} catch (e) {
	err = grabError(e, e.toString());
} finally {
    AddTestCase("Test construct of subclassed dynamic Array",
                "Error #1063",
                err );
}

err = "no error";
try {
	var a = new MyDynamicArray2(1,2,3);
	var temp = a.length;							// expect ArgumentError: Error #1063
} catch (e) {
	err = grabError(e, e.toString());
} finally {
    AddTestCase("Test construct of grandchild of subclassed dynamic Array",
                "Error #1063",
                err );
}

err = "no error";
try {
	var a = new MyNonDynamicArray(1,2,3);
	var temp = a.length;							// expect ArgumentError: Error #1063
} catch (e) {
	err = grabError(e, e.toString());
} finally {
    AddTestCase("Test construct in subclassed non-dynamic Array",
                "Error #1063",
                err );
}

err = "no error";
try {
	var a = new MyNonDynamicArray2(1,2,3);
	var temp = a.length;							// expect ArgumentError: Error #1063
} catch (e) {
	err = grabError(e, e.toString());
} finally {
    AddTestCase("Test construct in grandchild of subclassed non-dynamic Array",
                "Error #1063",
                err );
}

// test "call"
var a = Array(1,2,3);
AddTestCase("Test array call", 3, a.length);

err = "no error";
try {
	var a = MyDynamicArray(1,2,3);
	var temp = a.length;							// expect ArgumentError: Error #1112
} catch (e) {
	err = grabError(e, e.toString());
} finally {
    AddTestCase("Test call in subclassed dynamic Array",
                "Error #1112",
                err );
}

err = "no error";
try {
	var a = MyDynamicArray2(1,2,3);
	var temp = a.length;							// expect ArgumentError: Error #1112
} catch (e) {
	err = grabError(e, e.toString());
} finally {
    AddTestCase("Test call in grandchild of subclassed dynamic Array",
                "Error #1112",
                err );
}

err = "no error";
try {
	var a = MyNonDynamicArray(1,2,3);
	var temp = a.length;							// expect ArgumentError: Error #1112
} catch (e) {
	err = grabError(e, e.toString());
} finally {
    AddTestCase("Test call in subclassed non-dynamic Array",
                "Error #1112",
                err );
}

err = "no error";
try {
	var a = MyNonDynamicArray2(1,2,3);
	var temp = a.length;							// expect ArgumentError: Error #1112
} catch (e) {
	err = grabError(e, e.toString());
} finally {
    AddTestCase("Test call in grandchild of subclassed non-dynamic Array",
                "Error #1112",
                err );
}


// test holes vs elements-with-value-of-undefined
var a = [undefined];
for (var e in a) {
    AddTestCase("test holes vs elements-with-value-of-undefined: for-var-in",
                0,
                e);
}
for each (var e in a) {
    AddTestCase("test holes vs elements-with-value-of-undefined: for-each-var-in",
                undefined,
                e);
}


// Next two testcases: for loops will not loop over delete elements
var a = [1];
delete a[0];
var x=0;
for (var e in a) {
    x++;
}
AddTestCase("test holes vs elements-with-value-of-undefined - deleted element: for-var-in",
            0,
            x);

x=0;
for each (var e in a) {
    x++
}
AddTestCase("test holes vs elements-with-value-of-undefined - deleted element: for-each-var-in",
            0,
            x);

test();

