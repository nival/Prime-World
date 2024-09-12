#include "TamarinPCH.h"

#include "Sound.h"
#include "../../FlashMovieAvmCore.h"
#include "../../Characters.h"
#include "../../FlashMovie.h"
#include "../../SoundData.h"

#include "Sound/EventScene.h"

namespace avmplus
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundObject::SetSoundData( flash::SoundData * _soundData )
{
//  NI_VERIFY( _soundData, "invalid sound character data", return);
//  simpleSound = _soundData->GetSimpleSound();
}

//------------------------------FLASH METHODS----------------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double SoundObject::extract( ByteArrayObject* target, double length, double startPosition )
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundObject", "extract" );
  return (double)0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundObject::_load( URLRequestObject* stream, bool checkPolicyFile, double bufferTime )
{
  AvmString className = this->vtable->traits->formatClassName();

  //check. may be we have data associated with this class
  flash::ICharacter * soundCharacter = FlashCore()->GetMovie()->GetCharacterByName(className);

  NI_VERIFY( soundCharacter,"for now no other way to load other than from symbol class link", return);

  if ( soundCharacter )
  {
    soundCharacter->InitObject(this);
  }

  return (void)0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SoundObject::close()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundObject", "close" );
  return (void)0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
avmplus::AvmString SoundObject::get_url()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundObject", "get_url" );
  return (AvmString)0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint SoundObject::get_bytesLoaded()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundObject", "get_bytesLoaded" );
  return (uint)0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SoundChannelObject* SoundObject::play( double startTime, int loops, SoundTransformObject* sndTransform )
{
  Stringp stringProperty = core()->internConstantStringLatin1( "soundEvent" ); 

  if ( hasStringProperty( stringProperty ) )
  {
    Stringp eventName = core()->string( getStringProperty( stringProperty ) );
    StUTF8String nameT( eventName );

    NDb::DBFMODEventDesc eventDesc;

    eventDesc.eventName = nameT.c_str();
    eventDesc.groupName = "UI";

    NSoundScene::EventStart( eventDesc );
  }

  return (SoundChannelObject*)0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double SoundObject::get_length()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundObject", "get_length" );
  return (double)0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScriptObject/*ID3Info*/ * SoundObject::get_id3()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundObject", "get_id3" );
  return (ScriptObject/*ID3Info*/ *)0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int SoundObject::get_bytesTotal()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundObject", "get_bytesTotal" );
  return (int)0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool SoundObject::get_isBuffering()
{
  NI_ALWAYS_ASSERT("Not yet implemented"); // SwfDebugLog::CallLog( "SoundObject", "get_isBuffering" );
  return (bool)0;
}


}
