#include "stdafx.h"

#include "Alphabet.h"
#include "FontRender.hpp"
#include "../Render/UIRenderer.h"

#include "Resolution.h"

#include FT_OUTLINE_H
#include FT_GLYPH_H
#include FT_SYNTHESIS_H
#include FT_BBOX_H
#include FT_MODULE_H

static bool s_useFontHintingInFlash = true;
REGISTER_DEV_VAR( "flash_use_font_hinting", s_useFontHintingInFlash, STORAGE_NONE );


namespace UI
{



FT_Long FromFTPosNoScale( FT_Fixed pos )
{
  if ( pos < 0 )
    return -( ( -pos + 0 ) >> 6 );

  return ( pos + 0 ) >> 6;
}



Alphabet::Alphabet( FontRenderer* _fontRenderer ) : 
  widthK( 1.f ), 
  heightK( 1.f ), 
  face( 0 ), 
  fontRenderer( _fontRenderer ),
  fontHeight( 1.f ), 
  fontAscent( 1.f ), 
  bold( false ),
  italic( false ),
  flashFont( false )
{
}


void Alphabet::LoadAlphabet( FT_Library ftLibrary, const char* _ttfFileName, int _fontSize, bool _bold, bool _italic, bool loadSystemFont, bool forFlash )
{
  flashFont = forFlash;

  bold = _bold;
  italic = _italic;

  fontFileCache = fontRenderer->GetFontFileCache( _ttfFileName, loadSystemFont ? EFontLocation::SystemFont : EFontLocation::GameFont );

  NI_VERIFY_TRACE( fontFileCache, "Cannot find font cache", return );

#ifdef TT_USE_BYTECODE_INTERPRETER
  FT_TrueTypeEngineType engineType = FT_Get_TrueType_Engine_Type( ftLibrary );
  engineType;
#endif

  // Loading font
  if ( FT_New_Memory_Face( ftLibrary, &(fontFileCache->alphaBytes[0]), fontFileCache->alphaBytes.size(), 0, &face ) )
  {
    NI_ALWAYS_ASSERT_TRACE( NStr::StrFmt( "Can't load font from file. Possible wrong format: %s", _ttfFileName ) );
    return;
  }

  if ( NFile::GetFileExt( _ttfFileName ) == ".pfb" )
  {
    if ( !(fontFileCache->kerningBytes.empty()) )
    {
      FT_Open_Args args;
      args.flags = FT_OPEN_MEMORY;
      args.memory_base = ( &(fontFileCache->kerningBytes[0]) );
      args.memory_size = fontFileCache->kerningBytes.size();

      if ( FT_Attach_Stream( face, &args ) )
      {
        NI_ALWAYS_ASSERT_TRACE( NStr::StrFmt( "Can't read kerning and additional metrics for font from file: %s", _ttfFileName ) );
      }
    }
  }
  
  if ( FT_Select_Charmap( face, FT_ENCODING_UNICODE ) )
  {
    NI_ALWAYS_ASSERT_TRACE( NStr::StrFmt( "Can't set unicode charmap: %s", _ttfFileName ) );
    return;
  }

  if ( flashFont )
  { //Flash branch
    widthK = UI::GetScreenResolution().x > 0 ? ( float( UI::GetUIScreenResolution().x ) / float( UI::GetScreenResolution().x ) ) : 1.0f;
    heightK = UI::GetScreenResolution().y > 0 ? ( float( UI::GetUIScreenResolution().y ) / float( UI::GetScreenResolution().y ) ) : 1.0f;

    FT_Size_RequestRec  req;

    req.type           = FT_SIZE_REQUEST_TYPE_NOMINAL;
    req.width          = _fontSize << 6;
    req.height         = _fontSize << 6;
    req.horiResolution = 0;
    req.vertResolution = 0;

    if ( FT_Request_Size( face, &req ) )
    {
      NI_ALWAYS_ASSERT_TRACE( NStr::StrFmt( "Can't set size for fonts: %s", _ttfFileName ) );
      return;
    }

    //Height and ascent is in UI pixels
    fontHeight =  FromFTPosNoScale( face->size->metrics.height ) * heightK;
    fontAscent =  FromFTPosNoScale( face->size->metrics.ascender ) * heightK;
//    fontHeight =  int ( float( face->height ) / float( face->units_per_EM ) * face->size->metrics.y_ppem/* + 0.5f */) * heightK;
//    fontAscent =  int ( float( face->ascender ) / float( face->units_per_EM ) * face->size->metrics.y_ppem/* + 0.5f */) * heightK;
  }
  else //UI Legacy branch
  {
    //All values is 26.6 ffp format
    FT_Pos maxAscent = 0;
    FT_Pos minDescent = 0;

    //Ðàñ÷èòàåì ðàçìåð øðèôòà ïî ãàáàðèòàì áóêàâàê
    static const wchar_t * sampleChars = L" AIWZapqyÀÐßàðùóö";

    for ( const wchar_t * checkFace = sampleChars; *checkFace; ++checkFace )
    {
      FT_Load_Char( face, *checkFace, FT_LOAD_IGNORE_TRANSFORM | FT_LOAD_NO_SCALE );

      if ( bold )
        FT_GlyphSlot_Embolden( face->glyph );

      if ( italic ) 
        MakeOutlineItalic( face->glyph );

      maxAscent = max( maxAscent, face->glyph->metrics.horiBearingY );
      minDescent = min( minDescent, -( face->glyph->metrics.height - face->glyph->metrics.horiBearingY ) );
    }

    //DebugTrace( "Loading alphabet '%s' size %d%s%s%s", _ttfFileName, _fontSize,
    //    _bold ? ", bold" : "", _italic ? ", italic" : "", loadSystemFont ? ", system" : "" );

    widthK = UI::GetScreenResolution().x > 0 ? ( float( UI::GetUIScreenResolution().x ) / float( UI::GetScreenResolution().x ) ) : 1.0f;
    heightK = UI::GetScreenResolution().y > 0 ? ( float( UI::GetUIScreenResolution().y ) / float( UI::GetScreenResolution().y ) ) : 1.0f;

    float ascent  = _fontSize;
    float descent = ceilf( _fontSize * float( minDescent ) / float( maxAscent ) );
    float height = ascent - descent;

    //Height and ascent is in UI pixels
    fontHeight = height * heightK;
    fontAscent = ascent * heightK;

    FT_Size_RequestRec  req;

    req.type           = FT_SIZE_REQUEST_TYPE_SCALES;
    req.width          = 0; //Keep default aspect
    req.height         = FT_DivFix( (int)( ascent * 64.0f + 0.5f ), maxAscent ); 
    req.horiResolution = 0;
    req.vertResolution = 0;

    if ( FT_Request_Size( face, &req ) )
    {
      NI_ALWAYS_ASSERT_TRACE( NStr::StrFmt( "Can't set size for fonts: %s", _ttfFileName ) );
      return;
    }
  }

  spaceGlyph = GetGlyph( L' ' );
}



void Alphabet::MakeOutlineItalic( FT_GlyphSlot  slot )
{
  FT_Matrix    transform;
  FT_Outline*  outline = &slot->outline;


  /* only oblique outline glyphs */
  if ( slot->format != FT_GLYPH_FORMAT_OUTLINE )
    return;

  /* we don't touch the advance width */

  /* For italic, simply apply a shear transform, with an angle */
  /* of about 12 degrees.                                      */

  transform.xx = 0x10000L;
  transform.yx = 0x00000L;

  transform.xy = 0x06000L;
  transform.yy = 0x10000L;

//  int xstr = -int( float( face->units_per_EM ) / 2.f * tan( ToRadian( 12.f ) ) );

  FT_Outline_Transform( outline, &transform );
//  FT_Outline_Translate( outline, xstr, 0 ); 
}



const Glyph& Alphabet::GetGlyph( wchar_t symbol )
{
  GlyphHashMap::const_iterator pos = glyphHashMap.find( symbol );

  if ( pos != glyphHashMap.end() )
    return pos->second;

  //Lets create and cash down a new one
  Glyph & newGlyph = glyphHashMap[symbol];

  if ( flashFont )
    FT_Load_Char( face, symbol, s_useFontHintingInFlash ? FT_LOAD_FORCE_AUTOHINT : FT_LOAD_NO_HINTING );
  else
    FT_Load_Char( face, symbol, FT_LOAD_IGNORE_TRANSFORM | FT_LOAD_FORCE_AUTOHINT );

  if ( italic ) 
    MakeOutlineItalic( face->glyph );

  FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL );

