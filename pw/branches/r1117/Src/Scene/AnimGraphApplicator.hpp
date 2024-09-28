#pragma once
#include "AnimSequencer.h"
#include "SequencerData.hpp"
#include "Scene.h"
#include "../System/FastMath.h"
#include "../Scene/DBScene.h"
#include "../Render/DBRenderResources.h"
#include "../Render/SkeletonWrapper.h"
#include "AnimSequencer.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{
	class SkeletalAnimationSampler;
	class SkeletalAnimationBlender;
}
struct SkeletalAnimationData;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScene
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef vector<SSkelAnimDef> AnimationVector;
class AnimGraphApplicator: public CObjectBase
{
public:
  
  struct MixInfoItem
  {
    float rVPar;
    int   nSeqIdx;
    float rWeight;
    bool  bHardZeroWeight;
    MixInfoItem(): rVPar(0.0f), nSeqIdx(0), rWeight(1.0f), bHardZeroWeight(false) {}
    MixInfoItem(float rp, int ns, float rw): rVPar(rp), nSeqIdx(ns), rWeight(rw), bHardZeroWeight(false) {}
    MixInfoItem(MixInfoItem const &o): rVPar(o.rVPar), nSeqIdx(o.nSeqIdx), rWeight(o.rWeight), bHardZeroWeight(o.bHardZeroWeight) {}
  };
  struct BoneActiveInfo
  {
    int         nSeqIdx;
    char const *cpBoneName;
    int         nBoneIndex; //if -1, then bone name is used  
    bool        bActive;
    BoneActiveInfo(): nSeqIdx(-1), cpBoneName(NULL), nBoneIndex(-1), bActive(false) {}
    BoneActiveInfo(int _nSeqIdx, char const *_cpBoneName, int _nBoneIndex, bool _bActive): nSeqIdx(_nSeqIdx), cpBoneName(_cpBoneName), nBoneIndex(_nBoneIndex), bActive(_bActive) {}
  };

  typedef vector<MixInfoItem> MixInfo;
private:
	OBJECT_BASIC_METHODS(AnimGraphApplicator)

	Render::SkeletalMesh* pModel;

  nstl::string skeletalName;

  AnimationVector animations;
	float fSpeedFactor;
	Matrix43 curPlace;
	Matrix43 finalPlace;

  MixInfo  mixInfo;
  int      nCurGraphBaseMixIdx;
  int      nNextFreeMixIdx;
  bool     bInUpdate;
  vector<BoneActiveInfo> const* pInactiveBones; 

private:
  AnimGraphApplicator() : pModel(0), fSpeedFactor(1.f), nCurGraphBaseMixIdx(0), nNextFreeMixIdx(0), bInUpdate(false), pInactiveBones(NULL) {Identity(&curPlace);}

  void BlendBoneAnimationsLight(Matrix43* out, int nJointNumber);
  void BlendBoneAnimationsHeavy(Matrix43* out, int nJointNumber);

  void BlendTwoBoneAnimations(Matrix43* out, int nJointNumber, Render::SkeletalAnimationSampler *pFirstSampler, Render::SkeletalAnimationSampler *pSecondSampler, float rAlpha);
  static void RenormalizeMix(MixInfo &mix);
  bool IsBoneActive(int nJointNumber, int nSeqIdx, Render::SkeletonWrapper* pSkeleton);

public:
	AnimGraphApplicator(const NDb::Skeleton* _model, Render::SkeletalMesh* _pModel);
  AnimGraphApplicator(const NDb::DBAnimatedSceneComponent* _model, Render::SkeletalMesh* _pModel);
  virtual ~AnimGraphApplicator();

	Render::SkeletalMesh* GetModel() { return pModel; }
	Render::RenderComponent* GetRenderable();
  
  //access data from inside
  AnimationVector const &GetAnimationVector() const {return animations;}
  const SkeletalAnimationDataWrapper* GetAnim(const int &animName) const;
  Time GetAnimDuration(const int& animName) const;

	const Matrix43& GetFinalPlacement() const { return finalPlace; } 
	const Matrix43& GetCurPlacement() const { return curPlace; } 
  void SetCurPlacement(Matrix43 const& cP) {  curPlace = cP; } 

	int GetAnimIdxByName(const string&) const;

	void FixModelPlacement(const Matrix43& pParentPlacement);

  void SetInactiveBones(vector<BoneActiveInfo> const* _pInactiveBones)
  {
    pInactiveBones = _pInactiveBones;
  }

	template <class T> void Initialize(T _model );

  //true interface for animgraph
  void SetVirtualParameterByMix(int nMixIdx, float rT);
  bool RegisterSequencesToMix(int nSeqsCount, int  *npSeqIndices, float *rWeights);
  void ApplyToObject();

  void BeginUpdate();
  void EndUpdate();
  bool IsInUpdate() const;
  void ConsiderNextGraph();

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
