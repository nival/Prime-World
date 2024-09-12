#include "stdafx.h"
#include "DialogController.h"
#include "..\Sound\EventScene.h"
#include "AdventureFlashInterface.h"
#include "AdventureScreen.h"
#include "PFAIContainer.h"
#include "PrecompiledTooltips.h"
#include "FlashFSCommands.h"
#include "../UI/FlashContainer2.h"

#include "Scripts/Script.h"
#include "Scripts/lua.hpp"
#include "Scripts/FuncCallMacroses.h"

namespace
{
  // Flash-style byte order
  uint GetUInt( Render::Color color )
  {
    return ( (uint)(color.A) << 24 ) | ( (uint)(color.R) << 16 ) | ( (uint)(color.G) << 8 ) | color.B;
  }
}

namespace NGameX
{

DialogController::DialogController( UI::FlashContainer2* flashContainer, AdventureFlashInterface* _flashInterface, NDb::Ptr<NDb::DBUIData>& _pUIData, NWorld::PFWorld* pWorld )
 : flashWnd(flashContainer)
 , flashInterface(_flashInterface)
 , pUIData(_pUIData)
 , phraseDone(false)
 , volumeMusicMultiplier(1.f)
 , messageBoxResult(MESSAGEBOX_NORESULT)
{
  using namespace FlashFSCommands;

  if ( !IsValid( flashWnd ) )
    return;

  flashWnd->AddFSListner( ConvertToString(BubbleNextButtonClick), this );
  flashWnd->AddFSListner( ConvertToString(CinematicNextButtonClick), this );

  flashWnd->AddFSListner( ConvertToString(MessageBoxButtonClick), this );

  flashWnd->AddFSListner( ConvertToString(ExitHintDialog), this );

  pLuaScript = pWorld->GetAIContainer()->GetLuaScript();
  advScreen = pWorld->GetIAdventureScreen();

  eventsUI.AddActivationHandler( "skip_phrase_cinematic", &DialogController::SkipPhrase);

  NI_ASSERT( pUIData->dialogsSettings.FadeInOutPercentage >= 0.0f && pUIData->dialogsSettings.FadeInOutPercentage <= 1.0f, "bad FadeInOutPercentage parameter" )
}

bool DialogController::ProcessUIEvent( const Input::Event & message )
{  
  if ( eventsUI.ProcessEvent( message, this ) )
    return true;

  return false;
}

void DialogController::SkipPhrase()
{
  if( !dialogState.pDialogPlaying || !dialogState.isCinematic || phraseDone || dialogState.skipPhrase )
    return;

  if( GetPhrases()[ dialogState.currentPhrase ].terminate == NDb::PHRASETERMINATEEVENT_PRESSKEY
   || GetPhrases()[ dialogState.currentPhrase ].terminate == NDb::PHRASETERMINATEEVENT_TIMEANDKEY )
  {
    if ( dialogState.isPaused )
    {
      dialogState.skipPhrase = true;
      AdventureScreen::Instance()->UpdateCursor();
      flashInterface->EnableCinematicNextButton( false );
      flashInterface->ShowCinematicNextButtonAnim( true );
      return;
    }

    phraseDone = true;

    dialogState.currentPhrase++;

    UpdatePhrase();
  }
}

void DialogController::UpdatePhrase()
{
  const string& prevPhraseId = dialogState.currentPhrase > 0 ? GetPhrases()[dialogState.currentPhrase - 1].scriptName : "";

  if ( dialogState.currentPhrase == GetPhrases().size() ) // that was last phrase, dialog has ended
  {
    StopSound();

    dialogState.pDialogPlaying = 0;

    if ( dialogState.isCinematic )
      flashInterface->StopCinematic();
    else
      flashInterface->HideNPC();

    AdventureScreen::Instance()->UpdateCursor();
  }
  else
  {
    PlayPhrase( GetPhrases()[ dialogState.currentPhrase ] ); // play next phrase
  }

  if ( IsValid( pLuaScript ) )
  {
    CALL_LUA_FUNCTION_ARG1( pLuaScript, "OnAfterNextDialogPhrase", false, prevPhraseId.c_str() );
  }
}

void DialogController::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID, const char* args, const wchar_t * argsW )
{
  using namespace FlashFSCommands;

  FlashFSCommands::EFlashFSCommands command = ConvertToFSCommand(listenerID);

  switch( command )
  {
  case BubbleNextButtonClick:
    if ( IsValid( pLuaScript ) )
    {
      int bubbleIndex;
      sscanf_s( args, "%d", &bubbleIndex );
      CALL_LUA_FUNCTION_ARG1( pLuaScript, "OnBubbleNextButtonClick", false, bubbleIndex );
    }
    break;

  case CinematicNextButtonClick:
    SkipPhrase();
    break;

  case MessageBoxButtonClick:
    int buttonIndex;
    sscanf_s( args, "%d", &buttonIndex );
    NI_VERIFY( buttonIndex != MESSAGEBOX_NORESULT, "Message box button index should not be zero", buttonIndex = 1 );
    messageBoxResult = buttonIndex;
    break;

  case ExitHintDialog:

    StopDialog();

    if ( IsValid( pLuaScript ) )
    {
      char buf[128] = "0";
      sscanf_s( args, "%s", &buf, 128);
      CALL_LUA_FUNCTION_ARG1( pLuaScript, "OnHintDialogClose", false, buf );
    }
    break;
  
  default: return;
  }
}

