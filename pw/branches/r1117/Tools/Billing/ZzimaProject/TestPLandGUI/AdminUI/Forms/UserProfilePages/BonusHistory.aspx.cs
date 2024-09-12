using System;
using System.Collections;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.DAL;

namespace ZzimaBilling.AdminUI.Forms.UserProfilePages
{
    public partial class BonusHistory : UserProfileGridViewPage
    {
        private int rc = -1;
        public static string BONUS_FILTER_KEY = "bonusFilterKey";

        public BonusFilter bonusFilter
        {
            get
            {
                BonusFilter filter = new BonusFilter();
                filter.DateFrom = dtFrom.DateTime;
                filter.DateTo = dtTo.DateTime;
                filter.AmountFrom = bhSum.From;
                filter.AmountTo = bhSum.To;
                filter.Comment = bhComment.Text;
                return filter;
            }
        }

        protected void Page_Load(object sender, EventArgs e)
        {

            this.gridView = gvBonusHistory;
            SetPagerButtonStates(gvPagerRow);
            Session[BONUS_FILTER_KEY] = bonusFilter;
            UpdatePagerInfo();
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
            string ClickScript = String.Format(addClickScript, lbnApply.ClientID);

            Page.ClientScript.RegisterStartupScript(this.GetType(), "addClickFunctionScript", addClickFunctionScript.ToString(), true);
            Page.ClientScript.RegisterStartupScript(this.GetType(), "click_" + lbnApply.ClientID, ClickScript, true);

        }

        protected void gvBonusHistory_RowCreated(object sender, GridViewRowEventArgs e)
        {
            base.GridViewSortImages(sender, e);
        }

        protected void gvBonusHistory_Sorting(object sender, GridViewSortEventArgs e)
        {
            if (CurrentSortExpression == e.SortExpression.ToString())
            {
                if (CurrentSortDirection == "asc")
                    CurrentSortDirection = "desc";
                else
                    CurrentSortDirection = "asc";
            }
            else
            {
                CurrentSortExpression = e.SortExpression.ToString();
                CurrentSortDirection = "asc";
            }
        }

        protected void lbnApply_Click(object sender, EventArgs e)
        {
            rc = -1;
            PageIndex = 0;
            gvBonusHistory.DataBind();
            UpdatePagerInfo();
        }

        protected override void UpdatePagerInfo()
        {
            if (rc == -1)
            {
                rc = 0;
                foreach (object o in odsBonusHistory.Select())
                {
                    rc++;
                }
                RowsCount = rc;
                PagesCount = rc / gvBonusHistory.PageSize + (rc % gvBonusHistory.PageSize > 0 ? 1 : 0);
            }

            base.UpdatePagerInfo();
        }

        protected void gvBonusHistory_Sorted(object sender, EventArgs e)
        {
            gvBonusHistory.PageIndex = PageIndex;
            UpdatePagerInfo();
        }

        protected void cvDate_ServerValidate(object source, ServerValidateEventArgs args)
        {
            args.IsValid = (dtFrom.DateTime <= dtTo.DateTime);
        }
    }
}