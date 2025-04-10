/* -*- mode: java; tab-width: 4 -*- */
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

/* A somewhat nasty program.
 *
 * When run, ofib allocates 10946 new dynamic objects, and the largest
 * number of live objects (21 separate full structures) is 229866
 * objects.  Each object occupies at least 9 words plus 16 words for
 * the hash table's atoms table (the default capacity is 8), make it
 * 26 words for a total of 23906064 bytes.  This is the lower bound on
 * the amount of live data.  (Needs experimental verification, and
 * note the hash table size is subject to change.)
 *
 * The structure is entirely circular and utterly impervious to standard
 * reference counting - GC is needed to release it.
 *
 * The test is artificial and meant to stress the GC maximally, but if
 * you're charitable you can imagine the program as the abstraction of
 * one that manipulates a bunch of cached data structures where evicted
 * structures must be garbage collected.
 */

package 
{
    import avmplus.*;

    function fib(n, pp) {
		var p = { parent: pp };
		if (n < 2)
			return p;
		else {
			p.x = fib(n-1, p);
			p.y = fib(n-2, p);
			return p;
		}
    }
    var iters = 70;
    if (System.argv.length > 0)
		iters = parseInt(System.argv[0]);
    print("Iterations: " + iters);
    var then = new Date();
    var res = new Array;
    for ( var i=0 ; i < iters ; i++ )
		res[i%20] = fib(20, null);
    var now = new Date();
    print("metric ofib " + (now - then));
}

