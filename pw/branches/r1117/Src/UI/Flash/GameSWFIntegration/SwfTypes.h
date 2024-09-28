#pragma once

#define TWIPS_TO_PIXELS(x)	((x) / 20.f)
#define PIXELS_TO_TWIPS(x)	((x) * 20.f)

namespace  SWFTags
{
  enum SWFTagType
  {
    SWFTAGS_END = 0,
    SWFTAGS_SHOWFRAME = 1,
    SWFTAGS_DEFINESHAPE = 2,
    SWFTAGS_PLACEOBJECT = 4,
    SWFTAGS_REMOVEOBJECT = 5,
    SWFTAGS_DEFINEBITS = 6,
    SWFTAGS_DEFINEBUTTON = 7,
    SWFTAGS_JPEGTABLES = 8,
    SWFTAGS_SETBACKGROUNDCOLOR = 9,
    SWFTAGS_DEFINEFONT = 10,
    SWFTAGS_DEFINETEXT = 11,
    SWFTAGS_DOACTION = 12,
    SWFTAGS_DEFINEFONTINFO = 13,
    SWFTAGS_DEFINESOUND = 14,
    SWFTAGS_STARTSOUND = 15,
    SWFTAGS_DEFINEBUTTONSOUND = 17,
    SWFTAGS_SOUNDSTREAMHEAD = 18,
    SWFTAGS_SOUNDSTREAMBLOCK = 19,
    SWFTAGS_DEFINEBITSLOSSLESS = 20,
    SWFTAGS_DEFINEBITSJPEG2 = 21,
    SWFTAGS_DEFINESHAPE2 = 22,
    SWFTAGS_DEFINEBUTTONCXFORM = 23,
    SWFTAGS_PROTECT = 24,
    SWFTAGS_PLACEOBJECT2 = 26,
    SWFTAGS_REMOVEOBJECT2 = 28,
    SWFTAGS_DEFINESHAPE3 = 32,
    SWFTAGS_DEFINETEXT2 = 33,
    SWFTAGS_DEFINEBUTTON2 = 34,
    SWFTAGS_DEFINEBITSJPEG3 = 35,
    SWFTAGS_DEFINEBITSLOSSLESS2 = 36,
    SWFTAGS_DEFINEEDITTEXT = 37,
    SWFTAGS_DEFINESPRITE = 39,
    SWFTAGS_PRODUCTINFO = 41,
    SWFTAGS_FRAMELABEL = 43,
    SWFTAGS_SOUNDSTREAMHEAD2 = 45,
    SWFTAGS_DEFINEMORPHSHAPE = 46,
    SWFTAGS_DEFINEFONT2 = 48,
    SWFTAGS_EXPORTASSETS = 56,
    SWFTAGS_IMPORTASSETS = 57,
    SWFTAGS_ENABLEDEBUGGER = 58,
    SWFTAGS_DOINITACTION = 59,
    SWFTAGS_DEFINEVIDEOSTREAM = 60,
    SWFTAGS_VIDEOFRAME = 61,
    SWFTAGS_DEFINEFONTINFO2 = 62,
    SWFTAGS_DEBUGID = 63,
    SWFTAGS_ENABLEDEBUGGER2 = 64,
    SWFTAGS_SCRIPTLIMITS = 65,
    SWFTAGS_SETTABINDEX = 66,
    SWFTAGS_FILEATTRIBUTES = 69,
    SWFTAGS_PLACEOBJECT3 = 70,
    SWFTAGS_IMPORTASSETS2 = 71,
    SWFTAGS_DEFINEFONTALIGNZONES = 73,
    SWFTAGS_CSMTEXTSETTINGS = 74,
    SWFTAGS_DEFINEFONT3 = 75,
    SWFTAGS_SYMBOLCLASS = 76,
    SWFTAGS_METADATA = 77,
    SWFTAGS_DEFINESCALINGGRID = 78,
    SWFTAGS_DOABC = 82,
    SWFTAGS_DEFINESHAPE4 = 83,
    SWFTAGS_DEFINEMORPHSHAPE2 = 84,
    SWFTAGS_DEFINESCENEANDFRAMELABELDATA = 86,
    SWFTAGS_DEFINEBINARYDATA = 87,
    SWFTAGS_DEFINEFONTNAME = 88,
    SWFTAGS_STARTSOUND2 = 89,
    SWFTAGS_DEFINEBITSJPEG4 = 90,
    SWFTAGS_DEFINEFONT4 = 91,
  };

