#include "StdAfx.h"
#include "AnnouncementController.h"
#include "AdventureFlashInterface.h"
#include "AnnouncementParams.h"
#include "QueueSoundPlayer.h"
#include "PFUIEvent.h"

#include "DBStats.h"
#include "PFBaseUnit.h"
#include "PFHero.h"
#include "PFAchievement.h"


namespace NGameX
{


AnnouncementController::AnnouncementController( AdventureFlashInterface* _flashInterface, NDb::Ptr<NDb::DBUIData> _uiData, QueueSoundPlayer* _soundPlayer )
: uiData(_uiData)
, flashInterface(_flashInterface)
, soundPlayer(_soundPlayer)
{
  InitAnnouncementHandlers();
}
void AnnouncementController::ShowStartBattleAnnouncement()
{
  const NDb::BattleStartAnnouncementParams & battleParams = uiData->battleStartAnnouncementParams;
  ShowStartBattleAnnouncement( battleParams );
}

void AnnouncementController::ShowStartBattleAnnouncement( const NDb::BattleStartAnnouncementParams & params )
{
  if (!params.imageBurn)
    return;

  const char * leftIcon = params.imageBurn->textureFileName.c_str();

  if (!params.imageFreeze)
    return;

  const char * rightIcon = params.imageFreeze->textureFileName.c_str();

  flashInterface->ShowSpawnCreepsAnnouncement(leftIcon, rightIcon, params.announcementText.GetText());
}


void AnnouncementController::Update( float dt )
{
  if (soundPlayer)
  {
    soundPlayer->Update(dt);

    for( SoundCooldowns::iterator it = soundCooldowns.begin(); it != soundCooldowns.end(); )
    {
      it->second -= dt;
      SoundCooldowns::iterator next = it;
      ++next;
      if( it->second <= EPS_VALUE )
      {
        soundCooldowns.erase(it);
      }
      it = next;
    }
  }
}



void AnnouncementController::ShowAnnouncement( PFUISignAnnouncement const *sign , AnnouncementParams * announcementParams )
{
  if (!IsValid(sign) || !announcementParams || !flashInterface)
    return;

  if (announcementHandlers.find(sign->pDBDesc->announcementType) != announcementHandlers.end())
  {
    AnnouncementHandler method =  announcementHandlers[sign->pDBDesc->announcementType];
    (this->*method)(sign, announcementParams);
  }

  if (soundPlayer && soundCooldowns.find( sign->pDBDesc ) == soundCooldowns.end() )
  {
    soundPlayer->AddSoundToQueue(sign->pDBDesc->announcementSound, sign->pDBDesc->priority );

    float cooldown = sign->pDBDesc->announcementSoundCooldown;
    if ( cooldown > 0.0f )
    {
      soundCooldowns[sign->pDBDesc] = cooldown;
    }
  }
}

//////////////////////////////////////////////////////////////////////////

void AnnouncementController::InitAnnouncementHandlers()
{
   /*enum EAnnouncementType
  {
    ANNOUNCEMENTTYPE_PLAYERKILLED = 0,
    ANNOUNCEMENTTYPE_ACHIEVMENT = 1,
    ANNOUNCEMENTTYPE_TOWERDESTROYED = 2,
    ANNOUNCEMENTTYPE_SPAWNSUPERCREEPS = 3,
    ANNOUNCEMENTTYPE_PLAYERLEFT = 4,
    ANNOUNCEMENTTYPE_PLAYERRECONNECTED = 5,
    ANNOUNCEMENTTYPE_QUESTRECIEVED = 6,
    ANNOUNCEMENTTYPE_QUESTCOMPLETE = 7,
  };*/

  announcementHandlers[NDb::ANNOUNCEMENTTYPE_PLAYERKILLED   ] = &AnnouncementController::ShowTwoUnits;
  announcementHandlers[NDb::ANNOUNCEMENTTYPE_TOWERDESTROYED ] = &AnnouncementController::ShowTwoUnits;
  
  announcementHandlers[NDb::ANNOUNCEMENTTYPE_SPAWNSUPERCREEPS   ] = &AnnouncementController::ShowSpawnSuperCreeps;
  announcementHandlers[NDb::ANNOUNCEMENTTYPE_PLAYERLEFT         ] = &AnnouncementController::ShowOneUnit;
  announcementHandlers[NDb::ANNOUNCEMENTTYPE_PLAYERRECONNECTED  ] = &AnnouncementController::ShowOneUnit;
  announcementHandlers[NDb::ANNOUNCEMENTTYPE_EGGANNOUNCEMENT    ] = &AnnouncementController::ShowOneUnit;
  announcementHandlers[NDb::ANNOUNCEMENTTYPE_SUPERSIEGESPAWNED  ] = &AnnouncementController::ShowTwoUnitsOfDifferentFactions;
  
  announcementHandlers[NDb::ANNOUNCEMENTTYPE_ACHIEVMENT   ] = &AnnouncementController::ShowAchiev;

  announcementHandlers[NDb::ANNOUNCEMENTTYPE_CUSTOMANNOUNCEMENT ] = &AnnouncementController::ShowFixedIcons;
}


void AnnouncementController::ShowTwoUnits( PFUISignAnnouncement const *sign , const AnnouncementParams * announcementParams )
{
  ShowUnit(LeftPart, announcementParams->killer);
  ShowUnit(RightPart, announcementParams->victim);

   flashInterface->ShowAnnouncement(sign->pDBDesc->txt.GetText(), sign->pDBDesc->lifeTime, sign->pDBDesc->priority);
}

void AnnouncementController::ShowTwoUnitsOfDifferentFactions( PFUISignAnnouncement const *sign , const AnnouncementParams * announcementParams )
{
  const char * imageLeftPath = 0;
  const char * imageRightPath = 0;
  const NDb::EFaction faction      = announcementParams->killer->GetFaction();
  const NDb::EFaction otherFaction = announcementParams->killer->GetOppositeFaction();

  NI_VERIFY(sign->pDBDesc->imageBurn,   "invalid image for announcement burn faction",   return);
  NI_VERIFY(sign->pDBDesc->imageFreeze, "invalid image for announcement freeze faction", return);

  if (faction == NDb::FACTION_BURN)
  {
    imageLeftPath  = sign->pDBDesc->imageBurn->textureFileName.c_str();
    imageRightPath = sign->pDBDesc->imageFreeze->textureFileName.c_str();
  }
  else
  {
    imageLeftPath  = sign->pDBDesc->imageFreeze->textureFileName.c_str();
    imageRightPath = sign->pDBDesc->imageBurn->textureFileName.c_str();
  }
  flashInterface->SetAnnouncementPart( false, imageLeftPath,  0, wstring(), faction,      -1 );
  flashInterface->SetAnnouncementPart( true,  imageRightPath, 0, wstring(), otherFaction, -1 );

  flashInterface->ShowAnnouncement(sign->pDBDesc->txt.GetText(), sign->pDBDesc->lifeTime, sign->pDBDesc->priority);
}

void AnnouncementController::ShowOneUnit( PFUISignAnnouncement const *sign , const AnnouncementParams * announcementParams )
{
  ShowUnit(LeftPart, announcementParams->killer);
  NI_VERIFY(IsValid(announcementParams->killer), "invalid AnnouncementParams for announcement", return);
  ShowIcon(sign, announcementParams->killer->GetFaction());

  flashInterface->ShowAnnouncement(sign->pDBDesc->txt.GetText(), sign->pDBDesc->lifeTime, sign->pDBDesc->priority);
}

void AnnouncementController::ShowSpawnSuperCreeps( PFUISignAnnouncement const *sign , const AnnouncementParams * announcementParams )
{
  ShowUnit(LeftPart, announcementParams->killer);
  NI_VERIFY(IsValid(announcementParams->killer), "invalid AnnouncementParams for announcement", return);
  
  const char * imagePath = 0;

  NDb::EFaction faction = announcementParams->killer->GetFaction();
  if (faction == NDb::FACTION_BURN)
  {
    NI_VERIFY(sign->pDBDesc->imageBurn, "invalid image for announcement burn faction", return);
    imagePath = sign->pDBDesc->imageBurn->textureFileName.c_str();
  }
  else
  {
    NI_VERIFY(sign->pDBDesc->imageFreeze, "invalid image for announcement freeze faction", return);
    imagePath = sign->pDBDesc->imageFreeze->textureFileName.c_str();
  }
  flashInterface->SetAnnouncementPart(true, imagePath, 0, wstring(), faction,-1);


  flashInterface->ShowAnnouncement(sign->pDBDesc->txt.GetText(), sign->pDBDesc->lifeTime, sign->pDBDesc->priority);
}

void AnnouncementController::ShowAchiev( PFUISignAnnouncement const *sign , const AnnouncementParams * announcementParams )
{
  ShowUnit(LeftPart, announcementParams->killer);
  ShowAchievIcon(announcementParams);

  flashInterface->ShowAnnouncement(sign->pDBDesc->txt.GetText(), sign->pDBDesc->lifeTime, sign->pDBDesc->priority);
}

void AnnouncementController::ShowFixedIcons(PFUISignAnnouncement const *sign , const AnnouncementParams * announcementParams)
{
  NI_VERIFY(sign->pDBDesc->imageBurn, "invalid image for announcement burn faction", return);
  NI_VERIFY(sign->pDBDesc->imageFreeze, "invalid image for announcement freeze faction", return);

  flashInterface->SetAnnouncementPart(false, sign->pDBDesc->imageBurn->textureFileName.c_str(), 0, wstring(), -1,-1);
  flashInterface->SetAnnouncementPart(true, sign->pDBDesc->imageFreeze->textureFileName.c_str(), 0, wstring(), -1,-1);

  flashInterface->ShowAnnouncement(sign->pDBDesc->txt.GetText(), sign->pDBDesc->lifeTime, sign->pDBDesc->priority);
}
void AnnouncementController::ShowAchievIcon( const AnnouncementParams * announcementParams )
{
  NDb::Ptr<NDb::Texture> image = announcementParams->achiev->GetImage();
  NI_VERIFY(image, "announcement without image", return);
  const char * imagePath = image->textureFileName.c_str();
  flashInterface->SetAnnouncementPart(true, imagePath, 0, wstring(), -1,-1);
}

void AnnouncementController::ShowUnit( AnnouncementPart announcementPart, const NWorld::PFBaseUnit * unit )
{
  if (!IsValid(unit))
    return;

  const char * texturePath =  IsValid(unit)? unit->GetUiAvatarImage()->textureFileName.c_str() : "";
  int level = unit->IsHero()? unit->GetNaftaLevel() : unit->GetStatValue( NDb::STAT_LEVEL );
  const NWorld::PFBaseHero * unitAsHero = dynamic_cast<NWorld::PFBaseHero const *> (unit);
  const wstring & descTitle = IsValid(unitAsHero)? unitAsHero->GetPlayerName() : unit->GetDescription();


  flashInterface->SetAnnouncementPart(announcementPart == RightPart, texturePath, level, descTitle, unit->GetFaction(),IsValid(unitAsHero)? unitAsHero->GetPlayerId() : -1);
}

void AnnouncementController::ShowIcon( PFUISignAnnouncement const *sign, NDb::EFaction faction )
{
  const char * imagePath = 0;
  if (faction == NDb::FACTION_BURN)
  {
    NI_VERIFY(sign->pDBDesc->imageBurn, "invalid image for announcement burn faction", return);
    imagePath = sign->pDBDesc->imageBurn->textureFileName.c_str();
  }
  else
  {
    NI_VERIFY(sign->pDBDesc->imageFreeze, "invalid image for announcement freeze faction", return);
    imagePath = sign->pDBDesc->imageFreeze->textureFileName.c_str();
  }
  flashInterface->SetAnnouncementPart(true, imagePath, 0, wstring(), -1,-1);
}


}//namespace NGameX


NI_DEFINE_REFCOUNT(NGameX::AnnouncementController)


