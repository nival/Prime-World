using System.Linq;
using AdminLib.Entities;
using AdminLib.Repositories;
using AdminLib.Tests.Properties;
using NHibernate;
using NUnit.Framework;

namespace AdminLib.Tests
{
  [TestFixture]
  public class GMPermissionTests
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
        s.Delete("from GMPermission");
        s.Delete("from GMRole");
        s.Flush();
      }
    }

    public int CreateGMPermission()
    {
      return CreateGMPermission("Permission name", "Few words about this permission");
    }

    public int CreateGMPermission(string permissionName, string description)
    {
      using (var repo = new GMPermissionRepository())
      {
        var p = new GMPermission
        {
          PermissionName = permissionName,
          Description = description
        };
        repo.Add(p);

        return p.PermissionId;
      }
    }


    [Test]
    public void TestOpenSession()
    {
      ISession actual = NHibernateHelper.OpenSession();
      Assert.IsNotNull(actual);
    }
    
    [Test]
    public void TestAddNewPermission()
    {
      int permid;
      string permissionName = "permission 1";
      string description = "description 1";

      using (var repo = new GMPermissionRepository())
      {
        var perm = new GMPermission
        {
          PermissionName = permissionName,
          Description = description
        };
        repo.Add(perm);
        permid = perm.PermissionId;
      }

      using (var repo = new GMPermissionRepository())
      {
        var perm = repo.GetById(permid);
        Assert.AreEqual(perm.PermissionName, permissionName);
        Assert.AreEqual(perm.Description, description);
      }
    }


    [Test]
    public void TestUpdatePermission()
    {
      string newpermissionName = "Cool new permission";
      string newdescription = "Now you can walking on water";

      var permid = CreateGMPermission();

      using (var repo = new GMPermissionRepository())
      {
        var perm = repo.GetById(permid);
        Assert.IsNotNull(perm);
        Assert.AreNotEqual(perm.PermissionName, newpermissionName);
        Assert.AreNotEqual(perm.Description, newdescription);
        perm.PermissionName = newpermissionName;
        perm.Description = newdescription;
        repo.Update(perm);
      }

      using (var repo = new GMPermissionRepository())
      {
        var perm = repo.GetById(permid);
        Assert.AreEqual(perm.PermissionName, newpermissionName);
        Assert.AreEqual(perm.Description, newdescription);
      }
    }

    [Test]
    public void TestRemovePermission()
    {
      var permid = CreateGMPermission();

      using (var repo = new GMPermissionRepository())
      {
        var permission = repo.GetById(permid);
        Assert.IsNotNull(permission);
        repo.Remove(permission);
      }

      using (var repo = new GMPermissionRepository())
      {
        var perm = repo.GetById(permid);
        Assert.IsNull(perm);
      }
    }

    [Test]
    public void TestGetAllPermissions()
    {
      var permid1 = CreateGMPermission("Perm 1", "Description 1");
      var permid2 = CreateGMPermission("Perm 2", "Description 2");
      var permid3 = CreateGMPermission("Perm 3", "Description 3");

      using (var repo = new GMPermissionRepository())
      {
        var permissions = repo.GetAll();
        Assert.AreEqual(permissions.Count(), 3);
        Assert.That(permissions.Any(p => p.PermissionId == permid1));
        Assert.That(permissions.Any(p => p.PermissionId == permid2));
        Assert.That(permissions.Any(p => p.PermissionId == permid3));
      }
    }

    [Test]
    public void TestFillPermissions()
    {
      int perm1_id = CreateGMPermission("Permission1", null);
      CreateGMPermission("Permission2", null);

      string[] permissions = new[] {"Permission1", "Permission3"};

      using (var repo = new GMPermissionRepository())
      {
        repo.FillPermissions(permissions);
      }

      using (var repo = new GMPermissionRepository())
      {
        var gmpermissions = repo.GetAll();
        Assert.That(gmpermissions.Any(p => p.PermissionName == "Permission1" && p.PermissionId == perm1_id));
        Assert.That(!gmpermissions.Any(p => p.PermissionName == "Permission2"));
        Assert.That(gmpermissions.Any(p => p.PermissionName == "Permission3"));
      }
    }
  }
}
