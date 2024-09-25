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
   File Name:    typechecking.as
   Description:  
   verify runtime error when set or add mismatched types.
   *
   */
var SECTION="";
var VERSION = "ECMA_4";

startTest();

writeHeaderToLog( " Vector.typechecking");

// untyped
var vs1=new Vector.<String>();
// typed
var vs2:Vector.<String>=new Vector.<String>();
var v1:Vector.<Object>;

var err1="no error";
try {
  v1=vs2;
} catch (e) {
  err1=e.toString();
}

AddTestCase(
		"assign vector variable to mismatched builtin type, throws runtime error",
		"TypeError: Error #1034",
		parseError(err1,"TypeError: Error #1034".length));

class A { }
class B extends A { }
class C { }

var v2:Vector.<A>=new Vector.<A>();
var v3:Vector.<B>=new Vector.<B>();
try {
  v2=v3;
} catch (e) {
  err3=e.toString();
}
AddTestCase(
		"assign vector variable to mismatched types, throws runtime error",
		"TypeError: Error #1034",
		parseError(err3,"TypeError: Error #1034".length));


AddTestCase(
		"push inherited type into Vector is allowed",
		2,
		v2.push(new A(),new B()));

var err4="no error";
try {
  v2.push(new A(),new C());
} catch (e) {
  err4=e.toString();
}
AddTestCase(
		"push wrong type into Vector, throws runtime error",
		"TypeError: Error #1034",
		parseError(err4,"TypeError: Error #1034".length));

var v4:Vector.<A>=new Vector.<A>();

AddTestCase(
		"unshift inherited types is allowed",
		2,
		v4.unshift(new A(),new B()));

AddTestCase(
		"unshift inherited types is allowed, verify toString",
		"[object A],[object B]",
		v4.toString());

var err5="no error";
var v5=new Vector.<A>();
try {
 v5.unshift(new A(),new B(),new C());
} catch (e) {
 err5=e.toString();
}
AddTestCase(
		"unshift wrong type into Vector, throws runtime error",
		"TypeError: Error #1034",
		parseError(err5,"TypeError: Error #1034".length));

var v6:Vector.<A>=new Vector.<A>();
v6.push(new A(),new A());
var v6a:Vector.<B>=new Vector.<B>();
v6a.push(new B(),new B());
AddTestCase(
		"concat inherited types returns correct vector",
		"[object A],[object A],[object B],[object B]",
		v6.concat(v6a).toString());

var err7="no error";
var v7:Vector.<C>=new Vector.<C>();
v7.push(new C());
try {
  v6.concat(v7);
} catch (e) {
  err7=e.toString();
}
AddTestCase(
		"vector concat throws runtime error",
		"TypeError: Error #1034",
		parseError(err7,"TypeError: Error #1034".length));

var v8:Vector.<A>=new Vector.<A>();
var err8="no error";
try {
  v8[0]=new C();
} catch(e) {
  err8=e.toString();
}
AddTestCase(
		"vector assignment on incorrect type throws runtime error",
		"TypeError: Error #1034",
		parseError(err8,"TypeError: Error #1034".length));

test();
