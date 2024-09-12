#if (defined(FORCE_NIGHT_PARAMS_PRESENT) || (SpecularPinValue == PRESENT) || (EmissivePinValue == EMISSIVEFROMSPECULAR) || (LightingPinValue == LIGHTINGBAKED))

float2 vs_nightParams : register( VSHADER_NIGHT_PARAMS );
float2 ps_nightParams : register( PSHADER_NIGHT_PARAMS );

#endif