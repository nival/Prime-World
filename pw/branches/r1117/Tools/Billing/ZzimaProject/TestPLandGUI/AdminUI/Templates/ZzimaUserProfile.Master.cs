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

namespace ZzimaBilling.AdminUI.Templates
{
    public partial class ZzimaUserProfile : System.Web.UI.MasterPage, IErrorHandler
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            userPageInfoPanel.EnableViewState = false;
            //resetMessage();
        }
        
        #region IErrorHandler Members

        public void showMessage(bool err, string shortMsg, string fullMsg)
        {

            userPageInfoPanel.Visible = shortMsg != null;
            if (shortMsg == null)
                return;

            userPageInfoPanel.CssClass = err ? "errorMessageBar" : "infoMessageBar";
            userPageInfoMessage.Text = shortMsg;
            userPageInfoPanel.ToolTip = fullMsg == null ? shortMsg : fullMsg;

        }

        public void resetMessage()
        {
            showMessage(false, null, null);
        }

        #endregion
    }
}
