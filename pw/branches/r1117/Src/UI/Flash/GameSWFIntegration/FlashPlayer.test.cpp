//!Component('System/Dumpers')
//!Component('System/InlineProfiler')
//!Component('UI/Flash/GameSWFIntegration')
//!Component('UI/Flash/GameSWFIntegration/tests/FlashTests')
//!Component('Sound/Main')
//!Component('UI/Flash')
//!Component('System/Compatibility')
//!Component('UI/FontsRender')
//!Component('UI/Elements')
//!Component('UI/Core')
//!Component('Render/ImmediateRenderer')
//!Component('Render/PostEffects')
//!Component('Render/Occlusion')
//!Component('Render/RenderScene')

#include "cxxtest/TestSuite.h"
#include "UI/stdafx.h"
#include "UI/FlashContainer2.h"
#include "Render/FlashRendererInterface.h"
#include "System/DebugTraceDumper.h"
#include "System/nstring.h"
#include "FlashMovie.h"
#include "FlashPlayer.h"
#include "tests/FlashCompiler.h"
#include "Natives/display/StageProvider.h"
#include "FontsRenderInterface.h"
#include "Sound/SoundScene.h"

#include "System/InlineProfiler.h"

#include <sys/stat.h>

#pragma warning( disable : 4242 )

class MockStageProvider : public flash::IStageProvider, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MockStageProvider, BaseObjectST );

public:
  MockStageProvider() {}

  virtual int GetStageWidth() const { return 100; }
  virtual int GetStageHeight() const { return 100; }
  virtual void Invalidate() {}
};

class MockFontInstance : public flash::IFontInstance, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MockFontInstance, BaseObjectST );

public:
  MockFontInstance() {}

  virtual void RenderGlyph( wchar_t c, const flash::SWF_MATRIX & _matrix, const flash::SWF_RGBA & color ) {}
  virtual void RenderText( const wchar_t * text, unsigned length, const flash::SWF_MATRIX & _matrix, const flash::SWF_RGBA & color, const flash::SWF_RECT & ) {}
  virtual float GetStringLength( const wchar_t * text, unsigned length, float maxWidth, unsigned * charsFitIn, float additionalAdvance ) { if (charsFitIn) *charsFitIn = 10; return 10.f; };
  virtual float Height() const { return 10; } 
  virtual float Ascent() const { return 7; }
  virtual float Descent() const { return 1; }
  virtual float GapAbove() const { return 1; }
  virtual float GapUnder() const { return 1; }
  virtual float DefaultGlyphWidth() const { return 4; }
  virtual void SetBevel( bool _drawBevel, const flash::SWF_RGBA& _color ) {}
};

class MockFontRender : public flash::IFontRender, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MockFontInstance, BaseObjectST );

public:
  MockFontRender() {}
  virtual void SetViewport( int x, int y, int width, int height ) {}
  virtual void SetMovieRect( float x, float y, float width, float height ) {}
  virtual flash::IFontInstance * FindFont( const char * name, int height, bool bold, int italic, const flash::SFontMetricInfo * metric ) { return new MockFontInstance; }
  virtual void DebugLine( float x0, float y0, float x1, float y1, const flash::SWF_RGBA & color ) {};
};

namespace Render
{

class MockFlashRender : public IFlashRenderer, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MockFlashRender, BaseObjectST );

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

  virtual void SetFillStyleBitmap( IBitmapInfo* bi, const flash::SWF_MATRIX& m, EBitmapWrapMode::Enum wm, bool primary  ) {}

  virtual void DrawBitmap( IBitmapInfo* bi, float width, float height, int uniqueID, bool smoothing ) {}
  virtual void DrawBitmapScale9Grid( IBitmapInfo* bi, float width, float height, const flash::SWF_RECT& scale9Grid, float aspectX, float aspectY_, int uniqueID, bool smoothing ) {}

  virtual void DrawTriangleList( ShapeVertex* vertices, int count, int uniqueID ) {}
  virtual void DrawLineStrip( const nstl::vector<CVec2>& coords, int uniqueID ) {}

  virtual void DrawMeshStrip( const void* coords, int vertex_count, bool with_color, int unique_id, int submesh_id ){};

  virtual void SetLineWidth( float width ){};
  virtual void SetLineColor( const flash::SWF_RGBA& color ){};

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

  virtual IBitmapInfo* CreateBitmapInfoRgba( image::rgba* im, bool repeatable ) { return 0; }
  virtual IBitmapInfo* CreateLinearGradient( image::rgba* im, int& lineID, const char* fileName, unsigned short characterID, int gradientID, bool forLine ){ return 0; };
  virtual IBitmapInfo* CreateBitmapFromFile( const nstl::string& filename ){ return 0; };

  virtual void DebugNextBatch() {}

  virtual void SetMorph( float rate ) {}
  virtual void SetScale9Grid( const CVec4& constX, const CVec4& constY, const CVec4& trans ) {}
  virtual void ResetScale9Grid() {}
  virtual void BeginUnSubmitMask() {}
  virtual void RenderText( int _partID ) {}
  virtual void RenderTextBevel( bool withBevel, const flash::SWF_RGBA& color, Texture* fontTexture ) {}
  virtual IBitmapInfo* CreateGradientBitmap( const flash::SWF_GRADIENT& gradient ) { return 0; }
  virtual void ClearCaches() {}
};

}

