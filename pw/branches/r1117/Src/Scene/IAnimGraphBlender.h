// Author: EugBel
// Date:   06/05/2009

#pragma once

#include "AnimGraphApplicator.hpp"

class DiAnimGraph;

namespace NScene
{

_interface IAnimGraphBlender
{
  virtual AnimationVector const &GetAnimationVector() const=0;
  virtual Time GetAnimDuration(const int& animName) const=0;
  virtual void SetVirtualParameterByMix(int nMixIdx, float rT)=0;
  virtual bool RegisterSequencesToMix(int nSeqsCount, int  *npSeqIndices, float *rWeights)=0;
  virtual DiAnimGraph       *GetMainGraph()=0;
  virtual DiAnimGraph const *GetMainGraph() const=0;
  virtual DiAnimGraph       *GetAdditionalGraph()=0;
  virtual DiAnimGraph const *GetAdditionalGraph() const=0;
  virtual bool            Update(float dt)=0;
  virtual bool SetMainAGTargetNode( int nodeId )=0;
  virtual bool SetAdditionalAGTargetNode( int nodeId )=0;
};

} // namespace NScene
