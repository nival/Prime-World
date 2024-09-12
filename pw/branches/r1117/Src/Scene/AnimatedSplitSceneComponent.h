// Author: EugBel
// Date: 22/05/2009

#pragma once
#include "AnimatedSceneComponent.h"

namespace NScene
{

class AnimatedSplitSceneComponent : public AnimatedSceneComponent
{
  DiAnimGraph                                 *additionalGraph;
  DiAnGrExtPars                               *additionalExtPars;

  vector<AnimGraphApplicator::BoneActiveInfo> splitInfo;

public:

	AnimatedSplitSceneComponent( const NDb::Skeleton* pObject, const Placement& pos );
	AnimatedSplitSceneComponent( const NDb::DBAnimatedSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos, const nstl::string& nodeName );
  virtual ~AnimatedSplitSceneComponent();

  virtual ::DiAnimGraph          *GetAdditionalAnimGraph()       { return additionalGraph; }
  virtual ::DiAnimGraph const    *GetAdditionalAnimGraph() const { return additionalGraph; }

  virtual ::DiAnGrExtPars        *GetAdditionalExtPars()       {return additionalExtPars;}
  virtual ::DiAnGrExtPars const  *GetAdditionalExtPars() const {return additionalExtPars;}

  virtual void Reinit();
protected: 
  virtual void UpdateExtParams();
private:
  void                       FillBoneChildrenRecursive(unsigned int nJointIndex, vector<unsigned int> &children);
};


}