  if ( bold )
    FT_GlyphSlot_Embolden( face->glyph );

  const int glyphW = face->glyph->bitmap.width;
  const int glyphH = face->glyph->bitmap.rows;

  // Prepare outline
  unsigned char* bitmapBuffer = face->glyph->bitmap.buffer;
  int bitmapPitch = face->glyph->bitmap.pitch;

  // Copy rendered bitmap to our texture
  fontRenderer->AllocatePlace( newGlyph, glyphW, glyphH );

  Render::Texture2DRef fonts = fontRenderer->GetFontsTexture();
  if( IsValidPtr(fonts) ) {
    Render::LockedRect lockedRect = fonts->LockRect( 0, Render::LOCK_DEFAULT );

    if ( lockedRect.data )
    {
      int glyphOffs = (int)( FONT_TEXTURE_SIZE * ( newGlyph.u1 + newGlyph.v1 * FONT_TEXTURE_SIZE ) );

      for ( int i = 0; i < glyphH; ++ i )
      {
        NI_VERIFY_TRACE( ( glyphOffs + bitmapPitch ) <= ( FONT_TEXTURE_SIZE * FONT_TEXTURE_SIZE ), "Out of glyph's texture buffer!", continue );
        memcpy( lockedRect.data + glyphOffs, bitmapBuffer + i * bitmapPitch, bitmapPitch );
        glyphOffs += FONT_TEXTURE_SIZE;
      }
    }

    newGlyph.v1 -= 1.f / (float)FONT_TEXTURE_SIZE;
    newGlyph.u1 -= 1.f / (float)FONT_TEXTURE_SIZE;
    newGlyph.v2 += 2.f / (float)FONT_TEXTURE_SIZE;
    newGlyph.u2 += 1.f / (float)FONT_TEXTURE_SIZE;

    fonts->UnlockRect( 0 );
  }

