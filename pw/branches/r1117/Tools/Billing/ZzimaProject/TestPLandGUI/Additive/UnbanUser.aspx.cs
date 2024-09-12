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

public partial class Additive_UnbanUser : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void btnGetReason_Click(object sender, EventArgs e)
    {
        if (String.IsNullOrEmpty(txtUserName.Text) || String.IsNullOrEmpty(txtSvcName.Text))
        {
            lblResult.Text = "Неправильно заполнены поля";
            return;
        }
        string textCommand =
        @"if (not exists (select * from Users where name = @userName)) select 'no123user' else if (not exists (select * from Services where name = @svcName)) select 'no123service' else " +
        " select banReason from UserServices us inner join Services s on us.serviceid = s.id inner join Users u on u.id = us.userid where u.name = @userName and s.name = @svcName";

        using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        {
            conn.Open();
            SqlCommand getReason = new SqlCommand(textCommand, conn);
            getReason.Parameters.AddWithValue("@userName", txtUserName.Text);
            getReason.Parameters.AddWithValue("@svcName", txtSvcName.Text);
            string result = "";
            try
            {
                result = getReason.ExecuteScalar().ToString();
            }
            catch (Exception ex)
            {
                lblResult.Text = ex.ToString();
                return;
            }
            if (result == "no123user")
                lblResult.Text = "Нет такого пользователя";
            else if (result == "no123service")
            {
                lblResult.Text = "Нет такого сервиса";
            }
            else
            {
                if (String.IsNullOrEmpty(result))
                    lblResult.Text = "Reason = null или пустая строка";
                else
                    lblResult.Text = result;
            }           
        }
    }
    protected void btnUnban_Click(object sender, EventArgs e)
    {
        if (String.IsNullOrEmpty(txtUserName.Text) || String.IsNullOrEmpty(txtSvcName.Text))
        {
            lblResult.Text = "Неправильно заполнены поля";
            return;
        }
        string textCommandCheck = @"if (not exists (select * from Users where name = @userName)) select 'no123user' else if (not exists (select * from Services where name = @svcName)) select 'no123service' else select 'both123exists'";
        string textCommandUpdate = "update UserServices set ban = 0, banReason = NULL where userid = (select id from Users where name = @userName) and serviceid = (select id from Services where name = @svcName)";

        using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        {
            conn.Open();
            SqlCommand checkCommand = new SqlCommand(textCommandCheck, conn);
            checkCommand.Parameters.AddWithValue("@userName", txtUserName.Text);
            checkCommand.Parameters.AddWithValue("@svcName", txtSvcName.Text);
            string checkResult = "";
            try
            {
                checkResult = checkCommand.ExecuteScalar().ToString();
            }
            catch (Exception ex)
            {
                lblResult.Text = ex.ToString();
                return;
            }
            if (checkResult == "no123user")
            {
                lblResult.Text = "Нет такого пользователя";
                return;
            }
            if (checkResult == "no123service")
            {
                lblResult.Text = "Нет такого сервиса";
                return;
            }  
            
            SqlCommand unbanCommand = new SqlCommand(textCommandUpdate, conn);
            unbanCommand.Parameters.AddWithValue("@userName", txtUserName.Text);
            unbanCommand.Parameters.AddWithValue("@svcName", txtSvcName.Text);
            int result = 0;
            try
            {
                result = unbanCommand.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                lblResult.Text = ex.ToString();
                return;
            }
            if (result == 1)
                lblResult.Text = txtUserName.Text + " \"разбанен\"";
        }
    }
}
