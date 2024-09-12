using System;
using System.Collections.Generic;
using System.Threading;
using StatisticCore.Thrift;
using Thrift.Protocol;
using Thrift.Transport;
using ThriftClient.Properties;

namespace ThriftClient
{
  class Program
  {
    private static string scenario;
    private static uint repeatcount = 3;
    private static int sleepinterval = 10;

    private static StatisticService.Client client;
    private static TTransport transport;

    static bool ParseArgs(string[] args)
    {
      if (args == null) return false;
      if (args.Length >= 1 && !String.IsNullOrEmpty(args[0]))
        scenario = args[0];
      else return false;
      if (args.Length >= 2 && !String.IsNullOrEmpty(args[1])) 
        return UInt32.TryParse(args[1], out repeatcount);
      return true;
    }

    static int Main(string[] args)
    {
      // parse parameters
      if (!ParseArgs(args))
      {
        Console.WriteLine("Wrong args");
        return 1;
      }

      // create client
      try
      {
        /*TTransport*/ transport = new THttpClient(new Uri(Settings.Default.ThriftServerUrl));
        TProtocol proto = new TBinaryProtocol(transport);
        client = new StatisticService.Client(proto);
        Console.WriteLine("Connecting to statistic server by {0} port", Settings.Default.ThriftServerUrl);
      }
      catch (Exception ex)
      {
        Console.WriteLine(ex);
        return 1;
      }

      try
      {
        switch (scenario)
        {
          case "login":
            Login();
            Thread.Sleep(3*sleepinterval);
            Logout();
            break;
          case "chat":
            Chat();
            break;
          case "hero":
            GMHero();
            break;
          case "talent":
            GMTalent();
            break;
          case "ban":
            GMBan();
            break;
          case "mute":
            GMMute();
            break;
          case "edituser":
            GMEditUser();
            break;
          case "monitoring":
            Monitoring();
            break;
          case "awards":
            Awards();
            break;
          case "launcher":
            Launcher();
            break;
          case "ignore":
            Ignore();
            break;
          case "bath":
            Bath();
            break;
          case "faction":
            FactionSelect();
            break;
          case "quest":
            QuestChange();
            break;
          case "dquest":
            DQuestChange();
            break;
          case "join":
            JoinSession();
            break;
          case "ping":
            ClientPing();
            break;
          case "rune":
            Rune();
            break;
          default:
            Console.WriteLine("Unknown scenario \"{0}\"", scenario);
            return 1;
        }
        return 0;
      }
      catch (Exception ex)
      {
        Console.WriteLine("Failed to execute \"{0}\" scenario. Exception: {1}", scenario, ex);
        return 1;
      }
    }

    private static int ConvertToUnixTimestamp(DateTime dateTime)
    {
      TimeSpan delta = dateTime - new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc).ToLocalTime();
      return Convert.ToInt32(delta.TotalSeconds);
    }

    #region SCENARIOS

