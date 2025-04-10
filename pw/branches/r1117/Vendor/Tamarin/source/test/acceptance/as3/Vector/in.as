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
   File Name:    in.es
   Description:  test 'in' keyword.
    the exception is a current issue with properties defined in the prototype.
   *
   */

var SECTION = " ";
var VERSION = "AS3";
startTest();
writeHeaderToLog( SECTION + " Vector in statement");

var v1:Vector.<*>=new Vector.<*>();
var v2:Vector.<int>=Vector.<int>(["zero","one","two","three","four","five"]);
AddTestCase(    "in value valid index",
		true,
		(0 in v2));
AddTestCase(    "in value for empty vector",
		false,
		(0 in v1));

AddTestCase(    "in value valid index does not exist",
		false,
		(6 in v1));

AddTestCase(    "in value valid index in string form",
		true,
		("2" in v2));

err1="no exception";
try {
AddTestCase(    "in value is push function index ",
		true,
		("push" in v1));
AddTestCase(    "in value is concat function index ",
		true,
		("concat" in v1));
AddTestCase(    "in value negative number index ",
		false,
		(-2 in v1));
AddTestCase(    "in value decimal index",
		false,
		(1.1 in v1));
AddTestCase(    "in value decimal in string index",
		false,
		("1.1" in v1));
AddTestCase(    "in value valid string",
		false,
		("string" in v1));
} catch(e) {
  err1=e.toString();
  AddTestCase(    "in throws exception for invalid vector indexes",
                  "no exception",
                  err1);
}

test();

