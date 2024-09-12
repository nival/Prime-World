#pragma once

#include "ClinicItem.h"

namespace NDb
{
	struct PlaceDesc;
	enum EPlaceType;
}

namespace PF_Minigames
{

class ClinicCreep;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ClinicPlace : public ClinicItem
{
	OBJECT_METHODS( 0x9A678C02, ClinicPlace )

public:
	ClinicPlace();
	virtual ~ClinicPlace();

  // MinigameWorldObject:
  virtual wstring GetName() const { return placeDesc->name.GetText(); }
  virtual wstring GetDescription() const { return placeDesc->description.GetText(); }

  // ClinicItem:
  virtual const NDb::BaseUIMaterial* GetIconMaterial() const { return placeDesc->iconMaterial; }
  virtual int GetCost() const { return placeDesc->cost; }
  virtual int GetAccessibility() const { return placeDesc->accessibility; }

	void SetSoil( float _soil );
	float GetSoil() const;

  void SetCreepWorking( bool _creepWorking );
  bool IsCreepWorking( float& _progress );

	void SetOccupied( ClinicCreep* _occupant );
	ClinicCreep* GetOccupied() const;

	bool StartCleaning();

	void SetPlaceDesc( const NDb::PlaceDesc * _desc );
  const NDb::PlaceDesc * GetPlaceDesc() const { return placeDesc; }

	NDb::EPlaceType GetType() const;

	bool IsAvailable( NDb::EPlaceType _placeType, float soilPersent ) const;

	// from MinigameWorldObject
	virtual void Step( float deltaTime );
	virtual bool OnClick();
	virtual bool OnTouched( MinigameWorldObject* _other );
	virtual void Clear();

private:

  const NDb::PlaceDesc* placeDesc;
  ZDATA_(ClinicItem)
	float	soil; // [0,1]

  bool isCreepWorking;

	CPtr<ClinicCreep> occupant;

	bool cleaning;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(ClinicItem*)this); f.Add(2,&soil); f.Add(3,&isCreepWorking); f.Add(4,&occupant); f.Add(5,&cleaning); return 0; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline float ClinicPlace::GetSoil() const { return soil; }

inline void ClinicPlace::SetPlaceDesc( const NDb::PlaceDesc * _desc ) { placeDesc = _desc; }

inline ClinicCreep* ClinicPlace::GetOccupied() const { return occupant; }

} // namespace PF_Minigames

