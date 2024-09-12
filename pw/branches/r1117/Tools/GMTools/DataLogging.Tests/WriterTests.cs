using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using Npgsql;
using NUnit.Framework;

namespace DataLogging.Tests
{
/*

  [TestFixture]
  public class WriterTests
  {
    private NpgsqlConnection connection;
    
    [TestFixtureSetUp]
    public void OpenConnection()
    {
      const string cstr = "Server=localhost;Port=5432;Database=test_logs;User Id=postgres;Password=password;";
      connection = new NpgsqlConnection(cstr);
      connection.Open();

      var contex = new DataLoggingContext(cstr);
      if (!Writer.Init(contex))
        Assert.Fail("Failed to init DataLogging");
    }

    [TestFixtureTearDown]
    public void CloseConnection()
    {
      connection.Close();
    }

    [Test]
    public void WriteKillLoadTest()
    {
      var sw = new Stopwatch();
      sw.Start();
      
      for (int i = 1; i <= 100; i++)
        Writer.WriteKill(i, i, 0f, 1f, "cain", "abel", 6);

      sw.Stop();
      Debug.WriteLine(String.Format("Time elapsed: {0} ms", sw.ElapsedMilliseconds));
    }

    //[Test]
    public void WriteKillMultithreadLoadTest()
    {
      var start = DateTime.Now;

      Thread[] threads = new Thread[10]; 
      for (int t = 0; t < 10; t++)
      {
        threads[t] = new Thread(() => { for (int i = 1; i <= 1000; i++) Writer.WriteKill(i, i, 0f, 1f, "cain", "abel", 6); });
        threads[t].Start();
      }
      foreach (var thread in threads)
      {
        thread.Join();
      }

      var finish = DateTime.Now;
      Debug.WriteLine(String.Format("Time elapsed {0}", finish - start));
    }

    [Test]
    public void WriteAssistTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table assist";
      cmd.ExecuteNonQuery();

      Writer.WriteAssist(1, 100, 3.8576f, 5f, "ganker", "idiot", "killer", 666);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",victimlogin,killerlogin,killercreatureid from assist where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "ganker");
      Assert.AreEqual(reader[6], "idiot");
      Assert.AreEqual(reader[7], "killer");
      Assert.AreEqual(reader[8], 666);
      reader.Close();
    }

    [Test]
    public void WriteBuildingDestroyedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table buildingdestroyed";
      cmd.ExecuteNonQuery();

      Writer.WriteBuildingDestroyed(1, 100, 3.8576f, 5f, "observer", 18965487, "destroyer", 1);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",buildingid,destroyerlogin,destroyercreatureid FROM buildingdestroyed where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "observer");
      Assert.AreEqual(reader[6], 18965487);
      Assert.AreEqual(reader[7], "destroyer");
      Assert.AreEqual(reader[8], 1);
      reader.Close();
    }

    [Test]
    public void WriteConsumableBoughtTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table consumablebought";
      cmd.ExecuteNonQuery();

      Writer.WriteConsumableBought(1, 100, 3.8576f, 5f, "consumer", 100, 100500);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",consumableid,nafta FROM consumablebought where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "consumer");
      Assert.AreEqual(reader[6], 100);
      Assert.AreEqual(reader[7], 100500);
      reader.Close();
    }

    [Test]
    public void WriteConsumableUsedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table consumableused";
      cmd.ExecuteNonQuery();

      Writer.WriteConsumableUsed(1, 100, 3.8576f, 5f, "user", 100);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",consumableid FROM consumableused where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "user");
      Assert.AreEqual(reader[6], 100);
      reader.Close();
    }

    [Test]
    public void WriteCheatUsedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table cheatused";
      cmd.ExecuteNonQuery();

      Writer.WriteCheatUsed(1, 123, 45.6f, 78.9f, "fucking_cheater", "kill_self");
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",command FROM cheatused where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 123);
      Assert.AreEqual(reader[3], 45.6f);
      Assert.AreEqual(reader[4], 78.9f);
      Assert.AreEqual(reader[5], "fucking_cheater");
      Assert.AreEqual(reader[6], "kill_self");
      reader.Close();
    }

    [Test]
    public void WriteDeathTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table death";
      cmd.ExecuteNonQuery();

      Writer.WriteDeath(1, 100, 3.8576f, 5f, "innocent victim", "maniac", 0);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",killerlogin,killercreatureid FROM death where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "innocent victim");
      Assert.AreEqual(reader[6], "maniac");
      Assert.AreEqual(reader[7], DBNull.Value);
      reader.Close();
    }

    [Test]
    public void WriteAchievementTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table achievement";
      cmd.ExecuteNonQuery();

      Writer.WriteAchievement(1, 100, 3.8576f, 5f, "hero", 9);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",achievementid FROM achievement where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "hero");
      Assert.AreEqual(reader[6], 9);
      reader.Close();
    }

    [Test]
    public void WriteFlagTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table flag";
      cmd.ExecuteNonQuery();

      Writer.WriteFlag(1, 100, 3.8576f, 5f, "login", true, 1, 2, 3, "champion", 0);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",raised,faction,road,segment,activatorlogin,activatorcreatureid FROM flag where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      Assert.AreEqual(reader[6], true);
      Assert.AreEqual(reader[7], 1);
      Assert.AreEqual(reader[8], 2);
      Assert.AreEqual(reader[9], 3);
      Assert.AreEqual(reader[10], "champion");
      Assert.AreEqual(reader[11], DBNull.Value);
      reader.Close();
    }

    [Test]
    public void WriteImpulsiveBuffUsedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table impulsivebuffused";
      cmd.ExecuteNonQuery();

      Writer.WriteImpulsiveBuffUsed(1, 100, 3.8576f, 5f, "login", 6);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",impulsivebuffid FROM impulsivebuffused where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      Assert.AreEqual(reader[6], 6);
      reader.Close();
    }

    [Test]
    public void WriteImpulsiveBuffSuggestedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table impulsivebuffsuggested";
      cmd.ExecuteNonQuery();

      Writer.WriteImpulsiveBuffSuggested(1, 100, 8.4740f, 11f, "login", 6);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",impulsivebuffid FROM impulsivebuffsuggested where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 8.4740f);
      Assert.AreEqual(reader[4], 11f);
      Assert.AreEqual(reader[5], "login");
      Assert.AreEqual(reader[6], 6);
      reader.Close();
    }

    [Test]
    public void WriteKillTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table kill";
      cmd.ExecuteNonQuery();

      Writer.WriteKill(1, 100, 3.8576f, 5f, "cain", "abel", 6);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",victimlogin,victimcreatureid from kill where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "cain");
      Assert.AreEqual(reader[6], "abel");
      Assert.AreEqual(reader[7], 6);
      reader.Close();

      Writer.WriteKill(2, 100, 1f, 2f, "cain", null, 0);
      cmd.CommandText = "select victimlogin,victimcreatureid from kill where sessionid=2";
      reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[0], DBNull.Value);
      Assert.AreEqual(reader[1], DBNull.Value);
      reader.Close();
    }

    [Test]
    public void WriteLevelUpTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table levelup";
      cmd.ExecuteNonQuery();

      Writer.WriteLevelUp(1, 100, 3.8576f, 5f, "login", 12);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",level FROM levelup where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      Assert.AreEqual(reader[6], 12);
      reader.Close();
    }

    [Test]
    public void WriteNaftaIncomeTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table naftaincome";
      cmd.ExecuteNonQuery();

      Writer.WriteNaftaIncome(1, 103, 31337f, 4f, "login", 2, 100, 120, 140, 0);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",incomefrom,naftaForKill,naftaSpecForKill,teamNaftaForKill,nafta FROM naftaincome where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 103);
      Assert.AreEqual(reader[3], 31337f);
      Assert.AreEqual(reader[4], 4f);
      Assert.AreEqual(reader[5], "login");
      Assert.AreEqual(reader[6], 2);
      Assert.AreEqual(reader[7], 100);
      Assert.AreEqual(reader[8], 120);
      Assert.AreEqual(reader[9], 140);
      Assert.AreEqual(reader[10], 0);
      reader.Close();
    }

    [Test]
    public void WriteRessurectionTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table ressurection";
      cmd.ExecuteNonQuery();

      Writer.WriteRessurection(1, 100, 3.8576f, 5f, "login");
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\" FROM ressurection where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      reader.Close();
    }

    [Test]
    public void WriteTalentUnlockedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table talentunlocked";
      cmd.ExecuteNonQuery();

      Writer.WriteTalentUnlocked(1, 100, 3.8576f, 5f, "consumer", 100, 100600);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",talentid,nafta FROM talentunlocked where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "consumer");
      Assert.AreEqual(reader[6], 100);
      Assert.AreEqual(reader[7], 100600);
      reader.Close();
    }

    [Test]
    public void WriteTalentUsedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table talentused";
      cmd.ExecuteNonQuery();

      Writer.WriteTalentUsed(1, 100, 3.8576f, 5f, "consumer", 102);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",talentid FROM talentused where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "consumer");
      Assert.AreEqual(reader[6], 102);
      reader.Close();
    }

    [Test]
    public void WriteTalentSwitchedOffTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table talentswitchedoff";
      cmd.ExecuteNonQuery();

      Writer.WriteTalentSwitchedOff(1, 100, 3.8576f, 5f, "consumer", 102);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",talentid FROM talentswitchedoff where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "consumer");
      Assert.AreEqual(reader[6], 102);
      reader.Close();
    }

    [Test]
    public void WriteTimeSliceTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table timeslice";
      cmd.ExecuteNonQuery();

      Writer.WriteTimeSlice(1, 100, 3.8576f, 5f, "consumer", 1001, 1002, 1003, 1004);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",slice,level,currentnafta,totalnafta FROM timeslice where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 100);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "consumer");
      Assert.AreEqual(reader[6], 1001);
      Assert.AreEqual(reader[7], 1002);
      Assert.AreEqual(reader[8], 1003);
      Assert.AreEqual(reader[9], 1004);
      reader.Close();
    }

    [Test]
    public void WriteMG2StartedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table mg2started";
      cmd.ExecuteNonQuery();

      Writer.WriteMG2Started(1, 500, 3.8576f, 5f, "login");
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\" FROM mg2started where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 500);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      reader.Close();
    }

    [Test]
    public void WriteMG2ExitTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table mg2exit";
      cmd.ExecuteNonQuery();

      Writer.WriteMG2Exit(1, 500, 3.8576f, 5f, "login");
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\" FROM mg2exit where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 500);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      reader.Close();
    }

    [Test]
    public void WriteMG2LevelStartedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table mg2levelstarted";
      cmd.ExecuteNonQuery();

      Writer.WriteMG2LevelStarted(1, 500, 3.8576f, 5f, "login", 6, 2);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",level,paint FROM mg2levelstarted where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 500);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      Assert.AreEqual(reader[6], 6);
      Assert.AreEqual(reader[7], 2);
      reader.Close();
    }

    [Test]
    public void WriteMG2LevelWonTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table mg2levelwon";
      cmd.ExecuteNonQuery();

      Writer.WriteMG2LevelWon(1, 500, 3.8576f, 5f, "login", 6, 2);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",level,paint FROM mg2levelwon where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 500);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      Assert.AreEqual(reader[6], 6);
      Assert.AreEqual(reader[7], 2);
      reader.Close();
    }

    [Test]
    public void WriteMG2LevelFailedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table mg2levelfailed";
      cmd.ExecuteNonQuery();

      Writer.WriteMG2LevelFailed(1, 500, 3.8576f, 5f, "login", 6, 2);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",level,paint FROM mg2levelfailed where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 500);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      Assert.AreEqual(reader[6], 6);
      Assert.AreEqual(reader[7], 2);
      reader.Close();
    }

    [Test]
    public void WriteMG2BallsChangedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table mg2ballschanged";
      cmd.ExecuteNonQuery();

      Writer.WriteMG2BallsChanged(1, 500, 3.8576f, 5f, "login");
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\" FROM mg2ballschanged where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 500);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      reader.Close();
    }

    [Test]
    public void WriteMG2BoostUsedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table mg2boostused";
      cmd.ExecuteNonQuery();

      Writer.WriteMG2BoostUsed(1, 500, 3.8576f, 5f, "login", 42);
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",boostid FROM mg2boostused where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 500);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      Assert.AreEqual(reader[6], 42);
      reader.Close();
    }

    [Test]
    public void WriteMG2ZZBoostUsedTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table mg2zzboostused";
      cmd.ExecuteNonQuery();

      Writer.WriteMG2ZZBoostUsed(1, 500, 3.8576f, 5f, "login");
      cmd.CommandText = "select id,sessionid,step,x,y,\"login\" FROM mg2zzboostused where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 500);
      Assert.AreEqual(reader[3], 3.8576f);
      Assert.AreEqual(reader[4], 5f);
      Assert.AreEqual(reader[5], "login");
      reader.Close();
    }

    [Test]
    public void WriteDamageTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table damage";
      cmd.ExecuteNonQuery();

      Writer.WriteDamage(1, 500, "login", true, 123456, 3, 654321, 100f, 200f, 133.33f);
      cmd.CommandText = "select id, sessionId,step,login,dealt,opponentId,unitType,talentId,physicalDamage,magicalDamage,pureDamage FROM damage where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 500);
      Assert.AreEqual(reader[3], "login");
      Assert.AreEqual(reader[4], true);
      Assert.AreEqual(reader[5], 123456);
      Assert.AreEqual(reader[6], 3);
      Assert.AreEqual(reader[7], 654321);
      Assert.AreEqual(reader[8], 100f);
      Assert.AreEqual(reader[9], 200f);
      Assert.AreEqual(reader[10], 133.33f);
      reader.Close();
    }

    [Test]
    public void WriteDebugVarTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table debugvar";
      cmd.ExecuteNonQuery();

      var now = DateTime.Now;
      var now2 = new DateTime(now.Year, now.Month, now.Day, now.Hour, now.Minute, now.Second);
      Writer.WriteDebugVar(1, 600, now2, "olologin", "fps", "9.4");
      cmd.CommandText = "select id, sessionId,step,eventtime,login,name,value FROM debugvar where sessionid=1";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 1);
      Assert.AreEqual(reader[2], 600);
      Assert.AreEqual(reader[3], now2);
      Assert.AreEqual(reader[4], "olologin");
      Assert.AreEqual(reader[5], "fps");
      Assert.AreEqual(reader[6], "9.4");
      reader.Close();
    }

    [Test]
    public void DBVersionTest()
    {
      Debug.Write(Writer.DBVersion);
    }

    [Test]
    public void CopyTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table kill";
      cmd.ExecuteNonQuery();

      var values = new Dictionary<string, object>
                     {
                       {"sessionid", 111},
                       {"step", 222},
                       {"x", 33.3f},
                       {"y", 44.4f},
                       {"login", "Slayer"},
                       {"victimlogin", null},
                       {"victimcreatureid", 666}
                     };

      var sw = new Stopwatch();
      sw.Start();

      Writer.CopyInTable(values);

      sw.Stop();
      Debug.WriteLine(String.Format("Time elapsed: {0} ms", sw.ElapsedMilliseconds));

      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",victimlogin,victimcreatureid from kill where sessionid=111";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 111);
      Assert.AreEqual(reader[2], 222);
      Assert.AreEqual(reader[3], 33.3f);
      Assert.AreEqual(reader[4], 44.4f);
      Assert.AreEqual(reader[5], "Slayer");
      Assert.AreEqual(reader[6], DBNull.Value);
      Assert.AreEqual(reader[7], 666);
      reader.Close();
    }

    [Test]
    public void CopyMultithreadTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table kill";
      cmd.ExecuteNonQuery();

      var values1 = new Dictionary<string, object>
                      {
                        {"sessionid", 111},
                        {"step", 222},
                        {"x", 33.3f},
                        {"y", 44.4f},
                        {"login", "Slayer"},
                        {"victimlogin", null},
                        {"victimcreatureid", 666}
                      };
      var values2 = new Dictionary<string, object>
                      {
                        {"sessionid", 101},
                        {"step", 202},
                        {"x", 30.3f},
                        {"y", 40.4f},
                        {"login", "Killer"},
                        {"victimlogin", "Victim"},
                        {"victimcreatureid", 606}
                      };

      var t1 = new Thread(() => Writer.CopyInTable(values1));
      var t2 = new Thread(() => Writer.CopyInTable(values2));

      var sw = new Stopwatch();
      sw.Start();

      t1.Start();
      t2.Start();

      t1.Join();
      t2.Join();

      sw.Stop();
      Debug.WriteLine(String.Format("Time elapsed: {0} ms", sw.ElapsedMilliseconds));

      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",victimlogin,victimcreatureid from kill where sessionid=111";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 111);
      Assert.AreEqual(reader[2], 222);
      Assert.AreEqual(reader[3], 33.3f);
      Assert.AreEqual(reader[4], 44.4f);
      Assert.AreEqual(reader[5], "Slayer");
      Assert.AreEqual(reader[6], DBNull.Value);
      Assert.AreEqual(reader[7], 666);
      reader.Close();
    }

    [Test]
    public void InsertTest()
    {
      var cmd = connection.CreateCommand();
      cmd.CommandText = "truncate table kill";
      cmd.ExecuteNonQuery();

      var values = new Dictionary<string, object>
                     {
                       {"sessionid", 111},
                       {"step", 222},
                       {"x", 33.3f},
                       {"y", 44.4f},
                       {"login", "Slayer"},
                       {"victimlogin", null},
                       {"victimcreatureid", 666}
                     };

      var sw = new Stopwatch();
      sw.Start();

      Writer.InsertInTable(values);

      sw.Stop();
      Debug.WriteLine(String.Format("Time elapsed: {0} ms", sw.ElapsedMilliseconds));

      cmd.CommandText = "select id,sessionid,step,x,y,\"login\",victimlogin,victimcreatureid from kill where sessionid=111";
      var reader = cmd.ExecuteReader();
      Assert.That(reader.HasRows);
      reader.Read();
      Assert.AreEqual(reader[1], 111);
      Assert.AreEqual(reader[2], 222);
      Assert.AreEqual(reader[3], 33.3f);
      Assert.AreEqual(reader[4], 44.4f);
      Assert.AreEqual(reader[5], "Slayer");
      Assert.AreEqual(reader[6], DBNull.Value);
      Assert.AreEqual(reader[7], 666);
      reader.Close();
    }

  }
*/

}