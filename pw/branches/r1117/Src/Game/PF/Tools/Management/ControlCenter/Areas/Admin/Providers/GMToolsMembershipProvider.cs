using System;
using System.Collections.Generic;
using AdminLib.Entities;
using AdminLib.Repositories;

namespace ControlCenter.Areas.Admin.Providers
{
  public interface IMembershipProvider
  {
    IEnumerable<GMUser> GetAllUsers();
    GMUser GetUserById(int id);
    GMUser GetUserByName(string username);
    string CheckUserName(string username);
    GMUser UpdateUserInfo(int id, string fullname, string email, bool superuser);
    GMUser CreateUser(string username, string password, string fullname, string email, bool superuser);
    bool UserExists(string username);
    bool IsSuperuser(string username);
    bool ValidateUser(string username, string password);
    bool SetPassword(int id, string password);
    string DeleteUser( int userId );
  }

  public class GMToolsMembershipProvider : IMembershipProvider
  {
    private IGMUserMembershipRepository membershipRepository;
    private IGMUserRepository userRepository;

    public GMToolsMembershipProvider()
      : this(new GMUserMembershipRepository(), new GMUserRepository())
    {
    }

    public GMToolsMembershipProvider(IGMUserMembershipRepository mrepo, IGMUserRepository urepo)
    {
      membershipRepository = mrepo;
      userRepository = urepo;
    }

    #region IMembershipProvider

    public IEnumerable<GMUser> GetAllUsers()
    {
      return userRepository.GetAll();
    }

    public GMUser GetUserById(int id)
    {
      return userRepository.GetById(id);
    }

    public GMUser GetUserByName(string username)
    {
      return userRepository.GetByUserName(username);
    }

    public string CheckUserName(string username)
    {
      return membershipRepository.CheckUserName(username);
    }

    public GMUser UpdateUserInfo(int id, string fullname, string email, bool superuser)
    {
      var user = userRepository.GetById(id);
      if (user == null)
        return null;

      user.FullName = fullname;
      user.Email = email;
      user.Superuser = superuser;
      userRepository.Update(user);

      return user;
    }

    public GMUser CreateUser(string username, string password, string fullname, string email, bool superuser)
    {
      if (userRepository.GetByUserName(username) != null)
        throw new Exception("User exists");

      var user = new GMUser
                   {
                     UserName = username,
                     FullName = fullname,
                     Email = email,
                     Superuser = superuser
                   };

      return membershipRepository.CreateUser(user, password) ? user : null;
    }
    public string DeleteUser( int userId )
    {
      GMUserMembership membershipRecord = membershipRepository.GetById(userId);
      GMUser userRecord = userRepository.GetById( userId );
      //проверить что кол-во суперюзеров > 0 после удаления
      if ( userRecord.Superuser )
      {
        if ( userRepository.GetSuperUserQuantity() < 2 )
          return "You can not delete that user, mimimum one superuser is required";
      }
      membershipRepository.Remove( membershipRecord );
      userRepository.Remove( userRecord );
      return null;
    }

    public bool UserExists(string username)
    {
      return userRepository.GetByUserName(username) != null;
    }

    public bool IsSuperuser(string username)
    {
      return userRepository.GetByUserName(username).Superuser;
    }

    bool IMembershipProvider.ValidateUser(string username, string password)
    {
      return membershipRepository.ValidateUser(username, password);
    }

    public bool SetPassword(int id, string password)
    {
      return membershipRepository.SetPassword(id, password);
    }

    #endregion
  }
}