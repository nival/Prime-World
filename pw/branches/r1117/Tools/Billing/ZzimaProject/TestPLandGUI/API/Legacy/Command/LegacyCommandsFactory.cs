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
using System.Xml;
using System.Xml.Linq;

namespace ZzimaBilling.API.Legacy.Command
{
    public class LegacyCommandsFactory
    {
        public static ILegacyCommand Resolve(XmlNode nd)
        {
            if (nd == null)
                throw new Exception("Cannot find command block");

            ILegacyCommand res;
            switch (nd.Name)
            {
                case "accountLogin":
                    res = new AccountLogin(nd);
                    break;
                case "getUserMoney":
                    res = new GetUserMoney(nd);
                    break;
                case "removeUserMoney":
                    res = new RemoveUserMoney(nd);
                    break;
                case "addUserMoney":
                    res = new AddUserMoney(nd);
                    break;
                case "transferUserMoney":
                    res = new TransferUserMoney(nd);
                    break;
                default:
                    throw new Exception("Unknown command: " + nd.Name);
            }
            
            return res;
        }

    }
}
