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
     * Activate promo-code command request
     */
    public class PromoActivateReq : ServiceRequest
    {
        /** user name */
        public string userName;
        /** source account name */
        public string promoCode;
        /** account */
        public string account;


        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            stm = SerializeHelper.o2s(stm, promoCode);
            return stm;
        }
    }

    /**
     * Activate promo-code command response
     */
    public class PromoActivateResponse : Response
    {

    }
}
