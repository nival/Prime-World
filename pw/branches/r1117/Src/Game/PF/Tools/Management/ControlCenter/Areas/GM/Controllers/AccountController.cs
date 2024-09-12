using System;
using System.Collections;
using System.Globalization;
using System.Web.Mvc;
using System.Web.Routing;
using AccountLib;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.IO;
using System.Text;
using ControlCenter.Models;
using DAL.Entities;
using log4net;

namespace ControlCenter.Areas.GM.Controllers
{
  [Authorize]
  public class AccountController : Controller
  {
    private static ILog _log = LogManager.GetLogger(typeof (AccountController));

    public IAccountService AccountSvc { get; set; }
    public IComplaintService ComplaintService { get; set; }

    protected override void Initialize( System.Web.Routing.RequestContext requestContext )
    {
      base.Initialize( requestContext );

      if ( AccountSvc == null )
        AccountSvc = new AccountService();
      if (ComplaintService == null)
        ComplaintService = new ComplaintService();
    }

    [AuthorizeWithPermission( Permission = "GM_AccountView,GM_Broadcast" )]
    public ActionResult Index()
    {
      ViewData["all_sn"] = AccountSvc.SocialNetworks;
      return View();
    }

    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    [HttpPost]
    public ActionResult Index( SearchBySNModel model )
    {
      if ( Request.Form.ToString().Contains( "submitSnid" ) )
      {
        if ( string.IsNullOrEmpty( model.SNUid ) )
          ModelState.AddModelError( "model.SNUid", "Enter SN Uid name" );
        else
          return RedirectToAction( "Details", new { snid = model.SNid, snuid = model.SNUid.Trim() } );
      }
      else if ( Request.Form.ToString().Contains( "submitAuid" ) )
      {
        if ( !model.Auid.HasValue )
          ModelState.AddModelError( "model.Auid", "Enter valid Auid" );
        else
          return RedirectToAction( "Details", new { auid = model.Auid } );
      }
      else if ( Request.Form.ToString().Contains( "submitNickName" ) )
      {
        if ( string.IsNullOrEmpty( model.NickName ) )
          ModelState.AddModelError( "model.NickName", "Enter valid NickName" );
        else
          return RedirectToAction( "SearchByNickResults", new { nickName = model.NickName } );
      }

      ViewData["all_sn"] = AccountSvc.SocialNetworks;
      return View( model );
    }

    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult Details( string snid, string snuid, string login, long? auid )
    {
      if ( ( string.IsNullOrEmpty( snid ) || string.IsNullOrEmpty( snuid ) ) && ( login == null ) && !auid.HasValue )
        return RedirectToAction( "ShowError", new { error = "Necessary parameter [login] or [snuid, snid] or [auid] was not supplied" } );

      AccountInfoModel model;
      if ( auid.HasValue )
      {
        model = AccountSvc.GetAccountByAuid( auid.Value );
      }
      else
      {
        if ( login != null ) //<SNid, SNUid> неизвестны, получить их из логина
          GetSNDataFromLogin( login, out snid, out snuid );
        model = AccountSvc.GetAccountBySNUid( snid, snuid );
      }

      if (model.ErrorIfExistToShow != null)
        return RedirectToAction("ShowError", new {error = model.ErrorIfExistToShow});
      if (String.IsNullOrEmpty(model.Login))
        return RedirectToAction("ShowError", new {error = "Server returned wrong Login"});

      // Проверка на доступ ГМа к этим данным
      var user = (GMToolsPrincipal) HttpContext.User;
      if (!user.HasLocale(model.Locale) || !user.HasMuid(model.Muid))
        return View("Forbidden");

      //c соцсервера не присылают <SNid, SNUid> надо их получать при помощи GetSNDataFromLogin
      GetSNDataFromLogin( model.Login, out snid, out snuid );
      model.SNid = snid;
      model.SNUid = snuid;

      return View( model );
    }

    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult SearchByNickResults( string nickName )
    {
      GetAccountsResp uiResp = AccountSvc.GetAccountsByNickName( nickName );
      if ( uiResp.ErrorIfExistToShow != null )
        return RedirectToAction( "ShowError", new { error = uiResp.ErrorIfExistToShow } );
      List<AccountInfoModel> model = uiResp.accountsList;
      if ( model.Count == 1 )
        return RedirectToAction( "Details", "Account", new { login = model[0].Login } );
      return View( model );
    }

    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult Heroes( string login )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal) User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      GetHeroInfoListResp uiResp = AccountSvc.GetAccountHeroes( login );
      if ( uiResp.ErrorIfExistToShow != null )
        return RedirectToAction( "ShowError", new { error = uiResp.ErrorIfExistToShow } );
      var heroesCatalog = AccountSvc.GetHeroesCatalog();
      if ( heroesCatalog == null )
        return RedirectToAction( "ShowError", new { error = "Failed to get heroes catalog" } );
      if ( heroesCatalog.Count == 0 )
        return RedirectToAction( "ShowError", new { error = "Failed to get heroes catalog" } );
      ViewData["selClassHero"] = heroesCatalog.Except( uiResp.heroesList, new LambdaComparer<HeroInfoModel>( ( x, y ) => x.HeroClassId == y.HeroClassId ) ).Select( x => new SelectListItem { Text = x.HeroName, Value = x.HeroClassId.ToString(), Selected = false } );
      return View( uiResp.heroesList );
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult Heroes( string login, int? selClassHero )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if ( selClassHero != null )
      {
        string errorIfExistToShow = AccountSvc.UnlockHero( login, (int)selClassHero, User.Identity.Name );
        if ( errorIfExistToShow != null )
          return RedirectToAction( "ShowError", new { error = errorIfExistToShow } );
      }
      return Heroes( login );
    }

    [AuthorizeWithPermission(Permission = "GM_AccountView")]
    public ActionResult Skins(long auid)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      var models = AccountSvc.GetAccountSkins(auid);
      if (models == null)
        return RedirectToAction("ShowError", new {error = "Failed to get account skins"});
      ViewData["auid"] = auid;
      return View(models);
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult AddSkin(long auid, string persistentId)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      error = AccountSvc.AddSkin(auid, persistentId, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", new {error});
      ViewData["auid"] = auid;
      return RedirectToAction("Skins", new {auid});
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult DeleteSkin(long auid, string persistentId)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      error = AccountSvc.DeleteSkin(auid, persistentId, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", new {error});
      ViewData["auid"] = auid;
      return RedirectToAction("Skins", new { auid });
    }

    [AuthorizeWithPermission(Permission = "GM_AccountView")]
    public ActionResult TalentUpgradeEntities(long auid)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      var models = AccountSvc.GetAccountTalentUpgradeEntities(auid);
      if (models == null)
        return RedirectToAction("ShowError", new { error = "Failed to get account TalentUpgradeEntities" });
      ViewData["auid"] = auid;
      return View(models);
    }
    
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult DeleteTalentUpgradeEntity(long auid, int instanceId)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      error = AccountSvc.DeleteTalentUpgradeEntity(auid, instanceId, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", new { error });
      ViewData["auid"] = auid;
      return RedirectToAction("TalentUpgradeEntities", new { auid });
    }

    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult TalentSet( string login, int heroInstanceId, string heroName )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      ViewData["heroInstanceId"] = heroInstanceId;
      ViewData["heroName"] = heroName;
      GetTalentInfoListResp uiResp = AccountSvc.GetHeroTalentSet( login, heroInstanceId );
      if ( uiResp.ErrorIfExistToShow != null )
        return RedirectToAction( "ShowError", new { error = uiResp.ErrorIfExistToShow } );
      return View( uiResp.talentsList );
    }

    [AuthorizeWithPermission(Permission = "GM_AccountView")]
    public ActionResult SeasonsInfo(string login, int heroInstanceId, string heroName)
    {
        string snid, snuid, error;
        GetSNDataFromLogin(login, out snid, out snuid);
        if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
        {
            if (!String.IsNullOrEmpty(error))
                return RedirectToAction("ShowError", new { error });
            return View("Forbidden");
        }

        ViewData["login"] = login;
        ViewData["heroInstanceId"] = heroInstanceId;
        ViewData["heroName"] = heroName;

        GetSeasonInfoListResp uiResp = AccountSvc.GetHeroSeasonsInfo(login, heroInstanceId);
        if (uiResp.ErrorIfExistToShow != null)
            return RedirectToAction("ShowError", new { error = uiResp.ErrorIfExistToShow });
        return View(uiResp.seasonInfoList);
    }


    [AuthorizeWithPermission(Permission = "GM_AccountView")]
    public ActionResult Library(string login)
    {
      #region Locale permission check

      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal) User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      #endregion

      ViewData["login"] = login;

      var modelResp = AccountSvc.GetAccountLibrary(login);
      if (modelResp.ErrorIfExistToShow != null)
        return RedirectToAction("ShowError", new { error = modelResp.ErrorIfExistToShow });

      return View(modelResp.talentsList);
    }


    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult Library(string login, int[] selected)
    {
      #region Locale permission check

      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal) User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      #endregion

      if ( selected != null )
      {
        foreach ( var talentid in selected )
        {
          error = AccountSvc.LockTalent( login, -1, talentid, User.Identity.Name );
          if ( error != null )
            return RedirectToAction( "ShowError", new {error} );
        }
      }

      return RedirectToAction("Library", new { login });
    }


    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult AddTalents(string login)
    {
      #region Locale permission check

      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal) User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      #endregion

      ViewData["login"] = login;

      var models = AccountSvc
        .GetTalentsCatalog()
        .Select(t => new TalentAddModel
                       {
                         Count = 0,
                         Rarity = t.Rarity,
                         TalentClassId = t.TalentClassId,
                         TalentName = t.TalentName
                       }).ToList();

      return View(models);
    }


    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult AddTalents(string login, IEnumerable<TalentAddModel> model)
    {
      #region Locale permission check

      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal) User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      #endregion

      var talentsToAdd = new List<int>();
      foreach (var m in model.Where(m => m.Count > 0))
        for (int i = 0; i < m.Count; i++)
          talentsToAdd.Add(m.TalentClassId);

      error = AccountSvc.UnlockTalents(login, 0, talentsToAdd.ToArray(), User.Identity.Name);
      if (!String.IsNullOrEmpty(error))
        return RedirectToAction("ShowError", new { error });

      return RedirectToAction("Library", new { login });
    }


    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult Buildings(long auid)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["auid"] = auid;
      
      var models = AccountSvc.GetAccountBuildings(auid);
      if (models == null)
        return RedirectToAction("ShowError", new { error = "Failed to get buildings list"});

      return View(models);
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult DeleteBuilding(long auid, long instanceId)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      error = AccountSvc.DeleteBuilding(auid, instanceId, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", new {error});

      return RedirectToAction("Buildings", new {auid});
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult MoveBuilding(long auid, long instanceId)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      error = AccountSvc.MoveBuildingToStorage(auid, instanceId, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", new {error});

      return RedirectToAction("Buildings", new {auid});
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult AddBuilding(long auid)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      var model = new BuildingAddModel(auid);
      ViewData["allbuildings"] = CastleBuildingsCatalog.GetSelectList();
      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult AddBuilding(BuildingAddModel model)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, model.Auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      var allbuildings = CastleBuildingsCatalog.GetAll();
      if (!allbuildings.Exists(b => b.Id == model.ClassId))
        ModelState.AddModelError("ClassId", "Incorrect classsid value = " + model.ClassId);
      else
      {
        int maxlevel = allbuildings.Single(b => b.Id == model.ClassId).MaxLevel;
        if (model.Level < 1 || model.Level > maxlevel)
          ModelState.AddModelError("Level", "Level should be in range 1.." + maxlevel);
      }

      if (ModelState.IsValid)
      {
        error = AccountSvc.AddBuilding(model.Auid, model.ClassId, model.Level, User.Identity.Name);
        if (error != null)
          return RedirectToAction("ShowError", new {error});

        return RedirectToAction("Buildings", new {model.Auid});
      }

      ViewData["allbuildings"] = CastleBuildingsCatalog.GetSelectList();
      return View(model);
    }

      private void FillQuestsForTalentsViewModel(QuestsForTalentsModel model, string login)
      {
          var quests = AccountSvc.GetQuestsForTalentsByAuid(login).QuestsForTalentsInfo;
          model.items = quests.Select(q => new QuestForTalentModel
          {
              QuestId = q.QuestId,
              StartTime = q.StartTime.FromUnixTimestamp(),
              EndTime = q.EndTime.FromUnixTimestamp(),
              CurrentObjectiveValue = q.CurrentObjectiveValue,
              ShardsSpent = q.ShardsSpent,
              TalentAwardPersistentId = q.TalentAwardPersistentId,
              TalentAwardName = q.TalentAwardName,
              CurrentObjectiveData = q.CurrentObjectiveData,
              FullDynamicQuestDump = q.FullDynamicQuestInfo,
              ObjectiveId = q.CurrentObjectiveId,
              AwardId = q.CurrentAwardId,
              TotalObjectiveData = q.TotalObjectiveData,
              Reason = q.Reason
          }).ToList();
      }

      
      [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
      public ActionResult QuestsForTalents(long auid, string login)
      {
          string error;
          if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
          {
              if (!String.IsNullOrEmpty(error))
                  return RedirectToAction("ShowError", new { error });
              return View("Forbidden");
          }

          var model = new QuestsForTalentsModel();

          FillQuestsForTalentsViewModel(model, login);
          model.Login = login;
          model.Auid = auid;

          return View(model);
      }

      [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
      public ActionResult EditQuestForTalent(long auid, string login, int questNumber)
      {
          string error;
          if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
          {
              if (!String.IsNullOrEmpty(error))
                  return RedirectToAction("ShowError", new { error });
              return View("Forbidden");
          }


          var model = new QuestsForTalentsModel();

          FillQuestsForTalentsViewModel(model, login);
          ViewData["Login"] = login;
          ViewData["Auid"] = auid;

          return View(model.items[questNumber]);
      }

      [HttpPost]
      [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
      public ActionResult EditQuestForTalent(QuestForTalentModel edit, string login, long auid)
      {          
          string error;
          if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, edit.Auid, out error))
          {
              if (!String.IsNullOrEmpty(error))
                  return RedirectToAction("ShowError", new { error });
              return View("Forbidden");
          }

          string errorIfExistToShow = AccountSvc.EditQuestForTalent(login, edit, User.Identity.Name);
          if (errorIfExistToShow != null)
              return RedirectToAction("ShowError", new { error = errorIfExistToShow });

          return RedirectToAction("QuestsForTalents", new { auid, login });
      }

    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult EditAccount( long auid )
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      var model = AccountSvc.GetAccountByAuid(auid);
      if (model.ErrorIfExistToShow != null)
        return RedirectToAction("ShowError", new { error = model.ErrorIfExistToShow });
      if (String.IsNullOrEmpty(model.Login))
        return RedirectToAction("ShowError", new { error = "Server returned wrong Login" });

      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult EditAccount( AccountInfoModel edit )
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, edit.Auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if ( ModelState.IsValid )
      {
        string errorIfExistToShow = AccountSvc.EditAccount( edit, User.Identity.Name );
        if ( errorIfExistToShow != null )
          return RedirectToAction( "ShowError", new { error = errorIfExistToShow } );

        string errorIfExistEditFree = null;
        if ( ( edit.SwitchQuant != edit.HiddenSwitchQuant ) || ( edit.NickChangesQuant != edit.HiddenNickChanges ) )
          errorIfExistEditFree = AccountSvc.EditFreeChanges( edit.Login, User.Identity.Name, ( edit.MaxNickChangesQuant - edit.NickChangesQuant ), ( edit.MaxFractionChangesQuant - edit.SwitchQuant ) );
        if ( errorIfExistEditFree != null )
          return RedirectToAction( "ShowError", new { error = "in EditFreeChanges : " + errorIfExistEditFree } );

        string errorIfExistNickname = null;
        if (edit.NickName != edit.HiddenNickName)
          errorIfExistNickname = AccountSvc.EditNickname(edit.Login, User.Identity.Name, edit.NickName);
        if (errorIfExistNickname != null)
          return RedirectToAction("ShowError", new { error = "in EditNickName : " + errorIfExistNickname });

        if (!String.IsNullOrEmpty(edit.MessageToUser))
        {
          var trimmedMessage = edit.MessageToUser.Trim();
          if (trimmedMessage.Length > 1)
          {
            // заголовок сообщения всё равно не показывается в замке
            string errorIfExistSendMessage = AccountSvc.SendMessageToUser(edit.Auid, edit.Login, string.Empty,
              trimmedMessage, User.Identity.Name);
            if (errorIfExistSendMessage != null)
              return RedirectToAction("ShowError", new {error = errorIfExistSendMessage});
          }
        }
      }
      else
      {
        var errors = ModelState
          .Where(pair => pair.Value.Errors.Count > 0)
          .Select(pair => String.Format("ModelState[{0}].Value='{1}',error={2}", pair.Key, pair.Value.Value.AttemptedValue,
                                        String.Join(",", pair.Value.Errors.Select(e => e.ErrorMessage).ToArray())));
        _log.DebugFormat("AccountInfoModel errors: {0}", String.Join(";", errors.ToArray()));
        if (edit.JoinedSNids == null) edit.JoinedSNids = new List<string>(0);
        return View(edit);
      }

      return RedirectToAction("Details", new {edit.Login});
    }

    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult LockHero( string login, long heroInstanceId )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if ( Request.HttpMethod == "GET" )
      {
        string errorIfExistToShow = AccountSvc.LockHero( login, heroInstanceId, User.Identity.Name );
        if ( errorIfExistToShow != null )
          return RedirectToAction( "ShowError", new { error = errorIfExistToShow } );
      }
      return RedirectToAction( "Heroes", new { login } );
    }

    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult EditHero( string login, string heroName, HeroInfoModel edit )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      ViewData["heroName"] = heroName;
      ViewData["noNeedToShowEditResult"] = 1;
      if ( Request.HttpMethod == "POST" )
      {
        if ( ModelState.IsValid )
        {
          string errorIfExistToShow = AccountSvc.EditHero( login, edit, User.Identity.Name );
          if ( errorIfExistToShow != null )
            return RedirectToAction( "ShowError", new { error = errorIfExistToShow } );
          ViewData["noNeedToShowEditResult"] = 0;
        }
      }
      return View();
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult EditSeasonAwards(string login, SeasonAwardsModel edit)
    {
        string snid, snuid, error;
        GetSNDataFromLogin(login, out snid, out snuid);
        if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
        {
            if (!String.IsNullOrEmpty(error))
                return RedirectToAction("ShowError", new { error });
            return View("Forbidden");
        }


        ViewData["login"] = login;
        ViewData["seasonName"] = edit.SeasonName;
        ViewData["noNeedToShowEditResult"] = 1;
        if (Request.HttpMethod == "POST")
        {
            if (ModelState.IsValid)
            {
                string errorIfExistToShow = AccountSvc.EditSeasonAwards(login, edit, User.Identity.Name);
                if (errorIfExistToShow != null)
                    return RedirectToAction("ShowError", new { error = errorIfExistToShow });
                ViewData["noNeedToShowEditResult"] = 0;
            }
        }
        return View();
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult EditSeasonInfo(string login, long heroInstanceId, string heroName, SeasonInfoModel edit)
    {
        string snid, snuid, error;
        GetSNDataFromLogin(login, out snid, out snuid);
        if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
        {
            if (!String.IsNullOrEmpty(error))
                return RedirectToAction("ShowError", new { error });
            return View("Forbidden");
        }


        ViewData["login"] = login;
        ViewData["seasonName"] = edit.SeasonName;
        ViewData["heroInstanceId"] = heroInstanceId;
        ViewData["heroName"] = heroName;
        ViewData["noNeedToShowEditResult"] = 1;
        if (Request.HttpMethod == "POST")
        {
            if (ModelState.IsValid)
            {
                string errorIfExistToShow = AccountSvc.EditSeasonInfo(login, heroInstanceId, edit, User.Identity.Name);
                if (errorIfExistToShow != null)
                    return RedirectToAction("ShowError", new { error = errorIfExistToShow });
                ViewData["noNeedToShowEditResult"] = 0;
            }
        }
        return View();
    }


    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult EditTalent(string login, long talentInstanceId, string cameFrom, int? heroInstanceId, string heroName)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;

      GetTalentInfoListResp alltalents;
      if (cameFrom == "TalentSet")
      {
        ViewData["cameFrom"] = cameFrom;
        ViewData["heroInstanceId"] = heroInstanceId;
        ViewData["heroName"] = heroName;

        if (!heroInstanceId.HasValue)
          throw new ArgumentException("hero id cannot be null", "heroInstanceId");
        alltalents = AccountSvc.GetHeroTalentSet(login, heroInstanceId.Value);
      }
      else
      {
        alltalents = AccountSvc.GetAccountLibrary(login);
      }
      if (alltalents == null)
        return RedirectToAction("ShowError", new {error = "Can't find talents for " + login});

      var allheroes = new List<HeroInfoModel> { new HeroInfoModel {HeroName = "NONE"}};
      var heroesResp = AccountSvc.GetAccountHeroes(login);
      if (!String.IsNullOrEmpty(heroesResp.ErrorIfExistToShow))
        return RedirectToAction("ShowError", new {error = heroesResp.ErrorIfExistToShow});
      allheroes.AddRange(heroesResp.heroesList);
      ViewData["allheroes"] = allheroes;

      var model = new TalentInfoModel();
      try
      {
        model = alltalents.talentsList.Single(t => t.TalentInstanceId == talentInstanceId);
      }
      catch (InvalidOperationException)
      {
        const string localRedirectAction = "Library";
        const string localRedirectController = "Account";
        var localRedirectRoutes = new RouteValueDictionary
        {
          {"area", ControllerContext.RouteData.DataTokens["area"]},
          {"login", login}
        };
        return View("Warning", new WarningModel
        {
          Message = "Talent doesn't exists.",
          Action = localRedirectAction,
          Controller = localRedirectController,
          RedirectRoute = localRedirectRoutes,
          RedirectUrl = ""
        });
      }
      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult EditTalent(string login, TalentInfoModel editTalent, string cameFrom, int? heroInstanceId, string heroName)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      if (cameFrom == "TalentSet")
      {
        ViewData["cameFrom"] = cameFrom;
        ViewData["heroInstanceId"] = heroInstanceId;
        ViewData["heroName"] = heroName;
      }

      if (ModelState.IsValid)
      {
        string errorIfExistToShow = AccountSvc.EditTalent(login, editTalent, User.Identity.Name);
        if (errorIfExistToShow != null)
          return RedirectToAction("ShowError", new {error = errorIfExistToShow});

        if (cameFrom == "TalentSet")
          return RedirectToAction("TalentSet", new {login, heroInstanceId, heroName});

        return RedirectToAction("Library", new {login});
      }

        var errors = ModelState
          .Where( pair => pair.Value.Errors.Count > 0 )
          .Select( pair => String.Format( "ModelState[{0}].Value='{1}',error={2}", pair.Key, pair.Value.Value.AttemptedValue,
                                        String.Join( ",", pair.Value.Errors.Select( e => e.ErrorMessage ).ToArray() ) ) );
        _log.DebugFormat( "EditTalent errors: {0}", String.Join( ";", errors.ToArray() ) );
        var allheroes = new List<HeroInfoModel> { new HeroInfoModel { HeroName = "NONE" } };
        var heroesResp = AccountSvc.GetAccountHeroes( login );
        if ( !String.IsNullOrEmpty( heroesResp.ErrorIfExistToShow ) )
          return RedirectToAction( "ShowError", new { error = heroesResp.ErrorIfExistToShow } );
        allheroes.AddRange( heroesResp.heroesList );
        ViewData["allheroes"] = allheroes;
        return View( editTalent );
    }

    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult MoveSetToLib( string login, long heroInstanceId, long talentInstanceId, string heroName )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if ( Request.HttpMethod == "GET" )
      {
        string errorIfExistToShow = AccountSvc.MoveTalentFromTalentSetToLibrary( login, heroInstanceId, talentInstanceId, User.Identity.Name );
        if ( errorIfExistToShow != null )
          return RedirectToAction( "ShowError", new { error = errorIfExistToShow } );
      }
      return RedirectToAction( "TalentSet", new { login, heroInstanceId, heroName } );
    }

    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult RemoveFromSet( string login, long heroInstanceId, long talentInstanceId, int talentSetId, string heroName )
    {
      string snid, snuid, error;
      GetSNDataFromLogin( login, out snid, out snuid );
      if ( !AccountSvc.CheckLocalePermissionBySNUid( (GMToolsPrincipal)User, snid, snuid, out error ) )
      {
        if ( !String.IsNullOrEmpty( error ) )
          return RedirectToAction( "ShowError", new { error } );
        return View( "Forbidden" );
      }

      if ( Request.HttpMethod == "GET" )
      {
        string errorIfExistToShow = AccountSvc.RemoveTalentFromTalentSet( login, heroInstanceId, talentInstanceId, talentSetId, User.Identity.Name );
        if ( errorIfExistToShow != null )
          return RedirectToAction( "ShowError", new { error = errorIfExistToShow } );
      }
      return RedirectToAction( "TalentSet", new { login, heroInstanceId, heroName } );
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult DisjointSN(long auid, string sn)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      error = AccountSvc.DisjointSN(auid, sn);
      if (!String.IsNullOrEmpty(error))
        return RedirectToAction("ShowError", new { error });
      return RedirectToAction("EditAccount", new { auid });
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult ChangeFSN( long auid, string sn )
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      error = AccountSvc.ChangeFSN( auid, sn );
      if (!String.IsNullOrEmpty(error))
        return RedirectToAction("ShowError", new { error });
      return RedirectToAction("EditAccount", new { auid });
    }    


    [AuthorizeWithPermission( Permission = "GM_AccountSendMessage" )]
    public ActionResult SendMessageUser( long auid, string login )
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      ViewData["noNeedToShowResult"] = 1;

      SendMessageModel sm = new SendMessageModel();
      if ( Request.HttpMethod == "POST" )
      {
        if ( TryUpdateModel( sm ) )
        {
          string errorIfExistToShow = AccountSvc.SendMessageToUser( auid, login, sm.MessageTitle, sm.MessageText, User.Identity.Name );
          if ( errorIfExistToShow != null )
            return RedirectToAction( "ShowError", "Account", new { error = errorIfExistToShow } );
          ViewData["noNeedToShowResult"] = 0;
        }
      }
      return View( sm );
    }


    [AuthorizeWithPermission(Permission = "GM_AccountBanMute")]
    public ActionResult UserOperation(string op, long? auid, bool? negative, string returnUrl)
    {
      if (auid.HasValue)
      {
        string error;
        if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid.Value, out error))
        {
          if (!String.IsNullOrEmpty(error))
            return RedirectToAction("ShowError", new { error });
          return View("Forbidden");
        }
      }

      // check for valid operation
      UserOperationType operation;
      try
      {
        operation = (UserOperationType)Enum.Parse(typeof(UserOperationType), op, true);
      }
      catch (Exception ex)
      {
        return View("Error", new HandleErrorInfo(new Exception("Invalid operation = " + op, ex), "Account", "UserOperation"));
      }

      // create a model
      var model = new UserOperationModel { Type = operation, Negative = negative ?? false };

      // set a return url
      ViewData["returnUrl"] = returnUrl;


      if (!auid.HasValue)
        return View("Error", new HandleErrorInfo(new Exception("auid can't be null"), "Account", "UserOperation"));

      // if operation with a single account
      var accountModel = AccountSvc.GetAccountByAuid(auid.Value);
      if (!String.IsNullOrEmpty(accountModel.ErrorIfExistToShow))
        return RedirectToAction("ShowError", "Account", new { error = accountModel.ErrorIfExistToShow });

      // no need to show the form for Unban/Unmute operation
      if (operation == UserOperationType.Unban || operation == UserOperationType.Unmute)
      {
        var nonExistingAuids = new List<Int64>();
        var error = AccountSvc.UserOperation(auid.Value, operation, 0, null, null, User.Identity.Name, null);
        if (error != RequestResult.Success)
        {
          if (error == RequestResult.AuidNotExist)
          {
            nonExistingAuids.Add(auid.Value);
          }
          else
          {
            var errorText = AccountService.GetVerboseErrorMessage(error);
            if (!String.IsNullOrEmpty(errorText))
              return View("Error", new HandleErrorInfo(new Exception(errorText), "Account", "UserOperation"));
          }
        }
        // I don't think it's possible
        if (nonExistingAuids.Count > 0)
        {
          const string localRedirectAction = "Details";
          const string localRedirectController = "Account";
          var localRedirectRoutes = new RouteValueDictionary
          {
            {"area", ControllerContext.RouteData.DataTokens["area"]},
            {"auid", auid}
          };
          return View("Warning", new WarningModel
          {
            Message = "Some auid was not found: "
                      + String.Join(", ", nonExistingAuids.Select(x => x.ToString(CultureInfo.InvariantCulture)).ToArray())
                      + ". Maybe they were merged with another auids.",
            Action = localRedirectAction,
            Controller = localRedirectController,
            RedirectRoute = localRedirectRoutes,
            RedirectUrl = ""
          });
        }
        return RedirectToAction("Details", new { auid });
      }

      // fill the model and show the form otherwise
      var userinfo = new UserOperationModel.UserInfo {Auid = auid.Value, Nickname = accountModel.NickName, Complaints = 0};
      model.Users = new List<UserOperationModel.UserInfo> {userinfo};
      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountBanMute")]
    public ActionResult UserOperation(string[] selected, string op, string returnUrl)
    {
      // check for valid operation
      UserOperationType operation;
      try
      {
        operation = (UserOperationType)Enum.Parse(typeof(UserOperationType), op, true);
      }
      catch (Exception ex)
      {
        return View("Error", new HandleErrorInfo(new Exception("Invalid operation = " + op, ex), "Account", "UserOperation"));
      }
      // create a model
      var model = new UserOperationModel { Type = operation };

      // set a return url
      ViewData["returnUrl"] = returnUrl;

      // if redirect from Complaint.GroupOperation
      if (selected == null) return View("Warning", new WarningModel
      {
        Message = "No Player was chosen for operation.",
        Action = "",
        Controller = "",
        RedirectRoute = new RouteValueDictionary(),
        RedirectUrl = returnUrl
      });
      // fill the model from "selectedPlayers" array
      model.Users = new List<UserOperationModel.UserInfo>();
      foreach (string p in selected)
      {
        // stupid splitting of format ID_NICKNAME_COMPLAINTSCOUNT
        // (we can't use String.Split, because NICKNAME can contain '_' chars)
        model.Users.Add(new UserOperationModel.UserInfo
        {
          Auid = Int64.Parse(p.Substring(0, p.IndexOf('_'))),
          Nickname = p.Substring(p.IndexOf('_') + 1, p.LastIndexOf('_') - p.IndexOf('_') - 1),
          Complaints = Int32.Parse(p.Substring(p.LastIndexOf('_') + 1, p.Length - p.LastIndexOf('_') - 1))
        });
      }
      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountBanMute")]
    public ActionResult ApplyOperation(UserOperationModel model, string returnUrl)
    {
      // Проверка на возможность выполнения операции со всеми пользователями
      string error;
      foreach (var user in model.Users)
      {
        if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, user.Auid, out error))
        {
          if (!String.IsNullOrEmpty(error))
            return RedirectToAction("ShowError", new { error });
          return View("Forbidden");
        }
      }

      if (model.Type != UserOperationType.Ban && model.Type != UserOperationType.Mute &&
          model.Type != UserOperationType.Forgive && model.Type != UserOperationType.SetLeave)
        return View("Error", new HandleErrorInfo(new Exception("Invalid operation " + model.Type), "Account", "UserOperation"));

      if (!ModelState.IsValid)
        return View("UserOperation", model);

      var nonExistingAuids = new List<Int64>();
      try
      {
        
        foreach (var user in model.Users)
        {
          List<int> complaintIds = null;
          List<long> complaintAuids = null;
          if (user.Complaints > 0)
          {
            var complaintInfos = ComplaintService.GetComplaintsForPlayer(user.Auid, user.Nickname, (GMToolsPrincipal)User);
            complaintIds = complaintInfos.Select(c => c.Id).ToList();
            complaintAuids = complaintInfos.Select(c => c.FromPlayerAuid).Distinct().ToList();
          }

          var errorCode = AccountSvc.UserOperation(user.Auid, model.Type, model.Negative ? -model.Value : model.Value, model.Reason, complaintIds, User.Identity.Name, complaintAuids);
          if (errorCode != RequestResult.Success)
          {
            if (errorCode == RequestResult.AuidNotExist)
            {
              nonExistingAuids.Add(user.Auid);
            }
            else
            {
              var errorText = AccountService.GetVerboseErrorMessage(errorCode);
              if (!String.IsNullOrEmpty(errorText))
                return View("Error", new HandleErrorInfo(new Exception(errorText), "Account", "UserOperation"));
            }
          }
        }
      }
      catch (Exception ex)
      {
        return View("Error", new HandleErrorInfo(ex, "Account", "UserOperation"));
      }

      var localRedirectLink = String.IsNullOrEmpty(returnUrl) ? "" : returnUrl;
      const string localRedirectAction = "Overview";
      const string localRedirectController = "Complaint";
      var localRedirectRoutes = new RouteValueDictionary
      {
        {"area", ControllerContext.RouteData.DataTokens["area"]},
      };

      if (nonExistingAuids.Count > 0)
      {
        return View("Warning", new WarningModel
        {
          Message = "Some auids were not found: "
                    + String.Join(", ", nonExistingAuids.Select(x => x.ToString(CultureInfo.InvariantCulture)).ToArray())
                    + ". Maybe they were merged with another auids.",
          Action = localRedirectAction,
          Controller = localRedirectController,
          RedirectRoute = localRedirectRoutes,
          RedirectUrl = localRedirectLink
        });
      }
      if (!String.IsNullOrEmpty(localRedirectLink))
      {
        return Redirect(localRedirectLink);
      }
      return RedirectToAction(localRedirectAction, localRedirectController, localRedirectRoutes);
    }


    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult ResetUser( string login )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      string errorIfExistToShow = AccountSvc.ResetUserAccount( login, User.Identity.Name );
      if ( errorIfExistToShow != null )
        return RedirectToAction( "ShowError", "Account", new { error = errorIfExistToShow } );
      return RedirectToAction( "Details", new { login } );
    }

    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult ActivateEmail( string login, string email )
    {
      string snid, snuid, error;
      GetSNDataFromLogin( login, out snid, out snuid );
      if ( !AccountSvc.CheckLocalePermissionBySNUid( (GMToolsPrincipal)User, snid, snuid, out error ) )
      {
        if ( !String.IsNullOrEmpty( error ) )
          return RedirectToAction( "ShowError", new { error } );
        return View( "Forbidden" );
      }

      string errorIfExistToShow = AccountSvc.ActivateEmail( email, User.Identity.Name );
      if ( errorIfExistToShow != null )
        return RedirectToAction( "ShowError", "Account", new { error = errorIfExistToShow } );
      return RedirectToAction( "Details", new { login } );
    }

    [AuthorizeWithPermission( Permission = "GM_AccountKick" )]
    public ActionResult KickUser( string login )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      string errorIfExistToShow = AccountSvc.KickUser( login, User.Identity.Name );
      if ( errorIfExistToShow != null )
        return RedirectToAction( "ShowError", "Account", new { error = errorIfExistToShow } );
      return RedirectToAction( "Details", new { login } );
    }


    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult RefreshHeroesCatalog( string login )
    {
      HeroesCatalog.RefreshHeroesCatalog();
      return RedirectToAction( "Heroes", new { login } );
    }


    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult RefreshTalentsCatalog( string login )
    {
      TalentsCatalog.RefreshTalentsCatalog();
      return RedirectToAction( "Library", new { login } );
    }


    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult GetFullUserDump( string login )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      StringUIResponse uiResp = AccountSvc.GetFullUserDump( login, false );
      if ( uiResp.ErrorIfExistToShow != null )
        return RedirectToAction( "ShowError", "Account", new { error = uiResp.ErrorIfExistToShow } );
      return File( Encoding.ASCII.GetBytes ( uiResp.Data ),
                 "text/plain", string.Format( "{0}.pwdump", login ) );
    }


    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult ApplyUserDump( string login )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      ViewData["noNeedToShowResult"] = 1;
      if ( Request.HttpMethod == "POST" )
      {
        HttpPostedFileBase file = Request.Files["dumpUpload"];
        if ( !( file != null && file.ContentLength > 0 ) )
          return RedirectToAction( "ShowError", "Account", new { error = "Dump file doesn't exist or is empty" } );
        
        byte[] input = new byte[file.ContentLength];
        Stream stream = file.InputStream;
        stream.Read( input, 0, file.ContentLength );
        string dump = Encoding.ASCII.GetString( input );
        string errorIfExistToShow = AccountSvc.ApplyFullUserDump( login, dump );
        if ( errorIfExistToShow != null )
          return RedirectToAction( "ShowError", "Account", new { error = errorIfExistToShow } );
        ViewData["noNeedToShowResult"] = 0;
      }
      return View();
    }


    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult RemoveFakeAuid( string login )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      string errorIfExistToShow = AccountSvc.RemoveFakeAuid( login );
      if ( errorIfExistToShow != null )
        return RedirectToAction( "ShowError", "Account", new { error = errorIfExistToShow } );
      return RedirectToAction( "Details", new { login } );
    }


    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult CheckAccountValidity( string login )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      ViewData["noNeedToShowResult"] = 1;
      if ( Request.HttpMethod == "GET" )
      {
        StringUIResponse uiResp = AccountSvc.CheckAccountValidity( login );
        if ( uiResp.ErrorIfExistToShow != null )
          return RedirectToAction( "ShowError", new { error = uiResp.ErrorIfExistToShow } );
        if ( uiResp.Data == null )
          uiResp.Data = "Account is OK";
        ViewData["checkResult"] = uiResp.Data;
      }
      if ( Request.HttpMethod == "POST" )
      {
        string errorIfExistToShow = AccountSvc.FixAccount( login, User.Identity.Name );
        if ( errorIfExistToShow != null )
          return RedirectToAction( "ShowError", "Account", new { error = errorIfExistToShow } );
        return RedirectToAction( "CheckAccountValidity", "Account", new { login } );
      }
      return View();
    }


    [AuthorizeWithPermission(Permission = "GM_PayOperation")]
    public ActionResult PayEditNickname(string login)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if (String.IsNullOrEmpty(login))
        return RedirectToAction("ShowError", new { error = "Empty login value" });
      return View(new PayEditNicknameModel {Login = login});
    }


    [AuthorizeWithPermission(Permission = "GM_PayOperation")]
    [HttpPost]
    public ActionResult PayEditNickname(PayEditNicknameModel model)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(model.Login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if (ModelState.IsValid)
      {
        error = AccountSvc.PayEditNickname(model.Login, model.Nickname);
        if (error == null)
        {
          return RedirectToAction("Details", new { login = model.Login });
        }
        ModelState.AddModelError(String.Empty, error);
      }
      return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_PayOperation")]
    public ActionResult PayChangeFaction(string login)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if (String.IsNullOrEmpty(login))
        return RedirectToAction("ShowError", new { error = "Empty login value" });
      return View(new PayChangeFactionModel { Login = login });
    }


    [AuthorizeWithPermission(Permission = "GM_PayOperation")]
    [HttpPost]
    public ActionResult PayChangeFaction(PayChangeFactionModel model)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(model.Login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if (ModelState.IsValid)
      {
        error = AccountSvc.PayChangeFraction(model.Login, (int)model.NewFaction);
        if (error == null)
        {
          return RedirectToAction("Details", new { login = model.Login });
        }
        ModelState.AddModelError(String.Empty, error);
      }
      return View(model);
    }


    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult LampInfo( string login )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      if ( String.IsNullOrEmpty( login ) )
        return RedirectToAction( "ShowError", new { error = "Empty login value" } );

      LampInfoResponse resp = AccountSvc.GetLampInfo( login );
      if ( resp.Result != RequestResult.Success )
        return RedirectToAction( "ShowError", new { error = resp.Result } );
      LampInfoModel model = new LampInfoModel();
      model.Bonus = resp.LampInfo.Bonus;
      model.Gold = resp.LampInfo.GoldBonus;
      model.Transaction = resp.LampInfo.Transaction;
      model.Duration = resp.LampInfo.Duration;
      return View( model );
    }


    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    [HttpPost]
    public ActionResult LampInfo( LampInfoModel model )
    {
      string snid, snuid, error;
      GetSNDataFromLogin(model.Login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if ( ModelState.IsValid )
      {
        error = AccountSvc.GiveLamp( model.Login, model.Bonus, model.Gold, model.Transaction, model.Duration, User.Identity.Name );
        if ( error == null )
        {
          return RedirectToAction( "Details", new { login = model.Login } );
        }
        ModelState.AddModelError( String.Empty, error );
      }
      return View( model );
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult UpgradeHeroTalentsInfo(string login)
    {
        string snid, snuid, error;
        GetSNDataFromLogin(login, out snid, out snuid);
        if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
        {
            if (!String.IsNullOrEmpty(error))
                return RedirectToAction("ShowError", new { error });
            return View("Forbidden");
        }

        ViewData["login"] = login;
        if (String.IsNullOrEmpty(login))
            return RedirectToAction("ShowError", new { error = "Empty login value" });

        UpgradeHeroTalentsInfoResponse resp = AccountSvc.GetUpgradeHeroTalentsInfo(login);
        if (resp.Result != RequestResult.Success)
            return RedirectToAction("ShowError", new { error = resp.Result });
        UpgradeHeroTalentsInfoModel model = new UpgradeHeroTalentsInfoModel();
        model.CountRunes = resp.UpgradeHeroTalentsInfo.UsesLeft;
        return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    [HttpPost]
    public ActionResult UpgradeHeroTalentsInfo(UpgradeHeroTalentsInfoModel model)
    {
        string snid, snuid, error;
        GetSNDataFromLogin(model.Login, out snid, out snuid);
        if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
        {
            if (!String.IsNullOrEmpty(error))
                return RedirectToAction("ShowError", new { error });
            return View("Forbidden");
        }

        if (ModelState.IsValid)
        {
            error = AccountSvc.GiveUpgradeHeroTalents(model.Login, model.CountRunes, User.Identity.Name);
            if (error == null)
            {
                return RedirectToAction("Details", new { login = model.Login });
            }
            ModelState.AddModelError(String.Empty, error);
        }
        return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_PayOperation")]
    public ActionResult PayService(string login)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if (String.IsNullOrEmpty(login))
        return RedirectToAction("ShowError", new { error = "Empty login value" });

      var accountInfo = AccountSvc.GetAccountBySNUid(snid, snuid);

      var model = new PayServiceModel { Login = login };
      if (accountInfo.PremiumAccountDate.HasValue && accountInfo.PremiumAccountDate >= DateTime.UtcNow)
        model.PremiumAccountDate = accountInfo.PremiumAccountDate;
      return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_PayOperation")]
    [HttpPost]
    public ActionResult PayService(PayServiceModel model)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(model.Login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if (model.ServiceTypeId != 1 && model.ServiceTypeId != 2)
        ModelState.AddModelError("ServiceTypeId", "Incorrect value = " + model.ServiceTypeId);

      if (ModelState.IsValid)
      {
        if (model.ServiceTypeId == 2) // Если Withdraw - количество дней делаем отрицательным
          model.Days = -model.Days;

        error = AccountSvc.PayService(model.Login, PayServiceType.PremiumAccount, model.Days, User.Identity.Name);
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        
        return RedirectToAction("Details", new { login = model.Login });
      }
      return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_AccountBanMute")]
    public ActionResult Complaints(long auid, string nickname, string locale, string orderby, bool? asc)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      try
      {
        var model = new PlayerComplaintInfosModel(auid, nickname, locale, orderby, asc);
        ComplaintService.FillComplaintsForPlayer(model, (GMToolsPrincipal)User);
        return View(model);
      }
      catch (Exception ex)
      {
        return View("Error", new HandleErrorInfo(ex, "Account", "Complaints"));
      }
    }


    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult TournamentInfo(string login, long auid)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      ViewData["auid"] = auid;
      if (String.IsNullOrEmpty(login))
        return RedirectToAction("ShowError", new { error = "Empty login value" });

      TournamentInfoResponse resp = AccountSvc.GetAccountTournamentInfo(login);
      if (resp.Result != RequestResult.Success)
        return RedirectToAction("ShowError", new { error = resp.Result });
      TournamentInfoModel model = new TournamentInfoModel();
      model.Wins = resp.TournamentInfo.Wins;
      model.Losses = resp.TournamentInfo.Losses;
      model.LastGameTime = resp.TournamentInfo.LastGameTime.FromUnixTimestamp();
      model.TicketPriseState = (TicketPriseStateEnum)resp.TournamentInfo.TicketPriseState;
      model.TicketBoughtType = (TicketBoughtTypeEnum)resp.TournamentInfo.TicketBoughtType;
      model.State = (TicketStateEnum)resp.TournamentInfo.State;
      model.MissedGames = resp.TournamentInfo.MissedGames;
      model.IsSynchronized = resp.TournamentInfo.IsSynchronized;
      return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    [HttpPost]
    public ActionResult TournamentInfo(TournamentInfoModel model)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(model.Login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if (ModelState.IsValid)
      {
        error = AccountSvc.EditTournamentInfo( model.Login, model.Wins, model.Losses, model.LastGameTime.ToUnixTimestamp(), (TicketPriseState)model.TicketPriseState, (TicketState)model.State, (TicketBoughtType)model.TicketBoughtType, model.MissedGames, model.IsSynchronized, User.Identity.Name );
        if (error == null)
        {
          return RedirectToAction("Details", new { login = model.Login });
        }
        ModelState.AddModelError(String.Empty, error);
      }
      return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult TournamentTicketGiven(string login)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      if (String.IsNullOrEmpty(login))
        return RedirectToAction("ShowError", new { error = "Empty login value" });

      GiveTournamentTicketResponse resp = AccountSvc.GiveTournamentTicket(login);
      if (resp.Result != RequestResult.Success)
        return RedirectToAction("ShowError", new { error = resp.Result });
      GiveTournamentTicketModel model = new GiveTournamentTicketModel();
      return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_AccountView")]
    public ActionResult TournamentGames(string login)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      GetTournamentGamesListResp uiResp = AccountSvc.GetAccountTournamentGames(login);
      if (uiResp.ErrorIfExistToShow != null)
        return RedirectToAction("ShowError", new { error = uiResp.ErrorIfExistToShow });
      return View(uiResp.tournamentGamesList);
    }


    [AuthorizeWithPermission(Permission = "GM_AccountView")]
    public ActionResult Quests(long auid)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      var models = AccountSvc.GetQuests(auid, out error);
      if (!String.IsNullOrEmpty(error))
        return RedirectToAction("ShowError", new { error });

      ViewData["auid"] = auid;
      return View(models);
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult QuestChange(long auid, int questid, string act)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      error = AccountSvc.QuestChange(auid, questid, act, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", new { error });

      return RedirectToAction("Quests", new {auid});
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult Flags(string login)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      ViewData["login"] = login;
      GetFlagListResp uiResp = AccountSvc.GetAccountFlags(login);
      if (uiResp.ErrorIfExistToShow != null)
        return RedirectToAction("ShowError", new { error = uiResp.ErrorIfExistToShow });

      ViewData["selPaidFlag"] = uiResp.NotOwnedFlagsList.Select( x => new SelectListItem
                                                                                      {
                                                                                        Value = x.FlagPersistentId,
                                                                                        Text = x.FlagPersistentId,
                                                                                        Selected = false
                                                                                      } );
      ViewData["selAdminFlag"] = uiResp.AdminFlagsList.Select( x => new SelectListItem
                                                                     {
                                                                       Value = x.FlagPersistentId,
                                                                       Text = x.FlagPersistentId,
                                                                       Selected = false
                                                                     } );
      return View(uiResp.OwnedFlagsList);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult Flags(string login, string selPaidFlag, string selAdminFlag)
    {
      string snid, snuid, error;
      string flagId = null;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }
      if (selPaidFlag != null)
      {
        flagId = selPaidFlag;
      }
      else if (selAdminFlag != null)
      {
        flagId = selAdminFlag;
      }

      if (flagId != null)
      {
        string errorIfExistToShow = AccountSvc.UnlockFlag(login, flagId, User.Identity.Name);
        if (errorIfExistToShow != null)
          return RedirectToAction("ShowError", new { error = errorIfExistToShow });
      }
      
      return RedirectToAction("Flags", new { login });
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult LockFlag(string login, string flagPersistentId)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if (Request.HttpMethod == "GET")
      {
        string errorIfExistToShow = AccountSvc.LockFlag(login, flagPersistentId, User.Identity.Name);
        if (errorIfExistToShow != null)
          return RedirectToAction("ShowError", new { error = errorIfExistToShow });
      }
      return RedirectToAction("Flags", new { login });
    }

    [AuthorizeWithPermission(Permission = "GM_AccountLoginHistory")]
    public ActionResult AdminMessages(string login, int? pageNum, int? pageSize)
    {
      string snid, snuid, error;
      GetSNDataFromLogin(login, out snid, out snuid);
      if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal)User, snid, snuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      int pageQuant;
      pageNum = pageNum ?? 1;
      pageSize = pageSize ?? 20;
      ViewData["login"] = login;
      ViewData["CurrentPage"] = pageNum;
      var model = AccountSvc.GetAccountAdminMessages(login, (int)pageNum, (int)pageSize, out pageQuant);
      ViewData["TotalPages"] = pageQuant;
      if (model == null)
        return RedirectToAction("ShowError", "Account", new { error = "DAL returned null or is unaccessible" });
      return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_AccountView")]
    public ActionResult Geolocation(long auid)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      var info = AccountSvc.GetAccountByAuid(auid);
      if (info.ErrorIfExistToShow != null)
        return RedirectToAction("ShowError", new { error = info.ErrorIfExistToShow });

      var model = new GeolocationInfoModel
                    {
                      Auid = auid,
                      Country = info.Country,
                      Region = info.Region,
                      City = info.City,
                      GMCountry = info.GMCountry,
                      GMRegion = info.GMRegion,
                      GMCity = info.GMCity,
                    };

      var allcountries = GeolocationCache.Instance.GetCountries();
      
      if (!String.IsNullOrEmpty(model.Country))
      {
        try
        {
          var country = allcountries.Single(c => c.Code == model.Country);
          model.CountryName = country.Name;
          model.RegionName = GeolocationCache.Instance.GetRegions(country.Id).Single(r => r.Region_code == model.Region).Region_name_en;
        }
        catch (Exception ex)
        {
          model.CountryName = "UNKNOWN";
          model.RegionName = "UNKNOWN";
          _log.Error(ex);
        }
      }

      if (!String.IsNullOrEmpty(model.GMCountry))
      {
        try
        {
          var country = allcountries.Single(c => c.Code == model.GMCountry);
          model.GMCountryName = country.Name;
          model.GMRegionName = GeolocationCache.Instance.GetRegions(country.Id).Single(r => r.Region_code == model.GMRegion).Region_name_en;
        }
        catch (Exception ex)
        {
          model.GMCountryName = "UNKNOWN";
          model.GMRegionName = "UNKNOWN";
          _log.Error(ex);
        }
      }

      return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult ResetGeolocation(long auid)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      error = AccountSvc.ResetGeolocation(auid, User.Identity.Name);
      if (!String.IsNullOrEmpty(error))
        return RedirectToAction("ShowError", new { error });

      return RedirectToAction("Geolocation", new { auid });
    }


    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult BindGeolocation(long auid)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      var info = AccountSvc.GetAccountByAuid(auid);
      if (info.ErrorIfExistToShow != null)
        return RedirectToAction("ShowError", new { error = info.ErrorIfExistToShow });

      var model = new BindGeolocationModel
                    {
                      Auid = auid,
                      Country = info.GMCountry ?? info.Country ?? "RU", // RUSSIA is the best, RUSSIA is default!
                      Region = info.GMRegion ?? info.Region ?? "48",
                      City = info.GMCity ?? info.City ?? "Moscow"
                    };

      var countries = GeolocationCache.Instance.GetCountries();
      if (countries == null || countries.Count == 0)
        return View("Error", new HandleErrorInfo(new Exception("Can't get list of counties"), "Account", "BindGeolocation"));

      ViewData["CountriesList"] = new SelectList(countries, "Code", "Name");

      try
      {
        var regions = GeolocationCache.Instance.GetRegions(countries.Single(s => s.Code == model.Country).Id); 
        ViewData["RegionsList"] = new SelectList(regions, "Region_code", "Region_name_en");
        ViewData["CitiesList"] = new SelectList(regions.Single(r => r.Region_code == model.Region).Cities);
      }
      catch (Exception ex)
      {
        _log.Error(ex);
        return View("Error", new HandleErrorInfo(ex, "Account", "BindGeolocation"));
      }

      return View(model);
    }


    [HttpPost]
    public ActionResult BindGeolocationChangedCountry(string country)
    {
      var countries = GeolocationCache.Instance.GetCountries();
      try
      {
        var regions = GeolocationCache.Instance.GetRegions(countries.Single(s => s.Code == country).Id);
        return Json(regions);
      }
      catch (Exception ex)
      {
        _log.Error(ex);
        return Json("");
      }
    }


    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult BindGeolocation(BindGeolocationModel model)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, model.Auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", new { error });
        return View("Forbidden");
      }

      if (String.IsNullOrEmpty(model.Country) || String.IsNullOrEmpty(model.Region) || String.IsNullOrEmpty(model.City))
        return RedirectToAction("ShowError", new { error = "All geolocation parameters should be set" });

      AccountSvc.BindGeolocation(model.Auid, model.Country, model.Region, model.City, User.Identity.Name);

      return RedirectToAction("Geolocation", new { model.Auid });
    }

    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult Friends( long auid )
    {
      #region Locale permission check

      string error;
      if ( !AccountSvc.CheckLocalePermissionByAuid( (GMToolsPrincipal)User, auid, out error ) )
      {
        if ( !String.IsNullOrEmpty( error ) )
          return RedirectToAction( "ShowError", new { error } );
        return View( "Forbidden" );
      }

      #endregion

      ViewData["auid"] = auid;

      var modelResp = AccountSvc.GetAccountFriends( auid );
      if ( modelResp.ErrorIfExistToShow != null )
        return RedirectToAction( "ShowError", new { error = modelResp.ErrorIfExistToShow } );

      return View( modelResp.Friends );
    }


    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult Friends( long auid, int[] selected )
    {
      #region Locale permission check

      string error;
      if ( !AccountSvc.CheckLocalePermissionByAuid( (GMToolsPrincipal)User, auid, out error ) )
      {
        if ( !String.IsNullOrEmpty( error ) )
          return RedirectToAction( "ShowError", new { error } );
        return View( "Forbidden" );
      }

      #endregion

      if ( selected != null )
      {
        foreach ( var friendAuid in selected )
        {
          error = AccountSvc.RemoveFriend( auid, friendAuid );
          if ( error != null )
            return RedirectToAction( "ShowError", new { error } );
        }
      }

      return RedirectToAction( "Friends", new { auid } );
    }

    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult RemoveFriend( long auid, long friendAuid )
    {
      #region Locale permission check

      string error;
      if ( !AccountSvc.CheckLocalePermissionByAuid( (GMToolsPrincipal)User, auid, out error ) )
      {
        if ( !String.IsNullOrEmpty( error ) )
          return RedirectToAction( "ShowError", new { error } );
        return View( "Forbidden" );
      }

      #endregion

      ViewData["auid"] = auid;

      error = AccountSvc.RemoveFriend( auid, friendAuid );
      if ( error != null )
        return RedirectToAction( "ShowError", new { error } );

      return RedirectToAction( "Friends", new { auid } );
    }

    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult BrokenAccounts()
    {

      var backupResp = AccountSvc.GetBackups();
      if ( backupResp.ErrorIfExistToShow != null )
        return RedirectToAction( "ShowError", new { error = backupResp.ErrorIfExistToShow } );


      ViewData["BackupDates"] = new SelectList(backupResp.BackupDates.OrderByDescending(q =>
      {        
        try
        {
          return DateTime.Parse(q.Split('_')[1]);
        }
        catch 
        {
          return DateTime.MinValue; 
        }
        
      }));

      var model = new BrokenAccountsModel();
      return View( model );
    }


    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult BrokenAccounts( BrokenAccountsModel model )
    {
      #region Locale permission check

      if ( model.Login != null )
      {
        string snid, snuid, error;
        GetSNDataFromLogin(model.Login, out snid, out snuid);
        if (!AccountSvc.CheckLocalePermissionBySNUid((GMToolsPrincipal) User, snid, snuid, out error))
        {
          if (!String.IsNullOrEmpty(error))
            return RedirectToAction("ShowError", new {error});
          return View("Forbidden");
        }
      }

      #endregion

      if(model.Login == null && model.Nickname == null)
      {
        ModelState.AddModelError( "model.Login", "Enter valid Login or Nickname" );
        return View(model);
      }

      StringUIResponse uiResp;
      
      uiResp = model.Nickname == null ? AccountSvc.GetBrokenUserDump( model.Login, model.BackupDate, false ) : AccountSvc.GetBrokenUserDumpByNickname( model.Nickname, model.BackupDate, false );
      
      if ( uiResp.ErrorIfExistToShow != null )
        return RedirectToAction( "ShowError", "Account", new { error = uiResp.ErrorIfExistToShow } );
      return File(Encoding.ASCII.GetBytes(uiResp.Data),
                  "text/plain", string.Format("{0}.pwdump", model.Login));
          
    }

    public ActionResult ShowError( string error )
    {
      ViewData["errorMessage"] = error;
      return View();
    }

    private void GetSNDataFromLogin( string login, out string sn, out string snuid )
    {
      try
      {
        string[] ar = login.Split( '#' );
        sn = ar[0];
        snuid = ar[1];
      }
      catch
      {
        throw new Exception( "login is in format impossible convert to <sn, snuid>" );
      }
    }


    private class LambdaComparer<T> : IEqualityComparer<T>
    {
      private readonly Func<T, T, bool> _lambdaComparer;
      private readonly Func<T, int> _lambdaHash;
      public LambdaComparer( Func<T, T, bool> lambdaComparer )
        : this( lambdaComparer, o => 0 )
      {
      }
      public LambdaComparer( Func<T, T, bool> lambdaComparer, Func<T, int> lambdaHash )
      {
        if ( lambdaComparer == null )
          throw new ArgumentNullException( "lambdaComparer" );
        if ( lambdaHash == null )
          throw new ArgumentNullException( "lambdaHash" );
        _lambdaComparer = lambdaComparer;
        _lambdaHash = lambdaHash;
      }
      public bool Equals( T x, T y )
      {
        return _lambdaComparer( x, y );
      }
      public int GetHashCode( T obj )
      {
        return _lambdaHash( obj );
      }
    }
  }
}
