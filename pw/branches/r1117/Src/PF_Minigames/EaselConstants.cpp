#include "stdafx.h"

#include "EaselConstants.h"

namespace PF_Minigames
{

int       EASEL_LEVEL_MIN = 0;
int       EASEL_LEVEL_MAX = 15;

const int EASEL_PAINT_MIN = 1;
const int EASEL_PAINT_MAX = 5;

float     LUX_LOGIC_TIME_MULTIPLIER = 10000.0f;  // timer multiplier

float     BORDER_WIDTH_OFFSET  = 20.0f;                                // border offset width
float     BORDER_HEIGHT_OFFSET = 30.0f;                                // border offset height
float     LOGIC_FIELD_WIDTH    = 10000.0f*LUX_LOGIC_TIME_MULTIPLIER;   // logical width
float     LOGIC_FIELD_HEIGHT   = 10000.0f*LUX_LOGIC_TIME_MULTIPLIER;   // logical height
float     PLATFORM_OFFSET      = 100.0f;

float     BALL_DEF_DIAMETER = 500.0f*LUX_LOGIC_TIME_MULTIPLIER; // default ball radius
float     BALL_DEF_RADIUS   = BALL_DEF_DIAMETER / 2.0f;

float     POLYLINE_SEGMENT_SIZE          = 100.0f*LUX_LOGIC_TIME_MULTIPLIER;

int       MIN_BALLS_TO_BLOW = 3;                                     // minimal chain balls amount to blow

int EaselConst::Get_EASEL_LEVEL_MIN() { return EASEL_LEVEL_MIN; }
int EaselConst::Get_EASEL_LEVEL_MAX() { return EASEL_LEVEL_MAX; }

int EaselConst::Get_EASEL_PAINT_MIN() { return EASEL_PAINT_MIN; }
int EaselConst::Get_EASEL_PAINT_MAX() { return EASEL_PAINT_MAX; }

float EaselConst::Get_LUX_LOGIC_TIME_MULTIPLIER() { return LUX_LOGIC_TIME_MULTIPLIER; }

float EaselConst::Get_BORDER_WIDTH_OFFSET() { return BORDER_WIDTH_OFFSET; }
float EaselConst::Get_BORDER_HEIGHT_OFFSET() { return BORDER_HEIGHT_OFFSET; }
float EaselConst::Get_LOGIC_FIELD_WIDTH() { return LOGIC_FIELD_WIDTH; }
float EaselConst::Get_LOGIC_FIELD_HEIGHT() { return LOGIC_FIELD_HEIGHT; }

float EaselConst::Get_POLYLINE_SEGMENT_SIZE() { return POLYLINE_SEGMENT_SIZE; }

float EaselConst::Get_BALL_DEF_DIAMETER() { return BALL_DEF_DIAMETER; }
float EaselConst::Get_BALL_DEF_RADIUS() { return BALL_DEF_RADIUS; }

int EaselConst::Get_MIN_BALLS_TO_BLOW() { return MIN_BALLS_TO_BLOW; }

} // namespace PF_Minigames

