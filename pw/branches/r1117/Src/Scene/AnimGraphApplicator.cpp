#include "stdafx.h"
#include "AnimGraphApplicator.hpp"
#include "Animators.h"
#include "../System/Transform.h"
#include "../System/Spline.h"

#include "../Render/renderer.h"
#include "../Render/renderstates.h"
#include "../Render/renderstatesmanager.h"
#include "../Render/SkeletalMesh.h"
#include "../Render/SkeletalAnimationSampler.h"
#include "../Render/SkeletalAnimationBlender.h"
#include "../Render/SkeletonWrapper.h"
#include "../Render/renderresourcemanager.h"

#include "../System/InlineProfiler.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Uncomment this define to enable some log into "Output"
//#define ENABLE_APP_TEXT_DEBUG
  
#ifdef ENABLE_APP_TEXT_DEBUG
  #define APP_TRACE           NLogg::StreamLocker( GetSystemLog() ) ).GetLog().Trace
#else
  #define APP_TRACE
#endif // ENABLE_APP_TEXT_DEBUG

namespace NScene
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimGraphApplicator::AnimGraphApplicator( const NDb::Skeleton* _model, Render::SkeletalMesh* _pModel )
: pModel( _pModel )
, fSpeedFactor(1.f)
, pInactiveBones(NULL)
{
  Initialize< const NDb::Skeleton*>( _model );
}

AnimGraphApplicator::AnimGraphApplicator( const NDb::DBAnimatedSceneComponent* _model, Render::SkeletalMesh* _pModel )
: pModel( _pModel )
, fSpeedFactor(1.f)
, pInactiveBones(NULL)
{

  Initialize<const NDb::DBAnimatedSceneComponent*>( _model );
}

