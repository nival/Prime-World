using System.Web.Mvc;

namespace ControlCenter.Helpers
{
  public class HttpStatusCodeResult : ActionResult
  {
    private readonly int code;
    public HttpStatusCodeResult(int code)
    {
      this.code = code;
    }

    public override void ExecuteResult(ControllerContext context)
    {
      context.HttpContext.Response.StatusCode = code;
    }
  }
}