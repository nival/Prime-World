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
    public class ServiceShortInfo
    {
        /** user name */
        public string serviceName;
        /** source account name */
        public bool subscribed;

    }

    /**
     * Get services list command request
     */
    public class GetServicesListReq : ServiceRequest
    {
        /** user name */
        public string userName;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            return stm;
        }

        public override void validate()
        {
            base.validate();
            if (userName == null || userName.Trim().Length == 0)
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Empty userName field");
        }

    }

    /**
     * Get services list command response
     */
    public class GetServicesListResponse : Response
    {
        /** array of services */
        public ServiceShortInfo[] services;
    }

}
