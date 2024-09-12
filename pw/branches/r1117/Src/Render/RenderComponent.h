#pragma once

#include "../System/noncopyable.h"
#include "aabb.h"
#include "OcclusionQueries.h"

// 
#define REPLACE_DEFAULT_NEW_DELETE(className)		static uint className##InstanceCounter; \
																								public: \
																								static void* operator new(size_t size); \
																								static void operator delete(void* ptr); \
																								static uint GetInstanceCounter() { return className##InstanceCounter; } \
																								private: \
																								static void* operator new[](size_t size); \
																								static void operator delete[](void* ptr); \
																								static void* operator new(size_t size, void* ptr); \
                                                static void operator delete(void* ptr, void* pMem);

#define DECLARE_INSTANCE_COUNTER(className)	uint className##::##className##InstanceCounter = 0; \
																						void* className##::operator new(size_t size) { ++className##InstanceCounter; return Aligned_MAlloc(sizeof(className), 16); } \
																						void className::operator delete(void* ptr)	{ --className##InstanceCounter; Aligned_Free(ptr); } \
                                            void* className##::operator new(size_t size, void* ptr) { return ptr; } \
                                            void className##::operator delete(void* ptr, void* pMem) { ((className*)ptr)->~className(); }
																								
#define SET_INSTANCE_COUNTER(className) ;// NDebug::SetDebugVar( #className, string(NStr::StrFmt("%d x %db = %d bytes", className##::GetInstanceCounter(), sizeof(className), sizeof(className)*className##::GetInstanceCounter())), false );

namespace NDb
{
	class DBID;
}
																							
namespace Render
{

class RenderComponent;
class BatchQueue;
class BaseMaterial;

__declspec(align(16))
class RenderComponent : public NonCopyable
{
protected:
	const NDb::DBID *pResourceDBID;

public:
	RenderComponent() : pResourceDBID(0) {}
	virtual ~RenderComponent() {}

	virtual void RenderToQueue( Render::BatchQueue &/*queue*/ ) {}

	virtual void PrepareRendererAfterMaterial( unsigned int elementNumber ) const {} //set constants

  virtual void SetMaterial( int slotNumber, BaseMaterial* _pMaterial ) {}
  virtual BaseMaterial* GetMaterial( int slotNumber ) { return 0; }

	void SetDBID(const NDb::DBID &dbid) { pResourceDBID = &dbid; }
	const NDb::DBID* GetDBID() const { return pResourceDBID; }

  virtual bool FillOBB(CVec3 (&_vertices)[8]) const { return false; } // = 0;
  virtual OcclusionQueries* GetQueries()   const = 0; //{ return 0; }
  virtual const Matrix43& GetWorldMatrix() const { static const Matrix43 m( CVec3::Zero() ); return m; } // = 0;
  virtual const AABB&     GetLocalAABB()   const { static const AABB bb( CVec3::Zero(), CVec3::Zero() ); return bb; } // = 0;

  // Get AABB. _pIsLocal indicates, what kind of AABB is wanted, and what was returned.
  virtual const AABB& GetAABB(/*in-out*/ bool *_pIsLocal) const
  {
    *_pIsLocal = false;
    return AABB::Huge();
  }

  // fill oriented bounding-box in _pBox
  static void FillOBB(const AABB& _localAABB, const Matrix43& _mtxWorld, CVec3 * __restrict _pBox);
  // fill oriented bounding-box in homogeneous space. Useful for perspective transforms
  static void FillOBBH(const AABB& _localAABB, const SHMatrix& _transform, CVec4 * __restrict _pBox);
};

_interface IMaterialProcessor
{
  virtual void operator()(BaseMaterial &material) = 0;
};

}
