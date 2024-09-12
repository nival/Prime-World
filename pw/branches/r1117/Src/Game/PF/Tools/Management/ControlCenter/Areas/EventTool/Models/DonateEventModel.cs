using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using AccountLib;
using Castle.Components.DictionaryAdapter;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class DonateRewardModel
  {
    [DisplayName("Lootboxes")]
    [Required]
    public string Lootboxes { get; set; }

    public DonateRewardModel()
    {
    }

    public DonateRewardModel(DonateReward info)
    {
      Lootboxes = ConvertLootboxesInfoToString(info.Lootboxes);
    }

    public DonateReward ToTType()
    {
      return new DonateReward()
      {
        Lootboxes = ConvertLootboxesStringToInfo(Lootboxes),
      };
    }

    private List<string> ConvertLootboxesStringToInfo(string lootboxes)
    {
      List<string> result = new List<string>();
      foreach (var lootboxData in lootboxes.Split(','))
      {
        var kvpStr = lootboxData.Trim().Split(':');
        var kvp = new KeyValuePair<string, int>(kvpStr[0], kvpStr.Length > 1 ? int.Parse(kvpStr[1]) : 1);
        for (int i = 0; i < kvp.Value; i++)
        {
          result.Add(kvp.Key);
        }
      }

      return result;
    }

    private string ConvertLootboxesInfoToString(List<string> lootboxes)
    {
      var map = new Dictionary<string, int>();
      foreach (var lootboxId in lootboxes)
      {
        if (map.ContainsKey(lootboxId))
          map[lootboxId]++;
        else
          map[lootboxId] = 1;
      }

      string result = "";
      foreach (var kvp in map)
      {
        result += kvp.Key;
        if (kvp.Value > 1)
          result += string.Format(":{0}", kvp.Value);

        result += ",";
      }

      return result.TrimEnd(',');
    }

    public DonateRewardModel Clone()
    {
      return new DonateRewardModel
      {
        Lootboxes = Lootboxes
      };
    }
  }

  public class DonateRangeModel
  {
    [DisplayName("AmountFrom")]
    [Required]
    public int AmountFrom { get; set; }

    [DisplayName("AmountTo")]
    [Required]
    public int AmountTo { get; set; }

    [DisplayName("Rewards")]
    [Required]
    public List<DonateRewardModel> Rewards { get; set; }


    #region Helper Fields

    public int Index { get; set; }
    public string CommandPrefix { get; set; }

    #endregion

    public DonateRangeModel()
    {    
      Rewards = new List<DonateRewardModel>();
    }

    public DonateRangeModel(DonateRange info)
    {
      AmountFrom = info.AmountFrom;
      AmountTo = info.AmountTo;
      Rewards = new List<DonateRewardModel>();
      Rewards.AddRange(info.Rewards.Select(reward => new DonateRewardModel(reward)));
    }

    public DonateRange ToTType()
    {
      return new DonateRange()
      {
        AmountFrom = AmountFrom,
        AmountTo = AmountTo,
        Rewards = Rewards.Select(r => r.ToTType()).ToList(),
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
        case "reward_add":
          Rewards.Add(new DonateRewardModel());
          break;
        case "reward_remove":
          Rewards.RemoveAt(param);
          break;
        case "reward_up":
          Utils.CommandElementMove(param, Rewards);
          break;
        case "reward_down":
          Utils.CommandElementMove(param + 1, Rewards);
          break;
        case "reward_clone":
          Rewards.Add(Rewards[param].Clone());
          break;
        default:
          return false;
      }
      return true;
    }

    public DonateRangeModel Clone()
    {
      return new DonateRangeModel
      {
        AmountFrom = AmountFrom,
        AmountTo = AmountTo,
        Rewards = new List<DonateRewardModel>(Rewards.Select(r => r.Clone()))
      };
    }
  }

  public class DonateEventModel //: INewPricesListModel<SkinPriceInfoModel>
  {
    #region CommandsDefines

    //public const string RangeRewardCommand = "range_reward";
    public const string RangeCommand = "range";

    #endregion

    #region Common Data Fields

    [DisplayName("Event Id")]
    public int Id { get; set; }

    [DisplayName("Internal description")]
    [Required]
    public string Description { get; set; }

    [DisplayName("Starting time")]
    [Required]
    public DateTime StartTime { get; set; }

    [DisplayName("Ending time")]
    [Required]
    public DateTime EndTime { get; set; }

    [DisplayName("Enabled?")]
    [Required]
    public bool Enabled { get; set; }

    #endregion

    #region Specific Data Fields
    
    [DisplayName("Ranges")]
    [Required]
    public List<DonateRangeModel> Ranges { get; set; }
    
    #endregion


    public bool New { get; set; }

    public DonateEventModel()
    {
      Ranges = new List<DonateRangeModel>();
    }


    public DonateEventModel(DonateEvent info)
    {
      Id = info.PersistentId;
      Description = info.Description;
      Enabled = info.Enabled;
      StartTime = info.StartTime.FromUnixTimestamp();
      EndTime = info.EndTime.FromUnixTimestamp();

      Ranges = new List<DonateRangeModel>();
      Ranges.AddRange(info.Ranges.Select(p => new DonateRangeModel(p)));
    }


    public override string ToString()
    {
      return
        String.Format(
          "DonateEventModel(Id: {0}, Description: {1}, Enabled: {2}, StartTime: {3}, EndTime: {4})",
          Id, Description, Enabled, StartTime, EndTime);
    }

    public DonateEvent ToTType()
    {
      return new DonateEvent()
      {
        PersistentId = Id,
        Description = Description,
        StartTime = StartTime.ToUnixTimestamp(),
        EndTime = EndTime.ToUnixTimestamp(),
        Enabled = Enabled,
        Ranges = Ranges.Select(r => r.ToTType()).ToList(),
      };
    }

    public void PrepareControlFields()
    {
      New = Id == 0;
      string rangeCommandPrefix = RangeCommand + "_command:";
      for (int i = 0; i < Ranges.Count; i++)
      {
        Ranges[i].PrepareControlFields(i, rangeCommandPrefix);
      }
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
        case RangeCommand + "_add":
          Ranges.Add(new DonateRangeModel());
          break;
        case RangeCommand + "_remove":
          Ranges.RemoveAt(param);
          break;
        case RangeCommand + "_up":
          Utils.CommandElementMove(param, Ranges);
          break;
        case RangeCommand + "_down":
          Utils.CommandElementMove(param + 1, Ranges);
          break;
        case RangeCommand + "_clone":
          Ranges.Add(Ranges[param].Clone());
          break;
        case RangeCommand + "_command":
          return ProcessRangeCommand(param, cmdArgs, startIdx + 2);
        default:
          return false;
      }

      return true;
    }

    private bool ProcessRangeCommand(int index, string[] cmdArgs, int startIndex)
    {
      if (index < 0 || index >= Ranges.Count)
        return false;
      return Ranges[index].ProcessCommand(cmdArgs, startIndex);
    }
  }
}