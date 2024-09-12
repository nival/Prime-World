using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Xml.Linq;
using System.IO;
using ZzimaBilling.API.Common;

namespace ZzimaBilling.API.PL
{
    public class GetValuePSDetailedReq : ServiceRequest
    {
        public string userName;
        public string ps;

        protected override MemoryStream getContent ( )
        {
            MemoryStream stm = base.getContent();
            stm = SerializeHelper.o2s(stm, userName);
            return stm;
        }

        public override void validate ( )
        {
        }
    }
    public class GetValuePSDetailedResponse : Response
    {
        public decimal amount;
    }
}