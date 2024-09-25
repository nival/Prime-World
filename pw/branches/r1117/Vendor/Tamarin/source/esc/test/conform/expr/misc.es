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

// this

var global = this;

function f1() {
    print("THIS GLOBAL 1 " + (this === global));
}
f1();

var x = {}
function f2() {
    function f3() {
        print("THIS GLOBAL 2 " + (this === global));
    }
    print("THIS X 1 " + (this === x));
    f3();
}
x.f2 = f2;
x.f2();

var x = {}
function f4() {
    print("THIS X 2 " + (this === x));
}
with (x) {
    f4();
}

// literals
print("INT " + 37);
print("DOUBLE " + 3.14159);
print("DOUBLE " + 0.5);
print("HEX " + 0xDEADBEEF);
print("STRING HELLO");
print("XESCAPE \x48\x45\x4C\x4C\x4F");
print("UESCAPE \u0048\u0045\u004C\u004C\u004F");
print("BOOL " + true);
print("BOOL " + false);
print("NULL " + null);
var y = [1,2,3];
print("ARRAY " + y);
print("ARRAY length " + y.length);
for ( i=0 ; i < 3 ; i++ )
    print("ARRAY ELEMENT " + y[i]);
var y = [1,,3,,];
print("ARRAY 2 " + y);
print("ARRAY 2 length " + y.length);
print("ARRAY 2 element " + (1 in y));
var z = { x: 1, y: 2, z: 3 }
print("OBJECT " + z);
print("OBJECT x " + z.x);
print("OBJECT y " + z.y);
print("OBJECT z " + z.z);

var w = /abc/g;
print("REGEXP " + w);
print("REGEXP source " + w.source);
print("REGEXP global " + w.global);
print("REGEXP multiline " + w.multiline);
print("REGEXP ignoreCase " + w.ignoreCase);

// Functions

var fn = function f(n) { print("NAMED " + n); if (n > 0) f(n-1) }
fn(2);
var fn2 = function(n) { print("UNNAMED " + n); if (n > 0) fn2(n-1) }
fn2(2);

// Property reference

print( "PAREN " + ( 10 ) );
print( "FIELD " + { x: 10 }.x );
print( "FIELD " + { x: 20 }["x"] );

// Call

function g(a,b,c) { return a+b+c }

print( "FN " + g(1,2,3) );

// constructor

var x = new Number;
print( "NEW cls default " + x );
var y = new Number(37);
print( "NEW cls param " + y );

function MyType(t) {
    this.t = t;
}

var z = new MyType;
print( "NEW fn default " + z.t );
var zz = new MyType(10);
print( "NEW fn param " + zz.t );

// conditional

print( "?: " + (true ? "RIGHT" : "WRONG") );

print("DONE");
