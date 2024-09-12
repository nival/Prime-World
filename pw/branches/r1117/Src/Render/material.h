#pragma once

#include "../System/SimpleObjectsFactory.h"
#include "../System/Ring.h"
#include "../System/Singleton4DLL.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "sampler.h"
#include "states.h"
#include "priorities.h"

//#ifndef _SHIPPING
#ifdef _DEBUG
  #define _CHECK_CONSISTENCY
#endif

namespace Render
{

bool EqualIDs(UINT _lhs, UINT _rhs);

struct Batch;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Material
{
	enum
	{
		NEED_TO_CALL_UPDATE	= (1L << 0), // Require alpha blending turned on
	};

public:
	// Constructor goes with default values
	Material() : sortId(0), crc32(0), shaderIndex(-1), priority(4), flags(0), subPriority(0), alternativeMaterial(0) {}
	Material( int _priority, int /*_flags*/, int _shaderIndex ) 
		: sortId(0), crc32(0), shaderIndex(_shaderIndex), priority(_priority)
		, flags(0), renderFlags(NDb::MATERIALFLAGS_NONE), subPriority(0), altPriorityEnabled(false)
    , alternativeMaterial(0), parentMaterial(0), fadingAlternativeMaterial(false)
	{}
  virtual ~Material() { MarkMaterialUpdated(); } 

  int GetResourceManagerShaderIndex() const { return shaderIndex; }

	// Get priority
	int GetPriority() const { return priority; }
	void SetPriority(int prior) { priority = prior; }
	
  static const int SUBPRIORITY_SIZE = 6; // 6 bits for subPriority
	static const int SUBPRIORITY_MIN = -1 << (SUBPRIORITY_SIZE - 1);
  static const int SUBPRIORITY_MAX = -SUBPRIORITY_MIN - 1;
  // Get subpriority
	int GetSubPriority() const { return subPriority; }
  void SetSubPriority(int subprior) { subPriority = subprior; }

	void SetMaterialFlags(NDb::MaterialFlags f) { renderFlags = f; }
	NDb::MaterialFlags GetMaterialFlags() const { return renderFlags; }

  Material* GetAlternativeMaterial() const { return alternativeMaterial; }
  void SetAlternativeMaterial( Material* _mat )
  {
    if(alternativeMaterial) alternativeMaterial->parentMaterial = NULL;
    alternativeMaterial = _mat;
    altPriorityEnabled = true;
    if(_mat) _mat->parentMaterial = this;
  }

  Material* GetAlternativeMaterialParent() const { return parentMaterial; }

  bool IsFadingAlternativeMaterial() const { return fadingAlternativeMaterial; }
  void SetFadingAlternativeMaterial( bool _fading ) { fadingAlternativeMaterial = _fading; }

  int GetBasePriority() const { return basePriority; }
  void SetBasePriority( int _priority ) { basePriority = _priority; }

  int GetAltPriority() const { return altPriority; }
  void SetAltPriority( int _priority ) { altPriority = _priority; }

  void SetEnableAltPriority(bool st) { altPriorityEnabled = st; }
  bool IsAltPriorityEnabled() const { return altPriorityEnabled; }

	bool Need2CallUpdate() const { return (flags & NEED_TO_CALL_UPDATE) != 0; }
  virtual bool SkipIDEvaluation() const { return Need2CallUpdate(); }

	// Setups renderer before calling DIP() 
	virtual void PrepareRenderer() = 0;
	virtual void PrepareRendererWithBatch(const Batch &/*batch*/) {}
	virtual void RegisterInstancedBatch(const Batch &/*batch*/)   {}

  virtual void FillMaterial( const NDb::Material *pDbMaterial, void * texturePoolId, bool savePointer = true )
	{
		subPriority = pDbMaterial->SubPriority;
		renderFlags = pDbMaterial->renderFlags;
		if (IsAnimated())
			flags |= NEED_TO_CALL_UPDATE;
	}

	virtual void FillMaterial()
	{
	}

	virtual const NDb::Material* GetDBMaterial() const { return 0; }

