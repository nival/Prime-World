/* -*- mode: java; tab-width: 4; indent-tabs-mode: nil -*- */
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

// Canonical API: call START first, then PASS or FAIL for each test, then END.

package 
{
    var PASSED = " PASSED!";
    var FAILED = " FAILED! expected: ";
    var summary = "";

    public function START(_summary)
    {
        summary = _summary;
        print("Testing: " + summary);
    }

    public function PASS(name)
    {
        print(name + PASSED);
    }

    public function FAIL(name, expected, actual)
    {
        print(name + FAILED + expected + ", actual: " + actual);
    }

    public function END()
    {
        print("Finished testing " + summary);
    }

    // Useful helpers

    public function COMPARE_STRICTEQ(name, expected, actual)
    {
        
        //    because    ( NaN == NaN ) always returns false, need to do
        //    a special compare to see if    we got the right result.
        if ( actual != actual )    {
            if ( typeof actual == "object" ) {
                actual = "NaN object";
            } else {
                actual = "NaN number";
            }
        }
        if ( expected != expected )    {
            if ( typeof    expected == "object" ) {
                expected = "NaN object";
            } else {
                expected = "NaN number";
            }
        }
        if (expected !== actual)
            FAIL(name, expected, actual);
        else
            PASS(name);
    }

    public function COMPARE_TYPEERROR(name, expected, actual)
    {
        // Trim the typeerror to just the number so that we can compare in both release and debugger
        actual = String(actual).substr(0,22);
        if (expected !== actual)
            FAIL(name, expected, actual);
        else
            PASS(name);
    }

    /**
     *  Compare to a specified precision.
     */
    public function COMPARE_NUMBEREQ(name, expected, actual, fractionDigits=-1)
    {
        if (fractionDigits >= 0) {
            if (expected.toFixed(fractionDigits) !== actual.toFixed(fractionDigits))
                FAIL(name, expected, actual);
            else
                PASS(name);
        }
        else
            COMPARE_STRICTEQ(name, expected, actual);
    }
}


