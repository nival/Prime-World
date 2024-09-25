/* -*- mode: java -*- */
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
/*
 *
 * Generate selftest C++ code from spec files.
 *
 * Usage
 *
 *   selftest.abc filename ...
 *
 * Overview
 *
 *   The input to this program is some set of file names.  These
 *   should have a .st extension and conform to the grammar below.
 *
 *   This program processes the input files and creates the
 *   corresponding .cpp files (same path and file name, just different
 *   extension).  These .cpp files should be included in the project.
 *
 *   Additionally, the program produces a single file "SelftestInit.cpp"
 *   in the program's working directory.  This will contain a single
 *   function, "SelftestRunner::createGeneratedSelftestClasses()", which
 *   is called on AVM startup.  This file too should be included in the
 *   project.
 *
 * Grammar
 *
 *   file      ::= component category ifdef* (decls | methods | prologue | epilogue | test)*
 *   component ::= SOL "%%component" ident EOL
 *   category  ::= SOL "%%category" ident EOL
 *   ifdef     ::= SOL "%%ifdef" ident EOL
 *   decls     ::= SOL "%%decls" EOL text
 *   methods   ::= SOL "%%methods" EOL text
 *   prologue  ::= SOL "%%prologue" EOL text
 *   epilogue  ::= SOL "%%epilogue" EOL text
 *   test      ::= SOL "%%test" ident EOL (text | verify)*
 *   verify    ::= SOL "%%verify" expr EOL
 *   expr      ::= text but not newline
 *   text      ::= arbitrary text not containing "%%" at SOL
 *   EOL       ::= newline
 *   SOL       ::= beginning of line, possibly with leading spaces
 *
 *   Comment lines are C++ style, "//" possibly preceded by blanks, to the end of line.
 *   Blank lines are legal everywhere.
 *
 * Semantic constraints
 *
 *   There can be an arbitrary number of tests, but at least one.
 *   There can be at most one prologue or epilogue.
 *   There can be an arbitrary number of decls and methods, they are just cat'ed together.
 *   There must be at least one verify in a test.
 *
 *   (The requirements for at least one test and at least one verify
 *   are fascistic, but may help catch errors.  Experience will tell.)
 *
 * Semantics
 *
 *   A selftest file defines one or more test cases for a component
 *   (like "avmplus" or "player") and a category (like "peephole" or
 *   "jit").  Additionally, each test is named.  The test harness lets
 *   the user define the components, categories, and tests to run.
 *
 *   Each generated file is compiled conditionally on the existence of
 *   AVMPLUS_SELFTEST and also each of the names declared in %%ifdef
 *   statements.
 *
 *   The code that is generated comprises a class and its methods, all
 *   within a "namespace avmplus" block. Text in %%decls blocks is
 *   inserted verbatim into the class definition; text in %%methods
 *   blocks is inserted verbatim into the top level of the file.
 *   These sections allow the test case to define and use auxiliary
 *   data and methods.
 *
 *   The code in a %%prologue section will be run once, before any
 *   test in the file is run.  The code in an %%epilogue section will
 *   also be run once, after all tests in the file have been run.
 *   They are typically used to initialize instance data (declared by
 *   %%decls).
 *
 *   Each %%test is enclosed in an anonymous method of the generated
 *   class.  Each %%verify that appears in the test will test its
 *   condition, and if it does not hold that test function will be
 *   aborted and the error recorded.  Subsequent %%verify statements
 *   in that test will not be executed; however, subsequent tests in
 *   the same selftest spec will be executed.
 *
 *   Comment lines preceding directives are copied verbatim to the output.
 */

