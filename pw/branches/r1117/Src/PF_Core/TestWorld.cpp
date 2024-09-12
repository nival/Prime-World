#include "stdafx.h"

#include <CxxTest.h>

#include "ClientObject.h"
#include "WorldObject.h"
#include "World.hpp"
#include "../System/RandomGenerator.h"

namespace PF_Tests
{
  
	class TestClientObject;

  class TestWorldObject : public PF_Core::WorldObjectBase
  {
    WORLD_OBJECT_METHODS_WITH_CLIENT(0xFFFE8B09, TestWorldObject, TestClientObject);

    explicit TestWorldObject() : PF_Core::WorldObjectBase() {}
		explicit TestWorldObject(int dummy);

	public:
    explicit TestWorldObject(PF_Core::World* pWorld) : PF_Core::WorldObjectBase(pWorld, 1) {}

    virtual ~TestWorldObject() {}
  };

	class TestClientObject : public PF_Core::ClientObjectBase
	{
		CLIENT_OBJECT_METHODS(0xFFFD8B09, TestClientObject, TestWorldObject);
	public:
		explicit TestClientObject() {}
		explicit TestClientObject(PF_Core::WorldObjectRef pWO) : PF_Core::ClientObjectBase(pWO)
		{
		}

		virtual ~TestClientObject()
		{
			;
		}

		virtual void OnFirstUpdate() const {}
		virtual void OnSecondUpdate() const {}
	};

	TestWorldObject::TestWorldObject(int dummy) : PF_Core::WorldObjectBase() 
	{
		CreateClientObject<TestClientObject>();
	}
    
  CXX_TEST( WorldClientCreationTest )
  {
    CObj<PF_Core::World>  pTestWorld(new PF_Core::World());
    
    int firstObjectId = PF_Core::INVALID_OBJECT_ID, lastObjectId = PF_Core::INVALID_OBJECT_ID;
    {
      for(unsigned i = 0, count = NRandom::RandomFromSeed(0, 10, 50); i < count; ++i)
      {
        TestWorldObject* pWO = new TestWorldObject(pTestWorld);
        const int objectId   = pWO->GetObjectId();

        TestClientObject* pCO = pWO->ClientObject();
        TS_ASSERT_DIFFERS((TestClientObject*)NULL, pCO);
        TS_ASSERT_DIFFERS((TestClientObject*)NULL, dynamic_cast<TestClientObject*>(pCO));
        TS_ASSERT_EQUALS(pWO, pCO->WorldObject());
        TS_ASSERT_EQUALS(pWO, pTestWorld->GetObjectById(objectId));

        firstObjectId = PF_Core::INVALID_OBJECT_ID == firstObjectId ? objectId : firstObjectId;
        lastObjectId  = objectId;
      }
      
      TS_ASSERT_DIFFERS((TestWorldObject*)NULL, pTestWorld->GetObjectById(firstObjectId));
      TS_ASSERT_DIFFERS((TestWorldObject*)NULL, pTestWorld->GetObjectById(lastObjectId));
      TS_ASSERT_DIFFERS((TestWorldObject*)NULL, pTestWorld->GetObjectById(NRandom::RandomFromSeed(0, firstObjectId, lastObjectId)));
    }

    TS_ASSERT_EQUALS((TestWorldObject*)NULL, pTestWorld->GetObjectById(firstObjectId));
    TS_ASSERT_EQUALS((TestWorldObject*)NULL, pTestWorld->GetObjectById(lastObjectId));
    TS_ASSERT_EQUALS((TestWorldObject*)NULL, pTestWorld->GetObjectById(NRandom::RandomFromSeed(0, firstObjectId, lastObjectId)));
  }

}; // namespace PF_Tests

WORLD_OBJECT_FUNCTIONS_NM(TestWorldObject, PF_Tests);
WORLD_OBJECT_DUMMY_METHOD_DEFINE_NM(TestWorldObject, PF_Tests);