using System;
using System.Data;
using System.Configuration;
using System.Globalization;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml;
using System.IO;
using ZzimaBilling.API.Common;
using ZzimaBilling.API.BL;
using ZzimaBilling.API.PL;

namespace ZzimaBilling.API.Legacy.Command
{
    /*
    <xml>
        <getUserMoney>
            <username>User Name</username>
        </getUserMoney>
    </xml>

     */
    public class GetUserMoney : ILegacyCommand
    {
        private string userName;

        public GetUserMoney(XmlNode nd): base(nd)
        {
        }

        public void Parse(XmlNode nd)
        {
            // get username
            XmlNode node = nd.SelectSingleNode("./username");
            if (node == null)
                throw new Exception("username is empty");

            userName = node.InnerText;
        }

        public override void Execute(HttpContext context)
        {
            XmlDocument resp = new XmlDocument();
            resp.CreateXmlDeclaration("1.0", "utf-8", null);
            XmlElement nroot = (XmlElement)resp.AppendChild(resp.CreateElement("xml"));
            try
            {
                Parse(request);

                decimal balance = User.legacyGetBalance(context, userName);

                XmlElement nreturn = (XmlElement)nroot.AppendChild(resp.CreateElement("return"));

                // add user name
                XmlElement nname = (XmlElement)nreturn.AppendChild(resp.CreateElement("username"));
                nname.AppendChild(resp.CreateCDataSection(userName));

                // add balance
                XmlElement nbalance = (XmlElement)nreturn.AppendChild(resp.CreateElement("money"));
                CultureInfo ci = CultureInfo.CreateSpecificCulture("en-GB");
                ci.NumberFormat.CurrencyGroupSeparator = "";
                ci.NumberFormat.CurrencyDecimalSeparator = ".";
                ci.NumberFormat.CurrencySymbol = "";
                nbalance.InnerText = balance.ToString("C", ci);

                XmlElement noperation = (XmlElement)nreturn.AppendChild(resp.CreateElement("operation"));
                noperation.AppendChild(resp.CreateCDataSection(""));
            }
            catch (Exception e)
            {
                nroot.RemoveAll();
                ApiException.ErrorCode code = ApiException.ErrorCode.E_UNEXPECTED;
                if (e is ApiException)
                    code = (ApiException.ErrorCode)((ApiException)e).code;

                XmlElement nerror = (XmlElement)nroot.AppendChild(resp.CreateElement("error"));
                XmlElement ndesc = (XmlElement)nerror.AppendChild(resp.CreateElement("description"));
                ndesc.AppendChild(resp.CreateCDataSection(e.Message));
                XmlElement ncode = (XmlElement)nerror.AppendChild(resp.CreateElement("code"));
                ncode.InnerText = LegacyErrorConverter.convert(code);
                nerror.AppendChild(resp.CreateElement("operation"));
            }

            nroot.AppendChild(resp.CreateElement("generation")).InnerText = "10";

            StringWriter buff_writer = new StringWriter();
            resp.Save(buff_writer);
            buff_writer.Flush();
            string buffer = buff_writer.ToString().Replace("\r\n", "\n");
            buffer += "\n";

            context.Response.Output.Write(buffer);
        }
    }
}