#ifndef ILOGINSVCWRAPPER_H_INCLUDED
#define ILOGINSVCWRAPPER_H_INCLUDED

namespace Login
{
  class IAddSessionKeyCallback;
}

namespace lobby
{

class ISessionLoginWrapper : public IBaseInterfaceMT
{
public:
  NI_DECLARE_CLASS_1( ISessionLoginWrapper, IBaseInterfaceMT );

  virtual void Poll() = 0;
  virtual void AddSessionKey( const string & sessionLogin, const Transport::TServiceId & sessionPath, const string & zzLogin, int zzUserId, Cluster::TGameId gameid, Login::IAddSessionKeyCallback * callback ) = 0;
};

} //namespace lobby

#endif //ILOGINSVCWRAPPER_H_INCLUDED
