#pragma once
#ifndef _NATUREMAP_H_
#define _NATUREMAP_H_

#include "../Render/aabb.h"
#include "../System/PlaneGeometry.h"
#include "NatureAttackSpace.h"

namespace Terrain
{

typedef long NatureMapElementId;
static const NatureMapElementId NATUREMAPELEMENTID_BAD = -1;

struct NatureMapElementInfo
{
  enum { VERSION = 3 };

  CVec2 attackPos;
  unsigned ownerData;
  unsigned natureCur : 2; // NDb::ENatureType
  unsigned natureOld : 2; // NDb::ENatureType
  unsigned natureBase : 2; // NDb::ENatureType
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct NatureOverrideElementData
{
  ZDATA
  NDb::ENatureType nature;
  unsigned ownerData;
  float timeSpan;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&nature); f.Add(3,&ownerData); f.Add(4,&timeSpan); return 0; }
};

typedef vector<NatureOverrideElementData> TInactiveStak;

struct NatureOverrideElement
{
  ZDATA
  NatureMapElementId id;
  NatureOverrideElementData data;
  float timeToApply;
  TInactiveStak inactiveStack;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&id); f.Add(3,&data); f.Add(4,&timeToApply); f.Add(5,&inactiveStack); return 0; }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct NatureMapParams
{
  const NDb::DBNatureMap* pDBNatureMap;
  CVec3 worldSize;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct NatureOverride
{
  ZDATA
  NDb::ENatureType faction;
  CCircle circle;
  float lifeTime;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&faction); f.Add(3,&circle); f.Add(4,&lifeTime); return 0; }

  bool IsInside(CVec2 const & pt) const
  {
    return circle.IsInside(pt);
  }

  void GetBounds(CTRect<float> & pBounds) const
  {
    pBounds.Set(circle.center.x - circle.r,
                circle.center.y - circle.r,
                circle.center.x + circle.r,
                circle.center.y + circle.r);
  }
};

typedef map<unsigned int, NatureOverride> TOverrides;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NatureMap
{
public :
  typedef nstl::vector<NatureMapElementId> NatureMapElementIdList;

public:
  explicit NatureMap(bool editable_);
  ~NatureMap();

  bool Initialize(NatureMapParams const& params_, NatureMapElementIdList *modifiedElemsListener );
  bool Save(nstl::string const& name) const;

  bool OnStep(float dt);
  virtual bool Reinit( NDb::ENatureType faction, const NDb::DBNatureMap* pDbNatureMap, bool forceCreate );
  void Reset();

  void EditNature(NatureMapElementId id, NDb::ENatureType faction); 


  void SetDesiredPosition(NDb::ENatureType faction, NDb::ENatureRoad roadIndex, int segment);
  void Attack(NDb::ENatureType faction, NDb::ENatureRoad roadIndex, int numSegments);
  void Override(NDb::ENatureType faction, const CCircle & circle, float lifeTime, unsigned ownerData);
  void UnOverride(NatureOverride overrideData, unsigned int id);

  int GetNature(float x, float y) const;
  int GetNature(NatureMapElementId id) const;
  CVec2 GetNatureBound(NDb::ENatureType faction, NDb::ENatureRoad roadIndex) const;
  float GetNaturePercent(NDb::ENatureType faction, NDb::ENatureRoad roadIndex) const;
  float GetNaturePercent(NDb::ENatureType faction) const;
  int GetNumSegments() const;
  void GetNatureSegment(CVec2 const &pos, NDb::ENatureRoad &road, int &segment) const;

  NDb::DBNatureMap const &GetDB() const { return dbNatureMap; }
  float GetElementSize() const { return dbNatureMap.gridStep; }
  unsigned GetSizeX() const { return xCount; }
  unsigned GetSizeY() const { return yCount; }

  NatureMapElementId LocateElement(float x, float y) const;
  NatureMapElementId LocateElement(const Matrix43& worldMatrix) const;
  NatureMapElementId LocateElement(unsigned row, unsigned column) const;
  
  NatureMapElementInfo& GetElementInfo(NatureMapElementId id);
  NatureMapElementInfo const& GetElementInfo(NatureMapElementId id) const;
  unsigned GetElementRow(NatureMapElementId id) const { return id / xCount; }
  unsigned GetElementColumn(NatureMapElementId id) const { return id % xCount; }
  void GetElementPosition(NatureMapElementId id, CVec2& pos) const;
  void GetElementBounds(NatureMapElementId id, Render::AABB& aabb) const;

  bool IsAtBase(float x, float y) const;

  template <class CLASS, class METHOD> inline void ForAllElements(CLASS* self, METHOD func); // METHOD ~ "void (CLASS::*)(NatureMapElementId, NatureMapElementInfo [const]&)"
  template <class FUNCTOR> void ForAllElements(FUNCTOR& func);
  //template <class FUNCTOR> void ForAllElementAABB(FUNCTOR& func, Render::AABB const& bounds);
  template <class CLASS, class METHOD> inline void ForAllModifiedElements(CLASS* self, METHOD func); // METHOD ~ "void (CLASS::*)(NatureMapElementId, NatureMapElementInfo [const]&)"

  template <class FUNCTOR> inline void ForAllElementsInCircle(FUNCTOR& func, const CVec2& center, float radius ); // METHOD ~ "void (CLASS::*)(CVec2, NatureMapElementId, NatureMapElementInfo [const]&)"
  template <class FUNCTOR> inline void ForAllElementsInPolygon(FUNCTOR& func, const vector<CVec2>& polygon );

  void UpdateNature(NatureMapElementId id, NatureMapElementInfo& info);
  void SetDebugPosition(CVec2 const& pos) { debugPos = pos; }
  virtual void RenderDebug();
  void ShowAttackSpace();

  bool IsOverrideActive(unsigned int ownerData) const;

  
  int operator&( IBinSaver &f );

protected:
  virtual bool OnCreate();
  
  virtual bool OnLoad( Stream* pStream, int fraction, bool fromRecconect );
  virtual bool OnSave( Stream* pStream, bool fromRecconect ) const;
  virtual bool OnLoadAtRuntime( Stream* pStream, int fraction, bool fromRecconect ) = 0;
  virtual bool OnSaveAtRuntime( Stream* pStream, bool fromRecconect ) const = 0;

  virtual void OnNatureChanged( int const* pQuadRanges, int numQuadRanges );

  struct ReconnectElemInfo
  {
    unsigned char ownerData : 1;
    unsigned char natureCur : 2; // NDb::ENatureType
    unsigned char natureOld : 2; // NDb::ENatureType
    unsigned char natureBase : 2; // NDb::ENatureType
  };

  void SaveAtRuntime( Stream* pStream, bool fromRecconect ) const;
  void LoadAtRuntime( Stream* pStream, bool fromRecconect );

  void InitElement(NatureMapElementId id, NatureMapElementInfo& info);
  void InitSortedList();
  void MarkAsModified(NatureMapElementId id, NatureMapElementInfo& info);

private :
  NDb::ENatureType GetNaturePrecise(CVec2 const& _attackPos);
  void ApplyOverride(NatureOverrideElement const &ovr);
  void ExpireOverride(NatureOverrideElement const &ovr);
  void OverrideInternal(NatureMapElementId id, NDb::ENatureType faction, float timeToApply, float lifeTime, unsigned ownerData);
  void UnOverrideInternal(NatureMapElementId id, unsigned ownerData);
  bool OverrideStep(float dt);
  void ResetImpl();

protected:
  typedef nstl::vector<NatureMapElementInfo> NatureMapElementList;

  // non copyable
  NatureMap(NatureMap const&);
  void operator=(NatureMap const&);

  unsigned long checksum;
  NDb::DBNatureMap dbNatureMap;
  CVec3 worldSize;

private:
  const bool editable;
  unsigned xCount;
  unsigned yCount;
  NatureMapElementList elemList;
  NatureAttackSpace attackSpace;
  nstl::vector<NatureMapElementId> elemListSorted;
  nstl::vector<int> quadToOffset; // offset in elemListSorted for quads
  nstl::vector<NatureOverrideElement> overrideElements;
  int overridesAdded;
  TOverrides overrides;

  nstl::vector<NatureMapElementId> editedElements;

  struct RoadProgress
  {
    struct Border
    {
      int last;
      int position;
      int target;
    } borders[2];
  } roads[NDb::KnownEnum<NDb::ENatureRoad>::sizeOf];
  float roadsStep;

  CVec2 debugPos;
  NatureMapElementIdList *modifiedElems;

  ScopedPtr<NatureMapElementInfo> overrideElementInfo; // editor only

  typedef nstl::vector<int> TValidRoads;
  TValidRoads validRoads;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline NatureMapElementId NatureMap::LocateElement(unsigned row, unsigned column) const
{
  NI_ASSERT(column < xCount && row < yCount, "NatureMap element is out of bounds");
  return row * xCount + column;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline NatureMapElementId NatureMap::LocateElement(const Matrix43& worldMatrix) const
{
  return LocateElement(worldMatrix._14, worldMatrix._24);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class CLASS, class METHOD> inline void NatureMap::ForAllElements(CLASS* self, METHOD func)
{
  NatureMapElementId id = 0;
  for (NatureMapElementList::iterator it = elemList.begin(); it != elemList.end(); ++it, ++id)
    (self->*func)(id, overrideElementInfo ? *overrideElementInfo : *it);
}

template <class FUNCTOR> inline void NatureMap::ForAllElements(FUNCTOR& func)
{
  NatureMapElementId id = 0;
  for (NatureMapElementList::iterator it = elemList.begin(); it != elemList.end(); ++it, ++id)
    func(id, overrideElementInfo ? *overrideElementInfo : *it);
}

template <class CLASS, class METHOD> void NatureMap::ForAllModifiedElements(CLASS* self, METHOD func)
{
  NatureMapElementIdList const& modifiedElemsRef = *modifiedElems;
  for (int i = 0, endI = modifiedElemsRef.size(); i != endI; ++i)
    (self->*func)(modifiedElemsRef[i], GetElementInfo(modifiedElemsRef[i]));
}


template <class FUNCTOR> void NatureMap::ForAllElementsInCircle( FUNCTOR& func, const CVec2& center, float radius )
{
  CVec2 lb( center.x - radius, center.y - radius ), rt( center.x + radius, center.y + radius );

  NatureMapElementId lbHex = LocateElement( ClampFast(lb.x, 0.f, worldSize.x), ClampFast(lb.y, 0.f, worldSize.y)),
    rtHex = LocateElement(ClampFast(rt.x, 0.f, worldSize.x), ClampFast(rt.y, 0.f, worldSize.y));

 unsigned int startRow = GetElementRow(lbHex), endRow = GetElementRow(rtHex);
 unsigned int startCol =  Max( (int)GetElementColumn(lbHex) - 1, 0 ), endCol = Min( (int)GetElementColumn(rtHex) + 1, (int)xCount - 1 );

 CVec2 elemPos;
 float radius2 = radius * radius;
 for( unsigned int i = startRow, endI = endRow + 1; i != endI; ++i )
 {
   for ( unsigned int j = startCol, endJ = endCol + 1; j != endJ; ++j)
   {
     NatureMapElementId id = LocateElement(i, j);
     GetElementPosition( id, elemPos );

     if ( fabs2( center.x - elemPos.x, center.y - elemPos.y) <= radius2 )
       func( elemPos, id, GetElementInfo( id ) );
   }
 }
}

template <class FUNCTOR> void NatureMap::ForAllElementsInPolygon(FUNCTOR& func, const vector<CVec2>& polygon )
{
  CTRect<float> bb = GetPolygonBoundingBox( polygon );

  NatureMapElementId lbHex = LocateElement( ClampFast(bb.left, 0.f, worldSize.x), ClampFast(bb.top, 0.f, worldSize.y)),
    rtHex = LocateElement(ClampFast(bb.right, 0.f, worldSize.x), ClampFast(bb.bottom, 0.f, worldSize.y));

  unsigned int startRow = GetElementRow(lbHex), endRow = GetElementRow(rtHex);
  unsigned int startCol =  Max( (int)GetElementColumn(lbHex) - 1, 0 ), endCol = Min( (int)GetElementColumn(rtHex) + 1, (int)xCount - 1 );

  CVec2 elemPos;
  for( unsigned int i = startRow, endI = endRow + 1; i != endI; ++i )
  {
    for ( unsigned int j = startCol, endJ = endCol + 1; j != endJ; ++j)
    {
      NatureMapElementId id = LocateElement(i, j);
      GetElementPosition( id, elemPos );

      if ( ClassifyPolygon( polygon, elemPos ) != CP_OUTSIDE )
        func( elemPos, id, GetElementInfo( id ) );
    }
  }
}


/*
template <class FUNCTOR> void NatureMap::ForAllElementAABB(FUNCTOR& func, Render::AABB const& bounds)
{ 
  CVec3 lb = bounds.center - bounds.halfSize, rt = bounds.center + bounds.halfSize;
  NatureMapElementId lbHex = LocateElement(min(lb.x, worldSize.x), min(lb.y, worldSize.y)),
                     rtHex = LocateElement(min(rt.x, worldSize.x), min(rt.y, worldSize.y));
  unsigned int start[ 2 ], end[ 2 ];

  unsigned int lbRow = GetElementRow(lbHex), rtRow = GetElementRow(rtHex);
  unsigned int startRow = lbRow, endRow = rtRow;
  CVec2 lbHexPos, rtHexPos;
  float hexSize3 = gridSize / 3;
  GetElementPosition(lbHex, lbHexPos);
  GetElementPosition(rtHex, rtHexPos);

  start[ 0 ] = GetElementColumn(lbHex); start[ 1 ] = start[ 0 ];
 
  if (lbRow & 1)
  {
    if (lbHexPos.x - lb.x < 0 && start[ 1 ] != GetSizeX())
      ++start[ 0 ];
  }
  else
  {
    if (lb.x - lbHexPos.x < 0 && start[ 0 ])    
      --start[ 1 ];
  }

  end[ 0 ] = GetElementColumn(rtHex); end[ 1 ] = end[ 0 ];
  if (rtRow & 1)
  {
    if (rtHexPos.x - rt.x < 0 && end[ 1 ] != GetSizeX())
      ++end[ 0 ];
  }
  else
  {
    if ( rt.x - rtHexPos.x < 0 && end[ 0 ] )    
      --end[ 1 ];
  }

  if ( lb.y > lbHexPos.y + hexSize3 || lb.y < lbHexPos.y - hexSize3 )
  {
    CVec2 rb( lb.x + 2 * bounds.halfSize.x, lb.y );
    NatureMapElementId rbHex = LocateElement(min(rb.x, worldSize.x), min(rb.y, worldSize.y));
    unsigned int rbRow = GetElementRow( rbHex );
    unsigned int botRow = 0, startCol = 0, endCol = 0;

    if ( lb.y > lbHexPos.y + hexSize3 )
    {
      if ( lbRow != rbRow )
      {
        ASSERT( lbRow == rbRow - 1 );
        ++startRow;
        botRow = lbRow;
        startCol = GetElementColumn(lbHex);
        endCol   = end[ rbRow & 1 ] + (rbRow & 1);
      }
    }
    else
    { 
      if ( lbRow == rbRow )
      {
        botRow = lbRow - 1;
        startCol = start[ lbRow & 1 ] + (lbRow & 1);
        endCol   = end[ lbRow & 1 ] + (lbRow & 1);
      }
      else
      {
        ASSERT( lbRow == rbRow + 1 );
        botRow = rbRow;
        startCol = start[ lbRow & 1 ] + (lbRow & 1);
        endCol   = GetElementColumn(rbHex) + 1;
      }
    }

    if ( botRow > 0 )
    {
      for ( int j = startCol, endJ = endCol; j != endJ; ++j )
        func( LocateElement(botRow, j), GetElementInfo( LocateElement(botRow, j) ) );
    }
  }

  if ( rt.y < rtHexPos.y - hexSize3 || rt.y > rtHexPos.y + hexSize3 )
  {
    CVec2 lt( rt.x - 2 * bounds.halfSize.x, rt.y );
    NatureMapElementId ltHex = LocateElement(min(lt.x, worldSize.x), min(lt.y, worldSize.y));
    unsigned int ltRow = GetElementRow( ltHex );
    unsigned int topRow = 0, startCol = 0, endCol = 0;

    if ( rt.y < rtHexPos.y - hexSize3 )
    {
      if( ltRow != rtRow )
      {
        ASSERT( rtRow == ltRow + 1 );
        --endRow;
        topRow = rtRow;
        startCol = start[ ltRow & 1 ] + (ltRow & 1);
        endCol   = GetElementColumn(rtHex) + 1;
      }
    }
    else
    {
      if ( ltRow == rtRow )
      {
        topRow = rtRow + 1;
        startCol = start[ rtRow & 1 ] + (rtRow & 1);
        endCol   = end[ rtRow & 1 ] + (rtRow & 1);
      }
      else
      {
        ASSERT( ltRow == rtRow + 1 );
        topRow = ltRow;
        startCol = GetElementColumn(ltHex);
        endCol   = end[ rtRow & 1 ] + (rtRow & 1);
      }
    }
 
    if ( topRow < GetSizeY( ) )
    {
      for ( int j = startCol, endJ = endCol; j != endJ; ++j )
        func( LocateElement(topRow, j), GetElementInfo( LocateElement(topRow, j) ) );
    }
  }

  for( unsigned int i = startRow, endI = endRow + 1; i != endI; ++i )
  {
    unsigned int rowType = i & 1;
    for ( unsigned int j = start[ rowType ], endJ = end[ rowType ] + 1; j != endJ; ++j)
      func( LocateElement(i, j), GetElementInfo( LocateElement(i, j) ) );
  }
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace Terrain

#endif /* _NATUREMAP_H_ */
