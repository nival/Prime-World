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
using ZzimaBilling.AdminUI.BLL;
using ZzimaBilling.AdminUI.DAL;
using System.Linq;

namespace ZzimaBilling.Additive
{
    public partial class SignUsersPW : System.Web.UI.Page
    {
        static DataSet resUsers = new DataSet();
        protected void Page_Load(object sender, EventArgs e)
        {
            lblServiceName.Text = "Подписка на serviceName = " + ConfigurationManager.AppSettings["pwTestName"];
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

            if (String.IsNullOrEmpty(txtSubscribe.Text))
                return;
            string[] separators = new string[] { "\r\n" };
            string[] inputUsers = txtSubscribe.Text.Split(separators, StringSplitOptions.RemoveEmptyEntries);
            string serviceName = ConfigurationManager.AppSettings["pwTestName"];
            List<string> succedSub = new List<string>();
            int success = 0;

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
                        subscribeSvc.Parameters["@error"].Direction = ParameterDirection.Output;
                        subscribeSvc.ExecuteScalar();
                        //if (result != null)
                        //{
                        //    if (result.ToString().Length >= 38) succedSub.Add(inputUsers[i]);
                        //}
                        int error = Convert.ToInt32(subscribeSvc.Parameters["@error"].Value);
                        if (error == 0)
                        {
                            succedSub.Add(inputUsers[i]);
                            success++;
                        }
                        else succedSub.Add(error.ToString());
                    }
                }
                catch (Exception ex)
                {
                    lblWarn.Text = ex.ToString();
                    return;
                }
            }
            lblWarn.Text = "Удалось подписать " + success.ToString();
            gvSubcribed.DataSource = succedSub;
            gvSubcribed.DataBind();
        }
        protected void btnDeSubscribeFromTextbox_Click(object sender, EventArgs e)
        {
            if (String.IsNullOrEmpty(txtSubscribe.Text))
                return;
            string[] separators = new string[] { "\r\n" };
            string[] inputUsers = txtSubscribe.Text.Split(separators, StringSplitOptions.RemoveEmptyEntries);
            string serviceName = ConfigurationManager.AppSettings["pwTestName"];
            List<string> succedDeSub = new List<string>();
            int success = 0;

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
                        if (error == 0)
                        {
                            succedDeSub.Add(inputUsers[i]);
                            success++;
                        }
                        else succedDeSub.Add(error.ToString());
                    }
                }
                catch (Exception ex)
                {
                    lblWarn.Text = ex.ToString();
                    return;
                }
            }
            lblWarn.Text = "Удалось отписать " + success.ToString();
            gvSubcribed.DataSource = succedDeSub;
            gvSubcribed.DataBind();
        }

        protected void btnDeSubcribe_Click(object sender, EventArgs e)
        {
            lblWarn.Text = "";
            gvSubcribed.DataSource = null;
            gvSubcribed.DataBind();

            string textCommand = "update UserServices set active = 0 where serviceid = @svcid";

            string serviceName = ConfigurationManager.AppSettings["pwTestName"];
            int svcid = 0;
            using (BillingDataContext db = new BillingDataContext())
            {
                try
                {
                    svcid = db.Services.Where(serv => serv.name == serviceName).Select(serv => serv.id).SingleOrDefault<int>();
                }
                catch (Exception ex)
                {
                    lblWarn.Text = ex.ToString();
                }
            }
            using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
            {
                SqlCommand updUserServ = new SqlCommand(textCommand, conn);
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
                }
            }
            lblWarn.Text = "все отписаны успешно";
        }
    }
}