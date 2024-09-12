using System;
using System.Linq;
using System.Web.Mvc;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;

namespace ControlCenter.Areas.GM.Controllers
{
  [Authorize]
  public class BroadcastController : Controller
  {
    private const int PAGE_SIZE = 20;

    public IAccountService AccountSvc { get; set; }


    protected override void Initialize( System.Web.Routing.RequestContext requestContext )
    {
      base.Initialize( requestContext );
      if ( AccountSvc == null )
        AccountSvc = new AccountService();
    }


    [AuthorizeWithPermission(Permission = "GM_Broadcast")]
    public ActionResult GetBroadcastList(int? page)
    {
      if (!page.HasValue || page < 1) page = 1;
      int totalpages;

      var model = AccountSvc.GetBroadcastList((GMToolsPrincipal) User, page.Value, PAGE_SIZE, out totalpages);
      if ( model.ErrorIfExistToShow != null )
        return RedirectToAction( "ShowError", "Account", new { error = model.ErrorIfExistToShow } );

      ViewData["page"] = page.Value;
      ViewData["totalpages"] = totalpages;
      return View( model.broadcastList );
    }


    [AuthorizeWithPermission(Permission = "GM_Broadcast")]
    public ActionResult CreateNew()
    {
      return View(new BroadcastModel(AccountSvc.GetBroadcastLocales((GMToolsPrincipal) User)));
    }


    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_Broadcast")]
    public ActionResult CreateNew(BroadcastModel model)
    {
      if (model.Messages == null || model.Messages.All(m => m.Text == null || m.Text.Trim() == String.Empty))
        ModelState.AddModelError("", "At least one broadcast text should be filled");

      if (!ModelState.IsValid)
        return View(model);

      string error = AccountSvc.CreateBroadcastMessage(model, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", "Account", new {error});

      return RedirectToAction("GetBroadcastList");
    }


    [AuthorizeWithPermission(Permission = "GM_Broadcast")]
    public ActionResult EditMessage(int id)
    {
      var model = AccountSvc.GetBroadcastById(id, (GMToolsPrincipal)User);
      if (model == null)
        return RedirectToAction("ShowError", "Account", new {error = "Cannot get broadcast with id = " + id});
      
      if (model.Messages.Count == 0)
        return View("Forbidden");

      return View(model);
    }


    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_Broadcast")]
    public ActionResult EditMessage(BroadcastModel model)
    {
      if (model.Messages == null || model.Messages.All(m => m.Text == null || m.Text.Trim() == String.Empty))
        ModelState.AddModelError("", "At least one broadcast text should be filled");

      if (!ModelState.IsValid)
        return View(model);

      // Запрашиваем бродкаст с сервера, чтобы определить, были ли у ГМа права его редактировать
      var checkmodel = AccountSvc.GetBroadcastById(model.Id, (GMToolsPrincipal)User);
      if (checkmodel.Messages.Count == 0)
        return View("Forbidden");

      string error = AccountSvc.EditBroadcastMessage(model, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", "Account", new {error});

      return RedirectToAction("GetBroadcastList");
    }


    [AuthorizeWithPermission(Permission = "GM_Broadcast")]
    public ActionResult StartRotation(int id)
    {
      // Запрашиваем бродкаст с сервера
      var checkmodel = AccountSvc.GetBroadcastById(id, (GMToolsPrincipal)User);
      if (checkmodel.Messages.Count == 0)
        return View("Forbidden");

      string error = AccountSvc.StartMessageRotation(id, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", "Account", new {error});

      return RedirectToAction("GetBroadcastList");
    }


    [AuthorizeWithPermission(Permission = "GM_Broadcast")]
    public ActionResult StopRotation(int id)
    {
      // Запрашиваем бродкаст с сервера
      var checkmodel = AccountSvc.GetBroadcastById(id, (GMToolsPrincipal)User);
      if (checkmodel.Messages.Count == 0)
        return View("Forbidden");

      string error = AccountSvc.StopMessageRotation(id, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", "Account", new {error});

      return RedirectToAction("GetBroadcastList");
    }


    [AuthorizeWithPermission(Permission = "GM_Broadcast")]
    public ActionResult DeleteMessage(int id)
    {
      // Запрашиваем бродкаст с сервера
      var checkmodel = AccountSvc.GetBroadcastById(id, (GMToolsPrincipal)User);
      if (checkmodel.Messages.Count == 0)
        return View("Forbidden");

      string error = AccountSvc.DeleteBroadcastMessage(id, User.Identity.Name);
      if (error != null)
        return RedirectToAction("ShowError", "Account", new {error});

      return RedirectToAction("GetBroadcastList");
    }

  }
}