  const char *EnumToString( const SWFTagType value );
}

namespace gameswf
{
  struct matrix;
}

namespace Render
{
  _interface IFlashRenderer;
  _interface IBitmapInfo;
}


namespace flash
{

typedef unsigned int    UI32;
typedef unsigned short  UI16;
typedef unsigned char   UI8;

typedef int             SI32;
typedef short           SI16;
typedef char            SI8;

typedef float           FLOAT;
typedef double          DOUBLE;

typedef UI16            RECORDHEADER;

const static float      TWIP = 20.0f;

struct SWF_POINT
{
  float X;
  float Y;

  SWF_POINT() : X( 0 ), Y( 0 ) {}
  SWF_POINT( float x, float y ) : X( x ), Y( y ) {}
};

struct SWF_RECT
{
  float X1;
  float X2;
  float Y1;
  float Y2;

  float GetWidth() const { return X2 - X1; }
  float GetHeight() const { return Y2 - Y1; }

  SWF_POINT	GetCorner( int i ) const;

  void ExpandToPoint( const SWF_POINT& point );
  void ExpandToRect( const SWF_RECT& rect );

  bool PointTest( float x, float y ) const;

  void Lerp( const SWF_RECT& r1, const SWF_RECT& r2, float t );

  SWF_RECT() : X1( 0 ), X2( 0 ), Y1( 0 ), Y2( 0 ) {}
  SWF_RECT( float x1, float y1, float x2, float y2 ) : X1( x1 ), X2( x2 ), Y1( y1 ), Y2( y2 ) {}
};

struct TagInfo 
{
  SWFTags::SWFTagType tagType;
  int tagLen;
  uint parserPos;
};

struct SWFInfo
{
  SWF_RECT rect;

  int frameRate;
  int frameCount;

  uint swflen;
};

inline float flerp(float a, float b, float f) { return (b - a) * f + a; }

struct SWF_RGBA
{
	UI8 r;
	UI8 g;
	UI8 b;
	UI8 a;

  SWF_RGBA() : r( 0 ), g( 0 ), b( 0 ), a( 0 ) {}
  SWF_RGBA( UI8 _r, UI8 _g, UI8 _b, UI8 _a = 255 ) : r( _r ), g( _g ), b( _b ), a( _a ) {}
  explicit SWF_RGBA( UI32 i ) { SetUInt( i ); }

  void Lerp( const SWF_RGBA& c1, const SWF_RGBA& c2, float t )
  {
    r = (UI8) flerp(c1.r, c2.r, t);
    g = (UI8) flerp(c1.g, c2.g, t);
    b = (UI8) flerp(c1.b, c2.b, t);
    a = (UI8) flerp(c1.a, c2.a, t);
  }

  void SetUInt( UI32 i )
  {
    a = ( i & 0xff000000 ) >> 24;
    r = ( i & 0x00ff0000 ) >> 16;
    g = ( i & 0x0000ff00 ) >> 8;
    b = ( i & 0x000000ff );
  }

  UI32 GetUInt() const
  {
    return ( (UI32)a << 24 ) | ( (UI32)r << 16 ) | ( (UI32)g << 8 ) | b;
  }

  operator UI32() const { return GetUInt(); }
};

struct SWF_MATRIX
{
  SWF_MATRIX() 
  {
    Identity();
  }

  SWF_MATRIX( bool doNotInitialize ) {}

