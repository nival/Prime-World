using System;
using System.Data;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

namespace ZzimaBilling.BLL
{
    public class AdministratorBLL
    {
        public Int32 AdministratorID { get; set; }
        public String Name { get; set; }
        public String Password { get; set; }

        public AdministratorBLL() { }

        public AdministratorBLL(Int32 administratorID, String name, String password)
        {
            this.AdministratorID = administratorID;
            this.Name = name;
            this.Password = password;
        }

        public AdministratorBLL(String name, String password)
        {
            this.Name = name;
            this.Password = password;
        }
    }
}
