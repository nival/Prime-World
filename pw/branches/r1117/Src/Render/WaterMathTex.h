#pragma once

#include "../System/noncopyable.h"

namespace Render
{
namespace Water
{

class ScrollTexture : public NonCopyable
{
public :
  ScrollTexture( int nNumMipmaps, Render::ERenderFormat format );

public :
  void Update( float time );

public :
	const Texture2DRef& getTexture() const { return hDxDyTexture; }

private :
  void InitLayersParams();

private :
  CVec4              rotationMatrices[ 2 ];
  CVec3              layersA, layersVelocities;
  CVec2              texDuDv;
  float              heightCoeff, curTime;

private :
  Texture2DRef       baseHeightmapTexture, hTexture, hDxDyTexture;
};

} // namespace Water
} // namespace Render
