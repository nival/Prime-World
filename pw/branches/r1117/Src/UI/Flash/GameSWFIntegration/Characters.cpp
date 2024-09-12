#include "TamarinPCH.h"

#include "Characters.h"
#include "FlashMovieAvmCore.h"
#include "FlashMovie.h"

#include "SoundData.h"

#include "Natives/display/Bitmap.h"
#include "Natives/display/BitmapData.h"
#include "Natives/display/Shape.h"
#include "Natives/display/Sprite.h"
#include "Natives/display/MovieClip.h"
#include "Natives/media/Sound.h"

namespace flash
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
avmplus::ClassClosure* ShapeCharacter::GetDefaultDisplayClass( FlashMovieAvmCore * flashCore )
{
  return flashCore->GetClassCache().GetClass<avmplus::ShapeClass>( EFlashClassID::ShapeClass );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShapeCharacter::InitObject( avmplus::ScriptObject* _scriptObject )
{
  avmplus::ShapeObject* shapeObject = dynamic_cast<avmplus::ShapeObject*>( _scriptObject );
  NI_ASSERT( shapeObject, "Try to init DisplayObject by wrong character" );

  shapeObject->SetShape( shapeDesc );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShapeCharacter::Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID )
{
  shapeDesc.Load( streamReader, tagInfo, characterID );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
avmplus::ClassClosure* SpriteCharacter::GetDefaultDisplayClass( FlashMovieAvmCore * flashCore )
{
  return flashCore->GetClassCache().GetClass<avmplus::SpriteClass>( EFlashClassID::SpriteClass );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpriteCharacter::InitObject( avmplus::ScriptObject* _scriptObject )
{
  avmplus::SpriteObject* spriteObject = dynamic_cast<avmplus::SpriteObject*>(_scriptObject);
  NI_ASSERT( spriteObject, "Try to init DisplayObject by wrong character" );
  
  spriteObject->SetCharacter( this );

  if ( useScale9Grid )
    spriteObject->SetScale9Grid( scale9Grid );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SpriteCharacter::GetFrameByLabel( const nstl::string& fameLabel )
{
  FrameLabelMap::iterator it  = frameLabelMap.find( fameLabel );

  if ( it != frameLabelMap.end() )
    return it->second;

  return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SpriteCharacter::AddFrameLabel( int frameId, const nstl::string& fameLabel )
{
  FrameLabelMap::iterator it = frameLabelMap.find( fameLabel );

  NI_ASSERT( it == frameLabelMap.end(), "Duplicated frame label" );

  frameLabelMap[fameLabel] = frameId;
}

DisplayTags * SpriteCharacter::GetTags( int frame )
{
   if (displayTagsMap.find(frame) == displayTagsMap.end())
     return 0;

   return &(displayTagsMap[frame]);
}

void SpriteCharacter::AddDisplayTag( IDisplayTag* _displayTag )
{
  if ( !_displayTag )
    return;

  displayTagsMap[frameToFill].push_back( _displayTag );
  _displayTag->CountFrames(frameToFill);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MovieCharacter::InitObject( avmplus::ScriptObject* _scriptObject )
{
  SpriteCharacter::InitObject( _scriptObject );

  avmplus::MovieClipObject* movieObject = dynamic_cast<avmplus::MovieClipObject*>(_scriptObject);

  if ( movieObject )
  {
    FlashMovieAvmCore * flashCore = (FlashMovieAvmCore *)movieObject->core();
    movieObject->SetFrameTime( flashCore->GetMovie()->GetFrameTime() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
avmplus::ClassClosure* MovieCharacter::GetDefaultDisplayClass( FlashMovieAvmCore * flashCore )
{
  return flashCore->GetClassCache().GetClass<avmplus::MovieClipClass>( EFlashClassID::MovieClipClass );
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BitmapCharacter::InitWithNonDisplayObject( avmplus::ScriptObject* _scriptObject, avmplus::ScriptObject * scriptObject )
{
  avmplus::BitmapDataObject* object = dynamic_cast<avmplus::BitmapDataObject*>(scriptObject);
  NI_ASSERT( object, "Try to init BitmapCharacter with wron ScriptObject" );

  avmplus::BitmapObject* displayObject = dynamic_cast<avmplus::BitmapObject*>(_scriptObject);
  NI_ASSERT( displayObject, "Try to init BitmapObject by wrong character" );

  displayObject->set_bitmapData( object );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
avmplus::ClassClosure* BitmapCharacter::GetDefaultDisplayClass( FlashMovieAvmCore * flashCore )
{
  return flashCore->GetClassCache().GetClass<avmplus::BitmapClass>( EFlashClassID::BitmapClass );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BitmapCharacter::InitObject( avmplus::ScriptObject* _scriptObject )
{
  avmplus::BitmapObject* object = dynamic_cast<avmplus::BitmapObject*>(_scriptObject);

  if ( object )
  {
    object->SetImage( imageData );
  }
  else
  {
    avmplus::BitmapDataObject* dataObject = dynamic_cast<avmplus::BitmapDataObject*>(_scriptObject);
    dataObject->SetBitmapInfo( imageData.GetBitmapInfo() );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BitmapCharacter::Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID )
{
  NI_ASSERT( movie, "Movie should not be null" );
  imageData.Load( movie, streamReader, tagInfo, movie->IsBitmapCharacterRepeatable( characterID ) );
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundCharacter::Load( SwfStreamReader & streamReader, TagInfo & tagInfo, UI16 characterID )
{
  if ( !soundData )
    soundData = new SoundData();
  soundData->Load(streamReader,tagInfo);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundCharacter::InitObject( avmplus::ScriptObject* _scriptObject )
{
  avmplus::SoundObject* soundObject = dynamic_cast<avmplus::SoundObject*>(_scriptObject);
  NI_VERIFY( soundObject, "Try to init SoundObject by wrong character", return );

  soundObject->SetSoundData(soundData);
}



}

NI_DEFINE_REFCOUNT(flash::ICharacter);
