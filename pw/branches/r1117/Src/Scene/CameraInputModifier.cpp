#include "stdafx.h"
#include "CameraInputModifier.h"

namespace NScene
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CameraInputModifier::CameraInputModifier()
		: touched( false )
    , fwd( "camera_forward" )
		, strafe( "camera_strafe" )
		, zoom( "camera_zoom" )
		, pitch( "camera_pitch" )
		, yaw( "camera_rotate" )
		, roll( "camera_roll" )
		, upward( "camera_upward" )
		, mouse_fwd( "camera_forward_mouse" )
		, mouse_strafe( "camera_strafe_mouse" )
		, mouse_zoom( "camera_zoom_mouse" )
		, mouse_pitch( "camera_pitch_mouse" )
		, mouse_yaw( "camera_rotate_mouse" )
		, mouse_locked( "win_right_button_down" )
		, mouse_unlocked( "win_right_button_up" )
	{
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CameraInputModifier::ProcessEvent( const Input::Event & event )
	{
		bool noKeyboard = false;
		bool noMouse = false;

		touched = false;

		if ( !noKeyboard )
		{
			touched |= fwd.ProcessEvent( event );
	    touched |= strafe.ProcessEvent( event );
			touched |= zoom.ProcessEvent( event );
			touched |= pitch.ProcessEvent( event );
			touched |= yaw.ProcessEvent( event );
			touched |= roll.ProcessEvent( event );
			touched |= upward.ProcessEvent( event );
		}

		if ( !noMouse )
		{
			touched |= mouse_fwd.ProcessEvent( event );
			touched |= mouse_strafe.ProcessEvent( event );
			touched |= mouse_zoom.ProcessEvent( event );
			touched |= mouse_pitch.ProcessEvent( event );
			touched |= mouse_yaw.ProcessEvent( event );

			mouse_locked.ProcessEvent( event );
			mouse_unlocked.ProcessEvent( event );
		}

		return touched;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}