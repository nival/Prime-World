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
    public class ConfirmWriteOffReq : ServiceRequest
    {
        public int reserveId;

        protected override MemoryStream getContent()
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, reserveId);
            return stm;
        }
    }

    /**
     * Get user profile command response
     */
    public class ConfirmWriteOffResponse : Response
    {

    }
}
