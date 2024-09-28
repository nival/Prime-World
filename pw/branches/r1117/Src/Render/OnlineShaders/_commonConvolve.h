#include "_commonPostProcess.h"

#define ARRAY_SIZE    (1 + (KERNEL_SIZE)/2)

sampler diffuseMap : register(s0);
float4  kernel[ARRAY_SIZE] : register(PSHADER_LOCALCONST1);

float4 Texture(VS_OUTPUT Input, float2 offset)
{
  return tex2D(diffuseMap, Input.Texcoord + offset);
}

float4 PS_main(VS_OUTPUT Input) : COLOR
{
  float4 diffuse = kernel[0].z * Texture(Input, 0);

  for (int i = 1; i < ARRAY_SIZE; i++) {
    diffuse += kernel[i].z * Texture(Input, +kernel[i].xy);
    diffuse += kernel[i].w * Texture(Input, -kernel[i].xy);
  }

  return diffuse;
}
