#include "stdafx.h"
#include "FPUState.h"



namespace nfpu
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FPUStatesData::FPUStatesData()
{
  states.resize(_AT_COUNT);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FPUStatesData::SetStartState( ActionType actionType, unsigned int startState )
{
  NI_VERIFY( actionType >= 0 && actionType < states.size(), "Wrong action type!", return );
  states[actionType].startState = startState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FPUStatesData::SetFinishState( ActionType actionType, unsigned int finishState )
{
  NI_VERIFY( actionType >= 0 && actionType < states.size(), "Wrong action type!", return );
  states[actionType].finishState = finishState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int FPUStatesData::GetStartState( ActionType actionType ) const
{
  NI_VERIFY( actionType >= 0 && actionType < states.size(), "Wrong action type!", return 0 );
  return states[actionType].startState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int FPUStatesData::GetFinishState( ActionType actionType ) const
{
  NI_VERIFY( actionType >= 0 && actionType < states.size(), "Wrong action type!", return 0 );
  return states[actionType].finishState;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int FPUStatesData::operator&( IBinSaver &f )
{
  // States for map load should not be serialized on reconnect but are used in crc calculation
  if (f.IsChecksum())
    f.Add( AT_MAP_LOAD, &states[AT_MAP_LOAD] );

  // Others are used in reconnect, so crc of the first step will count a valid data (not zero)
  for ( int i = AT_WORLD_STEP; i < _AT_COUNT; ++i )
    f.Add( i, &states[i] );

  return 0;
}


} // namespace nfpu

