#pragma once


namespace NDb
{
  struct DBUIData;
  enum EAnnouncementType;
}

namespace NGameX
{
  class AdventureFlashInterface;
  struct AnnouncementParams;
  class PFUISignAnnouncement;
  class QueueSoundPlayer;
}

namespace NWorld
{
  class PFBaseUnit;
}

namespace NGameX
{

class AnnouncementController: public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( AnnouncementController, BaseObjectST );
public:
  AnnouncementController( AdventureFlashInterface* _flashInterface, NDb::Ptr<NDb::DBUIData> _uiData, QueueSoundPlayer* _soundPlayer );

  void ShowStartBattleAnnouncement( const NDb::BattleStartAnnouncementParams & params );
  void ShowStartBattleAnnouncement();
  void ShowAnnouncement(PFUISignAnnouncement const *sign ,  AnnouncementParams * announcementParams);
  void Update(float dt);

private:

  enum AnnouncementPart
  {
    LeftPart,
    RightPart
  };

  void InitAnnouncementHandlers();
  
  void ShowTwoUnits(PFUISignAnnouncement const *sign ,  const AnnouncementParams * announcementParams);
  void ShowTwoUnitsOfDifferentFactions(PFUISignAnnouncement const *sign ,  const AnnouncementParams * announcementParams);
  void ShowSpawnSuperCreeps(PFUISignAnnouncement const *sign ,  const AnnouncementParams * announcementParams);
  void ShowOneUnit(PFUISignAnnouncement const *sign ,  const AnnouncementParams * announcementParams);
  void ShowAchiev(PFUISignAnnouncement const *sign , const AnnouncementParams * announcementParams);
  void ShowFixedIcons(PFUISignAnnouncement const *sign , const AnnouncementParams * announcementParams);
  

  void ShowUnit(AnnouncementPart announcementPart, const NWorld::PFBaseUnit * unit);
  void ShowIcon(PFUISignAnnouncement const *sign, NDb::EFaction faction);
  void ShowAchievIcon(const AnnouncementParams * announcementParams);
   
  NDb::Ptr<NDb::DBUIData> uiData;
  Weak<AdventureFlashInterface>         flashInterface;
  Weak<QueueSoundPlayer>  soundPlayer;

  typedef void (AnnouncementController::*AnnouncementHandler)(PFUISignAnnouncement const *sign , const  AnnouncementParams * announcementParams);
  typedef map<NDb::EAnnouncementType, AnnouncementHandler> AnnouncementHandlers;
  typedef map<NDb::UISignAnnouncement const*, float> SoundCooldowns;

  AnnouncementHandlers announcementHandlers;
  SoundCooldowns soundCooldowns;
};

}