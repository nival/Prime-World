using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using DAL.Entities;
using DAL.Repositories;
using log4net.Config;
using Npgsql;
using NUnit.Framework;

namespace DAL.Tests
{

  [TestFixture]
  public abstract class BaseTestFixture
  {

    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
      DatabaseHelper.Init();
    }

    protected void TruncateTables(params string[] tables)
    {
      if (tables == null || tables.Length == 0)
        return;

      using (var connection = new NpgsqlConnection(DatabaseHelper.ConnectionString))
      {
        connection.Open();
        var cmd = connection.CreateCommand();

        foreach (var table in tables)
        {
          cmd.CommandText = "truncate " + table + " cascade";
          cmd.ExecuteNonQuery();
        }
      }
    }


    protected Player CreatePlayer()
    {
      return new Player
             {
               Id = 10,
               Nickname = "TestPlayer",
               Faction = Faction.Dokt,
               Nival = true,
               Sex = 1,
               Reliability = 200,
               Locale = "ru"
             };
    }

    protected AfterParty CreateAfterParty()
    {
      return new AfterParty
             {
               PersistentId = 123456,
               MMStarted = true,
               Timestamp = DateTime.Today
             };
    }

    protected AfterPartyMember CreateAfterPartyMember()
    {
      var a = CreateAfterParty();
      using (var repo = new Repository<AfterParty>())
        repo.Add(a);

      var p = CreatePlayer();
      using (var repo = new PlayerRepository())
        repo.Add(ref p);

      return new AfterPartyMember
             {
               PersistentId = 1234567,
               AfterParty = a,
               Player = p,
               Kicked = true,
               Leaved = false,
               Timestamp = DateTime.Today
             };
    }

    protected LeaverPointsLog CreateLeaverPointsLog()
    {
      var p = CreatePlayer();
      using (var repo = new PlayerRepository())
        repo.Add(ref p);

      return new LeaverPointsLog
             {
               Player = p,
               PersistentId = 1234567,
               Type = "LeaverPointsLog_type",
               LeaverPointsChange = 12,
               LeaverPointsTotal = 13,
               IsLeaverChanged = true,
               IsLeaver = false,
               IsBadBehaviour = true,
               Timestamp = DateTime.Today
             };
    }

    protected ReRollShopLog CreatReRollShopLog()
    {
        var p = CreatePlayer();
        using (var repo = new PlayerRepository())
            repo.Add(ref p);

        return new ReRollShopLog
        {
            Player = p,
            Timestamp = DateTime.Today,
            ItemId =1,
            ItemGroup = 1,
            ItemPrice = 1,
            ItemPriceType = "Resource1",
            RerollCount  = 1,
            SlotType ="SkinRerollSlot",
            

        };
    }


    [SetUp]
    public abstract void Setup();

  }

}