using System;
using System.Collections.Generic;
using System.Linq;
using AdminLib.Entities;
using AdminLib.Repositories;

namespace ControlCenter.Areas.Admin.Providers
{
  public interface IRoleProvider
  {
    IEnumerable<GMRole> GetAllRoles();
    GMRole GetRoleById(int id);
    GMRole CreateRole(string rolename, string description, string locale, string muid, IEnumerable<int> permissions);
    GMRole UpdateRole(int id, string rolename, string description, string locale, string muid, IEnumerable<int> permissions);
    GMRole UpdateRoleMembership(int id, IEnumerable<int> users);
    GMRole AddUserInRole(int id, int userid);
    GMRole RemoveUserFromRole(int id, int userid);
    string[] GetRolesForUser(string username);
    bool IsUserInRole(string username, string roleName);
    string DeleteRole( int roleId );
  }
  
  public class GMToolsRoleProvider : IRoleProvider
  {
    private IGMRoleRepository roleRepository;
    private IGMUserRepository userRepository;

    public GMToolsRoleProvider()
      : this(new GMRoleRepository(), new GMUserRepository())
    {
    }

    public GMToolsRoleProvider(IGMRoleRepository rrepo, IGMUserRepository urepo)
    {
      roleRepository = rrepo;
      userRepository = urepo;
    }

    #region IRoleProvider

    IEnumerable<GMRole> IRoleProvider.GetAllRoles()
    {
      return roleRepository.GetAll();
    }

    public GMRole GetRoleById(int id)
    {
      return roleRepository.GetById(id);
    }

    public GMRole CreateRole(string rolename, string description, string locale, string muid, IEnumerable<int> permissions)
    {
      if (rolename == null) throw new ArgumentNullException("rolename");

      var role = new GMRole
                   {
                     RoleName = rolename,
                     Description = description,
                     Locale = locale,
                     Muid = muid,
                     Permissions = new List<GMPermission>(),
                     Users = new List<GMUser>()
                   };
      roleRepository.Add(role);

      if (permissions != null)
        foreach (int permissionid in permissions)
          roleRepository.AddPermission(role, permissionid);

      return role;
    }

    public string DeleteRole( int roleId )
    {
      GMRole role = GetRoleById( roleId );
      if ( ! roleRepository.CheckNoUsersReferThatRole( role ))
        return "You can not delete that role, there are users refering it";
      roleRepository.Remove( role );
      return null;
    }

    public GMRole UpdateRole(int id, string rolename, string description, string locale, string muid, IEnumerable<int> permissions)
    {
      if (rolename == null) throw new ArgumentNullException("rolename");
      if (permissions == null) permissions = new int[0];

      var role = roleRepository.GetById(id);
      if (role == null)
        return null;

      role.RoleName = rolename;
      role.Description = description;
      role.Locale = locale;
      role.Muid = muid;
      roleRepository.Update(role);

      // remove disabled permissions from role
      int[] permissionsToRemove = role.Permissions.Select(p => p.PermissionId).Except(permissions).ToArray();
      if (permissionsToRemove.Length > 0)
      {
        foreach (int permissionid in permissionsToRemove)
        {
          roleRepository.RemovePermission(role, permissionid);
        }
      }

      // add new permissions to role
      int[] permissionsToAdd = permissions.Except(role.Permissions.Select(p => p.PermissionId)).ToArray();
      if (permissionsToAdd.Length > 0)
      {
        foreach (int permissionid in permissionsToAdd)
        {
          roleRepository.AddPermission(role, permissionid);
        }
      }

      return role;
    }

    public GMRole UpdateRoleMembership(int id, IEnumerable<int> users)
    {
      if (users == null) users = new int[0];

      var role = roleRepository.GetById(id);
      if (role == null)
        return null;

      // remove users from role
      int[] usersToRemove = role.Users.Select(u => u.UserId).Except(users).ToArray();
      if (usersToRemove.Length > 0)
      {
        foreach (int userid in usersToRemove)
        {
          roleRepository.RemoveUser(role, userid);
        }
      }

      // add new users to role
      int[] usersToAdd = users.Except(role.Users.Select(p => p.UserId)).ToArray();
      if (usersToAdd.Length > 0)
      {
        foreach (int userid in usersToAdd)
        {
          roleRepository.AddUser(role, userid);
        }
      }

      return role;
    }

    public GMRole AddUserInRole(int id, int userid)
    {
      var role = roleRepository.GetById(id);
      if (role == null)
        return null;

      return roleRepository.AddUser(role, userid)
               ? role
               : null;
    }

    public GMRole RemoveUserFromRole(int id, int userid)
    {
      var role = roleRepository.GetById(id);
      if (role == null)
        return null;

      return roleRepository.RemoveUser(role, userid)
               ? role
               : null;
    }

    public string[] GetRolesForUser(string username)
    {
      var user = userRepository.GetByUserName(username);
      if (user == null)
        throw new Exception(String.Format("User \"{0}\" was not found in database", username));

      return user.Roles.Select(r => r.RoleName).ToArray();
    }

    public bool IsUserInRole(string username, string roleName)
    {
      var user = userRepository.GetByUserName(username);
      if (user == null)
        throw new Exception(String.Format("User \"{0}\" was not found in database", username));

      return user.Roles.Any(r => r.RoleName == roleName);
    }

    #endregion

  }
}