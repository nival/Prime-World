using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web.Mvc;
using System.Web.Routing;
using DAL.Entities;
using log4net;

namespace ControlCenter.Areas.GM.Models
{
  public interface ISortingModel
  {
    string OrderBy { get; }
    bool Asc { get; }

    RouteValueDictionary GetSortingRouteDictionary();
  }

  public class SortingAttribute : Attribute
  {
  }

  public class ComplaintOverviewModel : ISortingModel
  {
    private static ILog _log = LogManager.GetLogger(typeof(ComplaintOverviewModel));

    public DateTime DateFrom { get; set; }
    public DateTime DateTo { get; set; }
    public int TimeZone { get; set; }
    [DisplayName("Complains type")]
    public string ComplaintType { get; set; }
    [DisplayName("from")]
    public int? MinComplaints { get; set; }
    [DisplayName("to")]
    public int? MaxComplaints { get; set; }
    [DisplayName("History type")]
    public string HistoryType { get; set; }
    [DisplayName("from")]
    public int? MinHistory { get; set; }
    [DisplayName("to")]
    public int? MaxHistory { get; set; }
    [DisplayName("Users per page")]
    public int UsersPerPage { get; set; }
    [DisplayName("Locale (by default ALL)")]
    public string Locale { get; set; }
    public List<string> Muids { get; set; }
    [DisplayName("Reported by (auid)")]
    public long? ReportedBy { get; set; }

    [DisplayName("from")]
    public int? MinLeaverPoints { get; set; }
    [DisplayName("to")]
    public int? MaxLeaverPoints { get; set; }
    [DisplayName("from")]
    public int? MinLeaverStatusChanges { get; set; }
    [DisplayName("to")]
    public int? MaxLeaverStatusChanges { get; set; }
    [DisplayName("from")]
    public int? MinLeaverStatusChangesByGM { get; set; }
    [DisplayName("to")]
    public int? MaxLeaverStatusChangesByGM { get; set; }

    [DisplayName("BanAmnistia")]    
    public string BanAmnistia { get; set; }

    [DisplayName("MuteTimeAmnistia")]   
    public string MuteTimeAmnistia { get; set; }

    [DisplayName("LeaveAmnistia")]
    public string LeaveAmnistia { get; set; }


    public List<PlayerComplaintsModel> Results { get; set; }

    public string OrderBy { get; set; }
    public bool Asc { get; set; }

    public int PageNum { get; set; }
    public int TotalPages { get; set; }

    public SelectList ComplaintTypesList;
    public SelectList HistoryTypesList;
    public SelectList YesNoList;

    private static List<string> allLocales;
    public static List<string> AllLocales
    {
      get
      {
        if (allLocales == null)
          FillLocales();
        return allLocales ?? new List<string>();
      }
    }

    static void FillLocales()
    {
      try
      {
        allLocales = new List<string> { "" };
        var svcLocales = new AccountService().GetBroadcastLocales();
        AllLocales.AddRange(svcLocales);
      }
      catch (Exception ex)
      {
        allLocales = null;
        _log.Error(ex);
      }
    }

    public ComplaintOverviewModel()
    {
    }

    public ComplaintOverviewModel(int? pageNum, int? usersPerPage, string orderby, bool? asc, string locale, List<string> muids)
    {
      PageNum = pageNum ?? 1;
      UsersPerPage = usersPerPage ?? 30;
      Locale = locale;
      Muids = muids;

      var sortingProps = typeof (PlayerComplaintsModel)
        .GetProperties().Where(p => p.GetCustomAttributes(typeof (SortingAttribute), false).Length > 0).ToList();

      OrderBy = sortingProps.Any(p => p.Name == orderby) ? orderby : sortingProps[0].Name ;
      Asc = asc ?? false;
    }

    public void FillSelectLists(IComplaintService complaintService)
    {
      var list = new List<string> { "" };
      list.AddRange(complaintService.GetComplainsTypes());
      ComplaintTypesList = new SelectList(list);
      list = new List<string> { "" };
      list.AddRange(complaintService.GetHistoryTypes());
      HistoryTypesList = new SelectList(list);
      YesNoList = new SelectList(new List<string> { "", "YES", "NO"});
    }

    public RouteValueDictionary GetSortingRouteDictionary()
    {
      var dic = new RouteValueDictionary();
      dic["DateFrom"] = DateFrom;
      dic["DateTo"] = DateTo;
      dic["TimeZone"] = TimeZone;
      dic["ComplaintType"] = ComplaintType;
      dic["MinComplaints"] = MinComplaints;
      dic["MaxComplaints"] = MaxComplaints;
      dic["HistoryType"] = HistoryType;
      dic["MinHistory"] = MinHistory;
      dic["MaxHistory"] = MaxHistory;
      dic["ReportedBy"] = ReportedBy;
      dic["MinLeaverPoints"] = MinLeaverPoints;
      dic["MaxLeaverPoints"] = MaxLeaverPoints;
      dic["MinLeaverStatusChanges"] = MinLeaverStatusChanges;
      dic["MaxLeaverStatusChanges"] = MaxLeaverStatusChanges;
      dic["MinLeaverStatusChangesByGM"] = MinLeaverStatusChangesByGM;
      dic["MaxLeaverStatusChangesByGM"] = MaxLeaverStatusChangesByGM;
      dic["UsersPerPage"] = UsersPerPage;
      dic["Locale"] = Locale;
      return dic;
    }
  }

