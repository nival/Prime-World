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
 * The Original Code is [ActiveScripting implemented with Tamarin].
 *
 * The Initial Developer of the Original Code is Mozilla Corp.
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Mark Hammond
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

// hackery - for now, this file is "built" via:
// %java -ea -DAS3 -DAVMPLUS -classpath ../utils/asc.jar macromedia.asc.embedding.ScriptCompiler -abcfuture -builtin -d -import ../core/builtin.abc -import ../esc/bin/esc-core.es.abc -import ../esc/bin/eval-support.es.abc -out axtoplevel mscom.as Domain.as ../shell/ByteArray.as && move /y ..\shell\axtoplevel.* .
// Note the '-d' will include debug info which is handy in the early days...

package axtam 
{
	// should possibly be private...
	public class System
	{
		public native static function getAvmplusVersion():String
		public native static function write(s:String):void
		public native static function trace(a:Array):void
		public native static function debugger():void
		public native static function isDebugger():Boolean
		public native static function nativeDebugBreak():void
	}
}

package 
{
	// a global 'print' statement...
	public function print(...s)
	{
		axtam.System.trace(s)
	}

	namespace ESC = "ESC"; // implicit namespace from esc-env.ast

	// 'eval' support is still a work in progress.
	public function eval(...rest) {} // just needs to exist!!
}

// a clone of the File class from shell/toplevel.as
package avmplus {
	public class File
	{
		public native static function exists(filename:String):String;
		public native static function read(filename:String):String;
		public native static function write(filename:String, data:String):void;
	}
}

package axtam.com {
	// Its not clear if we should subclass the standard 'Error', but given
	// it has its own concept of 'Message' and 'ID', it doesn't seem a good fit.
	// Maybe a new base-class should be introduced?
	public dynamic class Error
	{
		public static const S_OK = 0
		public static const S_FALSE = 1

		public static const E_NOTIMPL = 0x80004001
		public static const E_INVALIDARG = 0x80070057
		public static const E_UNEXPECTED = 0x8000ffff
		public static const E_FAIL = 0x80004005
		public static const E_NOINTERFACE = 0x80000004

		public var hresult: int
		public var excepinfo: EXCEPINFO
		function Error(hresult, excepinfo:EXCEPINFO = null) {
			this.hresult = hresult;
			this.excepinfo = excepinfo;
		}

		prototype.toString = function():String
		{
			var excepinfo:EXCEPINFO = this.excepinfo;
			var e:axtam.com.Error = this
			var code:uint;
			var msg:String;
			code = e.hresult;
			if (excepinfo) {
				// our hresult is almost certainly DISP_E_EXCEPTION, so
				// either of the ones in the excep info are likely to be better
				if (excepinfo.code)
					code = excepinfo.code
				else if (excepinfo.scode)
					code = excepinfo.scode
			}
			if (excepinfo && excepinfo.description) {
				msg = excepinfo.description + " (source:" + excepinfo.source + ", help:" + excepinfo.helpFile + ", helpContext:" + excepinfo.helpContext + ")";
			} else {
				msg = ProviderError.getErrorMessage(code);
			}
			var hv:String = code >= 0 ? code.toString(16) : (code+0x100000000).toString(16)
			return "COM Error 0x" + hv + ": " + msg
		}
		_setPropertyIsEnumerable(prototype, "toString", false);

		// *sob* - I can't get this to work without tamarin throwing exceptions.
		//public native static function getErrorMessage(index:int):String;

		public static function throwError(hresult:int, ... rest)
		{
			// todo: rich error support?
			throw new axtam.com.ProviderError(hresult);
		}

	}
	// This is the actual class that is thrown by script code (see throwError above)
	// When exceptions of this class are thrown, they are not treated as "unhandled",
	// but simply indicate that script code wants a COM error returned.
	public dynamic class ProviderError extends axtam.com.Error {
		function ProviderError(hresult, excepinfo:EXCEPINFO = null) {
			super(hresult, excepinfo)
		}
		// *sob* - see above
		public native static function getErrorMessage(index:int):String;
	}

	// This is the class that is thrown by *native* code when a COM object you are using
	// (such as Window) returns a COM error code.  These are never thrown by script code,
	// and are treated as "unhandled" when the occur - eg, a traceback is printed, debugger
	// semantics followed, etc.
	public dynamic class ConsumerError extends axtam.com.Error {
		function ConsumerError(hresult, excepinfo:EXCEPINFO = null) {
			super(hresult, excepinfo)
		}
		// *sob* - see above
		public native static function getErrorMessage(index:int):String;
	}

	public class EXCEPINFO {
		public native function get code():uint
		public native function get source():String
		public native function get description():String
		public native function get helpFile():String
		public native function get helpContext():uint
		public native function get scode():uint
	}

	// constants go directly in the axtam.com package.
	public const SCRIPTINFO_IUNKNOWN = 0x00000001
	public const SCRIPTINFO_ITYPEINFO = 0x00000002

	public const SCRIPTITEM_ISVISIBLE = 0x00000002
	public const SCRIPTITEM_ISSOURCE = 0x00000004
	public const SCRIPTITEM_GLOBALMEMBERS = 0x00000008
	public const SCRIPTITEM_ISPERSISTENT = 0x00000040
	public const SCRIPTITEM_CODEONLY = 0x00000200
	public const SCRIPTITEM_NOCODE = 0x00000400

	public const SCRIPTSTATE_UNINITIALIZED       = 0
	public const SCRIPTSTATE_INITIALIZED         = 5
	public const SCRIPTSTATE_STARTED             = 1
	public const SCRIPTSTATE_CONNECTED           = 2
	public const SCRIPTSTATE_DISCONNECTED        = 3
	public const SCRIPTSTATE_CLOSED              = 4
}

