#include "stdafx.h"

#include "EaselPaintLayerSceneComponent.h"

DEFINE_DEV_VAR(s_drawPaintMesh, true, "draw_paint_mesh", STORAGE_NONE);

namespace Render
{
  DECLARE_INSTANCE_COUNTER(PaintMesh);

  PaintMesh::PaintMesh()
  {
    Reset();
  }

  void PaintMesh::Reset()
  {
    memset(&fragmentCompleteFlags, 0, sizeof(fragmentCompleteFlags));
    memset(&paintFragmentOpacities, 0, sizeof(paintFragmentOpacities));
  }

  void PaintMesh::PrepareRendererAfterMaterial( unsigned int elementNumber ) const
  {
    StaticMesh::PrepareRendererAfterMaterial(elementNumber);

    Render::GetRenderer()->SetPixelShaderConstants(PSHADER_LOCALCONST1, materials[elementNumber]->GetPackedMasksNumberPin() + 1, &paintFragmentOpacities);
  }

  void PaintMesh::SetFragmentOpacity(int fragmentNum, int point, float opacity, bool complete)
  {
    NI_VERIFY(point >= 0 && point < MAX_PAINT_POINTS_PER_FRAGMENT, "PaintMesh: point is is out of range", return);

    int index = fragmentNum * 4 + point;
    NI_VERIFY( index >=0 && index <NUM_CONSTANTS, "PaintMesh: fragment index is out of range", return);

    if(complete)
    {
      if(opacity > 0)
      {
        fragmentCompleteFlags[index] = complete;
        paintFragmentOpacities[index] = opacity + 1.0f;
      }
    }
    else if(!fragmentCompleteFlags[index])
    {
      paintFragmentOpacities[index] = opacity;
    }
    
  }
}

namespace NScene
{


EaselPaintSceneComponent::EaselPaintSceneComponent( const NDb::StaticMesh* pDBMesh, const Placement& pos )
{
  NI_VERIFY(pDBMesh, "EaselPaintSceneComponent: invalid mesh", return);

  renderComponent = AutoPtr<Render::PaintMesh>(new Render::PaintMesh());
  renderComponent->Initialize( IDENTITY_MATRIX, pDBMesh );

  localAABB.Set(pDBMesh->aabb);
}

EaselPaintSceneComponent::EaselPaintSceneComponent( const nstl::string& geometry, const NDb::Ptr<NDb::PaintMaterial>& material, const Placement& pos )
{
  geometryName = geometry;
  renderComponent = AutoPtr<Render::PaintMesh>(new Render::PaintMesh() );

  // get layer geometry
  const Render::MeshGeometry* loadedGeometry = Render::RenderResourceManager::LoadStaticMeshGeometry(geometry, false);
  NI_VERIFY(loadedGeometry, "", return;);

  // get material
  nstl::vector<Render::BaseMaterial*> materials;
  Render::BaseMaterial* renMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( material ) );
  NI_VERIFY(renMaterial, "", return);

  materials.push_back(renMaterial);

  renderComponent->Initialize( IDENTITY_MATRIX, loadedGeometry, materials );
  offset.SetPlacement( offset.GetPlacement() + pos);

  localAABB.center   = CVec3( 0.0f, 0.0f, 0.0f );
  localAABB.halfSize = CVec3( 1.0f, 1.0f, 1.0f );;
}

