using System;
using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;
using AccountLib;
using ControlCenter.Helpers;
using DAL.Repositories;
using DAL.Entities;

namespace ControlCenter.Areas.GM.Models
{
  public interface IComplaintService
  {
    void FillComplaintsOverviewModel(ComplaintOverviewModel model);
    void FillComplaintsForPlayer(PlayerComplaintInfosModel model, GMToolsPrincipal user);
    IEnumerable<ComplaintInfoModel> GetComplaintsForPlayer(long auid, string nickname, GMToolsPrincipal user);
    IEnumerable<ComplaintInfoModel> GetComplaintsForGMUserOperation(int operationid);
    List<string> GetComplainsTypes();
    List<string> GetHistoryTypes();
  }
  
  public class ComplaintService : IComplaintService
  {
    private const int PAGE_SIZE = 30;

    private IClaimRepository claimRepo;
    private IGMUserOperationRepository gmuoRepo;

    public ComplaintService()
    {
      claimRepo = new ClaimRepository();
      gmuoRepo = new GMUserOperationRepository();
    }

    public void FillComplaintsOverviewModel(ComplaintOverviewModel model)
    {
      int rows = 0;
      int pageSize = (model.UsersPerPage == 0 ? PAGE_SIZE : model.UsersPerPage);
      var filter = new PlayerClaimFilter
      {
        StartDate = model.DateFrom,
        EndDate = model.DateTo,
        Locale = model.Locale,
        Muids = model.Muids,
        CurrentComplaintsType = string.IsNullOrEmpty(model.ComplaintType)
          ? (PlayerClaimFilter.ComplaintsType?) null
          : (PlayerClaimFilter.ComplaintsType) Enum.Parse(typeof (PlayerClaimFilter.ComplaintsType), model.ComplaintType),
        MinComplaints = model.MinComplaints,
        MaxComplaints = model.MaxComplaints,
        CurrentHistoryType = string.IsNullOrEmpty(model.HistoryType)
          ? (PlayerClaimFilter.HistoryType?) null
          : (PlayerClaimFilter.HistoryType) Enum.Parse(typeof (PlayerClaimFilter.HistoryType), model.HistoryType),
        MinHistory = model.MinHistory,
        MaxHistory = model.MaxHistory,
        ReportedBy = model.ReportedBy,
        MinLeaverPoints = model.MinLeaverPoints,
        MaxLeaverPoints = model.MaxLeaverPoints,
        MinLeaverStatusChanges = model.MinLeaverStatusChanges,
        MaxLeaverStatusChanges = model.MaxLeaverStatusChanges,
        MinLeaverStatusChangesByGM = model.MinLeaverStatusChangesByGM,
        MaxLeaverStatusChangesByGM = model.MaxLeaverStatusChangesByGM,
      };

      IEnumerable<PlayerClaimCountDTO> dtos;
      bool megaResponse = false;
      if ((model.BanAmnistia != null && !model.BanAmnistia.Equals("")) ||
          (model.MuteTimeAmnistia != null && !model.MuteTimeAmnistia.Equals("")) ||
          (model.LeaveAmnistia != null && !model.LeaveAmnistia.Equals("")))
      {
        dtos = claimRepo.GetPlayerClaimCounts(filter, model.OrderBy, model.Asc, 0, 999999999);
        megaResponse = true;
      }
      else
        dtos = claimRepo.GetPlayerClaimCounts(filter, model.OrderBy, model.Asc, (model.PageNum - 1)*pageSize, pageSize);


      model.Results = new List<PlayerComplaintsModel>();
      foreach (var dto in dtos)
      {
        if (rows == 0 && !megaResponse)
          rows = dto.TotalRows;

        string localesinfo = String.Empty;
        if (!String.IsNullOrEmpty(dto.ClaimsLocaleCount))
        {
          var groups = dto.ClaimsLocaleCount.Trim('{', '}').Split(',')
            .GroupBy(s => s).OrderByDescending(gr => gr.Count());

          localesinfo = String.Join("", groups.Select(gr => String.Format("{0}: {1}\n", gr.Key, gr.Count())).ToArray());
        }

        var banOrMuteHistory = gmuoRepo.GetOperationsByPlayerId(dto.PlayerId)
          .Select(op => new BanOrMuteHistoryModel(op)).ToList();

        // да да, выборка не на стороне бд
        // берём последнюю дату бана мьюта или лива (получаем дату или null)
        var lastBan = banOrMuteHistory.Where(r => (GMUserOperationType)Enum.Parse(typeof(GMUserOperationType), r.EventType) == GMUserOperationType.Ban).OrderByDescending(o => o.Time).FirstOrDefault();
        var lastMute = banOrMuteHistory.Where(r => (GMUserOperationType)Enum.Parse(typeof(GMUserOperationType), r.EventType) == GMUserOperationType.Mute ||
                                                   (GMUserOperationType)Enum.Parse(typeof(GMUserOperationType), r.EventType) == GMUserOperationType.ModeratorMute).OrderByDescending(o => o.Time).FirstOrDefault();
        var lastLeave = banOrMuteHistory.Where(r => (GMUserOperationType)Enum.Parse(typeof(GMUserOperationType), r.EventType) == GMUserOperationType.SetLeave).OrderByDescending(o => o.Time).FirstOrDefault();


        // теперь определяем время амнистий
        // текста которые будут отображаться в страничке 
        var yesText = "YES";
        var noText = "NO";

        // определяем время, после которого у нас сново можно банить 
        var rottenTime = new DateTime(1970, 1, 1).AddMonths(3).ToUnixTimestamp();

        //AddHours(3) это типо приводим к UTC+3
        var timeBanAmnistia = lastBan != null ? DateTime.Now.ToUnixTimestamp() - lastBan.Time.AddHours(3).ToUnixTimestamp() > rottenTime : true;
        var timeMuteAmnistia = lastMute != null ? DateTime.Now.ToUnixTimestamp() - lastMute.Time.AddHours(3).ToUnixTimestamp() > rottenTime : true;
        var timeLeaveAmnistia = lastLeave != null ? DateTime.Now.ToUnixTimestamp() - lastLeave.Time.AddHours(3).ToUnixTimestamp() > rottenTime : true;

        var lastBanTrueOrFalse = timeBanAmnistia ? yesText : noText;
        var lastMuteTrueOrFalse = timeMuteAmnistia ? yesText : noText;
        var lastLeaveTrueOrFalse = timeLeaveAmnistia ? yesText : noText;

        
        
        if (model.BanAmnistia != null)
          //так сравнивается, т.к. значения в model определяются в другом месте
          if (model.BanAmnistia.Equals("NO") && timeBanAmnistia || model.BanAmnistia.Equals("YES") && !timeBanAmnistia)
            continue;
        
        if (model.MuteTimeAmnistia != null)
          if (model.MuteTimeAmnistia.Equals("NO") && timeMuteAmnistia || model.MuteTimeAmnistia.Equals("YES") && !timeMuteAmnistia)
              continue;

        if (model.LeaveAmnistia != null)
          if (model.LeaveAmnistia.Equals("NO") && timeLeaveAmnistia || model.LeaveAmnistia.Equals("YES") && !timeLeaveAmnistia)
            continue;
        
          

        //задаём стильный текст в колонки уже непосредственного вывода в страничку
        var lastBanMuteTime = MvcHtmlString.Create("<b>LastBanTime:</b> " + (lastBan != null ? lastBan.Time.AddHours(3).ToString() : "None") +
                        "<br>" + "<b>LastMuteTime:</b> " + (lastMute != null ? lastMute.Time.AddHours(3).ToString() : "None") +
                        "<br>" + "<b>LastLeaveTime:</b> " + (lastLeave != null ? lastLeave.Time.AddHours(3).ToString() : "None"));
        var amnistia = MvcHtmlString.Create("<b>BanAmnistia:</b> " + lastBanTrueOrFalse +
                       "<br>" + "<b>MuteTimeAmnistia:</b> " + lastMuteTrueOrFalse +
                       "<br>" + "<b>LeaveAmnistia:</b> " + lastLeaveTrueOrFalse);

        model.Results.Add(new PlayerComplaintsModel
                          {
                            Auid = dto.PlayerId,
                            Nickname = dto.PlayerNickname,
                            ClaimsCount = dto.ClaimsCount,
                            ClaimsLocaleCount = localesinfo,
                            OffenceClaimsCount = dto.OffenceClaimsCount,
                            UnfairClaimsCount = dto.UnfairClaimsCount,
                            BotClaimsCount = dto.BotClaimsCount,
                            GMUserOperationsCount = dto.GMUserOperationsCount,
                            GMBansCount = dto.GMBansCount,
                            GMMutesCount = dto.GMMutesCount,
                            GMUnbansCount = dto.GMUnbansCount,
                            GMForgivesCount = dto.GMForgivesCount,
                            LeaverPoints = dto.LeaverPoints,
                            LeaverChanged = dto.LeaverChanged,
                            LeaverChangedByGM = dto.LeaverChangedByGM,
                            LastBanMuteTime = lastBanMuteTime,
                            Amnistia = amnistia,
                            Status = String.Format("{0}{1}{2}", dto.Muted, !String.IsNullOrEmpty(dto.Muted) && !String.IsNullOrEmpty(dto.Banned) ? "\n" : "", dto.Banned)
                          });
      }

      //rows = model.Results.Count;

      model.TotalPages = rows / pageSize + (rows % pageSize != 0 ? 1 : 0);
    }

