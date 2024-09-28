#ifndef VOTINGFORSURRENDERCONTROLLER_H_B
#define VOTINGFORSURRENDERCONTROLLER_H_B

#include "AIWorldFacets/VotingForSurrenderLogic.h"
#include "UI/FlashInterface.h"
#include "UI/FSCommandListner.h"
#include "UI/FlashContainer2.h"


namespace NGameX
{
typedef NWorld::AIWorldFacets::VotingForSurrenderLogic VotingForSurrenderLogic;

class VotingForSurrenderController: public UI::FlashInterface, public UI::IFSCommandListner
{
  NI_DECLARE_REFCOUNT_CLASS_2( VotingForSurrenderController, UI::FlashInterface, UI::IFSCommandListner )

public:
  VotingForSurrenderController( const CPtr<VotingForSurrenderLogic> &pVFS, NDb::Ptr<NDb::VotingForSurrender> pDb, UI::FlashContainer2 * flashWnd, const char* className );
  void Update( float timeDelta );
  
private:
  void StartVoting();
  void MakeDecision( bool vote );
  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );

private:
  VotingForSurrenderLogic::State curUIState;
  CPtr<VotingForSurrenderLogic> pVFS;
  NDb::Ptr<NDb::VotingForSurrender> pDb;
};
}

#endif //#define VOTINGFORSURRENDERCONTROLLER_H_B