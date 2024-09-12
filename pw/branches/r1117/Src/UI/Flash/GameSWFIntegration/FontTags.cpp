#include "TamarinPCH.h"
#include "FontTags.h"

#include "swf_parse.h"
#include "ShapeData.h"
#include "FontsRenderInterface.h"


NI_DEFINE_REFCOUNT( flash::SwfFont );

namespace flash
{

FontData::FontData() :
FontID(),
FontFlagsHasLayout(),
FontFlagsShiftJIS(),
FontFlagsSmallText(),
FontFlagsANSI(),
FontFlagsWideOffsets(),
FontFlagsWideCodes(),
FontFlagsItalic(),
FontFlagsBold(),
LanguageCode(),
NumGlyphs(),

FontAscent(),
FontDescent(),
FontLeading(),

KerningCount()
{
}



void FontData::Load( SwfStreamReader & swf, TagInfo & tagInfo )
{
  swf.clearBitreader( true );

  FontID = swf.readUI16();

  FontFlagsHasLayout =    swf.readSingleBit();
  FontFlagsShiftJIS =     swf.readSingleBit();
  FontFlagsSmallText =    swf.readSingleBit();
  FontFlagsANSI =         swf.readSingleBit();
  FontFlagsWideOffsets =  swf.readSingleBit();
  FontFlagsWideCodes =    swf.readSingleBit();
  FontFlagsItalic =       swf.readSingleBit();
  FontFlagsBold =         swf.readSingleBit();

  LanguageCode = (ESwfLanguageCode::Enum)swf.readUI8();

  int nameLen = swf.readUI8();
  string nameUtf8;
  nameUtf8.resize( nameLen, 0 );
  swf.readBuffer( (UI8 *)&nameUtf8[0], nameLen );
  NStr::UTF8ToMBCS( &FontName, nameUtf8 );

  //truncate zeroes
  while ( !FontName.empty() && !FontName[FontName.size() - 1] )
    FontName.pop_back();

  swf.clearBitreader( false );

  NumGlyphs = swf.readUI16();

  OffsetTable.resize( NumGlyphs, 0 );
  for ( int i = 0; i < NumGlyphs; ++i )
    OffsetTable[i] = FontFlagsWideOffsets ? swf.readUI32() : swf.readUI16();

  CodeTableOffset = FontFlagsWideOffsets ? swf.readUI32() : swf.readUI16();

  GlyphShapeTable.resize( NumGlyphs );
  for ( int i = 0; i < NumGlyphs; ++i )
    GlyphShapeTable[i].Load( swf, tagInfo, false, 0 );

  CodeTable.resize( NumGlyphs, 0 );
  for ( int i = 0; i < NumGlyphs; ++i )
    CodeTable[i] = swf.readUI16();

  if ( FontFlagsHasLayout )
  {
    //There are some info on this:
    //http://help.adobe.com/en_US/AS3LCR/Flash_10.0/flash/text/TextLineMetrics.html
    FontAscent = (SI16)swf.readUI16();
    FontDescent = (SI16)swf.readUI16();
    FontLeading = (SI16)swf.readUI16();

    FontAdvanceTable.resize( NumGlyphs, 0 );
    for ( int i = 0; i < NumGlyphs; ++i )
      FontAdvanceTable[i] = (SI16)swf.readUI16();

    FontBoundsTable.resize( NumGlyphs );
    for ( int i = 0; i < NumGlyphs; ++i )
      swf.readRect( FontBoundsTable[i] );

    KerningCount = swf.readUI16();
    FontKerningTable.resize( KerningCount );
    for ( int i = 0; i < KerningCount; ++i )
    {
      FontKerningTable[i].FontKerningCode1 = FontFlagsWideCodes ? swf.readUI16() : (UI16)swf.readUI8();
      FontKerningTable[i].FontKerningCode2 = FontFlagsWideCodes ? swf.readUI16() : (UI16)swf.readUI8();
      FontKerningTable[i].FontKerningAdjustment = (SI16)swf.readUI16();
    }
  }

  //generate glyphs codes
  gryphCodes.clear();
  for ( int i = 0; i < NumGlyphs; ++i )
    gryphCodes[CodeTable[i]] = i;
}




void SFontAlign_ZONERECORD::Load( SwfStreamReader & swf )
{
  UI8 NumZoneData = swf.readUI8();

  NI_ASSERT( NumZoneData == 2, "" );
  ZoneData.resize( NumZoneData );
  for ( int i = 0; i < NumZoneData; ++i )
  {
    ZoneData[i].AlignmentCoordinate = swf.readFoat16();
    ZoneData[i].Range = swf.readFoat16();
  }

  UI32 reserved = swf.readUBits( 6 );
  NI_ASSERT( reserved == 0, "" );

  ZoneMaskY = swf.readSingleBit();
  ZoneMaskX = swf.readSingleBit();
}





void SwfFont::LoadAlignZonesRecords( SwfStreamReader & swf, UI32 _CSMTableHint )
{
  CSMTableHint = (ECSMTableHint::Enum)_CSMTableHint;

  NI_DATA_ASSERT( alignZoneRecords.empty(), NStr::StrFmt( "Duplicate align zones for font %d (%s)", data.FontID, data.FontName.c_str() ) );

  alignZoneRecords.resize( data.NumGlyphs );
  for ( int i = 0; i < data.NumGlyphs; ++i )
    alignZoneRecords[i].Load( swf );
}



void SwfFont::SetFontName( const string & _name, const string & _copyrite )
{
  if ( !data.FontName.empty() && !_name.empty() && ( data.FontName != _name ) )
    DebugTrace( "Overriding font %d name '%s' with '%s'", data.FontID, data.FontName.c_str(), _name.c_str());

  if ( !_name.empty() )
    data.FontName = _name;

  copyrite = _copyrite;
}



IFontInstance * SwfFont::GetRenderable( IFontRender * render, int height )
{
  if ( data.FontName.empty() )
    return 0;

  if ( data.FontFlagsHasLayout )
  {
    SFontMetricInfo metric( data.FontAscent, data.FontDescent, data.FontLeading );
    return render->FindFont( data.FontName.c_str(), height, false, false, &metric );
  }
  else
    return render->FindFont( data.FontName.c_str(), height, false, false, 0 );
}

} //namespace flash