    public void FillComplaintsForPlayer(PlayerComplaintInfosModel model, GMToolsPrincipal user)
    {
      var complaintModels = claimRepo
        .GetActiveClaimsByPlayerId(model.Auid, model.Locale)
        .Where(c => user.HasLocale(c.FromPlayer.Locale))
        .Select(c => new ComplaintInfoModel(c));

      switch (model.OrderBy)
      {
        case "FromPlayerNickname":
          complaintModels = model.Asc ? complaintModels.OrderBy(m => m.FromPlayerNickname) : complaintModels.OrderByDescending(m => m.FromPlayerNickname);
          break;
        case "Source":
          complaintModels = model.Asc ? complaintModels.OrderBy(m => m.Source) : complaintModels.OrderByDescending(m => m.Source);
          break;
        case "Category":
          complaintModels = model.Asc ? complaintModels.OrderBy(m => m.Category) : complaintModels.OrderByDescending(m => m.Category);
          break;
        case "Comment":
          complaintModels = model.Asc ? complaintModels.OrderBy(m => m.Comment) : complaintModels.OrderByDescending(m => m.Comment);
          break;
        case "Timestamp":
          complaintModels = model.Asc ? complaintModels.OrderBy(m => m.Timestamp) : complaintModels.OrderByDescending(m => m.Timestamp);
          break;
        case "Locale":
          complaintModels = model.Asc ? complaintModels.OrderBy(m => m.Locale) : complaintModels.OrderByDescending(m => m.Locale);
          break;
      }

      model.Results = complaintModels.ToList();
    }

    public IEnumerable<ComplaintInfoModel> GetComplaintsForPlayer(long auid, string nickname, GMToolsPrincipal user)
    {
      var model = new PlayerComplaintInfosModel(auid, nickname, null, "FromPlayerNickname", true);
      FillComplaintsForPlayer(model, user);
      return model.Results;
    }

    public IEnumerable<ComplaintInfoModel> GetComplaintsForGMUserOperation(int operationid)
    {
      return claimRepo
        .GetClaimsByGMUserOperationId(operationid)
        .Select(c => new ComplaintInfoModel(c));
    }

    public List<string> GetComplainsTypes()
    {
      return Enum.GetNames(typeof (PlayerClaimFilter.ComplaintsType)).ToList();
    }
    public List<string> GetHistoryTypes()
    {
      return Enum.GetNames(typeof (PlayerClaimFilter.HistoryType)).ToList();
    }
  }
}