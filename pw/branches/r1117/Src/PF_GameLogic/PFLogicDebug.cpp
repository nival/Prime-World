#include "stdafx.h"
#include "System/StringDumper.h"
#include "PFBaseUnit.h"
#include "PFHero.h"
#include "PFGameLogicLog.h"
#include "PFLogicDebug.h"
#include "PFDispatch.h"
#include "PFAbilityData.h"
#include "PFAbilityInstance.h"

#include "../System/fixedstring.h"
#include "../System/nalgoritm.h"

#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

namespace NWorld
{

#ifdef LogGL
#error Bad naming
#endif
#define LogGL LogLogicInfo(GetGameLogicLog())

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *MakeUnitIDString(PFLogicObject *pUnit)
{
	if (!IsValid(pUnit))
		return "(invalid)";

  PFBaseHero *pHero = dynamic_cast<PFBaseHero*>(pUnit);
  if (pHero)
  {
    return NStr::StrFmt("(Player %d @ %3.2f %3.2f)", pHero->GetPlayer() ? pHero->GetPlayer()->GetPlayerID() : -1, 
			                   pHero->GetPosition().x, pHero->GetPosition().y);
  }
  else
  {
    return NStr::StrFmt("(%s from %s [%d] @ %3.2f %3.2f)", pUnit->GetObjectTypeName(), EnumToString(pUnit->GetFaction()), pUnit->GetObjectId(), 
			                   pUnit->GetPosition().x, pUnit->GetPosition().y );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *MakeTargetString(const Target &target)
{
	static FixedString<100> s_targetString;

	switch (target.GetType())
	{
	case Target::POSITION: s_targetString.Printf("Position (%5.2f %5.2f)", target.GetPosition().x, target.GetPosition().y); break;
	case Target::UNIT: s_targetString.Printf("Unit %s", MakeUnitIDString(target.GetUnit())); break;
	case Target::OBJECT: s_targetString.Printf("Object %s", MakeUnitIDString(target.GetUnit())); break;
	}

	return s_targetString.c_str();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DumpApplicatorFunctor
{
  DumpApplicatorFunctor(NLogg::CChannelLogger &stream): stream(stream) {}
  void operator()(CObj<PFBaseApplicator> const &pApp)
  {
    pApp->DumpInfo(stream);
  }

  NLogg::CChannelLogger &stream;
private:
  DumpApplicatorFunctor &operator=(DumpApplicatorFunctor const &);
};

/*NLogg::CChannelLogger &GetStringLog()
{
  static NLogg::CChannelLogger g_strLog( 0, "System", NLogg::LEVEL_MESSAGE );
  return g_strLog;
}*/

/*struct StrDumpApplicatorFunctor
{
  void operator()(CObj<PFBaseApplicator> const &pApp)
  {
    pApp->DumpInfo(GetStringLog());
  }
};*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DumpObjectInfoToString(const PFLogicObject *pUnit, char *buffer, int bufLen)
{
	NStr::Copy(buffer, "Unit information:\n", bufLen);
	NStr::Cat (buffer, NStr::StrFmt("  type:     %s\n", EnumToString(pUnit->GetUnitType()) ), bufLen);
	NStr::Cat (buffer, NStr::StrFmt("  faction:  %s\n", EnumToString(pUnit->GetFaction()) ), bufLen);
	NStr::Cat (buffer, NStr::StrFmt("  health:   %.1f\n", pUnit->GetHealth() ), bufLen);
	NStr::Cat (buffer, NStr::StrFmt("  player:   %i\n", pUnit->GetPlayerId() ), bufLen);
	NStr::Cat (buffer, NStr::StrFmt("  world id: %d\n", pUnit->GetObjectId() ), bufLen);
	NStr::Cat (buffer, NStr::StrFmt("  C++ type: %s\n", pUnit->GetObjectTypeName() ), bufLen);
}

void DumpUnitInfoToString(PFBaseUnit const *pBaseUnit, char *buffer, int bufLen)
{
  NLogg::CChannelLogger stream( "logicLogger" );
  NLogg::CStringDumper dumper( &stream, buffer, bufLen );
	buffer[0] = 0;
  DumpUnitInfo(stream, pBaseUnit);
}

void DumpLogicObjectInfo(const PFLogicObject *pUnit, char *buffer, int bufLen)
{
  PFBaseUnit const *pBaseUnit = dynamic_cast<PFBaseUnit const *>(pUnit);
  if (!pBaseUnit)
  {
    DumpObjectInfoToString(pUnit, buffer, bufLen);
  }
  else
  {
    DumpUnitInfoToString(pBaseUnit, buffer, bufLen);
  }
}

void DumpUnitInfo(NLogg::CChannelLogger &stream, PFBaseUnit const* pUnit)
{
  // prevent 'unused argument' warning
  (void)pUnit;
#ifndef _SHIPPING
  if(NULL == pUnit)
    return;

  const PFWorld* pWorld = pUnit->GetWorld();

#ifdef Log2Sys
#error Bad naming
#endif
#define Log2Sys LogLogicInfo(stream)

  Log2Sys("Unit information:\n");
  Log2Sys("  type:     %s\n", EnumToString(pUnit->GetUnitType()) );
  Log2Sys("  faction:  %s\n", EnumToString(pUnit->GetFaction()) );
	Log2Sys("  health:   %.1f\n", pUnit->GetHealth() );
	Log2Sys("  gold:     %i\n", pUnit->GetGold() );
  Log2Sys("  player:   %i\n", pUnit->GetPlayerId() );
  Log2Sys("  world id: %d\n", pUnit->GetObjectId() );
  Log2Sys("  C++ type: %s\n", pUnit->GetObjectTypeName() );
  Log2Sys("  resource: %s\n", pUnit->GetDebugDescription() );
	Log2Sys("  target:   %s\n", pUnit->GetCurrentTarget() ? MakeUnitIDString(pUnit->GetCurrentTarget()) : "none" );
	pUnit->DumpInfo(stream);
  Log2Sys("  stats:\n");

  typedef vector<NWorld::ValueWithModifiers::Modifier> TModifiers;
  for ( int i = NDb::STAT_LIFE, count = NDb::KnownEnum<NDb::EStat>::SizeOf(); i < count; ++i )
  {
    const NDb::EStat stat = static_cast<NDb::EStat>(i);
    if ( NWorld::StatValueWithModifiers const* pValue = pUnit->GetStat(stat) )
    {
      Log2Sys("  %s : %.2f (base: %.2f)\n", NDb::EnumToString(stat), pValue->GetValue(), pValue->GetUnmodifiedValue() );

      TModifiers const& modifiers = pValue->GetModifiers();
      if(modifiers.empty())
        continue;
      for(TModifiers::const_iterator it = modifiers.begin(), end = modifiers.end(); it != end; ++it)
      {
        if(!it->active)
          continue;

        PF_Core::WorldObjectBase *pWO = pWorld->GetObjectById(it->provider);
        PFBaseUnit *pSender = dynamic_cast<PFBaseUnit*>(pWO);
        Log2Sys("    modifier mul: %4.2f add: %4.2f sender: %s %s\n", it->mulValue, it->addValue, 
          pSender ? MakeUnitIDString(pSender) : "unknown",
          it->active ? "" : "[inactive]");
      }

    } 
  }

  DumpApplicatorFunctor f(stream);
  Log2Sys("  active applicators:\n");
  pUnit->ForAllAppliedApplicators(f);
	Log2Sys("  sent applicators:\n");
	pUnit->ForAllSentApplicators(f);
  Log2Sys("  applied applicators (history):\n");
  pUnit->ForAllAppliedApplicatorsInHistory(f);
  Log2Sys("  sent applicators (history):\n");
  pUnit->ForAllSentApplicatorsInHistory(f);
#endif
}

#ifndef _SHIPPING

namespace
{
bool s_isLogEnabled = false;
bool s_isLogDispatchEnabled = true;
bool s_isLogApplicatorEnabled = true;
bool s_isWoidFiltering = false;
bool s_isUnitTypeFiltering = false;
nstl::vector<int> s_filterWoid;
nstl::vector<NDb::EUnitType> s_filterUnitType;
unsigned int s_filterFlags = 0;
bool s_isSimpleUnitLogging = true;

void LogV3d(char const *str, CVec3 const &v)
{
  NI_ASSERT(s_isLogEnabled, "Strange");
  LogGL("%s%f %f %f\n", str, v.x, v.y, v.z);
}

void LogTarget(char const *str, Target const &target)
{
  NI_ASSERT(s_isLogEnabled, "Strange");
  LogGL("%s", str);
  if (target.IsPosition())
  {
    LogV3d("    Pos: ", target.GetPosition());
  }
  else if (target.IsUnitValid())
  {
    LogLogicObject(target.GetUnit(), "    Unit: ", true);
  }
  else if (target.IsObject())
  {
    LogLogicObject(target.GetObject(), "    Object: ", true);
  }
  else
  {
    LogGL("    Invalid target");
  }
  LogGL("\n");
}

bool LogAddUnitTypeCmd(const char *name, const vector<wstring> &paramsSet)
{
  if (paramsSet.size() != 1)
  {
    DebugTrace("Usage: %s unit_type_string", name);
    return true;
  }
  string eName;
  NStr::UnicodeToUTF8(&eName, paramsSet[0]);
  NDb::EUnitType ut = NDb::KnownEnum<NDb::EUnitType>::ToEnum(eName);
  if (ut != NDb::UNITTYPE_INVALID)
  {
    LogAddUnitType(ut);
  }
  return true;
}

bool LogRemoveUnitTypeCmd(const char *name, const vector<wstring> &paramsSet)
{
  if (paramsSet.size() != 1)
  {
    DebugTrace("Usage: %s unit_type_string", name);
    return true;
  }
  string eName;
  NStr::UnicodeToUTF8(&eName, paramsSet[0]);
  NDb::EUnitType ut = NDb::KnownEnum<NDb::EUnitType>::ToEnum(eName);
  if (ut != NDb::UNITTYPE_INVALID)
  {
    LogRemoveUnitType(ut);
  }
  return true;
}

bool LogAddWorldObjectCmd(const char *name, const vector<wstring> &paramsSet)
{
  if (paramsSet.size() != 1)
  {
    DebugTrace("Usage: %s unit_id", name);
    return true;
  }
  int woid = (int)NGlobal::VariantValue(paramsSet[0]).GetFloat();
  LogAddWorldObject(woid);
  return true;
}

bool LogRemoveWorldObjectCmd(const char *name, const vector<wstring> &paramsSet)
{
  if (paramsSet.size() != 1)
  {
    DebugTrace("Usage: %s unit_id", name);
    return true;
  }
  int woid = (int)NGlobal::VariantValue(paramsSet[0]).GetFloat();
  LogRemoveWorldObject(woid);
  return true;
}

bool IsOkByWoid(PFLogicObject const *pUnit)
{
	if (!IsValid(pUnit))
		return false;

  return find(s_filterWoid.begin(), s_filterWoid.end(), pUnit->GetObjectId()) != s_filterWoid.end();
}

bool IsOkByUnitType(PFLogicObject const *pUnit)
{
	if (!IsValid(pUnit))
		return false;

	return find(s_filterUnitType.begin(), s_filterUnitType.end(), pUnit->GetUnitType()) != s_filterUnitType.end();
}

bool IsOkByWoid(Target const &target)
{
  if (target.IsPosition())
  {
    return true;
  }
  else if (target.IsUnitValid())
  {
    return IsOkByWoid(target.GetUnit());
  }
  else if (target.IsObject())
  {
    return IsOkByWoid(target.GetObject());
  }
  return true;
}

bool IsOkByUnitType(Target const &target)
{
  if (target.IsPosition())
  {
    return true;
  }
  else if (target.IsUnitValid())
  {
    return IsOkByUnitType(target.GetUnit());
  }
  else if (target.IsObject())
  {
    return IsOkByUnitType(target.GetObject());
  }
  return true;
}

bool IsOkByWoid(PFBaseApplicator const &appl)
{
  return IsOkByWoid(appl.GetAbilityOwner()) || IsOkByWoid(appl.GetReceiver()) || IsOkByWoid(appl.GetTarget());
}

bool IsOkByUnitType(PFBaseApplicator const &appl)
{
  return IsOkByUnitType(appl.GetAbilityOwner()) || IsOkByWoid(appl.GetReceiver()) || IsOkByUnitType(appl.GetTarget());
}

bool IsOkByWoid(PFDispatch const &dispatch)
{
  return IsOkByWoid(dispatch.GetSender()) || IsOkByWoid(dispatch.GetTarget());
}

bool IsOkByUnitType(PFDispatch const &dispatch)
{
  return IsOkByUnitType(dispatch.GetSender()) || IsOkByUnitType(dispatch.GetTarget());
}

}

void LogEnable(bool enable)
{
  s_isLogEnabled = enable;
}

void LogStepBegin(int step)
{
  if (!s_isLogEnabled)
  {
    return;
  }
  LogGL("World step %i\n------------------------------------------------\n", step);
}

bool IsGameLogicLogEnabled(PFLogicObject const *pUnit, bool noFiltering)
{
  if (!s_isLogEnabled)
  {
    return false;
  }

  bool ok = true;
  if (!noFiltering)
  {
    ok = (!s_isWoidFiltering || IsOkByWoid(pUnit)) && (!s_isUnitTypeFiltering || IsOkByUnitType(pUnit));
  }
  return ok;
}

void LogGameLogicString(char const *string)
{
  if (!s_isLogEnabled)
  {
    return;
  }  
  LogGL(string);
}

void LogLogicObject(PFLogicObject const *pUnit, char const *str, bool noFiltering)
{
  if (!IsGameLogicLogEnabled(pUnit, noFiltering))
  {
    return;
  }

  LogGL("%s", str);

	if (!IsValid(pUnit))
	{
		LogGL("invalid-unit");
		return;
	}

  if (s_isSimpleUnitLogging)
  {
    LogGL("(%s %s %d %s)", EnumToString(pUnit->GetUnitType()), EnumToString(pUnit->GetFaction()), pUnit->GetObjectId(), pUnit->GetObjectTypeName());
  }
  else
  {
    PFBaseUnit const *pBaseUnit = dynamic_cast<PFBaseUnit const *>(pUnit);
    if (!pBaseUnit)
    {
      char buffer[1024];
      DumpObjectInfoToString(pUnit, buffer, DIM(buffer));
      LogGL("%s", buffer);
    }
    else
    {
      DumpUnitInfo(GetGameLogicLog(), pBaseUnit);
    }
  }
}

void LogApplicator(PFBaseApplicator const &appl, char const *str)
{
  if (!s_isLogEnabled || !s_isLogApplicatorEnabled)
  {
    return;
  }

  bool ok = (!s_isWoidFiltering || IsOkByWoid(appl)) && (!s_isUnitTypeFiltering || IsOkByUnitType(appl));
  if (!ok)
  {
    return;
  }

  LogGL("%s\n  Applicator C++ type: %s\n", str, appl.GetObjectTypeName());
  LogLogicObject(appl.GetAbilityOwner(), "  Sender: ", true);
	if (IsValid(appl.GetReceiver()))
		LogLogicObject(appl.GetReceiver(), "  Receiver: ", true);
  LogTarget("\n  Target:\n", appl.GetTarget());
	appl.DumpInfo(GetGameLogicLog());
  LogGL("\n");
}

void LogDispatch(PFDispatch const &dispatch, char const *str)
{
  if (!s_isLogEnabled || !s_isLogDispatchEnabled)
  {
    return;
  }

  bool ok = (!s_isWoidFiltering || IsOkByWoid(dispatch)) && (!s_isUnitTypeFiltering || IsOkByUnitType(dispatch));
  if (!ok)
  {
    return;
  }

  LogGL("%s", str);
  LogGL("  Dispatch ID: %i\n" "  Dispatch type: %s\n", dispatch.GetObjectId(), dispatch.GetObjectTypeName());
  LogLogicObject(dispatch.GetSender(), "  Sender: ", true);
  LogTarget("\n  Target:\n", dispatch.GetTarget());
}

void LogAbilityUsage(PFAbilityInstance const *pAbilityInstance)
{
  if (!s_isLogEnabled || !s_isLogDispatchEnabled)
  {
    return;
  }

  int abilityIndex = -1;
  PFAbilityData const* pAbility = pAbilityInstance->GetData();
  PFBaseUnit const *pUnit = pAbility->GetOwner();
  PFBaseHero const *pHero = dynamic_cast<PFBaseHero const *>(pUnit);
  if (pHero)
  {
    abilityIndex = pHero->GetAbilityIndex(pAbility);
    if (abilityIndex >= 0)
    {
      LogGL("DISPATCH CREATING BY ABILITY %i\n", abilityIndex);
    }
  }
  //LogGL("DISPATCH CREATING BY ABILITY %i\n", abilityIndex);
}

void LogAddWorldObject(int woid)
{
  PushUnique(s_filterWoid, woid);
}

void LogRemoveWorldObject(int woid)
{
  s_filterWoid.remove(woid);
}

void LogAddUnitType(NDb::EUnitType unitType)
{
  PushUnique(s_filterUnitType, unitType);
}

void LogRemoveUnitType(NDb::EUnitType unitType)
{
  s_filterUnitType.remove(unitType);
}

void LogSetFilteringFlags(unsigned int flags)
{
  s_filterFlags = flags;
}

#endif

REGISTER_DEV_VAR("gl_log_dispatch_enable", s_isLogDispatchEnabled, STORAGE_NONE);
REGISTER_DEV_VAR("gl_log_applicator_enable", s_isLogApplicatorEnabled, STORAGE_NONE);
REGISTER_DEV_VAR("gl_log_woid_filter", s_isWoidFiltering, STORAGE_NONE);
REGISTER_DEV_VAR("gl_log_unittype_filter", s_isUnitTypeFiltering, STORAGE_NONE);
REGISTER_DEV_VAR("gl_log_enable", s_isLogEnabled, STORAGE_NONE);
REGISTER_DEV_VAR("gl_log_unit_simple", s_isSimpleUnitLogging, STORAGE_NONE);
REGISTER_DEV_CMD(gl_log_add_world_object, LogAddWorldObjectCmd);
REGISTER_DEV_CMD(gl_log_remove_world_object, LogRemoveWorldObjectCmd);
REGISTER_DEV_CMD(gl_log_add_unit_type, LogAddUnitTypeCmd);
REGISTER_DEV_CMD(gl_log_remove_unit_type, LogRemoveUnitTypeCmd);


}