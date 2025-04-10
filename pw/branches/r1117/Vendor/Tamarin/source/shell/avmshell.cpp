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

#include "avmshell.h"
#if defined FEATURE_NANOJIT
#include "../nanojit/nanojit.h"
#endif

namespace avmshell
{
#ifdef AVMPLUS_WIN32
	extern bool show_error;	// in avmshellWin.cpp
#endif
  
	ShellSettings::ShellSettings()
		: ShellCoreSettings()
		, programFilename(NULL)
		, filenames(NULL)
		, numfiles(-1)
		, do_selftest(false)
		, do_repl(false)
		, do_log(false)
		, do_projector(false)
		, numthreads(1)
		, numworkers(1)
		, repeats(1)
		, stackSize(0)
	{
  	}
  
	ShellCoreImpl::ShellCoreImpl(MMgc::GC* gc, ShellSettings& settings, bool mainthread)
		: ShellCore(gc)
		, settings(settings)
		, mainthread(mainthread)
  	{
  	}
  
	/* virtual */
	void ShellCoreImpl::setStackLimit()
  	{
		uintptr_t minstack;
		if (settings.stackSize != 0)
		{
			// Here we really depend on being called fairly high up on
			// the thread's stack, because we don't know where the highest
			// stack address is.
			minstack = uintptr_t(&minstack) - settings.stackSize + avmshell::kStackMargin;
		}
		else 
		{
#ifdef VMCFG_WORKERTHREADS
			if (mainthread)
				minstack = Platform::GetInstance()->getMainThreadStackLimit();
			else {
				// Here we really depend on being called fairly high up on
				// the thread's stack, because we don't know where the highest
				// stack address is.
				size_t stackheight;
				pthread_attr_t attr;
				pthread_attr_init(&attr);
				pthread_attr_getstacksize(&attr, &stackheight);
				pthread_attr_destroy(&attr);
				minstack = uintptr_t(&stackheight) - stackheight + avmshell::kStackMargin;
			}
#else
			minstack = Platform::GetInstance()->getMainThreadStackLimit();
#endif
		}

		// call the non-virtual setter on AvmCore
		AvmCore::setStackLimit(minstack);
  	}
  	
	/* static */
	int Shell::run(int argc, char *argv[]) 
	{
		MMgc::GCHeap::EnterLockInit();
		MMgc::GCHeapConfig conf;
		//conf.verbose = AvmCore::DEFAULT_VERBOSE_ON;
		MMgc::GCHeap::Init(conf);

		// Note that output from the command line parser (usage messages, error messages,
		// and printed version number / feature list) will not go to the log file.  We
		// could fix this if it's a hardship.

		{
			MMGC_ENTER_RETURN(OUT_OF_MEMORY);
			ShellSettings settings;
			parseCommandLine(argc, argv, settings);
			
			if (settings.do_log)
			  initializeLogging(settings.numfiles > 0 ? settings.filenames[0] : "AVMLOG");
			
#ifdef VMCFG_WORKERTHREADS
			if (settings.numworkers == 1 && settings.numthreads == 1 && settings.repeats == 1)
				singleWorker(settings);
			else
				multiWorker(settings);
#else
			singleWorker(settings);
#endif			
		}
		
#ifdef AVMPLUS_WITH_JNI
		// This surely does not belong here?
		if (Java::startup_options) delete Java::startup_options;
#endif /* AVMPLUS_WITH_JNI */
		
		MMgc::GCHeap::Destroy();
		MMgc::GCHeap::EnterLockDestroy();
	 	return 0;
	}

	// In the single worker case everything is run on the main thread.  This
	// is where we handler the repl, selftest, and projectors.

	/* static */
	void Shell::singleWorker(ShellSettings& settings)
	{
		MMgc::GC *gc = mmfx_new( MMgc::GC(MMgc::GCHeap::GetGCHeap(), settings.gcMode()) );
		{
			MMGC_GCENTER(gc);			
			ShellCore* shell = new ShellCoreImpl(gc, settings, true);
			Shell::singleWorkerHelper(shell, settings);			
			delete shell;
		}
		mmfx_delete( gc );
	}

	/* static */
	void Shell::singleWorkerHelper(ShellCore* shell, ShellSettings& settings)
	{
		if (!shell->setup(settings))
			Platform::GetInstance()->exit(1);
		
#ifdef AVMPLUS_SELFTEST
		if (settings.do_selftest) {
			shell->executeSelftest(settings);
			return;
		}
#endif
		
#ifdef AVMSHELL_PROJECTOR_SUPPORT
		if (settings.do_projector) {
			AvmAssert(settings.programFilename != NULL);
			int exitCode = shell->executeProjector(settings.programFilename);
			if (exitCode != 0)
				Platform::GetInstance()->exit(exitCode);
		}
#endif

#ifdef VMCFG_AOT
        int exitCode = shell->evaluateFile(settings, NULL);
        if (exitCode != 0) 
            Platform::GetInstance()->exit(exitCode);
        return;
#endif
		
		// execute each abc file
		for (int i=0 ; i < settings.numfiles ; i++ ) {
			int exitCode = shell->evaluateFile(settings, settings.filenames[i]);
			if (exitCode != 0) 
				Platform::GetInstance()->exit(exitCode);
		}
		
#ifdef VMCFG_EVAL
		if (settings.do_repl)
			repl(shell);
#endif
	}
	
#ifdef VMCFG_WORKERTHREADS

//#define LOGGING(x)    x
#define LOGGING(x)

