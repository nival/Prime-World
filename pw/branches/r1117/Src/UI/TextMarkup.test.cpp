//!Component('System/Dumpers')
//!Component('UI/TextMarkup')

#include "cxxtest/TestSuite.h"
#include "System/systemStdAfx.h"
#include "System/nstring.h"
#include "System/DebugTraceDumper.h"
#include "UI/TextMarkup.h"


class MockTextImage : public NMarkup::IImage, public CObjectBase
{
  OBJECT_BASIC_METHODS( MockTextImage );

public:
  MockTextImage() {}
  virtual void RenderImage( const NMarkup::TPoint & offset, const NMarkup::TPoint & size ) {}
};


class MockTextStyle : public NMarkup::IStyle, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MockTextStyle, BaseObjectST );

public:
  MockTextStyle() {}

  virtual NMarkup::TOffset GetTextBounds( NMarkup::SBounds * bounds, const NMarkup::TChar * text, NMarkup::TOffset length, NMarkup::TUnit maxWidth ) const
  {
    bounds->width = (NMarkup::TUnit)( length * 12.0f );
    bounds->ascent = (NMarkup::TUnit)( 25.0f );
    bounds->descent = (NMarkup::TUnit)( 3.0f );
    bounds->gapAbove = (NMarkup::TUnit)( 1.0f );
    bounds->gapUnder = (NMarkup::TUnit)( 1.0f );
    return length;
  }
  virtual void GetDefaultBounds( NMarkup::SBounds * bounds ) const { return; }
  virtual NMarkup::TUnit DefaultGlyphWidth() const { return (NMarkup::TUnit)10.0f; }
  virtual NMarkup::TUnit DefaultLineGap() const { return (NMarkup::TUnit)30.0f; }
  virtual NMarkup::TUnit VisualHeight() const { return (NMarkup::TUnit)25.0f; }
  virtual void RenderText( const NMarkup::SBounds & bounds, const NMarkup::TPoint & offset, const NMarkup::TChar * text, NMarkup::TOffset length )
  {
  }
};


class MockUiRender : public NMarkup::IUiRender, public CObjectBase
{
  OBJECT_BASIC_METHODS( MockUiRender );

  Strong<MockTextStyle> styleMock;
  CObj<MockTextImage> imageMock;
public:
  MockUiRender()
  {
    styleMock = new MockTextStyle;
    imageMock = new MockTextImage;
  }
  virtual NMarkup::IStyle * GetStyle( const NMarkup::TChar * style ) { return styleMock; }
  virtual NMarkup::IImage * CreateImage( NMarkup::TPoint * size, const NMarkup::TChar * image ) { return imageMock; }
};



struct FlashPlayerTests : public CxxTest::TestSuite 
{
private:
  CObj<MockUiRender> uiRender;

public:

  virtual void setUp()
  {
    uiRender = new MockUiRender;
  }
  virtual void tearDown()
  {
    uiRender = 0;
  }
  
  void test_basic()
  {
    NMarkup::TextMarkup markup;
    markup.Process( L"first  line\n", uiRender, NMarkup::TPoint( (NMarkup::TUnit)200.0, (NMarkup::TUnit)100.0 ), 0 );

    TS_ASSERT( markup.LinesCount() == 1 );
    TS_ASSERT( markup.ElementsCount() == 2 );

    NMarkup::TPoint minPt, maxPt;
    NMarkup::TOffset start = 0, length = 0;
    markup.GetLineInfo( 0, minPt, maxPt, start, length, 0 );

    TS_ASSERT( length == 11 );
    TS_ASSERT( start == 0 );
  }

  void test_raw_mode()
  {
    NMarkup::TextMarkup markup;
    markup.CondenseWhite( false );
    markup.EnableTags( true );
    markup.Process( L"line1<br>\nline2<br>", uiRender, NMarkup::TPoint( (NMarkup::TUnit)200.0, (NMarkup::TUnit)100.0 ), 0 );

    TS_ASSERT_EQUALS( markup.LinesCount(), 4 );
    TS_ASSERT_EQUALS( markup.ElementsCount(), 4 );

    NMarkup::TPoint minPt, maxPt;
    NMarkup::TOffset start = 0, length = 0;

    markup.GetLineInfo( 3, minPt, maxPt, start, length, 0 );
    TS_ASSERT( start == 15 );
    TS_ASSERT( length == 0 );

    markup.GetLineInfo( 2, minPt, maxPt, start, length, 0 );
    TS_ASSERT( start == 10 );
    TS_ASSERT( length == 5 );
  }
};

