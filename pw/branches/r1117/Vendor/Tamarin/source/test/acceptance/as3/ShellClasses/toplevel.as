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

    import avmplus.File

    var SECTION = "toplevel";
    var VERSION = "as3";
    startTest();
    var TITLE   = "test toplevel classes";

    import avmplus.System
    import flash.system.Capabilities

    writeHeaderToLog( SECTION + " "+ TITLE );

    AddTestCase("playerType is AVMPlus",
      "AVMPlus",
      Capabilities.playerType);

    AddTestCase("isDebugger is true/false",
      true,
      Capabilities.isDebugger==true || Capabilities.isDebugger==false
    );

    AddTestCase("System getAvmplusVersion",
      true,
      System.getAvmplusVersion().length>0);

    AddTestCase("System argv",
      0,
      System.argv.length);

    AddTestCase("System.isDebugger",
      true,
      System.isDebugger()==true || System.isDebugger()==false);

    AddTestCase("System.freeMemory >=0",
      true,
      System.freeMemory>=0);

    AddTestCase("System.freeMemory <= System.totalMemory",
      true,
      System.freeMemory<=System.totalMemory);

    AddTestCase("System.totalMemory >0",
      true,
      System.totalMemory>0);

    AddTestCase("System.privateMemory >0",
      true,
      System.privateMemory>0);

    print("metric System.totalMemory "+System.totalMemory);
    print("metric System.freeMemory "+System.freeMemory);
    print("metric System.privateMemory "+System.privateMemory);


    var err="";
    try {
        System.exec();
    } catch (e) {
        err=e.toString();
    }
    AddTestCase("System.exec no params throws exception",
      "ArgumentError: Error #1063",
      err.substring(0,26));

    var ct=0;
    while (getTimer()==0) {
      ct++;
      if (ct==1000000) break;
    }
    var time=getTimer();
    AddTestCase("System getTimer>0",
      true,
      time>0);
    print("metric System.getTimer "+getTimer());
    
    
    // Bug 407894: getTimer() returns values that are a power of 2
    // https://bug407894.bugzilla.mozilla.org/attachment.cgi?id=293543
    function notPower2():Boolean {
        // it is possible that there could be a timer returned that is a power
        // of 2, so check multiple times in a row that the timer is not a power of 2.
        var count:int = 0;
        var sleeper:int = 2;
        for(var i:int = 0; i < 5; i++){
            var t1:int = getTimer();  
            var t2:int;
            while ( (t2 = getTimer()) == t1 ) {
                // Do some work in order to take up CPU time, keep doing this until the 
                // a call to getTimer() != what we have in t1
                for(var j:int = 0; j < sleeper; j++){ var x:Array = [1,2,3,4,5,6,7,8,9,10]; }
                if (sleeper == 2)
                    sleeper <<= 2;
            }
            // determine if the t1 or t2 are a power of 2
            if ( (t1 & (t1 -1)) == 0 )
                count++;
            if ( (t2 & (t2 -1)) == 0 )
                count++;
        }
        if (count == 10)
            return false;
        else
            return true;
    }
    
    AddTestCase("System getTimer bug 407894",
      true,
      notPower2());


    test();

    
    System.trace(["trace message ln cr \n\r"]);
    System.trace(["trace message ln \n","trace message cr \r"]);
    System.write("write message to stdout");
    System.exit(0);
    
    