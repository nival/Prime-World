#include "CommonMaterialFunc.inl"
void ModifyColor(const HDRColor &mul, const HDRColor &add);
void ModifyOpacity(float opacity);
void ModifyBlendMode( NDb::BlendMode blendMode, bool isSetDefaultBlendMode );
void ModifyUVOffset(float u, float v);