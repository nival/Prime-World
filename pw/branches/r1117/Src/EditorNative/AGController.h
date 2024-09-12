#pragma once

#include "Utility.h"
#include "../Scene/AnimatedSceneComponent.h"
#include "EditorSceneComponent.h"
#include "SimpleEditorScene.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

public enum class AnimGraphType  
{ 
	Main = 0, 
	Additional = 1
};

public ref class AGEntity sealed
{
public:
  int pNodeIdx;
  int pFromNodeIdx;
  int pToNodeIdx;
};

public ref class AnimInfo sealed
{
public:
  System::String^ animName;
  float animLength;
  int animFrames;
};

public ref class AGController sealed
{
  NScene::AnimGraphController* agc;
  NScene::AnimatedSceneComponent* sc;
  ::DiAnimGraph* mainAG;
  ::DiAnimGraph* additionalAG;
  ::DiAnimGraph* fakeAG;
  ::DiAnGrExtPars* extPars;
  libdb::DB::DBID^ dbid;
  libdb::DB::DBID^ animatedSceneComponentdbid;
  System::Collections::Generic::IList<AnimInfo^>^ animInfos;
  bool isAGMode;
  bool isValid;
  EditorNative::SimpleEditorScene^ scene;
  EditorSceneComponent^ esc;

public:
  AGController( NScene::AnimatedSceneComponent* _sc, AnimGraphType agType, EditorNative::SimpleEditorScene^ _scene );
  AGController( EditorSceneComponent^ _sc, AnimGraphType agType, EditorNative::SimpleEditorScene^ _scene );
  ~AGController()
  {
    this->!AGController();
  }
  !AGController()
  {
    delete agc;
    agc = 0;
  }

  void SetNodeInfo( int nodeIdx, DBTypes::AnGrMacronode^ nodeInfo );
  void SetSequenceInfo( int nodeIdx, int seqIdx, DBTypes::AnGrFormula^ startPar, DBTypes::AnGrFormula^ stopPar, 
    DBTypes::AnGrFormula^ speed, String^ name );

  void SetFlMultiTransactionsInfo( int fromNodeIdx, int toNodeIdx, DBTypes::AnGrFlMultiTransaction^ transactionInfo );
  void SetFlTransactionsInfo( int fromNodeIdx, int toNodeIdx, int partIdx, DBTypes::AnGrFlTransaction^ partInfo );

  void PlayNodes( System::Collections::Generic::IList<int>^ nodeIndices, float loopTime );
  void SetGlobalSpeed( float speed );

  void SetVirtualParameter( int nodeIdx, float value );
  void ResetVirtualParameter();

  void SetInvalid() 
  { 
    agc = 0;
    dbid = libdb::DB::DBID::Empty;
    isValid = false;
  }
  bool IsValid()
  {
    return isValid;
  }

  AGEntity^ GetActiveEntity();
  int  GetCurTargetNode();

  DBTypes::Vec2^ GetCurNodeSurfSpeed();

  property libdb::DB::DBID^ DBID
  {
    libdb::DB::DBID^ get()
    {
      return dbid;
    }
  }

  libdb::DB::DBID^ GetAnimatedSceneComponentDBID()
  {
    return animatedSceneComponentdbid;
  }

  System::Collections::Generic::IList<AnimInfo^>^ GetAnimInfos()
  {
    return animInfos;
  }

  void SwitchToAnims();
  void SwitchToAG();

  void Reset( EditorSceneComponent^ _sc, AnimGraphType agType )
  {
    esc = _sc;
    Reset( _sc->sceneComponent, agType );
  }
  void Reset( NScene::SceneComponent* _sc, AnimGraphType agType );

};


}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative