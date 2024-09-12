using System;
using System.Diagnostics;
using System.Linq;
using AdminLib.Entities;
using AdminLib.Repositories;
using AdminLib.Tests.Properties;
using NHibernate;
using NUnit.Framework;

namespace AdminLib.Tests
{
  [TestFixture]
  public class GMUserMembershipTests
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
        s.Flush();
      }
    }

    public int CreateGMUserMembership()
    {
      return CreateGMUserMembership("username", "qwerty", new DateTime(2011, 06, 01), new DateTime(2011, 06, 04));
    }

    public int CreateGMUserMembership(string username, string password, DateTime createdate, DateTime lastlogindate)
    {
      using (var repo = new GMUserMembershipRepository())
      {
        var user = new GMUser
        {
          UserName = username,
          FullName = "full name",
          Email = "user@ema.il"
        };

        var umemb = new GMUserMembership
                      {
                        GMUser = user,
                        Password = GMUserMembershipRepository.EncryptPassword(password),
                        CreateDate = createdate,
                        LastLoginDate = lastlogindate
                      };
        repo.Add(umemb);

        return umemb.GMUser.UserId;
      }
    }


    [Test]
    public void TestOpenSession()
    {
      ISession actual = NHibernateHelper.OpenSession();
      Assert.IsNotNull(actual);
    }

    [Test]
    public void TestAddUserMembership()
    {
      int usermemid;
      var user = new GMUser
                   {
                     UserName = "username",
                     FullName = "full name",
                     Email = "user@ema.il"
                   };
      string password = "qwerty";
      var createdate = new DateTime(2011, 06, 04, 11, 00, 00);
      var lastlogindate = new DateTime(2011, 06, 04, 12, 00, 00);

      using (var repo = new GMUserMembershipRepository())
      {
        var usermem = new GMUserMembership
                     {
                       GMUser = user,
                       Password = password,
                       CreateDate = createdate,
                       LastLoginDate = lastlogindate
                     };
        repo.Add(usermem);
        usermemid = usermem.GMUser.UserId;
      }

      using (var repo = new GMUserMembershipRepository())
      {
        var usermem = repo.GetById(usermemid);
        Assert.IsNotNull(usermem.GMUser);
        Assert.AreEqual(usermem.GMUser.UserId, user.UserId);
        Assert.AreEqual(usermem.Password, password);
        Assert.AreEqual(usermem.CreateDate, createdate);
        Assert.AreEqual(usermem.LastLoginDate, lastlogindate);
      }
    }

    [Test]
    public void TestUpdateUserMembership()
    {
      var usermemid = CreateGMUserMembership();

      string newpassword = "111";
      var newcreatedate = new DateTime(2011, 06, 04, 11, 00, 00);
      var newlastlogindate = new DateTime(2011, 06, 04, 12, 00, 00);

      using (var repo = new GMUserMembershipRepository())
      {
        var usermem = repo.GetById(usermemid);
        Assert.IsNotNull(usermem);

        usermem.Password = newpassword;
        usermem.CreateDate = newcreatedate;
        usermem.LastLoginDate = newlastlogindate;

        repo.Update(usermem);
      }

      using (var repo = new GMUserMembershipRepository())
      {
        var usermem = repo.GetById(usermemid);
        Assert.AreEqual(usermem.Password, newpassword);
        Assert.AreEqual(usermem.CreateDate, newcreatedate);
        Assert.AreEqual(usermem.LastLoginDate, newlastlogindate);
      }
    }

    [Test]
    public void TestRemoveUserMembership()
    {
      var usermemid = CreateGMUserMembership();

      using (var repo = new GMUserMembershipRepository())
      {
        var usermem = repo.GetById(usermemid);
        Assert.IsNotNull(usermem);

        repo.Remove(usermem);
      }

      using (var repo = new GMUserMembershipRepository())
      {
        var usermem = repo.GetById(usermemid);
        Assert.IsNull(usermem);
      }
    }

    [Test]
    public void TestGetAllUsers()
    {
      var usermemid1 = CreateGMUserMembership("user1", "qwerty1", new DateTime(2011, 06, 01), new DateTime(2011, 06, 02));
      var usermemid2 = CreateGMUserMembership("user2", "qwerty2", new DateTime(2011, 06, 03), new DateTime(2011, 06, 04));

      using (var repo = new GMUserMembershipRepository())
      {
        var usermems = repo.GetAll();
        Assert.AreEqual(usermems.Count(), 2);
        Assert.That(usermems.Any(u => u.GMUser.UserId == usermemid1));
        Assert.That(usermems.Any(u => u.GMUser.UserId == usermemid2));
      }
    }

    [Test]
    public void TestCreateUser()
    {
      CreateGMUserMembership("existinguser", "123", new DateTime(2011, 06, 03), new DateTime(2011, 06, 04));

      var user = new GMUser { UserName = "newuser" };
      var baduser = new GMUser { UserName = "existinguser" };
      
      using (var repo = new GMUserMembershipRepository())
      {
        Assert.That(repo.CreateUser(user, "кириллическийпасворд"));
        Assert.That(!repo.CreateUser(baduser, "234"));
      }

      using (var repo = new GMUserMembershipRepository())
      {
        Assert.That(repo.ValidateUser("newuser", "кириллическийпасворд"));
        Assert.That(!repo.ValidateUser("newuser", "incorrectpassword"));

        Assert.That(repo.ValidateUser("existinguser", "123"));
        Assert.That(!repo.ValidateUser("existinguser", "234"));
      }
    }

    [Test]
    public void TestValidateUser()
    {
      var initialLastLogin = new DateTime(2011, 06, 06);
      string rightlogin = "login";
      string rightpassword = "password";
      string wronglogin = "ololo";
      string wrongpassword = "wrongpassword";

      var usermemid = CreateGMUserMembership(rightlogin, rightpassword, new DateTime(2011, 06, 01), initialLastLogin);

      using (var repo = new GMUserMembershipRepository())
      {
        Assert.That(!repo.ValidateUser(wronglogin, wrongpassword));
        Assert.That(!repo.ValidateUser(rightlogin, wrongpassword));
        Assert.That(!repo.ValidateUser(wronglogin, rightpassword));
        var usermem = repo.GetById(usermemid);
        Assert.AreEqual(usermem.LastLoginDate, initialLastLogin);

        Assert.That(repo.ValidateUser(rightlogin, rightpassword));
      }

      using (var repo = new GMUserMembershipRepository())
      {
        var usermem = repo.GetById(usermemid);
        Assert.Greater(usermem.LastLoginDate, initialLastLogin);
      }
    }

    [Test]
    public void TestCheckUserName()
    {
      var originalName = "PascalCasedUser";
      CreateGMUserMembership(originalName, "123123", DateTime.Now, DateTime.Now);

      using (var repo = new GMUserMembershipRepository())
      {
        Assert.AreEqual(originalName, repo.CheckUserName("pascalcaseduser"));
        Assert.AreEqual(originalName, repo.CheckUserName("PASCALcaseduSer"));
        try
        {
          repo.CheckUserName("camelCaseUser");
          Assert.Fail("Wrong name checked without exception");
        }
        catch (Exception)
        {
          Assert.That(true);
        }
      }
    }

  }
}
