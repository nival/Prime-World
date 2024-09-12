#pragma once

#include "AsyncMapStartup.h"

namespace
{
  static inline bool ShouldStopLoadingMap(const ::NWorld::MapLoadingControllerPtr& controller)
  {
    if (!controller)
      return false;

    return !controller->CanLoad();
  }
}

// IP stands for Interruption Point
#define MAP_LOADING_SCOPE(controller) const ::NWorld::MapLoadingControllerPtr __mapLoadingController(controller);
#define MAP_LOADING_IP_(...) { if (ShouldStopLoadingMap(__mapLoadingController)) return __VA_ARGS__; }

#define MAP_LOADING_IP MAP_LOADING_IP_(false)
#define MAP_LOADING_IP_VOID MAP_LOADING_IP_()