	// When we have more than one worker then we spawn as many threads as
	// called for and create a number of ShellCores corresponding to
	// the number of workers.  Those cores are scheduled on the threads.
	// The main thread acts as a supervisor, handing out work and scheduling
	// cores on the threads.
	//
	// At this time pthreads is required.  Windows Vista provides condition
	// variables and it is a straightforward exercise to map from pthread types
	// and calls to the Vista types and calls.  For older Win32 the situation
	// is grimmer.  If you need to run this code on older Win32, please download
	// and install the available open-source pthreads libraries for Win32.

	struct MultiworkerState;

	struct CoreNode 
	{
		CoreNode(ShellCore* core, int id) 
			: core(core)
			, id(id)
			, next(NULL)
		{
		}

		~CoreNode()
		{
			// Destruction order matters.
			MMgc::GC* gc = core->GetGC();
			delete core;
			delete gc;
		}
		
		ShellCore * const	core;
		const int			id;
		CoreNode *			next;		// For the LRU list of available cores
	};
	
	struct ThreadNode
	{
		ThreadNode(MultiworkerState& state, int id)
			: state(state)
			, id(id)
			, corenode(NULL)
			, filename(NULL)
			, next(NULL)
		{
			// 'thread' is initialized after construction
			pthread_cond_init(&c, NULL);
			pthread_mutex_init(&m, NULL);
		}

		~ThreadNode()
		{
			pthread_cond_destroy(&c);
			pthread_mutex_destroy(&m);
		}
		
		// Called from master, which should not be holding m.
		void startWork(CoreNode* corenode, const char* filename)
		{
			pthread_mutex_lock(&m);
			this->corenode = corenode;
			this->filename = filename;
			pthread_cond_signal(&c);
			pthread_mutex_unlock(&m);
		}
		
		MultiworkerState& state;
		pthread_t thread;
		const int id;
		pthread_cond_t c;
		pthread_mutex_t m;			// Protects corenode, filename, next, c
		CoreNode* corenode;			// The core running (or about to run, or just finished running) on this thread
		const char* filename;		// The work given to that core
		ThreadNode * next;			// For the LRU list of available threads 
	};
	
	struct MultiworkerState 
	{
		MultiworkerState(ShellSettings& settings)
			: settings(settings)
			, numthreads(settings.numthreads)
			, numcores(settings.numworkers)
			, free_threads(NULL)
			, free_threads_last(NULL)
			, free_cores(NULL)
			, free_cores_last(NULL)
			, num_free_threads(0)
		{
			pthread_mutex_init(&m, NULL);
			pthread_cond_init(&c, NULL);
		}
		
		~MultiworkerState()
		{
			pthread_mutex_destroy(&m);
			pthread_cond_destroy(&c);
		}

		// Called from the slave threads, which should not be holding m.
		void freeThread(ThreadNode* t)
		{
			pthread_mutex_lock(&m);
			
			if (free_threads_last != NULL)
				free_threads_last->next = t;
			else
				free_threads = t;
			free_threads_last = t;
			
			if (t->corenode != NULL) {
				if (free_cores_last != NULL)
					free_cores_last->next = t->corenode;
				else
					free_cores = t->corenode;
				free_cores_last = t->corenode;
			}

			num_free_threads++;

			pthread_cond_signal(&c);
			pthread_mutex_unlock(&m);
		}

		// Called from the master thread, which must already hold m.
		bool getThreadAndCore(ThreadNode** t, CoreNode** c)
		{
			if (free_threads == NULL || free_cores == NULL)
				return false;
			
			*t = free_threads;
			free_threads = free_threads->next;
			if (free_threads == NULL)
				free_threads_last = NULL;
			(*t)->next = NULL;
			
			*c = free_cores;
			free_cores = free_cores->next;
			if (free_cores == NULL)
				free_cores_last = NULL;
			(*c)->next = NULL;
			
			num_free_threads--;

			return true;
		}
			
		ShellSettings&		settings;
		int					numthreads;
		int					numcores;

		// Queues of available threads and cores.  Protected by m, availability signaled on c.
		pthread_mutex_t		m;
		pthread_cond_t		c;
		ThreadNode*			free_threads;
		ThreadNode*			free_threads_last;
		CoreNode*			free_cores;
		CoreNode*			free_cores_last;
		int					num_free_threads;
	};

