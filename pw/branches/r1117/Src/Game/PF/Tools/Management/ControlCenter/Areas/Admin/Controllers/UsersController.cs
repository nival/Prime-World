using System.Collections.Generic;
using System.Web.Mvc;
using ControlCenter.Areas.Admin.Models;
using ControlCenter.Helpers;
using log4net;

namespace ControlCenter.Areas.Admin.Controllers
{
  [Authorize]
  public class UsersController : Controller
  {
    private static ILog _log = LogManager.GetLogger(typeof (UsersController));

    private IUserInfoService _service;

    protected override void Initialize(System.Web.Routing.RequestContext requestContext)
    {
      if (_service == null) _service = new UserInfoService();

      base.Initialize(requestContext);
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Index()
    {
      return View(_service.GetAllUsers());
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Details(int id)
    {
      var model = _service.GetUserById(id);
      if (model == null)
        return View("Error");

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Edit(int id)
    {
      var model = _service.GetUserById(id);
      if (model == null)
        return View("Error");

      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Edit(UserInfoModel model)
    {
      if (ModelState.IsValid)
      {
        var changedmodel = _service.ChangeUserInfo(model);

        if (changedmodel == null)
          return View("Error");

        return RedirectToAction("Details", new { id = changedmodel.UserId });
      }

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Create()
    {
      return View();
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult Create(UserCreateModel model)
    {
      if (ModelState.IsValid)
      {
        if (_service.UserExists(model.UserName))
        {
          ModelState.AddModelError("UserName", "User with the same login is existing in the database");
        }
        int newid = _service.CreateUser(model);
        return RedirectToAction("Details", new { id = newid });
      }

      return View();
    }

    [AuthorizeWithPermission( Permission = "Admin" )]
    public ActionResult DeleteUser( int userId )
    {
      string errorIfExist = _service.DeleteUser( userId );
      if (errorIfExist != null)
        return RedirectToAction( "ShowError", "Roles", new { error = errorIfExist } );
      return RedirectToAction( "Index" );
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult ResetPassword(int id)
    {
      var infomodel = _service.GetUserById(id);
      if (infomodel == null)
        return View("Error");

      return View(new AdminUserResetPasswordModel { UserId = id, UserName = infomodel.UserName });
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult ResetPassword(AdminUserResetPasswordModel model)
    {
      if (ModelState.IsValid)
      {
        if (_service.SetPassword(model.UserId, model.NewPassword))
          return RedirectToAction("Details", new { id = model.UserId });
        else
          return View("Error");
      }

      return View(model);
    }

    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult EditRoles(int id)
    {
      var model = _service.GetUserById(id);
      if (model == null)
        return View("Error");

      ViewData["AllRoles"] = _service.GetAllRoles();

      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "Admin")]
    public ActionResult EditRoles(UserInfoModel model, IEnumerable<int> chkRoles)
    {
      int id = model.UserId;
      model = _service.GetUserById(id); // Request model from db
      if (model == null)
      {
        _log.InfoFormat("Cannot update roles for non-existing user(id={0})", id);
        return View("Error");
      }

      if (!_service.ChangeRoles(model, chkRoles ?? new int[0]))
      {
        return View("Error");
      }
      
      return RedirectToAction("Details", new { id });
    }

  }
}
