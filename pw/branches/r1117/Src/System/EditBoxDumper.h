#pragma once

#include "Dumper.h"

namespace NLogg
{

class EditBoxDumper : public CDumper
{
  NI_DECLARE_REFCOUNT_CLASS_1( EditBoxDumper, CDumper );

public:
  EditBoxDumper( CLogger *defaultLogger, HWND ownerWindow );

  void ResizeLogWindow();

protected:
  virtual void OnDump( const SEntryInfo & entryInfo, const char * headerAndText, const char * textOnly );

private:
  HWND ownerWindow;
  HWND logWindow;
  DWORD ownerThread;
  char text[8192];
  size_t textPos;

  threading::Mutex mutex;
};

}
