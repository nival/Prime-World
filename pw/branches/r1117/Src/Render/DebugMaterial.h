//generated file
#pragma once
#include "IMaterial.h"
#include "MaterialResourceInterface.h"


namespace Render
{
	namespace Materials
	{

		class DebugMaterial : public IMaterial
		{
			NDb::DepthState default_DepthState;
			NDb::CullingState default_CullingState;
			NDb::FillState default_FillState;
			NDb::DarkMapPin DarkMapPinValue;
			NDb::SkeletalMeshPin SkeletalMeshPinValue;
			NDb::DebugPin DebugPinValue;


		public:
			static Materials::DebugMaterial* CreateMaterialInstance( const NDb::DebugMaterial* pDebugMaterial );
			virtual void PrepareRenderer( NDb::Techniques techniqueID );
			virtual ~DebugMaterial() { }


			bool IsBlendEnabled() const
			{
				return false;
			}

			bool IsShadowCaster() const
			{
				return false;
			}

			DWORD GetTypeID() const
			{
				return 0x4A55D341;
			}

			void SetDebugPinValue( NDb::DebugPin _DebugPinValue ) { DebugPinValue = _DebugPinValue; }
			NDb::DebugPin GetDebugPinValue( ) const { return DebugPinValue; }
			void SetSkeletalMeshPinValue( NDb::SkeletalMeshPin _SkeletalMeshPinValue ) { SkeletalMeshPinValue = _SkeletalMeshPinValue; }
			NDb::SkeletalMeshPin GetSkeletalMeshPinValue( ) const { return SkeletalMeshPinValue; }

		private:
			void BindSamplers( NDb::Techniques techniqueID );
			void BindShaders( NDb::Techniques techniqueID );
			void SetRenderStates( NDb::Techniques techniqueID );

			unsigned int GetShaderIndex() const
			{
				return 1 * DebugPinValue + 3 * SkeletalMeshPinValue;
			}
		};

	}//namespace Materials
}//namespace Render
