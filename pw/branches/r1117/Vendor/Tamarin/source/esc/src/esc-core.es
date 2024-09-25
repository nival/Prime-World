/* -*- mode: java; tab-width: 4; insert-tabs-mode: nil; indent-tabs-mode: nil;  -*- */
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

use default namespace ESC,
    namespace ESC;

internal function compile(consume, produce, context, start_line) {
    let t1 = new Date;

    let input = consume();
    let parser = new Parse::Parser(input, getTopFixtures(), context, start_line);
    let prog = parser.program();

    let t2 = new Date;

    let res = produce( Gen::cg(prog) );

    let t3 = new Date;

    return [t2-t1, t3-t2, res];
}

// Public API below.  The API is ad hoc on purpose, each function
// serves a different use case and is provided for convenience.
// Keeping the API small is not (currently) a goal.

class Flags 
{
    var es3_keywords = false;             // recognize only ES3 keywords (not future reserved)
    var es4_kwd_debugger = false;         // language misfeature
    var debugging = false;                // true to enable debug code
    var ext_dynamic_override = false;     // true to enable 'dynamic override' expression
    var ext_toplevel_letexpr = false;     // true to recognize let expressions at the top level
    var profile_compiler = false;         // true to profile the ESC run (used in esc.es)
}

const version = { major: 0, minor: 1, nick: "That depends on what the meaning of 'is' is" };
const flags = new Flags;

// Flags are:
//   -[no-]debug
//   -g
//   -[no-]extensions
//   -[no-]es3

internal var flagvalues = [ ["-es3",      [["es3_keywords",true]]],
                            ["-no-es3",   [["es3_keywords",false]]],
                            ["-g",        [["debugging",true]]],
                            ["-debug",    [["debugging",true]]],
                            ["-no-debug", [["debugging",false]]],
                            ["-extensions", [["ext_dynamic_override",true],
                                             ["ext_toplevel_letexpr",true]]],
                            ["-no-extensions", [["ext_dynamic_override",false],
                                                ["ext_toplevel_letexpr",false]]],
                            ["-Xprofile", [["profile_compiler",true]]] ];


function filterCommandLine(argv) {
    outer:
    while (argv.length > 0) {
        for ( let i=0 ; i < flagvalues.length ; i++ ) {
            let [name,settings] = flagvalues[i];
            if (argv[0] == name) {
                for ( let j=0 ; j < settings.length ; j++ ) {
                    let [prop,val] = settings[j];
                    flags[prop] = val;
                }
                argv.shift();
                continue outer;
            }
        }
        break;
    }
    return argv;
}

function getTopFixtures()
    ESC::bootstrap_namespaces;    // in esc-env.es

function compileFile(fname, start_line=1)
    compile( (function () Util::readStringFromFile(fname)),
             (function (abc) Util::writeBytesToFile(abc.getBytes(), fname + ".abc")),
             fname,
             start_line );

function compileAndLoadFile(fname, start_line=1)
    compile( (function () Util::readStringFromFile(fname)),
             (function (abc) Util::loadBytes(abc.getBytes())),
             fname,
             start_line );

function compileAndLoadString(input, context, start_line=1)
    compile( (function () input),
             (function (abc) Util::loadBytes(abc.getBytes())),
             context,
             start_line );

function compileStringToBytes(input, context="(string)", start_line=1) {
    let [_,_,res] = compile( (function () input),
                             (function (abc) abc.getBytes()),
                             context,
                             start_line );
    return res;
}

function parseFromStringAndEncodeAst(input, context="string input"): String {
    let parser = new Parse::Parser(input, getTopFixtures(), context);
    let program = parser.program();
    return (new Ast::Serializer()).serialize(program);
}

function parseFromFileAndEncodeAst(fname)
    parseFromStringAndEncodeAst(Util::readStringFromFile(fname), fname);

function decodeAstFromString(input): Ast::Program
    (new Ast::Unserializer()).unserializeText(input);

function decodeAstFromFile(fname)
    decodeAstFromString(Util::readStringFromFile(fname));
