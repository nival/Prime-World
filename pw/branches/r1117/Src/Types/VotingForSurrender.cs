using System.Collections.Generic;
using libdb.DB;
using System.ComponentModel;

namespace UI.DBVotingForSurrender
{
  public enum VFSUserMessages
  {
    CantStartAnotherInProgress,
    CantStartCooldown,          
    PlayerStartVoting,          
    CantMakeDecisionIsntInProgress,
    CantMakeDecisionAlreadyVoted,
    CommandAcceptSurrender,
    CommandDeclineSurrender
  }

  public enum VFSMessageType
  {
    ShowMessageToPlayer,
    ShowMessageToCommand,
    ShowMessageToAll
  }

  public class VFSMessageDesc
  {
    public VFSMessageType type = VFSMessageType.ShowMessageToAll;
    public TextRef text;
  }

  [DBVersion(1)]
  public class VotingForSurrenderPerMission : DBResource
  {
    [Description("Минимальная задержка перед первым голосованием")]
    public float cooldownAfterStart = 1 * 60;

    [Description("Минимальная задержка после завершившегося голосования перед началом следующего")]
    public float cooldownAfterPrevisionVoting = 15;

    [Description("Минимальное количество пользователей, которые могут проголосовать против при общем положительном итоге")]
    public int maxUsersForFightIgnored = 1;

    [Description("Время (в секундах), в течение которого отключенные игроки (не ливеры!) автоматически голосуют ПРОТИВ")]
    public float timeDisconnectedPlayersVoteForFight = 3 * 60;
  }

  [DBVersion(1)]
  public class VotingForSurrender: DBResource
  {
    [Description("Настройки по-умолчанию для миссии. Будут использоваться если такие настройки не указаны в данных миссии")]
    public DBPtr<VotingForSurrenderPerMission> defaultMissionSettings;

    [Description("Задержка после успешного голосования перед капитуляцией")]
    public float delayBeforeVotingComplete = 5;

    [Description("Продолжительность голосования")]
    public float votingDuration = 1 * 60;

    [Description("Радиус области под варфогом, которая открывается после капитуляции")]
    public int warforOpenedRadius = 80;

    [Description("Сообщения пользователю")]
    [EnumArray(typeof(VFSUserMessages))]
    public List<VFSMessageDesc> messages; 
  }
}
