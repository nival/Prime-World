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
using ZzimaBilling.AdminUI.Forms.UserProfilePages;

namespace ZzimaBilling.Admin.UserProfilePages
{
    public partial class GeneralInfo : UserProfileBasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                RenderGeneralInfo(UserDAL.GetUserGeneralInfo(this.UserID));
            }
        }

        protected void RenderGeneralInfo(UserGeneralInfoBLL userInfo)
        {
            if (userInfo != null)
            {
                lblUserName.Text = userInfo.Username;
                lblUserId.Text = userInfo.ID.ToString();
                lblEmail.Text = userInfo.Email;
                lblReferalLink.Text = userInfo.RefferalCode;
                lblRegDate.Text = userInfo.RegisteredDate.ToString("dd/MM/yyyy");
            }
        }
    }
}
