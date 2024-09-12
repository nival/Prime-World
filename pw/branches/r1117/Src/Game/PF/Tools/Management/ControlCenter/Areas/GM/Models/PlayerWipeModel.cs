using System.ComponentModel.DataAnnotations;

namespace ControlCenter.Areas.GM.Models
{
  public class PlayerWipeModel
  {
    public const string CommandFindAccountByNick = "FindAccountByNick";
    public const string CommandFindAccountByEmail = "FindAccountByEmail";
    public const string CommandChangeAccountEmail = "ChangeAccountEmail";
    public const string CommandWipeAccount = "WipeAccount";

    //this data is receiving
    [UIHint("AccountShortInfoView")]
    public AccountShortInfoModel FoundAccountByNick { get; set; }
    [UIHint("AccountShortInfoView")]
    public AccountShortInfoModel FoundAccountByEmail { get; set; }
    [UIHint("AccountShortInfoView")]
    public AccountShortInfoModel EditedAccountAfterChangeEmail { get; set; }
    [UIHint("AccountShortInfoView")]
    public AccountShortInfoModel EditedAccountAfterWipe { get; set; }

    //this data is sending
    public string Email { get; set; }
    public string NewEmail { get; set; }
    public string NickName { get; set; }
    public string NewPassword { get; set; }
    

    public PlayerWipeModel()
    {
    
    }
  }
}
