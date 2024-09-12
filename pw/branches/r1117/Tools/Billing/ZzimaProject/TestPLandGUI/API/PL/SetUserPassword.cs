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
using System.IO;
using ZzimaBilling.API.Common;

namespace ZzimaBilling.API.PL
{
    /**
     * Set user profile command request
     */
    public class SetUserPasswordReq : ServiceRequest
    {
        /** user name */
        public string userName;
        /** hash of user's password */
        public byte[] userPassword;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            stm = SerializeHelper.o2s(stm, userPassword);
            return stm;
        }
    }

    /**
     * Set user profile user command response
     */
    public class SetUserPasswordResponse : Response
    {
    }
}
