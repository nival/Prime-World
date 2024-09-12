#ifndef MM_HEROESTABLE_H_INCLUDED
#define MM_HEROESTABLE_H_INCLUDED

#include "IMMakingLogic.h"

namespace mmaking
{

class HeroesTable : public IHeroesTable, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( HeroesTable, IHeroesTable, BaseObjectMT );

public:
  struct HeroInfo;

  HeroesTable() {}

  THeroShortId Add( const SHeroDescription & descr );

  virtual THeroShortId MaxShortId() const { return _array.size(); }
  virtual const SHeroDescription * FindDescr( const string & id ) const;
  virtual SHeroDescription * FindDescr( const string & id );
  virtual const SHeroDescription * FindDescr( THeroShortId id ) const;
  
  void AttachAntogonistsList( THeroShortId id, const vector<string>& antogonists );


private:
  typedef map<string, StrongMT<HeroInfo> > TById;

  TById  _byId;
  vector<StrongMT<HeroInfo> >  _array;
};

} //namespace mmaking

#endif //MM_HEROESTABLE_H_INCLUDED
