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
     * Transfer money command request
`    */
    public class MoneyTranseferReq : ServiceRequest
    {
        /** user name */
        public string srcUserName;
        /** source account name */
        public string srcAccount;
        /** dest user name */
        public string dstUserName;
        /** destination account name */
        public string dstAccount;
        /** amount */
        public decimal amount;
        /** reason */
        public string reason;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, srcUserName);
            stm = SerializeHelper.o2s(stm, srcAccount);
            stm = SerializeHelper.o2s(stm, dstUserName);
            stm = SerializeHelper.o2s(stm, dstAccount);
            stm = SerializeHelper.o2s(stm, amount);
            stm = SerializeHelper.o2s(stm, reason);
            return stm;
        }

        public override void validate()
        {
            base.validate();

            if ((srcUserName == null || srcUserName.Trim().Length == 0) ||
                (dstUserName == null || dstUserName.Trim().Length == 0) ||
                 amount <= 0 ||
                (reason == null || reason.Trim().Length == 0) )
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Some of required fields are empty");
        }

    }

    /**
     * Transfer money command response
     */
    public class MoneyTranseferResponse : Response
    {

    }
}