  virtual bool Instanceable()  const { return false; }
  UINT GetStaticShaderIndex()  const { return staticShaderIndex; }
	virtual void Update(float /*dt*/) {}
	virtual void SetStartTime( float /* startTime */ ) {}

  bool IsTransparent() const
  {
    return priority == NDb::MATERIALPRIORITY_TRANSPARENTSPECIAL ||
           priority == NDb::MATERIALPRIORITY_TRANSPARENT;
  }

  virtual float GetAnimLength() const
  {
    return 0.0f;
  }

	// Warning! Lazy evaluation here.
  unsigned int GetSortId();

	void EvaluateSortId();

	void MarkShadersUpdated();
  void MarkMaterialUpdated(); // Call this BEFORE material change

	seDECLARE_RING_CLASS(Material, ringPart, Ring);

	int  Compare(const Material &mat) const;

  struct Samplers
  {
    int* samplers;
    int count;
    
    Samplers() : samplers( 0 ), count( 0 ) { }
  };

  const Samplers& GetSamplers() const { return samplers; }
protected:
	virtual bool IsAnimated() const { return false; }

	virtual int SignificantPartLength() const { return 0; }

  // Get corrected render state and samplers representation for SortID calculation needs.
  // Given null pointer, return size of required memory block
  virtual int GetRSandSamplersRep(PBYTE _pRep, int *_pProcessedSize = 0) const;
  // Helper for GetRSandSamplersRep
  int Material::GetSamplersRep(PBYTE _pRep) const;

  int  CompareNoShaders(const Material &mat, PBYTE thisSamplers = 0) const;
  int  CompareSP(const Material &mat, int significantLength, PBYTE thisSamplers) const;
	void UpdateInternals() // Override this function in successors to get non-default priority & flags calculation
	{
		// Do nothing. 
	}

	void OnPrepareRender(); // Override this function in successors to perform material specific prepare actions

  Material* alternativeMaterial;
  Material* parentMaterial; // Holder of alternative material
  bool fadingAlternativeMaterial;
  int basePriority;
  int altPriority;
  bool altPriorityEnabled;        // Selectively enable/disable use of alternative priority

	Ring::Part         ringPart;    // Ring of materials for sorting
	unsigned int       sortId;      // Identificator
	unsigned int			 crc32;       // CRC variable
#ifdef _CHECK_CONSISTENCY
	unsigned int			 shadersID;
#endif // _CHECK_CONSISTENCY

	int                shaderIndex; // Shader index
  unsigned int staticShaderIndex;

	int                flags;       // Material flags
	NDb::MaterialFlags renderFlags;	// Material flags
	int                priority;    // It is a responsibility of material to set this priority
	int                subPriority; // For sorting within mesh 

  static Matrix43 worldMatrices[];

  Samplers samplers;

	friend class MaterialManager;

  void SetSamplers( int *_samplers, int _count )
  {
    samplers.samplers = _samplers;
    samplers.count = _count ;
  }

private:
  void ComposeID(UINT _crcID);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillSampler( const NDb::Sampler& dbSampler, Render::Sampler* pSampler, bool canBeVisualDegrade, void * texturePoolId );
void FillSampler( const NDb::SamplerEx& dbSampler, Render::Sampler* pSampler, bool canBeVisualDegrade, void * texturePoolId );
void FillSampler( const NDb::SamplerCube& dbSampler, Render::Sampler* pSampler, bool canBeVisualDegrade, void * texturePoolId );

inline void BindSampler(int samplerIndex, const Render::Sampler& sampler) { sampler.Bind(samplerIndex); }

void BindShader( const int multiShaderIndex, int shaderIndex );
void SetRenderState(const RenderState& state);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::Material* CreateRenderMaterialInPool( const NDb::Material* pDbMaterial, void * texturePoolId );
Render::Material* CreateRenderMaterial( const NDb::Material* pDbMaterial );
Render::Material* CreateRenderMaterial( const int typeId );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void SetShadersCount( int shadersCount );
//void RegisterShader( const string& fileName, int shaderIndex );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterMaterialType( const int typeId, SimpleObjectsFactory<Render::Material>::TNewFunction newFunction, const string& typeName );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}