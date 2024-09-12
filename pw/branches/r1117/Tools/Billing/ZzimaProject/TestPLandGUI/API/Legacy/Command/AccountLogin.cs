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
using System.Xml;
using System.Xml.Xsl;
using System.IO;
using System.Text;
using System.Security.Cryptography;
using ZzimaBilling.API.Common;
using ZzimaBilling.API.BL;
using ZzimaBilling.API.PL;

namespace ZzimaBilling.API.Legacy.Command
{

    /*
    <accountLogin>
    <username>login encoded base64</username>
    <password>md5 password</password>
    <remote_addr>IP address</remote_addr>
    </accountLogin>
    */

    /**
     * Class implements processing of legacy API command accountLogin
     */
    public class AccountLogin : ILegacyCommand
    {
        private string userName;
        private byte[] password;
        private string remoteIp;

        public AccountLogin(XmlNode nd): base(nd)
        {
        }

        string getMd5Hash(string input)
        {
            MD5 md5Hasher = MD5.Create();
            byte[] data = md5Hasher.ComputeHash(Encoding.UTF8.GetBytes(input));
            StringBuilder sBuilder = new StringBuilder();
            for (int i = 0; i < data.Length; i++)
            {
                sBuilder.Append(data[i].ToString("x2"));
            }
            return sBuilder.ToString();
        }

        public void Parse(XmlNode nd)
        {

            // get username
            XmlNode node = nd.SelectSingleNode("./username");
            if (node == null)
                throw new Exception("username is empty");
            userName = System.Text.Encoding.UTF8.GetString(Convert.FromBase64String(node.InnerText));
            // get password
            node = nd.SelectSingleNode("./password");
            if (node == null)
                throw new Exception("password is empty");

            string wrapPass = "<password>" + node.InnerText + "</password>";
            XmlTextReader r = new XmlTextReader(new StringReader(wrapPass));
            r.Read();
            byte[] buf = new byte[80 * 2];
            int bytesRead = r.ReadBinHex(buf, 0, buf.Length);
            password = new byte[bytesRead];
            Array.Copy(buf, 0, password, 0, bytesRead);
            // get ip

            node = nd.SelectSingleNode("./remote_addr");
            if (node == null)
                throw new Exception("remote_addr is empty");
            remoteIp = node.InnerText;
        }

        public override void Execute(HttpContext context)
        {
            XmlDocument resp = new XmlDocument();
            resp.CreateXmlDeclaration("1.0", "utf-8", null);
            XmlElement nroot = (XmlElement)resp.AppendChild(resp.CreateElement("xml"));
            try
            {
                Parse(request);

                User us = User.legacyAuthorize(context, userName, password, remoteIp);
                ProfileInfo pi = User.getProfile(userName);

                XmlElement nuser = (XmlElement)nroot.AppendChild(resp.CreateElement("user"));
                // add user id
                XmlElement nuserid = (XmlElement)nuser.AppendChild(resp.CreateElement("user_id"));
                nuserid.InnerText = us.id.ToString();
                // add password
                XmlElement npassword = (XmlElement)nuser.AppendChild(resp.CreateElement("password"));
                StringWriter sw = new StringWriter();
                {
                    XmlTextWriter wt = new XmlTextWriter(sw);
                    wt.WriteBinHex(password, 0, password.Length);
                    wt.Flush();
                }
                //                npassword.AppendChild(resp.CreateCDataSection(sw.ToString().ToLower()));
                npassword.InnerText = getMd5Hash(sw.ToString().ToLower() + userName);
                // add email
                XmlElement nemail = (XmlElement)nuser.AppendChild(resp.CreateElement("email"));
                nemail.AppendChild(resp.CreateCDataSection(pi.email));
                // add user name
                XmlElement nname = (XmlElement)nuser.AppendChild(resp.CreateElement("username"));
                nname.AppendChild(resp.CreateCDataSection(Convert.ToBase64String(System.Text.Encoding.UTF8.GetBytes(userName))));
                // add remote address
                XmlElement nrem = (XmlElement)nuser.AppendChild(resp.CreateElement("remote_addr"));
                string[] splitIp = remoteIp.Split('.');
                string hexIp = "";
                foreach (string ip in splitIp)
                {
                    int a = Convert.ToInt32(ip);
                    String ch = String.Format("{0:X2}", a);
                    hexIp += ch;
                }
                //                nrem.InnerText = hexIp.ToLower();
                nrem.AppendChild(resp.CreateCDataSection(hexIp.ToLower()));
                // add salt
                //                nuser.AppendChild(resp.CreateElement("salt")).AppendChild(resp.CreateCDataSection(""));

                // add generation
                XmlElement ngeneration = (XmlElement)nroot.AppendChild(resp.CreateElement("generation"));
                ngeneration.InnerText = "0.0440001487732";
                // add operation
                XmlElement noperation = (XmlElement)nroot.AppendChild(resp.CreateElement("operation"));
                noperation.AppendChild(resp.CreateCDataSection(""));
                //                noperation.InnerText = "<![CDATA[]]>";
            }
            catch (Exception e)
            {
                nroot.RemoveAll();
                ApiException.ErrorCode code = ApiException.ErrorCode.E_UNEXPECTED;
                if (e is ApiException)
                    code = (ApiException.ErrorCode)((ApiException)e).code;

                XmlElement ncode = (XmlElement)nroot.AppendChild(resp.CreateElement("errno"));
                ncode.InnerText = LegacyErrorConverter.convert(code);
                XmlElement nerror = (XmlElement)nroot.AppendChild(resp.CreateElement("error"));
                nerror.AppendChild(resp.CreateCDataSection(e.Message));
                if (userName != null)
                {
                    XmlElement nname = (XmlElement)nroot.AppendChild(resp.CreateElement("user")).AppendChild(resp.CreateElement("username"));
                    nname.AppendChild(resp.CreateCDataSection(Convert.ToBase64String(System.Text.Encoding.UTF8.GetBytes(userName))));
                }
            }
            resp.Save(context.Response.Output);

        }
    }
}