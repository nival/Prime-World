using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using ControlCenter.Areas.GM;
using ControlCenter.Areas.GM.Models;

namespace ControlCenter.Areas.MassOperations.Models
{
  public enum MassOperationAuidsList
  {
    FromFile = 0,
    CopyPaste = 1,
  }

  public enum MassOperationType
  {
    UnlockFlag = 0,
    LockFlag,
    AddTalent,
    AddTalents,
    PremiumAccount,
    SendMessageToUser,
    GiveLamp,
    AddSkin,
    DeleteSkin,
    UnlockHero,
    AddBuilding,
    EditAccount,
    FlushServerId,
  }

  public class MassOperationsModel
  {
    public MassOperationAuidsList AuidsListType { get; set; }

    [DisplayName( "Operation type" )]
    public MassOperationType MassOperationType { get; set; }

    [RegularExpression( @"((\d)+(\s)*(,)(\s)*)*(\d)+" )]
    [Required]
    public string Auids { get; set; }

    [DisplayName( "Flag PersistentId" )]
    public string FlagId { get; set; }

    [DisplayName( "Talent PersistentId (number id)" )]
    public int Talent { get; set; }

    [DisplayName( "Talent PersistentIds (number id), comma separated" )]
    public string Talents { get; set; }

    [DisplayName( "Days of premium account" )]
    public int PremiumDays { get; set; }

    [DisplayName( "Message for user" )]
    public string UserMessage { get; set; }

    public LampModel LampSettings { get; set; }

    [DisplayName( "Skin PersistentId (string)" )]
    public string HeroSkinId { get; set; }

    [DisplayName( "Hero PersistentId" )]
    public string HeroClassId { get; set; }

    [DisplayName( "Building PersistentId" )]
    public string BuildingPersistentId { get; set; }

    public AccountModel AccountSettings { get; set; }

    public SelectList MassOperationTypes { get; set; }
    public SelectList HeroList;
    public SelectList ConstructionList;
    public SelectList FactionList;

    public List<long> GetAuids()
    {
      return GetAuids( Auids );
    }

    public static List<long> GetAuids( string auidsString )
    {
      List<long> auidsInt;

      try
      {
        var auids = auidsString.Split( '\n' );
        auidsInt =
          ( from auid in auids where !String.IsNullOrEmpty( auid.Trim() ) select Convert.ToInt64( auid.Trim() ) ).ToList();
      }
      catch ( OverflowException )
      {
        return null;
      }
      catch ( FormatException )
      {
        return null;
      }

      return auidsInt;
    }

    public MassOperationsModel()
    {
      Auids = "";
      Talents = "";
      LampSettings = new LampModel();
      AccountSettings = new AccountModel();
      FlagId = "";
      HeroSkinId = "";
      UserMessage = "";
    }

    public void FillSelectLists(IAccountService accountSvc)
    {
      MassOperationTypes = new SelectList( new List<SelectListItem>
      {
        new SelectListItem {Text = "UnlockFlag", Value = "UnlockFlag"},
        new SelectListItem {Text = "LockFlag", Value = "LockFlag"},
        new SelectListItem {Text = "AddTalent", Value = "AddTalent"},
        new SelectListItem {Text = "AddTalents", Value = "AddTalents"},
        new SelectListItem {Text = "PremiumAccount", Value = "PremiumAccount"},
        new SelectListItem {Text = "SendMessageToUser", Value = "SendMessageToUser"},
        new SelectListItem {Text = "GiveLamp", Value = "GiveLamp"},
        new SelectListItem {Text = "AddSkin", Value = "AddSkin"},
        new SelectListItem {Text = "DeleteSkin", Value = "DeleteSkin"},
        new SelectListItem {Text = "UnlockHero", Value = "UnlockHero"},
        new SelectListItem {Text = "LockHero", Value = "LockHero"},
        new SelectListItem {Text = "AddBuilding", Value = "AddBuilding"},
        new SelectListItem {Text = "EditAccount", Value = "EditAccount"},
        new SelectListItem {Text = "FlushServerId", Value = "FlushServerId"},
      } );
      HeroList = new SelectList( accountSvc.GetHeroesCatalog().Select( x => new SelectListItem { Text = x.HeroName, Value = x.HeroName } ) );
      ConstructionList = CastleBuildingsCatalog.GetPersistentIdOnlySelectList();
      FactionList = new SelectList( Enum.GetValues(typeof(FractionEnum)).Cast<FractionEnum>().Select(v => new SelectListItem {
            Text = v.ToString(),
            Value = ((int)v).ToString()
      } ).Reverse().ToList() );
    }

    public static string GetAllTexts( SelectList list )
    {
      return String.Join( "\", \"",
        list.Items.OfType<SelectListItem>().ToList().Count == 0
          ? list.Select( x => x.Text ).ToArray()
          : list.Items.OfType<SelectListItem>().ToList().Select( x => x.Text ).ToArray() );
    }

    public static string GetAllValues( SelectList list )
    {
      return String.Join( "\", \"", list.Items.OfType<SelectListItem>().ToList().Select( x => x.Value ).ToArray() );
    }

    public List<int> GetTalents()
    {
      if (Talents == "") return new List<int>();
      return new List<int>(Talents.Split(',').Select(int.Parse));
    }
  }

  public class LampModel
  {    
    [DisplayName( "Bonus" )]
    public int Bonus { get; set; }

    [DisplayName( "Gold bonus" )]
    public int Gold { get; set; }

    [DisplayName( "Transaction" )]
    public int Transaction { get; set; }

    [DisplayName( "Duration" )]
    public long Duration { get; set; }
  }

  public class AccountModel
  {
    public int Silver { get; set; }
    [DisplayName( "Wood/Silk" )]
    public int Resource1 { get; set; }
    [DisplayName( "Ore/Sap" )]
    public int Resource2 { get; set; }
    [DisplayName( "Food" )]
    public int Resource3 { get; set; }
    public int Perl { get; set; }
    public int RedPerl { get; set; }
    [DisplayName( "ClanWar points" )]
    public int CWPoints { get; set; }
    public FractionEnum Fraction { get; set; }
    public string Currencies { get; set; }
  }

  public class MassOperationInfoModel
  {
    public int OperationId { get; set; }

    [DisplayName( "Start time" )]
    public DateTime StartTime { get; set; }

    [DisplayName( "End time" )]
    public DateTime EndTime { get; set; }

    [DisplayName( "Operation type" )]
    public MassOperationType OperationType { get; set; }

    [DisplayName( "State" )]
    public bool Finished { get; set; }

    public string FailedAuids { get; set; }
  }
}