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
    public class SetUserProfileReq : ServiceRequest
    {
        /** user name */
        public string userName;
        /** email address */
        public string email;
        /** display name */
        public string displayName;
        /** agreement accepted */
        public bool agreementAccepted;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            stm = SerializeHelper.o2s(stm, email);
            stm = SerializeHelper.o2s(stm, displayName);
            stm = SerializeHelper.o2s(stm, agreementAccepted);
            return stm;
        }
    }

    /**
     * Set user profile user command response
     */
    public class SetUserProfileResponse : Response
    {
    }
}
