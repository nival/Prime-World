// Generated from ST_mmgc_threads.st
// -*- mode: c -*-
//
// ***** BEGIN LICENSE BLOCK *****
// Version: MPL 1.1/GPL 2.0/LGPL 2.1
//
// The contents of this file are subject to the Mozilla Public License Version
// 1.1 (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at
// http://www.mozilla.org/MPL/
//
// Software distributed under the License is distributed on an "AS IS" basis,
// WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
// for the specific language governing rights and limitations under the
// License.
//
// The Original Code is [Open Source Virtual Machine.].
//
// The Initial Developer of the Original Code is
// Adobe System Incorporated.
// Portions created by the Initial Developer are Copyright (C) 2004-2006
// the Initial Developer. All Rights Reserved.
//
// Contributor(s):
//   Adobe AS3 Team
//
// Alternatively, the contents of this file may be used under the terms of
// either the GNU General Public License Version 2 or later (the "GPL"), or
// the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
// in which case the provisions of the GPL or the LGPL are applicable instead
// of those above. If you wish to allow use of your version of this file only
// under the terms of either the GPL or the LGPL, and not to allow others to
// use your version of this file under the terms of the MPL, indicate your
// decision by deleting the provisions above and replace them with the notice
// and other provisions required by the GPL or the LGPL. If you do not delete
// the provisions above, a recipient may use your version of this file under
// the terms of any one of the MPL, the GPL or the LGPL.
//
// ***** END LICENSE BLOCK ***** */

#include "avmshell.h"
#ifdef AVMPLUS_SELFTEST
#if defined VMCFG_WORKERTHREADS
namespace avmplus {
class ST_mmgc_threads : public Selftest {
public:
ST_mmgc_threads(AvmCore* core);
virtual void run(int n);
virtual void prologue();
virtual void epilogue();
private:
static const char* ST_names[];
void test0();
	
private:
    MMgc::GC *gc;
    MMgc::FixedAlloc *fa;
    MMgc::FixedMalloc *fm;
	bool waiting;
	bool result;
	bool isDead;
	pthread_t pthread;
	pthread_mutex_t pmutex;	
	pthread_cond_t pcond;

	static void* slaveRunner(void *arg)
    {
	    ((ST_mmgc_threads*)arg)->slaveRun();
		return NULL;
    }

	void slaveRun()
	{
		wait();
        {
		 MMGC_GCENTER(gc);	
  	     result &= !isDead;
	     gc->ReapZCT();
  	     result &= !isDead;
	     gc->Collect();
		 result &= !isDead;
		}
 		kick();
	}

	void startSlave()
	{
	   pthread_create(&pthread, NULL, slaveRunner, this);
	}
	
	void kick()
    {
		pthread_mutex_lock (&pmutex);
		while(!waiting) {
			pthread_mutex_unlock (&pmutex);
			usleep(100);
		    pthread_mutex_lock (&pmutex);
        }
		pthread_cond_signal (&pcond);
		while(waiting) {
			pthread_mutex_unlock (&pmutex);
			usleep(100);
		    pthread_mutex_lock (&pmutex);
        }
		pthread_mutex_unlock (&pmutex);
    }

	void wait()
	{
		pthread_mutex_lock (&pmutex);
		GCAssert(waiting == false);
		waiting = true;
		pthread_cond_wait (&pcond, &pmutex);
		waiting = false;
		pthread_mutex_unlock (&pmutex);
	}
	
};
ST_mmgc_threads::ST_mmgc_threads(AvmCore* core)
    : Selftest(core, "mmgc", "threads", ST_mmgc_threads::ST_names)
{}
const char* ST_mmgc_threads::ST_names[] = {"mmgc_gc_root_thread", NULL };
void ST_mmgc_threads::run(int n) {
switch(n) {
case 0: test0(); return;
}
}
void ST_mmgc_threads::prologue() {
	gc=new MMgc::GC(MMgc::GCHeap::GetGCHeap(), MMgc::GC::kIncrementalGC);
	if (gc==NULL) {
	    MMgc::GCHeap::Init();
	    gc=new MMgc::GC(MMgc::GCHeap::GetGCHeap(), MMgc::GC::kIncrementalGC);
	}
	pthread_mutex_init(&pmutex, NULL);
	pthread_cond_init(&pcond, NULL);
	result = true;
    isDead = false;
	waiting = false;

}
void ST_mmgc_threads::epilogue() {
	pthread_mutex_destroy(&pmutex);
	pthread_cond_destroy(&pcond);
	delete gc;

}
using namespace MMgc;

class RCObjectNotifier : public RCObject
{
public:
		RCObjectNotifier(bool *isDead) : isDead(isDead) {}
		~RCObjectNotifier() { *isDead = true; isDead = NULL; }
		bool *isDead;
};

void ST_mmgc_threads::test0() {
	   startSlave();
	   MMGC_GCENTER(gc);
   	   /*RCObject *obj =*/ new (gc) RCObjectNotifier(&isDead);
	   {
          MMGC_GC_ROOT_THREAD(gc);
		  kick();
    	  wait();
       }

verifyPass(result, "result", __FILE__, __LINE__);

verifyPass(!isDead, "!isDead", __FILE__, __LINE__);
	   gc->ReapZCT();
verifyPass(!isDead, "!isDead", __FILE__, __LINE__);
	   gc->Collect();
verifyPass(!isDead, "!isDead", __FILE__, __LINE__);

	   pthread_join(pthread, NULL);

}
void create_mmgc_threads(AvmCore* core) { new ST_mmgc_threads(core); }
}
#endif
#endif