	static void masterThread(MultiworkerState& state);
	static void* slaveThread(void *arg);

	/* static */
	void Shell::multiWorker(ShellSettings& settings)
	{
		AvmAssert(!settings.do_repl && !settings.do_projector && !settings.do_selftest);
		
		MultiworkerState	state(settings);
		const int			numthreads(state.numthreads);
		const int			numcores(state.numcores);
		ThreadNode** const	threads(new ThreadNode*[numthreads]);
		CoreNode** const	cores(new CoreNode*[numcores]);
		
		// Going multi-threaded.

		// Create and start threads.  They add themselves to the free list.
		for ( int i=0 ; i < numthreads ; i++ )	{
			threads[i] = new ThreadNode(state, i);
			pthread_create(&threads[i]->thread, NULL, slaveThread, threads[i]);
		}

		// Create collectors and cores.
		// Extra credit: perform setup in parallel on the threads.
		for ( int i=0 ; i < numcores ; i++ ) {
			MMgc::GC* gc = new MMgc::GC(MMgc::GCHeap::GetGCHeap(), settings.gcMode());
			MMGC_GCENTER(gc);
			cores[i] = new CoreNode(new ShellCoreImpl(gc, settings, false), i);
			if (!cores[i]->core->setup(settings))
				Platform::GetInstance()->exit(1);
		}

		// Add the cores to the free list.
		for ( int i=numcores-1 ; i >= 0 ; i-- ) {
			cores[i]->next = state.free_cores;
			state.free_cores = cores[i];
		}
		state.free_cores_last = cores[numcores-1];

		// No locks are held by the master at this point
		masterThread(state);
		// No locks are held by the master at this point

		// Some threads may still be computing, so just wait for them
		pthread_mutex_lock(&state.m);
		while (state.num_free_threads < numthreads)
			pthread_cond_wait(&state.c, &state.m);
		pthread_mutex_unlock(&state.m);
		
		// Shutdown: feed NULL to all threads to make them exit.
		for ( int i=0 ; i < numthreads ; i++ )
			threads[i]->startWork(NULL,NULL);
		
		// Wait for all threads to exit.
		for ( int i=0 ; i < numthreads ; i++ ) {
			pthread_join(threads[i]->thread, NULL);
			LOGGING( AvmLog("T%d: joined the main thread\n", i); )
		}

		// Single threaded again.
		
		for ( int i=0 ; i < numthreads ; i++ )
			delete threads[i];
		
		for ( int i=0 ; i < numcores ; i++ )
			delete cores[i];
		
		delete [] threads;
		delete [] cores;
	}
	
	static void masterThread(MultiworkerState& state)
	{
		const int numfiles(state.settings.numfiles);
		const int repeats(state.settings.repeats);
		char** const filenames(state.settings.filenames);
		
		pthread_mutex_lock(&state.m);
		int r=0;
		for (;;) {
			int nextfile = 0;
			for (;;) {
				ThreadNode* threadnode;
				CoreNode* corenode;
				while (state.getThreadAndCore(&threadnode, &corenode)) {
					LOGGING( AvmLog("Scheduling %s on T%d with C%d\n", filenames[nextfile], threadnode->id, corenode->id); )
					threadnode->startWork(corenode, filenames[nextfile]);
					nextfile++;
					if (nextfile == numfiles) {
						r++;
						if (r == repeats)
							goto finish;
						nextfile = 0;
					}
				}
				
				LOGGING( AvmLog("Waiting for available threads.\n"); )
				pthread_cond_wait(&state.c, &state.m);
			}
		}
	finish:
		pthread_mutex_unlock(&state.m);
	}

	static void* slaveThread(void *arg)
	{
		MMGC_ENTER_RETURN(NULL);

		ThreadNode* self = (ThreadNode*)arg;
		MultiworkerState& state = self->state;
		
		for (;;) {
			// Signal that we're ready for more work: add self to the list of free threads
			
			state.freeThread(self);

			// Obtain more work.  We have to hold self->m here but the master won't touch corenode and
			// filename until we register for more work, so they don't have to be copied out of
			// the thread structure.
			
			pthread_mutex_lock(&self->m);
			pthread_cond_wait(&self->c, &self->m);
			pthread_mutex_unlock(&self->m);

			if (self->corenode == NULL) {
				LOGGING( AvmLog("T%d: Exiting\n", self->id); )
				pthread_exit(NULL);
			}

			// Perform work
			LOGGING( AvmLog("T%d: Work starting\n", self->id); )
			{
				MMGC_GCENTER(self->corenode->core->GetGC());
				self->corenode->core->evaluateFile(state.settings, self->filename);	// Ignore the exit code for now
			}
			LOGGING( AvmLog("T%d: Work completed\n", self->id); )
		}
		return (void*) NULL;
	}
	
#endif  // VMCFG_WORKERTHREADS

#ifdef VMCFG_EVAL

