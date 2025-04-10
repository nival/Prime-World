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
 * Portions created by the Initial Developer are Copyright (C) 2009
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

/* testcases: 
 *   backward branches: execute loop to verify significant number of samples
 */

package {

    import flash.sampler.*
    import avmplus.*

    var SECTION = "Sampling";
    var VERSION = "AS3";
    var TITLE   = "backward branches";

    var isdebugger=System.isDebugger();

    startTest();
    writeHeaderToLog("Sampling backward branches tests");

    var callcount:uint=0;
    var samplescount:uint=0;    
    var stoppagetime=0;

    function calculatepi(n:uint):Number {
        var sign=1;
        var result=0;
        var start=getTimer();
        var i=1;
        while (true) {
           callcount+=1;
           result+=sign*4/(i*2-1);
           sign*=-1;
           i++;
           if ((getTimer()-start>n && callcount>n) || getTimer()-start>5000)
               break;
        }
        return result;
    }
    function samplecallback() {
        var time=getTimer();
        samplescount+=getSampleCount();
        clearSamples();
        stoppagetime+=getTimer()-time;
        return true;
    }

    setSamplerCallback(samplecallback);
    sampleInternalAllocs(false);
    startSampling();
    var totaltime=getTimer();    
    var result=calculatepi(1000);
    pauseSampling();
    totaltime=getTimer()-totaltime-stoppagetime;
    samplescount+=getSampleCount();
    AddTestCase("assert the number of samples is greater than 20, actual is "+samplescount,
        true,
        samplescount>20);
    test();
}