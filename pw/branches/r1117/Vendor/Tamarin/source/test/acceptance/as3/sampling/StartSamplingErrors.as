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

import flash.sampler.*;
import avmplus.*;

var SECTION = "Sampling";
var VERSION = "AS3";
var TITLE   = "Sampling Basic Usage";

var isdebugger=System.isDebugger();

startTest();
writeHeaderToLog("Sampling api");

var objs:Array=new Array();
class simpleobject {
    var str:String;
    function simpleobject(s:String) { 
        this.str=s;
    }
}


stopSampling();
if (isdebugger) {
    AddTestCase("StopBeforeStarted: call stopSampling() before startSampling is called",
    0,
    getSampleCount()
    );
} else {
    AddTestCase("StopBeforeStarted: call stopSampling() before startSampling is called",
    -1,
    getSampleCount()
    );
}

pauseSampling();
if (isdebugger) {
    AddTestCase("PauseBeforeStarted: call pauseSampling() before startSampling is called",
    0,
    getSampleCount()
    );
}
sampleInternalAllocs(true);
startSampling();
startSampling();
startSampling();
startSampling();
simpleLoop();
pauseSampling();

if (isdebugger) {
    AddTestCase(
      "StartSamplingMult:  call startSampling() multiple times in a row",
      true,
      getSampleCount()>50
    );
}
clearSamples();
clearSamples();

if (isdebugger) {
    AddTestCase(
      "ClearSamplingTwice: call clearSampling() twice in a row",
      0,
      getSampleCount()
    );
}
startSampling();
simpleLoop();
pauseSampling();
pauseSampling();
pauseSampling();

if (isdebugger) {
    AddTestCase(
      "PauseSamplingTwice: call pauseSamples() twice in a row",
      true,
      getSampleCount()>50
    );
}
test();

function simpleLoop() {
    for (var i:int=0;i<100;i++) {
       objs.push(new simpleobject(""+i));
    }
}
