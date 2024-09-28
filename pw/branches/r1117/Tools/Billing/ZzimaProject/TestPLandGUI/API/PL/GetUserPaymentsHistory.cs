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
     * Single history record
     */
    public class UserPaymentsHistoryRecord
    {
        /** date-time of payment */
        public DateTime date;
        /** amount */
        public decimal amount;
        /** payment system */
        public string paymentSystem;

    }

    /**
     * Set user profile command request
     */
    public class GetUserPaymentsHistoryReq : ServiceRequest
    {
        /** user name */
        public string userName;
        /** from date */
        public DateTime from;
        /** to date */
        public DateTime to;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            stm = SerializeHelper.o2s(stm, from);
            stm = SerializeHelper.o2s(stm, to);
            return stm;
        }

        public override void validate()
        {
            base.validate();
            if (from > to)
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Incorrect time period");
        }
    }

    /**
     * Set user profile user command response
     */
    public class GetUserPaymentsHistoryResponse : Response
    {
        /** list of payments */
        public UserPaymentsHistoryRecord[] payments;
    }
}
