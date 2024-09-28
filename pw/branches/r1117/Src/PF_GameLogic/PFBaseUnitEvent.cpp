#include "stdafx.h"
#include "PFBaseUnitEvent.h"
#include "PFBaseUnit.h"
#include "LuaScript.h"
#include "PFAIContainer.h"

namespace NWorld
{

int PFBaseUnitPickupEvent::PushArgsForScript( lua_State *L ) const
{
  luaValueSetter::Set( L, scriptName );
  return 1;
}

bool PFBaseUnitApplicatorEvent::IsEventHostileTo( PFBaseUnit const* pListenerUnit ) const
{
  return IsValid( pAppl->GetAbilityOwner() ) ? pAppl->GetAbilityOwner()->GetFaction() != pListenerUnit->GetFaction() : false;
}


int PFBaseUnitUseAbilityEvent::PushArgsForScript( lua_State *L ) const
{
  NDb::DBID id = pAbility->GetData()->GetDBDesc()->GetDBID();
  luaValueSetter::Set( L, id.GetFormatted() );
  luaValueSetter::Set( L, pAbility->GetTarget() );
  return 2;
}

int PFBaseUnitAbilityStartEvent::PushArgsForScript( lua_State *L ) const
{
  if ( !IsValid(pAbility) || !pAbility->GetData() || !pAbility->GetData()->GetDBDesc() )
  {
    luaValueSetter::Set( L, "" );
    return 1;
  }

  NDb::DBID id = pAbility->GetData()->GetDBDesc()->GetDBID();
  luaValueSetter::Set( L, id.GetFormatted() );
  luaValueSetter::Set( L, pAbility->GetTarget() );

  return 2;
}

int PFBaseUnitEventUnitDeath::PushArgsForScript( lua_State *L ) const
{
  if ( !pVictim )
    return 0;

  PFAIContainer* pAICont = pVictim->GetWorld()->GetAIContainer();
  string name; 
  pAICont->FindObjectName( name, pVictim );
  luaValueSetter::Set(L, name.c_str() );
  pAICont->FindObjectName( name, pKiller );
  luaValueSetter::Set(L, name.c_str() );
  pAICont->FindObjectName( name, pQualifiedKiller );
  luaValueSetter::Set(L, name.c_str() );
  return 3;
}

int PFBaseUnitDamageEvent::PushArgsForScript( lua_State *L ) const
{
  luaValueSetter::Set(L,pDesc->amount);
  if ( pDesc->pSender )
  {
    PFAIContainer* pAICont = pDesc->pSender->GetWorld()->GetAIContainer();
    string name; 
    pAICont->FindObjectName( name, pDesc->pSender );
    luaValueSetter::Set(L, name.c_str() );
    return 2;
  }
  return 1;
}



}