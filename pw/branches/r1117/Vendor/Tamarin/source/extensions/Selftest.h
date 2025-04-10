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

#include "avmplus.h"

#ifdef AVMPLUS_SELFTEST

namespace avmplus
{
    #include "SelftestClasses.h"
	class Selftest;
	
	// Call 'selftests()' to create a selftest runner, instantiate all the
	// test classes, run all the tests, and delete all selftest objects.
	//
	// The component_glob, category_glob, or name_glob may be NULL (matching
	// anything) or must be globs that are matched against component name,
	// category names, and test names, respectively; names that match are
	// selected for running.
	//
	// For example, to run only the avmplus tests (but all of them) one would 
	// call this as
	//
	//    selftests("avmplus", NULL, NULL);
	//
	// Typically the values come from command line arguments.
	
	void selftests(AvmCore* core, const char* component_glob, const char* category_glob, const char* name_glob);
	
	
	// The SelftestRunner maintains a set of test objects and manages the
	// running of tests; it should not be instantiated except from the 'selftests()'
	// function.
	
	class SelftestRunner : public MMgc::GCRoot
	{
		friend class Selftest;
		
	public:
		SelftestRunner(AvmCore* core);
		~SelftestRunner();
		
		// 'run()' is called by the 'selftests()' function to run the tests and
		// record the results.  See above for a description of the arguments.
		
		void run(const char* component_glob, const char* category_glob, const char* name_glob);
		
	private:
		// 'join()' is called by the Selftest constructor to register a 
		// Selftest instance with this runner.
		
		void join(Selftest* test);
		void createSelftestClasses();
		void createGeneratedSelftestClasses();
		
		void logStart();
		void logEnd();
		void logTest();
		void logPass();
		void logFailure(const char* text, const char* file, int line);
		void logException();
		void logCrash();
		
		AvmCore*  core;
		Selftest* tests;             // linked through the 'next' field of 'Selftest'
		Selftest* last;              // last element in the list
		Atom      token;             // used by logging, typically a heap-allocated double
		
		const char *test_component;  // maintained
		const char *test_category;   //   by the
		const char *test_name;       //     'run()' method
		
		static bool match(const char* glob, const char* s);
	};

	
	// Specific test categories subclass Selftest and pass information
	// about the tests to the constructor.  The selftest runner uses
	// the information to decide whether to run a particular test.
	//
	// The pair component/category must be globally unique, and the
	// test names must be unique for a particular subclass of Selftest.
	
	class Selftest 
	{
		friend class SelftestRunner;
		
	public:
		Selftest(AvmCore* core, const char* component, const char* category, const char** names);
		virtual ~Selftest();
		
		virtual void prologue();
		virtual void epilogue();
		virtual void run(int n) = 0;
		
	protected:
		void verifyPass(int expr, const char* text_expr, const char* file, int line);

		AvmCore*     core;
		const char*  component;   // component, eg 'avmplus' or 'player'
		const char*  category;    // category, eg 'peephole' or 'jit'
		const char** names;       // test names
		
	private:
		Selftest*    next;        // next test in a list owned by the SelftestRunner
	};
}

#endif // AVMPLUS_SELFTEST
