#include "stdafx.h"

#include "TerrainLayerManager.h"
#include "TerrainElementManager.h"
#include "TerrainElement.h"
#include "Terrain.h"

#include "../System/Array2DWrapper.h"
#include "ArraySampler.h"

#include "../Render/texture.h"
#include "../Render/renderer.h"

#include "../System/Win32Random.h"

namespace Terrain
{

	void TerrainLayerRegion::GetWorldAABB(GridConstants const& params, Render::AABB& bounds) const
	{
		bounds.center = (ptMax + ptMin) * 0.5f;
		bounds.halfSize = (ptMax - ptMin) * 0.5f;

		bounds.center.Mul(bounds.center, params.worldSize);
		bounds.halfSize.Mul(bounds.halfSize, params.worldSize);

		CVec3 halfTexel(0.5f * params.metersPerTexel, 0.5f * params.metersPerTexel, 0.0f);
		bounds.center += halfTexel;
		bounds.halfSize += 3.0f * halfTexel; // add safe boundary of one texel for bilinear filtration
		bounds.halfSize.z = 1000.0f;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initialization

	TerrainLayerManager::TerrainLayerManager() : pOwner(NULL), maskXSize(0), maskYSize(0), isNatureMapDirty(true), lastWrittenLayer(-1)
	{
    // Create 27 unique colors
    debugPalette.clear();

    nstl::vector<float> realValues;
    realValues.push_back(1.0f);
    realValues.push_back(0.5f);
    realValues.push_back(0.0f);

    for ( int x = 0; x < realValues.size(); x++ )
    {
      for ( int y = 0; y < realValues.size(); y++ )
      {
        for ( int z = 0; z < realValues.size(); z++ )
        {
          CVec4 color;
          color.x = realValues[x];
          color.y = realValues[y];
          color.z = realValues[z];
          color.w = 1.0f;
          debugPalette.push_back( color );
        }
      }
    }
	}

	TerrainLayerManager::~TerrainLayerManager()
	{
		for(TerrainLayerList::iterator it = layers.begin(); it != layers.end(); ++it)
		{
			delete it->second.pMaterial;
		}
	}

	void TerrainLayerManager::Initialize()
	{
		ASSERT(maskXSize == 0 && maskYSize == 0);
		GridConstants const& params = pOwner->GetGridConstants();
		maskXSize = params.sizeInTexels.x;
		maskYSize = params.sizeInTexels.y;
		layerMask.SetSizes(maskXSize, maskYSize);
		layerMask.FillEvery(LOCAL_LAYER);

		layers[HOLES_LAYER].pMaterial = NULL;
		layers[LOCAL_LAYER].pMaterial = NULL;

#ifndef VISUAL_CUTTED
/*
		// smirnov [2008/12/15]: debug code
		struct dbgdist { 
			float operator()(float x, float y, float x0, float y0) { return sqr(x-x0) + sqr(y-y0); }
		} dist2;
		for (int i = 0, n = natureMap.GetSizeY(); i < n; ++i)
		{
			float y = float(i) / float(n-1);
			for (int j = 0, m = natureMap.GetSizeX(); j < m; ++j)
			{
				float x = float(j) / float(m-1);
				if (dist2(x, y, 0.0f, 0.5f) < 0.125f || dist2(x, y, 0.5f, 0.0f) < 0.125f)
					natureMap[i][j] = NATURE_A;
				else if (dist2(x, y, 1.0f, 0.5f) < 0.125f || dist2(x, y, 0.5f, 1.0f) < 0.125f)
					natureMap[i][j] = NATURE_B;
				else
					natureMap[i][j] = NATURE_0;
			}
		}
*/
#endif
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Serialization

	void TerrainLayerManager::Load( const NDb::TerrainLayers& layers, const string& maskFileName )
	{
		// smirnov [2008/12/2]: note, this function is called only in-game

		LoadLayerMask(maskFileName, false); // load but don't update color masks
		for(vector<NDb::TerrainLayer>::const_iterator it = layers.terrainLayers.begin(); it != layers.terrainLayers.end(); ++it )
			if( IsValid( it->pTerrainType ) && IsValid( it->pTerrainType->pDBMaterial ) )
				AddLayer( it->pTerrainType->pDBMaterial );
		areIndicesDirty = true;
	}

	void TerrainLayerManager::SaveLayerMask( const nstl::string& filename )
	{
		CObj<Stream> pStream = RootFileSystem::OpenFile( filename, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
		NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open file for writing %s", filename ), return );
		pStream->Write(&layerMask[0][0], layerMask.GetSizeX() * layerMask.GetSizeY());

        MessageTrace( "TerrainLayerManager::SaveLayerMask done" );
	}

	void TerrainLayerManager::LoadLayerMask( const nstl::string& filename, bool forceUpdate /*= true*/ )
	{
		CObj<Stream> pStream = RootFileSystem::OpenFile( filename, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
		if (pStream != 0)
			pStream->Read(&layerMask[0][0], layerMask.GetSizeX() * layerMask.GetSizeY());
		else
			layerMask.FillEvery(LOCAL_LAYER);
		
		if (forceUpdate)
			updateRegion.SetToWorld();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Creation

	int TerrainLayerManager::AddLayer( const NDb::Material* pMaterial )
	{
		int counter = RESERVED_LAYERS_COUNT;
#ifndef VISUAL_CUTTED
    while( layers.find(counter) != layers.end() ) { ++counter; } // smirnov [2008/11/27]: slow
		layers[counter].pMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( pMaterial ) );
#endif
		return counter;
	}

	void TerrainLayerManager::ReplaceLayer( int index, const NDb::Material* pMaterial )
	{
#ifndef VISUAL_CUTTED
    ASSERT(index >= RESERVED_LAYERS_COUNT);
		ASSERT( pMaterial );
		TerrainLayer& layer = layers[index];
		delete layer.pMaterial;
    layer.pMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( pMaterial ) );
#endif
	}

	void TerrainLayerManager::RemoveLayer( int index )
	{
		ASSERT( index >= RESERVED_LAYERS_COUNT );
		ASSERT( layers.find(index) != layers.end() );
		TerrainLayerList::iterator it = layers.find(index);
		delete it->second.pMaterial;
		layers.erase(it);

		// remove layer references and shift others
		for (int row = 0; row < maskYSize; row++)
		{
			for (int col = 0; col < maskXSize; col++)
			{
				unsigned char layerIndex = ReadLayerValue(row, col);
				if (layerIndex == index)
					WriteLayerValue(LOCAL_LAYER, row, col);
			}
		}
		areIndicesDirty = true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Modification

	void TerrainLayerManager::WriteLayerValue(int layerIndex, int row, int column)
	{
//		ASSERT(layerIndex < layers.size());
		layerMask[row][column] = layerIndex;
		updateRegion.Add(CVec3(float(column) / float(maskXSize), float(row) / float(maskYSize), 0.0f));
    lastWrittenLayer = layerIndex;
	}

	unsigned char TerrainLayerManager::ReadLayerValue(int layerIndex, int row, int column)
	{
//		ASSERT(layerIndex < layers.size());
		return 255 * (layerMask[row][column] == layerIndex);
	}

	void TerrainLayerManager::InvalidateLayers()
	{
		updateRegion.SetToWorld();
	}

	void TerrainLayerManager::NotifyElementChange(TerrainElementId id)
	{
#ifndef VISUAL_CUTTED
		TerrainElement* pFragment = pOwner->GetElementManager().GetElement(id);
		Render::AABB const& aabb = pFragment->GetWorldAABB();
		GridConstants const& params = pOwner->GetGridConstants();
		
		CVec3 pt, scale(1.0f / params.worldSize.x, 1.0f / params.worldSize.y, 1.0f);
		pt.Mul(aabb.center - aabb.halfSize, scale);
		updateRegion.Add(pt);
		pt.Mul(aabb.center + aabb.halfSize, scale);
    updateRegion.Add(pt);
#endif
	}

  namespace
  {
    int _CompareLayers(void const *pp1, void const *pp2)
    {
      pair<int, int> const &p1 = *(pair<int, int>const*)pp1;
      pair<int, int> const &p2 = *(pair<int, int>const*)pp2;
      if (p1.second > p2.second)
        return -1;
      if (p1.second < p2.second)
        return 1;
      return 0;
    }
  }

  unsigned char TerrainLayerManager::FindMostUsedLayerAround(unsigned row, unsigned col, nstl::vector<pair<int, int>> const &validLayers)
  {
    // try simple case -- target cell contains valid layer
    {
      int l = ReadLayerValue(row, col);
      int i;
      for (i = 0; i < validLayers.size(); ++i)
      {
        if (l == validLayers[i].first)
          break;
      }
      if (i < MAX_NUM_LAYERS)
        return ReadLayerValue(row, col);
    }

    unsigned int layerUsage[256];
    ZeroMemory(layerUsage, sizeof(int) * 256);

    // we hope that 9x9 region will contain at least one pixel in any valid layer
    // otherwise someone is trying to eliminate layer that's not really rare
    
    unsigned rowStart = Max((int)row - 6, 1) - 1;
    unsigned colStart = Max((int)col - 6, 1) - 1;
    unsigned rowEnd = Min((int)row + 6, pOwner->GetGridConstants().sizeInTexels.y - 1);
    unsigned colEnd = Min((int)col + 6, pOwner->GetGridConstants().sizeInTexels.x - 1);

    // scan 9x9 neighbourhood
    for (unsigned r = rowStart; r <= rowEnd; r++)
    {
      for (unsigned c = colStart; c <= colEnd; c++)
      {
        ++layerUsage[ ReadLayerValue(r, c) ];
      }
    }

    // build sorted used-layers-list
    nstl::vector<pair<int, int>> usedLayers;
    for (int i = 0; i < 256; ++i)
    {
      if (layerUsage[i] > 0)
        usedLayers.push_back(pair<int,int>(i, layerUsage[i]));
    }
    qsort(&usedLayers[0], usedLayers.size(), sizeof(pair<int,int>), _CompareLayers);

    // find the most popular valid layer
    for (int i = 0; i < usedLayers.size(); ++i)
    {
      int const &l = usedLayers[i].first;
      for (int j = 0; j < validLayers.size(); ++j)
      {
        if (l == validLayers[j].first)
          return l;
      }
    }

    // failed to find valid layers around, return just the most popular (but invalid)
    return usedLayers[0].first;
  }

  void TerrainLayerManager::Update()
	{
		if (!updateRegion.IsEmpty())
			areIndicesDirty = true;

		if (areIndicesDirty)
		{
			// Find out which pixels were changed
			Render::AABB pixelBounds;
			TerrainLayerRegion updateRegionCopy = updateRegion;
			if (updateRegionCopy.IsEmpty())
				updateRegionCopy.SetToWorld();
			updateRegionCopy.GetWorldAABB(pOwner->GetGridConstants(), pixelBounds);

#ifndef VISUAL_CUTTED
			// Update layer indices in affected elements
			GridConstants const& params = pOwner->GetGridConstants();
			struct UpdateIDFunctor
			{
				TerrainLayerManager* layerManager;
				TerrainLayerMask *layerMask;
        TerrainElementManager* elemManager;
				unsigned pixelsPerElement;
				unsigned rowMax, colMax;
        bool bEditable;

				void operator()(TerrainElementInfo const& elem)
				{
					unsigned rowStart = Max(elemManager->GetElementRow(elem.id) * pixelsPerElement, 1U) - 1;
					unsigned colStart = Max(elemManager->GetElementColumn(elem.id) * pixelsPerElement, 1U) - 1;
					unsigned rowEnd = Min(rowStart + pixelsPerElement + 1, rowMax);
					unsigned colEnd = Min(colStart + pixelsPerElement + 1, colMax);
          int i = 0;

					// gather layer usage statistics
          int layerUsage[256];
          ZeroMemory(layerUsage, sizeof(int) * 256);
					for (unsigned row = rowStart; row <= rowEnd; row++)
					{
						for (unsigned col = colStart; col <= colEnd; col++)
						{
              ++layerUsage[ layerManager->ReadLayerValue(row, col) ];
						}
					}

          // build used layers list
          nstl::vector<pair<int, int>> layers;
          for (i = 0; i < 256; ++i)
          {
            if (layerUsage[i] > 0)
              layers.push_back(pair<int,int>(i, layerUsage[i]));
          }

/*
          // eliminate rarely used layers
          // (this aplies only in edit mode)
          if (bEditable && layers.size() > MAX_NUM_LAYERS)
          {
            // build sorted layer list (descending by usage)
            qsort(&layers[0], layers.size(), sizeof(pair<int,int>), _CompareLayers);

            NI_ASSERT(layers.size() == MAX_NUM_LAYERS + 1, "Added several extra layers at once, weird");

            // can't eliminate layer that's being written to right now
            for (i = MAX_NUM_LAYERS; i < layers.size(); ++i)
            {
              if (layers[i].first == layerManager->GetLastWrittenLayer())
              {
                // swap with last valid layer
                pair<int, int> t = layers[i];
                layers[i] = layers[MAX_NUM_LAYERS - 1];
                layers[MAX_NUM_LAYERS - 1] = t;
                break;
              }
            }

            // strip invalid layers
            layers.resize(MAX_NUM_LAYERS);

            // build fill mask for invalid cells
            CArray2D<unsigned char> newMask(rowEnd - rowStart + 1, colEnd - colStart + 1);
            newMask.FillZero();

            for (unsigned row = rowStart; row <= rowEnd; row++)
            {
              for (unsigned col = colStart; col <= colEnd; col++)
              {
                // is layer valid at this place?
                int l = layerManager->ReadLayerValue(row, col);
                for (i = 0; i < MAX_NUM_LAYERS; ++i)
                {
                  if (l == layers[i].first)
                    break;
                }

                if (i == MAX_NUM_LAYERS)
                  newMask.Set(row - rowStart, col - colStart, layerManager->FindMostUsedLayerAround(row, col, layers));
              }
            }

            // copy fill mask to main mask
            for (unsigned row = rowStart; row <= rowEnd; row++)
            {
              for (unsigned col = colStart; col <= colEnd; col++)
              {
                // is layer valid at this place?
                int l = layerManager->ReadLayerValue(row, col);
                for (i = 0; i < MAX_NUM_LAYERS; ++i)
                {
                  if (l == layers[i].first)
                    break;
                }

                if (i == MAX_NUM_LAYERS)
                  (*layerMask)[row][col] = newMask.Get(row - rowStart, col - colStart);
              }
            }
          }
*/

					// copy the set to the element
					elem.pElement->layerIndices.resize(0);
					for (int i = 0; i < layers.size(); ++i)
          {
            elem.pElement->layerIndices.push_back(layers[i].first);
          }
				}
			} updateIDs = {this, &layerMask, &pOwner->GetElementManager(), params.texelsPerElement, params.sizeInTexels.y - 1, params.sizeInTexels.x - 1, pOwner->IsEditable()};
			pOwner->GetElementManager().ForAllElementInfosAABB(updateIDs, pixelBounds);
#endif

			areIndicesDirty = false;
		}

		if (isNatureMapDirty)
		{
#ifndef VISUAL_CUTTED
			struct UpdateMapFunctor
			{
				void operator()(TerrainElementInfo const& elem)
				{
          // smirnov [2009/4/20]: todo:
				}
			} updateMap;
			pOwner->GetElementManager().ForAllElementInfos(updateMap);

#endif
			isNatureMapDirty = false;
		}
	}

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Render::Texture* TerrainLayerManager::GetLayerTexture( int layerNumber, NatureType natureType, Render::BaseMaterial* localMaterial ) const
	{
		Render::BaseMaterial* pMaterial = localMaterial;
		if (layerNumber >= RESERVED_LAYERS_COUNT)
		{
			TerrainLayerList::const_iterator it = layers.find(layerNumber);
			if (it != layers.end())
				pMaterial = it->second.pMaterial;
		}

		if (!pMaterial)
			return 0;

		switch (natureType)
		{
		case NATURE_0:
			return pMaterial->GetDiffuseMap()->GetTexture();
		case NATURE_A:
			return pMaterial->GetDiffuseMapFrozen()->GetTexture();
		case NATURE_B:
			return pMaterial->GetDiffuseMapBurned()->GetTexture();
		default:
			NI_ALWAYS_ASSERT("Illegal nature type");
			return 0;
		}
	}

	CVec4 const& TerrainLayerManager::GetLayerDebugColor( int layerNumber )
	{
    NI_VERIFY( 0 <= layerNumber, "Bad layer number", return debugPalette[0] );

    // We need more than 27 layers!
		if ( layerNumber >= debugPalette.size() )
    {
      CVec4 color;
      color.x = NWin32Random::Random( 0.0f, 1.0f );
      color.y = NWin32Random::Random( 0.0f, 1.0f );
      color.z = NWin32Random::Random( 0.0f, 1.0f );
      color.w = 1.0f;
      debugPalette.push_back( color );
      return GetLayerDebugColor( layerNumber );
    }
		return debugPalette[layerNumber];
	}

	void TerrainLayerManager::NotifyNatureChange(TerrainElementId id)
	{
		isNatureMapDirty = true;

#ifndef VISUAL_CUTTED
		// invalidate elements around given
		//TerrainElementManager& elemManager = pOwner->GetElementManager();
		//unsigned row = elemManager.GetElementRow(id);
		//unsigned rowMax = Min(row + 1, elemManager.GetMaxRow());
		//row = Max(row, 1U) - 1;
		//unsigned col = elemManager.GetElementColumn(id);
		//unsigned colMax = Min(col + 1, elemManager.GetMaxColumn());
		//col = Max(col, 1U) - 1;
		//for (unsigned i = row; i <= rowMax; i++)
		//{
		//	for (unsigned j = col; j <= colMax; j++)
		//	{
		//		id = elemManager.LocateElement(i, j);
		//		natureMapDirty.SetData(id);
		//	}
		//}
#endif
  }

};
