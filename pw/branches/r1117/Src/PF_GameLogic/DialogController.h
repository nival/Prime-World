#pragma once

#include "../UI/FSCommandListner.h"
#include "NivalInput/BindsContainer.h"

namespace NGameX
{
  class AdventureFlashInterface;
}

namespace NSoundScene
{
  class FMODEvent;
}

namespace NWorld
{
  class PFBaseHero;
  class PFScript;
}
namespace NNameMap
{
  class Map;
}

namespace NGameX
{

  _interface IAdventureScreen;

class DialogController: public UI::IFSCommandListner, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( DialogController, UI::IFSCommandListner, BaseObjectST );
public:
  DialogController( UI::FlashContainer2* flashContainer, AdventureFlashInterface* _flashInterface, NDb::Ptr<NDb::DBUIData>& _pUIData, NWorld::PFWorld* pWorld );

  virtual void OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  );
  
  void Init( NWorld::PFBaseHero const* pHero, NDb::Ptr<NDb::DialogsCollection> const& _dialogsCollection, NDb::Ptr<NDb::HintsCollection> const& _hintsCollection, NDb::Ptr<NDb::SessionQuestsCollection> const& _questsCollection );
  void StartDialog( const char* id, bool isCinematic );
  void StartHintDialog( const char* dialogId, const char* hintId, const char* imageId );
  void Update( float dt );
  bool IsDialogFinished( const char* id ) const;
  bool IsPhraseFinished( const char* id ) const;
  void PauseDialog( bool pause );
  void SetHint( char const* id, const char* bubbleViewType );

  bool ProcessUIEvent( const Input::Event & message );
  
  // Quests
  void AddSessionQuest( string id, const NNameMap::Map* pMap );
  void RemoveSessionQuest( string id );
  bool UpdateSessionQuestCounter( string id, const int count );
  void UpdateSessionQuestText( string id, const NNameMap::Map* pMap );

  void GetHintTextById( string id, wstring& hintText ) const;

  //MessageBox
  enum 
  {
    MESSAGEBOX_NORESULT =0,
  };

  //!! IDs in advMapSettings.hintsCollection!!
  void ShowMessageBox( const string& headerId, const string& textId ); 
  int GetLastMessageBoxResult() const { return messageBoxResult; } 

  void StopDialog();

private:
  struct DialogState
  {
    NDb::Dialog const* pDialogPlaying;
    int currentPhrase;
    NSoundScene::FMODEvent* pSound;
    float phraseDuration;
    bool isCinematic;
    bool isPaused;
    bool skipPhrase;

    DialogState() : pDialogPlaying(0), currentPhrase(0), pSound(0), phraseDuration(0.0f), isCinematic(false), isPaused(false), skipPhrase(false) {}
    void Cleanup()
    {
      pDialogPlaying = 0;
      currentPhrase = 0;
      pSound = 0;
      phraseDuration = 0.0f;
      isCinematic = false;
      isPaused = false;
      skipPhrase = false;
    };
  };

  typedef vector<NDb::Ptr<NDb::Dialog>> TDialogs;
  typedef vector<NDb::SessionQuest> TQuests;
  typedef vector<NDb::HintImage> THintImages;
  typedef vector<NDb::Phrase> TPhrases;

  vector<NDb::Phrase> const& GetPhrases() const;
  void PreparePhraseText( wstring& text, wstring const& actorName, NDb::Phrase const& phrase );
  void PlayPhrase( NDb::Phrase const& phrase );
  void SkipPhrase();
  void UpdatePhrase();
  void ShowCinematicNextButton();
  void StopSound(bool immediately = false);
  void StartSound( const NDb::DBFMODEventDesc& dbFMODDesc );
  void UpdateMusicVolume( float dt );
  NDb::SessionQuest const* DialogController::FindQuest( const string& id );

  NDb::Dialog const* FindDialogById( const char* );
  int FindPhraseIdByScriptName( const char* );
  void PreloadDialogImages();

  Weak<NWorld::PFScript> pLuaScript;
  Weak<UI::FlashContainer2> flashWnd;
  Weak<AdventureFlashInterface> flashInterface;
  NDb::Ptr<NDb::DialogsCollection> dialogsCollection;
  NDb::Ptr<NDb::HintsCollection> hintsCollection;
  NDb::Ptr<NDb::SessionQuestsCollection> questsCollection;
  NDb::Ptr<NDb::DBUIData> pUIData;
  bool heroIsMale;
  NDb::EFaction faction;
  DialogState dialogState;
  bool phraseDone;
  Input::BindsContainer eventsUI;
  float volumeMusicMultiplier;
  int messageBoxResult;
  Weak<NGameX::IAdventureScreen> advScreen;
};

} //namespace NGameX