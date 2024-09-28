#include "stdafx.h"
#include "LPeered.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Peered
{


	typedef void (Peered::IGameClient::*TStart)( const ClientStartInfo* clientStartInfo, RIGameServerReconnect * gameServerReconnect);
	typedef void (Peered::IGameClient::*TStep)( int step, int lastConfirmedStep, const nstl::vector<rpc::MemoryBlock>* commands, const nstl::vector<BriefClientInfo>* statuses, const nstl::vector<GapInfo>* clientGaps, const Transport::MessageMiscInfo* __miscInfo__);
	typedef void (Peered::IGameClient::*TStepLoading)( int step, int lastConfirmedStep, const nstl::vector<rpc::MemoryBlock>* commands, const nstl::vector<BriefClientInfo>* statuses, const nstl::vector<GapInfo>* clientGaps);
	typedef void (Peered::IGameClient::*TStepBatch)( int lastConfirmedStep, const nstl::vector<ClientStepData>* stepData);
	typedef void (Peered::IGameClient::*TOnAsync)( int step, const nstl::vector<AsyncInfo>* async);
	typedef void (Peered::IGameClient::*TOnChangeClientStatus)( const nstl::vector<BriefClientInfo>* clientStatuses);
	typedef void (Peered::IGameClient::*TAward)( const vector<roll::SAwardInfo> * _awards);
	typedef void (Peered::IGameClient::*TOnSpectate)( const SpectatorInfo* info);


    bool LIGameClient::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Peered::IGameClient::Start/0");rpc::VCall( stack, localObject.Get(), TStart(&Peered::IGameClient::Start), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("Peered::IGameClient::Step/1");rpc::VCall( stack, localObject.Get(), TStep(&Peered::IGameClient::Step), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("Peered::IGameClient::StepLoading/2");rpc::VCall( stack, localObject.Get(), TStepLoading(&Peered::IGameClient::StepLoading), popResult); } break;
			case 3: { NI_PROFILE_BLOCK("Peered::IGameClient::StepBatch/3");rpc::VCall( stack, localObject.Get(), TStepBatch(&Peered::IGameClient::StepBatch), popResult); } break;
			case 4: { NI_PROFILE_BLOCK("Peered::IGameClient::OnAsync/4");rpc::VCall( stack, localObject.Get(), TOnAsync(&Peered::IGameClient::OnAsync), popResult); } break;
			case 5: { NI_PROFILE_BLOCK("Peered::IGameClient::OnStart/5");rpc::VCall( stack, localObject.Get(), &Peered::IGameClient::OnStart, popResult); } break;
			case 6: { NI_PROFILE_BLOCK("Peered::IGameClient::OnTimeScaleChanged/6");rpc::VCall( stack, localObject.Get(), &Peered::IGameClient::OnTimeScaleChanged, popResult); } break;
			case 7: { NI_PROFILE_BLOCK("Peered::IGameClient::OnChangeClientStatus/7");rpc::VCall( stack, localObject.Get(), TOnChangeClientStatus(&Peered::IGameClient::OnChangeClientStatus), popResult); } break;
			case 8: { NI_PROFILE_BLOCK("Peered::IGameClient::OnDisconnect/8");rpc::VCall( stack, localObject.Get(), &Peered::IGameClient::OnDisconnect, popResult); } break;
			case 9: { NI_PROFILE_BLOCK("Peered::IGameClient::OnRejoin/9");rpc::VCall( stack, localObject.Get(), &Peered::IGameClient::OnRejoin, popResult); } break;
			case 10: { NI_PROFILE_BLOCK("Peered::IGameClient::RequestWorldData/10");rpc::VCall( stack, localObject.Get(), &Peered::IGameClient::RequestWorldData, popResult); } break;
			case 11: { NI_PROFILE_BLOCK("Peered::IGameClient::RequestCrcData/11");rpc::VCall( stack, localObject.Get(), &Peered::IGameClient::RequestCrcData, popResult); } break;
			case 12: { NI_PROFILE_BLOCK("Peered::IGameClient::Award/12");rpc::VCall( stack, localObject.Get(), TAward(&Peered::IGameClient::Award), popResult); } break;
			case 13: { NI_PROFILE_BLOCK("Peered::IGameClient::OnSpectate/13");rpc::VCall( stack, localObject.Get(), TOnSpectate(&Peered::IGameClient::OnSpectate), popResult); } break;
			case 14: { NI_PROFILE_BLOCK("Peered::IGameClient::OnPlaySameTeamDecision/14");rpc::VCall( stack, localObject.Get(), &Peered::IGameClient::OnPlaySameTeamDecision, popResult); } break;
			case 15: { NI_PROFILE_BLOCK("Peered::IGameClient::OnBadBehaviourComplaint/15");rpc::VCall( stack, localObject.Get(), &Peered::IGameClient::OnBadBehaviourComplaint, popResult); } break;
			case 16: { NI_PROFILE_BLOCK("Peered::IGameClient::OnProtectionAsync/16");rpc::VCall( stack, localObject.Get(), &Peered::IGameClient::OnProtectionAsync, popResult); } break;

        default:
            popResult = false;
            break;
        }
        return popResult;
    }

}


