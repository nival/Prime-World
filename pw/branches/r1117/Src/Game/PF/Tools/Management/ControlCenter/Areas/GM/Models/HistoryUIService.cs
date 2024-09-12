using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text.RegularExpressions;
using System.Web.Mvc;
using ControlCenter.Areas.GWEvents.Models;
using DAL.Entities;
using DAL.Repositories;
using log4net;

namespace ControlCenter.Areas.GM.Models
{
  public interface IHistoryUIService
  {
    List<LoginInfoModel> GetLoginHistory( long auid, int pageNum, out int pageQuant );
    List<BanOrMuteHistoryModel> GetBanAndMuteHistory( long auid, int pageNum, out int pageQuant );
    List<GMOperationInfoModel> GetGMOperationHistory( long auid, int pageNum, out int pageQuant );
    PlayerResourceFilterModel GetResourcesHistory(PlayerResourceFilterModel model);
    BanOrMuteHistoryModel GetBanMuteById(int id);
    List<FractionChangeHistoryModel> GetFractionChangeHistory(long auid, int pageNum, out int pageQuant);
    CWPlayerResourcesFilterModel GetCWPlayerResourcesHistory(CWPlayerResourcesFilterModel model);
    CWGuildResourcesFilterModel GetCWGuildResourcesHistory(CWGuildResourcesFilterModel model);
    LeavePointsFilterModel GetLeavePointsHistory(LeavePointsFilterModel model);
    LeavePointsFilterModel FillLeavePointsCounters(LeavePointsFilterModel model);
    RuneOperationsFilterModel GetRunesHistory(RuneOperationsFilterModel model);
    void GetGwEventHistoryByEvent(GWEventHistory model, int eventIdx, DateTime starTime, DateTime endTime);
    void GetGwEventHistoryByGuild(GWEventHistory model, long guildIdx, DateTime starTime, DateTime endTime);
    void GetGwEventHistoryByAuid(GWEventHistory model, int auid, DateTime starTime, DateTime endTime);
    void GetQuestEventsStagesModel(QuestEventsStepsModel model, int auid, DateTime starTime, DateTime endTime);
    void GetQuestEventsStepsModel(QuestEventsStepsModel model, int auid, int stage, DateTime starTime, DateTime endTime);
  }

  public class HistoryUIService : IHistoryUIService
  {
    private static ILog log = LogManager.GetLogger( typeof( HistoryUIService ) );
    private static int pageSize = 50;//количество записей на странице

    private IHistoryRecordsRepository historyRepo;
    private IGMOperationRepository gmoRepo;
    private IGMUserOperationRepository gmuoRepo;
    private IClaimRepository claimRepo;
    private IPlayerRepository playerRepo;
    private IGWEventsLogRepository gwEventsRepo;
    private IQuestEventsStagesRepository gwQuestEventsStagesRepo;
    private IQuestEventsStepsRepository gwQuestEventsStepsRepo;

    public HistoryUIService()
      : this(new HistoryRecordsRepository(), new GMOperationRepository(), new GMUserOperationRepository(), new ClaimRepository(), new PlayerRepository(), new GWEventsLogRepository(),
          new QuestEventsStagesRepository(), new QuestEventsStepsRepository())
    {
    }

    public HistoryUIService(IHistoryRecordsRepository historyRepo, IGMOperationRepository gmoRepo, IGMUserOperationRepository gmuoRepo, IClaimRepository claimRepo, IPlayerRepository playerRepo, IGWEventsLogRepository gwEventsRepo,
        IQuestEventsStagesRepository gwQuestEventsStagesRepo, IQuestEventsStepsRepository gwQuestEventsStepsRepo)
    {
      this.historyRepo = historyRepo;
      this.gmoRepo = gmoRepo;
      this.gmuoRepo = gmuoRepo;
      this.claimRepo = claimRepo;
      this.playerRepo = playerRepo;
      this.gwEventsRepo = gwEventsRepo;
      this.gwQuestEventsStagesRepo = gwQuestEventsStagesRepo;
      this.gwQuestEventsStepsRepo = gwQuestEventsStepsRepo;
    }


    public List<LoginInfoModel> GetLoginHistory( long auid, int pageNum, out int pageQuant )
    {
      pageQuant = 0;
      try
      {
        var sessions = historyRepo.GetSessionsByPlayerId( auid, pageNum, out pageQuant );
        return sessions.Select( s => new LoginInfoModel( s ) ).ToList();
      }
      catch ( Exception ex )
      {
        log.Error( "Failed to get login history from DAL for account id = " + auid, ex );
        return null;
      }
    }


