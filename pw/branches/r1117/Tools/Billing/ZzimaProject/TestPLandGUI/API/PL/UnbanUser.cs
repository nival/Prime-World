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
     * Unban user command request
     */
    public class UnbanUserReq : ServiceRequest
    {
        /** name of user to ban */
        public string userName;
        /** reason of operation */
        public string reason;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            stm = SerializeHelper.o2s(stm, reason);
            return stm;
        }

        public override void validate()
        {
            base.validate();
            if (userName == null || userName.Trim().Length == 0 ||
                reason == null || reason.Trim().Length == 0)
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Empty userName or serviceName fields");
        }
    }

    /**
     * Unban user command response
     */
    public class UnbanUserResponse : Response
    {
    }
}
