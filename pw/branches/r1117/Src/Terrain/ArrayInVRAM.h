#pragma once

template <typename TEXEL> class ArrayInVRAM
{
public:
	ArrayInVRAM(Render::ERenderFormat format): format(format), pLocked(NULL) {}
	~ArrayInVRAM() { Destroy(); }

	void Create(unsigned int width, unsigned int height)
	{
		Destroy();
		sysTexture = Render::CreateTexture2D(width, height, 1, Render::RENDER_POOL_SYSMEM, format);
		vramTexture = Render::CreateRenderTexture2D(width, height, format);
	}

	bool IsReady() const { return sysTexture && vramTexture; }
	const Render::Texture2DRef& GetTexture() { return vramTexture; }

	TEXEL const* Fetch();

private:
	void Unlock()
	{
		if (pLocked)
		{
			sysTexture->UnlockRect(0);
			pLocked = NULL;
		}
	}

	void Destroy()
	{
		Unlock();
		sysTexture = 0;
		vramTexture = 0;
	}

private:
	Render::ERenderFormat format;
	Render::Texture2DRef sysTexture;
	Render::Texture2DRef vramTexture;
	TEXEL const* pLocked;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename TEXEL> TEXEL const* ArrayInVRAM<TEXEL>::Fetch()
{
	Unlock();

	// synchronize surfaces
	Render::GetRenderer()->GetRenderTargetData( Get(vramTexture->GetSurface(0)), Get(sysTexture->GetSurface(0)) );

//	static int hackcounter = 0;
//	D3DXSaveSurfaceToFile( NStr::StrFmt( "heights%d.pfm", hackcounter++), D3DXIFF_PFM, dst->GetD3DSurface(), 0, 0);

	// lock
	Render::LockedRect rect = sysTexture->LockRect(0, Render::LOCK_READONLY);
	pLocked = reinterpret_cast<TEXEL const*>(rect.data);
	int width = vramTexture->GetWidth();
	NI_ASSERT(rect.pitch == int( width * sizeof(TEXEL) ), NStr::StrFmt("pitch %d, width %d", rect.pitch, width));
	return pLocked;
}

