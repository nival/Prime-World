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
using ZzimaBilling.AdminUI.DAL;
using ZzimaBilling.AdminUI.BLL;
using System.Collections.Generic;
using ZzimaBilling.AdminUI.Forms.UserProfilePages;

namespace ZzimaBilling.Admin.UserProfilePages
{
    public partial class ActualBalance : UserProfileGridViewPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            this.gridView = gvPaymentSystems;
            //SetPagerButtonStates(gvPagerRow);
            RenderActualBalance(UserDAL.GetActualBalance(this.UserID, ddlServices.SelectedValue));
            //GetRowsCount();
            //UpdatePagerInfo();

            if (! IsPostBack)
            {
                FillServices(ddlServices);
            }
        }
        private void FillServices(DropDownList ddlServices)
        {
            ddlServices.Items.Clear();
            ddlServices.Items.Add(new ListItem("общий", "0"));
            List<ServiceBLL> lsIndependents = ServiceDAL.IndependentSvcsListForBalance();
            foreach (ServiceBLL svc in lsIndependents)
            {
                ddlServices.Items.Add(new ListItem(svc.Name, svc.ServiceID.ToString()));
            }
        }
        private void GetRowsCount()
        {
            string serviceID = ddlServices.SelectedValue;
            if (String.IsNullOrEmpty(serviceID)) serviceID = "0";
            RowsCount = (UserDAL.GetPaymentSystemsTableFiltered(this.UserID, serviceID)).Rows.Count;
            PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
        }

        private void RenderActualBalance(ActualBalanceBLL actualBalanceBLL)
        {
            //Instead of Custom Paging and Sorting
            //RenderPaymentSystemAccounts(actualBalanceBLL.PaymentSystemAccounts);
            RenderPaymentSystemValues(actualBalanceBLL);
        }

        protected void RenderPaymentSystemValues(ActualBalanceBLL actualBalanceBLL)
        {
            lblTotalBalanceValue.Text = actualBalanceBLL.TotalBalance.ToString();
            lblBonusBalanceValue.Text = actualBalanceBLL.BonusBalance.ToString();
        }

        protected void gvPaymentSystems_RowCreated(object sender, GridViewRowEventArgs e)
        {
            base.GridViewSortImages(sender, e);
        }

        protected void gvPaymentSystems_Sorting(object sender, GridViewSortEventArgs e)
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

        protected void gvPaymentSystems_DataBound(object sender, EventArgs e)
        {
            if (gvPaymentSystems.Rows.Count > 0)
            {
                for (int i = 0; i < gvPaymentSystems.Rows.Count; i++)
                {
                    if (gvPaymentSystems.Rows[i].Cells[0].Text == " BONUSES")
                    {
                        lblBonusBalanceValue.Text = gvPaymentSystems.Rows[i].Cells[1].Text;
                        return;
                    }
                }
            }
        }

        //Instead of Custom Paging and Sorting
        //protected void RenderPaymentSystemAccounts(List<PaymentSystemAccountBLL> psAccounts)
        //{
        //    if (psAccounts != null && psAccounts.Count >= 1)
        //    {
        //        gvPaymentSystems.DataSource = psAccounts;
        //        gvPaymentSystems.DataBind();
        //    }
        //}

        

        //protected void EmptyGridFix(GridView gridView)
        //{
        //    if (gridView.DataSource == null)
        //    {
        //        gridView.DataSourceID = null;
        //        DataTable table = new DataTable();
        //        DataRow emptyRow = table.NewRow();
        //        gridView.DataSource = table;
        //    }
        //}
    }
}
