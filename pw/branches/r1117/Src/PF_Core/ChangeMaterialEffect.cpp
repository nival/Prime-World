#include "stdafx.h"

#include "ChangeMaterialEffect.h"
#include "../Scene/SceneObjectUtils.h"

namespace PF_Core
{

void ChangeMaterialEffect::Init()
{
  const NDb::ChangeMaterialEffect& DB = GetDBEffect();

  dbFadeInTime = DB.fadeInTime;
  dbFadeOutTime = DB.fadeOutTime;

  curFadeInTime = 0.f;
  curFadeOutTime = 0.f;

  BasicEffect::Init();
}

void ChangeMaterialEffect::Apply( CPtr<PF_Core::ClientObjectBase> const& _pUnit )
{
  struct SetAltMaterialProc : public Render::IMaterialProcessor, public NonCopyable
  {
    NDb::Ptr<NDb::ChangeMaterialEffect> desc;

    Materials& baseMaterials;
    Materials& altMaterials;

    SetAltMaterialProc( NDb::ChangeMaterialEffect const* _desc, Materials& _baseMaterials, Materials& _altMaterials ) : desc(_desc), baseMaterials(_baseMaterials), altMaterials(_altMaterials) {}

    virtual void operator()(Render::BaseMaterial &material)
    {
      vector<NDb::Ptr<NDb::Material>>::const_iterator it = desc->materials.begin();
      vector<NDb::Ptr<NDb::Material>>::const_iterator last = desc->materials.end();

      for (; it != last; ++it )
      {
        if ( (*it)->caption == material.GetDBMaterial()->caption )
        {
          Render::BaseMaterial* altMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( *it ) );

          if ( altMaterial )
          {
            altMaterial->SetSkeletalMeshPin( material.GetSkeletalMeshPin() );

            if(Render::BasicMaterial* basic = dynamic_cast<Render::BasicMaterial*>(&material))
            {
              // Transparency effects modify blend values which ruins configured fading,
              // we need to ignore the override and use what is initially configured.
              basic->SetBlendModeOverride(false);
            }
    
            material.SetAlternativeMaterial( altMaterial );
            material.SetEnableAltPriority(true);
            altMaterials.push_back( altMaterial );
            baseMaterials.push_back( &material );

            altMaterial->SetFadingAlternativeMaterial( true );
 
            // If we are transparent, don't disrupt it by fading into an opaque state
            bool transp = material.IsTransparent();
            altMaterial->SetBasePriority( transp ? NDb::MATERIALPRIORITY_TRANSPARENTSPECIAL : NDb::MATERIALPRIORITY_TRANSPARENT );
            altMaterial->SetAltPriority( transp ? NDb::MATERIALPRIORITY_TRANSPARENTSPECIAL : NDb::MATERIALPRIORITY_MESHESOPAQUE );
          }
        }
      }
    }
  };

  pUnit = _pUnit;

  if ( IsValid(pUnit) )
  {
    NScene::SceneObject* sceneObject = pUnit->GetSceneObject();

    if ( sceneObject )
    {
      SetAltMaterialProc proc( &GetDBEffect(), baseMaterials, altMaterials );
      NScene::ForAllMaterials( *sceneObject, proc );
    }

    pUnit->UpdateColor();
  }

  curFadeInTime = 0.f;
  doFadeIn = true;
}

void ChangeMaterialEffect::Die() 
{
  if ( bDying )
    return;

  bDying = true;

  curFadeOutTime = doFadeIn ? (min<float>(1.0f, curFadeInTime / dbFadeInTime) * dbFadeOutTime) : 0.f;
  doFadeIn = false;
  doFadeOut = true;

  SetFading( true );
}

void ChangeMaterialEffect::DieImmediate()
{
  {
    Materials::iterator it = baseMaterials.begin();
    Materials::iterator last = baseMaterials.end();

    for (; it != last; ++it )
    {
      if ( Render::BaseMaterial* m = *it )
      {
        m->SetAlternativeMaterial( 0 );
      }
    }
  }

  {
    Materials::iterator it = altMaterials.begin();
    Materials::iterator last = altMaterials.end();

    for (; it != last; ++it )
    {
      if ( *it )
        delete *it;
    }
  }

  altMaterials.clear();
  baseMaterials.clear();

  if (IsValid(pUnit))
    pUnit->UpdateColor();

  BasicEffect::DieImmediate();
}


void ChangeMaterialEffect::Update( float timeDelta )
{
  // Don't fully blend into 1 from/to blend (1 will be set at the end of blending).
  // Current transparency effect will look broken if started with full opacity (1).
  const float maxOp = 0.99f;

  SetEnableAltPriority(!(doFadeOut == doFadeIn));

  if ( doFadeIn )
  {
    float t = min<float>(1.0f, curFadeInTime / dbFadeInTime);

    ModifyBaseOpacity( std::max(maxOp - t, 0.0f) );
    ModifyAltEmissive( t );

    curFadeInTime += timeDelta;

    if ( t >= 1.0f )
    {
      SetFading( false );
      doFadeIn = false;
    }
  }

  if ( doFadeOut )
  {
    float t = min<float>(1.0f, curFadeOutTime / dbFadeOutTime);

    ModifyBaseOpacity( std::min(t, maxOp) );
    ModifyAltEmissive( 1.f - t );

    curFadeOutTime += timeDelta;

    if ( t >= 1.0f )
    {
      ModifyBaseOpacity( 1.f );
      ModifyAltEmissive( 1.f - t );

      SetFading( false );
      doFadeOut = false;

      DieImmediate();
    }
  }
}


void ChangeMaterialEffect::SetFading( bool fading )
{
  Materials::iterator it = altMaterials.begin();
  Materials::iterator last = altMaterials.end();

  for (; it != last; ++it )
  {
    if ( *it )
      (*it)->SetFadingAlternativeMaterial( fading );
  }
}


void ChangeMaterialEffect::ModifyBaseOpacity( float opacity )
{
  Materials::iterator it = baseMaterials.begin();
  Materials::iterator last = baseMaterials.end();

  for (; it != last; ++it )
  {
    if ( *it )
      (*it)->ModifyOpacity( opacity );
  }
}


void ChangeMaterialEffect::ModifyAltEmissive( float power )
{
  Materials::iterator it = altMaterials.begin();
  Materials::iterator last = altMaterials.end();

  for (; it != last; ++it )
  {
    if ( *it )
      (*it)->ModifyEmissive( power );
  }
}


void ChangeMaterialEffect::SetEnableAltPriority( bool state )
{
  Materials::iterator it = baseMaterials.begin();
  Materials::iterator last = baseMaterials.end();

  for (; it != last; ++it )
  {
      (*it)->SetEnableAltPriority(state);
  }
}


bool ChangeMaterialEffect::Ready2Die()
{
  return !(curFadeOutTime < dbFadeOutTime);
}

}
BASIC_REGISTER_CLASS( PF_Core::ChangeMaterialEffect );