#pragma once

#include "../System/noncopyable.h"
#include "PFLogicObject.h"
#include "System/InlineProfiler.h"


namespace NWorld
{

class PFBaseUnit;

// Simple implementation of BBox class for 2D Voxel Map
typedef CTRect<float> BBox2D;

template<class E, class R>
class RingElementRemovalHandler
{
public:
  RingElementRemovalHandler() : pTopNext(0)
  {
    nextPointers.reserve( 8 );
  }

  void OnRemove( E* e )
  {
    if ( !nextPointers.empty() )
    {
      for ( TCurrentNextPointers::iterator it = nextPointers.begin(); it != nextPointers.end(); ++it )
      {
        if ( e == *it )
        {
          *it = R::next( e );
        }
      }
    }
  }

  void PushNext( E* e )
  {
    nextPointers.push_back( e );
    pTopNext = 0;
  }

  void PopNext( E const* e )
  {
    pTopNext = nextPointers.back();
    if ( e == pTopNext )
      pTopNext = 0;
    nextPointers.pop_back();
  }

  E* GetTopNext()
  {
    E* pTmp = pTopNext;
    pTopNext = 0;
    return pTmp;
  }

private:
  typedef vector<E*> TCurrentNextPointers;
  TCurrentNextPointers nextPointers;
  E* pTopNext;
};


class PFVoxelMap : public PFWorldObjectBase
{
private:
  WORLD_OBJECT_METHODS(0x286233C1, PFVoxelMap);

	struct Voxel 
  {
    ZDATA
    BBox2D   bbox;
    PFLogicObject::LORing   objectsRing;
    PFLogicObject::LORing   unitsRing;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&bbox); f.Add(3,&objectsRing); f.Add(4,&unitsRing); return 0; }
  
