#define HLSL
#include "../GlobalMasks.h"

// vertex shader input
struct VS_INPUT
{
  float2 Position : POSITION;
};			

struct VS_OUTPUT
{
  float4 Position : POSITION;
};

float4 params : register( VSHADER_LOCALCONST2 ); 

VS_OUTPUT VS_main(VS_INPUT Input)
{
  VS_OUTPUT output;

  Input.Position.xy = Input.Position.xy * params.xy + params.zw;

  output.Position = float4(Input.Position.xy, 1.0f, 1.0f); 

  return output; 
}
