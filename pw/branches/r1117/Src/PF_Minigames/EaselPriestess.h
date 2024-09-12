#pragma once

#include "../PF_GameLogic/NaftaInfoProvider.h"
#include "../PF_Core/WorldObject.h"

namespace NDb
{
  enum EBidonType;
  struct Consumable;
  struct GameObject;
}

namespace EMinigameLevelStatus
{
  enum Enum;
};

namespace PF_Minigames
{

// forward declarations
class Easel;

//////////////////////////////////////////////////////////////////////////
//
// priestess proxy object, needed to accumulate gold and experience
// current class is abstract, has to be implemented
//
//////////////////////////////////////////////////////////////////////////
_interface IPriestessProxy : public NGameX::INaftaInfoProvider
{
public:
  IPriestessProxy() {};
  virtual ~IPriestessProxy() {};

  // gold operations
  //FIXME: it's better to use 'unsigned' for money operations, but current codebase is already is messed up with 'int's
  virtual int   GetGold() const = 0;
  virtual void  TakeGold( int value ) = 0;
  virtual void  AddGold( int value ) = 0;

  virtual void  AddGoldDelayed( int value ) = 0;
  virtual void  ApplyDelayedGold() = 0;

  // ZZgold operations
  virtual bool  CanBuyZZBoost() const = 0;
  virtual void  BuyZZBoost() = 0;

  virtual int   GetLevel() = 0;

  // minigame specific operations
  virtual int   GetMinigameLevel() const = 0;
  virtual int   SetMinigameLevel( int _level ) = 0;

  virtual void  SetRewardItemId( int id ) = 0;
  virtual const NDb::Consumable * GetRewardItem() = 0;
  virtual void  ClearRewardItem() = 0;

  //Level status
  virtual void  MinigameComplete() = 0;
  virtual void  MinigameLevelEnd( int levelIndex, EMinigameLevelStatus::Enum status ) = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// priestess gold sack, level and experience provider
//
//////////////////////////////////////////////////////////////////////////
class EaselPriestess : public IPriestessProxy
{
public:
  EaselPriestess();
  ~EaselPriestess();

  // pointer setter
  void SetEaselPtr(CPtr<Easel> ptrEasel) { easel = ptrEasel; };

  // proxy methods implementation
  virtual int   GetGold() const;

  virtual void  AddGoldDelayed( int _gold );
  virtual void  ApplyDelayedGold();
 
  virtual int   GetLevel();

  virtual bool  CanBuyZZBoost() const;

  virtual void  SetRewardItemId( int id );
  virtual const NDb::Consumable * GetRewardItem() { return rewardItem; }
  virtual void  ClearRewardItem() { rewardItem = 0; }
  
  virtual int   GetMinigameLevel() const;
  virtual int   SetMinigameLevel(int _level);

  int GetDelayedGold() const { return delayedGold; }

  virtual int GetNaftaAmount() {return GetGold();}

private:             //TODO перенести переменные в EaselRemote 
  ZDATA
  ZNOPARENT(IPriestessProxy)
  int easelLevel;
  int delayedGold; // delayed gold counter
  NDb::Ptr<NDb::Consumable> rewardItem;

protected:
  CPtr<Easel> easel;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&easelLevel); f.Add(3,&delayedGold); f.Add(4,&rewardItem); f.Add(5,&easel); return 0; }
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Хитросплетенная подпорка для обхода проблемы влияния сессии на L/R-миниигру
//Метод вызывается из Remote Easel, что бы сообщить Local EaselPriestess о восстановлении
//возможности использовать буст про подвиги
_interface IRemoteToLocalLink : public IObjectBase
{
public:
  IRemoteToLocalLink() {}

  virtual void  AllowFeatBoostLocally() = 0;
  virtual void  BalanceLocalGold( int delta ) = 0;
};


//////////////////////////////////////////////////////////////////////////
//
// local priestess proxy object, can only read priestess data
//
//////////////////////////////////////////////////////////////////////////
class EaselPriestessLocal : public EaselPriestess, public IRemoteToLocalLink, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9D6BBBC7, EaselPriestessLocal );

public:
  EaselPriestessLocal( PF_Core::IWorld* _pWorld );
  ~EaselPriestessLocal() {}

  virtual int   GetGold() const;
  virtual void  AddGold( int _gold );
  virtual void  TakeGold( int _value );

  virtual void  BuyZZBoost(){}

  //Level status
  virtual void  MinigameComplete() {}
  virtual void  MinigameLevelEnd( int levelIndex, EMinigameLevelStatus::Enum status ) {}

  //IRemoteToLocalLink
  virtual void  AllowFeatBoostLocally() { allowFeatBoost = true; }
  virtual void  BalanceLocalGold( int delta );

private:
  EaselPriestessLocal() {}

  bool          allowFeatBoost;
  int           localGoldDebt;
};


//////////////////////////////////////////////////////////////////////////
//
// remote priestess proxy object, can read/write priestess data
//
//////////////////////////////////////////////////////////////////////////
class EaselPriestessRemote : public EaselPriestess, public PF_Core::WorldObjectBase
{
  OBJECT_METHODS( 0x9D6BBBC8, EaselPriestessRemote );

  EaselPriestessRemote() {}

public:
  EaselPriestessRemote(  PF_Core::IWorld* _pWorld, IRemoteToLocalLink * _localLink );
  ~EaselPriestessRemote() {}

  virtual void  AddGold( int _gold );
  virtual void  TakeGold( int _value );

  virtual void   BuyZZBoost();

  //Level status
  virtual void  MinigameComplete();
  virtual void  MinigameLevelEnd(int levelIndex, EMinigameLevelStatus::Enum status );

private:
  CPtr<IRemoteToLocalLink> localLink;

  ZDATA_( EaselPriestess )
  ZPARENT(PF_Core::WorldObjectBase)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,( EaselPriestess *)this); f.Add(2,(PF_Core::WorldObjectBase*)this); return 0; }
};

} //namespace PF_Minigames
