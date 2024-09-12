using System;
using System.Web;
using System.Web.Security;
using ControlCenter.Areas.Admin.Providers;

namespace ControlCenter.Areas.Admin.Models
{
  public interface IFormsAuthenticationService
  {
    HttpCookie SignIn(string userName, bool createPersistentCookie, bool issuperuser);
    void SignOut();
  }

  public class FormsAuthenticationService : IFormsAuthenticationService
  {
    private readonly IPermissionProvider _permissionProvider;
    private readonly IRoleProvider _roleProvider;

    public FormsAuthenticationService()
      : this(new GMToolsRoleProvider(), new GMToolsPermissionProvider())
    {
    }

    public FormsAuthenticationService(IRoleProvider roleProvider, IPermissionProvider permissionProvider)
    {
      this._roleProvider = roleProvider;
      this._permissionProvider = permissionProvider;
    }

    public HttpCookie SignIn(string userName, bool createPersistentCookie, bool issuperuser)
    {
      if (String.IsNullOrEmpty(userName)) throw new ArgumentException("Value cannot be null or empty.", "userName");

      var userdata = new CustomUserData
                       {
                         superuser = issuperuser,
                         roles = _roleProvider.GetRolesForUser(userName),
                         permissions = _permissionProvider.GetPermissionsForUser(userName),
                         locales = _permissionProvider.GetLocalesForUser(userName),
                         muids = _permissionProvider.GetMuidsForUser(userName),
                       };

      var authTicket = new FormsAuthenticationTicket(1, userName, DateTime.Now, DateTime.Now.AddHours(12),
                                                     createPersistentCookie, userdata.Serialize());
      string encryptedTicket = FormsAuthentication.Encrypt(authTicket);
      var authCookie = new HttpCookie(FormsAuthentication.FormsCookieName, encryptedTicket);
      if (createPersistentCookie)
        authCookie.Expires = authTicket.Expiration;

      return authCookie;
    }

    public void SignOut()
    {
      FormsAuthentication.SignOut();
    }
  }
}