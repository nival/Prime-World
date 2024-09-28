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
   File Name:    foreach.es
   Description:  foreach(object,eacher,thisobj)
     calls checker on every vector element of object in increasing numerical index order,
     collecting all the vector elements for which checker returns a value.
     checker is called with three arguments, the property value, the property index, the object itself.
     the thisobj is used as the this object in the call.
     returns a new vector object containing the elements that were collected in the order they were
     collected.
   */
var SECTION="";
var VERSION = "ECMA_1";

startTest();

writeHeaderToLog( " Vector.forEach()-using-initializers");

function eacher(value,index,obj) {
  result+="("+value+":"+index+")";
}
var bad_eacher="astring";

var errormsg="";
try {
  var result=new <int>[].forEach();
} catch (e) {
  errormsg=e.toString();
}
AddTestCase( 	"forEach eacher is undefined",
		"ArgumentError: Error #1063",
    parseError(errormsg,"ArgumentError: Error #1063".length));

var errormsg="";
try {
  var result=new <int>[0,1,2].forEach(bad_eacher);
} catch (e) {
  errormsg=e.toString();
}
AddTestCase("forEach eacher is not a function",
         		"TypeError: Error #1034",
            parseError(errormsg,"TypeError: Error #1034".length));

var result="";
new <String>["s0","s1","s2"].forEach(eacher);
AddTestCase(	"forEach simple vector",
		"(s0:0)(s1:1)(s2:2)",
		result);
		
var i:int;
for (i in new <int> [1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8])
{}

AddTestCase("for-in loop",
    39,
    i);


var str:String = "";
for each (var o in new <Object>[1,2,3,"hello",'out',"there",true, false, 3.14159])
{
  str += o;
}

AddTestCase("for-each-in loop",
    "123helloouttheretruefalse3.14159",
    str);

test();
