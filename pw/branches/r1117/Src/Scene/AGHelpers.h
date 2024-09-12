#pragma once

namespace test
{

  struct SkeletonInfo
  {
    nstl::vector<int> animations;
    nstl::vector<float> weights;
    nstl::vector<float> progresses;
    int size() const { return min(min(animations.size(), weights.size()), progresses.size()); } 
  };

  struct AnimationDataHolder
  {
    nstl::vector<NDb::Animation> animations;
    nstl::vector<NScene::Time> durations;
    void AddAnimation(const char* name, NScene::Time duration)
    {
      NDb::Animation animation;
      animation.name = name;
      bool isFind = false;
      for ( int i = 0; i < animations.size(); i++ )
      {
        if ( animations[i].name == animation.name )
        {
          isFind = true;
          break;
        }
      }
      if ( !isFind )
      {
        animations.push_back(animation);
        durations.push_back(duration);
      }
    }

    void Fill( const NDb::AnimGraphCreator* creator )
    {
      for ( int i = 0; i < creator->macroNodes.size(); i++ )
      {
        AddAnimation( creator->macroNodes[i].sequenceName.c_str(), 1.5f );
      }
    }
  };

  struct MockAnimGraphBlender : NScene::IAnimGraphBlender
  {
    const AnimationDataHolder& data;
    MockAnimGraphBlender(const AnimationDataHolder& _data):
    data(_data)
    {

    }
    virtual NScene::AnimationVector const &GetAnimationVector() const { return animations; }
    virtual NScene::Time GetAnimDuration(const int& animName) const 
    { 
      return data.durations[animName];
    }
    virtual void SetVirtualParameterByMix(int nMixIdx, float rT) 
    {
      frames[frames.size()-1].progresses[nMixIdx] = rT;
    }
    virtual bool RegisterSequencesToMix(int nSeqsCount, int  *npSeqIndices, float *rWeights)  
    { 
      SkeletonInfo info;
      for (int i=0;i<nSeqsCount;++i)
      {
        info.animations.push_back(npSeqIndices[i]);
        info.weights.push_back(rWeights[i]);
      }
      info.progresses.resize(nSeqsCount);
      frames.push_back(info);
      return true; 
    }
    virtual DiAnimGraph       *GetAdditionalGraph()  { return 0; }
    virtual DiAnimGraph const *GetAdditionalGraph() const { return 0; }
    virtual DiAnimGraph       *GetMainGraph()  { return 0; }
    virtual DiAnimGraph const *GetMainGraph() const { return 0; }
    virtual bool            Update(float dt) { return false; }
    virtual bool SetMainAGTargetNode( int nodeId ) { return false; }
    virtual bool SetAdditionalAGTargetNode( int nodeId ) { return false; }

    const SkeletonInfo& GetLastFrame() const { return frames[frames.size()-1]; }

    NScene::AnimationVector animations;
    nstl::vector<SkeletonInfo> frames;
  };

  NDb::AnGrMacronode& CreateMacroNode( NDb::AnimGraphCreator& creator, const nstl::string& animname, float animDuration )
  {
    NDb::AnGrMacronode node;
    node.nodeName = animname;
    node.nodeType = NDb::ANGRNODETYPE_NORMAL;
    node.nextNode = animname;
    node.surfSpeedX = 0.f;
    node.surfSpeedY = 0.f;
    {
      node.sequenceName = animname;
      node.startPar.value = 0.f;
      node.stopPar.value = 1.f;
      node.speed.value = 1.f;
    }
    creator.macroNodes.push_back(node);
    return creator.macroNodes[creator.macroNodes.size()-1];
  }

  NDb::AnGrFlMultiTransaction& CreateTransaction( NDb::AnGrMacronode& node, const nstl::string& targetNode, float duration )
  {
    NDb::AnGrFlMultiTransaction tr;
    tr.targetNode = targetNode;
    tr.probability = 0.f;
    {
      NDb::AnGrFlTransaction t;
      t.blending = NDb::ANGRTRANSACTIONUPDATE_POSETOANIM;
      t.kind = NDb::ANGRTRANSACTIONKIND_UNIFORM;
      t.parA.value = MAX_FLOAT;
      t.parB.value = MAX_FLOAT;
      t.fromMin.value = 0.f;
      t.fromMax.value = 1.f;
      t.toParam.value = 0.f;
      t.duration = duration;
      tr.parameters = t;
    }
    node.simpleTransactions.push_back(tr);
    return node.simpleTransactions[node.simpleTransactions.size()-1];
  }

}