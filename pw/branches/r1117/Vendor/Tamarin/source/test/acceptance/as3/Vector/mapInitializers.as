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
   File Name:    map.as
   Description:  map(object,mapper,thisobj)
     calls mapper on each vector element of object in increasing numerical index order, collecting
     the return values from mapper in a new vector object.
     mapper is called with three arguments: the property value, the property index, and object itself.
     The thisobj is used as the this object in the call.
     returns a new vector object where the vector element at index i is the value returned from the call
     to mapper on object[i].
   */
var SECTION="";
var VERSION = "ECMA_1";

startTest();

writeHeaderToLog( " Vector.map()-initializers");

function mapper1(value,index,obj) {
   return "("+value+":"+index+")";
}
var mapper2="a string";
function mapper3(value,index,obj) {
   return "("+this.message+")";
}
function mapper4(value,index,obj) {
   return value*value;
}

var errormsg="";
try {
  var result=new <int>[1].map();
} catch (e) {
  errormsg=e.toString();
}
AddTestCase(
		"map mapper is undefined",
		"ArgumentError: Error #1063",
		parseError(errormsg,"ArgumentError: Error #1063".length));

var errormsg="";
try {
  var result=new<int>[1].map(mapper2);
} catch (e) {
  errormsg=e.toString();
}
AddTestCase(
		"map mapper is not a function",
		"TypeError: Error #1034",
		parseError(errormsg,"TypeError: Error #1034".length));

AddTestCase(
		"map empty vector",
		"",
		new <int>[].map(mapper1).toString());

AddTestCase(
		"map small vector",
		"(a:0),(b:1),(c:2)",
		new<String>['a','b','c'].map(mapper1).toString());


AddTestCase(
		"map fixed size small vector",
		"(a:0),(b:1),(c:2)",
		new<String>['a','b','c'].map(mapper1).toString());

testobj=new Object();
testobj.message="testobj";
AddTestCase(   "map vector passing new object",
               "(testobj),(testobj)",
               new<String>['a','b'].map(mapper3,testobj).toString());

AddTestCase(   "map vector of int",
               "1,4,9,16",
               new<int>[1,2,3,4].map(mapper4).toString());

test();
