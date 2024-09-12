#include "stdafx.h"
#include "EditorDumper.h"
#include "StringUtils.h"
#include "../System/SystemLog.h"
#include "../System/AssertDumper.h"

using namespace libdb::Diagnostics;

namespace EditorNative
{

public ref class EditorDumperInit
{
  EditorDumper * editorDumper;
public:
  EditorDumperInit()
  {
    editorDumper = new EditorDumper( &GetSystemLog() );
  }

  ~EditorDumperInit()
  {
    this->!EditorDumperInit();
  }

  !EditorDumperInit()
  {
    GetSystemLog().RemoveDumper( editorDumper );
    editorDumper = 0;
    //NO delete. SystemLog (ChannelLogger) object will take care
    //delete editorDumper;
  }
};


void EditorDumper::OnDump( const NLogg::SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly )
{
  if ( !entryInfo.filename || !textOnly )
    return;

  threading::MutexLock lock( mutex );

  switch ( entryInfo.level )
  {
  case NLogg::LEVEL_MESSAGE:
    Log::Trace( EditorNative::FromMBCS( entryInfo.filename ), entryInfo.line, Log::Level::Information, EditorNative::FromMBCS( textOnly ) );
    break;
  case NLogg::LEVEL_DEBUG:
  case NLogg::LEVEL_UNDEFINED:
  case NLogg::LEVEL_ASSERT:
    Log::Trace( EditorNative::FromMBCS( entryInfo.filename ), entryInfo.line, Log::Level::Debug, EditorNative::FromMBCS( textOnly ) );
    break;
  // under editor and Visual Studio we catch assert twice in this line and in line were assert occured
  //case NLogg::LEVEL_ASSERT:
  //  Log::Trace( EditorNative::FromMBCS( entryInfo.filename ), entryInfo.line, Log::Level::Assert, EditorNative::FromMBCS( textOnly ) );
  //  break;
  case NLogg::LEVEL_WARNING:
    Log::Trace( EditorNative::FromMBCS( entryInfo.filename ), entryInfo.line, Log::Level::Warning, EditorNative::FromMBCS( textOnly ) );
    break;
  case NLogg::LEVEL_CRITICAL:
    Log::Trace( EditorNative::FromMBCS( entryInfo.filename ), entryInfo.line, Log::Level::Error, EditorNative::FromMBCS( textOnly ) );
    break;
  }
}

} // namespace EditorNativez