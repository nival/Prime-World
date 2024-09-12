using System.IO;
using System.Text;
using System.Web.Mvc;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Controllers
{
  [Authorize]
  public class GameSessionController : Controller
  {
    public IGameSessionService GameSessionSvc { get; set; }

    protected override void Initialize( System.Web.Routing.RequestContext requestContext )
    {
      base.Initialize( requestContext );

      if ( GameSessionSvc == null )
        GameSessionSvc = new GameSessionService();
    }

    [AuthorizeWithPermission( Permission = "GM_GameSessionView" )]
    public ActionResult Details( int id )
    {
      GameSessionShortInfoModel model = GameSessionSvc.GetSessionShortInfoById( id );
      if ( model.ErrorIfExistToShow != null )
        return RedirectToAction( "ShowError", "Account", new { error = model.ErrorIfExistToShow } );
      return View( model );
    }

    [AuthorizeWithPermission( Permission = "GM_GameSessionView" )]
    public ActionResult GameReplays()
    {
      var model = new GameReplayModel();
      return View( model );
    }

    [HttpPost]
    [AuthorizeWithPermission( Permission = "GM_GameSessionView" )]
    public ActionResult GameReplays(GameReplayModel model)
    {
      model.ErrorIfExistToShow = "";
      string searchDirectory;
      model.Replays = GameSessionSvc.GetReplays( model.Hostname, model.Date, model.GameSessionId, out searchDirectory );
      if ( model.Replays.Count == 0 )
        model.ErrorIfExistToShow = string.Format("No replays found. Please try another date or another session id. Directory = {0}", searchDirectory);
      return View( model );
    }

    [AuthorizeWithPermission( Permission = "GM_GameSessionView" )]
    public ActionResult DownloadReplay( string replayLink )
    {
      if (replayLink.Length==0)
        return RedirectToAction( "ShowError", "Account", new { error = "Can't download, no such file on a server." } );
      return Redirect(replayLink);
    }
  }
}
