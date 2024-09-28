#include "CommonMaterialFunc.inl"
void ModifyColor(const HDRColor &mul, const HDRColor &add);
void ModifyOpacity(float opacity);
void ModifyBlendMode( NDb::BlendMode blendMode, bool isSetDefaultBlendMode );

static RenderState CorrectRS(const RenderState &_src)
{
  RenderState result(_src);
  if(NDb::BLENDMODE_LERPBYALPHA <= result.GetBlendMode() && result.GetBlendMode() <= NDb::BLENDMODE_ADDCOLORMULALPHA)
    result.SetBlendMode(NDb::BLENDMODE_PREMULTIPLIEDLERP);
  if(result.GetAlphaTest() == NDb::ONOFFSTATE_OFF)
    result.SetAlphaTestRef(127);

  return result;
}

// Get corrected render state and samplers representation for SortID calculation needs.
// Given null pointer, return size of required memory block
virtual int GetRSandSamplersRep(PBYTE _pRep, int *_pProcessedSize = 0) const;

friend class ParticlesManager;
friend class ParticleFX;

public:
const float GetScale() const { return scale; }
static void SetInstancingFlag(bool enabled);

