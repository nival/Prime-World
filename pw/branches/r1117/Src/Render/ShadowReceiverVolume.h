#pragma once

namespace Render
{

_interface IShadowReceiverVolume : public IObjectBase
{
  virtual void GetBoundsInCamera( const Render::AABB& _cameraAABB, Render::AABB& _receiversAABB ) = 0;
};

};//namespace Render