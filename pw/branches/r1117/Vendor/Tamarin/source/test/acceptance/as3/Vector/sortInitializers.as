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
   File Name:          sort.as
   ECMA Section:       Vector.sort(comparefn)
   Description:


   Author:             christine@netscape.com 12 Nov 1997
   Updated:            dschaffe@adobe.com 2 Nov 2007
*/


var SECTION = "";
var VERSION = "ECMA_1";
startTest();
var TITLE   = "Vector.sort(comparefn)";

writeHeaderToLog( SECTION + " "+ TITLE);

var errormsg="";
try {
  new<int>[4,92,1].sort()
} catch (e) {
  errormsg=e.toString();
}
AddTestCase(
   "sort vector without setting compare function throws exception",
   "TypeError: Error #1034",
   parseError(errormsg,"TypeError: Error #1034".length));

AddTestCase(
    "sort vector",
    "-12,2,17,56,999",
    new<Number>[999,2,56,-12,17].sort(Compare).toString());


test();

function Sort( a ) {
  for ( i = 0; i < a.length; i++ ) {
    for ( j = i+1; j < a.length; j++ ) {
      var lo = a[i];
      var hi = a[j];
      var c = Compare( lo, hi );
      if ( c == 1 ) {
	a[i] = hi;
	a[j] = lo;
      }
    }
  }
  return a;
}

function Compare( x, y ) {
  if ( x == void 0 && y == void 0  && typeof x == "undefined" && typeof y == "undefined" ) {
    return +0;
  }
  if ( x == void 0  && typeof x == "undefined" ) {
    return 1;
  }
  if ( y == void 0 && typeof y == "undefined" ) {
    return -1;
  }
  if ( x < y ) {
    return -1;
  }
  if ( x > y ) {
    return 1;
  }
  return 0;
}
