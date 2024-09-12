using System;
using System.Collections.Generic;
using System.Web.Mvc;
using System.Web.Routing;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Controllers
{
  [Authorize]
  public class ComplaintController : Controller
  {
    public IComplaintService ComplaintService { get; set; }
    public IHistoryUIService HistoryService { get; set; }

    protected override void Initialize(RequestContext requestContext)
    {
      base.Initialize(requestContext);

      if (ComplaintService == null) ComplaintService = new ComplaintService();
      if (HistoryService == null) HistoryService = new HistoryUIService();
    }


    [AuthorizeWithPermission(Permission = "GM_Complains")]
    public ActionResult Overview(DateTime? datefrom, DateTime? dateto, int? timezone, string complaintType,
      int? minComplaints, int? maxComplaints, string historyType, int? minHistory, int? maxHistory, long? reportedBy,
      int? minLeaverPoints, int? maxLeaverPoints, int? minLeaverStatusChanges, int? maxLeaverStatusChanges,
      int? minLeaverStatusChangesByGM, int? maxLeaverStatusChangesByGM, int? pageNum, int? usersPerPage, string banAmnistia, 
      string muteTimeAmnistia, string leaveAmnistia, string locale, string orderby, bool? asc)
    {
      var user = (GMToolsPrincipal) User;
      if (datefrom != null && dateto != null && !user.HasLocale(locale))
        return View("Forbidden");

      var model = new ComplaintOverviewModel(pageNum, usersPerPage, orderby, asc, locale, user.GetMuids());
      model.FillSelectLists(ComplaintService);

      if (datefrom != null && dateto != null)
      {
        model.DateFrom = datefrom.Value.AddHours(-timezone ?? 0);
        model.DateTo = dateto.Value.AddHours(-timezone ?? 0);

        model.ComplaintType = complaintType;
        model.MinComplaints = minComplaints;
        model.MaxComplaints = maxComplaints;
        model.HistoryType = historyType;
        model.MinHistory = minHistory;
        model.MaxHistory = maxHistory;
        model.ReportedBy = reportedBy;
        model.MinLeaverPoints = minLeaverPoints;
        model.MaxLeaverPoints = maxLeaverPoints;
        model.MinLeaverStatusChanges = minLeaverStatusChanges;
        model.MaxLeaverStatusChanges = maxLeaverStatusChanges;
        model.MinLeaverStatusChangesByGM = minLeaverStatusChangesByGM;
        model.MaxLeaverStatusChangesByGM = maxLeaverStatusChangesByGM;

        model.BanAmnistia = banAmnistia;
        model.MuteTimeAmnistia = muteTimeAmnistia;
        model.LeaveAmnistia = leaveAmnistia;

        try
        {
          ComplaintService.FillComplaintsOverviewModel(model);
        }
        catch (Exception ex)
        {
          return View("Error", new HandleErrorInfo(ex, "Complaint", "Overview"));
        }
      }
      else
      {
        model.DateFrom = DateTime.UtcNow.AddDays(-14).Date;
        model.DateTo = DateTime.UtcNow.AddDays(1).Date;
      }

      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_Complains")]
    public ActionResult Overview(ComplaintOverviewModel model)
    {
      if (model == null) throw new ArgumentNullException("model");
      if (!ModelState.IsValid)
      {
        model.FillSelectLists(ComplaintService);
        return View(model);
      }

      if (!((GMToolsPrincipal)User).HasLocale(model.Locale))
        return View("Forbidden");

      return RedirectToAction("Overview",
        new
        {
          model.DateFrom,
          model.DateTo,
          model.TimeZone,
          model.ComplaintType,
          model.MinComplaints,
          model.MaxComplaints,
          model.HistoryType,
          model.MinHistory,
          model.MaxHistory,
          model.ReportedBy,
          model.MinLeaverPoints,
          model.MaxLeaverPoints,
          model.MinLeaverStatusChanges,
          model.MaxLeaverStatusChanges,
          model.MinLeaverStatusChangesByGM,
          model.MaxLeaverStatusChangesByGM,
          model.UsersPerPage,
          model.BanAmnistia,
          model.MuteTimeAmnistia,
          model.LeaveAmnistia,
          model.Locale,
          model.OrderBy,
          model.Asc
        });
    }


    [AuthorizeWithPermission(Permission = "GM_Complains")]
    public ActionResult ByGMUserOperation(int id)
    {
      try
      {
        ViewData["gmuseroperation"] = HistoryService.GetBanMuteById(id);
        var models = ComplaintService.GetComplaintsForGMUserOperation(id);
        return View(models);
      }
      catch (Exception ex)
      {
        return View("Error", new HandleErrorInfo(ex, "Complaint", "ByGMUserOperation"));
      }
    }
  }
}
