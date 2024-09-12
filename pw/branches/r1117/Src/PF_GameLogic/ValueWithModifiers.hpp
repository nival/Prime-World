#pragma once

#include <System/SyncProcessorState.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{

const int INVALID_MODIFIER_ID = -1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ValueWithModifiers
{
  struct Modifier
	{
    ZDATA
		int   id;
		int   provider;
		float mulValue;
		float addValue;
    bool  active;
    bool  top;
    NDb::EStatConstraint constraint;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&id); f.Add(3,&provider); f.Add(4,&mulValue); f.Add(5,&addValue); f.Add(6,&active); f.Add(7,&top); f.Add(8,&constraint); return 0; }

		Modifier()
      : id( INVALID_MODIFIER_ID ), provider( PF_Core::INVALID_OBJECT_ID ), mulValue( 1.0f ), addValue( 0.0f ), active( false ), top( false ), constraint(NDb::STATCONSTRAINT_NONE) {}

    Modifier( int _id, int _provider, float _mul, float _add, bool _top, NDb::EStatConstraint _constraint ) 
			: id( _id ), provider( _provider ), mulValue( _mul ), addValue( _add ), active( true ), top( _top ), constraint(_constraint) {}

		bool operator==( int _id ) const { return id == _id; }
	};

protected:
  float CalculateValue( float _value, int ignoreModifierID = INVALID_MODIFIER_ID ) const
  {
    float add = 0.0f;
    float mul = 1.0f;
    float add_top = 0.0f;
    float mul_top = 1.0f;
    float upperLimit = 1e10;
    float lowerLimit = -1e10;

    for ( vector<Modifier>::const_iterator it = modifiers.begin(), end = modifiers.end(); it != end; ++it )
    {
	    if ( !it->active )
		    continue;

      if ( ignoreModifierID == it->id )
        continue;

      if ( it->constraint == NDb::STATCONSTRAINT_LOWERLIMIT )
      {
        lowerLimit = max( lowerLimit, _value * it->mulValue + it->addValue );
      }
      else if ( it->constraint == NDb::STATCONSTRAINT_UPPERLIMIT )
      {
        upperLimit = min( upperLimit, _value * it->mulValue + it->addValue );
      }
      else
      {
        if ( !it->top )
        {
          add += it->addValue;
          mul *= it->mulValue;
        }
        else
        {
          add_top += it->addValue;
          mul_top *= it->mulValue;
        }
      }
    }

    float result = ( _value * mul + add ) * mul_top + add_top;

    return Clamp( result, lowerLimit, upperLimit );
  }

private:
	void OnSerialize( IBinSaver &f ) { if ( f.IsReading() ) isCacheValid = false; }

