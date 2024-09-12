using System.Collections.Generic;
using System.Security.Principal;
using System.Linq;

namespace ControlCenter.Helpers
{

  public class GMToolsPrincipal : GenericPrincipal
  {
    private readonly string[] permissions;
    private readonly string[] locales;
    private readonly string[] muids;

    public GMToolsPrincipal(IIdentity identity, bool superuser, string[] roles, string[] permissions, string[] locales, string[] muids)
      : base(identity, roles)
    {
      this.permissions = permissions;
      this.IsSuperuser = superuser;
      this.locales = locales;
      this.muids = muids;
    }

    public bool IsSuperuser { get; private set; }

    public bool HasPermission(string permission)
    {
      return IsSuperuser || permissions.Any(p => p == permission);
    }

    public bool IsBoundedByLocale
    {
      get { return (locales.Length > 0) || (muids.Length > 0); }
    }

    public bool HasLocale(string locale)
    {
      return IsSuperuser || locales.Length == 0 || locales.Any(p => p == locale);
    }

    public bool HasMuid(string muid)
    {
      return IsSuperuser || muids.Length == 0 || muids.Any(p => p == muid);
    }

    public List<string> GetMuids()
    {
      return IsSuperuser || muids.Length == 0 ? null : new List<string>(muids);
    }
  }

}