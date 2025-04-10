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

    import flash.utils.ByteArray
    import avmplus.File

    var SECTION = "ByteArray";
    var VERSION = "as3";
    startTest();
    var TITLE   = "test ByteArray class";

    writeHeaderToLog( SECTION + " "+ TITLE );

    // test constructors

    var bytearray:ByteArray=new ByteArray();
    AddTestCase(
      "ByteArray constructor no args",
      true,
      bytearray!=null
      );

    // operations on empty bytearray

    AddTestCase(
      "ByteArray length of empty",
      0,
      bytearray.length);

    AddTestCase(
      "ByteArray toString empty",
      "",
      bytearray.toString())

    AddTestCase(
      "ByteArray available on empty",
      0, 
      bytearray.bytesAvailable);

// boolean
    bytearray.writeBoolean(true);
    bytearray.writeBoolean(false);
    bytearray.position=0;
    AddTestCase(
      "ByteArray move position to 0",
      0,
      bytearray.position);
    AddTestCase(
      "ByteArray write/read boolean true",
      true,
      bytearray.readBoolean());

    AddTestCase(
      "ByteArray write/read boolean false",
      false,
      bytearray.readBoolean());

// short
    bytearray.position=0;
    bytearray.writeShort(100);
    bytearray.position=0;
    AddTestCase(
     "ByteArray readShort",
     100,
     bytearray.readShort());

// short
    bytearray.position=0;
    bytearray.writeShort(-65436);
    bytearray.position=0;
    AddTestCase(
     "ByteArray readUnsignedShort",
     100,
     bytearray.readUnsignedShort());

// int
    bytearray.position=0;
    bytearray.writeInt(100);
    bytearray.position=0;
    AddTestCase(
     "ByteArray readInt",
     100,
     bytearray.readInt());
   
// unsigned int
    bytearray.position=0;
    bytearray.writeUnsignedInt(100);
    bytearray.position=0;
    AddTestCase(
     "ByteArray readUnsignedInt",
     100,
     bytearray.readUnsignedInt());

// float
    bytearray.position=0;
    bytearray.writeFloat(-3.14);
    bytearray.position=0;
    AddTestCase(
     "ByteArray readFloat with 0.001",
     true,
     -3.14-bytearray.readFloat()<0.01);

// float
    bytearray.position=0;
    bytearray.writeDouble(-3.14);
    bytearray.position=0;
    AddTestCase(
     "ByteArray readDouble with 0.001",
     true,
     -3.14-bytearray.readDouble()<0.01);

//  byte
    bytearray.position=0;
    bytearray.writeByte(-257);
    bytearray.position=0;
    AddTestCase(
     "ByteArray readByte",
     -1,
     bytearray.readByte());

// unsigned byte
    bytearray.position=0;
    bytearray.writeByte(-259);
    bytearray.position=0;
    AddTestCase(
     "ByteArray readByte",
     253,
     bytearray.readUnsignedByte());

// utf
    bytearray.position=0;
    bytearray.writeUTF("string");
    bytearray.position=0;
    AddTestCase(
     "ByteArray length of utf string",
     8,
     bytearray.length);
    AddTestCase(
     "ByteArray readUTF",
     "string",
     bytearray.readUTF());

// utf
    bytearray.position=0;
    bytearray.length=0;
    bytearray.writeUTFBytes("string");
    bytearray.position=0;
    AddTestCase(
     "ByteArray length of utf bytes string",
     6,
     bytearray.length);
    AddTestCase(
     "ByteArray readUTFBytes",
     "string",
     bytearray.readUTFBytes(6));

// compress/uncompress
    bytearray.compress();
    AddTestCase(
     "ByteArray length after compress",
     14,
     bytearray.length);

    bytearray.uncompress();
    AddTestCase(
     "ByteArray length after uncompress",
     6,
     bytearray.length);

    bytearray.length=0;
    bytearray.compress();
    AddTestCase(
     "ByteArray length after empty compress",
     0,
     bytearray.length);

    bytearray.uncompress();
    AddTestCase(
     "ByteArray length after empty uncompress",
     0,
     bytearray.length);

// endian
    AddTestCase(
     "get default endian",
     "bigEndian",
     bytearray.endian);

    bytearray.endian="littleEndian";
    AddTestCase(
     "set endian littleEndian",
     "littleEndian",
     bytearray.endian);

    bytearray.endian="bigEndian";
    AddTestCase(
     "set endian bigEndian",
     "bigEndian",
     bytearray.endian);

    var err="none";
    try {
        bytearray.endian="none";
    } catch (e) {
        err=e.toString();
    }
    AddTestCase(
     "exception thrown when endian is to littleEndian or bigEndian",
     "ArgumentError: Error #1508",
     err.substring(0,26));
    AddTestCase(
     "endian value is uchanged after invalid set",
     "bigEndian",
     bytearray.endian);

// [] syntax
    bytearray.position=0;
    bytearray.writeByte(10);
    bytearray.writeByte(11);
    bytearray.writeByte(12);
    AddTestCase(
     "ByteArray get [] syntax",
     12,
     bytearray[2]);
   
    bytearray[2]=13;
    AddTestCase(
     "ByteArray set [] syntax",
     13,
     bytearray[2]);

// fill empty spaces with 0s
    bytearray.length=10;
    AddTestCase(
     "ByteArray empty slots filled with 0",
     0,
     bytearray[9]);

    var bytearray_shrink=new ByteArray;
    bytearray_shrink.length=10;    
    bytearray_shrink.length=5;
    AddTestCase(
     "ByteArray shrink length",
     5,
     bytearray_shrink.length);

    
