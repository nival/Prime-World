using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using AdminLib.Entities;
using ControlCenter.Areas.Admin.Providers;

namespace ControlCenter.Areas.Admin.Models
{
  public class RoleInfoModel
  {
    [Required]
    public int RoleId { get; set; }

    [Required]
    [DisplayName("Role name")]
    public string RoleName { get; set; }

    [DisplayName("Description")]
    public string Description { get; set; }

    [DisplayName("Locale")]
    public string Locale { get; set; }

    [DisplayName("Muid")]
    public string Muid { get; set; }

    private Dictionary<int, string> _users;
    public Dictionary<int, string> Users
    {
      get
      {
        if (_users == null) _users = new Dictionary<int, string>();
        return _users;
      }
      set { _users = value; }
    }

    private Dictionary<int, string> _permissions;
    public Dictionary<int, string> Permissions
    {
      get
      {
        if (_permissions == null) _permissions = new Dictionary<int, string>();
        return _permissions;
      }
      set { _permissions = value; }
    }


    public RoleInfoModel()
    {
      Users = new Dictionary<int, string>();
      Permissions = new Dictionary<int, string>();
    }

    public RoleInfoModel(GMRole gmrole)
      : this()
    {
      this.RoleId = gmrole.RoleId;
      this.RoleName = gmrole.RoleName;
      this.Description = gmrole.Description;
      this.Locale = gmrole.Locale;
      this.Muid = gmrole.Muid;

      if (gmrole.Users != null)
        gmrole.Users.ToList()
          .ForEach(u => this.Users.Add(u.UserId, u.UserName));

      if (gmrole.Permissions != null)
        gmrole.Permissions.ToList()
          .ForEach(p => this.Permissions.Add(p.PermissionId, p.PermissionName));
    }
  }

  public interface IRoleInfoService
  {
    IEnumerable<RoleInfoModel> GetAllRoles();
    RoleInfoModel GetRoleById(int id);
    RoleInfoModel ChangeRoleInfo(RoleInfoModel model, IEnumerable<int> permissions);
    RoleInfoModel ChangeRoleMembership(RoleInfoModel model, IEnumerable<int> users);
    RoleInfoModel CreateRole(RoleInfoModel model, IEnumerable<int> permissions);
    Dictionary<int, string> GetAllPermissions();
    Dictionary<int, string> GetAllUsers();
    string DeleteRole(int roleId );
  }

  public class RoleInfoService : IRoleInfoService
  {
    private IRoleProvider roleProvider;
    private IPermissionProvider permissionProvider;
    private IMembershipProvider membershipProvider;

    public RoleInfoService()
      : this(new GMToolsRoleProvider(), new GMToolsPermissionProvider(), new GMToolsMembershipProvider())
    {
    }

    public RoleInfoService(IRoleProvider rpro, IPermissionProvider ppro, IMembershipProvider mpro)
    {
      roleProvider = rpro;
      permissionProvider = ppro;
      membershipProvider = mpro;
    }

    public IEnumerable<RoleInfoModel> GetAllRoles()
    {
      return roleProvider.GetAllRoles().Select(r => new RoleInfoModel(r));
    }

    public RoleInfoModel GetRoleById(int id)
    {
      return new RoleInfoModel(roleProvider.GetRoleById(id));
    }

    public RoleInfoModel ChangeRoleInfo(RoleInfoModel model, IEnumerable<int> permissions)
    {
      GMRole updatedRole = roleProvider.UpdateRole(model.RoleId, model.RoleName, model.Description, model.Locale, model.Muid, permissions);
      return new RoleInfoModel(updatedRole);
    }

    public RoleInfoModel ChangeRoleMembership(RoleInfoModel model, IEnumerable<int> users)
    {
      GMRole updatedRole = roleProvider.UpdateRoleMembership(model.RoleId, users);
      return new RoleInfoModel(updatedRole);
    }

    public RoleInfoModel CreateRole(RoleInfoModel model, IEnumerable<int> permissions)
    {
      GMRole newRole = roleProvider.CreateRole(model.RoleName, model.Description, model.Locale, model.Muid, permissions);
      return new RoleInfoModel(newRole);
    }
    public string DeleteRole( int roleId )
    {
      return roleProvider.DeleteRole( roleId );
    }

    public Dictionary<int, string> GetAllPermissions()
    {
      var result = new Dictionary<int, string>();
      permissionProvider.GetAllPermissions().ToList()
        .ForEach(p => result.Add(p.PermissionId, p.PermissionName));
      return result;
    }

    public Dictionary<int, string> GetAllUsers()
    {
      var result = new Dictionary<int, string>();
      membershipProvider.GetAllUsers().ToList()
        .ForEach(p => result.Add(p.UserId, p.UserName));
      return result;
    }
  }

}