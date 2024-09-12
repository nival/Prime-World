#ifndef WALKINGRABBIT_TEST_H_EA231448_F0
#define WALKINGRABBIT_TEST_H_EA231448_F0
#include <RPC/RPC.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace MulticallPerformanceTest
{
  struct TestInitialSnapshot : rpc::Data
  {
    SERIALIZE_ID();

    struct DiffDesc
    {
      int id;
      bool isDead;
    };

    typedef list<DiffDesc> Diffs;

    struct SnapshotDesc
    {
      ZDATA
        int id;
      CVec3 target;
      ZEND int operator&( IBinSaver &f ) { f.Add(2,&id); f.Add(3,&target); return 0; }

      SnapshotDesc() : id(0), target(VNULL3) {}
    };

    typedef list<SnapshotDesc> Objects;

    ZDATA
      Objects dynamicObjects;
    Diffs difference;
    float serverTime;
    ZEND int operator&( IBinSaver &f ) { f.Add(2, &dynamicObjects); f.Add(3, &difference); f.Add(4, &serverTime); return 0; }
  };

  REMOTE struct RemoteApi : BaseObjectMT
  {
    RPC_ID();
    NI_DECLARE_REFCOUNT_CLASS_1(RemoteApi, BaseObjectMT);
  public:

    RemoteApi():isProcessed(false)
    {
    }

    REMOTE void callRemote()
    {
      isProcessed = true;
    }
    bool isProcessed;
  }; 


  REMOTE struct WalkingRabbit : BaseObjectMT
  {
    RPC_ID();
    NI_DECLARE_REFCOUNT_CLASS_1(WalkingRabbit, BaseObjectMT);
  public:
    int timesProcessed;
    TestInitialSnapshot s;
    float x, y, time;
    static int totalProcessed;
    RemoteApi api;

    WalkingRabbit()
    {
      timesProcessed = 0;
      x=y=time=0.f;
      ++totalProcessed;
    }

    ~WalkingRabbit()
    {
      ++totalProcessed;
    }

    REMOTE void WalkTo( float _x, float _y, float _time )
    {
      x = _x;
      y = _y;
      time = _time;
      ++timesProcessed;
      ++totalProcessed;
    }
    REMOTE void SetSomeData( const TestInitialSnapshot& _s )
    {
      s = _s;
      ++timesProcessed;
      ++totalProcessed;
    }

    RemoteApi* GetRemoteApi()
    {
      return &api;
    }
  };

}



#endif //#define WALKINGRABBIT_TEST_H_EA231448_F0   