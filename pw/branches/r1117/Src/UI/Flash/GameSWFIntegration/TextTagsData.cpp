#include "TamarinPCH.h"
#include "TextTagsData.h"

#include "swf_parse.h"
#include "FontsDict.h"
#include "FontTags.h"


NI_DEFINE_REFCOUNT( flash::StaticTextTagData );
NI_DEFINE_REFCOUNT( flash::EditTextTagData );


namespace flash
{

void SCsmTextSettings::Load( SwfStreamReader & swf )
{
  UseFlashType = (ECsmTextFlashType::Enum)swf.readUBits( 2 );

  GridFit = (ECsmTextGridFit::Enum)swf.readUBits( 3 );

  UI32 reserved = swf.readUBits( 3 );
  NI_ASSERT( !reserved, "Reserved bits must be 0" );

  Thickness = swf.readFloat();
  Sharpness = swf.readFloat();

  reserved = swf.readUI8();
  NI_ASSERT( !reserved, "Reserved bits must be 0" );
}



STextTag_TEXTRECORD::STextTag_TEXTRECORD() :
styleFlagsHasFont(),
styleFlagsHasColor(),
styleFlagsHasYOffset(),
styleFlagsHasXOffset(),
fontID(),
textColor( 255, 255, 255 ),
xOffset(),
yOffset(),
textHeight()
{
}



void SStaticTextTagData::Load( SwfStreamReader & swf, TagInfo & tagInfo, FontsDictionary * fontsDict )
{
  NI_VERIFY( tagInfo.tagType == SWFTags::SWFTAGS_DEFINETEXT || tagInfo.tagType == SWFTags::SWFTAGS_DEFINETEXT2, "", return );

  swf.readRect( textBounds );
  swf.readMatrix( textMatrix );
  UI8 glyphBits = swf.readUI8();
  UI8 advanceBits = swf.readUI8();

  //Read TEXTRECORD's
  while( true )
  {
    if ( !swf.readUBits( 1 ) )
      break;

    NI_ASSERT( swf.readUBits( 3 ) == 0, "Non-zero reserved bits!" );

    textRecords.push_back( STextTag_TEXTRECORD() );
    STextTag_TEXTRECORD & tr = textRecords.back();

    tr.styleFlagsHasFont = swf.readSingleBit();
    tr.styleFlagsHasColor = swf.readSingleBit();
    tr.styleFlagsHasYOffset = swf.readSingleBit();
    tr.styleFlagsHasXOffset = swf.readSingleBit();

    if ( tr.styleFlagsHasFont )
    {
      tr.fontID = swf.readUI16();
      if ( fontsDict )
        tr.font = fontsDict->GetFontById( tr.fontID );
    }

    if ( tr.styleFlagsHasColor )
      swf.readRGBA( tr.textColor, tagInfo.tagType == SWFTags::SWFTAGS_DEFINETEXT2 );

    if ( tr.styleFlagsHasXOffset )
      tr.xOffset = (SI16)swf.readUI16();

    if ( tr.styleFlagsHasYOffset )
      tr.yOffset = (SI16)swf.readUI16();

    if ( tr.styleFlagsHasFont )
      tr.textHeight = swf.readUI16();

    //Read glyphs
    UI8 glyphCount = swf.readUI8();
    tr.glyphEntries.resize( glyphCount );
    for ( UI8 i = 0; i < glyphCount; ++i )
    {
      STextTag_GLYPHENTRY & g = tr.glyphEntries[i];
      g.glyphIndex = swf.readUBits( glyphBits );
      g.glyphAdvance = swf.readSBits( advanceBits );
    }

    //Convert glyps to string
    if ( tr.font )
    {
      tr.rawText.clear();
      tr.rawText.resize( glyphCount, L' ' );
      const vector<UI16> & codeTable = tr.font->Data().CodeTable;
      for ( UI8 i = 0; i < glyphCount; ++i )
      {
        const STextTag_GLYPHENTRY & g = tr.glyphEntries[i];
        NI_VERIFY( (int)g.glyphIndex < codeTable.size(), "Wrong code table", continue );
        tr.rawText[i] = (wchar_t)codeTable[g.glyphIndex];
      }
    }
  }

  swf.clearBitreader( false );
}



void StaticTextTagData::Copy( const StaticTextTagData * source )
{
  *(SStaticTextTagData*)this = *(StaticTextTagData *)source;
  csmSettings = source->csmSettings;
}










SEditTextTagData::SEditTextTagData() :
HasText(),
WordWrap(),
Multiline(),
Password(),
ReadOnly(),
HasTextColor(),
HasMaxLength(),
HasFont(),
HasFontClass(),
AutoSize(),
HasLayout(),
NoSelect(),
Border(),
WasStatic(),
HTML(),
UseOutlines(),
FontID(),
FontClass(),
FontHeight(),
MaxLength(),
Align(),
LeftMargin(),
RightMargin(),
Indent(),
Leading(),
VariableName(),
InitialText()
{
}



void SEditTextTagData::Load( SwfStreamReader & swf, FontsDictionary * fontsDict )
{
  swf.readRect( Bounds );

  HasText       = swf.readSingleBit();
  WordWrap      = swf.readSingleBit();
  Multiline     = swf.readSingleBit();
  Password      = swf.readSingleBit();
  ReadOnly      = swf.readSingleBit();
  HasTextColor  = swf.readSingleBit();
  HasMaxLength  = swf.readSingleBit();
  HasFont       = swf.readSingleBit();
  HasFontClass  = swf.readSingleBit();
  AutoSize      = swf.readSingleBit();
  HasLayout     = swf.readSingleBit();
  NoSelect      = swf.readSingleBit();
  Border        = swf.readSingleBit();
  WasStatic     = swf.readSingleBit();
  HTML          = swf.readSingleBit();
  UseOutlines   = swf.readSingleBit();

  if ( HasFont )
    FontID = swf.readUI16();

  if ( HasFontClass )
    swf.readString( FontClass );

  if ( HasFont )
    FontHeight = swf.readUI16();
  
  if ( HasTextColor )
    swf.readRGBA( TextColor, true );

  if ( HasMaxLength )
    MaxLength = swf.readUI16();

  if ( HasLayout )
  {
    Align = (EEditTextAlign::Enum)swf.readUI8();
    LeftMargin  = swf.readUI16();
    RightMargin = swf.readUI16();
    Indent      = swf.readUI16();

    Leading = (SI16)swf.readUI16();
  }
  
  swf.readString( VariableName );

  if ( HasText )
    swf.readUTF8String( InitialText );

  if ( HasFont && fontsDict )
    font = fontsDict->GetFontById( FontID );
}



void EditTextTagData::Copy( const EditTextTagData * source )
{
  *(SEditTextTagData *)this = *(SEditTextTagData *)source;
  csmSettings = source->csmSettings;
}

} //namespace flash
