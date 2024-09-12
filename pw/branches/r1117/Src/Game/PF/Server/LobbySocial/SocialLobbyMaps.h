#ifndef SOCIALLOBBYMAPS_H_INCLUDED
#define SOCIALLOBBYMAPS_H_INCLUDED

#include "SocialLobbyTypes.h"


namespace NDb
{
  struct AdvMapDescription;
}


namespace socialLobby
{

class IMaps : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IMaps, IBaseInterfaceST );

public:
  virtual size_t Size() const = 0;
  virtual const char * GetMapId( size_t idx ) const = 0;
  virtual const NDb::AdvMapDescription * GetMap( size_t idx ) const = 0;
  virtual const NDb::AdvMapDescription * FindMap( const char * mapId ) const = 0;
};

IMaps * LoadMaps();

} //namespace socialLobby

#endif //SOCIALLOBBYMAPS_H_INCLUDED
