#pragma once
#include "texture.h"
#include "Rect.h"
#include "rendermode.h"
#include "renderer.h"

#include "renderformat.h"
#include "locktype.h"
//#include "renderresourcemanager.h"

#error "Removed from project by BVS"

namespace Render
{

	/* @BVS@CLEAN
	namespace Renderer
	{
		IRenderSurface* GetDepthStencilSurface();
	} */

/*
	class RenderTarget
	{
		unsigned int Width;
		unsigned int Height;
		ERenderFormat Format;
		EMultiSampleType MultiSampleType;

		IRenderSurface* pColorSurface;
		IRenderSurface* pDepthStencilSurface;

	public:
		RenderTarget(): Width(0), Height(0), pColorSurface(0), pDepthStencilSurface(0) {}

		RenderTarget(Texture2D* pTexture) 
			: Width(pTexture->GetWidth()), Height(pTexture->GetHeight())
			, pColorSurface(pTexture->GetSurface(0)), pDepthStencilSurface(0)
		{
			pDepthStencilSurface = GetRenderer()->GetDepthStencilSurface();
		}

		virtual ~RenderTarget() 
		{
		}

		unsigned int GetWidth() const { return Width; }
		unsigned int GetHeight() const { return Height; }

		EMultiSampleType GetMultiSampleType() const { return MultiSampleType; }
		ERenderFormat GetFormat() const { return Format; }


		void SetColorSurface( unsigned int renderTargetIndex, IRenderSurface* surface ) { pColorSurface = surface; }
		void SetDepthStencilSurface( IRenderSurface* surface ) { pDepthStencilSurface = surface; }
		IRenderSurface* GetColorSurface() { return pColorSurface; }
		const IRenderSurface* GetColorSurface() const { return pColorSurface; }
		IRenderSurface* GetDepthStencilSurface() { return pDepthStencilSurface; }
		const IRenderSurface* GetDepthStencilSurface() const { return pDepthStencilSurface; }

	};
	*/
};