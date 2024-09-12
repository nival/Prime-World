using System;
using System.Security.Cryptography;
using System.Text;
using AdminLib.Entities;
using NHibernate.Criterion;

namespace AdminLib.Repositories
{
  public interface IGMUserMembershipRepository : IRepository<GMUserMembership>
  {
    bool CreateUser(GMUser user, string password);
    bool ValidateUser(string username, string password);
    bool SetPassword(int userid, string password);
    string CheckUserName(string username);
  }

  public class GMUserMembershipRepository : Repository<GMUserMembership>, IGMUserMembershipRepository
  {
    public bool CreateUser(GMUser user, string password)
    {
      if (Session.Contains(user))
        return false;

      var checkforuser = Session.CreateCriteria<GMUser>()
        .Add(Restrictions.InsensitiveLike("UserName", user.UserName))
        .UniqueResult<GMUser>();

      if (checkforuser != null)
        return false;

      var membership = new GMUserMembership
                         {
                           GMUser = user,
                           CreateDate = DateTime.Now,
                           Password = EncryptPassword(password)
                         };
     
      using (var tran = Session.BeginTransaction())
      {
        Session.Save(membership);
        tran.Commit();
      }

      return true;
    }

    public bool ValidateUser(string username, string password)
    {
      var user = Session.CreateCriteria<GMUser>()
        .Add(Restrictions.InsensitiveLike("UserName", username))
        .UniqueResult<GMUser>();

      if (user == null)
        return false;

      var membership = GetById(user.UserId);
      Session.Refresh(membership);

      if (membership.Password != EncryptPassword(password))
        return false;

      using (var tran = Session.BeginTransaction())
      {
        membership.LastLoginDate = DateTime.Now;
        Session.SaveOrUpdate(membership);
        tran.Commit();
      }
      return true;
    }

    public bool SetPassword(int userid, string password)
    {
      var membership = GetById(userid);

      if (membership == null)
        throw new Exception(String.Format("Not exists membership for UserId = {0}", userid));

      using (var tran = Session.BeginTransaction())
      {
        membership.Password = EncryptPassword(password);
        tran.Commit();
      }
      return true;
    }

    public string CheckUserName(string username)
    {
      var user = Session.CreateCriteria<GMUser>()
        .Add(Restrictions.InsensitiveLike("UserName", username))
        .UniqueResult<GMUser>();

      if (user == null)
        throw new Exception(String.Format("User with name {0} not found in database", username));

      return user.UserName;
    }

    public static string EncryptPassword(string password)
    {
      var md5Crypter = new MD5CryptoServiceProvider();
      
      byte[] data = Encoding.UTF8.GetBytes(password);
      data = md5Crypter.ComputeHash(data);
      
      return Convert.ToBase64String(data);
    }
  }
}