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
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
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

package avmplus 
{
    import flash.utils.ByteArray

	// this namespace exists solely so that nativegen.py will encounter them during shell building,
	// thus giving us a test case for parsing methods with custom namespaces in nativegen.py
	namespace ns_example = "http://www.example.com"

	// this interface exists solely so that nativegen.py will encounter them during shell building,
	// thus giving us a test case for interface parsing in nativegen.py
	interface ITest
	{
		function test();
	}
	class CTest //implements ITest
	{
		public function test() { }
	}

	// this class exists solely to test native classes that use MI.
	[native(cls="::avmshell::MIClass", instance="::avmshell::MIObject", methods="::avmshell::MIObjectImpl")]
	internal class MI
	{
		public native function plus(i:Number):Number;
	}

	[native(cls="::avmshell::SystemClass", methods="auto")]
	public class System
	{
		// this metadata exists solely so that nativegen.py will encounter it during shell building,
		// thus giving us a test case for metadata parsing in nativegen.py
		[foo]
		public native static function exit(status:int):void

		// this metadata exists solely so that nativegen.py will encounter it during shell building,
		// thus giving us a test case for metadata parsing in nativegen.py
		[bar(attr="whatever")]
		public native static function exec(command:String):int

		public native static function getAvmplusVersion():String
		public native static function trace(a:Array):void
		public native static function write(s:String):void
		public native static function debugger():void
		public native static function isDebugger():Boolean
		public native static function getTimer():uint
		private native static function getArgv():Array
		public static const argv:Array = getArgv();
		public native static function readLine():String;

		// Amount of real memory we've aqcuired from the OS
		public native static function get totalMemory():Number;

		// Part of totalMemory we aren't using
		public native static function get freeMemory():Number;

		// process wide size of resident private memory 
		public native static function get privateMemory():Number;

        // Initiate a garbage collection; future versions will not return before completed.
        public native static function forceFullCollection():void;

        // Queue a garbage collection request.
        public native static function queueCollection():void;

		// function exists solely to test native-methods with custom namespaces
		ns_example native static function nstest():void;

		// function exists solely to test ScriptObject::isGlobalObject
		public native static function isGlobal(o:Object):Boolean;
	}
	
	[native(cls="::avmshell::FileClass", methods="auto")]
	public class File
	{
		public native static function exists(filename:String):Boolean;
		public native static function read(filename:String):String;
		public native static function write(filename:String, data:String):void;

		public static function fileToByteArray(filename:String, readOnly:Boolean):ByteArray
		{
			return ByteArray.readFile(filename)
		}

		public static function writeByteArray(filename:String, bytes:ByteArray):Boolean
		{
			bytes.writeFile(filename)
			return true
		}
	}

	public function debugger()
	{
		System.debugger()
	}
}

// The flash.system package is present so identical ATS test media can be used
// in the command-line VM and the Player
package flash.system
{
	import avmplus.*;
	
	public final class Capabilities
	{
		public static function get playerType():String { return "AVMPlus"; }
		public static function get isDebugger():Boolean { return System.isDebugger(); }
	}
}
		
package {

	import avmplus.*

	public function getClassByName(name:String):Class
	{
		return Domain.currentDomain.getClass(name);
	}
		
	// nonstandard extensions to ECMAScript
	public function print(...s)
	{
		System.trace(s)
	}

	// nonstandard Flash Player extensions
	public function trace(...s)
	{
		System.trace(s)
	}

	public function getTimer():uint
	{
		return System.getTimer()
	}

	public function readLine():String
	{
		return System.readLine()
	}
}

// test library code

/*
 tests
 - unversioned names: are in all versions, as though version 0
 - versioned names: are not visible to smaller versions (bindings, not number)
 - multiple versioned names: are visible to all compatible versions
 - class, interface, method, accessor, slot, static names
 - running multiple active versions
*/

