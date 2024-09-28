#include "stdafx.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "CameraControllersContainer.h"
#include "CameraController.h"


namespace NSoundScene
{
	void SetListener( CVec3 const &position, CVec3 const &forward, CVec3 const &up );
	void EventSystemSetListener( CVec3 const &position, CVec3 const &forward, CVec3 const &up, CVec3 const &anchor );

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  CameraControllersContainer::CameraControllersContainer( ICamera *_pCamera )
    : pCamera( _pCamera )
    , bEnableEffects(true)
  {
    pCamera->GetPosition( &curPos );
  }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void CameraControllersContainer::EraseInvalidFrom( TCameraControllers& controllers )
	{
		for ( TCameraControllers::iterator it = controllers.begin(); it != controllers.end(); )
		{
			if ( IsValid( *it ) )
				++it;
			else
				it = controllers.erase( it );
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void CameraControllersContainer::EraseInvalid()
	{
		EraseInvalidFrom( cameraControllers );
		EraseInvalidFrom( cameraEffects );
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ICameraController* CameraControllersContainer::SelectFirstActiveController() const
	{
		if ( cameraControllers.empty() )
			return 0;

		TCameraControllers::const_iterator lastController = cameraControllers.end();
		--lastController;
		for ( TCameraControllers::const_iterator it = lastController; ; --it )
		{
			if ( (*it)->IsActive() )
				return *it;
			else if ( it == cameraControllers.begin() )
				return 0;
		}
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void CameraControllersContainer::Step( const Time timeDiff )
	{
		EraseInvalid();

		SCameraPosition basePos = curPos;	
    ICameraController* pActiveController = SelectFirstActiveController();
		if ( pActiveController )
			pActiveController->Update( &basePos, curPos, curPos, timeDiff );

    SCameraPosition wantedPos = basePos;	

    if( bEnableEffects )
    {
      for ( TCameraControllers::iterator it = cameraEffects.begin(); it != cameraEffects.end(); ++it )
      {
        (*it)->Update( &wantedPos, basePos, wantedPos, timeDiff );
      }
    }

    if( wantedPos != curPos )
		{
			pCamera->SetPosition( wantedPos );
			NSoundScene::SetListener(wantedPos.GetCameraPos(), wantedPos.GetCameraDir(), wantedPos.GetCameraUp());
			
			NSoundScene::EventSystemSetListener(wantedPos.GetCameraPos(), wantedPos.GetCameraDir(), 
        wantedPos.GetCameraUp(), wantedPos.vAnchor );
		}

    curPos = basePos;
    
    //NSoundScene::Update();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	bool CameraControllersContainer::ProcessEvent( const Input::Event &event )
	{
		EraseInvalid();

		ICameraController* pActiveController = SelectFirstActiveController();
		if ( pActiveController )
			pActiveController->ProcessEvent( event );

		// Someone had killed reverse_iterator, so that code will looks so ugly
		if ( !cameraEffects.empty() )
		{
			TCameraControllers::iterator it = cameraEffects.end();
			do
			{
				--it;
				if ( (*it)->ProcessEvent( event ) )
					return true;
			}
			while ( it != cameraEffects.begin() );
		}

		return false;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void CameraControllersContainer::AddCameraController( ICameraController *pCameraController )
	{
    
		NI_VERIFY( IsValid( pCamera ), "Invalid camera in camera controllers container", return );
		if ( IsValid( pCameraController ) )
		{
			pCameraController->SetCamera( pCamera );

			if ( pCameraController->IsEffect() )
				cameraEffects.push_back( pCameraController );
			else
      {
        cameraControllers.push_back( pCameraController );
      }
		}

	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS_NM( CameraControllersContainer, NScene )
BASIC_REGISTER_CLASS( NScene::ICameraController )