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
   File Name:          put.es
   ECMA Section:       [[ Put]] (P, V)
   Description:
   Vector objects use a variation of the [[Put]] method used for other native
   put usage for vectors is v1[i]=..., may only set v1[i] where i<=v1.length

   Author:             dschaffe@adobe.com 19-Nov-2007
*/

var SECTION = "";
var VERSION = "ECMA_1";
startTest();
var TITLE   = "Vector [[Put]] (P, V)";

writeHeaderToLog( SECTION + " "+ TITLE);

var v1=new Vector.<int>();
v1[0]=10;
AddTestCase("set [0] to empty vector",
            10,
            v1[0]);
AddTestCase("set [0] to empty vector, length increments",
            1,
            v1.length);

var v1=new Vector.<int>();
var errormsg="";
try {
  v1[1]=10;
} catch (e) {
  errormsg=e.toString();
}
AddTestCase("set [1] element on empty vector, throws exception",
            "RangeError: Error #1125",
            parseError(errormsg,"RangeError: Error #1125".length));
AddTestCase("set [1] element on empty vector, array is still empty",
            "",
            v1.toString());

var v1=new Vector.<int>(5,true);
for (var i:uint=0;i<5;i++) v1[i]=i+1;
var errormsg="";
try {
  v1[5]=10;
} catch (e) {
  errormsg=e.toString();
}
AddTestCase("set fixed vector past fixed length throws exception",
            "RangeError: Error #1125",
            parseError(errormsg,"RangeError: Error #1125".length));
AddTestCase("set fixed vector past fixed length throws exception, original vector remains same",
            "1,2,3,4,5",
            v1.toString());

var v1=new Vector.<int>(5);
for (var i=0;i<5;i++) v1[i]=i;
v1[4]=10;
AddTestCase("set existing element in vector to new value",
            "0,1,2,3,10",
            v1.toString());

var v1=new Vector.<int>(5);
for (var i=0;i<5;i++) v1[i]=i;
v1[5]=5;
AddTestCase("existing vector set expand the vector by setting element to v1[length]",
            "0,1,2,3,4,5",
            v1.toString());


test();
