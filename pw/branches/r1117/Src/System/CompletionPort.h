#ifndef COMPLETIONPORT_H_EB372940_5DB1_4
#define COMPLETIONPORT_H_EB372940_5DB1_4

#include "System/Thread.h"
#include "System/ThreadNames.h"

namespace threading
{

  class IOCPSheduler;
  struct IOCPRequest;

  class IOCPClient
  {
  public:
    virtual HANDLE GetAssociatedHandle() = 0;
    virtual void ProcessRequest( IOCPSheduler* sheuduler, IOCPRequest* req, DWORD numBytes ) = 0;
    virtual void ProcessError( DWORD errorCode, IOCPRequest* req ) = 0;
  };

  struct IOCPRequest : public OVERLAPPED
  {
    IOCPRequest() { Internal = 0; InternalHigh = 0; Offset = 0; OffsetHigh = 0;  hEvent = 0; }
    enum ERequest
    {
      StopWorkerThread = 0,
      FirstClientRequest = 1,
      LastClientRequest = 10000,
      FirstShedulerRequest = 10001,
      LastShedulerRequest = 20000,
    };
    ERequest requestType;

  };

  class IOCPSheduler
  {
  public:
    void Initialize( int numThreads, int numConcurrent )
    {
      completionPort = CreateIoCompletionPort( INVALID_HANDLE_VALUE, 0, 0, numConcurrent );
      threadPool.resize( numThreads );
      for ( int i = 0; i < numThreads; ++i )
      {
        threadPool[i] = new IOCPThread( this );
        threadPool[i]->Resume();
      }
    }
    void Terminate()
    {
      IOCPRequest stopRequest;
      stopRequest.requestType = IOCPRequest::StopWorkerThread;

      for ( int i = 0; i < threadPool.size(); ++i )
      {
        if ( !threadPool[i]->Finished() )
          PostRequest( 0, &stopRequest );
      }

      bool allTerminated;
      do 
      {
        allTerminated = true;
        for ( int i = 0; i < threadPool.size(); ++i )
        {
          if ( !threadPool[i]->Finished() )
            allTerminated = false; 
        }
        Sleep( 10 );
        PostRequest( 0, &stopRequest );
      } while ( !allTerminated );

      for ( int i = 0; i < threadPool.size(); ++i )
      {
        delete threadPool[i];
      }
      threadPool.clear();
      CloseHandle( completionPort );
      completionPort = INVALID_HANDLE_VALUE;
    }

    IOCPSheduler( int numThreads, int numConcurrent )
      : completionPort( INVALID_HANDLE_VALUE )
    {
      Initialize( numThreads, numConcurrent );
    }

    ~IOCPSheduler()
    {
    }

    void PostRequest( IOCPClient* cli, IOCPRequest* req )
    {
      if ( completionPort == INVALID_HANDLE_VALUE )
        return;

      BOOL ret = PostQueuedCompletionStatus( completionPort, 0, (ULONG_PTR)cli, (OVERLAPPED*)req );

      NI_ASSERT( ret, NI_STRFMT("PostQueuedCompletionStatus error: %x", GetLastError() ) );
    }

    void CancelIO( IOCPClient* cli )
    {
      if ( completionPort == INVALID_HANDLE_VALUE )
        return;

      ::CancelIo( cli->GetAssociatedHandle() );
    }

    virtual void RegisterClient( IOCPClient* cli )
    {
      HANDLE h = cli->GetAssociatedHandle();
      if ( h == 0 )
        return;

      completionPort = CreateIoCompletionPort( h, completionPort, (ULONG_PTR)cli, 0 );
      NI_ASSERT( completionPort != 0, NI_STRFMT("RegisterClient error: %x", GetLastError() ) );
    }

    virtual void DisconnectClient( IOCPClient* cli ) {}
    virtual void ProcessRequest( IOCPRequest* req, DWORD numBytes ) {}

  private:
    class IOCPThread : public threading::Thread
    {
    public:

      virtual unsigned Work() 
      {
#if !defined( _SHIPPING )
        threading::SetDebugThreadName( "IOCP worker" );
#endif
        while( isRunning )
        {
          DWORD numBytes = 0;
          IOCPClient* client = 0;
          OVERLAPPED* overlapped = 0;

          BOOL ret = GetQueuedCompletionStatus( pOwner->completionPort, &numBytes, (DWORD*)&client, &overlapped, INFINITE );

          if ( ret )  
          {
            IOCPRequest* req = static_cast<IOCPRequest*>( overlapped );

            if ( client == 0 )
            {
              IOCPRequest* req = static_cast<IOCPRequest*>( overlapped );
              NI_ASSERT(  req->requestType == IOCPRequest::StopWorkerThread, "Error: client is not specified" );
              isRunning = false;
            } 
            else
            {
              if ( req->requestType == IOCPRequest::StopWorkerThread )
              {
                isRunning = false;
              }
              else if( req->requestType >= IOCPRequest::FirstClientRequest && req->requestType <= IOCPRequest::LastClientRequest )
              {
                client->ProcessRequest( pOwner, req, numBytes );  
              }
              else if( req->requestType >= IOCPRequest::FirstShedulerRequest && req->requestType <= IOCPRequest::LastShedulerRequest )
              {
                pOwner->ProcessRequest( req, numBytes );
              }
              else 
                NI_ALWAYS_ASSERT( "Invalid request type" );
            }

          }
          else
          {
            DWORD ioError = GetLastError();
            NI_ASSERT( ioError == ERROR_NETNAME_DELETED || ioError == ERROR_OPERATION_ABORTED, NI_STRFMT("GetQueuedCompletionStatus error: %x", ioError ) );
            if (client)
            {
              IOCPRequest* req = static_cast<IOCPRequest*>( overlapped );
              client->ProcessError( ioError, req );
              pOwner->DisconnectClient( client );
            }
          }
        }

        return 0;
      }
      IOCPThread( IOCPSheduler* _pOwner ) : pOwner( _pOwner ) 
      {
      }
    private:
      IOCPSheduler* pOwner;
    };

    HANDLE completionPort;
    vector<IOCPThread*> threadPool;
  };


}

#endif //#define COMPLETIONPORT_H_EB372940_5DB1_4
