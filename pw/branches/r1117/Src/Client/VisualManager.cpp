#include "stdafx.h"
#include "./VisualManager.h"

#include "../Scene/Scene.h"
#include "../Scene/SceneObject.h"

namespace NClient
{
	NScene::SceneObject* VisualManager::BuildSceneObject( NScene::IScene *pAtScene, const NScript::StringValues & values )
	{
		NScene::SceneObject *pSceneObject = CreateSceneObject( pAtScene, values );
		if ( !pSceneObject )
			return 0;
		AddSceneObject( pAtScene, pSceneObject, values, 0 );
		return pSceneObject;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void VisualManager::AddSceneObject( NScene::IScene *pAtScene, NScene::SceneObject *pSceneObject, const NScript::StringValues & values, int subId )
	{
		if ( !pSceneObject )
			return;
		Item object;
		object.pScene = pAtScene;
		object.pSceneObject = pSceneObject;
		object.values = values;
		object.subId = subId;
		objects.push_back( object );
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	NScene::SceneObject* VisualManager::FindSceneObject( const NScene::IScene *pAtScene, int subId ) const
	{
		for ( vector<Item>::const_iterator it = objects.begin(); it != objects.end(); ++it )
		{
			if ( it->pScene == pAtScene && subId == it->subId/* && IsValid(it->pSceneObject)*/ )
				return it->pSceneObject;
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void VisualManager::RemoveSceneObject( NScene::SceneObject *pSceneObject )
	{
		for ( vector<Item>::iterator it = objects.begin(); it != objects.end(); )
		{
			if ( it->pSceneObject == pSceneObject )
			{
				if ( IsValid(it->pScene) )
					it->pScene->RemoveObject( pSceneObject );
				it = objects.erase( it );
			}
			else
				++it;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void VisualManager::RemoveSceneObject( int subId )
	{
		for ( vector<Item>::iterator it = objects.begin(); it != objects.end(); )
		{
			if ( it->subId == subId )
			{
				if ( IsValid(it->pScene) )
					it->pScene->RemoveObject( it->pSceneObject );
				it = objects.erase( it );
			}
			else
				++it;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void VisualManager::RemoveAllSceneObjects()
	{
		for ( vector<Item>::iterator it = objects.begin(); it != objects.end(); ++it )
		{
			if ( IsValid(it->pScene) )
				it->pScene->RemoveObject( it->pSceneObject );

			delete it->pSceneObject;
		}
		objects.clear();
	}
}

BASIC_REGISTER_CLASS( NClient::VisualManager );
