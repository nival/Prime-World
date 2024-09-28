#pragma once

#include "DBStats.h"
#include "PFBaseUnit.h"
#include "PF_GameLogic/PFPlayer.h"

namespace NGameX
{ 

class PFUIEventData
{
public:
  PFUIEventData() : signRecipients() {}
  PFUIEventData(NDb::Ptr<NDb::UIEvent> const& dbDesc);

  NDb::ERecipients signRecipients;
  //list of signs for this event    
  vector<CObj<PFUISign>> signs;

  NDb::Ptr<NDb::UIEvent> dbEvent;
};

class PFUISign : public CObjectBase
{
  OBJECT_BASIC_METHODS( PFUISign );

public:
  PFUISign() : signRecipients(), signType() {}
  PFUISign(NDb::UISign const& dbDesc) : signRecipients(dbDesc.signRecipients), signType(NDb::SIGN_NONE) {}

  NDb::ERecipients signRecipients;
  NDb::ESign signType;
};

class PFUISignMessageToChat : public PFUISign
{
  OBJECT_BASIC_METHODS( PFUISignMessageToChat )
public:
  PFUISignMessageToChat() {}
  PFUISignMessageToChat(NDb::UISignMessageToChat const& dbDesc);
  StaticArray<wstring,  NDb::KnownEnum<NDb::EMessage>::sizeOf> messages;
  NDb::EChatChannel GetChannel() const {return chatChannel;}
private: 
  NDb::EChatChannel chatChannel;

};

class PFUISignPlaySound : public PFUISign
{
  OBJECT_BASIC_METHODS( PFUISignPlaySound )
public:
  PFUISignPlaySound() {}
  PFUISignPlaySound(NDb::UISignPlaySound const& dbDesc);
  
  NDb::DBFMODEventDesc soundDesc;
};

class PFUISignMessageToStatusLine : public PFUISign
{
  OBJECT_BASIC_METHODS( PFUISignMessageToStatusLine )
public:
  PFUISignMessageToStatusLine() {}
  PFUISignMessageToStatusLine(NDb::UISignMessageToStatusLine const& dbDesc);
  
  StaticArray<wstring,  NDb::KnownEnum<NDb::EMessage>::sizeOf> messages;
};

class PFUISignFlyOffText : public PFUISign
{
  OBJECT_BASIC_METHODS( PFUISignFlyOffText )
public:
  PFUISignFlyOffText() {}
  PFUISignFlyOffText(NDb::UISignFlyOffText const& dbDesc);
  NDb::FlyOffText text;
};


class PFUISignAnnouncement : public PFUISign
{
  OBJECT_BASIC_METHODS( PFUISignAnnouncement)
  PFUISignAnnouncement() {}
public:
  PFUISignAnnouncement(NDb::UISignAnnouncement const& dbDesc);

  NDb::UISignAnnouncement const* pDBDesc;
};


class PFUIEvent : public CObjectBase
{
  OBJECT_BASIC_METHODS( PFUIEvent )

  PFUIEventData pEvent;
  ConstPtr<NWorld::PFBaseUnit> pOwner;
  NDb::EMessage messageId;
  NDb::EMessage messageLinearId;

public:
  PFUIEvent() : messageId(), messageLinearId() {}
  PFUIEvent ( NDb::Ptr<NDb::UIEvent> const& dbDesc, NWorld::PFBaseUnit const* owner = 0 ) : 
      pEvent(dbDesc)
    , pOwner(owner)
    , messageId(NDb::MESSAGE_SIMPLE_MESSAGE)
    , messageLinearId(NDb::MESSAGE_SIMPLE_MESSAGE)
      {} ;

  PFUIEventData const & GetEventData() const { return pEvent; } 
  NWorld::PFBaseUnit const* GetOwner() const { return pOwner; }
  void SetOwner(NWorld::PFBaseUnit const* unit) { pOwner = unit; }

  bool CheckSignRecipients ( NWorld::PFPlayer const * pCurentPlayer, CObj<PFUISign> const pSign );
  NDb::EMessage GetCurMessageID() { return messageId; }
  void SetCurLinearMessageID( NDb::EMessage id ) { messageLinearId = id; }

  virtual bool IsCurrentHeroEventParticipant ( NWorld::PFPlayer const * pCurentPlayer );
  virtual bool IsCurrentHeroInKillerTeam ( NWorld::PFPlayer const * pCurentPlayer );
  virtual bool IsCurrentHeroEventOwner ( NWorld::PFPlayer const * pCurentPlayer );
  bool ExtractLinearAchievement ( NWorld::PFPlayer const * pCurentPlayer, CObj<PFUISign> const pSign );
};

//////////////////////////////////////////////////////////////////////////
// custom events
//////////////////////////////////////////////////////////////////////////
class PFUITwoUnitsEvent : public NGameX::PFUIEvent
{
  OBJECT_BASIC_METHODS( PFUITwoUnitsEvent )
public:
  PFUITwoUnitsEvent() {}
  PFUITwoUnitsEvent( NDb::Ptr<NDb::UIEvent> const& dbDesc, NWorld::PFBaseUnit const* owner = 0 ) : PFUIEvent(dbDesc, owner), pSender(0), pReciever(0) {};

  void SetSender  ( const NWorld::PFBaseUnit * unit ) { pSender = unit; }
  void SetReciever( const NWorld::PFBaseUnit * unit ) { pReciever = unit; }

  virtual bool IsCurrentHeroEventParticipant( NWorld::PFPlayer const * pCurentPlayer );
  virtual bool IsCurrentHeroEventOwner ( NWorld::PFPlayer const * pCurentPlayer );
private:
  ConstPtr<NWorld::PFBaseUnit> pSender;
  ConstPtr<NWorld::PFBaseUnit> pReciever;

  const NWorld::PFBaseUnit*  GetSender() const { return pSender; } 
  const NWorld::PFBaseUnit*  GetReciever() const { return pReciever; }
};


} // namespace NGameX

