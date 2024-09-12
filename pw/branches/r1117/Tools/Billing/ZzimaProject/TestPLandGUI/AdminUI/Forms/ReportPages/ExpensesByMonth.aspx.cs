using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.Forms;
using ZzimaBilling.AdminUI.Forms.ReportPages;
using ZzimaBilling.AdminUI.Templates;

namespace ZzimaBilling.Admin.ReportsPages
{
    public partial class ExpensesByMonth : ReportBasePage
    {

        protected override void Page_Load(object sender, EventArgs e)
        {
            base.lbtnReport = lbtnReport;
            base.Page_Load(sender, e);
        }

        public override ReportParametersBLL LoadReportParameters()
        {
            try
            {
                ReportParametersBLL parameters = new ReportParametersBLL();
                parameters.AddParameter("fromDate", dtTimePeriod.fromDate.ToString());
                parameters.AddParameter("toDate", dtTimePeriod.toDate.ToString());
                parameters.ReportName = RPT_ExpensesByMonth;
                parameters.ReportTitle = Translate("Reports.Menu.ExpensesByMonth");
                return parameters;
            }
            catch (Exception e)
            {
                ((IErrorHandler)Master).showMessage(true, Translate("Error.Reports"), e.Message);
            }
            return null;
        }
    }
}