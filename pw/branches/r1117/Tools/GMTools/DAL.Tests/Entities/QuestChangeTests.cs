using System;
using System.IO;
using DAL.Entities;
using DAL.Repositories;
using log4net.Config;
using Npgsql;
using NUnit.Framework;

namespace DAL.Tests.Entities
{
  [TestFixture]
  public class QuestChangeTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(Player));
      NHibernateHelper.SessionFactory.Evict(typeof(Quest));
      NHibernateHelper.SessionFactory.Evict(typeof(QuestChange));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate quest cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static QuestChange CreateNewQuestChange()
    {
      var p = new Player { Id = 100, Nickname = "TestPlayer", Locale = "RU" };
      using (var repo = new PlayerRepository())
        repo.Add(p);
      var q = new Quest {Id = 100600, QuestId = "q_01", Name = "Убить всех людей"};
      using (var repo = new Repository<Quest>())
        repo.Add(q);
      return new QuestChange
               {
                 Player = p,
                 Quest = q,
                 ChangeType = QuestChangeType.Complete,
                 Timestamp = DateTime.Today
               };
    }

    [Test]
    public void AddObjectTest()
    {
      var qc = CreateNewQuestChange();
      using (var repo = new Repository<QuestChange>())
        repo.Add(qc);
      using (var repo = new Repository<QuestChange>())
      {
        var qc2 = repo.GetById(qc.Id);
        Assert.AreNotSame(qc, qc2);
        Assert.AreEqual(qc, qc2);
      }
    }
  }
}