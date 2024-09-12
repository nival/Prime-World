using System.IO;
using System.Text;
using System.Web.Mvc;
using ControlCenter.Areas.EventTool.Models;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Controllers
{
  [Authorize]
  public class BruteForceDefenderController : Controller
  {
      public IBruteForceDefenderService BruteForceDefenderSvc { get; set; }
      
    protected override void Initialize( System.Web.Routing.RequestContext requestContext )
    {
      base.Initialize( requestContext );

      if (BruteForceDefenderSvc == null)
          BruteForceDefenderSvc = new BruteForceDefenderService();

   
    }

    [AuthorizeWithPermission(Permission = "GM_BruteForceDefenderView")]
    public ActionResult Details( string email )
    {
        BruteForceAccountModel model = new BruteForceAccountModel();
        if (email!= null && email != string.Empty)
        {
            model = BruteForceDefenderSvc.GetBruteForceAccount(email);
            if (model.ErrorIfExistToShow != null)
                return RedirectToAction("ShowError", "Account", new {error = model.ErrorIfExistToShow});
        }
        return View( model );
    }
    [AuthorizeWithPermission(Permission = "GM_BruteForceDefenderView")]
    public ActionResult UnBan(string email)
    {
        BruteForceAccountModel model = new BruteForceAccountModel();
        if (email != null && email != string.Empty)
        {
            model = BruteForceDefenderSvc.UnBanBruteForceAccount(email);
            return RedirectToAction("ShowError", "Account", new { error = model.ErrorIfExistToShow });
        }
        return View(model);
    }
    

    [AuthorizeWithPermission(Permission = "GM_BruteForceDefenderView")]
    public ActionResult BannedIp(  int? limit, int? skip)
    {

        
        BannedIpFullListModel model = new BannedIpFullListModel();
        if (skip == null)
            skip = model.Skip;
        else 
            model.Skip = (int)skip ;
        limit = limit?? model.Limit ;
        //int pageQuant = page;

        model = BruteForceDefenderSvc.GetBannedIp((int)limit, (int)skip);

        if (model.ErrorIfExistToShow != null && model.ErrorIfExistToShow != null)
            return RedirectToAction("ShowError", "Account", new { error = model.ErrorIfExistToShow });
        return View(model);
    }


    [AuthorizeWithPermission(Permission = "GM_BruteForceDefenderView")]
    public ActionResult UnBanIp(string ip)
    {
        BannedIpFullListModel model = new BannedIpFullListModel();
        if (ip != null && ip != string.Empty)
        {
            model = BruteForceDefenderSvc.UnBanIp(ip);
            return RedirectToAction("BannedIp", "BruteForceDefender", new { limit= model.Limit, skip= model.Skip });
        }
        return View(model);
    }



  }
}
