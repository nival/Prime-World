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

    public class ByIdProfileInfo
    {
        public string userName;
        /** email address */
        public string email;
        /** referal code */
        public string referalCode;
        /** creation date */
        public DateTime creationDate;
        /** display name of user */
        public string displayName;
        /** partner program name */
        public string partner;
        /** user agreement accept state */
        public bool agreementAccepted;
        public string banSn;

    }
    /**
     * Get user profile command request
     */
    public class ByIdGetUserProfileReq : ServiceRequest
    {
        /** user name */
        public int userid;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userid);
            return stm;
        }
    }

    /**
     * Get user profile command response
     */
    public class ByIdGetUserProfileResponse : Response
    {
        public ByIdProfileInfo info;
    }
}