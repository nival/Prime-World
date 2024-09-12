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
using ZzimaBilling.BLL;
using ZzimaBilling.DAL;

namespace ZzimaBilling.DAL
{
    public class AdministratorDAL
    {
        //public static List<AdministratorBLL> GetAllAdministrators()
        //{
        //    var dataContext = new BillingDataContext().Administrators;
        //    var data=(from s in data
        //}

        public static Boolean ValidateAdministrator(AdministratorBLL administrator)
        {
            var dataContext = new BillingDataContext();
            Int32 count = (from adms in dataContext.Administrators
                         where adms.name == administrator.Name && adms.password == administrator.Password
                         select adms).Count<Administrator>();
            return count > 0;
        }

    }
}
