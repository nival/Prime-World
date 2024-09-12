#pragma once

namespace EditorNative {
namespace DebugVars {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
public ref class EditorDebugVar sealed
{
private:
	NDebug::IDebugVar* pDebugVar;
  System::String^ name;
	System::String^ value;
	bool isWarning;

	EditorDebugVar( NDebug::IDebugVar* pDebugVar );

public:
	property System::String^ Name { System::String^ get() { return name; } }
  property System::String^ Value { System::String^ get() { return value; } }
	property bool IsWarning { bool get() { return isWarning; } }

  void Update();

  static System::Collections::Generic::List<System::String^>^ GetDebugVars();
  static EditorDebugVar^ FindDebugVar( System::String^ name );
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace DebugVars
}	// namespace EditorNative
