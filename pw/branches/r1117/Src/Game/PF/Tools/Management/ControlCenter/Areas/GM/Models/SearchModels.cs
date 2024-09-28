using System.ComponentModel;

namespace ControlCenter.Areas.GM.Models
{
  public class SearchBySNModel
  {
    [DisplayName( "Social network id" )]
    public string SNid { get; set; }

    [DisplayName( "User id in the social network" )]
    public string SNUid { get; set; }

    public long? Auid { get; set; }

    public string NickName { get; set; }
  }
}