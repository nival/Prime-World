#pragma once
#include "Network/TransportTypes.h"

namespace Coordinator
{
  struct SConfigServiceOption
  {
    Transport::TServiceId serviceId; 
    nstl::string option;

    // признак опции, которые нужно раздавать всем сервисам (не одному конкретному)
    bool IsGlobalOption() const { return serviceId.empty() || ("all" == NStr::GetLower( string(serviceId.c_str()) )); } 
  };

  // Global singleton vector <serviceName, option>
  typedef vector<SConfigServiceOption*> TConfigServiceOptions;
  TConfigServiceOptions & GetConfigServiceOptions();
}
