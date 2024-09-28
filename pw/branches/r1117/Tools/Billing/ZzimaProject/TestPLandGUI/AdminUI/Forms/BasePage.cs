using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using ZzimaBilling.AdminUI.BLL;
using System.Web.UI;
using System.Web.UI.WebControls;
using ZzimaBilling.AdminUI.Templates;
using System.Web.Security;

namespace ZzimaBilling.AdminUI.Forms
{
    public class BasePage : System.Web.UI.Page
    {
        public Control FindControlRecursive(string Id)
        {
            return FindControlRecursive(this, Id, null);
        }

        public Control FindControlRecursive(string Id, Type t)
        {
            return FindControlRecursive(this, Id, t);
        }

        public Control FindControlRecursive(Control Root, string Id, Type t)
        {

            if (t == null || t ==Root.GetType())
            {
                if (Root.ID != null && Root.ID == Id)
                    return Root;
            }

            if (!Root.HasControls())
                return null;


            foreach (Control Ctl in Root.Controls )
            {
                Control FoundCtl = FindControlRecursive(Ctl, Id, t);
                if (FoundCtl != null)
                    return FoundCtl;
            }
            return null;
        }


        public string Translate(string key)
        {
            Object obj = HttpContext.GetGlobalResourceObject("AdminUI", key);
            if (obj == null)
                return key;
            return obj.ToString();
        }

        public Employer employer
        {
            get
            {
                if (Session[Employer.SESSION_KEY] != null)
                    return (Employer)Session[Employer.SESSION_KEY];
                else
                {
                    FormsAuthentication.RedirectToLoginPage();
                    Response.End();
                    return null;
                }
            }
        }

        public void ShowMessage(bool isError, string shortMessage, string longMessage)
        {
            if (Master == null) return;
            if (Master is ZzimaMaster)
                (Master as ZzimaMaster).showMessage(isError, shortMessage, longMessage);
            if (Master is ZzimaUserProfile)
                (Master as ZzimaUserProfile).showMessage(isError, shortMessage, longMessage);
        }
    }
}
