#ifndef FONTTAGS_H_INCLUDED
#define FONTTAGS_H_INCLUDED

#include "SwfTypes.h"
#include "ShapeData.h"

namespace SWFParser
{
  struct TagInfo;
};

namespace flash
{

class SwfStreamReader;
struct ShapeData;

_interface IFontInstance;
_interface IFontRender;


namespace ECSMTableHint
{
  enum Enum
  {
    Thin = 0,
    Medium = 1,
    Thick = 2
  };
}



namespace ESwfLanguageCode
{
  enum Enum
  {
    NoLanguage          = 0,
    Latin               = 1,
    Japanese            = 2,
    Korean              = 3,
    SimplifiedChinese   = 4,
    TraditionalChinese  = 5
  };
}




struct SFontTag_KERNINGRECORD
{
  UI16    FontKerningCode1;
  UI16    FontKerningCode2;
  SI16    FontKerningAdjustment;

  SFontTag_KERNINGRECORD() : FontKerningCode1(), FontKerningCode2(), FontKerningAdjustment() {}
};



struct FontData
{
  UI16          FontID;
  bool          FontFlagsHasLayout; //1 bit
  bool          FontFlagsShiftJIS; //1 bit
  bool          FontFlagsSmallText; //1 bit
  bool          FontFlagsANSI; //1 bit
  bool          FontFlagsWideOffsets; //1 bit
  bool          FontFlagsWideCodes; //1 bit
  bool          FontFlagsItalic; //1 bit
  bool          FontFlagsBold; //1 bit
  ESwfLanguageCode::Enum  LanguageCode; //UI8
  string        FontName; // UI8 FontNameLen + chars UI8[length]
  UI16          NumGlyphs;
  vector<UI32>  OffsetTable; // [NumGlyphs] of UI32 or UI16 

  UI32          CodeTableOffset;//of UI32 or UI16 
  vector<ShapeData> GlyphShapeTable; //[NumGlyphs]

  vector<UI16>  CodeTable; //[NumGlyphs]
  SI16          FontAscent;
  SI16          FontDescent;
  SI16          FontLeading;
  vector<SI16>  FontAdvanceTable; //[NumGlyphs]
  vector<SWF_RECT>  FontBoundsTable; //[NumGlyphs]

  UI16          KerningCount;
  vector<SFontTag_KERNINGRECORD>  FontKerningTable; //[KerningCount]

  //generated data
  typedef map<wchar_t, int>  TGlyphCode;
  TGlyphCode    gryphCodes; //[NumGlyphs], character codes -> glyphs

  FontData();
  void Load( SwfStreamReader & swf, TagInfo & tagInfo );
};



struct SFontAlign_ZONEDATA
{
  float   AlignmentCoordinate;
  float   Range;
  SFontAlign_ZONEDATA() : AlignmentCoordinate( 0 ), Range( 0 ) {}
};



struct SFontAlign_ZONERECORD
{
  vector<SFontAlign_ZONEDATA> ZoneData;
  bool                  ZoneMaskY;
  bool                  ZoneMaskX;

  void Load( SwfStreamReader & swf );

  SFontAlign_ZONERECORD() : ZoneMaskY(), ZoneMaskX() {}
};




class SwfFont : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( SwfFont, BaseObjectST );

public:
  SwfFont() : CSMTableHint() {}

  void LoadDefineFont3( SwfStreamReader & swf, TagInfo & tagInfo ) { data.Load( swf, tagInfo ); }
  void LoadAlignZonesRecords( SwfStreamReader & swf, UI32 _CSMTableHint );

  const FontData & Data() const { return data; }

  void SetFontName( const string & _name, const string & _copyrite );

  IFontInstance * GetRenderable( IFontRender * render, int height );

private:
  FontData  data;

  string    copyrite;

  ECSMTableHint::Enum   CSMTableHint;
  vector<SFontAlign_ZONERECORD> alignZoneRecords;
};

} //namespace flash

#endif //FONTTAGS_H_INCLUDED
