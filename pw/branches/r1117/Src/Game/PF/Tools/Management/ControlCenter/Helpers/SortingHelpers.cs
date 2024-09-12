using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Linq.Expressions;
using System.Web;
using System.Web.Mvc;
using System.Web.Mvc.Html;
using ControlCenter.Areas.GM.Models;

namespace ControlCenter.Helpers
{
  public static class SortingHelpers
  {
    public static MvcHtmlString SortingLink<T>(this HtmlHelper<T> html, Expression<Func<T, object>> selector, string action, T model, bool defaultAsc)
      where T : ISortingModel
    {
      var m = selector.Body as MemberExpression ?? (MemberExpression)((UnaryExpression)selector.Body).Operand;

      if (m.Member.GetCustomAttributes(typeof (SortingAttribute), false).Length == 0)
        throw new Exception(String.Format("Invalid selector for SortingLink. Field '{0}' has no attribute [Sorting]", m.Member.Name));

      var descAtts = m.Member.GetCustomAttributes(typeof (DescriptionAttribute), false);
      string linktext = descAtts.Length > 0 ? ((DescriptionAttribute) descAtts[0]).Description : m.Member.Name;

      var routeDic = model.GetSortingRouteDictionary();
      routeDic["OrderBy"] = m.Member.Name;
      routeDic["Asc"] = defaultAsc;
      
      if (model.OrderBy == m.Member.Name)
      {
        linktext += model.Asc ? " ▲" : " ▼";
        routeDic["Asc"] = !model.Asc;
      }

      return html.ActionLink(linktext, action, routeDic);
    }
  }
}
