using System.Collections.Generic;
using DBCodeGen.BasicTypes;
using DBCodeGen.CodeGeneration;

namespace ResourceSystem.ResourceDesc
{

// List of heroes that will be aviable in our "game"
public enum Heroes
{
  SuperHero,
  SpiderMan,
  Batman,
}

public class HeroStat
{
  public float health = 50;
  public float strength = 10;
  public float dexterity = 10;
}

// This is Ability class that is base for every heroe's ability. we define it as class because
// - we need inheritance for abilities
// - we need sharing of abilities among different heroes
// [TypeId] means that every child of this class whould have typeId field and GetObjectTypeID() function and we can
// determinate type of Ability without dynamic_cast
// [NonTerminal] means that we should not have instances of this class at all
[TypeId]
[NonTerminal]
public class Ability : DBResource
{
  public string name;
}

// FlyAbility is child of Ability and we have specify its TypeId exactly
[TypeId( 0x4969C440 )]
public class FlyAbility : Ability
{
  public float speed = 1.0f;
  public float maxHeight = 20.0f;
}

[TypeId( 0x4969C441 )]
public class JumpAbility : Ability
{
  public float distance = 10.0f;
}

[TypeId( 0x4969C442 )]
public class ThrowAbility : Ability
{
  public float damage = 0.0f;
  public float maxDistance = 10.0f;
}

// Just a class for Hero, its name, its stats and array of abilities (can be empty)
public class Hero : DBResource
{
  public string name;
  // HeroStat is the structure (in meaning of resource system) so it cannot exists without Hero object
  public HeroStat stats = new HeroStat();
  // Ability is the class, we have to referenced it via DBPtr, instance of this class can exists alone
  // and can be shared among different objects
  public List<DBPtr<Ability>> abilities;
}

// This object will be "entry point" for entire resource system. In out project we'll have only and only one NDb::Get<>( ... )
public class GameRoot : DBResource
{
  // Amount of elements in heroes array exactly equals to amount of elements in Heroe enumeration
  [EnumArray( typeof( Heroes ) )]
  public List<DBPtr<Hero>> heroes;
}

}