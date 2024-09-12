#include "CommonMaterialFunc.inl"
void ModifyColor(const HDRColor &mul, const HDRColor &add);
void ModifyOpacity(float opacity);
void ModifyEmissive(float power);
void ModifyBlendMode( NDb::BlendMode blendMode, bool isSetDefaultBlendMode );

bool Instanceable() const;
bool SkipIDEvaluation() const;
void PrepareRendererWithBatch(const Batch &batch);
void RegisterInstancedBatch(const Batch &batch);

public:
void SetBlendModeOverride(bool state) { isBlendModeOverrided = state ? 1 : 0; } 