void EaselPaintSceneComponent::SetFragmentOpacity(int fragmentId, int point, float opacity, bool complete)
{
  if(Get(renderComponent))
  {
    renderComponent->SetFragmentOpacity(fragmentId, point, opacity, complete);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintSceneComponent::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  // Make result matrix
  Matrix43 resultmatrix;
  worldPlacement.GetMatrix( &resultmatrix );

  // Transform local AABB to global one
  worldAABB.Transform( resultmatrix, localAABB );
  NI_ASSERT(worldAABB.IsValid(), "AABB should be valid");

  // Update object's AABB
  pars.objectAABB.Grow(worldAABB);
  NI_ASSERT(pars.objectAABB.IsValid(), "AABB should be valid");

  if ( renderComponent )
  {
    renderComponent->SetWorldMatrix( resultmatrix );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintSceneComponent::RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants )
{
  if(s_drawPaintMesh && renderComponent) {
    SceneComponent::RenderToQueue(queue, sceneConstants);
    renderComponent->RenderToQueue( queue );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselPaintLayerSceneComponent::EaselPaintLayerSceneComponent( const nstl::string& geometry, const NDb::Ptr<NDb::Material>& material
                                                             , float layerHeight, const Placement& pos )
: lastFadeOpacity(1.0f)
, lastFadeEnds(0.0f)
, currentOpacity(1.0f)
, paintComponent(0)
, fragmentId(-1)
{
  renderComponent = AutoPtr<Render::StaticMesh>(new Render::StaticMesh() );

  // get layer geometry
  const Render::MeshGeometry* loadedGeometry = Render::RenderResourceManager::LoadStaticMeshGeometry(geometry, false);
  NI_VERIFY(loadedGeometry, "", return;);

  // get material
  nstl::vector<Render::BaseMaterial*> materials;
  Render::BaseMaterial* renMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( material ) );
  NI_VERIFY(renMaterial, "", return);

  materials.push_back(renMaterial);

  renderComponent->Initialize( IDENTITY_MATRIX, loadedGeometry, materials );
  offset.SetPlacement( offset.GetPlacement() + pos);

  localAABB.center   = CVec3( 0.0f, 0.0f, 0.0f );
  localAABB.halfSize = CVec3( 1.0f, 1.0f, 1.0f );;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EaselPaintLayerSceneComponent::EaselPaintLayerSceneComponent(EaselPaintSceneComponent& _paintComponent, int _fragmentId, int _point, bool _complete)
: lastFadeOpacity(1.0f)
, lastFadeEnds(0.0f)
, currentOpacity(1.0f)
, paintComponent(&_paintComponent)
, fragmentId(_fragmentId)
, point(_point)
, complete(_complete)
{
  NI_ASSERT(paintComponent, "EaselPaintLayerSceneComponent: invalid paint component");

  localAABB.center   = CVec3( 0.0f, 0.0f, 0.0f );
  localAABB.halfSize = CVec3( 1.0f, 1.0f, 1.0f );;

  offset.SetPlacement(NULLPLACEMENT);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintLayerSceneComponent::AddFade(float fadeToOpacity, float fadeDuration)
{
  NI_VERIFY( (fadeDuration >= 0) , "EaselPaintLayerSceneComponent: time duration can't be negative", (fadeDuration = 0.0f) );
  NI_VERIFY( ((fadeToOpacity >= 0) && (fadeToOpacity <= 1.0f))
    , "EaselPaintLayerSceneComponent: fade opacity should be in [0, 1] interval"
    , fadeToOpacity = Clamp(fadeToOpacity, 0.0f, 1.0f) );

  Fade newFade;
  newFade.fadeToOpacity = fadeToOpacity;
  newFade.fadeDuration = fadeDuration;

  if(fadesChain.empty())
  {
    timeController.Reinit(*this);
    lastFadeEnds = 0.0f;
  }

  fadesChain.push_back( newFade );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintLayerSceneComponent::AddFadeWaitInterval(float waitDuration)
{
  NI_VERIFY( (waitDuration >= 0) , "EaselPaintLayerSceneComponent: time duration can't be negative", return );

  Fade newFade;

  newFade.fadeDuration = waitDuration;

  if(fadesChain.empty())
  {
    timeController.Reinit(*this);
    lastFadeEnds = 0.0f;
    newFade.fadeToOpacity = lastFadeOpacity;
  }
  else
  {
    newFade.fadeToOpacity = fadesChain.back().fadeToOpacity;
  }

  fadesChain.push_back( newFade );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintLayerSceneComponent::ForceOpacity(float opacity)
{
  fadesChain.clear();
  lastFadeEnds = 0.0f;
  lastFadeOpacity = opacity;
  SetOpacity(opacity);
}

// return [0,1] factor. if fromTime == toTime - will return 1.0
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static float CalculateFadeFactor(float fromTime, float toTime, float currentTime )
{
  float timeInterval = toTime - fromTime;
  if( timeInterval <= FP_EPSILON )
  {
    return 1.0f;
  }

  float deltaTimeFromStart = currentTime - fromTime; 
  if(deltaTimeFromStart <= FP_EPSILON)
  {
    return 0.0f;
  }

  float factor = deltaTimeFromStart / timeInterval;

  return min(factor, 1.0f);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintLayerSceneComponent::ApplyFades()
{
  if(fadesChain.empty())
  {
    return;
  }

  const Fade& currentFade = fadesChain.front();

  float currentTime = timeController.GetTime();

  // apply fade
  float currentFadeEnds = lastFadeEnds + currentFade.fadeDuration;
  float fadeFactor = CalculateFadeFactor( lastFadeEnds, currentFadeEnds, currentTime );

  // interpolate opacity
  float opacity = lastFadeOpacity + (currentFade.fadeToOpacity - lastFadeOpacity)*fadeFactor;
  SetOpacity( opacity );

  // check if fade is out of date
  if( currentFadeEnds < currentTime)
  {
    lastFadeOpacity = currentFade.fadeToOpacity;
    lastFadeEnds += currentFade.fadeDuration;
    fadesChain.pop_front();

    // try apply next fades recursively
    ApplyFades();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintLayerSceneComponent::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  // Make result matrix
  Matrix43 resultmatrix;
  worldPlacement.GetMatrix( &resultmatrix );

  // Transform local AABB to global one
  worldAABB.Transform( resultmatrix, localAABB );
  NI_ASSERT(worldAABB.IsValid(), "AABB should be valid");

  // Update object's AABB
  pars.objectAABB.Grow(worldAABB);
  NI_ASSERT(pars.objectAABB.IsValid(), "AABB should be valid");

  ApplyFades();

  if ( renderComponent )
  {
    renderComponent->SetWorldMatrix( resultmatrix );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintLayerSceneComponent::RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants )
{
  if ( !renderComponent )
  {
    return;
  }

  if(currentOpacity > FP_EPSILON)
  {
	  SceneComponent::RenderToQueue(queue, sceneConstants);
    renderComponent->RenderToQueue( queue );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct OpacityChanger : public Render::IMaterialProcessor, public NonCopyable
{
  float opacity;

  OpacityChanger(float o) : opacity(o) {}
  virtual void operator()(Render::BaseMaterial &material)
  {
    material.ModifyOpacity(opacity);
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EaselPaintLayerSceneComponent::SetOpacity( float opacity )
{
  currentOpacity = opacity;

  if( paintComponent )
  {
    paintComponent->SetFragmentOpacity(fragmentId, point, opacity, complete);
  }

  if ( renderComponent )
  {
    OpacityChanger proc(opacity);

    renderComponent->ForAllMaterials( proc );
  }
}

} // PF_Minigames