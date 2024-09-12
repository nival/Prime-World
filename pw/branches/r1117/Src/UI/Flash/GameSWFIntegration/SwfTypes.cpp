#include "TamarinPCH.h"

#include <Render/FlashRendererInterface.h>

#include "Image.h"
#include "SwfTypes.h"
#include "FlashMovie.h"
#include "Characters.h"

namespace flash
{

SWF_POINT	SWF_RECT::GetCorner( int i ) const
{
  NI_ASSERT( i >= 0 && i < 4, "Wrong corner id" );

  return SWF_POINT(
    (i == 0 || i == 3) ? X1 : X2,
    (i < 2) ? Y1 : Y2);
}

void SWF_RECT::ExpandToPoint( const SWF_POINT& point )
{
  X1 = min( X1, point.X );
  Y1 = min( Y1, point.Y );

  X2 = max( X2, point.X);
  Y2 = max( Y2, point.Y );
}

void SWF_RECT::ExpandToRect( const SWF_RECT& rect )
{
  ExpandToPoint( SWF_POINT( rect.X1, rect.Y1 ) );
  ExpandToPoint( SWF_POINT( rect.X2, rect.Y2 ) );
}

bool SWF_RECT::PointTest( float x, float y ) const
{
  return  ( X1 <= x && x <= X2 && Y1 <= y && y <= Y2 );
}

void SWF_RECT::Lerp( const SWF_RECT& r1, const SWF_RECT& r2, float t )
{
  X1 = flerp(r1.X1, r2.X1, t);
  X2 = flerp(r1.X2, r2.X2, t);
  Y1 = flerp(r1.Y1, r2.Y1, t);
  Y2 = flerp(r1.Y2, r2.Y2, t);
}

void SWF_MATRIX::Transform( SWF_POINT& result, const SWF_POINT& point ) const
{
  result.X = m_[0][0] * point.X + m_[0][1] * point.Y + m_[0][2];
  result.Y = m_[1][0] * point.X + m_[1][1] * point.Y + m_[1][2];
}

void SWF_MATRIX::Transform( SWF_RECT& rect ) const
{
  SWF_POINT transformed[4];
  Transform( transformed[0], rect.GetCorner(0) );
  Transform( transformed[1], rect.GetCorner(1) );
  Transform( transformed[2], rect.GetCorner(2) );
  Transform( transformed[3], rect.GetCorner(3) );

  // Build bound that covers transformed bound

  rect.X1 = rect.X2 = transformed[0].X; 
  rect.Y1 = rect.Y2 = transformed[0].Y; 

  rect.ExpandToPoint( transformed[1] );
  rect.ExpandToPoint( transformed[2] );
  rect.ExpandToPoint( transformed[3] );
}

void SWF_MATRIX::Concatenate( const SWF_MATRIX& m )
{
  SWF_MATRIX	t;

  t.m_[0][0] = m_[0][0] * m.m_[0][0] + m_[0][1] * m.m_[1][0];
  t.m_[1][0] = m_[1][0] * m.m_[0][0] + m_[1][1] * m.m_[1][0];
  t.m_[0][1] = m_[0][0] * m.m_[0][1] + m_[0][1] * m.m_[1][1];
  t.m_[1][1] = m_[1][0] * m.m_[0][1] + m_[1][1] * m.m_[1][1];
  t.m_[0][2] = m_[0][0] * m.m_[0][2] + m_[0][1] * m.m_[1][2] + m_[0][2];
  t.m_[1][2] = m_[1][0] * m.m_[0][2] + m_[1][1] * m.m_[1][2] + m_[1][2];

  *this = t;
}

void SWF_MATRIX::Concatenate( const SWF_MATRIX& m1, const SWF_MATRIX& m2 )
{
  m_[0][0] = m1.m_[0][0] * m2.m_[0][0] + m1.m_[0][1] * m2.m_[1][0];
  m_[1][0] = m1.m_[1][0] * m2.m_[0][0] + m1.m_[1][1] * m2.m_[1][0];
  m_[0][1] = m1.m_[0][0] * m2.m_[0][1] + m1.m_[0][1] * m2.m_[1][1];
  m_[1][1] = m1.m_[1][0] * m2.m_[0][1] + m1.m_[1][1] * m2.m_[1][1];
  m_[0][2] = m1.m_[0][0] * m2.m_[0][2] + m1.m_[0][1] * m2.m_[1][2] + m1.m_[0][2];
  m_[1][2] = m1.m_[1][0] * m2.m_[0][2] + m1.m_[1][1] * m2.m_[1][2] + m1.m_[1][2];
}

void	SWF_MATRIX::ConcatenateTranslation( float tx, float ty )
{
  m_[0][2] += m_[0][0] * tx + m_[0][1] * ty;
  m_[1][2] += m_[1][0] * tx + m_[1][1] * ty;
}

void SWF_MATRIX::ConcatenateScale( float scale )
{
  m_[0][0] *= scale;
  m_[0][1] *= scale;
  m_[1][0] *= scale;
  m_[1][1] *= scale;
}

void SWF_MATRIX::ConcatenateScale( float scaleX, float scaleY )
{
  m_[0][0] *= scaleX;
  m_[0][1] *= scaleY;
  m_[1][0] *= scaleX;
  m_[1][1] *= scaleY;
}

void SWF_MATRIX::Lerp( const SWF_MATRIX& m1, const SWF_MATRIX& m2, float t )
{
  m_[0][0] = flerp(m1.m_[0][0], m2.m_[0][0], t);
  m_[1][0] = flerp(m1.m_[1][0], m2.m_[1][0], t);
  m_[0][1] = flerp(m1.m_[0][1], m2.m_[0][1], t);
  m_[1][1] = flerp(m1.m_[1][1], m2.m_[1][1], t);
  m_[0][2] = flerp(m1.m_[0][2], m2.m_[0][2], t);
  m_[1][2] = flerp(m1.m_[1][2], m2.m_[1][2], t);
}

void SWF_MATRIX::SetInverse( const SWF_MATRIX& m )
{
  NI_ASSERT( this != &m, "Try to invert matrix to the same matrix" );

  float	det = m.m_[0][0] * m.m_[1][1] - m.m_[0][1] * m.m_[1][0];

  if (det == 0.0f)
  {
    Identity();
    m_[0][2] = -m.m_[0][2];
    m_[1][2] = -m.m_[1][2];
  }
  else
  {
    float	inv_det = 1.0f / det;
    m_[0][0] = m.m_[1][1] * inv_det;
    m_[1][1] = m.m_[0][0] * inv_det;
    m_[0][1] = -m.m_[0][1] * inv_det;
    m_[1][0] = -m.m_[1][0] * inv_det;

    m_[0][2] = -(m_[0][0] * m.m_[0][2] + m_[0][1] * m.m_[1][2]);
    m_[1][2] = -(m_[1][0] * m.m_[0][2] + m_[1][1] * m.m_[1][2]);
  }
}

float	SWF_MATRIX::GetMaxScale() const
{
  float	basis0_length2 = m_[0][0] * m_[0][0] + m_[0][1] * m_[0][1];
  float	basis1_length2 = m_[1][0] * m_[1][0] + m_[1][1] * m_[1][1];
  float	max_length2 = max(basis0_length2, basis1_length2);
  return sqrtf(max_length2);
}

float	SWF_MATRIX::GetDeterminant() const
{
  return m_[0][0] * m_[1][1] - m_[1][0] * m_[0][1];
}

float	SWF_MATRIX::GetXScale() const
{
  float scale = sqrtf(m_[0][0] * m_[0][0] + m_[1][0] * m_[1][0]);

  // Are we turned inside out?
  if ( GetDeterminant() < 0.f )
  {
    scale = -scale;
  }

  return scale;
}

float SWF_MATRIX::GetYScale() const
{
  return sqrtf( m_[1][1] * m_[1][1] + m_[0][1] * m_[0][1] );
}

float SWF_MATRIX::GetRotation() const
{
  if (GetDeterminant() < 0.f)
  {
    // We're turned inside out; negate the
    // x-component used to compute rotation.
    //
    // Matches get_x_scale().
    //
    // @@ this may not be how Macromedia does it!  Test this!
    return atan2f(m_[1][0], -m_[0][0]);
  }
  else
  {
    return atan2f(m_[1][0], m_[0][0]);
  }
}

void SWF_MATRIX::SetScaleRotation( float x_scale, float y_scale, float angle )
{
  float	cos_angle = cosf(angle);
  float	sin_angle = sinf(angle);
  m_[0][0] = x_scale * cos_angle;
  m_[0][1] = y_scale * -sin_angle;
  m_[1][0] = x_scale * sin_angle;
  m_[1][1] = y_scale * cos_angle;
}

void SWF_FILLSTYLE::SetGradientType()
{
  switch( FillStyleType )
  {
  case 0x10: Gradient.type = EGradientType::Linear; break; 
  case 0x12: Gradient.type = EGradientType::Radial; break;  
  case 0x13: Gradient.type = EGradientType::Focal; break; 
  }
}

void SWF_FILLSTYLE::Apply( Render::IFlashRenderer* _renderer, Movie* _movie, bool primary )
{
  if ( IsGradient() )
  {
    // 0x10: linear gradient fill
    // 0x12: radial gradient fill

    if ( !bitmapInfo )
    {
      bitmapInfo = _renderer->CreateGradientBitmap( Gradient );
    }

    if ( bitmapInfo )
    {
      const SWF_MATRIX& gradientMatrix = GetBitmapMatrix( _movie );
      _renderer->SetFillStyleBitmap( bitmapInfo, gradientMatrix, EBitmapWrapMode::CLAMP, primary );
    }
  }
  else if ( IsBitmap() )
  {
    if ( !bitmapInfo )
    {
      BitmapCharacter* character =  _movie->GetBitmapCharacter( BitmapId );

      if ( character )
        bitmapInfo = character->GetImageData().GetBitmapInfo();
    }

    if ( bitmapInfo )
    {
      const SWF_MATRIX& bitmapMatrix = GetBitmapMatrix( _movie );

      switch ( FillStyleType )
      {
      case 0x40 :
      case 0x42 :
        _renderer->SetFillStyleBitmap( bitmapInfo, bitmapMatrix,  EBitmapWrapMode::REPEAT, primary );
        break;

      case 0x41 :
      case 0x43 :
        _renderer->SetFillStyleBitmap( bitmapInfo, bitmapMatrix, EBitmapWrapMode::CLAMP, primary );
        break;
      }
    }
  }
}

const SWF_MATRIX& SWF_FILLSTYLE::GetBitmapMatrix( Movie* _movie )
{
  //if ( invalid )
  {
    if ( IsGradient() )
    {
      if ( invalid )
      {
        if ( FillStyleType == 0x10 )
        {
          NI_ASSERT( bitmapInfo, "Gradient bitmap is null" );

          CachedBitmapMatrix.Identity();
          CachedBitmapMatrix.ConcatenateTranslation( 128.f, 0.5f );

          CachedBitmapMatrix.m_[0][0] *= 1.0f / 128.0f;
          CachedBitmapMatrix.m_[0][1] *= 0.f;
          CachedBitmapMatrix.m_[1][0] *= 1.0f / 128.0f;
          CachedBitmapMatrix.m_[1][1] *= 0.f;
        }
        else 
        {
          CachedBitmapMatrix.Identity();
          CachedBitmapMatrix.ConcatenateTranslation( 32.f, 32.f );
          CachedBitmapMatrix.ConcatenateScale( 1.0f / 512.0f );
        }

        SWF_MATRIX m;
        m.SetInverse( GradientMatrix );
        CachedBitmapMatrix.Concatenate( m );

        float inv_width = 1.0f / ( FillStyleType == 0x10 ? 256.f : 64.f );
        float inv_height = 1.0f / ( FillStyleType == 0x10 ? 256.f : 64.f );

        CachedBitmapMatrix.m_[0][0] *= inv_width;  CachedBitmapMatrix.m_[1][0] *= inv_height;
        CachedBitmapMatrix.m_[0][1] *= inv_width;  CachedBitmapMatrix.m_[1][1] *= inv_height;
        CachedBitmapMatrix.m_[0][2] *= inv_width;  CachedBitmapMatrix.m_[1][2] *= inv_height;

        invalid = false;
      }
    }
    else
    {
      BitmapCharacter* character =  _movie->GetBitmapCharacter( BitmapId );

      if ( character )
      {
        Render::IBitmapInfo* bitmap = character->GetImageData().GetBitmapInfo();

        if ( bitmap != cachedInfo || invalid )
        {
          CachedBitmapMatrix.SetInverse( BitmapMatrix );

          float inv_width = 1.0f / bitmap->GetWidth();
          float inv_height = 1.0f / bitmap->GetHeight();

          CachedBitmapMatrix.m_[0][0] *= inv_width;  CachedBitmapMatrix.m_[1][0] *= inv_height;
          CachedBitmapMatrix.m_[0][1] *= inv_width;  CachedBitmapMatrix.m_[1][1] *= inv_height;
          CachedBitmapMatrix.m_[0][2] *= inv_width;  CachedBitmapMatrix.m_[1][2] *= inv_height;

          float scaleU = bitmap->GetUV2().x - bitmap->GetUV1().x;
          float scaleV = bitmap->GetUV2().y - bitmap->GetUV1().y;

          SWF_MATRIX atlasScale;

          atlasScale.Identity();
          atlasScale.ConcatenateTranslation( bitmap->GetUV1().x, bitmap->GetUV1().y );
          atlasScale.ConcatenateScale( scaleU, scaleV );
          atlasScale.Concatenate( CachedBitmapMatrix );

          CachedBitmapMatrix = atlasScale;

          invalid = false;
          cachedInfo = bitmap;
        }
      }
    }
  }

  return CachedBitmapMatrix;
}

void SWF_FILLSTYLE::Lerp( const SWF_FILLSTYLE& fs1, const SWF_FILLSTYLE& fs2, float t )
{
  FillStyleType = fs1.FillStyleType;

  if ( fs1.IsColor() && fs2.IsColor() )
    Color.Lerp( fs1.Color, fs2.Color, t );
  else if ( fs1.IsColor() && !fs2.IsColor() )
    Color = fs1.Color;
  else if ( !fs1.IsColor() && fs2.IsColor() )
    Color = fs2.Color;

  GradientMatrix.Lerp( fs1.GradientMatrix, fs2.GradientMatrix, t ) ;
  Gradient.Lerp( fs1.Gradient, fs2.Gradient, t ) ;
  BitmapId = fs1.BitmapId;
  BitmapMatrix.Lerp( fs1.BitmapMatrix, fs2.BitmapMatrix, t ) ;

  bitmapInfo = fs1.bitmapInfo;
}

void SWF_CXFORMWITHALPHA::Transform( SWF_RGBA& result, const SWF_RGBA& source ) const
{
  result.r = (UI8) Clamp(source.r * m_[0][0] + m_[0][1], 0.f, 255.f);
  result.g = (UI8) Clamp(source.g * m_[1][0] + m_[1][1], 0.f, 255.f);
  result.b = (UI8) Clamp(source.b * m_[2][0] + m_[2][1], 0.f, 255.f);
  result.a = (UI8) Clamp(source.a * m_[3][0] + m_[3][1], 0.f, 255.f);
}

void SWF_CXFORMWITHALPHA::Concatenate( const SWF_CXFORMWITHALPHA& c1, const SWF_CXFORMWITHALPHA& c2 )
{
  m_[0][1] = c1.m_[0][1] + c1.m_[0][0] * c2.m_[0][1];
  m_[1][1] = c1.m_[1][1] + c1.m_[1][0] * c2.m_[1][1];
  m_[2][1] = c1.m_[2][1] + c1.m_[2][0] * c2.m_[2][1];
  m_[3][1] = c1.m_[3][1] + c1.m_[3][0] * c2.m_[3][1];

  m_[0][0] = c1.m_[0][0] * c2.m_[0][0];
  m_[1][0] = c1.m_[1][0] * c2.m_[1][0];
  m_[2][0] = c1.m_[2][0] * c2.m_[2][0];
  m_[3][0] = c1.m_[3][0] * c2.m_[3][0];
}

void SWF_LINESTYLE2::Apply( Render::IFlashRenderer* _renderer, Movie* _movie )
{
  _renderer->SetLineWidth( Width );
  _renderer->SetLineColor( Color );

  if ( HasFillFlag )
    FillType.Apply( _renderer, _movie, true );
}

void SWF_LINESTYLE2::ApplyMorph( Render::IFlashRenderer* _renderer, SWF_LINESTYLE2& other, Movie* _movie, float rate )
{
  _renderer->SetLineWidth( (UI16)flerp( Width, other.Width, rate ) );

  if ( HasFillFlag && other.HasFillFlag )
  {
    FillType.Apply( _renderer, _movie, true );
    other.FillType.Apply( _renderer, _movie, false );
  }

  flash::SWF_RGBA color;
  color.Lerp( Color, other.Color, rate );

  _renderer->SetLineColor( color );
}

void SWF_LINESTYLE2::Lerp( const SWF_LINESTYLE2& ls1, const SWF_LINESTYLE2& ls2, float t )
{
  Width = (UI16)flerp( ls1.Width, ls2.Width, t );

  StartCapStyle = ls1.StartCapStyle;
  JointStyle = ls1.JointStyle;
  HasFillFlag = ls1.HasFillFlag;
  NoHScaleFlag = ls1.NoHScaleFlag;
  NoVScaleFlag = ls1.NoVScaleFlag;
  PixelHintingFlag = ls1.PixelHintingFlag;
  NoClose = ls1.NoClose;
  EndCapStyle = ls1.EndCapStyle;
  MiterLimitFactor = ls1.MiterLimitFactor;

  Color.Lerp( ls1.Color, ls2.Color, t );
  FillType.Lerp( ls1.FillType, ls2.FillType, t );
}

void SWF_GRADRECORD::Lerp( const SWF_GRADRECORD& g1, const SWF_GRADRECORD& g2, float t )
{ 
  Ratio = (UI8) flerp( g1.Ratio, g2.Ratio, t );
  Color.Lerp( g1.Color, g2.Color, t );
}

void SWF_GRADIENT::Lerp( const SWF_GRADIENT& g1, const SWF_GRADIENT& g2, float t )
{
  NI_ASSERT( g1.GradientRecords.size() == g2.GradientRecords.size(), "Size of GradientRecords should be equal" );

  NumGradient = g1.NumGradient;
  SpreadMode = g1.SpreadMode;
  InterpolationMode = g1.InterpolationMode;
  type = g1.type;

  GradientRecords.resize( NumGradient );

  for ( int i = 0; i < NumGradient; ++i )
  {
    GradientRecords[ i ].Lerp( g1.GradientRecords[ i ], g2.GradientRecords[ i ], t );
  }

  FocalPoint = flerp( g1.FocalPoint, g2.FocalPoint, t );
}

void SWF_SHAPERECORD::Lerp( const SWF_SHAPERECORD& sh1, const SWF_SHAPERECORD& sh2, float t )
{
  edgeRecord = sh1.edgeRecord;

  StateNewStyles = sh1.StateNewStyles;
  StateLineStyle = sh1.StateLineStyle;
  StateMoveTo = sh1.StateMoveTo;

  MoveDeltaX = (SI32) flerp( sh1.MoveDeltaX, sh2.MoveDeltaX, t );
  MoveDeltaY = (SI32) flerp( sh1.MoveDeltaY, sh2.MoveDeltaY, t );

  // Swap fill styles -- for some reason, morph
  // shapes seem to be defined with their fill
  // styles backwards!
  StateFillStyle1 = sh1.StateFillStyle0;
  StateFillStyle0 = sh1.StateFillStyle1;
  FillStyle1 = sh1.FillStyle0;
  FillStyle0 = sh1.FillStyle1;

  LineStyle = sh1.LineStyle;

  StraightFlag = false; //sh1.StraightFlag;

  if ( sh1.StraightFlag && sh2.StraightFlag )
  {
    StraightFlag = true;
    DeltaX = (int) flerp( sh1.DeltaX, sh2.DeltaX, t );
    DeltaY = (int) flerp( sh1.DeltaY, sh2.DeltaY, t );
  }
  else
  {
    StraightFlag = false;
    int ControlDeltaX1 = sh1.StraightFlag ? ceil( float( sh1.DeltaX ) / 2.f ) : sh1.ControlDeltaX;
    int ControlDeltaY1 = sh1.StraightFlag ? ceil( float( sh1.DeltaY ) / 2.f ) : sh1.ControlDeltaY;
    int ControlDeltaX2 = sh2.StraightFlag ? ceil( float( sh2.DeltaX ) / 2.f ) : sh2.ControlDeltaX;
    int ControlDeltaY2 = sh2.StraightFlag ? ceil( float( sh2.DeltaY ) / 2.f ) : sh2.ControlDeltaY;

    int AnchorDeltaX1 = sh1.StraightFlag ? ceil( float( sh1.DeltaX ) / 2.f ) : sh1.AnchorDeltaX;
    int AnchorDeltaY1 = sh1.StraightFlag ? ceil( float( sh1.DeltaY ) / 2.f ) : sh1.AnchorDeltaY;
    int AnchorDeltaX2 = sh2.StraightFlag ? ceil( float( sh2.DeltaX ) / 2.f ) : sh2.AnchorDeltaX;
    int AnchorDeltaY2 = sh2.StraightFlag ? ceil( float( sh2.DeltaY ) / 2.f ) : sh2.AnchorDeltaY;

    ControlDeltaX = (int) flerp( ControlDeltaX1, ControlDeltaX2, t );
    ControlDeltaY = (int) flerp( ControlDeltaY1, ControlDeltaY2, t );
    AnchorDeltaX = (int) flerp( AnchorDeltaX1, AnchorDeltaX2, t );
    AnchorDeltaY = (int) flerp( AnchorDeltaY1, AnchorDeltaY2, t );
  }
}


} // FlashMovie
