#pragma once

#include "MinigameClientObject.h"

namespace NDb
{
  struct DBSceneObject;
}

namespace PF_Minigames
{

class Easel;
class Minigames;

class EaselLuxViewTunnelPoint : public MinigameClientObject
{
  OBJECT_METHODS(0xF465EA42,EaselLuxViewTunnelPoint);

public:
  EaselLuxViewTunnelPoint() {};

  bool Init( Easel& _easel, const SVector& _point );

  virtual void OnLevelStarted();
  virtual void OnLevelFinished();
};

} // namespace PF_Minigames
