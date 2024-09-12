#pragma once

#include "../PlayerGlobalIncludes.h"

namespace flash
{
  class FlashMovieAvmCore;
}

namespace avmplus
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StageAlign : public MMgc::GCRoot
{
public:
  enum Enum
  {
    TOP,
    BOTTOM,
    LEFT,
    RIGHT,
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
  };

  explicit StageAlign( AvmCore * _core );

  Enum GetValue() const { return value; }

  void SetStringValue( AvmString _stringValue );
  AvmString GetStringValue();

private:
  DRC(Stringp) kTOP;
  DRC(Stringp) kBOTTOM;
  DRC(Stringp) kLEFT;
  DRC(Stringp) kRIGHT;
  DRC(Stringp) kTOP_LEFT;
  DRC(Stringp) kTOP_RIGHT;
  DRC(Stringp) kBOTTOM_LEFT;
  DRC(Stringp) kBOTTOM_RIGHT;

  Enum value;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StageScaleMode : public MMgc::GCRoot
{
public:
  enum Enum
  {
    EXACT_FIT,
    NO_BORDER,
    NO_SCALE,
    SHOW_ALL
  };

  explicit StageScaleMode( AvmCore * _core );

  Enum GetValue() const { return value; }

  void SetStringValue( AvmString _stringValue );
  AvmString GetStringValue();

private:
  DRC(Stringp) kEXACT_FIT;
  DRC(Stringp) kNO_BORDER;
  DRC(Stringp) kNO_SCALE;
  DRC(Stringp) kSHOW_ALL;

  Enum value;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StageQuality : public MMgc::GCRoot
{
public:
  enum Enum
  {
    BEST,
    LOW,
    MEDIUM,
    HIGH
  };

  explicit StageQuality( AvmCore * _core );

  Enum GetValue() const { return value; }

  void SetStringValue( AvmString _stringValue );
  AvmString GetStringValue();

private:
  DRC(Stringp) kBEST;
  DRC(Stringp) kLOW;
  DRC(Stringp) kMEDIUM;
  DRC(Stringp) kHIGH;

  Enum value;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StageDisplayState : public MMgc::GCRoot
{
public:
  enum Enum
  {
    FULL_SCREEN,
    NORMAL,
  };

  explicit StageDisplayState( AvmCore * _core );

  Enum GetValue() const { return value; }

  void SetStringValue( AvmString _stringValue );
  AvmString GetStringValue();

private:
  DRC(Stringp) kFULL_SCREEN;
  DRC(Stringp) kNORMAL;

  Enum value;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ColorCorrection : public MMgc::GCRoot
{
public:
  enum Enum
  {
    DEFAULT,
    ON,
    OFF,
  };

  explicit ColorCorrection( AvmCore * _core );

  Enum GetValue() const { return value; }

  void SetStringValue( AvmString _stringValue );
  AvmString GetStringValue();

private:
  DRC(Stringp) kDEFAULT;
  DRC(Stringp) kON;
  DRC(Stringp) kOFF;

  Enum value;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ColorCorrectionSupport : public MMgc::GCRoot
{
public:
  enum Enum
  {
    DEFAULT_OFF,
    UNSUPPORTED,
    DEFAULT_ON,
  };

  explicit ColorCorrectionSupport( AvmCore * _core );

  Enum GetValue() const { return value; }

  void SetStringValue( AvmString _stringValue );
  AvmString GetStringValue();

private:
  DRC(Stringp) kDEFAULT_OFF;
  DRC(Stringp) kUNSUPPORTED;
  DRC(Stringp) kDEFAULT_ON;

  Enum value;
};

}