/**
 * ***** BEGIN LICENSE BLOCK *****
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
 * The Original Code is [Open Source Virtual Machine].
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

package { 
    import flash.utils.ByteArray;
    import flash.net.Socket;
    import flash.display.*;
    import flash.system.*;
    import flash.text.*;
    import flash.events.*;

    var tf;
    var linectr:int=0;
    var contents:String="";
    public function print(...s):void {
        for (var i=0;i<s.length;i++) {
            trace("[flashrunner]"+s[i]);
            contents+=s[i]+"\n";
            if (linectr<50)
     	        tf.text+=s[i]+"\n";
            linectr++;
        }
    }
    public class template extends Sprite {
        var loader:Loader;
        var context; 
        var sock:Socket;
        public function template():void {
            setup();
            loadProgram();
        }
        public function setup():void {
            var versionString=Capabilities.playerType+" "+Capabilities.version;
            loader=new Loader();
            loader.contentLoaderInfo.addEventListener(Event.INIT,initHandler);
            loader.contentLoaderInfo.addEventListener(Event.COMPLETE,completeHandler);
            loader.contentLoaderInfo.addEventListener(IOErrorEvent.IO_ERROR, ioErrorHandler);
            tf=new TextField();
            tf.x=0;tf.y=0;
            tf.width=550;tf.height=400;
            tf.text=versionString+"\n";
            addChild(tf);
        }
        public function sendresults() {
            var server:String="localhost";
            var serverPort:uint=1189;
            var ok=true;
            try {
                sock=new Socket();
                sock.addEventListener(Event.CONNECT,onConnect);
                sock.addEventListener(ProgressEvent.SOCKET_DATA, onData);
                sock.connect(server,serverPort);
            } catch (e) {
                ok=false;
                print("error sending results: "+e)
            }
    //     if (ok) print("sent results successfully");
        }
        private function onConnect(event:Event):void {
            contents="player version: "+Capabilities.version+"\n"+contents;
            if (contents.length>4096) {
                var ptr=0;
                while(ptr<contents.length) {
                    sock.writeUTFBytes(contents.substring(ptr,Math.min(ptr+1000,contents.length)));
                    ptr+=1000;
                }
            } else {
                sock.writeUTFBytes(contents);
            }
            sock.writeByte(13);
            sock.flush();
            sock.close();
    //      print("sent results over socket");
        }
        private function onData(event:ProgressEvent):void {
            message.text='onData event received at '+new Date();
        }
        public function initHandler(event:Event):void {
        }
        public function completeHandler(event:Event):void {
    //      print("loader finished, sending results");
            sendresults();
        }
        public function ioErrorHandler(event:Event):void {
            print("error thrown loading bytes")
        }
        public function loadProgram():void {
            // this line must match exact for code generation
            var bytes=[];//pointer
            var bytearray:ByteArray=new ByteArray();
            for (var i:uint=0;i<bytes.length;i++) {
                bytearray.writeByte(bytes[i]);
            }
            loader.loadBytes(bytearray);
        }
    }
}
