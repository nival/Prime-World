using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using AccountLib;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Controllers
{
  [Authorize]
  public class PlayerWipeController : Controller
  {
    public IAccountService AccountSvc { get; set; }

    protected override void Initialize(System.Web.Routing.RequestContext requestContext)
    {
      base.Initialize(requestContext);

      if (AccountSvc == null)
        AccountSvc = new AccountService();
    }

    //
    // GET: /GM/PlayerWipe/
    [AuthorizeWithPermission(Permission = "GM_PlayerWipe")]
    public ActionResult PlayerWipe()
    {
      var model = new PlayerWipeModel();
      //var testThriftResponse = new AccountShortInfo
      //{
      //  Email = "testEmail",
      //  Login = "testLogin",
      //  Nickname = "testNickname",
      //  Snid = "12312312321",
      //  Snuid = "123123112312132"
      //};


      //model.FoundAccountByEmail = new AccountShortInfoModel(testThriftResponse);
      //model.FoundAccountByNick = new AccountShortInfoModel(testThriftResponse);
      //model.EditedAccountAfterChangeEmail = new AccountShortInfoModel(testThriftResponse);
      //model.EditedAccountAfterWipe = new AccountShortInfoModel(testThriftResponse);


      TimeSpan epochTicks = new TimeSpan(new DateTime(1970, 1, 1).Ticks);
      TimeSpan unixTicks = new TimeSpan(DateTime.UtcNow.Ticks) - epochTicks;
      double unixTime = unixTicks.TotalSeconds;

      model.NewEmail = ((int)unixTime) + ":deleted";
       
      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_PlayerWipe")]
    public ActionResult PlayerWipe(PlayerWipeModel model, string command)
    {
      PlayerWipeResp response;
      switch (command)
      {
        case PlayerWipeModel.CommandFindAccountByNick:
          response = AccountSvc.FindPlayerByNickname(model.NickName);
          if (!string.IsNullOrEmpty(response.ErrorIfExistToShow))
            return RedirectToAction("ShowError", "Account", new { error = response.ErrorIfExistToShow });
          model.FoundAccountByNick = response.PlayerModel;
          break;

        case PlayerWipeModel.CommandFindAccountByEmail:
          response = AccountSvc.FindPlayerByEmail(model.Email);
          if (!string.IsNullOrEmpty(response.ErrorIfExistToShow))
            return RedirectToAction("ShowError", "Account", new { error = response.ErrorIfExistToShow });
          model.FoundAccountByEmail = response.PlayerModel;
          break;

        case PlayerWipeModel.CommandChangeAccountEmail:
          response = AccountSvc.PlayerChangeEmail(model.Email, model.NewEmail, model.NewPassword);
          if (!string.IsNullOrEmpty(response.ErrorIfExistToShow))
            return RedirectToAction("ShowError", "Account", new { error = response.ErrorIfExistToShow });
          model.EditedAccountAfterChangeEmail = response.PlayerModel;
          break;

        case PlayerWipeModel.CommandWipeAccount:
          response = AccountSvc.PlayerRemoveNickname(model.Email, model.NickName);
          if (!string.IsNullOrEmpty(response.ErrorIfExistToShow))
            return RedirectToAction("ShowError", "Account", new { error = response.ErrorIfExistToShow });
          model.EditedAccountAfterWipe = response.PlayerModel;
          break;

      }
      return View(model);
    }

    [HttpGet]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult DeleteSaAccount(long? auid)
    {
      var model = new DeleteSaAccountModel();
      if (auid.HasValue)
        model.Auid = auid.Value;

      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult DeleteSaAccount(DeleteSaAccountModel model)
    {
      ModelState.Clear();
      model.Done = true;
      if (model.Confirmed())
      {
        model.Result = AccountSvc.RemoveSaAccount(model.Auid);
        //model.Result = string.Empty;
      }
      else
      {
        model.Result = "Action not confirmed!";
      }
      return View(model);
    }
  }
}
