//#include "../Types/UI.cs"

using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using PF_GameLogic.DBAbility;
using Scene.DBScene;
using Scene.DBSceneBase;

namespace PF_GameLogic.DBMinigamesTypes
{

  public enum MinigameClientType
  {
    Local,
    Remote,
    Any,
  }

  public enum MinigameVisualState
  {
    None,
    Session,
    Clinic_Lobby,
    Clinic_InGame,
    Clinic_Shop,
    Easel_Lobby,
    Easel_LeavingLobby,
    Easel_InGame,
  }

  public enum ChangesApplyType
  {
    DoNotApply,
    ApplyDefault,
    ApplyAbsoluteRotation,
    ApplyAbsoluteAll,
    ApplyRelational,
  }

  public enum EBidonType
  {
    None,
    Speedclock,
    Slowdownglue,
    Magicpointer,
    Palette,
  }

  [TypeId(0xE96AD341)]
  public class MinigameVisualStateChange : DBResource
  {
    public MinigameVisualState fromState = MinigameVisualState.None;
    public MinigameVisualState toState = MinigameVisualState.None;
    public MinigameClientType clientType = MinigameClientType.Any;

    [Description("Rotation and scale are absolute. Position is relative to minigame place position.")]
    public AnimatedPlacement newPlacement;
    public ChangesApplyType changePlacement = ChangesApplyType.DoNotApply;
  }

  [TypeId(0xE96B3440)]
  public class MinigamePlaceParams : DBResource
  {
    public List<DBPtr<MinigameVisualStateChange>> stateChanges = new List<DBPtr<MinigameVisualStateChange>>();
  }

}

namespace PF_Minigames.DBMinigames
{
  public class Bidon
  {
    public DBPtr<Ability> ability;
    public string commonNode;
    public string upperNode;
    public string commonMarker;
    public string upperMarker;
  }


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  [FactoryImpl("Construct", "PF_Minigames::MinigamesMain", "MinigamesMain.h")]
  public class DBMinigamesCommon : PF_GameLogic.DBGameLogic.MinigamesBasic
	{
    [Description("Camera position at minigame lobby screen")]
    public ViewCamera cameraOptions;
    public bool smoothCamera = false;

    [FieldCategory("Creeps Pool")]
    [Description("Name pool for melee creeps")]
    public TextRef namePoolMelee = new TextRef();

    [FieldCategory("Creeps Pool")]
    [Description("Name pool for range creeps")]
    public TextRef namePoolRange = new TextRef();

    [FieldCategory("Creeps Pool")]
    [Description("Name pool for siege creeps")]
    public TextRef namePoolSiege = new TextRef();


    [Description("Abilities in session for bidons")]
    [EnumArray(typeof(PF_GameLogic.DBMinigamesTypes.EBidonType))]
    public List<Bidon> sessionBidonAbilities; 
  }
}
