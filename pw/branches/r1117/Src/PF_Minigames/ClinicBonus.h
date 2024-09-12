#pragma once

#include "ClinicItem.h"

namespace NDb
{
	enum EBonusType;
	struct BonusDesc;
}


namespace PF_Minigames
{

class ClinicCreep;
class ClinicPlace;
class ClinicBonusClientObject;
class ClinicDecorationClientObject;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ClinicBonus : public ClinicItem
{
	OBJECT_METHODS( 0x9A678C07, ClinicBonus )

public:
	ClinicBonus();
	virtual ~ClinicBonus();

  void SetClientObject( ClinicBonusClientObject * clObject) { clientObject = clObject; }
  ClinicBonusClientObject* GetStaticClientObject() { return clientObject; }
  ClinicDecorationClientObject * GetHandheldCientObject();

	void SetBonusDesc( NDb::EBonusType _type, const NDb::BonusDesc * _desc ) { bonusType = _type; bonusDesc = _desc; }
  const NDb::BonusDesc * GetBonusDesc() const { return bonusDesc; }

  // MinigameWorldObject:
  virtual wstring GetName() const;
  virtual wstring GetDescription() const;

  // ClinicItem:
  virtual const NDb::BaseUIMaterial* GetIconMaterial() const { return bonusDesc->iconMaterial; }
  virtual int GetCost() const { return bonusDesc->cost; }
  virtual int GetAccessibility() const { return bonusDesc->accessibility; }

	float GetCooldownPersent();

	int GetUseCost() const;
	NDb::EBonusType GetType() const;
	float GetValue() const;

	void SetCanBeBought(bool _canBeBought) { canBeBought = _canBeBought; }
	bool CanBeBought() const { return canBeBought; }

	bool TryUse();
	void Cooldown();
	bool HasCooldownPeriod();

	bool UseOnCreep( ClinicCreep* _clinicCreep, bool _forceUse = false );
	bool UseOnPlace( ClinicPlace* _clinicPlace );

	bool IsTargeted() const;

	virtual bool StartBonus();

		// from MinigameWorldObject
	virtual void Step( float deltaTime );
	virtual bool OnClick();
	virtual bool OnTouched( MinigameWorldObject* _other );
  virtual void Clear();

private:
	void OnWorkDone();

  //TODO: Convert to DBPtr or smth. like this
  const NDb::BonusDesc * bonusDesc;

	CObj<ClinicBonusClientObject> clientObject;
  CObj<ClinicDecorationClientObject> handheldClientObject;

  ZDATA_(ClinicItem)
  NDb::EBonusType bonusType;

	bool canBeBought;
	bool isBeeingCooled;
	float timeCooled;

	bool isWorking;
	float timeWorking;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(ClinicItem*)this); f.Add(2,&bonusType); f.Add(3,&canBeBought); f.Add(4,&isBeeingCooled); f.Add(5,&timeCooled); f.Add(6,&isWorking); f.Add(7,&timeWorking); return 0; }
};

} // namespace PF_Minigames

