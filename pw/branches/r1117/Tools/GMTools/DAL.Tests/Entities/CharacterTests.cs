using System.IO;
using DAL.Entities;
using DAL.Repositories;
using log4net.Config;
using Npgsql;
using NUnit.Framework;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class CharacterTests
  {
    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
      DatabaseHelper.Init();
    }

    [SetUp]
    public void Setup()
    {
      NHibernateHelper.SessionFactory.Evict(typeof(Character));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate character cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static Character CreateNewCharacter()
    {
      return new Character
               {
                 Id = 100500,
                 Name = "TestCharacter",
                 DBID = "/d/b/i/d.xml",
                 Description = "Test description",
                 Gender = 0,
                 Deleted = false
               };
    }

    [Test]
    public void AddCharacterTest()
    {
      var c = CreateNewCharacter();
      using (var repo = new CharacterRepository())
      {
        repo.Add(c);
      }

      using (var repo = new CharacterRepository())
      {
        var c2 = repo.GetById(c.Id);
        Assert.AreNotSame(c, c2);
        Assert.AreEqual(c, c2);
      }
    }

    [Test]
    public void UpdateCharacterTest()
    {
      var c = CreateNewCharacter();
      using (var repo = new CharacterRepository())
      {
        repo.Add(c);
      }

      Character c2;
      using (var repo = new CharacterRepository())
      {
        c2 = repo.GetById(c.Id);
        c2.Name = "NewTestCharacter";
        c2.DBID = "new/d/b/i/d.xml";
        c2.Description = "New test description";
        c2.Gender = 1;
        repo.Update(c2);
      }

      using (var repo = new CharacterRepository())
      {
        var c3 = repo.GetById(c2.Id);
        Assert.AreNotSame(c2, c3);
        Assert.AreEqual(c2, c3);
      }
    }

    [Test]
    public void RemovePlayerTest()
    {
      var c = CreateNewCharacter();
      using (var repo = new CharacterRepository())
      {
        repo.Add(c);
      }

      using (var repo = new CharacterRepository())
      {
        var c2 = repo.GetById(c.Id);
        repo.Remove(c2);
      }

      using (var repo = new CharacterRepository())
      {
        var c3 = repo.GetById(c.Id);
        Assert.IsNull(c3);
      }
    }
  }
}