// readBytes(ByteArray)
    bytearray.length=10;
    var bytearray2:ByteArray=new ByteArray;
    bytearray.readBytes(bytearray2,0,0);

    AddTestCase(
     "ByteArray constructor with ByteArray copies values, check values",
     103,
     bytearray2[2]);

    var bytearray3:ByteArray=new ByteArray;
    bytearray.readBytes(bytearray3,8);
    AddTestCase(
     "ByteArray readBytes 8 length copies values, check size",
     8,
     bytearray3.length);

// writeBytes
    var bytearray4=new ByteArray;
    bytearray4.writeBytes(bytearray);
    AddTestCase(
     "ByteArray writeBytes",
     10,
     bytearray4.length);

    var bytearray5=new ByteArray;
    bytearray5.writeBytes(bytearray,1,5);
    AddTestCase(
     "ByteArray writeBytes",
     5,
     bytearray5.length);

// hasAtomProperty
    var bytearray_atom=new ByteArray;
    bytearray_atom.writeByte(1);
    bytearray_atom.writeByte(2);
    bytearray_atom.writeByte(3);
    AddTestCase(
      "ByteArray hasAtomProperty true",
      true,
      1 in bytearray_atom);
    AddTestCase(
      "ByteArray hasAtomProperty false",
      false,
      5 in bytearray_atom);
    
// read/write file
    bytearray_atom.writeFile('test.ba');
    var bytearray_read=ByteArray.readFile('test.ba');
    AddTestCase(
      "ByteArray read/writeFile",
      3,
      bytearray_read.length);

    var err2="";
    try {
        var bytearray_badread=ByteArray.readFile('foo.ba');
    } catch (e) {
        err2=e.toString();
    }
    AddTestCase(
      "ByteArray read/writeFile exception",
      "Error: Error #1500",
      err2.substring(0,18));

// bom/toString
    bytearray_bom=new ByteArray;
    bytearray_bom[0]=0xef;
    bytearray_bom[1]=0xbb;
    bytearray_bom[2]=0xbf;
    bytearray_bom[3]=100;
    bytearray_bom[4]=97;
    bytearray_bom[5]=110;
    bytearray_bom[6]=33;
    AddTestCase(
      "ByteArray with bom toString",
      "dan!",
      bytearray_bom.toString());

    bytearray_str=new ByteArray;
    bytearray_str[0]=100;
    bytearray_str[1]=97;
    bytearray_str[2]=110;
    bytearray_str[3]=33;
    AddTestCase(
      "ByteArray with no bom toString",
      "dan!",
      bytearray_str.toString());

// bad partial sequence
    var bytearray_bad : ByteArray = new ByteArray();
    bytearray_bad[0]=0xE4; // 19968
    bytearray_bad[1]=0xB8;
    bytearray_bad[2]=0x80;
    bytearray_bad[3]=0xE4; // bad sequence
    bytearray_bad[4]=0xE4; // 19968
    bytearray_bad[5]=0xB8;
    bytearray_bad[6]=0x80;
    AddTestCase(
      "ByteArray with partial bad utf-8 sequence",
      "\u4e00\u00E4\u4e00",
      bytearray_bad.toString());

// truncated utf-8 sequence
    bytearray_bad = new ByteArray();
    bytearray_bad[0]=0xE4; // truncated sequence
    bytearray_bad[1]=0xB8;
    AddTestCase(
      "ByteArray with truncated utf-8 sequence",
      "\u00E4\u00B8",
      bytearray_bad.toString());

// utf-8 sequence > 0x1FFFF
    bytearray_bad = new ByteArray();
    bytearray_bad[0]=0xFB; // character == 0x3FFFF
    bytearray_bad[1]=0xBF;
    bytearray_bad[2]=0xBF;
    bytearray_bad[3]=0xBF;
    bytearray_bad[4]=0xBF;
    bytearray_bad[5]=0xE4; // 19968
    bytearray_bad[6]=0xB8;
    bytearray_bad[7]=0x80;
    AddTestCase(
      "ByteArray with out-of-range utf-8 sequence",
      "\udbbf\udfff\u00BF\u4e00",
      bytearray_bad.toString());

// compress/uncompress
    var bytearray_compress = new ByteArray();
    bytearray_compress[0]=0xef;
    bytearray_compress[1]=0xbb;
    bytearray_compress[2]=0xbf;
    bytearray_compress[3]=100;
    bytearray_compress[4]=97;
    bytearray_compress[5]=110;
    bytearray_compress[6]=33;
    // original length = 7
    var origlength=bytearray_compress.length;
    bytearray_compress.compress();
    // test the compressed bytearray values are all different from the original
    var compressstate=(bytearray_compress[0]==0xef || 
                       bytearray_compress[1]==0xbb ||
                       bytearray_compress[2]==0xbf ||
                       bytearray_compress[3]==100 ||
                       bytearray_compress[4]==97);
    // check the compressed length = 15 (small strings compress larger in zlib)
    var compresslength=bytearray_compress.length;
    bytearray_compress.uncompress();
    // check the uncompress/compress length should equal original length 7
    var restoredlength=bytearray_compress.length;
    var restorestate=(bytearray_compress[0]==0xef && 
                       bytearray_compress[1]==0xbb &&
                       bytearray_compress[2]==0xbf &&
                       bytearray_compress[3]==100 &&
                       bytearray_compress[4]==97 &&
                       bytearray_compress[5]==110 &&
                       bytearray_compress[6]==33
                     );
    AddTestCase("ByteArray.compress bytearray length is different",
                origlength==compresslength,false);
    AddTestCase("ByteArray.compress bytearray contents differ",
                compressstate,false);
    AddTestCase("ByteArray.uncompress bytearray length matches before compress",
                origlength,restoredlength);
    AddTestCase("ByteArray.uncompress uncompressing compressed string matches original",
                restorestate,true);
 
    test();

