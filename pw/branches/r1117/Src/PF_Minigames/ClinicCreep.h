#pragma once

#include "DBClinic.h"
#include "ClinicCreepWish.h"
#include "Minigames.h"
#include "MinigameWorldObject.h"
#include "ClinicUIDesc.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Minigames
{

namespace ECreepPhase
{
	enum Enum
	{
		InGame,
		IsFled,
		IsTrained
	};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Clinic;
class CreepState;
class ClinicPlace;

namespace ECreepType { enum Enum; }

class ClinicCreep : public MinigameWorldObject
{
	OBJECT_METHODS( 0x9A678C05, ClinicCreep )

public:
	ClinicCreep();
	virtual ~ClinicCreep();

	void SetClinic( Clinic* _clinic );
	CPtr<Clinic> GetClinic();

  void SetPoolID( int _id );
  int GetPoolID() const;

	void SetType( ECreepType::Enum _creepType );
	ECreepType::Enum GetType() const;

	void SetCreepWish( NDb::ECreepWish _creepWish );
	NDb::ECreepWish GetCreepWish() const;

	void SetCreepFirstWish( NDb::ECreepWish _creepWish );
	NDb::ECreepWish GetCreepFirstWish() const;

  bool IsCreepWaiting( float& _progrees );
  bool IsCreepWorking( float& _progrees );
  bool IsInPlaceCreepWants();

	void WantAtAnyPlace();

	void TryFindFriend();
	bool CheckFriendIsNear();
	ClinicCreep* GetFriend();

	void OnWakeUp();
	bool IsSleeping();

	void SetAtPlayerHand( bool _isAtHand ); 
	bool IsAtPlayerHand() const;

	void SetOwner( MinigameWorldObject* _owner );
	CPtr<MinigameWorldObject> GetOwner();

	void SetClinicPlace( ClinicPlace* _clinicPlace );
	ClinicPlace* GetClinicPlace();

	void SetClinicPlaceType( NDb::EPlaceType _placeType );
	NDb::EPlaceType GetClinicPlaceType() const;

	wstring GetTypeDesc() const;
	wstring GetStateDesc() const;

//deprecated
//	void  SetBarValue( float _value );
	float GetBarValue();
  void  AddBarValue( float _value );

  void SetGoldMadeInLevel(float gold) { goldMadeInLevel = gold; }
  float GetGoldMadeInLevel() const { return goldMadeInLevel; }

  void SetAward(EClinicCreepAward::Enum _award) { award = _award; }
  EClinicCreepAward::Enum GetAward() const { return award; }

	float GetTimeAtOnePlace();

	int GetFriendCreepID();
	void SetFriendCreepID( int _friendID );

	int GetFriendshipID();
	void SetFriendshipID( int _friendshipID );

	float GetSoilPersent();

	ECreepPhase::Enum GetCreepPhase() const;
	void SetCreepPhase( ECreepPhase::Enum _creepPhase );

	// from MinigameWorldObject
	virtual void Step( float deltaTime );
	virtual bool OnClick();
	virtual void Clear();

  virtual bool ReceiveClicks();

  virtual const Placement& GetTarget( bool& goInstantly ) const;
  virtual float GetLinearVelocity() const;

private:
  ZDATA_(MinigameWorldObject)
	float creepBar;
  float goldMadeInLevel;
  EClinicCreepAward::Enum award;

	ECreepType::Enum creepType;
	NDb::ECreepWish creepWish;
	NDb::ECreepWish creepWishAtStart;

	CObj<CreepState> creepState;
	CPtr<Clinic> clinic;

	CPtr<ClinicPlace> clinicPlace;
	NDb::EPlaceType clinicPlaceType;

	CPtr<MinigameWorldObject> owner;

	bool isAtHand;
	bool goingOut;

	float timeAtOnePlace;

	ECreepPhase::Enum creepPhase;

	int friendCreepID;
	int friendshipID; // To draw different heart colors

  int poolID;
public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(MinigameWorldObject*)this); f.Add(2,&creepBar); f.Add(3,&goldMadeInLevel); f.Add(4,&award); f.Add(5,&creepType); f.Add(6,&creepWish); f.Add(7,&creepWishAtStart); f.Add(8,&creepState); f.Add(9,&clinic); f.Add(10,&clinicPlace); f.Add(11,&clinicPlaceType); f.Add(12,&owner); f.Add(13,&isAtHand); f.Add(14,&goingOut); f.Add(15,&timeAtOnePlace); f.Add(16,&creepPhase); f.Add(17,&friendCreepID); f.Add(18,&friendshipID); f.Add(19,&poolID); return 0; }
private:

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline void ClinicCreep::SetPoolID( int _id ) { poolID = _id; }
inline int ClinicCreep::GetPoolID() const { return poolID; }

inline void ClinicCreep::SetType( ECreepType::Enum _creepType ) { creepType = _creepType; }
inline ECreepType::Enum ClinicCreep::GetType() const { return creepType; }

inline void ClinicCreep::SetClinic( Clinic* _clinic ) { clinic = _clinic; }
inline CPtr<Clinic> ClinicCreep::GetClinic() { return clinic; }

inline void ClinicCreep::SetAtPlayerHand( bool _isAtHand ) { isAtHand = _isAtHand; }
inline bool ClinicCreep::IsAtPlayerHand() const { return isAtHand; }

inline void ClinicCreep::SetCreepWish( NDb::ECreepWish _creepWish ) { creepWish = _creepWish; }
inline NDb::ECreepWish ClinicCreep::GetCreepWish() const { return creepWish; }

inline void ClinicCreep::SetCreepFirstWish( NDb::ECreepWish _creepWish ) { creepWishAtStart = _creepWish; }
inline NDb::ECreepWish ClinicCreep::GetCreepFirstWish() const { return creepWishAtStart; }

inline void ClinicCreep::SetOwner( MinigameWorldObject* _owner ) { owner = _owner; }
inline CPtr<MinigameWorldObject> ClinicCreep::GetOwner() { return owner; }

inline ClinicPlace* ClinicCreep::GetClinicPlace() { return clinicPlace; }

inline void ClinicCreep::SetClinicPlaceType( NDb::EPlaceType _placeType ) { clinicPlaceType = _placeType; }
inline NDb::EPlaceType ClinicCreep::GetClinicPlaceType() const { return clinicPlaceType; }

inline int ClinicCreep::GetFriendCreepID() { return friendCreepID; }
inline void ClinicCreep::SetFriendCreepID( int _friendID ) { friendCreepID = _friendID; }

inline int ClinicCreep::GetFriendshipID() { return friendshipID; }
inline void ClinicCreep::SetFriendshipID( int _friendshipID ) { friendshipID = _friendshipID; }

inline ECreepPhase::Enum ClinicCreep::GetCreepPhase() const { return creepPhase; }

} // namespace PF_Minigames

