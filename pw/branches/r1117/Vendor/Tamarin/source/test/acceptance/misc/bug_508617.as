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

class A
{
	private const p1:Object = new Object();
	protected const p2:Object = new Object();
	public const p3:Object = new Object();
	
	public function A()
	{
	}
}

class B extends A
{
	public function B()
	{
		super();
	}
}

class C1 extends A
{
	public function C1()
	{
		super();
		this.p1 = null; // illegal, should throw an error
	}
}

class C2 extends A
{
	public function C2()
	{
		super();
		this.p2 = null; // illegal, should throw an error
	}
}

class C3 extends A
{
	public function C3()
	{
		super();
		this.p3 = null; // illegal, should throw an error
	}
}

class C4 extends A
{
	public function C4()
	{
		super();
		this["p3"] = null; // illegal, should throw an error
	}
}

function test_one(c)
{
	var e = "no-exception";
	try
	{
		var x = new c();
	}
	catch (exception:*)
	{
		e = String(exception).substr(0, 27);
	}
	return e;
}


	var results = []

	results.push({expected: "no-exception", actual: test_one(B)});
	results.push({expected: "ReferenceError: Error #1056", actual: test_one(C1)});
	results.push({expected: "ReferenceError: Error #1074", actual: test_one(C2)});
	results.push({expected: "ReferenceError: Error #1074", actual: test_one(C3)});
	results.push({expected: "ReferenceError: Error #1074", actual: test_one(C4)});

startTest();
for (var i in results)
{
    var o = results[i]
    AddTestCase("test_"+i, o.expected, o.actual);
}
test();

