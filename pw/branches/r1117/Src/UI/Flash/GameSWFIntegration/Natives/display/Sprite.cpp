#include "TamarinPCH.h"

#include "../../Characters.h"
#include "../../DisplayTags.h"
#include "../../FlashMovieAvmCore.h"
#include "../../FlashMovie.h"

#include "Sprite.h"

#include "System/InlineProfiler.h"

namespace
{
  static NDebug::DebugVar<unsigned int> totalSpriteCount( "TotalSpriteCount", "PerfCnt" );
}

namespace avmplus
{

SpriteObject::SpriteObject(SpriteClass * classType) : 
  DisplayObjectContainerObject((DisplayObjectContainerClass * )classType),
  buttonMode(false),
  useHandCursor(true),
  frameCount(1),
  nextFrameToPlay(1)
{ 
  Initialize(); 
}

SpriteObject::SpriteObject(VTable* ivtable, ScriptObject* prototype) : 
  DisplayObjectContainerObject(ivtable, prototype),
  buttonMode(false),
  useHandCursor(true),
  frameCount(1),
  nextFrameToPlay(1)
{ 
  Initialize(); 
}

void SpriteObject::Initialize()
{
  flash::FlashMovieAvmCore * flashCore = (flash::FlashMovieAvmCore*) core();

  Atom args[] = {0};

  GraphicsClass * graphicsClass = flashCore->GetClassCache().GetClass<GraphicsClass>( EFlashClassID::GraphicsClass );
  graphics = (GraphicsObject *)flashCore->atomToScriptObject(graphicsClass->construct(0, args));

  totalSpriteCount.AddValue(1);
  NI_ASSERT(totalSpriteCount.GetValue()<6000, "Flash : Sprite count > 6000");
}

SpriteObject::~SpriteObject( void )
{
  totalSpriteCount.DecValue(1);
}

void SpriteObject::constructChildren()
{
  AdvanceCharacterList( 1 );
}

void SpriteObject::stopDrag()
{
  SetDragged( false );
  SetDropTarget( 0 );

  if ( FlashCore()->GetMovie()->GetDraggedSprite() == this )
    FlashCore()->GetMovie()->SetDraggedSprite( 0, false );
}

void SpriteObject::startDrag( bool lockCenter, ScriptObject/*Rectangle*/ * bounds )
{
  SetDragged( true );

  if (!bounds)
    FlashCore()->GetMovie()->SetDraggedSprite( this, lockCenter );
  else
  {
    //public var width:Number;
    //public var height:Number;
    //public var x:Number;
    //public var y:Number;

    int _c_x = FlashScriptObject::GetSlotID( bounds, "x" );
    int _c_y = FlashScriptObject::GetSlotID( bounds, "y" );

    int _c_width = FlashScriptObject::GetSlotID( bounds, "width" );
    int _c_height= FlashScriptObject::GetSlotID( bounds, "height" );

    double boundsX = core()->number_d( bounds->getSlotAtom( _c_x ) ) ;
    double boundsY = core()->number_d( bounds->getSlotAtom( _c_y ) ) ;

    double boundsWidth = core()->number_d( bounds->getSlotAtom( _c_width ) ) ;
    double boundsHeight = core()->number_d( bounds->getSlotAtom( _c_height ) ) ;

    FlashCore()->GetMovie()->SetDraggedSprite( this, lockCenter, true, boundsX, boundsX + boundsWidth, boundsY, boundsY+boundsHeight );
  }
}

void SpriteObject::SetCharacter( flash::SpriteCharacter* _character ) 
{ 
  spriteCharacter = _character;
  nextFrameToPlay = 1;
  frameCount = spriteCharacter ? spriteCharacter->GetFramesCount(): 1;
}

void SpriteObject::GotoFrame( int frameId )
{
  AdvanceCharacterList( frameId );
  RunFrameScript( frameId );
}

void SpriteObject::AdvanceCharacterList( int frameId )
{
  NI_PROFILE_FUNCTION

  if ( nextFrameToPlay -1== frameId )
    return;

  if ( ( nextFrameToPlay -1> frameId ) )
  {
    ClearSWFObjects();
    nextFrameToPlay = 1;
  }

  if ( spriteCharacter )
  {
    NI_PROFILE_BLOCK( "Execute tags" )

    for (;nextFrameToPlay<=frameId; nextFrameToPlay++)
    {
      flash::DisplayTags * tags = spriteCharacter->GetTags(nextFrameToPlay);
      if (!tags)
        continue;

      for (flash::DisplayTags::iterator tag = tags->begin(); tag!=tags->end(); tag++)
      {
        (*tag)->Execute( this, nextFrameToPlay);
      }
    }
  }
}



}