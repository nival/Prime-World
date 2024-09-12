#include "stdafx.h"
#include "DXManager.h"


#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
static NDebug::DebugVar<int> render_ActiveBuffSize( "ActiveBuffSize", "PerfCnt", false );
static NDebug::DebugVar<int> render_ActiveTexSize( "ActiveTexSize", "PerfCnt", false );
#endif


/* For use in ID3DResource9::SetPriority calls */
#define D3D9_RESOURCE_PRIORITY_MINIMUM       0x28000000
#define D3D9_RESOURCE_PRIORITY_LOW           0x50000000
#define D3D9_RESOURCE_PRIORITY_NORMAL        0x78000000
#define D3D9_RESOURCE_PRIORITY_HIGH          0xa0000000
#define D3D9_RESOURCE_PRIORITY_MAXIMUM       0xc8000000


namespace Render
{

void DXManager::Clear()
{
  indicesSet.map.clear();
  verticesSet.map.clear();
  texturesSet.map.clear();
}


static inline DXManager::Desc CreateData(IDirect3DVertexBuffer9* _buffer, UINT _timeStamp)
{
  DXManager::Desc result = { D3DPOOL_DEFAULT, _timeStamp };

  if(_buffer)
  {
    D3DVERTEXBUFFER_DESC desc;

    _buffer->GetDesc(&desc);
    result.pool = desc.Pool;
#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
    // Calculate approximate texture size in bytes
    result.size = desc.Size;
  }
  else {
    result.size = 0;
#endif
  }
  return result;
}


static inline DXManager::Desc CreateData(IDirect3DIndexBuffer9* _buffer, UINT _timeStamp)
{
  DXManager::Desc result = { D3DPOOL_DEFAULT, _timeStamp };

  if(_buffer)
  {
    D3DINDEXBUFFER_DESC desc;

    _buffer->GetDesc(&desc);
    result.pool = desc.Pool;
#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
    // Calculate approximate texture size in bytes
    result.size = desc.Size;
  }
  else {
    result.size = 0;
#endif
  }
  return result;
}


static inline DXManager::Desc CreateData(IDirect3DBaseTexture9 *_texture, UINT _timeStamp)
{
  DXManager::Desc result = { D3DPOOL_DEFAULT, _timeStamp };

#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
  const UINT  levelScale  = 1 << ( 2 * _texture->GetLevelCount() );
  const float mipMapScale = float(levelScale - 1) / (6 * levelScale);
  result.size = 0;
#endif

  switch( _texture->GetType() )
  {
  case D3DRTYPE_TEXTURE:
    {
      D3DSURFACE_DESC desc;
      ((IDirect3DTexture9*)_texture)->GetLevelDesc(0, &desc);
#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
      // Calculate approximate texture size in bytes
      result.size = mipMapScale * D3DFormatNumBits(desc.Format) * desc.Width * desc.Height;
#endif
      result.pool = desc.Pool;
      break;
    }
  case D3DRTYPE_VOLUMETEXTURE:
    {
      D3DVOLUME_DESC desc;
      ((IDirect3DVolumeTexture9*)_texture)->GetLevelDesc(0, &desc);
#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
      // Calculate approximate texture size in bytes
      result.size = mipMapScale * D3DFormatNumBits(desc.Format) * desc.Width * desc.Height * desc.Depth;
#endif
      result.pool = desc.Pool;
      break;
    }
  case D3DRTYPE_CUBETEXTURE:
    {
      D3DSURFACE_DESC desc;
      ((IDirect3DCubeTexture9*)_texture)->GetLevelDesc(0, &desc);
#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
      // Calculate approximate texture size in bytes
      result.size = mipMapScale * D3DFormatNumBits(desc.Format) * desc.Width * desc.Height * 6;
#endif
      result.pool = desc.Pool;
      break;
    }
  }
  return result;
}


//////////////////////////////////////////////////////////////////////////////////////////
//  DXManager class
//////////////////////////////////////////////////////////////////////////////////////////

DXManager::DXManager() :
#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
  indicesSet(&render_ActiveBuffSize), verticesSet(&render_ActiveBuffSize), texturesSet(&render_ActiveTexSize),
#endif
  timeStamp() {}


// Set NORMAL priority for resources that become visible and push them to preload list
template<class I>
void DXManager::AddResource(I *_resource, DXManager::ResourceSet& _set)
{
  Iter const it = _set.map.find(_resource);
  if( it != _set.map.end() )
    it->second.timeStamp = timeStamp;
  else
  { // Add new resource
    const DXManager::Desc& desc = CreateData(_resource, timeStamp);
    _set.map.insert( make_pair(_resource, desc) );
    if( D3DPOOL_MANAGED == desc.pool )
    {
      _resource->SetPriority(D3D9_RESOURCE_PRIORITY_HIGH);
#ifdef PRELOAD_MANAGED_POOL_RESOURCES
      newResources.push_back(_resource);
#endif
#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
      _set.counter.AddValue(desc.size);
#endif
    }
  }
}

// Set LOW priority for resources that become invisible and remove them from set
void DXManager::ManageResources(ResourceSet& _set)
{
  for(Iter it = _set.map.begin(); it != _set.map.end();)
  {
    const Desc& desc = it->second;
    if(desc.timeStamp == timeStamp)
      ++it;
    else
    { // Aged resource found - remove it
      if( D3DPOOL_MANAGED ==  desc.pool )
      {
        it->first->SetPriority(D3D9_RESOURCE_PRIORITY_LOW);
#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
        _set.counter.DecValue(desc.size);
#endif
      }
      it = _set.map.erase(it);
    }
  }
}


void DXManager::Manage()
{
  ManageResources(texturesSet);
  ManageResources(verticesSet);
  ManageResources(indicesSet);

#ifdef PRELOAD_MANAGED_POOL_RESOURCES
  for(ResourceList::iterator it = newResources.begin(), end = newResources.end(); it != end; ++it)
    (*it)->PreLoad();

  newResources.clear();
#endif
}


void DXManager::AddGeometry(const GeometryBuffers& _arg)
{
  if( _arg.pVB[0] )
    AddResource(_arg.pVB[0], verticesSet);
  if( _arg.pVB[1] )
    AddResource(_arg.pVB[1], verticesSet);
  if( _arg.pIB )
    AddResource(_arg.pIB, indicesSet);
}

void DXManager::AddTextures(const BaseMaterial* _pMaterial)
{
  // Dark art of black hacking - calculate samplers pointers.
  const Material::Samplers& samplers = _pMaterial->GetSamplers();
  const int * const pDisplacements = samplers.samplers;
  const char* const pMemberBase = (const char*)_pMaterial;
  for(int i = 0; i < samplers.count; ++i)
  {
    const Sampler *pSampler = (const Sampler*)(pMemberBase + pDisplacements[i]);
    if( const TextureRef& pTex = pSampler->GetTexture() )
      if( const DXBaseTextureRef& pDXTex = pTex->GetDXTexture() )
        AddResource(Get(pDXTex), texturesSet);
  }
}

}
