using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Linq;
using System.IO;
using ZzimaBilling.API.Common;

namespace ZzimaBilling.API.PL
{
    /**
     * Set user profile command request
     */
    public class GetOperationDetailsReq : ServiceRequest
    {
        /** user name */
        public string userName;
        public int operationId;

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
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Some of required fields are empty");
        }
    }

    /**
     * Set user profile user command response
     */
    public class GetOperationDetailsResponse : Response
    {
        /** current balance? excluding CBT */
        public List<OperationWriteOff> writeOffs;
    }

    public class OperationWriteOff
    {
        public int paymentSystemId;
        public decimal amount;
    }

}
