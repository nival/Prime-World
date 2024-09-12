using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.BLL;
using System.Collections.Generic;
using ZzimaBilling.AdminUI.DAL;
using ZzimaBilling.AdminUI.Forms.UserProfilePages;
using ZzimaBilling.AdminUI.Templates;

namespace ZzimaBilling.AdminUI.Forms
{
    public partial class PromoCodes : UserProfileGridViewPage
    {

        protected void Page_Load(object sender, EventArgs e)
        {
            this.gridView = gvPromoCodes;
            SetPagerButtonStates(gvPagerRow);

            if (!IsPostBack)
                ClearPromocodesSession();

            GetRowsCount();
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
            string ClickScript = String.Format(addClickScript, btnGenerate.ClientID);

            Page.ClientScript.RegisterStartupScript(this.GetType(), "addClickFunctionScript", addClickFunctionScript.ToString(), true);
            Page.ClientScript.RegisterStartupScript(this.GetType(), "click_" + btnGenerate.ClientID, ClickScript, true);

        }

        protected void GetRowsCount()
        {
            RowsCount = (GetPromoCodesDataTable() != null ? GetPromoCodesDataTable().Rows.Count : 0);
            PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
        }

        public DataTable GetPromoCodesDataTable()
        {
            return (DataTable)Session[PromoCodesBLL.SESSION_KEY_PROMOCODES];
        }

        private void ClearPromocodesSession()
        {
            if (Session[PromoCodesBLL.SESSION_KEY_PROMOCODES] != null)
                Session[PromoCodesBLL.SESSION_KEY_PROMOCODES] = null;
        }

        protected void btnGenerate_Click(object sender, EventArgs e)
        {
            try
            {
                ClearPromocodesSession();
                List<PromoCodesBLL> PromoCodesList = employer.generatePromocodes(Convert.ToDecimal(tpSum.Text), Convert.ToInt32(tpPromoCodesAmount.Text), tpComment.Text);
                DataTable PromoCodesTable = UserDAL.ToDataTable<PromoCodesBLL>(PromoCodesList);
                Session[PromoCodesBLL.SESSION_KEY_PROMOCODES] = PromoCodesTable;
                GetRowsCount();
                gridView.DataBind();
                UpdatePagerInfo();
                if (RowsCount > 0)
                    btnExport.Enabled = true;
                ((IErrorHandler)this.Master).showMessage(false, Translate("Error.Ok"), null);
            }
            catch (System.Exception ex)
            {
                ((IErrorHandler)this.Master).showMessage(true, Translate("Error.PromoCodes.Generate"), ex.Message);
            }
        }

        protected void gvPromoCodes_RowCreated(object sender, GridViewRowEventArgs e)
        {
            base.GridViewSortImages(sender, e);
        }

        protected void gvPromoCodes_Sorting(object sender, GridViewSortEventArgs e)
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

        protected void btnExport_Click(object sender, ImageClickEventArgs e)
        {
            RKLib.ExportData.Export exp = new RKLib.ExportData.Export("Web");
            int[] cols = { 0, 1, 2 };

            DataTable table = GetPromoCodesDataTable();
            exp.ExportDetails(table, cols, RKLib.ExportData.Export.ExportFormat.CSV, String.Format("PromoCodes_{0}.csv", DateTime.Now.ToString("yyyy_MM_dd")));
        }

        protected void gvPromoCodes_Sorted(object sender, EventArgs e)
        {
            gridView.SelectedIndex = -1;
            gridView.PageIndex = PageIndex;

            UpdatePagerInfo();
        }
    }
}