// API Versioning - Globals
package avmplus {
    public var public_var:Boolean = true;
    [API(660)] public var public_var_660:Boolean = true;
    [API(661)] public var public_var_661:Boolean = true;
    [API(662)] public var public_var_662:Boolean = true;
    [API(663)] public var public_var_663:Boolean = true;
    [API(664)] public var public_var_664:Boolean = true;
    [API(665)] public var public_var_665:Boolean = true;
    //[API(666)] public var public_var_666:Boolean = true;
    //[API(667)] public var public_var_667:Boolean = true;
    [API(661,662)] public var public_var_661_662:Boolean = true;
    [API(666,660)] public var public_var_666_660:Boolean = true;
    [API(664,662,666)] public var public_var_664_662_666:Boolean = true;
    [API(665,660,661,662)] public var public_var_665_660_661_662:Boolean = true;
    
    public const public_const:Boolean = true;
    [API(660)] public const public_const_660:Boolean = true;
    [API(661)] public const public_const_661:Boolean = true;
    [API(662)] public const public_const_662:Boolean = true;
    [API(663)] public const public_const_663:Boolean = true;
    [API(664)] public const public_const_664:Boolean = true;
    [API(665)] public const public_const_665:Boolean = true;
    //[API(666)] public const public_const_666:Boolean = true;
    //[API(667)] public const public_const_667:Boolean = true;
    [API(661,662)] public const public_const_661_662:Boolean = true;
    [API(666,660)] public const public_const_666_660:Boolean = true;
    [API(664,662,666)] public const public_const_664_662_666:Boolean = true;
    [API(665,660,661,662)] public const public_const_665_660_661_662:Boolean = true;
    
    public function public_function():Boolean { return true; } 
    [API(660)] public function public_function_660():Boolean { return true; } 
    [API(661)] public function public_function_661():Boolean { return true; } 
    [API(662)] public function public_function_662():Boolean { return true; } 
    [API(663)] public function public_function_663():Boolean { return true; } 
    [API(664)] public function public_function_664():Boolean { return true; } 
    [API(665)] public function public_function_665():Boolean { return true; } 
    //[API(666)] public function public_function_666():Boolean { return true; } 
    //[API(667)] public function public_function_667():Boolean { return true; } 
    [API(661,662)] public function public_function_661_662():Boolean { return true; } 
    [API(666,660)] public function public_function_666_660():Boolean { return true; } 
    [API(664,662,666)] public function public_function_664_662_666():Boolean { return true; } 
    [API(665,660,661,662)] public function public_function_665_660_661_662():Boolean { return true; }
    
    public function get public_getset():Boolean { return true; } 
    [API(660)] public function get public_getset_660():Boolean { return true; } 
    [API(661)] public function get public_getset_661():Boolean { return true; } 
    [API(662)] public function get public_getset_662():Boolean { return true; } 
    [API(663)] public function get public_getset_663():Boolean { return true; } 
    [API(664)] public function get public_getset_664():Boolean { return true; } 
    [API(665)] public function get public_getset_665():Boolean { return true; } 
    //[API(666)] public function get public_getset_666():Boolean { return true; } 
    //[API(667)] public function get public_getset_667():Boolean { return true; } 
    [API(661,662)] public function get public_getset_661_662():Boolean { return true; } 
    [API(666,660)] public function get public_getset_666_660():Boolean { return true; } 
    [API(664,662,666)] public function get public_getset_664_662_666():Boolean { return true; } 
    [API(665,660,661,662)] public function get public_getset_665_660_661_662():Boolean { return true; }
    
    public function set public_getset(x:*):void {  } 
    [API(660)] public function set public_getset_660(x:*):void {  } 
    [API(661)] public function set public_getset_661(x:*):void {  } 
    [API(662)] public function set public_getset_662(x:*):void {  } 
    [API(663)] public function set public_getset_663(x:*):void {  } 
    [API(664)] public function set public_getset_664(x:*):void {  } 
    [API(665)] public function set public_getset_665(x:*):void {  } 
    //[API(666)] public function set public_getset_666(x:*):void {  } 
    //[API(667)] public function set public_getset_667(x:*):void {  } 
    [API(661,662)] public function set public_getset_661_662(x:*):void {  } 
    [API(666,660)] public function set public_getset_666_660(x:*):void {  } 
    [API(664,662,666)] public function set public_getset_664_662_666(x:*):void {  } 
    [API(665,660,661,662)] public function set public_getset_665_660_661_662(x:*):void {  }
    
}

