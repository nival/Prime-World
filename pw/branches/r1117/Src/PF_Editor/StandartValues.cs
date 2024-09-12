using EditorLib.Extensions;

namespace PF_Editor
{
  //l:\Documents\PF_AssetListFPP_Session.xls
  [CustomStandardValuesFor( "Locator.name" )]
  public enum ELocatorNameStandardValues
  {
    General = 0,
    Above,
    Ground,
    Body,
    Death,
    Head,
  }

  [CustomStandardValuesFor( "Node.Name" )]
  public enum EAGNodeNameStandardValues
  {
    move,
    idle,
    attack,
    death,
    dead,
    revive,
    happy,
    critical,
    ability1,
    ability2,
    ability3,
    ability4,
    ability5,
    friendship,
    sleep,
    sad,
    table,
    gym,
    washtab,
    playground,
  }
}
