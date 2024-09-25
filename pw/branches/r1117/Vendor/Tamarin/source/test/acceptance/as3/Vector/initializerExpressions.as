/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
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
 * The Original Code is Mozilla Communicator client code, released
 * March 31, 1998.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
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
   File Name:          initializerExpressions.as
   ECMA Section:       n/a
   Description:

   Test Vector intitializer expressions.

   Author:             tharwood@adobe.com
   Date:               27 March 2009
*/
var SECTION=""
var VERSION=""

startTest();

var v = new<int>[1,2];

AddTestCase(
	"Initialize a variable with a Vector",
	"1,2", 
	v.toString());

var v2:Vector.<int> = new<int>[3,4];

AddTestCase(
	"Initialize a typed variable with a Vector",
	"3,4", 
	v2.toString());

var msg="no exception";
try {
	var v3:Vector.<*> = new<int>[49];
} catch ( ex )
{
	msg = ex.toString();
}

AddTestCase(
	"[neg]Initialize a typed variable with a Vector",
	"TypeError: Error #1034",
	parseError(msg,"TypeError: Error #1034".length));

AddTestCase(
	"pass Vector initializer as parameter", 
	2, 
	getLength(new <*>[new Object(),3.14159,]));

AddTestCase(
	"call Vector initializer method",
	3, 
	new<int>[1,2,3].length);

AddTestCase(
	"compare Vector initializers",
	false, 
	new<int>[1,2] == new<int>[1,2]);

AddTestCase(
	"compare Vector initializers - ne",
	true, 
	new<int>[1,2] != new<int>[1,2]);

AddTestCase(
	"compare Vector initializers - ne",
	true, 
	new<int>[1,2] != new<*>[1,2]);

AddTestCase(
	"add scalar to Vector",
	"1,2,34", 
	new<int>[1,2,3]+4);

AddTestCase(
	"add Vector to scalar",
	"61,2,3",
	6+ new<int>[1,2,3]);


AddTestCase(
	"subtract scalar from Vector",
	NaN,
	new<int>[1,2,3]-4);

AddTestCase(
	"subtract Vector from scalar",
	NaN,
	4 - new<int>[1,2,3]);

AddTestCase(
	"multiply scalar by Vector",
	NaN,
	new<int>[1,2,3]*4);

AddTestCase(
	"multiply Vector by scalar",
	NaN,
	4 * new<int>[1,2,3]);

AddTestCase(
	"divide scalar by Vector",
	NaN,
	new<int>[1,2,3]/4);

AddTestCase(
	"divide Vector by scalar",
	NaN,
	4 / new<int>[1,2,3]);

AddTestCase(
	"typeof Vector initializer",
	"object",
	typeof(new<int>[1,2]));

AddTestCase(
	"select element from Vector initializer",
	3,
	new<int>[1,2,3,4][2]);

AddTestCase(
	"select element from Vector initializer",
	3,
	new<int>[1,2,3,4]["2.00"]);

AddTestCase(
	"assign to element from Vector initializer",
	7,
	new<int>[1,2,3,4][2] = 7);


AddTestCase(
	"stringify Vector initializer",
	"1,2,3",
	String(new<int>[1,2,3]));


AddTestCase(
	"delete Vector initializer property",
	false,
	delete new<int>[1,2,3].length);

AddTestCase(
    "initializer fixed property is false",
    false,
    new <int>[4,5,6,7,3,5,6,7,8].fixed);
  
AddTestCase(
    "length property returns expected value",
    10,
    new <Number> [0,1,2,3,4,5,6,7,8,9].length);

// length is used here since comparing the string is a pain
AddTestCase(
    "xml elements can be used in a vector literal",
    28,
    new<XML>[<myXml><item1/></myXml>,<myXml2></myXml2>].toString().length);

AddTestCase(
    "pop element from Vector initializer",
    "popped",
    new<String>['not this one', 'not this either','popped'].pop());

AddTestCase(
    "pop empty element from Vector initializer",
    null,
    new<String>['not this one', 'not this either','popped',null,].pop());
    
AddTestCase(
    "push element into Vector initializer",
    6,
    new<Number>[0.3,.56,.12,3.14].push(4500,.0001));
    
AddTestCase(
    "push nothing into Vector initializer",
    1,
    new<String>['hello'].push());

AddTestCase(
    "push null into Vector initializer",
    2,
    new<String>['hello'].push(null));

AddTestCase(
    "shift element from Vector initializer",
    uint(15e23),
    new<uint>[15e23,6,7].shift());

AddTestCase(
    "shift empty element from Vector initializer",
    null,
    new<String>[null,'4','5'].shift());

AddTestCase(
    "unshift element into Vector initializer",
    4,
    new<String>['3','4','5'].unshift('hello'));

AddTestCase(
    "unshift empty element into Vector initializer",
    3,
    new<String>['3','4','5'].unshift());
    
AddTestCase(
    "splice elements in Vector initializer",
    "3,4,5,6",
    new<int>[0,1,2,3,4,5,6,7,8,9].splice(3,4,101,102,103).toString());

var vSplice1:Vector.<int> = new<int>[0,1,2,3,4,5,6,7,8,9]
vSplice1.splice(3,4,101,102,103);
AddTestCase(
    "splice elements into Vector using comma seperated list",
    "0,1,2,101,102,103,7,8,9",
    vSplice1.toString());

var vSplice2:Vector.<int> = new<int>[0,1,2,3,4,5,6,7,8,9]
vSplice2.splice(3,4,101,102,103);
AddTestCase(
    "splice elements into Vector using vector initializer",
    "0,1,2,101,102,103,7,8,9",
    vSplice2.toString());


/* Not currently supported
var vSplice3:Vector.<int> = new<int>[0,1,2,3,4,5,6,7,8,9]
vSplice3.splice(3,4,[101,102,103]);
AddTestCase(
    "splice elements into Vector using array",
    "0,1,2,101,102,103,7,8,9",
    vSplice3.toString());
*/

AddTestCase(
    "create vector with one element and trailing comma in initializer",
    1,
    new<int>[333,].length);
    
AddTestCase(
    "create vector with null element and trailing comma in the initializer",
    1,
    new<Object>[null,].length);

AddTestCase(
    "create vector with undefined element and trailing comma in the initializer",
    1,
    new<Object>[undefined,].length);

test();

function getLength(x:Vector.<*>):int
{
	return x.length;
}
