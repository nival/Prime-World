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
using ZzimaBilling.AdminUI.Forms.ReportPages;
using ZzimaBilling.AdminUI.Templates;

namespace ZzimaBilling.Admin.ReportsPages
{
    public partial class GeneralInfo : ReportBasePage
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
                parameters.AddParameter("FromDate", dtFrom.DateTime.ToString());
                parameters.AddParameter("ToDate", dtTo.DateTime.ToString());
                parameters.ReportName = RPT_GeneralInfo;
                parameters.ReportTitle = Translate("Reports.Menu.GeneralInfo");
                return parameters;
            }
            catch (Exception e)
            {
                ((IErrorHandler)Master).showMessage(true, Translate("Error.Reports"), e.Message);
            }
            return null;
        }

        protected void cvDate_ServerValidate(object source, ServerValidateEventArgs args)
        {
            args.IsValid = (dtFrom.DateTime <= dtTo.DateTime);
        }
    }
}
