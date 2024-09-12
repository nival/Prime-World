#include "_commonPostProcess.h"
#include "_commonDepthRead.h"

VS_OUTPUT_DR VS_main(VS_INPUT Input, out float4 Position : POSITION)
{
  VS_OUTPUT_DR Output;
  Output.ZScale = VS_DepthReadParams(Input, Output.Texcoord, Position);

  return Output;
}
