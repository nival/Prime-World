using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using ZzimaBilling.AdminUI.DAL;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.Forms.UserProfilePages;
using ZzimaBilling.AdminUI.Templates;

namespace ZzimaBilling.AdminUI.Forms
{
    public partial class Templates : UserProfileGridViewPage
    {
        #region Constants

        private const string TEMPLATE_URL = "Template.aspx";

        #endregion

        #region Properties

        public int CurrentIndex
        {
            get
            {
                if (String.IsNullOrEmpty(this.inp_row_index.Value))
                    return -1;
                else
                    return int.Parse(this.inp_row_index.Value);
            }
            set
            {
                this.inp_row_index.Value = value.ToString();
            }
        }

        public bool IsVisibleTemplateDetails
        {
            get
            {
                return DetailsFrame.Visible;
            }
            set
            {
                DetailsFrame.Visible = value;
            }
        }

        public string TemplateUrl
        {
            get
            {
                return DetailsFrame.Attributes["src"].ToString();
            }
            set
            {
                DetailsFrame.Attributes["src"] = value;
            }
        }

        private string PostBackEventTarget
        {
            get
            {
                return this.Request.Params.Get("__EVENTTARGET");
            }
        }

        private string PostBackEventArgument
        {
            get
            {
                return this.Request.Params.Get("__EVENTARGUMENT");
            }
        }

        #endregion

        #region Methods

        //Возвращает ID шаблона
        protected int GetTemplateIDByCurrentRowIndex()
        {
            if (gridView == null)
                gridView = gvTemplates;
            if (gridView.SelectedRow == null)
                return -1;
            return int.Parse(gridView.SelectedRow.Cells[0].Text);
        }

        public string getEditConfirm()
        {
            return GetGlobalResourceObject("AdminUI", "Templates.EditConfirm").ToString();
        }

        public string getDelConfirm()
        {
            return GetGlobalResourceObject("AdminUI", "Templates.DelConfirm").ToString();
        }

        public DataTable getTemplatesTable()
        {
            List<vw_gui_Template> templatesList = EmployeeDAL.getTemplates();
            DataTable templateTable = UserDAL.ToDataTable(templatesList);
            return templateTable;
        }

        protected void GetRowsCount()
        {
            RowsCount = getTemplatesTable().Rows.Count;
            PagesCount = RowsCount / gridView.PageSize + (RowsCount % gridView.PageSize > 0 ? 1 : 0);
        }

        #endregion

        #region Helper Methods

        #endregion

        #region Events

        protected override void OnPreInit(EventArgs e)
        {
            base.OnPreInit(e);
        }

        protected override void OnPreLoad(EventArgs e)
        {
            base.OnPreLoad(e);
        }

        

        protected void Page_Load(object sender, EventArgs e)
        {
            var req = this.Request;

            ProcessDeleteHandler();

            if(this.inp_row_index.Value.Length>0)
                CurrentIndex = Convert.ToInt32(this.inp_row_index.Value);
            this.gridView = gvTemplates;
            SetPagerButtonStates(gvPagerRow);

            if (!IsPostBack)
            {
                Page.DataBind(); 
                inp_row_index.Value = "";
                IsVisibleTemplateDetails = false;
                //enableButton(false);
            }
            else
            {
                string sIndex = Request[inp_row_index.Name];
                inp_row_index.Value = sIndex;
                if(!String.IsNullOrEmpty(inp_row_index.Value))
                    if (Int32.Parse(inp_row_index.Value) > gridView.Rows.Count - 1)
                        inp_row_index.Value = "";
            }
            GetRowsCount();
            UpdatePagerInfo();
        }

        private void ProcessDeleteHandler()
        {
            if (PostBackEventTarget == "btnDel" &&
                PostBackEventArgument == "btnDelete_click")
                btnDelete_Click();
            if (PostBackEventTarget == "btnEdit" &&
                PostBackEventArgument == "btnEdit_click")
                btnEdit_Click();
        }