    public List<BanOrMuteHistoryModel> GetBanAndMuteHistory(long auid, int pageNum, out int pageQuant)
    {
      pageQuant = 0;
      try
      {
        var bans = gmuoRepo.GetOperationsByPlayerId(auid)
                           .Select(op => new BanOrMuteHistoryModel (op)
                                           {
                                             Complaints = claimRepo.GetClaimsByGMUserOperation(op).Count()
                                           }).ToList();
        pageQuant = (int) Math.Ceiling((double) bans.Count()/pageSize);
        return bans.OrderBy(h => h.Time).Skip((pageNum - 1)*pageSize).Take(pageSize).ToList();
      }
      catch (Exception ex)
      {
        log.Error("Failed to get ban and mute history from DAL  for account id = " + auid, ex);
        return null;
      }
    }


    public List<GMOperationInfoModel> GetGMOperationHistory(long auid, int pageNum, out int pageQuant)
    {
      var infos = gmoRepo.GetOperationsByPlayer(auid, null).ToList();

      pageQuant = infos.Count()/pageSize + (infos.Count()%pageSize == 0 ? 0 : 1);
      
      return infos.Skip((pageNum - 1)*pageSize).Take(pageSize)
                  .Select(e => new GMOperationInfoModel
                                 {
                                   Auid = e.Player.Id,
                                   Type = e.Type.ToString(),
                                   Data = e.Data,
                                   GMLogin = e.GMLogin,
                                   Timestamp = e.Timestamp
                                 }).ToList();
    }


    public PlayerResourceFilterModel GetResourcesHistory(PlayerResourceFilterModel model)
    {
      if (model == null) throw new ArgumentNullException("model");
      model.Results = new List<PlayerResourceInfoModel>();

      if ( !model.SpentGold && !model.SpentSilver && !model.SpentPerl && !model.SpentRedPerl && !model.SpentResourceN && !model.TalentsChange )
        return model;

      var talentsIds = new List<Int32>();
      if (!String.IsNullOrEmpty((model.TalentName)))
      {
        talentsIds.AddRange(
          (from talent in TalentsCatalog.GetAllTalents() 
           where Regex.IsMatch(talent.TalentName.ToLower(), @"([\s\S]*)(" + model.TalentName.ToLower() + @")([\s\S]*)") 
           || Regex.IsMatch(talent.TalentClassId.ToString(CultureInfo.InvariantCulture), @"([\s\S]*)(" + model.TalentName + @")([\s\S]*)") 
           select talent.TalentClassId).ToList());
        if (talentsIds.Count == 0)
        {
          model.MessageToUser = "None of talents does not match the filter";
        }
      }

      int rows;
      var results = historyRepo.GetPlayerResources(
        model.Auid, model.DateFrom, model.DateTo, talentsIds, model.Gain, model.SpentGold, model.SpentSilver, model.SpentPerl,
        model.SpentRedPerl, model.SpentResourceN, model.TalentsChange, model.ResourcesEventIndex, model.TalentsEventIndex, model.Offset,
        PagedModel.PAGE_SIZE, out rows);

      model.Results.AddRange(results.Select(r => new PlayerResourceInfoModel(r)));

      model.SetTotalRows(rows);

      return model;
    }

    public BanOrMuteHistoryModel GetBanMuteById(int id)
    {
      return new BanOrMuteHistoryModel(gmuoRepo.GetById(id));
    }

    public List<FractionChangeHistoryModel> GetFractionChangeHistory(long auid, int pageNum, out int pageQuant)
    {
      var userChanges = historyRepo.GetFractionChangesByPlayerId(auid, pageNum, out pageQuant);
      var gmOperations = gmoRepo.GetOperationsByPlayer(auid, new List<GMOperationType>{ GMOperationType.PlayerEdit }).ToList();

      var history = userChanges.Select(factionChange => new FractionChangeHistoryModel
      {
        Date = factionChange.Timestamp,
        ChangeDetails = "fraction: old='" + factionChange.OldFaction.ToString() + "', new='" + factionChange.NewFaction.ToString() + "'",
        Tool = (factionChange.ResourceLog == null) ? "Free change" : "Gold"
      }).ToList();
      history.AddRange(from gmOperation in gmOperations
        where gmOperation.Data.Contains("fraction:")
        select new FractionChangeHistoryModel()
        {
          Date = gmOperation.Timestamp, ChangeDetails = gmOperation.Data, Tool = "GMTool"
        });
      history = history.OrderBy(x => x.Date).ToList();

      pageQuant = history.Count() / pageSize + (history.Count() % pageSize == 0 ? 0 : 1);
      return history.Skip((pageNum - 1)*pageSize).Take(pageSize).ToList();
    }


    public CWPlayerResourcesFilterModel GetCWPlayerResourcesHistory(CWPlayerResourcesFilterModel model)
    {
      if (model == null) throw new ArgumentNullException("model");

      int rows;
      var results = historyRepo.GetCWPlayerPoints(
        model.Auid, model.DateFrom, model.DateTo, model.Offset, PagedModel.PAGE_SIZE, out rows);

      model.SetTotalRows(rows);
      model.Results = results.ToList();

      return model;
    }

