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
    public class SubscribeServiceReq : ServiceRequest
    {
        /** user name */
        public string userName;
        /** name of service to subscribe */
        public string serviceName;
        /** password for service */
        public byte[] servicePassword;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            stm = SerializeHelper.o2s(stm, serviceName);
            stm = SerializeHelper.o2s(stm, servicePassword);
            return stm;
        }
        
        public override void validate()
        {
            base.validate();
            if (userName == null || userName.Trim().Length == 0 ||
                serviceName == null || serviceName.Trim().Length == 0)
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Empty userName or serviceName fields");
        }

    }

    /**
     * Subscribe service command response
     */
    public class SubscribeServiceResponse : Response
    {
        /** linked account name */
        public string accauntName;
    }
}
