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
    public partial class ZzimaMasterReports : System.Web.UI.MasterPage, IErrorHandler
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            reportsInfoPanel.EnableViewState = false;
        }
        
        #region IErrorHandler Members

        public void showMessage(bool err, string shortMsg, string fullMsg)
        {

            reportsInfoPanel.Visible = shortMsg != null;
            if (shortMsg == null)
                return;

            reportsInfoPanel.CssClass = err ? "errorMessageBar" : "infoMessageBar";
            reportsInfoMessage.Text = shortMsg;
            reportsInfoPanel.ToolTip = fullMsg == null ? shortMsg : fullMsg;

        }

        public void resetMessage()
        {
            showMessage(false, null, null);
        }

        #endregion
    }
}
