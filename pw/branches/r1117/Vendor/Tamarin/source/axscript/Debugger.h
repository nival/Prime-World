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
 * The Original Code is [axtam].
 *
 * The Initial Developer of the Original Code is Mozilla Corp.
 * Portions created by the Initial Developer are Copyright (C) 2008
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

#ifndef __axtam_Debugger__
#define __axtam_Debugger__

#ifdef DEBUGGER
namespace axtam
{
	/**
	 * An implementation of the Tamarin debugger.  Ultimately this will
	* interact with the ActiveDebugging interfaces, but for now it is a
	* minimal implementation so line-numbers and filenames work correctly
	* in stack traces.
	 */
	class Debugger : public avmplus::Debugger
	{
	public:
		Debugger(AvmCore *core) : avmplus::Debugger(core) {;}
		~Debugger() {;}
		
		void enterDebugger() {;}
		bool filterException(Exception *exception) {return false;}
		bool hitWatchpoint() {return false;}
		// Note: avmplus::Debugger::debugLine() is a fairly "heavy" function
		// given all we need is core->callStack->linenum updated, but until
		// we have a better idea about integration with the IActiveScriptDebug
		// interface, the base version will do.
	};
}
#endif

#endif /* __axtam_Debugger__ */
