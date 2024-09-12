using System;
using System.Collections.Generic;
using System.Linq;
using ControlCenter.Areas.Admin.Providers;

namespace ControlCenter.Areas.Admin.Models
{
  public interface IAdminInfoService
  {
    Dictionary<int, string> GetAllUsers();
    Dictionary<int, string> GetAllRoles();
  }

  public class AdminInfoService : IAdminInfoService
  {
    private readonly IMembershipProvider membershipProvider;
    private readonly IRoleProvider roleProvider;

    public AdminInfoService()
      : this(new GMToolsMembershipProvider(), new GMToolsRoleProvider())
    {
    }

    public AdminInfoService(IMembershipProvider mpro, IRoleProvider rpro)
    {
      membershipProvider = mpro;
      roleProvider = rpro;
    }

    public Dictionary<int, string> GetAllUsers()
    {
      var result = new Dictionary<int, string>();
      
      var users = membershipProvider.GetAllUsers();
      if (users != null)
        users.ToList().ForEach(u => result.Add(u.UserId, u.UserName));
      
      return result;
    }

    public Dictionary<int, string> GetAllRoles()
    {
      var result = new Dictionary<int, string>();

      var roles = roleProvider.GetAllRoles();
      if (roles != null)
        roles.ToList().ForEach(r => result.Add(r.RoleId, r.RoleName));

      return result;
    }
  }
}