#include "TamarinPCH.h"

#include <System/InlineProfiler.h>

#include "../../FlashMovieAvmCore.h"
#include "../../FlashMovie.h"
#include "../../Characters.h"

#include "MovieClip.h"

namespace avmplus
{

MovieClipObject::MovieClipObject(MovieClipClass * classType) : 
  SpriteObject((SpriteClass * )classType),
  enabled(true),
  frameTime(1.f / 24.f),
  currentFrameTime(0.f),
  isPlaying(true),
  firstAdvance(true)
{}

MovieClipObject::MovieClipObject(VTable* ivtable, ScriptObject* prototype) : 
  SpriteObject(ivtable, prototype),
  enabled(true),
  frameTime(1.f / 24.f),
  currentFrameTime(0.f),
  isPlaying(true),
  firstAdvance(true)
{

}

void MovieClipObject::_Init()
{
  AvmString className = this->vtable->traits->formatClassName();

  //check. may be we have data associated with this class
  flash::ICharacter * movieCharacter = FlashCore()->GetMovie()->GetCharacterByName(className);

  if ( movieCharacter )
  {
    movieCharacter->InitObject( this );
  }
}

MovieClipObject::~MovieClipObject()
{
  
}

int MovieClipObject::get_totalFrames() 
{ 
  return GetFrameCount(); 
}

int MovieClipObject::ConvertAtomToFrameNumber( AvmBox frame )
{
  if ( AvmCore::isNumber( frame ) )
  {
    return core()->toInteger( frame );
  }
  else if ( AvmCore::isString( frame ) )
  {
    AvmString frameLabel = core()->atomToString( frame );
    StUTF8String frameLabelT( frameLabel );

    int frameID = spriteCharacter->GetFrameByLabel( frameLabelT.c_str() );

    if ( frameID != -1 )
      return frameID;

    frameID = FlashCore()->GetMovie()->GetFrameNumber( frameLabelT.c_str() );

    if ( frameID != -1 )
      return frameID;
  }
  else
  {
    NI_ALWAYS_ASSERT("Wrong type for frame presentation");
  }

  return 1;
}

void MovieClipObject::gotoAndPlay(AvmBox frame, AvmString scene)
{
  int intFrame = ConvertAtomToFrameNumber( frame );

  GotoFrame( intFrame );

  isPlaying = true;
}

void MovieClipObject::gotoAndStop(AvmBox frame, AvmString scene)
{
  int intFrame = ConvertAtomToFrameNumber( frame );

  GotoFrame( intFrame );

  isPlaying = false;
}

void MovieClipObject::prevFrame()
{
  NI_ALWAYS_ASSERT("Not yet implemented");
}

void MovieClipObject::nextFrame()
{
  NI_ALWAYS_ASSERT("Not yet implemented");
}

void MovieClipObject::OnAddedToDisplayList()
{
  FlashCore()->GetMovie()->SubscribeForAdvanceMC( this );
}

void MovieClipObject::OnRemovedFromDisplayList()
{
  FlashCore()->GetMovie()->UnsubscribeForAdvanceMC( this );
}

void MovieClipObject::AdvanceNextFrame()
{
  NI_PROFILE_HEAVY_FUNCTION

  if ( firstAdvance )
  {
    if ( GetNextFrameToPlay() == 2 )
      RunFrameScript( 1 );

    firstAdvance = false;
  }

  if ( isPlaying )
  {
    int frameCount = GetFrameCount();

    if ( frameCount > 1 )
    {
      int frameToPlay = GetNextFrameToPlay();
      if (frameToPlay>frameCount)
        frameToPlay = 1;

      AdvanceCharacterList( frameToPlay);
    }
  }
}

void MovieClipObject::RunThisFrameScript()
{
  RunFrameScript( get_currentFrame() );
}

void MovieClipObject::RunFrameScript( int frameId )
{
  if (  frameScripts.find(frameId)!= frameScripts.end())
  {
    NI_PROFILE_BLOCK("MovieClipObject::RunFrameScript()");
    FunctionObject* functionObject = frameScripts[frameId]->Get()->script;

    if ( functionObject )
    {
      Atom argv[] = { atom() };
      functionObject->call( 0, argv );
    }
  }
}

void MovieClipObject::addFrameScript( AvmBox* argv, int argc )
{
  NI_VERIFY( argc % 2 == 0, "Wrong parameter number", return );

  for ( int i = 0; i < argc; i += 2 )
  {
    int frameNumber = core()->toInteger( argv[i] );
    frameNumber += 1; // frame number here is 0 based

    NI_VERIFY ( core()->isFunction( argv[i+1] ), "Wrong parameter type", continue ); 

    FunctionObject* functionObject = dynamic_cast<FunctionObject*>( core()->atomToScriptObject( argv[i+1] ) );

    NI_VERIFY ( functionObject, "Wrong parameter type", continue ); 

    frameScripts[frameNumber] = new FrameScriptWrapper(new FrameScript(core()->GetGC(), functionObject));
  }

  return (void)0;
}

void MovieClipObject::stop() 
{ 
  isPlaying = false; 
}

void MovieClipObject::play() 
{ 
  isPlaying = true; 
}

}

NI_DEFINE_REFCOUNT(avmplus::FrameScriptWrapper);