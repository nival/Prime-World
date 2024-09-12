#include "stdafx.h"
#include "TextComponentBasic.h"
#include "WindowNameMapInterface.h"

NI_DEFINE_REFCOUNT( UI::IWindowNameMapInterface );

namespace UI
{

NNameMap::ReadonlyVariant * TextComponentBasic::GetVariant( const char * name )
{
  if ( !nameMapInterface )
    return 0;

  return nameMapInterface->GetVariant( name, nameMapregistrationEnabled );
}

} //namespace UI
