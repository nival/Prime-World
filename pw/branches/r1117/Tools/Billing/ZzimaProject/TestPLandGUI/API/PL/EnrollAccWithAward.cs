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
      * Replenish user's account command request
      */
    public class EnrollAccWithAwardReq : ServiceRequest
    {
        /** user name */
        public string userName;
        /** amount */
        public decimal amount;
        public decimal award;
        /** account name */
        public string account;
        /** reason */
        public string reason;
        /** payment system name */
        public string paymentSystem;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            stm = SerializeHelper.o2s(stm, amount);
            stm = SerializeHelper.o2s(stm, account);
            stm = SerializeHelper.o2s(stm, reason);
            stm = SerializeHelper.o2s(stm, paymentSystem);
            return stm;
        }

        public override void validate()
        {
            base.validate();

            if ((userName == null || userName.Trim().Length == 0) ||
                 amount <= 0 ||
                (paymentSystem == null || paymentSystem.Trim().Length == 0))
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Some of required fields are empty");
        }

    }

    /**
     *  Replenish user's account command response
     */
    public class EnrollAccWithAwardResponse : Response
    {

    }
}
