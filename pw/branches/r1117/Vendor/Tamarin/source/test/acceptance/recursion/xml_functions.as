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

var SECTION = "E4XNode__deepCopy";
var VERSION = "";
var TITLE   = "Shouldn't crash on high XML trees upon invoking E4XNode::_deepCopy and E4X::_equals";

startTest();
writeHeaderToLog(SECTION + " " + TITLE);
var testcases = getTestCases();
test();

function createXML(depth)
{
    // char code for the first letter of the abc
    var FIRSTCHARCODE = 97;
    // lenght of the abc
    var ABCLENGTH = 26;

    // string holding the open tags
    var openTagList = "";
    var closeTagList = new Vector.<String>();

    for (var i = 0; i < depth; ++i) {
	var tagContent = "";
	var tagNameLength = i / ABCLENGTH;

	for (var j = 0; j <= tagNameLength; ++j) {
	    tagContent += String.fromCharCode(FIRSTCHARCODE + i % ABCLENGTH);
	}

	openTagList += "<" + tagContent + ">";
	closeTagList.push("</" + tagContent + ">");
    }

    var xmlstring = openTagList + "sample";

    for each (var closeTag in closeTagList.reverse()) {
	xmlstring += closeTag;
    }

    return new XML(xmlstring);
}

/*
 * The test creates a big XML tree, then calls copy() to trigger the execution of E4XNode::_deepCopy.
 * Upon checking the result against the expected value, _equals is also called.
 * */

function getTestCases() 
{
    var array = new Array();
    var item = 0;

    var xml = createXML(1000);

    try {
	var copied = xml.copy();
	var res = xml == copied;
	array[item++] = new TestCase(SECTION, "new XML(...).copy()", true, res);
    }
    catch (e: Error) {
	if (e.message.match("#1023"))
	    array[item++] = new TestCase(SECTION, "new XML(...).copy()", 0, 0);
	else
	    throw(e);
    }

    try {
	//dummy test, execution of toXMLString is the goal here
	res = xml.toXMLString().indexOf("sample") > 0;

	array[item++] = new TestCase(SECTION, "new XML(...).toXMLString()", true, res);
    }
    catch (e: Error) {
	if (e.message.match("#1023"))
	    array[item++] = new TestCase(SECTION, "new XML(...).toXMLString()", 0, 0);
	else
	    throw(e);
    }

    try {
	//dummy test, execution of descendants is the goal here
	res = xml.descendants().length() > 0;

	array[item++] = new TestCase(SECTION, "new XML(...).descendants()", true, res);
    }
    catch (e: Error) {
	if (e.message.match("#1023"))
	    array[item++] = new TestCase(SECTION, "new XML(...).descendants()", 0, 0);
	else
	    throw(e);
    }

    return array;
}
