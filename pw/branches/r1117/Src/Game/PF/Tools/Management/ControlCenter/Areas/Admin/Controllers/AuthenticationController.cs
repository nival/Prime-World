using System;
using System.Web.Mvc;
using System.Web.Routing;
using ControlCenter.Areas.Admin.Models;

namespace ControlCenter.Areas.Admin.Controllers
{
  [HandleError]
  public class AuthenticationController : Controller
  {
    private IFormsAuthenticationService formsService;
    private IMembershipService membershipService;
    private IUserInfoService userInfoService;

    protected override void Initialize(RequestContext requestContext)
    {
      if (formsService == null) formsService = new FormsAuthenticationService();
      if (membershipService == null) membershipService = new MembershipService();
      if (userInfoService == null) userInfoService = new UserInfoService();

      base.Initialize(requestContext);
    }

    public ActionResult LogOn()
    {
      return View();
    }

    [HttpPost]
    public ActionResult LogOn(LogOnModel model, string returnUrl)
    {
      if (ModelState.IsValid)
      {
        if (membershipService.ValidateUser(model.UserName, model.Password))
        {
          model.UserName = membershipService.CheckUserName(model.UserName);
          var cookie = formsService.SignIn(model.UserName, model.RememberMe, membershipService.IsSuperuser(model.UserName));
          Response.Cookies.Add(cookie);

          return !String.IsNullOrEmpty(returnUrl)
                   ? (ActionResult) Redirect(returnUrl)
                   : RedirectToAction("Index", "Home");
        }
        ModelState.AddModelError("", "The user name or password provided is incorrect.");
      }
      // If we got this far, something failed, redisplay form
      return View(model);
    }

    public ActionResult LogOff()
    {
      formsService.SignOut();
      return RedirectToAction("Index", "Home");
    }

    [Authorize]
    public ActionResult Profile()
    {
      UserInfoModel model = userInfoService.GetUserByName(HttpContext.User.Identity.Name);
      return View(model);
    }

    [Authorize]
    public ActionResult ChangePassword()
    {
      return View();
    }

    [Authorize]
    [HttpPost]
    public ActionResult ChangePassword(ChangePasswordModel model)
    {
      if (ModelState.IsValid)
      {
        if (membershipService.ChangePassword(User.Identity.Name, model.OldPassword, model.NewPassword))
        {
          return RedirectToAction("ChangePasswordSuccess");
        }
        ModelState.AddModelError("", "The current password is incorrect or the new password is invalid.");
      }
      return View(model);
    }

    [Authorize]
    public ActionResult ChangePasswordSuccess()
    {
      return View();
    }
  }
}