package axtam.com.consumer {
	// scripting interfaces we consume in AS (ie, implemented externally)
	// Each method listed here corresponds to a native method in the engine, 
	// which inturn delegates to the real COM object.
	// Note that some of these classes have no scriptable methods, but they
	// are used internally
	public class IUnknown
	{
		public function toString():String
		{
			return "[COM Object]"
		}
	}

	// The rest of these 'derive' from IUnknown...
	// An IDispatch object does *not* expose IDispatch methods - instead,
	// it uses IDispatch to provide normal "object.property" style access.
	// This is primarily due to a lack of "catch-alls" and effort required in
	// managing the args used by the native functions.
	// It is "dynamic" as it supports 'expandos'
	public dynamic class IDispatch extends IUnknown
	{
	}

	public class ITypeInfo extends IUnknown
	{
	}

	public class IActiveScriptSite
	{
		// somewhat like GetItemInfo() - but gets both IDispatch and ITypelib,
		// and wraps them in a ScriptObject which can be used from script.
		public native function GetItemInfo(name:String, flags:uint):Array
		public native function GetDocVersionString(): String
		public native function OnStateChange(state:uint):int
		public native function OnEnterScript():int
		public native function OnLeaveScript():int
	}
}

package axtam.com.provider {
	// scripting interfaces provided by AS (ie, for consumption by external
	// code).  As such, there are no classes available for use by JS!
	// A couple of functions are used to *create* such objects, but they
	// are returned via an axtam.com.consumer.IUnknown (which is wrapping
	// the object we provide)
	public native function createDispatchProvider(ob:Object): axtam.com.consumer.IUnknown;
}

package {

	import flash.utils.*; // for our ByteArray clone - either it should die, or we rename the package in our clone!

	public function compileString(str, fname:String = "", startLineNumber:int = 0)
	{
		// NOTE: This requires the patch to bug 432242 (and by the time this
		// comment is stale, we should remove compileString() completely and
		// inline it!
		return ESC::compileStringToBytes(str, fname, startLineNumber+1);
	}
}

