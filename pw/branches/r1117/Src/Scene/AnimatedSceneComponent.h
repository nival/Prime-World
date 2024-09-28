#pragma once
#include "SceneComponent.h"
#include "Scene.h"
#include "DiAnGr.h"
#include "DiAnGrExtPars.h"
#include "DiAnGrMarker.h"
#include "AnimGraphApplicator.hpp"
#include "AnimGraphBlender.h"
#include "AnimGraphController.h"
#include "DiAnGrNLinker.h"

namespace NScene
{

const int s_standardAnimationFPSInMaya = 30; // 30 frames per second. Ivn said to have this constant here

enum AgNode;

class AnimatedSceneComponent : public SceneComponent
{
public:

  struct AnimationCallbackHelper
  {
    AnimatedSceneComponent* component;
    int skinID;

    AnimationCallbackHelper() : component(0), skinID(-1) {}
  };

protected:
	NDb::Ptr<NDb::Skeleton> pDBObject;
	NDb::Ptr<NDb::DBAnimatedSceneComponent> pDBObject2;

	static const unsigned int maxSlotsCount = 16;
	static const unsigned int maxSkinsCount = 64;

	unsigned int fragments[ maxSkinsCount ][ maxSlotsCount ];
	unsigned int fragmentsCount[ maxSkinsCount ];

  DiAnimGraph                 *animGraph;
  DiAnGrExtPars               *extPars;
  AnimGraphApplicator         *agApplicator;
  AnimGraphBlender            *agBlender;

  typedef nstl::vector<AnimationCallbackHelper>  AnimationCallbackHelpers;
  AnimationCallbackHelpers animationCallbackHelpers; 

	void  AnimationKeyFrame();
	int   GetKeyFrame( int curAnim, float animTime, float animLastTime );
  template <class T> void  InternalConstructor( const T* pObject, const Placement& pos, const nstl::string& nodeName );
  virtual void UpdateExtParams();
public:	
  virtual DiAnimGraph* GetAG(bool mainGraph) { return mainGraph ? GetMainAnimGraph() : GetAdditionalAnimGraph(); } ///eugbel///

	typedef NDb::DBAnimatedSceneComponent NDbType;

	AnimatedSceneComponent( const NDb::Skeleton* pObject, const Placement& pos );
	AnimatedSceneComponent( const NDb::DBAnimatedSceneComponent* pObject, const NDb::AttachedSceneComponent* pObj, const Placement& pos, const nstl::string& nodeName );
  virtual ~AnimatedSceneComponent();

	virtual void Update( UpdatePars &pars, const Placement& parentPos, float timeDiff );
  virtual void RenderToQueue( class Render::BatchQueue& queue, const struct Render::SceneConstants& sceneConstants );

  virtual void OnAfterAdded(class SceneObject *pObject);
  virtual void OnAfterAttached();

  virtual void Init();
  virtual void Reinit();
	virtual void OnTimeLooped(float time2StartWith);

	virtual void Attach( SceneComponent* toadd );

	void ShowSkin( const string& skinName, bool show );
	void ShowSkin( int skinIdx, bool show );
  void EnableSkin( int skinIdx, bool val );
	bool IsSkinActive( int skinIdx );
	void TurnOffSkins();
	void StartAnimation( int animationIndex );
  void StartAnimSequence( int animationIndex );
	void StartAnimation( string const& animName, EAnimAction mode = AA_ONESHOT);
	bool IsAnimationPlaying( string const& animName ) const;
  nstl::vector<int> GetActiveSkins();
  nstl::vector<int> GetPassiveSkins();
  nstl::vector<nstl::string> GetAnimations();
  const nstl::vector<NDb::Animation>& GetDBAnimations();

	virtual void SetNodeName( const nstl::string& nodeName );

	float GetAnimDuration( int animIdx ) const;
  int   GetAnimDurationInFrames( int animIdx ) const;

  void                          SetAnimGraphs( DiAnimGraph* main, DiAnimGraph* additional, DiAnGrExtPars *firstGraphExtPars );
  void                          SetFakeAnimGraphs( DiAnimGraph* main, DiAnimGraph* additional, DiAnGrExtPars *firstGraphExtPars );
  ::DiAnimGraph                 *GetMainAnimGraph()             { return animGraph; }
  ::DiAnimGraph   const         *GetMainAnimGraph() const       { return animGraph; }
  virtual ::DiAnimGraph         *GetAdditionalAnimGraph()       { return NULL; }
  virtual ::DiAnimGraph const   *GetAdditionalAnimGraph() const { return NULL; }

  ::DiAnGrExtPars                *GetExtPars()       {return extPars;}
  ::DiAnGrExtPars const          *GetExtPars() const {return extPars;}
  virtual ::DiAnGrExtPars        *GetAdditionalExtPars()       {return NULL;}
  virtual ::DiAnGrExtPars const  *GetAdditionalExtPars() const {return NULL;}

  AnimGraphApplicator        *GetGraphApplicator()       {return agApplicator;}
  AnimGraphApplicator const  *GetGraphApplicator() const {return agApplicator;}
  IAnimGraphBlender          *GetGraphBlender()          {return agBlender;   }
  IAnimGraphBlender const    *GetGraphBlender()    const {return agBlender;   }

  void                       FillBoneChildrenRecursive(unsigned int nJointIndex, vector<unsigned int> &children);

  AnimGraphController       *CreateAnimGraphController( int agIdx ); // 0 - main graph, 1 - additional graph

	virtual bool RetrieveJointPlacement(const string& name, Placement &pos);

	virtual float GetPureAnimLength() /*const*/;

  virtual void ForAllMaterials(Render::IMaterialProcessor &proc);

  virtual vector<string> GetJointsList() const;

  NDb::Ptr<NDb::DBAnimatedSceneComponent> GetDBComponent() const { return pDBObject2; }

  virtual float GetCurTime() const;
  void ResetCurAnimTime() { timeController.SetPureAnimationLength(GetPureAnimLength()); oldTime = GetAnimatedTime(); }
  void SetCurAnimIdx( int idx ) { curAnim = idx; }
  void SetAnimSpeed( float val );

  virtual void ProcessExternalEvent(const char *eventName);

private:
  void RegisterSkinEvents();

  int curAnim;
  float oldTime;
  float animSpeed;
};


}

