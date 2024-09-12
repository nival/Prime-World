//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateInternals()
{
//     priority = (renderState.GetBlendMode() != NDb::BLENDMODE_OFF ? PRIORITY_TRANSPARENT : PRIORITY_MESHES_OPAQUE);
// 
//     bool isEmissiveUsed = (
//       LightModePinValue == NDb::LIGHTMODEPIN_DIFFUSEEMISSIVE || 
//       LightModePinValue == NDb::LIGHTMODEPIN_DIFFUSESPECULAREMISSIVE || 
//       LightModePinValue == NDb::LIGHTMODEPIN_DIFFUSESPECULARTOEMISSIVE);
//    renderState.SetEmissive(isEmissiveUsed ? NDb::ONOFFSTATE_ON : NDb::ONOFFSTATE_OFF);
}

void OnPrepareRender()
{
  Material::OnPrepareRender();

  CVec4 opacityEmissiveReflectivitySpecPower(opacity, 0, 0, 0);
  GetRenderer()->SetPixelShaderConstantsVector4(OPACITY_AND_OTHERS, opacityEmissiveReflectivitySpecPower);

//     const SceneConstants &sceneConst = SceneConstants::Global();
//     HDRColor color; 
//     color.Mul(sceneConst.ambientColor, ambientColor);
//     GetRenderer()->SetPixelShaderConstantsHDRColor(BASICMAT_AMBIENT, color);
//     color.Mul(sceneConst.diffuse1Color, diffuse1Color);
//     GetRenderer()->SetPixelShaderConstantsHDRColor(BASICMAT_DIFFUSE1, color);
//     color.Mul(sceneConst.diffuse2Color, diffuse2Color);
//     GetRenderer()->SetPixelShaderConstantsHDRColor(BASICMAT_DIFFUSE2, color);
}

void ModifyOpacity(float opacity_)
{
//     if (!pDbMaterial)
//       return;

  opacity = opacity_;
//     if (opacity == 1.0f)
//     {
//       renderState.SetBlendMode(pDbMaterial->renderState.blendMode);
//       renderState.SetAlphaTest(pDbMaterial->renderState.alphaTest);
//       LightModePinValue = pDbMaterial->LightModePinValue;
//     }
//     else
//     {
//       switch (pDbMaterial->LightModePinValue)
//       {
//       case NDb::LIGHTMODEPIN_DIFFUSE: LightModePinValue = NDb::LIGHTMODEPIN_DIFFUSEOPACITY; break;
//       case NDb::LIGHTMODEPIN_DIFFUSESPECULAR: LightModePinValue = NDb::LIGHTMODEPIN_DIFFUSESPECULAROPACITY; break;
//       case NDb::LIGHTMODEPIN_DIFFUSEEMISSIVE: LightModePinValue = NDb::LIGHTMODEPIN_DIFFUSEOPACITY; break;
//       case NDb::LIGHTMODEPIN_DIFFUSESPECULAREMISSIVE: 
//       case NDb::LIGHTMODEPIN_DIFFUSESPECULARTOEMISSIVE:
//         LightModePinValue = NDb::LIGHTMODEPIN_DIFFUSESPECULAROPACITY; 
//         break;
//       }
//       renderState.SetBlendMode(NDb::BLENDMODE_LERPBYALPHA);
//       renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
//     }
//     UpdateStaticShaderIndex();
//     UpdateInternals();
}
