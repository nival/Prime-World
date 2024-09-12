using System.Collections.Generic;
using System.ComponentModel;
using Scene.DBScene;
using libdb.DB;
using PF_GameLogic.DBAbility;
using PF_GameLogic.DBUnit;

namespace PF_GameLogic.DBConsumable
{
  public enum EConsumableOrigin
  {
    Default,
    Shop,
    Minigame,
    Pickupable,
    Applicator,
    Script,
  }

  [TypeId(0xF68CB80)]
  [UseTypeName("ARCT")]
  [DBVersion(1)]
  [Custom( "Social" )]
  public class Consumable : Ability
  {
    [FieldCategory("Logic")]
    [Description("Cost of artifact")]
    public int naftaCost = 0;
    
    [FieldCategory("Logic")]
    [Description("Maximum quantity in one slot (stacking). Set 0 if item doesn't spend on use")]
    [IntMin(0)]
    public int maxQuantity = 1;

    [FieldCategory("Visual")]
    [Description("Visual object for lying consumable( chest, etc..)")]
    public DBPtr<Scene.DBSceneBase.GameObject> gameObject;

		[FieldCategory( "Logic" )]
		[Description( "Flag for determining potions" )]
		public bool isPotion = false;

    [Description( "Global consumable ID" )]
    public string persistentId = "";
	}

  [TypeId(0xF68CB81)]
  [UseTypeName("CNSH")]
  public class ConsumablesShop : DBResource
  {
    [Description("List of consumables")]
    public List<DBPtr<Consumable>> items = new List<DBPtr<Consumable>>();
    [Description("Interaction radius")]
    [FloatMin(0.0f)]
    public float interactionRadius = 10.0f;

    [Description("True if shop is secret")]
    public bool secretShop = false;
  }
}