/* -*- mode: java; tab-width: 4 -*- */
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
 * The Original Code is [Open Source Virtual Machine].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2005-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 olr later (the "GPL"), or
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
//-----------------------------------------------------------------------------

var SECTION = "pcre_could_be_empty_branch";
var VERSION = "";
var TITLE   = "Shouldn't crash on regexps with many nested parentheses embedded in ()* constructs";

startTest();
writeHeaderToLog(SECTION + " " + TITLE);
var testcases = getTestCases();
test();

function getTestCases() 
{
    var array = new Array();
    var item = 0;

    // setting this to < 407 results in evaluating the 'search' to 0, from 407, it is -1
    var NUM_PAREN = 406;

    var pattern = '';
    for (var i = 0; i < NUM_PAREN; i++) pattern += '(';
    for (var i = 0; i < NUM_PAREN; i++) pattern += 'a)';
    pattern += '*';

    try {
	var re = new RegExp(pattern);
    
	var res = "aaaaa".search(re);
	array[item++] = new TestCase(SECTION, "'aaaaa'.search(re)", 0, res);
    }
    catch (e: Error) {
	if (e.message.match("#1023"))
	    array[item++] = new TestCase(SECTION, "'aaaaa'.search(re)", 0, 0);
	else
	    throw(e);
    }
    return array;
}
