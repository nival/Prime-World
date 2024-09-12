#pragma once

namespace NMainLoop
{

void  UpdateTime();
void  MarkStepFrame();
float GetTime();
NHPTimer::STime GetHPTime();
float GetTimeDelta();

float GetTimeScale();
void SetTimeScale( float scale );

void SetTemporaryTimeDelta( float val );
void SetTemporaryTime( float val );
}