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
   File Name:    splice.as
   Description:  splice(object,start,deletCount,...items)
     splice replaces the deleteCount vector elements of object starting at vector index start with values
     from the items, the methods returns a new vector object containing the vector elements that were removed
     from objects, in order.
   *
   */
var SECTION="";
var VERSION = "ECMA_1";

startTest();

/*
writeHeaderToLog( " Vector.splice()");
var v1=new Vector.<String>();
AddTestCase(
		"splice empty vector with nothing",
		"",
		v1.splice().toString());

var v1=new Vector.<String>();
v1.splice(0,0);
AddTestCase(
		"splice empty vector with nothing set start",
		"",
		v1.toString());
var v1=new Vector.<String>();
v1[0]="one";v1[1]="two";v1[2]="three";
var splice=v1.splice(2,0,"three","four")
AddTestCase(
		"splice small vector no delete",
		"one,two,three,four",
		v1.toString());
*/
var v1=new Vector.<String>();
v1.push("one");v1.push("delete");v1.push("delete");v1.push("two");v1.push("three");
var splice=v1.splice(1,2)
AddTestCase(
		"splice small vector delete 2 items, no add",
		"one,two,three",
		v1.toString());
var v1=new Vector.<String>();
v1.push("one");v1.push("delete");v1.push("delete");v1.push("four");v1.push("five");v1.push("six");
var splice=v1.splice(1,2,"two","three")
AddTestCase(
		"splice small vector delete 2 items, add 2 items",
		"one,two,three,four,five,six",
		v1.toString());

var v1=new Vector.<String>();
v1.push("one");v1.push("delete1");v1.push("delete2");v1.push("four");v1.push("five");v1.push("six");
var splice=v1.splice(-5,2,"two","three")
AddTestCase(
		"splice small vector start is negative",
		"one,two,three,four,five,six",
		v1.toString());
/*
var v1=new Vector.<String>();
v1.push("one");v1.push("delete1");v1.push("delete2");v1.push("four");v1.push("five");v1.push("six");
var splice=v1.splice(1,-2,"two","three")
AddTestCase(
		"splice small vector deletecount is negative",
		"one,two,three,delete1,delete2,four,five,six",
		v1.toString());
*/
test();
