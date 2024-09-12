//--------------------------------------------------------------------------------------
// File: Instancing.fx
//
// The effect file for the Instancing sample.  
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
#include "../Shaders/_common.hlsl"

//float4 g_Position : register(VSHADER_LOCALCONST0);
//float3 g_Size     : register(VSHADER_LOCALCONST1);


//-----------------------------------------------------------------------------
// Name: VS_ConstantsInstancing
// Type: Vertex shader (Constants Instancing)
// Desc: This shader computes standard transform and lighting for unlit, texture-mapped triangles.
//-----------------------------------------------------------------------------
void VS_main( float3 vPos : POSITION, out float4 oPos : POSITION )
{
//	// Use the fourth component of the vBoxInstance to rotate the box:
//  float2 Rotation; // Rotation.x = cos(g_Position.w), Rotation.y = sin(g_Position.w)
//  sincos(g_Position.w, Rotation.y, Rotation.x);
//  float3 pos = vPos * g_Size;
//	float3 rotatedPos = float3(pos.x * Rotation.x + pos.y * Rotation.y + g_Position.x,
//                             pos.y * Rotation.x - pos.x * Rotation.y + g_Position.y,
//                             pos.z + g_Position.z);

	// Transform the position from object space to homogeneous projection space
  float3 rotatedPos = mul( float4( vPos, 1.0 ), World );
	oPos = mul( float4( rotatedPos, 1.0 ), ViewProjection );
}
