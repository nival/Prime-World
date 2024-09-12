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

namespace ZzimaBilling.AdminUI.Forms
{
    public partial class Login : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            Control ctl = lgnPanel.FindControl("LoginLinkButton");
            if (ctl != null && ctl is IButtonControl)
                lgnPanel.Attributes.Add("onkeypress", string.Format("javascript:return WebForm_FireDefaultButton(event, '{0}')", ctl.ClientID));
            
            //lgnPanel.Focus();
            //HtmlForm mainform = (HtmlForm)Master.FindControl("form1");
            //LinkButton loginbtn =
            //(LinkButton)lgnPanel.FindControl("LoginLinkButton");
            //if (mainform != null && loginbtn != null)
            //{
            //    mainform.DefaultButton = loginbtn.UniqueID;
            //}
        }

        protected void lgnPanel_LoggedIn(object sender, EventArgs e)
        {
            // Manually redirect to DestinationPageUrl as Framework doesn't give property precedence over the
            // referring page (ReturnUrl), which it should, according to Login.DestinationPageUrl documentation 
            Response.Redirect(ResolveClientUrl(lgnPanel.DestinationPageUrl));
        }

        protected void Page_PreRender(object sender, EventArgs e)
        {
            JavaScriptLoad();
        }

        private void JavaScriptLoad()
        {
            Control ctl = lgnPanel.FindControl("LoginLinkButton");
            StringBuilder addClickFunctionScript = new StringBuilder();
            addClickFunctionScript.Append(" function addClickFunction(id) {{ ");
            addClickFunctionScript.Append(" var b = document.getElementById(id); ");
            addClickFunctionScript.Append(" if (b && typeof(b.click) == 'undefined') b.click = function() {{ ");
            addClickFunctionScript.Append(" var result = true; if (b.onclick) result = b.onclick(); ");
            addClickFunctionScript.Append(" if (typeof(result) == 'undefined' || result) {{ eval(b.getAttribute('href')); }} ");
            addClickFunctionScript.Append(" }}}}; ");

            string addClickScript = "addClickFunction('{0}');";
            string ClickScript = String.Format(addClickScript, ctl.ClientID);

            Page.ClientScript.RegisterStartupScript(this.GetType(), "addClickFunctionScript", addClickFunctionScript.ToString(), true);
            Page.ClientScript.RegisterStartupScript(this.GetType(), "click_" + ctl.ClientID, ClickScript, true);
        }
        
    }
}
