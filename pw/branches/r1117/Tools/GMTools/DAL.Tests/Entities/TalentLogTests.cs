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
  public class TalentLogTests
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
      NHibernateHelper.SessionFactory.Evict(typeof(Talent));
      NHibernateHelper.SessionFactory.Evict(typeof(Character));
      NHibernateHelper.SessionFactory.Evict(typeof(TalentLog));

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();
        cmd.CommandText = "truncate player cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate talent cascade";
        cmd.ExecuteNonQuery();
        cmd.CommandText = "truncate character cascade";
        cmd.ExecuteNonQuery();
      }
    }

    private static TalentLog CreateNewTalentLog()
    {
      var p = new Player {Id = 100, Nickname = "TestPlayer", Locale = "RU"};
      using (var repo = new PlayerRepository())
        repo.Add(p);
      var t = new Talent {Id = 123456, Name = "УБИТЬ ВСЕХ ЛЮДЕЙ"};
      using (var repo = new TalentRepository())
        repo.Add(t);
      var c = new Character {Id = 234567, Name = "Харатьян"};
      using (var repo = new CharacterRepository())
        repo.Add(c);
      return new TalentLog
               {
                 Operation = "testoperation",
                 Data = "testdata",
                 Player = p,
                 Talent = t,
                 TalentInstanceId = 1020304050,
                 Character = c,
                 PersistentId = 5776506343380746254,
                 Timestamp = DateTime.Today
               };
    }

    [Test]
    public void AddObjectTest()
    {
      var tl = CreateNewTalentLog();
      using (var repo = new TalentLogRepository())
        repo.Add(tl);
      using (var repo = new TalentLogRepository())
      {
        var tl2 = repo.GetById(tl.Id);
        Assert.AreNotSame(tl, tl2);
        Assert.AreEqual(tl.Operation, tl2.Operation);
        Assert.AreEqual(tl.Data, tl2.Data);
        Assert.AreEqual(tl.Player, tl2.Player);
        Assert.AreEqual(tl.Talent, tl2.Talent);
        Assert.AreEqual(tl.TalentInstanceId, tl2.TalentInstanceId);
        Assert.AreEqual(tl.Character, tl2.Character);
        Assert.AreEqual(tl.PersistentId, tl2.PersistentId);
      }
    }

    [Test]
    public void AddObjectNullableFieldsTest()
    {
      var tl = CreateNewTalentLog();
      tl.PersistentId = null;
      tl.Character = null;
      using (var repo = new TalentLogRepository())
        repo.Add(tl);
      using (var repo = new TalentLogRepository())
      {
        var tl2 = repo.GetById(tl.Id);
        Assert.AreNotSame(tl, tl2);
        Assert.AreEqual(tl.Operation, tl2.Operation);
        Assert.AreEqual(tl.Data, tl2.Data);
        Assert.AreEqual(tl.Player, tl2.Player);
        Assert.AreEqual(tl.Talent, tl2.Talent);
        Assert.AreEqual(tl.TalentInstanceId, tl2.TalentInstanceId);
        Assert.IsNull(tl2.Character);
        Assert.IsNull(tl2.PersistentId);
      }
    }

    [Test]
    public void CreateObjectTest()
    {
      var tl = CreateNewTalentLog();
      TalentLog tl2;
      using (var repo = new TalentLogRepository())
        tl2 = repo.Create(tl.Operation, tl.Data, tl.Player.Id, tl.Talent.Id, tl.TalentInstanceId, tl.Character.Id, tl.PersistentId, tl.Timestamp);

      using (var repo = new TalentLogRepository())
      {
        var tl3 = repo.GetById(tl2.Id);
        Assert.AreNotSame(tl2, tl3);
        Assert.AreEqual(tl2.Operation, tl3.Operation);
        Assert.AreEqual(tl2.Data, tl3.Data);
        Assert.AreEqual(tl2.Player, tl3.Player);
        Assert.AreEqual(tl2.Talent, tl3.Talent);
        Assert.AreEqual(tl2.TalentInstanceId, tl3.TalentInstanceId);
        Assert.AreEqual(tl2.Character, tl3.Character);
        Assert.AreEqual(tl2.PersistentId, tl3.PersistentId);
      }
    }

  }
}