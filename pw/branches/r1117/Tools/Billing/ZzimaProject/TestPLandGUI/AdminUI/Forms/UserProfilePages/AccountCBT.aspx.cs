using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.BLL;
using System.Collections.Generic;
using ZzimaBilling.AdminUI.DAL;

namespace ZzimaBilling.AdminUI.Forms.UserProfilePages
{
    public partial class AccountCBT : UserProfileGridViewPage
    {
        #region Methods

        private void GetRowsCount()
        {
            RowsCount = UserDAL.GetAccountDetails(UserID).Count;
            PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
        }

        protected void RenderTotalAmount(decimal cbtAmount)
        {
            lblCBTAmountValue.Text = cbtAmount.ToString();
        }

        protected void RenderDetails(List<AccountDetailBLL> accountDetails)
        {
            if (accountDetails != null && accountDetails.Count > 0)
            {
                gvAccountCBTDetails.DataSource = accountDetails;
                gvAccountCBTDetails.DataBind();
            }
        }

        #endregion

        #region Events

        protected void Page_Load(object sender, EventArgs e)
        {
            this.gridView = gvAccountCBTDetails;
            SetPagerButtonStates(gvPagerRow);
            if (!IsPostBack)
            {
                RenderTotalAmount(UserDAL.GetCBTAmount(this.UserID));
                GetRowsCount();
                UpdatePagerInfo();
            }
        }

        protected void gvAccountCBTDetails_RowCreated(object sender, GridViewRowEventArgs e)
        {
            base.GridViewSortImages(sender, e);
        }

        protected void gvAccountCBTDetails_Sorting(object sender, GridViewSortEventArgs e)
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

        #endregion
    }
}
