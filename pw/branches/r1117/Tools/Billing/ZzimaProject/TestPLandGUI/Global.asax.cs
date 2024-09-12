using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.SessionState;
using System.Xml.Linq;
using System.Web.UI;
using ZzimaBilling.AdminUI.BLL;

namespace ZzimaBilling
{
    public class Global : System.Web.HttpApplication
    {
        #region Constants

        

        #endregion

        #region Methods

        public void DownloadReportParameters(ReportParametersBLL reportParametersBLL)
        {
            if(Session["ReportParameters"]!=null)
                Session["ReportParameters"] = reportParametersBLL;
        }

        public ReportParametersBLL UploadReportParameters()
        {
            if (Session["ReportParameters"] == null)
                return null;
            else
            {
                ReportParametersBLL temp = new ReportParametersBLL();
                temp = Session["ReportParameters"] as ReportParametersBLL;
                Session["ReportParameters"] = null;
                return temp;
            }
        }

        #endregion


        protected void Application_Start(object sender, EventArgs e)
        {

        }

        protected void Session_Start(object sender, EventArgs e)
        {
            
        }

        protected void Application_BeginRequest(object sender, EventArgs e)
        {

        }

        protected void Application_AuthenticateRequest(object sender, EventArgs e)
        {

        }

        protected void Application_Error(object sender, EventArgs e)
        {

        }

        protected void Session_End(object sender, EventArgs e)
        {

        }

        protected void Application_End(object sender, EventArgs e)
        {

        }
    }
}