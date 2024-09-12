#ifndef SOCIALLOBBYCTRL_H_INCLUDED
#define SOCIALLOBBYCTRL_H_INCLUDED

#include "SocialLobbyTypes.h"


namespace socialLobby
{

class UserContext;
class Game;
class Party;
class IPvxAcknowledge;
class IPvxSvc;
class IMaps;
class RemoteMmLogic;



//FXIME: move this interface somewhere else
class IPvxSvcWrapper : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IPvxSvcWrapper, IBaseInterfaceST );

public:
  virtual IPvxSvc *                       Remote() const = 0;
  virtual const Transport::TServiceId &   SvcId() const = 0;
};



class IControl : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IControl, IBaseInterfaceMT );

public:
  virtual RemoteMmLogic *             GetMmLogic( const string & mapId ) const = 0;
  virtual Strong<IPvxSvcWrapper>      AllocatePvxSvc( const string & _clusterId, unsigned _loadIncrement ) = 0;
  virtual string                      DetermineClusterForGame( const mmaking::SGame & _game ) const = 0;
  virtual StrongMT<IPvxAcknowledge>   GetPvxAcknowledge() = 0;
  virtual void                        RemoveUserContext( UserContext * _ctx, bool _logStatistics ) = 0;
  virtual int                         MapClientRevision( int srcRev ) = 0;
};

} //namespace socialLobby

#endif //SOCIALLOBBYCTRL_H_INCLUDED
