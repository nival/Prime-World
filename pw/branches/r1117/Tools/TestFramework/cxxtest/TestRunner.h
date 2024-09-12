#ifndef __cxxtest_TestRunner_h__
#define __cxxtest_TestRunner_h__

//
// TestRunner is the class that runs all the tests.
// To use it, create an object that implements the TestListener
// interface and call TestRunner::runAllTests( myListener );
// 

#include <cxxtest/TestListener.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestSuite.h>
#include <cxxtest/TestTracker.h>

namespace CxxTest 
{
    class TestRunner
    {
      const std::vector<std::string>& params;

      static void EnumerateThreads( std::vector<DWORD>& threadIds )
      {
        HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
        if (h != INVALID_HANDLE_VALUE) 
        {
          THREADENTRY32 te;
          te.dwSize = sizeof(te);
          if (Thread32First(h, &te)) 
          {
            do 
            {
              if (te.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(te.th32OwnerProcessID)) 
              {
                if ( te.th32OwnerProcessID == GetCurrentProcessId() )
                {
                  threadIds.push_back(te.th32ThreadID);
                }
              }
              te.dwSize = sizeof(te);
            } while (Thread32Next(h, &te));
          }
          CloseHandle(h);
        }
      }

    public:
        static void runAllTests( const std::vector<std::string>& params, TestListener &listener )
        {
            tracker().setListener( &listener );
            _TS_TRY { TestRunner(params).runWorld(); }
            _TS_LAST_CATCH( { tracker().failedTest( __FILE__, __LINE__, "Exception thrown from world" ); } );
            tracker().setListener( 0 );
        }

        static void runAllTests( const std::vector<std::string>& params, TestListener *listener )
        {
            if ( listener ) {
                listener->warning( __FILE__, __LINE__, "Deprecated; Use runAllTests( TestListener & )" );
                runAllTests( params, *listener );
            }
        }        
    
    private:

      TestRunner( const std::vector<std::string>& _params ) : params(_params) {}

      bool IsFindTest( TestDescription *sd )
      {
        bool isFind = false;
        for ( unsigned int i = 0; i < params.size(); i++ )
        {
          if ( strcmp( params[i].c_str(), sd->testName() ) == 0 || strcmp( params[i].c_str(), sd->suiteName() ) == 0 )
          {
            isFind = true;
            break;
          }
        }

        return isFind;
      }

        void runWorld()
        {
            RealWorldDescription wd;
            WorldGuard sg;
            
            tracker().enterWorld( wd );
            if ( wd.setUp() ) 
            {
              for ( SuiteDescription *sd = wd.firstSuite(); sd; sd = sd->next() )
              {
                if ( sd->active() )
                {
                  runSuite( *sd );
                }
              }
              wd.tearDown();
            }
            tracker().leaveWorld( wd );
        }
    
        void runSuite( SuiteDescription &sd )
        {
            StateGuard sg;
            
            bool isNotNeedFind = params.empty();

            tracker().enterSuite( sd );

            if ( sd.setUp() ) 
            {
              for ( TestDescription *td = sd.firstTest(); td; td = td->next() )
              {
                if ( ( isNotNeedFind || IsFindTest(td) ) && td->active() )
                {
                  runTest( *td );
                }
              }
              sd.tearDown();
            }
            tracker().leaveSuite( sd );
        }

        void runTest( TestDescription &td )
        {
            StateGuard sg;

            std::vector<DWORD> threadIds;
            std::vector<DWORD> afterThreadIds;
            std::vector<DWORD> hangsThreadIds;
            EnumerateThreads( threadIds );
            
            tracker().enterTest( td );
            if ( td.setUp() ) {
                td.run();
                td.tearDown();
            }
            tracker().leaveTest( td );

            EnumerateThreads( afterThreadIds );

            for ( unsigned int i = 0; i < afterThreadIds.size(); i++ )
            {
              if ( std::find(threadIds.begin(),threadIds.end(),afterThreadIds[i]) == threadIds.end())
              {
                hangsThreadIds.push_back(afterThreadIds[i]);
              }
            }
            for ( unsigned int i = 0; i < hangsThreadIds.size(); i++ )
            {
              HANDLE hThread = OpenThread( THREAD_ALL_ACCESS, false, hangsThreadIds[i] );
              if( hThread == 0 || !TerminateThread( hThread, 0 ) )
              {
                TS_FAIL( "Error close hang thread" );
              }
            }

            if ( hangsThreadIds.size() )
            {
              TS_FAIL( "Have hang threads" );
            }
        }
        
        class StateGuard
        {
#ifdef _CXXTEST_HAVE_EH
            bool _abortTestOnFail;
#endif // _CXXTEST_HAVE_EH
            unsigned _maxDumpSize;
            
        public:
            StateGuard()
            {
#ifdef _CXXTEST_HAVE_EH
                _abortTestOnFail = abortTestOnFail();
#endif // _CXXTEST_HAVE_EH
                _maxDumpSize = maxDumpSize();
            }
            
            ~StateGuard()
            {
#ifdef _CXXTEST_HAVE_EH
                setAbortTestOnFail( _abortTestOnFail );
#endif // _CXXTEST_HAVE_EH
                setMaxDumpSize( _maxDumpSize );
            }
        };

        class WorldGuard : public StateGuard
        {
        public:
            WorldGuard() : StateGuard()
            {
#ifdef _CXXTEST_HAVE_EH
                setAbortTestOnFail( CXXTEST_DEFAULT_ABORT );
#endif // _CXXTEST_HAVE_EH
                setMaxDumpSize( CXXTEST_MAX_DUMP_SIZE );
            }
        };
    };

    //
    // For --no-static-init
    //
    void initialize();
};


#endif // __cxxtest_TestRunner_h__
