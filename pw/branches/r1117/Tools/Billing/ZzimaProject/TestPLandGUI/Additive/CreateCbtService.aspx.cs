using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Data.SqlClient;
using System.Data.Sql;
using System.Web.Configuration;
using System.Security.Cryptography;
using System.Text;
using System.IO;

public partial class AdminUI_Forms_CreateCbtService : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void Button1_Click(object sender, EventArgs e)
    {
        string textCommand = "INSERT INTO dbo.Services(name,description,cbtMode,password,currencyid,independent,trusted) " +
             "VALUES(@svcName,@svcDescr,@IsCBT,cast(@passw as varbinary(80)),NULL,@IsIndep,0)";
        
        using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        {
            conn.Open();
            SqlCommand insServ = new SqlCommand(textCommand, conn);
            insServ.Parameters.AddWithValue("@svcName", txtServName.Text);
            insServ.Parameters.AddWithValue("@svcDescr", txtServDescr.Text);
            insServ.Parameters.AddWithValue("@IsCBT", chkIsCBT.Checked ? "1" : "0");
            insServ.Parameters.AddWithValue("@passw", getMd5Hash(txtPassword.Text));
            insServ.Parameters.AddWithValue("@IsIndep", chkIsIndependent.Checked ? "1" : "0");
            int result = 0;
            try
            {
                result = insServ.ExecuteNonQuery();
            }
            catch(Exception ex) 
            {
                lblResult.Text = ex.ToString();
                return;
            }
        }
    }
    static string getMd5Hash(string input)
    {
        // Create a new instance of the MD5CryptoServiceProvider object.
        MD5 md5Hasher = MD5.Create();

        // Convert the input string to a byte array and compute the hash.
        byte[] data = md5Hasher.ComputeHash(Encoding.Default.GetBytes(input));

        // Create a new Stringbuilder to collect the bytes
        // and create a string.
        StringBuilder sBuilder = new StringBuilder();

        // Loop through each byte of the hashed data 
        // and format each one as a hexadecimal string.
        for (int i = 0; i < data.Length; i++)
        {
            sBuilder.Append(data[i].ToString("x2"));
        }

        // Return the hexadecimal string.
        return sBuilder.ToString();
    }
}