    Voxel &operator = (const Voxel &v) 
    { NI_ALWAYS_ASSERT(""); return *this; }
    Voxel(const Voxel &v) 
    {NI_ALWAYS_ASSERT(""); }
    Voxel() 
    {
      bbox.minx = bbox.miny = bbox.maxx = bbox.maxy = -1111.11f;
    }
  };

  struct Range : public NonCopyable
  {
    const CVec3  &center;
    const float  radiusSquared;

    Range(const CVec3 &_center, float radius) : center(_center), radiusSquared(radius * radius) 
    {
      NI_ASSERT( radius > 0.0f, "Do you really need radius == 0.0?" );
    }
  };

  struct SelectObjects
  {
    static const PFLogicObject::LORing& Select(const Voxel &vox) { return vox.objectsRing; }
    static PFLogicObject* Cast(PFLogicObject* obj);
    typedef PFLogicObject Obj;
  };

  struct SelectUnits
  {
    static const PFLogicObject::LORing& Select(const Voxel &vox) { return vox.unitsRing; }
    static PFBaseUnit* Cast(PFLogicObject* obj);
    typedef PFBaseUnit Obj;
  };

  struct DummyPredicate
  {
    bool operator() (const PFLogicObject & /*obj*/) const { return true; }
		bool TraverseObjects() const { return true; }
		bool TraverseUnits() const { return true; }
  };

  // TFunc(Voxel &v), TSel()
  template <typename TFunc, typename TSel, typename TPredicate>
  void ForAllEntities(TFunc &func, TPredicate const &p) const
  { 
    NI_PROFILE_FUNCTION
    
    // for all voxels
    for (int i = 0; i < width * height; i++)
    {
      const PFLogicObject::LORing &ring = TSel::Select(pVoxels[i]);
      
      // for all elements in ring
      for (ring::Range<PFLogicObject::LORing> r(ring); r; ++r)
      {
        TSel::Obj *pObj = TSel::Cast(&(*r));
        NI_VERIFY(pObj != NULL, "Failed logic in Voxel map! (1)", continue;);
        if (p(*pObj))
          func(*pObj);
      }
    }
  }

  // TFunc(Voxel &v), TSel()
  template <typename TFunc, typename TSel, typename TPredicate>
  void ForAllEntitiesInBBox(const BBox2D &bbox, const Range &range, TFunc &func, TPredicate const &p) const
  { 
    NI_PROFILE_FUNCTION
  
    NI_VERIFY( range.radiusSquared > 0.0f, "Zero distance!", return; );

    int startI, startJ, endI, endJ; // use no constructor to speedup!
    CalcVoxelIndices(bbox.minx, bbox.miny, startI, startJ);
    CalcVoxelIndices(bbox.maxx, bbox.maxy, endI, endJ);
    NI_ASSERT(startI <= endI && startJ <= endJ, "Bad indices for bboxes(1)");
    NI_ASSERT(0 <= startI && endI < width && 0 <= startJ && endJ < height, "Bad indices for bboxes(2)");

    // for all voxels in bbox
    for (int i = startI; i <= endI; i++)
    {
      for (int j = startJ; j <= endJ; j++)
      {
        PFLogicObject::LORing const &ring = TSel::Select(GetVoxel(i, j));

        TSel::Obj *const pObjLast = TSel::Cast(ring.last());
        for (TSel::Obj *pObj = TSel::Cast(ring.first()); pObj != pObjLast;)
        {
          //next prep
          NI_VERIFY(pObj != NULL, "Failed logic in Voxel map! (2)", break;);
          TSel::Obj *pNext = TSel::Cast(PFLogicObject::LORing::next(pObj));
          if ( pNext == 0 )
            pNext = static_cast<TSel::Obj*>(ringElemRemovalHandler.GetTopNext());
          if (IsPointInRange(pObj->GetPosition(), range) && p(*pObj))
          {
            ringElemRemovalHandler.PushNext( pNext );
            func(*pObj);
            ringElemRemovalHandler.PopNext( pNext );
          }
          //next do
          pObj = pNext;
        }
      }
    }
  }

        Voxel &GetVoxel(PFLogicObject &obj);
        Voxel &GetVoxel(int i, int j);
  const Voxel &GetVoxel(int i, int j) const;
        Voxel &GetVoxel(int linearI);
  const Voxel &GetVoxel(int linearI) const;

  BBox2D  ConvertRangeToBBox(CVec3 const& vPos, float fRange) const;
  static void    CalcVoxelIndices(float x, float y, int &voxelI, int &voxelJ);
  static bool    IsPointInRange(const CVec3 &pos, const Range &range);

