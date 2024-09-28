#ifndef __NODE_INITIALIZER_H_INCLUDED__993121__
#define __NODE_INITIALIZER_H_INCLUDED__993121__

#include "NodeManager.h"
#include "System/sleep.h"
#include <boost/thread.hpp>

namespace nvl {
namespace node {


    enum ERunnerStates {

			STARTING,
			STARTED,
			FAIL

		};

		struct CRunNodeResults {

			CRunNodeResults(): State( STARTING )
			{}

			volatile ERunnerStates State;
			CPtr< INodeManager > cpNodeManager;

		};

		struct CThreadRunner {

			CRunNodeResults & ResultsContainer;

			CThreadRunner( CRunNodeResults & _ResultsContainer ): ResultsContainer( _ResultsContainer )
			{}

			CThreadRunner & operator = ( CThreadRunner const & Other )
			{
				ResultsContainer = Other.ResultsContainer;
				return *this;
			}

			void operator()()
			{
				CPtr< INodeManager > cpNodeManager;
				if ( NV_CFAIL( CreateNodeManager( cpNodeManager ) ) )
					ResultsContainer.State = FAIL;
				else {

					ResultsContainer.cpNodeManager = cpNodeManager;
					ResultsContainer.State = STARTED;

					NI_VERIFY_NO_RET(
						NV_CSUCCESS( cpNodeManager->GetThreadManager()->RunMainThread( cpNodeManager, NULL, NULL ) ),
						"Cannot run the main thread (Node System)"
					);

				}
			}

		};


	bool Initialize( CPtr< INodeManager > &cpNodeManager )
	{
		CRunNodeResults ResultsContainer;
		CThreadRunner Runner( ResultsContainer );

		try {

			boost::thread NodeMainThread( Runner );

		} catch ( boost::thread_resource_error & ) {
			return result_no_resources;
		}

		while ( STARTING == ResultsContainer.State )
			nival::sleep( 0 );

		if ( STARTED == ResultsContainer.State ) {

			cpNodeManager = ResultsContainer.cpNodeManager;
			return true;

		}

		return false;
	}

} // namespace node
} // namespace nvl

#endif // __NODE_INITIALIZER_H_INCLUDED__993121__
