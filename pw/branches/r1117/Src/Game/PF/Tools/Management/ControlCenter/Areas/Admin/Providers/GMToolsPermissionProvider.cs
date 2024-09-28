using System;
using System.Collections.Generic;
using System.Linq;
using AdminLib.Entities;
using AdminLib.Repositories;

namespace ControlCenter.Areas.Admin.Providers
{
  public interface IPermissionProvider
  {
    bool RoleHasPermission(string rolename, string permissionname);
    bool UserHasPermission(string username, string permissionname);

    string[] GetPermissionsForRole(string rolename);
    string[] GetPermissionsForUser(string username);
    string[] GetLocalesForUser(string username);
    string[] GetMuidsForUser(string username);

    int GetNumberOfPermissions();
    IEnumerable<GMPermission> GetAllPermissions();
  }
  
  public class GMToolsPermissionProvider : IPermissionProvider
  {
    private IGMRoleRepository roleRepository;
    private IGMUserRepository userRepository;
    private IGMPermissionRepository permissionRepository;

    public GMToolsPermissionProvider()
      : this(new GMRoleRepository(), new GMUserRepository(), new GMPermissionRepository())
    {
    }

    public GMToolsPermissionProvider(IGMRoleRepository rrepo, IGMUserRepository urepo, IGMPermissionRepository prepo)
    {
      roleRepository = rrepo;
      userRepository = urepo;
      permissionRepository = prepo;
    }

    public int GetNumberOfPermissions()
    {
      return roleRepository.GetTotalCount();
    }

    public IEnumerable<GMPermission> GetAllPermissions()
    {
      return permissionRepository.GetAll();
    }

    public bool RoleHasPermission(string rolename, string permissionname)
    {
      var role = roleRepository.GetByRoleName(rolename);
      if (role == null)
        throw new Exception(String.Format("Role \"{0}\" not exists in database", rolename));

      return role.Permissions.Any(p => p.PermissionName == permissionname);
    }

    public bool UserHasPermission(string username, string permissionname)
    {
      var user = userRepository.GetByUserName(username);
      if (user == null)
        throw new Exception(String.Format("User \"{0}\" not exists in database", username));

      return user.Roles.Any(r => r.Permissions.Any(p => p.PermissionName == permissionname));
    }

    public string[] GetPermissionsForRole(string rolename)
    {
      var role = roleRepository.GetByRoleName(rolename);
      if (role == null)
        throw new Exception(String.Format("Role \"{0}\" not exists in database", rolename));

      return role.Permissions.Select(p => p.PermissionName).ToArray();
    }

    public string[] GetPermissionsForUser(string username)
    {
      var user = userRepository.GetByUserName(username);
      if (user == null)
        throw new Exception(String.Format("User \"{0}\" not exists in database", username));

      return user.Roles.Select(r => r.Permissions)
        .SelectMany(p => p).Distinct()
        .Select(p => p.PermissionName)
        .ToArray();
    }

    public string[] GetLocalesForUser(string username)
    {
      var user = userRepository.GetByUserName(username);
      if (user == null)
        throw new Exception(String.Format("User \"{0}\" not exists in database", username));

      return user.Roles.Any(r => r.Locale == null)
               ? new string[0]
               : user.Roles.Select(r => r.Locale).ToArray();
    }

    public string[] GetMuidsForUser(string username)
    {
      var user = userRepository.GetByUserName(username);
      if (user == null)
        throw new Exception(String.Format("User \"{0}\" not exists in database", username));

      return user.Roles.Any(r => r.Muid == null)
               ? new string[0]
               : user.Roles.Select(r => r.Muid).ToArray();
    }
  }

}