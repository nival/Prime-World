bool Instanceable() const;
bool SkipIDEvaluation() const;
void PrepareRendererWithBatch(const Batch &batch);
void RegisterInstancedBatch(const Batch &batch);

// Get corrected render state and samplers representation for SortID calculation needs.
// Given null pointer, return size of required memory block
virtual int GetRSandSamplersRep(PBYTE _pRep, int *_pProcessedSize = 0) const;

public:
static ShadowMaterial* CreateMaterial(BaseMaterial *pMaterial);

bool oldInstancing;
