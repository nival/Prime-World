using System;
using System.Collections;
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
using ZzimaBilling.AdminUI.Templates;

namespace ZzimaBilling.AdminUI.Forms.UserProfilePages
{
    public partial class GmaHistory : UserProfileGridViewPage
    {
        public static string GMA_HISTORY_FILTER_KEY    = "gmaHistoryFilter";

        public GmaHistoryFilter Filter
        {
            get
            {
                GmaHistoryFilter filter;
                try
                {
                    filter = new GmaHistoryFilter();
                    filter.DateFrom = dtFrom.DateTime;
                    filter.DateTo = dtTo.DateTime;
                    filter.AmountFrom = ncAmount.From;
                    filter.AmountTo = ncAmount.To;
                    filter.GmaLogin = tbGmaLogin.Text;
                    filter.Comment = tbComment.Text;
                    filter.Validate();

                }
                catch (System.Exception ex)
                {
                    filter = new GmaHistoryFilter();
                    filter.Validate();
                    ((IErrorHandler)this.Master).showMessage(true, Translate("Error.Filtering"), ex.Message);
                }
                return filter;
            }
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
            }
            gridView = gvGmaHistory;
            SetPagerButtonStates(gvPagerRow);
            Session[GMA_HISTORY_FILTER_KEY] = Filter;
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

        protected void lbnApply_Click(object sender, EventArgs e)
        {
            // List<GmaHistoryBLL> payments = UserDAL.GetGmaHistory().getUserPaymentsHistory(UserID, Filter);
            // gvDetails.DataSource = payments;
            rc = -1;
            PageIndex = 0;
            gvGmaHistory.DataBind();
            UpdatePagerInfo();

        }

        protected void gvGmaHistory_Sorting(object sender, GridViewSortEventArgs e)
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

        protected void gvGmaHistory_RowCreated(object sender, GridViewRowEventArgs e)
        {
            GridViewSortImages(sender, e);
        }

        protected void gvGmaHistory_Sorted(object sender, EventArgs e)
        {
            gvGmaHistory.PageIndex = PageIndex;
            UpdatePagerInfo();
        }

        private int rc = -1;
        protected override void UpdatePagerInfo()
        {
           // RowsCount = UserDAL.GetGmaHistory(Convert.ToInt32(Session["UserID"]),(GmaHistoryFilter)Session[GMA_HISTORY_FILTER_KEY]).Count;
            //IEnumerator enm = odsGmaHistory.Select().GetEnumerator();
            if (rc==-1)
            {
                rc = 0;
                foreach (object o in odsGmaHistory.Select())
                {
                    rc++;
                }
                RowsCount = rc;
                PagesCount = rc / gvGmaHistory.PageSize + (rc % gvGmaHistory.PageSize > 0 ? 1 : 0);
            }
            
            base.UpdatePagerInfo();
        }

        protected void cvDate_ServerValidate(object source, ServerValidateEventArgs args)
        {
            args.IsValid = (dtFrom.DateTime <= dtTo.DateTime);
        }
    }
}
