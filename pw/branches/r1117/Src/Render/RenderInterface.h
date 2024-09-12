#pragma once

#include "rendermode.h"
#include "batch.h"
#include "debugrenderer.h"

class IRenderableScene;

namespace Render
{

struct Rect;

class ConvexVolume;

struct Renderer2Texture
{
	virtual void Render2SHTexture(const SHMatrix &view, const SHMatrix &proj, const Render::BatchQueue &queue) = 0;
};

class Interface : public Renderer2Texture
{
public:
	typedef Interface* (*Factory)(HWND hwnd);

	Interface(HWND hwnd = 0);
	virtual ~Interface();

	static Interface *Get();

  virtual bool Start( RenderMode& renderMode );
	virtual void Stop();

  virtual void Render( bool bEditorSpecific ) {};
  virtual void Render( bool bEditorSpecific, int x, int y, int width, int height ) {};

  virtual void RenderUI( bool bEditorSpecific ) {}; //special part for compulsory part of render

  virtual void ConstrainRender(const RECT &_rect) = 0;

	void SetClearColor( Color color ) { clearColor = color; }
	void Clear();
	void Clear( Color color );
	
	void RegisterSceneForRendering( IRenderableScene *pScene_ ) { pScene = pScene_; }

  virtual bool SetShadows( bool val ) { return true; };

	void Present();
	void Present( HWND hWnd, const Render::Rect& sourceRect, const Render::Rect& destRect );
  void Present( HWND hWnd, const Render::Rect* sourceRect, const Render::Rect* destRect );

	void GetTriangleAndDipCount( unsigned int& triangleCount, unsigned int& dipCount ); 

	static void RegisterFactory(Factory func);
	static Interface* Create(HWND hwnd = 0);

  virtual void Render2SHTexture(const SHMatrix &view, const SHMatrix &proj, const Render::BatchQueue &queue) {}
  void SetHWND( HWND hwnd);

  virtual IDebugRender *GetDebugRender() { return NULL; }

  void DisableWarFog(bool disable) {disableWarFog = disable;}

protected:
	IRenderableScene *pScene; // @BVS@PFRENDER Should be changed
	Color            clearColor; 
  bool             disableWarFog;

private:
	static Interface *s_pSelf;
	static Factory    s_creationFactory;
};

}
