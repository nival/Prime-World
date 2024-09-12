#include "stdafx.h"
#include "Coordinator/ConfigServiceOption.h"

namespace Coordinator
{
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  TConfigServiceOptions & GetConfigServiceOptions()
  {
    static TConfigServiceOptions g_ConfigServiceOptions;
    return g_ConfigServiceOptions;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // конфиг-команда просто перепихивает описания опций из конфига в глобальный синглтон, а ServerFactory оттуда почитает, когда захочет
  static bool CommandAddServiceOption( const char *name, const vector<wstring> &params ) 
  {
    if ( params.size() >= 1 && ( !params[0].empty() ) )
    {
      SConfigServiceOption* def = new SConfigServiceOption;
      if( def )
      {
        // [0] option name
        def->option = NStr::ToMBCS( params[0] ).c_str();
        GetConfigServiceOptions().push_back( def );

        // [1] service name
        if( params.size() >= 2 && ( !params[1].empty() ) )
        {
          Transport::TServiceId service = NStr::ToMBCS( params[1] ).c_str();
          def->serviceId = service;
        }

        LOG_M(0) << "service_option: add option '" << def->option << "'"
          " for serviceId '" << def->serviceId.c_str() << "' (isGlobalOption=" << def->IsGlobalOption() << ")"
          ;
      }
    }
    else
    {
      LOG_W(0) << "usage: " << name << " <option name: string> [<service_name: 1..16 chars> if option should be passed to specific service only]";
    }

    return true;
  }

  static bool CommandRemoveServiceOption( const char *name, const vector<wstring> &params ) 
  {
    if ( params.size() >= 1 && ( !params[0].empty() ) )
    {
      // [0] option name
      string option = NStr::ToMBCS( params[0] ).c_str();

      for( TConfigServiceOptions::iterator it = GetConfigServiceOptions().begin(); it != GetConfigServiceOptions().end(); )
      {
        if ( (*it)->option == option )
        {
          LOG_M(0) << "removing service option '" << (*it)->option << "'" 
            " for serviceId '" << (*it)->serviceId.c_str() << "'";
          delete *it;
          it = GetConfigServiceOptions().erase( it );
        }
        else
          ++it;
      }
    }
    else
    {
      LOG_W(0) << "usage: " << name << " <option name: string>";
    }

    return true;
  }

}

REGISTER_CMD( add_service_option, Coordinator::CommandAddServiceOption )
REGISTER_CMD( remove_service_option, Coordinator::CommandRemoveServiceOption )
