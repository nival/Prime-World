#pragma once

namespace NWorld
{

class PFBaseUnit;
class PFAbilityData;

#define LogLogicInfo( log ) ( NLogg::StreamBuffer( log, NLogg::SEntryInfo( NLogg::LEVEL_MESSAGE, "", 1 ) ) ).Trace



void DumpUnitInfo(NLogg::CChannelLogger &stream, const PFBaseUnit *pUnit);
void DumpUnitInfoToString(PFBaseUnit const *pBaseUnit, char *buffer, int bufLen);
void DumpObjectInfoToString(PFLogicObject const *pUnit, char *buffer, int bufLen);
void DumpLogicObjectInfo(PFLogicObject const *pUnit, char *buf, int bufLen);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *MakeUnitIDString(PFLogicObject *pUnit);
const char *MakeTargetString(const Target &target);

#ifndef _SHIPPING
enum LogFilteringType
{
  FILTER_BY_WOID = 1 << 0,
  FILTER_BY_UNITTYPE = 1 << 1
};

void LogEnable(bool enable);
void LogStepBegin(int step);
void LogApplicator(PFBaseApplicator const &appl, char const *str);
void LogDispatch(PFDispatch const &dispatch, char const *str);
void LogLogicObject(PFLogicObject const *pUnit, char const *str, bool noFiltering);
//char *GetLogicObjectInfo(PFLogicObject const *pUnit, char *buf, int bufSize);
bool IsGameLogicLogEnabled(PFLogicObject const *pUnit, bool noFiltering);
void LogAddWorldObject(int woid);
void LogRemoveWorldObject(int woid);
void LogAddUnitType(NDb::EUnitType unitType);
void LogRemoveUnitType(NDb::EUnitType unitType);
void LogSetFilteringFlags(unsigned int flags);
void LogAbilityUsage(PFAbilityInstance const *pAbility);
void LogGameLogicString(char const *string);
#else
#define LogEnable(b)
#define LogStepBegin(i)
#define LogApplicator(appl, str)
#define LogDispatch(dispatch, str)
#define LogLogicObject(pUnit, str, b)
#define IsGameLogicLogEnabled(pUnit, b) (false)
#define LogAddWorldObject(woid)
#define LogRemoveWorldObject(woid)
#define LogAddUnitType(unitType)
#define LogRemoveUnitType(unitType)
#define LogSetFilteringFlags(flags)
#define LogAbilityUsage(a)
#define LogGameLogicString(s)
#endif

}