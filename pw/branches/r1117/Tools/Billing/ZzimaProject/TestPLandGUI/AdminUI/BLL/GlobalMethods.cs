using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Text;

namespace ZzimaBilling.AdminUI.BLL
{
    public class GlobalMethods
    {
        #region Reports

        public static void PushReportParameters(ReportParametersBLL reportParametersBLL)
        {
            HttpContext.Current.Session["ReportParameters"] = reportParametersBLL;
        }

        public static ReportParametersBLL PopReportParameters()
        {
            if (HttpContext.Current.Session["ReportParameters"] == null)
                return null;
            else
            {
                ReportParametersBLL temp = new ReportParametersBLL();
                temp = HttpContext.Current.Session["ReportParameters"] as ReportParametersBLL;
                HttpContext.Current.Session["ReportParameters"] = null;
                return temp;
            }
        }

        public static void OpenPageInNewWindow(Page page, string pageUrl)
        {
            Type t=page.GetType();
            StringBuilder sb = new StringBuilder();
            sb.Append("<script language='javascript'>");
            sb.Append("window.open('" + pageUrl + "');");
            sb.Append("</script>");
            if (!page.ClientScript.IsClientScriptBlockRegistered(t,"newwindow"))
            {
                page.ClientScript.RegisterClientScriptBlock(t,"newwindow",sb.ToString());
            }
        }

        #endregion
    }
}
