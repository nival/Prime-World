#include "stdafx.h"
#include "NetDriver.h"
#include "LinksManager.h"

#include "..\System\Commands.h"

const int N_DEFAULT_GAME_PORT = 8888;

int g_nNetGamePort = N_DEFAULT_GAME_PORT;

namespace NNet
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLinksManagerContainer: public ILinksManagerContainer
{
	OBJECT_METHODS( 0x1E4A8B04, CLinksManagerContainer )
	hash_map<int, CObj<ILinksManager> > linksManagers;
private:
	void CreateLinksManager( int nPort );
public:
	CLinksManagerContainer() {}
	virtual ILinksManager *GetGameLinksManager();
	virtual ILinksManager *GetLinksManagerOnPort( int nPort );
	virtual ILinksManager *GetUnboundLinksManager();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLinksManagerContainer::CreateLinksManager( int nPort )
{
	if ( IsValid( linksManagers[nPort] ) )
		return;
	linksManagers[nPort] = CreateServerLinksManager( nPort );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ILinksManager *CLinksManagerContainer::GetGameLinksManager()
{
	CreateLinksManager( g_nNetGamePort );
	return linksManagers[g_nNetGamePort];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ILinksManager *CLinksManagerContainer::GetLinksManagerOnPort( int nPort )
{
	CreateLinksManager( nPort );
	return linksManagers[nPort];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ILinksManager *CLinksManagerContainer::GetUnboundLinksManager()
{
	CreateLinksManager( 0 );
	return linksManagers[0];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ILinksManagerContainer *CreateLinksManagerContainer()
{
	return new CLinksManagerContainer();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NNet
REGISTER_VAR( "net_game_port", g_nNetGamePort, STORAGE_GLOBAL );
//START_REGISTER( LinksManagerContainer )
//REGISTER_VAR_EX( "net_game_port", NGlobal::VarIntHandler, &g_nNetGamePort, N_DEFAULT_GAME_PORT, STORAGE_GLOBAL );
//FINISH_REGISTER
