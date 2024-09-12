// Author: EugBel
// Date:   06/05/2009

#include "stdafx.h"
#include "AnimGraphBlender.h"

#include "../System/InlineProfiler.h"

namespace
{

const char *s_nodeIdleName = "null"; // this name is used to find "basic", "central" node in additional graph

} // end of anonymous namespace

// Uncomment this define to enable some log into "Output"
//#define ENABLE_AGB_TEXT_DEBUG
  
#ifdef ENABLE_AGB_TEXT_DEBUG
  #define AGB_TRACE           DebugTrace
#else
  #define AGB_TRACE
#endif // ENABLE_APP_TEXT_DEBUG


DiInt32 _wholeGraph2UpdateCallback(DiAnGrCallbackParams const &cpParams)
{
  NScene::AnimGraphBlender *blender = (NScene::AnimGraphBlender *)cpParams.vpUserData;
  NI_VERIFY(blender  != NULL, "Invalid blender ptr!", return DIOBJMSG_CONTINUE; );


  DiAnimGraph *addGr = blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_ADDITIONAL].m_graph;
  NI_VERIFY(addGr != NULL, "Invalid graph ptr!", DIOBJMSG_CONTINUE; );
  
  if (addGr->IsInTransactionOrFLTransaction())
  {
    if (int(addGr->GetPrevNode()) == blender->GetIdleNodeIdx()) // going from "idle" to some node
    {
      float additionalGraphWeight = addGr->GetCurTransactionPar();
      blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_ADDITIONAL].m_weight = additionalGraphWeight;
      blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_MAIN].m_weight       = 1.0f - additionalGraphWeight;
      AGB_TRACE("AGB: Moving FROM idle... MAIN: %5.3lf | ADD: %.3lf", 1.0f - additionalGraphWeight, additionalGraphWeight);
    }
    else if (int(addGr->GetNextNode()) == blender->GetIdleNodeIdx()) // going back to "idle" from some node
    {
      float additionalGraphWeight = 1.0f - addGr->GetCurTransactionPar();
      blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_ADDITIONAL].m_weight = additionalGraphWeight;
      blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_MAIN].m_weight       = 1.0f - additionalGraphWeight;
      AGB_TRACE("AGB: Moving TO idle... MAIN: %5.3lf | ADD: %.3lf", 1.0f - additionalGraphWeight, additionalGraphWeight);
    }

    NI_ASSERT(0.0f <= blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_ADDITIONAL].m_weight && blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_ADDITIONAL].m_weight <= 1.0f, "Weights error");
    NI_ASSERT(0.0f <= blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_MAIN].m_weight && blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_MAIN].m_weight <= 1.0f, "Weights error");
  }
  else if(addGr->IsInNodeOrMacronode())
  {
    if((int)addGr->GetCurNode() == blender->GetIdleNodeIdx())
    {
      blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_ADDITIONAL].m_weight = 0.0f;
      blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_MAIN      ].m_weight = 1.0f;
    }
    else
    {
      blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_ADDITIONAL].m_weight = 1.0f;
      blender->GetGraphsMixInfo()[NScene::AnimGraphBlender::AG_MAIN      ].m_weight = 0.0f;
    }
  }


  return DIOBJMSG_CONTINUE;
}




