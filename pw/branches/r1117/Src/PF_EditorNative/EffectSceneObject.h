#pragma once
#include "../PF_Core/EffectsPool.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_EditorNative
{

public ref class EffectSceneObject : public EditorNative::SceneElements::SceneObjects::EditorSceneObject
{
  libdb::DB::DBID^ EffectDbId;
  CObj<PF_Core::BasicEffect>* effect;
  NScene::SceneObject* so;
  void Retrieve();

public:
  EffectSceneObject( libdb::DB::DBID^ DbId, libdb::DB::DBID^ DbId2 );
  ~EffectSceneObject()
  {
    this->!EffectSceneObject();
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  !EffectSceneObject()
  {
    //delete effect;
  }
  virtual void Update( float delta ) override;
  virtual void Die() override;
  virtual void Create( System::IntPtr _scene ) override;

  virtual void Delete( System::IntPtr _scene ) override;
};

}