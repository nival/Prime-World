#ifndef MAPCOLLECTION_H_INCLUDED
#define MAPCOLLECTION_H_INCLUDED

#include "GameMaps.h"
#include "ResourcesCollection.h"
#include "DbMapList.h"

namespace NDb
{
	struct AdvMapDescription;	
}

namespace NWorld
{

class PWMapCollection : public IMapCollection, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( PWMapCollection, IMapCollection, BaseObjectMT );

public:
  PWMapCollection();

  void ScanForMaps();

  //IMapCollection
  virtual int MapsListSize() const;
  virtual const char * MapId( int index ) const;
  virtual const char * MapDescId( int index ) const;
  virtual const wchar_t * MapTitle( int index ) const;
  virtual const wchar_t * MapDescription( int index ) const;

  virtual const char * CustomDescId( int index ) const;
  virtual const wchar_t * CustomTitle( int index ) const;
  virtual const wchar_t * CustomDescription( int index ) const;
  virtual void InitCustomList( const NDb::Ptr<NDb::MapList> list );

  virtual int FindMapById( const char * id ) const;
  virtual IMapLoader * CreateMapLoader( const char * id );

private:
  NWorld::ResourcesCollection<NDb::AdvMapDescription> maps;
  NDb::Ptr<NDb::MapList> listCustom;
};

} //namespace NWorld

#endif //MAPCOLLECTION_H_INCLUDED