  FT_Glyph_Metrics &metrics = face->glyph->metrics;

  newGlyph.width = float( glyphW + 2 ) * widthK;
  newGlyph.height = float( glyphH + 3 ) * heightK;
  newGlyph.offsetW = float( FromFTPosNoScale( metrics.horiBearingX ) - 1 ) * widthK;
  newGlyph.offsetH = float( FromFTPosNoScale( metrics.horiBearingY ) + 1 ) * heightK;
  const float advance = float( FromFTPosNoScale( metrics.horiAdvance ) ) * widthK;
  newGlyph.A = float( FromFTPosNoScale( metrics.horiBearingX ) ) * widthK;
  newGlyph.B = float( glyphW ) * widthK;
  newGlyph.C = advance - newGlyph.B - newGlyph.A;

  if ( newGlyph.A < 0 )
  {
    wstring dummy;
    dummy += symbol; //FIXME: not so efficient uh?
    //DebugTrace( "Font '%s' (ascent %.1f) has shifted char '%s'",
    //  ( face && face->family_name ) ? face->family_name : "", fontAscent,
    //  NStr::ToMBCS( dummy ).c_str() );
  }

  return newGlyph;
}



float Alphabet::GetKerningAmount( wchar_t first, wchar_t second ) const
{
  if ( !FT_HAS_KERNING( face ) )
  {
    return 0.f;
  }

  FT_Vector akerning;

  FT_UInt first_index = FT_Get_Char_Index( face, first ); 
  FT_UInt second_index = FT_Get_Char_Index( face, second ); 

  if ( FT_Get_Kerning( face, first_index, second_index, FT_KERNING_DEFAULT, &akerning ) )
  {
    NI_ALWAYS_ASSERT( "Can't find kerning for font" );
    return 0.f;
  }

  return float( FromFTPosNoScale( akerning.x ) ) * widthK;
}



