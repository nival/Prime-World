using System.Web.Mvc;
using ControlCenter.Areas.Admin.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.Admin.Controllers
{
  [Authorize]
  public class InfoController : Controller
  {
    private IAdminInfoService Service { get; set; }

    protected override void Initialize(System.Web.Routing.RequestContext requestContext)
    {
      if (Service == null) Service = new AdminInfoService();
      base.Initialize(requestContext);
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Index()
    {
      ViewData["AllUsers"] = Service.GetAllUsers();
      ViewData["AllRoles"] = Service.GetAllRoles();
      return View();
    }
  }
}