    public CWGuildResourcesFilterModel GetCWGuildResourcesHistory(CWGuildResourcesFilterModel model)
    {
      if (model == null) throw new ArgumentNullException("model");

      int rows;
      var results = historyRepo.GetCWGuildPoints(
        model.GuildId, model.DateFrom, model.DateTo, model.Offset, PagedModel.PAGE_SIZE, out rows);

      model.SetTotalRows(rows);
      model.Results = results.ToList();

      return model;
    }


    public LeavePointsFilterModel GetLeavePointsHistory(LeavePointsFilterModel model)
    {
      if (model == null) throw new ArgumentNullException("model");

      int rows;
      var results = historyRepo.GetLeaverPoints(model.Auid, model.DateFrom, model.DateTo, model.Offset, PagedModel.PAGE_SIZE, out rows);

      model.SetTotalRows(rows);
      model.Results = results.ToList();

      return model;
    }

    public LeavePointsFilterModel FillLeavePointsCounters(LeavePointsFilterModel model)
    {
      var player = playerRepo.GetById(model.Auid);
      if (player != null)
      {
        model.LeaverCount = player.LeaverCount ?? 0;
        model.LeaverGMCount = player.LeaverGMCount ?? 0;
      }
      return model;
    }


    public RuneOperationsFilterModel GetRunesHistory(RuneOperationsFilterModel model)
    {
      model.Results = historyRepo.GetRuneOperations(model.Auid, model.DateFrom, model.DateTo).ToList();
      return model;
    }

    public void GetGwEventHistoryByEvent(GWEventHistory model, int eventIdx, DateTime starTime, DateTime endTime)
    {
      int rows;
      var gwEventLog = gwEventsRepo.GetGWEventLogByEventIdx(eventIdx, starTime, endTime, model.Offset, PagedModel.PAGE_SIZE, out rows);
      model.SetTotalRows(rows);

      model.GwEvents.AddRange(gwEventLog.Select(e => new GWEventHistoryModel
      {
        EventIndex = int.Parse(e.GWEventmid),
        CurrentPoints = e.CurrentPoints,
        GuildId = e.GuildId,
        LastPoints = e.LastPoints,
        TimeStamp = e.TimeStamp,
        Auid = e.Auid
      }));
    }

    public void GetGwEventHistoryByGuild(GWEventHistory model, long guildIdx, DateTime starTime, DateTime endTime)
    {
      int rows;
      var gwEventLog = gwEventsRepo.GetGWEventLogByGuild(guildIdx, starTime, endTime, model.Offset, PagedModel.PAGE_SIZE, out rows);
      model.SetTotalRows(rows);

      model.GwEvents.AddRange(gwEventLog.Select(e => new GWEventHistoryModel
      {
        EventIndex = int.Parse(e.GWEventmid),
        CurrentPoints = e.CurrentPoints,
        GuildId = e.GuildId,
        LastPoints = e.LastPoints,
        TimeStamp = e.TimeStamp,
        Auid = e.Auid
      }));
    }

    public void GetGwEventHistoryByAuid(GWEventHistory model, int auid, DateTime starTime, DateTime endTime)
    {
      int rows;
      var gwEventLog = gwEventsRepo.GetGWEventLogByAuid(auid, starTime, endTime, model.Offset, PagedModel.PAGE_SIZE, out rows);
      model.SetTotalRows(rows);

      model.GwEvents.AddRange(gwEventLog.Select(e => new GWEventHistoryModel
      {
        EventIndex = int.Parse(e.GWEventmid),
        CurrentPoints = e.CurrentPoints,
        GuildId = e.GuildId,
        LastPoints = e.LastPoints,
        TimeStamp = e.TimeStamp,
        Auid = e.Auid
      }));
    }

      public void GetQuestEventsStagesModel(QuestEventsStepsModel model, int auid, DateTime starTime, DateTime endTime)
      {
          int rows;
          var eventLog = gwQuestEventsStagesRepo.GetQuestEventsStepsByAuid(auid, starTime, endTime, model.Offset, PagedModel.PAGE_SIZE, out rows);
          model.SetTotalRows(rows);
          model.Stage = -1;

          model.Events.AddRange(eventLog.Select(e => new QuestEventsStepsHistoryModel
          {
              ToStageStepChange = e.ToStageChange,
              TimeStamp = e.TimeStamp,
              Auid = e.Auid,
              Stage = -1,
          }));
      }

      public void GetQuestEventsStepsModel(QuestEventsStepsModel model, int auid, int stage, DateTime starTime, DateTime endTime)
      {
          int rows;
          var eventLog = gwQuestEventsStepsRepo.GetQuestEventsStepsByAuidAndStage(auid, stage, starTime, endTime, model.Offset, PagedModel.PAGE_SIZE, out rows);
          model.SetTotalRows(rows);
          
          model.Events.AddRange(eventLog.Select(e => new QuestEventsStepsHistoryModel
          {
              ToStageStepChange = e.ToStepChange,
              Stage = e.Stage,
              TimeStamp = e.TimeStamp,
              Auid = e.Auid
          }));
      }
  }

}