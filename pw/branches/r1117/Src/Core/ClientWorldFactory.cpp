#error "Removed from project by BVS (12.12.2008) due to world-client communication simplification"

#include "StdAfx.h"
#include "ClientWorldFactory.h"
#include "..\System\StrProc.h"

namespace NClientFactory
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef hash_map<int, int> TClientToWorldHash;	 
//
//class RegistryHolder : public CObjectBase
//{
//	OBJECT_BASIC_METHODS( RegistryHolder )
//public:
//	TClientToWorldHash registry;
//};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static TClientToWorldHash &GetRegistry()
{
	static TClientToWorldHash registry;
	//if ( !pHolder )
	//	pHolder = new RegistryHolder();
	return registry;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterClientType( int clientID, int worldID )
{
	TClientToWorldHash::iterator it = GetRegistry().find( worldID );
	NI_VERIFY( it == GetRegistry().end(), NStr::StrFmt( "Client object for world object ID %x is already registered", worldID ), return );

	GetRegistry()[worldID] = clientID;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// создать объект по его typeID
CObjectBase *MakeObject( int worldID )
{
	TClientToWorldHash::iterator it = GetRegistry().find( worldID );
	//NI_VERIFY( it != GetRegistry().end(), NStr::StrFmt( "Client object for world object ID %x is unregistered", worldID ), return 0 );
	if (it == GetRegistry().end())
	{
		// @BVS@TODO HACKED!
		return 0;
	}

	int clientID = it->second;

  CObjectBase* pObject = NObjectFactory::MakeObject( clientID );

	return pObject;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
