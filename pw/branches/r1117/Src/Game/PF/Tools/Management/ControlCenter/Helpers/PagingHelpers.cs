using System;
using System.Text;
using System.Web.Mvc;

namespace ControlCenter.Helpers
{
    public static class PagingHelpers
    {
        public static string PageLinks(this HtmlHelper html, int currentPage,
                                       int totalPages, Func<int, string> pageUrl)
        {
            StringBuilder result = new StringBuilder();
            for (int i = 1; i <= totalPages; i++)
            {
                TagBuilder tag = new TagBuilder("a"); // Construct an <a> tag
                tag.MergeAttribute("href", pageUrl(i));
                tag.InnerHtml = i.ToString();
                if (i == currentPage)
                    tag.AddCssClass("selected");
                result.AppendLine(tag.ToString());
            }
            return result.ToString();
        }

        public static string PageLinksForMongo(this HtmlHelper html, int limit, int skip,
                                   int total, Func<int, int, string> pageUrl)
        {
            StringBuilder result = new StringBuilder();
            int t = total/limit;
            for (int i = 1; i<=t + 1; i++)
            {
                TagBuilder tag = new TagBuilder("a"); // Construct an <a> tag
                tag.MergeAttribute("href", pageUrl(limit,(i-1)*limit));
                tag.InnerHtml = i.ToString();
                if ((i-1)*limit == skip)
                    tag.AddCssClass("selected");
                result.AppendLine(tag.ToString());
            }
            return result.ToString();
        }

    
    }
}