void Alphabet::SetupMetric( SFontMetric & metric, float gapAbove, float gapUnder, const SFontRenderTweaks & tweaks ) const
{
  metric.ascent = fontAscent;
  metric.descent = fontHeight - fontAscent;

  metric.gapAbove = gapAbove;
  metric.gapUnder = gapUnder;

  metric.tweaks = tweaks;

  metric.defaultGlyphWidth = spaceGlyph.A + spaceGlyph.B + spaceGlyph.C;
}



float Alphabet::GetStringLength( const wchar_t *text, unsigned length, float maxWidth, unsigned * charsFitIn, const SFontRenderTweaks & tweaks )
{
  if ( length == 0 )
    return 0.f;

  float width = 0.f;

  float addAdvanceLeftover = 0;

  unsigned int i = 0;
  for ( ; i < length; ++i )
  {
    wchar_t wch = text[i];
    if ( wch == 0 ) // consider: 'length' is limiter, not real length, so check zero-terminated here
      break;

    const Glyph & glyph = GetGlyph( wch );

    float widthBackup = width;

    if ( i > 0 )
    {
      width += glyph.A;
      width += GetKerningAmount(text[i - 1], text[i]);
    }

    addAdvanceLeftover += tweaks.additionalAdvance;
    float roundedAdvance = widthK * floorf( addAdvanceLeftover / widthK + 0.5f );
    addAdvanceLeftover -= roundedAdvance;

    width += glyph.B + roundedAdvance;

    //Space's glyph only have positive C and A=B=0
    if ( wch == L' ' )
      width += glyph.C * tweaks.spaceScale;

    if( charsFitIn && maxWidth )
      if( width > maxWidth + 1e-3f )
      {
        width = widthBackup;
        break;
      }

    if ( wch != L' ' )
      if ( i + 1 < length )
        if ( text[ i + 1 ] )
          width += glyph.C;
  }

  if( charsFitIn )
    *charsFitIn = i;

  return width;
}



void Alphabet::DrawString( const wchar_t *text, unsigned length, float _x, float _y, Render::BaseMaterial * fontMaterial, const Render::Color & color, const Rect & cropRect, const SFontRenderTweaks & tweaks, const CVec2& _scale )
{
  if ( length == 0 )
    return;

  if ( !cropRect.IsEmpty() )
    Render::GetUIRenderer()->PushCrop( cropRect );
  else
    Render::GetUIRenderer()->PushNoCrop();

  Render::SMaterialParams params;
  params.color0 = color;

  float x = widthK * floorf( _x / widthK );
  float y = heightK * floorf( _y / heightK );

  float addAdvanceLeftover = 0;

  Render::GetUIRenderer()->BeginText();
  for ( unsigned int i = 0; i < length; ++i )
  {
    wchar_t wch = text[i];
    if ( wch == 0 ) // consider: 'length' is limiter, not real length, so check zero-terminated here
      break;

    const Glyph& glyph = GetGlyph( wch );

    if ( i > 0 )
    {
      x += glyph.A * _scale.x;
      x += GetKerningAmount(text[i - 1], text[i]) * _scale.x;
    }

    float xx = x;
    float xx2 = xx + glyph.width * _scale.x;

    float yy = y + ( fontAscent - glyph.offsetH ) * _scale.y;
    float yy2 = yy + glyph.height * _scale.y;

    Render::UIQuad quad;

    quad.tl.y = yy;
    quad.br.y = yy2;

    quad.tl.x = xx;
    quad.br.x = xx2;

    quad.uv.u = glyph.u1;
    quad.uv.v = glyph.v1;

    quad.uvl.u = glyph.u2;
    quad.uvl.v = glyph.v2;

    Render::GetUIRenderer()->AddTextQuad( quad, params );

    addAdvanceLeftover += tweaks.additionalAdvance;
    float roundedAdvance = widthK * floorf( addAdvanceLeftover / widthK + 0.5f );
    addAdvanceLeftover -= roundedAdvance;

    const float spaceScale = ( wch == ' ' ) ? tweaks.spaceScale : 1.0f;

    x += ( roundedAdvance + ( glyph.C + glyph.B ) * spaceScale ) * _scale.x;
  }

  Render::GetUIRenderer()->EndText( fontMaterial );

  Render::GetUIRenderer()->PopCrop();
}

} // namespace UI
