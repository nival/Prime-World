#pragma once

const float c_fDefaultGrassFarLod = 200.0f;
const float c_fGrassFadeLength = 50.0f;
const float c_fMinBladeNoise = -0.2f;
const float c_fMaxBladeNoise = 0.2f;
const float c_fMinBladeThrow = 0.5f;
const float c_fMaxBladeThrow = 1.5f;
const float c_fMinBladeSize = 0.3f;
const float c_fMaxBladeSize = 1.3f;
const	int		c_nNumBladeMaps = 2;
const float c_fGrassBillboardWideScalar = 3.0f;
const float c_fWalkerHeight = 12.0f;
const int   c_nDefaultGrassBladeCount = 30000;
const int   c_nGrassRegionCount = 20;
const	int		c_nGrassSubDivs = 5; // must be an odd number

// grass vertex attribute sizes
const int c_nGrassVertexTexture0Size = 2 * sizeof(float);         // base map coordinate
const int c_nGrassVertexTexture1Size = 4 * sizeof(float);         // vertex index, blade size, wind weight, noise factor
const int c_nGrassVertexPositionSize = 3 * sizeof(float);         // (x, y, z)

const int c_nGrassVertexTotalSize = c_nGrassVertexTexture0Size + c_nGrassVertexTexture1Size + c_nGrassVertexPositionSize;

class CSpeedGrassRT
{
public:
	CSpeedGrassRT(void);
	virtual ~CSpeedGrassRT(void);

	///////////////////////////////////////////////////////////////////////  
	//  struct SBlade

	struct SBlade
	{
		SBlade(void);

		// geometry
		float				m_afPos[3];
		float				m_afNormal[3];
		float				uv[8];
		float				m_fSize;

		//// wind
		//float				m_fNoise;
		float				m_fThrow;

		//// color
		//float				m_afBottomColor[3];
		//float				m_afTopColor[3];
	};


	///////////////////////////////////////////////////////////////////////  
	//  struct SRegion

	struct SRegion
	{
		SRegion(void);
		~SRegion(void);

		// dimensions
		float						m_afCenter[3];
		float						m_afMin[3];
		float						m_afMax[3];

		// grass/brush blades
		vector<SBlade>			m_vBlades;
	};

	const SRegion*		GetRegions(unsigned int& uiNumRegions);
	void							DeleteRegions(void);
	//bool							ParseSffFile(const char* pFilename, unsigned int uiRows, unsigned int uiCols);
	//bool							ParseBsfFile(const char* pFilename, unsigned int nNumBlades, unsigned int uiRows, unsigned int uiCols, float fCollisionDistance = 0.0f);
	//bool							CustomPlacement(unsigned int uiRows, unsigned int uiCols);


	///////////////////////////////////////////////////////////////////////  
	//  Geometry

	//static	const float*		GetUnitBillboard(void) { return m_afUnitBillboard; }


	///////////////////////////////////////////////////////////////////////  
	//  LOD

	//static  void	GetLodParams(float& fFarDistance, float& fTransitionLength);
	//static  void	SetLodParams(float fFarDistance, float fTransitionLength);


	///////////////////////////////////////////////////////////////////////  
	//  Culling

	//bool				AllRegionsAreCulled(void) const { return m_bAllRegionsCulled; }
	//void				Cull(void);


	///////////////////////////////////////////////////////////////////////  
	//  Wind

	//static	void						SetWindDirection(const float* pWindDir);
	//static	const float*		GetWindDirection(void);


	///////////////////////////////////////////////////////////////////////  
	//  Terrain hugging

	//virtual float				Color(float /*fX*/, float /*fY*/, const float* /*pNormal*/, float* /*pTopColor*/, float* /*pBottomColor*/) { return 0.0f; }	
	//virtual float				Height(float /*fX*/, float /*fY*/, float* /*pNormal*/) const { return 0.0f; }	

protected:

	//void								CreateRegions(const vector<SBlade>& vSceneBlades, float fCollisionDistance = 0.0f);
	//static	void				ComputeFrustum(void);
	//static	void				ComputeUnitBillboard(void);
	//void								ConvertCoordsToCell(const float* pCoords, int* pGridCoords) const;
	int				GetRegionIndex(int uiRow, int uiCol) const	{ return uiRow * m_nNumRegionCols + uiCol; }
	//static	bool				OutsideFrustum(SRegion* pRegion);

protected:

	// general
	//static	float					m_fLodFarDistance;
	//static	float					m_fLodTransitionLength;
	//static	float					m_afUnitBillboard[16];
	//static	float					m_afWindDir[4];

	// regions
	int						m_nNumRegionCols;
	int						m_nNumRegionRows;
	hash_map<int, SRegion> m_vRegions;

	//float					m_afBoundingBox[6];
};

