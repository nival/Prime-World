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
          <addUserMoney>
            <username>User Name</username>
            <money>Sum</money>
            <remoteaddr>IP adress</remoteaddr>
            <clientid>Client ID</clientid>
            <serviceid>Item ID</serviceid>
            <crc>CRC</crc>
            <operation>Operation description</operation>
          </addUserMoney>
        </xml>
    */     
    public class AddUserMoney : ILegacyCommand
    {
        private string userName; 
        private decimal money; 
        private string remoteaddr; 
        private string clientid; 
        private string serviceid; 
        private string crc;
        private string operation;

        public AddUserMoney(XmlNode nd): base(nd)
        {
        }

        public void Parse(XmlNode nd)
        {
            // get username
            XmlNode node = nd.SelectSingleNode("./username");
            if (node == null)
                throw new Exception("username is empty");
            userName = node.InnerText;

            node = nd.SelectSingleNode("./money");
            if (node == null)
                throw new Exception("money field is empty");
            money = Convert.ToDecimal(node.InnerText);

            node = nd.SelectSingleNode("./remoteaddr");
            if (node == null)
                throw new Exception("remoteaddr field is empty");
            remoteaddr = node.InnerText;

            node = nd.SelectSingleNode("./clientid");
            if (node == null)
                throw new Exception("remoteaddr field is empty");
            clientid = node.InnerText;

            node = nd.SelectSingleNode("./serviceid");
            if (node == null)
                throw new Exception("remoteaddr field is empty");
            serviceid = node.InnerText;

            node = nd.SelectSingleNode("./crc");
            if (node == null)
                throw new Exception("remoteaddr field is empty");
            crc = node.InnerText;

            node = nd.SelectSingleNode("./operation");
            if (node == null)
                throw new Exception("operation field is empty");
            operation = node.InnerText;

        }

        public override void Execute(HttpContext context)
        {
            XmlDocument resp = new XmlDocument();
            resp.CreateXmlDeclaration("1.0", "utf-8", null);
            XmlElement nroot = (XmlElement)resp.AppendChild(resp.CreateElement("xml"));
            try
            {
                Parse(request);
                String content = userName + ":" + ((int)money) + ":" + remoteaddr + ":" + clientid + ":" + serviceid + ":";
                Service svc = Service.legacyCheckCRC(context, clientid, crc, content);
                User.legacyReplenish(svc, userName, money, serviceid);

                money = User.legacyGetBalance(context, userName); 
                buildAnnotation(nroot, true);
            }
            catch (Exception e)
            {
                nroot.RemoveAll();
                // build error resp block
                ApiException.ErrorCode code = ApiException.ErrorCode.E_UNEXPECTED;
                if (e is ApiException)
                    code = (ApiException.ErrorCode)((ApiException)e).code;

                XmlElement nerror = (XmlElement)nroot.AppendChild(resp.CreateElement("error"));
                XmlElement ndesc = (XmlElement)nerror.AppendChild(resp.CreateElement("description"));
                ndesc.AppendChild(resp.CreateCDataSection(e.Message));
                XmlElement ncode = (XmlElement)nerror.AppendChild(resp.CreateElement("code"));
                ncode.InnerText = LegacyErrorConverter.convert(code);

                buildAnnotation(nroot, false);
            }
            resp.Save(context.Response.Output);
        }

        private void buildAnnotation(XmlElement root, bool succ)
        {
            XmlDocument resp = root.OwnerDocument;

            // build annotation block
            XmlElement nret = (XmlElement)root.AppendChild(resp.CreateElement("return"));
            if (userName != null)
            {
                XmlElement node = (XmlElement)nret.AppendChild(resp.CreateElement("username"));
                node.AppendChild(resp.CreateCDataSection(userName));
            }


            XmlElement ntrans = (XmlElement)nret.AppendChild(resp.CreateElement("transfer"));
            ntrans.InnerText = succ ? "1" : "0";

            XmlElement nmoney = (XmlElement)nret.AppendChild(resp.CreateElement("balance"));
            CultureInfo ci = CultureInfo.CreateSpecificCulture("en-GB");
            ci.NumberFormat.CurrencyGroupSeparator = "";
            ci.NumberFormat.CurrencyDecimalSeparator = ".";
            ci.NumberFormat.CurrencySymbol = "";
            nmoney.InnerText = money.ToString("C", ci);

            if (operation != null)
            {
                XmlElement node = (XmlElement)nret.AppendChild(resp.CreateElement("operation"));
                node.AppendChild(resp.CreateCDataSection(Convert.ToString(operation)));
            }
        }
    }
}
