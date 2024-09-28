using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class SeasonEventShopGroupModel
  {
    #region Data Fields

    [DisplayName("Name")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Name { get; set; }

    [UIHint("SeasonEventShopItemModel")]
    public List<SeasonEventShopItemModel> Items { get; set; }

    #endregion

    #region Helper Fields

    public int Index { get; set; }
    public string CommandPrefix { get; set; }

    #endregion

    public SeasonEventShopGroupModel()
    {
      Name = string.Empty;
      Items = new List<SeasonEventShopItemModel>();
    }

    public SeasonEventShopGroupModel(AccountLib.SeasonEventShopGroup model)
    {
      Name = model.Name;
      Items = model.Items.Select(q => new SeasonEventShopItemModel(q)).ToList();
    }

    public AccountLib.SeasonEventShopGroup ToTType()
    {
      return new AccountLib.SeasonEventShopGroup
      {
        Name = Name,
        Items = Items.Select(q => q.ToTType()).ToList()
      };
    }

    public SeasonEventShopGroupModel Clone()
    {
      return new SeasonEventShopGroupModel
      {
        Name = Name,
        Items = new List<SeasonEventShopItemModel>(Items.Select(q => q.Clone()))
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
        case "item_add":
          Items.Add(new SeasonEventShopItemModel());
          break;
        case "item_remove":
          Items.RemoveAt(param);
          break;
        case "item_up":
          Utils.CommandElementMove(param, Items);
          break;
        case "item_down":
          Utils.CommandElementMove(param + 1, Items);
          break;
        case "item_clone":
          Items.Add(Items[param].Clone());
          break;
        default:
          return false;
      }
      return true;
    }
  }

  public class SeasonEventShopItemModel
  {
    #region Data Fields

    [DisplayName("Name")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Name { get; set; }

    [DisplayName("Image")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Image { get; set; }

    [DisplayName("Lootbox Id")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string LootboxId { get; set; }

    [DisplayName("Cost")]
    [Required]
    public int Cost { get; set; }

    [DisplayName("Limit")]
    [Required]
    [DefaultValue(-1)]
    public int Limit { get; set; }

    #endregion

    public SeasonEventShopItemModel()
    {
      Name = string.Empty;
      Image = string.Empty;
      LootboxId = string.Empty;
      Cost = 0;
      Limit = -1;
    }

    public SeasonEventShopItemModel(AccountLib.SeasonEventShopItem model)
    {
      Name = model.Name;
      Image = model.Image;
      LootboxId = model.LootboxId;
      Cost = model.Cost;
      Limit = model.Limit;
    }

    public AccountLib.SeasonEventShopItem ToTType()
    {
      return new AccountLib.SeasonEventShopItem
      {
        Name = Name,
        Image = Image,
        Cost = Cost,
        Limit = Limit,
        LootboxId = LootboxId
      };
    }

    public SeasonEventShopItemModel Clone()
    {
      return new SeasonEventShopItemModel
      {
        Name = Name,
        Image = Image,
        Cost = Cost,
        Limit = Limit,
        LootboxId = LootboxId
      };
    }


  }
}