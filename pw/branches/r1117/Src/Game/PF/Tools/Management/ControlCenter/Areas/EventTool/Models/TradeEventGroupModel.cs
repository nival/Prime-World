using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class TradeEventGroupModel
  {
    #region Data Fields

    [DisplayName("Name")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Name { get; set; }

    [UIHint("TradeGroupMemberModel")]
    public List<TradeGroupMemberModel> TradeGroupMembers { get; set; }

    #endregion

    #region Helper Fields

    public int Index { get; set; }
    public string CommandPrefix { get; set; }

    #endregion

    public TradeEventGroupModel()
    {
      Name = string.Empty;
      TradeGroupMembers = new List<TradeGroupMemberModel>();
    }

    public TradeEventGroupModel(AccountLib.TradeEventGroupModel model)
    {
      Name = model.Name;
      TradeGroupMembers = model.TradeGroupMembers.Select(q => new TradeGroupMemberModel(q)).ToList();
    }

    public AccountLib.TradeEventGroupModel ToTType()
    {
      return new AccountLib.TradeEventGroupModel
      {
        Name = Name,
        TradeGroupMembers = TradeGroupMembers.Select(q => q.ToTType()).ToList()
      };
    }

    public TradeEventGroupModel Clone()
    {
      return new TradeEventGroupModel
      {
        Name = Name,
        TradeGroupMembers = new List<TradeGroupMemberModel>(TradeGroupMembers.Select(q => q.Clone()))
      };
    }

    public void PrepareControlFields(int index, string commandPrefix)
    {
      Index = index;
      CommandPrefix = commandPrefix + Index + ":";
    }

    public bool ProcessCommand(string[] cmdArgs, int startIdx)
    {
      if (cmdArgs.Length < startIdx + 2)
        return false;

      string cmd = cmdArgs[startIdx];
      int param;
      if (!int.TryParse(cmdArgs[startIdx + 1], out param))
        return false;

      switch (cmd)
      {
        case "member_add":
          TradeGroupMembers.Add(new TradeGroupMemberModel());
          break;
        case "member_remove":
          TradeGroupMembers.RemoveAt(param);
          break;
        case "member_up":
          Utils.CommandElementMove(param, TradeGroupMembers);
          break;
        case "member_down":
          Utils.CommandElementMove(param + 1, TradeGroupMembers);
          break;
        case "member_clone":
          TradeGroupMembers.Add(TradeGroupMembers[param].Clone());
          break;
        default:
          return false;
      }
      return true;
    }
  }

  public class TradeGroupMemberModel
  {
    #region Data Fields

    [DisplayName("Name")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Name { get; set; }

    [DisplayName("Image")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Image { get; set; }

    [DisplayName("CurrencyName")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string CurrencyName { get; set; }

    [DisplayName("CurrencyCostPerExp")]
    [Required]
    public double CurrencyCostPerExp { get; set; }

    [DisplayName("RewardA")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("RollEventItemModel")]
    public RollEventItemModel RewardA { get; set; }

    [DisplayName("RewardACost")]
    [Required]
    public int RewardACost { get; set; }

    [DisplayName("RewardB")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("RollEventItemModel")]
    public RollEventItemModel RewardB { get; set; }

    [DisplayName("RewardBCost")]
    [Required]
    public int RewardBCost { get; set; }
    
    #endregion

    public TradeGroupMemberModel()
    {
      Name = string.Empty;
      Image = string.Empty;
      CurrencyName = string.Empty;
      RewardA = new RollEventItemModel(RollEventItemTypeEnum.Lootbox, false);
      RewardB = new RollEventItemModel(RollEventItemTypeEnum.Lootbox, false);
    }

    public TradeGroupMemberModel(AccountLib.TradeGroupMemberModel model)
    {
      Name = model.Name;
      Image = model.Image;
      CurrencyName = model.CurrencyName;
      CurrencyCostPerExp = model.CurrencyCostPerExp;
      RewardA = new RollEventItemModel(model.RewardA, false);
      RewardACost = model.RewardACost;
      RewardB = new RollEventItemModel(model.RewardB, false);
      RewardBCost = model.RewardBCost;
    }

    public AccountLib.TradeGroupMemberModel ToTType()
    {
      return new AccountLib.TradeGroupMemberModel
      {
        Name = Name,
        Image = Image,
        CurrencyName = CurrencyName,
        CurrencyCostPerExp = CurrencyCostPerExp,
        RewardA = RewardA.ToRollEventItem(),
        RewardACost = RewardACost,
        RewardB = RewardB.ToRollEventItem(),
        RewardBCost = RewardBCost
      };
    }

    public TradeGroupMemberModel Clone()
    {
      return new TradeGroupMemberModel
      {
        Name = Name,
        Image = Image,
        CurrencyName = CurrencyName,
        CurrencyCostPerExp = CurrencyCostPerExp,
        RewardA = RewardA.Clone(),
        RewardACost = RewardACost,
        RewardB = RewardB.Clone(),
        RewardBCost = RewardBCost
      };
    }


  }
}