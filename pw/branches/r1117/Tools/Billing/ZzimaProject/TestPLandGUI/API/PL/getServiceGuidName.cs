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
     * Subscribe service command request
     */
    public class GetServiceGuidNameReq : ServiceRequest
    {
        /** user name */
        public int userid;
        /** name of service to subscribe */
        public string serviceName;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userid);
            stm = SerializeHelper.o2s(stm, serviceName);
            return stm;
        }

        public override void validate()
        {
            if (serviceName == null )
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Empty userName or serviceName fields");
        }

    }

    /**
     * Subscribe service command response
     */
    public class GetServiceGuidNameResponse : Response
    {
        /** linked account name */
        public string accauntName;
    }
}