struct FlashPlayerTests2 : public CxxTest::TestSuite 
{
private:
  void handleABCTest(flash::FlashMovieAvmCore * core ,const char * filename)
  {
    if (!filename) return;
   
    struct stat results;
    if (stat(filename, &results) != 0) 
    {
      TS_ASSERT(false);
      return;//err occurred
    }
    size_t bufSize = results.st_size;

    FILE * abcFile;
    fopen_s(&abcFile, filename,"rb");
    avmplus::ScriptBuffer code = core->newScriptBuffer(bufSize);
    fread(code.getBuffer(), 1, bufSize,abcFile);
    fclose(abcFile);

    if (avmplus::AbcParser::canParse(code) == 0) 
      core->RunActionBlock(code);
  }

  void TestActionFile(const char * filename)
  {
    flash::InitializeFlash();
    flash::Player* player = flash::Player::Get();
    player;

    {
      MMGC_ENTER_VOID;
      MMgc::GC* gc = mmfx_new( MMgc::GC(MMgc::GCHeap::GetGCHeap(), MMgc::GC::kIncrementalGC) );

      {
        MMGC_GCENTER( gc );

        Strong<MockStageProvider> stageProvider = new MockStageProvider();

        flash::Movie* flashMovie = new flash::Movie( stageProvider, gc, new MockFontRender, 0 );
        nstl::string abcFile = FlashCompiler::CompileActionFile(filename);
        TS_ASSERT(!abcFile.empty());

        handleABCTest(flashMovie->GetAvmCore(), abcFile.c_str());
        delete flashMovie;
      }

      mmfx_delete( gc );
    }

    flash::ReleaseFlash();
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

        Strong<MockStageProvider> stageProvider = new MockStageProvider();
        Strong<Render::MockFlashRender> renderer = new Render::MockFlashRender();

        flash::Movie * flashMovie = new flash::Movie( stageProvider, gc, new MockFontRender, 0 );

        flashMovie->SetFlashRenderer( renderer );
        flashMovie->SetViewport( 0, 0, 100, 100, 1 );
        flashMovie->LoadFile( swffile );

       /* for ( int i = 0 ; i < 100; ++i )
        {
          bool capture;
          flashMovie->OnMouseDown( UI::EMButton::Left, UI::Point(50,50), capture );
          flashMovie->Advance( 0.02f );
        }*/

        delete flashMovie;
      }

      mmfx_delete( gc );
    }

    flash::ReleaseFlash();
  }


public:

  virtual void setUpSuite()
  {
    NI_ASSERT(NSoundScene::InitWithCreatingSystem( 4000, 1.0f ), "sound was not initialized correctly");

    NSoundScene::SetVolume(1);
   
    /*for ( int i = 0; i < NDb::SoundRoot::GetRoot()->sceneScenes.size(); i++ )
      NSoundScene::InitSoundScene( i, NDb::SoundRoot::GetRoot()->sceneScenes[i] );
    NSoundScene::ActivateSoundScene( NDb::SOUNDSCENE_LOADING );
    NSoundScene::UpdateVolumes();*/
  }

  virtual void tearDownSuite()
  {
    NSoundScene::Release();
  }

  virtual void setUp()
  {
  }

  virtual void tearDown()
  {
  }
  
  void test_AsTests()
  {
    TestActionFile("DisplayObjectContainer.as");
    TestActionFile("EventPhases.as");
    TestActionFile("EventCtor.as");
    TestActionFile("Timer.as");
  }


  void test_CrushesTests()
  {
    TestActionFile("NoProperty.as");
  }

  void test_SWF0()
  {
    char* test[2048];

    int testNum = 983;

    for ( int i = 0; i < testNum; ++i )
    {
      test[i] = new char[1024 * 1024];

      for ( int j = 0; j < 1024 * 1024; ++j )
        test[i][j] = 0;
    }

    for ( int i = 0; i < 10; ++i )
    {
      TestSWF("ZZButton.swf");
      TestSWF("lightBox.swf");
      TestSWF("ZZButton.swf");
      TestSWF("lightBox.swf");
    }

    for ( int i = 0; i < testNum; ++i )
    {
      delete [] test[i];
    }
  }

  void test_SWF1()
  {
    //TestSWF("simpletext.swf");
  }

  void test_SWF2()
  {
    TestSWF("TestRemoveAt.swf");
  }

  void test_Flex()
  {
    //TestSWF("SimpleGraphicsTest.swf");
  }

  void test_LoadingPerformance()
  {
    /*NGlobal::SetVar( "profiler_enable", NGlobal::VariantValue( true), STORAGE_NONE );
    profiler::Pause(false);
    profiler::Frame();

    TestSWF("main.swf");

    profiler::Frame();
    profiler::Pause(true);
    vector<profiler::SFrameInfo> frames;
    int kb = profiler::MemoryUsage();
    kb;
    profiler::GetFrames(frames);

    for (int i= 0; i< frames.size(); i++)
    {
      CObj<profiler::CallGraphNode> graphNode = profiler::CollectCallGraph(frames[i].index);
      profiler::DumpCallgraph(graphNode);
    }*/
  }

  
};

//BASIC_REGISTER_CLASS( Render::IBitmapInfo );
//BASIC_REGISTER_CLASS( UI::FlashContainer2 );