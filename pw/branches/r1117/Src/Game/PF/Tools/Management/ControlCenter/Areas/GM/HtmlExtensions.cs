using System.Text;
using System.Web;
using System.Web.Mvc;

namespace ControlCenter.Areas.GM.Views
{
  public static class HtmlExtensions
  {
    public static MvcHtmlString Nl2Br(this HtmlHelper htmlHelper, string text)
    {
      if (string.IsNullOrEmpty(text))
        return MvcHtmlString.Create(text);
      else
      {
        StringBuilder builder = new StringBuilder();
        string[] lines = text.Split('\n');
        for (int i = 0; i < lines.Length; i++)
        {
          if (i > 0)
            builder.Append("<br/>\n");
          builder.Append(HttpUtility.HtmlEncode(lines[i]));
        }
        return MvcHtmlString.Create(builder.ToString());
      }
    }
  }
}