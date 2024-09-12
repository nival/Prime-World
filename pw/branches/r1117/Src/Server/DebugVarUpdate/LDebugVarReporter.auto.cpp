#include "stdafx.h"
#include "LDebugVarReporter.auto.h"

#pragma warning( push )
#pragma warning( disable : 4065 )

namespace NDebug
{


	typedef const wchar_t* (NDebug::DebugVarReporter::*TGetDebugVar)( const wstring* sVarName);
	typedef const wchar_t* (NDebug::DebugVarReporter::*TRunRemoteCommand)( const wstring* cmd);


    bool LDebugVarReporter::vcall( byte method_id, rpc::MethodCall& call, rpc::MethodCallStack& stack )
    {
        bool popResult = true;
        switch ( method_id )
        {
			case 0: { NI_PROFILE_BLOCK("NDebug::DebugVarReporter::GetDebugVar/0");
			{
				const wchar_t* result = rpc::VCall( stack, localObject.Get(), TGetDebugVar(&NDebug::DebugVarReporter::GetDebugVar), popResult); 
				call.Prepare(0).Push(result);
			}
			} break;
			case 1: { NI_PROFILE_BLOCK("NDebug::DebugVarReporter::RunRemoteCommand/1");
			{
				const wchar_t* result = rpc::VCall( stack, localObject.Get(), TRunRemoteCommand(&NDebug::DebugVarReporter::RunRemoteCommand), popResult); 
				call.Prepare(1).Push(result);
			}
			} break;

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
rpc::ILocalEntity* CreateLocalEntity(NDebug::DebugVarReporter* api, rpc::IEntityMap* entityMap)
{
  return new NDebug::LDebugVarReporter(api, entityMap);
}

} // rpc

#pragma warning( pop )

NI_DEFINE_REFCOUNT( NDebug::LDebugVarReporter )


