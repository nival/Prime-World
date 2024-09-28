float2 opacityAndEmissive : register( OPACITY_AND_OTHERS );

#define OpacityModePinValue OpacityAndEmissiveModePinValue

void ApplyOpacity2(inout half4 color, half opacity)
{
#if OpacityModePinValue == ADDITIVEOPACITY
	color.xyz *= opacity;
#elif OpacityModePinValue == BLENDOPACITY
	color.w *= opacity;
#endif
}

void ApplyOpacity(inout half4 color) { ApplyOpacity2(color, opacityAndEmissive.x); }