#include "stdafx.h"

#include "SpeedGrass.h"
//#include "../System/Win32Random.h"


// static variables
//float CSpeedGrassRT::m_fLodFarDistance = 100.0f;
//float CSpeedGrassRT::m_fLodTransitionLength = 37.5f;
//float CSpeedGrassRT::m_afUnitBillboard[16] = { 0.0f, 0.0f, 0.0f, 1.0f,
//												0.0f, 0.0f, 0.0f, 1.0f,
//												0.0f, 0.0f, 0.0f, 1.0f,
//												0.0f, 0.0f, 0.0f, 1.0f };
//float CSpeedGrassRT::m_afWindDir[4] = { 1.0f, 0.3f, 0.0f, 0.0f };

///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::SBlade::SBlade

CSpeedGrassRT::SBlade::SBlade( ) :
	m_fSize(1.0f)
	//m_fNoise(0.0f),
	, m_fThrow(0.0f)
{
	//m_afBottomColor[0] = m_afBottomColor[1] = m_afBottomColor[2] = 1.0f;
	//m_afTopColor[0] = m_afTopColor[1] = m_afTopColor[2] = 1.0f;
}


///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::SRegion::SRegion

CSpeedGrassRT::SRegion::SRegion( )
{
	//m_afCenter[0] = m_afCenter[1] = m_afCenter[2] = 0.5f;
	//m_afMin[0] = m_afMin[1] = m_afMin[2] = 0.0f;
	//m_afMax[0] = m_afMax[1] = m_afMax[2] = 1.0f;
}


///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::SRegion::~SRegion

CSpeedGrassRT::SRegion::~SRegion( )
{
	//delete m_pGeomBuffer;
	//m_pGeomBuffer = NULL;
}


///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::CSpeedGrassRT

CSpeedGrassRT::CSpeedGrassRT( ) :
	m_nNumRegionCols(0),
	m_nNumRegionRows(0)
	//, m_bAllRegionsCulled(false)
{
	//m_afBoundingBox[0] = m_afBoundingBox[1] = m_afBoundingBox[2] = 0.0f;
	//m_afBoundingBox[3] = m_afBoundingBox[4] = m_afBoundingBox[5] = 1.0f;
}


///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::~CSpeedGrassRT

CSpeedGrassRT::~CSpeedGrassRT( )
{
	
}


///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::GetRegions

//const CSpeedGrassRT::SRegion* CSpeedGrassRT::GetRegions(unsigned int& uiNumRegions)
//{
//	uiNumRegions = (unsigned int)m_vRegions.size( );
//	return &m_vRegions[0];
//}

///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::GetLodParams
 
//void CSpeedGrassRT::GetLodParams(float& fFarDistance, float& fTransitionLength)
//{
//	fFarDistance = m_fLodFarDistance;
//	fTransitionLength = m_fLodTransitionLength;
//}


///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::SetLodParams

//void CSpeedGrassRT::SetLodParams(float fFarDistance, float fTransitionLength)
//{
//	m_fLodFarDistance = fFarDistance;
//	m_fLodTransitionLength = fTransitionLength;
//}



///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::SetWindDirection
//
//void CSpeedGrassRT::SetWindDirection(const float* pWindDir)
//{
//	memcpy(m_afWindDir, pWindDir, 3 * sizeof(float));
//	m_afWindDir[3] = 0.0f;
//}

///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::GetWindDirection

//const float* CSpeedGrassRT::GetWindDirection(void)
//{
//	return m_afWindDir;
//}

///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::CreateRegions