  public class PlayerComplaintsModel
  {
    public long Auid { get; set; }
    public string Nickname { get; set; }
    [Sorting]
    [Description("Complaints")]
    public int ClaimsCount { get; set; }
    public string ClaimsLocaleCount { get; set; }
    [Sorting]
    [Description("Offence")]
    public int OffenceClaimsCount { get; set; }
    [Sorting]
    [Description("Unfair")]
    public int UnfairClaimsCount { get; set; }
    [Sorting]
    [Description("Bot usage")]
    public int BotClaimsCount { get; set; }
    [Sorting]
    [Description("Ban/mute history")]
    public int GMUserOperationsCount { get; set; }

    [DisplayName("Bans")]
    public int GMBansCount { get; set; }
    [DisplayName("Unbans")]
    public int GMUnbansCount { get; set; }
    [DisplayName("Mutes")]
    public int GMMutesCount { get; set; }
    [DisplayName("Unmutes")]
    public int GMUnmutesCount { get; set; }
    [DisplayName("AutoForgives")]
    public int GMForgivesCount { get; set; }
    [DisplayName("LeaverPoints")]
    public int LeaverPoints { get; set; }
    [DisplayName("LeaverChanged")]
    public int LeaverChanged { get; set; }
    [DisplayName("LeaverChangedByGM")]
    public int LeaverChangedByGM { get; set; }
    [DisplayName("Last Ban/MuteTimeAmnistia")]
    public MvcHtmlString LastBanMuteTime { get; set; }
    [DisplayName("Amnistia")]
    public MvcHtmlString Amnistia { get; set; }
    [DisplayName("Status")]
    public string Status { get; set; }
  }

  public class PlayerComplaintInfosModel : ISortingModel
  {
    public long Auid { get; set; }
    public string Locale { get; set; }
    public string Nickname { get; set; }

    public string OrderBy { get; set; }
    public bool Asc { get; set; }

    public List<ComplaintInfoModel> Results { get; set; }

    public PlayerComplaintInfosModel()
    {
    }

    public PlayerComplaintInfosModel(long auid, string nickname, string locale, string orderby, bool? asc)
    {
      Auid = auid;
      Locale = locale;
      Nickname = nickname;

      var sortingProps = typeof(ComplaintInfoModel)
        .GetProperties().Where(p => p.GetCustomAttributes(typeof(SortingAttribute), false).Length > 0).ToList();

      OrderBy = sortingProps.Any(p => p.Name == orderby) ? orderby : sortingProps[0].Name;
      Asc = asc ?? true;
    }

    public RouteValueDictionary GetSortingRouteDictionary()
    {
      var dic = new RouteValueDictionary();
      dic["Auid"] = Auid;
      dic["Locale"] = Locale;
      return dic;
    }
  }


  public class ComplaintInfoModel
  {
    public int Id { get; set; }
    public long FromPlayerAuid { get; set; }
    [Sorting]
    [Description("Player")]
    public string FromPlayerNickname { get; set; }
    [Sorting]
    [Description("Source (Session ID)")]
    public string Source { get; set; }
    [Sorting]
    public string Category { get; set; }
    [Sorting]
    public string Locale { get; set; }
    [Sorting]
    public string Comment { get; set; }
    public string ChatLog { get; set; }
    [Sorting]
    [Description("Timestamp, UTC+0")]
    public DateTime Timestamp { get; set; }
    public string GameSessionInfo { get; set; }

    public static string ParseSource(int source)
    {
      switch (source)
      {
        case 0: return "Castle";
        case 1: return "Session";
        default: return "UNDEFINED";
      }
    }

    public static string ParseCategory(int category)
    {
      switch (category)
      {
        case 0: return "Offence";
        case 1: return "Unfair";
        case 2: return "Bot usage";
        default: return "UNDEFINED";
      }
    }

    public ComplaintInfoModel()
    {
    }

    public ComplaintInfoModel(Claim claim)
    {
      if (claim == null)
        throw new ArgumentNullException("claim");

      Id = claim.Id;
      FromPlayerAuid = claim.FromPlayer.Id;
      FromPlayerNickname = claim.FromPlayer.Nickname;
      Source = ParseSource(claim.Source);
      if (claim.Source == 1)
      {
        Source += "\n(" + claim.PersistentId + ")";
      }
      Category = ParseCategory(claim.Category);
      Locale = claim.FromPlayer.Locale;
      Comment = claim.Comment;
      ChatLog = claim.ChatLog;
      Timestamp = claim.Timestamp;
           
      GameSessionInfo =
          String.Format(
            "kills/deaths/assists = {0}/{1}/{2}\npoints = {3}\nprime = {4}\ndistance = {5}\nafks = {6}\nstatus = {7}",
            claim.Kills, claim.Deaths, claim.Assists, claim.Points, claim.Prime, claim.Distance, claim.Afks, claim.ConnStatus);
    }
  }
}