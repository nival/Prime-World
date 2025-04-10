/* -*- mode: java; tab-width: 4; insert-tabs-mode: nil; indent-tabs-mode: nil -*- */
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

/* Interactive/non-interactive shell.  If there are command line
 * arguments, treat them as filenames to load and eval, and then exit
 * after processing.  Otherwise, read input from the console.
 */

use default namespace internal;

use namespace "avmplus";
use namespace "flash.utils";

{
    // Users can use -no-debug to turn it off; enabling debugging is
    // the right choice for the REPL.

    ESC::flags.debugging = true;

    let files = ESC::filterCommandLine(Util::commandLineArguments());

    if (files.length == 0) {
        //let v = ESC::version;
        //print("ESC v" + v.major + "." + v.minor + " (\"" + v.nick + "\")");
        repl();
    }
    else {
        for ( let i=0 ; i < files.length ; i++ )
            ESC::compileAndLoadFile(files[i]);
    }
    System.exit(0);
}

// "eval" really belongs in the builtins, but OK here for the moment.
public function eval(...args)
    ESC::evaluateInScopeArray(args, [], "");

function repl() {
    while( true ) {
        let s = "";
        System.write("es> ");
        while( true ) {
            try {
                s += System.readLine();
                let [_,_,res] = ESC::compileAndLoadString(s, "(repl)");
                if (res !== undefined)
                    print(res);
                break; // worked - this command is complete.
            } catch (x) {
                // If it is a premature-EOF error, read another line
                if (x.message.indexOf("found EOS") == -1) {
                    let msg = x.getStackTrace();
                    if (!msg) { // probably a non *_Debugger build
                        msg = x;
                    }
                    print(msg);
                    break;
                }
                // else fall through and read another line
            }
        }
    }
}


