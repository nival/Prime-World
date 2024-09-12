//!Component('Scene/AnimationGraph')
//!Component('Scene/AGTestHelpers')
//!Component('System/FileSystem/TestFileSystem')
#include "stdafx.h"
#include <cxxtest/TestSuite.h>

#include "System/FileSystem/TestFileSystem.h"
#include <Render/texture.h>
#include <Scene/DiAnGr.h>
#include "AGTrace.h"
#include "AGHelpers.h"
#include "TestHelpers.h"
#include <iostream>

namespace test
{

static int g_OnEnterCallback = 0;
static int g_OnLeaveCallback = 0;
static int g_OnCallback = 0;

DiInt32 OnEnterCallback(const DiAnGrCallbackParams& params)
{
  g_OnEnterCallback++;
  return DIOBJMSG_CONTINUE;
}
DiInt32 OnLeaveCallback(const DiAnGrCallbackParams& params)
{
  g_OnLeaveCallback++;
  return DIOBJMSG_CONTINUE;
}
DiInt32 OnCallback(const DiAnGrCallbackParams& params)
{
  g_OnCallback++;
  return DIOBJMSG_CONTINUE;
}

} // test

using namespace test;

struct Test_AG : public CxxTest::TestSuite
{
  DiAnimGraph* g;
  MockAnimGraphBlender* blender;
  DiAnGrExtPars* extPars;

  void setUp()
  {
    g = 0;
    blender = 0;
    extPars = 0;
  }

  void Create(AnimationDataHolder& data, const NDb::AnimGraphCreator* creator = 0, bool isCreateExtParams = false)
  {
    blender = new MockAnimGraphBlender(data);
    g = DiAnimGraph::CreateByData(creator, data.animations, blender);
    if ( isCreateExtParams)
    {
      extPars = new DiAnGrExtPars(creator, g);
      extPars->applyParamsToGraph();
    }
    g->StoreDefaultValues();
		g->Restart( g->GetDefNode(), true );
  }

  void tearDown()
  {
    if (g)
    {
      DiAnimGraph::Destroy(g);
    }
    if (extPars)
    {
      delete  extPars;
    }
    if (blender)
    {
      delete blender;
    }
  }

  void test_LoopedPlayingNode()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("0", 5.f);

