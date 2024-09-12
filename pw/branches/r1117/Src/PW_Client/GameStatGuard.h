#pragma once

#ifndef GAMESTATGUARD_H_INCLUDED
#define GAMESTATGUARD_H_INCLUDED

#include "stdafx.h"

namespace StatisticService
{

const int GAMESTATGUARD_NUMBEROFREPETITIONS = 20;
const int GAMESTATGUARD_STEPCOUNTOFREPETITIONS = 5; 

struct GuardDataEntry
{
  GuardDataEntry(int _stepNumber) : count(1), stepNumber(_stepNumber), countCap(0), stepCap(0){}
  int count;
  int stepNumber;
  int countCap;
  int stepCap;
};

enum GuardDataInspectResult
{
  INSPECT_OK = 0,
  INSPECT_STEP_ERR,
  INSPECT_COUNT_ERR
};

typedef hash_map<wstring, GuardDataEntry> TGameStatGuardSimpleData;

class GameStatGuard : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( GameStatGuard, BaseObjectST );
public:
  GameStatGuard(int _numberOfRepetitions = GAMESTATGUARD_NUMBEROFREPETITIONS, int _stepCountOfRepetitions = GAMESTATGUARD_STEPCOUNTOFREPETITIONS)
    : maxNumberOfRepetitions(_numberOfRepetitions), maxStepCountForRepetitions(_stepCountOfRepetitions), lastInspected(L""){};

  void Reset() { guardData.clear(); }

  GuardDataInspectResult Inspect(const StatisticService::RPC::SessionEventInfo& _params, int _stepNumber = 0)
  {
    return Inspect(_params.strParam1, _params.strParam2, _stepNumber);
  }

  GuardDataInspectResult Inspect(const wstring& _msg1, const wstring& _msg2, int _stepNumber = 0)
  {
    return Inspect(_msg1, _stepNumber);
  }

  GuardDataInspectResult Inspect(const wstring& _msg, int _stepNumber = 0)
  {
    lastInspected = _msg;
    TGameStatGuardSimpleData::iterator found = guardData.find(lastInspected);
    if(found != guardData.end())
    {
      found->second.count += 1;
      
      bool stepsCriteria = (_stepNumber - found->second.stepNumber) < maxStepCountForRepetitions;
      bool msgCountCriteria = found->second.count > maxNumberOfRepetitions;

      found->second.stepNumber = _stepNumber;

      if(msgCountCriteria)
      {
        found->second.countCap += 1;
        return INSPECT_COUNT_ERR;
      }
      else if(stepsCriteria)
      {
        found->second.stepCap += 1;
        return INSPECT_STEP_ERR;
      }
    }
    else
    {
      guardData.insert(make_pair<wstring, GuardDataEntry>(lastInspected, GuardDataEntry(_stepNumber)));
    }

    return INSPECT_OK;
  }

  const wstring* GetLastInspectedMsg() {return &lastInspected;}

  void PrintGuardStatistic()
  {
#ifndef _SHIPPING
    struct GDataPrinter
    {
      void operator()(const pair<wstring, GuardDataEntry>& value)
      {
        DevTrace("%s ... %d (%d : %d)", value.first, value.second.count, value.second.countCap, value.second.stepCap);
      }
    } dataPrinter;

    DevTrace("GameStatGuard statistic:");
    DevTrace("Message ... count( count cap : step cap )");
    for_each(guardData.begin(), guardData.end(), dataPrinter);
#endif
  }

private:
  TGameStatGuardSimpleData guardData;
  int maxNumberOfRepetitions;
  int maxStepCountForRepetitions;
  wstring lastInspected;
};

};

#endif //#ifndef GAMESTATGUARD_H_INCLUDED