//void CSpeedGrassRT::CreateRegions(const vector<SBlade>& vSceneBlades, float fCollisionDistance)
//{
//	// create regions based on overall extents
//	m_vRegions.clear( );
//	m_vRegions.resize(m_nNumRegionRows * m_nNumRegionCols);
//
//	// run through all regions, computing extents for each
//	float fCellWidth = (m_afBoundingBox[3] - m_afBoundingBox[0]) / m_nNumRegionCols;
//	float fCellHeight = (m_afBoundingBox[4] - m_afBoundingBox[1]) / m_nNumRegionRows;
//
//	float fY = m_afBoundingBox[1];
//	for (int nRow = 0; nRow < m_nNumRegionRows; ++nRow)
//	{
//		float fX = m_afBoundingBox[0];
//		for (int nCol = 0; nCol < m_nNumRegionCols; ++nCol)
//		{
//			SRegion* pRegion = &m_vRegions[GetRegionIndex(nRow, nCol)];
//
//			// compute extents
//			pRegion->m_afMin[0] = fX;
//			pRegion->m_afMax[0] = fX + fCellWidth;
//			pRegion->m_afMin[1] = fY;
//			pRegion->m_afMax[1] = fY + fCellHeight;
//		
//			// compute center
//			pRegion->m_afCenter[0] = 0.5f * (pRegion->m_afMin[0] + pRegion->m_afMax[0]);
//			pRegion->m_afCenter[1] = 0.5f * (pRegion->m_afMin[1] + pRegion->m_afMax[1]);
//
//			pRegion->index = GetRegionIndex( nRow, nCol );
//
//			fX += fCellWidth;
//		}
//
//		fY += fCellHeight;
//	}
//
//	// assign each blade of grass to its particular region
//	for (vector<SBlade>::const_iterator iBlade = vSceneBlades.begin( ); iBlade != vSceneBlades.end( ); ++iBlade)
//	{
//		// convert position to row/col index
//		float fPercentAlongX = (iBlade->m_afPos[0] - m_afBoundingBox[0]) / (m_afBoundingBox[3] - m_afBoundingBox[0]);
//		float fPercentAlongY = (iBlade->m_afPos[1] - m_afBoundingBox[1]) / (m_afBoundingBox[4] - m_afBoundingBox[1]);
//
//		// clip values
//		unsigned int uiCol = (unsigned int)min(fPercentAlongX * m_nNumRegionCols, m_nNumRegionCols - 1);
//		unsigned int uiRow = (unsigned int)min(fPercentAlongY * m_nNumRegionRows, m_nNumRegionRows - 1);
//
//		m_vRegions[GetRegionIndex(uiRow, uiCol)].m_vBlades.push_back(*iBlade);
//	}
//
//	// compute z extents (now that the blades are in)
//	for (int i = 0; i < (int)m_vRegions.size( ); ++i)
//	{
//		SRegion* pRegion = &m_vRegions[i];
//
//		pRegion->m_afMin[2] = FP_MAX_VALUE;
//		pRegion->m_afMax[2] = -FP_MAX_VALUE;
//		for (vector<SBlade>::iterator iBlade = pRegion->m_vBlades.begin( ); iBlade != pRegion->m_vBlades.end( ); ++iBlade)
//		{
//			pRegion->m_afMin[2] = min(pRegion->m_afMin[2], iBlade->m_afPos[2]);
//			pRegion->m_afMax[2] = max(pRegion->m_afMax[2], iBlade->m_afPos[2]);
//		}
//
//		pRegion->m_afCenter[0] = 0.5f * (pRegion->m_afMin[0] + pRegion->m_afMax[0]);
//		pRegion->m_afCenter[1] = 0.5f * (pRegion->m_afMin[1] + pRegion->m_afMax[1]);
//		pRegion->m_afCenter[2] = 0.5f * (pRegion->m_afMin[2] + pRegion->m_afMax[2]);
//	}
//
//	// collision detection
//	if (fCollisionDistance > 0.0f)
//	{
//		fCollisionDistance *= fCollisionDistance;
//		for (int nRow = 0; nRow < m_nNumRegionRows; ++nRow)
//		{
//			//float fX = m_afBoundingBox[0];
//			for (int nCol = 0; nCol < m_nNumRegionCols; ++nCol)
//			{
//				SRegion* pRegion = &m_vRegions[GetRegionIndex(nRow, nCol)];
//
//				// check each blade against all other blades in the region
//				for (int i = 0; i < (int)pRegion->m_vBlades.size( ); ++i)
//				{
//					float fX = pRegion->m_vBlades[i].m_afPos[0];
//					float fY = pRegion->m_vBlades[i].m_afPos[1];
//					bool bCollision = false;
//					for (int j = 0; j < (int)pRegion->m_vBlades.size( ) && !bCollision; ++j)
//					{
//						if (i != j)
//						{
//							float fDistance = (fX - pRegion->m_vBlades[j].m_afPos[0]) * (fX - pRegion->m_vBlades[j].m_afPos[0]) + (fY - pRegion->m_vBlades[j].m_afPos[1]) * (fY - pRegion->m_vBlades[j].m_afPos[1]);
//							if (fDistance < fCollisionDistance)
//								bCollision = true;
//						}
//					}
//					
//					// delete the blade if necessary and adjust the main loop counter to compensate
//					if (bCollision)
//						pRegion->m_vBlades.erase(pRegion->m_vBlades.begin( ) + i--);
//				}
//			}
//		}
//	}
//}

///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::ConvertCoordsToCell

//void CSpeedGrassRT::ConvertCoordsToCell(const float* pCoords, int* pGridCoords) const
//{
//	float fPercentAlongX = (pCoords[0] - m_afBoundingBox[0]) / (m_afBoundingBox[3] - m_afBoundingBox[0]);
//	float fPercentAlongY = (pCoords[1] - m_afBoundingBox[1]) / (m_afBoundingBox[4] - m_afBoundingBox[1]);
//
//	if (fPercentAlongX < 0.0f)
//		pGridCoords[0] = -1;
//	else if (fPercentAlongX > 1.0f)
//		pGridCoords[0] = m_nNumRegionCols;
//	else
//		pGridCoords[0] = (int)(fPercentAlongX * m_nNumRegionCols);
//
//	if (fPercentAlongY < 0.0f)
//		pGridCoords[1] = -1;
//	else if (fPercentAlongY > 1.0f)
//		pGridCoords[1] = m_nNumRegionRows;
//	else
//		pGridCoords[1] = (int)(fPercentAlongY * m_nNumRegionRows);
//}

///////////////////////////////////////////////////////////////////////  
//	CSpeedGrassRT::DeleteRegions

//void CSpeedGrassRT::DeleteRegions( )
//{
//	//for (int i = 0; i < m_vRegions.size( ); ++i)
//	//{
//	//	delete m_vRegions[i].m_pGeomBuffer;
//	//	m_vRegions[i].m_pGeomBuffer = NULL;
//	//}
//	m_vRegions.clear( );
//}
