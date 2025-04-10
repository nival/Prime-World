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
    import flash.utils.ByteArray

    var SECTION = "File";
    var VERSION = "as3";
    startTest();
    var TITLE   = "test File class";

    writeHeaderToLog( SECTION + " "+ TITLE );

    AddTestCase("File does not exist",
    false,
    File.exists("nothing"));

    File.write("test.txt","test file");

    AddTestCase("File exists just written file",
      true,
      File.exists("test.txt"));

    AddTestCase("File read test file",
      "test file",
      File.read("test.txt"));

    var err="";
    try {
        File.read('unknown.txt');
    } catch (e) {
        err=e.toString();
    }
    AddTestCase("File read on unknown file should throw exception",
      "Error: Error #1500",
      err.substring(0,18));

    File.write("test2.ba","sample test data");
    var ba:ByteArray=File.fileToByteArray("test2.ba",false);
    AddTestCase("File.fileToByteArray length",true,ba.length=="sample test data".length);

    // Regression for https://bugzilla.mozilla.org/show_bug.cgi?id=473863
    //      File.read fail for binary files
    
    // ByteArray with partial bad utf-8 sequence
    var bytearray_bad : ByteArray = new ByteArray();
    bytearray_bad[0]=0xE4; // 19968
    bytearray_bad[1]=0xB8;
    bytearray_bad[2]=0x80;
    bytearray_bad[3]=0xE4; // bad sequence
    bytearray_bad[4]=0xE4; // 19968
    bytearray_bad[5]=0xB8;
    bytearray_bad[6]=0x80;
    
    File.write("test.bin", bytearray_bad);
    AddTestCase("File read binary test file",
                "\u4e00\u00E4\u4e00",
                File.read("test.bin")
               );


    test();
