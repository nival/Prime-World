#include "stdafx.h"
#include "NameMappedWindow.h"

namespace UI
{

BEGIN_LUA_TYPEINFO( NameMappedWindow, Window )
END_LUA_TYPEINFO( NameMappedWindow )


NNameMap::ReadonlyVariant * NameMappedWindow::GetVariant( const char * name, bool registerNameMap )
{
  for( const Window * p = this; p; p = p->GetParent() )
  {
    if ( p->GetNameMapRedirect() )
      p = p->GetNameMapRedirect();

    NNameMap::IMap * nmap = p->GetNameMap();
    if( !nmap )
      continue;

    const NNameMap::IMap * constNMap = nmap; //We need const Map ptr to obtain ReadonlyVariants too
    NNameMap::ReadonlyVariant * var = constNMap->GetVariant( name );
    if( !var )
      continue;
    
    if ( registerNameMap )
      GetContext()->RegisterNameMapWindow( nmap, this );

    return var;
  }
  return GetContext()->GetVariant( name );
}



void NameMappedWindow::ResetNameMapAssociations()
{
  GetContext()->UnregisterWindowFromNameMaps( this );
}


} //namespace UI
