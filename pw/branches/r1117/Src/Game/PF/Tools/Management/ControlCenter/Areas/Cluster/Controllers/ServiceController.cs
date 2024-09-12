using System;
using System.Collections.Generic;
using System.Web.Mvc;
using System.Web.Routing;
using ControlCenter.Areas.Cluster.Models;
using ControlCenter.Helpers;
using log4net;

namespace ControlCenter.Areas.Cluster.Controllers
{
  [Authorize]
  public class ServiceController : Controller
  {
    private static ILog _log = LogManager.GetLogger(typeof (ServiceController));

    public IClusterService CMService { get; set; }

    protected override void Initialize(RequestContext requestContext)
    {
      if (CMService == null) CMService = new ClusterService();
      
      base.Initialize(requestContext);
    }

    [AuthorizeWithPermission(Permission = "Cluster_ServiceView")]
    public ActionResult Index(string groupby)
    {
      var group_by = GroupServicesBy.Machine;
      try
      {
        if (!String.IsNullOrEmpty(groupby))
          group_by = (GroupServicesBy)Enum.Parse(typeof(GroupServicesBy), groupby, true);
      }
      catch (ArgumentException)
      {
        _log.InfoFormat("Invalid value of parameter \"groupby\" = \"{0}\"", groupby);
      }

      ViewData["groupby"] = group_by;

      IEnumerable<ServiceInfoModel> model = CMService.GetAllServices();
      if (model == null)
      {
        _log.Error("Failed to get list of services");
        return View("Error");
      }

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "Cluster_RunCommand")]
    public ActionResult Command(string cmd, string serviceid, string groupby)
    {
      if (String.IsNullOrEmpty(cmd) || !Enum.IsDefined(typeof(ServiceCommand), cmd))
      {
        _log.ErrorFormat("Invalid command '{0}'", cmd);
        return View("Error");
      }
      var command = (ServiceCommand)Enum.Parse(typeof(ServiceCommand), cmd, true);

      bool result = CMService.ExecuteCommand(serviceid, command);
      if (!result)
      {
        _log.ErrorFormat("Failed to execute command '{0}' for service '{1}'", cmd, serviceid);
        return View("Error");
      }
      
      return RedirectToAction("Index", new { groupby });
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "Cluster_RunCommand")]
    public ActionResult GroupCommand(string cmd, IEnumerable<string> chkService, string groupby)
    {
      if (String.IsNullOrEmpty(cmd) || !Enum.IsDefined(typeof(ServiceCommand), cmd))
      {
        _log.ErrorFormat("Invalid command '{0}'", cmd);
        return View("Error");
      }
      var command = (ServiceCommand)Enum.Parse(typeof(ServiceCommand), cmd, true);

      if (chkService != null)
      {
        foreach (string chkValue in chkService)
        {
          bool result = CMService.ExecuteCommand(chkValue, command);
        }
      }
      return RedirectToAction("Index", new { groupby });
    }

    [AuthorizeWithPermission(Permission = "Cluster_ServiceView")]
    public ActionResult Details(string id)
    {
      if (id == null)
        return View("Error", new HandleErrorInfo(new ArgumentNullException("id"), "Service", "Details" ));

      id = id.Replace('+', '/'); // Подпорка на тот случай если в имени сервиса были прямые слэши

      var model = CMService.GetServiceById(id);
      if (model == null)
      {
        _log.ErrorFormat("Service with id = '{0}' was not found", id);
        return View("Error");
      }

      return View(model);
    }
  }
}
