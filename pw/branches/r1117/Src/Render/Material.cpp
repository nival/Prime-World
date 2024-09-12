#include "stdafx.h"

#include "../System/Crc32Checksum.h"

#include "Renderer.h"
#include "texture.h"
#include "RenderResourceManager.h"
#include "MultiShader.h"
#include "Material.h"
#include "MaterialSpec.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static SimpleObjectsFactory<Render::Material>& GetMaterials()
{
  static SimpleObjectsFactory<Render::Material> materials;
  return materials;
}

static struct SRegister_MaterialHelper
{
  SRegister_MaterialHelper() 
  {
    void *p = &GetMaterials(); 
    __asm {
      mov eax, p
    }
  }
} materialVarRegistrar;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{

static bool s_disableTriLinear = false;
REGISTER_VAR("rndr_disableTriLinear", s_disableTriLinear, STORAGE_USER);
bool SamplerState::IsTriLinearDisabled() { return s_disableTriLinear; }

static const UINT CRC_BITS = 22;
static const UINT CRC_MASK = ((1 << CRC_BITS) - 1) << 1;
static const UINT SHADER_ID_SHIFT = CRC_BITS + 1;
static const UINT SHADER_ID_MASK = (UINT_MAX << SHADER_ID_SHIFT);

// test crcID parts for equality
bool EqualIDs(UINT _lhs, UINT _rhs)
{
  return 0 == ((_lhs ^ _rhs) & CRC_MASK);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SamplerState& SamplerState::PRESET_CLAMP_POINT()
{
	static const SamplerState ss(NDb::MINFILTERTYPE_POINT, NDb::MAGFILTERTYPE_POINT, NDb::MIPFILTERTYPE_NONE, NDb::TEXTUREADDRESSTYPE_CLAMP, NDb::TEXTUREADDRESSTYPE_CLAMP);
	return ss;
}
const SamplerState& SamplerState::PRESET_CLAMP_BILINEAR()
{
	static const SamplerState ss(NDb::MINFILTERTYPE_LINEAR, NDb::MAGFILTERTYPE_LINEAR, NDb::MIPFILTERTYPE_NONE, NDb::TEXTUREADDRESSTYPE_CLAMP, NDb::TEXTUREADDRESSTYPE_CLAMP);
	return ss;
}
const SamplerState& SamplerState::PRESET_CLAMP_MIP_BILINEAR()
{
  static const SamplerState ss(NDb::MINFILTERTYPE_LINEAR, NDb::MAGFILTERTYPE_LINEAR, NDb::MIPFILTERTYPE_POINT, NDb::TEXTUREADDRESSTYPE_CLAMP, NDb::TEXTUREADDRESSTYPE_CLAMP);
  return ss;
}
const SamplerState& SamplerState::PRESET_CLAMP_TRILINEAR()
{
  static const SamplerState ss(NDb::MINFILTERTYPE_LINEAR, NDb::MAGFILTERTYPE_LINEAR, NDb::MIPFILTERTYPE_LINEAR, NDb::TEXTUREADDRESSTYPE_CLAMP, NDb::TEXTUREADDRESSTYPE_CLAMP);
  return ss;
}

const SamplerState& SamplerState::PRESET_WRAP_BILINEAR()
{
  static const SamplerState ss(NDb::MINFILTERTYPE_LINEAR, NDb::MAGFILTERTYPE_LINEAR, NDb::MIPFILTERTYPE_NONE, NDb::TEXTUREADDRESSTYPE_WRAP, NDb::TEXTUREADDRESSTYPE_WRAP);
  return ss;
}
const SamplerState& SamplerState::PRESET_WRAP_MIP_BILINEAR()
{
  static const SamplerState ss(NDb::MINFILTERTYPE_LINEAR, NDb::MAGFILTERTYPE_LINEAR, NDb::MIPFILTERTYPE_POINT, NDb::TEXTUREADDRESSTYPE_WRAP, NDb::TEXTUREADDRESSTYPE_WRAP);
  return ss;
}
const SamplerState& SamplerState::PRESET_WRAP_TRILINEAR()
{
  static const SamplerState ss(NDb::MINFILTERTYPE_LINEAR, NDb::MAGFILTERTYPE_LINEAR, NDb::MIPFILTERTYPE_LINEAR, NDb::TEXTUREADDRESSTYPE_WRAP, NDb::TEXTUREADDRESSTYPE_WRAP);
  return ss;
}
const SamplerState& SamplerState::PRESET_WRAP_POINT()
{
  static const SamplerState ss(NDb::MINFILTERTYPE_POINT, NDb::MAGFILTERTYPE_POINT, NDb::MIPFILTERTYPE_NONE, NDb::TEXTUREADDRESSTYPE_WRAP, NDb::TEXTUREADDRESSTYPE_WRAP);
  return ss;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void FillSamplerState( const NDb::SamplerState &samplerState, Render::Sampler* pSampler )
{
	pSampler->SetSamplerState( samplerState );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void FillSamplerTexture( const NDb::Ptr<NDb::TextureBase> &pTexture, Render::Sampler* pSampler, bool canBeVisualDegrade, void * texturePoolId )
{
	if ( IsValid( pTexture ) )
    pSampler->SetTexture( pTexture->LoadInPool( canBeVisualDegrade, texturePoolId ) );
	else
		pSampler->SetTexture( GetWhiteTexture2D() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillSamplerCubemap( const NDb::Ptr<NDb::CubeMap> &pTexture, Render::Sampler* pSampler, bool canBeVisualDegrade, void * texturePoolId )
{
	if ( IsValid( pTexture ) )
    pSampler->SetTexture( LoadCubeTextureFromFileIntoPoolRef( pTexture->textureFileName, canBeVisualDegrade, texturePoolId ) );
	else
		pSampler->SetTexture( GetWhiteTexture2D() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillSampler( const NDb::Sampler& dbSampler, Render::Sampler* pSampler, bool canBeVisualDegrade, void * texturePoolId )
{
  FillSamplerState( dbSampler.samplerState, pSampler );
	FillSamplerTexture( dbSampler.texture, pSampler, canBeVisualDegrade, texturePoolId );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillSampler( const NDb::SamplerEx& dbSampler, Render::Sampler* pSampler, bool canBeVisualDegrade, void * texturePoolId )
{
  FillSamplerState( dbSampler.samplerState, pSampler );
	FillSamplerTexture( dbSampler.texture, pSampler, canBeVisualDegrade, texturePoolId );
	pSampler->SetMultiplierAndAdd( dbSampler.Multiplier, dbSampler.Add );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FillSampler( const NDb::SamplerCube& dbSampler, Render::Sampler* pSampler, bool canBeVisualDegrade, void * texturePoolId )
{
  FillSamplerState( dbSampler.samplerState, pSampler );
	FillSamplerCubemap( dbSampler.texture, pSampler, canBeVisualDegrade, texturePoolId );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BindShader( const int multiShaderIndex, int shaderIndex ) 
{ 
  //int multiShaderIndex = RenderResourceManager::GetShaderIndexByTypeId(typeId);
  RenderResourceManager::GetMultiShader( multiShaderIndex )->GetShaderPairByIndex( shaderIndex ).Bind(); 
}
void SetRenderState(const RenderState& state) { GetStatesManager()->SetState( state ); }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::Material* CreateRenderMaterialInPool( const NDb::Material* pDbMaterial, void * texturePoolId )
{
	NI_VERIFY( pDbMaterial, "Invalid data base material", return 0 );
	Render::Material* pResult = GetMaterials().CreateObject( pDbMaterial->GetObjectTypeID() );
	pResult->FillMaterial( pDbMaterial, texturePoolId ); 

	return pResult;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::Material* CreateRenderMaterial( const NDb::Material* pDbMaterial )
{
  return CreateRenderMaterialInPool( pDbMaterial, 0 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::Material* CreateRenderMaterial( const int typeId )
{
	Render::Material* pResult = GetMaterials().CreateObject( typeId );
	pResult->FillMaterial(); 

	return pResult;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RegisterMaterialType( const int typeId, SimpleObjectsFactory<Render::Material>::TNewFunction newFunction, const string& typeName )
{
	GetMaterials().RegisterType( typeId, newFunction );
  RenderResourceManager::SetTypeId( typeName, typeId );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MaterialManager
{
public:
  MaterialManager() : currentID(0) {}

  void Add(Material &mat, PBYTE thisSamplers);
  void FreeID(Material *mat);
  UINT GetShadersID(const Material *_pMat);

  static MaterialManager* Get()
  {
    static MaterialManager manager;
    return &manager;
  }

  // debug helpers
  void PrintStatistics() const;
  static bool MaterialManager::ResetSortIDs(const char*, const vector<wstring>&);

private:
  enum
  {
    HASH_TABLE_POWER = 8,
    HASH_TABLE_SIZE  = 1 << HASH_TABLE_POWER,
  };

#ifdef _CHECK_CONSISTENCY
  static void CheckRingConsistency(Material::Ring &ring);
  void CheckConsistency();
#else
  static void CheckRingConsistency(Material::Ring &ring) {}
  void CheckConsistency() {}
#endif // _CHECK_CONSISTENCY
  UINT GetFreeID();

  Material::Ring& GetRing(UINT crc32)
  {
    // Convert CRC32 to hash index
    unsigned int hashIndex = crc32 ^ (crc32 >> (HASH_TABLE_POWER*2));
    hashIndex ^= hashIndex >> HASH_TABLE_POWER;
    hashIndex &= HASH_TABLE_SIZE - 1;

    return hashTable[hashIndex];
  }

  unsigned int   currentID;
  Material::Ring hashTable[HASH_TABLE_SIZE];
  vector<UINT>   freeIDs;

  typedef hash_map<UINT, UINT> Map;
  Map shaderIds;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Material::OnPrepareRender()
{
	// mark shadow receivers in stencil buffer
  DWORD bits = (renderFlags & NDb::MATERIALFLAGS_SHADOWRECEIVER) ? STENCILBIT_SHADOWRECEIVER : 0x00;
  GetStatesManager()->SetStencilStateAddonBits(STENCILBIT_SHADOWRECEIVER, bits);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Material::MarkShadersUpdated()
{
  sortId &= ~SHADER_ID_MASK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Material::MarkMaterialUpdated()
{
  if(sortId)
    MaterialManager::Get()->FreeID(this);

  ASSERT( !ringPart.isLinked() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void Material::ComposeID(UINT _crcID)
{
  const UINT shaderID = MaterialManager::Get()->GetShadersID(this);
#ifdef _CHECK_CONSISTENCY
  shadersID = shaderID;
#endif // _CHECK_CONSISTENCY
  ASSERT( shaderID <= (UINT_MAX >> SHADER_ID_SHIFT) );
  _crcID += _crcID;
  sortId = _crcID & CRC_MASK | (shaderID << SHADER_ID_SHIFT);

  const int significantLength = SignificantPartLength();
  if(significantLength)
  {
    const RenderState& rs = *((RenderState*)(PBYTE(this) + sizeof(Material)));
    sortId |= rs.GetEmissive();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Material::GetSamplersRep(PBYTE _pRep) const
{
  if(_pRep) {
    Sampler::SignificantPart* const pSParts = (Sampler::SignificantPart*)_pRep;

    const int * const pDisplacements = samplers.samplers;
    PBYTE pMemberBase = PBYTE(this);

    for(int i = 0; i < samplers.count; ++i)
    {
      const Sampler *pSampler = (const Sampler*)(pMemberBase + pDisplacements[i]);
      pSampler->GetSignificantPart(pSParts + i);
    }
  }

  return samplers.count * sizeof(Sampler::SignificantPart);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Material::GetRSandSamplersRep(PBYTE _pRep, int *_pProcessedSize) const
{
  if(_pRep) {
    *((RenderState*)_pRep) = ((RenderState*)(PBYTE(this) + sizeof(Material)))->GetCRCValue();
    _pRep += sizeof(RenderState);
  }

  if(_pProcessedSize)
    *_pProcessedSize = sizeof(RenderState) + samplers.count * sizeof(Sampler);

  return sizeof(RenderState) + GetSamplersRep(_pRep);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Material::EvaluateSortId()
{
	if( SkipIDEvaluation() )
  { // We don't account materials that should be updated
    crc32 = 0;
    ComposeID(0);
    return;
  }

  Crc32Checksum calc;
  const int significantLength = SignificantPartLength();
  PBYTE thisSamplers = 0;
  if(significantLength)
  {
    const int samplersSize = GetRSandSamplersRep(0);
    int processedSize = 0;
    thisSamplers = PBYTE( alloca(samplersSize) );
    GetRSandSamplersRep(thisSamplers, &processedSize);
    calc.Add(thisSamplers, samplersSize);

    ASSERT(significantLength >= processedSize);
    crc32 = calc.Add(PBYTE(this) + sizeof(Material) + processedSize, significantLength - processedSize).Get();
  }

	MaterialManager::Get()->Add(*this, thisSamplers);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int Material::GetSortId()
{
  // lazy evaluation
  if (sortId == 0)
    EvaluateSortId();
  else if((sortId & SHADER_ID_MASK) == 0)
    ComposeID(sortId >> 1);

  return (GetRuntimePins().RenderModeValue == NDb::RENDERMODEPIN_RENDERNORMAL) ? sortId : sortId & ~1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Material::CompareSP(const Material &mat, int significantLength, PBYTE thisSamplers) const
{
  if(!significantLength)
    return 0;

  ASSERT( samplers.count == mat.samplers.count );
  int processedSize = 0;
  const int samplersSize = GetRSandSamplersRep(0, &processedSize);
  if(!thisSamplers) {
    thisSamplers = PBYTE( alloca(samplersSize) );
    GetRSandSamplersRep(thisSamplers);
  }
  ASSERT(significantLength >= processedSize);

  const int samplersSizeRhs = mat.GetRSandSamplersRep(0);
  if(samplersSize != samplersSizeRhs)
    return samplersSize - samplersSizeRhs;

  PBYTE const samplersRhs = (PBYTE)alloca(samplersSizeRhs);
  int processedSizeRhs = 0;
  mat.GetRSandSamplersRep(samplersRhs, &processedSizeRhs);
  ASSERT(processedSize == processedSizeRhs);

  int compResult = memcmp(thisSamplers, samplersRhs, samplersSize);
  if( compResult )
    return compResult;

  const int offset = sizeof(Material) + processedSize;
  return memcmp(PBYTE(this) + offset, PBYTE(&mat) + offset, significantLength - processedSize);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Material::CompareNoShaders(const Material &mat, PBYTE thisSamplers) const
{
  const int significantLength = SignificantPartLength();
  const int significantLengthRhs = mat.SignificantPartLength();

  if(significantLength == significantLengthRhs)
    return CompareSP(mat, significantLength, thisSamplers);

  return significantLength - significantLengthRhs;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Material::Compare(const Material &mat) const
{
	int diff = shaderIndex - mat.shaderIndex;
	if( diff )
    return diff;

  diff = staticShaderIndex - mat.staticShaderIndex;
  if( diff )
    return diff;

  const int significantLength = SignificantPartLength();

  NI_ASSERT(significantLength == mat.SignificantPartLength(), "Materials of the same type have different significant part length! Very bad.");

  return CompareSP(mat, significantLength, 0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT MaterialManager::GetFreeID()
{
  if( freeIDs.empty() )
  {
    ASSERT( currentID < CRC_MASK );
    return ++currentID;
  }

  UINT freeID = freeIDs.back();
  freeIDs.pop_back();
  return freeID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MaterialManager::Add(Material &mat, PBYTE thisSamplers)
{
	// Check material
	NI_ASSERT(!mat.ringPart.isLinked(), "Material is already added to material manager. Logic fatal error.");
	NI_ASSERT(mat.sortId == 0, "Material sort id should be zero. This indicates that it should be added");

  const UINT crc32 = mat.crc32;
	Material::Ring &ring = GetRing(crc32);
	ring::Range<Material::Ring> it(ring);
	// Skip materials with lower CRC value
  while(it && crc32 > it->crc32)
    ++it;

	// Process materials with the same CRC value
	for (; it && it->crc32 <= crc32; ++it)
	{
    int compResult = mat.CompareNoShaders(*it, thisSamplers);
		if (compResult == 0)
		{
			// This is the same material!
			mat.ComposeID(it->sortId >> 1);
			ring.addAfter(&mat, &(*it));
#ifdef _CHECK_CONSISTENCY
      CheckRingConsistency(ring);
      ASSERT(mat.shadersID == it->shadersID || mat.shaderIndex != it->shaderIndex || mat.GetStaticShaderIndex() != it->GetStaticShaderIndex());
#endif // _CHECK_CONSISTENCY
			return;
		} 
		else 
		{
			// CRC are the same but materials are not. Should be very rare.
			if (compResult < 0)
		  	break;
		}
	}
	// Well. Material not found.
	mat.ComposeID( GetFreeID() );
	if (it)
    ring.insertBefore(&mat, &(*it));
	else
		ring.addLast(&mat);

  CheckRingConsistency(ring);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MaterialManager::FreeID(Material *mat)
{
  if( !EqualIDs(mat->sortId, 0) )
  {
    Material::Ring::Part &ringPart = mat->ringPart;
    // Check material
    NI_ASSERT(ringPart.isLinked(), "Material should be added to material manager already. Logic fatal error.");

    Material* const dummy = GetRing(mat->crc32).self();
    const UINT sortId = mat->sortId;
    if( (ringPart.next == dummy || !EqualIDs(ringPart.next->sortId, sortId)) &&
      (ringPart.prev == dummy || !EqualIDs(ringPart.prev->sortId, sortId)) )
      freeIDs.push_back(sortId >> 1); // There are no other materials with this sortId in the ring
  }
  mat->sortId = 0;
  Material::Ring::safeRemove(mat);
  //CheckConsistency();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MaterialManager::PrintStatistics() const
{
	int materialCount = 0;
	int uniqueMaterialCount = 0;
	int uniqueCRCMaterialCount = 0;
	int hashTableCount[HASH_TABLE_SIZE];
	memset(hashTableCount, 0, sizeof(hashTableCount));

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		const Material::Ring &ring = hashTable[i];
		if (ring.empty())
			continue;

		materialCount++;
		uniqueMaterialCount++;
		uniqueCRCMaterialCount++;
		hashTableCount[i]++;

		ring::Range<Material::Ring> it(ring);
		unsigned int crcVal = it->crc32;
		const Material *pMat = &(*it);
		for (++it; it; ++it)
		{
			materialCount++;
			hashTableCount[i]++;

			NI_ASSERT(crcVal <= it->crc32, "CRC sorting failed");

			if (it->crc32 != crcVal)
			{
				uniqueMaterialCount++;
				uniqueCRCMaterialCount++;
				crcVal = it->crc32;
			}
			else
			{
				if (pMat->Compare(*it) != 0)
				{
					uniqueMaterialCount++;
					pMat = &(*it);
				}
			}
		}
	}

	const int MAX_MATERIAL_COUNT = 1024;
	int histogram[MAX_MATERIAL_COUNT];
	memset(histogram, 0, sizeof(histogram));

	// Build histogram
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		int count = min(MAX_MATERIAL_COUNT-1, hashTableCount[i]);
		histogram[count]++;
	}

	// Scan for right histogram border
	int rightBorder = MAX_MATERIAL_COUNT-1;
	for (int i = MAX_MATERIAL_COUNT-1; i >= 0; i--)
	{
		if (histogram[i] != 0)
		{
			rightBorder = i;
		  break;
		}
	}

	// Print statistics
	DebugTrace("============================================================");
	DebugTrace("Material Manager Statistics:");
	DebugTrace("Histogram:");
	for (int i = 0; i <= rightBorder; i++)
	{
		if (histogram[i] == 0)
			continue;
		
		DebugTrace("  [%3d]: %d", i, histogram[i]);
	}
  DebugTrace("Materials (uniq/crc-uniq/count): %d / %d / %d", uniqueCRCMaterialCount, uniqueMaterialCount, materialCount);

  DebugTrace("MaterialManager free id capacity: %d, max.id: %d", freeIDs.capacity(), currentID);
}

#ifdef _CHECK_CONSISTENCY
void MaterialManager::CheckRingConsistency(Material::Ring &ring)
{
  ring::Range<Material::Ring> it(ring);
  unsigned int crcVal = it->crc32;
  unsigned int sortId = it->sortId;
  const Material *pMat = &(*it);
  for (++it; it; ++it)
  {
    NI_ASSERT(crcVal <= it->crc32, "CRC sorting failed");

    const int compResult = pMat->CompareNoShaders(*it);
    if(it->crc32 == crcVal)
    {
      char msg[_MAX_PATH];
      _snprintf_s(msg, _TRUNCATE, "Sorting failed: it->sortId = %x, sortId = %x", it->sortId, sortId);
      if( EqualIDs(it->sortId, sortId) )
        NI_ASSERT(compResult == 0, msg)
      else
        NI_ASSERT(compResult < 0, msg)
    }

    crcVal = it->crc32;
    sortId = it->sortId;
    pMat = &(*it);
  }
}

void MaterialManager::CheckConsistency()
{
  for (int hash = 0; hash < HASH_TABLE_SIZE; ++hash)
  {
    Material::Ring &ring = hashTable[hash];
    if( !ring.empty() )
      CheckRingConsistency(ring);
  }
}
#endif

bool MaterialManager::ResetSortIDs(const char*, const vector<wstring>&)
{
  MaterialManager& manager = *MaterialManager::Get();
  for (int hash = 0; hash < HASH_TABLE_SIZE; ++hash)
  {
    Material::Ring &ring = manager.hashTable[hash];
    if (ring.empty())
      continue;

    while(true)
    {
      ring::Range<Material::Ring> it(ring);
      if(!it)
        break;
      it->MarkMaterialUpdated();
    }
  }

  manager.freeIDs.clear();
  manager.currentID = 0;
  return true;
}

UINT MaterialManager::GetShadersID(const Material *_pMat)
{
  static const UINT shaderIdBits = 22; // Волюнтаризм чистой воды
  static const UINT shaderIdMask = (1 << shaderIdBits) - 1;

  const int  idMulti = _pMat->GetResourceManagerShaderIndex();
  ASSERT( idMulti < (1<<(8*sizeof(UINT)-shaderIdBits)) && (_pMat->GetStaticShaderIndex() < (1<<shaderIdBits)) );
  const UINT shaderIndex = (idMulti << shaderIdBits) | (_pMat->GetStaticShaderIndex() & shaderIdMask);
  Map::iterator it = shaderIds.find(shaderIndex);
  if(shaderIds.end() == it)
  {
    const UINT id = shaderIds.size() + 1;
    shaderIds.insert( Map::value_type(shaderIndex, id) );
    return id;
  }
  return it->second;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Render
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


static bool PrintMaterialManagerStatistics(const char *name, const vector<wstring>& params)
{
  Render::MaterialManager::Get()->PrintStatistics();
  return true;
}

REGISTER_DEV_CMD( render_mm_stat, PrintMaterialManagerStatistics);
REGISTER_DEV_CMD( resetSortIDs, Render::MaterialManager::ResetSortIDs );
