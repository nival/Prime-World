#include "TamarinPCH.h"

#include "SwfStreamReader.h"

#include <System\Math\ieeehalfprecision.h>
#include "FlashMovie.h"

namespace flash
{

SwfStreamReader::SwfStreamReader( Movie& _movie ) : 
  bitPos(0),
  bitBuf(0),
  pos(0),
  movie(_movie)
{

}

void SwfStreamReader::SetStreamBuffer( avmplus::ScriptBuffer swf )
{
  this->swf = swf;
}
 
void SwfStreamReader::SetPos( uint32_t _newPos )
{
  NI_ASSERT( _newPos < swf.getSize(), "Wrong SWF position" );
  pos = _newPos;
}

// UI16 SwfStreamReader::readUI16() 
// { 
// //  NI_ASSERT( pos + 2 < swf.getSize(), "SWF file buffer overrun" ); 
//   UI16 result = *((UI16*)&swf[pos]);
//   pos += 2;
//   return result; 
// }
// 
// UI32 SwfStreamReader::readUI32() 
// { 
//   //NI_ASSERT( pos < swf.getSize(), "SWF file buffer overrun" ); 
//   UI32 result = *((UI32*)&swf[pos]);
//   pos += 4;
//   return result; 
// }

UI16 SwfStreamReader::swapUI16( UI16 u )
{
  return  ((u & 0x00FF) << 8) | 
          ((u & 0xFF00) >> 8);
}

UI32 SwfStreamReader::swapUI32( UI32 u )
{ 
  return  ((u & 0x000000FF) << 24) | 
          ((u & 0x0000FF00) << 8)  |
          ((u & 0x00FF0000) >> 8)  |
          ((u & 0xFF000000) >> 24);
}

float SwfStreamReader::readFoat16()
{
  UI16 val = readUI16();
  float result = 0;
  int err = halfp2singles( &result, &val, 1 );
  NI_ASSERT( err == 0, "" );
  return result;
}

float	SwfStreamReader::readFixed()
{
  SI32 val = readLEUI32();
  return (float) val / 65536.0f;
}

float SwfStreamReader::readFixed8()
{
  UI8 val2 = readUI8();
  UI8 _val = readUI8();
  SI8 val;
  memcpy(&val, &_val, sizeof(SI8));
  return float( val ) + float( val2 ) / 256.0f;
}

float SwfStreamReader::readFloat()
{
  UI32 val = readLEUI32();
  float f;
  memcpy(&f, &val, sizeof(float));
  return f;
}

void SwfStreamReader::skipHeader()
{
  // skip rect
  int n = readUBits(5);
  readUBits(n); // xmin
  readUBits(n); // xmax
  readUBits(n); // ymin
  readUBits(n); // ymax

  // skip frame rate and frame count
  NI_ASSERT( pos + 4 <= swf.getSize(), "SWF file buffer overrun" );
  pos += 4;
}

void SwfStreamReader::readTagInfo( TagInfo& tagInfo )
{
  int tag = readUI16();
  int type = tag >> 6;
  uint32_t taglen = (tag & 63);

  if (taglen == 63)
    taglen = readUI32();

  tagInfo.tagLen = taglen;
  tagInfo.tagType = (SWFTags::SWFTagType)type;
  tagInfo.parserPos = pos;
}

UI32 SwfStreamReader::readUI32Encoded()
{
  unsigned int result = readUI8();

  if (!(result & 0x00000080))
  {
    return result;
  }
  result = (result & 0x0000007f) | readUI8() << 7;
  if (!(result & 0x00004000))
  {
    return result;
  }
  result = (result & 0x00003fff) | readUI8() << 14;
  if (!(result & 0x00200000))
  {
    return result;
  }
  result = (result & 0x001fffff) | readUI8() << 21;
  if (!(result & 0x10000000))
  {
    return result;
  }
  result = (result & 0x0fffffff) | readUI8() << 28;
  return result;
}

void SwfStreamReader::fillBitBuf()
{
  bitBuf = readUI8();
  bitPos = 8;
}

UI32 SwfStreamReader::readUBits( int n )
{
  if ( n == 0 )
    return 0;

  int bitsLeft = n;
  UI32 result = 0;

  if ( bitPos == 0 )
    fillBitBuf();

  int shift;

  for ( shift = bitsLeft - bitPos; shift > 0; shift = bitsLeft - bitPos ) 
  {
    result |= bitBuf << shift;
    bitsLeft -= bitPos;
    fillBitBuf();
  }

  // consume part of buffer
  result |= bitBuf >> -shift;
  bitPos -= bitsLeft;
  bitBuf &= 0xff >> (8 - bitPos); // mask consumed bits

  return result;
}

SI32 SwfStreamReader::readSBits( int n )
{
  //AvmAssert(n <= 32);
  UI32 num = readUBits(n);
  int shift = 32 - n;
  return ( (SI32)( num << shift ) ) >> shift; // sign extend
}

void SwfStreamReader::skipString()
{
  while (readUI8() != 0) {}
}

void SwfStreamReader::readString( nstl::string & result )
{
  result.clear();
  while ( char c = (char)readUI8() )
    result += c;
}

void SwfStreamReader::readUTF8String( nstl::wstring & result )
{
  string tmp;
  readString( tmp );
  NStr::UTF8ToUnicode( &result, tmp );
}

int SwfStreamReader::readBuffer( UI8 * buffer, int bytesToRead )
{
  int actualBytesToRead = min( uint32_t(bytesToRead), swf.getSize() - pos ); 

  if ( actualBytesToRead <= 0 )
    return 0;

  memcpy( buffer, (byte*)swf + pos, actualBytesToRead );
  pos += actualBytesToRead;

  return actualBytesToRead;
}

void SwfStreamReader::readRGBA( SWF_RGBA& _color, bool withAlpha )
{
  _color.r = readUI8();
  _color.g = readUI8();
  _color.b = readUI8();

  _color.a = withAlpha ? readUI8() : 0xFF;
}

void SwfStreamReader::readCXForm( SWF_CXFORMWITHALPHA& _cxform )
{
  clearBitreader( true );
  
  int	has_add = readUBits(1);
  int	has_mult = readUBits(1);
  int	nbits = readUBits(4);

  if ( has_mult ) 
  {
    _cxform.m_[0][0] = readSBits(nbits) / 256.0f;
    _cxform.m_[1][0] = readSBits(nbits) / 256.0f;
    _cxform.m_[2][0] = readSBits(nbits) / 256.0f;
    _cxform.m_[3][0] = readSBits(nbits) / 256.0f;
  }
  else 
  {
    for (int i = 0; i < 4; i++) 
    { 
      _cxform.m_[i][0] = 1; 
    }
  }

  if (has_add) 
  {
    _cxform.m_[0][1] = (float) readSBits(nbits);
    _cxform.m_[1][1] = (float) readSBits(nbits);
    _cxform.m_[2][1] = (float) readSBits(nbits);
    _cxform.m_[3][1] = (float) readSBits(nbits);
  }
  else 
  {
    for (int i = 0; i < 4; i++) 
    { 
      _cxform.m_[i][1] = 0; 
    }
  }

  clearBitreader( false );
}

void SwfStreamReader::readRect( SWF_RECT& _rect )
{
  clearBitreader( true );
  int n = readUBits(5);
  _rect.X1 = readSBits(n);
  _rect.X2 = readSBits(n);
  _rect.Y1 = readSBits(n);
  _rect.Y2 = readSBits(n);
  clearBitreader( false );
}

void SwfStreamReader::readMatrix( SWF_MATRIX& _matrix )
{
  clearBitreader( true );
  _matrix.Identity();

  if ( readUBits(1) ) // has scale
  {
    int	scale_nbits = readUBits(5);

    _matrix.m_[0][0] = readSBits( scale_nbits ) / 65536.0f;
    _matrix.m_[1][1] = readSBits( scale_nbits ) / 65536.0f;
  }

  if ( readUBits(1) ) // has rotate
  {
    int	rotate_nbits = readUBits(5);

    _matrix.m_[1][0] = readSBits( rotate_nbits ) / 65536.0f;
    _matrix.m_[0][1] = readSBits( rotate_nbits ) / 65536.0f;
  }

  int	translate_nbits = readUBits(5);

  if (translate_nbits > 0) 
  {
    _matrix.m_[0][2] = (float) readSBits(translate_nbits);
    _matrix.m_[1][2] = (float) readSBits(translate_nbits);
  }
  clearBitreader( false );
}

void SwfStreamReader::readGradient( SWF_GRADIENT& _gradient, EGradientType::Enum type, bool withAlpha )
{
  clearBitreader( true );

  _gradient.SpreadMode = readUBits(2);
  _gradient.InterpolationMode = readUBits(2);

  _gradient.SpreadMode = 0; // чтобы было меньше вариаций в кеше градиентных текстур 
  _gradient.InterpolationMode = 0; // чтобы было меньше вариаций в кеше градиентных текстур

  _gradient.NumGradient = readUBits(4);
  _gradient.type = type;
  
  _gradient.GradientRecords.resize( _gradient.NumGradient );

  for( int i = 0; i < _gradient.NumGradient; ++i )
  {
    _gradient.GradientRecords[i].Ratio = readUI8();
    readRGBA( _gradient.GradientRecords[i].Color, withAlpha );
  }

  if ( type == EGradientType::Focal )
    _gradient.FocalPoint = readFixed8();
  else
    _gradient.FocalPoint = 0.f;
}

void SwfStreamReader::readFillstyle( SWF_FILLSTYLE& _fillstyle, bool withAlpha, UI16 characterID, int styleID, bool forLine )
{
  clearBitreader( true );

  _fillstyle.Invalidate();

  _fillstyle.FillStyleType = readUI8();

  if ( _fillstyle.IsColor() )
  {
    readRGBA( _fillstyle.Color, withAlpha );
  }
  else if ( _fillstyle.IsGradient() )
  {
    readMatrix( _fillstyle.GradientMatrix );

    if ( _fillstyle.FillStyleType == 0x13 )
      readGradient( _fillstyle.Gradient, EGradientType::Focal, withAlpha );
    else if ( _fillstyle.FillStyleType == 0x12 )
      readGradient( _fillstyle.Gradient, EGradientType::Radial, withAlpha );
    else
      readGradient( _fillstyle.Gradient, EGradientType::Linear, withAlpha );
  }
  else if ( _fillstyle.IsBitmap() )
  {
    _fillstyle.BitmapId = readUI16();

    if ( _fillstyle.FillStyleType == 0x40 || _fillstyle.FillStyleType == 0x42 )
      movie.MarkRepeatableBitmapCharacter( _fillstyle.BitmapId );

    readMatrix( _fillstyle.BitmapMatrix );
  }
  else
  {
    NI_ALWAYS_ASSERT("Not supported fill style");
  }
}

void SwfStreamReader::readMorphFillstyle( SWF_FILLSTYLE& _fillstyleStart, SWF_FILLSTYLE& _fillstyleEnd, UI16 characterID, int styleID, bool forLine )
{
  clearBitreader( true );

  _fillstyleStart.FillStyleType = readUI8();
  _fillstyleEnd.FillStyleType = _fillstyleStart.FillStyleType;

  if ( _fillstyleStart.IsColor() )
  {
    readRGBA( _fillstyleStart.Color, true );
    readRGBA( _fillstyleEnd.Color, true );
  }
  else if ( _fillstyleStart.IsGradient() )
  {
    readMatrix( _fillstyleStart.GradientMatrix );
    readMatrix( _fillstyleEnd.GradientMatrix );

    _fillstyleStart.Gradient.NumGradient = readUI8();
    _fillstyleEnd.Gradient.NumGradient = _fillstyleStart.Gradient.NumGradient; 
    
    _fillstyleStart.Gradient.GradientRecords.resize( _fillstyleStart.Gradient.NumGradient );
    _fillstyleEnd.Gradient.GradientRecords.resize( _fillstyleStart.Gradient.NumGradient );

    for( int i = 0; i < _fillstyleStart.Gradient.NumGradient; ++i )
    {
      _fillstyleStart.Gradient.GradientRecords[i].Ratio = readUI8();
      readRGBA( _fillstyleStart.Gradient.GradientRecords[i].Color, true );

      _fillstyleEnd.Gradient.GradientRecords[i].Ratio = readUI8();
      readRGBA( _fillstyleEnd.Gradient.GradientRecords[i].Color, true );
    }

    if ( _fillstyleStart.FillStyleType == 0x13 )
    {
      _fillstyleStart.Gradient.FocalPoint = readFixed8();
      _fillstyleEnd.Gradient.FocalPoint = readFixed8();
    }

    _fillstyleStart.SetGradientType();
    _fillstyleEnd.SetGradientType();
  }
  else if ( _fillstyleStart.IsBitmap() )
  {
    _fillstyleStart.BitmapId = readUI16();
    _fillstyleEnd.BitmapId = _fillstyleStart.BitmapId; 
    readMatrix( _fillstyleStart.BitmapMatrix );
    readMatrix( _fillstyleEnd.BitmapMatrix );
  }
  else
  {
    NI_ALWAYS_ASSERT("Not supported fill style");
  }
}

void SwfStreamReader::readLinestyle( SWF_LINESTYLE2& _linestyle, bool style2, bool withAlpha, UI16 characterID, int styleID )
{
  clearBitreader( true );

  _linestyle.Width = readUI16();

  if ( style2 )
  {
    _linestyle.StartCapStyle = readUBits(2);
    _linestyle.JointStyle = readUBits(2);
    _linestyle.HasFillFlag = readUBits(1);
    _linestyle.NoHScaleFlag = readUBits(1);
    _linestyle.NoVScaleFlag = readUBits(1);
    _linestyle.PixelHintingFlag = readUBits(1);

     readUBits(5);

    _linestyle.NoClose = readUBits(1);
    _linestyle.EndCapStyle = readUBits(2);
    
    if ( _linestyle.JointStyle == 2 )
      _linestyle.MiterLimitFactor = readUI16();

    if( _linestyle.HasFillFlag )
      readFillstyle( _linestyle.FillType, true, characterID, styleID, true );
    else
      readRGBA( _linestyle.Color, true );
  }
  else
  {
    readRGBA( _linestyle.Color, withAlpha );
  }
}

void SwfStreamReader::readMorphLinestyle( SWF_LINESTYLE2& _linestyleStart, SWF_LINESTYLE2& _linestyleEnd, bool style2, UI16 characterID, int styleID )
{
  clearBitreader( true );

  _linestyleStart.Width = readUI16();
  _linestyleEnd.Width = readUI16();

  if ( style2 )
  {
    _linestyleEnd.StartCapStyle = _linestyleStart.StartCapStyle = readUBits(2);
    _linestyleEnd.JointStyle = _linestyleStart.JointStyle = readUBits(2);
    _linestyleEnd.HasFillFlag = _linestyleStart.HasFillFlag = readUBits(1);
    _linestyleEnd.NoHScaleFlag = _linestyleStart.NoHScaleFlag = readUBits(1);
    _linestyleEnd.NoVScaleFlag = _linestyleStart.NoVScaleFlag = readUBits(1);
    _linestyleEnd.PixelHintingFlag = _linestyleStart.PixelHintingFlag = readUBits(1);

    readUBits(5);

    _linestyleEnd.NoClose = _linestyleStart.NoClose = readUBits(1);
    _linestyleEnd.EndCapStyle = _linestyleStart.EndCapStyle = readUBits(2);

    if ( _linestyleEnd.JointStyle == 2 )
      _linestyleEnd.MiterLimitFactor = _linestyleStart.MiterLimitFactor = readUI16();

    if( _linestyleStart.HasFillFlag )
    {
      readMorphFillstyle( _linestyleStart.FillType, _linestyleEnd.FillType, characterID, styleID, true );
    }
    else
    {
      readRGBA( _linestyleStart.Color, true );
      readRGBA( _linestyleEnd.Color, true );
    }
  }
  else
  {
    readRGBA( _linestyleStart.Color, true );
    readRGBA( _linestyleEnd.Color, true );
  }
}

void SwfStreamReader::readShape( SWF_SHAPERECORD& _shapeRecord, int& NumFillbits, int& NumLinebits,    
    int& fillOffset, int& lineOffset,
    nstl::vector<SWF_FILLSTYLE>& _fillStyles, nstl::vector<SWF_LINESTYLE2>& _lineStyles,
    bool style2, bool withAlpha, UI16 characterID )
{
  _shapeRecord.edgeRecord = readUBits(1); // TypeFlag

  if ( _shapeRecord.edgeRecord )
  {
    _shapeRecord.StraightFlag = readUBits(1);

    int NumBits = readUBits(4) + 2;

    if ( _shapeRecord.StraightFlag )
    {
      bool GeneralLineFlag = readUBits(1);
      bool VertLineFlag = false;

      if ( !GeneralLineFlag )
        VertLineFlag = readUBits(1);

      _shapeRecord.DeltaX = 0;
      _shapeRecord.DeltaY = 0;

      if ( GeneralLineFlag || !VertLineFlag )
        _shapeRecord.DeltaX = readSBits( NumBits );

      if ( GeneralLineFlag || VertLineFlag )
        _shapeRecord.DeltaY = readSBits( NumBits );

//      DebugTrace("StraightEdge\n");
    }
    else
    {
      _shapeRecord.ControlDeltaX = readSBits( NumBits );
      _shapeRecord.ControlDeltaY = readSBits( NumBits );
      _shapeRecord.AnchorDeltaX = readSBits( NumBits );
      _shapeRecord.AnchorDeltaY = readSBits( NumBits );

//      DebugTrace("CurveEdge\n");
    }
  }
  else
  {
    _shapeRecord.StateNewStyles = readUBits(1);
    _shapeRecord.StateLineStyle = readUBits(1);
    _shapeRecord.StateFillStyle1 = readUBits(1);
    _shapeRecord.StateFillStyle0 = readUBits(1);
    _shapeRecord.StateMoveTo = readUBits(1);

    if ( _shapeRecord.StateMoveTo )
    {
      int MoveBits = readUBits(5);
      _shapeRecord.MoveDeltaX = readSBits(MoveBits);
      _shapeRecord.MoveDeltaY = readSBits(MoveBits);

//      DebugTrace("MoveTo\n");
    }

    if ( _shapeRecord.StateFillStyle0 )
    {
      _shapeRecord.FillStyle0 = readUBits(NumFillbits) + fillOffset;
//      DebugTrace("Fill0\n");
    }

    if ( _shapeRecord.StateFillStyle1 )
    {
      _shapeRecord.FillStyle1 = readUBits(NumFillbits) + fillOffset;
//      DebugTrace("Fill1\n");
    }

    if ( _shapeRecord.StateLineStyle )
    {
      _shapeRecord.LineStyle = readUBits(NumLinebits) + lineOffset;
//      DebugTrace("Line\n");
    }

    if ( _shapeRecord.StateNewStyles )
    {
//      DebugTrace("New Styles\n");

      clearBitreader( false );

      fillOffset = _fillStyles.size();
      lineOffset = _lineStyles.size();

      readFillstyles( _fillStyles, withAlpha, characterID );
      readLinestyles( _lineStyles, style2, withAlpha, characterID );

      clearBitreader( true );

      NumFillbits = readUBits(4);
      NumLinebits = readUBits(4);
    }
  }
}

void SwfStreamReader::readFillstyles( FillStyles& _fillstyles, bool withAlpha, UI16 characterID )
{
  UI8 fillStyleCount = readUI8();

  NI_ASSERT( fillStyleCount != 0xff, "Fill array extended not yet implemented" );

  int startPos = _fillstyles.size();

  _fillstyles.resize( startPos + fillStyleCount );

  for ( int i = startPos; i < startPos + fillStyleCount; ++ i )
  {
    readFillstyle( _fillstyles[i], withAlpha, characterID, i, false );
  }
}

void SwfStreamReader::readLinestyles( LineStyles& _linestyles, bool style2, bool withAlpha, UI16 characterID )
{

  UI8 lineStyleCount = readUI8();

  NI_ASSERT( lineStyleCount != 0xff, "Line array extended not yet implemented" );

  int startPos = _linestyles.size();

  _linestyles.resize( startPos + lineStyleCount );

  for ( int i = startPos; i < startPos + lineStyleCount; ++ i )
  {
    readLinestyle( _linestyles[i], style2, withAlpha, characterID, i );
  }
}

void SwfStreamReader::readMorphFillstyles( FillStyles& _fillstylesStart, FillStyles& _fillstylesEnd, UI16 characterID )
{
  UI8 fillStyleCount = readUI8();

  NI_ASSERT( fillStyleCount != 0xff, "Fill array extended not yet implemented" );

  _fillstylesStart.resize( fillStyleCount );
  _fillstylesEnd.resize( fillStyleCount );

  for ( int i = 0; i < fillStyleCount; ++ i )
  {
    readMorphFillstyle( _fillstylesStart[i], _fillstylesEnd[i], characterID, i, false );
  }
}

void SwfStreamReader::readMorphLinestyles( LineStyles& _linestylesStart, LineStyles& _linestylesEnd, bool style2, UI16 characterID )
{
  UI8 lineStyleCount = readUI8();

  NI_ASSERT( lineStyleCount != 0xff, "Line array extended not yet implemented" );

  _linestylesStart.resize( lineStyleCount );
  _linestylesEnd.resize( lineStyleCount );

  for ( int i = 0; i < lineStyleCount; ++ i )
  {
    readMorphLinestyle( _linestylesStart[i], _linestylesEnd[i], style2, characterID, i );
  }
}

void SwfStreamReader::clearBitreader( bool withAssert )
{
  if ( withAssert )
  {
    NI_ASSERT( bitPos == 0, "Bit position is not 0" );
  }

  bitPos = 0;
}

}