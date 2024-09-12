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
using System.Collections.Generic;
using ZzimaBilling.API.Common;
using ZzimaBilling.API.DL;
using ZzimaBilling.API.DL.apidsTableAdapters;
using ZzimaBilling.API.PL;

public partial class Additive_SignUsersToService : System.Web.UI.Page
{
    const int NumSvcIdColumn = 2;
    static DataSet resUsers = new DataSet();
    protected void Page_Load(object sender, EventArgs e)
    {
        string textCommand = ("select id, name, description from dbo.Services");
        using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        {
            conn.Open();
            SqlCommand getCbtSvcs = new SqlCommand(textCommand, conn);
            SqlDataReader dr = getCbtSvcs.ExecuteReader();
            gvCBTSvcs.DataSource = dr;
            gvCBTSvcs.DataBind();
        }
    }
    protected void gvCBTSvcs_SelectedIndexChanged(object sender, EventArgs e)
    {
        if (gvCBTSvcs.SelectedValue != null)
            lblWarn.Text = "";

        //SqlDataAdapter dataAdapter = new SqlDataAdapter();
        //string textCommand = "select top(200) u.name from UserServices us inner join Users u on u.id = us.userid where serviceid = @svcid and active = 1 order by u.name";
        //using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        //{
        //    conn.Open();
        //    SqlCommand getUsers = new SqlCommand(textCommand, conn);
        //    getUsers.Parameters.AddWithValue("@svcid", gvCBTSvcs.SelectedRow.Cells[NumSvcIdColumn].Text);
        //    dataAdapter.SelectCommand = getUsers;
        //    resUsers.Clear();
        //    dataAdapter.Fill(resUsers);
        //    gvSubcribed.DataSource = resUsers;
        //    gvSubcribed.DataBind();
        //}
        gvSubcribed.DataSource = null;
        gvSubcribed.DataBind();

    }
    protected void gvSubcribed_PageIndexChanging(object sender, GridViewPageEventArgs e)
    {
        gvSubcribed.PageIndex = e.NewPageIndex;
        gvSubcribed.DataSource = resUsers;
        gvSubcribed.DataBind();
    }
    protected void btnSubcribe_Click(object sender, EventArgs e)
    {
        gvSubcribed.DataSource = null;
        gvSubcribed.DataBind();
        if (gvCBTSvcs.SelectedValue == null)
        {
            lblWarn.Text = "Не выбран сервис";
            return;
        }

        if (String.IsNullOrEmpty(txtSubscribe.Text))
            return;
        string[] separators = new string[] { "\r\n" };
        string[] inputUsers = txtSubscribe.Text.Split(separators, StringSplitOptions.RemoveEmptyEntries);
        string serviceName = gvCBTSvcs.SelectedValue.ToString();
        List<string> succedSub = new List<string>();
        
        using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        {
            try
            {
                conn.Open();
                for (int i = 0; i < inputUsers.Length; i++)
                {
                    SqlCommand subscribeSvc = new SqlCommand("sp_api_subscribeUser", conn);
                    subscribeSvc.CommandType = CommandType.StoredProcedure;
                    subscribeSvc.Parameters.AddWithValue("@userName", inputUsers[i]);
                    subscribeSvc.Parameters.AddWithValue("@serviceName", serviceName);
                    subscribeSvc.Parameters.AddWithValue("@password", System.DBNull.Value);
                    subscribeSvc.Parameters["@password"].SqlDbType = SqlDbType.VarBinary;
                    subscribeSvc.Parameters.AddWithValue("@error", 0);
                    object result = subscribeSvc.ExecuteScalar();
                    if (result != null)
                    {
                        if (result.ToString().Length >= 38) succedSub.Add(inputUsers[i]);
                    }
                }
            }
            catch (Exception ex)
            {
                lblWarn.Text = ex.ToString();
                return;
            }
        }
        lblWarn.Text = "Удалось подписать " + succedSub.Count.ToString();
        gvSubcribed.DataSource = succedSub;
        gvSubcribed.DataBind();
    }
    protected void btnDeSubcribe_Click(object sender, EventArgs e)
    {
        lblWarn.Text = "";
        gvSubcribed.DataSource = null;
        gvSubcribed.DataBind();
        if (gvCBTSvcs.SelectedValue == null)
        {
            lblWarn.Text = "Не выбран сервис";
        }

        string textCommand = "update UserServices set active = 0 where serviceid = @svcid";
            
        using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        {
            SqlCommand updUserServ = new SqlCommand(textCommand, conn);
            int svcid = 0;
            if (gvCBTSvcs.SelectedRow != null)
            {
                int.TryParse(gvCBTSvcs.SelectedRow.Cells[NumSvcIdColumn].Text, out svcid);
            }
            if (svcid == 0) return;
            updUserServ.Parameters.AddWithValue("@svcid", svcid);
            conn.Open();
            int result = 0;
            try
            {
                result = updUserServ.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                lblWarn.Text = ex.ToString();
                return;
            }
        }
    }

    protected void btnDeSubscribeFromTextbox_Click(object sender, EventArgs e)
    {
        if (gvCBTSvcs.SelectedValue == null)
        {
            lblWarn.Text = "Не выбран сервис";
            return;
        }

        if (String.IsNullOrEmpty(txtSubscribe.Text))
            return;
        string[] separators = new string[] { "\r\n" };
        string[] inputUsers = txtSubscribe.Text.Split(separators, StringSplitOptions.RemoveEmptyEntries);
        string serviceName = gvCBTSvcs.SelectedValue.ToString();
        List<string> succedDeSub = new List<string>();

        using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        {
            try
            {
                conn.Open();
                for (int i = 0; i < inputUsers.Length; i++)
                {
                    SqlCommand banSvc = new SqlCommand("sp_api_unsubscribeUser", conn);
                    banSvc.CommandType = CommandType.StoredProcedure;
                    banSvc.Parameters.AddWithValue("@userName", inputUsers[i]);
                    banSvc.Parameters.AddWithValue("@serviceName", serviceName);
                    banSvc.Parameters.Add(new SqlParameter("@error", SqlDbType.Int, int.MaxValue));
                    banSvc.Parameters["@error"].Direction = ParameterDirection.Output;
                    banSvc.ExecuteNonQuery();
                    int error = Convert.ToInt32(banSvc.Parameters["@error"].Value);
                    if (error == 0) succedDeSub.Add(inputUsers[i]);
                }
            }
            catch (Exception ex)
            {
                lblWarn.Text = ex.ToString();
                return;
            }
        }
        lblWarn.Text = "Удалось отписать " + succedDeSub.Count.ToString();
        gvSubcribed.DataSource = succedDeSub;
        gvSubcribed.DataBind();
    }
}
