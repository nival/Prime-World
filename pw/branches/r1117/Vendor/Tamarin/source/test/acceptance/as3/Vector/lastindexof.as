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
   File Name:    lastindexof.es
   Description:  lastindexOf(object,value,from=...)
     compares value with every vector element of object in increasing numerical index order, starting at the 
     index from, stopping when an vector lement is equial to value by the === operator, From is rounded toward zero 
     before use.  If from is negative, it is treated as object.length+from, returns vector index from first value or -1 
     if no such element is found.
   *
   */

var SECTION = ""
var VERSION = "ECMA_1";

startTest();

writeHeaderToLog( SECTION + " Vector.lastIndexOf()");

/*
var v1=new Vector.<int>();
AddTestCase(	"lastIndexOf empty vector",
		-1,
		v1.lastIndexOf(0));
var v1=new Vector.<int>();
for (var i=0;i<10;i++) v1[i]=i;
AddTestCase(	"lastIndexOf object not found",
		-1,
		v1.lastIndexOf(10));
*/
var v1=new Vector.<int>();
for (var i=0;i<10;i++) v1[i]=i;
AddTestCase(	"lastIndexOf single match found",
		4,
		v1.lastIndexOf(4));

var v1=new Vector.<int>();
for (var i=0;i<10;i++) v1[i]=i;
for (var i=0;i<10;i++) v1[i+10]=i;
for (var i=0;i<10;i++) v1[i+20]=i;
AddTestCase(	"lastIndexOf first match found",
		24,
		v1.lastIndexOf(4));

var v1=new Vector.<int>();
for (var i=0;i<10;i++) v1[i]=i;
for (var i=0;i<10;i++) v1[i+10]=i;
for (var i=0;i<10;i++) v1[i+20]=i;
AddTestCase(	"lastIndexOf first match found setting start parameter",
		14,
		v1.lastIndexOf(4,20));

var v1=new Vector.<int>();
for (var i=0;i<10;i++) v1[i]=i;
for (var i=0;i<10;i++) v1[i+10]=i;
for (var i=0;i<10;i++) v1[i+20]=i;
AddTestCase(	"lastIndexOf start parameter greater than vector length",
		24,
		v1.lastIndexOf(4,100));

var v1=new Vector.<int>();
for (var i=0;i<10;i++) v1[i]=i;
for (var i=0;i<10;i++) v1[i+10]=i;
for (var i=0;i<10;i++) v1[i+20]=i;
AddTestCase(	"lastIndexOf start parameter negative",
		14,
		v1.lastIndexOf(4,-10));

test();