	/* static */
	void Shell::repl(ShellCore* shellCore)
	{
		const int kMaxCommandLine = 1024;
		char commandLine[kMaxCommandLine];
		String* input;

		AvmLog("avmplus interactive shell\n"
			   "Type '?' for help\n\n");
		
		for (;;)
		{
			bool record_time = false;
			AvmLog("> ");
			
			if(Platform::GetInstance()->getUserInput(commandLine, kMaxCommandLine) == NULL)
				return;
			
			commandLine[kMaxCommandLine-1] = 0;
			if (VMPI_strncmp(commandLine, "?", 1) == 0) {
				AvmLog("Text entered at the prompt is compiled and evaluated unless\n"
					   "it is one of these commands:\n\n"
					   "  ?             print help\n"
					   "  .input        collect lines until a line that reads '.end',\n"
					   "                then eval the collected lines\n"
					   "  .load file    load the file (source or compiled)\n"
					   "  .quit         leave the repl\n"
					   "  .time expr    evaluate expr and report the time it took.\n\n");
				continue;
			}
			
			if (VMPI_strncmp(commandLine, ".load", 5) == 0) {
				const char* s = commandLine+5;
				while (*s == ' ' || *s == '\t')
					s++;
				// wrong, handles only source code
				//readFileForEval(NULL, newStringLatin1(s));
				// FIXME: implement .load
				// Small amount of generalization of the code currently in the main loop should
				// take care of it.
				AvmLog("The .load command is not implemented\n");
				continue;
			}
			
			if (VMPI_strncmp(commandLine, ".input", 6) == 0) {
				input = shellCore->newStringLatin1("");
				for (;;) {
					if(Platform::GetInstance()->getUserInput(commandLine, kMaxCommandLine) == NULL)
						return;
					commandLine[kMaxCommandLine-1] = 0;
					if (VMPI_strncmp(commandLine, ".end", 4) == 0)
						break;
					input->appendLatin1(commandLine);
				}
				goto compute;
			}
			
			if (VMPI_strncmp(commandLine, ".quit", 5) == 0) {
				return;
			}
			
			if (VMPI_strncmp(commandLine, ".time", 5) == 0) {
				record_time = true;
				input = shellCore->newStringLatin1(commandLine+5);
				goto compute;
			}

			input = shellCore->newStringLatin1(commandLine);

		compute:
			shellCore->evaluateString(input, record_time);
		}
	}

#endif // VMCFG_EVAL
	
	// open logfile based on a filename
	/* static */
	void Shell::initializeLogging(const char* basename)
	{
		const char* lastDot = VMPI_strrchr(basename, '.');
		if(lastDot)
		{
			//filename could contain '/' or '\' as their separator, look for both
			const char* lastPathSep1 = VMPI_strrchr(basename, '/');
			const char* lastPathSep2 = VMPI_strrchr(basename, '\\');
			if(lastPathSep1 < lastPathSep2) //determine the right-most 
				lastPathSep1 = lastPathSep2;
				
				//if dot is before the separator, the filename does not have an extension
				if(lastDot < lastPathSep1)
					lastDot = NULL;
		}
		
		//if no extension then take the entire filename or 
		size_t logFilenameLen = (lastDot == NULL) ? VMPI_strlen(basename) : (lastDot - basename); 
		
		char* logFilename = new char[logFilenameLen + 5];  // 5 bytes for ".log" + null char
		VMPI_strncpy(logFilename,basename,logFilenameLen);
		VMPI_strcpy(logFilename+logFilenameLen,".log");
		
		Platform::GetInstance()->initializeLogging(logFilename);
		
		delete [] logFilename;
	}

