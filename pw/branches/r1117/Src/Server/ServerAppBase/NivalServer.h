#ifndef NIVALSERVER_H_INCLUDED
#define NIVALSERVER_H_INCLUDED

#include "NivalServerBase.h"

namespace Transport
{

class NivalServer : public NivalServerBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( NivalServer, NivalServerBase );

public:
  NivalServer();
  ~NivalServer();

  bool Startup( int argc, char* argv[] );

private:
  bool ParseServiceSpawnDirective( TStartList & serversToStart, const string & cmdLnOpt );
};

} // namespace Transport

#endif //NIVALSERVER_H_INCLUDED
