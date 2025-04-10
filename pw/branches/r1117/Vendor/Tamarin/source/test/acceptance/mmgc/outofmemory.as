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

import avmplus.*;

		/****  inner class Node  ***/
		class Node 
		{
			var left:Node, right:Node;
			var i:int, j:int;
			function Node(l:Node = null, r:Node = null) { left = l; right = r; }
			
		}
		/**** end Node *******/


trace("before out-of-memory PASSED!");
var data:Array=new Array();
var last:Node=new Node();
var counter:int = 0;
var memWatcher:Number = 0;
while (true) {
    var node=new Node(last,last);
    data.push(node);
    last=node;
    counter++;
    if ((counter % 20000) == 0){
        if (System.totalMemory < memWatcher){
            trace("memory stopped growing, something wrong?");
            break;
        }
        memWatcher = System.totalMemory
    }
}

// if reaches this point did not run out of memory
// in order to run out of memory -memlimit 100 must be a runtime arg to the vm
trace("out-of-memory FAILED!");
