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
 * Portions created by the Initial Developer are Copyright (C) 2008
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

print(eval("print('hello, nested world'); 37"))
print("hello, world");
print(9 % 4);
print({ "foo": 10, bar: 20 });
print({ "foo": 10, bar: 20 }.foo);
print({ "foo": 10, bar: 20 }.bar);
print(["a","b",,"c",,].length); // should be 5
print(["a","b",,"c",,]);
print(/a*b/g);
var v = "v!";
print(v);
var x = 10;
print(x++);
print(++x);
function f() { 
	 function g() { print("holy smokes, batman!"); }
	 g();
	 return "zappa";
}
print(f());
var x = 10;
if (x < 5)
   print("true");
else
   print("false");
for ( var i=0 ; i < 10 ; i++ )
    print(i);
print("done");
print(w);
var w = "outer";
function g() { var w = "inner"; }
g();
print(w);
print(delete w);
print(typeof w);

function h() { print("first"); }
h();
function h() { print("second"); }
h();
function zappa(x, y) { return x + y; }
print(zappa("hello", "there"));
print(x);
print(x *= 5);
print(x);
var obj = ["a"];
print(obj.toString());
print(obj["toString"]());
print(new Array(1,2,3));
function ww() {
    return "" + this.x + "," + this.y
}
function c(x) {
    this.x = x;
    this.toString = ww;
}
c.prototype = { y: 20 };
print(new c(10));
var zz = function (x) { return x }
print(zz("hello"));
var uu = "nothing special"
var yy = function uu(x) { return x }
print(yy("hello"))
print(uu)

var obj = ["a","b","c"]
for ( i in obj)
    print(i);
for ( var i=17 in [] )
    print(i);
print(i);
for ( var i=17 in obj )
    print(i + "," + obj[i]);

try {
    obj = null;
    print("Should happen");
}
catch (e) {
      print("Should not happen");
}

try {
    throw "Foo";
    print("Should not happen");
}
catch (e) {
      print("Should happen with foo: " + e);
}
try {
    print("Number 1");
}
finally {
    print("Number 2");
}
try {
    throw "foo";
}
catch (e) {
    print(e);
}
finally {
    print("number 3");
}

print("Got to end");
function abba() {
	 print(arguments);
}

abba(1,2,3,4)
for each ( var i in [1,2,3])
    print(i);

include "smoketest2.as";
include "smoketest2.as"

function typed1(x: int): void { 
    var v : String = "foo";
    return;
}

print("hello".split("ll"));

	x = 0;
loop:
	while(x < 10) {
		x++;
		continue loop;
		print("not here");
	}
	
	print(x);

for ( x=0 ; x < 1 ; x++ )
    for each ( i in [1,2,3] )
        print(i);

var object = { fun: function() { return this.valueOf(); }, valueOf: function () { return this.value }, value: 37 };
print(object.fun());
function t() {
    var a = 1;
    with ({a: 2}) {
         function f() { return a }
    }
    return f();
}
print(t());

print(1.7976931348623145e308);
print(Number.MAX_VALUE);

print(0x0);
print(0x12);

print(/\u0041/g);
print(/\u0041/.exec("A").length);
print("\u0041");
print(/\u004g/);

function p() {
	     function g() { return this }
		 var o = g() 
		 return o == this
	  }
print(p())
try {
    print(eval("function () { broken broken broken"));
}
catch (e) {
    print(e);
}
print(parseInt(341, 8).toString(16));
var f = function (x) { print(arguments); return arguments.callee; }
print(f(10));

function container() {
    var v = function () { print("hello"); }
    v.toString = Object.prototype.toString;
    print(v);
}
container();

function rest(x, ...rest) {
   print(x);
   print(rest);
}
rest(1,2,3,4);

order = 
<order>
    <customer>
        <name>John Smith</name>
    </customer>
    <item id="1">
        <description>Big Screen Television</description>
        <price>1299.99</price>
    </item>
    <item id="2">
        <description>DVD Player</description>
        <price>399.99</price>
    </item>
</order>;
print(order);

var xml7 = <><c q='1'>"quotes"</c><c q='2'>&#x7B;curly brackets&#x7D;</c></>;
print(xml7);

e = <employees>
    <employee id="0"><fname>John</fname><age>20</age></employee>
    <employee id="1"><fname>Sue</fname><age>30</age></employee>
    </employees>;


correct = <employee id="0"><fname>John</fname><age>20</age></employee>;

john = e.employee.(fname == "John");

print(john);

x1 = 
<alpha attr1="value1" attr2="value2">
    <bravo>
        one
        <charlie>two</charlie>
    </bravo>
</alpha>;

print("---");
print(x1..*);
print("---");

// -- Nothing new beyond this line! ----------------------------------------------------------

print("");
print("SMOKETEST DONE!");
