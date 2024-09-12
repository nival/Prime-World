#pragma once

#include "../../SwfTypes.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace flash
{

class MeshSet;
_interface ITesselatedShape;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FlashMeshCollection
{
public:
	FlashMeshCollection();
  ~FlashMeshCollection();

  void Initialize();
  void Release();

  static FlashMeshCollection* GetInstance();

  int	GetMeshSetID( const nstl::string& fileName, int characterID, int rate );
  MeshSet*	GetMeshSet( int meshSetID, float error_tolerance, const ITesselatedShape* shape );

private:

  void sortMeshes( nstl::vector<Strong<MeshSet>>& meshes );

  struct MeshSetDesc
  {
    nstl::vector<Strong<MeshSet>>	cashedMeshes;
  };

  typedef nstl::hash_map<nstl::string, int> NameIDMap;
  typedef nstl::vector<MeshSetDesc> Meshes;

  NameIDMap nameIDMap;
  Meshes  meshes;
  int uniqueMeshID;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace gameswf