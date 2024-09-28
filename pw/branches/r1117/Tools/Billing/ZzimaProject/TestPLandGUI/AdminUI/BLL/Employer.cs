using System;
using System.Data;
using System.Configuration;
using System.Collections.Generic;
using System.Data.Linq;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.DAL;
using System.Text;
using System.Security.Cryptography;

namespace ZzimaBilling.AdminUI.BLL
{
    public class Employer
    {
        public static string SESSION_KEY = "employerProfile";

        private int _id;
        private int _groupid;
        private string _name;

        public int id { get { return _id; } }
        public int groupid { get { return _groupid; } }
        public string name { get { return _name; } }

        public Employer(int id, int groupid, string name)
        {
            this._id = id;
            this._groupid = groupid;
            this._name = name;
        }

        public static byte[] generateHash(string password)
        {
            byte[] decoded = Encoding.UTF8.GetBytes(password);
            MD5 md5Hasher = MD5.Create();
            return md5Hasher.ComputeHash(decoded, 0, decoded.Length);
        }

        public static byte[] getMd5HashPassword(string user, byte[] password)
        {
            if (password == null)
                return null;
            StringBuilder sBuilder = new StringBuilder();
            for (int i = 0; i < password.Length; i++)
                sBuilder.Append(password[i].ToString("x2"));
            sBuilder.ToString();

            byte[] hashPassword = Employer.generateHash(sBuilder.ToString() + user.ToLower());
            return hashPassword;
        }

        public void writeOff( string password, int userId, decimal amount, int paymentSystem, string reason)
        {
            EmployeeDAL.writeOff(_id, generateHash(password), userId, paymentSystem, amount, reason);
        }
            
        public List<PromoCodesBLL> generatePromocodes(decimal amount, int count, string reason)
        {
            using (BillingSPDataContext db = new BillingSPDataContext())
            {
                int? error = -1;
                ISingleResult<sp_gui_generatePromocodesResult> results = db.sp_gui_generatePromocodes(_id, count, amount, reason, ref error);
                List<PromoCodesBLL> prCodeslst = new List<PromoCodesBLL>();

                foreach (sp_gui_generatePromocodesResult prCodeItem in results)
                {
                    prCodeslst.Add(new PromoCodesBLL
                    {
                        Code = prCodeItem.code,
                        Amount = prCodeItem.amount,
                        GeneratedAt = prCodeItem.generatedat
                    });
                }
                return prCodeslst;
            }
        }
    }
}
