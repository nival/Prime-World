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

// Framework code

#include "avmshell.h"

#ifdef AVMPLUS_SELFTEST

// The logging infrastructure uses stdio for the time being, this needs to be fixed.
#ifdef AVMPLUS_WIN32
#  include <stdio.h>
#endif

namespace avmplus
{
    static SelftestRunner *selftestRunner;
	
    void selftests(AvmCore* core, const char* component_glob, const char* category_glob, const char* name_glob) 
    {
		selftestRunner = new SelftestRunner(core);
		selftestRunner->run(component_glob, category_glob, name_glob);
		delete selftestRunner;
    }
	
    SelftestRunner::SelftestRunner(AvmCore* core) 
		: MMgc::GCRoot(core->GetGC())
		, core(core)
		, tests(NULL) 
		, last(NULL)
		, token(core->doubleToAtom(0.5))
    {
	}
	
    SelftestRunner::~SelftestRunner()
    {
		while (tests != NULL) 
		{
			Selftest* tmp = tests;
			tests = tests->next;
			delete tmp;
		}
    }
	
    void SelftestRunner::join(Selftest* test) 
    {
		test->next = NULL;
		if (last != NULL)
			last->next = test;
		else
			tests = test;
		last = test;
    }
	
    // run all tests; failures are printed on stderr or similar
    // print summary at the end, we have total number of tests that _should_ have run,
    // can print number that failed, that didn't run, that succeeded
	
    void SelftestRunner::run(const char* component_glob, const char* category_glob, const char* name_glob) 
    {
		createSelftestClasses();
		for ( Selftest* volatile ts = tests ; ts != NULL ; ts = ts->next )
		{
			Selftest* t = ts;
			if ((component_glob == NULL || match(component_glob, t->component)) &&
				(category_glob == NULL || match(category_glob, t->category)))
			{
				test_component = t->component;
				test_category = t->category;
				
				logStart();
				TRY(core, kCatchAction_Ignore)
				{
					t->prologue();
					for (volatile int n=0 ; ; n++) 
					{
						test_name = t->names[n];
						if (test_name == NULL)
							break;
						if (name_glob == NULL || match(name_glob, test_name)) 
						{
							TRY(core, kCatchAction_Ignore)
							{
								logTest();
								t->run(n);
								logPass();
							}
							CATCH (Exception* e) 
							{
								if (e->atom != token)
									logException();
							}
							END_CATCH
							END_TRY
						}
					}
					t->epilogue();
				}
				CATCH (Exception* e) 
				{
					(void)e;
					logCrash();
				}
				END_CATCH
				END_TRY
				logEnd();
			}
		}
    }
	
    void SelftestRunner::logStart()
    {
		AvmLog("['start', '%s', '%s']\n", test_component, test_category);
    }
	
    void SelftestRunner::logEnd()
    {
		AvmLog("['end', '%s', '%s']\n", test_component, test_category);
    }
	
    void SelftestRunner::logTest()
    {
		AvmLog("['test', '%s', '%s', '%s']\n", test_component, test_category, test_name);
    }
	
    void SelftestRunner::logPass()
    {
		AvmLog("['pass', '%s', '%s', '%s']\n", test_component, test_category, test_name);
    }
	
    void SelftestRunner::logFailure(const char* text, const char* file, int line)
    {
		AvmLog("['failure', '%s', '%s', '%s', '%s', '%s', %d]\n",
				test_component, test_category, test_name,
				text, file, line );
    }
	
    void SelftestRunner::logException()
    {
		AvmLog("['exception', '%s', '%s', '%s']\n", test_component, test_category, test_name);
    }
	
    void SelftestRunner::logCrash()
    {
		AvmLog("['crash', '%s', '%s']\n", test_component, test_category);
    }
	
    void SelftestRunner::createSelftestClasses()
    {
		// Initialize manually written tests here
		
		// Initialize generated tests
		createGeneratedSelftestClasses();
    }
	
	/* Not a true globber, only handles trailing '*' */
	/* static */
	bool SelftestRunner::match(const char* glob, const char* s)
	{
		while (*glob == *s && *glob != '*' && *s != 0) {
			glob++;
			s++;
		}
		return *glob == '*' || *glob == *s;
	}
    
    Selftest::Selftest(AvmCore* core, const char* component, const char* category, const char** names) 
		: core(core)
		, component(component)
		, category(category)
		, names(names)
		, next(NULL)
    {
		selftestRunner->join(this);
    }
	
	/* virtual */ Selftest::~Selftest() 
	{
	}
	
    /* virtual */ void Selftest::prologue() 
    {
    }
	
    /* virtual */ void Selftest::epilogue() 
    {
    }
	
    /* final */ void Selftest::verifyPass(int expr, const char* text_expr, const char* file, int line) 
    {
		if (!expr) {
			selftestRunner->logFailure(text_expr, file, line);
			core->throwException(new (core->GetGC()) Exception(core, selftestRunner->token));
		}
    }
	
}
#endif // AVMPLUS_SELFTEST
