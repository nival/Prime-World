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

namespace ZzimaBilling.API.Common
{
    public class SerializeHelper
    {
        public static byte[] date2s(DateTime value)
        {
            return Encoding.UTF8.GetBytes(value.ToString("yyyy/MM/dd hh:mm:ss", DateTimeFormatInfo.InvariantInfo));
        }

        public static byte[] decimal2s(decimal value)
        {
            return Encoding.UTF8.GetBytes(value.ToString("F", CultureInfo.InvariantCulture));
        }

        public static byte[] bool2s(bool value)
        {
            return Encoding.UTF8.GetBytes(value ? "1" : "0");
        }

        public static byte[] int2s(int value)
        {
            return Encoding.UTF8.GetBytes(value.ToString());
        }

        public static byte[] string2s(string value)
        {
            if (value!=null)
                return Encoding.UTF8.GetBytes(value);
            else
                return  new byte[]{};
        }

        public static MemoryStream o2s(MemoryStream ss, object val)
        {
            if (val != null)
            {
                byte[] buf = null;
                if (val.GetType() == typeof(string))
                    buf = string2s((string)val);
                else if (val.GetType() == typeof(int))
                    buf = int2s((int)val);
                else if (val.GetType() == typeof(DateTime))
                    buf = date2s((DateTime)val);
                else if (val.GetType() == typeof(decimal))
                    buf = decimal2s((decimal)val);
                else if (val.GetType() == typeof(bool))
                    buf = bool2s((bool)val);

                if (buf != null)
                    ss.Write(buf, 0, buf.Length);
            }
            return ss;
        }
    }
}
