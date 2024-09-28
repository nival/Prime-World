//generated file
// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "GrassMaterial.h"
#include "renderresourcemanager.h"

namespace Render
{
	namespace Materials
	{

		Materials::GrassMaterial* GrassMaterial::CreateMaterialInstance( const NDb::GrassMaterial* pGrassMaterial )
		{
			GrassMaterial* pMaterialInstance = new GrassMaterial();
			pMaterialInstance->default_BlendState = pGrassMaterial->default_BlendState;
			pMaterialInstance->default_AlphaState = pGrassMaterial->default_AlphaState;
			pMaterialInstance->default_CullingState = pGrassMaterial->default_CullingState;
			pMaterialInstance->FrozenDiffuseMap = pGrassMaterial->FrozenDiffuseMap;
			pMaterialInstance->NormalDiffuseMap = pGrassMaterial->NormalDiffuseMap;
			pMaterialInstance->BurnedDiffuseMap = pGrassMaterial->BurnedDiffuseMap;
			pMaterialInstance->ShadowReciverPinValue = pGrassMaterial->ShadowReciverPinValue;
			pMaterialInstance->bladeSize = pGrassMaterial->bladeSize;
			pMaterialInstance->elasticity = pGrassMaterial->elasticity;
			pMaterialInstance->subpriority = pGrassMaterial->subpriority;
			return pMaterialInstance;
		}

		void GrassMaterial::PrepareRenderer( NDb::Techniques techniqueID )
		{
			#include "GrassMaterial.inl"
			SetRenderStates( techniqueID );
			BindSamplers( techniqueID );
			BindShaders( techniqueID );
			return;
		}

		void GrassMaterial::BindSamplers( NDb::Techniques currentTechniqueID )
		{
			if( IsFrozenDiffuseMapPresent() )
				FrozenDiffuseMap.Bind();
			if( IsNormalDiffuseMapPresent() )
				NormalDiffuseMap.Bind();
			if( IsBurnedDiffuseMapPresent() )
				BurnedDiffuseMap.Bind();
		}

		void GrassMaterial::BindShaders( NDb::Techniques currentTechniqueID )
		{
			switch ( currentTechniqueID )
			{
				case NDb::TECHNIQUES_SHADOWPASS:
					RenderResourceManager::GetMultiShader( 109 )->GetShaderPairByIndex( GetShaderIndex() ).Bind();
					break;
				case NDb::TECHNIQUES_MAINPASS:
					RenderResourceManager::GetMultiShader( 9 )->GetShaderPairByIndex( GetShaderIndex() ).Bind();
					break;
			}
		}

		void GrassMaterial::SetRenderStates( NDb::Techniques currentTechniqueID )
		{
			switch ( currentTechniqueID )
			{
				case NDb::TECHNIQUES_SHADOWPASS:
					GetStatesManager()->SetAlphaState( default_AlphaState );
					GetStatesManager()->SetBlendState( default_BlendState );
					GetStatesManager()->SetCullingState( default_CullingState );
					return;
				case NDb::TECHNIQUES_MAINPASS:
					GetStatesManager()->SetAlphaState( default_AlphaState );
					GetStatesManager()->SetBlendState( default_BlendState );
					GetStatesManager()->SetCullingState( default_CullingState );
					return;
				default:
					NI_ALWAYS_ASSERT( "wrong technique" );
			}
		}


	}//namespace Materials
}//namespace Render