void DialogController::Init( NWorld::PFBaseHero const* pHero, NDb::Ptr<NDb::DialogsCollection> const& _dialogsCollection, NDb::Ptr<NDb::HintsCollection> const& _hintsCollection, NDb::Ptr<NDb::SessionQuestsCollection> const& _questsCollection )
{
  dialogsCollection = _dialogsCollection;
  hintsCollection = _hintsCollection;
  questsCollection = _questsCollection;
  heroIsMale = pHero->IsMale();
  faction = pHero->GetFaction();

  if(IsValid(dialogsCollection) && !dialogsCollection->dialogs.empty())
    PreloadDialogImages();
}

void DialogController::PreloadDialogImages()
{
  if(!advScreen)
    return;

  string nodeName = "";

  for ( TDialogs::const_iterator it = dialogsCollection->dialogs.begin(); it != dialogsCollection->dialogs.end(); ++it )
  {
    if ( !it->GetPtr() ) 
      continue;

    const vector<NDb::Phrase> &phrase = ( faction == NDb::FACTION_FREEZE ) ? it->GetPtr()->phrasesA : it->GetPtr()->phrasesB;

    for(TPhrases::const_iterator resPhraseIter = phrase.begin(); resPhraseIter != phrase.end(); ++resPhraseIter)
    {
      const NDb::Ptr<NDb::Actor>& actor = !heroIsMale && resPhraseIter->actorFemale ? resPhraseIter->actorFemale : resPhraseIter->actorMale;
      if(IsValid(actor))
        advScreen->PreloadEffectsInResourceTree( actor, nodeName );

      for(THintImages::const_iterator resHintImageIter = resPhraseIter->hintImages.begin();resHintImageIter != resPhraseIter->hintImages.end();++resHintImageIter)
      {
        advScreen->PreloadEffectsInResourceTree( resHintImageIter->image, nodeName );
      }
    }
  }
}

void DialogController::AddSessionQuest( string id, const NNameMap::Map* pMap )
{
  NDb::SessionQuest const* pDBSessionQuest = FindQuest( id );
  if (! pDBSessionQuest )  
    return;

  wstring text;
  if ( pMap )
  {
    PrecompiledTooltip precompiledTooltip;
    precompiledTooltip.Init( pMap, pDBSessionQuest->text.GetText() );
    precompiledTooltip.MakeText( text );
  }
  else 
    text = pDBSessionQuest->text.GetText();

  flashInterface->AddQuest( Crc32Checksum().AddString(pDBSessionQuest->id.c_str()).Get(), pDBSessionQuest->primary, text, pDBSessionQuest->counter );
}

void DialogController::RemoveSessionQuest( string id )
{
  NDb::SessionQuest const* pDBSessionQuest = FindQuest( id );
  if (! pDBSessionQuest )  
    return;
  flashInterface->RemoveQuest( Crc32Checksum().AddString(pDBSessionQuest->id.c_str()).Get() );
}

bool DialogController::UpdateSessionQuestCounter( string id, const int count )
{
  NDb::SessionQuest const* pDBSessionQuest = FindQuest( id );
  if ( !pDBSessionQuest )  
    return false;

  NI_ASSERT( count <= pDBSessionQuest->counter, "bad completed quest argument")

  flashInterface->UpdateQuest( Crc32Checksum().AddString(pDBSessionQuest->id.c_str()).Get(), count );
  return ( count == pDBSessionQuest->counter );
}