namespace NScene
{

void AnimGraphBlender::SetAnimGraphs(DiAnimGraph *mainGraph, DiAnimGraph *additionalGraph)
{

  // init mix info
  m_graphsMixInfo[AG_MAIN].m_graph        = mainGraph;
  m_graphsMixInfo[AG_MAIN].m_weight       = 1.0f;
  m_graphsMixInfo[AG_ADDITIONAL].m_graph  = additionalGraph;
  m_graphsMixInfo[AG_ADDITIONAL].m_weight = 0.0f;


  m_idleNodeIdx = 0;
  if (additionalGraph != NULL)
  {
    // Register callback on additional graph update
    DiAnimGraph *graph2 = m_graphsMixInfo[AG_ADDITIONAL].m_graph;
    graph2->RegisterCallback(DIANGR_ENTIREGRAPH, DIANGR_NO_SUCH_ELEMENT, ::_wholeGraph2UpdateCallback, DIANGR_CF_UPDATE_END, this);

    // 
    m_idleNodeIdx = graph2->GetNodeIDByNameSlow(s_nodeIdleName);
    NI_ASSERT(graph2->GetNodeData(m_idleNodeIdx)->IsMacronode() == false, "Idle node should be macronode!"); // this assumption is used in SetAdditionalAGTargetNode()
  }
}

AnimGraphBlender::AnimGraphBlender(AnimGraphApplicator *applicator)
{
  m_agApplicator = applicator;
}

AnimGraphBlender::~AnimGraphBlender()
{
  m_agApplicator = NULL;
}

bool AnimGraphBlender::SetMainAGTargetNode( int nodeId1 )
{
  return m_graphsMixInfo[AG_MAIN].m_graph->SetTargetNode(nodeId1);
}

bool AnimGraphBlender::SetAdditionalAGTargetNode( int nodeId2 )
{
  NI_VERIFY(m_graphsMixInfo[AG_ADDITIONAL].m_graph != NULL, "No additional graph!", return false; );

  DiAnimGraph *ag2 = m_graphsMixInfo[AG_ADDITIONAL].m_graph;

  if (int(ag2->GetCurNodeUnsafe()) == m_idleNodeIdx)
    ag2->ReplaceSeqInNode(nodeId2, 0, m_idleNodeIdx, 0);

  return ag2->SetTargetNode(nodeId2);
}

bool AnimGraphBlender::Update(float dt)
{
  NI_PROFILE_FUNCTION

  AGB_TRACE("======================\nAGB: BeginUpdate");
  m_agApplicator->BeginUpdate();

  // Additional graph should be updated first!
  AGB_TRACE("AGB: ADDITIONAL");
  m_curGraph = AG_ADDITIONAL;
  if (m_graphsMixInfo[m_curGraph].m_graph != NULL)
  {
    m_agApplicator->ConsiderNextGraph();
    m_graphsMixInfo[m_curGraph].m_graph->Update(dt);
  }

  AGB_TRACE("AGB: MAIN");
  m_curGraph = AG_MAIN;
  m_agApplicator->ConsiderNextGraph();
  m_graphsMixInfo[m_curGraph].m_graph->Update(dt);


  m_agApplicator->EndUpdate();
  AGB_TRACE("AGB: EndUpate()");

  return true;
}

void AnimGraphBlender::SetVirtualParameterByMix(int nMixIdx, float rT)
{
  NI_ASSERT(0.0f <= rT && rT <= 1.0f, "Wrong time");
  NI_ASSERT( m_agApplicator->IsInUpdate(), "Not in update" );
  m_agApplicator->SetVirtualParameterByMix(nMixIdx, rT);
}

bool AnimGraphBlender::RegisterSequencesToMix(int nSeqsCount, int  *npSeqIndices, float *rWeights)
{
  NI_ASSERT( m_agApplicator->IsInUpdate(), "Not in update" );
  AGB_TRACE("AGB: Weights: MAIN(%5.3lf) ADD(%5.3lf))", m_graphsMixInfo[AG_MAIN].m_weight, m_graphsMixInfo[AG_ADDITIONAL].m_weight);
  AGB_TRACE("AGB: SetWeights-in(num=%i, %5.3lf, %5.3lf, %5.3lf)", nSeqsCount, rWeights[0], rWeights[1], rWeights[2]);
  // correct weights using global graph weight in blender
  for (int i = 0; i < nSeqsCount; i++)
    rWeights[i] *= m_graphsMixInfo[m_curGraph].m_weight;
  AGB_TRACE("AGB: SetWeights-out(num=%i, %5.3lf, %5.3lf, %5.3lf)", nSeqsCount, rWeights[0], rWeights[1], rWeights[2]);
  return  m_agApplicator->RegisterSequencesToMix(nSeqsCount, npSeqIndices, rWeights);
}

bool AnimGraphBlender::Restart(int startNode)
{
  bool res = m_graphsMixInfo[AG_MAIN].m_graph->Restart( startNode, true );
  m_graphsMixInfo[AG_MAIN].m_weight       = 1.0f;

  if (m_graphsMixInfo[AG_ADDITIONAL].m_graph != NULL)
  {
    res = res && m_graphsMixInfo[AG_ADDITIONAL].m_graph->Restart( m_idleNodeIdx, true );
    m_graphsMixInfo[AG_ADDITIONAL].m_weight = 0.0f;
  }

  return res;
}

void AnimGraphBlender::SetGraphs( DiAnimGraph* main, DiAnimGraph* additional )
{
  NI_VERIFY( main != NULL, "First graph can't be NULL!", return;);

  m_graphsMixInfo[AG_MAIN].m_graph       = main;
  m_graphsMixInfo[AG_ADDITIONAL].m_graph = additional;

  Restart();
}

} // namespace NScene

