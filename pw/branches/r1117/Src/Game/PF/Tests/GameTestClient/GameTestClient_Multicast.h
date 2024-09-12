#pragma once

#include "Game/PF/Tests/GTCBase/GTCBase.h"

namespace GameTestClient2
{
  namespace MTCStage
  {
    enum
    {
      INVALID = -1,
      INITIAL = BaseStage::LOGIN_FINISHED_POST_STEP,
      NUMBER_OF_STAGES
    };
  };


  class MulticastTestClient : public ClientBase, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( MulticastTestClient, ClientBase, BaseObjectMT );

  public:
    MulticastTestClient(unsigned int sessionDurationInSteps,
      int localid, 
      StrongMT<Network::INetworkDriver> const & driver, 
      StrongMT<TransportLayer::TransportModule> const & sptm = 0, 
      unsigned int stepInMs = 100,
      nstl::string const & loginaddr = "",
      nstl::string const & user = "", 
      nstl::string const & pswd = "",
      nstl::string const & sessionKey = "");
    ~MulticastTestClient();

  public:

    int Step();

  private:
    void sessionId(int sid);
    int sessionId() const;

  private:

    unsigned int sessionDurationInSteps_;
  };

}
