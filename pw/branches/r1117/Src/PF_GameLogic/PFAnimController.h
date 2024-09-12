#pragma once

#include "../Scene/DiAnGr.h"
#include "../Scene/DiAnGrNLinker.h"
#include "../System/AutoPtr.h"
#include "../System/FixedString.h"
#include "../Scene/AnimGraphBlender.h"

namespace NScene
{
  class SceneComponent;
} // namespace Scene

namespace NDb
{
  enum   EAnimStates;
  enum   EAnimStatePlayMode;
  struct AnimSet;
} // namespace NDb

namespace NGameX
{
  struct AnimEventParams;

  _interface IAnimEventCallback : public IObjectBase
  {
    virtual void operator () (AnimEventParams const& ) const = 0;
    virtual bool IsEqualTo (IAnimEventCallback const* pOther) const = 0;         
  };

  template<typename T, typename Dummy>
  class AnimEventCallback : public IAnimEventCallback, public CObjectBase
  {
    OBJECT_BASIC_METHODS( AnimEventCallback );

    AnimEventCallback() : pClient( 0 ), pCallback( 0 ) {}

  public:
    typedef void (T::*Callback)(AnimEventParams const&);
    AnimEventCallback(T* pClient, Callback pCallback) : pClient(pClient), pCallback(pCallback) {}
    
    void operator () (AnimEventParams const& context) const 
    { 
      if ( pClient && pCallback )
        (pClient->*pCallback)(context);
    }

    virtual bool IsEqualTo (IAnimEventCallback const* p) const
    {
      if( AnimEventCallback<T, Dummy> const* pOther = p ? dynamic_cast<AnimEventCallback<T, Dummy> const*>(p) : NULL)
        return pOther->pClient == pClient && pOther->pCallback == pCallback;

      return false;
    }
  private:
    T*       pClient;
    Callback pCallback;
  };

  template<typename T>
  class AnimEventCallback<T, void> : public IAnimEventCallback, public CObjectBase
  {
    OBJECT_BASIC_METHODS( AnimEventCallback );

    AnimEventCallback() : pClient( 0 ), pCallback( 0 ) {}

  public:
    typedef void (T::*Callback)();
    AnimEventCallback(T* pClient, Callback pCallback) : pClient(pClient), pCallback(pCallback) {}

    virtual void operator () (AnimEventParams const&) const 
    { 
      if ( pClient && pCallback )
        (pClient->*pCallback)();
    }

    virtual bool IsEqualTo (IAnimEventCallback const* p) const
    {
      if( AnimEventCallback<T, void> const* pOther = p ? dynamic_cast<AnimEventCallback<T, void> const*>(p) : NULL)
        return pOther->pClient == pClient && pOther->pCallback == pCallback;

      return false;
    }
  private:
    T*       pClient;
    Callback pCallback;
  };

    
  template<typename T, typename C>
  IAnimEventCallback* CreateAnimEventCallback(T* pClient, /*typename AnimEventCallback<T, C>::Callback*/  void (T::* pCallback)(C const&) )
  {
    return new AnimEventCallback<T, C>(pClient, pCallback);
  }
  
  template<typename T>
  IAnimEventCallback* CreateAnimEventCallback(T* pClient, /*typename AnimEventCallback<T, C>::Callback*/  void (T::* pCallback)() )
  {
    return new AnimEventCallback<T, void>(pClient, pCallback);
  }

  struct AnimEventParams
  {
    enum EType { Invalid, EnterNode, LeaveNode, ExactParam, Marker }; 

    EType                   type;
    NDb::EAnimStates        state;
    DiUInt32                nodeId;
    float                   fValue;
    string                  sValue;
    NDb::EAnimStatePlayMode mode;
       

    AnimEventParams()
      : type(Invalid)
      , state(NDb::ANIMSTATES_INVALID)
      , fValue(0.0f)
      , mode(NDb::ANIMSTATEPLAYMODE_PLAYBOTH)
      , nodeId(DIANGR_NO_SUCH_ELEMENT)
    {
    }

    AnimEventParams(NDb::EAnimStatePlayMode mode, NDb::EAnimStates state, EType type, float fValue = 0.0f)
      : type(type)
      , state(state)
      , mode(mode) 
      , fValue(fValue)
      , nodeId(DIANGR_NO_SUCH_ELEMENT)
    {
      if( Marker == type )
      {
        NI_ALWAYS_ASSERT("Incompatible ctor for marker animEvent");
        type = Invalid;
      }
    }

    AnimEventParams(NDb::EAnimStatePlayMode mode, string const& sValue)
      : type(Marker)
      , state(NDb::ANIMSTATES_INVALID)
      , fValue(0.0f)
      , mode(mode)
      , sValue(sValue)
      , nodeId(DIANGR_NO_SUCH_ELEMENT)
    {
    }
  };

  class PFAnimController;

  class AnimEvent
  {
    AnimEventParams      params;

    PFAnimController*    pController;
    CObj<IAnimEventCallback> pCallBack;
    int                  setId;
  public:
    AnimEvent(AnimEventParams const& params, DiUInt32 nodeId, PFAnimController* pController, IAnimEventCallback* pCallBack, int setId);
  
