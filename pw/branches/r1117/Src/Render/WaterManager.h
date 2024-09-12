#pragma once

#include "../System/Singleton4DLL.h"
#include "../System/fixedvector.h"

#include "sceneconstants.h"
#include "WaterMesh.h"
#include "WaterMathTex.h"


namespace Render
{
  static const int g_numWaterLevels = 10;

  class BatchQueue;

	class WaterLevel
	{
	public:
		float GetLevel() const { return level; }

		template <class F>
		void ForAllConvexes( F &f )
		{
			ListElement *pEl = pHead;
			while (pEl)
			{
				pEl->pWaterMesh->ForAllConvexes( f );
				pEl = pEl->pNext;
			}
		}

		void PushWaterBatches( BatchQueue &queue );

    void BuildMatricesForReflection(SceneConstants *_pOutConsts, const SceneConstants &_inConsts, float _levelShift = 0.0f) const;

	private:
		struct ListElement
		{
			WaterMesh *pWaterMesh;
			ListElement     *pNext;
		};

		ListElement *pHead;
		float       level;

		friend class WaterManager;
	};

	class WaterManager : public Singleton4DLL<WaterManager>
	{
	public:
		struct CreateParams
		{
			CreateParams(float reflCoeff, float refrCoeff) : reflectionTextureSizeFactor(reflCoeff), refractionTextureSizeFactor(refrCoeff) {}
			float reflectionTextureSizeFactor; // 1.0 - to have the save dimensions as main back buffer
			float refractionTextureSizeFactor; // 1.0 - to have the save dimensions as main back buffer
		};

		WaterManager(const CreateParams &pars);
    ~WaterManager() { delete pDummyMaterial; }

		void AddWaterMesh(WaterMesh &mesh);

		bool IsReflectionRendering() { return isReflectionRendering; }
		void SetReflectionRenderingFlag( bool isReflRendering ) { isReflectionRendering = isReflRendering; }

		static void SetAnimationSpeedFactor( float factor );
    static void SetReflectedColors(const HDRColor& _color0, const HDRColor& _color1);
		
		template <class F>
		void ProcessGatherdWaterLevels(F &f)
		{
			// Call functor for all water levels
			for (TWaterLevelVector::iterator it = waterLevels.begin(); it != waterLevels.end(); ++it)
				f(*it);
			// Clear array
			waterLevels.clear();
			listElements.resize(0);
		}

		// Binds water render target
		void StartRenderingToReflectionTexture(bool _clearColor);
		void ShowWaterTexture(int index);
		void Update( float time );

		void StartWaterSurfaceRendering( const SHMatrix &reflViewProj, const SHMatrix &refrViewProj, const Render::SceneConstants &sceneConsts, Render::Texture2DRef const& pMainDepth );
		void StopWaterSurfaceRendering();

    Texture2DRef const& GetHDxDyTexture() const { return hnTexture.getTexture(); }
    BaseMaterial* GetDummyMaterial() const { return pDummyMaterial; }

	private:
    void SetupTextureMatrix(const Render::Texture2D &_texture);

		typedef FixedVector<WaterLevel, g_numWaterLevels> TWaterLevelVector;

		SHMatrix           halfMtx;
    SHMatrix           halfMtxV;
		TWaterLevelVector  waterLevels; 
		// Vector of list elements
		nstl::vector<WaterLevel::ListElement> listElements;
		// Reflection texture & depth buffer here
		Texture2DRef       pRTTexture;
		RenderSurfaceRef   pRTDepth;
		// A copy of target buffer
		Texture2DRef       pRefrTexture;
		//
		DXPixelShaderRef   pReflTexClearPS;

		//
		bool               isReflectionRendering;
		bool               isRefractionEnabled;
		float              animationSpeedFactor;
		// Water texture
    Water::ScrollTexture hnTexture;
    BaseMaterial*          pDummyMaterial;
	};

};//namespace Render