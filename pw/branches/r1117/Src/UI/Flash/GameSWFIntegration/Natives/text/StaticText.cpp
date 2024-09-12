#include "TamarinPCH.h"

#include "StaticText.h"
#include "../../TextTagsData.h"
#include "../../FontTags.h"
#include "../../FontsRenderInterface.h"
#include "../../FlashMovie.h"


namespace avmplus
{

StaticTextObject::StaticTextObject( StaticTextClass * classType ) : 
  DisplayObjectObject( (DisplayObjectClass*)classType ) 
{ 
  InitializeStaticText(); 
}

StaticTextObject::StaticTextObject( VTable * ivtable, ScriptObject * delegate ) : 
  DisplayObjectObject( ivtable, delegate ) 
{ 
  InitializeStaticText(); 
}

void StaticTextObject::InitializeStaticText()
{
  NI_ALWAYS_ASSERT("We should not use Static Text");

  data = new flash::StaticTextTagData;
}

void StaticTextObject::DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode )
{
  NI_ASSERT( data, "" );

  for ( int i = 0; i < data->textRecords.size(); ++i )
  {
    flash::STextTag_TEXTRECORD & tr = data->textRecords[i];
    if ( !cachedFonts[i] || !tr.font )
      continue;

//     flash::SWF_RECT bounds;  
//     GetBounds( bounds );

    float x = ( tr.xOffset ) / flash::TWIP;
    float y = ( tr.yOffset ) / flash::TWIP;

    for( int j = 0; j < tr.rawText.size(); ++j )
    {
      flash::SWF_MATRIX advance;
      advance.ConcatenateTranslation( x, y );

      flash::SWF_MATRIX glyphMatrix;
      glyphMatrix.Concatenate( _matrix, advance );
      //FIXME: optimize this per-glyph matrix madness

      flash::SWF_RGBA finalColor;
      _cxform.Transform( finalColor, tr.textColor );

      flash::Movie* flashMovie = FlashCore()->GetMovie();

      if ( flashMovie && flashMovie->IsBlocked() )
      {
        flashMovie->FadeBlockedColor( finalColor, IsNonBlocked() );
      }

      cachedFonts[i]->SetBevel( false, flash::SWF_RGBA(0,0,0) );
      cachedFonts[i]->RenderGlyph( tr.rawText[j], glyphMatrix, finalColor );

      x += tr.glyphEntries[j].glyphAdvance;
    }
  }
}


void StaticTextObject::GetBounds( flash::SWF_RECT& _rect )
{
  _rect = data->textBounds;
}


void StaticTextObject::SetData( flash::StaticTextTagData * _data )
{
  NI_ASSERT( data, "" );
  data->Copy( _data );

  flash::IFontRender * _fontRender = FlashCore()->GetMovie()->FontRender();
  if ( !_fontRender )
    return;

  cachedFonts.resize( data->textRecords.size() );

  for ( int i = 0; i < data->textRecords.size(); ++i )
  {
    flash::STextTag_TEXTRECORD & tr = data->textRecords[i];
    if ( !tr.font )
      continue;

    cachedFonts[i] = tr.font->GetRenderable( _fontRender, tr.textHeight );
  }
}

} //namespace avmplus
