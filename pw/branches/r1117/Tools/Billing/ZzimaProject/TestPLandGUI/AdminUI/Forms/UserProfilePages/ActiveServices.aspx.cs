using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.SqlClient;
using System.Data;
using System.Web.Configuration;
using ZzimaBilling.AdminUI.DAL;
using ZzimaBilling.AdminUI.BLL;
using System.Net;

namespace ZzimaBilling.AdminUI.Forms.UserProfilePages
{
    public partial class ActiveServices : UserProfileGridViewPage
    {
        static List<ServiceRecord> lsSvc;
        static List<string> existSvcList;
        static UserGeneralInfoBLL user;
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
            if (!Page.IsPostBack)
            {
                user = UserDAL.GetUserGeneralInfo(this.UserID);
                BindCheckBoxes();
                chkTotalBan.Checked = user.FinalBan ?? false;
                if (user.TempBan != null && user.TempBan > DateTime.Now)
                {
                    lblBefore.Text = "Забанен до : ";
                    lblAfter.Text = "";
                    txtHoursTemp.Text = user.TempBan.ToString();
                    btnTempBan.Text = "Разбанить";
                    RegularExpressionValidator1.Enabled = false;
                }
                else
                {
                    lblBefore.Text = "Временный бан на ";
                    lblAfter.Text = " часов ";
                    btnTempBan.Text = "Забанить";
                    RegularExpressionValidator1.Enabled = true;
                }
            }
            if (employer.groupid == 4)
            {
                btnTempBan.Enabled = false;
                btnSubscribe.Enabled = false;
                btnBanAllSvcs.Enabled = false;
                chkTotalBan.Enabled = false;
                btnTempBan.Visible = false;
                btnSubscribe.Visible = false;
                btnBanAllSvcs.Visible = false;
                chkTotalBan.Visible = false;
            }
        }

