#include "BasicMaterial.inl"

public:
const Render::HDRColor &GetColorMul() const { return outputMul; }
const Render::HDRColor &GetColorAdd() const { return outputAdd; }

private:
