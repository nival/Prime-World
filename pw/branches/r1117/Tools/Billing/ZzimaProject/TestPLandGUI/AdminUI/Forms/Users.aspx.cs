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
using ZzimaBilling.AdminUI.DAL;
using System.Collections.Generic;
using ZzimaBilling.AdminUI.Forms;
using ZzimaBilling.AdminUI.Templates;
using ZzimaBilling.AdminUI.Templates.WebUserControls;
using System.Data.Linq;
using System.IO;
using System.Text;
using System.Resources;
using System.Reflection;
using System.Drawing;

namespace ZzimaBilling.Admin
{
    public partial class Users : BasePage//System.Web.UI.Page
    {
        #region Fields

        private LinkButton btnFirst = null;
        private LinkButton btnPrevious = null;
        private LinkButton btnNext = null;
        private LinkButton btnLast = null;
        private Label lblCountUsers;
        private Label lblPageCount;
        private Label lblPageNumber;
        public DataTable UsersTable;

        #endregion

        #region Properties

        public int PageIndex
        {
            get
            {
                if (ViewState["pi"] == null)
                {
                    ViewState["pi"] = 0;
                }
                return Convert.ToInt32(ViewState["pi"]);
            }
            set
            {
                if (value >= 0)
                    ViewState["pi"] = value;
            }
        }

        public int UsersCount
        {
            get
            {
                if (ViewState["ucount"] == null)
                {
                    ViewState["ucount"] = 0;
                }
                return Convert.ToInt32(ViewState["ucount"]);
            }
            set
            {
                if (value >= 0)
                    ViewState["ucount"] = value;
            }
        }

        public int PagesCount
        {
            get
            {
                if (ViewState["pcount"] == null)
                {
                    ViewState["pcount"] = 0;
                }
                return Convert.ToInt32(ViewState["pcount"]);
            }
            set
            {
                if (value >= 0)
                    ViewState["pcount"] = value;
            }
        }

        public string CurrentSortExpression
        {
            get
            {
                if (ViewState["sortExpression"] != null)
                {
                    return ViewState["sortExpression"].ToString();
                }
                else
                {
                    ViewState["sortExpression"] = string.Empty;
                    return string.Empty;
                }
            }
            set
            {
                ViewState["sortExpression"] = value;
            }
        }

        public string CurrentSortDirection
        {
            get
            {
                if (ViewState["sortDirection"] != null)
                {
                    return ViewState["sortDirection"].ToString();
                }
                return string.Empty;
            }
            set
            {
                ViewState["sortDirection"] = value;
            }
        }

        public UserFilterBLL UserFilter
        {
            get
            {
                UserFilterBLL userFilter = new UserFilterBLL();
                userFilter.UsernameMask = tpUsername.Text;
                userFilter.UserIDMask = txtUserId.Text;
                userFilter.EmailMask = tpEmail.Text;
                userFilter.TotalFrom = ncTotal.From;
                userFilter.TotalTo = ncTotal.To;
                userFilter.RealFrom = ncReal.From;
                userFilter.RealTo = ncReal.To;
                userFilter.BonusFrom = ncBonus.From;
                userFilter.BonusTo = ncBonus.To;
                userFilter.PartnerProgramName = ddlPartnerProgram.SelectedItem.Value;
                return userFilter;
            }
            set
            {
                UserFilter = (UserFilterBLL)value;
            }
        }
        
        #endregion

        #region Methods

        protected void SetPagerButtonStates()
        {
            // get controls
            lblCountUsers = (Label)gvPagerRow.FindControl("lblCount");
            lblPageCount = (Label)gvPagerRow.FindControl("TotalPagesLabel");
            lblPageNumber = (Label)gvPagerRow.FindControl("PageNumberLabel");
            btnFirst = (LinkButton)gvPagerRow.FindControl("lnkFirstPage");
            btnPrevious = (LinkButton)gvPagerRow.FindControl("lnkPrevPage");
            btnNext = (LinkButton)gvPagerRow.FindControl("lnkNextPage");
            btnLast = (LinkButton)gvPagerRow.FindControl("lnkLastPage");

            // define events
            btnFirst.Click += new EventHandler(Navigate);
            btnPrevious.Click += new EventHandler(Navigate);
            btnLast.Click += new EventHandler(Navigate);
            btnNext.Click += new EventHandler(Navigate);
        }

        protected void GetUsersCount()
        {
            UsersCount = UserDAL.SelectCount(this.UserFilter);
            PagesCount = UsersCount / gvUsers.PageSize + (UsersCount % gvUsers.PageSize > 0 ? 1 : 0);
        }

        protected void UpdatePagerInfo()
        {
            // set labels
            lblCountUsers.Text = UsersCount.ToString();
            lblPageCount.Text = PagesCount.ToString();

            lblPageNumber.Text = (PagesCount != 0 ? PageIndex + 1 : 0).ToString();
            btnFirst.Enabled = btnPrevious.Enabled = (PageIndex != 0);
            btnNext.Enabled = btnLast.Enabled = (PageIndex < (PagesCount - 1));

            btnExport.Enabled = (PagesCount != 0);
        }

        protected void BindUsers(int startIndexRow)
        {
            BindUsers(startIndexRow, CurrentSortExpression, (CurrentSortDirection == "asc") ? true : false);
        }

        protected void BindUsers(int startIndexRow, string sortExpression, bool asc)
        {
            gvUsers.DataSource = UserDAL.GetUsers(startIndexRow, gvUsers.PageSize, this.UserFilter, sortExpression, asc);
            gvUsers.DataBind();
            UpdatePagerInfo();
        }

        public bool FilterIsValid()
        {
            var numericalList = new List<NumericalControl> { ncTotal, ncReal, ncBonus };
            return NumericalControl.IsValid(numericalList);
        }

        protected void FillPartnerPrograms(List<PartnerProgram> pps)
        {
            foreach (var pp in pps)
            {
                ddlPartnerProgram.Items.Add(new ListItem(pp.name, pp.name));
            }
        }

        #endregion

        #region Events

        protected void Page_Load(object sender, EventArgs e)
        {
            SetPagerButtonStates();
            if (!IsPostBack)
            {
                FillPartnerPrograms(new PartnerProgramDAL().Select());

                PageIndex = 0;
                PagesCount = 0;
                UpdatePagerInfo();
            }
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
            string ClickScript = String.Format(addClickScript, btnSearch.ClientID);

            Page.ClientScript.RegisterStartupScript(this.GetType(), "addClickFunctionScript", addClickFunctionScript.ToString(), true);
            Page.ClientScript.RegisterStartupScript(this.GetType(), "click_" + btnSearch.ClientID, ClickScript, true);

        }

        protected void gvUsers_RowCreated(object sender, GridViewRowEventArgs e)
        {
            int d = e.Row.RowIndex % 2;
            if (d == 0)
                e.Row.Attributes.Add("st", "normalRow");
            else
                e.Row.Attributes.Add("st", "alternativeRow");
            GridViewSortImages(sender, e);
        }

        protected void btnSearch_Click(object sender, EventArgs e)
        {
            if (FilterIsValid())
            {
                PagesCount = 0;
                PageIndex = 0;
                GetUsersCount();
                BindUsers(PageIndex * gvUsers.PageSize);
            }
        }

        protected void btnExport_Click(object sender, ImageClickEventArgs e)
        {
            RKLib.ExportData.Export exp = new RKLib.ExportData.Export("Web");
            int[] cols = { 1, 2, 3, 4, 5, 6 };

            DataTable table = UserDAL.GetAllUsersTable(UserFilter, CurrentSortExpression, (CurrentSortDirection == "asc") ? true : false);
            exp.ExportDetails(table, cols, RKLib.ExportData.Export.ExportFormat.CSV, String.Format("Users_{0}.csv", DateTime.Now.ToString("yyyy_MM_dd")));
        }

        protected void gvUsers_RowDataBound(object sender, GridViewRowEventArgs e)
        {
            //Handles clicking
            if (e.Row.RowType == DataControlRowType.DataRow)
            {
                if (((System.Data.DataRowView)(e.Row.DataItem)).Row.ItemArray.GetValue(0).ToString().Length != 0)
                    e.Row.Attributes["onclick"] = "location.href='UserProfilePages/GeneralInfo.aspx?id=" +
                        DataBinder.Eval(e.Row.DataItem, "id") + "'";
                else
                    ((IErrorHandler)this.Master).showMessage(true, Translate("Error.Users"), null);
            }
        }

        protected void Navigate(object sender, EventArgs e)
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
            BindUsers(PageIndex * gvUsers.PageSize);
        }

        protected void gvUsers_Sorting(object sender, GridViewSortEventArgs e)
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

            BindUsers(PageIndex * gvUsers.PageSize, CurrentSortExpression, (CurrentSortDirection == "asc") ? true : false);
        }

        protected void GridViewSortImages(object sender, GridViewRowEventArgs e)
        {
            GridView senderGridView = (GridView)sender;
            Literal space = new Literal();
            space.Text = "    ";
            if (e.Row != null && e.Row.RowType == DataControlRowType.Header)
            {
                for (int i = 0; i < gvUsers.Columns.Count; i++)
                {
                    TableCell cell = e.Row.Cells[i];
                    DataControlField column = gvUsers.Columns[i];

                    if (cell.HasControls())
                    {
                        LinkButton button = cell.Controls[0] as LinkButton;
                        if (button != null)
                        {
                            if (CurrentSortExpression == column.SortExpression)
                            {
                                if (CurrentSortDirection == "asc")
                                    cell.ControlStyle.CssClass = "headerRowAsc";
                                else if (CurrentSortDirection == "desc")
                                    cell.ControlStyle.CssClass = "headerRowDesc";
                            }
                        }
                    }
                }
            }
        }
        
        #endregion

    }
}
