using System;
using System.Collections.Generic;
using System.Linq;
using BusinessLogic.Queuing;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;
using log4net;

namespace BusinessLogic.DBManagement
{

  public abstract class BaseTask : ITask
  {
    public int ErrorCount { get; set; }
    public string LastErrorMessage { get; set; }
    public DateTime? LastExecutionTime { get; set; }
    public string Dump()
    {
      return this.ToString();
    }
    public abstract bool Execute();
  }
  
  public class SocialLogoutTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof (SocialLogoutTask));

    private IEnumerable<LoginInfoBL> logins;

    private readonly IPlayerRepository playerRepository;
    private readonly ISocialSessionRepository socialSessionRepository;

    public SocialLogoutTask(IEnumerable<LoginInfoBL> logins)
      : this(logins, new PlayerRepository(), new SocialSessionRepository())
    {
    }

    public SocialLogoutTask(IEnumerable<LoginInfoBL> logins, IPlayerRepository prepo, ISocialSessionRepository srepo)
    {
      if (logins == null) throw new ArgumentNullException("logins");

      this.logins = logins;
      this.playerRepository = prepo;
      this.socialSessionRepository = srepo;
    }

    public override bool Execute()
    {
      var failedlogouts = new List<LoginInfoBL>();
      foreach (LoginInfoBL login in logins)
      {
        try
        {
          Player p = playerRepository.GetById(login.UserId);
          if (p == null)
            throw new Exception(String.Format("Cannot write social logout info {0}, Player(id={1}) was not found", login, login.UserId));
          socialSessionRepository.WriteLogout(p, login.Server, login.Cluster, login.Timestamp);
        }
        catch (Exception ex)
        {
          _log.Error("Failed task SocialLogoutTask, logout info " + login, ex);
          LastErrorMessage = ex.Message;
          failedlogouts.Add(login);
        }
      }
      if (failedlogouts.Count > 0)
      {
        ErrorCount++;
        logins = failedlogouts;
        return false;
      }
      playerRepository.Dispose();
      socialSessionRepository.Dispose();
      return true;
    }
  }

  public class FactionChangeTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof(FactionChangeTask));

    private List<FactionSelectInfoBL> infos;
    private readonly IPlayerRepository playerRepository;
    private readonly IRepository<FactionChange> factionChangeRepository;
    private readonly IResourceLogRepository resourceLogRepository;

    public FactionChangeTask(IEnumerable<FactionSelectInfoBL> infos)
      : this(infos, new PlayerRepository(), new Repository<FactionChange>(), new ResourceLogRepository())
    {
    }
    public FactionChangeTask(IEnumerable<FactionSelectInfoBL> infos,
      IPlayerRepository prepo, IRepository<FactionChange> fcrepo, IResourceLogRepository rlrepo)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      this.infos = infos.ToList();
      this.playerRepository = prepo;
      this.factionChangeRepository = fcrepo;
      this.resourceLogRepository = rlrepo;
    }

    public override bool Execute()
    {
      var failedinfos = new List<FactionSelectInfoBL>();
      foreach (FactionSelectInfoBL info in infos)
      {
        try
        {
          Player p = playerRepository.GetById(info.UserId);
          if (p == null)
            throw new Exception(String.Format("Cannot write faction select info {0}, Player(id={1}) was not found", info, info.UserId));

          if (p.Faction != (Faction) info.NewFaction)
          {
            p.Faction = (Faction) info.NewFaction;
            playerRepository.Update(p);
          }

          if (!info.RChange.IsEmpty && info.ResourceLog == null)
          {
            var rl = new ResourceLog
                       {
                         Player = p,
                         Gain = false,
                         Source = "factionchange",
                         GoldChange = -info.RChange.Gold,
                         SilverChange = -info.RChange.Silver,
                         PerlChange = -info.RChange.Perl,
                         RedPerlChange = -info.RChange.RedPerl,
                         PopulationChange = -info.RChange.Population,
                         Resource1Change = -info.RChange.Resource1,
                         Resource2Change = -info.RChange.Resource2,
                         Resource3Change = -info.RChange.Resource3,
                         ShardChange = -info.RChange.Shard,
                        CurrencyName = info.RChange.CurrencyName,
                        CurrencyChangeValue = -info.RChange.CurrencyValue,
                         GoldTotal = info.RTotal.Gold,
                         SilverTotal = info.RTotal.Silver,
                         PerlTotal = info.RTotal.Perl,
                         RedPerlTotal = info.RTotal.RedPerl,
                         PopulationTotal = info.RTotal.Population,
                         Resource1Total = info.RTotal.Resource1,
                         Resource2Total = info.RTotal.Resource2,
                         Resource3Total = info.RTotal.Resource3,
                         ShardTotal = info.RTotal.Shard,
                         CurrencyTotalValue = info.RTotal.CurrencyValue,
                         Timestamp = info.Timestamp
                       };
            resourceLogRepository.Add(rl);
            info.ResourceLog = rl;
          }

          var fc = new FactionChange
                     {
                       Player = p,
                       NewFaction = (Faction) info.NewFaction,
                       OldFaction = (Faction) info.OldFaction,
                       ResourceLog = info.ResourceLog,
                       Timestamp = info.Timestamp
                     };
          factionChangeRepository.Add(fc);
        }
        catch (Exception ex)
        {
          _log.Error("Failed task FactionChangeTask, info = " + info, ex);
          LastErrorMessage = ex.Message;
          failedinfos.Add(info);
        }
      }
      if (failedinfos.Count > 0)
      {
        ErrorCount++;
        infos = failedinfos;
        return false;
      }
      playerRepository.Dispose();
      resourceLogRepository.Dispose();
      factionChangeRepository.Dispose();
      return true;
    }
  }

  public class CharacterUnlockTask : BaseTask
  {
    public const string RLOG_SOURCE = "characterunlock";

    private static ILog _log = LogManager.GetLogger(typeof(CharacterUnlockTask));

    private List<UnlockHeroInfoBL> unlocks;

    private readonly IPlayerRepository playerRepository;
    private readonly IPlayerCharacterRepository playerCharacterRepository;
    private readonly ICharacterUnlockRepository characterUnlockRepository;
    private readonly IResourceLogRepository resourceLogRepository;

    public CharacterUnlockTask(IEnumerable<UnlockHeroInfoBL> unlocks)
      : this(unlocks, new PlayerRepository(), new PlayerCharacterRepository(), new CharacterUnlockRepository(), new ResourceLogRepository())
    {
    }

    public CharacterUnlockTask(IEnumerable<UnlockHeroInfoBL> unlocks,
      IPlayerRepository prepo, IPlayerCharacterRepository pcrepo, ICharacterUnlockRepository curepo, IResourceLogRepository rlrepo)
    {
      if (unlocks == null) throw new ArgumentNullException("unlocks");
      this.unlocks = unlocks.ToList();

      this.playerRepository = prepo;
      this.playerCharacterRepository = pcrepo;
      this.characterUnlockRepository = curepo;
      this.resourceLogRepository = rlrepo;
    }

    public override bool Execute()
    {
      var failedunlocks = new List<UnlockHeroInfoBL>();
      foreach (var unlock in unlocks)
      {
        try
        {
          Player player = playerRepository.GetById(unlock.UserId);
          if (player == null)
            throw new Exception(String.Format("Cannot write character unlock {0}, player(id={1}) is not exists", unlock, unlock.UserId));

          var pc = playerCharacterRepository.GetOrCreateByParams(player, unlock.HeroId);
          pc.UnlockDate = unlock.Timestamp;
          playerCharacterRepository.Update(pc);
          
          if (unlock.ResourceLog == null)
          {
            var rl = new ResourceLog
                       {
                         Player = player,
                         Gain = false,
                         Source = RLOG_SOURCE,
                         BuildingName = pc.Character.Name,
                         GoldChange = -unlock.RChange.Gold,
                         SilverChange = -unlock.RChange.Silver,
                         PerlChange = -unlock.RChange.Perl,
                         RedPerlChange = -unlock.RChange.RedPerl,
                         PopulationChange = -unlock.RChange.Population,
                         Resource1Change = -unlock.RChange.Resource1,
                         Resource2Change = -unlock.RChange.Resource2,
                         Resource3Change = -unlock.RChange.Resource3,
                         ShardChange = -unlock.RChange.Shard,
                         CurrencyName = unlock.RChange.CurrencyName,
                         CurrencyChangeValue = -unlock.RChange.CurrencyValue,
                         GoldTotal = unlock.RTotal.Gold,
                         SilverTotal = unlock.RTotal.Silver,
                         PerlTotal = unlock.RTotal.Perl,
                         RedPerlTotal = unlock.RTotal.RedPerl,
                         PopulationTotal = unlock.RTotal.Population,
                         Resource1Total = unlock.RTotal.Resource1,
                         Resource2Total = unlock.RTotal.Resource2,
                         Resource3Total = unlock.RTotal.Resource3,
                         ShardTotal = unlock.RTotal.Shard,
                         CurrencyTotalValue = unlock.RTotal.CurrencyValue,
                         Timestamp = unlock.Timestamp
                       };
            resourceLogRepository.Add(rl);
            unlock.ResourceLog = rl;
          }

          var cu = new CharacterUnlock
                     {
                       PlayerCharacter = pc,
                       ResourceLog = unlock.ResourceLog,
                       Timestamp = unlock.Timestamp
                     };
          characterUnlockRepository.Add(cu);
        }
        catch (Exception ex)
        {
          _log.Error("Failed task CharacterUnlockTask, unlock info " + unlock, ex);
          LastErrorMessage = ex.Message;
          failedunlocks.Add(unlock);
        }
      }
      if (failedunlocks.Count > 0)
      {
        ErrorCount++;
        unlocks = failedunlocks;
        return false;
      }
      return true;
    }
  }

  public class MoveToBathTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof(MoveToBathTask));

    private IEnumerable<MoveToBathInfoBL> infos;

    private readonly IPlayerRepository playerRepository;
    private readonly IPlayerCharacterRepository playerCharacterRepository;
    private readonly IRepository<MoveToBath> mainRepository;
    private readonly IResourceLogRepository resourceLogRepository;

    public MoveToBathTask(IEnumerable<MoveToBathInfoBL> infos)
      : this(infos, new PlayerRepository(), new PlayerCharacterRepository(), new Repository<MoveToBath>(), new ResourceLogRepository())
    {
    }

    public MoveToBathTask(IEnumerable<MoveToBathInfoBL> infos,
      IPlayerRepository prepo, IPlayerCharacterRepository pcrepo, IRepository<MoveToBath> repo, IResourceLogRepository rlrepo)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      this.infos = infos;

      this.playerRepository = prepo;
      this.playerCharacterRepository = pcrepo;
      this.mainRepository = repo;
      this.resourceLogRepository = rlrepo;
    }

    public override bool Execute()
    {
      var failedinfos = new List<MoveToBathInfoBL>();
      foreach (var info in infos)
      {
        try
        {
          Player player = playerRepository.GetById(info.UserId);
          if (player == null)
            throw new Exception(String.Format("Cannot write moving character to bath {0}, player(id={1}) is not exists", info, info.UserId));

          if (info.ResourceLog == null)
          {
            var rl = new ResourceLog
                       {
                         Player = player,
                         Gain = false,
                         Source = "movetobath",
                         GoldChange = -info.RChange.Gold,
                         SilverChange = -info.RChange.Silver,
                         PerlChange = -info.RChange.Perl,
                         RedPerlChange = -info.RChange.RedPerl,
                         PopulationChange = -info.RChange.Population,
                         Resource1Change = -info.RChange.Resource1,
                         Resource2Change = -info.RChange.Resource2,
                         Resource3Change = -info.RChange.Resource3,
                         ShardChange = -info.RChange.Shard,
                        CurrencyName = info.RChange.CurrencyName,
                         CurrencyChangeValue = -info.RChange.CurrencyValue,
                        GoldTotal = info.RTotal.Gold,
                         SilverTotal = info.RTotal.Silver,
                         PerlTotal = info.RTotal.Perl,
                         RedPerlTotal = info.RTotal.RedPerl,
                         PopulationTotal = info.RTotal.Population,
                         Resource1Total = info.RTotal.Resource1,
                         Resource2Total = info.RTotal.Resource2,
                         Resource3Total = info.RTotal.Resource3,
                         ShardTotal = info.RTotal.Shard,
                        CurrencyTotalValue = info.RTotal.CurrencyValue,
                        Timestamp = info.Timestamp
                       };
            resourceLogRepository.Add(rl);
            info.ResourceLog = rl;
          }

          var pc = playerCharacterRepository.GetOrCreateByParams(player, info.HeroId);

          var mb = new MoveToBath
                     {
                       PlayerCharacter = pc,
                       ResourceLog = info.ResourceLog,
                       Minutes = info.Minutes,
                       Timestamp = info.Timestamp
                     };
          mainRepository.Add(mb);
        }
        catch (Exception ex)
        {
          _log.Error("Failed task MoveToBathTask, info = " + info, ex);
          LastErrorMessage = ex.Message;
          failedinfos.Add(info);
        }
      }
      if (failedinfos.Count > 0)
      {
        ErrorCount++;
        infos = failedinfos;
        return false;
      }
      return true;
    }
  }

  public class ResourcesLogTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof(ResourcesLogTask));

    private IEnumerable<ResourcesChangeInfoBL> infos;

    private readonly IPlayerRepository playerRepository;
    private readonly IResourceLogRepository resourceLogRepository;

    public ResourcesLogTask(IEnumerable<ResourcesChangeInfoBL> infos)
      : this(infos, new PlayerRepository(), new ResourceLogRepository())
    {
    }

    public ResourcesLogTask(IEnumerable<ResourcesChangeInfoBL> infos,
      IPlayerRepository prepo, IResourceLogRepository rlrepo)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      this.infos = infos;

      this.playerRepository = prepo;
      this.resourceLogRepository = rlrepo;
    }

    public override bool Execute()
    {
      var failedinfos = new List<ResourcesChangeInfoBL>();
      foreach (var info in infos)
      {
        try
        {
          Player player = playerRepository.GetById(info.Auid);
          if (player == null)
            throw new Exception(String.Format("Cannot write resource change {0}, player is not exists", info));

          var resource = new ResourceLog
                           {
                             Player = player,
                             Gain = info.Gain,
                             Source = info.Source,
                             BuildingName = info.BuildingName,
                             GoldChange = (info.Gain ? 1 : -1)*info.RChange.Gold,
                             SilverChange = (info.Gain ? 1 : -1)*info.RChange.Silver,
                             PerlChange = (info.Gain ? 1 : -1)*info.RChange.Perl,
                             RedPerlChange = (info.Gain ? 1 : -1)*info.RChange.RedPerl,
                             PopulationChange = (info.Gain ? 1 : -1)*info.RChange.Population,
                             Resource1Change = (info.Gain ? 1 : -1)*info.RChange.Resource1,
                             Resource2Change = (info.Gain ? 1 : -1)*info.RChange.Resource2,
                             Resource3Change = (info.Gain ? 1 : -1)*info.RChange.Resource3,
                             ShardChange = (info.Gain ? 1 : -1)*info.RChange.Shard,
                             CurrencyName = info.RChange.CurrencyName,
                             CurrencyChangeValue = (info.Gain ? 1 : -1) * info.RChange.CurrencyValue,
                             GoldTotal = info.RTotal.Gold,
                             SilverTotal = info.RTotal.Silver,
                             PerlTotal = info.RTotal.Perl,
                             RedPerlTotal = info.RTotal.RedPerl,
                             PopulationTotal = info.RTotal.Population,
                             Resource1Total = info.RTotal.Resource1,
                             Resource2Total = info.RTotal.Resource2,
                             Resource3Total = info.RTotal.Resource3,
                             ShardTotal = info.RTotal.Shard,
                             CurrencyTotalValue = info.RTotal.CurrencyValue,
                             Timestamp = info.Timestamp
                           };
          resourceLogRepository.Add(resource);
        }
        catch (Exception ex)
        {
          _log.Error("Failed task ResourcesLogTask, unlock info " + info, ex);
          LastErrorMessage = ex.Message;
          failedinfos.Add(info);
        }
      }
      if (failedinfos.Count > 0)
      {
        ErrorCount++;
        infos = failedinfos;
        return false;
      }
      return true;
    }
  }

  public class QuestChangeTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof(QuestChangeTask));

    private IEnumerable<QuestChangeInfoBL> infos;

    private readonly IPlayerRepository playerRepository;
    private readonly IRepository<Quest> questRepository;
    private readonly IRepository<QuestChange> questChangeRepository;

    public QuestChangeTask(IEnumerable<QuestChangeInfoBL> infos)
      : this(infos, new PlayerRepository(), new Repository<Quest>(), new Repository<QuestChange>())
    {
    }

    public QuestChangeTask(IEnumerable<QuestChangeInfoBL> infos, IPlayerRepository prepo, IRepository<Quest> qrepo, IRepository<QuestChange> qcrepo)
    {
      if (infos == null) throw new ArgumentNullException("infos");
      this.infos = infos;

      this.playerRepository = prepo;
      this.questRepository = qrepo;
      this.questChangeRepository = qcrepo;
    }

    public override bool Execute()
    {
      var failedinfos = new List<QuestChangeInfoBL>();
      foreach (var info in infos)
      {
        try
        {
          Player player = playerRepository.GetById(info.Auid);
          if (player == null)
            throw new Exception(String.Format("Cannot write quest change {0}, player is not exists", info));

          Quest quest = questRepository.GetById(info.QuestId);
          if (quest == null)
            throw new Exception(String.Format("Cannot write quest change {0}, quest is not exists", info));

          var qchange = new QuestChange
                          {
                            Player = player,
                            Quest = quest,
                            ChangeType = (QuestChangeType) info.Reason,
                            Timestamp = info.Timestamp
                          };
          questChangeRepository.Add(qchange);
        }
        catch (Exception ex)
        {
          _log.Error("Failed task QuestChangeTask, info = " + info, ex);
          LastErrorMessage = ex.Message;
          failedinfos.Add(info);
        }
      }
      if (failedinfos.Count > 0)
      {
        ErrorCount++;
        infos = failedinfos;
        return false;
      }
      return true;
    }
  }
}