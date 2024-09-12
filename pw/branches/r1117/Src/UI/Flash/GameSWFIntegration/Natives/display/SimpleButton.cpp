#include "TamarinPCH.h"

#include "../PlayerGlobalIncludes.h"
#include "SimpleButton.h"

namespace avmplus
{

SimpleButtonObject::SimpleButtonObject( SimpleButtonClass * classType ) :
  InteractiveObjectObject((InteractiveObjectClass*)classType),
  enabled(true),
  useHandCursor(false),
  trackAsMenu(false)
{
  
}

SimpleButtonObject::SimpleButtonObject( VTable* ivtable, ScriptObject* prototype ) :
  InteractiveObjectObject(ivtable, prototype),
  enabled(true),
  useHandCursor(false),
  trackAsMenu(false)
{

}

SimpleButtonObject::~SimpleButtonObject()
{

}

void SimpleButtonObject::_updateButton()
{

}

void SimpleButtonObject::DoRender( Render::IFlashRenderer* _renderer, const flash::SWF_MATRIX& _matrix, const flash::SWF_CXFORMWITHALPHA& _cxform, EFlashBlendMode::Enum _worldMode )
{
  if ( currentState )
    currentState->DoRender( _renderer, _matrix, _cxform, _worldMode );
}

void SimpleButtonObject::GetBounds( flash::SWF_RECT& _rect )
{
  if ( currentState )
    currentState->GetBounds( _rect );
}
  
}