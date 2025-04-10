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
   File Name:          tostring.js
   ECMA Section:       Vector.toString()
   Description:        The elements of this object are converted to strings
   and these strings are then concatenated, separated by
   comma characters.  The result is the same as if the
   built-in join method were invoiked for this object
   with no argument.
   Author:             christine@netscape.com 7-Oct-1997
   Updated:            dschaffe@adobe.com 1-Nov-2007
*/

var SECTION = "";
var VERSION = "ECMA_1";
startTest();
var TITLE   = "Vector.toString";

writeHeaderToLog( SECTION + " "+ TITLE);
 
AddTestCase(
	      "Vector.<int>.prototype.toString.length",  
	      0,  
	      Vector.<int>.prototype.toString.length );

AddTestCase(
	      "new Vector.<int>().toString()",     
	      "",     
	      new Vector.<int>().toString() );
AddTestCase(
	      "(new Vector.<int>(5)).toString()",    
	      "0,0,0,0,0",    
	      (new Vector.<int>(5)).toString() );
AddTestCase(
	      "(new Vector.<Boolean>(5)).toString()",    
	      "null,null,null,null,null",    
	      (new Vector.<Boolean>(5)).toString() );
AddTestCase(
	      "(new Vector.<String>(2)).toString()",    
	      "null,null",    
	      (new Vector.<String>(2)).toString() );

AddTestCase(  
	      "(new Vector.<int>(5,true)).toString()",  
	      "0,0,0,0,0",  
	      (new Vector.<int>(5,true)).toString() );

var v1:Vector.<Number>=new Vector.<Number>;
v1.push(1.1);v1.push(3.14);v1.push(99.99);
AddTestCase(  
	      "small vector toString",  
	      "1.1,3.14,99.99",  
	      v1.toString() );
test();
