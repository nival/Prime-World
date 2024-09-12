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
using ZzimaBilling.AdminUI.Forms.UserProfilePages;
using ZzimaBilling.AdminUI.BLL;
using System.Collections.Generic;
using ZzimaBilling.AdminUI.DAL;
using System.Web.UI.DataVisualization.Charting;

namespace ZzimaBilling.AdminUI.Forms.UserProfilePages
{
    public partial class TransfersHistory : UserProfileGridViewPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            lnkFirstPage.Click += new EventHandler(Navigate);
            lnkPrevPage.Click += new EventHandler(Navigate);
            lnkLastPage.Click += new EventHandler(Navigate);
            lnkNextPage.Click += new EventHandler(Navigate);
            gridView = this.gvTransferHistory;
            Session["Filter"] = Filter;
            if (! Page.IsPostBack)
            {
                GetRowsCount();
                UpdatePagerInfo(gvPagerRow);
            }
        }

        private void GetRowsCount()
        {
            int rc = 0;
            foreach (object o in odsTransfers.Select())
            {
                rc++;
            }
            RowsCount = rc;
            PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
        }
        public Filter Filter
        {
            get
            {
                Filter filter = new Filter();
                filter.AmountFrom = ncAmount.From;
                filter.AmountTo = ncAmount.To;
                filter.DateFrom = dtFrom.DateTime;
                filter.DateTo = dtTo.DateTime;
                return filter;
            }
        }
        protected void lbnApply_Click(object sender, EventArgs e)
        {
            Session["Filter"] = Filter;
            gridView.DataBind();
            PagesCount = 0;
            PageIndex = 0;
            GetRowsCount();
            UpdatePagerInfo(gvPagerRow);
        }

        protected void gvTransfersHistory_Sorting(object sender, GridViewSortEventArgs e)
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

        protected void gvTransfersHistory_RowCreated(object sender, GridViewRowEventArgs e)
        {
            base.GridViewSortImages(sender, e);
        }

        protected new void Navigate(object sender, EventArgs e)
        {
            LinkButton button = (sender as LinkButton);
            switch (button.CommandArgument)
            {
                case "First":
                    PageIndex = 0;
                    break;

                case "Prev":
                    PageIndex--;
                    break;

                case "Next":
                    PageIndex++;
                    break;

                case "Last":
                    PageIndex = PagesCount - 1;
                    break;
            }
            gvTransferHistory.DataBind();
            UpdatePagerInfo(gvPagerRow);
        }
        protected void cvDate_ServerValidate(object source, ServerValidateEventArgs args)
        {
            args.IsValid = (dtFrom.DateTime <= dtTo.DateTime);
        }
    }
}