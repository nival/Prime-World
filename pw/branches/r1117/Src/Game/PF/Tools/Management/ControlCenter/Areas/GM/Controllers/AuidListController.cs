using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Web.Mvc;
using System.Web.Routing;
using AccountLib;
using ControlCenter.Areas.GM.Models;
using ControlCenter.Helpers;
using ControlCenter.Models;

namespace ControlCenter.Areas.GM.Controllers
{
  [Authorize]
  public class AuidListController : Controller
  {
    public IDynamicQuestService DynamicQuestSvc { get; set; }
    public IAccountService AccountSvc { get; set; }

    protected override void Initialize(RequestContext requestContext)
    {
      base.Initialize(requestContext);

      if (DynamicQuestSvc == null)
        DynamicQuestSvc = new DynamicQuestService();

      if (AccountSvc == null)
        AccountSvc = new AccountService();
    }

    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult Index()
    {
      var model = DynamicQuestSvc.GetAuidsLists();
      return View(model);
    }

    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult AuidListMember(int? id)
    {
      var idValue = id ?? -1;
      var model = DynamicQuestSvc.GetAuidsListById(idValue);
      return View(model);
    }

    [HttpPost]
    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult AuidListMember(AuidListMemberModel submitted)
    {
      if (!ModelState.IsValid)
        return View(submitted);

      List<long> auidsInt = null;
      var readFile = false;
      if (Request.Files.Count > 0)
      {
        var httpPostedFileBase = Request.Files[0];
        if (httpPostedFileBase != null)
        {
          var fileName = Path.GetFileName(httpPostedFileBase.FileName);
          // store the file inside ~/App_Data folder
          if (!String.IsNullOrEmpty(fileName))
          {
            readFile = true;
            var path = Path.Combine(Server.MapPath("~/App_Data"), fileName);
            httpPostedFileBase.SaveAs(path);
            var data = System.IO.File.ReadAllBytes(path);
            auidsInt = AuidListMemberModel.GetAuids(Encoding.UTF8.GetString(data));
            System.IO.File.Delete(path);
          }
        }
      }
      if (!readFile)
      {
        auidsInt = submitted.GetAuids();
      }

      if (auidsInt == null)
      {
        ModelState.AddModelError("Auids", "Error parsing auids data. Chack for overflow and file content");
        return View(submitted);
      }

      var error = "";
      if (submitted.Index == -1)
      {
        error =
          DynamicQuestSvc.AddAuidsList(
            new AuidsList {Index = submitted.Index, Description = submitted.Description, Auids = auidsInt},
            User.Identity.Name);
      }
      else
      {
        error =
          DynamicQuestSvc.EditAuidsList(
            new AuidsList {Index = submitted.Index, Description = submitted.Description, Auids = auidsInt},
            User.Identity.Name);
      }

      if (!String.IsNullOrEmpty(error))
      {
        ViewData["Warning"] = "Error: " + error;
        return View(submitted);
      }

      return RedirectToAction("Index");
    }

    [AuthorizeWithPermission(Permission = "GM_DynamicQuests")]
    public ActionResult RemoveAuidListMember(int id)
    {
      var model = DynamicQuestSvc.GetAuidsListById(id);

      if (model.Links > 0)
      {
        const string localRedirectAction = "Index";
        const string localRedirectController = "AuidList";
        var localRedirectRoutes = new RouteValueDictionary
        {
          {"area", ControllerContext.RouteData.DataTokens["area"]}
        };
        return View("Warning", new WarningModel
        {
          Message = "Error: You cant delete used list. First you shoult delete all links to it.",
          Action = localRedirectAction,
          Controller = localRedirectController,
          RedirectRoute = localRedirectRoutes,
          RedirectUrl = ""
        });
      }
      DynamicQuestSvc.RemoveAuidsList(id);
      return RedirectToAction("Index");
    }
  }
}