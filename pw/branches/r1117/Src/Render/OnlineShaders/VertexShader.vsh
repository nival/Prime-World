#include "_commonPostProcess.h"

float4 madValueUV  : register(VSHADER_LOCALCONST0);
float4 madValuePos : register(VSHADER_LOCALCONST1);

VS_OUTPUT VS_main(VS_INPUT Input, out float4 Position : POSITION)
{
  Position = float4(Input.Position.xy * madValuePos.xy + madValuePos.zw, 1.0f, 1.0f); 

  VS_OUTPUT Output;
  Output.Texcoord = madValueUV.xy * Input.Texcoord + madValueUV.zw;
  return Output;
}
