using System.Collections.Generic;
using System.Web.Mvc;
using ControlCenter.Areas.Admin.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.Admin.Controllers
{
  [Authorize]
  public class RolesController : Controller
  {
    private IRoleInfoService _service;

    protected override void Initialize(System.Web.Routing.RequestContext requestContext)
    {
      if (_service == null) _service = new RoleInfoService();

      base.Initialize(requestContext);
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Index()
    {
      return View(_service.GetAllRoles());
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Details(int id)
    {
      var model = _service.GetRoleById(id);
      if (model == null)
        return View("Error");

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Edit(int id)
    {
      var model = _service.GetRoleById(id);
      if (model == null)
        return View("Error");

      ViewData["AllPermissions"] = _service.GetAllPermissions();

      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Edit(RoleInfoModel model, IEnumerable<int> chkPermissions)
    {
      if (ModelState.IsValid)
      {
        var changedmodel = _service.ChangeRoleInfo(model, chkPermissions ?? new int[0]);
        return RedirectToAction("Details", new { id = changedmodel.RoleId });
      }

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Members(int id)
    {
      var model = _service.GetRoleById(id);
      if (model == null)
        return View("Error");

      ViewData["AllUsers"] = _service.GetAllUsers();

      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Members(RoleInfoModel model, IEnumerable<int> chkUsers)
    {
      if (ModelState.IsValid)
      {
        var changedmodel = _service.ChangeRoleMembership(model, chkUsers ?? new int[0]);
        return RedirectToAction("Details", new { id = changedmodel.RoleId });
      }

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Create()
    {
      ViewData["AllPermissions"] = _service.GetAllPermissions();

      return View();
    }

    [AuthorizeWithPermission( Permission = "Admin" )]
    public ActionResult DeleteRole( int roleId )
    {
      string errorIfExist = _service.DeleteRole( roleId );
      if ( errorIfExist != null )
        return RedirectToAction( "ShowError", "Roles", new { error = errorIfExist } );
      return RedirectToAction( "Index" );
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Create([Bind(Exclude = "Id")] RoleInfoModel model, IEnumerable<int> chkPermissions)
    {
      if (ModelState.IsValid)
      {
        var newmodel = _service.CreateRole(model, chkPermissions);
        return RedirectToAction("Details", new { id = newmodel.RoleId });
      }

      ViewData["AllPermissions"] = _service.GetAllPermissions();

      return View(model);
    }

    public ActionResult ShowError( string error )
    {
      ViewData["errorMessage"] = error;
      return View();
    }
  }
}
