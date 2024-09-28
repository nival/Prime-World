#include "stdafx.h"
#include "../Render/VertexColorStream.h"
#include "../Render/InstancedMesh.h"
#include "VertexColorManager.h"
#include "RenderableScene.h"
#include "SceneObject.h"
#include "StaticSceneComponent.h"

#include "../System/InlineProfiler.h"


namespace NScene
{

#include "TestBB.h"
DECLARE_NULL_RENDER_FLAG

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StaticSceneComponent::StaticSceneComponent( const NDb::StaticMesh* pDBMesh, const Placement& pos )
: SceneComponent(0, 0, pos)
, time ( 0.f )
, pStaticMesh( 0 )
, needLightingSH( false )
, pDBObject( 0 )
{
	Render::StaticMesh *pSM = new Render::StaticMesh();
	pSM->Initialize( IDENTITY_MATRIX, pDBMesh );
	Reset(pStaticMesh, pSM);

	localAABB.Set(pDBMesh->aabb);
  TEST_BB_UNIQUE( localAABB.IsValid() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StaticSceneComponent::CheckMaterials(const NDb::DBStaticSceneComponent* pDBComponent, NDb::LightingPin* pLighting)
{
  int numMaterials = pDBComponent->materialsReferences.size();
  if (numMaterials <= 0)
    return false;

//  bool hasBakedLightingSettings = false;
  bool hasBakedLighting = false;
  bool hasInstancing = false;
  bool hasSHLighting = false;

  // look through all materials
  for (int i = 0; i < numMaterials; i++)
  {
    NDb::Material const* pMaterial = pDBComponent->materialsReferences[i].GetPtr();
    DWORD typeId = pMaterial->GetObjectTypeID();

    //////////////////////////////////////////////////////////////////////////
    // Basic Material
    if (typeId == NDb::BasicMaterial::typeId)
    {
      NDb::BasicMaterial const* pBasicMaterial = dynamic_cast<const NDb::BasicMaterial*>(pMaterial);
      NI_VERIFY(pBasicMaterial != NULL,
        NStr::StrFmt("Couldn't cast material %i to BasicMaterial. See '%s'", i, GetFormattedDbId(dbid).c_str()), return false);

      bool thisBakedLighting = (pBasicMaterial->LightingPinValue == NDb::LIGHTINGPIN_LIGHTINGBAKED);
//       NI_DATA_VERIFY(!hasBakedLightingSettings || thisBakedLighting == hasBakedLighting,
//         NStr::StrFmt("Baked lighting settings mismatch in different materials on a single mesh. See '%s'", 
//         GetFormattedDbId(dbid).c_str()), return false);
      
      hasBakedLighting = thisBakedLighting;
//      hasBakedLightingSettings = true;
      hasSHLighting = (hasSHLighting || (pBasicMaterial->LightingPinValue == NDb::LIGHTINGPIN_LIGHTINGSH));
      hasInstancing = (pBasicMaterial->LightingPinValue == NDb::LIGHTINGPIN_LIGHTINGINSTANCEDSH);
    }
    //////////////////////////////////////////////////////////////////////////
    // Basic FX Material
    else if (typeId == NDb::BasicFXMaterial::typeId)
    {
      NDb::BasicFXMaterial const* pBasicFXMaterial = dynamic_cast<const NDb::BasicFXMaterial*>(pMaterial);
      NI_VERIFY(pBasicFXMaterial != NULL,
        NStr::StrFmt("Couldn't cast material %i to BasicFXMaterial. See '%s'", i, GetFormattedDbId(dbid).c_str()), return false);
    }
    //////////////////////////////////////////////////////////////////////////
    // Drop Material
    else if (typeId == NDb::DropMaterial::typeId)
    {
      NDb::DropMaterial const* pDropMaterial = dynamic_cast<const NDb::DropMaterial*>(pMaterial);
      NI_VERIFY(pDropMaterial != NULL,
        NStr::StrFmt("Couldn't cast material %i to DropMaterial. See '%s'", i, GetFormattedDbId(dbid).c_str()), return false);
    }
  }

  needLightingSH = (hasSHLighting || hasInstancing);

  // check further inconsistencies

  NI_DATA_VERIFY(!hasInstancing || numMaterials == 1, 
    NStr::StrFmt("Instancing is supported only for a single material mesh (found %i materials). See '%s'", 
    numMaterials, GetFormattedDbId(dbid).c_str()), return false);

  if (hasInstancing)
    *pLighting = NDb::LIGHTINGPIN_LIGHTINGINSTANCEDSH;
  else if (hasBakedLighting)
    *pLighting = NDb::LIGHTINGPIN_LIGHTINGBAKED;

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StaticSceneComponent::StaticSceneComponent( const NDb::DBStaticSceneComponent* pDBComponent, const NDb::AttachedSceneComponent* pObj, 
																						const Placement& pos )
:	SceneComponent(pDBComponent, pObj, pos)
, time ( 0.f )
, needLightingSH( false )
, pDBObject( pDBComponent )
{
  localAABB.Set(pDBComponent->aabb);
  NI_ASSERT( localAABB.IsValid(), NStr::StrFmt("AABB should be valid %s", FormatDescription()) );

	// Check material types and settings
  NDb::LightingPin const lightInvalid = (NDb::LightingPin)(-1);
  NDb::LightingPin light = lightInvalid;
  if (!CheckMaterials(pDBComponent, &light))
    return;

  // Select mesh types
	if (light == NDb::LIGHTINGPIN_LIGHTINGINSTANCEDSH)
  {
    Render::InstancedMesh *pIM = new Render::InstancedMesh();
    pIM->Initialize( pDBComponent );
    pIM->SetDBID(dbid);
    Reset(pStaticMesh, pIM);
  }
  else // not necessarily BasicMaterial! [2/11/2010 smirnov]
	{
/* // remove in a few weeks [2/15/2010 smirnov]
    {
      int numMaterials = pDBComponent->materialsReferences.size();
      for (int i = 0; i < numMaterials; i++)
      {
        NDb::Material const* pMaterial = pDBComponent->materialsReferences[i].GetPtr();
        DWORD typeId = pMaterial->GetObjectTypeID();
        if (typeId == NDb::BasicMaterial::typeId)
        {
          systemLog(NLogg::LEVEL_MESSAGE) << "STATICMESH:MATERIAL = " << GetFormattedDbId(pMaterial->GetDBID());
        }
      }
    }
*/
		Render::StaticMesh *pSM = new Render::StaticMesh();

    if(!RENDER_DISABLED)
      pSM->Initialize(IDENTITY_MATRIX, pDBComponent, light == NDb::LIGHTINGPIN_LIGHTINGBAKED);

    pSM->SetDBID(dbid);
    Reset(pStaticMesh, pSM);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticSceneComponent::UpdateComponent( UpdatePars &pars, const Placement& parentPos, float timeDiff )
{
  NI_PROFILE_FUNCTION

  // Make result matrix
	Matrix43 resultmatrix;
	worldPlacement.GetMatrix( &resultmatrix );

	// Transform local AABB to global one
	worldAABB.Transform( resultmatrix, localAABB );
  NI_ASSERT(worldAABB.IsValid() || !localAABB.IsValid(), NStr::StrFmt( "AABB should be valid %s", FormatDescription() ) );

	// Update object's AABB
	pars.objectAABB.Grow(worldAABB);
  NI_ASSERT(pars.objectAABB.IsValid(), NStr::StrFmt( "AABB should be valid %s", FormatDescription() ) );

	if ( pStaticMesh )
	{
		pStaticMesh->SetWorldMatrix( resultmatrix );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticSceneComponent::RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants )
{
	if ( pStaticMesh )
	{
		SceneComponent::RenderToQueue(queue, sceneConstants);
    pStaticMesh->RenderToQueue( queue );
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticSceneComponent::ForAllMaterials(Render::IMaterialProcessor &proc)
{
  if (pStaticMesh)
  {
    pStaticMesh->ForAllMaterials(proc);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticSceneComponent::OnAfterAdded(class SceneObject *pObject)
{
	if (pStaticMesh && needLightingSH)
		pObject->SetupForLighting();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StaticSceneComponent::LoadVertexColors(NScene::MeshVertexColorsManager &man, int componentIdx)
{
  if( BakedLightingUsed() )
  {
    if( AutoPtr<Render::MeshVertexColors> pMVC = man.RequestVertexColorStream(componentIdx, this) )
    {
      Render::StaticMesh* pSM = dynamic_cast<Render::StaticMesh*>(Get(pStaticMesh));
      NI_VERIFY(pSM, "Bad assumption: pStaticMesh is NOT a StaticMesh", return false);
      pSM->SetVertexColors(pMVC, false);
      return true;
    }
    else
    {
      Render::StaticMesh* pSM = dynamic_cast<Render::StaticMesh*>(Get(pStaticMesh));
      NI_VERIFY(pSM, "Bad assumption: pStaticMesh is NOT a StaticMesh", return false);
      pSM->SetVertexColors(pMVC, true);
    }
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StaticSceneComponent::BakedLightingUsed()
{
#ifdef _USE_DB
  NDb::Ptr<NDb::DBStaticSceneComponent> pDBSC = NDb::Get<NDb::DBStaticSceneComponent>( GetDBID() );
  if( !pDBSC.IsEmpty() ) {
    NDb::LightingPin light = (NDb::LightingPin)(-1);
    return CheckMaterials(pDBSC.GetRawResourcePtr(), &light) && NDb::LIGHTINGPIN_LIGHTINGBAKED == light;
  }
#else // _USE_DB
  if(pStaticMesh) {
    struct CheckBakedLighting : Render::IMaterialProcessor 
    {
      bool result;

      CheckBakedLighting() : result(false) {}
      void operator()(Render::BaseMaterial &material)
      {
        result |= NDb::LIGHTINGPIN_LIGHTINGBAKED == material.GetLightingPin();
      }
    } checkBakedLighting;

    pStaticMesh->ForAllMaterials(checkBakedLighting);
    return checkBakedLighting.result;
  }
#endif // _USE_DB

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void StaticSceneComponent::AddGeometryCRC(Crc32Checksum &crc)
{
  if (pStaticMesh)
  {
    pStaticMesh->AddGeometryCRC(crc);
  }
}

void StaticSceneComponent::Attach( SceneComponent* toadd )
{
  if ( !toadd )
    return;

  SceneComponent* it = toadd;
  do 
  {
    it->SetJointIdx( -1 );
    if ( it->GetLocatorName().length() && !pDBObject.IsEmpty() && !pDBObject->locatorList.IsEmpty() )
    {
      for ( int i = 0; i < pDBObject->locatorList->locators.size(); i++ )
      {
        if ( pDBObject->locatorList->locators[i].name == it->GetLocatorName() )
        {
          const NDb::Locator& locator = pDBObject->locatorList->locators[i];
          const Placement& offset = locator.offset2.GetPlace();
          it->SetLocatorPos( offset.pos, offset.rot, offset.scale );
          it->SetLocatorName( it->GetLocatorName(), pDBObject->locatorList->locators[i].flags );
          break;
        }
      }
    }
    it = it->GetBrother();
  } while ( it && it != toadd );

  SceneComponent::Attach( toadd );
}

} // namespace NScene
