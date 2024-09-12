#pragma once

#include "AnimatedPlacement.h"

namespace NDb
{
  struct SceneObjectTrack;
}

namespace NScene
{

class SceneObjectTrack
{
public:
  SceneObjectTrack() : dbResource( 0 ), curTime( 0.0f ), length( 0.0f ), opacity( 1.0f ), lastStep( false ),
    isDirected( false ), direction( 0.0f, 0.0f, 0.0f ) {}

  void Reinit( const NDb::SceneObjectTrack* track );
  void Update( float timeDiff );
  const Placement& GetCurrentPlacement() const;
  bool IsValid() const { return !dbResource.IsEmpty(); }
  float GetCurrentOpacity() const;
  float GetLength() const;
	void Reset();

  bool GetDirected() const { return isDirected; }
  void SetDirected( bool _isDirected ) { isDirected = _isDirected; }
  const CVec3& GetDirection() const { return direction; }
  void SetDirection( const CVec3& dir );

private:
  NDb::Ptr<NDb::SceneObjectTrack> dbResource;
  Placement basePlacement;
  AnimatedPlacement animatedPlacement;
  Placement placement;
  NDb::AnimatedWrapper<NDb::Animated<float, NDb::AnimatedAlgorithms::Linear> > opacityTrack;
  float opacity;
  
  float curTime;
  float length;

  bool lastStep;

  bool isDirected;
  CVec3 direction;
};

}