  void Identity()
  {
    m_[0][0] = 1;
    m_[1][1] = 1;
    m_[1][0] = 0;
    m_[0][1] = 0;
    m_[0][2] = 0;
    m_[1][2] = 0;
  }

  void Transform( SWF_POINT& result, const SWF_POINT& point ) const;
  void Transform( SWF_RECT& rect ) const; 

	void Concatenate( const SWF_MATRIX& m );
  void Concatenate( const SWF_MATRIX& m1, const SWF_MATRIX& m2 );
  void ConcatenateTranslation( float tx, float ty );
  void ConcatenateScale( float scale );
  void ConcatenateScale( float scaleX, float scaleY );
  void Lerp( const SWF_MATRIX& m1, const SWF_MATRIX& m2, float t );

  void SetInverse( const SWF_MATRIX& m );

  float	GetMaxScale() const;	// return the maximum scale factor that this transform applies

  float	GetDeterminant() const;
  float	GetXScale() const;
  float	GetYScale() const;
  float	GetRotation() const;
  void  SetScaleRotation( float x_scale, float y_scale, float angle );

  float m_[2][3];

  // m_[0][0] == ScaleX;
  // m_[1][1] == ScaleY;
  // m_[1][0] == RotateSkew0;
  // m_[0][1] == RotateSkew1;
  // m_[0][2] == TranslateX;
  // m_[1][2] == TranslateY;
};

__forceinline bool operator==( const SWF_MATRIX& matrix1, const SWF_MATRIX& matrix2 )
{
  return memcmp( &matrix1, &matrix2, sizeof( matrix1 ) ) == 0;
}

struct SWF_GRADRECORD
{
  UI8 Ratio;
  SWF_RGBA Color;

  bool operator < (const SWF_GRADRECORD& g) const
  {
    return Ratio < g.Ratio;
  }

  void Lerp( const SWF_GRADRECORD& g1, const SWF_GRADRECORD& g2, float t );
};

inline bool operator == ( const SWF_GRADRECORD&a , const SWF_GRADRECORD& b )
{
  return a.Ratio == b.Ratio && a.Color == b.Color;
}


namespace EGradientType
{
  enum Enum
  {
    Linear,
    Radial,
    Focal
  };
}

struct SWF_GRADIENT
{
  int SpreadMode;
  int InterpolationMode;
  int NumGradient;

  EGradientType::Enum type;

  nstl::vector<SWF_GRADRECORD> GradientRecords;

  float FocalPoint;

  SWF_GRADIENT() : 
    SpreadMode(0),
    InterpolationMode(0),
    NumGradient(0),
    FocalPoint(0.f),
    type(EGradientType::Linear)
  {}

  void Lerp( const SWF_GRADIENT& g1, const SWF_GRADIENT& g2, float t );
};

inline bool operator == ( const SWF_GRADIENT&a , const SWF_GRADIENT& b )
{
  return a.NumGradient == b.NumGradient && a.type == b.type && fabs(a.FocalPoint - b.FocalPoint) <FLT_EPSILON && 
      a.GradientRecords == b.GradientRecords;
}

class Movie;

struct SWF_FILLSTYLE
{
  SWF_FILLSTYLE() : invalid(true) {}

  UI8 FillStyleType;
  SWF_RGBA Color;
  SWF_MATRIX GradientMatrix;
  SWF_GRADIENT Gradient;
  UI16 BitmapId;
  SWF_MATRIX BitmapMatrix;

  Strong<Render::IBitmapInfo> bitmapInfo;

  bool IsColor() const { return (FillStyleType == 0x00); }
  bool IsGradient() const { return (FillStyleType == 0x10 || FillStyleType == 0x12 || FillStyleType == 0x13 ); }
  bool IsBitmap() const { return (FillStyleType >= 0x40 && FillStyleType <= 0x43); }

  void SetGradientType();

  void Apply( Render::IFlashRenderer* _renderer, Movie* _movie, bool primary );

  const SWF_MATRIX& GetBitmapMatrix( Movie* _movie );

  void Lerp( const SWF_FILLSTYLE& fs1, const SWF_FILLSTYLE& fs2, float t );

