using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using ZzimaBilling.AdminUI.Templates.WebUserControls;

namespace ZzimaBilling.AdminUI.Templates.WebUserControls
{
    public partial class TimePeriodParameter : System.Web.UI.UserControl
    {

        public DateTime fromDate
        {
            get
            {
                return dtFrom != null ? dtFrom.DateTime : DateTime.Now;
            }
        }

        public DateTime toDate
        {
            get
            {
                return dtTo != null ? dtTo.DateTime : DateTime.Now;
            }
        }
        
        public string Translate(string key)
        {
            Object obj = HttpContext.GetGlobalResourceObject("AdminUI", key);
            if (obj == null)
                return key;
            return obj.ToString();
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                FillDownList(ddlPeriodValues);
                ddlPeriodValues.SelectedIndex = 0;
            }
            ddlPeriodValues_SelectedIndexChanged();
        }

        protected void FillDownList(DropDownList ddl)
        {
            ddl.Items.Add(new ListItem(Translate("TimePeriodParameter.CurrentWeek")));
            ddl.Items.Add(new ListItem(Translate("TimePeriodParameter.CurrentMonth")));
            ddl.Items.Add(new ListItem(Translate("TimePeriodParameter.AnyPeriod")));
        }

        protected void ddlPeriodValues_SelectedIndexChanged()
        {
            int index = ddlPeriodValues.SelectedIndex;
            switch (index)
            {
                case 0:
                    dtFrom.DateTime = DateTime.Today.AddDays(1 - (int)DateTime.Now.DayOfWeek);
                    dtTo.DateTime = dtFrom.DateTime.AddDays(7);
                    dtFrom.Enabled = dtTo.Enabled = false;
                    break;
                
                case 1:
                    dtFrom.DateTime = DateTime.Today.AddDays(1 - (int)DateTime.Now.Day);
                    dtTo.DateTime = dtFrom.DateTime.AddMonths(1).AddSeconds(-1);
                    dtFrom.Enabled = dtTo.Enabled = false;
                    break;
                
                case 2:
                    dtFrom.Enabled = dtTo.Enabled = true;
                    break;
            }
        }

        protected void cvDate_ServerValidate(object source, ServerValidateEventArgs args)
        {
            args.IsValid = (dtFrom.DateTime <= dtTo.DateTime);
        }
    }
}