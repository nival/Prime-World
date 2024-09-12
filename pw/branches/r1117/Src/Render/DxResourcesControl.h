#pragma once


#ifndef _SHIPPING
// comment this to turn off DX resource control completely
//#define DX_RESOURCE_CONTROL
#endif

#ifdef _DEBUG
// comment this to turn off collecting DX resource stack
//#define DX_RESOURCE_STACK
#endif


enum DXPtrType
{
  DPT_VertexShader,
  DPT_PixelShader,
  DPT_Texture,
  DPT_VertexBuffer,
  DPT_IndexBuffer,
  DPT_Surface,
  DPT_VertexDeclaration,

  DPT_COUNT
};


string const &GetCurrentDXPool();
void PushDXPool(char const *pool);
void PopDXPool(char const *pool);

class PushDXPoolGuard
{
#ifdef DX_RESOURCE_CONTROL
  char const *pool;
public:
  explicit PushDXPoolGuard(char const *_pool) : pool(_pool) { PushDXPool(pool); }
  ~PushDXPoolGuard() { PopDXPool(pool); }
#else
public:
  explicit PushDXPoolGuard(char const *) {}
#endif
};

#ifdef DX_RESOURCE_CONTROL

void RegisterDXPtr(IUnknown *ptr, DXPtrType type);
void RegisterDXPtr(IDirect3DResource9 *ptr);

inline void RegisterDXPtr(IDirect3DVertexShader9 *ptr) { if(ptr) RegisterDXPtr(ptr, DPT_VertexShader); }
inline void RegisterDXPtr(IDirect3DPixelShader9  *ptr) { if(ptr) RegisterDXPtr(ptr, DPT_PixelShader); }
inline void RegisterDXPtr(IDirect3DBaseTexture9  *ptr) { if(ptr) RegisterDXPtr(ptr, DPT_Texture); }
inline void RegisterDXPtr(IDirect3DVertexBuffer9 *ptr) { if(ptr) RegisterDXPtr(ptr, DPT_VertexBuffer); }
inline void RegisterDXPtr(IDirect3DIndexBuffer9  *ptr) { if(ptr) RegisterDXPtr(ptr, DPT_IndexBuffer); }
inline void RegisterDXPtr(IDirect3DSurface9 *ptr)      { if(ptr) RegisterDXPtr(ptr, DPT_Surface); }
inline void RegisterDXPtr(IDirect3DVertexDeclaration9 *ptr) { if(ptr) RegisterDXPtr(ptr, DPT_VertexDeclaration); }
inline void RegisterDXPtr(IUnknown *ptr) {}

void UnregisterDXPtr(IUnknown *ptr);
void DumpDXResourcesLeaks();
void DumpDXResourcesInDefaultPool();

#else

#define RegisterDXPtr(ptr)    ((void)0)
#define UnregisterDXPtr(ptr)  ((void)0)
#define DumpDXResourcesLeaks()((void)0)
#define DumpDXResourcesInDefaultPool() ((void)0)

#endif
