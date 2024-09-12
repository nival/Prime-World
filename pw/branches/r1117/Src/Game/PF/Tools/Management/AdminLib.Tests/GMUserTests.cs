using System.Linq;
using AdminLib.Entities;
using AdminLib.Repositories;
using AdminLib.Tests.Properties;
using NHibernate;
using NUnit.Framework;

namespace AdminLib.Tests
{
  [TestFixture]
  public class GMUserTests
  {
    [TestFixtureSetUp]
    public void Init()
    {
      var context = new DBContext(Settings.Default.ConnectionString);
      NHibernateHelper.Init(context);
    }

    [SetUp]
    public void ClearAll()
    {
      using (var s = NHibernateHelper.OpenSession())
      {
        s.Delete("from GMUserMembership");
        s.Delete("from GMUser");
        s.Delete("from GMRole");
        s.Flush();
      }
    }

    public int CreateGMUser()
    {
      return CreateGMUser("username", "Full Name", "some@ema.il");
    }

    public int CreateGMUser(string username, string fullname, string email)
    {
      using (var repo = new GMUserRepository())
      {
        var u = new GMUser
                  {
                    UserName = username,
                    FullName = fullname,
                    Email = email
                  };
        repo.Add(u);
        
        return u.UserId;
      }
    }

    [Test]
    public void TestOpenSession()
    {
      ISession actual = NHibernateHelper.OpenSession();
      Assert.IsNotNull(actual);
    }

    [Test]
    public void TestAddNewUser()
    {
      int userid;
      string username = "test";
      string fullname = "Test Morjovy";
      string email = "admin@mail.ru";
      
      using (var repo = new GMUserRepository())
      {
        var user = new GMUser
                     {
                       UserName = username,
                       FullName = fullname,
                       Email = email
                     };
        repo.Add(user);
        userid = user.UserId;
      }

      using (var repo = new GMUserRepository())
      {
        var user = repo.GetById(userid);
        Assert.AreEqual(user.UserName, username);
        Assert.AreEqual(user.FullName, fullname);
        Assert.AreEqual(user.Email, email);
      }
    }

    [Test]
    public void TestUpdateUser()
    {
      string newfullname = "new full name";
      string newemail = "new@ema.il";

      var userid = CreateGMUser();

      using (var repo = new GMUserRepository())
      {
        var user = repo.GetById(userid);
        Assert.IsNotNull(user);
        Assert.AreNotEqual(user.FullName, newfullname);
        Assert.AreNotEqual(user.Email, newemail);
        user.FullName = newfullname;
        user.Email = newemail;
        repo.Update(user);
      }

      using (var repo = new GMUserRepository())
      {
        var user = repo.GetById(userid);
        Assert.AreEqual(user.FullName, newfullname);
        Assert.AreEqual(user.Email, newemail);
      }
    }

    [Test]
    public void TestRemoveUser()
    {
      var userid = CreateGMUser();

      using (var repo = new GMUserRepository())
      {
        var user = repo.GetById(userid);
        Assert.IsNotNull(user);
        repo.Remove(user);
      }

      using (var repo = new GMUserRepository())
      {
        var user = repo.GetById(userid);
        Assert.IsNull(user);
      }
    }

    [Test]
    public void TestGetAllUsers()
    {
      var userid1 = CreateGMUser("user1", "full name 1", "user1@ema.il");
      var userid2 = CreateGMUser("user2", "full name 2", "user2@ema.il");

      using (var repo = new GMUserRepository())
      {
        var users = repo.GetAll();
        Assert.AreEqual(users.Count(), 2);
        Assert.That(users.Any(u => u.UserId == userid1));
        Assert.That(users.Any(u => u.UserId == userid2));
      }
    }

    [Test]
    public void TestAddRoleToUser()
    {
      var userid = CreateGMUser();

      var role1 = new GMRole { RoleName = "Foo", Description = "Bar" };
      var role2 = new GMRole { RoleName = "FFFUUU", Description = "no comments" };

      using (var repo = new GMRoleRepository())
      {
        repo.Add(role1);
        repo.Add(role2);
      }

      using (var repo = new GMUserRepository())
      {
        var user = repo.GetById(userid);
        user.Roles.Add(role1);
        user.Roles.Add(role2);
        repo.Update(user);
      }

      using (var repo = new GMUserRepository())
      {
        var user = repo.GetById(userid);
        Assert.AreEqual(user.Roles.Count, 2);
        Assert.That(user.Roles.Any(r => r.RoleId == role1.RoleId));
        Assert.That(user.Roles.Any(r => r.RoleId == role2.RoleId));
      }
    }

    [Test]
    public void TestGetByUserName()
    {
      int userid = CreateGMUser("Eyjafjallajökull", "doesn't matter", "smoke@mail.is");

      using (var repo = new GMUserRepository())
      {
        var user1 = repo.GetByUserName("icantspellitproper");
        Assert.IsNull(user1);

        var user2 = repo.GetByUserName("Eyjafjallajökull");
        Assert.IsNotNull(user2);
        Assert.AreEqual(userid, user2.UserId);
      }
    }

    [Test]
    public void TestGetNumberOfUsers()
    {
      CreateGMUser("user1", "fullname1", "email1");
      CreateGMUser("user2", "fullname2", "email2");
      
      using (var repo = new GMUserRepository())
      {
        Assert.AreEqual(2, repo.GetTotalCount());
      }

      CreateGMUser("user3", "fullname3", "email3");

      using (var repo = new GMUserRepository())
      {
        Assert.AreEqual(3, repo.GetTotalCount());
      }
    }
  }
}
