#include "stdafx.h"
#include "EditorDebugVars.h"
#include "StringUtils.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Collections::Generic;

using namespace EditorNative::DebugVars;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorDebugVar::EditorDebugVar( NDebug::IDebugVar* _pDebugVar ) : pDebugVar( _pDebugVar )
{
  name = gcnew System::String( pDebugVar->GetName() );
  value = System::String::Empty;
  isWarning = false;
  Update();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EditorDebugVar::Update()
{
  wchar_t buffer[128];
  const int length = pDebugVar->FormatValue( buffer, 128 );
  value = gcnew System::String( buffer, 0, length );
  isWarning = pDebugVar->IsWarning();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void __stdcall CollectDebugVar( const wchar_t* screen, const wchar_t* name, const NDebug::IDebugVar* var, void* pData )
{
  vector<wstring>* names = (vector<wstring>*)pData;
  names->push_back( name );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
System::Collections::Generic::List<System::String^>^ EditorDebugVar::GetDebugVars()
{
  vector<wstring> names;
  NDebug::ProcessAllDebugVars( CollectDebugVar, &names );

  System::Collections::Generic::List<System::String^>^ result = gcnew System::Collections::Generic::List<System::String^>();
  for( vector<wstring>::const_iterator it = names.begin(); it != names.end(); ++it )
    result->Add( gcnew System::String( it->c_str() ) );

  return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EditorDebugVar^ EditorDebugVar::FindDebugVar( System::String^ name )
{
  NDebug::IDebugVar* var = NDebug::FindDebugVar( ToUnicodeCS( name ).c_str() );
  if ( var == 0 )
    return nullptr;

  return gcnew EditorDebugVar( var );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

