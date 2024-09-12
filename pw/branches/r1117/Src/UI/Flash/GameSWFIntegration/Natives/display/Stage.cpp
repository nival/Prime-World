#include "TamarinPCH.h"

#include "Stage.h"
#include "../../../../IStageFocusHandler.h"
#include "../events/Event.h"

namespace avmplus
{

StageObject::StageObject( StageClass * classType ) : 
  DisplayObjectContainerObject(classType)
{
  Initialize();
}

StageObject::StageObject(VTable* ivtable, ScriptObject* prototype) :
  DisplayObjectContainerObject(ivtable, prototype)
{
  Initialize();
}

void StageObject::Initialize()
{
  stageFocusRect = false;
  frameRate = 25.0;
  showDefaultContextMenu = false;

  align = new StageAlign( core() ),
  scaleMode = new StageScaleMode( core() ),
  quality = new StageQuality( core() ),
  displayState = new StageDisplayState( core() ),
  colorCorrection = new ColorCorrection( core() ),
  colorCorrectionSupport = new ColorCorrectionSupport( core() );
}

StageObject::~StageObject(void)
{
  delete align;
  delete scaleMode;
  delete quality;
  delete displayState;
  delete colorCorrection;
  delete colorCorrectionSupport;
}

void StageObject::Stage_swapChildrenAt( int index1, int index2 )
{
  // [TODO] разобраться зачем у StageObject переопределен этот  метод 
  DisplayObjectContainerObject::swapChildrenAt( index1, index2 );
}

DisplayObjectObject* StageObject::Stage_removeChildAt( int index )
{
  // [TODO] разобраться зачем у StageObject переопределен этот  метод 
  return DisplayObjectContainerObject::removeChildAt( index );
}

int StageObject::get_stageHeight()
{
  return stageProvider->GetStageHeight();
}

int StageObject::get_stageWidth()
{
  return stageProvider->GetStageWidth();
}

void StageObject::set_focus( InteractiveObjectObject* newFocus )
{
  focusObject = newFocus;
  if (focusObject && stageFocusHandler)
    stageFocusHandler->OnStageFocusGain();

}

void StageObject::FireResolutionScaleCoeff( float coeff )
{
  avmplus::ClassClosure * eventClass = FlashCore()->GetClassByName( "Events.ResolutionScaleEvent" );


  Atom args[] = 
  {
    0,
    FlashCore()->doubleToAtom( 1.0f),// coeff),
  };

  if (!eventClass)
    return;

  ScriptObject * scriptObject = FlashCore()->atomToScriptObject( eventClass->construct( 1, args ) );
  EventObject * eventObject = dynamic_cast<EventObject*>( scriptObject );

  if (eventObject)
    dispatchEventFunction(eventObject);
}

}