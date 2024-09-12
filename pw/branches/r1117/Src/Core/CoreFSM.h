#pragma once
#include "BaseFSM.h"
#include "../System/Updater.h"

namespace Updater
{
	_interface IFunctor;
}

namespace NCore
{
	class CoreFSM 
		: public CFSMBase
	{
		OBJECT_METHODS( 0x1F4A8B37, CoreFSM )

	protected:
		Updater::CUpdater updatesFromUI;
		Updater::CUpdater updatesToUI;

	public:
		typedef int StateId;
		typedef CObjectBase* (*MessageBuilder)();

	private:
		///< message cañh for created states, key - id for state, value - message builder
		hash_map<StateId, MessageBuilder> messages;

	public:
		CoreFSM();
		virtual void Step(float dt);
		virtual void SetState( IBaseFSMState* state ); // Hack for Audit

    void RegisterToCore( int, Updater::IUpdateProcessorFunc* );
    void RegisterFromCore( int, Updater::IUpdateProcessorFunc* );
		void RegisterProcessorToCore( Updater::CUpdateProcessor *pProcessor );
		void RegisterProcessorFromCore( Updater::CUpdateProcessor *pProcessor );

		void PushMessageToCore( CObjectBase *pMsg );
		void PushMessageFromCore( CObjectBase *pMsg );

		void RegisterMessageBuilder( StateId, MessageBuilder );

		virtual void Init();
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CoreFSM *GetGlobalGameFSM();
	void ReleaseGlobalGameFSM();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
