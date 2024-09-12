#pragma once

#include "System/Spline.h"

using namespace System::Collections::Generic;

namespace EditorNative
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class CubicSpline3D sealed
	{
	private:
		CCubicSpline3D* spline;

  public: 
    CubicSpline3D() { spline = new CCubicSpline3D; }

    property float Length
		{
			float get();
		}

		property int Segments
		{
			int get();
		}

    Vector3^ GetValue( float t );
    bool Setup( IList<Vector3^>^ path, Vector3^ startDir, Vector3^ endDir, float tension );
    bool Setup( IList<Vector3^>^ path, Vector3^ startDir, Vector3^ endDir );
	};
}	// namespace EditorNative
