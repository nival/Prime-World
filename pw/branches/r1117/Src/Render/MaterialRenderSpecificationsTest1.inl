
SHMatrix world;
Copy( &world, instanceConstants.worldMatrix );
SHMatrix MVP = sceneConstants.viewProjection*world;

Render::Renderer::SetVertexShaderConstants(0, 4, &MVP);
Render::Renderer::SetVertexShaderConstants(4, 4, &world);
Render::Renderer::SetVertexShaderConstants(12, 4, &sceneConstants.viewProjection);

SHMatrix matrix;
matrix.HomogeneousInverse(sceneConstants.view);

CVec4 eyePos = matrix.GetTrans4();
Render::Renderer::SetVertexShaderConstants(8, 1, &eyePos);
static const float worldscale = 1.f / (64.f * 2.5f);
Render::Renderer::SetVertexShaderConstants( 255, 1, &worldscale );
//////////////////////////////////////////////////////////////////////////
Render::Renderer::SetPixelShaderConstants(0, 1, &sceneConstants.sunLightDirection);
ASSERT(instanceConstants.lightCount < 3);
OmniLightCountPinValue = (NDb::OmniLightCountPin) instanceConstants.lightCount;
for (unsigned int i = 0; i < instanceConstants.lightCount; ++i)
{
	Render::Renderer::SetPixelShaderConstants(4+i, 1, &instanceConstants.lightList[i]->position);
	Render::Renderer::SetPixelShaderConstants(20+i, 1, &instanceConstants.lightList[i]->diffuseColor);
	Render::Renderer::SetPixelShaderConstants(36+i, 1, &instanceConstants.lightList[i]->radius);
}

Render::Renderer::SetPixelShaderConstants(1, 1, &(this->ObjectColor));
Render::Renderer::SetPixelShaderConstants(2, 1, &(this->EmissiveMultiplier));