    private static void Login()
    {
      var infos = new List<LoginInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new LoginInfo
        {
          Auid = 100 + i,
          Ip = "192.168.0." + i,
          Nick = "Test" + i,
          Server = "no.server",
          Cluster = "my.cluster",
          Isdeveloper = i % 2 == 0,
          Guildid = 86001,
          Guildshortname = "ILT",
          Guildfullname = "I Like Trains",
          Timestamp = ConvertToUnixTimestamp(DateTime.Now)
        };
        infos.Add(info);
        Console.WriteLine("LoginInfo[{0}] = {1}", i, info);
      }
      client.LoginUsers(infos);
      Console.WriteLine("Sent {0} logins", infos.Count);
    }

    private static void Logout()
    {
      var infos = new List<LoginInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new LoginInfo
        {
          Auid = 100 + i,
          Nick = "Test" + i,
          Server = "no.server",
          Cluster = "my.cluster",
          Timestamp = ConvertToUnixTimestamp(DateTime.Now.AddHours(1))
        };
        infos.Add(info);
        Console.WriteLine("LoginInfo[{0}] = {1}", i, info);
      }
      client.LogoutUsers(infos);
      Console.WriteLine("Sent {0} logouts", infos.Count);
    }

    private static void Chat()
    {
      var infos = new List<ChatMessageInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new ChatMessageInfo
                     {
                       Auid = 102 - i%2,
                       Timestamp = ConvertToUnixTimestamp(DateTime.Now),
                       Channel = "#утренник_в_дурдоме",
                       Message = i%2 == 1 ? "чёё?" : "все говорят \"чёё\", а ты купи слона"
                     };
        infos.Add(info);
        Console.WriteLine("ChatMessageInfo[{0}] = {1}", i, info);
      }
      client.ChatMessages(infos);
      Console.WriteLine("Sent {0} chat messages", infos.Count);
    }

    private static void GMHero()
    {
      for (int i = 1; i <= repeatcount; i++)
      {
        //client.GMUnlockHero(100 + i, "gmtest", -1139813982, ConvertToUnixTimestamp(DateTime.Now));
        Thread.Sleep(sleepinterval);
      }

      Thread.Sleep(3 * sleepinterval);

      for (int i = 1; i <= repeatcount; i++)
      {
        //client.GMLockHero(100 + i, "gmtest", 1318972637, ConvertToUnixTimestamp(DateTime.Now));
      }

      var unlocks = new List<UnlockHeroInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        unlocks.Add(new UnlockHeroInfo { Auid = 100 + i, Heroid = 1318972637, /*Silver = 100500 + i,*/ Timestamp = ConvertToUnixTimestamp(DateTime.Now) });
      }
      client.UnlockHero(unlocks);
    }

    private static void GMTalent()
    {
      for (int i = 1; i <= repeatcount; i++)
      {
        //client.GMAddTalent(100 + i, "gmtest", -315222848, ConvertToUnixTimestamp(DateTime.Now));
        Console.WriteLine("GMAddTalent[{0}] = ({1},{2},{3},{4})", i, 100 + i, "gmtest", -315222848, DateTime.Now);
        Thread.Sleep(sleepinterval);
      }

      Thread.Sleep(3 * sleepinterval);

      for (int i = 1; i <= repeatcount; i++)
      {
        //client.GMDeleteTalent(100 + i, "gmtest", 968657663, ConvertToUnixTimestamp(DateTime.Now));
        Console.WriteLine("GMDeleteTalent[{0}] = ({1},{2},{3},{4})", i, 100 + i, "gmtest", -315222848, DateTime.Now);
      }
    }

    private static void GMBan()
    {
/*      var infos = new List<GMMuteBanInfo>();
      for (int i = 1; i <= repeatcount+2; i++)
      {
        infos.Add(new GMMuteBanInfo { Auid = 100 + i, Gmlogin = "gmtest", Minutes = 5 + i, Reason = "ибо олень", Timestamp = ConvertToUnixTimestamp(DateTime.Now) });
        Console.WriteLine("BanUser[{0}] = ({1},{2},{3},{4},{5})", i, 100 + i, "gmtest", 5 + i, "ибо олень", DateTime.Now);
        Thread.Sleep(sleepinterval);
      }
      client.BanUser(infos);

      Thread.Sleep(30 * sleepinterval);
      
      var userinfos = new List<GMUserInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        userinfos.Add(new GMUserInfo {Auid = 100 + i, Gmlogin = "gmtest", Timestamp = ConvertToUnixTimestamp(DateTime.Now)});
        Console.WriteLine("UnbanUser[{0}] = ({1},{2},{3})", i, 100 + i, "gmtest", DateTime.Now);
      }
      client.UnbanUser(userinfos);*/
    }

    private static void GMMute()
    {
/*      for (int i = 1; i <= repeatcount; i++)
      {
        //client.MuteUser(100 + i, "gmtest", 5 + i, "ибо дебил", ConvertToUnixTimestamp(DateTime.Now));
        Console.WriteLine("MuteUser[{0}] = ({1},{2},{3},{4},{5})", i, 100 + i, "gmtest", 5 + i, "ибо дебил", DateTime.Now);
        Thread.Sleep(sleepinterval);
      }

      Thread.Sleep(3 * sleepinterval);

      for (int i = 1; i <= repeatcount; i++)
      {
        //client.UnmuteUser(100 + i, "gmtest", ConvertToUnixTimestamp(DateTime.Now));
        Console.WriteLine("UnmuteUser[{0}] = ({1},{2},{3})", i, 100 + i, "gmtest", DateTime.Now);
      }*/
    }

    private static void GMEditUser()
    {
      var fields = new List<FieldEditInfo>
                     {
                       new FieldEditInfo {Field = "name", Oldvalue = "oldname", Newvalue = "newname"},
                       new FieldEditInfo {Field = "mail", Oldvalue = "oldmail", Newvalue = "newmail"}
                     };
      for (int i = 1; i <= repeatcount; i++)
      {
        //client.GMEditUser(100 + i, "gmtest", fields, ConvertToUnixTimestamp(DateTime.Now));
        Console.WriteLine("GMEditUser[{0}] = ({1},{2},{3},{4})", i, 100 + i, "gmtest", fields, DateTime.Now);
        Thread.Sleep(sleepinterval);
      }
    }

    private static void Monitoring()
    {
      for (int d = 0; d < 10; d++)
      {
        TTransport transport2 = new THttpClient(new Uri(Settings.Default.ThriftServerUrl));
        TProtocol proto2 = new TBinaryProtocol(transport2);
        StatisticService.Client client2 = new StatisticService.Client(proto2);

        var infos = new List<MonitoringResultInfo>();
        for (int i = 1; i <= repeatcount; i++)
        {
          var info = new MonitoringResultInfo
          {
            Property = "property" + i % 2,
            Counter = "co/un/ter/" + i % 2,
            Value = 100500 + i,
            Timestamp = ConvertToUnixTimestamp(DateTime.Now)
          };
          infos.Add(info);
          Console.WriteLine("LoginInfo[{0}] = {1}", i, info);
        }
        if (!transport.IsOpen)
          transport.Open();
        client2.MonitoringResults(infos);
        transport2.Close();
        Console.WriteLine("Sent {0} monitoring results", infos.Count);

        Thread.Sleep(100);
      }
    }

    private static void Awards()
    {
      var a1 = new SessionAwardsInfo
                 {
                   Auid = 7,
                   Sessionpersistentid = 5881056756582318111,
                   Nick = "Мышь Белая",
                   Heroid = 701063780,
                   Rchange = new ResourceTable(),
                   Rtotal = new ResourceTable(),
                   Inc_reliability = 130,
                   New_reliability = 1300,
                   Force = 100.5,
                   Talents = new List<TalentInfo> { new TalentInfo { ClassId = -315222848 }, new TalentInfo { ClassId = 535679838 } },
                   Timestamp = ConvertToUnixTimestamp(DateTime.Now)
                 };
      /*var a2 = new SessionAwardsInfo
                 {
                   Auid = 13,
                   Sessionpersistentid = 5690312848035545110,
                   Nick = "itimei",
                   Heroid = 571020430,
                   Rchange = new ResourceTable(),
                   Rtotal = new ResourceTable(),
                   Inc_reliability = 230,
                   New_reliability = 2300,
                   Force = 200.6,
                   Talents = new List<int> { -595421952, 754290667 },
                   Rune = 1469305204,
                   Timestamp = ConvertToUnixTimestamp(DateTime.Now)
                 };*/
      var awards = new List<SessionAwardsInfo> {a1};
      client.GiveSessionAwards(awards);
      Console.WriteLine("Sent 1 awards");
    }

    private static void Launcher()
    {
      var infos = new List<LauncherInfo>();
      var einfos = new List<LauncherEventsInfo>();
      var dinfos = new List<LauncherDActionsInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new LauncherInfo
                     {
                       Hostid = "host" + i,
                       Package = "package" + i,
                       Ip = "127.0.0.1",
                       Location = "This computer",
                       Status = LauncherStatus.Complete,
                       Version = "v." + i
                     };
        infos.Add(info);
        Console.WriteLine("LauncherInfo[{0}] = {1}", i, info);
        var einfo = new LauncherEventsInfo
                      {
                        Auid = 100 + i,
                        Muid = "muid" + i,
                        Bitmask = 12345,
                        Timestamp = ConvertToUnixTimestamp(DateTime.UtcNow)
                      };
        einfos.Add(einfo);
        Console.WriteLine("LauncherEventsInfo[{0}] = {1}", i, einfo);
        var dinfo = new LauncherDActionsInfo
                      {
                        Action = "test action",
                        Auid = (100 + i).ToString(),
                        Muid = "muid" + i,
                        Applied_patches = 5,
                        Avg_speed = 125.3f,
                        Downloaded = 12312f,
                        Error = "no error",
                        Geolocation = "MSK",
                        Hostid = "D88393CE-2000-470B-BAAE-82F261497A90",
                        Min_speed = 1.2f,
                        Need_close = 0,
                        Speed = 56000f,
                        Total_download = 404444f,
                        Total_patches = 66,
                        Version = "9.4.1",
                        Timestamp = ConvertToUnixTimestamp(DateTime.UtcNow.AddHours(-1)),
                        Server_timestamp = ConvertToUnixTimestamp(DateTime.UtcNow)
                      };
        dinfos.Add(dinfo);
        Console.WriteLine("LauncherDActionsInfo[{0}] = {1}", i, dinfo);
      }

      client.LauncherStart(infos);
      Console.WriteLine("Sent {0} LauncherStart", infos.Count);
      Thread.Sleep(1000);

      client.LauncherEvents(einfos);
      Console.WriteLine("Sent {0} LauncherEvents", einfos.Count);
      Thread.Sleep(1000);

      client.LauncherDActions(dinfos);
      Console.WriteLine("Sent {0} LauncherDActions", dinfos.Count);
      Thread.Sleep(1000);
    }

    private static void Ignore()
    {
      var addinfos = new List<AddIgnoreInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new AddIgnoreInfo
                     {
                       Auid = 2,
                       Ignoreauid = 3,
                       Reason = "дурь против машки",
                       Timestamp = ConvertToUnixTimestamp(DateTime.Now)
                     };
        addinfos.Add(info);
        Console.WriteLine("AddIgnoreInfo[{0}] = {1}", i, info);
      }
      client.AddIgnore(addinfos);
      Thread.Sleep(2000);

      var reminfos = new List<RemoveIgnoreInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new RemoveIgnoreInfo
                     {
                       Auid = 3,
                       Ignoreauid = 2,
                       Timestamp = ConvertToUnixTimestamp(DateTime.Now)
                     };
        reminfos.Add(info);
        Console.WriteLine("RemoveIgnoreInfo[{0}] = {1}", i, info);
      }
      client.RemoveIgnore(reminfos);
    }

    private static void Bath()
    {
      var bathInfos = new List<MoveToBathInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new MoveToBathInfo
        {
          Auid = 2,
          Heroid = 1318972637,
          Rchange = new ResourceTable {Gold = 1, Silver = 2, Perl = 3, RedPerl = 4, Population = 5, Resource1 = 6, Resource2 = 7, Resource3 = 8},
          Rtotal = new ResourceTable {Gold = 11, Silver = 22, Perl = 33, RedPerl = 44, Population = 55, Resource1 = 66, Resource2 = 77, Resource3 = 88},
          Timestamp = ConvertToUnixTimestamp(DateTime.Now)
        };
        bathInfos.Add(info);
        Console.WriteLine("MoveToBathInfo[{0}] = {1}", i, info);
      }
      client.MoveHeroToBath(bathInfos);
    }

    private static void FactionSelect()
    {
      var infos = new List<FactionSelectInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new FactionSelectInfo
        {
          Auid = 2,
          Oldfaction = "A",
          Newfaction = "B",
          Rchange = new ResourceTable { Gold = 1, Silver = 2, Perl = 3, RedPerl = 4, Population = 5, Resource1 = 6, Resource2 = 7, Resource3 = 8 },
          Rtotal = new ResourceTable { Gold = 11, Silver = 22, Perl = 33, RedPerl = 44, Population = 55, Resource1 = 66, Resource2 = 77, Resource3 = 88 },
          Timestamp = ConvertToUnixTimestamp(DateTime.Now)
        };
        infos.Add(info);
        Console.WriteLine("MoveToBathInfo[{0}] = {1}", i, info);
      }
      client.FactionSelect(infos);
    }

    private static void QuestChange()
    {
      var infos = new List<QuestChangeInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new QuestChangeInfo
                     {
                       Auid = 2,
                       Reason = QuestChangeItem.Add,
                       Questid = -752976361,
                       Timestamp = ConvertToUnixTimestamp(DateTime.Now)
                     };
        infos.Add(info);
        Console.WriteLine("QuestChangeInfo[{0}] = {1}", i, info);
      }
      client.QuestChange(infos);
    }

    private static void DQuestChange()
    {
      var infos = new List<DynamicQuestChangeInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new DynamicQuestChangeInfo
                     {
                       Auid = 80,
                       Reason = QuestChangeItem.Accept,
                       Questindex = 123,
                       Questname= "lol dquest",
                       Timestamp = ConvertToUnixTimestamp(DateTime.Now)
                     };
        infos.Add(info);
        Console.WriteLine("DynamicQuestChangeInfo[{0}] = {1}", i, info);
      }
      client.DynamicQuestChange(infos);
    }

    private static void TQuestChange()
    {
      var infos = new List<TournamentQuestChangeInfo>();
      for ( int i = 1; i <= repeatcount; i++ )
      {
        var info = new TournamentQuestChangeInfo
        {
          Auid = 80,
          Reason = TournamentQuestResult.Loss,
          Questindex = 123,
          Questname = "lol dquest",
          Timestamp = ConvertToUnixTimestamp( DateTime.Now )
        };
        infos.Add( info );
        Console.WriteLine( "TournamentQuestChangeInfo[{0}] = {1}", i, info );
      }
      client.TournamentQuestChange( infos );
    }

    private static void JoinSession()
    {
      var infos = new List<JoinSessionInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new JoinSessionInfo
                     {
                       Auid = 5,
                       Heroid = 1523535311,
                       Sessionpersistentid = 1000000 + i,
                       Talentset = new List<int> {23777502, 25313680, 28571083, 28927687, 51203738, 54011443},
                       Timestamp = ConvertToUnixTimestamp(DateTime.Now)
                     };
        infos.Add(info);
        Console.WriteLine("JoinSessionInfo[{0}] = {1}", i, info);
      }
      client.JoinPvpSession(infos);
    }

    private static void ClientPing()
    {
      var infos = new List<ClientPingInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new ClientPingInfo
                     {
                       Auid = 5,
                       Location = "ru0",
                       MsecPing = 1000 + i,
                       Timestamp = ConvertToUnixTimestamp(DateTime.Now)
                     };
        infos.Add(info);
        Console.WriteLine("ClientPingInfo[{0}] = {1}", i, info);
      }
      client.ClientPings(infos);
    }

    private static void Rune()
    {
      var infos = new List<RuneReplenishInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new RuneReplenishInfo
                     {
                       Auid = 5,
                       Rune = 1469305204,
                       Timestamp = ConvertToUnixTimestamp(DateTime.Now)
                     };
        infos.Add(info);
        Console.WriteLine("RuneReplenishInfo[{0}] = {1}", i, info);
      }
      client.RuneReplenish(infos);

      var infos2 = new List<RuneExpireInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new RuneExpireInfo
                     {
                       Auid = 5,
                       Rune = 1469305204,
                       TransactionsLeft = 100,
                       BonusLeft = 500,
                       Timestamp = ConvertToUnixTimestamp(DateTime.Now)
                     };
        infos2.Add(info);
        Console.WriteLine("RuneExpireInfo[{0}] = {1}", i, info);
      }
      client.RuneExpire(infos2);

      var infos3 = new List<RuneSoulboundInfo>();
      for (int i = 1; i <= repeatcount; i++)
      {
        var info = new RuneSoulboundInfo
        {
          Auid = 5,
          Rune = 1469305204,
          Talent = -2144653155,
          Timestamp = ConvertToUnixTimestamp(DateTime.Now)
        };
        infos3.Add(info);
        Console.WriteLine("RuneSoulboundInfo[{0}] = {1}", i, info);
      }
      client.RuneUnsoulbound(infos3);

    }

    #endregion

  }
}
