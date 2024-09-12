#pragma once

namespace PF_Minigames
{
  struct EaselConst
  {
    static int   Get_EASEL_LEVEL_MIN();
    static int   Get_EASEL_LEVEL_MAX();

    static int   Get_EASEL_PAINT_MIN();
    static int   Get_EASEL_PAINT_MAX();

    static float Get_LUX_LOGIC_TIME_MULTIPLIER();

    static float Get_BORDER_WIDTH_OFFSET();          // border offset width
    static float Get_BORDER_HEIGHT_OFFSET();         // border offset height
    static float Get_LOGIC_FIELD_WIDTH();            // logical width
    static float Get_LOGIC_FIELD_HEIGHT();           // logical height

    static float Get_POLYLINE_SEGMENT_SIZE();

    static float Get_BALL_DEF_DIAMETER();   // default ball radius
    static float Get_BALL_DEF_RADIUS();

    static int   Get_MIN_BALLS_TO_BLOW();            // minimal chain balls amount to blow
  };

} // namespace PF_Minigames