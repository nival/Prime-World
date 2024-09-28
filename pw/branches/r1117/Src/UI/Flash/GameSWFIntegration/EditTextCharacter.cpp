#include "TamarinPCH.h"
#include "EditTextCharacter.h"

#include "swf_parse.h"
#include "FontsDict.h"
#include "TextTagsData.h"

#include "Natives/text/TextField.h"


namespace flash
{


EditTextCharacter::EditTextCharacter( FontsDictionary * _fontsDict ) :
BasicTextCharacter( _fontsDict )
{
}



void EditTextCharacter::Load( SwfStreamReader & swf, TagInfo & tagInfo, UI16 characterID )
{
  data = new EditTextTagData;
  data->Load( swf, fontsDictionary );
}



void EditTextCharacter::AddDisplayTag( IDisplayTag* _displayTag )
{
}


void EditTextCharacter::InitWithNonDisplayObject( avmplus::ScriptObject* _scriptObject, avmplus::ScriptObject * scriptObject )
{
}


avmplus::ClassClosure* EditTextCharacter::GetDefaultDisplayClass( FlashMovieAvmCore * flashCore )
{
  return flashCore->GetClassCache().GetClass<avmplus::TextFieldClass>( EFlashClassID::TextFieldClass );
}



void EditTextCharacter::InitObject( avmplus::ScriptObject* _scriptObject )
{
  avmplus::TextFieldObject * textObject = dynamic_cast<avmplus::TextFieldObject *>( _scriptObject );
  NI_ASSERT( textObject, "" );
  NI_ASSERT( data, "" );

  textObject->SetData( data );
}



void EditTextCharacter::LoadCsmSettings( SwfStreamReader & swf )
{
  NI_VERIFY( data, "", return );
  data->csmSettings.Load( swf );
}

} //namespace flash
