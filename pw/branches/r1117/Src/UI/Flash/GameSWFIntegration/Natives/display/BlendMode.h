#pragma once

#include <Render/FlashRendererInterface.h>

#include "../PlayerGlobalIncludes.h"

namespace flash
{
  class FlashMovieAvmCore;
}

namespace avmplus
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BlendMode : public MMgc::GCRoot
{
public:

  explicit BlendMode( AvmCore * _core );

  void SetValue( EFlashBlendMode::Enum _value ) { value = _value; }
  EFlashBlendMode::Enum GetValue() const { return value; }

  void SetStringValue( AvmString _stringValue );
  AvmString GetStringValue();

private:
  DRC(Stringp) kADD;
  DRC(Stringp) kERASE;
  DRC(Stringp) kALPHA;
  DRC(Stringp) kSUBTRACT;
  DRC(Stringp) kINVERT;
  DRC(Stringp) kLIGHTEN;
  DRC(Stringp) kMULTIPLY;
  DRC(Stringp) kSHADER;
  DRC(Stringp) kDARKEN;
  DRC(Stringp) kNORMAL;
  DRC(Stringp) kHARDLIGHT;
  DRC(Stringp) kSCREEN;
  DRC(Stringp) kOVERLAY;
  DRC(Stringp) kLAYER;
  DRC(Stringp) kDIFFERENCE;

  EFlashBlendMode::Enum value;
};

}