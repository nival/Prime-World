#pragma once

#include "StaticMesh.h"
#include "WaterConvexes.h"

namespace Render
{
  class WaterMesh : public StaticMesh
  {
    REPLACE_DEFAULT_NEW_DELETE(WaterMesh);

  public:
    void Initialize( const Matrix43& _worldMatrix, const NDb::DBWaterSceneComponent* pDBMeshResource, const NDb::DBWaterInfo* pParams );

    float GetLevel() const { return level + worldMatrix._34; }
    template <class F> void ForAllConvexes( F &f ) { convexes.ForAll(f, worldMatrix, level); }
    void RenderToQueuePostponed( BatchQueue& queue );
    bool HasCaustics() const { return pCaustics && pCaustics != Render::GetWhiteTexture2D(); }

    // From Render::RenderComponent
    virtual void RenderToQueue( BatchQueue& queue );
    virtual void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;

  private:
    float level;
    WaterConvexes convexes;
    TextureRef pGradients;
    TextureRef pCaustics;

    float tiling;
    float shininess;
    float ripplesFactor;
    float ripplesHeight;
    float refraction;
    float causticsTiling;
    float causticsIntensity;
    float scaleH0;
    float scaleZ0;
    float scaleH0refl;
    CVec2 speed;
  };
} //namespace Render