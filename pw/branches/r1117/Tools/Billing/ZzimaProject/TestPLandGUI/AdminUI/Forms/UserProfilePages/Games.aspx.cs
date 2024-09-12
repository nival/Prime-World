using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;
using ZzimaBilling.AdminUI.BLL;
using System.Collections.Generic;
using ZzimaBilling.AdminUI.DAL;

namespace ZzimaBilling.AdminUI.Forms.UserProfilePages
{
    public partial class Games : UserProfileGridViewPage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            #region Prev version
            //if (!String.IsNullOrEmpty(UserId))
            //{
            //    int userID = Convert.ToInt32(UserId);
            //    RenderLastSessions(UserDAL.GetLastSessions(userID));
            //} 
            #endregion
            this.gridView = gvLastSessions;
            SetPagerButtonStates(gvPagerRow);

            if (!IsPostBack)
            {
                GetRowsCount();
                UpdatePagerInfo();
            }
        }

        private void GetRowsCount()
        {
            RowsCount = UserDAL.GetLastSessions(UserID).Count;
            PagesCount = RowsCount / gvLastSessions.PageSize + (RowsCount % gvLastSessions.PageSize > 0 ? 1 : 0);
        }

        protected void gvLastSessions_RowCreated(object sender, GridViewRowEventArgs e)
        {
            base.GridViewSortImages(sender, e);
        }

        protected void gvLastSessions_Sorting(object sender, GridViewSortEventArgs e)
        {
            if (CurrentSortExpression == e.SortExpression.ToString())
            {
                if (CurrentSortDirection == "asc")
                    CurrentSortDirection = "desc";
                else
                    CurrentSortDirection = "asc";
            }
            else
            {
                CurrentSortExpression = e.SortExpression.ToString();
                CurrentSortDirection = "asc";
            }
        }

        #region Prev version
        //protected void RenderLastSessions(List<LastGameSessionBLL> lastSessions)
        //{
        //    if (lastSessions.Count > 0)
        //    {
        //        gvLastSessions.DataSource = lastSessions;
        //        gvLastSessions.DataBind();
        //    }
        //    else
        //    {
        //        lastSessions.Add(new LastGameSessionBLL 
        //        { 
        //            ID=0,
        //            Name=string.Empty,
        //            LastSession=DateTime.Now
        //        });
        //        gvLastSessions.DataSource = lastSessions;
        //        gvLastSessions.DataBind();
        //    }
        //}

        //protected List<LastGameSessionBLL> GenerateList()
        //{
        //    List<LastGameSessionBLL> list = new List<LastGameSessionBLL>();
        //    for (int i = 1; i < 10; i++)
        //    { 
        //        LastGameSessionBLL item=new LastGameSessionBLL
        //        {
        //            Name="Game "+i.ToString(),
        //            LastSession=DateTime.Now
        //        };
        //        list.Add(item);
        //    }
        //    return list;
        //} 
        #endregion
    }
}
