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
     * Get service settings command request
     */
    public class GetServiceSettingsReq : ServiceRequest
    {
        /** name of owner */
        public string userName;
        /** name of service */
        public string serviceName;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            return stm;
        }
        
        public override void validate()
        {
            if (userName == null || userName.Trim().Length == 0 ||
                serviceName == null || serviceName.Trim().Length == 0)
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Empty userName or serviceName fields");
        }
    }

    /**
     * Get service settings command response
     */
    public class GetServiceSettingsResponse : Response
    {
        /** string with XML content */
        public string serviceSettings;
    }
}
