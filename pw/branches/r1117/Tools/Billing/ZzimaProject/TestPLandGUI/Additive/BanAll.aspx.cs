using System;
using System.Collections.Generic;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Web.Configuration;
using System.Data;

public partial class Additive_BanAll : System.Web.UI.Page
{
    static List<ServiceRecord> lsSvc;
    class ServiceRecord
    {
        public ServiceRecord(int serviceidPar, string sericenamePar, bool subscrPar)
        {
            serviceid = serviceidPar;
            sericename = sericenamePar;
            subscr = subscrPar;
        }
        private int serviceid;
        public int SERVICEID
        {
            get { return serviceid; }
            set { serviceid = value; }
        }

        private string sericename;
        public string SERVICENAME
        {
            get { return sericename; }
            set { sericename = value; }
        }
        private bool subscr;
        public bool SUBSCR
        {
            get { return subscr; }
            set { subscr = value; }
        }
    }

    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void btnGetActiveList_Click(object sender, EventArgs e)
    {
        if (String.IsNullOrEmpty(txtUserName.Text)) return;

        using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        {
            SqlCommand getActiveList = new SqlCommand("sp_api_getServicesList", conn);
            getActiveList.CommandType = CommandType.StoredProcedure;
            getActiveList.Parameters.AddWithValue("@user", txtUserName.Text);
            getActiveList.Parameters.AddWithValue("@error", 0);
            SqlDataReader dr;
            try
            {
                conn.Open();
                dr = getActiveList.ExecuteReader();
                lsSvc = new List<ServiceRecord>();
                while (dr.Read())
                {
                    ServiceRecord rec = new ServiceRecord((int)dr["SERVICEID"], (string)dr["SERVICENAME"], Convert.ToBoolean(dr["SUBSCR"]));
                    lsSvc.Add(rec);
                }
            }
            catch (Exception ex)
            {
                lblResult.Text = ex.ToString();
                return;
            }
            chkBoxList.Items.Clear();
            foreach (ServiceRecord t in lsSvc)
            {
                ListItem item = new ListItem(t.SERVICENAME);
                if (t.SUBSCR) item.Selected = true;
                chkBoxList.Items.Add(item);
            }
        }
    }
    protected void btnSubscribe_Click(object sender, EventArgs e)
    {
        if (String.IsNullOrEmpty(txtUserName.Text)) return;
        using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        {
            try
            {
                conn.Open();
                for (int i = 0; i < chkBoxList.Items.Count; i++)
                {
                    if (chkBoxList.Items[i].Selected != lsSvc[i].SUBSCR)
                    {
                        if (chkBoxList.Items[i].Selected)
                        {
                            SqlCommand subscribeSvc = new SqlCommand("sp_api_subscribeUser", conn);
                            subscribeSvc.CommandType = CommandType.StoredProcedure;
                            subscribeSvc.Parameters.AddWithValue("@userName", txtUserName.Text);
                            subscribeSvc.Parameters.AddWithValue("@serviceName", chkBoxList.Items[i].Text);
                            subscribeSvc.Parameters.AddWithValue("@password", System.DBNull.Value);
                            subscribeSvc.Parameters["@password"].SqlDbType = SqlDbType.VarBinary;
                            subscribeSvc.Parameters.AddWithValue("@error", 0);
                            subscribeSvc.ExecuteNonQuery();
                        }
                        else
                        {
                            SqlCommand banSvc = new SqlCommand("sp_api_unsubscribeUser", conn);
                            banSvc.CommandType = CommandType.StoredProcedure;
                            banSvc.Parameters.AddWithValue("@userName", txtUserName.Text);
                            banSvc.Parameters.AddWithValue("@serviceName", chkBoxList.Items[i].Text);
                            banSvc.Parameters.AddWithValue("@error", 0);
                            banSvc.ExecuteNonQuery();
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                lblResult.Text = ex.ToString();
                return;
            }
            btnGetActiveList_Click(null, null);
        }
    }

    protected void btnBanAllSvcs_Click(object sender, EventArgs e)
    {
        if (String.IsNullOrEmpty(txtUserName.Text)) return;

        using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
        {
            conn.Open();
            try
            {
                for (int i = 0; i < chkBoxList.Items.Count; i++)
                {
                    SqlCommand banAllSvcs = new SqlCommand("sp_api_unsubscribeUser", conn);
                    banAllSvcs.CommandType = CommandType.StoredProcedure;
                    banAllSvcs.Parameters.AddWithValue("@userName", txtUserName.Text);
                    banAllSvcs.Parameters.AddWithValue("@serviceName", chkBoxList.Items[i].Text);
                    banAllSvcs.Parameters.AddWithValue("@error", 0);
                    banAllSvcs.ExecuteNonQuery();
                }
            }
            catch (Exception ex)
            {
                lblResult.Text = ex.ToString();
                return;
            }
            btnGetActiveList_Click(null, null);
        }
    }
}