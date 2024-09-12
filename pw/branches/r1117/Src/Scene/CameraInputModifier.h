#pragma once

#include "NivalInput/InputCommandRef.h"

namespace NScene
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	struct CameraInputModifier
	{
		Input::CommandReference fwd, strafe, zoom, pitch, yaw, roll, upward;
		Input::CommandReference mouse_fwd, mouse_strafe, mouse_zoom, mouse_pitch, mouse_yaw, mouse_locked, mouse_unlocked;
		bool touched;

		CameraInputModifier();
    bool ProcessEvent( const Input::Event & event );

    inline float GetDeltaFoward() { return mouse_fwd.RetrieveDelta() + fwd.RetrieveDelta(); }
		inline float GetDeltaStrafe() { return mouse_strafe.RetrieveDelta() + strafe.RetrieveDelta(); }
		inline float GetDeltaUpward() { return upward.RetrieveDelta(); }
		inline float GetDeltaZoom() { return zoom.RetrieveDelta(); }
    inline float GetDeltaMouseZoom() { return mouse_zoom.RetrieveDelta();}
		inline float GetDeltaPitch() { return mouse_pitch.RetrieveDelta() + pitch.RetrieveDelta(); }
		inline float GetDeltaYaw() { return /* mouse_yaw.RetrieveDelta() + */ yaw.RetrieveDelta(); } //We DO NOT use mouse yawing in session
		inline float GetDeltaRoll() { return roll.RetrieveDelta(); }

    inline void ClearDeltaFoward() { mouse_fwd.ClearDelta(); fwd.ClearDelta(); }
    inline void ClearDeltaStrafe() { mouse_strafe.ClearDelta(); strafe.ClearDelta(); }

  };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}