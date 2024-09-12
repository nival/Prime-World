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
using System.Web.UI.MobileControls;
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.DAL;
using System.Collections.Generic;
using System.Text;
using System.Security.Cryptography;
using ZzimaBilling.AdminUI.Templates;

namespace ZzimaBilling.AdminUI.Forms.UserProfilePages
{
    public partial class GmaTool : UserProfileBasePage
    {
  /*      protected override void OnInit(EventArgs e)
        {
            base.OnPreRender(e);
        }
    */

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                FillPaymentSystems(ddlPaymentSystem);                
            }

            ((IErrorHandler)this.Master).resetMessage();
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
            string ClickScript = String.Format(addClickScript, btnAccept.ClientID);

            Page.ClientScript.RegisterStartupScript(this.GetType(), "addClickFunctionScript", addClickFunctionScript.ToString(), true);
            Page.ClientScript.RegisterStartupScript(this.GetType(), "click_" + btnAccept.ClientID, ClickScript, true);

        }

        protected void FillPaymentSystems(DropDownList ddl)
        {
            List<PSystemBLL> psystems = PaymentSystemDAL.SelectReal();
            //List<PaymentSystemAccountBLL> ppsystems = UserDAL.GetPaymentSystemReplenishments(UserID);
            ddl.Items.Clear();
            foreach (PSystemBLL item in psystems)
            {
                ddl.Items.Add(new ListItem(item.Name, item.PSystemID.ToString()));
            }
        }

        protected void rblWriteOff_RadioChanged(object sender, EventArgs e)
        {
            ddlPaymentSystem.Visible = (rblWriteOff.SelectedIndex == 0);
        }

        protected void onclick_writeoff(object sender, EventArgs e)
        {

            int systemId = -1;
            switch(this.rblWriteOff.SelectedIndex)
            {
                case 0:
                    systemId = Convert.ToInt32(ddlPaymentSystem.SelectedValue);
                    break;
                default:                        
                case 1:
                    systemId = 1;
                    break;
                case 2:
                    systemId = 2;
                    break;
            }

            try
            {
                employer.writeOff(tpPassword.Text, UserID, Convert.ToDecimal(tpSum.Text), systemId, tpComment.Text);
                ((IErrorHandler)this.Master).showMessage(false, Translate("Error.Ok"), null);
            }
            catch(Exception ex)
            {
                ((IErrorHandler)this.Master).showMessage(true, Translate("Error.GMA.Writeoff"), ex.Message);
            }
            
        }

    }
}