package selftest
{
    import avmplus.*;

    class Selftest {
		var comments = [];
		var component = null;
		var category = null;
		var ifdefs = [];
		var decls = [];
		var methods = [];
		var prologue = null;
		var epilogue = null;
		var tests = [];
		// generated by the formatter
		var ifdef_text = null;
		var classname = null;
    }

    function parse(lines) {
		var st = new Selftest;
		var i=0;
		var l=lines.length;
		var res;
		var state = -1;
		while (i < l) {
			var line = lines[i++];
			if (res = /^\s*%%component\s+([a-zA-Z_][a-zA-Z0-9_]+)\s*$/.exec(line)) {
				if (state > 0)
					throw "Too late to define component";
				state = 0;
				if (st.component != null)
					throw "Component already defined";
				st.component = res[1];
			}
			else if (res = /^\s*%%category\s+([a-zA-Z_][a-zA-Z0-9_]+)\s*$/.exec(line)) {
				if (state > 0)
					throw "Too late to define category";
				state = 0;
				if (st.category != null)
					throw "Category already defined";
				st.category = res[1];
			}
			else if (res = /^\s*%%ifdef\s+([a-zA-Z_][a-zA-Z0-9_]+)\s*$/.exec(line)) {
				if (state > 1)
					throw "Too late to define ifdef";
				state = 1;
				st.ifdefs.push(res[1]);
			}
			else if (line.match(/^\s*%%decls/)) {
				state = 2;
				pushMultiple(st.decls, text());
			}
			else if (line.match(/^\s*%%methods/)) {
				state = 2;
				pushMultiple(st.methods, text());
			}
			else if (line.match(/^\s*%%prologue/)) {
				state = 2;
				if (st.prologue != null)
					throw "Prologue already defined";
				st.prologue = text();
			}
			else if (line.match(/^\s*%%epilogue/)) {
				state = 2;
				if (st.epilogue != null)
					throw "Epilogue already defined";
				st.epilogue = text();
			}
			else if (res = /^\s*%%test\s+([a-zA-Z_][a-zA-Z0-9_]+)\s*$/.exec(line)) {
				state = 2;
				var loc = i;
				var t = [];
				var vs = 0;
				var name = res[1];
				while (i < l) {
					pushMultiple(t, text());
					if (i == l)
						break;
					line = lines[i];
					if ((res = /^\s*%%verify\s+(.*)$/.exec(line)) == null)
						break;
					vs++;
					i++;
					t.push("verifyPass(" + res[1] + ", \"" + res[1] + "\", __FILE__, __LINE__);");
				}
				if (vs == 0)
					throw "No %%verify statements for test on line " + loc;
				st.tests.push([name, t]);
			}
			else if (line.match(/^\s*\/\//)) {
				if (state < 0)
					st.comments.push(line);
			}
			else if (line.match(/^\s*$/)) {
				if (state < 0)
					st.comments.push(line);
			}
			else {
				throw "Bogus line " + (i+1) + ": " + line;
			}
		}

		if (st.category == null)
			throw "Category missing";
		if (st.component == null)
			throw "Component missing";
		if (st.tests.length == 0)
			throw "No tests";
	    
		return st;

		// note, this uses i, l, and lines and updates i
		function text() {
			var res;
			var t = [];
			while (i < l) {
				line = lines[i];
				if (line.match(/^\s*%%/))
					break;
				i++;
				t.push(line);
			}
			return t;
		}

    }

    function formatSelftest(input, st) {
		var s = [];
		var classname = "ST_" + st.component + "_" + st.category;
		st.classname = classname;
		s.push("// Generated from " + input);
		pushMultiple(s, st.comments);
		s.push("#include \"avmshell.h\"");
		st.ifdef_text = null;
		if (st.ifdefs.length > 0)
			st.ifdef_text = "#if defined " + st.ifdefs.join(" && defined ");
		s.push("#ifdef AVMPLUS_SELFTEST");
		if (st.ifdef_text != null)
			s.push(st.ifdef_text);
		s.push("namespace avmplus {");

		s.push("class " + classname + " : public Selftest {");
        s.push("public:");
		s.push(classname + "(AvmCore* core);");
		s.push("virtual void run(int n);");
		if (st.prologue)
			s.push("virtual void prologue();");
		if (st.epilogue)
			s.push("virtual void epilogue();");
		s.push("private:");
		s.push("static const char* ST_names[];");
		for ( var i=0 ; i < st.tests.length ; i++ )
			s.push("void test" + i + "();");
		pushMultiple(s, st.decls);
        s.push("};");

		s.push(classname + "::" + classname + "(AvmCore* core)");
		s.push("    : Selftest(core, \"" + st.component + "\", \"" + st.category + "\", " + classname + "::ST_names)");
		s.push("{}");

		s.push("const char* " + classname + "::ST_names[] = {" + 
			   st.tests.map(function (t) { return '"' + t[0] + '"' }).join(",") + ", NULL };");

		s.push("void " + classname + "::run(int n) {");
		s.push("switch(n) {");
		for ( var i=0 ; i < st.tests.length ; i++ )
			s.push("case " + i + ": test" + i + "(); return;");
		s.push("}");
		s.push("}");

		if (st.prologue) {
			s.push("void " + classname + "::prologue() {");
			pushMultiple(s, st.prologue);
			s.push("}");
		}

		if (st.epilogue) {
			s.push("void " + classname + "::epilogue() {");
			pushMultiple(s, st.epilogue);
			s.push("}");
		}

		if (st.methods) {
			pushMultiple(s, st.methods);
		}

		for ( var i=0 ; i < st.tests.length ; i++ ) {
			s.push("void " + classname + "::test" + i + "() {");
			pushMultiple(s, st.tests[i][1]);
			s.push("}");
		}

		s.push("void create_" + st.component + "_" + st.category + "(AvmCore* core) { new " + classname + "(core); }");

		s.push("}");
		if (st.ifdef_text != null)
			s.push("#endif");
		s.push("#endif");

		return s.join("\n") + "\n";
    }

    function pushMultiple(stk, xs) {
		for ( var i=0 ; i < xs.length ; i++ )
			stk.push(xs[i]);
		return stk;
    }

    // VS2008 requires the extern declarations to be at the top level for
    // the namespace tagging to work out correctly.
    function formatGeneratedInitializer() {
		var s = [];
		s.push("/* ***** BEGIN LICENSE BLOCK *****");
		s.push(" * Version: MPL 1.1/GPL 2.0/LGPL 2.1");
		s.push(" *");
		s.push(" * The contents of this file are subject to the Mozilla Public License Version");
		s.push(" * 1.1 (the \"License\"); you may not use this file except in compliance with");
		s.push(" * the License. You may obtain a copy of the License at");
		s.push(" * http://www.mozilla.org/MPL/");
		s.push(" *");
		s.push(" * Software distributed under the License is distributed on an \"AS IS\" basis,");
		s.push(" * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License");
		s.push(" * for the specific language governing rights and limitations under the");
		s.push(" * License.");
		s.push(" *");
		s.push(" * The Original Code is [Open Source Virtual Machine.].");
		s.push(" *");
		s.push(" * The Initial Developer of the Original Code is");
		s.push(" * Adobe System Incorporated.");
		s.push(" * Portions created by the Initial Developer are Copyright (C) 2008");
		s.push(" * the Initial Developer. All Rights Reserved.");
		s.push(" *");
		s.push(" * Contributor(s):");
		s.push(" *   Adobe AS3 Team");
		s.push(" *");
		s.push(" * Alternatively, the contents of this file may be used under the terms of");
		s.push(" * either the GNU General Public License Version 2 or later (the \"GPL\"), or");
		s.push(" * the GNU Lesser General Public License Version 2.1 or later (the \"LGPL\"),");
		s.push(" * in which case the provisions of the GPL or the LGPL are applicable instead");
		s.push(" * of those above. If you wish to allow use of your version of this file only");
		s.push(" * under the terms of either the GPL or the LGPL, and not to allow others to");
		s.push(" * use your version of this file under the terms of the MPL, indicate your");
		s.push(" * decision by deleting the provisions above and replace them with the notice");
		s.push(" * and other provisions required by the GPL or the LGPL. If you do not delete");
		s.push(" * the provisions above, a recipient may use your version of this file under");
		s.push(" * the terms of any one of the MPL, the GPL or the LGPL.");
		s.push(" *");
		s.push(" * ***** END LICENSE BLOCK ***** */");
		s.push("// Initialization code for generated selftest code");
		s.push("#include \"avmshell.h\"");
		s.push("namespace avmplus {");
		s.push("#ifdef AVMPLUS_SELFTEST");
		for ( var i=0 ; i < selftests.length ; i++ ) {
			var st = selftests[i];
			if (st.ifdef_text != null)
				s.push(st.ifdef_text);
			s.push("extern void create_" + st.component + "_" + st.category + "(AvmCore* core);");
			if (st.ifdef_text != null)
				s.push("#endif");
		}
		s.push("void SelftestRunner::createGeneratedSelftestClasses() {");
		for ( var i=0 ; i < selftests.length ; i++ ) {
			var st = selftests[i];
			if (st.ifdef_text != null)
				s.push(st.ifdef_text);
			s.push("create_" + st.component + "_" + st.category + "(core);");
			if (st.ifdef_text != null)
				s.push("#endif");
		}
		s.push("}");
		s.push("#endif // AVMPLUS_SELFTEST");
		s.push("}");
		return s.join("\n") + "\n";
    }

    var selftests = [];

    function process(input, output) {
		var st = parse(File.read(input).split("\n"));
		selftests.push(st);
		File.write(output, formatSelftest(input, st));
    }

    for ( var i=0 ; i < System.argv.length ; i++ ) {
		if (!System.argv[i].match(/\.st$/))
			print("WARNING: ignoring non-selftes file " + System.argv[i]);
		process(System.argv[i], System.argv[i].replace(/\.st$/, ".cpp"));
    }
    File.write("SelftestInit.cpp", formatGeneratedInitializer());
}

