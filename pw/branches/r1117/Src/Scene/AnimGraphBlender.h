// Author: EugBel
// Date:   06/05/2009

#pragma once
#include "IAnimGraphBlender.h"
#include "DiAnGr.h"
namespace NScene
{

class AnimGraphBlender : public IAnimGraphBlender
{
public:
  enum GraphID
  {
    AG_MAIN = 0,
    AG_ADDITIONAL,
    _AG_NUM,
  };

  struct GraphsMixInfo
  {
    DiAnimGraph *m_graph;
    float        m_weight;

    GraphsMixInfo() : m_graph(NULL), m_weight(0.0f) {}
  };

  AnimGraphBlender(AnimGraphApplicator *applicator);
  ~AnimGraphBlender();

  void SetAnimGraphs(DiAnimGraph *mainGraph, DiAnimGraph *additionalGraph);

  bool SetMainAGTargetNode( int nodeId );
  bool SetAdditionalAGTargetNode( int nodeId );

  // Interfaces from AnimGraph
  AnimationVector const &GetAnimationVector() const { return m_agApplicator->GetAnimationVector(); }
  Time GetAnimDuration(const int& animName) const { return m_agApplicator->GetAnimDuration(animName); }
  void SetVirtualParameterByMix(int nMixIdx, float rT);
  bool RegisterSequencesToMix(int nSeqsCount, int  *npSeqIndices, float *rWeights);


  GraphsMixInfo  *GetGraphsMixInfo() { return m_graphsMixInfo; };
  int             GetIdleNodeIdx()   { return m_idleNodeIdx; }
  bool            Update(float dt);

  // Functions passes-through
  bool              Restart(int startNode = 0);
  void              SetGraphs( DiAnimGraph* main, DiAnimGraph* additional );
  DiAnimGraph       *GetMainGraph()               { return m_graphsMixInfo[AG_MAIN].m_graph; }
  DiAnimGraph const *GetMainGraph() const         { return m_graphsMixInfo[AG_MAIN].m_graph; }
  DiAnimGraph       *GetAdditionalGraph()         { return m_graphsMixInfo[AG_ADDITIONAL].m_graph; }
  DiAnimGraph const *GetAdditionalGraph() const   { return m_graphsMixInfo[AG_ADDITIONAL].m_graph; }

private:
  AnimGraphApplicator *m_agApplicator;
  GraphsMixInfo       m_graphsMixInfo[_AG_NUM];
  int                 m_idleNodeIdx;

  // runtime
  GraphID             m_curGraph; // for Update()

  friend DiInt32 _wholeGraph2UpdateCallback(DiAnGrCallbackParams const &cpParams);
};

} // namespace NScene
