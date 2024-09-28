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

#ifndef __avmshell__
#define __avmshell__

#include "avmplus.h"

#if defined AVMPLUS_MAC || defined AVMPLUS_UNIX
  // Support for the -workers switch and distributing files across
  // multiple AvmCores on multiple threads.  Only the code in the
  // shell depends on this setting; the AVM core code works out of
  // the box.
  //
  // Requires pthreads.
  #define VMCFG_WORKERTHREADS
#endif

#if defined VMCFG_TESTING
  // We simulate Flash's use of API versioning for testing only.
  #define VMCFG_TEST_VERSIONING
#endif

#if !defined(UNDER_CE) && !defined(AVM_SHELL_NO_PROJECTOR)
#  define AVMSHELL_PROJECTOR_SUPPORT
#endif

#define INT32_T_MAX		0x7FFFFFFF	//max value for a 32-bit integer
#define UINT32_T_MAX	0xFFFFFFFF	//max value for a 32-bit unsigned integer

#ifdef _MSC_VER
#pragma warning(disable:4996)		// 'scanf' was declared deprecated
#endif

// forward declarations for shell_toplevel.h
namespace avmshell
{
	class SystemClass;
}
namespace avmplus
{
	class SampleObject;
	class StackFrameObject;
	class NewObjectSampleObject;
	class TraceClass;
}

#include "shell_toplevel.h"

using namespace avmplus;

namespace avmplus
{
	class Dictionary;
}

#ifdef VMCFG_AOT
#include "../aot/AOTCompiler.h"
#endif

namespace avmshell
{
	class ByteArray;
	class Shell;
	class ShellCodeContext;
	class ShellCore;
	class ShellCoreImpl;
	class ShellSettings;
	class ShellToplevel;
}

#include "Selftest.h"
#include "Platform.h"
#include "File.h"

#include "FileInputStream.h"
#include "ConsoleOutputStream.h"
#include "SystemClass.h"
#include "FileClass.h"
#include "DomainClass.h"
#include "DebugCLI.h"
#include "Profiler.h"
#include "DataIO.h"
#include "ByteArrayGlue.h"
#include "DictionaryGlue.h"
#include "SamplerScript.h"
#include "JavaGlue.h"
#include "ShellCore.h"

namespace avmshell
{ 
	// The stack margin is the amount of stack that should be available to native
	// code that does not itself check for stack overflow.  The execution engines
	// in the VM will reserve this amount of stack.
	
#ifdef AVMPLUS_64BIT
	const size_t kStackMargin = 262144;
#elif (defined AVMPLUS_WIN32 && defined UNDER_CE) || defined AVMPLUS_SYMBIAN
	// FIXME: all embedded platforms, but we have no way of expressing that now
	const size_t kStackMargin = 32768;
#else
	const size_t kStackMargin = 131072;
#endif
	
	// The fallback stack size is probably not safe but is used by the shell code
	// if it fails to obtain the stack size from the operating system.
	// 512KB is the traditional value.

	const size_t kStackSizeFallbackValue = 512*1024;

	// exit codes
	enum {
		OUT_OF_MEMORY = 128,
	};
	
	// swf support, impl code in swf.cpp
	bool isSwf(ScriptBuffer);
	void handleSwf(const char *, ScriptBuffer, DomainEnv*, Toplevel*&, CodeContext*);

#ifdef VMCFG_AOT
	// AOT support, impl code in aot.cpp
    void handleAOT(AvmCore*, Domain*, DomainEnv*, Toplevel*&, CodeContext*);
#endif

	class ShellSettings : public ShellCoreSettings
	{
	public:
		ShellSettings();
		
		char* programFilename;			// name of the executable, or NULL
		char** filenames;				// non-terminated array of file names, never NULL
		int numfiles;					// number of entries in 'filenames'
		bool do_selftest;
		bool do_repl;
		bool do_log;
		bool do_projector;
		int numthreads;
		int numworkers;
		int repeats;
		uint32_t stackSize;
		char st_mem[200];				// Selftest scratch memory.  200 chars ought to be enough for anyone
	};
	
	/**
	 * Shell driver and command line parser.
	 */
	class Shell {
	public:
		static int run(int argc, char *argv[]);

	private:
		static void singleWorker(ShellSettings& settings);
		static void singleWorkerHelper(ShellCore* shell, ShellSettings& settings);
#ifdef VMCFG_WORKERTHREADS
		static void multiWorker(ShellSettings& settings);
#endif
		static void repl(ShellCore* shellCore);
		static void initializeLogging(const char* basename);
		static void parseCommandLine(int argc, char* argv[], ShellSettings& settings);
		static void usage();
	};
	

	/**
	 * A subclass of ShellCore that provides an implementation of setStackLimit().
	 */
	class ShellCoreImpl : public ShellCore {
	public:
		/**
		 * @param gc          The garbage collector for this core
		 * @param mainthread  True if this core is being used on the main thread and not on a spawned
		 *                    thread.  It must be one or the other; a core created on a spawned thread
		 *                    cannot be used on the main thread or vice versa.
		 */
		ShellCoreImpl(MMgc::GC* gc, ShellSettings& settings, bool mainthread);
		
		/**
		 * Set AvmCore::minstack appropriately for the current thread.
		 */
		virtual void setStackLimit();
		
	private:
		ShellSettings& settings;
		bool mainthread;
	};
}

#endif /* __avmshell__ */
