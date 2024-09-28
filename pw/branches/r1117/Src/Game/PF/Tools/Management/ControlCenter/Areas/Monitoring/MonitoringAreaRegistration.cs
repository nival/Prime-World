using System.Web.Mvc;

namespace ControlCenter.Areas.Monitoring
{
  public class MonitoringAreaRegistration : AreaRegistration
  {
    public override string AreaName
    {
      get
      {
        return "Monitoring";
      }
    }

    public override void RegisterArea( AreaRegistrationContext context )
    {
      context.MapRoute(
          "Monitoring_default",
          "Monitoring/{controller}/{action}/{id}",
          new { action = "Index", id = UrlParameter.Optional }
      );
    }
  }
}
