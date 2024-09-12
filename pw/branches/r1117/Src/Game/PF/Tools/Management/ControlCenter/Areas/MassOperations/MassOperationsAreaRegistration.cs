using System.Web.Mvc;

namespace ControlCenter.Areas.MassOperations
{
  public class MassOperationsAreaRegistration : AreaRegistration
  {
    public override string AreaName
    {
      get
      {
        return "MassOperations";
      }
    }

    public override void RegisterArea( AreaRegistrationContext context )
    {
      context.MapRoute(
          "MassOperations_default",
          "MassOperations/{controller}/{action}/{id}",
          new { action = "Index", id = UrlParameter.Optional }
      );
    }
  }
}