void DialogController::UpdateSessionQuestText( string id, const NNameMap::Map* pMap )
{
  NDb::SessionQuest const* pDBSessionQuest = FindQuest( id );
  if ( !pDBSessionQuest )  
    return;

  PrecompiledTooltip precompiledTooltip;
  precompiledTooltip.Init( pMap, pDBSessionQuest->text.GetText() );

  wstring text;
  precompiledTooltip.MakeText( text );

  flashInterface->UpdateQuestText( Crc32Checksum().AddString(pDBSessionQuest->id.c_str()).Get(), text );
  return;
}

NDb::SessionQuest const* DialogController::FindQuest( const string& id )
{
  NI_DATA_VERIFY( questsCollection, "No quests for the map", return 0 );
  NI_VERIFY( id != "", "ID should not be null", return 0 );

  // find quest by id
  for ( TQuests::const_iterator it = questsCollection->quests.begin(); it != questsCollection->quests.end(); ++it )
  {
    if( it->id == id )
    {
      return it;
    }
  }
  NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Quest with id = '%s' not found", id ) );
  return 0;
}

NDb::Dialog const* DialogController::FindDialogById(const char* id)
{
  NDb::Dialog const* pDBDialog = 0;
  // find dialog by id
  for ( TDialogs::const_iterator it = dialogsCollection->dialogs.begin(); it != dialogsCollection->dialogs.end(); ++it )
  {
    if ( !it->GetPtr() ) 
      continue;
    if ( strcmp( it->GetPtr()->id.c_str(), id ) == 0 )
    {
      pDBDialog = *it;
    }
  }

  return pDBDialog;
}

int DialogController::FindPhraseIdByScriptName(const char* phraseScriptName)
{
  int phraseId = -1;

  vector<NDb::Phrase> const& phrases = GetPhrases();
  int phrasesCount = phrases.size();
  for( int i = 0; i < phrasesCount; ++i )
  {
    if ( strcmp( phrases[i].scriptName.c_str(), phraseScriptName ) == 0 )
    {
      phraseId = i;
      break;
    }
  }
  return phraseId;
}

void DialogController::StartHintDialog( const char* dialogId, const char* phraseScriptName, const char* dialogHintImagePath )
{
  NI_DATA_VERIFY( dialogsCollection, "No dialogs for the map", return );

  NDb::Dialog const* pDBDialog = FindDialogById(dialogId);
  NI_DATA_VERIFY( pDBDialog, NStr::StrFmt( "Dialog with id = '%s' not found", dialogId ), return );

  StopDialog();
  dialogState.pDialogPlaying = pDBDialog;

  int phraseId = FindPhraseIdByScriptName(phraseScriptName);
  NI_DATA_VERIFY( phraseId >= 0, NStr::StrFmt( "Phrase with script name = '%s'  not found", phraseScriptName ), return );

  dialogState.currentPhrase = phraseId;

  NDb::Phrase const& phrase = GetPhrases()[ dialogState.currentPhrase ];

  StartSound( !heroIsMale && !phrase.soundFemale.projectName.empty() ? phrase.soundFemale : phrase.soundMale );

  wstring dialogMessage = !heroIsMale && !phrase.textFemale.GetText().empty() ? phrase.textFemale.GetText().c_str() : phrase.textMale.GetText().c_str();
  wstring dialogTitle = pDBDialog->title.GetText();

  flashInterface->ShowHintDialog(dialogId, dialogTitle, dialogMessage, dialogHintImagePath);
}

void DialogController::StartDialog( const char* id, bool isCinematic )
{
  NI_DATA_VERIFY( dialogsCollection, "No dialogs for the map", return );

  MessageTrace( "Dialog '%s' was started", id );

  NDb::Dialog const* pDBDialog = FindDialogById(id);

  NI_DATA_VERIFY( pDBDialog, NStr::StrFmt( "Dialog with id = '%s' not found", id ), return );

  if ( dialogState.pDialogPlaying )
  {
    MessageTrace( "Dialog '%s' was forcedly finished", dialogState.pDialogPlaying->id.c_str() );
  }

  StopDialog();
  dialogState.pDialogPlaying = pDBDialog;
  dialogState.isCinematic = isCinematic;

  if ( isCinematic )
  {
    flashInterface->StartCinematic();
    flashInterface->ShowCinematicNextButton( true );
  }

  NDb::Phrase const& phrase = GetPhrases()[ dialogState.currentPhrase ];
  PlayPhrase( phrase );
}