namespace rpc
{
template<>
rpc::ILocalEntity* CreateLocalEntity(Peered::IGameClient* api, rpc::IEntityMap* entityMap)
{
  return new Peered::LIGameClient(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Peered::LIGameClient )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Peered
{


	typedef void (Peered::IGameClientReconnect::*TApplyWorldDataInfo)( const WorldDataInfo* worldDataInfo);
	typedef void (Peered::IGameClientReconnect::*TApplyWorldDataPart)( const rpc::MemoryBlock* worldDataPart);


    bool LIGameClientReconnect::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Peered::IGameClientReconnect::ApplyWorldDataInfo/0");rpc::VCall( stack, localObject.Get(), TApplyWorldDataInfo(&Peered::IGameClientReconnect::ApplyWorldDataInfo), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("Peered::IGameClientReconnect::ApplyWorldDataPart/1");rpc::VCall( stack, localObject.Get(), TApplyWorldDataPart(&Peered::IGameClientReconnect::ApplyWorldDataPart), popResult); } break;

        default:
            popResult = false;
            break;
        }
        return popResult;
    }

}


namespace rpc
{
template<>
rpc::ILocalEntity* CreateLocalEntity(Peered::IGameClientReconnect* api, rpc::IEntityMap* entityMap)
{
  return new Peered::LIGameClientReconnect(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Peered::LIGameClientReconnect )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Peered
{


	typedef void (Peered::IGameServer::*TAddClient)( const char* name, uint clientId, const Login::ClientVersion* clientVersion, NI_LPTR IGameClient* _client);
	typedef void (Peered::IGameServer::*TSendCommand)( int clientIndex, const rpc::MemoryBlock* command, bool isPlayerCommand);
	typedef SHybridPongResult& (Peered::IGameServer::*TPing)( SHybridPongResult* time_step);
	typedef void (Peered::IGameServer::*TOnGameFinish)( int clientIndex, int step, const StatisticService::RPC::SessionClientResults * finishInfo);
	typedef void (Peered::IGameServer::*TSendCrcData)( int clientIndex, int step, const rpc::MemoryBlock* crcData);


    bool LIGameServer::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Peered::IGameServer::AddClient/0");rpc::VCall( stack, localObject.Get(), TAddClient(&Peered::IGameServer::AddClient), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("Peered::IGameServer::AddClientFast/1");rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::AddClientFast, popResult); } break;
			case 2: { NI_PROFILE_BLOCK("Peered::IGameServer::SendCommand/2");rpc::VCall( stack, localObject.Get(), TSendCommand(&Peered::IGameServer::SendCommand), popResult); } break;
			case 3: { NI_PROFILE_BLOCK("Peered::IGameServer::OnFinishStep/3");rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::OnFinishStep, popResult); } break;
			case 4: { NI_PROFILE_BLOCK("Peered::IGameServer::OnClientReady/4");rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::OnClientReady, popResult); } break;
			case 5: { NI_PROFILE_BLOCK("Peered::IGameServer::SetTimeScale/5");rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::SetTimeScale, popResult); } break;
			case 6: { NI_PROFILE_BLOCK("Peered::IGameServer::Ping/6");
			{
				SHybridPongResult& result = rpc::VCall( stack, localObject.Get(), TPing(&Peered::IGameServer::Ping), popResult); 
				call.Prepare(6).Push(result);
			}
			} break;
			case 7: { NI_PROFILE_BLOCK("Peered::IGameServer::OnGameFinish/7");rpc::VCall( stack, localObject.Get(), TOnGameFinish(&Peered::IGameServer::OnGameFinish), popResult); } break;
			case 8: { NI_PROFILE_BLOCK("Peered::IGameServer::RequestWorldData/8");rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::RequestWorldData, popResult); } break;
			case 9: { NI_PROFILE_BLOCK("Peered::IGameServer::OnGameLeave/9");
			{
				bool result = rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::OnGameLeave, popResult); 
				call.Prepare(9).Push(result);
			}
			} break;
			case 10: { NI_PROFILE_BLOCK("Peered::IGameServer::SendCrcData/10");rpc::VCall( stack, localObject.Get(), TSendCrcData(&Peered::IGameServer::SendCrcData), popResult); } break;
			case 11: { NI_PROFILE_BLOCK("Peered::IGameServer::OnDisconnectAck/11");rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::OnDisconnectAck, popResult); } break;
			case 12: { NI_PROFILE_BLOCK("Peered::IGameServer::DispatchPlaySameTeamDecision/12");rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::DispatchPlaySameTeamDecision, popResult); } break;
			case 13: { NI_PROFILE_BLOCK("Peered::IGameServer::DispatchBadBehaviourComplaint/13");rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::DispatchBadBehaviourComplaint, popResult); } break;
			case 14: { NI_PROFILE_BLOCK("Peered::IGameServer::OnProtectionError/14");rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::OnProtectionError, popResult); } break;
			case 15: { NI_PROFILE_BLOCK("Peered::IGameServer::SendProtectionMagic/15");rpc::VCall( stack, localObject.Get(), &Peered::IGameServer::SendProtectionMagic, popResult); } break;

        default:
            popResult = false;
            break;
        }
        return popResult;
    }

}


