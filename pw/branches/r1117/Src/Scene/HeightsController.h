#pragma once

namespace Terrain { class Terrain; }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
class CollisionHull;

_interface IHeightsController
{
  virtual bool GetHeight( const float x, const float y, int layer, float* pHeight, CVec3* pNormal ) const = 0;
  virtual bool GetHeightsOfSquareArea( int sideInTiles, float x, float y, float& u, float& v, float result[] ) const = 0;
  virtual bool GetHeightByTile( const int x, const int y, int layer, float* pHeight, CVec3* pNormal ) const = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class HeightsController : public IHeightsController
{
public:
	_interface ILayerHeights : public CObjectBase
	{
		//OBJECT_BASIC_METHODS( ILayerHeight );
	public:

		virtual void Update() = 0;
		virtual int GetVersion() const = 0;
		virtual bool GetHeight( const float x, const float y, float* pHeight, CVec3* pNormal ) const = 0;

		virtual void AddObject( CollisionHull* pHull ) = 0;
		virtual void RemoveObject( CollisionHull* pHull ) = 0;

		virtual bool IsTerrainLayer() const = 0;

    virtual void Load(const nstl::string& filename) = 0;
    virtual void Save(const nstl::string& filename) = 0;

    virtual void Clear(int layer) = 0;
	};

private:
	class LayerInfo
	{
		int version;

	public:
		CObj<ILayerHeights> pLayerHeights;

		void Set( ILayerHeights* pLayerHeights );
		void Reset();
		
		bool UpdateVersion();
	};

	vector<LayerInfo> layers;
	int version;
  Terrain::Terrain* pTerrain;

  bool _GetHeight( const float x, const float y, int layer, float* pHeight, CVec3* pNormal ) const;

public:
	HeightsController() : version( -1 ), pTerrain( 0 ) {}

	void Initialize( const int layersCount );

	void AddTerrainToLayer( const int layer, Terrain::Terrain* pTerrain );
	
	void AddObjectToLayer( const int layer, CollisionHull* pHull );
	// RemoveObject is time consuming function
	void RemoveObject( CollisionHull* pHull );

	int GetVersion() const;

	virtual bool GetHeight( const float x, const float y, int layer, float* pHeight, CVec3* pNormal ) const;
  virtual bool GetHeightsOfSquareArea( int sideInTiles, float x, float y, float& u, float& v, float result[] ) const;
  virtual bool GetHeightByTile( const int tileX, const int tileY, int layer, float* pHeight, CVec3* pNormal ) const;

  void LoadObjectLayer( int layer, const nstl::string& filename );
  void SaveObjectLayer( int layer, const nstl::string& filename );
  void ClearHeightMapLayer( int layer );

  bool Intersect( CVec3* pIntersection, const CRay& ray ) const;

	void Update();
};

void PlaceOnTerrain(const IHeightsController &controller, CVec3 &pos, int layer = 0);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NScene
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
