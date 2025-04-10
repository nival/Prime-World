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
* Portions created by the Initial Developer are Copyright (C) 2008
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

function test_pos() 
{
    // d starts life as a kIntegerType atom
    var d = 0xffff|0
    var i = 16

    // double d over and over to exceed the range limits of atom and 32 bit,
    // to try to demonstrate extra precision that shouldn't be there.  To test
    // for precision, we explicitly convert d to double by multiplication, then
    // mask of the low bits and compare with an unconverted (masked) d.
    //
    // if d has more precision than double supports, the masked result should
    // be different.

    while ((d&15) == ((d*1.0)&15) && i < 64) {
        d = d + d + 1
        i++
        if (String(d) != String(d*1.0))
            print(i + " " + d + " " + d*1.0)
    }
    return i;
}

function test_neg() 
{
    // d starts life as a kIntegerType atom
    var d = -65535
    var i = 16

    // double d over and over to exceed the range limits of atom and 32 bit,
    // to try to demonstrate extra precision that shouldn't be there.  To test
    // for precision, we explicitly convert d to double by multiplication, then
    // mask of the low bits and compare with an unconverted (masked) d.
    //
    // if d has more precision than double supports, the masked result should
    // be different.

    while ((d&15) == ((d*1.0)&15) && i < 64) {
        d = d + d + 1
        i++
        if (String(d) != String(d*1.0))
            print(i + " " + d + " " + d*1.0)
    }
    return i;
}


	var results = []

    var e = (-1 >>> 0)
	results.push({expected: 4294967295, actual: e});

	results.push({expected: 2147483648, actual: (- - "0x80000000")});

	results.push({expected: 64, actual: test_pos()});
	results.push({expected: 64, actual: test_neg()});
    
    var u:uint = 0xffffffff;
	results.push({expected: 0, actual: ~u});
	results.push({expected: -4294967295, actual: -u});
    
startTest();
for (var i in results)
{
    var o = results[i]
    AddTestCase("test_"+i, o.expected, o.actual);
}
test();
