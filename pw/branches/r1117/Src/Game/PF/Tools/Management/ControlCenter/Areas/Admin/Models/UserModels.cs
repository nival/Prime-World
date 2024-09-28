using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using AdminLib.Entities;
using ControlCenter.Areas.Admin.Providers;

namespace ControlCenter.Areas.Admin.Models
{
  public class UserInfoModel
  {
    [Required]
    public int UserId { get; set; }

    [Required]
    [DisplayName("User name")]
    public string UserName { get; set; }

    [Required]
    [DisplayName("Full name")]
    public string FullName { get; set; }

    [Required]
    [DataType(DataType.EmailAddress)]
    [RegularExpression(@"\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*", ErrorMessage = "Invalid email")]
    [DisplayName("Email address")]
    public string Email { get; set; }

    [DisplayName("Superuser")]
    public bool Superuser { get; set; }

    private Dictionary<int, string> _roles;
    public Dictionary<int, string> Roles
    {
      get
      {
        if (_roles == null) _roles = new Dictionary<int, string>();
        return _roles;
      }
      set { _roles = value; }
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

    public UserInfoModel()
    {
      Roles = new Dictionary<int, string>();
      Permissions = new Dictionary<int, string>();
    }

    public UserInfoModel(GMUser gmuser)
      : this()
    {
      this.UserId = gmuser.UserId;
      this.UserName = gmuser.UserName;
      this.FullName = gmuser.FullName;
      this.Email = gmuser.Email;
      this.Superuser = gmuser.Superuser;

      gmuser.Roles.ToList()
        .ForEach(a => this.Roles.Add(a.RoleId, a.RoleName));

      gmuser.Roles.SelectMany(r => r.Permissions).Distinct().ToList()
        .ForEach(a => this.Permissions.Add(a.PermissionId, a.PermissionName));
    }
  }

  [PropertiesMustMatch("Password", "ConfirmPassword", ErrorMessage = "The password and confirmation password do not match.")]
  public class UserCreateModel
  {
    [Required]
    [DisplayName("User name")]
    public string UserName { get; set; }

    [Required]
    [DisplayName("Full name")]
    public string FullName { get; set; }

    [Required]
    [DataType(DataType.EmailAddress)]
    [RegularExpression(@"\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*", ErrorMessage = "Invalid email")]
    [DisplayName("Email address")]
    public string Email { get; set; }

    [DisplayName("Superuser")]
    public bool Superuser { get; set; }

    [Required]
    [ValidatePasswordLength]
    [DataType(DataType.Password)]
    [DisplayName("Password")]
    public string Password { get; set; }

    [Required]
    [DataType(DataType.Password)]
    [DisplayName("Confirm password")]
    public string ConfirmPassword { get; set; }
  }

  [PropertiesMustMatch("NewPassword", "ConfirmPassword", ErrorMessage = "The new password and confirmation password do not match.")]
  public class AdminUserResetPasswordModel
  {
    [Required]
    public int UserId { get; set; }

    public string UserName { get; set; }

    [Required]
    [DataType(DataType.Password)]
    [DisplayName("New password")]
    public string NewPassword { get; set; }

    [Required]
    [DataType(DataType.Password)]
    [DisplayName("Confirm new password")]
    public string ConfirmPassword { get; set; }
  }

  public interface IUserInfoService
  {
    IEnumerable<UserInfoModel> GetAllUsers();
    UserInfoModel GetUserById(int id);
    UserInfoModel GetUserByName(string name);
    UserInfoModel ChangeUserInfo(UserInfoModel model);
    bool UserExists(int id);
    bool UserExists(string username);
    int CreateUser(UserCreateModel model);
    bool SetPassword(int id, string password);
    Dictionary<int, string> GetAllRoles();
    bool ChangeRoles(UserInfoModel model, IEnumerable<int> roles);
    string DeleteUser( int userId );
  }

  public class UserInfoService : IUserInfoService
  {
    private IMembershipProvider membershipProvider;
    private IRoleProvider roleProvider;

    public UserInfoService()
      : this(new GMToolsMembershipProvider(), new GMToolsRoleProvider())
    {
    }

    public UserInfoService(IMembershipProvider mpro, IRoleProvider rpro)
    {
      membershipProvider = mpro;
      roleProvider = rpro;
    }

    public IEnumerable<UserInfoModel> GetAllUsers()
    {
      return membershipProvider.GetAllUsers().Select(u => new UserInfoModel(u));
    }

    public Dictionary<int, string> GetAllRoles()
    {
      var result = new Dictionary<int, string>();
      roleProvider.GetAllRoles().ToList()
        .ForEach(p => result.Add(p.RoleId, p.RoleName));
      return result;
    }

    public bool ChangeRoles(UserInfoModel model, IEnumerable<int> roles)
    {
      if (model == null) throw new ArgumentNullException("model");
      if (roles == null) throw new ArgumentNullException("roles");

      if (model.Roles != null && model.Roles.Count > 0)
      {
        model.Roles.Keys.Except(roles).ToList()
        .ForEach(r => roleProvider.RemoveUserFromRole(r, model.UserId));
      }

      if (roles.Count() > 0)
      {
        var modelRoles = model.Roles != null ? model.Roles.Keys.AsEnumerable() : new int[0];
        roles.Except(modelRoles).ToList()
          .ForEach(r => roleProvider.AddUserInRole(r, model.UserId));
      }
      

      model.Roles.Keys.Except(roles).ToList()
        .ForEach(r => roleProvider.RemoveUserFromRole(r, model.UserId));

      model.Roles.Keys.Except(roles).ToList()
        .ForEach(r => roleProvider.RemoveUserFromRole(r, model.UserId));

      return true;
    }

    public UserInfoModel GetUserById(int id)
    {
      var user = membershipProvider.GetUserById(id);
      return user != null ? new UserInfoModel(user) : null;
    }

    public UserInfoModel GetUserByName(string name)
    {
      var user = membershipProvider.GetUserByName(name);
      return user != null ? new UserInfoModel(user) : null;
    }

    public UserInfoModel ChangeUserInfo(UserInfoModel model)
    {
      var updatedUser = membershipProvider.UpdateUserInfo(model.UserId, model.FullName, model.Email, model.Superuser);
      return new UserInfoModel(updatedUser);
    }

    public bool UserExists(int id)
    {
      return membershipProvider.GetUserById(id) != null;
    }

    public bool UserExists(string username)
    {
      return membershipProvider.UserExists(username);
    }

    public int CreateUser(UserCreateModel model)
    {
      var newUser = membershipProvider.CreateUser(model.UserName, model.Password, model.FullName, model.Email, model.Superuser);
      return newUser.UserId;
    }

    public bool SetPassword(int id, string password)
    {
      return membershipProvider.SetPassword(id, password);
    }

    public string DeleteUser( int userId )
    {
      return membershipProvider.DeleteUser( userId );
    }
  }
}