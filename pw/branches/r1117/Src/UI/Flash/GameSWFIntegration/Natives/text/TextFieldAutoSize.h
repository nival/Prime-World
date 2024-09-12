#pragma once

#include <Render/FlashRendererInterface.h>

#include "../PlayerGlobalIncludes.h"

namespace flash
{
  class FlashMovieAvmCore;
}

namespace avmplus
{

namespace ETextFieldAutoSize
{
  enum Enum
  {
    CENTER,
    LEFT,
    NONE,
    RIGHT
  };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TextFieldAutoSize : public MMgc::GCRoot
{
public:

  explicit TextFieldAutoSize( AvmCore * _core );

  void SetValue( ETextFieldAutoSize::Enum _value ) { value = _value; }
  ETextFieldAutoSize::Enum GetValue() const { return value; }

  void SetStringValue( AvmString _stringValue );
  AvmString GetStringValue();

private:
  DRC(Stringp) kCENTER;
  DRC(Stringp) kLEFT;
  DRC(Stringp) kNONE;
  DRC(Stringp) kRIGHT;

  ETextFieldAutoSize::Enum value;
};

}