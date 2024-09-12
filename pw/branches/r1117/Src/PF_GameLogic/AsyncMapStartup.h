#pragma once

#include "System/JobThread.h"

namespace NWorld
{
  class MapLoadingJob;

  class MapLoadingController
    : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1(MapLoadingController, BaseObjectMT);
  public:
    virtual bool CanLoad() const = 0;
  protected:
    MapLoadingController() {}
  };

  typedef StrongMT<MapLoadingController> MapLoadingControllerPtr;

  struct MapLoader
  {
    static bool IsThreaded();

    static threading::JobThread* CreateMapLoadingThread(MapLoadingJob* const job);
  };
}
