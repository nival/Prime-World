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


package {

	import avmplus.*;
	
	public namespace ns = "some_ns"
	public namespace ns2 = "another_ns"
	
	public interface IBar
	{
		function i0():*;
	};

	public interface IFoo
	{
		function i1():*;
		function get i2():*;
	};

	public class FooBase extends Object implements IBar
	{
		public function i0():* {}
	}

	public class Foo extends FooBase implements IFoo
	{
		public var z:int;
		
		[metahere(foo="vectorriffic")]
		public var vec:Vector.<int>;

		[metahere(foo="vectorriffic_foo")]
		public var vecfoo:Vector.<IFoo>;

		[metahere(foo="Foo get w")]
		public function get w():int { return 0; }
		
		function Foo(q:int, s:String = "") { z = q; }
		
		[metahere(foo="blah")]
		public function yah(d:Number):String { return String(z+d); }

		ns function yah(d:Number):String { return String(z+d); }

		public function i1():* {}
		public function get i2():* {}
	}

	[classmeta(a="b", c="d")]
	public class Foo2 extends Foo implements IFoo
	{
		public var aa:int;
		public const bb:IFoo = null;
		ns2 const bb:IFoo = undefined;
		
		function Foo2(q:int) { super(q); }
		override public function yah(d:Number):String { return String(z+d+1); }

		public function whatever(a:*, b:int, c:String):* {}
		ns2 function whatever(a:*, b:int, c:String = "hey"):* {}

		[metahere]
		override public function get w():int { return 1; }

		[metahere(foo="Foo2 set w")]
		public function set w(i:int):* {  }

		ns function get w():int { return 1; }

		public static function statfunc():void {}
	}

	var oi = describeType(new Foo2(2), FLASH10_FLAGS);
	var oc = describeType(Foo2, FLASH10_FLAGS);
	var ov = describeType(new Vector.<String>(), FLASH10_FLAGS);
	
	var expected = []
	var xc = 
<type name="Foo2" base="Class" isDynamic="true" isFinal="true" isStatic="true">
    <extendsClass type="Class"/>
    <extendsClass type="Object"/>
    <method name="statfunc" declaredBy="Foo2" returnType="void"/>
    <accessor name="prototype" access="readonly" type="*" declaredBy="Class"/>
    <factory type="Foo2">
        <metadata name="classmeta">
            <arg key="a" value="b"/>
            <arg key="c" value="d"/>
        </metadata>
        <extendsClass type="Foo"/>
        <extendsClass type="FooBase"/>
        <extendsClass type="Object"/>
        <implementsInterface type="IFoo"/>
        <implementsInterface type="IBar"/>
        <constructor>
            <parameter index="1" type="int" optional="false"/>
        </constructor>
        <constant name="bb" type="IFoo"/>
        <method name="yah" declaredBy="Foo2" returnType="String">
            <parameter index="1" type="Number" optional="false"/>
            <metadata name="metahere">
                <arg key="foo" value="blah"/>
            </metadata>
        </method>
        <method name="whatever" declaredBy="Foo2" returnType="*">
            <parameter index="1" type="*" optional="false"/>
            <parameter index="2" type="int" optional="false"/>
            <parameter index="3" type="String" optional="false"/>
        </method>
        <accessor name="w" access="readwrite" type="int" declaredBy="Foo2">
            <metadata name="metahere"/>
            <metadata name="metahere">
                <arg key="foo" value="Foo2 set w"/>
            </metadata>
        </accessor>
        <constant name="bb" type="IFoo" uri="another_ns"/>
        <method name="whatever" declaredBy="Foo2" returnType="*" uri="another_ns">
            <parameter index="1" type="*" optional="false"/>
            <parameter index="2" type="int" optional="false"/>
            <parameter index="3" type="String" optional="true"/>
        </method>
        <variable name="aa" type="int"/>
        <variable name="z" type="int"/>
        <accessor name="i2" access="readonly" type="*" declaredBy="Foo"/>
        <method name="i0" declaredBy="FooBase" returnType="*"/>
        <method name="i1" declaredBy="Foo" returnType="*"/>
        <variable name="vecfoo" type="__AS3__.vec::Vector.&lt;IFoo&gt;">
            <metadata name="metahere">
                <arg key="foo" value="vectorriffic_foo"/>
            </metadata>
        </variable>
        <variable name="vec" type="__AS3__.vec::Vector.&lt;int&gt;">
            <metadata name="metahere">
                <arg key="foo" value="vectorriffic"/>
            </metadata>
        </variable>
    </factory>
</type>

	var xi = 
<type name="Foo2" base="Foo" isDynamic="false" isFinal="false" isStatic="false">
    <metadata name="classmeta">
        <arg key="a" value="b"/>
        <arg key="c" value="d"/>
    </metadata>
    <extendsClass type="Foo"/>
    <extendsClass type="FooBase"/>
    <extendsClass type="Object"/>
    <implementsInterface type="IFoo"/>
    <implementsInterface type="IBar"/>
    <constructor>
        <parameter index="1" type="int" optional="false"/>
    </constructor>
    <constant name="bb" type="IFoo"/>
    <method name="yah" declaredBy="Foo2" returnType="String">
        <parameter index="1" type="Number" optional="false"/>
        <metadata name="metahere">
            <arg key="foo" value="blah"/>
        </metadata>
    </method>
    <method name="whatever" declaredBy="Foo2" returnType="*">
        <parameter index="1" type="*" optional="false"/>
        <parameter index="2" type="int" optional="false"/>
        <parameter index="3" type="String" optional="false"/>
    </method>
    <accessor name="w" access="readwrite" type="int" declaredBy="Foo2">
        <metadata name="metahere"/>
        <metadata name="metahere">
            <arg key="foo" value="Foo2 set w"/>
        </metadata>
    </accessor>
    <constant name="bb" type="IFoo" uri="another_ns"/>
    <method name="whatever" declaredBy="Foo2" returnType="*" uri="another_ns">
        <parameter index="1" type="*" optional="false"/>
        <parameter index="2" type="int" optional="false"/>
        <parameter index="3" type="String" optional="true"/>
    </method>
    <variable name="aa" type="int"/>
    <variable name="z" type="int"/>
    <accessor name="i2" access="readonly" type="*" declaredBy="Foo"/>
    <method name="i0" declaredBy="FooBase" returnType="*"/>
    <method name="i1" declaredBy="Foo" returnType="*"/>
    <variable name="vecfoo" type="__AS3__.vec::Vector.&lt;IFoo&gt;">
        <metadata name="metahere">
            <arg key="foo" value="vectorriffic_foo"/>
        </metadata>
    </variable>
    <variable name="vec" type="__AS3__.vec::Vector.&lt;int&gt;">
        <metadata name="metahere">
            <arg key="foo" value="vectorriffic"/>
        </metadata>
    </variable>
</type>

	var xv = 
<type name="__AS3__.vec::Vector.&lt;String&gt;" base="__AS3__.vec::Vector.&lt;*&gt;" isDynamic="true" isFinal="false" isStatic="false">
    <extendsClass type="__AS3__.vec::Vector.&lt;*&gt;"/>
    <extendsClass type="Object"/>
    <accessor name="fixed" access="readwrite" type="Boolean" declaredBy="__AS3__.vec::Vector.&lt;*&gt;"/>
    <accessor name="length" access="readwrite" type="uint" declaredBy="__AS3__.vec::Vector.&lt;*&gt;"/>
</type>


	
	function sortXMLAttrs(x:XML):XML
	{
		var a:Array = [];
		for each (var att:XML in x.@*)
		{
			a.push({name:att.name(), value:att.toString()});
		}
		a.sortOn('name');
		for each (var o:* in a)
			delete x['@'+o.name]
		for each (o in a)
			x['@'+o.name] = o.value;
		return x;
	}

	function sortXML(x:XML):XML
	{
		// sort attrs first to normalize toXMLString compares
		sortXMLAttrs(x);

		XML.ignoreComments = true;
		XML.ignoreProcessingInstructions = true;
		XML.ignoreWhitespace = true;
		XML.prettyIndent = 4;
		XML.prettyPrinting = true;

		var a:Array = [];
		for each (var node:XML in x.children())
		{
			a.push(sortXML(node).toXMLString());
		}
		a.sort();

		x.setChildren(new XMLList);
		for each (var s:String in a)
		{
			x.appendChild(sortXML(new XML(s)));
		}
		
		
		
		return x;
	}
	
    // save values to restore afterwards (for ATS)
    var ignoreComments = XML.ignoreComments ;
    var ignoreProcessingInstructions = XML.ignoreProcessingInstructions ;
    var ignoreWhitespace = XML.ignoreWhitespace ;
    var prettyIndent = XML.prettyIndent;
    var prettyPrinting = XML.prettyPrinting ;
    
    startTest();

	AddTestCase("sortXML(oc)", String(sortXML(xc)), String(sortXML(oc)));	// describeType doesn't return the children in a canonical order; sort for stability
	AddTestCase("sortXML(oi)", String(sortXML(xi)), String(sortXML(oi)));	// describeType doesn't return the children in a canonical order; sort for stability
	AddTestCase("sortXML(ov)", String(sortXML(xv)), String(sortXML(ov)));	// describeType doesn't return the children in a canonical order; sort for stability
	AddTestCase("getQualifiedClassName(Object)", "Object", getQualifiedClassName(Object));
	AddTestCase("getQualifiedClassName(Foo)", "Foo", getQualifiedClassName(Foo));
	AddTestCase("getQualifiedClassName(Foo2)", "Foo2", getQualifiedClassName(Foo2));
	AddTestCase("getQualifiedClassName(new Object)", "Object", getQualifiedClassName(new Object));
	AddTestCase("getQualifiedClassName(new Foo(1))", "Foo", getQualifiedClassName(new Foo(1)));
	AddTestCase("getQualifiedClassName(new Foo2(1))", "Foo2", getQualifiedClassName(new Foo2(1)));
	AddTestCase("getQualifiedSuperclassName(Object)", null, getQualifiedSuperclassName(Object));
	AddTestCase("getQualifiedSuperclassName(Foo)", "FooBase", getQualifiedSuperclassName(Foo));
	AddTestCase("getQualifiedSuperclassName(Foo2)", "Foo", getQualifiedSuperclassName(Foo2));
	AddTestCase("getQualifiedSuperclassName(new Object)", null, getQualifiedSuperclassName(new Object));
	AddTestCase("getQualifiedSuperclassName(new Foo(1))", "FooBase", getQualifiedSuperclassName(new Foo(1)));
	AddTestCase("getQualifiedSuperclassName(new Foo2(1))", "Foo", getQualifiedSuperclassName(new Foo2(1)));
	AddTestCase("describeType(null, FLASH10_FLAGS).toXMLString()", '<type name="null" isDynamic="false" isFinal="true" isStatic="false"/>', describeType(null, FLASH10_FLAGS).toXMLString());
	AddTestCase("describeType(void 0, FLASH10_FLAGS).toXMLString()", '<type name="void" isDynamic="false" isFinal="true" isStatic="false"/>', describeType(void 0, FLASH10_FLAGS).toXMLString());


    test();
    
    
    // restore XML values (for ATS)
    XML.ignoreComments = ignoreComments;
    XML.ignoreProcessingInstructions = ignoreProcessingInstructions;
    XML.ignoreWhitespace = ignoreWhitespace;
    XML.prettyIndent = prettyIndent;
    XML.prettyPrinting = prettyPrinting;
}

