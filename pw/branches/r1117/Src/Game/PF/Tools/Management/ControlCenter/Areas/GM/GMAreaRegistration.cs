using System.Web.Mvc;

namespace ControlCenter.Areas.GM
{
  public class GMAreaRegistration : AreaRegistration
  {
    public override string AreaName
    {
      get
      {
        return "GM";
      }
    }

    public override void RegisterArea(AreaRegistrationContext context)
    {
      context.MapRoute(
          "GM_default",
          "GM/{controller}/{action}/{id}",
          new { action = "Index", id = UrlParameter.Optional }
      );
    }
  }
}
