#pragma once

#include "renderableprimitive.h"
#include "MaterialSpec.h"

#ifndef _SHIPPING
  #define COUNT_ACTIVE_MANAGED_POOL_RESOURCES
  //#define PRELOAD_MANAGED_POOL_RESOURCES
#endif

namespace Render
{

  struct PtrHash
  {
    template<class T, class U>
    size_t operator()(const IntrusivePtr<T, U>& _arg) const { return hash<void*>()((void*)Get(_arg)); }
    template<class T>
    size_t operator()(const T* _arg) const { return hash<void*>()((void*)_arg); }
  };

  class DXManager : public DeviceLostHandler
  {
  public:
    struct Desc
    {
      D3DPOOL   pool;
      UINT timeStamp;
#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
      UINT size;
#endif
    };

  private:
    typedef IntrusivePtr<IDirect3DResource9, DXObjectRefPolicy> ResourcePtr;
    struct ResourceSet
    {
      hash_map<const ResourcePtr, Desc, PtrHash> map;
#ifdef COUNT_ACTIVE_MANAGED_POOL_RESOURCES
      NDebug::DebugVar<int> &counter;

      ResourceSet(NDebug::DebugVar<int> *_pCounter) : counter(*_pCounter) {}
    private:
      ResourceSet(const ResourceSet& _src) : counter(_src.counter) {}
      ResourceSet& operator=(const ResourceSet&) {}
#endif
    };
    typedef hash_map<const ResourcePtr, Desc, PtrHash>::iterator Iter;
    typedef vector<IDirect3DResource9*> ResourceList;

    // each ResourceSet contain entries for all resources that are rendered at correspondent frame (after Add**() cycle)
    // ResourceSet[Resource] is true for all resources that was rendered at previous frame (after ManageResources(,) call)
    ResourceSet indicesSet;
    ResourceSet verticesSet;
    ResourceSet texturesSet;

#ifdef PRELOAD_MANAGED_POOL_RESOURCES
    ResourceList newResources;
#endif
    UINT timeStamp;

    // Set NORMAL priority for resources that become visible and push them to preload list
    template<class I>
    void AddResource(I *_resource, DXManager::ResourceSet& _set);
    // Set LOW priority for resources that become invisible and remove them from set
    void ManageResources(ResourceSet& _set);

  protected:
    DXManager();

  public:
    virtual void OnDeviceLost()  { Clear(); }
    virtual void OnDeviceReset() {}

    void OnNextFrame() { ++timeStamp; }
    void Clear();

    void Manage();

    void AddGeometry(const GeometryBuffers& _arg);
    void AddTextures(const BaseMaterial* _pMaterial);
  };

}