    Create(data);

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }

    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.5f, info.progresses[0]); 
    }

    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(1.f, info.progresses[0]);
    }

    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.5f, info.progresses[0]); 
    }
  }

  void test_TwoNodes()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 5.f);
    data.AddAnimation("death", 5.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 5.f );
    test::CreateTransaction( idleNode, "death", 4.f );
    test::CreateMacroNode( creator, "death", 5.f );
    Create(data, &creator);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }
    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.5f, info.progresses[0]); 
    }
    g->SetTargetNode(1);

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1, info.animations[1]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.weights[1]);
      TS_ASSERT_EQUALS(0.5f, info.progresses[0]); 
      TS_ASSERT_EQUALS(0.f, info.progresses[1]);
    }
    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1, info.animations[1]);
      TS_ASSERT_EQUALS(0.75f, info.weights[0]);
      TS_ASSERT_EQUALS(0.25f, info.weights[1]);
      TS_ASSERT_EQUALS(0.5f, info.progresses[0]); 
      TS_ASSERT_EQUALS(0.2f, info.progresses[1]);
    }
    g->Update(3.f);  
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.8f, info.progresses[0]);
    }
    g->Update(2.f);  
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.2f, info.progresses[0], 1e-3f);
    }
  }

  void test_SimpleEvents()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("0", 5.f);
    test::g_OnEnterCallback = 0;
    test::g_OnLeaveCallback = 0;
    test::g_OnCallback = 0;
    Create(data);
    g->RegisterCallback(DIANGR_NODE, 0, test::OnEnterCallback, DIANGR_CF_ELEMENT_ENTER, 0 );
    g->RegisterCallback(DIANGR_NODE, 0, test::OnLeaveCallback, DIANGR_CF_ELEMENT_LEAVE, 0 );
    g->RegisterCallback(DIANGR_NODE, 0, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.5f );

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.f, info.progresses[0], 1e-3f);
    }

    g->Update(4.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.8f, info.progresses[0], 1e-3f);
    }

    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.2f, info.progresses[0], 1e-3f);
    }

    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.7f, info.progresses[0], 1e-3f);
    }

    g->Update(5.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.7f, info.progresses[0], 1e-3f);
    }

    TS_ASSERT_EQUALS( 0, test::g_OnLeaveCallback );
    TS_ASSERT_EQUALS( 1, test::g_OnEnterCallback );
    TS_ASSERT_EQUALS( 3, test::g_OnCallback );
  }

  void test_EventLowFPS()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 5.f);
    data.AddAnimation("death", 5.f);
    data.AddAnimation("rebirth", 5.f);
    NDb::AnimGraphCreator creator;

    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 5.f );
    test::CreateTransaction( idleNode, "death", 4.0f );
    NDb::AnGrMacronode& battleNode = test::CreateMacroNode( creator, "death", 5.f );
    test::CreateTransaction( battleNode, "rebirth", 4.0f );
    test::CreateMacroNode( creator, "rebirth", 5.f );
    Create(data, &creator);
    test::g_OnCallback = 0;
    g->RegisterCallback(DIANGR_MACRONODE, 2, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.5f );
    g->SetTargetNode(2);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.001f, info.progresses[0], 1e-3f);
    }
    g->Update(8.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2, info.animations[0]);
      TS_ASSERT_DELTA(1.f, info.weights[0], 1e-3f);
      TS_ASSERT_DELTA(0.8f, info.progresses[0], 1e-3f);
    }
    TS_ASSERT_EQUALS( 1, test::g_OnCallback );
  }

  void test_SpeedPoseToAnimBlending()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 5.f);
    data.AddAnimation("death", 5.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 5.f );
    test::CreateTransaction( idleNode, "death", 2.f );
    NDb::AnGrMacronode& deathNode = test::CreateMacroNode( creator, "death", 5.f );
    deathNode.speed.value = 0.5f;
    Create(data, &creator);
    g->SetTargetNode( 1 );
    unsigned __int64 starttime = __rdtsc();
    for ( int i = 0; i < 100; i++ )
    {
      g->Update(0.01f);
    }
    unsigned __int64 time = __rdtsc() - starttime;

    tearDown();

    NDb::AnimGraphCreator creator2;
    NDb::AnGrMacronode& idleNode2 = test::CreateMacroNode( creator2, "battleIdle", 5.f );
    NDb::AnGrFlMultiTransaction& tr = test::CreateTransaction( idleNode2, "death", 2.f );
    tr.parameters.blending = NDb::ANGRTRANSACTIONUPDATE_POSETOPOSE;
    NDb::AnGrMacronode& deathNode2 = test::CreateMacroNode( creator2, "death", 5.f );
    deathNode2.speed.value = 0.5f;
    Create(data, &creator2);
    g->SetTargetNode( 1 );
    unsigned __int64 starttime2 = __rdtsc();
    for ( int i = 0; i < 100; i++ )
    {
      g->Update(0.01f);
    }
    unsigned __int64 time2 = __rdtsc() - starttime2;

    double ratio = (double)time/(double)time2;

    TS_ASSERT( ratio < 5.0 );
    TS_ASSERT( ratio > 0.1 );
  }

  void test_NewSpeedNode()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("0", 5.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "0", 5.f );
    idleNode.speed.value = 0.5f;

    Create( data, &creator );

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }
    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.25f, info.progresses[0], 1e-3f); 
    }
    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.5f, info.progresses[0], 1e-3f); 
    }
    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.75f, info.progresses[0], 1e-3f); 
    }
  }

  void test_DefaultNode()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("second", 5.f);

    NDb::AnimGraphCreator creator;
    creator.defaultNode = "second";
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    test::CreateTransaction( idleNode, "second", 2.f );
    test::CreateMacroNode( creator, "second", 5.f );

    Create( data, &creator );

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }
  }

  void test_DefaultNodeWithSubNodes()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("first", 5.f);
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("idle1", 5.f);
    data.AddAnimation("idle2", 5.f);

    NDb::AnimGraphCreator creator;
    creator.defaultNode = "idle";
    NDb::AnGrMacronode& firstNode = test::CreateMacroNode( creator, "first", 5.f );
    test::CreateTransaction( firstNode, "idle", 2.f );
    
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    idleNode.nodeType = NDb::ANGRNODETYPE_DISPATCHER;
    idleNode.stopPar.value = 0.01f;
    idleNode.nextNode = "idle1";
    NDb::AnGrFlMultiTransaction& idle1Tr = test::CreateTransaction( idleNode, "idle1", 0.001f );
    idle1Tr.probability = 1.0f;
    NDb::AnGrFlMultiTransaction& idle2Tr = test::CreateTransaction( idleNode, "idle2", 0.001f );
    idle2Tr.probability = 1.0f;
    NDb::AnGrMacronode& idle1Node = test::CreateMacroNode( creator, "idle1", 5.f );
    idle1Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    NDb::AnGrMacronode& idle2Node = test::CreateMacroNode( creator, "idle2", 5.f );
    idle2Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;

    Create( data, &creator );

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1,info.animations.size());
      TS_ASSERT( info.animations[0] != 2 || info.animations[0] != 3 );
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }
  }

  void test_RandomNodesLoop()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("idle1", 5.f);
    data.AddAnimation("idle2", 5.f);
    srand(11);

    NDb::AnimGraphCreator creator;

    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    idleNode.nodeType = NDb::ANGRNODETYPE_DISPATCHER;
    idleNode.nextNode = "idle1";
    test::CreateTransaction( idleNode, "idle1", 0.001f ).probability = 1.0f;
    test::CreateTransaction( idleNode, "idle2", 0.001f ).probability = 1.0f;
    
    NDb::AnGrMacronode& idle1Node = test::CreateMacroNode( creator, "idle1", 5.f );
    idle1Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle1Node.nextNode = "idle";
    test::CreateTransaction( idle1Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;

    NDb::AnGrMacronode& idle2Node = test::CreateMacroNode( creator, "idle2", 5.f );
    idle2Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle2Node.nextNode = "idle";
    test::CreateTransaction( idle2Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;

    Create( data, &creator );

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1,info.animations.size());
      TS_ASSERT( info.animations[0] != 1 || info.animations[0] != 2 );
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }
    bool isIdle1 = false;
    bool isIdle2 = false;
    bool isIdle = false;
    for ( int i = 0; i < 100; i++ )
    {
      g->Update(0.2f);
      const SkeletonInfo& info = blender->GetLastFrame();
      for ( int k = 0; k < info.animations.size(); k++ )
      {
        if ( info.animations[k] == 0 )
          isIdle = true;
        if ( info.animations[k] == 1 )
          isIdle1 = true;
        if ( info.animations[k] == 2 )
          isIdle2 = true;
      }
    }
    TS_ASSERT( !isIdle );
    TS_ASSERT( isIdle1 );
    TS_ASSERT( isIdle2 );
  }

  void test_TransferToRandomNode()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("move", 5.f);
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("idle1", 5.f);
    data.AddAnimation("idle2", 5.f);

    NDb::AnimGraphCreator creator;
    creator.defaultNode = "move";

    NDb::AnGrMacronode& moveNode = test::CreateMacroNode( creator, "move", 5.f );
    test::CreateTransaction( moveNode, "idle", 2.f );
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    idleNode.nodeType = NDb::ANGRNODETYPE_DISPATCHER;
    idleNode.nextNode = "idle1";
    test::CreateTransaction( idleNode, "idle1", 0.001f ).probability = 1.0f;
    test::CreateTransaction( idleNode, "idle2", 0.001f ).probability = 1.0f;
    NDb::AnGrMacronode& idle1Node = test::CreateMacroNode( creator, "idle1", 5.f );
    idle1Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle1Node.nextNode = "idle";
    test::CreateTransaction( idle1Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;
    NDb::AnGrMacronode& idle2Node = test::CreateMacroNode( creator, "idle2", 5.f );
    idle2Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle2Node.nextNode = "idle";
    test::CreateTransaction( idle2Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;

    Create( data, &creator );

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1,info.animations.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }

    g->SetTargetNode(1);

    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2,info.animations.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT( 1 == info.animations[1] || 2 == info.animations[1] );
      TS_ASSERT_DELTA(0.5f, info.weights[0], 1e-3f); 
      TS_ASSERT_DELTA(0.5f, info.weights[1], 1e-3f); 
      TS_ASSERT_DELTA(0.f, info.progresses[0], 1e-3f); 
      TS_ASSERT_DELTA(0.2f, info.progresses[1], 1e-3f); 
    }

    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1,info.animations.size());
      TS_ASSERT( 1 == info.animations[0] || 2 == info.animations[0] );
      TS_ASSERT_DELTA(1.0f, info.weights[0], 1e-3f); 
      TS_ASSERT_DELTA(0.4f, info.progresses[0], 1e-3f); 
    }
  }

  void test_TransferFromRandomNode()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("move", 5.f);
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("idle1", 5.f);
    data.AddAnimation("idle2", 5.f);

    NDb::AnimGraphCreator creator;

    NDb::AnGrMacronode& moveNode = test::CreateMacroNode( creator, "move", 5.f );
    test::CreateTransaction( moveNode, "idle", 2.f );
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    idleNode.nodeType = NDb::ANGRNODETYPE_DISPATCHER;
    idleNode.nextNode = "idle1";
    test::CreateTransaction( idleNode, "idle1", 0.001f ).probability = 1.0f;
    test::CreateTransaction( idleNode, "idle2", 0.001f ).probability = 1.0f;
    NDb::AnGrMacronode& idle1Node = test::CreateMacroNode( creator, "idle1", 5.f );
    idle1Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle1Node.nextNode = "idle";
    test::CreateTransaction( idle1Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;
    test::CreateTransaction( idle1Node, "move", 2.f );
    NDb::AnGrMacronode& idle2Node = test::CreateMacroNode( creator, "idle2", 5.f );
    idle2Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle2Node.nextNode = "idle";
    test::CreateTransaction( idle2Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;
    test::CreateTransaction( idle2Node, "move", 2.f );

    Create( data, &creator );

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1,info.animations.size());
      TS_ASSERT( 1 == info.animations[0] || 2 == info.animations[0] );
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }

    g->SetTargetNode(0);

    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2,info.animations.size());
      TS_ASSERT( 1 == info.animations[0] || 2 == info.animations[0] );
      TS_ASSERT_EQUALS(0, info.animations[1]);
      TS_ASSERT_DELTA(0.5f, info.weights[0], 1e-3f); 
      TS_ASSERT_DELTA(0.5f, info.weights[1], 1e-3f); 
      TS_ASSERT_DELTA(0.f, info.progresses[0], 1e-3f); 
      TS_ASSERT_DELTA(0.2f, info.progresses[1], 1e-3f); 
    }

    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1,info.animations.size());
      TS_ASSERT( 0 == info.animations[0] );
      TS_ASSERT_DELTA(1.0f, info.weights[0], 1e-3f); 
      TS_ASSERT_DELTA(0.4f, info.progresses[0], 1e-3f); 
    }
  }

  void test_LongTransferToRandomNode()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("first", 5.f);
    data.AddAnimation("move", 5.f);
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("idle1", 5.f);
    data.AddAnimation("idle2", 5.f);

    NDb::AnimGraphCreator creator;
    creator.defaultNode = "first";

    NDb::AnGrMacronode& firstNode = test::CreateMacroNode( creator, "first", 5.f );
    test::CreateTransaction( firstNode, "move", 2.f );
    NDb::AnGrMacronode& moveNode = test::CreateMacroNode( creator, "move", 5.f );
    test::CreateTransaction( moveNode, "idle", 2.f );
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    idleNode.nodeType = NDb::ANGRNODETYPE_DISPATCHER;
    idleNode.nextNode = "idle1";
    test::CreateTransaction( idleNode, "idle1", 0.001f ).probability = 1.0f;
    test::CreateTransaction( idleNode, "idle2", 0.001f ).probability = 1.0f;
    NDb::AnGrMacronode& idle1Node = test::CreateMacroNode( creator, "idle1", 5.f );
    idle1Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle1Node.nextNode = "idle";
    test::CreateTransaction( idle1Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;
    NDb::AnGrMacronode& idle2Node = test::CreateMacroNode( creator, "idle2", 5.f );
    idle2Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle2Node.nextNode = "idle";
    test::CreateTransaction( idle2Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;

    Create( data, &creator );

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1,info.animations.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }

    g->SetTargetNode(2);

    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2,info.animations.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT( 1 == info.animations[1] );
      TS_ASSERT_DELTA(0.5f, info.weights[0], 1e-3f); 
      TS_ASSERT_DELTA(0.5f, info.weights[1], 1e-3f); 
      TS_ASSERT_DELTA(0.f, info.progresses[0], 1e-3f); 
      TS_ASSERT_DELTA(0.2f, info.progresses[1], 1e-3f); 
    }
    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1,info.animations.size());
      TS_ASSERT( 1 == info.animations[0] );
      TS_ASSERT_DELTA(1.0f, info.weights[0], 1e-3f); 
      TS_ASSERT_DELTA(0.4f, info.progresses[0], 1e-3f); 
    }
    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2,info.animations.size());
      TS_ASSERT( 1 == info.animations[0] );
      TS_ASSERT( 2 == info.animations[1] || 3 == info.animations[1] );
      TS_ASSERT_DELTA(0.5f, info.weights[0], 1e-3f); 
      TS_ASSERT_DELTA(0.5f, info.weights[1], 1e-3f); 
      TS_ASSERT_DELTA(0.4f, info.progresses[0], 1e-3f); 
      TS_ASSERT_DELTA(0.2f, info.progresses[1], 1e-3f); 
    }
  }

  void test_Probability()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("idle1", 5.f);
    data.AddAnimation("idle2", 5.f);
    srand(11);

    NDb::AnimGraphCreator creator;

    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    idleNode.nodeType = NDb::ANGRNODETYPE_DISPATCHER;
    idleNode.nextNode = "idle1";
    test::CreateTransaction( idleNode, "idle1", 0.001f ).probability = 50.0f;
    test::CreateTransaction( idleNode, "idle2", 0.001f ).probability = 60.0f;

    NDb::AnGrMacronode& idle1Node = test::CreateMacroNode( creator, "idle1", 5.f );
    idle1Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle1Node.nextNode = "idle";
    test::CreateTransaction( idle1Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;

    NDb::AnGrMacronode& idle2Node = test::CreateMacroNode( creator, "idle2", 5.f );
    idle2Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle2Node.nextNode = "idle";
    test::CreateTransaction( idle2Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;

    Create( data, &creator );

    int numIdle1 = 0;
    int numIdle2 = 0;

    for ( int i = 0; i < 100; i++ )
    {
      g->Update(5.f);
      const SkeletonInfo& info = blender->GetLastFrame();
      for ( int k = 0; k < info.animations.size(); k++ )
      {
        if ( info.animations[k] == 1 )
          numIdle1++;
        if ( info.animations[k] == 2 )
          numIdle2++;
      }
    }
    TS_ASSERT_DELTA( 5.0f/4.0f, (float)numIdle2/(float)numIdle1, 0.3f );
  }

  void test_PoseToAnimBlendingEvent()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 5.f);
    data.AddAnimation("death", 5.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 5.f );
    test::CreateTransaction( idleNode, "death", 2.f );
    test::CreateMacroNode( creator, "death", 5.f );

    test::g_OnEnterCallback = 0;
    test::g_OnLeaveCallback = 0;
    test::g_OnCallback = 0;
    Create(data, &creator);
    g->RegisterCallback(DIANGR_NODE, 1, test::OnEnterCallback, DIANGR_CF_ELEMENT_ENTER, 0 );
    g->RegisterCallback(DIANGR_NODE, 1, test::OnLeaveCallback, DIANGR_CF_ELEMENT_LEAVE, 0 );
    g->RegisterCallback(DIANGR_NODE, 1, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.1f );
    g->SetTargetNode( 1 );
    TS_ASSERT( test::g_OnEnterCallback == 0 );
    g->Update(0.f);
    TS_ASSERT( test::g_OnEnterCallback == 1 );
    g->Update(0.49f);
    TS_ASSERT( test::g_OnCallback == 0 );
    g->Update(0.02f);
    TS_ASSERT( test::g_OnCallback == 1 );
  }

  void test_PoseToAnimBlendingEventNotFromStart()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 5.f);
    data.AddAnimation("death", 5.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 5.f );
    NDb::AnGrFlMultiTransaction& tr = test::CreateTransaction( idleNode, "death", 2.f );
    tr.parameters.fromMin.value = 0.5f;
    test::CreateMacroNode( creator, "death", 5.f );

    test::g_OnEnterCallback = 0;
    test::g_OnLeaveCallback = 0;
    test::g_OnCallback = 0;
    Create(data, &creator);
    g->RegisterCallback(DIANGR_NODE, 1, test::OnEnterCallback, DIANGR_CF_ELEMENT_ENTER, 0 );
    g->RegisterCallback(DIANGR_NODE, 1, test::OnLeaveCallback, DIANGR_CF_ELEMENT_LEAVE, 0 );
    g->RegisterCallback(DIANGR_NODE, 1, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.1f );
    g->SetTargetNode( 1 );
    TS_ASSERT( test::g_OnEnterCallback == 0 );
    g->Update(0.f);
    TS_ASSERT( test::g_OnEnterCallback == 0 );
    g->Update(2.49f);
    TS_ASSERT( test::g_OnEnterCallback == 0 );
    g->Update(0.02f);
    TS_ASSERT( test::g_OnEnterCallback == 1 );
    TS_ASSERT( test::g_OnCallback == 0 );
    g->Update(2.49f);
    TS_ASSERT( test::g_OnCallback == 1 );
  }

  void test_PoseToAnimBlendingEventNotFromStartReal()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 5.f);
    data.AddAnimation("death", 5.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 5.f );
    NDb::AnGrFlMultiTransaction& tr = test::CreateTransaction( idleNode, "death", 2.f );
    tr.parameters.fromMin.value = 0.5f;
    test::CreateMacroNode( creator, "death", 5.f );

    test::g_OnEnterCallback = 0;
    test::g_OnLeaveCallback = 0;
    test::g_OnCallback = 0;
    Create(data, &creator);
    g->RegisterCallback(DIANGR_NODE, 1, test::OnEnterCallback, DIANGR_CF_ELEMENT_ENTER, 0 );
    g->RegisterCallback(DIANGR_NODE, 1, test::OnLeaveCallback, DIANGR_CF_ELEMENT_LEAVE, 0 );
    g->RegisterCallback(DIANGR_NODE, 1, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.38f );
    g->SetTargetNode( 1 );
    TS_ASSERT( test::g_OnEnterCallback == 0 );
    g->Update(0.f);
    TS_ASSERT( test::g_OnEnterCallback == 0 );
    g->Update(2.49f);
    TS_ASSERT( test::g_OnEnterCallback == 0 );
    g->Update(0.02f);
    TS_ASSERT( test::g_OnEnterCallback == 1 );
    TS_ASSERT( test::g_OnCallback == 0 );
    for ( int k = 0; k < 10; k++ )
    {
      g->Update(0.25f);
    }
    TS_ASSERT( test::g_OnCallback == 1 );
  }

  void test_ReachMarkerByTimePoseToAnim()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 2.f);
    data.AddAnimation("death", 4.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 2.f );
    NDb::AnGrFlMultiTransaction& tr = test::CreateTransaction( idleNode, "death", 2.f );
    tr.parameters.fromMin.value = 0.99f;
    NDb::AnGrMacronode& deathNode = test::CreateMacroNode( creator, "death", 4.f );
    NDb::AnGrMarker marker;
    marker.name = "lofik";
    marker.virtPar = 0.5f;
    deathNode.markers.push_back(marker);

    Create(data, &creator);
    bool isReach = g->ReachMarkerByTime("lofik",2000);
    TS_ASSERT( isReach );
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT( info.animations.size() == 1 );
      TS_ASSERT_DELTA( info.progresses[0], 0.5f, 0.1f );
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT( info.animations.size() == 2 );
      TS_ASSERT_DELTA( info.progresses[0], 0.99f, 0.1f );
      TS_ASSERT_DELTA( info.progresses[1], 0.01f, 0.1f );
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT( info.animations.size() == 2 );
      TS_ASSERT_DELTA( info.progresses[0], 0.99f, 0.1f );
      TS_ASSERT_DELTA( info.progresses[1], 0.25f, 0.1f );
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT( info.animations.size() == 1 );
      TS_ASSERT_DELTA( info.progresses[0], 0.5f, 0.1f );
    }
  }

  void test_ReachMarkerByTimePoseToPose()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 2.f);
    data.AddAnimation("death", 4.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 2.f );
    NDb::AnGrFlMultiTransaction& tr = test::CreateTransaction( idleNode, "death", 2.f );
    tr.parameters.fromMin.value = 0.99f;
    tr.parameters.blending = NDb::ANGRTRANSACTIONUPDATE_POSETOPOSE;
    NDb::AnGrMacronode& deathNode = test::CreateMacroNode( creator, "death", 4.f );
    NDb::AnGrMarker marker;
    marker.name = "lofik";
    marker.virtPar = 0.5f;
    deathNode.markers.push_back(marker);

    Create(data, &creator);
    bool isReach = g->ReachMarkerByTime("lofik",2000);
    TS_ASSERT( isReach );
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT( info.animations.size() == 1 );
      TS_ASSERT_DELTA( info.progresses[0], 0.75f, 0.1f );
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT( info.animations.size() == 2 );
      TS_ASSERT_DELTA( info.progresses[0], 0.99f, 0.1f );
      TS_ASSERT_DELTA( info.progresses[1], 0.01f, 0.1f );
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT( info.animations.size() == 1 );
      TS_ASSERT_DELTA( info.progresses[0], 0.125f, 0.1f );
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT( info.animations.size() == 1 );
      TS_ASSERT_DELTA( info.progresses[0], 0.5f, 0.1f );
    }
  }

  void test_TransferDurationZero()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 5.f);
    data.AddAnimation("death", 5.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 5.f );
    test::CreateTransaction( idleNode, "death", 0.f );
    test::CreateMacroNode( creator, "death", 5.f );
    Create(data, &creator);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }
    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.5f, info.progresses[0]); 
    }
    g->SetTargetNode(1);

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }
    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.2f, info.progresses[0], 1e-3f);
    }
    g->Update(3.f);  
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.8f, info.progresses[0], 1e-3f);
    }
    g->Update(2.f);  
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.2f, info.progresses[0], 1e-3f);
    }
  }

  void test_EventProbability()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("0", 5.f);
    srand(73);
    test::g_OnEnterCallback = 0;
    test::g_OnLeaveCallback = 0;
    test::g_OnCallback = 0;
    Create(data);
    g->RegisterCallback(DIANGR_NODE, 0, test::OnEnterCallback, DIANGR_CF_ELEMENT_ENTER, 0 );
    g->RegisterCallback(DIANGR_NODE, 0, test::OnLeaveCallback, DIANGR_CF_ELEMENT_LEAVE, 0 );
    g->RegisterCallback(DIANGR_NODE, 0, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.3f, 50.f );

    g->Update(0.f);
    for ( int i = 0; i < 100; i++ )
    {
      g->Update(0.5f);
    }
    TS_ASSERT_EQUALS( 0, test::g_OnLeaveCallback );
    TS_ASSERT_EQUALS( 1, test::g_OnEnterCallback );
    TS_ASSERT_EQUALS( 5, test::g_OnCallback );
  }

  void test_SetNodeSpeed()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("idle", 5.f);

    NDb::AnimGraphCreator creator;
    test::CreateMacroNode( creator, "idle", 5.f );
    Create(data, &creator);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.f, info.progresses[0], 1e-3f);
    }
    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.4f, info.progresses[0], 1e-3f);
    }
    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.8f, info.progresses[0], 1e-3f);
    }
    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(1.f, info.progresses[0], 1e-3f);
    }
    g->SetNodeSpeed(0,2.f);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(1.f, info.progresses[0], 1e-3f);
    }
    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.8f, info.progresses[0], 1e-3f);
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(1.f, info.progresses[0], 1e-3f);
    }
    g->SetNodeSpeed(0,0.5f);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(1.f, info.progresses[0], 1e-3f);
    }
    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.2f, info.progresses[0], 1e-3f);
    }
    g->Update(6.0f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.8f, info.progresses[0], 1e-3f);
    }
    g->Update(2.0f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(1.f, info.progresses[0], 1e-3f);
    }
  }

  void test_SetNodeSpeedRandomNodes()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("idle1", 5.f);
    data.AddAnimation("idle2", 5.f);
    srand(11);

    NDb::AnimGraphCreator creator;

    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    idleNode.nodeType = NDb::ANGRNODETYPE_DISPATCHER;
    idleNode.nextNode = "idle1";
    test::CreateTransaction( idleNode, "idle1", 0.001f ).probability = 1.0f;
    test::CreateTransaction( idleNode, "idle2", 0.001f ).probability = 1.0f;

    NDb::AnGrMacronode& idle1Node = test::CreateMacroNode( creator, "idle1", 5.f );
    idle1Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle1Node.nextNode = "idle";
    test::CreateTransaction( idle1Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;

    NDb::AnGrMacronode& idle2Node = test::CreateMacroNode( creator, "idle2", 5.f );
    idle2Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle2Node.nextNode = "idle";
    test::CreateTransaction( idle2Node, "idle", 0.001f ).parameters.fromMin.value = 0.99f;

    Create( data, &creator );

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.f, info.progresses[0], 1e-3f);
    }
    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.4f, info.progresses[0], 1e-3f);
    }
    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.8f, info.progresses[0], 1e-3f);
    }
    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.01f, info.progresses[0], 1e-3f);
    }
    g->SetNodeSpeed(0,2.f);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.01f, info.progresses[0], 1e-3f);
    }
    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.81f, info.progresses[0], 1e-3f);
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.02f, info.progresses[0], 1e-3f);
    }
    g->SetNodeSpeed(0,0.5f);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.02f, info.progresses[0], 1e-3f);
    }
    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.22f, info.progresses[0], 1e-3f);
    }
    g->Update(6.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.82f, info.progresses[0], 1e-3f);
    }
    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT(1 == info.animations[0] || 2 == info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.03f, info.progresses[0], 1e-3f);
    }
  }

  void test_EventInZeroParamInRandomNodes()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("idle1", 5.f);
    data.AddAnimation("idle2", 5.f);
    srand(11);

    NDb::AnimGraphCreator creator;

    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    idleNode.nodeType = NDb::ANGRNODETYPE_DISPATCHER;
    idleNode.nextNode = "idle1";
    test::CreateTransaction( idleNode, "idle1", 2.001f ).probability = 1.0f;
    test::CreateTransaction( idleNode, "idle2", 2.001f ).probability = 1.0f;

    NDb::AnGrMacronode& idle1Node = test::CreateMacroNode( creator, "idle1", 5.f );
    idle1Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle1Node.nextNode = "idle";
    test::CreateTransaction( idle1Node, "idle", 2.001f ).parameters.fromMin.value = 1.0f;

    NDb::AnGrMacronode& idle2Node = test::CreateMacroNode( creator, "idle2", 5.f );
    idle2Node.nodeType = NDb::ANGRNODETYPE_SUBNODE;
    idle2Node.nextNode = "idle";
    test::CreateTransaction( idle2Node, "idle", 2.001f ).parameters.fromMin.value = 1.0f;

    test::g_OnCallback = 0;
    Create( data, &creator );
    g->RegisterCallback(DIANGR_NODE, 1, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.0f );
    g->RegisterCallback(DIANGR_NODE, 2, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.0f );
    TS_ASSERT( test::g_OnCallback == 0 );
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
    }
    TS_ASSERT( test::g_OnCallback == 1 );
    g->Update(5.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT(!info.animations.empty());
    }
    TS_ASSERT( test::g_OnCallback == 2 );
    g->Update(2.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT(!info.animations.empty());
    }
    for ( int i = 0; i < 5; i++ )
    {
      g->Update(5.f);
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT(!info.animations.empty());
    }
    TS_ASSERT( test::g_OnCallback == 7 );

    for ( int i = 0; i < 500; i++ )
    {
      g->Update(0.05f);
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT(!info.animations.empty());
    }
    TS_ASSERT( test::g_OnCallback == 12 );
  }

  void test_ReachMarkerByTimeInRealCase()
  {
    test::AnimationDataHolder data;
    CObj<TestFileSystem> pFileSystem;
    pFileSystem = new TestFileSystem( "", true, false );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
    pFileSystem->AssignFileWithFile( "_.ANGR.xdb", "_.ANGR.xdb" );
    NDb::Ptr<NDb::AnimGraphCreator> creator = Get<NDb::AnimGraphCreator>( NDb::DBID( "_.ANGR" ) );
    for ( int i = 0; i < creator->macroNodes.size(); i++ )
    {
      data.AddAnimation( creator->macroNodes[i].sequenceName.c_str(), 5.f );
    }
    srand(11);
    Create( data, creator.GetPtr() );
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 14 || info.animations[0] == 2 );
    }
    g->SetTargetNode(24);
    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 16 || info.animations[0] == 0 );
      TS_ASSERT_DELTA( 0.2f, info.progresses[0], 1e-3f );
    }
    bool isReach = g->ReachMarkerByTime( "doFire", 100 );
    TS_ASSERT( isReach );
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2, info.size());
      TS_ASSERT( info.animations[0] == 16 || info.animations[0] == 0 );
      TS_ASSERT_DELTA( 0.2f, info.progresses[0], 1e-3f );
      TS_ASSERT( info.animations[1] == 17 );
      TS_ASSERT_DELTA( 0.0f, info.progresses[1], 1e-3f );
    }
    g->Update(0.1f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 17  );
      TS_ASSERT_DELTA( 0.1358f, info.progresses[0], 1e-3f );
    }
    g->Update(4.27f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 17  );
      TS_ASSERT_DELTA( 0.99f, info.progresses[0], 1e-2f );
    }
    isReach = g->ReachMarkerByTime( "doFire", 680 );
    TS_ASSERT( isReach );
    g->Update(0.68f); // <---- TODO Bad NextNode!!!
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 15  );
      TS_ASSERT_DELTA( 0.1358f, info.progresses[0], 1e-3f );
      TS_ASSERT_DELTA( 1.0f, g->GetGraphSpeedCoeff(), 0.1f );
    }
    g->Update(0.1f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 15  );
      TS_ASSERT_DELTA( 0.1558f, info.progresses[0], 1e-3f );
      TS_ASSERT_DELTA( 1.0f, g->GetGraphSpeedCoeff(), 1e-3f );
    }
    g->Update(4.1f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 15  );
      TS_ASSERT_DELTA( 0.9758f, info.progresses[0], 1e-3f );
      TS_ASSERT_DELTA( 1.0f, g->GetGraphSpeedCoeff(), 1e-3f );
    }
    g->Update(0.1f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 15  );
      TS_ASSERT_DELTA( 0.9958f, info.progresses[0], 1e-3f );
      TS_ASSERT_DELTA( 1.0f, g->GetGraphSpeedCoeff(), 1e-3f );
    }
    g->Update(0.1f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2, info.size());
      TS_ASSERT( info.animations[0] == 15  );
      TS_ASSERT( info.animations[1] == 14  );
      TS_ASSERT_DELTA( 0.9958f, info.progresses[0], 1e-3f );
      TS_ASSERT_DELTA( 0.02f, info.progresses[1], 1e-3f );
      TS_ASSERT_DELTA( 1.0f, g->GetGraphSpeedCoeff(), 1e-3f );
    }
  }

  void test_DefaultNextNode()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("A", 5.f);
    data.AddAnimation("B", 5.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& ANode = test::CreateMacroNode( creator, "A", 5.f );
    NDb::AnGrFlMultiTransaction& tr = test::CreateTransaction( ANode, "B", 0.1f );
    tr.parameters.fromMin.value = 0.0f;
    tr.parameters.fromMax.value = 1.0f;
    ANode.nextNode = "B";
    test::CreateMacroNode( creator, "B", 5.f );
    Create(data, &creator);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.f, info.progresses[0], 1e-3f );
    }
    g->Update(4.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.8f, info.progresses[0], 1e-3f );
    }
    g->Update(0.9f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.98f, info.progresses[0], 1e-3f );
    }
    g->Update(0.1f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 1  );
      TS_ASSERT_DELTA( 0.02f, info.progresses[0], 1e-3f );
    }
    g->Restart( 0, true );
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.f, info.progresses[0], 1e-3f );
    }
    g->SetTargetNode(1);
    g->Update(0.0f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT( info.animations[1] == 1  );
      TS_ASSERT_DELTA( 0.f, info.progresses[0], 1e-3f );
      TS_ASSERT_DELTA( 0.f, info.progresses[1], 1e-3f );
    }
  }

  void test_ForReachMarkerByTimeInSameNode()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("A", 5.f);
    data.AddAnimation("B", 5.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& ANode = test::CreateMacroNode( creator, "A", 5.f );
    NDb::AnGrMarker marker;
    marker.name = "tm";
    marker.virtPar = 0.2f;
    ANode.markers.push_back(marker);
    NDb::AnGrFlMultiTransaction& tr = test::CreateTransaction( ANode, "B", 0.5f );
    tr.parameters.fromMin.value = 0.0f;
    tr.parameters.fromMax.value = 1.0f;
    ANode.nextNode = "B";
    NDb::AnGrMacronode& BNode = test::CreateMacroNode( creator, "B", 5.f );
    NDb::AnGrFlMultiTransaction& tr2 = test::CreateTransaction( BNode, "A", 0.5f );
    tr2.parameters.fromMin.value = 0.0f;
    tr2.parameters.fromMax.value = 1.0f;
    Create(data, &creator);
    g->Update(0.0f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.f, info.progresses[0], 1e-3f );
    }
    g->Update(4.9f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.98f, info.progresses[0], 1e-3f );
    }
    bool isReach = g->ReachMarkerByTime( "tm", 500, true, false );
    TS_ASSERT(isReach);
    g->Update(0.0f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.98f, info.progresses[0], 1e-3f );
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.2f, info.progresses[0], 1e-3f );
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.3f, info.progresses[0], 1e-3f );
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.4f, info.progresses[0], 1e-3f );
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.5f, info.progresses[0], 1e-3f );
    }
    g->Update(2.4f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0  );
      TS_ASSERT_DELTA( 0.98f, info.progresses[0], 1e-3f );
    }
    g->Update(1.0f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 1  );
      TS_ASSERT_DELTA( 0.18f, info.progresses[0], 1e-3f );
    }
  }

  void test_ReachMarkerByTimeRanged()
  {
    test::AnimationDataHolder data;
    CObj<TestFileSystem> pFileSystem;
    pFileSystem = new TestFileSystem( "", true, false );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
    pFileSystem->AssignFileWithFile( "Range.ANGR.xdb", "Range.ANGR.xdb" );
    NDb::Ptr<NDb::AnimGraphCreator> creator = Get<NDb::AnimGraphCreator>( NDb::DBID( "Range.ANGR" ) );
    for ( int i = 0; i < creator->macroNodes.size(); i++ )
    {
      data.AddAnimation( creator->macroNodes[i].sequenceName.c_str(), 1.5f );
    }
    srand(11);
    Create( data, creator.GetPtr() );
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0 );
    }
    SkeletonInfo info;
    for ( int i = 0; i < 100; i++ )
    {
      if ( i%15 == 0 )
      {
        bool isReach = g->ReachMarkerByTime( "doFire", 100, true, false );
        TS_ASSERT(isReach);
        g->Update(0.1f);
        {
          info = blender->GetLastFrame();
          TS_ASSERT( 2 == info.size() || 1 == info.size() );
          TS_ASSERT( info.animations[0] == 5 || info.animations[0] == 4 || info.animations[1] == 5 || info.animations[1] == 4 );
          if ( info.animations.size() == 1 )
          {
            TS_ASSERT_DELTA( 0.04f, info.progresses[0], 1e-2f );
          }
          else if ( info.animations.size() == 2 )
          {
            TS_ASSERT( fabs(0.04f - info.progresses[0]) < 1e-2f || fabs(0.04f - info.progresses[1]) < 1e-2f );
          }
          else
          {
            TS_ASSERT(false);
          }
        }
      }
      else
      {
        g->Update(0.1f);
        {
          info = blender->GetLastFrame();
          TS_ASSERT( 2 == info.size() || 1 == info.size() );
          TS_ASSERT( info.animations[0] == 0 || info.animations[0] == 4 || info.animations[0] == 5 );
        }
      }
    }
  }

  void test_ReachMarkerByTimeChangeRandomNode()
  {
    test::AnimationDataHolder data;
    CObj<TestFileSystem> pFileSystem;
    pFileSystem = new TestFileSystem( "", true, false );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
    pFileSystem->AssignFileWithFile( "Range.ANGR.xdb", "Range.ANGR.xdb" );
    NDb::Ptr<NDb::AnimGraphCreator> creator = Get<NDb::AnimGraphCreator>( NDb::DBID( "Range.ANGR" ) );
    for ( int i = 0; i < creator->macroNodes.size(); i++ )
    {
      data.AddAnimation( creator->macroNodes[i].sequenceName.c_str(), 1.5f );
    }
    srand(11);
    Create( data, creator.GetPtr() );

    int startAllocs = GetMallocsTotal();

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0 );
    }
    bool isReach = g->ReachMarkerByTime( "doFire", 100, true, false );
    TS_ASSERT(isReach);
    g->Update(0.1f);
    bool isFirstRandomNode = false;
    bool isSecondRandomNode = false;
    for ( int i = 1; i < 1000; i++ )
    {
      if ( i%15 == 0 )
      {
        bool isReach = g->ReachMarkerByTime( "doFire", 100, true, false );
        TS_ASSERT(isReach);
        g->Update(0.1f);
        {
          const SkeletonInfo& info = blender->GetLastFrame();
          TS_ASSERT( 1 == info.size() || 2 == info.size() );
          TS_ASSERT( info.animations[0] == 5 || info.animations[0] == 4 );
          if ( info.animations[0] == 4 )
          {
            isFirstRandomNode = true;
          }
          if ( info.animations[0] == 5 )
          {
            isSecondRandomNode = true;
          }
        }
      }
      else
      {
        g->Update(0.1f);
        {
          const SkeletonInfo& info = blender->GetLastFrame();
          TS_ASSERT( 2 == info.size() || 1 == info.size() );
          TS_ASSERT( info.animations[0] == 0 || info.animations[0] == 4 || info.animations[0] == 5 );
        }
      }
    }
    int endAllocs = GetMallocsTotal();
    std::cout << "\n" << endAllocs - startAllocs << "\n";

    TS_ASSERT( isFirstRandomNode );
    TS_ASSERT( isSecondRandomNode );
  }

  void test_ReachMarkerByTimeAndEvents()
  {
    test::AnimationDataHolder data;
    CObj<TestFileSystem> pFileSystem;
    pFileSystem = new TestFileSystem( "", true, false );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
    pFileSystem->AssignFileWithFile( "Range.ANGR.xdb", "Range.ANGR.xdb" );
    NDb::Ptr<NDb::AnimGraphCreator> creator = Get<NDb::AnimGraphCreator>( NDb::DBID( "Range.ANGR" ) );
    for ( int i = 0; i < creator->macroNodes.size(); i++ )
    {
      data.AddAnimation( creator->macroNodes[i].sequenceName.c_str(), 1.5f );
    }
    srand(11);
    Create( data, creator.GetPtr() );
    g->RegisterCallback(DIANGR_NODE, 6, test::OnEnterCallback, DIANGR_CF_ELEMENT_ENTER, 0 );
    g->RegisterCallback(DIANGR_NODE, 6, test::OnLeaveCallback, DIANGR_CF_ELEMENT_LEAVE, 0 );
    g->RegisterCallback(DIANGR_NODE, 6, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.0f );
    g->RegisterCallback(DIANGR_NODE, 7, test::OnEnterCallback, DIANGR_CF_ELEMENT_ENTER, 0 );
    g->RegisterCallback(DIANGR_NODE, 7, test::OnLeaveCallback, DIANGR_CF_ELEMENT_LEAVE, 0 );
    g->RegisterCallback(DIANGR_NODE, 7, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.0f );
    test::g_OnEnterCallback = 0;
    test::g_OnLeaveCallback = 0;
    test::g_OnCallback = 0;
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0 );
    }
    bool isReach = g->ReachMarkerByTime( "doFire", 100, true, false );
    TS_ASSERT(isReach);
    g->Update(0.1f);
    bool isFirstRandomNode = false;
    bool isSecondRandomNode = false;
    for ( int i = 1; i < 1000; i++ )
    {
      if ( i%15 == 0 )
      {
        bool isReach = g->ReachMarkerByTime( "doFire", 100, true, false );
        TS_ASSERT(isReach);
        g->Update(0.1f);
        {
          const SkeletonInfo& info = blender->GetLastFrame();
          TS_ASSERT( 1 == info.size() || 2 == info.size() );
          TS_ASSERT( info.animations[0] == 5 || info.animations[0] == 4 );
          if ( info.animations[0] == 4 )
          {
            isFirstRandomNode = true;
          }
          if ( info.animations[0] == 5 )
          {
            isSecondRandomNode = true;
          }
        }
      }
      else
      {
        g->Update(0.1f);
        {
          const SkeletonInfo& info = blender->GetLastFrame();
          TS_ASSERT( 2 == info.size() || 1 == info.size() );
          TS_ASSERT( info.animations[0] == 0 || info.animations[0] == 4 || info.animations[0] == 5 );
        }
      }
    }
    TS_ASSERT( isFirstRandomNode );
    TS_ASSERT( isSecondRandomNode );
    TS_ASSERT_EQUALS( 66, test::g_OnLeaveCallback );
    TS_ASSERT_EQUALS( 67, test::g_OnEnterCallback );
    TS_ASSERT_EQUALS( 67, test::g_OnCallback );
  }

  void test_ZeroInOut()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 5.f);
    data.AddAnimation("death", 5.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 5.f );
    idleNode.startPar.value = 0.0f;
    idleNode.stopPar.value = 0.0f;
    test::CreateTransaction( idleNode, "death", 4.f );
    test::CreateMacroNode( creator, "death", 5.f );
    Create(data, &creator);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }
    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]); 
    }
    g->SetTargetNode(1);

    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1, info.animations[1]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.weights[1]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]); 
      TS_ASSERT_EQUALS(0.f, info.progresses[1]);
    }
    g->Update(1.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(2, info.size());
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1, info.animations[1]);
      TS_ASSERT_EQUALS(0.75f, info.weights[0]);
      TS_ASSERT_EQUALS(0.25f, info.weights[1]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]); 
      TS_ASSERT_EQUALS(0.2f, info.progresses[1]);
    }
    g->Update(3.f);  
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.8f, info.progresses[0]);
    }
    g->Update(2.f);  
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.2f, info.progresses[0], 1e-3f);
    }
  }

  void test_FemaleDeathEvent()
  {
    test::AnimationDataHolder data;
    CObj<TestFileSystem> pFileSystem;
    pFileSystem = new TestFileSystem( "", true, false );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
    pFileSystem->AssignFileWithFile( "Female.ANGR.xdb", "Female.ANGR.xdb" );
    NDb::Ptr<NDb::AnimGraphCreator> creator = Get<NDb::AnimGraphCreator>( NDb::DBID( "Female.ANGR" ) );
    for ( int i = 0; i < creator->macroNodes.size(); i++ )
    {
      data.AddAnimation( creator->macroNodes[i].sequenceName.c_str(), 1.5f );
    }
    srand(11);
    Create( data, creator.GetPtr() );
    g->RegisterCallback(DIANGR_NODE, 3, test::OnEnterCallback, DIANGR_CF_ELEMENT_ENTER, 0 );
    test::g_OnEnterCallback = 0;
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0 || info.animations[0] == 8 || info.animations[0] == 11 );
    }
    for ( int i = 1; i < 20; i++ )
    {
      g->Update(0.5f);
      {
        const SkeletonInfo& info = blender->GetLastFrame();
        TS_ASSERT( info.animations[0] == 0 || info.animations[0] == 8 || info.animations[0] == 11 );
        if ( info.animations.size() > 1 )
        {
          TS_ASSERT( info.animations.size() == 2 )
          TS_ASSERT( info.animations[1] == 0 || info.animations[1] == 8 || info.animations[1] == 11 );
        }
      }
    }
    g->SetTargetNode( 3 );
    g->Update(0.1f);
    TS_ASSERT_EQUALS( 1, test::g_OnEnterCallback );
  }

  void assertCurTime( float curTime )
  {
    if ( curTime > 0.2f )
    {
      TS_ASSERT(test::g_OnCallback == 1);
    }
    else
    {
      TS_ASSERT(test::g_OnCallback == 0);
    }
  }

  void test_ReachMarkerByTimeCorrectTime()
  {
    test::AnimationDataHolder data;
    CObj<TestFileSystem> pFileSystem;
    pFileSystem = new TestFileSystem( "", true, false );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
    pFileSystem->AssignFileWithFile( "Melee1.ANGR.xdb", "Melee1.ANGR.xdb" );
    NDb::Ptr<NDb::AnimGraphCreator> creator = Get<NDb::AnimGraphCreator>( NDb::DBID( "Melee1.ANGR" ) );
    for ( int i = 0; i < creator->macroNodes.size(); i++ )
    {
      data.AddAnimation( creator->macroNodes[i].sequenceName.c_str(), 1.5f );
    }
    srand(11);
    Create( data, creator.GetPtr() );
    g->RegisterCallback(DIANGR_NODE, 6, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.13333f );
    g->RegisterCallback(DIANGR_NODE, 7, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.13333f );
    g->RegisterCallback(DIANGR_NODE, 11, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.13333f );
    g->RegisterCallback(DIANGR_NODE, 12, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.13333f );
    g->RegisterCallback(DIANGR_NODE, 14, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.13333f );
    test::g_OnEnterCallback = 0;
    test::g_OnLeaveCallback = 0;
    test::g_OnCallback = 0;
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.size());
      TS_ASSERT( info.animations[0] == 0 );
    }

    float deltaTime = 0.0f;
    float curTime = 0.0f;
    for ( int i = 0; i < 20; i++ )
    {
      test::g_OnCallback = 0;
      curTime = 0.0f;
      bool isReach = g->ReachMarkerByTime( "doFire", 200, true, false );
      TS_ASSERT(isReach);
      TS_ASSERT(test::g_OnCallback == 0);
      while ( curTime < 2.0f )
      {
        deltaTime = (rand()%150)*0.001f;
        curTime += deltaTime;
        g->Update( deltaTime );
        assertCurTime( curTime );
      }
    }
  }

  void test_EventWhenRestart()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("0", 5.f);
    test::g_OnEnterCallback = 0;
    test::g_OnCallback = 0;
    Create(data);
    g->RegisterCallback(DIANGR_NODE, 0, test::OnEnterCallback, DIANGR_CF_ELEMENT_ENTER, 0 );
    g->RegisterCallback(DIANGR_NODE, 0, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.0f );
    g->Update(0.0f);

    g->Restart( 0, true );
    g->Update(0.0f);

    g->Restart( 0, true );
    g->Update(0.0f);

    TS_ASSERT_EQUALS(test::g_OnEnterCallback,3);
    TS_ASSERT_EQUALS(test::g_OnCallback,3);
  }

  void test_InOutVParamEqual()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("battleIdle", 2.f);
    data.AddAnimation("death", 4.f);

    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "battleIdle", 2.f );
    NDb::AnGrFlMultiTransaction& tr = test::CreateTransaction( idleNode, "death", 0.f );
    tr.parameters.fromMin.value = 0.99f;
    NDb::AnGrMacronode& deathNode = test::CreateMacroNode( creator, "death", 4.f );
    deathNode.startPar.value = 0.5f;
    deathNode.stopPar.value = 0.5f;
    NDb::AnGrMarker marker;
    marker.name = "lofik";
    marker.virtPar = 0.5f;
    deathNode.markers.push_back(marker);

    Create(data, &creator);
    bool isReach = g->ReachMarkerByTime("lofik",2000);
    TS_ASSERT( isReach );
    test::g_OnCallback = 0;
    g->RegisterCallback(DIANGR_NODE, 1, test::OnCallback, DIANGR_CF_EXACT_PARAM, 0, 0.5f );
    g->Update(0.5f);
    g->Update(0.5f);
    g->Update(0.5f);
    g->Update(0.501f);
    TS_ASSERT_EQUALS( test::g_OnCallback, 1 );
  }

  //void test_Output()
  //{
  //  test::AnimationDataHolder data;
  //  CObj<TestFileSystem> pFileSystem;
  //  pFileSystem = new TestFileSystem( "", true, false );
  //  NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
  //  pFileSystem->AssignFileWithFile( "Idle.ANGR.xdb", "Idle.ANGR.xdb" );
  //  NDb::Ptr<NDb::AnimGraphCreator> creator = Get<NDb::AnimGraphCreator>( NDb::DBID( "Idle.ANGR" ) );
  //  for ( int i = 0; i < creator->macroNodes.size(); i++ )
  //  {
  //    data.AddAnimation( creator->macroNodes[i].sequenceName.c_str(), 10.f );
  //  }
  //  srand(11);
  //  Create( data, creator.GetPtr() );
  //  DiAnimNode* node = g->GetNodeData(0);
  //  std::cout << "\n\n\n";
  //  std::cout << node->GetStartPar() << " " << node->GetStopPar() << " " << node->GetVPar() << "\n";

  //  for ( int i = 0; i < 10; i++ )
  //  {
  //    g->Update(1.0f);
  //    DiAnimNode* node = g->GetNodeData(0);
  //    std::cout << node->GetPrevPar() << " " << node->GetVPar() << "\n";
  //  }
  //}

   void test_TransactionPlaceInOut()
   {
     test::AnimationDataHolder data;
     CObj<TestFileSystem> pFileSystem;
     pFileSystem = new TestFileSystem( "", true, false );
     NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
     pFileSystem->AssignFileWithFile( "Transaction.ANGR.xdb", "Transaction.ANGR.xdb" );
     NDb::Ptr<NDb::AnimGraphCreator> creator = Get<NDb::AnimGraphCreator>( NDb::DBID( "Transaction.ANGR" ) );
     for ( int i = 0; i < creator->macroNodes.size(); i++ )
     {
       data.AddAnimation( creator->macroNodes[i].sequenceName.c_str(), 10.f );
     }
     srand(11);
     Create( data, creator.GetPtr() );
     g->SetTargetNode(1);
     g->Update(0.99f);
     {
       const SkeletonInfo& info = blender->GetLastFrame();
       TS_ASSERT_EQUALS(1, info.size());
       TS_ASSERT( info.animations[0] == 0 );
     }
     g->Update(0.1f);
     {
       const SkeletonInfo& info = blender->GetLastFrame();
       TS_ASSERT_EQUALS(1, info.size());
       TS_ASSERT( info.animations[0] == 1 );
     }
   }

   void test_MarkerPlaceInOut()
   {
     test::AnimationDataHolder data;
     CObj<TestFileSystem> pFileSystem;
     pFileSystem = new TestFileSystem( "", true, false );
     NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
     pFileSystem->AssignFileWithFile( "Idle.ANGR.xdb", "Idle.ANGR.xdb" );
     NDb::Ptr<NDb::AnimGraphCreator> creator = Get<NDb::AnimGraphCreator>( NDb::DBID( "Idle.ANGR" ) );
     for ( int i = 0; i < creator->macroNodes.size(); i++ )
     {
       data.AddAnimation( creator->macroNodes[i].sequenceName.c_str(), 10.f );
     }
     srand(11);
     Create( data, creator.GetPtr() );
     test::g_OnCallback = 0;
     DiAnGrMarker* m = g->FindMarkerByName("tm");
     TS_ASSERT(m);
     g->RegisterCallback( *m, test::OnCallback, 0 );
     g->Update(0.5f);
     TS_ASSERT_EQUALS( test::g_OnCallback, 0 );
     g->Update(0.501f);
     TS_ASSERT_EQUALS( test::g_OnCallback, 1 );
   }

   void test_FreezeUnFreeze()
   {
     test::AnimationDataHolder data;
     data.AddAnimation("0", 5.f);

     Create(data);

     g->Update(0.f);
     {
       const SkeletonInfo& info = blender->GetLastFrame();
       TS_ASSERT_EQUALS(0, info.animations[0]);
       TS_ASSERT_EQUALS(1.f, info.weights[0]);
       TS_ASSERT_EQUALS(0.f, info.progresses[0]);
     }

     g->Update(2.5f);
     {
       const SkeletonInfo& info = blender->GetLastFrame();
       TS_ASSERT_EQUALS(0, info.animations[0]);
       TS_ASSERT_EQUALS(1.f, info.weights[0]);
       TS_ASSERT_EQUALS(0.5f, info.progresses[0]); 
     }
     g->Freeze();
     for ( int i = 0; i < 100; i++ )
     {
       g->Update(2.5f);
       {
         const SkeletonInfo& info = blender->GetLastFrame();
         TS_ASSERT_EQUALS(0, info.animations[0]);
         TS_ASSERT_EQUALS(1.f, info.weights[0]);
         TS_ASSERT_EQUALS(0.5f, info.progresses[0]); 
       }
     }
     g->UnFreeze();
     g->Update(2.5f);
     {
       const SkeletonInfo& info = blender->GetLastFrame();
       TS_ASSERT_EQUALS(0, info.animations[0]);
       TS_ASSERT_EQUALS(1.f, info.weights[0]);
       TS_ASSERT_EQUALS(1.f, info.progresses[0]);
     }
   }
  void test_ThreeNodes()
  {
  }

  void test_MinMaxTransitionTimes()
  {
  }

  void test_SimpleMarker()
  {
  }
};