// API Versioning - Classes
package avmplus {
    public class public_class {
        
        public var public_var:Boolean = true;
        [API(660)] public var public_var_660:Boolean = true;
        [API(661)] public var public_var_661:Boolean = true;
        [API(662)] public var public_var_662:Boolean = true;
        [API(663)] public var public_var_663:Boolean = true;
        [API(664)] public var public_var_664:Boolean = true;
        [API(665)] public var public_var_665:Boolean = true;
        //[API(666)] public var public_var_666:Boolean = true;
        //[API(667)] public var public_var_667:Boolean = true;
        [API(661,662)] public var public_var_661_662:Boolean = true;
        [API(666,660)] public var public_var_666_660:Boolean = true;
        [API(664,662,666)] public var public_var_664_662_666:Boolean = true;
        [API(665,660,661,662)] public var public_var_665_660_661_662:Boolean = true;
        
        public const public_const:Boolean = true;
        [API(660)] public const public_const_660:Boolean = true;
        [API(661)] public const public_const_661:Boolean = true;
        [API(662)] public const public_const_662:Boolean = true;
        [API(663)] public const public_const_663:Boolean = true;
        [API(664)] public const public_const_664:Boolean = true;
        [API(665)] public const public_const_665:Boolean = true;
        //[API(666)] public const public_const_666:Boolean = true;
        //[API(667)] public const public_const_667:Boolean = true;
        [API(661,662)] public const public_const_661_662:Boolean = true;
        [API(666,660)] public const public_const_666_660:Boolean = true;
        [API(664,662,666)] public const public_const_664_662_666:Boolean = true;
        [API(665,660,661,662)] public const public_const_665_660_661_662:Boolean = true;
        
        public function public_function():Boolean { return true; } 
        [API(660)] public function public_function_660():Boolean { return true; } 
        [API(661)] public function public_function_661():Boolean { return true; } 
        [API(662)] public function public_function_662():Boolean { return true; } 
        [API(663)] public function public_function_663():Boolean { return true; } 
        [API(664)] public function public_function_664():Boolean { return true; } 
        [API(665)] public function public_function_665():Boolean { return true; } 
        //[API(666)] public function public_function_666():Boolean { return true; } 
        //[API(667)] public function public_function_667():Boolean { return true; } 
        [API(661,662)] public function public_function_661_662():Boolean { return true; } 
        [API(666,660)] public function public_function_666_660():Boolean { return true; } 
        [API(664,662,666)] public function public_function_664_662_666():Boolean { return true; } 
        [API(665,660,661,662)] public function public_function_665_660_661_662():Boolean { return true; }
    
        public function get public_getset():Boolean { return true; } 
        [API(660)] public function get public_getset_660():Boolean { return true; } 
        [API(661)] public function get public_getset_661():Boolean { return true; } 
        [API(662)] public function get public_getset_662():Boolean { return true; } 
        [API(663)] public function get public_getset_663():Boolean { return true; } 
        [API(664)] public function get public_getset_664():Boolean { return true; } 
        [API(665)] public function get public_getset_665():Boolean { return true; } 
        //[API(666)] public function get public_getset_666():Boolean { return true; } 
        //[API(667)] public function get public_getset_667():Boolean { return true; } 
        [API(661,662)] public function get public_getset_661_662():Boolean { return true; } 
        [API(666,660)] public function get public_getset_666_660():Boolean { return true; } 
        [API(664,662,666)] public function get public_getset_664_662_666():Boolean { return true; } 
        [API(665,660,661,662)] public function get public_getset_665_660_661_662():Boolean { return true; }
        
        public function set public_getset(x:*):void {  } 
        [API(660)] public function set public_getset_660(x:*):void {  } 
        [API(661)] public function set public_getset_661(x:*):void {  } 
        [API(662)] public function set public_getset_662(x:*):void {  } 
        [API(663)] public function set public_getset_663(x:*):void {  } 
        [API(664)] public function set public_getset_664(x:*):void {  } 
        [API(665)] public function set public_getset_665(x:*):void {  } 
        //[API(666)] public function set public_getset_666(x:*):void {  } 
        //[API(667)] public function set public_getset_667(x:*):void {  } 
        [API(661,662)] public function set public_getset_661_662(x:*):void {  } 
        [API(666,660)] public function set public_getset_666_660(x:*):void {  } 
        [API(664,662,666)] public function set public_getset_664_662_666(x:*):void {  } 
        [API(665,660,661,662)] public function set public_getset_665_660_661_662(x:*):void {  }
    }
    
    [API(660)] public class  public_class_660 {  } 
    [API(661)] public class  public_class_661 {  } 
    [API(662)] public class  public_class_662 {  } 
    [API(663)] public class  public_class_663 {  } 
    [API(664)] public class  public_class_664 {  } 
    [API(665)] public class  public_class_665 {  } 
    [API(661,662)] public class  public_class_661_662 {  } 
    [API(666,660)] public class  public_class_666_660 {  } 
    [API(664,662,666)] public class  public_class_664_662_666 {  } 
    [API(665,660,661,662)] public class  public_class_665_660_661_662 {  }
    
    public interface  public_interface {}
    [API(660)] public interface  public_interface_660 {  } 
    [API(661)] public interface  public_interface_661 {  } 
    [API(662)] public interface  public_interface_662 {  } 
    [API(663)] public interface  public_interface_663 {  } 
    [API(664)] public interface  public_interface_664 {  } 
    [API(665)] public interface  public_interface_665 {  } 
    [API(661,662)] public interface  public_interface_661_662 {  } 
    [API(666,660)] public interface  public_interface_666_660 {  } 
    [API(664,662,666)] public interface  public_interface_664_662_666 {  } 
    [API(665,660,661,662)] public interface  public_interface_665_660_661_662 {  }
    
}