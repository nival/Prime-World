#pragma once

#include "Utility.h"

namespace EditorNative {
namespace SceneElements {
namespace SceneObjects {

ref class EditorSceneObject;

public ref class EditorSceneComponent sealed
{
public:
  NScene::SceneComponent* sceneComponent;
  EditorSceneObject^ sceneObject;
  System::Collections::Generic::List<EditorSceneComponent^>^ brothers;
  EditorSceneComponent^ child;

  libdb::DB::DBID^ GetDBID()
  {
    return libdb::DB::DBID::FromString( FromMBCS(NDb::GetFormattedDbId(sceneComponent->GetDBID())) );
  }

  void SetHide( bool val )
  {
    sceneComponent->SetHide( val );
  }

  System::String^ FormatComponentName()
  {
    libdb::DB::DBID^ dbid = GetDBID();
    if(dbid == libdb::DB::DBID::Empty)
    {
      return gcnew System::String("null");
    }
    libdb::DB::DBPtr<libdb::DB::DBResource^>^ resource = libdb::DB::DataBase::Get<libdb::DB::DBResource^>(dbid);
    if ( resource == nullptr || resource->Get() == nullptr )
    {
      return dbid->FileName;
    }
    System::Type^ type = resource->Get()->GetType();
    System::String^ inlined;
    if ( dbid->IsInlined )
    {
      inlined = gcnew System::String("Inlined, ");
    }
    else
    {
      inlined = gcnew System::String("");
    }
    return type->Name + ", " + inlined + dbid->FileName;
  }

  bool IsProxy()
  {
    libdb::DB::DBResource^ resource = GetDBResource();

    if(resource == nullptr)
    {
      return false;
    }

    return DBTypes::DBSceneComponent::typeid->IsInstanceOfType( resource ); 
  }

  System::Collections::Generic::List<System::String^>^ GetJointsList()
  {
    System::Collections::Generic::List<System::String^>^ names = gcnew System::Collections::Generic::List<System::String^>();
    if (sceneComponent)
    {
      const nstl::vector<nstl::string>& joints = sceneComponent->GetJointsList();
      for ( int i = 0; i < joints.size(); i++ )
      {
        names->Add( FromMBCS( joints[i] ) );
      }
    }
    return names;
  }

private: 

  libdb::DB::DBResource^ GetDBResource()
  {
    libdb::DB::DBID^ dbid = GetDBID();
    
    if(dbid != libdb::DB::DBID::Empty)
    {
      libdb::DB::DBPtr<libdb::DB::DBResource^>^ ptr = libdb::DB::DataBase::Get<libdb::DB::DBResource^>(dbid);
      
      if ( ptr != nullptr) 
        return ptr->Get();      
    }

    return nullptr;
  }

};

}	// namespace SceneObjects
}	// namespace SceneElements
}	// namespace EditorNative