template <class T>
void AnimGraphApplicator::Initialize(T _model )
{
  Identity(&curPlace);
  Identity(&finalPlace);
  skeletalName = _model->skeletonFileName;
  pModel->Initialize( curPlace, _model->skeletonFileName );

  animations.clear();
	animations.reserve( _model->animations.size() );

	for (int i = 0; i < _model->animations.size(); ++i )
	{
		const NDb::Animation *pAnim = &_model->animations[i];

		if ( !pAnim )
			continue;
		if ( pAnim->animationFileName.empty() )
			continue;

		SSkelAnimDef& def = animations.push_back();
		def.animType = i;
		def.animName = pAnim->name;
		def.pAnim    = Render::RenderResourceManager::LoadSkeletalAnimation( pAnim->animationFileName );
    def.pSampler = new Render::SkeletalAnimationSampler(0, def.pAnim);

    if ( pAnim->name.length() == 0 )
      def.animName = string("UNNAMED ANIM! Source: ") + pAnim->srcFileName;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AnimGraphApplicator::~AnimGraphApplicator()
{
	delete pModel;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::RenderComponent* AnimGraphApplicator::GetRenderable()
{
	return pModel;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const SkeletalAnimationDataWrapper* AnimGraphApplicator::GetAnim( const int &animName ) const
{
	for ( int i = 0; i < animations.size(); ++i )
	{
		if ( animations[i].animType == animName )
			return animations[i].pAnim;
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Time AnimGraphApplicator::GetAnimDuration( const int& animName ) const
{
	const SkeletalAnimationDataWrapper* pAnim = GetAnim( animName );
	if ( !pAnim )
		return 0;
	return pAnim->GetData()->maxTime - pAnim->GetData()->minTime;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimGraphApplicator::FixModelPlacement( const Matrix43& pParentPlacement )
{
	Matrix43 fixedMatrix = pParentPlacement * curPlace;
	pModel->SetWorldMatrix(fixedMatrix);
}

int AnimGraphApplicator::GetAnimIdxByName( const string& name ) const
{
	int animIdx = -1;

	for ( int i = 0; i < animations.size(); i++ )
	{
		if ( name == animations[i].animName )
		{
			animIdx = i;
			break;
		}
	}

	return animIdx;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//1 * (1.0 - a) + 2 * a
void AnimGraphApplicator::BlendTwoBoneAnimations(Matrix43* out, int nJointNumber, Render::SkeletalAnimationSampler *pFirstSampler, Render::SkeletalAnimationSampler *pSecondSampler, float rAlpha)
{
  NI_VERIFY( !pSecondSampler || pFirstSampler->GetJointsCount() == pSecondSampler->GetJointsCount(), "animations appears to be not the same!", return );

  CQuat leftRotation;
  pFirstSampler->GetRotation(nJointNumber, leftRotation );
  CVec3 leftTranslation;
  pFirstSampler->GetTranslation(nJointNumber, leftTranslation );
  CVec3 leftScale;
  pFirstSampler->GetScale(nJointNumber, leftScale );

  if(rAlpha > 0)
  {
    CQuat rightRotation;
    pSecondSampler->GetRotation(nJointNumber, rightRotation );
    CVec3 rightTranslation;
    pSecondSampler->GetTranslation(nJointNumber, rightTranslation );
    CVec3 rightScale;
    pSecondSampler->GetScale(nJointNumber, rightScale );

    CQuat qrot;
    qrot.Interpolate(leftRotation, rightRotation, rAlpha);
    CVec3 trans = Lerp(leftTranslation, rightTranslation, rAlpha);
    CVec3 scale = Lerp(leftScale, rightScale, rAlpha);
  }
  else
  {
    out->Set(leftRotation, leftTranslation, leftScale);
  }
}

void AnimGraphApplicator::RenormalizeMix(MixInfo &mix)
{
  float rSum = 0.0f;

  for(MixInfo::iterator miIt = mix.begin(); miIt != mix.end(); miIt++)
  {
    rSum += miIt->rWeight;
  }
  if(rSum > 0.0f)
  {
    for(MixInfo::iterator miIt = mix.begin(); miIt != mix.end(); miIt++)
    {
      miIt->rWeight = miIt->rWeight / rSum;
    }
  }
  else
  {
    if(mix.begin() != mix.end())
    {
      MixInfo::iterator miIt = mix.begin();
      for(; miIt != mix.end(); miIt++)
      {
        if(!miIt->bHardZeroWeight)
        {
          miIt->rWeight = 1.0f;
          break;
        }
      }
      if(miIt == mix.end())
      {
        mix.begin()->rWeight = 1.0f;
      }
    }
  }

}

//the whole function is logic hack... so...
bool AnimGraphApplicator::IsBoneActive(int nJointNumber, int nSeqIdx, Render::SkeletonWrapper* pSkeleton)
{
  if(pInactiveBones != NULL)
  {
    for(int nI = 0; nI < pInactiveBones->size(); nI++)
    {
      BoneActiveInfo const & pInfo = (*pInactiveBones)[nI];
      if(nSeqIdx == pInfo.nSeqIdx)
      {
        if(pInfo.nBoneIndex == -1)
        {
          char const *pBoneName = pSkeleton->GetJointNameByIndex(nJointNumber);
          if(strcmp(pBoneName, pInfo.cpBoneName) == 0)
          {
            return pInfo.bActive;
          }
        }
        else
        {
          if(pInfo.nBoneIndex == nJointNumber)
          {
            return pInfo.bActive;
          }
        }
      }
    }
  }
  return true;
} 

void AnimGraphApplicator::BlendBoneAnimationsHeavy(Matrix43* out, int nJointNumber)
{
  //prepare mixInfo for partial animation
  MixInfo localMix;
  int nAnimToBlend = mixInfo.size();
  //just do  localMix = mixInfo; fast
  *((MixInfoItem **)&localMix + 0) = (MixInfoItem *)_alloca(sizeof(MixInfoItem) * nAnimToBlend);// _M_start;
  *((MixInfoItem **)&localMix + 1) = *((MixInfoItem **)&localMix + 0) + nAnimToBlend; //_M_finish;
  *((MixInfoItem **)&localMix + 2) = *((MixInfoItem **)&localMix + 1);//_M_end_of_storage;
  memcpy(*((MixInfoItem **)&localMix + 0), (MixInfoItem *)mixInfo.begin(), sizeof(MixInfoItem) * nAnimToBlend);
  int nPair;
  int nI;
  bool bNeedRenormalize = false;
  
  //drop inactive bones
  for(nI = 0; nI < nAnimToBlend; nI++)
  {
    //Render::SkeletalAnimationSampler *pSampler = animations[localMix[nI].nSeqIdx].pSampler;
    //if(!pSampler->IsBoneActive(nJointNumber))
    if(!IsBoneActive(nJointNumber, localMix[nI].nSeqIdx, pModel->GetSkeletonWrapper()))
    {
      NI_ASSERT(localMix[nI].bHardZeroWeight == false, "Logic");
      localMix[nI].rWeight         = 0.0f;
      localMix[nI].bHardZeroWeight = true;
      bNeedRenormalize = true;
    }
  }
  if(bNeedRenormalize)
    RenormalizeMix(localMix);

  Render::SkeletalAnimationSampler *pFirstSampler = animations[localMix.begin()->nSeqIdx].pSampler;
  float                             rBlendSum     = localMix.begin()->rWeight;
  unsigned int                      nJointsNum    = pFirstSampler->GetJointsCount();

  CQuat leftRotation;
  CVec3 leftTranslation;
  CVec3 leftScale;

  //grab sampler info
  pFirstSampler->GetRotation(nJointNumber, leftRotation);
  pFirstSampler->GetTranslation(nJointNumber, leftTranslation);
  pFirstSampler->GetScale(nJointNumber, leftScale);

  CQuat rightRotation;
  CVec3 rightTranslation;
  CVec3 rightScale;
  float rAlpha;

  //build up blending pairs
  for(nPair = 1; nPair < nAnimToBlend; nPair++)
  {
    if(fabs(localMix[nPair].rWeight) <= EPS_VALUE)
      continue;

    //if true it means what we have done before was useless, but we do not care since it is a fail-safe...
    if((rBlendSum + localMix[nPair].rWeight) <= EPS_VALUE)
    {
      //and just skip to next sampler
      continue;
    }


    Render::SkeletalAnimationSampler *pNextSampler = animations[localMix[nPair].nSeqIdx].pSampler;
    NI_VERIFY(nJointsNum == pNextSampler->GetJointsCount(), NStr::StrFmt("Not equal number of bones during blending from %s to %s in %s", animations[localMix.begin()->nSeqIdx].animName.c_str(), animations[localMix[nPair].nSeqIdx].animName.c_str(), skeletalName.c_str()), return;);

    //grab sampler info
    pNextSampler->GetRotation(nJointNumber, rightRotation);
    pNextSampler->GetTranslation(nJointNumber, rightTranslation);
    pNextSampler->GetScale(nJointNumber, rightScale);

    NI_VERIFY((rBlendSum + localMix[nPair].rWeight) > 0.0f, " Zero in division!", return;);
    rAlpha = localMix[nPair].rWeight / (rBlendSum + localMix[nPair].rWeight);
    CQuat qrot;
    qrot.Interpolate(leftRotation, rightRotation, rAlpha);
    leftRotation    = qrot;
    leftTranslation = Lerp(leftTranslation, rightTranslation, rAlpha);
    leftScale       = Lerp(leftScale, rightScale, rAlpha);
    //advance
    rBlendSum += localMix[nPair].rWeight;
  }
  out->Set(leftRotation, leftTranslation, leftScale);

  //clean up
  *((MixInfoItem **)&localMix + 0) = 0;
  *((MixInfoItem **)&localMix + 1) = 0;
  *((MixInfoItem **)&localMix + 2) = 0;

}

void AnimGraphApplicator::BlendBoneAnimationsLight(Matrix43* out, int nJointNumber)
{
  int nPair;
  int nAnimToBlend = mixInfo.size();

  Render::SkeletalAnimationSampler *pFirstSampler = animations[mixInfo.begin()->nSeqIdx].pSampler;
  float                             rBlendSum     = mixInfo.begin()->rWeight;
  unsigned int                      nJointsNum    = pFirstSampler->GetJointsCount();

  //grab sampler info
  CQuat leftRotation;
  CVec3 leftTranslation;
  CVec3 leftScale;

  pFirstSampler->GetRotation(nJointNumber, leftRotation);
  pFirstSampler->GetTranslation(nJointNumber, leftTranslation);
  pFirstSampler->GetScale(nJointNumber, leftScale);

  CQuat rightRotation;
  CVec3 rightTranslation;
  CVec3 rightScale;
  float rAlpha;

  //build up blending pairs
  for(nPair = 1; nPair < nAnimToBlend; nPair++)
  {
    if(fabs(mixInfo[nPair].rWeight) <= EPS_VALUE)
      continue;

    //if true it means what we have done before was useless, but we do not care since it is a fail-safe...
    if((rBlendSum + mixInfo[nPair].rWeight) <= EPS_VALUE)
    {
      //and just skip to next sampler
      continue;
    }


    Render::SkeletalAnimationSampler *pNextSampler = animations[mixInfo[nPair].nSeqIdx].pSampler;
    NI_VERIFY(nJointsNum == pNextSampler->GetJointsCount(), NStr::StrFmt("Not equal number of bones during blending from %s to %s in %s", animations[mixInfo.begin()->nSeqIdx].animName.c_str(), animations[mixInfo[nPair].nSeqIdx].animName.c_str(), skeletalName.c_str()), return;);

    //grab sampler info
    pNextSampler->GetRotation(nJointNumber, rightRotation);
    pNextSampler->GetTranslation(nJointNumber, rightTranslation);
    pNextSampler->GetScale(nJointNumber, rightScale);

    NI_VERIFY((rBlendSum + mixInfo[nPair].rWeight) > 0.0f, " Zero in division!", return;);
    rAlpha = mixInfo[nPair].rWeight / (rBlendSum + mixInfo[nPair].rWeight);
    CQuat qrot;
    qrot.Interpolate(leftRotation, rightRotation, rAlpha);
    leftRotation    = qrot;
    leftTranslation = Lerp(leftTranslation, rightTranslation, rAlpha);
    leftScale       = Lerp(leftScale, rightScale, rAlpha);
    //advance
    rBlendSum += mixInfo[nPair].rWeight;
  }

  out->Set(leftRotation, leftTranslation, leftScale);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimGraphApplicator::ApplyToObject()
{    
  NI_PROFILE_FUNCTION

  unsigned int jointsCount = animations[mixInfo.begin()->nSeqIdx].pSampler->GetJointsCount();

  float rSum = 0;

  for ( MixInfo::iterator miIt = mixInfo.begin(); miIt != mixInfo.end(); ++miIt )
  {
    rSum += miIt->rWeight;

    Render::SkeletalAnimationSampler *pNextSampler = animations[miIt->nSeqIdx].pSampler;
    pNextSampler->SetVPar( miIt->rVPar );
  }

  NI_VERIFY(fabs(rSum - 1.0f) < EPS_VALUE * 100, "Weights are not normalized", RenormalizeMix(mixInfo));

  Matrix43* boneMatrix = pModel->GetSkeletonWrapper()->GetSampledMatrix();

  if ( pInactiveBones )
  {
    for ( unsigned int jointNumber = 0; jointNumber < jointsCount; jointNumber++ )
    {
      BlendBoneAnimationsHeavy(boneMatrix + jointNumber, jointNumber); 
    }
  }
  else
  {
    for ( unsigned int jointNumber = 0; jointNumber < jointsCount; jointNumber++ )
    {
      BlendBoneAnimationsLight(boneMatrix + jointNumber, jointNumber); 
    }
  }

  pModel->SetWorldMatrix(curPlace);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimGraphApplicator::SetVirtualParameterByMix(int nMixIdx, float rT)
{
  int nMixIdxCor = nMixIdx + nCurGraphBaseMixIdx;

  NI_VERIFY(0.0f <= rT && rT <= 1.0f, "Range violation", return;);
  NI_VERIFY(0 <= nMixIdxCor && nMixIdxCor < mixInfo.size(), "Range violation", return;);

  mixInfo[nMixIdxCor].rVPar = rT;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool AnimGraphApplicator::RegisterSequencesToMix(int nSeqsCount, int *npSeqIndices, float *rWeights)
{
  APP_TRACE("AGA: RegSeqToMix(num=%i, %i, %i, %i))", nSeqsCount, npSeqIndices[0], npSeqIndices[1], npSeqIndices[2]);

  NI_VERIFY(nSeqsCount > 0, "Sanity", return false;);
  NI_VERIFY(npSeqIndices != NULL, "Sanity", return false;);

  float rDefW = 1.0f / float(nSeqsCount);
  for(int nI = 0; nI < nSeqsCount; nI++)
  {
    int nAnimationIdx = npSeqIndices[nI];
    NI_VERIFY(nAnimationIdx >= 0, "Animation index should be positive.", nAnimationIdx = 0);
    NI_VERIFY(nAnimationIdx < animations.size(), "Attempt to register animation, that does not exists.", nAnimationIdx = animations.size() - 1;);
    mixInfo.push_back(MixInfoItem(0.0f, nAnimationIdx, rDefW));
    nNextFreeMixIdx++;
  }

  /*
  #ifdef _DEBUG
  float s = 0;
  for(int i = 0; i < nSeqsCount; i++)
  {
  s += rWeights[i];
  // [2008-12-03] Assert commented by EugBel. Weights are checked by AnimGraph and very rarely they are 0.0 (intentionally)
  //NI_ASSERT(rWeights[i] > 0.0f, "Performance sanity. Should not mix if weight is zero.");
  }
  NI_VERIFY(abs(s - 1.0f) < 1e-4, "Weights should be normalized", return;);
  #endif
  */

  APP_TRACE("AGA: SetWeights(num=%i, %5.3lf, %5.3lf, %5.3lf)", nSeqsCount, rWeights[0], rWeights[1], rWeights[2]);
  NI_VERIFY(mixInfo.size() >= nSeqsCount, "Wrong vector size", return true;);
  for(int i = 0; i < nSeqsCount; i++)
  {
    mixInfo[i + nCurGraphBaseMixIdx].rWeight = rWeights[i];
  }
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AnimGraphApplicator::BeginUpdate()
{
  APP_TRACE("AGA: BeginUpdate()");

  // clear MixInfo
  mixInfo.clear();
  nCurGraphBaseMixIdx = 0;
  nNextFreeMixIdx     = 0;
  bInUpdate           = true;
}

void AnimGraphApplicator::EndUpdate()
{
  NI_PROFILE_FUNCTION

  APP_TRACE("AGA: EndUpdate()");

  bInUpdate = false;
  ApplyToObject();
}

bool AnimGraphApplicator::IsInUpdate() const
{
  return bInUpdate;
}

void AnimGraphApplicator::ConsiderNextGraph()
{
  APP_TRACE("AGA: NextGraph()");
  nCurGraphBaseMixIdx = nNextFreeMixIdx;
}

} // end of namespace NScene
