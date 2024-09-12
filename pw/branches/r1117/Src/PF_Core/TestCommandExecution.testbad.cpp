#pragma once
#include "stdafx.h"

#include <CxxTest.h>

#include "ClientObject.h"
#include "WorldObject.h"
#include "World.hpp"
#include "../Core/Transceiver.h"
#include "../Core/RandomGenerator.h"
#include "../Core/WorldCommand.h"
#include "../Core/GameNode.h"
#include "../Core/GameCommand.h"

namespace PF_Tests
{

_interface IFakeUpdate : public IObjectBase
{
  virtual void Update() = 0;
};

class CDummyClientObject;

class CDummyWorldObject : public PF_Core::WorldObjectBase
{
  WORLD_OBJECT_METHODS(0xFFEE8B14, CDummyWorldObject, CDummyClientObject)

  bool bChanged;
  explicit CDummyWorldObject() : bChanged(false) {}
public:
  explicit CDummyWorldObject(PF_Core::IWorld* pWorld);
  void Change();
  bool IsChanged() const {return bChanged;}
};

class CDummyClientObject : public PF_Core::ClientObjectBase, public IFakeUpdate
{
  OBJECT_METHODS(0xFFEE8B15, CDummyClientObject)
  bool bChanged;
public:
	explicit CDummyClientObject() {}
	explicit CDummyClientObject(PF_Core::WorldObjectRef pWO) : PF_Core::ClientObjectBase(pWO), bChanged(false){}
  virtual void Update() {bChanged = true;}

  bool IsChanged() const {return bChanged;}
};

CDummyWorldObject::CDummyWorldObject(PF_Core::IWorld* pWorld) 
	: PF_Core::WorldObjectBase(pWorld) , bChanged(false)
{
	CreateClientObject<CDummyClientObject>();
}

void CDummyWorldObject::Change()
{
	bChanged = true; 
	ClientObject()->Update();
}


DEFINE_1_PARAM_CMD( 0xFFEE8B16, CTransceivedCommand, CPtr<CDummyWorldObject>, pObject)


void CTransceivedCommand::Execute(NCore::IWorldBase* pWorld)
{
  TS_ASSERT_EQUALS(true, IsValid(pWorld));
  TS_ASSERT_EQUALS(true, IsValid(pObject));

  pObject->Change();
}

class CValueHolder : public CObjectBase
{
  OBJECT_METHODS(0xFFEE8B13, CValueHolder)
    explicit CValueHolder() :  value(0) {}
public:
  explicit CValueHolder(int value) : value(value) {}

  int value;
};


DEFINE_1_PARAM_CMD( 0xFFEE8B12, CLocalCmd,  CPtr<CValueHolder>, pValue)
DEFINE_2_PARAM_CMD( 0xFFEE8B11, CGlobalCmd, CPtr<CValueHolder>, pValue, int, nSubcommands)

DEFINE_2_PARAM_CMD_CHECK( 0xFFEE8B1B, CSimpleCmd, int, nValue, bool, bCanExecute)

bool CSimpleCmd::CanExecute()const
{
  return bCanExecute;
}

void CSimpleCmd::Execute( NCore::IWorldBase* pWorld)
{
  TS_ASSERT_EQUALS(true, IsValid(pWorld));
  nValue *= NCore::RandomFromSeed(0, 2, 10);
}

void CGlobalCmd::Execute( NCore::IWorldBase* pWorld )
{
  TS_ASSERT_EQUALS(true, IsValid(pWorld));
  for (int i = 0; i < nSubcommands; ++i )
    pWorld->ExecuteCommand(new CLocalCmd(pValue));

  ++pValue->value;
}

void CLocalCmd::Execute( NCore::IWorldBase* pWorld )
{
  TS_ASSERT_EQUALS(true, IsValid(pWorld));
  ++pValue->value;
}

//
//class WorldCommandExecutionTest : public CxxTest::TestSuite
//{
//  CObj<PF_Core::World>   pWorld;
//  CObj<NCore::CGameNode> pGameNode;
//  NCore::Transceiver     transceiver;
//public:
//  
//  virtual bool setUpSuite()
//  {
//    pWorld    = new PF_Core::World;
//    pGameNode = new NCore::CGameNode();
//
//    transceiver.Init(pGameNode);
//		transceiver.Init(pWorld, NULL);
//    
//    return true;
//  }
//  virtual bool tearDownSuite()
//  {
//    return true;
//  }
//
//  void TestSimpleCommands()
//  {
//    const int nRandomValue = NCore::RandomFromSeed(0, 1, 100);
//
//    // executable command
//    CObj<CSimpleCmd> pCmd  = new CSimpleCmd(nRandomValue, true);
//    pWorld->ExecuteCommand(pCmd);
//    TS_ASSERT_DIFFERS(nRandomValue, pCmd->nValue);
//
//    // non-executable command
//    pCmd  = new CSimpleCmd(nRandomValue, false);
//    pWorld->ExecuteCommand(pCmd);
//    TS_ASSERT_EQUALS(nRandomValue, pCmd->nValue);
//  }
//
//  void TestLocalCommands()
//  {
//    const int nSubcommands    = NCore::RandomFromSeed(0, 10, 100);
//    const int nBaseValue      = NCore::RandomFromSeed(0, 10, 100);
//    
//    CPtr<CValueHolder> pValue = new CValueHolder(nBaseValue);
//    CObj<CGlobalCmd> pCmd     = new CGlobalCmd(pValue, nSubcommands);
//
//    pWorld->ExecuteCommand(pCmd);
//    
//    TS_ASSERT_EQUALS(pValue->value, 1/*CGlobalCmd execution*/ + nSubcommands + nBaseValue);
//  }
//
//  void TestTransceiver()
//  {
//    TS_ASSERT_EQUALS(true, IsValid(pGameNode));
//    
//    CDummyWorldObject* pObject         = new CDummyWorldObject(pWorld);
//    CPtr<CTransceivedCommand> pCommand = new CTransceivedCommand(pObject);
//
//    pGameNode->PushGameCommand( new NCore::CSerializedWorldCommand( -1, pCommand, pWorld->GetPointerSerialization() ) );
//    transceiver.Step(0);    
//
//    TS_ASSERT_EQUALS(true, pObject->IsChanged());
//    TS_ASSERT_EQUALS(true, pObject->ClientObject()->IsChanged());
//  }
//
//};

} // namespace PF_Tests

//using PF_Tests::WorldCommandExecutionTest;
//CXX_REGISTER_TEST_SUITE( WorldCommandExecutionTest )
//{
//  CXX_REGISTER_TEST_FUNCTION( TestSimpleCommands );
//  CXX_REGISTER_TEST_FUNCTION( TestLocalCommands );
//  CXX_REGISTER_TEST_FUNCTION( TestTransceiver );
//}

BASIC_REGISTER_CLASS(PF_Tests::IFakeUpdate);

REGISTER_SAVELOAD_CLASS_NM( CValueHolder,        PF_Tests )
REGISTER_SAVELOAD_CLASS_NM( CLocalCmd,           PF_Tests )
REGISTER_SAVELOAD_CLASS_NM( CGlobalCmd,          PF_Tests )
REGISTER_SAVELOAD_CLASS_NM( CSimpleCmd,          PF_Tests )
REGISTER_SAVELOAD_CLASS_NM( CDummyWorldObject,   PF_Tests )
WORLD_OBJECT_FUNCTIONS_NM( CDummyWorldObject,   PF_Tests )
REGISTER_SAVELOAD_CLASS_NM( CTransceivedCommand, PF_Tests ) 
