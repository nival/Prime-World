using System;
using ControlCenter.Areas.Admin.Providers;
using log4net;

namespace ControlCenter.Areas.Admin.Models
{
  public interface IMembershipService
  {
    bool ValidateUser(string userName, string password);
    bool IsSuperuser(string username);
    string CheckUserName(string userName);
    bool ChangePassword(string userName, string oldPassword, string newPassword);
  }

  public class MembershipService : IMembershipService
  {
    private readonly IMembershipProvider membershipProvider;

    public MembershipService()
      : this(new GMToolsMembershipProvider())
    {
    }

    public MembershipService(IMembershipProvider provider)
    {
      membershipProvider = provider;
    }

    public bool ValidateUser(string userName, string password)
    {
      return membershipProvider.ValidateUser(userName, password);
    }

    public bool IsSuperuser(string username)
    {
      return membershipProvider.IsSuperuser(username);
    }

    public string CheckUserName(string username)
    {
      return membershipProvider.CheckUserName(username);
    }

    public bool ChangePassword(string userName, string oldPassword, string newPassword)
    {
      if (!ValidateUser(userName, oldPassword))
        return false;

      var user = membershipProvider.GetUserByName(userName);
      return membershipProvider.SetPassword(user.UserId, newPassword);
    }
  }
}