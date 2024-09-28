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
   File Name:    every.es
   Description:  every(object,checker,thisObj=)
     calls checker on every Vector element of object in increasing numerical index order, stopping
     as soon as any call returns false.
     checker is called with three arguments: the property value, the property index
     and the object itself.  The thisobj is used as the this object in the call.
     returns true if all the calls to checker returned true values, otherwise it returns false.
   *
   */
var SECTION="";
var VERSION = "ECMA_1";

startTest();

writeHeaderToLog( " Vector.every()");

function checker1(value,index,obj):Boolean {
  msg+="checker1("+value+","+index+",["+obj+"])";
  if (value==0)
    return false;
  return true;
}
function checker3(value,index,obj):Boolean {
  msg+=this.message;
  return true;
}

var msg="";
var v1=new Vector.<int>();
AddTestCase(	"every empty array",
		true,
		v1.every(checker1));

var msg="";
var v1=new Vector.<int>();
for (var i=0;i<3;i++) v1.push(i+1);
AddTestCase(	"every small array returns true",
		true,
		v1.every(checker1));

AddTestCase(	"every small array check function",
		"checker1(1,0,[1,2,3])checker1(2,1,[1,2,3])checker1(3,2,[1,2,3])",
		msg);

var msg="";
var v1=new Vector.<int>();
for (var i=0;i<3;i++) v1.push(2-i);
AddTestCase(    "every small array returns false on 0",
                false,
                v1.every(checker1));


var msg="";
var thisobj=new Object();
thisobj.message="object";
var v1=new Vector.<int>(5);
v1.every(checker3,thisobj);
AddTestCase(	"every small array with a specified this object",
		"objectobjectobjectobjectobject",
		msg);

// Custom vector class
class TestClass {
    private var myVal:Object;
    public function TestClass(v:Object):void {
        myVal = v;
    }
    public function toString():String {
        return myVal.toString();
    }
    
    public function doubleMyVar():void {
        myVal *= 2;
    }
    
    public static function double(item:Object, index:int, vector:Vector.<TestClass>):Object {
        item.doubleMyVar();
        return item;
    }
    
    public static function lessThan100(obj:TestClass):Boolean {
        if (obj.myVal < 100) {
            return true;
        } else {
            return false;
        }
    }
}

function thisObjectTest(item:Object, index:int, vector:Vector.<TestClass>):Object {
    return this.lessThan100(item);
}

var v4:Vector.<TestClass> = new Vector.<TestClass>();
v4.push(new TestClass(33));
v4.push(new TestClass(44));
v4.push(new TestClass(1));
v4.push(new TestClass(50));

AddTestCase("thisObject test 1",
            true,
            v4.every(thisObjectTest, TestClass)
            );

v4.push(new TestClass(500));

AddTestCase("thisObject test 2",
            false,
            v4.every(thisObjectTest, TestClass)
            );

var errorMsg = "";
try {
    v4.every(thisObjectTest, undefined);
} catch (e) {
    errorMsg = e.toString();
}

AddTestCase("thisObject test 3",
            "TypeError: Error #1006", 
            parseError(errorMsg,"TypeError: Error #1006".length)
            );

errorMsg = "";
try {
    v4.every(thisObjectTest, NaN);
} catch (e) {
    errorMsg = e.toString();
}

AddTestCase("thisObject test 4",
            "TypeError: Error #1006", 
            parseError(errorMsg,"TypeError: Error #1006".length)
            );

errorMsg = "";
try {
    v4.every(thisObjectTest, false);
} catch (e) {
    errorMsg = e.toString();
}

AddTestCase("thisObject test 5",
            "TypeError: Error #1006", 
            parseError(errorMsg,"TypeError: Error #1006".length)
            );

test();
