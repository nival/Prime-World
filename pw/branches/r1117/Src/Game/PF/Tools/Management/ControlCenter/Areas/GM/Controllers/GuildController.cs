using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Web.Mvc;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Controllers
{
  public class GuildController : Controller
  {
    public IGuildService GuildSvc { get; set; }
    public IAccountService AccountSvc { get; set; }

    protected override void Initialize( System.Web.Routing.RequestContext requestContext )
    {
      base.Initialize( requestContext );

      if ( GuildSvc == null )
        GuildSvc = new GuildService();

      if (AccountSvc == null)
        AccountSvc = new AccountService();
    }

    [HttpGet]
    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult Search()
    {
      return View();
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult Search( GuildSearchModel model )
    {
      if ( Request.Form.ToString().Contains( "searchById" ) )
      {
        if ( model.GuildId == null )
          ModelState.AddModelError( "GuildId", "GuildId is required" );
        else
          return RedirectToAction( "Details", new { id = model.GuildId } );
      }
      if ( Request.Form.ToString().Contains( "searchByName" ) )
      {
        if ( String.IsNullOrEmpty( model.ShortName ) && String.IsNullOrEmpty( model.FullName ) )
        {
          ModelState.AddModelError( "ShortName", "At least one of the search criterias is required" );
          ModelState.AddModelError( "FullName", "At least one of the search criterias is required" );
        }
        else
          return RedirectToAction( "Details", new { shortname = model.ShortName, fullname = model.FullName } );
      }
      return View( model );
    }

    [HttpGet]
    [AuthorizeWithPermission( Permission = "GM_AccountView" )]
    public ActionResult Details( long? id, string shortname, string fullname )
    {
      GuildInfoModel model;
      if ( id.HasValue )
      {
        model = GuildSvc.GetGuildInfoById( id.Value );
        if ( model.Error != null )
          return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + model.Error } );
      }
      else
      {
        model = GuildSvc.GetGuildInfoByName( shortname, fullname );
        if ( model.Error != null )
          return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + model.Error } );
      }

      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, model.LeaderAuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      return View( model );
    }

    [HttpGet]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult Edit( long id )
    {
      var infomodel = GuildSvc.GetGuildInfoById( id );
      if ( infomodel.Error != null )
        return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + infomodel.Error } );

      var editmodel = new GuildEditModel
                        {
                          GuildId = infomodel.GuildId,
                          ShortName = infomodel.ShortName,
                          FullName = infomodel.FullName,
                          MessageOfTheDay = infomodel.MessageOfTheDay,
                          GuildExperience = infomodel.GuildExperience,
                          CWPoints = infomodel.CWPoints,
                          GuildRating = infomodel.CWRating
                        };

      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, infomodel.LeaderAuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      return View( editmodel );
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult Edit( GuildEditModel model )
    {
      if ( ModelState.IsValid )
      {
        var error = GuildSvc.EditGuild(model, User.Identity.Name);
        if ( error != null )
          return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + error } );

        return RedirectToAction( "Details", new { id = model.GuildId } );
      }
      return View( model );
    }

    [HttpGet]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult ViewMembers( long id )
    {
      var infomodel = GuildSvc.GetGuildInfoById( id );
      if ( infomodel.Error != null )
        return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + infomodel.Error } );

      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, infomodel.LeaderAuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      return View( infomodel );
    }

    [HttpGet]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult EditMember(long guildid, long auid)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      var infomodel = GuildSvc.GetGuildMemberById(guildid, auid);
      if (infomodel.Error != null)
        return RedirectToAction("ShowError", "Account", new { error = "Server returned an error: " + infomodel.Error });

      return View(infomodel);
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult EditMember(GuildMemberModel model)
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, model.Auid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      error = GuildSvc.EditMember( model.GuildId, model, User.Identity.Name );
      if ( error != null )
        return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + error } );

      return RedirectToAction( "Details", new { id = model.GuildId } );
    }

    [HttpGet]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult RemoveMembers( long id )
    {
      var infomodel = GuildSvc.GetGuildInfoById( id );
      if ( infomodel.Error != null )
        return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + infomodel.Error } );

      return View( new GuildRemoveMembersModel
                    {
                      GuildId = infomodel.GuildId,
                      FullName = infomodel.FullName,
                      Members = infomodel.Members,
                      RemoveMembers = new List<long>()
                    } );
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult RemoveMembers( GuildRemoveMembersModel model )
    {
      var error = GuildSvc.RemoveMembers( model.GuildId, model.RemoveMembers.ToArray(), User.Identity.Name );
      if ( error != null )
        return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + error } );

      return RedirectToAction( "Details", new { id = model.GuildId } );
    }

    [HttpGet]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult ChangeLeader( long id )
    {
      var infomodel = GuildSvc.GetGuildInfoById( id );
      if ( infomodel.Error != null )
        return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + infomodel.Error } );

      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, infomodel.LeaderAuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      return View( new GuildChangeLeaderModel
                    {
                      GuildId = infomodel.GuildId,
                      FullName = infomodel.FullName,
                      OldLeader = infomodel.LeaderAuid,
                      Members = infomodel.Members
                    } );
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult ChangeLeader( GuildChangeLeaderModel model )
    {
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, model.OldLeader, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      if ( model.NewLeader != model.OldLeader )
      {
        error = GuildSvc.ChangeLeader( model.GuildId, model.NewLeader, User.Identity.Name );
        if ( error != null )
          return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + error } );
      }

      return RedirectToAction( "Details", new { id = model.GuildId } );
    }

    [HttpGet]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult SetIcon( long id )
    {
      var infomodel = GuildSvc.GetGuildInfoById( id );
      if ( infomodel.Error != null )
        return RedirectToAction( "ShowError", "Account", new { error = "Server returned an error: " + infomodel.Error } );

      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, infomodel.LeaderAuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      var model = new GuildSetIconModel()
      {
        GuildId = infomodel.GuildId,
        FullName = infomodel.FullName,
        LeaderAuid = infomodel.LeaderAuid,
        IconChangesCount = infomodel.IconChangesCount
      };

      return View( model );
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult SetIcon( GuildSetIconModel model )
    {
      if ( model.Image != null && model.Image.ContentType == "image/png" )
      {
        var img = new Bitmap( model.Image.InputStream );
        if ( img.Width == 64 && img.Height == 64 )
        {
          model.Image.InputStream.Position = 0;
          var buffer = new byte[model.Image.InputStream.Length];
          model.Image.InputStream.Read( buffer, 0, (int)model.Image.InputStream.Length );
          /// 1. Uploading icon file
          var err = GuildSvc.SetIcon( model.GuildId, buffer );
          if ( err != null )
            ModelState.AddModelError( String.Empty, string.Format( "Uploading icon: {0}", err ) );
          else
          {
            /// 2. Trying to write off gold if required
            err = GuildSvc.TryToPayForGuildIconChange( model.LeaderAuid, model.IconChangesCount );
            if ( err != null )
              ModelState.AddModelError( String.Empty, string.Format( "Icon change payment: {0}", err ) );
            else
            {
              /// 3. Activating uploaded on first step icon
              err = GuildSvc.SwitchToNewGuildIcon( model.GuildId, User.Identity.Name );
              if ( err != null )
                ModelState.AddModelError( String.Empty, string.Format( "Switching to new icon in GuildData: {0}", err ) );
            }
          }
        }
        else
          ModelState.AddModelError( String.Empty, String.Format( "Image must have size 64x64 (got {0}x{1} instead)", img.Width, img.Height ) );
      }
      else
        ModelState.AddModelError( String.Empty, String.Format( "File must be in .png format (got '{0}' instead)", model.Image != null ? model.Image.ContentType : "(null)" ) );

      if ( !ModelState.IsValid ) 
        return View( model );

      return RedirectToAction( "Details", new { id = model.GuildId } );
    }

    [HttpGet]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult FreeGuildBankTalents(long id)
    {
      // Просто для проверки гильдии на редактируемость
      var model = GuildSvc.GetGuildInfoById(id);
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, model.LeaderAuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      // Непосредственно операция с талантами
      var infomodel = GuildSvc.GetFreeGuildBankTalents( id );
      if( infomodel.Error != null )
        return RedirectToAction( "ShowError", "Account", new {error = "Server returned an error: " + infomodel.Error} );

      return View( infomodel );
    }

    [HttpGet]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult TakenGuildBankTalents(long id)
    {
      // Просто для проверки гильдии на редактируемость
      var model = GuildSvc.GetGuildInfoById(id);
      string error;
      if (!AccountSvc.CheckLocalePermissionByAuid((GMToolsPrincipal)User, model.LeaderAuid, out error))
      {
        if (!String.IsNullOrEmpty(error))
          return RedirectToAction("ShowError", "Account", new { error });
        return View("Forbidden");
      }

      // Непосредственно операция с талантами
      var infomodel = GuildSvc.GetTakenGuildBankTalents(id);
      if (infomodel.Error != null)
        return RedirectToAction("ShowError", "Account", new { error = "Server returned an error: " + infomodel.Error });

      return View(infomodel);
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult ReturnTalentToGuildBank(long guildid, long talentInstanceId)
    {
      if (Request.HttpMethod == "GET")
      {
        string errorIfExistToShow = GuildSvc.ReturnTalentToGuildBank( guildid, talentInstanceId, User.Identity.Name );
        if (errorIfExistToShow != null)
          return RedirectToAction("ShowError", "Account", new { error = errorIfExistToShow });
      }
      return RedirectToAction("TakenGuildBankTalents", new { id = guildid });
    }

    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult ReturnTalentToOwner(long guildid, long talentInstanceId)
    {
      if (Request.HttpMethod == "GET")
      {
        string errorIfExistToShow = GuildSvc.ReturnTalentToOwner( guildid, talentInstanceId, User.Identity.Name );
        if (errorIfExistToShow != null)
          return RedirectToAction("ShowError", "Account", new { error = errorIfExistToShow });
      }
      return RedirectToAction("FreeGuildBankTalents", new { id = guildid });
    }

    [HttpGet]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult AcquireGuildLock(long id)
    {
      var errorIfExistToShow = GuildSvc.AcquireGuildLock(id, User.Identity.Name);
      if (errorIfExistToShow != null)
        return RedirectToAction("ShowError", "Account", new { error = errorIfExistToShow });

      return RedirectToAction("Details", new { id });
    }

    [HttpGet]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult ReleaseGuildLock(long id)
    {
      var errorIfExistToShow = GuildSvc.ReleaseGuildLock(id, User.Identity.Name);
      if (errorIfExistToShow != null)
        return RedirectToAction("ShowError", "Account", new { error = errorIfExistToShow });

      return RedirectToAction("Details", new { id });
    }

    [HttpGet]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult StopGuildSiege(long id)
    {
      var errorIfExistToShow = GuildSvc.StopGuildSiege(id, User.Identity.Name);
      if (errorIfExistToShow != null)
        return RedirectToAction("ShowError", "Account", new { error = errorIfExistToShow });

      return RedirectToAction("Details", new { id });
    }

    [HttpGet]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult AddGuildSuzerain(long guildid)
    {
      var infomodel = GuildSvc.GetGuildInfoById(guildid);
      if (infomodel == null)
      {
        return RedirectToAction("Details", new { id = guildid });
      }
      var guildChangeSuzerainModel = new GuildChangeSuzerainModel
      {
        FullName = infomodel.FullName,
        ShortName = infomodel.ShortName,
        GuildId = infomodel.GuildId,
        SuzerainId = 0
      };
      return View(guildChangeSuzerainModel);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult AddGuildSuzerain(GuildChangeSuzerainModel model)
    {
      var errorIfExistToShow = GuildSvc.AddGuildSuzerain(model.GuildId, model.SuzerainId, User.Identity.Name);
      if (errorIfExistToShow != null)
        return RedirectToAction("ShowError", "Account", new { error = errorIfExistToShow });

      return RedirectToAction("Details", new { id = model.GuildId });
    }

    [HttpGet]
    [AuthorizeWithPermission(Permission = "GM_AccountEdit")]
    public ActionResult RemoveGuildSuzerain(long id)
    {
      var errorIfExistToShow = GuildSvc.RemoveGuildSuzerain(id, User.Identity.Name);
      if (errorIfExistToShow != null)
        return RedirectToAction("ShowError", "Account", new { error = errorIfExistToShow });

      return RedirectToAction("Details", new { id });
    }

    [AuthorizeWithPermission( Permission = "GM_AccountEdit" )]
    public ActionResult GetFullGuildDump( long id )
    {

      StringUIResponse uiResp = GuildSvc.GetFullGuildDump( id, false );
      if ( uiResp.ErrorIfExistToShow != null )
        return RedirectToAction( "ShowError", "Account", new { error = uiResp.ErrorIfExistToShow } );
      return File( Encoding.ASCII.GetBytes( uiResp.Data ),
                 "text/plain", string.Format( "guild_{0}.pwdump", id ) );
    }
  }
}
