#include "stdafx.h"

#include "PFBaseUseState.h"
#include "PFBaseUnitStates.h"
#include "PFHeroStates.h"

namespace
{
  void DumpStateInternal( NWorld::IPFState * state, int depths )
  {
    NI_VERIFY(IsValid(state), "invalid state to dump", return);
    nstl::string dumpString;
    for (int i=0;i<depths;i++)
      dumpString+=" ";

    dumpString+=state->GetObjectTypeName();

    DebugTrace(dumpString.c_str());
  }

  void DumpFSMState(NWorld::PFHFSM * fsm, NWorld::IPFState * state, int depths)
  {
    depths++;

    DumpStateInternal(state, depths);

    NI_VERIFY(fsm, "invalid fsm to dump", return);
    fsm->DumpAllStates(depths);
  }
}

namespace NWorld
{
  void DumpSimpleState( IPFState * state, int depths )
  {
    depths++;
    DumpStateInternal(state, depths);
  }

void MoveUnitStateFSM::DumpStateToConsole( int depths )
{
    DumpFSMState(this, this, depths);
}

void HeroStateFSM::DumpStateToConsole( int depths )
{
  DumpFSMState(this, this, depths);
}

void PFBaseUseState::DumpStateToConsole( int depths )
{
  DumpFSMState(this, this, depths);
}

}