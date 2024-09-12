using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.DAL;
using System.Collections.Specialized;
using System.Web.UI.HtmlControls;
using System.Drawing;
using ZzimaBilling.AdminUI.Templates;

namespace ZzimaBilling.AdminUI.Forms
{
    public partial class Template : BasePage
    {
        #region Properties

        public TemplateBLL CurrentTemplate
        {
            get
            {
                if (ViewState["CurrentTemplate"] == null)
                {
                    TemplateBLL tempplateBLL = new TemplateBLL();
                    tempplateBLL.Name = tbxName.Text;
                    tempplateBLL.Mask = tbxMask.Text;
                    tempplateBLL.Services = GetListServices(lbxActualServices);
                    ViewState["CurrentTemplate"] = tempplateBLL;
                }
                return (TemplateBLL)ViewState["CurrentTemplate"];
            }
            set
            {
                ViewState["CurrentTemplate"] = (TemplateBLL)value;
            }
        }

        public string Action
        {
            get
            {
                if (ViewState["Action"] == null)
                {
                    ViewState["Action"] = "new";
                }
                return ViewState["Action"].ToString();
            }
            set
            {
                if (value == null)
                    ViewState["Action"] = "new";
                else
                    ViewState["Action"] = value;
            }
        }

        public int? PreviousServiceID
        {
            get
            {
                if (ViewState["PreviousServiceID"] == null)
                {
                    return -1;
                }
                return Convert.ToInt32(ViewState["PreviousServiceID"]);
            }
            set
            {
                ViewState["PreviousServiceID"] = value;
            }
        }

        public string PreviousServiceSettings
        {
            get
            {
                if (ViewState["PreviousServiceSettings"] == null)
                {
                    return null;
                }
                return ViewState["PreviousServiceSettings"].ToString();
            }
            set
            {
                ViewState["PreviousServiceSettings"] = value;
            }
        }

        public string ErrorMessage
        {
            get
            {
                if (ViewState["ErrorMessage"] == null)
                {
                    ViewState["ErrorMessage"] = string.Empty;
                    return string.Empty;
                }
                return ViewState["ErrorMessage"].ToString();
            }
            set
            {
                if (!string.IsNullOrEmpty(value.ToString()))
                {
                    ViewState["ErrorMessage"] = value;
                }
                else
                {
                    ViewState["ErrorMessage"] = null;
                }
            }
        } 

        #endregion

        #region Events

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(ErrorMessage))
            {
                ShowError();
            }
            else
                HideError();
            if (!IsPostBack)
            {
                btnSave.Click += new EventHandler(btnSave_Click);
                //this.PreRenderComplete += new EventHandler(Page_PreRenderComplete);
                int templateID = Convert.ToInt32(Request.QueryString["id"]);
                Action = Request.QueryString["action"];
                if (!String.IsNullOrEmpty(Action) && Action == "edit" && templateID > 0)
                {
                    TemplateBLL temp = LoadTemplate(templateID);
                    CurrentTemplate = temp;
                    RenderTemplate(temp);
                }
                if (Action == "new")
                {
                    FillListBox(lbxAllServices, GetAllServices());
                }
                tbxParameters.Visible = false;
            }
            
            if (IsPostBack)
            {
                CurrentTemplate.Services = GetListServices(lbxActualServices);
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
            string ClickScript = String.Format(addClickScript, btnSave.ClientID);

            Page.ClientScript.RegisterStartupScript(this.GetType(), "addClickFunctionScript", addClickFunctionScript.ToString(), true);
            Page.ClientScript.RegisterStartupScript(this.GetType(), "click_" + btnSave.ClientID, ClickScript, true);

        }

        protected List<ServiceBLL> GetListServices(ListBox lbxActualServices)
        {
            List<ServiceBLL> actualServices = new List<ServiceBLL>();
            for(int i = 0; i < lbxActualServices.Items.Count; i++)
            {
                int id = Int32.Parse(lbxActualServices.Items[i].Value);
                ServiceBLL curr = GetAllServices().GetServiceByID(id);
                ServiceBLL old = CurrentTemplate.Services.GetServiceByID(id);
                if (old != null)
                    curr.Settings = old.Settings;
                else
                    CurrentTemplate.Services.Add(curr);
                actualServices.Add(curr);
            }
            return actualServices;
        }

        protected void FillListBox(ListBox listBox, List<ServiceBLL> services)
        {
            listBox.Items.Clear();

            if (services != null)
            {
                foreach (ServiceBLL s in services)
                {
                    listBox.Items.Add(new ListItem(s.Name, s.ServiceID.ToString()));
                    if (s.ServiceID == PreviousServiceID)
                        listBox.SelectedIndex = listBox.Items.Count - 1;
                }
            }
        }

        protected void savePreviousSettings()
        {
            if (PreviousServiceID != null && PreviousServiceSettings != null)
            {
                PreviousServiceSettings = tbxParameters.Text;
                foreach (ServiceBLL service in CurrentTemplate.Services)
                {
                    if (service.ServiceID == PreviousServiceID.Value)
                        service.Settings = PreviousServiceSettings;
                }
            }
        }

