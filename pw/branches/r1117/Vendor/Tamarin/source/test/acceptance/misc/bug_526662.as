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

function parse(s:String):String
{
    try
    {
        return XML(s).toXMLString();
    }
    catch(e)
    {
        var str:String = String(e);
        var numIndex = str.indexOf("Error #");
        return str.substr(numIndex, 11);
    }
}


    XML.prettyPrinting = false;
    XML.prettyIndent = 0;
    
	var results = []

    var s:String = "foo"
    var r:String = parse(s);
	results.push({expected: "foo", actual: r});

    var s:String = "<one>1</one>"
    var r:String = parse(s);
	results.push({expected: "<one>1</one>", actual: r});

    var s:String = "foo" + String.fromCharCode(0) + "<one>1</one>"
    var r:String = parse(s);
	//results.push({expected: "Error #1088", actual: r});
    // the XML parser stops at the first zero char, regardless of length
	results.push({expected: "foo", actual: r});

    var s:String = "foo" + String.fromCharCode(0) + "??garbled randomness that is not legal XML!"
    var r:String = parse(s);
	//results.push({expected: "foo&#x0;??garbled randomness that is not legal XML!", actual: r});
    // the XML parser stops at the first zero char, regardless of length
	results.push({expected: "foo", actual: r});
    
    var s:String = String.fromCharCode(0) + "<one>1</one>"
    var r:String = parse(s);
	//results.push({expected: "Error #1088", actual: r});
    // the XML parser stops at the first zero char, regardless of length
	results.push({expected: "", actual: r});

    var s:String = "<head><one>1</one>" + String.fromCharCode(0) + "<two>2</two></head>"
    var r:String = parse(s);
	//results.push({expected: "<head><one>1</one>&#x0;<two>2</two></head>", actual: r});
    // the XML parser stops at the first zero char, regardless of length
	results.push({expected: "Error #1085", actual: r});


startTest();
for (var i in results)
{
    var o = results[i]
    AddTestCase("test_"+i, o.expected.toString(), o.actual.toString());
}

test();
