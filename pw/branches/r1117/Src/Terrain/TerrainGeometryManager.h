#pragma once

#include "../System/staticarray.h"
#include "../System/noncopyable.h"
#include "../System/Stream.h"
#include "../Render/aabb.h"
#include "../Render/light.h"
#include "BezierSurface.h"
#include "../Render/MeshResource.h"
#include "TerrainElementManager.h"

namespace NDb
{
	struct TerrainElement;
}

namespace NScene
{
	class LightingScene;
}

struct TerrainElementStrideNew;

namespace Terrain
{
	class Terrain;

	typedef CVec3 ControlVertex;
	enum
  {
    INVALID_GEOMETRY = 0x0001,
    INVALID_LIGHTING = 0x0002,
    INVALID_MASKS    = 0x0004
  };

  namespace EModification
  {
    enum Enum
    {
      First,
      Next,
      Last
    };
  }

	/**
	 *	Manage patches and terrain elements
	 */
	class TerrainGeometryManager
		: private NonCopyable
	{
	public:
		struct ModificationRequestData
		{
			///< terrain element id
			TerrainElementId id;
			int flags; ///< flags defining what should be invalidated
			///< buffer for result
			volatile unsigned char* pData;
			///< target AABB to be filled
			Render::AABB *pAABB;
			///< field determine if the request had been processed 
			volatile bool finished;

      ModificationRequestData() 
				: id( -1 ), flags( 0 ), pAABB( 0 ), finished( false ), pData( 0 ) {}
			ModificationRequestData( TerrainElementId _id, int _flags, Render::AABB *_pAABB ) 
				: id( _id ), flags( _flags ), pAABB( _pAABB ), finished( false ), pData( 0 ) {}

      void Set( TerrainElementId _id, int _flags, Render::AABB *_pAABB )
      {
        id = _id;
        flags = _flags;
        pAABB = _pAABB;
      }
		};

	public:
    typedef void (*ModificationCallback)( void *pData, int flags, int elementID, EModification::Enum callbackType );

		static const int MAXIMUM_NUMBER_OF_PATCHES = 128;
		static const int MAXIMUM_INDEX_OF_TCV = MAXIMUM_NUMBER_OF_PATCHES + 1;
		
    static const int NUMBER_OF_CV = MAXIMUM_INDEX_OF_TCV + MAXIMUM_NUMBER_OF_PATCHES * (Patch::NUMBER_OF_CV - 2);

	private:
		Terrain* pOwner; // smirnov [2008/12/11]: CPtr<> is not possible here

		struct TCVManager;
		typedef StaticArray<StaticArray<ControlVertex, NUMBER_OF_CV>, NUMBER_OF_CV> ControlVertexesContainer;
		ControlVertexesContainer controlVertexes;

		CVec3 patchesOrigin;
    float weldThreshold;
    float weldLookupSize;

		// what is TCV see in http://SITE
		///< storage of TCV basis
		typedef StaticArray<StaticArray<Matrix43, MAXIMUM_INDEX_OF_TCV>, MAXIMUM_INDEX_OF_TCV> TCVContainer;
		TCVContainer TCVs;

		/** used demand modification of terrain elements */
		StaticArray<StaticArray<bool, MAXIMUM_INDEX_OF_TCV>, MAXIMUM_INDEX_OF_TCV> changedTCVs;


		///< cache of association TCV <=> TerrainElement
		typedef StaticArray<StaticArray<vector<TerrainElementId>, MAXIMUM_INDEX_OF_TCV>, MAXIMUM_INDEX_OF_TCV> TCV2TerrainAssociation;
		TCV2TerrainAssociation TCV2TerrainElement;

		///< requests to calculation of geometry
		typedef list<ModificationRequestData> RequestsContainer;
		mutable RequestsContainer requests;

		typedef const char* OriginalGeometriesBuffer;
		struct OriginalGeometryInformation
		{
			///< size of vertex buffer [in bytes]
			unsigned int bufferSize;
			///< pointer to original vertex buffer
			OriginalGeometriesBuffer pOriginaVertexBuffer;

			OriginalGeometryInformation() : bufferSize( 0 ), pOriginaVertexBuffer( 0 ) {}
			OriginalGeometryInformation( unsigned int size, OriginalGeometriesBuffer pBuffer ) 
				: bufferSize( size ), pOriginaVertexBuffer( pBuffer ) {}

			bool operator == ( const OriginalGeometryInformation& other ) const 
			{
				return bufferSize == other.bufferSize && pOriginaVertexBuffer == other.pOriginaVertexBuffer;
			}

			bool operator != ( const OriginalGeometryInformation& other ) const { return !( *this == other ); }
		};

		typedef hash_map<TerrainElementId, Matrix43> TerrainElementPlacementContainer;
		TerrainElementPlacementContainer geometryPlacement;

		///< original geometry
		typedef hash_map<TerrainElementId, OriginalGeometryInformation> GeometryInformationContainer;
		GeometryInformationContainer geometryInformations;

		///< used in editor while elements can be removed and added
		typedef hash_map<string, OriginalGeometryInformation> FileToOriginalGeometryAssociation;
		FileToOriginalGeometryAssociation fileToOriginalGeometry;

		///< used in editor to optimize terrain baking
		typedef hash_map<TerrainElementId, Render::TerrainElementGeometryRaw> TerrainElementModifiedContainer;
		TerrainElementModifiedContainer modifiedGeometry;

    NScene::LightingScene *lightingScene;

    typedef  list<pair<void*, void*>>  ModificationCallbackList;
    ModificationCallbackList  modificationCallbacks;

	public:	
		TerrainGeometryManager();
		~TerrainGeometryManager();

		void SetOwner(Terrain* owner) { pOwner = owner; }

		/** init manager in editor */
		void Initialize( const NDb::TerrainGeometry& descriptor );

		/** load all terrain geometry in game from map descriptor (terrain elements and TCV) */
		bool Load( const NDb::TerrainGeometry& descriptor );

		/** bake terrain element geometry to stream */
		bool BakeTerrainElement( TerrainElementId, Stream* toBake ) const;
    void WeldVertices(bool syncVisual) const;

    unsigned GetBakedTerrainFileSignature() const;

		/** add new terrain element */
		TerrainElementId AddTerrainElement( const NDb::TerrainElementInstance& descriptor, const string& fileName );
		/** delete terrain element */
		bool DeleteTerrainElement( TerrainElementId id );
		/** set new world position */
//		void SetPlacement( TerrainElementId id, const Matrix43& worldPosition );

    Render::TerrainElementGeometryRaw* GetElement(TerrainElementId id);
    Render::TerrainElementGeometryRaw const* GetElement(TerrainElementId id) const;

		/** save TCV */
		void SaveTCV( Stream* );
		/** load TCV */
		void LoadTCV( Stream*, bool applyInstuntly );

		/** process demand modification of geometry */
		void Update();

		/**
		 *	set for given TCV world position
		 *	TCV is pointed by index (column, row) [0, MAXIMUM_NUMBER_OF_PATCHES]
		 *	do demand modification
		 */
		void SetTCV( int column, int row, const Matrix43& basis );
		/** get TCV basis for modification */
		const Matrix43& GetTCV( int column, int row ) const;

		void Modify( TerrainElementStrideNew* out, const TerrainElementStrideNew* in, unsigned int bufferSize, const Matrix43& basis ) const;

		//template<typename Geometry, bool normalPresent, bool binormalPresent, bool tangentPresent>
		//	void Modify( Geometry* out, const Geometry* in, unsigned int bufferSize, const Matrix43& basis ) const;

		void InvalidateElement(TerrainElementId id, int flags);

    void SetLightingScene( NScene::LightingScene *lightingScene_ ) { lightingScene = lightingScene_; }

    void SubscribeOnModification(ModificationCallback cb, void *pData)
    {
      modificationCallbacks.push_back(pair<void*, void*>((void*)cb, pData));
    }

    void UnsubscribeOnModification(ModificationCallback cb, void *pData)
    {
      modificationCallbacks.remove(pair<void*, void*>((void*)cb, pData));
    }

    void CopySubscribers(TerrainGeometryManager &otherMan)
    {
      modificationCallbacks.insert(modificationCallbacks.end(), otherMan.modificationCallbacks.begin(), otherMan.modificationCallbacks.end());
    }

	private:
		/** apply TCV to elements */
		void ApplyTCV( int row, int column );

		/** add new terrain element from baked file */
		TerrainElementId AddTerrainElement( const NDb::TerrainElementInstance&, Stream* baked );
		
		/** link terrain elements and patches */
		void AssociateTerrainElementAndTCV( TerrainElementId id );

		/** calculate vertex position by using NURBS, get points in NURBS space */
		CVec3 ComputeVertex( const CVec3& vertex ) const;

		/** check data and send modification requests */
		void CheckTCV();
		void CheckMasks();

		/** process TE modification request, modify TEs */
		void ProcessModificationRequests();
		void CopyMasks( TerrainElementId id, TerrainElementStrideNew* out, unsigned int bufferSize );
		void CalculateLighting( TerrainElementId id, TerrainElementStrideNew* out, unsigned int bufferSize );
    void CalculateLightingEx(TerrainElementId id, TerrainElementStrideNew* out, unsigned int bufferSize, const NDb::ELightEnvironment selector);
    
		/** serialize TCV information */
		void Serialize( Stream*, bool reading, bool applyInstuntly = false );

    void DoubleSizeConverter( int fromSize );

		/** used in editor to get hashed information */
		const OriginalGeometryInformation& GetOriginalGeometryInformation( const string& fileName, const Render::TerrainElementGeometryRaw& rawData );

    bool LoadBakedGeometry(const NDb::TerrainGeometry& descriptor);
    bool LoadRawGeometry(const NDb::TerrainGeometry& descriptor);
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//template<typename Geometry, bool normalPresent, bool binormalPresent, bool tangentPresent>
	//	void TerrainGeometryManager::Modify( Geometry* out, const Geometry* in, unsigned int bufferSize, const Matrix43& basis ) const
	//	{
	//		const Matrix43 inverseMatrix = basis.GetInversed();

	//		const unsigned int numberOfElements = bufferSize / sizeof( Geometry );
	//		for( unsigned int i = 0; i < numberOfElements; ++i )
	//		{
	//			const CVec3 inPosition = Transform( reinterpret_cast<const CVec3&>( in[i] ), basis );
	//			CVec3& outPosition = reinterpret_cast<CVec3&>( out[i] );

	//			//const float x = inPosition.x - patchesOrigin.x;
	//			//const float y = inPosition.y - patchesOrigin.y;

	//			// compute NURBS vertex
	//			//const CVec3 nurbsVertex = ComputeVertex( x, y );

	//			const CVec3 vertex = inPosition - patchesOrigin;
	//			const CVec3 nurbsVertex = ComputeVertex( vertex );


	//			//// calculate normal for NURBS vertex
	//			//const float delta = 0.05f;
	//			//CVec3 vector1;
	//			//CVec3 vector2;
	//			////
	//			//if( x + delta < Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES )
	//			//	vector1 = ComputeVertex( x + delta, y ) - nurbsVertex;
	//			//else
	//			//	vector1 = ComputeVertex( x - delta, y ) - nurbsVertex;

	//			//if( y + delta <= Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES )
	//			//	vector2 = ComputeVertex( x, y + delta ) - nurbsVertex;
	//			//else
	//			//	vector2 = ComputeVertex( x, y - delta ) - nurbsVertex;

	//			//CVec3 nurbsNormal;
	//			//if( (x + delta < Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES && y + delta >= Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES ) ||
	//			//	(x + delta >= Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES && y + delta < Patch::SIZE_OF_PATCH * MAXIMUM_NUMBER_OF_PATCHES ) )
	//			//	nurbsNormal= vector2 ^ vector1;
	//			//else
	//			//	nurbsNormal= vector1 ^ vector2;
	//			//Normalize( &nurbsNormal );

	//			////NI_ASSERT( nurbsNormal.z > 0.f, "" );

	//			//// calculate result position, move NURBS point along normal by z
	//			//outPosition.Displace( nurbsVertex, nurbsNormal, inPosition.z );
	//			
	//			// to show nurbs uncomment next code
	//			outPosition = nurbsVertex;

	//			//const float epsilon = 0.01f;
	//			//ASSERT( ::fabs( inPosition.x - outPosition.x ) < epsilon 
	//			//	&& ::fabs( inPosition.y - outPosition.y ) < epsilon
	//			//	&& ::fabs( inPosition.z - outPosition.z ) < epsilon );

	//			outPosition = Transform( outPosition, inverseMatrix );

	//			//if( normalPresent )
	//			//{
	//			//	const CVec3& inNormal = reinterpret_cast<const CVec3&>( *( &in[i] + sizeof( inPosition ) ) );
	//			//	CVec3& outNormal = reinterpret_cast<CVec3&>( *( &out[i] + sizeof( outPosition ) ) );
	//			//	// TODO: need to implement					
	//			//}

	//			//if( binormalPresent )
	//			//{
	//			//	//const CVec3& inBinormal = reinterpret_cast<const CVec3&>( *( &in[i] + sizeof( inPosition ) ) );
	//			//	//CVec3& outBinormal = reinterpret_cast<CVec3&>( *out[i] );
	//			//	// TODO: need to implement
	//			//}

	//			//if( tangentPresent )
	//			//{
	//			//	// TODO: need to implement
	//			//}
	//		}
	//	}

}
