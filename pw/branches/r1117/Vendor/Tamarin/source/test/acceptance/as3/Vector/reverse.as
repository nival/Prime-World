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
   File Name:          reverse.as
   ECMA Section:       Vector.reverse()
   Description:

   The elements of the vector are rearranged so as to reverse their order.
   This object is returned as the result of the call.

   
   Note that the reverse function is intentionally generic; it does not require
   that its this value be an Array/Vector object. Therefore it can be transferred to other
   kinds of objects for use as a method. Whether the reverse function can be applied
   successfully to a host object is implementation dependent.

   Author:             christine@netscape.com
   Date:               7 october 1997
*/
var SECTION = "";
var VERSION = "ECMA_1";
startTest();

writeHeaderToLog( SECTION + " Vector.reverse()");
AddTestCase( 
	      "Vector.<int>.prototype.reverse.length",           
	      0,      
	      Vector.<int>.prototype.reverse.length );
var v1:Vector.<int>=new Vector.<int>();
v1.reverse();
AddTestCase(
	      "reverse empty vector",
	      "",
	      v1.toString());

var v1:Vector.<int>=new Vector.<int>();
v1[0]=111;
v1.reverse();
AddTestCase(
	      "reverse vector length 1",
	      "111",
	      v1.toString());

var v1:Vector.<int>=new Vector.<int>();
for (var i=0;i<20;i++) v1[i]=i;
v1.reverse();
AddTestCase(
	      "reverse vector of int",
	      "19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0",
	      v1.toString() );

var v2:Vector.<String>=new Vector.<String>();
v2[0]='one';v2[1]='two';v2[2]='three';
v2.reverse();
AddTestCase(
	      "reverse vector of String",
	      "three,two,one",
	      v2.toString() );

test();