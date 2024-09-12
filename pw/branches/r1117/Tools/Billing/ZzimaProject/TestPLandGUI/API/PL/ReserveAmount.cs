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
     * Write off user's account command request
     */
    public class ReserveAmountReq : ServiceRequest
    {
        public string userName;
        public decimal amount;
        public string reason;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            stm = SerializeHelper.o2s(stm, amount);
            stm = SerializeHelper.o2s(stm, reason);
            return stm;
        }

        public override void validate()
        {
            base.validate();

            if ((userName == null || userName.Trim().Length == 0) || amount <= 0 ||
                (reason == null || reason.Trim().Length == 0))
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Some of required fields are empty");
        }
    }

    /**
     * Write off user command response
     */
    public class ReserveAmountResponse : Response
    {
        public decimal reserveId;
    }
}