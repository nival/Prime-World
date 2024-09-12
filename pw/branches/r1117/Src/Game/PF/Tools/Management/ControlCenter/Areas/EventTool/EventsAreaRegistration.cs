using System.Web.Mvc;

namespace ControlCenter.Areas.EventTool
{
  public class EventsAreaRegistration : AreaRegistration
  {
    public override string AreaName
    {
      get
      {
        return "EventTool";
      }
    }

    public override void RegisterArea(AreaRegistrationContext context)
    {
      context.MapRoute(
          "EventTool_default",
          "EventTool/{controller}/{action}/{id}",
          new { action = "Index", id = UrlParameter.Optional }
      );
    }
  }
}
