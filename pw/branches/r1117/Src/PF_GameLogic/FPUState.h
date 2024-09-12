#ifndef FPUSTATE_H_471DA6BE_E226_4F8A_85
#define FPUSTATE_H_471DA6BE_E226_4F8A_85

#include "System/SyncProcessorState.h"


namespace nfpu
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum ActionType
{
  AT_MAP_LOAD    = 0,
  AT_WORLD_STEP  = 1,
  AT_CMD_EXECUTE = 2,
  _AT_COUNT
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct FPUState
{
  FPUState() : startState(0.0f), finishState(0.0f) {}

  ZDATA
  unsigned int startState;
  unsigned int finishState;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&startState); f.Add(3,&finishState); return 0; }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct FPUStatesData
{
  FPUStatesData();

  void SetStartState( ActionType actionType, unsigned int startState );
  void SetFinishState( ActionType actionType, unsigned int finishState );
  unsigned int GetStartState( ActionType actionType ) const;
  unsigned int GetFinishState( ActionType actionType ) const;

  int operator&( IBinSaver &f );

private:
  vector<FPUState>  states;
};


} // namespace nfpu


#endif //#define FPUSTATE_H_471DA6BE_E226_4F8A_85