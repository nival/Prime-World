using System;
using System.Web;
using System.Xml;
using ZzimaBilling.API.Common;
using ZzimaBilling.API.Legacy.Command;
namespace ZzimaBilling.API.Legacy
{
    public class IISLegacyHandler : IHttpHandler
    {
        /// <summary>
        /// You will need to configure this handler in the web.config file of your 
        /// web and register it with IIS before being able to use it. For more information
        /// see the following link: http://go.microsoft.com/?linkid=8101007
        /// </summary>
        #region IHttpHandler Members

        public bool IsReusable { get { return true; } }

        public void ProcessRequest(HttpContext context)        
        {
            context.Response.ContentType = "text/xml";

            XmlDocument doc = new XmlDocument();
            string xml = context.Request.Params["xml"];
            if (xml == null)
                return;

            xml = xml.TrimEnd(' ','\n');
            xml = xml.Replace(Convert.ToChar(0x0).ToString(), "");
            if (xml.EndsWith("</"))
                xml += "xml>";

            try
            {
                doc.LoadXml(xml);
            }
            catch (Exception e)
            {
                throw new ApiException(ApiException.ErrorCode.E_INVALID_ARG, "Invalid xml. " + e.ToString());
            }
            
            XmlNode nd = doc.SelectSingleNode("/xml/*");
            
            ILegacyCommand cmd = LegacyCommandsFactory.Resolve(nd);
            cmd.Execute(context);

        }

        #endregion

    }
}
