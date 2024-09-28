#pragma once

#include "../Scene/SceneComponent.h"
#include "../Render/StaticMesh.h"

namespace Render
{
  class EaselPaintLayerRenderComponent;
}


namespace Render
{
  class PaintMesh : public StaticMesh
  {
    REPLACE_DEFAULT_NEW_DELETE(PaintMesh);

  public:

    enum 
    {
      MAX_PAINT_FRAGMENTS = 24,
      MAX_PAINT_POINTS_PER_FRAGMENT = 3,
      NUM_CONSTANTS = MAX_PAINT_FRAGMENTS * 4,
    };

    PaintMesh();
    void Reset();

    virtual void PrepareRendererAfterMaterial( unsigned int elementNumber ) const;

    void SetFragmentOpacity(int fragmentNum, int point, float opacity, bool complete);

  private:

    bool fragmentCompleteFlags[NUM_CONSTANTS];
    float paintFragmentOpacities[NUM_CONSTANTS];
  };
}

namespace NScene
{
  class EaselPaintSceneComponent : public SceneComponent
  {
    AutoPtr<Render::PaintMesh> renderComponent;
    nstl::string geometryName;

  public:

    EaselPaintSceneComponent( const nstl::string& geometry, const NDb::Ptr<NDb::PaintMaterial>& material, const Placement& pos );
    EaselPaintSceneComponent( const NDb::StaticMesh* pObject, const Placement& pos );

    const nstl::string& GetGeometryName() const { return geometryName; }

    void SetFragmentOpacity(int fragmentId, int point, float opacity, bool complete);

    virtual void UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff );
    virtual void RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants );
  };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class EaselPaintLayerSceneComponent : public SceneComponent
{
  OBJECT_BASIC_METHODS( EaselPaintLayerSceneComponent );

  AutoPtr<Render::StaticMesh> renderComponent;
public:
  EaselPaintLayerSceneComponent() : lastFadeOpacity(), lastFadeEnds(), currentOpacity(), paintComponent(), fragmentId() {}
  EaselPaintLayerSceneComponent( const nstl::string& geometry, const NDb::Ptr<NDb::Material>& material, float layerHeight, const Placement& pos );
  EaselPaintLayerSceneComponent( EaselPaintSceneComponent& _paintComponent, int _fragmentId, int _point, bool _complete);
  virtual ~EaselPaintLayerSceneComponent() {}

  // add fade to chain of fades. opacity should be in [0, 1] interval. fade duration should be positive
  void AddFade(float fadeToOpacity, float fadeDuration);

  // add wait interval to chain of fades
  void AddFadeWaitInterval(float waitDuration);

  // drop fade chain
  void ForceOpacity(float opacity);

  virtual void UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff );
  virtual void RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants );

private:
  struct Fade
  {
    float fadeToOpacity;
    float fadeDuration;
  };

  nstl::list<Fade> fadesChain;

  virtual void SetOpacity( float k );

  void ApplyFades();

  EaselPaintSceneComponent* paintComponent;
  int fragmentId;
  int point;
  bool complete;

  float lastFadeOpacity;
  float lastFadeEnds;
  float currentOpacity;
};

} // NScene