	/* static */
	void Shell::parseCommandLine(int argc, char* argv[], ShellSettings& settings)
	{
		bool print_version = false;
		
		// options filenames -- args
		
		settings.programFilename = argv[0];		// How portable / reliable is this?
		for (int i=1; i < argc ; i++) {
			const char * const arg = argv[i];
			
			if (arg[0] == '-') 
			{
				if (arg[1] == '-' && arg[2] == 0) {
					if (settings.filenames == NULL)
						settings.filenames = &argv[i];
					settings.numfiles = int(&argv[i] - settings.filenames);
					i++;
					settings.arguments = &argv[i];
					settings.numargs = argc - i;
					break;
				}
				
				if (arg[1] == 'D') {
					if (!VMPI_strcmp(arg+2, "timeout")) {
						settings.interrupts = true;
					}
					else if (!VMPI_strcmp(arg+2, "version")) {
						print_version = true;
					}
					else if (!VMPI_strcmp(arg+2, "nodebugger")) {
						// allow this option even in non-DEBUGGER builds to make test scripts simpler
						settings.nodebugger = true;
					}
#if defined(AVMPLUS_IA32) && defined(FEATURE_NANOJIT)
					else if (!VMPI_strcmp(arg+2, "nosse")) {
						settings.sse2 = false;
					}
                    else if (!VMPI_strcmp(arg+2, "fixedesp")) {
                        settings.fixed_esp = true;
                    }
#endif /* AVMPLUS_IA32 */
#ifdef AVMPLUS_VERIFYALL
					else if (!VMPI_strcmp(arg+2, "verifyall")) {
						settings.verifyall = true;
					}
#endif /* AVMPLUS_VERIFYALL */
					else if (!VMPI_strcmp(arg+2, "greedy")) {
						settings.greedy = true;
					}
					else if (!VMPI_strcmp(arg+2, "nogc")) {
						settings.nogc = true;
					}
					else if (!VMPI_strcmp(arg+2, "noincgc")) {
						settings.incremental = false;
					}
#ifdef DEBUGGER
					else if (!VMPI_strcmp(arg+2, "astrace") && i+1 < argc ) {
						settings.astrace_console = VMPI_strtol(argv[++i], 0, 10);
					}
					else if (!VMPI_strcmp(arg+2, "language")) {
						settings.langID=-1;
						for (int j=0;j<kLanguages;j++) {
							if (!VMPI_strcmp(argv[i+1],languageNames[j].str)) {
								settings.langID=j;
								break;
							}
						}
						if (settings.langID==-1) {
							settings.langID = VMPI_atoi(argv[i+1]);
						}
						i++;
					}
#endif /* DEBUGGER */
#ifdef AVMPLUS_SELFTEST
					else if (!VMPI_strncmp(arg+2, "selftest", 8)) {
						settings.do_selftest = true;
						if (arg[10] == '=') {
							VMPI_strncpy(settings.st_mem, arg+11, sizeof(settings.st_mem));
							settings.st_mem[sizeof(settings.st_mem)-1] = 0;
							char *p = settings.st_mem;
							settings.st_component = p;
							while (*p && *p != ',')
								p++;
							if (*p == ',')
								*p++ = 0;
							settings.st_category = p;
							while (*p && *p != ',')
								p++;
							if (*p == ',')
								*p++ = 0;
							settings.st_name = p;
							if (*settings.st_component == 0)
								settings.st_component = NULL;
							if (*settings.st_category == 0)
								settings.st_category = NULL;
							if (*settings.st_name == 0)
								settings.st_name = NULL;
						}
					}
#endif /* AVMPLUS_SELFTEST */
#ifdef AVMPLUS_VERBOSE
					else if (!VMPI_strncmp(arg+2, "verbose", 7)) {
						settings.do_verbose = AvmCore::DEFAULT_VERBOSE_ON; // all 'on' by default
						if (arg[9] == '=') {
                            settings.do_verbose = AvmCore::parseVerboseFlags(&arg[10]);
                        }
					}
#endif /* AVMPLUS_VERBOSE */
#ifdef FEATURE_NANOJIT
					else if (!VMPI_strcmp(arg+2, "nocse")) {
						settings.cseopt = false;
					}
					else if (!VMPI_strcmp(arg+2, "jitordie")) {
						settings.runmode = RM_jit_all;
						settings.jitordie = true;
					}
#endif /* FEATURE_NANOJIT */
					else if (!VMPI_strcmp(arg+2, "interp")) {
						settings.runmode = RM_interp_all;
					}
					else {
						AvmLog("Unrecognized option %s\n", arg);
						usage();
					}
				} 
				else if (!VMPI_strcmp(arg, "-cache_bindings") && i+1 < argc) {
					settings.cacheSizes.bindings = (uint16_t)VMPI_strtol(argv[++i], 0, 10);
				}
				else if (!VMPI_strcmp(arg, "-cache_metadata") && i+1 < argc) {
					settings.cacheSizes.metadata = (uint16_t)VMPI_strtol(argv[++i], 0, 10);
				}
				else if (!VMPI_strcmp(arg, "-cache_methods") && i+1 < argc ) {
					settings.cacheSizes.methods = (uint16_t)VMPI_strtol(argv[++i], 0, 10);
				}
#ifdef FEATURE_NANOJIT
				else if (!VMPI_strcmp(arg, "-Ojit")) {
					settings.runmode = RM_jit_all;
				} 
#endif /* FEATURE_NANOJIT */
#ifdef AVMPLUS_JITMAX
				else if (!VMPI_strcmp(arg, "-jitmax") && i+1 < argc ) {
					extern int jitmin;
					extern int jitmax;
					
					char* val = argv[++i];
					char* dash = VMPI_strchr(val,'-');
					if (dash) {
						if (dash==&val[0]) 
							jitmax = VMPI_atoi(&val[1]); // -n form
						else {
							int32_t hl = VMPI_strlen(dash);
							dash[0] = '\0'; // hammer argv ;)  - go boom?
							jitmin = VMPI_atoi(val); 
							if (hl>1)
								jitmax = VMPI_atoi(&dash[1]); 
						}
					} else {                                            
						jitmax = VMPI_atoi(val);
					}
				}
#endif /* AVMPLUS_JITMAX */
				else if (!VMPI_strcmp(arg, "-memstats")) {
					MMgc::GCHeap::GetGCHeap()->Config().gcstats = true;
					MMgc::GCHeap::GetGCHeap()->Config().autoGCStats = true;
				}
				else if (!VMPI_strcmp(arg, "-memstats-verbose")) {
					MMgc::GCHeap::GetGCHeap()->Config().gcstats = true;
					MMgc::GCHeap::GetGCHeap()->Config().autoGCStats = true;
					MMgc::GCHeap::GetGCHeap()->Config().verbose = true;
				}
				else if (!VMPI_strcmp(arg, "-memlimit") && i+1 < argc ) {
					MMgc::GCHeap::GetGCHeap()->Config().heapLimit = VMPI_strtol(argv[++i], 0, 10);
				}
#ifdef MMGC_POLICY_PROFILING
				else if (!VMPI_strcmp(arg, "-gcbehavior")) {
					MMgc::GCHeap::GetGCHeap()->Config().gcbehavior = true;
				}
#endif
				else if (!VMPI_strcmp(arg, "-eagersweep")) {
					MMgc::GCHeap::GetGCHeap()->Config().eagerSweeping = true;
				}
				else if (!VMPI_strcmp(arg, "-load") && i+1 < argc ) {
					double load;
					double limit;
					int nchar;
					const char* val = argv[++i];
					size_t len = VMPI_strlen(val);
					// limit=0 is legal, it means unlimited
					if (VMPI_sscanf(val, "%lf,%lf%n", &load, &limit, &nchar) == 2 && size_t(nchar) == len && load > 1.0 && limit >= 0.0) {
						MMgc::GCHeap::GetGCHeap()->Config().gcLoad = load;
						MMgc::GCHeap::GetGCHeap()->Config().gcLoadCeiling = limit;
					}
					else if (VMPI_sscanf(val, "%lf%n", &load, &nchar) == 1 && size_t(nchar) == len && load > 1.0) {
						MMgc::GCHeap::GetGCHeap()->Config().gcLoad = load;
					}
					else {
						AvmLog("Bad value to -load: %s\n", val);
						usage();
					}
				}
				else if (!VMPI_strcmp(arg, "-gcwork") && i+1 < argc ) {
					double work;
					int nchar;
					const char* val = argv[++i];
					if (VMPI_sscanf(val, "%lf%n", &work, &nchar) == 1 && size_t(nchar) == VMPI_strlen(val) && work > 0.0 && work <= 1.0) {
						MMgc::GCHeap::GetGCHeap()->Config().gcEfficiency = work;
					}
					else {
						AvmLog("Bad value to -gcwork: %s\n", val);
						usage();
					}
				}
 				else if (!VMPI_strcmp(arg, "-stack")) {
 					unsigned stack;
 					int nchar;
 					const char* val = argv[++i];
 					if (VMPI_sscanf(val, "%u%n", &stack, &nchar) == 1 && size_t(nchar) == VMPI_strlen(val) && stack > avmshell::kStackMargin) {
 						settings.stackSize = uint32_t(stack);
 					}
 					else
 					{
 						AvmLog("Bad argument to -stack\n");
 						usage();
 					}
				}
				else if (!VMPI_strcmp(arg, "-log")) {
					settings.do_log = true;
				} 
#ifdef VMCFG_EVAL
				else if (!VMPI_strcmp(arg, "-repl")) {
					settings.do_repl = true;
				}
#endif /* VMCFG_EVAL */
#ifdef VMCFG_WORKERTHREADS
				else if (!VMPI_strcmp(arg, "-workers") && i+1 < argc ) {
					const char *val = argv[++i];
					int nchar;
					if (val == NULL)
						val = "";
					if (VMPI_sscanf(val, "%d,%d,%d%n", &settings.numworkers, &settings.numthreads, &settings.repeats, &nchar) != 3)
						if (VMPI_sscanf(val, "%d,%d%n", &settings.numworkers, &settings.numthreads, &nchar) != 2) {
							AvmLog("Bad value to -workers: %s\n", val);
							usage();
						}
					if (settings.numthreads < 1 || 
						settings.numworkers < settings.numthreads || 
						settings.repeats < 1 ||
						size_t(nchar) != VMPI_strlen(val)) {
						AvmLog("Bad value to -workers: %s\n", val);
						usage();
					}
				}
#endif // VMCFG_WORKERTHREADS
#ifdef AVMPLUS_WIN32
				else if (!VMPI_strcmp(arg, "-error")) {
					show_error = true;
#ifndef UNDER_CE
					SetErrorMode(0);  // set to default
#endif
				}
#endif // AVMPLUS_WIN32
#ifdef AVMPLUS_WITH_JNI
				else if (!VMPI_strcmp(arg, "-jargs")) {
					// all the following args until the semi colon is for java.
					//@todo fix up this hard limit
					bool first = true;
					Java::startup_options = new char[256];
					VMPI_memset(Java::startup_options, 0, 256);
					
					for(i++; i<argc; i++)
					{
						if (*argv[i] == ';')
							break;
						if (!first) VMPI_strcat(Java::startup_options, " ");
						VMPI_strcat(Java::startup_options, argv[i]);
						first = false;
					}
					AvmAssert(VMPI_strlen(Java::startup_options) < 256);
				}
#endif /* AVMPLUS_WITH_JNI */
#ifdef DEBUGGER
				else if (!VMPI_strcmp(arg, "-d")) {
					settings.enter_debugger_on_launch = true;
				}
#endif /* DEBUGGER */
#ifdef VMCFG_TEST_API_VERSIONING
				else if (!VMPI_strcmp(arg, "-api")) {
					settings.api = VMPI_atoi(argv[i+1]);
					i++;
				}
#endif
				else {
					// Unrecognized command line option
					AvmLog("Unrecognized option %s\n", arg);
					usage();
				}
			}
			else {
				if (settings.filenames == NULL)
					settings.filenames = &argv[i];
			}
		}
		
		if (settings.filenames == NULL)
			settings.filenames = &argv[argc];
		
		if (settings.numfiles == -1)
			settings.numfiles = int(&argv[argc] - settings.filenames);
		
		if (settings.arguments == NULL) {
			settings.arguments = &argv[argc];
			settings.numargs = 0;
		}

		AvmAssert(settings.filenames != NULL && settings.numfiles != -1);
		AvmAssert(settings.arguments != NULL && settings.numargs != -1);
	
		if (print_version)
		{
			AvmLog("shell " AVMPLUS_VERSION_USER " " AVMPLUS_BIN_TYPE " build " AVMPLUS_BUILD_CODE "\n");
			AvmLog("features %s\n", avmfeatures);
			Platform::GetInstance()->exit(1);
		}
		
		// Vetting the options
		
#ifdef AVMSHELL_PROJECTOR_SUPPORT
		if (settings.programFilename != NULL && ShellCore::isValidProjectorFile(settings.programFilename)) {
			if (settings.do_selftest || settings.do_repl || settings.numfiles > 0) {
				AvmLog("Projector files can't be used with -repl, -Dselftest, or program file arguments.\n");
				usage();
			}
			if (settings.numthreads > 1 || settings.numworkers > 1) {
				AvmLog("A projector requires exactly one worker on one thread.\n");
				usage();
			}
			settings.do_projector = 1;
			return;
		}
#endif

#ifndef VMCFG_AOT
		if (settings.numfiles == 0) {
			// no files, so we need something more
			if (!settings.do_selftest && !settings.do_repl) {
				AvmLog("You must provide input files, -repl, or -Dselftest, or the executable must be a projector file.\n");
				usage();
			}
		}
#endif

#ifdef VMCFG_EVAL
		if (settings.do_repl)
		{
			if (settings.numthreads > 1 || settings.numworkers > 1) {
				AvmLog("The REPL requires exactly one worker on one thread.\n");
				usage();
			}
		}
#endif
		
#ifdef AVMPLUS_SELFTEST
		if (settings.do_selftest)
		{
			// Presumably we'd want to use the selftest harness to test multiple workers eventually.
			if (settings.numthreads > 1 || settings.numworkers > 1 || settings.numfiles > 0) {
				AvmLog("The selftest harness requires exactly one worker on one thread, and no input files.\n");
				usage();
			}
		}
#endif
	}
	
