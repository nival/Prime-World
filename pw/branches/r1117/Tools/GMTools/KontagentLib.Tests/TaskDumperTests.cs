using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using log4net.Config;
using NUnit.Framework;

namespace KontagentLib.Tests
{
  [TestFixture]
  public class TaskDumperTests
  {
    [TestFixtureSetUp]
    public void FixtureSetup()
    {
      XmlConfigurator.Configure(new FileInfo("log4net.config"));
    }

    private const string FILENAME = "test.dump";

    [SetUp]
    public void TestSetup()
    {
      foreach (var file in  Directory.GetFiles(Environment.CurrentDirectory, FILENAME + "*"))
        File.Delete(file);
    }

    [Test]
    public void DumpRestoreTest()
    {
      var tasks = new List<IKontagentTask>
                    {
                      new CastleLoginTask {Auid = 1234, Faction = 1},
                      new FactionSelectedTask {Auid = 2345, Faction = 1},
                      new SessionStartTask {Auid = 3456, Faction = 0, SessionType = 4, HeroId = 100500},
                      new ResourceChangeTask
                        {
                          Auid = 1488,
                          Source = "reich",
                          Gain = true,
                          GoldChange = 1,
                          SilverChange = 2,
                          PerlChange = 3,
                          RedPerlChange = 4,
                          Resource1Change = 5,
                          Resource2Change = 6,
                          Resource3Change = 7,
                          ShardChange = 8
                        }
                    };
      var dumper = new TaskFileDumper(FILENAME);
      dumper.Dump(tasks);

      Assert.That(File.Exists(FILENAME));
      Assert.That(dumper.HasDumpedTasks);

      var tasks2 = dumper.Restore(1);
      Assert.IsNotNull(tasks2);
      Assert.AreEqual(1, tasks2.Count());

      Assert.That(File.Exists(FILENAME));
      Assert.That(dumper.HasDumpedTasks);

      var tasks3 = dumper.Restore(100);
      Assert.IsNotNull(tasks3);
      Assert.AreEqual(3, tasks3.Count());

      Assert.That(!File.Exists(FILENAME));
      Assert.That(!dumper.HasDumpedTasks);
    }

    [Test]
    public void CastleLoginTaskSerializationTest()
    {
      var dumper = new TaskFileDumper(FILENAME);
      var task = new CastleLoginTask {Auid = 1234, Faction = 1};

      var serialized = dumper.SerializeTask(task);
      Console.WriteLine("serialized value = " + serialized);
      var task2 = dumper.DeserializeTask(serialized) as CastleLoginTask;

      Assert.IsNotNull(task2);
      Assert.AreEqual(task2.Auid, task.Auid);
      Assert.AreEqual(task2.Faction, task.Faction);
    }

    [Test]
    public void FactionSelectedTaskSerializationTest()
    {
      var dumper = new TaskFileDumper(FILENAME);
      var task = new FactionSelectedTask {Auid = 2345, Faction = 1};

      var serialized = dumper.SerializeTask(task);
      Console.WriteLine("serialized value = " + serialized);
      var task2 = dumper.DeserializeTask(serialized) as FactionSelectedTask;

      Assert.IsNotNull(task2);
      Assert.AreEqual(task2.Auid, task.Auid);
      Assert.AreEqual(task2.Faction, task.Faction);
    }

    [Test]
    public void SessionStartTaskSerializationTest()
    {
      var dumper = new TaskFileDumper(FILENAME);
      var task = new SessionStartTask {Auid = 3456, Faction = 0, SessionType = 4, HeroId = 100500};

      var serialized = dumper.SerializeTask(task);
      Console.WriteLine("serialized value = " + serialized);
      var task2 = dumper.DeserializeTask(serialized) as SessionStartTask;

      Assert.IsNotNull(task2);
      Assert.AreEqual(task2.Auid, task.Auid);
      Assert.AreEqual(task2.Faction, task.Faction);
      Assert.AreEqual(task2.SessionType, task.SessionType);
      Assert.AreEqual(task2.HeroId, task.HeroId);
      if (String.IsNullOrEmpty(task2.HeroName))
        Assert.IsTrue(String.IsNullOrEmpty(task.HeroName));
      else
        Assert.AreEqual(task2.HeroName, task.HeroName);
    }