    AnimEventParams const& GetParams() const { return params; }

    bool operator == ( AnimEvent const& other) const;
    bool operator != ( AnimEvent const& other) const { return !(*this == other); }

    void Trigger();
  };

  // This class should simplify PFAnimController in future for use in different animation objects.
  // It should contains AnimationGraph
  // but now it used for PlayAnimEffect
  struct IAnimatedClientObject
  {
    virtual unsigned  GetCurrentStateId() const = 0;
    virtual unsigned  GetNextStateId() const = 0;
    virtual unsigned  GetStateIdByName(char const* name) const = 0;
    virtual unsigned  GetNumNodes() const = 0;
    virtual bool      SetAnimStateId(unsigned int nodeId) = 0;
    virtual bool      ReachStateMarker(char const* sMarker, float time, bool preferShortestPath = true, bool preferDefaultNextNode = false) = 0;
    virtual void      SetCinematicPause( bool pause ) = 0;
  };
  
  class PFAnimController : public IAnimatedClientObject
  {
  public:
    enum { MaxAnimSets = 4 };
    typedef NDb::EAnimStatePlayMode ETargetAG;
    //enum ETargetAG { Normal, Upper, Both };

    PFAnimController();
    bool          Initialize( NScene::SceneObject* pSceneObject, bool _isHero );
    bool          Initialize( NScene::IAnimGraphBlender* _blender, NScene::IScene* _scene, bool _isHero );

    void          Update( float timeDiff );
    void          Freeze(const bool freeze, NScene::SceneObject& sceneObject, bool isClientVisible = true );
    void          SetCommandQueueDepth(const float seconds) { queueTimeDepth = max(0.0f, seconds); }

    void          FreezeAG();
    void          UnFreezeAG();

    int           RegisterAnimSet( NDb::AnimSet const* pAnimSet );
    bool          UnRegisterAnimSet( int id );
    bool          ActivateAnimSet( int id );

    int           ReplaceAnimation( NDb::EAnimStates state, char const* name, char const* marker, bool upper, bool allSets = false);
    bool          RollbackAnimation( NDb::EAnimStates state, const int id, bool upper);
    
    void          Cleanup();
    
    bool          RegisterAnimEvent( AnimEventParams params, IAnimEventCallback* pCallback, int setId);

    bool          SetAnimState(NDb::EAnimStates target, ETargetAG targetGraph = NDb::ANIMSTATEPLAYMODE_PLAYBOTH);
    virtual bool  SetAnimStateId(unsigned int nodeId);
		bool          SetAnimStateId(unsigned int nodeId, ETargetAG targetGraph = NDb::ANIMSTATEPLAYMODE_PLAYBOTH);
    bool          SetRandomAnimState(NDb::EAnimStates first, NDb::EAnimStates last, ETargetAG targetGraph = NDb::ANIMSTATEPLAYMODE_PLAYBOTH);

    bool          SetTargetNode( int node ) { return pAG->SetTargetNode( node ); }
    
    virtual bool  ReachStateMarker(char const* sMarker, float time, bool preferShortestPath = true, bool preferDefaultNextNode = false);
    bool          ReachStateMarker( NDb::EAnimStates target, float time, bool preferShortestPath = true, bool preferDefaultNextNode = false, ETargetAG targetGraph = NDb::ANIMSTATEPLAYMODE_PLAYBOTH);

    void          Restart(NDb::EAnimStates target, ETargetAG targetGraph = NDb::ANIMSTATEPLAYMODE_PLAYBOTH);
		void          Restart(const nstl::string& nodeName, ETargetAG targetGraph = NDb::ANIMSTATEPLAYMODE_PLAYBOTH);
    bool          IsValidState(NDb::EAnimStates target, ETargetAG targetGraph = NDb::ANIMSTATEPLAYMODE_PLAYBOTH) const;

    float         GetStateDuration( NDb::EAnimStates state, bool upper = false ) const;
    float         GetStateIdDuration( unsigned int nodeId, bool upper = false ) const;
    float         GetSurfaceSpeed(NDb::EAnimStates state, bool upper = false) const;
    float         GetSurfaceSpeedCurrentNode( bool upper = false ) const;
    
    bool          IsSameInternalState(NDb::EAnimStates l, NDb::EAnimStates r, bool upper = false) const;

    void SetSurfaceSpeedMultiplier( float scale );

    virtual unsigned  GetCurrentStateId() const;
    virtual unsigned  GetNumNodes() const;
    virtual unsigned  GetNextStateId() const;
    virtual unsigned  GetNearestStateId() const;
		const char* GetNearestStateName() const;
    virtual unsigned  GetStateIdByName(char const* name) const;
    unsigned      GetStateId(NDb::EAnimStates state, bool upper = false) const;

    const char*   GetStateMarker( NDb::EAnimStates state, bool upper = false ) const;
    ETargetAG     GetStatePlayMode( NDb::EAnimStates state ) const;
    
    int           GetCurrentSetId() const { return activeAnimSet; }
    static bool   IsValidStateId(unsigned id);

