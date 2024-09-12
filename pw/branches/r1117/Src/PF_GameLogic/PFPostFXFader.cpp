#include "stdafx.h"

#include "PFPostFXParams.h"
#include "PFPostFXFader.h"

namespace PF_Render
{

  PostFXFader::PostFXFader()
    : curVal(255.f)
    , endVal(255)
    , step(0)
    , timeLeft(0)
  {

    cur.InMin  = CVec4(0.f, 0.f, 0.f, 0.f);
    cur.InMax  = CVec4(1.f, 1.f, 1.f, 0.f);
    cur.OutMin = CVec4(0.f, 0.f, 0.f, 0.f);
    cur.OutMax = CVec4(1.f, 1.f, 1.f, 0.f);
    cur.Gamma  = CVec4(0.f, 0.f, 0.f, 0.f);

    cur.Color = CVec4(1.f, 1.f, 1.f, 1.f);
    cur.ColorCastCoef = 0.f;
    cur.SharpPixelSize = 0.f;
    cur.SharpCoef = 0.f;
  }

  PostFXFader::~PostFXFader()
  {
    PostFXParamsManager::SetOverrideFXParams( 0 );
  }

  void PostFXFader::FadeTo( int brightness, float time )
  {
    timeLeft = time;
    endVal = brightness;
    step = ( endVal - curVal ) / time;
    if ( time < 0 )
    {
      SetValue( endVal );
      if (endVal == 255)
        PostFXParamsManager::SetOverrideFXParams( 0 );
    }
  }

  void PostFXFader::Tick( float deltaTime )
  {
    if ( timeLeft <= 0.f )
      return;

    timeLeft -= deltaTime;
    if ( timeLeft > 0.f )
      SetValue( curVal + step * deltaTime );
    else 
    {
      SetValue( endVal );
      if (endVal == 255)
         PostFXParamsManager::SetOverrideFXParams( 0 );
    }
  }

  void PostFXFader::SetValue( float value )
  {
    curVal = value;
    float c = value / 255.f;
    
    //cur.InMax = CVec4( c, c, c , 0.f );
    cur.OutMax = CVec4( c, c, c , 0.f );
    //cur.InMin = CVec4( 1.f-c, 1.f-c, 1.f-c , 0.f );
   
    PostFXParamsManager::SetOverrideFXParams( &cur );
  }


}