    [Test]
    public void ResourceChangeTaskSerializationTest()
    {
      var dumper = new TaskFileDumper(FILENAME);
      var task = new ResourceChangeTask
                   {
                     Auid = 1488,
                     Source = "reich",
                     Gain = true,
                     GoldChange = 1,
                     SilverChange = 2,
                     PerlChange = 3,
                     RedPerlChange = 4,
                     Resource1Change = 5,
                     Resource2Change = 6,
                     Resource3Change = 7,
                     ShardChange = 8
                   };

      var serialized = dumper.SerializeTask(task);
      Console.WriteLine("serialized value = " + serialized);
      var task2 = dumper.DeserializeTask(serialized) as ResourceChangeTask;

      Assert.IsNotNull(task2);
      Assert.AreEqual(task2.Auid, task.Auid);
      Assert.AreEqual(task2.Source, task.Source);
      Assert.AreEqual(task2.Gain, task.Gain);
      Assert.AreEqual(task2.GoldChange, task.GoldChange);
      Assert.AreEqual(task2.SilverChange, task.SilverChange);
      Assert.AreEqual(task2.PerlChange, task.PerlChange);
      Assert.AreEqual(task2.RedPerlChange, task.RedPerlChange);
      Assert.AreEqual(task2.Resource1Change, task.Resource1Change);
      Assert.AreEqual(task2.Resource2Change, task.Resource2Change);
      Assert.AreEqual(task2.Resource3Change, task.Resource3Change);
      Assert.AreEqual(task2.ShardChange, task.ShardChange);
    }

    [Test]
    public void UnaccessibleFileTest()
    {
      var dumper = new TaskFileDumper(FILENAME);
      var task1 = new CastleLoginTask { Auid = 1001, Faction = 1 };
      var task2 = new CastleLoginTask { Auid = 1002, Faction = 1 };

      dumper.Dump(new[] {task1});

      using (var reader = new StreamReader(FILENAME))
      {
        string content = reader.ReadToEnd();
        Assert.AreEqual(dumper.SerializeTask(task1) + Environment.NewLine, content);
      }

      using (File.Open(FILENAME, FileMode.Open, FileAccess.Read, FileShare.None))
      {
        dumper.Dump(new[] { task2 });
      }

      using (var reader = new StreamReader(FILENAME))
      {
        Assert.AreEqual(dumper.SerializeTask(task1) + Environment.NewLine, reader.ReadToEnd());
      }
      Assert.That(File.Exists(FILENAME+".2"));
      using (var reader = new StreamReader(FILENAME + ".2"))
      {
        Assert.AreEqual(dumper.SerializeTask(task2) + Environment.NewLine, reader.ReadToEnd());
      }
    }

    [Test]
    public void RestoringFromDifferentFilesTest()
    {
      var dumper = new TaskFileDumper(FILENAME);
      var task1 = new CastleLoginTask { Auid = 1001, Faction = 1 };
      var task2 = new CastleLoginTask { Auid = 1002, Faction = 1 };

      string file1 = String.Empty;
      using (var writer = new StreamWriter(FILENAME))
      {
        for (int i = 0; i < 3; i++)
          file1 += dumper.SerializeTask(task1) + Environment.NewLine;
        writer.Write(file1);
      }
      string file2 = String.Empty;
      using (var writer = new StreamWriter(FILENAME + ".2"))
      {
        for (int i = 0; i < 2; i++)
          file2 += dumper.SerializeTask(task2) + Environment.NewLine;
        writer.Write(file2);
      }

      dumper = new TaskFileDumper(FILENAME);
      Assert.That(dumper.HasDumpedTasks);

      var tasks = dumper.Restore(100).ToArray();
      Assert.AreEqual(3, tasks.Length);
      foreach (CastleLoginTask t in tasks)
        Assert.AreEqual(t.Auid, task1.Auid);

      Assert.That(dumper.HasDumpedTasks);

      tasks = dumper.Restore(100).ToArray();
      Assert.AreEqual(2, tasks.Length);
      foreach (CastleLoginTask t in tasks)
        Assert.AreEqual(t.Auid, task2.Auid);

      Assert.IsFalse(dumper.HasDumpedTasks);

      Assert.IsFalse(File.Exists(FILENAME));
      Assert.IsFalse(File.Exists(FILENAME + ".2"));
    }

  }
}