	// Does not return

	/*static*/
	void Shell::usage()
	{
		AvmLog("avmplus shell " AVMPLUS_VERSION_USER " " AVMPLUS_BIN_TYPE " build " AVMPLUS_BUILD_CODE "\n\n");
		AvmLog("usage: avmplus\n");
#ifdef DEBUGGER
		AvmLog("          [-d]          enter debugger on start\n");
#endif
		AvmLog("          [-memstats]   generate statistics on memory usage\n");
		AvmLog("          [-memstats-verbose]\n"
			   "                        generate more statistics on memory usage\n");
		AvmLog("          [-memlimit d] limit the heap size to d pages\n");
		AvmLog("          [-eagersweep] sweep the heap synchronously at the end of GC;\n"
			   "                        improves usage statistics.\n");
#ifdef MMGC_POLICY_PROFILING
		AvmLog("          [-gcbehavior] summarize GC behavior and policy computation\n"); 
#endif
		AvmLog("          [-load L[,X]] GC load factor (default 2.0) and max multiplier (default 3.0)\n");
		AvmLog("          [-gcwork G]   Max fraction of time (default 0.25) we're willing to spend in GC\n");
		AvmLog("          [-stack N]    Stack size in bytes (will be honored approximately).\n"
			   "                        Be aware of the stack margin: %u\n", avmshell::kStackMargin);
		AvmLog("          [-cache_bindings N]   size of bindings cache (0 = unlimited)\n");
		AvmLog("          [-cache_metadata N]   size of metadata cache (0 = unlimited)\n");
		AvmLog("          [-cache_methods  N]   size of method cache (0 = unlimited)\n");
		AvmLog("          [-Dgreedy]    collect before every allocation\n");
		AvmLog("          [-Dnogc]      don't collect\n");
		AvmLog("          [-Dnoincgc]   don't use incremental collection\n");
#ifdef DEBUGGER
		AvmLog("          [-Dastrace N] display AS execution information, where N is [1..4]\n");
		AvmLog("          [-Dlanguage l] localize runtime errors, languages are:\n");
		AvmLog("                        en,de,es,fr,it,ja,ko,zh-CN,zh-TW\n");
#endif
#ifdef AVMPLUS_VERBOSE
		AvmLog("          [-Dverbose[=[parse,verify,interp,traits,builtins,jit,minaddr,memstats,sweep,occupancy]] \n");
		AvmLog("                        With no options, enables extreme! output mode.  Otherwise the\n");
		AvmLog("                        options are mostly self-descriptive except for the following: \n");
		AvmLog("                           builtins - includes output from builtin methods\n");
		AvmLog("                           minaddr - [jit] minimize intstruction address output\n");
		AvmLog("                           memstats - generate statistics on memory usage \n");
		AvmLog("                           sweep - [memstats] include detailed sweep information \n");
		AvmLog("                           occupancy - [memstats] include occupancy bit graph \n");
		AvmLog("                        Note that ordering matters for options with dependencies.  Dependencies \n");
		AvmLog("                        are contained in [ ] For example, 'minaddr' requires 'jit' \n");
#endif
#ifdef FEATURE_NANOJIT
		AvmLog("          [-Dinterp]    do not generate machine code, interpret instead\n");
		AvmLog("          [-Ojit]       use jit always, never interp (except when the jit fails)\n");
		AvmLog("          [-Djitordie]  use jit always, and abort when the jit fails\n");
		AvmLog("          [-Dnocse]     disable CSE optimization \n");
	#ifdef AVMPLUS_IA32
        AvmLog("          [-Dnosse]     use FPU stack instead of SSE2 instructions\n");
        AvmLog("          [-Dfixedesp]  pre-decrement stack for all needed call usage upon method entry\n");
	#endif
#endif
#ifdef AVMPLUS_JITMAX
        AvmLog("          [-jitmax N-M] jit the Nth to Mth methods only; N- and -M are also valid.\n");
#endif
#ifdef AVMPLUS_VERIFYALL
	    AvmLog("          [-Dverifyall] verify greedily instead of lazily\n");
#endif
#ifdef AVMPLUS_SELFTEST
		AvmLog("          [-Dselftest[=component,category,test]]");
		AvmLog("                        run selftests\n");
#endif
		AvmLog("          [-Dtimeout]   enforce maximum 15 seconds execution\n");
		AvmLog("          [-Dversion]   print the version and the list of compiled-in features and then exit\n");
#ifdef AVMPLUS_WIN32
		AvmLog("          [-error]      crash opens debug dialog, instead of dumping\n");
#endif
#ifdef VMCFG_EVAL
		AvmLog("          [-repl]       read-eval-print mode\n");
#endif
#ifdef VMCFG_WORKERTHREADS
		AvmLog("          [-workers W,T[,R]]\n");
		AvmLog("                        Spawn W worker VMs on T threads where W >= T and T >= 1.\n");
		AvmLog("                        The files provided are handed off to the workers in the order given,\n");
		AvmLog("                        as workers become available, and these workers are scheduled onto threads\n");
		AvmLog("                        in a deterministic order that prevents them from having affinity to a thread.\n");
		AvmLog("                        To test this functionality you want many more files than workers and many more\n");
		AvmLog("                        workers than threads, and at least two threads.\n");
		AvmLog("                        If R > 0 is provided then it is the number of times the list of files is repeated.\n");
#endif
		AvmLog("          [-log]\n");
#ifdef VMCFG_TEST_API_VERSIONING
		AvmLog("          [-api N] execute ABCs as version N (see api-versions.h)\n");
#endif
		AvmLog("          [-jargs ... ;] args passed to Java runtime\n");
		AvmLog("          [filename.{abc,swf} ...\n");
		AvmLog("          [-- application argument ...]\n");
		Platform::GetInstance()->exit(1);
	}
}
