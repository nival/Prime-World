#pragma once

#include "ScriptBuffer.h"
#include "SwfTypes.h"

namespace Render
{
  _interface IFlashRenderer;
}

namespace flash
{

class SwfStreamReader 
{
  int bitPos;
  UI32 bitBuf;
  uint32_t pos;

public:
  avmplus::ScriptBuffer swf;

  SwfStreamReader( Movie& _movie );

  void SetFlashRenderer( Render::IFlashRenderer* _renderer ) { renderer = _renderer; }
  Render::IFlashRenderer* GetFlashRenderer() { return renderer; }
  
  void SetStreamBuffer(avmplus::ScriptBuffer swf);

  uint32_t GetPos() const { return pos; }
  void SetPos( uint32_t _newPos );

  //skip swf header
  void skipHeader();

  void readTagInfo( TagInfo& tagInfo );

  UI8  readUI8()  { /*NI_ASSERT( pos < swf.getSize(), "SWF file buffer overrun" );*/ return swf[pos++]; }
//   UI16 readUI16();
//   UI32 readUI32();
  UI16 readUI16() { return readUI8() | readUI8()<<8; }
  UI32 readUI32() { return readUI8() | readUI8()<<8 | readUI8()<<16 | readUI8()<<24; }
  UI32 readUI32Encoded();

  bool readSingleBit() { return readUBits( 1 ) ? true : false; }

  void readRGBA( SWF_RGBA& _color, bool withAlpha );
  void readRect( SWF_RECT& _rect );
  void readMatrix( SWF_MATRIX& _matrix );
  void readGradient( SWF_GRADIENT& _gradient, EGradientType::Enum type, bool withAlpha );

  void readFillstyle( SWF_FILLSTYLE& _fillstyle, bool withAlpha, UI16 characterID, int styleID, bool forLine );
  void readLinestyle( SWF_LINESTYLE2& _linestyle, bool style2, bool withAlpha, UI16 characterID, int styleID );

  void readMorphFillstyle( SWF_FILLSTYLE& _fillstyleStart, SWF_FILLSTYLE& _fillstyleEnd, UI16 characterID, int styleID, bool forLine );
  void readMorphLinestyle( SWF_LINESTYLE2& _linestyleStart, SWF_LINESTYLE2& _linestyleEnd, bool style2, UI16 characterID, int styleID );

  void readShape( SWF_SHAPERECORD& _shapeRecord, int& NumFillbits, int& NumLinebits, 
    int& fillOffset, int& lineOffset,
    nstl::vector<SWF_FILLSTYLE>& _fillStyles, nstl::vector<SWF_LINESTYLE2>& _lineStyles,
    bool style2, bool withAlpha, UI16 characterID);
  void readCXForm( SWF_CXFORMWITHALPHA& _cxform );

  void readFillstyles( FillStyles& _fillstyles, bool withAlpha, UI16 characterID );
  void readLinestyles( LineStyles& _linestyles, bool style2, bool withAlpha, UI16 characterID );

  void readMorphFillstyles( FillStyles& _fillstylesStart, FillStyles& _fillstylesEnd, UI16 characterID );
  void readMorphLinestyles( LineStyles& _linestylesStart, LineStyles& _linestylesEnd, bool style2, UI16 characterID );

  void fillBitBuf();
  int  readBuffer( UI8 * buffer, int bytesToRead );

  void clearBitreader( bool withAssert );
  UI32 readUBits( int n );
  SI32 readSBits( int n );

  void skipString();
  void readString( nstl::string & result );
  void readUTF8String( nstl::wstring & result );

  void ignore(int n) { NI_ASSERT( pos + n <= swf.getSize(), "SWF file buffer overrun" ); pos += n; }

  float readFloat();
  float readFoat16(); //IEEE half precision 1/5/10 format

  float readFixed();
  float readFixed8(); // actualy 16 bit

private:
  UI16 swapUI16( UI16 u );
  UI32 swapUI32( UI32 u );

  UI32 readLEUI32() { return swapUI32( readUI32() ); }
  UI16 readLEUI16() { return swapUI16( readUI16() ); }

  Weak<Render::IFlashRenderer> renderer;
  Movie& movie;
};

}