        void inp_row_index_ServerChange(object sender, EventArgs e)
        {
            int index = int.Parse(inp_row_index.Value);
            gridView.SelectedIndex = index;

            if (index >= 0)
            {
                TemplateUrl = TEMPLATE_URL + "?action=edit&id=" + GetTemplateIDByCurrentRowIndex().ToString();
                IsVisibleTemplateDetails = true;
            }
            else
                IsVisibleTemplateDetails = false;
        }

        protected void gvTemplates_RowCreated(object sender, GridViewRowEventArgs e)
        {
            if (inp_row_index.Value.Equals("-1") == false)
            {
                string sIndex = Request[inp_row_index.Name];
                inp_row_index.Value = sIndex;
            }
            int d = e.Row.RowIndex % 2;
            if(d == 0)
                e.Row.Attributes.Add("st", "normalRow");
            else
                e.Row.Attributes.Add("st", "alternativeRow");

            if (e.Row.RowType == DataControlRowType.DataRow)
            {
                if (CurrentIndex == e.Row.RowIndex)
                {
                    e.Row.CssClass = "selectRow";
                    gvTemplates.SelectedIndex = CurrentIndex;
                }
                e.Row.Attributes.Add("id", String.Format("row{0}", e.Row.RowIndex));
                e.Row.Attributes.Add("onclick", String.Format("select(this, {0});", e.Row.RowIndex));
                ScriptManager.RegisterStartupScript(this, GetType(), "", "onLoadT();", true);
            }
            //enableButton(CurrentIndex >= 0);
            base.GridViewSortImages(sender, e);
        }

        #region New, Edit, Delete Events

        protected void btnEdit_Click()
        {
            if (CurrentIndex >= 0)
            {
                TemplateUrl = TEMPLATE_URL + "?action=edit&id=" + GetTemplateIDByCurrentRowIndex().ToString();
                IsVisibleTemplateDetails = true;
            }
            else
            {
                IsVisibleTemplateDetails = false;
            }
        }

        protected void btnDelete_Click()
        {
            try
            {
                if (CurrentIndex >= 0)
                    EmployeeDAL.deleteTemplate(GetTemplateIDByCurrentRowIndex(), employer.id);

                IsVisibleTemplateDetails = false;
                inp_row_index.Value = "";
                gridView.DataBind();
                GetRowsCount();
                UpdatePagerInfo();

                ((IErrorHandler)this.Master).showMessage(false, Translate("Error.Ok"), null);
            }
            catch (System.Exception ex)
            {
                ((IErrorHandler)this.Master).showMessage(true, Translate("Error.Template.Delete"), ex.Message);
            }
        }

        protected void btnAdd_Click(object sender, ImageClickEventArgs e)
        {
            IsVisibleTemplateDetails = true;
            //enableButton(false);
            TemplateUrl = TEMPLATE_URL + "?action=new";
        }

        //protected void enableButton(bool enable)
        //{
        //    btnEdit.Enabled = enable;
        //    if (enable)
        //    {
        //        btnDelete.Attributes["onclick"]= "onDelete()";
        //        //btnDelete.Attributes["cursor"] = "pointer";
        //    }
        //    else
        //    {
        //        //btnDelete.Attributes["cursor"] = "default";
        //        btnDelete.Attributes["onclick"] = null;
        //    }
        //}

        #endregion

        protected override void Navigate(object sender, EventArgs e)
        {
            gridView.SelectedIndex = -1;
            inp_row_index.Value = "-1";
            IsVisibleTemplateDetails = false;
            //enableButton(false);
            base.Navigate(sender, e);
        }

        protected void gvTemplates_SelectedIndexChanged(object sender, EventArgs e)
        {
            TemplateUrl = TEMPLATE_URL + "?action=edit&id=" + GetTemplateIDByCurrentRowIndex().ToString();
            if (!IsVisibleTemplateDetails)
                IsVisibleTemplateDetails = true;
        }

        protected void gvTemplates_Sorting(object sender, GridViewSortEventArgs e)
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

        protected void gvTemplates_Sorted(object sender, EventArgs e)
        {
            gridView.SelectedIndex = -1;
            inp_row_index.Value = "-1";
            IsVisibleTemplateDetails = false;
            //enableButton(false);
            gvTemplates.PageIndex = PageIndex;
            UpdatePagerInfo();
        }

        #endregion  
    }
}