package {

	final class NamedItem {
		public var domain:axtam.Domain
		public var host_dispatch:axtam.com.consumer.IDispatch
		public var script_dispatch:axtam.com.consumer.IDispatch
	}

	class ScriptEngine {
		// A hashtable of NamedItem() objects, with a null key being the global object.
		public var namedItems;
		public var codeBlocks; // code blocks "pushed" but not yet executed.
		public var state:int;
		public var site; // IUnknownConsumer

		public function ScriptEngine()
		{
			stateTransitions = _getStateTransitions()
			state = axtam.com.SCRIPTSTATE_UNINITIALIZED
		}
		public function InitNew()
		{
			SetScriptState(axtam.com.SCRIPTSTATE_INITIALIZED)
		}
		public function SetScriptSite(undef)
		{
			// currently arg is ignored!
			site = new axtam.com.consumer.IActiveScriptSite() // XXX - fix me
		}
		public function ParseScriptText(code:String, itemName:String, context:Object, delim:String, sourceCookie:int, lineNumber:int, flags:int)
		{
			// Check for 'invalid' states first.
			if (state==axtam.com.SCRIPTSTATE_UNINITIALIZED || state==axtam.com.SCRIPTSTATE_CLOSED || state==axtam.com.SCRIPTSTATE_DISCONNECTED)
				axtam.com.Error.throwError(axtam.com.Error.E_FAIL)

			// synthesize a filename
			var fname:String = "<script " + sourceCookie + ">"
			var bytes = compileString(code, fname, lineNumber)

			var scriptBlock = {'code': code,
			                   'bytes': bytes,
			                   'item_name' : itemName,
			                   'context' : context,
			                   'delim': delim,
			                   'source_cookie': sourceCookie,
			                   'line_number': lineNumber,
			                   'flags':flags}

			// If flags & SCRIPTTEXT_ISEXPRESSION, we need to do something better.
			// Note that http://blogs.msdn.com/ericlippert/archive/2005/10/11/479696.aspx
			// says the engine moves to 'started' once this flag is specified.
			// assert(flags & SCRIPTTEXT_ISEXPRESSION == 0);
			// If we are in the INITIALIZED state, queue it up, otherwise we execute it now.
			if (state==axtam.com.SCRIPTSTATE_INITIALIZED) {
				codeBlocks.push(scriptBlock)
			} else {
				executeScriptBlock(scriptBlock)
			}
		}

		// This function is called as a 'named item' is added to the environment.
		// Examples include IE's 'window' object.
		public function AddNamedItem(name:String, flags:uint):void
		{
			//print('AddNamedItem(', name, flags)
			// MS docs say we should avoid grabbing typeinfo unless we
			// really need it.  At this stage, we need it if the item is
			// "global", and later will need it if it sources events
			var gii_flags:uint = axtam.com.SCRIPTINFO_IUNKNOWN
//			if (flags & axtam.com.SCRIPTITEM_GLOBALMEMBERS)
//				gii_flags |= axtam.com.SCRIPTINFO_ITYPEINFO

			var items = site.GetItemInfo(name, gii_flags)
			var dispatch = items[0]
			var typeinfo = items[1]
			var globalDomain:axtam.Domain = namedItems[null].domain
			globalDomain.global[name] = dispatch
			// but we also need to tell the VM exactly what 'scope'
			// provides this object.
			globalDomain.addNamedScriptObject(name)
			// if its global, we enumerate items and make them public - all 
			// this is done inside exposeGlobalMembers
			//if (flags & axtam.com.SCRIPTITEM_GLOBALMEMBERS && typeinfo != null) {
			//	domain.exposeGlobalMembers(dispatch, typeinfo)
			//}
			// create a new domain for the object with the IDispatch as its global (or not!)
			var obDomain =  new axtam.Domain(globalDomain, null) // dispatch)
			var item = new NamedItem()
			item.domain = obDomain
			item.host_dispatch = dispatch
			//item.host_typeinfo = typeinfo
			item.script_dispatch = null
			namedItems[name] = item
		}

		public function GetScriptDispatch(name:String): axtam.com.consumer.IDispatch
		{
			// XXX - todo - cache these so we don't create new ones each time
			// (or at least work out if its necessary to do that ;)
			// return an IDispatch impl around the domain's global.
			var item:NamedItem = getNamedItem(name)
			if (!item.script_dispatch) {
				var domain:axtam.Domain = item.domain
				// XXX - this is wrong, but for now, treat the host_dispatch as the global.
				item.script_dispatch = axtam.com.provider.createDispatchProvider(item.host_dispatch)
			}
			return item.script_dispatch
		}

		public function GetScriptState(): uint
		{
			return state;
		}

		public function SetScriptState(new_state:uint): uint
		{
			return transitionTo(new_state);
		}
		public function Close(): void
		{
			SetScriptState(axtam.com.SCRIPTSTATE_CLOSED)
		}

		// End of COM interfaces...
		// Start of implementation functions...
		/* Script State Management */
		// A state table.  First index is current state, second index is new state.
		// The intent of our state management is:
		// * We can always reset back to "initialized"
		// * Apart from the above, we can not move "backwards" in 
		//   state - ie, if you are 'connected', you can't move
		//   back to 'started'
		// * You can move to 'closed' from any state.  Once closed, you can't 
		//   transition anywhere - not even back to "initialized" (we drop state
		//   that prevents a reset)
		// This means that most entries in the state table are error state - which
		// implement by the policy that missing entries are a transition we don't support.
		// Also: We special case state==new_state, and CLOSED.
		// This leaves us with INITIALIZED, STARTED, CONNECTED and DISCONNECTED
		// XXX: due to compiler bugs, we can't reference our own function in a variable
		// declaration.  So we define the table in a function, and our ctor sets the variable.
		var stateTransitions; // = _getStateTransitions()

		function _getStateTransitions() {
			return { 
				// *sob* - why are the consts not working?
				// existing state
				0 /*axtam.com.SCRIPTSTATE_UNINITIALIZED */ : {
					// moving to INITIALIZED
					5 /*axtam.com.SCRIPTSTATE_INITIALIZED */ : function() {
						setStateInitialized()
					},
					// moving to STARTED
					1 /* axtam.com.SCRIPTSTATE_STARTED */: function() {
						setStateInitialized()
						setStateStarted()
					},
					// moving to CONNECTED
					2 /* axtam.com.SCRIPTSTATE_CONNECTED */: function() {
						setStateInitialized()
						setStateStarted()
						setStateConnected()
					},
					// moving to DISCONNECTED - nothing to do.
					3 /* axtam.com.DISCONNECTED */: function() {
						// uninit -> disconnected - nothing to do!
					}
				},
				// existing state == INITIALIZED
				5 /*axtam.com.SCRIPTSTATE_INITIALIZED */ : {
					// moving to STARTED
					1 /* axtam.com.SCRIPTSTATE_STARTED */: function() {
						setStateStarted()
					},
					// moving to CONNECTED
					2 /* axtam.com.SCRIPTSTATE_CONNECTED */: function() {
						setStateStarted()
						setStateConnected()
					},
					3 /* axtam.com.SCRIPTSTATE_DISCONNECTED */: function() {
						// init -> disconnected - nothing to do!
					}
				},
				// existing state == STARTED
				1 /* axtam.com.SCRIPTSTATE_STARTED */: {
					// moving to CONNECTED
					2 /* axtam.com.SCRIPTSTATE_CONNECTED */: function() {
						setStateConnected()
					},
					// moving to DISCONNECTED - nothing to do.
					3 /* axtam.com.SCRIPTSTATE_DISCONNECTED */: function() {
						// started -> disconnected - nothing to do!
					}
				},
				// Existing state == CONNECTED
				2 /* axtam.com.SCRIPTSTATE_CONNECTED */: {
					// only state we support from here is disconnected.
					3 /* axtam.com.SCRIPTSTATE_DISCONNECTED */: function() {
						setStateDisconnected()
					}
				},
				// Existing state == DISCONNECTED
				3 /* axtam.com.SCRIPTSTATE_DISCONNECTED */: {
					// We can't transition to anywhere from here, so this
					// is empty (but must exist to keep state logic happy)
				}
			}
		}

		function transitionTo(new_state:uint): uint
		{
			// states are a little complex - see the MS docs for
			// the official word.  To make our life easy, we special
			// case INITIALIZED and CLOSED.
			// MS documents the following return codes:
			// S_OK  Success.
			// E_FAIL  The scripting engine does not support the transition back to the initialized state.
			//        [We use this to mean it does not support the transition back to the specified state,
			//         which may or may not be 'initialized']
			// E_UNEXPECTED  The call was not expected (eg, not initialized)
			// OLESCRIPT_S_PENDING  The method was queued successfully, but the state has not changed yet. 
			//                      When the state changes, the site will be called back through the 
			//                      IActiveScriptSite::OnStateChange method.  [We don't handle this yet]
			// S_FALSE  The method succeeded, but the script was already in the given state.  

			if (state == axtam.com.SCRIPTSTATE_CLOSED) {
				axtam.com.Error.throwError(axtam.com.Error.E_FAIL)
			}

			if (state == new_state)
				return axtam.com.Error.S_FALSE

			// from here we notify the site of the new state.
			if (new_state == axtam.com.SCRIPTSTATE_INITIALIZED)
				setStateInitialized()
			else if (new_state == axtam.com.SCRIPTSTATE_CLOSED) {
				// setting state closed will clear this.site - so save it
				var s = site
				setStateClosed()
				if (s) {
					state = new_state
					s.OnStateChange(new_state)
				}
			} else {
				// use our state table.  No entry means we can't transition
				// from the current state to the requested state.
				var transFunc = stateTransitions[state][new_state]
				if (!transFunc)
					axtam.com.Error.throwError(axtam.com.Error.E_FAIL)
				transFunc();
			}
			state = new_state
			if (site)
				site.OnStateChange(new_state)
			return axtam.com.Error.S_OK
		}

		// The "heavy lifters" of the state transition.  transitionToInitialized
		// is special in that it allows us to transition backwards from all
		// states except 'closed'.
		function setStateInitialized(): void
		{
			// we could be in any state here (except CLOSED)
			namedItems = {}
			var global_item:NamedItem = new NamedItem()
			global_item.domain = new axtam.Domain(null, null)
			namedItems[null] = global_item
			codeBlocks = new Array()
		}

		public function setStateStarted(): void
		{
			// assert(state == axtam.com.SCRIPTSTATE_INITIALIZED, "must be exactly initialized!")
			executePendingScriptBlocks()
		}

		function setStateConnected(): void
		{
		}

		function setStateDisconnected(): void
		{
		}

		function setStateClosed(): void
		{
			namedItems = null
			codeBlocks = null
			site = null
		}
		// End of state management.
		function getNamedItem(name:String):NamedItem
		{
			var ret:NamedItem = namedItems[name]
			// If the name is not known, return an empty object
			// so the attributes themselves are undefined.
			if (ret==undefined)
				ret = new NamedItem()
			return ret
		}

		function executeScriptBlock(scriptBlock)
		{
			var domain:axtam.Domain = getNamedItem(scriptBlock.item_name).domain
			domain.loadBytes(scriptBlock.bytes)
		}
		
		function executePendingScriptBlocks()
		{
			while (codeBlocks.length != 0) {
				var block = codeBlocks.pop()
				executeScriptBlock(block)
			}
		}
	}

	public var engine = new ScriptEngine()
	// and magically methods will be called on 'engine'
}
