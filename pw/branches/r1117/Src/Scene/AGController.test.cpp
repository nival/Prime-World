//!Component('Scene/AnimationGraph')
//!Component('System/FileSystem/TestFileSystem')
//!Component('Scene/AGController')
#include "stdafx.h"
#include <cxxtest/TestSuite.h>

#include "System/FileSystem/TestFileSystem.h"
#include <Render/texture.h>
#include <Scene/DiAnGr.h>
#include "AGTrace.h"
#include "AGHelpers.h"
#include "TestHelpers.h"
#include "AnimGraphController.h"
#include <iostream>

namespace testAGC
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

struct Test_AnimGraphController : public CxxTest::TestSuite
{
  DiAnimGraph* g;
  MockAnimGraphBlender* blender;
  DiAnGrExtPars* extPars;
  NScene::AnimGraphController* agc;

  void setUp()
  {
    g = 0;
    blender = 0;
    extPars = 0;
    agc = 0;
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
    g->Restart( 0, true );
    agc = new NScene::AnimGraphController(g, data.animations );
  }

  void tearDown()
  {
    if ( agc )
      delete agc;
    if (g)
      DiAnimGraph::Destroy(g);
    if (extPars)
      delete  extPars;
    if (blender)
      delete blender;
  }

  void test_PlayOneByOneNode()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("death", 5.f);
    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    test::CreateTransaction( idleNode, "death", 0.f );
    test::CreateMacroNode( creator, "death", 5.f );
    Create(data, &creator);

    nstl::vector<int> nodesToPlay;
    nodesToPlay.push_back(0);
    agc->PlayNodes(nodesToPlay, 0.0f);
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
    nodesToPlay[0] = 1;
    agc->PlayNodes(nodesToPlay, 0.0f);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.f, info.progresses[0]);
    }

    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.5f, info.progresses[0]); 
    }

    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(1.f, info.progresses[0]);
    }

    g->Update(2.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_EQUALS(0.5f, info.progresses[0]); 
    }
  }

  void test_PlaySequenceFromTwoNodesWithoutLoop()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("death", 5.f);
    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    NDb::AnGrFlMultiTransaction& tr = test::CreateTransaction( idleNode, "death", 0.f );
    tr.parameters.fromMin.value = 0.1f;
    tr.parameters.fromMax.value = 1.0f;
    test::CreateMacroNode( creator, "death", 5.f );
    Create(data, &creator);

    nstl::vector<int> nodesToPlay;
    nodesToPlay.push_back(0);
    nodesToPlay.push_back(1);
    agc->PlayNodes(nodesToPlay, 0.0f);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.0f, info.progresses[0], 1e-3f);
    }
    g->Update(0.4f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.08f, info.progresses[0], 1e-3f);
    }
    g->Update(0.1f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.0f, info.progresses[0], 1e-3f);
    }
    g->Update(0.4f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.08f, info.progresses[0], 1e-3f);
    }
    g->Update(4.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.98f, info.progresses[0], 1e-3f);
    }
    g->Update(0.1f);
    g->Update(0.0f); //TODO: Потому что Restart не обновляет sequence
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.0f, info.progresses[0], 1e-3f);
    }
  }

  void test_PlaySequenceFromTwoNodesWithLoop()
  {
    test::AnimationDataHolder data;
    data.AddAnimation("idle", 5.f);
    data.AddAnimation("death", 5.f);
    NDb::AnimGraphCreator creator;
    NDb::AnGrMacronode& idleNode = test::CreateMacroNode( creator, "idle", 5.f );
    test::CreateTransaction( idleNode, "death", 0.f );
    test::CreateMacroNode( creator, "death", 5.f );
    Create(data, &creator);

    nstl::vector<int> nodesToPlay;
    nodesToPlay.push_back(0);
    nodesToPlay.push_back(1);
    agc->PlayNodes(nodesToPlay, 1.0f);
    g->Update(0.f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.0f, info.progresses[0], 1e-3f);
    }
    g->Update(0.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.1f, info.progresses[0], 1e-3f);
    }
    g->Update(0.4f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.18f, info.progresses[0], 1e-3f);
    }
    g->Update(0.1f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.0f, info.progresses[0], 1e-3f);
    }
    g->Update(0.4f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.08f, info.progresses[0], 1e-3f);
    }
    g->Update(4.5f);
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(1, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.98f, info.progresses[0], 1e-3f);
    }
    g->Update(0.1f);
    g->Update(0.0f); //TODO: Потому что Restart не обновляет sequence
    {
      const SkeletonInfo& info = blender->GetLastFrame();
      TS_ASSERT_EQUALS(0, info.animations[0]);
      TS_ASSERT_EQUALS(1.f, info.weights[0]);
      TS_ASSERT_DELTA(0.0f, info.progresses[0], 1e-3f);
    }
  }

};
