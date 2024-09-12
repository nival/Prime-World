using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Security;

namespace ZzimaBilling.AdminUI.Forms.UserProfilePages
{
    //Base page class for all UserProfile's pages
    public class UserProfileBasePage : BasePage
    {
        public int UserID
        {
            get
            {
                string UserId = null;

                //First try to retrieve User ID from QueryString
                if (!String.IsNullOrEmpty(Request.QueryString["id"]))
                {
                    UserId = Request.QueryString["id"];
                    Session["UserId"] = UserId;
                }
                //Else get it from Session
                else
                {
                    if (Session["UserId"] != null)
                        UserId = Session["UserId"].ToString();
                }

                //Check given string and return it
                if (!String.IsNullOrEmpty(UserId))
                {
                    return Convert.ToInt32(UserId);
                }
                else
                {
                    FormsAuthentication.RedirectToLoginPage();
                    Response.End();
                    return 0;
                }
            }
        }
    }
}
