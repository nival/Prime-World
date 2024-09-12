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
using ZzimaBilling.API.Common;

namespace ZzimaBilling.API.PL
{
    /**
     * Register user command parameters
     */
    public class RegisterUserReq : ServiceRequest
    {
        /** user name */
        public string userName;
        /** hash of password */
        public byte[] userPassword;
        /** e-mail */
        public string userEmail;
        /** referal code */
        public string userReferal;
        
        public override void validate()
        {
            base.validate();

            if ((userName == null || userName.Trim().Length == 0) ||
                 (userPassword == null || userPassword.Length == 0) ||
                 (userEmail == null || userEmail.Trim().Length == 0))
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Some of required fields are empty");
        }
    }

    /**
     * Register user command response
     */
    public class RegisterUserResponse : Response
    {
        /** internal user id */
        public int userId = -1;
        /** main account name */
        public string accountName;
    }
}