public:
  ValueWithModifiers() : cachedValue( 0.0f ), isCacheValid( false ), baseValue( 0.0f ), currentModifierID( 0 ) {}
	ValueWithModifiers( float base ) : cachedValue( 0 ), isCacheValid( false ), baseValue( base ), currentModifierID( 0 ) {}

  float GetBaseValue() const { return baseValue; }

  bool IsCacheValid() const { return isCacheValid; };

  void SetBaseValue( float _baseValue )
	{
		if ( fabs( baseValue - _baseValue ) < EPS_VALUE )
      return;

		baseValue = _baseValue;
		isCacheValid = false;
	}

	const Modifier* Retrieve( int id ) const
	{ 
		vector<Modifier>::const_iterator modifier = find( modifiers.begin(), modifiers.end(), id );
		return modifier != modifiers.end() ? modifier : 0;
	}

  // Retrieves value modifiers to the destination ValueWithModifiers container. Modifiers of the
  // specific provider are retreived or any if the requested provider is PF_Core::INVALID_OBJECT_ID.
  void Retrieve(ValueWithModifiers *destination, int provider) const
  {
    if (!destination)
      return;

    for ( vector<Modifier>::const_iterator it = modifiers.begin(), end = modifiers.end(); it != end; ++it )
    {
      if (it->provider == provider || provider == PF_Core::INVALID_OBJECT_ID)
      {
        destination->AddModifier(it->mulValue, it->addValue, it->provider, it->top);
      }
    }
  }

  int AddModifier( float mulValue, float addValue, int provider, bool top = false, NDb::EStatConstraint constraint = NDb::STATCONSTRAINT_NONE )
	{
		modifiers.push_back( Modifier( currentModifierID, provider, mulValue, addValue, top, constraint ) );
		isCacheValid = false;
		return currentModifierID++;
	}

  void UpdateModifier( int id, float newMulValue, float newAddValue )
  {
		vector<Modifier>::iterator modifier = find( modifiers.begin(), modifiers.end(), id );
		NI_VERIFY( modifier != modifiers.end() , "Modifier assumed to be present", return; );
    if ( modifier->mulValue == newMulValue && modifier->addValue == newAddValue )
      return;
    modifier->mulValue = newMulValue;
    modifier->addValue = newAddValue;
		isCacheValid = false;
  }

  void UpdateModifierAdd( int id, float newAddValue )
  {
		vector<Modifier>::iterator modifier = find( modifiers.begin(), modifiers.end(), id );
		NI_VERIFY( modifier != modifiers.end() , "Modifier assumed to be present", return; );
    if ( modifier->addValue == newAddValue )
      return;
    modifier->addValue = newAddValue;
		isCacheValid = false;
  }

  void UpdateModifierMul( int id, float newMulValue )
  {
		vector<Modifier>::iterator modifier = find( modifiers.begin(), modifiers.end(), id );
		NI_VERIFY( modifier != modifiers.end() , "Modifier assumed to be present", return; );
    if ( modifier->mulValue == newMulValue )
      return;
    modifier->mulValue = newMulValue;
		isCacheValid = false;
  }

  void RemoveModifier( int id )
  {
    // NUM_TASK Проверка на отсутствие модификаторов
    if (!modifiers.empty() && modifiers.begin() != NULL)
    {
		  vector<Modifier>::iterator modifier = find( modifiers.begin(), modifiers.end(), id );
		  NI_VERIFY( modifier != modifiers.end() , "Modifier assumed to be present", return; );
		  modifiers.erase( modifier );
      isCacheValid = false;
    }
  }

  void RemoveModifiers( int provider )
	{
		for ( vector<Modifier>::iterator it = modifiers.begin(); it != modifiers.end(); )
		{
			if ( it->provider == provider )
			{
				it = modifiers.erase( it );
				isCacheValid = false;
			}
			else
				++it;
		}
	}

  void EnableModifier( int id, bool active )
	{
		vector<Modifier>::iterator modifier = find( modifiers.begin(), modifiers.end(), id );
		NI_VERIFY( modifier != modifiers.end() , "Modifier assumed to be present", return; );
    isCacheValid = modifier->active == active;
		modifier->active = active;
	}

  void EnableModifiers( int provider, bool active )
	{
		for ( vector<Modifier>::iterator it = modifiers.begin(); it != modifiers.end(); ++it )
		{
			if ( it->provider == provider )
			{
				isCacheValid &= ( it->active == active );
				it->active = active;
			}
		}
	}

	virtual float GetValue() const
  {
    if ( !isCacheValid )
    {
      cachedValue = CalculateValue( baseValue );
      isCacheValid = IsProcessorStateForLogic();
    }

    return cachedValue;
  }

  virtual float GetAbsModification( int modifierID ) const
  {
    float valWithoutMod = CalculateValue( baseValue, modifierID );
    float valWithMod = CalculateValue( baseValue );
    return abs(valWithMod - valWithoutMod);
  }


  // Used by cheat and LuaSetUnitStat
  virtual void SetValue( float newValue )
  {
    SetBaseValue( newValue );
  }

  bool HasModifiers() const { return !modifiers.empty(); }
  const vector<Modifier>& GetModifiers() const { return modifiers; }

