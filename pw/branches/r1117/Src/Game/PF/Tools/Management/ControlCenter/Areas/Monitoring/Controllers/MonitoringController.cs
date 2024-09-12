using System.Web.Mvc;
using log4net;
using ControlCenter.Helpers;
using System.Web.Routing;
using ControlCenter.Areas.Cluster.Models;

namespace ControlCenter.Areas.Monitoring.Controllers
{
  [Authorize]
  public class MonitoringController : Controller
  {
    private static ILog _log = LogManager.GetLogger( typeof( MonitoringController ) );

    public IClusterService CMService { get; set; }
    protected override void Initialize( RequestContext requestContext )
    {
      if ( CMService == null )
        CMService = new ClusterService();

      base.Initialize( requestContext );
    }

    [AuthorizeWithPermission(Permission = "Monitoring_Overview")]
    public ActionResult Index()
    {
      var model = CMService.GetFullMonitoringInfo();
      return View(model);
    }

  }
}
