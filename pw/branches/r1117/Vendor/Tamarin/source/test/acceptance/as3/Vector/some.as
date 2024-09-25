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
   File Name:    some.as
   Description:  some(object,checker,thisobj=)
     calls checker on every vector element in object in increasing numerical index order,
     stopping as soon as checker returns a true value.
     checker is called with three arguments: the property value, the property index, and the object
     itself.  The thisobj is used as the this object in the call.
     returns true when checker returns a true value, otherwise returns false if all the calls to checker
     return false values.
   *
   */
var SECTION="";
var VERSION = "ECMA_1";

startTest();

writeHeaderToLog(" Vector.some()");
var msg;
function checker1(value,index,obj) {
  msg+="(value="+value+",index="+index+",object=["+obj+"])";
  if (value=='t')
    return true;
  return false;
}

var v1=new Vector.<int>();
var errormsg="";
try {
  result=v1.some();
} catch (e) {
  errormsg=e.toString();
}
AddTestCase(
		"some no checker",
		"ArgumentError: Error #1063",
		parseError(errormsg,"ArgumentError: Error #1063".length));


var checker2="a string";
var v1=new Vector.<int>();
v1.push(1);
var errormsg="";
try {
  result=v1.some(checker2);
} catch (e) {
  errormsg=e.toString();
}
AddTestCase(
		"some checker not a function",
		"TypeError: Error #1034",
		parseError(errormsg,"TypeError: Error #1034".length));

var msg="";
var v1=new Vector.<int>();
var result=v1.some(checker1);
AddTestCase(
                "some empty vector result",
                false,
                result);
AddTestCase(
                "some empty vector message empty",
                "",
                msg);
var msg="";
var v1=new Vector.<String>();
v1[0]='a';v1[1]='b';v1[2]='c';
var result=v1.some(checker1);
AddTestCase(
                "some small vector result",
                false,
                result);
AddTestCase(
                "some small vector message",
                "(value=a,index=0,object=[a,b,c])(value=b,index=1,object=[a,b,c])(value=c,index=2,object=[a,b,c])",
                msg);

var msg="";
var v1=new Vector.<String>();
v1[0]='a';v1[1]='b';v1[2]='t';v1[3]='c';v1[4]='d';
var result=v1.some(checker1);
AddTestCase(
                "some small vector result with a true",
                true,
                result);
AddTestCase(
                "some small vector message with a true",
                "(value=a,index=0,object=[a,b,t,c,d])(value=b,index=1,object=[a,b,t,c,d])(value=t,index=2,object=[a,b,t,c,d])",
                msg);
test();