        protected void lbxActualServices_SelectedIndexChanged(object sender, EventArgs e)
        {
            //1. Check what have been shown previous time and save it 
            savePreviousSettings();

            //2.  Display settings for chosen service
            string val = lbxActualServices.SelectedValue;
            int serviceID;
            tbxParameters.Visible = false;
            if (val != string.Empty)
            {
                serviceID = Convert.ToInt32(val);

                ServiceBLL svc = CurrentTemplate.GetServiceByID(serviceID);
                if (svc != null)
                {
                    tbxParameters.Text = CurrentTemplate.GetServiceByID(serviceID).Settings;
                }
                else
                    tbxParameters.Text = "";

                //3. Write current id and settings into view state
                PreviousServiceID = serviceID;
                PreviousServiceSettings = tbxParameters.Text;                
                tbxParameters.Visible = true;
            }
        }

        protected void btnRemove_Click(object sender, EventArgs e)
        {
            MoveService(lbxActualServices, lbxAllServices);
        }

        protected void btnAdd_Click(object sender, EventArgs e)
        {
            MoveService(lbxAllServices, lbxActualServices);
        }

        protected void MoveService(ListBox from, ListBox to)
        {
            int[] indexes = from.GetSelectedIndices();
            for (int i = indexes.Length-1; i >=0; --i)
            {
                int pos = indexes[i];
                to.Items.Add(from.Items[pos]);
                from.Items[pos].Selected = false;
                from.Items.Remove(from.Items[pos]);
            }

        }

        protected void btnSave_Click(object sender, EventArgs ea)
        {
            savePreviousSettings();

            try
            {
                TemplateBLL tmplate = CurrentTemplate;
                tmplate.Name = tbxName.Text;
                if (chDefault.Checked)
                    tmplate.Mask = null;
                else
                    tmplate.Mask = tbxMask.Text;
                tmplate.Services = CurrentTemplate.Services;
                int? templateId = null;
                if (Action != "new")
                    templateId = tmplate.ID;
 
                EmployeeDAL.saveTemplate(templateId, tmplate.ToTemplate(), employer.id);

                Page.RegisterStartupScript("RefreshParent","<script language='javascript'>RefreshParent()</script>");
                ((IErrorHandler)Master).showMessage(false, Translate("Error.Ok"), null);
            }
            catch(Exception e)
            {
                ((IErrorHandler)Master).showMessage(true, Translate("Error.Template.Save"), e.Message);
            }
        }

        #endregion

        #region Reading values from lbxActualServices

        #endregion

        #region Template Methods

        protected TemplateBLL LoadTemplate(int templateID)
        {
            if (templateID>0)
            {
                TemplateBLL template = new TemplateBLL(new EmployeeDAL().getTemplate(templateID));
                CurrentTemplate = template;
                return template;
                
            }
            return null;
        }

        protected void RenderTemplate(TemplateBLL templateBLL)
        {
            if (templateBLL != null)
            {
                tbxName.Text = templateBLL.Name;
                tbxMask.Text = templateBLL.Mask;
                FillListBoxes();
            }
        }

        protected void FillListBoxes()
        {
            List<ServiceBLL> all = GetAllServices();
            foreach (ServiceBLL service in all)
            {
                bool bactual = false;
                foreach (ServiceBLL actualService in CurrentTemplate.Services)
                {
                    if (service.ServiceID == actualService.ServiceID)
                    {
                        bactual = true;
                        break;
                    }
                }

                if(bactual)
                {
                    lbxActualServices.Items.Add(new ListItem(service.Name, service.ServiceID.ToString()));
                }
                else
                {
                    lbxAllServices.Items.Add(new ListItem(service.Name, service.ServiceID.ToString()));
                }
            }
        }

        #endregion

        #region Services Methods

        protected List<ServiceBLL> GetAllServices()
        {
            return new ServiceDAL().Select();
        }

        private List<ServiceBLL> InitializeSettings(List<ServiceBLL> actualServices)
        {
            if (actualServices != null)
            {
                List<ServiceBLL> list = new List<ServiceBLL>();
                foreach (ServiceBLL service in actualServices)
                {
                    service.Settings = CurrentTemplate.Services.GetSettings(service.ServiceID);
                    list.Add(service);
                }
                return list;
            }
            return null;
        }

        #endregion

        public void ShowError()
        {
            if(ErrorMessage!=string.Empty)
            {
                lblError.Text="* "+ErrorMessage;
                lblError.ForeColor=Color.Red;
                lblError.Visible = true;
            }
        }

        public void HideError()
        {
            lblError.Visible = false;
            lblError.Text = string.Empty;
        }

        protected void chDefault_CheckedChanged(object sender, EventArgs e)
        {
            tbxMask.Enabled = !chDefault.Checked;
            rfvMask.Enabled = !chDefault.Checked;
        }
    }

    public static class HelperClass
    {
        public static string GetName(this List<ServiceBLL> list, int id)
        {
            if (list != null)
            {
                ServiceBLL service = (from item in list
                                      where item.ServiceID == id
                                      select item).SingleOrDefault<ServiceBLL>();
                if (service != null)
                    return service.Name;
                return string.Empty;
            }
            return string.Empty;
        }

        public static string GetSettings(this List<ServiceBLL> list, int id)
        {
            if (list != null)
            {
                ServiceBLL service = (from item in list
                                      where item.ServiceID == id
                                      select item).SingleOrDefault<ServiceBLL>();
                if (service != null)
                    return service.Settings;
                return string.Empty;
            }
            return string.Empty;
        }

        public static ServiceBLL GetServiceByID(this List<ServiceBLL> list, int id)
        {
            ServiceBLL service = (from item in list
                                  where item.ServiceID == id
                                  select item).SingleOrDefault<ServiceBLL>();
            return service;
        }
    }
}
