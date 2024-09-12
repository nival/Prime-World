#pragma once

#include "System/PlacementSpline.h"

using namespace System::Collections::Generic;

namespace EditorNative
{
  public ref class PlacementSpline sealed
  {
  private:
    CPlacementSpline* spline;
  public: 
    PlacementSpline() { spline = new CPlacementSpline(); }

    void Setup( IList<Vector3^>^ _points, IList<Vector3^>^ _angles, float tension, int quantNumber );

    void GetValue( float t, Vector3^ _pos, Quaternion^ _quat );

  };
}