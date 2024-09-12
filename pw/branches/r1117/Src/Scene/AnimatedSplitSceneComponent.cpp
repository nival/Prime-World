#include "stdafx.h"
#include "AnimatedSplitSceneComponent.h"
#include "RenderableScene.h"
#include "../Render/SkeletalMesh.h"
#include "../Render/SkeletalAnimationBlender.h"
#include "../Render/SkeletonWrapper.h"
#include "../Render/RenderInterface.h"

namespace NScene
{

namespace
{

struct animationFinder
{
  string st;
  animationFinder(string const &s): st(s) {}
  bool operator()(NDb::Animation const &it)
  {
    return it.name == st;
  }
};

struct animationFinder2
{
  string st;
  animationFinder2(string const &s): st(s) {}
  bool operator()(string &it)
  {
    return it == st;
  }
};

void extractAllAnimNamesFromAG(const NDb::AnimGraphCreator *agCreator, vector<string> &animsInGraph)
{
  // parse the graph and extract anim names into the array
  for (int nodeIdx = 0; nodeIdx < agCreator->macroNodes.size(); nodeIdx++)
  {
    const string *curName = &agCreator->macroNodes[nodeIdx].sequenceName;
    vector<string>::const_iterator anim = find_if(animsInGraph.begin(), animsInGraph.end(), animationFinder2(*curName));
    if(anim == animsInGraph.end())
      animsInGraph.push_back(*curName);
  }
}


}

#pragma warning (disable : 4355)
AnimatedSplitSceneComponent::AnimatedSplitSceneComponent( const NDb::Skeleton* pObject, const Placement& pos )
: AnimatedSceneComponent(pObject, pos)
{
  additionalGraph = DiAnimGraph::CreateByData(pObject->additionalGraph, pObject->animations, agBlender, NULL);
  NI_VERIFY(additionalGraph != NULL, "Failed to create animation graph", return;);
  additionalGraph->Restart( 0, true );
}

AnimatedSplitSceneComponent::AnimatedSplitSceneComponent( const NDb::DBAnimatedSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos, const nstl::string& nodeName )
: AnimatedSceneComponent(pObject, pObj, pos, nodeName)
{
  additionalGraph   = DiAnimGraph::CreateByData(pObject->additionalGraph, pObject->animations, agBlender, NULL);

  additionalExtPars = new DiAnGrExtPars(pObject->additionalGraph, additionalGraph);
  additionalExtPars->applyParamsToGraph();
  additionalGraph->StoreDefaultValues();

  NI_VERIFY(additionalGraph != NULL, "Failed to create animation graph", return;);
  additionalGraph->Restart( 0, true );

  // parse additional (top) animation graph and prepare array of "splitAnimNames"
  vector<string> animsInTopAG;
  extractAllAnimNamesFromAG(pObject->additionalGraph, animsInTopAG);

  if(!pObject->splitBoneName.empty() && agApplicator != NULL)
  {
    unsigned int         nJointIndex; 
    vector<unsigned int> boneChildren;
    vector<unsigned int> boneInactive;
    if(agApplicator->GetModel()->GetSkeletonWrapper()->GetJointIndexByName(pObject->splitBoneName.c_str(), nJointIndex))
    {
      NI_ASSERT(strcmp(agApplicator->GetModel()->GetSkeletonWrapper()->GetJointNameByIndex(nJointIndex), pObject->splitBoneName.c_str()) == 0, NStr::StrFmt( "!! %s", FormatDescription() ) );
      FillBoneChildrenRecursive(nJointIndex, boneChildren);
    }
    //get inactive bones
    for(unsigned int i = 0; i < (unsigned int)agApplicator->GetModel()->GetSkeletonWrapper()->GetBonesCount(); i++)
    {
      if(boneChildren.end() == find(boneChildren.begin(), boneChildren.end(), i))
      {
        boneInactive.push_back(i);
      }
    }
    //for each bone
    for(vector<unsigned int>::iterator it = boneInactive.begin(); it != boneInactive.end(); it++)
    {
      //for each sequence
      for(vector<string>::const_iterator itAN = animsInTopAG.begin(); itAN != animsInTopAG.end(); itAN++)
      {
        vector<NDb::Animation>::const_iterator anim = find_if(pObject->animations.begin(), pObject->animations.end(), animationFinder(*itAN));
        if(anim != pObject->animations.end())
        {
          AnimGraphApplicator::BoneActiveInfo boneInfo;
          boneInfo.bActive    = false;
          boneInfo.cpBoneName = agApplicator->GetModel()->GetSkeletonWrapper()->GetJointNameByIndex(*it);
          boneInfo.nBoneIndex = *it;
          boneInfo.nSeqIdx    = anim - pObject->animations.begin();
          splitInfo.push_back(boneInfo);
        }
      }
    }
    if(!splitInfo.empty())
    {
      agApplicator->SetInactiveBones(&splitInfo);
    }
  }
}

void AnimatedSplitSceneComponent::FillBoneChildrenRecursive(unsigned int nJointIndex, vector<unsigned int> &children)
{
  vector<unsigned int> boneChildren;
  agApplicator->GetModel()->GetSkeletonWrapper()->GetBoneChildren(nJointIndex, boneChildren);
  for(vector<unsigned int>::iterator it = boneChildren.begin(); it != boneChildren.end(); it++)
  {
    FillBoneChildrenRecursive(*it, children);
    children.push_back(*it);
  }
}


AnimatedSplitSceneComponent::~AnimatedSplitSceneComponent()
{
  if (additionalGraph != NULL)
  {
    DiAnimGraph::Destroy(additionalGraph);
    additionalGraph = NULL;
  }
  
  SAFE_DELETE(additionalExtPars);

  splitInfo.clear();
}

void AnimatedSplitSceneComponent::UpdateExtParams()
{
  AnimatedSceneComponent::UpdateExtParams();
  additionalExtPars->applyParamsToGraph();
}

void AnimatedSplitSceneComponent::Reinit()
{
  AnimatedSceneComponent::Reinit();
  additionalExtPars->restart();
}

} // namespace NScene
