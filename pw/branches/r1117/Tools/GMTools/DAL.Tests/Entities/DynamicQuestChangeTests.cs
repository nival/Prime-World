using System;
using System.IO;
using DAL.Entities;
using DAL.Repositories;
using NUnit.Framework;
using Npgsql;
using log4net.Config;

namespace DAL.Tests.Entities
{

  [TestFixture]
  public class DynamicQuestChangeTests
  {

    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
      DatabaseHelper.Init();
    }


    [SetUp]
    public void SetUp()
    {
      NHibernateHelper.SessionFactory.Evict(typeof(Player));
      NHibernateHelper.SessionFactory.Evict(typeof(QuestChange));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
      }
    }


    private static DynamicQuestChange CreateNewDynamicQuestChange()
    {
      var p = new Player { Id = 100, Nickname = "TestPlayer", Locale = "RU" };
      using (var repo = new PlayerRepository())
        repo.Add(p);

      return new DynamicQuestChange
      {
        Player = p,
        QuestIndex = 803,
        QuestName = "test dquest",
        ChangeType = QuestChangeType.Accept,
        Timestamp = DateTime.Today
      };
    }


    [Test]
    public void AddObjectTest()
    {
      var q = CreateNewDynamicQuestChange();
      using (var repo = new Repository<DynamicQuestChange>())
        repo.Add(q);

      using (var repo = new Repository<DynamicQuestChange>())
      {
        var q2 = repo.GetById(q.Id);
        Assert.IsNotNull(q2);
        Assert.AreNotSame(q, q2);
        Assert.AreEqual(q, q2);
      }
    }

  }
}