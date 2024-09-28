using System.ComponentModel;

namespace ControlCenter.Areas.Monitoring.Models
{
  public class MonitoringInfoModel
  {
    [DisplayName("Game CCU")]
    public string GameCCU { get; set; }
    [DisplayName("Borderland CCU")]
    public string BldCCU { get; set; }
    [DisplayName("Dragonwald CCU")]
    public string DwdCCU { get; set; }
    [DisplayName("Native earth CCU")]
    public string NerCCU { get; set; }
    [DisplayName("Outpost CCU")]
    public string OpsCCU { get; set; }
    [DisplayName("Training CCU")]
    public string TrnCCU { get; set; }
    [DisplayName("Tutorial CCU")]
    public string TutCCU { get; set; }
    [DisplayName("Other CCU")]
    public string OthCCU { get; set; }
    [DisplayName("Users in matchmaking")]
    public string MMakingUsers { get; set; }
  }
}
