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
   File Name:    nested.as
   Description:  tests nested Vectors: Vector.<Vector.<int>>
   *
   */
var SECTION="";
var VERSION = "ECMA_1";

startTest();

writeHeaderToLog( " nested Vector-initializers");

var v1:Vector.<Vector.<int>> = new <Vector.<int>> [
	new <int>[0,1],
	new <int>[2,3],
    new <int>[4,5]];
AddTestCase("push nested vector.<int>",
            "0,1,2,3,4,5",
            v1.toString());

var v3:Vector.<Vector.<String>>=new <Vector.<String>>
[
	new <String>['one','two'],
	new <String>['three','four'],
	new <String>['five','six'],
]
AddTestCase("push nested vector.<String>",
            "one,two,three,four,five,six",
            v3.toString());


AddTestCase("push nested vector.<String> as value",
            "one,two,three,four,five,six",
				new <Vector.<String>>
				[
					new <String>['one','two'],
					new <String>['three','four'],
					new <String>['five','six'],
				]
			.toString());

var v5:Vector.<Vector.<Vector.<int>>> =
	new <Vector.<Vector.<int>>>[
	new <Vector.<int>>[ new <int>[0,1]],
	new <Vector.<int>>[ new <int>[2,3]],
	new <Vector.<int>>[ new <int>[4,5]],
	];

AddTestCase("push nested vector.<vector.<int>>",
            "0,1,2,3,4,5",
            v5.toString());

AddTestCase("nested vector.<vector.<int>> as value",
            "0,1,2,3,4,5",
			new <Vector.<Vector.<int>>>[
				new <Vector.<int>>[ new <int>[0,1]],
				new <Vector.<int>>[ new <int>[2,3]],
				new <Vector.<int>>[ new <int>[4,5]],
			].toString());

test();
