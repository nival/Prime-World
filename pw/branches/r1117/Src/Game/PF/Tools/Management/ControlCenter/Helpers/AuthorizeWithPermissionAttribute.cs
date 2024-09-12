using System;
using System.Linq;
using System.Web.Mvc;

namespace ControlCenter.Helpers
{
  public class AuthorizeWithPermissionAttribute : AuthorizeAttribute
  {
    public string Permission { get; set; }

    protected override bool AuthorizeCore(System.Web.HttpContextBase httpContext)
    {
      if (!base.AuthorizeCore(httpContext))
        return false;

      if (String.IsNullOrEmpty(Permission))
        return true;

      var principal = (GMToolsPrincipal) httpContext.User;
      return principal.IsSuperuser || Permission.Split(',').Any(principal.HasPermission);
    }

    protected override void HandleUnauthorizedRequest(AuthorizationContext filterContext)
    {
      filterContext.Result = new HttpStatusCodeResult(403);
      filterContext.RequestContext.HttpContext.Response.Redirect("/Home/Forbidden");
    }
  }
}