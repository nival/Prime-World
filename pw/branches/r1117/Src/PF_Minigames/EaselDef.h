#pragma once

//////////////////////////////////////////////////////////////////////////
//
// file contains common defines for all Easel minigame modules
//
//////////////////////////////////////////////////////////////////////////

namespace PF_Minigames
{
  // all supported colors
  enum DebugDrawColor
  {
    DDRAW_COLOR_BLACK	= 0xff000000,
    DDRAW_COLOR_BLUE	= 0xff0000ff,
    DDRAW_COLOR_GREEN	= 0xff00ff00,
    DDRAW_COLOR_RED	  = 0xffff0000,
    DDRAW_COLOR_WHITE	= 0xffffffff,
    DDRAW_COLOR_YELLOW	= 0xff00ffff,
    DDRAW_COLOR_MAGENTA	= 0xffff00ff,
    DDRAW_COLOR_CYAN	= 0xffffff00,
  };

  // all supported user clicks
  namespace EEaselMouseEvents
  {
    enum Enum
    {
      LeftButton,
      RightButton
    };
  }

  namespace EEaselKeyboardEvents
  {
    enum Enum
    {
      //By now only "skip movie" key is needed
      SkipMovie
    };
  }

  // Input state for easel minigame
  //TODO: join it with / replace by SEaselMouseInput from LuxDef.h
  struct EaselInputState
  {
    EaselInputState() :
    mousePos( 0, 0 ), mouseLeftButton( false ), mouseRightButton( false ) {};
    
    SVector mousePos; // mouse pos in screen coordinates
    bool mouseLeftButton;
    bool mouseRightButton;
  };

  // step info with single input state at the end of delta time
  struct EaselStepInfo
  {
    EaselStepInfo() : stepID(0), deltaTime(0) {}

    int deltaTime;		// time from last step
    uint stepID;
    EaselInputState inputState;
  };
}