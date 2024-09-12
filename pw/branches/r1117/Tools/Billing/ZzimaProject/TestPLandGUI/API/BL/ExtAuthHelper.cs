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
using ZzimaBilling.API.Common;
using System.Collections.Generic;
using System.Text;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Net;
using System.IO;
using System.Data.Sql;
using System.Data.SqlClient;
using System.Security.Cryptography;

namespace ZzimaBilling.API.BL
{
    public class ExtAuthHelper
    {
        public static bool authorize(string className, string userName, string password, string email)
        {
            //////////from itos - com version
            //try
            //{
            //    AuthFactoryClass fac = new AuthFactoryClass();
            //    return fac.ExtAuthorize(className, userName, password, email) != 0;
            //}
            //catch(Exception e)
            //{
            //    throw new ApiException(ApiException.ErrorCode.E_UNEXPECTED, e.ToString());
            //}
            //////////from itos - com version
            if (className == "rambler")
            {
                return RamblerAuthorize(userName, password, email);
            }
            return false;
        }
        public static bool RamblerAuthorize(string userName, string password, string email)
        {
            byte[] resBytes = Convert.FromBase64String(password);
            StringBuilder sBuilder = new StringBuilder();
            for (int i = 0; i < resBytes.Length; i++)
            {
                sBuilder.Append(resBytes[i].ToString("x2"));
            }
            string passwordString = sBuilder.ToString();
            
            string post_data = String.Format("mode=checklogin&login={0}&passw={1}&md5=1", email, passwordString);

            string uri = "http://int-id.rambler.ru/script/auth.cgi";
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(uri);
            request.KeepAlive = false;
            request.ProtocolVersion = HttpVersion.Version10;
            request.Method = "POST";
            request.Timeout = 10000;

            byte[] postBytes = Encoding.ASCII.GetBytes(post_data);

            request.ContentType = "application/x-www-form-urlencoded";
            request.ContentLength = postBytes.Length;
            int stCode = 0;
            bool flag = false;
            try
            {
                Stream requestStream = request.GetRequestStream();
                requestStream.Write(postBytes, 0, postBytes.Length);
                requestStream.Close();
                HttpWebResponse response = (HttpWebResponse)request.GetResponse();
                string result = new StreamReader(response.GetResponseStream()).ReadToEnd();
                stCode = (int)response.StatusCode;
                if (response.StatusCode == HttpStatusCode.OK)
                    flag = true;
            }
            catch { }
            return flag;
        }
    }
}
