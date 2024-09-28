#pragma once

#include "System/JobThread.h"

namespace NGameX
{
  class TutorialSplash : public NonCopyable
  {
  public:
    TutorialSplash();
    ~TutorialSplash();
  private:
    const StrongMT<threading::JobThread> thread;
  };
}
