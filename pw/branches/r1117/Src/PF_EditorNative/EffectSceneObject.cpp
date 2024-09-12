#include "stdafx.h"
#include "EffectsPool.h"
#include "EffectSceneObject.h"
#include "../PF_Core/EffectsPool.h"

inline nstl::string ToMBCS( System::String^ str )
{
  if ( !System::String::IsNullOrEmpty( str ) )
  {
    pin_ptr<wchar_t> pString = &str->ToCharArray()[0];
    return NStr::ToMBCS( pString );
  }
  else
  {
    return nstl::string();
  }
}

template <typename T>
inline NDb::Ptr<T> GetObject( libdb::DB::DBID^ dbId )
{
  if ( ( (System::Object^)dbId) != nullptr )
  {
    return NDb::Get<T>( NDb::DBID( ToMBCS( dbId->Name ) ) );
  }
  else
  {
    return nullptr;
  }
}

namespace PF_EditorNative
{
  EffectSceneObject::EffectSceneObject( libdb::DB::DBID^ DbId, libdb::DB::DBID^ DbId2 ) 
  : EditorSceneObject( DbId2 )
  , EffectDbId( DbId )
  {
    effect = new CObj<PF_Core::BasicEffect>();
    Retrieve();
  }

  void EffectSceneObject::Update( float delta )
  {
    if ( !(*effect)->IsInPool() )
      (*effect)->Update(delta);
  }

  void EffectSceneObject::Die()
  {
    (*effect)->Die();
  }

  void EffectSceneObject::Create( System::IntPtr _scene )
  {
    Retrieve();
    EditorSceneObject::Create( _scene );
    if ( so )
    {
      so->Reinit();
      so->UpdateForced();
    }
  }

  void EffectSceneObject::Delete( System::IntPtr _scene )
  {
    if ( !(*effect)->IsInPool() )
      (*effect)->DieImmediate();
    EditorSceneObject::Delete( _scene );
  }

  void EffectSceneObject::Retrieve()
  {
    NDb::Ptr<NDb::EffectBase> pEFFT = GetObject<NDb::EffectBase>( EffectDbId );
    *effect = PF_Core::EffectsPool::Get()->Retrieve( pEFFT );
    so = 0;
    if ( PF_Core::BasicEffectStandalone* eff = dynamic_cast<PF_Core::BasicEffectStandalone*>(effect->GetPtr()) )
    {
      so = eff->GetSceneObject();
      SetEffect( System::IntPtr(so) );
    }
    else if ( PF_Core::BasicEffectAttached* eff = dynamic_cast<PF_Core::BasicEffectAttached*>(effect->GetPtr()) )
    {
      so = new NScene::SceneObject();
      eff->Attach( so );
      //so = eff->GetSceneObject();
      SetEffect( System::IntPtr(so) );
    }
  }
}