    float GetFirstUpdateTime() { return firstUpdateTime; }

    virtual void  SetCinematicPause( bool pause ) {}
  protected:
    void          ClearCommandQueue() { commandQueue.clear(); }
  private:
    typedef DiAnGrNamesIDLinker<NDb::EAnimStates> TLinker;
    
    NScene::IScene*           pIScene;
    DiAnimGraph*              pAG;
    DiAnimGraph*              pUpperAG;
    NScene::IAnimGraphBlender* pAGBlender;
    DiAnGrExtPars*            pAGExtParams;
    DiAnGrExtPars*            pUpperAGExtParams;

    struct NodeSurfaceInfo
    {
      DiFloat speed;
      DiVec2  surfSpeed;
      NodeSurfaceInfo( DiFloat _speed = 0.0f, DiVec2 _surfSpeed = DiVec2( 0.0f, 0.0f ) ) : speed( _speed ), surfSpeed( _surfSpeed ) {}
    };
    
    struct AnimSet
    {
      enum{ stateMissing = 0x0fffffff};
      
      bool                                                             isValid;
      AutoPtr<TLinker>                                                 pLinker;
      StaticArray<FixedString<32>,    NDb::KnownEnum<NDb::EAnimStates>::sizeOf> markers;
      
      AutoPtr<TLinker>                                                 pUpperLinker;
      StaticArray<FixedString<32>,    NDb::KnownEnum<NDb::EAnimStates>::sizeOf> upperMarkers;

      StaticArray<ETargetAG, NDb::KnownEnum<NDb::EAnimStates>::sizeOf> permissions;
      list<AnimEvent>                                                  animEvents;

      vector<NodeSurfaceInfo> nodesBaseSpeedInfo;
      float                   surfaceSpeedMultiplier;
      vector<NodeSurfaceInfo> upperNodesBaseSpeedInfo;
      float                   upperSurfaceSpeedMultiplier;

      AnimSet() : isValid(false)
      {
        Reset();
      }

      void Reset();
    };

    struct AnimReplaceData
    {
      int              id;  

      DiUInt32         stateId;
      FixedString<32> marker;
      int              setId;

      AnimReplaceData() : id(-1), stateId((DiUInt32)(-1)), setId(-1) {}
    };
    
    struct StateReplacement
    {
      int                     lastNormalUsed;
      vector<AnimReplaceData> normal;
      
      int                     lastUpperUsed;
      vector<AnimReplaceData> upper;

      StateReplacement() : lastNormalUsed(-1), lastUpperUsed(-1) {}
    };

    StaticArray<StateReplacement, NDb::KnownEnum<NDb::EAnimStates>::sizeOf> replacedAnims;

    StaticArray<AnimSet, MaxAnimSets> animSets;
    int activeAnimSet;

    int            FindEmptyAnimSet();
    AnimSet*       GetActiveAnimSet();
    AnimSet const* GetActiveAnimSet() const; 

    struct Command
    {
      enum ECommandType{ CT_Invalid, CT_SetState, CT_ReachMarker, CT_Nope } ;
      
      ECommandType             type;
      ETargetAG                mode;
      ETargetAG                permission; 

      pair<DiUInt32, DiUInt32> stateIds; 
      pair<string,   string>   markers;
      float                    timeOffset;
      bool                     preferShortestPath;
      bool                     preferDefaultNextNode; 

      NScene::Time             time;
      NScene::Time             duration;

      explicit Command() 
        : type(CT_Invalid)
        , mode(NDb::ANIMSTATEPLAYMODE_PLAYBOTH)
        , permission(NDb::ANIMSTATEPLAYMODE_PLAYBOTH)
        , stateIds(make_pair(DIANGR_NO_SUCH_ELEMENT, DIANGR_NO_SUCH_ELEMENT))
        , timeOffset(-1.0f)
        , time(-1.0f)
        , preferShortestPath(true)
        , preferDefaultNextNode(false) {}
    };
    
    typedef nstl::vector<Command> TCommandQueue;
    TCommandQueue commandQueue;
    bool          freezed;
    float         queueTimeDepth;
    float         firstUpdateTime;
    bool          isHero;

    pair<DiUInt32, DiUInt32> GetStateIDs( NDb::EAnimStates state, bool checkReplaced = true ) const;
    bool                     SetAnimStateInternal(pair<DiUInt32, DiUInt32> const& ids, ETargetAG target);
    bool                     ReachStateMarkerInternal(pair<string, string> const& markers, float time, bool preferShortestPath, bool preferDefaultNextNode, ETargetAG targetGraph, ETargetAG permission);
    AnimReplaceData const*   GetStateReplacement(NDb::EAnimStates state, bool upper) const;


    bool           RegisterAnimEventInternal(AnimEventParams const& params, IAnimEventCallback* pCallback, int setId);
    static DiInt32 AnimEventDispatcher(DiAnGrCallbackParams const &cpParams);

	  void TryDeleteRepeatedCommands();
	  bool IsSameCommand( Command& cmd1, Command& cmd2 );
#ifndef _SHIPPING
    void DebugPrintAllCommands();
#endif
  };

} // namespace NGameX

