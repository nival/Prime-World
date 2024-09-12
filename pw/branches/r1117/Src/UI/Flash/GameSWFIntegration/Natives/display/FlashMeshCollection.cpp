#include "TamarinPCH.h"

#include <Render/FlashRendererInterface.h>

#include "FlashMeshCollection.h"
#include "MeshSet.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace 
{
  flash::FlashMeshCollection* flashMeshCollection = 0;
}


namespace flash
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InitializeFlash()
{
  if ( flashMeshCollection  == 0)
  {
    flashMeshCollection = new FlashMeshCollection();
    flashMeshCollection->Initialize(); 
  }


  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool  ReleaseFlash()
{
  if ( flashMeshCollection )
  {
    flashMeshCollection->Release(); 
    delete flashMeshCollection;
    flashMeshCollection = 0;
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlashMeshCollection* FlashMeshCollection::GetInstance()
{
  return flashMeshCollection;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlashMeshCollection::FlashMeshCollection() :
  uniqueMeshID(0)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlashMeshCollection::~FlashMeshCollection()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashMeshCollection::Initialize()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashMeshCollection::Release()
{
  meshes.clear();
  nameIDMap.clear();
  uniqueMeshID = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int	FlashMeshCollection::GetMeshSetID( const nstl::string& fileName, int characterID, int rate )
{
  nstl::string fullName = fileName + "_" + NStr::IntToStr( characterID ) + "_" + NStr::IntToStr( rate );

  NameIDMap::iterator it = nameIDMap.find( fullName );

  if ( it != nameIDMap.end() )
    return it->second;

  meshes.resize( meshes.size() + 1 );

  int newID = meshes.size() - 1;

  nameIDMap[ fullName ] = newID;

  return newID;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MeshSet*	FlashMeshCollection::GetMeshSet( int meshSetID, float error_tolerance, const ITesselatedShape* shape )
{
  if ( meshSetID < 0 || meshSetID >= meshes.size() )
    return 0;

  MeshSetDesc& meshSetDesc = meshes[meshSetID];

  for ( int i = 0, n = meshSetDesc.cashedMeshes.size(); i < n; i++ )
  {
    MeshSet* candidate = meshSetDesc.cashedMeshes[i];

    if ( error_tolerance > candidate->get_error_tolerance() )
    {
      return candidate;
    }
  }

  Strong<MeshSet>	newMesh = shape ? new MeshSet( shape, error_tolerance * 0.75f ) : new MeshSet( error_tolerance * 0.75f );
  meshSetDesc.cashedMeshes.push_back( newMesh );

  sortMeshes( meshSetDesc.cashedMeshes );

  return newMesh;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int	sortByDecreasingError(const void* A, const void* B)
{
  const MeshSet*	a = *(const MeshSet**) A;
  const MeshSet*	b = *(const MeshSet**) B;

  if (a->get_error_tolerance() < b->get_error_tolerance())
  {
    return 1;
  }
  else if (a->get_error_tolerance() > b->get_error_tolerance())
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashMeshCollection::sortMeshes( nstl::vector<Strong<MeshSet>>& meshes )
{
  // Re-sort.
  if ( meshes.size() > 0 )
  {
    qsort(
      &meshes[0],
      meshes.size(),
      sizeof( meshes[0] ),
      sortByDecreasingError);
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} //namespace gameswf

