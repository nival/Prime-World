#include "TamarinPCH.h"

#include "FlashMovieAvmCore.h"
#include "ButtonCharacter.h"

#include "Natives/display/SimpleButton.h"

namespace flash
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
avmplus::ClassClosure* ButtonCharacter::GetDefaultDisplayClass( FlashMovieAvmCore * flashCore )
{
  return flashCore->GetClassCache().GetClass<avmplus::SimpleButtonClass>( EFlashClassID::SimpleButtonClass );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ButtonCharacter::InitObject( avmplus::ScriptObject* _scriptObject )
{
  avmplus::SimpleButtonObject* buttonObject = dynamic_cast<avmplus::SimpleButtonObject*>( _scriptObject );
  NI_ASSERT( buttonObject, "Try to init DisplayObject by wrong character" );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ButtonCharacter::Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID )
{

}

}