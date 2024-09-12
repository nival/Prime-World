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
    public class ZeroAwardMoneyReq : ServiceRequest
    {
        public string[] users;
        public bool zeroAll;

        //protected override MemoryStream getContent()
        //{
        //    MemoryStream stm = base.getContent();
        //    stm = SerializeHelper.o2s(stm, zeroAll);
        //    return stm;
        //}

        //public override void validate()
        //{
        //    base.validate();
        //    if (userName == null || userName.Trim().Length == 0)
        //        throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Some of required fields are empty");
        //}
    }

    public class ZeroAwardMoneyResponse : Response
    {
        public decimal zeroedAmount;
        //public user[] users;
    }
    public class user
    {
        public string name;
        public int errorCode;
    }
}