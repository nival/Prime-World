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
     * Set service settings command request
     */
    public class SetServiceSettingsReq : ServiceRequest
    {
        /** name of owner */
        public string userName;

        /** name of service */
        public string serviceName;

        /** service settings - string with XML content */
        public string serviceSettings;

        /** password to service */
        public byte[] servicePassword;


        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            stm = SerializeHelper.o2s(stm, serviceSettings);
            return stm;
        }

        public override void validate()
        {
            base.validate();
            if (userName == null || userName.Trim().Length == 0 ||
                serviceName == null || serviceName.Trim().Length == 0 )
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Some of required fields are empty");
        }

    }

    /**
     * Set service settings command response
     */
    public class SetServiceSettingsResponse : Response
    {
    }
}
