using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.UI;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.Templates.WebUserControls;
using System.Web.UI.WebControls;
using Microsoft.Reporting.WebForms;

namespace ZzimaBilling.AdminUI.Forms.ReportPages
{
    public abstract class ReportBasePage: BasePage
    {
        #region Constants

        //Report Page Url
        public const string REPORT_PAGE_URL = "ReportPage.aspx";
        //Report names
        public const string RPT_GeneralInfo = "/ZzimaReports/GeneralInfo";
        public const string RPT_Payment = "/ZzimaReports/Payments";
        public const string RPT_Expenses = "/ZzimaReports/Expenses";
        public const string RPT_PromoActivation = "/ZzimaReports/PromoCodesActivation";
        public const string RPT_ExpensesByMonth = "/ZzimaReports/SpendingStatisticByMonth";
        public const string RPT_ExpensesByGame = "/ZzimaReports/SpendingStatisticByGames";
        public const string RPT_CheckPaymentSystem = "/ZzimaReports/PaymentSystemCheck";
        public const string RPT_GMTransaction = "/ZzimaReports/GMTransaction";
        //Mask constants
        public const string MASK_ALL = "%";
        #endregion

        #region Fields

        public LinkButton lbtnReport;

        #endregion

        #region Properties

        public ReportParametersBLL ReportParameters { get; set; }

        #endregion

        #region Methods

        public ReportBasePage()
        {
            lbtnReport = this.FindControl("lbtnReport") as LinkButton;
            ReportParameters = new ReportParametersBLL();
        }

        public abstract ReportParametersBLL LoadReportParameters();

        #endregion

        #region Helper Methods

        protected static string JoinList<T>(List<T> list)
        {
            string result = string.Empty;
            if (list != null && list.Count > 0)
            {
                for (int i = 0; i < list.Count; i++)
                {
                    result += list[i].ToString();
                    result += (i != list.Count - 1) ? "," : string.Empty;
                }
            }
            else
            {
                return null;
            }
            return result;
        }

        protected static string JoinList<T>(List<T> list, string delimitor)
        {
            string result = string.Empty;
            if (list != null && list.Count > 0)
            {
                for (int i = 0; i < list.Count; i++)
                {
                    result += list[i].ToString();
                    result += (i != list.Count - 1) ? delimitor : string.Empty;
                }
            }
            else
            {
                return null;
            }
            return result;
        }

        protected void CheckAll(CheckBoxList checkBoxList)
        {
            if (checkBoxList != null && checkBoxList.Items.Count > 0)
            {
                foreach (ListItem listItem in checkBoxList.Items)
                {
                    if (!listItem.Selected)
                        listItem.Selected = true;
                }
            }
        }

        public static string FormatUserMasks(string usernameMask)
        {
            if (string.IsNullOrEmpty(usernameMask))
                return "%";
           
            if (HasStarsAndQuestions(usernameMask))
                return ReplaceStarsAndQuestions(usernameMask);

            return usernameMask;
        }

        private static String ReplaceStarsAndQuestions(string mask)
        {
            return mask.Replace('*', '%').Replace('?', '_');
        }

        private static bool HasStarsAndQuestions(string mask)
        {
            return mask.Contains('*') || mask.Contains('?');
        }

        #endregion

        #region Events

        protected virtual void Page_Load(object sender, EventArgs e)
        {
            lbtnReport.Click += new EventHandler(lbtnReport_Click);
        }

        protected virtual void lbtnReport_Click(object sender, EventArgs e)
        {
            if (IsValid)
            {
                ReportParameters = LoadReportParameters();
                if (ReportParameters == null)
                    return;
                
                GlobalMethods.PushReportParameters(ReportParameters);
                GlobalMethods.OpenPageInNewWindow(this, REPORT_PAGE_URL);
            }
        }

        protected void Page_PreRender(object sender, EventArgs e)
        {
            JavaScriptLoad();
        }

        private void JavaScriptLoad()
        {
            StringBuilder addClickFunctionScript = new StringBuilder();

            addClickFunctionScript.Append(" function addClickFunction(id) {{ ");
            addClickFunctionScript.Append(" var b = document.getElementById(id); ");
            addClickFunctionScript.Append(" if (b && typeof(b.click) == 'undefined') b.click = function() {{ ");
            addClickFunctionScript.Append(" var result = true; if (b.onclick) result = b.onclick(); ");
            addClickFunctionScript.Append(" if (typeof(result) == 'undefined' || result) {{ eval(b.getAttribute('href')); }} ");
            addClickFunctionScript.Append(" }}}}; ");

            string addClickScript = "addClickFunction('{0}');";
            string ClickScript = String.Format(addClickScript, lbtnReport.ClientID);

            Page.ClientScript.RegisterStartupScript(this.GetType(), "addClickFunctionScript", addClickFunctionScript.ToString(), true);
            Page.ClientScript.RegisterStartupScript(this.GetType(), "click_" + lbtnReport.ClientID, ClickScript, true);

        }

        #endregion
    }
}
