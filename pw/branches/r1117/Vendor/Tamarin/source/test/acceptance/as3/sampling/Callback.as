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

package {

import flash.sampler.*;
import avmplus.*;

var SECTION = "Sampling";
var VERSION = "AS3";
var TITLE   = "test the callback functionality when sampler memory is too high";

var isdebugger=System.isDebugger();

startTest();
writeHeaderToLog("Sampling api: callback");

var objs:Array=new Array();
class simpleobject {
    var str:String;
    function simpleobject(s:String) { 
        this.str=s;
    }
}
function simpleLoop(n:int=10) {
    for (var i:int=0;i<n;i++) {
        var s="0123456789";
        objs.push(new simpleobject(s));
    }
}
var allocs:int=0;
var deallocs:int=0;
function testSamples():int {
    pauseSampling();
    var nos : NewObjectSample;
    var dos : DeleteObjectSample;
    for each (sample in getSamples()) {
        if ((nos=sample as NewObjectSample) != null) {
            allocs++;
        }
        if ((dos=sample as DeleteObjectSample) != null) {
            deallocs++;
        }
    }
    clearSamples();
    startSampling();
    return allocs;
}
var callback1_num:int=0;
var callback2_num:int=0;
var callback3_num:int=0;

function callback1() {
    print("callback1 called at "+objs.length)
    callback1_num++;
    testSamples();
}
function callback2():int {
    callback2_num++;
    print("callback2 called at "+objs.length)
    return testSamples();
}
function callback3(n:int):String {
    callback3_num++;
    print("callback3 called at "+objs.length)
    testSamples();
}

sampleInternalAllocs(true);
setSamplerCallback(callback1);
startSampling();
simpleLoop(80000);
pauseSampling();
print("memory summary: allocs="+allocs+" deallocs="+deallocs);

if (isdebugger)
AddTestCase(
  "Callback: callback called at least once callback#="+callback1_num,
  true,
  callback1_num>0
);

setSamplerCallback(callback2);
startSampling();
simpleLoop(80000);
pauseSampling();

if (isdebugger)
AddTestCase(
  "Callback: callback with return type called at least once callback#="+callback2_num,
  true,
  callback2_num>0
);

var errstr2="";

try {
    setSamplerCallback(abc);
    startSampling();
    simpleLoop(80000);
} catch (e) {
    errstr2=e.toString();
}
pauseSampling();
AddTestCase(
  "Callback: function is not defined",
  "ReferenceError: Error #1065",
  parseError(errstr2,"ReferenceError: Error #1065".length)
);

test();
}