  void Invalidate() { invalid = true; }

private:

  bool invalid;
  SWF_MATRIX CachedBitmapMatrix; 
  Strong<Render::IBitmapInfo> cachedInfo;
};

struct SWF_LINESTYLE2
{
  UI16 Width;
  int StartCapStyle;
  int JointStyle;
  bool HasFillFlag;
  bool NoHScaleFlag;
  bool NoVScaleFlag;
  bool PixelHintingFlag;
  bool NoClose;
  int EndCapStyle;
  UI16 MiterLimitFactor;
  SWF_RGBA Color;
  SWF_FILLSTYLE FillType;

  SWF_LINESTYLE2() :
    Width(1),
    StartCapStyle(0),
    JointStyle(0),
    HasFillFlag(false),
    NoHScaleFlag(false),
    NoVScaleFlag(false),
    PixelHintingFlag(false),
    NoClose(false),
    EndCapStyle(0),
    MiterLimitFactor(0)
  {}

  void Lerp( const SWF_LINESTYLE2& ls1, const SWF_LINESTYLE2& ls2, float t );

  void Apply( Render::IFlashRenderer* _renderer, Movie* _movie );
  void ApplyMorph( Render::IFlashRenderer* _renderer, SWF_LINESTYLE2& other, Movie* _movie, float rate );
};

typedef nstl::vector<SWF_FILLSTYLE> FillStyles;
typedef nstl::vector<SWF_LINESTYLE2> LineStyles;

struct SWF_SHAPERECORD
{
  bool IsFunctional()
  {
    return edgeRecord ||
      StateNewStyles ||
      StateLineStyle ||
      StateFillStyle1 ||
      StateFillStyle0 ||
      StateMoveTo;
  }

  bool edgeRecord;

  // StateRecord
  bool StateNewStyles;
  bool StateLineStyle;
  bool StateFillStyle1;
  bool StateFillStyle0;
  bool StateMoveTo;

  SI32 MoveDeltaX;
  SI32 MoveDeltaY;

  unsigned int FillStyle1;
  unsigned int FillStyle0;
  unsigned int LineStyle;

  //Edge record
  bool StraightFlag;

  int DeltaX;
  int DeltaY;

  int ControlDeltaX;
  int ControlDeltaY;
  int AnchorDeltaX;
  int AnchorDeltaY;

  void Lerp( const SWF_SHAPERECORD& sh1, const SWF_SHAPERECORD& sh2, float t );

  SWF_SHAPERECORD() :
    edgeRecord(false),
    StateNewStyles(false),
    StateLineStyle(false),
    StateFillStyle1(false),
    StateFillStyle0(false),
    StateMoveTo(false),
    MoveDeltaX(0),
    MoveDeltaY(0),
    FillStyle1(0),
    FillStyle0(0),
    LineStyle(0),
    StraightFlag(false),
    DeltaX(0),
    DeltaY(0),
    ControlDeltaX(0),
    ControlDeltaY(0),
    AnchorDeltaX(0),
    AnchorDeltaY(0)
  {

  }
};

struct SWF_CXFORMWITHALPHA
{
  float	m_[4][2];	// [RGBA][mult, add]

  SWF_CXFORMWITHALPHA()
  {
    for ( int i = 0; i < 4; ++i )
    {
      m_[i][0] = 1.f; // mult
      m_[i][1] = 0.f; // add
    }
  }

  SWF_CXFORMWITHALPHA( bool doNotInitialize ) {}

  void Transform( SWF_RGBA& result, const SWF_RGBA& source ) const;
  void Concatenate( const SWF_CXFORMWITHALPHA& c1, const SWF_CXFORMWITHALPHA& c2 );
};

__forceinline bool operator==( const SWF_CXFORMWITHALPHA& cxform1, const SWF_CXFORMWITHALPHA& cxform2 )
{
  return memcmp( &cxform1, &cxform2, sizeof( cxform1 ) ) == 0;
}

} // flash
