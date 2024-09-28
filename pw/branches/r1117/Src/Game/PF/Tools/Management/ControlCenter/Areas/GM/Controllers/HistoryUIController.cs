using System;
using System.Collections.Generic;
using System.Web.Mvc;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Areas.GWEvents.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Controllers
{
  [Authorize]
  public class HistoryUIController : Controller
  {
    public IHistoryUIService HistorySvc { get; set; }
    public IAccountService AccountSvc { get; set; }
    public IGuildService GuildSvc { get; set; }

    protected override void Initialize( System.Web.Routing.RequestContext requestContext )
    {
      base.Initialize( requestContext );

      if (HistorySvc == null)
        HistorySvc = new HistoryUIService();
      
      if (AccountSvc == null)
        AccountSvc = new AccountService();

      if (GuildSvc == null)
        GuildSvc = new GuildService();
    }

    [AuthorizeWithPermission( Permission = "GM_AccountLoginHistory" )]
    public ActionResult BanAndMuteHistory( long auid, string login, int? pageNum )
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      int pageQuant;
      pageNum = pageNum ?? 1;
      ViewData["auid"] = auid;
      ViewData["login"] = login;
      ViewData["CurrentPage"] = pageNum;
      var model = HistorySvc.GetBanAndMuteHistory( auid, (int)pageNum, out pageQuant );
      ViewData["TotalPages"] = pageQuant;
      if ( model == null )
        return RedirectToAction( "ShowError", "Account", new { error = "DAL returned null or is unaccessible" } );
      return View( model );
    }


    [AuthorizeWithPermission( Permission = "GM_AccountLoginHistory" )]
    public ActionResult GMOperationsHistory(long auid, int? pageNum)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      int pageQuant;
      pageNum = pageNum ?? 1;
      ViewData["auid"] = auid;
      ViewData["CurrentPage"] = pageNum;
      var model = HistorySvc.GetGMOperationHistory( auid, (int)pageNum, out pageQuant );
      ViewData["TotalPages"] = pageQuant;
      if ( model == null )
        return RedirectToAction( "ShowError", "Account", new { error = "DAL returned null or is unaccessible" } );
      return View( model );
    }


    [AuthorizeWithPermission( Permission = "GM_AccountLoginHistory" )]
    public ActionResult LoginHistory( long auid, string login, int? pageNum )
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      int pageQuant;
      pageNum = pageNum ?? 1;
      ViewData["auid"] = auid;
      ViewData["login"] = login;
      ViewData["CurrentPage"] = pageNum;
      var model = HistorySvc.GetLoginHistory( auid, (int)pageNum, out pageQuant );
      ViewData["TotalPages"] = pageQuant;
      if ( model == null )
        return RedirectToAction( "ShowError", "Account", new { error = "DAL returned null or is unaccessible" } );
      return View( model );
    }


    [AuthorizeWithPermission( Permission = "GM_AccountLoginHistory" )]
    public ActionResult ResourcesHistory(long auid, DateTime? datefrom, DateTime? dateto, int? timezone,
      PlayerResourceFilterModel.ChangeType? type, bool? spentgold, bool? spentsilver, bool? spentperl, bool? spentredperl, 
      bool? spentresourcen, bool? talentschange, String contains, String resourcesEvent, String talentsEvent,
      int? page)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      var model = new PlayerResourceFilterModel {Auid = auid};

      var dictValues = new Dictionary<string, string> { { "", "All" } };
      var allValues = AccountSvc.GetResourceEvents();
      foreach (var value in allValues)
      {
        dictValues.Add(value.ToLower(), value);
      }
      model.ResourcesEventList = new SelectList(dictValues, "key", "value");

      dictValues = new Dictionary<string, string> {{"", "All"}};
      allValues = AccountSvc.GetTalentsEvents();
      foreach (var value in allValues)
      {
        dictValues.Add(value.ToLower(), value);
      }
      model.TalentsEventList = new SelectList(dictValues, "key", "value");

      if (datefrom != null && dateto != null)
      {
        model.DateFrom = datefrom.Value.AddHours(timezone.HasValue ? -timezone.Value : 0);
        model.DateTo = dateto.Value.AddHours(timezone.HasValue ? -timezone.Value : 0);
        model.Type = type.HasValue ? type.Value : PlayerResourceFilterModel.ChangeType.Any;
        model.SpentGold = spentgold.HasValue && spentgold.Value;
        model.SpentSilver = spentsilver.HasValue && spentsilver.Value;
        model.SpentPerl = spentperl.HasValue && spentperl.Value;
        model.SpentRedPerl = spentredperl.HasValue && spentredperl.Value;
        model.SpentResourceN = spentresourcen.HasValue && spentresourcen.Value;
        model.TalentsChange = talentschange.HasValue && talentschange.Value;
        model.TalentName = contains;
        model.ResourcesEventIndex = resourcesEvent;
        model.TalentsEventIndex = talentsEvent;

        if (page.HasValue) model.Page = page.Value;

        try
        {
          model = HistorySvc.GetResourcesHistory(model);
        }
        catch (Exception ex)
        {
          return View("Error", new HandleErrorInfo(ex, "HistoryUI", "ResourcesHistory"));
        }
      }
      else
      {
        model.DateFrom = DateTime.UtcNow.AddDays(-14).Date;
        model.DateTo = DateTime.UtcNow.AddDays(1).Date;
      }

      return View(model);
    }

    [AuthorizeWithPermission( Permission = "GM_AccountLoginHistory" )]
    public ActionResult FractionChangeHistory(long auid, int? pageNum)
    {
      int pageQuant;
      pageNum = pageNum ?? 1;
      ViewData["auid"] = auid;
      ViewData["CurrentPage"] = pageNum;
      var model = HistorySvc.GetFractionChangeHistory(auid, (int)pageNum, out pageQuant);
      ViewData["TotalPages"] = pageQuant;
      return View(model);
    }

    [HttpPost]
    public ActionResult ResourcesHistory(PlayerResourceFilterModel model)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, model.Auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      if (model == null) throw new ArgumentNullException("model");
      if (!ModelState.IsValid)
        return View(model);

      return RedirectToAction("ResourcesHistory", new {model.Auid, model.DateFrom, model.DateTo, model.TimeZone, model.Type,
        model.SpentGold, model.SpentSilver, model.SpentPerl, model.SpentRedPerl, model.SpentResourceN, model.TalentsChange,
        contains = model.TalentName, resourcesEvent = model.ResourcesEventIndex, talentsEvent = model.TalentsEventIndex
      });
    }


    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult CWPlayerResourcesHistory(long auid, DateTime? datefrom, DateTime? dateto, int? timezone, int? page)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      var model = new CWPlayerResourcesFilterModel { Auid = auid };

      if (datefrom != null && dateto != null)
      {
        model.DateFrom = datefrom.Value.AddHours(timezone.HasValue ? -timezone.Value : 0);
        model.DateTo = dateto.Value.AddHours(timezone.HasValue ? -timezone.Value : 0);
        if (page.HasValue) model.Page = page.Value;

        model = HistorySvc.GetCWPlayerResourcesHistory(model);
      }
      else
      {
        model.DateFrom = DateTime.UtcNow.AddDays(-14).Date;
        model.DateTo = DateTime.UtcNow.AddDays(1).Date;
      }

      return View(model);
    }


    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult CWPlayerResourcesHistory(CWPlayerResourcesFilterModel model)
    {
      return RedirectToAction("CWPlayerResourcesHistory",
                              new
                                {
                                  model.Auid,
                                  model.DateFrom,
                                  model.DateTo,
                                  model.TimeZone,
                                });
    }



    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult CWGuildResourcesHistory(long guildid, DateTime? datefrom, DateTime? dateto, int? timezone, int? page)
    {
      var infomodel = GuildSvc.GetGuildInfoById(guildid);
      if (infomodel.Error != null)
        return RedirectToAction("ShowError", "Account", new { error = "Server returned an error: " + infomodel.Error });

      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, infomodel.LeaderAuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      var model = new CWGuildResourcesFilterModel { GuildId = guildid };

      if (datefrom != null && dateto != null)
      {
        model.DateFrom = datefrom.Value.AddHours(timezone.HasValue ? -timezone.Value : 0);
        model.DateTo = dateto.Value.AddHours(timezone.HasValue ? -timezone.Value : 0);
        if (page.HasValue) model.Page = page.Value;

        model = HistorySvc.GetCWGuildResourcesHistory(model);
      }
      else
      {
        model.DateFrom = DateTime.UtcNow.AddDays(-14).Date;
        model.DateTo = DateTime.UtcNow.AddDays(1).Date;
      }

      return View(model);
    }


    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult CWGuildResourcesHistory(CWGuildResourcesFilterModel model)
    {
      return RedirectToAction("CWGuildResourcesHistory",
                              new
                              {
                                model.GuildId,
                                model.DateFrom,
                                model.DateTo,
                                model.TimeZone,
                              });
    }


    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult LeavePointsHistory(long auid, DateTime? datefrom, DateTime? dateto, int? timezone, int? page)
    {
      var model = new LeavePointsFilterModel { Auid = auid };

      if (datefrom != null && dateto != null)
      {
        model.DateFrom = datefrom.Value.AddHours(-timezone ?? 0);
        model.DateTo = dateto.Value.AddHours(-timezone ?? 0);
        if (page.HasValue) model.Page = page.Value;

        model = HistorySvc.GetLeavePointsHistory(model);
      }
      else
      {
        model.DateFrom = DateTime.UtcNow.AddDays(-14).Date;
        model.DateTo = DateTime.UtcNow.AddDays(1).Date;
      }
      HistorySvc.FillLeavePointsCounters(model);

      return View(model);
    }


    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult LeavePointsHistory(LeavePointsFilterModel model)
    {
      return RedirectToAction("LeavePointsHistory",
                              new
                              {
                                model.Auid,
                                model.DateFrom,
                                model.DateTo,
                                model.TimeZone,
                              });
    }


    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult RuneHistory(long auid, DateTime? datefrom, DateTime? dateto, int? timezone)
    {
      var model = new RuneOperationsFilterModel { Auid = auid };

      if (datefrom != null && dateto != null)
      {
        model.DateFrom = datefrom.Value.AddHours(-timezone ?? 0);
        model.DateTo = dateto.Value.AddHours(-timezone ?? 0);
        model = HistorySvc.GetRunesHistory(model);
      }
      else
      {
        model.DateFrom = DateTime.UtcNow.AddDays(-14).Date;
        model.DateTo = DateTime.UtcNow.AddDays(1).Date;
      }

      return View(model);
    }


    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult RuneHistory(RuneOperationsFilterModel model)
    {
      return RedirectToAction("RuneHistory",
                              new
                              {
                                model.Auid,
                                model.DateFrom,
                                model.DateTo,
                                model.TimeZone,
                              });
    }


    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult GWEventPoolPointsHistory(int auid, int? page, DateTime? startTime, DateTime? endTime)
    {
      var model = new GWEventHistory();
      model.Auid = auid;
      if (page.HasValue) model.Page = page.Value;
      var StartTime = DateTime.MinValue;
      var EndTime = DateTime.MinValue;
      if (startTime.HasValue && endTime.HasValue)
      {
        StartTime = startTime.Value;
        EndTime = endTime.Value;
      }
      else
      {
        StartTime = DateTime.UtcNow.AddDays(-14);
        EndTime = DateTime.UtcNow.AddDays(1);
      }

      model.StartTime = StartTime;
      model.EndTime = EndTime;

      HistorySvc.GetGwEventHistoryByAuid(model, auid, StartTime, EndTime);
      return View(model);
    }

    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    [HttpPost, ValidateInput(false)]
    public ActionResult GWEventPoolPointsHistory(GWEventHistory model)
    {
      return RedirectToAction("GWEventPoolPointsHistory", new { auid = model.Auid, startTime = model.StartTime, endTime = model.EndTime });
    }



    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult GWEventPoolPointsHistoryToGuild(long guildAuid, int? page, DateTime? startTime, DateTime? endTime)
    {
      var model = new GWEventHistory();
      model.GuildAuid = guildAuid;
      if (page.HasValue) model.Page = page.Value;
      var StartTime = DateTime.MinValue;
      var EndTime = DateTime.MinValue;
      if (startTime.HasValue && endTime.HasValue)
      {
        StartTime = startTime.Value;
        EndTime = endTime.Value;
      }
      else
      {
        StartTime = DateTime.UtcNow.AddDays(-14);
        EndTime = DateTime.UtcNow.AddDays(1);
      }

      model.StartTime = StartTime;
      model.EndTime = EndTime;

      HistorySvc.GetGwEventHistoryByGuild(model, guildAuid, StartTime, EndTime);
      return View(model);
    }

    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    [HttpPost, ValidateInput(false)]
    public ActionResult GWEventPoolPointsHistoryToGuild(GWEventHistory model)
    {
      return RedirectToAction("GWEventPoolPointsHistoryToGuild", new { guildAuid = model.GuildAuid, startTime = model.StartTime, endTime = model.EndTime });
    }



    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult QuestEventsStepsHistory(int auid, int? page, DateTime? startTime, DateTime? endTime, int? stage)
    {
        var model = new QuestEventsStepsModel();
        model.Auid = auid;
        if (page.HasValue) model.Page = page.Value;
        var StartTime = DateTime.MinValue;
        var EndTime = DateTime.MinValue;
        if (startTime.HasValue && endTime.HasValue)
        {
            StartTime = startTime.Value;
            EndTime = endTime.Value;
        }
        else
        {
            StartTime = DateTime.UtcNow.AddDays(-14);
            EndTime = DateTime.UtcNow.AddDays(1);
        }

        model.StartTime = StartTime;
        model.EndTime = EndTime;

        if (stage.HasValue)
            HistorySvc.GetQuestEventsStepsModel(model, auid, stage.Value, StartTime, EndTime);
        else
            HistorySvc.GetQuestEventsStagesModel(model, auid, StartTime, EndTime);

        return View(model);
    }

    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    [HttpPost, ValidateInput(false)]
    public ActionResult QuestEventsStepsHistory(GWEventHistory model)
    {
        return RedirectToAction("QuestEventsStepsHistory", new { auid = model.Auid, startTime = model.StartTime, endTime = model.EndTime });
    }

  }

}