namespace rpc
{
template<>
rpc::ILocalEntity* CreateLocalEntity(Peered::IGameServer* api, rpc::IEntityMap* entityMap)
{
  return new Peered::LIGameServer(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Peered::LIGameServer )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Peered
{


	typedef void (Peered::IGameServerInternal::*TAddSpectator)( uint clientId, const wstring* nickname);


    bool LIGameServerInternal::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Peered::IGameServerInternal::OnRejoinClient/0");
			{
				bool result = rpc::VCall( stack, localObject.Get(), &Peered::IGameServerInternal::OnRejoinClient, popResult); 
				call.Prepare(0).Push(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("Peered::IGameServerInternal::AddSpectator/1");rpc::VCall( stack, localObject.Get(), TAddSpectator(&Peered::IGameServerInternal::AddSpectator), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("Peered::IGameServerInternal::UserLeftTheGameInCastle/2");rpc::VCall( stack, localObject.Get(), &Peered::IGameServerInternal::UserLeftTheGameInCastle, popResult); } break;

        default:
            popResult = false;
            break;
        }
        return popResult;
    }

}


namespace rpc
{
template<>
rpc::ILocalEntity* CreateLocalEntity(Peered::IGameServerInternal* api, rpc::IEntityMap* entityMap)
{
  return new Peered::LIGameServerInternal(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Peered::LIGameServerInternal )


#pragma warning( push )
#pragma warning( disable : 4065 )

namespace Peered
{


	typedef void (Peered::IGameServerReconnect::*TSendWorldDataInfo)( int clientIndex, const WorldDataInfo* worldDataInfo);
	typedef void (Peered::IGameServerReconnect::*TSendWorldDataPart)( int clientIndex, const rpc::MemoryBlock* worldDataPart);


    bool LIGameServerReconnect::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("Peered::IGameServerReconnect::SendWorldDataInfo/0");rpc::VCall( stack, localObject.Get(), TSendWorldDataInfo(&Peered::IGameServerReconnect::SendWorldDataInfo), popResult); } break;
			case 1: { NI_PROFILE_BLOCK("Peered::IGameServerReconnect::SendWorldDataPart/1");rpc::VCall( stack, localObject.Get(), TSendWorldDataPart(&Peered::IGameServerReconnect::SendWorldDataPart), popResult); } break;
			case 2: { NI_PROFILE_BLOCK("Peered::IGameServerReconnect::SetGameClientReconnect/2");rpc::VCall( stack, localObject.Get(), &Peered::IGameServerReconnect::SetGameClientReconnect, popResult); } break;

        default:
            popResult = false;
            break;
        }
        return popResult;
    }

}


namespace rpc
{
template<>
rpc::ILocalEntity* CreateLocalEntity(Peered::IGameServerReconnect* api, rpc::IEntityMap* entityMap)
{
  return new Peered::LIGameServerReconnect(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( Peered::LIGameServerReconnect )


