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

 /*
  * tests Vector.<type>(length,fixed) tests length and fixed parameter true|false
 */

var SECTION = " ";
var VERSION = "AS3";
var TITLE   = "Vector.<type> constructor (length, fixed)";

startTest();
writeHeaderToLog( SECTION + " "+ TITLE);

var v1=new Vector.<uint>;
AddTestCase("constructor no arg no parens syntax",0,v1.length);
var v2=new Vector.<uint>();
AddTestCase("constructor no arg empty parens syntax",0,v2.length);

var v3:Vector.<uint>=new Vector.<uint>();
AddTestCase("constructor to typed var no arg empty parens syntax",0,v3.length);

var v4=new Vector.<uint>(100);
AddTestCase("constructor length parameters",100,v4.length);

// default value for fixed is false
var v5=new Vector.<uint>(10);
v5.push(10);
AddTestCase( "constructor fixed parameter default is false", 11, v5.length);

var v6=new Vector.<uint>(10,false);
v6.push(10);
AddTestCase( "constructor fixed parameter false produces unfixed vector", 11, v6.length);
var v7=new Vector.<uint>(10,true);
var errormsg="";
try {
  v7.push(10);
} catch (e) {
  errormsg=e.toString();
}
AddTestCase( "constructor fixed parameter set to true write beyond length-1 throws exception", 
             "RangeError: Error #1126", 
             parseError(errormsg,"RangeError: Error #1126".length));
AddTestCase( "constructor fixed parameter set to true length is unchanged", 10, v7.length);
var v8=new Vector.<uint>(10,true);
var errormsg="";
try {
  v8[10];
} catch (e) {
  errormsg=e.toString();
}

/*
// 2^30=1073741824
var v9=new Vector.<int>(1073741824);
AddTestCase( "constructor large vector", 1073741824, v9.length);
*/

// test basic types: already 
var v10=new Vector.<uint>();
v10.push(10);
AddTestCase( "constructor type uint", 10, v10[0]);
var v11=new Vector.<int>();
v11.push(-10);
AddTestCase( "constructor type int", -10, v11[0]);
var v12=new Vector.<Number>();
v12.push(3.14);
AddTestCase( "constructor type Number", 3.14, v12[0]);
var v13=new Vector.<Boolean>();
v13.push(true);
AddTestCase( "constructor type Boolean", true, v13[0]);
var v14=new Vector.<String>();
v14.push("astring");
AddTestCase( "constructor type String", "astring", v14[0]);
class c1 { };
class c2 { };
class c3 extends c1 { };
var v15=new Vector.<c1>();
var c1inst=new c1();
v15.push(c1inst);
AddTestCase("constructor type custom class c1", c1inst, v15[0]);

var v16=new Vector.<c1>();
var c2inst=new c2();
var errormsg="";
try {
  v16.push(c2inst);
} catch (e) {
  errormsg=e.toString();
}
AddTestCase("constructor type custom class class mismatch", 
            "TypeError: Error #1034", 
            parseError(errormsg,"TypeError: Error #1034".length));

var c3inst=new c3();
var v17=new Vector.<c1>();
v17.push(new c3());
AddTestCase("constructor type custom class can caste to custom class", "[object c3]", v17[0].toString());

var v18=new Vector.<uint>();
v18.push(true);
AddTestCase("constructor type uint castes other types", 1, v18[0]);

function bug449468() {
    var v : Vector.<Vector.<Number>> = new Vector.<Vector.<Number>>(4);
    return v;
}

AddTestCase("Bug 449468: Crash with vector constructor in interp mode",
            "null,null,null,null",
            bug449468().toString()
            );

test();
