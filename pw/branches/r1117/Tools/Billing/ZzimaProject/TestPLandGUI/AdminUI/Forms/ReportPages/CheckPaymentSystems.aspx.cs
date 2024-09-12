using System;
using System.Collections;
using System.Collections.Generic;
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
using ZzimaBilling.AdminUI.DAL;
using ZzimaBilling.AdminUI.Forms;
using ZzimaBilling.AdminUI.Forms.ReportPages;
using ZzimaBilling.AdminUI.Templates;

namespace ZzimaBilling.Admin.ReportsPages
{
    public partial class CheckPaymentSystems : ReportBasePage
    {
        protected override void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                FillMonths(ddlMonth);
                FillYears(ddlYear);
                FillPaymentSystems(ddlPaymentSystems);
            }
            base.lbtnReport = lbtnReport;
            base.Page_Load(sender, e);
        }

        public override ReportParametersBLL LoadReportParameters()
        {
            try
            {
                DateTime fromDt = new DateTime(Convert.ToInt32(ddlYear.SelectedValue), (ddlMonth.SelectedIndex + 1), 1);
                DateTime toDt = fromDt.AddMonths(1);//.AddDays(-1);
                ReportParametersBLL parameters = new ReportParametersBLL();
                parameters.AddParameter("fromDate", fromDt.ToString());
                parameters.AddParameter("toDate", toDt.ToString());
                parameters.AddParameter("paymentSystem", ddlPaymentSystems.SelectedValue);
                parameters.ReportName = RPT_CheckPaymentSystem;
                parameters.ReportTitle = Translate("Reports.Menu.CheckPaymentSystems");
                return parameters;
            }
            catch (Exception e)
            {
                ((IErrorHandler)Master).showMessage(true, Translate("Error.Reports"), e.Message);
            }
            return null;
        }

        protected void FillMonths(DropDownList ddl)
        {
            ddl.Items.Clear();
            ddl.Items.Add(new ListItem(Translate("Calendar.M1")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M2")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M3")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M4")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M5")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M6")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M7")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M8")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M9")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M10")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M11")));
            ddl.Items.Add(new ListItem(Translate("Calendar.M12")));
            ddl.SelectedIndex = DateTime.Now.Month - 1;
        }

        protected void FillYears(DropDownList ddl)
        {
            ddl.Items.Clear();
            int year = DateTime.Now.Year;
            int delta = 10;
            for (int i = (year - delta); i < (year + delta); i++)
            {
                ddl.Items.Add(new ListItem(i.ToString()));
            }
            ddl.SelectedIndex = delta;
        }

        protected void FillPaymentSystems(DropDownList ddl)
        {
            List<PSystemBLL> ppsystems = new PaymentSystemDAL().Select();
            ddl.Items.Clear();
            //ddl.Items.Add(new ListItem(Translate("Reports.AllPaymentSystems"), string.Empty));
            foreach (PSystemBLL item in ppsystems)
                ddl.Items.Add(new ListItem(item.Name, item.Name));
        }
     }
}
