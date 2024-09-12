using System;
using System.Web;
using System.Xml;
using System.IO;
using ZzimaBilling.API.DL.apidsTableAdapters;
using ZzimaBilling.API.DL;
using System.Security.Cryptography;
using System.Text;
using System.Data.SqlClient;
using System.Data.Sql;
using System.Web.Configuration;

namespace ZzimaBilling.API.Common
{
    public class GameleadsHandler : IHttpHandler
    {
        /// <summary>
        /// You will need to configure this handler in the web.config file of your 
        /// web and register it with IIS before being able to use it. For more information
        /// see the following link: http://go.microsoft.com/?linkid=8101007
        /// </summary>
        #region IHttpHandler Members

        public bool IsReusable
        {
            // Return false in case your Managed Handler cannot be reused for another request.
            // Usually this would be false in case you have some state information preserved per request.
            get { return true; }
        }

        public void ProcessRequest(HttpContext context)
        {
            string wDump = null;
            try
            {
                context.Response.ContentType = "text/xml";
                string skey = context.Request.Params["skey"];
                wDump = "At : " + DateTime.Now.ToString() + "\n";
                wDump += skey + "\n";
                XmlDocument doc = new XmlDocument();
                string xmlData = null;
                if (context.Request.Params["xml"] != null)
                {
                    xmlData = context.Request.Params["xml"];
                    wDump += "data is in context.Request.Params[\"xml\"]" + "\n";
                }
                else
                {
                    StreamReader reader = new StreamReader(context.Request.InputStream);
                    xmlData = reader.ReadToEnd();
                    wDump += "data is in plain xml" + "\n";
                }
                wDump += xmlData + "\n";

                doc.LoadXml(xmlData);

                XmlNode dateFromInUnix = doc.SelectSingleNode("/request/date_from");
                XmlNode dateToInUnix = doc.SelectSingleNode("/request/date_to");
                XmlNode projectRef = doc.SelectSingleNode("/request/project");
                if (dateFromInUnix == null || dateToInUnix == null || projectRef == null)
                {
                    context.Response.Write("<?xml version=\"1.0\"?><error>error code</error>");
                    return;
                }

                MD5 md5Hasher = MD5.Create();
                byte[] byteMd5inBin = md5Hasher.ComputeHash(Encoding.UTF8.GetBytes("passForGameleads" + dateFromInUnix.InnerText + dateToInUnix.InnerText));
                //byte[] byteMd5inHex = md5Hasher.ComputeHash(Encoding.UTF8.GetBytes("passForGameleads" + dateFromInUnix.InnerText + dateToInUnix.InnerText));

                StringBuilder sBuilder = new StringBuilder();
                for (int i = 0; i < byteMd5inBin.Length; i++)
                {
                    sBuilder.Append(byteMd5inBin[i].ToString("x2"));
                }
                if (sBuilder.ToString() == skey)
                {
                    wDump += "internal pass : " + sBuilder.ToString() + " is equal" + "\n";
                }
                else
                {
                    wDump += "internal pass : " + sBuilder.ToString() + " not equal" + "\n";
                }

                DateTime dateFrom = ConvertFromUnixTimestamp(Convert.ToDouble(dateFromInUnix.InnerText));
                DateTime dateTo = ConvertFromUnixTimestamp(Convert.ToDouble(dateToInUnix.InnerText));
                apids.sp_gui_getPaymentsByPartnerDataTable table;
                sp_gui_getPaymentsByPartnerTableAdapter ad = new sp_gui_getPaymentsByPartnerTableAdapter();
                Nullable<int> errorCode = 0;
                table = ad.GetData(dateFrom, dateTo, projectRef.InnerText, ref errorCode);

                //if (errorCode != 0) throw new ApiException((int)errorCode, "");

                XmlDocument resp = new XmlDocument();
                resp.AppendChild(resp.CreateXmlDeclaration("1.0", null, null));
                XmlElement root = (XmlElement)resp.AppendChild(resp.CreateElement("items"));

                for (int i = 0; i < table.Rows.Count; i++)
                {
                    XmlElement item = resp.CreateElement("item");

                    XmlElement id = resp.CreateElement("id");
                    id.InnerText = table[i].userid.ToString();
                    item.AppendChild(id);
                    XmlElement price = resp.CreateElement("price");
                    price.InnerText = table[i].amount.ToString();
                    item.AppendChild(price);
                    XmlElement date = resp.CreateElement("date");
                    date.InnerText = dateFromInUnix.InnerText;
                    item.AppendChild(date);

                    root.AppendChild(item);
                }
                StringWriter buff_writer = new StringWriter();
                resp.Save(buff_writer);
                buff_writer.Flush();
                string buffer = buff_writer.ToString().Replace("\r\n", "\n");
                buffer += "\n";
                context.Response.Output.Write(buffer);
            }
            catch (Exception e)
            {
                context.Response.Write("<?xml version=\"1.0\"?><error>error code</error>");
                string textCommand = ("insert into Gameleads(string) values (@wDump)");
                using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
                {
                    conn.Open();
                    SqlCommand insertGameLeads = new SqlCommand(textCommand, conn);
                    wDump += "at " + DateTime.Now.ToString() + " " + e.ToString();
                    insertGameLeads.Parameters.AddWithValue("@wDump", wDump);
                    insertGameLeads.ExecuteScalar();
                }
                return;
            }
            string textCommand2 = ("insert into Gameleads(string) values (@wDump)");
            using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
            {
                conn.Open();
                SqlCommand insertGameLeads = new SqlCommand(textCommand2, conn);
                insertGameLeads.Parameters.AddWithValue("@wDump", wDump);
                insertGameLeads.ExecuteScalar();
            }

            //context.Response.Write(String.Format("dateFrom : {0}, dateTo : {1}, projectRef : {2}", dateFrom, dateTo, projectRef.InnerText));
        }
        #endregion

        static DateTime ConvertFromUnixTimestamp(double timestamp)
        {
            DateTime origin = new DateTime(1970, 1, 1, 0, 0, 0, 0);
            return origin.AddSeconds(timestamp);
        }
        static double ConvertToUnixTimestamp(DateTime date)
        {
            DateTime origin = new DateTime(1970, 1, 1, 0, 0, 0, 0);
            TimeSpan diff = date - origin;
            return Math.Floor(diff.TotalSeconds);
        }
    }
}
