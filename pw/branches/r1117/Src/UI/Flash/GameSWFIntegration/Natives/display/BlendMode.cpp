#include "TamarinPCH.h"

#include "../../FlashMovieAvmCore.h"

#include "BlendMode.h"

namespace avmplus
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BlendMode::BlendMode( AvmCore * _core ) :
  MMgc::GCRoot(_core->gc),
  value(EFlashBlendMode::NORMAL)
{
  kADD = _core->internConstantStringLatin1("add");
  kERASE = _core->internConstantStringLatin1("erase");
  kALPHA = _core->internConstantStringLatin1("alpha");
  kSUBTRACT = _core->internConstantStringLatin1("subtract");
  kINVERT = _core->internConstantStringLatin1("invert");
  kLIGHTEN = _core->internConstantStringLatin1("lighten");
  kMULTIPLY = _core->internConstantStringLatin1("multiply");
  kSHADER = _core->internConstantStringLatin1("shader");
  kDARKEN = _core->internConstantStringLatin1("darken");
  kNORMAL = _core->internConstantStringLatin1("normal");
  kHARDLIGHT = _core->internConstantStringLatin1("hardlight");
  kSCREEN = _core->internConstantStringLatin1("screen");
  kOVERLAY = _core->internConstantStringLatin1("overlay");
  kLAYER = _core->internConstantStringLatin1("layer");
  kDIFFERENCE = _core->internConstantStringLatin1("difference");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BlendMode::SetStringValue( AvmString _stringValue )
{
  if ( _stringValue == kADD ) value = EFlashBlendMode::ADD;
  else if ( _stringValue == kERASE ) value = EFlashBlendMode::ERASE;
  else if ( _stringValue == kALPHA ) value = EFlashBlendMode::ALPHA;
  else if ( _stringValue == kSUBTRACT ) value = EFlashBlendMode::SUBTRACT;
  else if ( _stringValue == kINVERT ) value = EFlashBlendMode::INVERT;
  else if ( _stringValue == kLIGHTEN ) value = EFlashBlendMode::LIGHTEN;
  else if ( _stringValue == kMULTIPLY ) value = EFlashBlendMode::MULTIPLY;
  else if ( _stringValue == kSHADER ) value = EFlashBlendMode::SHADER;
  else if ( _stringValue == kDARKEN ) value = EFlashBlendMode::DARKEN;
  else if ( _stringValue == kNORMAL ) value = EFlashBlendMode::NORMAL;
  else if ( _stringValue == kHARDLIGHT ) value = EFlashBlendMode::HARDLIGHT;
  else if ( _stringValue == kSCREEN ) value = EFlashBlendMode::SCREEN;
  else if ( _stringValue == kOVERLAY ) value = EFlashBlendMode::OVERLAY;
  else if ( _stringValue == kLAYER ) value = EFlashBlendMode::LAYER;
  else if ( _stringValue == kDIFFERENCE ) value = EFlashBlendMode::_DIFFERENCE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AvmString BlendMode::GetStringValue()
{
  switch ( value )
  {
  case EFlashBlendMode::ADD: return kADD;
  case EFlashBlendMode::ERASE: return kERASE;
  case EFlashBlendMode::ALPHA: return kALPHA;
  case EFlashBlendMode::SUBTRACT: return kSUBTRACT;
  case EFlashBlendMode::INVERT: return kINVERT;
  case EFlashBlendMode::LIGHTEN: return kLIGHTEN;
  case EFlashBlendMode::MULTIPLY: return kMULTIPLY;
  case EFlashBlendMode::SHADER: return kSHADER;
  case EFlashBlendMode::DARKEN: return kDARKEN;
  case EFlashBlendMode::NORMAL: return kNORMAL;
  case EFlashBlendMode::HARDLIGHT: return kHARDLIGHT;
  case EFlashBlendMode::SCREEN: return kSCREEN;
  case EFlashBlendMode::OVERLAY: return kOVERLAY;
  case EFlashBlendMode::LAYER: return kLAYER;
  case EFlashBlendMode::_DIFFERENCE: return kDIFFERENCE;
  }

  return kNORMAL;
}

} // namespace flash