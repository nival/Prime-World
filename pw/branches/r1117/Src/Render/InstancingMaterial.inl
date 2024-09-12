#include "CommonMaterialFunc.inl"
void ModifyColor(const HDRColor &mul, const HDRColor &add);
void ModifyOpacity(float opacity);

public:
const Render::HDRColor &GetColorMul() const { return outputMul; }
const Render::HDRColor &GetColorAdd() const { return outputAdd; }

private: