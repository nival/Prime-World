using System.Linq;
using AdminLib.Entities;
using AdminLib.Repositories;
using AdminLib.Tests.Properties;
using NHibernate;
using NUnit.Framework;

namespace AdminLib.Tests
{
  [TestFixture]
  public class GMRoleTests
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
        s.Delete("from GMRole");
        s.Delete("from GMUser");
        s.Delete("from GMPermission");
        s.Flush();
      }
    }

    public int CreateGMRole()
    {
      return CreateGMRole("Role name", "Long and boring description", "test locale", "test muid");
    }

    public int CreateGMRole(string rolename, string description, string locale, string muid)
    {
      using (var repo = new GMRoleRepository())
      {
        var r = new GMRole
                  {
                    RoleName = rolename,
                    Description = description,
                    Locale = locale,
                    Muid = muid
                  };
        repo.Add(r);

        return r.RoleId;
      }
    }

    [Test]
    public void TestOpenSession()
    {
      ISession actual = NHibernateHelper.OpenSession();
      Assert.IsNotNull(actual);
    }

    [Test]
    public void TestAddNewRole()
    {
      int roleid;
      string rolename = "Test users";
      string description = "Useless guys, we need them to produce a biofuel";
      string locale = "All the World";
      string muid = "Mooid";

      using (var repo = new GMRoleRepository())
      {
        var role = new GMRole
        {
          RoleName = rolename,
          Description = description,
          Locale = locale,
          Muid = muid
        };
        repo.Add(role);
        roleid = role.RoleId;
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        Assert.AreEqual(role.RoleName, rolename);
        Assert.AreEqual(role.Description, description);
        Assert.AreEqual(role.Locale, locale);
        Assert.AreEqual(role.Muid, muid);
      }
    }

    [Test]
    public void TestUpdateRole()
    {
      string newrolename = "Cool users";
      string newdescription = "Another useless guys";

      var roleid = CreateGMRole();

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        Assert.IsNotNull(role);
        Assert.AreNotEqual(role.RoleName, newrolename);
        Assert.AreNotEqual(role.Description, newdescription);
        role.RoleName = newrolename;
        role.Description = newdescription;
        repo.Update(role);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        Assert.AreEqual(role.RoleName, newrolename);
        Assert.AreEqual(role.Description, newdescription);
      }
    }

    [Test]
    public void TestRemoveRole()
    {
      var roleid = CreateGMRole();

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        Assert.IsNotNull(role);
        repo.Remove(role);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        Assert.IsNull(role);
      }
    }

    [Test]
    public void TestRemoveRoleLinkedToObjects()
    {
      var roleid = CreateGMRole();
      int permid, userid;
      
      using (var repo = new GMPermissionRepository())
      {
        var perm = new GMPermission { PermissionName = "CanDoSmth" };
        repo.Add(perm);
        permid = perm.PermissionId;
      }

      using (var repo = new GMUserRepository())
      {
        var user = new GMUser { UserName = "Someone" };
        repo.Add(user);
        userid = user.UserId;
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        repo.AddPermission(role, permid);
        repo.AddUser(role, userid);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        Assert.IsNotNull(role);
        repo.Remove(role);
      }

      using (var repo = new GMPermissionRepository())
      {
        var perm = repo.GetById(permid);
        Assert.IsNotNull(perm);
      }

      using (var repo = new GMUserRepository())
      {
        var user = repo.GetById(userid);
        Assert.IsNotNull(user);
      }
    }

    [Test]
    public void TestGetAllRoles()
    {
      var roleid1 = CreateGMRole("Role 1", "Description 1", "Locale 1", "Muid 1");
      var roleid2 = CreateGMRole("Role 2", "Description 2", "Locale 2", "Muid 2");
      var roleid3 = CreateGMRole("Role 3", "Description 3", "Locale 3", "Muid 3");

      using (var repo = new GMRoleRepository())
      {
        var roles = repo.GetAll();
        Assert.AreEqual(roles.Count(), 3);
        Assert.That(roles.Any(u => u.RoleId == roleid1));
        Assert.That(roles.Any(u => u.RoleId == roleid2));
        Assert.That(roles.Any(u => u.RoleId == roleid3));
      }
    }

    [Test]
    public void TestAddUserToRole()
    {
      var roleid = CreateGMRole("Korn", "Probably the best alternative band", "US", "742617000027");

      var user1 = new GMUser { UserName = "Jonathan", FullName = "Jonathan Davis" };
      var user2 = new GMUser { UserName = "Fieldy", FullName = "Reginald Arvizu" };
      var user3 = new GMUser { UserName = "Munky", FullName = "James Shaffer" };

      using (var repo = new GMUserRepository())
      {
        repo.Add(user1);
        repo.Add(user2);
        repo.Add(user3);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        role.Users.Add(user1);
        role.Users.Add(user2);
        role.Users.Add(user3);
        repo.Update(role);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        Assert.AreEqual(role.Users.Count, 3);
        Assert.That(role.Users.Any(r => r.UserId == user1.UserId));
        Assert.That(role.Users.Any(r => r.UserId == user2.UserId));
        Assert.That(role.Users.Any(r => r.UserId == user3.UserId));
      }
    }

    [Test]
    public void TestAddPermissionToRole()
    {
      var roleid = CreateGMRole("Editors", "Editor staff", null, null);

      var perm1 = new GMPermission { PermissionName = "CanWrite", Description = "Can write articles" };
      var perm2 = new GMPermission { PermissionName = "CanEdit", Description = "Can edit and remove content" };

      using (var repo = new GMPermissionRepository())
      {
        repo.Add(perm1);
        repo.Add(perm2);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        role.Permissions.Add(perm1);
        role.Permissions.Add(perm2);
        repo.Update(role);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        Assert.AreEqual(role.Permissions.Count, 2);
        Assert.That(role.Permissions.Any(r => r.PermissionId == perm1.PermissionId));
        Assert.That(role.Permissions.Any(r => r.PermissionId == perm2.PermissionId));
      }
    }

    [Test]
    public void TestGetByRoleName()
    {
      int roleid = CreateGMRole("Street sweeper", "They making our world better", null, null);

      using (var repo = new GMRoleRepository())
      {
        var role1 = repo.GetByRoleName("Policeman");
        Assert.IsNull(role1);

        var role2 = repo.GetByRoleName("Street sweeper");
        Assert.IsNotNull(role2);
        Assert.AreEqual(roleid, role2.RoleId);
      }
    }

    [Test]
    public void TestAddPermission()
    {
      int roleid = CreateGMRole();
      var perm = new GMPermission {PermissionName = "CanDoSmth"};
      using (var repo = new GMPermissionRepository())
      {
        repo.Add(perm);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        bool result = repo.AddPermission(role, perm.PermissionId);
        Assert.That(result);

        result = repo.AddPermission(role, -1);
        Assert.That(!result);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        Assert.That(role.Permissions.Any(p => p.PermissionId == perm.PermissionId));
      }
    }

    [Test]
    public void TestRemovePermission()
    {
      int roleid = CreateGMRole();
      GMRole role;

      var perm = new GMPermission {PermissionName = "CanDoSmth"};
      using (var repo = new GMPermissionRepository())
      {
        repo.Add(perm);
      }

      using (var repo = new GMRoleRepository())
      {
        role = repo.GetById(roleid);
        bool result = repo.AddPermission(role, perm.PermissionId);
        Assert.That(result);
      }

      using (var repo = new GMRoleRepository())
      {
        bool result = repo.RemovePermission(role, perm.PermissionId);
        Assert.That(result);

        result = repo.RemovePermission(role, -1);
        Assert.That(result);
      }

      using (var repo = new GMRoleRepository())
      {
        var role2 = repo.GetById(roleid);
        Assert.That(!role2.Permissions.Any(p => p.PermissionId == perm.PermissionId));
      }
    }

    [Test]
    public void TestAddUser()
    {
      int roleid = CreateGMRole();
      var user = new GMUser { UserName = "Someone"};
      using (var repo = new GMUserRepository())
      {
        repo.Add(user);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        bool result = repo.AddUser(role, user.UserId);
        Assert.That(result);

        result = repo.AddUser(role, -1);
        Assert.That(!result);
      }

      using (var repo = new GMRoleRepository())
      {
        var role = repo.GetById(roleid);
        Assert.That(role.Users.Any(p => p.UserId == user.UserId));
      }
    }

    [Test]
    public void TestRemoveUser()
    {
      int roleid = CreateGMRole();
      GMRole role;

      var user = new GMUser { UserName = "Someone" };
      using (var repo = new GMUserRepository())
      {
        repo.Add(user);
      }

      using (var repo = new GMRoleRepository())
      {
        role = repo.GetById(roleid);
        bool result = repo.AddUser(role, user.UserId);
        Assert.That(result);
      }

      using (var repo = new GMRoleRepository())
      {
        bool result = repo.RemoveUser(role, user.UserId);
        Assert.That(result);

        result = repo.RemoveUser(role, -1);
        Assert.That(result);
      }

      using (var repo = new GMRoleRepository())
      {
        var role2 = repo.GetById(roleid);
        Assert.That(!role2.Users.Any(p => p.UserId == user.UserId));
      }
    }


  }
}