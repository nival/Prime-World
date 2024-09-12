#include "TamarinPCH.h"
#include "TextCharacter.h"

#include "TextTagsData.h"
#include "Natives/text/StaticText.h"

namespace flash
{


TextCharacter::TextCharacter( FontsDictionary * _fontsDict ) :
BasicTextCharacter( _fontsDict )
{
}



void TextCharacter::Load( SwfStreamReader & swf, TagInfo & tagInfo, UI16 characterID )
{
  data = new StaticTextTagData;
  data->Load( swf, tagInfo, fontsDictionary );
}



void TextCharacter::AddDisplayTag( IDisplayTag* _displayTag )
{
}



avmplus::ClassClosure * TextCharacter::GetDefaultDisplayClass( FlashMovieAvmCore * flashCore )
{
  return flashCore->GetClassCache().GetClass<avmplus::StaticTextClass>( EFlashClassID::StaticTextClass );
}



void TextCharacter::InitObject( avmplus::ScriptObject* _scriptObject )
{
  avmplus::StaticTextObject * textObject = dynamic_cast<avmplus::StaticTextObject *>( _scriptObject );

  NI_ASSERT( textObject, "" );
  NI_ASSERT( data, "" );

  textObject->SetData( data );
}



void TextCharacter::LoadCsmSettings( SwfStreamReader & swf )
{
  NI_VERIFY( data, "", return );
  data->csmSettings.Load( swf );
}

} //namespace flash
