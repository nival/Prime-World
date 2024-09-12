#include "TamarinPCH.h"

#include "Natives/display/MorphShape.h"

#include "FlashMovieAvmCore.h"
#include "MorphCharacter.h"

namespace flash
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
avmplus::ClassClosure* MorphCharacter::GetDefaultDisplayClass( FlashMovieAvmCore * flashCore )
{
  return flashCore->GetClassCache().GetClass<avmplus::MorphShapeClass>( EFlashClassID::MorphShapeClass );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MorphCharacter::InitObject( avmplus::ScriptObject* _scriptObject )
{
  avmplus::MorphShapeObject* morphObject = dynamic_cast<avmplus::MorphShapeObject*>( _scriptObject );
  NI_ASSERT( morphObject, "Try to init DisplayObject by wrong character" );
 
  if ( morphData )
    morphObject->SetMorphData( morphData );

  if ( useScale9Grid )
    morphObject->SetScale9Grid( scale9Grid );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MorphCharacter::Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID )
{
  NI_ASSERT( !morphData, "morphData already initialized" );

  morphData = new MorphData();
  morphData->Load( streamReader, tagInfo, characterID );
}

}