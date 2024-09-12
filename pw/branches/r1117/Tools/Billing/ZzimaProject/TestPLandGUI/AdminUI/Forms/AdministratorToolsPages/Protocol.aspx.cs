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
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.DAL;
using System.Collections.Generic;

namespace ZzimaBilling.AdminUI.Forms
{
    public partial class Protocol : System.Web.UI.Page
    {
        private ProtocolSettings sett;

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
                UpdatePage();
            else
                SaveSettings();
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
            string ClickScript = String.Format(addClickScript, btnApply.ClientID);

            Page.ClientScript.RegisterStartupScript(this.GetType(), "addClickFunctionScript", addClickFunctionScript.ToString(), true);
            Page.ClientScript.RegisterStartupScript(this.GetType(), "click_" + btnApply.ClientID, ClickScript, true);

        }

        private void SaveSettings()
        {
            sett = new ProtocolSettings();
            SaveGeneralSett();
            SaveServicesSett();
            SavePSystemsSett();

            EmployeeDAL.saveProtocolSettings(sett);
        }

        private void SaveGeneralSett()
        {
            sett.servicesLevel = ServicesSett.SelectedIndex+1;
            sett.servicesPeriod = Int32.Parse(ServicesPeriod.Text);

            sett.paymentSystemsLevel = PSystemSett.SelectedIndex+1;
            sett.paymentSystemsPeriod = Int32.Parse(PSystemsPeriod.Text);

            sett.requestsLevel = RequestsSett.SelectedIndex+1;
            sett.requestsPeriod = Int32.Parse(RequestsPeriod.Text);
        }

        private void SaveServicesSett()
        {
            sett.servicesSel = new List<Int32>();
            for (int i = 0; i < ServicesList.Items.Count; i++)
            {
                if( ServicesList.Items[i].Selected == true)
                    sett.servicesSel.Add(Int32.Parse(ServicesList.Items[i].Value));
            }
        }

        private void SavePSystemsSett()
        {
            sett.paymentSystemsSel = new List<Int32>();
            for (int i = 0; i < PSystemsList.Items.Count; i++)
            {
                if (PSystemsList.Items[i].Selected == true)
                    sett.paymentSystemsSel.Add(Int32.Parse(PSystemsList.Items[i].Value));
            }
        }

        private void UpdatePage()
        {
            sett = EmployeeDAL.getProtocolSettings();
            ConfigureSettings();
            ConfigureServicesList();
            ConfigurePSystemsList();
        }

        private void ConfigureSettings()
        {
            if (sett.servicesLevel > 0 && sett.servicesLevel <= ServicesSett.Items.Count)
                ServicesSett.Items[sett.servicesLevel-1].Selected = true;
            if (sett.paymentSystemsLevel > 0 && sett.paymentSystemsLevel <= PSystemSett.Items.Count)
                PSystemSett.Items[sett.paymentSystemsLevel-1].Selected = true;
            if (sett.requestsLevel > 0 && sett.requestsLevel <= RequestsSett.Items.Count)
                RequestsSett.Items[sett.requestsLevel-1].Selected = true;
            ServicesPeriod.Text = sett.servicesPeriod.ToString();
            PSystemsPeriod.Text = sett.paymentSystemsPeriod.ToString();
            RequestsPeriod.Text = sett.requestsPeriod.ToString();
        }

        private void ConfigureServicesList()
        {
            int i;
            for (i = 0; i < sett.services.Count; i++)
            {
                ListItem item = new ListItem(sett.services[i].Name, sett.services[i].ServiceID.ToString());
                ServicesList.Items.Add(item);
            }
            for(i = 0; i < sett.servicesSel.Count; i++)
            {
                ListItem item = ServicesList.Items.FindByValue(sett.servicesSel[i].ToString());
                if (item != null)
                    item.Selected = true;
            }
        }

        private void ConfigurePSystemsList()
        {
            int i;            
            for (i = 0; i < sett.paymentSystems.Count; i++)
            {
                ListItem item = new ListItem(sett.paymentSystems[i].Name, sett.paymentSystems[i].PSystemID.ToString());
                PSystemsList.Items.Add(item);
            }

            for (i = 0; i < sett.paymentSystemsSel.Count; i++)
            {
                ListItem item = PSystemsList.Items.FindByValue(sett.paymentSystemsSel[i].ToString());
                if (item != null)
                    item.Selected = true;
            }
        }
    }
}
