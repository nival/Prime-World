using System;
using System.Reflection;
using System.Web.Mvc;
using ControlCenter.Areas.GM.Models;

namespace ControlCenter.Controllers
{
  [HandleError]
  [Authorize]
  public class HomeController : Controller
  {
    public ActionResult Index()
    {
      ViewData["Message"] = String.Format("Welcome, {0}!", User.Identity.Name);

      ViewData["SocVersion"] = new AccountService().GetSocServerVersion();
      ViewData["PvXVersion"] = "Not implemented";

      // т.к. номер билда у нас превышает UInt16.MaxValue, то в build хранится остаток от деления на 65535,
      // а в поле ревизии хранится целая часть от деления (подробнее см. в NUM_TASK)
      var version = Assembly.GetExecutingAssembly().GetName().Version;
      ViewData["GameToolsVersion"] = version.Build*UInt16.MaxValue + version.Revision;

      return View();
    }

    public ActionResult Forbidden()
    {
      return View();
    }
  }
}
