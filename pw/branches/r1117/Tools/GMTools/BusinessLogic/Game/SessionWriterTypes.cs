namespace BusinessLogic.Game
{
  public class MMakingPlayerInfo
  {
    public long UserId;
    public int Faction;
    public int Sex;
    public int HeroId;
    public int Rating;
    public int PlayerRating;
    public float Force;
    public int PartyId;
    public float WaitTime;
    public int LoseStreak;
    public int FameLevel;
    public int Basket;
    public int LobbyReaction;
    public float LobbyReactionTime;
  }

  public class SessionStartPlayerInfo
  {
    public long UserId { get; set; }
    public int Faction { get; set; }
    public int Sex { get; set; }
    public int HeroId { get; set; }
    public string Nickname { get; set; }
  }

  public class SessionResultPlayerInfo
  {
    public long UserId { get; set; }
    public int FinalLevel { get; set; }
    public bool Leaver { get; set; }
    public int Score { get; set; }
    public int Kills { get; set; }
    public int Deaths { get; set; }
    public int Assists { get; set; }
    public int EnemyCreepsKilled { get; set; }
    public int NeutralCreepsKilled { get; set; }
  }
}