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
     * Authorize user command request
     */
    public class AuthorizeUserReq : ServiceRequest
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
        
        public override void validate()
        {
            base.validate();

            if ((userName == null || userName.Trim().Length == 0) ||
                 (userPassword == null || userPassword.Length == 0) )
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Some of required fields are empty");
        }
    }

    /**
     * Authorize user command response
     */
    public class AuthorizeUserResponse : Response
    {
        /** internal user id */
        public int userId = -1;
    }
}
