using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Web.Mvc;
using System.Web.UI.MobileControls.Adapters;
using AccountLib;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.EventTool.Models
{
  public class TradeEventModel
  {
    #region Common Data Fields

    [DisplayName("Event Id")]
    public int EventId { get; set; }

    [DisplayName("Internal description")]
    [Required]
    public string Description { get; set; }

    [DisplayName("Event locale")]
    [Required]
    public string Locale { get; set; }

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

    [Required]
    public int TradeEventGUID { get; set; }

    [DisplayName("Completion Talent PersistentID")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string CompletionTalentId { get; set; }

    [DisplayName("Completion talent convert ratio")]
    [Required]
    [Range(1, 1000000, ErrorMessage = "Must be in range from 1 to 1000000")]
    public int CompletionTalentRatio { get; set; }

    [DisplayName("ExperienceCurrencyName")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string ExperienceCurrencyName { get; set; }

    [DisplayName( "BannerUrl (1107x597 (мб порезано до 698x597 на узких мониках))" )]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string BannerUrl { get; set; }

    [DisplayName("Title")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Title { get; set; }

    [DisplayName("Text")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string Text { get; set; }

    [DisplayName("RewardsBlockTitle")]
    [Required]
    [DisplayFormat(ConvertEmptyStringToNull = false)]
    public string RewardsBlockTitle { get; set; }

    [DisplayName("Groups")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("TradeEventGroupModel")]
    public List<TradeEventGroupModel> TradeEventGroups { get; set; }

    [DisplayName("ExperienceRewardRelations")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    public List<ExperienceRewardRelation> ExperienceRewardRelations { get; set; }

    [DisplayName("WorldRatingRewardRelations")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    public List<WorldRatingRewardRelation> WorldRatingRewardRelations { get; set; }

    #endregion

    #region HelperFields

    public SelectList AvailableLocales { get; set; }
    public bool New { get; set; }

    #endregion

    #region CommandsDefines

    public const string WorldRatingNameCommand = "worldrating_reward";
    public const string ExperienceNameCommand = "experience_reward";
    public const string GroupNameCommand = "group";
    public const string MemberNameCommand = "member";

    #endregion

    public TradeEventModel()
    {
      EventId = 0;
      Description = string.Empty;
      Locale = string.Empty;
      RewardsBlockTitle = string.Empty;
      StartTime = DateTime.UtcNow.AddDays(1);
      EndTime = DateTime.UtcNow.AddDays(2);
      Enabled = false;
      TradeEventGUID = -1;

      TradeEventGroups = new List<TradeEventGroupModel>();
      ExperienceRewardRelations = new List<ExperienceRewardRelation>();
      WorldRatingRewardRelations = new List<WorldRatingRewardRelation>();
 
      New = true;
    }

    public TradeEventModel(AccountLib.TradeEventModel model)
    {
      EventId = model.PersistentId;
      Description = model.Description;
      Locale = model.Locale;
      StartTime = model.StartTime.FromUnixTimestamp();
      EndTime = model.EndTime.FromUnixTimestamp();
      Enabled = model.Enabled;

      TradeEventGUID = model.Guid;
      BannerUrl = model.BannerUrl;
      Title = model.Title;
      Text = model.Text;
      ExperienceCurrencyName = model.ExperienceCurrencyName;
      CompletionTalentId = model.CompletionTalentId;
      CompletionTalentRatio = model.CompletionTalentRatio;
      RewardsBlockTitle = model.RewardsBlockTitle;

      TradeEventGroups = model.TradeEventGroups.Select(q => new TradeEventGroupModel(q)).ToList();
      ExperienceRewardRelations = model.ExperienceRewardRelations.Select(q => new ExperienceRewardRelation(q)).ToList();
      WorldRatingRewardRelations = model.WorldRatingRewardRelations.Select(q => new WorldRatingRewardRelation(q)).ToList();
    }

    public AccountLib.TradeEventModel ToTType()
    {
      return new AccountLib.TradeEventModel
      {
        PersistentId = EventId,
        Description = Description,
        Locale = Locale,
        StartTime = StartTime.ToUnixTimestamp(),
        EndTime = EndTime.ToUnixTimestamp(),
        Enabled = Enabled,
        RewardsBlockTitle = RewardsBlockTitle,

        Guid = TradeEventGUID,
        Title = Title,
        Text = Text,
        BannerUrl = BannerUrl,
        CompletionTalentId = CompletionTalentId,
        CompletionTalentRatio = CompletionTalentRatio,
        ExperienceCurrencyName = ExperienceCurrencyName,
        TradeEventGroups = TradeEventGroups.Select(q => q.ToTType()).ToList(),
        ExperienceRewardRelations = ExperienceRewardRelations.Select(q => q.ToTType()).ToList(),
        WorldRatingRewardRelations = WorldRatingRewardRelations.Select(q => q.ToTType()).ToList(),
      };
    }

    public void PrepareControlFields()
    {
      New = EventId == 0;
      string stageCommandPrefix = GroupNameCommand + "_command:";
      for (int i = 0; i < TradeEventGroups.Count; i++)
      {
        TradeEventGroups[i].PrepareControlFields(i, stageCommandPrefix);
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
        case GroupNameCommand + "_add":
          TradeEventGroups.Add(new TradeEventGroupModel());
          break;
        case GroupNameCommand + "_remove":
          TradeEventGroups.RemoveAt(param);
          break;
        case GroupNameCommand + "_up":
          Utils.CommandElementMove(param, TradeEventGroups);
          break;
        case GroupNameCommand + "_down":
          Utils.CommandElementMove(param + 1, TradeEventGroups);
          break;
        case GroupNameCommand + "_clone":
          TradeEventGroups.Add(TradeEventGroups[param].Clone());
          break;
        case GroupNameCommand + "_command":
          return CommandGroupCommand(param, cmdArgs, startIdx + 2);
        default:
          if (cmd.Contains(ExperienceNameCommand))
            return CommandExperienceReward(cmd, param);
          else if (cmd.Contains(WorldRatingNameCommand))
            return CommandWorldRatingReward(cmd, param);
          
          return false;
      }

      return true;
    }

    private bool CommandGroupCommand(int index, string[] cmdArgs, int startIndex)
    {
      if (index < 0 || index >= TradeEventGroups.Count)
        return false;
      return TradeEventGroups[index].ProcessCommand(cmdArgs, startIndex);
    }

    private bool CommandExperienceReward(string cmd, int param)
    {
      switch (cmd)
      {
        case ExperienceNameCommand + "_add":
          ExperienceRewardRelations.Add(new ExperienceRewardRelation());
          break;
        case ExperienceNameCommand + "_remove":
          ExperienceRewardRelations.RemoveAt(param);
          break;
        case ExperienceNameCommand + "_up":
          Utils.CommandElementMove(param, ExperienceRewardRelations);
          break;
        case ExperienceNameCommand + "_down":
          Utils.CommandElementMove(param + 1, ExperienceRewardRelations);
          break;
        case ExperienceNameCommand + "_clone":
          ExperienceRewardRelations.Add(ExperienceRewardRelations[param].Clone());
          break;
        default:
          return false;
      }
      return true;
    }

    private bool CommandWorldRatingReward(string cmd, int param)
    {
      switch (cmd)
      {
        case WorldRatingNameCommand + "_add":
          WorldRatingRewardRelations.Add(new WorldRatingRewardRelation());
          break;
        case WorldRatingNameCommand + "_remove":
          WorldRatingRewardRelations.RemoveAt(param);
          break;
        case WorldRatingNameCommand + "_up":
          Utils.CommandElementMove(param, WorldRatingRewardRelations);
          break;
        case WorldRatingNameCommand + "_down":
          Utils.CommandElementMove(param + 1, WorldRatingRewardRelations);
          break;
        case WorldRatingNameCommand + "_clone":
          WorldRatingRewardRelations.Add(WorldRatingRewardRelations[param].Clone());
          break;
        default:
          return false;
      }
      return true;
    }
  }

  public class ExperienceRewardRelation
  {
    [DisplayName("Reward")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("RollEventItemModel")]
    public RollEventItemModel Reward { get; set; }

    [Required]
    public int RewardCount { get; set; }
    [Required]
    public int Experience { get; set; }
    [Required]
    public bool IsMinor { get; set; }

    public ExperienceRewardRelation()
    {
      Reward = new RollEventItemModel(RollEventItemTypeEnum.Lootbox, false);
      RewardCount = 1;
    }

    public ExperienceRewardRelation(AccountLib.ExperienceRewardRelation model)
    {
      Reward = new RollEventItemModel(model.Reward, false);
      RewardCount = model.RewardCount;
      Experience = model.Experience;
      IsMinor = model.IsMinor;
    }

    public AccountLib.ExperienceRewardRelation ToTType()
    {
      return new AccountLib.ExperienceRewardRelation
      {
        Reward = Reward.ToRollEventItem(),
        RewardCount = RewardCount,
        Experience = Experience,
        IsMinor = IsMinor
      };
    }

    public ExperienceRewardRelation Clone()
    {
      return new ExperienceRewardRelation
      {
        Reward = Reward.Clone(),
        RewardCount = RewardCount,
        Experience = Experience,
        IsMinor = IsMinor
      };
    }
  }

  public class WorldRatingRewardRelation
  {
    [DisplayName("Reward")]
    [Required(ErrorMessage = "If you see this message, ask programmer!")]
    [UIHint("RollEventItemModel")]
    public RollEventItemModel Reward { get; set; }

    [Required]
    public int RewardCount { get; set; }
    [Required]
    public int WorldPosition { get; set; }

    public WorldRatingRewardRelation()
    {
      Reward = new RollEventItemModel(RollEventItemTypeEnum.Lootbox, false);
      RewardCount = 1;
    }

    public WorldRatingRewardRelation(AccountLib.WorldRatingRewardRelation model)
    {
      Reward = new RollEventItemModel(model.Reward, false);
      RewardCount = model.RewardCount;
      WorldPosition = model.WorldPosition;
    }

    public AccountLib.WorldRatingRewardRelation ToTType()
    {
      return new AccountLib.WorldRatingRewardRelation
      {
        Reward = Reward.ToRollEventItem(),
        RewardCount = RewardCount,
        WorldPosition = WorldPosition
      };
    }

    public WorldRatingRewardRelation Clone()
    {
      return new WorldRatingRewardRelation
      {
        Reward = Reward.Clone(),
        RewardCount = RewardCount,
        WorldPosition = WorldPosition
      };
    }
  }
}