using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web.Security;
using System.Web;
using ZzimaBilling.AdminUI.BLL;

namespace ZzimaBilling.SL
{
    public class ZzimaSiteMapProvider : System.Web.XmlSiteMapProvider
    {
        public override bool IsAccessibleToUser(HttpContext context, SiteMapNode node)

        {
            System.Collections.IList cs = node.Roles;
            if (cs == null || cs.Count == 0)
                return true;
            if (cs.Contains("*")||cs.Contains("?"))
                return true;

            foreach(string rl in  cs)
            {
                if (System.Web.HttpContext.Current.User.IsInRole(rl))
                    return true;
            }
            return false;
       }

    }
}
