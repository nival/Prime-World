#include "stdafx.h"
#include "Updater.h"
#include "UpdateProcessor.h"
#include "SystemLog.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Updater
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CUpdater::~CUpdater()
{
  //@Eliseev@TODO: crash on exit :-(
  //for( Functors::iterator itFunc = functors.begin(); itFunc != functors.end(); ++itFunc )
  //{
  //  for( FunctorsVector::iterator it = itFunc->second.begin(); it != itFunc->second.end(); ++it )
  //    delete *it;
  //}

  //functors.clear();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CUpdater::Register( CUpdateProcessor *pProcessor )
{
	const bool registered = find( processors.begin(), processors.end(), pProcessor ) != processors.end();
	if( !registered )
		processors.push_back( pProcessor );
}

void CUpdater::Register( int typeId, IUpdateProcessorFunc *pFunctor)
{
  if(pFunctor != 0)
    functors[typeId].push_back(CPtr<IUpdateProcessorFunc>(pFunctor));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CUpdater::ProcessUpdate( CObjectBase *pUpdate )
{
	// processors
	for ( TProcessors::iterator it = processors.begin(); it != processors.end(); )
	{
		if ( IsValid( *it ) )
		{
			(*it)->Process( pUpdate );
			//systemLog( NLogg::LEVEL_DEBUG ) << "*** Process update: " << pUpdate->GetObjectTypeName() << " by processor: " << (*it)->GetObjectTypeName() << endl;
			++it;
		}
		else
			it = processors.erase( it );
	}

	// functors
	const int typeId = pUpdate->GetTypeId();
	Functors::iterator it = functors.find( typeId );
	if ( it != functors.end() )
	{
		FunctorsVector::iterator iter = it->second.begin();
		FunctorsVector::iterator iterEnd = it->second.end();
		for(; iter != iterEnd; ++iter )
      //(**iter)( pUpdate );
      (*iter)->Process(pUpdate);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CUpdater::UnregisterCorpse()
{
	processors.remove_if( Validator<CUpdateProcessor>() );
  
  Functors::iterator iter = functors.begin();
  for(; iter != functors.end(); ++iter)
  {
    iter->second.remove_if(Validator<IUpdateProcessorFunc>());
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CUpdater::Push( CObjectBase *pUpdate, const bool bDelayed )
{
	NI_VERIFY( pUpdate, "Invalid update", return );
	
	CObj<CObjectBase> pGarbage = pUpdate; // чтобы не мучаться удалением pUpdate, наверняка нас позовут как Push( new .... )
	if ( bDelayed )
		updates.push_back( pUpdate );
	else
		ProcessUpdate( pUpdate );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CUpdater::Step()
{
	UnregisterCorpse();

	for ( TUpdates::iterator it = updates.begin(); it != updates.end(); ++it )
		ProcessUpdate( *it );

	updates.clear();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//REGISTER_SAVELOAD_CLASS_NM( Functor, Updater );   // Pavel@GnoM@Cherniavski: it's a template, cannot register (no deserialization)
REGISTER_SAVELOAD_CLASS_NM( CUpdater, Updater );


