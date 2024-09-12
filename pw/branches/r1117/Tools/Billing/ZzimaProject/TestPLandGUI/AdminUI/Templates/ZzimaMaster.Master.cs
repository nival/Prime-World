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
using System.Collections.Generic;
using ZzimaBilling.AdminUI.BLL;
using System.Text;


namespace ZzimaBilling.AdminUI.Templates
{
    public partial class ZzimaMaster : System.Web.UI.MasterPage, IErrorHandler
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Context.User.Identity.IsAuthenticated)
            {
                FormsAuthentication.RedirectToLoginPage();
                Response.End();
            }

            resetMessage();
        }

        protected void Logoff_Click(object sender, EventArgs e)
        {
            FormsAuthentication.SignOut();
            FormsAuthentication.RedirectToLoginPage();
            Response.End();
        }
        #region IErrorHandler Members

        public void showMessage(bool err, string shortMsg, string fullMsg)
        {

            mainInfoPanel.Visible = shortMsg != null;
            if (shortMsg == null)
                return;

            mainInfoPanel.CssClass = err ? "errorMessageBar" : "infoMessageBar";
            mainInfoMessage.Text = shortMsg;
            mainInfoPanel.ToolTip = fullMsg == null ? shortMsg : fullMsg;

        }

        public void resetMessage()
        {
            showMessage(false, null, null);
        }

        #endregion
    }
}
