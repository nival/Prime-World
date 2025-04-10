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
var TITLE   = "Iterate and investigate the sample data";

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
function simpleLoop() {
    for (var i:int=0;i<10;i++) {
       objs.push(new simpleobject(""+i));
    }
}

sampleInternalAllocs(true);
startSampling();
simpleLoop();
pauseSampling();

var nallocs:uint=0;
var ndeallocs:uint=0;
var allocs:uint=0;
var deallocs:uint=0;
var alloctable:Array=new Array();
var badalloc:String="";
for each (var sample in getSamples()) {
    var nos : NewObjectSample;
    var dos : DeleteObjectSample;
    if ( (nos=sample as NewObjectSample) != null) {
        nallocs++;
        allocs+=nos.size;
        alloctable[nos.id]=nos.size;   	
    } else if ( (dos=sample as DeleteObjectSample) !=null) {
        ndeallocs++;
	deallocs+=dos.size;
	if (alloctable[dos.id]!=dos.size) {
	    badalloc+="dealloc id:"+dos.id+" "+dos.size+" does not match alloc size: "+alloctable[dos.id]+"\n";
	}
    }
}
print("nallocs  ="+nallocs+" allocs  ="+allocs);
print("ndeallocs="+ndeallocs+" deallocs="+deallocs);

AddTestCase(
    "ProcessSamples: deallocs match allocs",
    "",
    badalloc
);

var sizeAllocs:uint=0;
var sizeDeallocs:uint=0;
for each (var sample1 in getSamples()) {
    var nos1 : NewObjectSample;
    var dos1 : DeleteObjectSample;
    if ( (nos1=sample as NewObjectSample) != null) {
        sizeAllocs+=getSize(nos1.object);
    }
}
print("sizeAllocs="+sizeAllocs);
print("sizeDeAllocs="+sizeDeallocs);

if (isdebugger) {
    AddTestCase(
        "GetSizeSamples: test getSize on NewObjectSamples returns a positive value",
        true,
        sizeAllocs>0
    );
} else {
    AddTestCase(
        "GetSizeSamples: test getSize on NewObjectSamples returns a positive value",
        false,
        sizeAllocs>0
    );
}    
var objs1:Object=new Object();
for each (var sample2 in getSamples()) {
    var nos2 : NewObjectSample;
    var dos2 : DeleteObjectSample;
    if ( (nos2=sample2 as NewObjectSample) != null) {
        if (objs1.hasOwnProperty(nos2.stack[0].name)==false)
            objs1[nos2.stack[0].name]=0;
        objs1[nos2.stack[0].name]+=nos2.size;
    }
}
for (var item in objs1) {
   print(item+" "+objs1[item]);
}
if (isdebugger) {
    AddTestCase(
        "InternalsInStack: assert the [verify] internal is shown in the samples and has > 0 size",
        true,
        objs1['[verify]']>0
    );
}

for (var sample3 in getSamples()) {
    print("getsample:"+sample3);
}

test();

}