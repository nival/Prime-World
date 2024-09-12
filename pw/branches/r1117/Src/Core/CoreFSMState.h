#ifndef _CORE_FSM_STATE_H_
#define _CORE_FSM_STATE_H_


#include "BaseState.h"
#include "../System/UpdateProcessor.h"

namespace NCore
{
	class CoreFSM;

	class CoreFSMState
		: public IBaseFSMState
		, public Updater::CUpdateProcessor
	{
	protected:
		CPtr<CoreFSM> pContext;
		virtual void SubscribeUpdates();

		CoreFSMState() {}

	public:		
		CoreFSMState( CoreFSM *pStateMachine ) : pContext( pStateMachine ) {};

		virtual void Init();
		virtual IBaseFSMState* Step(float) = 0;
	};
}

#endif

