//!Component('RPC/all')
//!Component('SerializeCase.test')
//!Component('System/NSTL')

#include <RPC/RPC.h>
#include <Server/RPC/RPCMixin.h>
#include <Server/RPC/LocalEntityFactory.h>

#include "SerializeCase.test.h"
#include "RSerializeCase.test.auto.h"
#include "LSerializeCase.test.auto.h"

namespace SerializeTest
{
  SERIALIZE_FACTORY(Header);
  SERIALIZE_FACTORY(PersonalInfo);
  SERIALIZE_FACTORY(BaseData);
}

struct Test_SerializeData : public CxxTest::TestSuite, RPCMixin   
{
  void test_Simple()
  {
    TwoNodesCase c;

    rpc::LocalEntityFactory factory0(&c.GetGate(0));
    factory0.Register<SerializeTest::Analyzer, SerializeTest::LAnalyzer>();

    StrongMT<SerializeTest::RAnalyzer> client_object = c.cnode1->Create<SerializeTest::RAnalyzer>();

    SerializeTest::BaseData data;
    data.basename = "test";
    data.header.numLines = 3;
    for ( int i = 0; i < 3; i++ )
    {
      data.header.numSubLines.push_back( i );
    }
    data.pos.x = 1.0f;
    data.pos.y = 2.0f;
    data.pos.z = 3.0f;

    for ( int i = 0; i < 2; i++ )
    {
      SerializeTest::PersonalInfo info;
      info.name = "one_";
      for ( int k = 0; k < 2; k++ )
      {
        info.ages.push_back( k );
      }
      data.infos.push_back( info );
    }

    StrongMT<rpc::RefValue<SerializeTest::BaseData>> t = new rpc::RefValue<SerializeTest::BaseData>;
    client_object->Do( data, t.Get(), &rpc::RefValue<SerializeTest::BaseData>::OnCall );
    TS_WAIT_FOR(t->IsSet(), 10000);

    TS_ASSERT( t->result.basename == "DoDone!" );
    TS_ASSERT( t->result.header.numLines == 13 );
    TS_ASSERT( t->result.header.numSubLines.size() == 3 );
    TS_ASSERT( t->result.header.numSubLines[0] == 10 );
    TS_ASSERT( t->result.header.numSubLines[1] == 11 );
    TS_ASSERT( t->result.header.numSubLines[2] == 12 );
    TS_ASSERT( t->result.pos.x == 11.0f );
    TS_ASSERT( t->result.pos.y == 12.0f );
    TS_ASSERT( t->result.pos.z == 13.0f );
    TS_ASSERT( t->result.infos.size() == 2 );
    TS_ASSERT( t->result.infos[0].name == "one_updated" );
    TS_ASSERT( t->result.infos[0].ages.size() == 2 );
    TS_ASSERT( t->result.infos[0].ages[0] == 10 );
    TS_ASSERT( t->result.infos[0].ages[1] == 11 );
    TS_ASSERT( t->result.infos[1].name == "one_updated" );
    TS_ASSERT( t->result.infos[1].ages.size() == 2 );
    TS_ASSERT( t->result.infos[1].ages[0] == 10 );
    TS_ASSERT( t->result.infos[1].ages[1] == 11 );
  }
};



