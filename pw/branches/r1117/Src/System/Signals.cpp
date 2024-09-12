#include "stdafx.h"
#include <signal.h>
#include "Signals.h"

namespace Signals {

	#if defined( NV_WIN_PLATFORM )

		void SignalHandler(int signal)
		{
			LOG_A(0) << "ABORT SIGNALED";
			throw "ABRT";
		}

		// перехватываем abort (который у нас любит делать кое-кто, не будем показывать пальцем, но это ACE/IOTerabit)
		void CatchAbort()
		{
			signal(SIGABRT, SignalHandler);
			_set_abort_behavior( 0, _WRITE_ABORT_MSG ); // чтобы не лезла печатать сообщение и делать CrtDbgBreak()
		}

		//// это нужно, чтобы ловить abort, проиходящий по ACE_ASSERT в глубине dll-ки, в стиле:
		//  try {
		//    abort();
		//  }
		//  catch(...) {
		//    printf( "Abort catched\n");
		//  }

	#elif defined( NV_LINUX_PLATFORM )

		void SignalHandler( int signal )
		{
			LOG_A(0) << "ABORT SIGNALED";
		}

		void CatchAbort()
		{
			signal( SIGABRT, SignalHandler );
		}

	#endif

} // namespace Signals