protected:
  mutable float cachedValue;
	mutable bool isCacheValid;

  friend struct StatValueWithModifiers;

  ZDATA
	int              currentModifierID;
  //ZNOCRC
	float            baseValue;
  vector<Modifier> modifiers;
  //ZNOCRCEND
	ZONSERIALIZE
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(2,&currentModifierID); f.Add(3,&baseValue); f.Add(4,&modifiers); OnSerialize( f ); return 0; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct StatValueWithModifiers : public ValueWithModifiers
{
public:
#ifndef _SHIPPING
  // cheated version
  StatValueWithModifiers() : ValueWithModifiers(), pCore(NULL), cheatAddValue(0.0f) {}
  StatValueWithModifiers( float base ) : ValueWithModifiers( base ), pCore(NULL), cheatAddValue(0.0f) {}
#else
  StatValueWithModifiers() : ValueWithModifiers(), pCore(NULL) {}
  StatValueWithModifiers( float base ) : ValueWithModifiers( base ), pCore(NULL) {}
#endif

  void SetCore( ValueWithModifiers* pCore_ )
  {
    NI_VERIFY( pCore_ != this, "Don't do that! It's a kinda stupid!", return );
    pCore = pCore_;
  }

  ValueWithModifiers const* GetCore() const { return pCore; }

  float GetCoreValue() const { return pCore ? pCore->GetValue() : baseValue; }

  void SetCoreValue( float _baseValue )
  {
    if ( pCore )
    {
      pCore->SetBaseValue( _baseValue );
      isCacheValid &= pCore->isCacheValid;
    }
    else
    {
      SetBaseValue( _baseValue );
    }
  }

  void CopyUnmodifiedValue( StatValueWithModifiers const* secondStat )
  {
    baseValue = secondStat->baseValue;
    if ( pCore && secondStat->GetCore() )
    {
      pCore->SetBaseValue( secondStat->GetCoreValue() );
    }
    isCacheValid = false;
  }

  virtual float GetValue() const
  {
    if ( !isCacheValid )
    {
      cachedValue = CalculateValue( GetUnmodifiedValue() );
      isCacheValid = IsProcessorStateForLogic();
    }

    return cachedValue;
  }

  virtual float GetAbsModification( int modifierID ) const
  {
    float valWithoutMod = CalculateValue( GetUnmodifiedValue(), modifierID );
    float valWithMod = CalculateValue( GetUnmodifiedValue() );
    return abs(valWithMod - valWithoutMod);
  }

  float GetUnmodifiedValue() const
  {
#ifndef _SHIPPING
    // cheated version
    if ( pCore )
      return baseValue + cheatAddValue + pCore->GetValue(); // yes, modified Core is used

    return baseValue + cheatAddValue;
#else
    if ( pCore )
      return baseValue + pCore->GetValue(); // yes, modified Core is used

    return baseValue;
#endif
  }

  void RemoveCoreModifiers( int provider )
  {
    if ( pCore )
    {
      pCore->RemoveModifiers( provider );
      isCacheValid &= pCore->isCacheValid;
    }
    else
    {
      RemoveModifiers( provider );
    }
  }

  int AddCoreModifier( float mulValue, float addValue, int provider, bool top = false )
  {
    if ( pCore )
    {
      isCacheValid = false;
      return pCore->AddModifier( mulValue, addValue, provider, top );
    }

    return AddModifier( mulValue, addValue, provider, top );
  }

#ifndef _SHIPPING
  // method for hero_force cheat
  void SetCheatModifier( float addValue )
  {
    cheatAddValue = addValue;
    isCacheValid = false;
  }

  float GetCheatModifier() const { return cheatAddValue; }
#endif

  // Used by cheat and LuaSetUnitStat
  virtual void SetValue( float newValue )
  {
#ifndef _SHIPPING
    newValue -= cheatAddValue; // modifier from hero_force cheat
#endif
    if ( pCore )
      newValue -= pCore->GetValue();

    SetBaseValue(newValue); // This cheat affects only Base value, not Core
  }

private:
  ZDATA_(ValueWithModifiers)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(ValueWithModifiers*)this); return 0; }
private:
  ValueWithModifiers* pCore; // Modifiers to the Core are applied only by hero_force cheat
#ifndef _SHIPPING
  float cheatAddValue;
#endif
};

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
