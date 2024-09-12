#pragma once

#error "Removed from project by BVS (12.12.2008) due to world-client communication simplification"

#include "../System/nvector.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NCore
{
	_interface IClientObjectBase;
}
namespace NClientFactory
{
	CObjectBase *MakeObject( int worldID );
	void RegisterClientType( int clientID, int worldID );

	template <class TYPE> 
	inline TYPE* MakeClientObject( int worldID ) 
	{ 
		return checked_cast<TYPE*>( MakeObject(worldID) ); 
	}

	template<typename TObject, typename TClient, typename TWorldObject>
	void Register( bool (*pfnProcessFunc)( TClient *pObject, TWorldObject *pWorldObject ) )
	{
		RegisterClientType( TObject::typeId, TWorldObject::typeId );
	}

  //typedef nstl::vector<CObj<CObjectBase> > TClientObjects;
  //void RegisterClientObjectsContainer(NCore::IClientObjectsContainer* pContainer);
};

#define REGISTER_CLIENT_CLASS( name )																																										\
	REGISTER_SAVELOAD_CLASS( name )																																												\
  static struct SRegister_##name##ClientRegister																																										\
	{																																																											\
		SRegister_##name##ClientRegister() { NClientFactory::Register<name>( name::Initialize ); }																			\
	} clientRegisterInit##name;

#define REGISTER_CLIENT_CLASS_NM( name, nmspace )																																				\
	REGISTER_SAVELOAD_CLASS_NM( name, nmspace )																																						\
	static struct SRegister_##name##ClientRegister																																										\
	{																																																											\
		SRegister_##name##ClientRegister() { NClientFactory::Register<nmspace::name>( nmspace::name::Initialize );}											\
	} clientRegisterInit##name;


//#define REGISTER_CLIENT_CLASS( worldName, clientName ) { NClientFactory::RegisterTypeName( &NClientFactory::MakeObjectFunc<clientName>, (worldName*)0 ); }
////#define REGISTER_TEMPL_CLASS( worldName, clientName ) { NClientFactory::RegisterTypeName( name##::New##className, (name*)0 ); }
//#define REGISTER_CLIENT_CLASS_NM( worldName, clientName, nmspace ) { NClientFactory::RegisterTypeName( &NClientFactory::MakeObjectFunc<nmspace::clientName>, (nmspace::worldName*)0 ); }
//
//#define REGISTER_WORLD_CLASS_PAIR( N, worldName, clientName )	\
//	BASIC_REGISTER_CLASS( worldName ) \
//	BASIC_REGISTER_CLASS( clientName ) \
//	static struct worldName##Register##N { \
//	worldName##Register##N() {						 \
//	REGISTER_CLASS( N, worldName )	\
//	REGISTER_CLIENT_CLASS( worldName, clientName ) \
//} } init##worldName##N;
//
//#define REGISTER_WORLD_CLASS_PAIR_NM( N, worldName, clientName, nmspace )	\
//	BASIC_REGISTER_CLASS( nmspace::worldName ) \
//	BASIC_REGISTER_CLASS( nmspace::clientName ) \
//	static struct worldName##Register##N { \
//	worldName##Register##N() { \
//	REGISTER_CLASS_NM( N, worldName, nmspace )	\
//	REGISTER_CLIENT_CLASS_NM( worldName, clientName, nmspace ) \
//} } init##worldName##N;
//
