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
using System.Globalization;
using System.Text;
using System.IO;
using System.Security.Cryptography;
using ZzimaBilling.API.Common;

namespace ZzimaBilling.API.PL
{
    /**
     * Base response for system
     */
    public class Response
    {
        /** result code. 0 if no errors */
        public int code = 0;
        /** error message id any */
        public string message;
    }

    /**
    * Base request for system
    */
    public abstract class ServiceRequest
    {
        /** crc of message content */
        public byte[] crc;
        /** service name */
        public string fromServiceName;

       public byte[] getCrc(System.Web.HttpContext ctx, byte[] password)
       {
            MemoryStream content = getContent();
            //SerializeHelper.o2s(content, ctx.Request.UserHostAddress);
            content.Write(password,0,password.Length);
            byte[] res = content.ToArray();
            MD5 md5Hasher = MD5.Create();
            return md5Hasher.ComputeHash(res, 0, res.Length);
        }


        protected virtual MemoryStream getContent()
        {
            return SerializeHelper.o2s(new MemoryStream(), fromServiceName);
        }

        public virtual void validate()
        {
            if (crc == null || fromServiceName == null)
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Empty crc or fromServiceName fields");
        }
        
    }

}
