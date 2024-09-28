#pragma once

#include "../Scripts/NameMap.h"
namespace NScene { _interface IScene; class SceneObject; }

namespace NClient
{
	class VisualManager
		: public CObjectBase
	{
		OBJECT_BASIC_METHODS( VisualManager )

	private:
		// TODO: need data refactor
		struct Item
		{
			CPtr<NScene::IScene> pScene;
			NScene::SceneObject* pSceneObject;
			NScript::StringValues values;
			int subId;
			Item(): subId( 0 ) {}
		};

		typedef vector<Item> ObjectsContainer;
		ObjectsContainer objects;

	protected:
		CPtr<NScene::IScene> pMainScene;
		NScene::SceneObject* pMainSceneObject;

	public:
		virtual NScene::SceneObject* CreateSceneObject( NScene::IScene *pAtScene, const NScript::StringValues & values ) { return 0; }

		NScene::IScene* GetMainScene() const { return pMainScene; }
		NScene::SceneObject* GetMainSceneObject() const { return pMainSceneObject; }

		NScene::SceneObject* BuildSceneObject( NScene::IScene *pAtScene, const NScript::StringValues & values );
		void AddSceneObject( NScene::IScene *pAtScene, NScene::SceneObject *pSceneObject, const NScript::StringValues & values, int subId );
		NScene::SceneObject* FindSceneObject( const NScene::IScene *pAtScene, int subId = 0 ) const;
		void RemoveSceneObject( NScene::SceneObject *pSceneObject );
		void RemoveSceneObject( int subId );
		void RemoveAllSceneObjects();

		template<typename T, typename U>
		void DoForAllScenesObjects( T *obj, void (T::*func)( const Item & data, const U & param ), const U & param )
		{
			if ( !obj || !func )
				return;
			for ( vector<Item>::iterator it = objects.begin(); it != objects.end(); )
			{
				if ( !IsValid(it->pScene)/* || !IsValid(it->pSceneObject)*/ ) // $BVS$ Should be reviewed while refactoring this code
					it = objects.erase( it );
				else
				{
					(obj->*func)( *it, param );
					++it;
				}
			}
		}

		template<typename T, typename U, typename C>
		void DoForAllScenesObjects( T *obj, void (T::*func)( const Item & data, const U & param, const C & param2 ), const U & param, const C & param2 )
		{
			if ( !obj || !func )
				return;
			for ( vector<Item>::iterator it = objects.begin(); it != objects.end(); )
			{
				if ( !IsValid(it->pScene)/* || !IsValid(it->pSceneObject)*/ ) // $BVS$ Should be reviewed while refactoring this code
					it = objects.erase( it );
				else
				{
					(obj->*func)( *it, param, param2 );
					++it;
				}
			}
		}
	};
}