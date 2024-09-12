using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Security.Principal;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Microsoft.Reporting.WebForms;
using ZzimaBilling.AdminUI.Forms.UserProfilePages;
using ZzimaBilling.AdminUI.BLL;

namespace ZzimaBilling.AdminUI.Forms.ReportPages
{
    internal class MyReportCredentials: Microsoft.Reporting.WebForms.IReportServerCredentials
    {
        string _userName, _password, _domain;

        public MyReportCredentials()
        {
            _userName = System.Configuration.ConfigurationSettings.AppSettings.Get("rptLogin");
            _password = System.Configuration.ConfigurationSettings.AppSettings.Get("rptPassword"); 
            _domain = System.Configuration.ConfigurationSettings.AppSettings.Get("rptDomain");
        }

        public bool GetFormsCredentials(out Cookie authCookie, out string userName, out string password, out string authority)
        {
            authCookie = new System.Net.Cookie(".ASPXAUTH", ".ASPXAUTH", "/", "Domain");
            userName = _userName;
            password = _password;
            authority = _domain;
            return true; 
        }

        public WindowsIdentity ImpersonationUser
        {
            get { return null; }
        }

        public ICredentials NetworkCredentials
        {
            get { return new NetworkCredential(_userName, _password, _domain); }
        }
    }

    public partial class ReportPage:BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            ZzimaReportViewer.ServerReport.ReportServerUrl = new Uri(System.Configuration.ConfigurationSettings.AppSettings.Get("rptURL"));
            if (!IsPostBack)
            {
                ReportParametersBLL reportParameters = GlobalMethods.PopReportParameters();
                if (reportParameters != null)
                {
                    LoadReportParameters(ZzimaReportViewer, reportParameters);
                }
            }
        }

        protected void SetTitle(string title)
        {
            titleId.Text = title;
        }

        protected void LoadReportParameters(ReportViewer reportViewer, ReportParametersBLL reportParametersBLL)
        {
            if (reportParametersBLL.Parameters != null && !string.IsNullOrEmpty(reportParametersBLL.ReportName))
            {
                SetTitle(reportParametersBLL.ReportTitle);
                reportViewer.ServerReport.ReportServerCredentials = new MyReportCredentials();
                reportViewer.ServerReport.ReportPath = reportParametersBLL.ReportName;
                reportViewer.ServerReport.SetParameters(reportParametersBLL.Parameters);
                reportViewer.ServerReport.Refresh();
            }
        }

        protected void ConfigureReportViewer(ReportViewer reportViewer)
        { 

        }
    }
}