public:
  void SetVoxelMapSizes(const TileMap *map);
  void AddObject(PFLogicObject &obj);
  void AddObject(PFBaseUnit &unit);
  void RemoveObject(PFLogicObject &obj);

  void OnUnitMove(PFBaseUnit &unit);

	virtual bool NeedToBeStepped() { return false; }

  /// Unit is PFBaseUnit
  template <typename TFunc, typename TPredicate>
  void ForAllUnits(TFunc &func, TPredicate const &p) const
  { 
    ForAllEntities<TFunc, SelectUnits, TPredicate>(func, p);
  }
  
  template <typename TFunc>
  void ForAllUnits(TFunc &func) const
  { 
    DummyPredicate p;
    ForAllUnits(func, p);
  }

  /// Unit is PFBaseUnit
  template <typename TFunc, typename TPredicate>
  void ForAllUnitsInRange(CVec3 const& vPos, float dist, TFunc &func, TPredicate const &p) const 
  { 
    Range range(vPos, dist);
    BBox2D bbox(ConvertRangeToBBox(vPos, dist));
    ForAllEntitiesInBBox<TFunc, SelectUnits, TPredicate>(bbox, range, func, p);
  }
  template <typename TFunc>
  void ForAllUnitsInRange(CVec3 const& vPos, float dist, TFunc &func) const 
  { 
    DummyPredicate p;
    ForAllUnitsInRange(vPos, dist, func, p);
  }
  template <typename TFunc>
  void ForAllUnitsInRangeConsiderSize( const CVec3& vPos, float dist, TFunc& func) const
  {
    const float maxUnitRadius = 0.5f * GetWorld()->GetAIWorld()->GetMaxObjectSize();

    struct IsUnitParticallyIncluded: public DummyPredicate
    {
       IsUnitParticallyIncluded( const CVec3& _vPos, float _dist ) : vPos( _vPos ), dist( _dist ) { }
       bool operator() ( const PFLogicObject& obj ) const { return ( fabs2( obj.GetPosition() - vPos ) < fabs2( dist + 0.5f * obj.GetObjectSize() ) ); }
       CVec3 vPos;
       float dist;
    }p( vPos, dist );

    ForAllUnitsInRange(vPos, dist + maxUnitRadius, func, p);
  }

  // Object is tree (now)
  template <typename TFunc, typename TPredicate>
  void ForAllObjects(TFunc &func, TPredicate const &p) const 
  { 
    ForAllEntities<TFunc, SelectObjects, TPredicate>(func, p);
  }

  template <typename TFunc>
  void ForAllObjects(TFunc &func) const 
  { 
    DummyPredicate p;
    ForAllObjects(func, p);
  }


  // Object is tree (now)
  template <typename TFunc, typename TPredicate>
  void ForAllObjectsInRange(CVec3 const& vPos, float dist, TFunc &func, TPredicate const &p) const 
  { 
		Range range(vPos, dist);
		BBox2D bbox(ConvertRangeToBBox(vPos, dist));
    ForAllEntitiesInBBox<TFunc, SelectObjects, TPredicate>(bbox, range, func, p);
  }
  template <typename TFunc>
  void ForAllObjectsInRange(CVec3 const& vPos, float dist, TFunc &func) const 
  { 
    DummyPredicate p;
    ForAllObjectsInRange(vPos, dist, func, p);
  }

  template <typename TFunc, typename TPredicate>
  void ForAll(TFunc &func, TPredicate const &p) const 
  { 
    if (p.TraverseObjects())
			ForAllEntities<TFunc, SelectObjects, TPredicate>(func, p);
		if (p.TraverseUnits())
	    ForAllEntities<TFunc, SelectUnits,   TPredicate>(func, p);
  }

  template <typename TFunc>
  void ForAll(TFunc &func) const 
  { 
    DummyPredicate p;
    ForAll(func, p);
  }

  template <typename TFunc, typename TPredicate>
  void ForAllInRange(CVec3 const& vPos, float dist, TFunc &func, TPredicate const &p) const 
  { 
    Range range(vPos, dist);
    BBox2D bbox(ConvertRangeToBBox(vPos, dist));
		if (p.TraverseObjects())
	    ForAllEntitiesInBBox<TFunc, SelectObjects, TPredicate>(bbox, range, func, p);
		if (p.TraverseUnits())
		  ForAllEntitiesInBBox<TFunc, SelectUnits,   TPredicate>(bbox, range, func, p);
  }
  template <typename TFunc>
  void ForAllInRange(CVec3 const& vPos, float dist, TFunc &func) const 
  { 
    DummyPredicate p;
    ForAllInRange(vPos, dist, func, p);
  }
    
	PFVoxelMap( PFWorld* world );

protected:
  virtual void OnDestroyContents();
	PFVoxelMap();

  template <class RingT> void insertSorted(RingT &r, PFLogicObject *o);

  ZDATA_(PFWorldObjectBase)
  ZNOCRC
  nstl::vector<Voxel>   pVoxels;  
  ZNOCRCEND
  int                   width;    // in voxels
  int                   height;   // in voxels
  float                 widthF;   // in meters
  float                 heightF;  // in meters
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this);  if(!f.IsChecksum()){ f.Add(2,&pVoxels);  } f.Add(3,&width); f.Add(4,&height); f.Add(5,&widthF); f.Add(6,&heightF); return 0; }

private:
  mutable RingElementRemovalHandler<PFLogicObject, PFLogicObject::LORing> ringElemRemovalHandler;
}; // class PFVoxelMap


} // namespace NWorld
