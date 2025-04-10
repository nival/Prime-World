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
 * Portions created by the Initial Developer are Copyright (C) 1993-2006
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


package flash.trace
{
	[native(cls="TraceClass", methods="auto")]
	public class Trace
	{
		/* levels of desired logging */
		public static const OFF:int = 0;
		public static const METHODS:int = 1;						// method entry only 
		public static const METHODS_WITH_ARGS:int = 2;				// method entry and arguments
		public static const METHODS_AND_LINES:int = 3;				// method entry and line numbers
		public static const METHODS_AND_LINES_WITH_ARGS:int = 4;	// method entry, arguments and line numbers

		/* used to select either file or listener callback logging. */
		public static const FILE = 1;
		public static const	LISTENER = 2;
		
		public static native function setLevel(l:int, target:int=LISTENER);
		public static native function getLevel(target:int=LISTENER):int;
		
		/**
		 * Register a listener to receive trace callbacks upon method and/or 
		 * line number changes.  Passing null to this function effectively
		 * 'unregisters' the listener and only a single listener can 
		 *  be specified.
		 * 
		 *  The callback funcition must have the following signature:
		 *
		 *     function foo(file_name:String, linenum:int, method_name:String, method_args:String):void
		 *
		 *  Depending upon the setting of the trace level, 2 or more arguments may be non-empty.  
		 *  In all cases file_name and method_name are obtained and passed to the callback.  If 
		 *  the trace level include line numbers information then this value is also obtained 
		 *  and passed into the callback.  Setting the trace level to include method arguments implies
		 *  that the 'method_args' parameter will be filled with string representation of the arguments
		 *  passed into the call.
		 */
		public static native function setListener(f:Function);
		public static native function getListener():Function;
	};
};
