#include "UI/stdafx.h"
#include "UI/FlashContainer2.h"
#include "Render/FlashRendererInterface.h"

#include "System/DebugTraceDumper.h"
#include "System/ServerStdOutDumper.h"
#include "System/nstring.h"

#include "FlashMovie.h"
#include "FlashPlayer.h"
#include "tests/FlashCompiler.h"
#include "Natives/display/StageProvider.h"
#include "FontsRenderInterface.h"

#include "Sound/SoundScene.h"

#include <sys/stat.h>

#pragma warning( disable : 4242 )


class MockStageProvider : public flash::IStageProvider, public CObjectBase
{
  OBJECT_METHODS( 0x9D764280, MockStageProvider );
public:
  MockStageProvider() {}

  virtual int GetStageWidth() const { return 100; }
  virtual int GetStageHeight() const { return 100; }
  virtual void Invalidate() {}
};

class MockFontInstance : public flash::IFontInstance, public CObjectBase
{
  OBJECT_BASIC_METHODS( MockFontInstance );
public:
  MockFontInstance() {}

  virtual void RenderGlyph( wchar_t c, const flash::SWF_MATRIX & _matrix, const flash::SWF_RGBA & color ) {}
  virtual void RenderText( const wchar_t * text, unsigned length, const flash::SWF_MATRIX & _matrix, const flash::SWF_RGBA & color ) {}
  virtual float GetStringLength( const wchar_t * text, unsigned length, float maxWidth, unsigned * charsFitIn, float additionalAdvance ) {  if ( charsFitIn ) *charsFitIn = 10; return 10.f;};
  virtual float Height() const { return 10; } 
  virtual float Ascent() const { return 7; }
  virtual float Descent() const { return 1; }
  virtual float GapAbove() const { return 1; }
  virtual float GapUnder() const { return 1; }
  virtual float DefaultGlyphWidth() const { return 4; }
  virtual void  SetBevel( bool _drawBevel, const flash::SWF_RGBA& _color ) {}
};

class MockFontRender : public flash::IFontRender, public CObjectBase
{
  OBJECT_BASIC_METHODS( MockFontRender );
public:
  MockFontRender() {}
  virtual void SetViewport( int x, int y, int width, int height ) {};
  virtual void SetMovieRect( float x, float y, float width, float height ) {} //Flash twips
  virtual flash::IFontInstance * FindFont( const char * name, int height, bool bold, int italic, const flash::SFontMetricInfo * metric ) { return new MockFontInstance; }
  virtual void DebugLine( float x0, float y0, float x1, float y1, const flash::SWF_RGBA & color ) {};
};

namespace Render
{

class MockFlashRender : public IFlashRenderer, public CObjectBase
{
  OBJECT_BASIC_METHODS( MockFlashRender );

public:
  virtual bool Initialize(){return 0;};
  virtual void Release(){};

  virtual void StartFrame(){};
  virtual void BeginQueue(){};
  virtual void EndQueue(){};

  virtual void BreakQueue(){};

  virtual void SetResolutionCoefs( float x, float y, float widthScale, float heightScale ){};

  virtual void SetMatrix( const flash::SWF_MATRIX& _m ){};
  virtual void SetColorTransform( const flash::SWF_CXFORMWITHALPHA& cx ){};
  virtual void SetBlendMode( EFlashBlendMode::Enum blendMode ){};

  virtual void SetFillStyleBitmap(int fill_side, IBitmapInfo* bi, const flash::SWF_MATRIX& m, EBitmapWrapMode::Enum wm ){};

  virtual void DrawBitmap( IBitmapInfo* bi, float width, float height ){};

  virtual void DrawMeshStrip( const void* coords, int vertex_count, bool with_color, int unique_id, int submesh_id ){};
  //virtual void DrawTriangleList( const void* coords, int vertex_count, bool with_color, int unique_id, int submesh_id ){};
  virtual void DrawLineStrip( const void* coords, int vertex_count ){};

  virtual void DrawBitmapScale9Grid( IBitmapInfo* bi, float width, float height, const flash::SWF_RECT& scale9Grid, float aspectX, float aspectY ) {}
  virtual void DrawTriangleList( const void* coords, int vertex_count ) {}
  virtual void DrawMorph( const void* coords, int vertex_count, float rate ) {}

  virtual void SetLineWidth( float width ){};
  virtual void SetLineColor( const flash::SWF_RGBA& color ){};

  virtual void RenderText( int _partID ) {}
  virtual void DebugNextBatch() {}

  virtual void BeginDisplay(
    int viewport_x0, int viewport_y0,
    int viewport_width, int viewport_height,
    float x0, float x1, float y0, float y1,
    bool useScissorRect ){};
  virtual void EndDisplay(){};

  virtual void BeginSubmitMask(){};
  virtual void EndSubmitMask(){};
  virtual void DisableMask(){};

  virtual void BeginColorMatrix( const SHMatrix& _colorMatrix, const CVec4& _addColor ){};
  virtual void EndColorMatrix(){};

  virtual IBitmapInfo* CreateBitmap( int width, int height ){ return 0; };
  virtual IBitmapInfo* CreateBitmapFromTexture( const Texture2DRef& _texture ){ return 0; };
  virtual IBitmapInfo* CreateBitmapInfoRgba( image::rgba* im ){ return 0; };
  virtual IBitmapInfo* CreateLinearGradient( image::rgba* im, int& lineID, const char* fileName, unsigned short characterID, int gradientID, bool forLine ){ return 0; };
  virtual IBitmapInfo* CreateBitmapFromFile( const nstl::string& filename ){ return 0; };

};

}
  
void TestSWF( const char * swffile )
  {
    flash::InitializeFlash();
    flash::Player* player = flash::Player::Get();
    player;

    {
      MMGC_ENTER_VOID;
      MMgc::GC* gc = mmfx_new( MMgc::GC(MMgc::GCHeap::GetGCHeap(), MMgc::GC::kIncrementalGC) );

      {
        MMGC_GCENTER( gc );

        CObj<MockStageProvider> stageProvider = new MockStageProvider();
        CObj<Render::MockFlashRender> renderer = new Render::MockFlashRender();

        flash::Movie * flashMovie = new flash::Movie( stageProvider, gc, new MockFontRender );

        flashMovie->SetFlashRenderer( renderer );
        flashMovie->SetViewport( 0, 0, 100, 100 );
        flashMovie->LoadFile( swffile );

        for ( int i = 0 ; i < 10; ++i )
          flashMovie->Advance( 0.1f );

        delete flashMovie;
      }

      mmfx_delete( gc );
    }

    flash::ReleaseFlash();
  }

void main( int argc, char ** args )
{
  if (argc!=2)
    return;

  NLogg::CServerStdOutDumper * stdOutDumper = new NLogg::CServerStdOutDumper( &GetSystemLog() );
  NLogg::CDebugTraceDumper * debugTraceDumper = new NLogg::CDebugTraceDumper( &GetSystemLog() );
  
  TestSWF(args[1]);

  delete debugTraceDumper;
  delete stdOutDumper;
}

BASIC_REGISTER_CLASS( Render::IBitmapInfo );
BASIC_REGISTER_CLASS( UI::FlashContainer2 );