bool DialogController::IsPhraseFinished( const char* id ) const
{
  if ( dialogState.pDialogPlaying == 0 )
    return true;

  vector<NDb::Phrase> const& phrases = GetPhrases();
  for( int i = 0; i < dialogState.currentPhrase; i++ )
  {
    if ( strcmp( phrases[i].scriptName.c_str(), id ) == 0 )
      return true;
  }
  return false;
}

bool DialogController::IsDialogFinished( const char* id ) const
{
  return dialogState.pDialogPlaying == 0 || ( id && strlen( id ) > 0 && strcmp( dialogState.pDialogPlaying->id.c_str(), id ) != 0 );
}

void DialogController::Update( float dt )
{
  UpdateMusicVolume( dt );

  if ( dialogState.pDialogPlaying == 0 )
    return;

  if ( dialogState.phraseDuration >= EPS_VALUE )
  {
    dialogState.phraseDuration -= dt;
    if ( dialogState.phraseDuration < EPS_VALUE )
    {
      phraseDone = true;
      dialogState.currentPhrase++;
    }
  }
  
  if ( dialogState.phraseDuration < EPS_VALUE && !dialogState.isPaused )
    UpdatePhrase();
}

void DialogController::UpdateMusicVolume( float dt )
{
  const float duringTime = 0.5f; // sec. fade in/out
  const float maxMultiplier = 1.0f;

  if( dialogState.pDialogPlaying == 0 )
  {
    if( volumeMusicMultiplier == maxMultiplier )
      return;

    volumeMusicMultiplier += ( dt * pUIData->dialogsSettings.FadeInOutPercentage / duringTime );
  }
  else
  {
    if( volumeMusicMultiplier == 1.f - pUIData->dialogsSettings.FadeInOutPercentage )
      return;

    volumeMusicMultiplier -= ( dt * pUIData->dialogsSettings.FadeInOutPercentage / duringTime );
  }

  volumeMusicMultiplier = Clamp( volumeMusicMultiplier, 1.f - pUIData->dialogsSettings.FadeInOutPercentage, maxMultiplier );

  NSoundScene::SetMusicMultiplier( volumeMusicMultiplier );
}

void DialogController::PlayPhrase( NDb::Phrase const& phrase )
{
  NDb::Ptr<NDb::Actor> const& actor = !heroIsMale && phrase.actorFemale ? phrase.actorFemale : phrase.actorMale;

  if ( actor )
  {
    wstring const& actorName = actor->name.GetText();

    if ( dialogState.isCinematic )
      flashInterface->ShowCinematicNPC( actor->icon ? actor->icon->textureFileName.c_str() : "", actorName );

    StartSound( !heroIsMale && !phrase.soundFemale.projectName.empty() ? phrase.soundFemale : phrase.soundMale );

    NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
    wstring message;
    PreparePhraseText( message, actorName, phrase );

    if ( dialogState.isCinematic )
      flashInterface->ShowCinematicMessage( message, heroIsMale ? GetUInt(phrase.colorTextMale) : GetUInt(phrase.colorTextFemale) );
    else
      advScreen->AddMessageToChat( message );

    dialogState.phraseDuration = dialogState.pSound->GetDuration();

    if ( dialogState.phraseDuration < EPS_VALUE )
      dialogState.phraseDuration = pUIData->dialogsSettings.defaultPhraseDuration;
    else
      dialogState.phraseDuration += pUIData->dialogsSettings.defaultSilenceDuration;
  }
  else
  {
    if ( dialogState.isCinematic )
    {
      flashInterface->ShowCinematicNPC( "", L"" );
      flashInterface->ShowCinematicMessage( L"", 0 );
    }
  }
  
  if ( phrase.duration > 0 && ( phrase.terminate == NDb::PHRASETERMINATEEVENT_TIME || phrase.terminate == NDb::PHRASETERMINATEEVENT_TIMEANDKEY ) )
  {   
    dialogState.phraseDuration = phrase.duration;
  }
  else if ( phrase.duration == 0 )
  {
    dialogState.phraseDuration = pUIData->dialogsSettings.defaultPhraseDuration;
  }
  
  ShowCinematicNextButton();
}

