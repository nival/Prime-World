#pragma once

#include "SafeGCRoot.h"

namespace EFlashClassID
{
  enum Enum
  {
    EventClass,
    GraphicsClass,
    TransformClass,
    Matrix3DClass,
    PerspectiveProjectionClass,
    ShapeClass,
    LoaderInfoClass,
    MovieClipClass,
    SpriteClass,
    StageClass,
    BitmapClass,
    BitmapDataClass,
    MorphShapeClass,
    TimerClass,
    SimpleButtonClass,

    TimerEventClass,
    MouseEventClass,

    StaticTextClass,
    TextFieldClass,

    KeyboardEventClass,

    SoundClass,

    Last
  };
}

namespace flash
{

struct FlashClassesCashe : public SafeGCRoot<FlashClassesCashe>
{
  DRC( avmplus::ClassClosure * ) classes[ EFlashClassID::Last ];

  void RegisterClass( EFlashClassID::Enum typeID, avmplus::ClassClosure * scriptClass )
  {
    NI_ASSERT( 0 <= typeID && typeID < EFlashClassID::Last, "typeID is out of range" );
    if (!classes[ typeID ] ) 
      classes[ typeID ] = scriptClass;
  }

  template < typename _ScriptClass >
  _ScriptClass * GetClass( EFlashClassID::Enum typeID )
  {
    NI_ASSERT( 0 <= typeID && typeID < EFlashClassID::Last, "typeID is out of range" );
    return dynamic_cast<_ScriptClass *>( ( avmplus::ClassClosure * ) classes[ typeID ] );
  }

  FlashClassesCashe( MMgc::GC *gc ) : 
    SafeGCRoot( gc )
  {

  }
};
}