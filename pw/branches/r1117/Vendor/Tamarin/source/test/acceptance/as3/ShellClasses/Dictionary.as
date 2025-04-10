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
 * Portions created by the Initial Developer are Copyright (C) 2005-2006
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

    import flash.utils.Dictionary

    var SECTION = "Dictionary";
    var VERSION = "as3";
    startTest();
    var TITLE   = "test Dictionary class";

    writeHeaderToLog( SECTION + " "+ TITLE );

    // test constructors

    var dict:Dictionary=new Dictionary();
    AddTestCase(
      "Dictionary constructor no args",
      true,
      dict!=null
      );

    var dict_notweak:Dictionary=new Dictionary(false);
    AddTestCase(
      "Dictionary constructor weakKeys=false",
      true,
      dict_notweak!=null
      );

    var dict_weak:Dictionary=new Dictionary(true);
    AddTestCase(
      "Dictionary constructor weakKeys=true",
      true,
      dict_weak!=null
      );

    // test get/set keys and values 

    AddTestCase(
      "empty dictionary toString",
      "[object Dictionary]",
      dict.toString()
      );

    AddTestCase(
      "dictionary key lookup fails",
      undefined,
      dict_notweak['notfound']
      );

    AddTestCase(
      "weak dictionary key lookup fails",
      undefined,
      dict_weak['notfound']
      );

    dict_notweak["one"]="one_value";
    AddTestCase(
      "dictionary key is literal",
      "one_value",
      dict_notweak["one"]
      );

    var obj1:Object=new Object();
    obj1.toString = function() { return "obj1" }
    dict_notweak[obj1]="obj1_value";
    AddTestCase(
      "dictionary key is object",
      "obj1_value",
      dict_notweak[obj1]
      );

    dict_weak["one"]="one_value";
    AddTestCase(
      "weak dictionary key is literal",
      "one_value",
      dict_weak["one"]
    );

    dict_weak[obj1]="obj1_value";
    AddTestCase(
      "weak dictionary key is object",
      "obj1_value",
      dict_weak[obj1]
    );

    // test in (hasAtomProperty)
    
    AddTestCase(
      "literal in dictionary key",
      true,
      ("one" in dict_notweak)
    );
    AddTestCase(
      "object in dictionary key",
      true,
      obj1 in dict_notweak
    );
    AddTestCase(
      "literal in weak dictionary key",
      true,
      "one" in dict_weak
    );
    AddTestCase(
      "object in weak dictionary key",
      true,
      obj1 in dict_weak
    );

    var a;
    var out1=new Array();
    for (a in dict_notweak) {
        out1.push(a.toString());
    }
    out1.sort();
    AddTestCase(
     "for in dictionary",
     "obj1,one",
     out1.toString());

    var out2=new Array(0);
    for (a in dict_weak) {
        out2.push(a.toString());
    }
    out2.sort();
    AddTestCase(
     "for in weak dictionary",
     "obj1,one",
     out2.toString());

    var out3=new Array();
    for each (a in dict_notweak) {
        out3.push(a.toString());
    }
    out3.sort();
    AddTestCase(
     "for each in dictionary",
     "obj1_value,one_value",
     out3.toString()); 

    var out4=new Array();
    for each (a in dict_weak) {
        out4.push(a.toString());
    }
    out4.sort();
    AddTestCase(
     "for each in weak dictionary",
     "obj1_value,one_value",
     out4.toString()); 

// test delete

    delete dict_notweak['one'];
    AddTestCase(
     "delete literal key from dictionary",
     undefined,
     dict_notweak['one']);

    delete dict_notweak[obj1];
    AddTestCase(
     "delete object key from dictionary",
     undefined,
     dict_notweak[obj1]);

    delete dict_weak['one'];
    AddTestCase(
     "delete literal key from weak dictionary",
     undefined,
     dict_weak['one']);

    delete dict_weak[obj1];
    AddTestCase(
     "delete object key from weak dictionary",
     undefined,
     dict_weak[obj1]);

    test();