vector<NDb::Phrase> const& DialogController::GetPhrases() const
{
  return faction == NDb::FACTION_BURN && !dialogState.pDialogPlaying->phrasesB.empty() ? dialogState.pDialogPlaying->phrasesB : dialogState.pDialogPlaying->phrasesA;
}

void DialogController::PreparePhraseText( wstring& text, wstring const& actorName, NDb::Phrase const& phrase )
{
  text = !heroIsMale && !phrase.textFemale.GetText().empty() ? phrase.textFemale.GetText().c_str() : phrase.textMale.GetText().c_str();
  
  if ( !dialogState.isCinematic && !actorName.empty() )
    text = NStr::StrFmtW( L"%s: %s", actorName.c_str(), text.c_str() );
}

void DialogController::ShowCinematicNextButton()
{
  if( dialogState.currentPhrase >= GetPhrases().size() || !dialogState.isCinematic )
    return;

  phraseDone = false;

  flashInterface->ShowCinematicNextButtonAnim( false );

  if( GetPhrases()[ dialogState.currentPhrase ].terminate == NDb::PHRASETERMINATEEVENT_PRESSKEY || GetPhrases()[ dialogState.currentPhrase ].terminate == NDb::PHRASETERMINATEEVENT_TIMEANDKEY )
  {
    flashInterface->EnableCinematicNextButton( true );
    NMainFrame::ShowCursor( true );
  }
  else
  {
    flashInterface->EnableCinematicNextButton( false );
    AdventureScreen::Instance()->UpdateCursor();
  }
}

void DialogController::StartSound( const NDb::DBFMODEventDesc& dbFMODDesc )
{
  StopSound();

  dialogState.pSound = NSoundScene::CreateFMODEvent();
  dialogState.pSound->Init( dbFMODDesc );
  dialogState.pSound->PlaySound();
}

void DialogController::StopSound(bool immediately /*= false*/)
{
  // Release current sound
  if ( dialogState.pSound )
  {
    dialogState.pSound->Stop(immediately);
    dialogState.pSound->Release();
    NSoundScene::ReleaseFMODEvent( dialogState.pSound );
    dialogState.pSound = 0;
  }
}

void DialogController::SetHint( char const* id, const char* bubbleViewType )
{
  NI_DATA_VERIFY( hintsCollection, "No hints for the map", return );

  if ( strlen( id ) == 0 )
    flashInterface->SetQuestHintLine( L"", "None" );

  for ( vector<NDb::Hint>::const_iterator it = hintsCollection->hints.begin(); it != hintsCollection->hints.end(); ++it )
  {
    if ( strcmp( it->id.c_str(), id ) == 0 )
    {
      flashInterface->SetQuestHintLine( it->text.GetText(), bubbleViewType );
    }
  }
}

void DialogController::PauseDialog( bool pause )
{
  if ( dialogState.pDialogPlaying == 0 )
  {
    MessageTrace( "No dialog to pause" );
    return; 
  }

  dialogState.isPaused = pause;

  if( !pause )
  {
    if ( dialogState.skipPhrase )
    {
      dialogState.skipPhrase = false;
      if ( !phraseDone )
      {
        phraseDone = true;
        dialogState.currentPhrase++;
        UpdatePhrase();
      }
    }
  }
}

void DialogController::GetHintTextById( string id, wstring& hintText ) const
{
  if ( !hintsCollection )
    return;

  for ( vector<NDb::Hint>::const_iterator it = hintsCollection->hints.begin(); it != hintsCollection->hints.end(); ++it )
  {
    if ( it->id == id )
    {
      hintText = it->text.GetText();
    }
  }
}

void DialogController::ShowMessageBox( const string& headerId, const string& textId )
{
  wstring header;
  wstring text;
  GetHintTextById( headerId, header );
  GetHintTextById( textId, text );
  NI_ASSERT( !header.empty(), NStr::StrFmt("ShowMessageBox: headerId '%s' not found in hintsCollection!", headerId.c_str() ) );
  NI_ASSERT( !textId.empty(), NStr::StrFmt("ShowMessageBox: textId '%s' not found in hintsCollection!", textId.c_str() ) );
  flashInterface->ShowMessageBox( header, text );
  messageBoxResult = MESSAGEBOX_NORESULT;
}

void DialogController::StopDialog()
{
  StopSound(true);
  dialogState.Cleanup();
}


} //namespace NGameX