        protected void btnSubscribe_Click(object sender, EventArgs e)
        {
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
                                subscribeSvc.Parameters.AddWithValue("@userName", user.Username);
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
                                banSvc.Parameters.AddWithValue("@userName", user.Username);
                                banSvc.Parameters.AddWithValue("@serviceName", chkBoxList.Items[i].Text);
                                banSvc.Parameters.AddWithValue("@error", 0);
                                banSvc.ExecuteNonQuery();
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    ShowMessage(true, "ошибка : " + ex.ToString(), null);
                    return;
                }
                BindCheckBoxes();
            }
        }
        public void BindCheckBoxes()
        {
            using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
            {
                SqlCommand getActiveList = new SqlCommand("sp_api_getServicesList", conn);
                getActiveList.CommandType = CommandType.StoredProcedure;
                getActiveList.Parameters.AddWithValue("@user", user.Username);
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
                    ShowMessage(true, "ошибка : " + ex.ToString(), null);
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

            using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
            {
                existSvcList = new List<string>();
                SqlCommand getOldList = new SqlCommand("sp_gui_getSvcsOnlyExists", conn);
                getOldList.CommandType = CommandType.StoredProcedure;
                getOldList.Parameters.AddWithValue("@userid", this.UserID);
                getOldList.Parameters.AddWithValue("@error", 0);
                SqlDataReader dr;
                try
                {
                    conn.Open();
                    dr = getOldList.ExecuteReader();
                    while (dr.Read())
                    {
                        string rec = (string)dr["SERVICENAME"];
                        existSvcList.Add(rec);
                    }
                }
                catch (Exception ex)
                {
                    ShowMessage(true, "ошибка : " + ex.ToString(), null);
                    return;
                }
                gvSvcsExists.DataSource = existSvcList;
                gvSvcsExists.DataBind();
            }
        }

        protected void btnBanAllSvcs_Click(object sender, EventArgs e)
        {
            using (SqlConnection conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString))
            {
                conn.Open();
                try
                {
                    for (int i = 0; i < chkBoxList.Items.Count; i++)
                    {
                        SqlCommand banAllSvcs = new SqlCommand("sp_api_unsubscribeUser", conn);
                        banAllSvcs.CommandType = CommandType.StoredProcedure;
                        banAllSvcs.Parameters.AddWithValue("@userName", user.Username);
                        banAllSvcs.Parameters.AddWithValue("@serviceName", chkBoxList.Items[i].Text);
                        banAllSvcs.Parameters.AddWithValue("@error", 0);
                        banAllSvcs.ExecuteNonQuery();
                    }
                }
                catch (Exception ex)
                {
                    ShowMessage(true, "ошибка : " + ex.ToString(), null);
                    return;
                }
                BindCheckBoxes();
            }
        }

        protected void btnSelectExisting_Click(object sender, EventArgs e)
        {
            foreach (ListItem li in chkBoxList.Items)
            {
                li.Selected = existSvcList.Contains(li.Text);
            }
        }

        protected void btnTempBan_Click(object sender, EventArgs e)
        {
            SqlConnection conn = null;
            try
            {
                if (btnTempBan.Text == "Забанить")
                {
                    int hours = Convert.ToInt32(txtHoursTemp.Text);

                    conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString);
                    conn.Open();
                    SqlCommand banTotal = new SqlCommand("sp_int_totalBanWithTemporary", conn);
                    banTotal.CommandType = CommandType.StoredProcedure;

                    banTotal.Parameters.AddWithValue("@user", user.Username);
                    banTotal.Parameters.AddWithValue("@empid", this.employer.id);
                    banTotal.Parameters.AddWithValue("@hours", hours);
                    int errorCode = 0;
                    banTotal.Parameters.AddWithValue("@error", errorCode);
                    banTotal.Parameters["@error"].Direction = ParameterDirection.InputOutput;
                    banTotal.ExecuteNonQuery();
                    errorCode = (int)banTotal.Parameters["@error"].Value;
                    if (errorCode != 0)
                    {
                        ShowMessage(true, "код ошибки : " + errorCode.ToString(), null);
                    }
                    else
                    {
                        user = UserDAL.GetUserGeneralInfo(this.UserID);
                        ShowMessage(false, String.Format("юзер забанен на {0} часов", hours), null);
                        if (CallKickPanel(user.ID))
                            ShowMessage(false, String.Format("юзер забанен на {0} часов", hours), null);
                        else
                            ShowMessage(false, String.Format("юзер забанен на {0} часов, но 'кик' из плашки недоступен", hours), null);
                        
                        lblBefore.Text = "Забанен до : ";
                        lblAfter.Text = "";
                        txtHoursTemp.Text = user.TempBan.ToString();
                        btnTempBan.Text = "Разбанить";
                        RegularExpressionValidator1.Enabled = false;

                    }
                }
                else
                {
                    conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString);
                    conn.Open();

                    SqlCommand banTotal = new SqlCommand("sp_int_unTotalBan", conn);
                    banTotal.CommandType = CommandType.StoredProcedure;

                    banTotal.Parameters.AddWithValue("@user", user.Username);
                    banTotal.Parameters.AddWithValue("@empid", this.employer.id);
                    banTotal.Parameters.AddWithValue("@removeTempBan", true);
                    int errorCode = 0;
                    banTotal.Parameters.AddWithValue("@error", errorCode);
                    banTotal.Parameters["@error"].Direction = ParameterDirection.InputOutput;
                    banTotal.ExecuteNonQuery();
                    errorCode = (int)banTotal.Parameters["@error"].Value;
                    if (errorCode != 0)
                    {
                        ShowMessage(true, "код ошибки : " + errorCode.ToString(), null);
                    }
                    else
                    {
                        ShowMessage(false, "бан снят", null);
                        lblBefore.Text = "Временный бан на ";
                        lblAfter.Text = " часов ";
                        txtHoursTemp.Text = "";
                        btnTempBan.Text = "Забанить";
                        RegularExpressionValidator1.Enabled = true;
                    }
                }
            }
            catch (Exception ex)
            {
                ShowMessage(true, "ошибка : " + ex.ToString(), null);
                return;
            }
            finally
            {
                conn.Dispose();
            }
        }

        protected void chkTotalBan_CheckedChanged(object sender, EventArgs e)
        {
            if (Page.IsPostBack)
            {
                if (chkTotalBan.Checked) //ban
                {
                    SqlConnection conn = null;
                    try
                    {
                        conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString);
                        conn.Open();

                        SqlCommand banTotal = new SqlCommand("sp_int_totalBanWithTemporary", conn);
                        banTotal.CommandType = CommandType.StoredProcedure;

                        banTotal.Parameters.AddWithValue("@user", user.Username);
                        banTotal.Parameters.AddWithValue("@empid", this.employer.id);
                        banTotal.Parameters.AddWithValue("@hours", DBNull.Value);
                        int errorCode = 0;
                        banTotal.Parameters.AddWithValue("@error", errorCode);
                        banTotal.Parameters["@error"].Direction = ParameterDirection.InputOutput;
                        banTotal.ExecuteNonQuery();
                        errorCode = (int)banTotal.Parameters["@error"].Value;
                        if (errorCode != 0)
                        {
                            ShowMessage(true, "код ошибки : " + errorCode.ToString(), null);
                        }
                        else
                        {
                            ShowMessage(false, "юзер успешно забанен", null);
                            chkTotalBan.Checked = true;
                            if (CallKickPanel(user.ID))
                                ShowMessage(false, "юзер успешно забанен", null);
                            else
                                ShowMessage(false, "юзер успешно забанен, но 'кик' из плашки недоступен", null);
                        }
                    }
                    catch (Exception ex)
                    {
                        ShowMessage(true, "ошибка : " + ex.ToString(), null);
                        return;
                    }
                    finally
                    {
                        conn.Dispose();
                    }
                }
                else //unban
                {
                    SqlConnection conn = null;
                    try
                    {
                        conn = new SqlConnection(WebConfigurationManager.ConnectionStrings["billiConnectionString"].ConnectionString);
                        conn.Open();

                        SqlCommand banTotal = new SqlCommand("sp_int_unTotalBan", conn);
                        banTotal.CommandType = CommandType.StoredProcedure;

                        banTotal.Parameters.AddWithValue("@user", user.Username);
                        banTotal.Parameters.AddWithValue("@empid", this.employer.id);
                        banTotal.Parameters.AddWithValue("@removeTempBan", DBNull.Value);
                        int errorCode = 0;
                        banTotal.Parameters.AddWithValue("@error", errorCode);
                        banTotal.Parameters["@error"].Direction = ParameterDirection.InputOutput;
                        banTotal.ExecuteNonQuery();
                        errorCode = (int)banTotal.Parameters["@error"].Value;
                        if (errorCode != 0)
                        {
                            ShowMessage(true, "код ошибки : " + errorCode.ToString(), null);
                        }
                        else
                        {
                            ShowMessage(false, "бан снят", null);
                            chkTotalBan.Checked = false;
                        }
                    }
                    catch (Exception ex)
                    {
                        ShowMessage(true, "ошибка : " + ex.ToString(), null);
                        return;
                    }
                    finally
                    {
                        conn.Dispose();
                    }
                }
            }
        }
        public bool CallKickPanel(int userid)
        {
            try
            {
                string requestUriString = System.Configuration.ConfigurationManager.AppSettings["urlForKick"];
                requestUriString += "user_id=" + userid.ToString();
                HttpWebRequest request = (HttpWebRequest)WebRequest.Create(requestUriString);
                request.KeepAlive = false;
                request.ProtocolVersion = HttpVersion.Version10;
                request.Method = "GET";
                request.Timeout = 3000;
                request.ContentType = "text/html";
                request.ContentLength = 1;
                HttpWebResponse response = (HttpWebResponse)request.GetResponse();
                return (response.StatusCode == HttpStatusCode.OK);
            }
            catch (Exception e)
            {
                return false;
            }
        }
    }
}